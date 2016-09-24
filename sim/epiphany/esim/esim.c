/* Epiphany eMesh functional simulator
   Copyright (C) 2014 Adapteva
   Contributed by Ola Jeppsson

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */


/** @todo Check address overflow (addr+nr_bytes) */

/*@todo rename es_tx_one_* to something better */


/* Need these for correct cpu struct */
#define WANT_CPU epiphanybf
#define WANT_CPU_EPIPHANYBF

#include "sim-main.h"
#include "mem-barrier.h"

#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>

/** @todo Standard errnos should be sufficient for now */
/* Errors are returned as negative numbers. */
#include <errno.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/mman.h>
#include <string.h>
#include <fcntl.h>
#include <sched.h>
#include <sys/file.h>

#include <stdio.h>

#include <pthread.h>

#include "esim.h"
#include "esim-int.h"

/*! Get core index in shared memory
 *
 * @warning Does not range check
 *
 * @param[in] esim   ESIM handle
 * @param[in] coreid Coreid
 *
 * @return Core index in shared memory
 */
static signed
es_shm_core_index(const es_state *esim, unsigned coreid)
{
  signed row_offset, col_offset;
  row_offset = ES_CORE_ROW(coreid) - ES_NODE_CFG.row_base;
  col_offset = ES_CORE_COL(coreid) - ES_NODE_CFG.col_base;

  return row_offset*ES_CLUSTER_CFG.cols_per_node + col_offset;
}

/*! Get pointer to core mem
 *
 * @param[in] esim   ESIM handle
 * @param[in] coreid Coreid
 *
 * @return Pointer to start of Epiphany cores memory, or NULL
 */
volatile static uint8_t *
es_shm_core_base(const es_state *esim, unsigned coreid)
{
  signed offset = es_shm_core_index(esim, coreid);
  if (offset < 0 || offset > (signed) ES_CLUSTER_CFG.cores_per_node)
    return NULL;

  return esim->cores_mem + ((size_t) offset) *
   (ES_SHM_CORE_STATE_SIZE+ES_CLUSTER_CFG.core_mem_region);
}

/*! Get node that holds this address. Must be a global address
 *
 * @param[in] esim   ESIM handle
 * @param[in] addr   target (Epiphany) memory address
 *
 * @return Simulator node where addr is located
 */
static signed
es_addr_to_node(const es_state *esim, uint32_t addr)
{
  unsigned coreid;
  signed row_offset, col_offset, node;

  if (ES_ADDR_IS_EXT_RAM(addr))
    {
      node = ES_CLUSTER_CFG.ext_ram_node;
      goto out;
    }

  coreid = ES_ADDR_TO_CORE(addr);

  row_offset = ES_CORE_ROW(coreid) - ES_CLUSTER_CFG.row_base;
  col_offset = ES_CORE_COL(coreid) - ES_CLUSTER_CFG.col_base;

  if (row_offset < 0 || col_offset < 0)
    {
      node = -EINVAL;
      goto out;
    }

  node = (row_offset/ES_CLUSTER_CFG.rows_per_node) *
	 (ES_CLUSTER_CFG.cols / ES_CLUSTER_CFG.cols_per_node) +
	 (col_offset / ES_CLUSTER_CFG.cols_per_node);

  if (node >= ES_CLUSTER_CFG.nodes)
    {
      node = -EINVAL;
      goto out;
    }

out:
#ifdef ES_DEBUG
  fprintf(stderr, "es_addr_to_node: addr=0x%8x node=%d\n", addr, node);
#endif
  return node;
}


/*! Translate target (Epiphany) address to simulator address
 *
 * @param[in]  esim   ESIM handle
 * @param[out] transl Simulator address
 * @param[in]  addr   target (Epiphany) memory address
 */
static void
es_addr_translate(const es_state *esim, es_transl *transl, uint32_t addr)
{
  uint8_t *tmp_ptr;
  signed node;

  if (es_initialized(esim) != ES_OK)
    {
      fprintf(stderr, "ESIM: Not initialized\n");
      transl->location = ES_LOC_INVALID;
      return;
    }

  /* TESTSET instruction requires requested address to be global */
  transl->addr_was_global = ES_ADDR_IS_GLOBAL(addr);

  addr = ES_ADDR_TO_GLOBAL(addr);
  transl->addr = addr;
  if ((node = es_addr_to_node(esim, addr)) < 0)
    {
      transl->location = ES_LOC_INVALID;
      return;
    }
  transl->node = node;

  transl->coreid = ES_ADDR_TO_CORE(addr);

  if (transl->node == ES_NODE_CFG.rank)
    {
      if (ES_ADDR_IS_EXT_RAM(addr))
	{
	  transl->location = ES_LOC_RAM;
	  transl->mem = ((uint8_t *) esim->ext_ram) +
	   (addr % ES_CLUSTER_CFG.ext_ram_size);
	  transl->in_region = ES_CLUSTER_CFG.ext_ram_size -
	   (addr % ES_CLUSTER_CFG.ext_ram_size);

	}
      else
	{
	  tmp_ptr = ((uint8_t *) esim->cores_mem) +
	    (es_shm_core_index(esim, transl->coreid) *
	      (ES_SHM_CORE_STATE_SIZE+ES_CLUSTER_CFG.core_mem_region)) +
	      ES_SHM_CORE_STATE_HEADER_SIZE;
	  transl->cpu = (sim_cpu *) tmp_ptr;
	  if (ES_ADDR_IS_MMR(addr))
	    {
	      if (addr % 4)
		{
		  /* Unaligned */
		  /** @todo ES_LOC_UNALIGNED would be more accurate */
		  transl->location = ES_LOC_INVALID;
		}
	      else
		{
		  transl->location = ES_LOC_SHM_MMR;
		  transl->reg = (addr & (ES_CORE_MMR_SIZE-1)) >> 2;
		  /* Point mem to sim cpu struct */
		  /** @todo Could optimize this so that entire region is one
		     transaction */
		  transl->in_region = 4;
		}
	    }
	  else
	    {
	      transl->location = ES_LOC_SHM;
	      transl->mem =
	       ((uint8_t *) esim->cores_mem) +
		(es_shm_core_index(esim, transl->coreid) *
		  (ES_SHM_CORE_STATE_SIZE+ES_CLUSTER_CFG.core_mem_region)) +
		  ES_SHM_CORE_STATE_SIZE +
		  (addr % ES_CLUSTER_CFG.core_mem_region);

	      /** @todo We have to check on which side of the memory mapped
	       * register we are and take that into account.
	       */
	      transl->in_region = (ES_CLUSTER_CFG.core_mem_region) -
		(addr % ES_CLUSTER_CFG.core_mem_region);
	    }
	}
    }
  else /* if (transl->node != ES_NODE_CFG.rank) */
    {
#if WITH_EMESH_NET
      es_net_addr_translate(esim, transl, addr);
#else
      transl->location = ES_LOC_INVALID;
#endif
    }
#ifdef ES_DEBUG
  /** @todo Revisit when adding network support */
  fprintf(stderr, "es_addr_translate: location=%d addr=0x%8x in_region=%ld"
	  " coreid=%d node=%d mem=0x%016lx\n reg=%d shm_offset=0x%016lx\n",
	  transl->location, transl->addr, transl->in_region, transl->coreid,
	  transl->node, (uint64_t) transl->mem, transl->reg,
	  transl->mem-esim->cores_mem);
#endif
}

/*! Translate next target (Epiphany) region address to simulator address
 *
 * @param[in]     esim   ESIM handle
 * @param[in,out] transl Simulator address
 */
static void
es_addr_translate_next_region(const es_state *esim, es_transl *transl)
{
  es_addr_translate(esim, transl, transl->addr+transl->in_region);
}

static int
es_tx_one_shm_load(es_state *esim, es_transaction *tx)
{
  size_t n = min(tx->remaining, tx->sim_addr.in_region);
  memmove(tx->target, tx->sim_addr.mem, n);
  tx->target += n;
  tx->remaining -= n;

  /** @todo Should we return nr of bytes ? */
  return ES_OK;
}


/*! Perform one store to SHM, and advance transaction state
 *
 * @param[in]     esim   ESIM handle
 * @param[in,out] tx     Transaction
 *
 * @return ES_OK on success
 */
static int
es_tx_one_shm_store(es_state *esim, es_transaction *tx)
{
  uint32_t i, invalidate;
  size_t n = min(tx->remaining, tx->sim_addr.in_region);
  memmove(tx->sim_addr.mem, tx->target, n);
  tx->target += n;
  tx->remaining -= n;
  if (tx->sim_addr.coreid == esim->coreid && esim->this_core_cpu_state)
    {
      /* Invalidate all instructions in the range.
       * Instructions are either 2 or 4 bytes long and must be half-word
       * aligned */
      for (i = 0; i < n+1; i += 2)
	{
	  invalidate = ((i+tx->addr) & ~1);
#ifdef ES_DEBUG
	  fprintf(stderr, "Invalidating %08x\n", invalidate);
#endif
	  epiphanybf_scache_invalidate((sim_cpu *) esim->this_core_cpu_state,
				       invalidate);
        }
    }
  else if (tx->sim_addr.location == ES_LOC_SHM)
    {
      /* Signal other CPU simulator a write from another core did occur so that
       * it can flush its scache.
       */
      MEM_BARRIER();
      tx->sim_addr.cpu->external_write = 1;
    }

  return ES_OK;
}


/*! Perform one TESTSET to SHM, and advance transaction state
 *
 * @param[in]     esim   ESIM handle
 * @param[in,out] tx     Transaction
 *
 * @return ES_OK on success
 */
static int
es_tx_one_shm_testset(es_state *esim, es_transaction *tx)
{
  uint32_t tmp;
  uint32_t *target;

  target = (uint32_t *) tx->target;

  /* TESTSET requires that requested addr is global */
  if (!tx->sim_addr.addr_was_global)
    return -EINVAL;

  /* Only word size is supported */
  if (tx->remaining != 4)
    return -EINVAL;

  /* Must be word aligned */
  if (tx->sim_addr.addr % 4)
    return -EINVAL;

  /* addr cannot reside in RAM, must be in on-chip memory  */
  if (tx->sim_addr.location != ES_LOC_SHM)
    return -EINVAL;

  tmp = es_cas32((uint32_t *) tx->sim_addr.mem, 0, *target);
  *target = tmp;

  tx->target += 4;
  tx->remaining -= 4;

  /* Signal other CPU simulator a write from another core did occur so that
   * it can invalidate its scache.
   */
  if (tx->sim_addr.coreid != esim->coreid)
    {
      /* Signal other CPU simulator a write from another core did occur so that
       * it can flush its scache.
       */
      MEM_BARRIER();
      tx->sim_addr.cpu->external_write = 1;
    }

  return ES_OK;
}

/*! Perform one load or store to MMR, and advance transaction state
 *
 * @param[in]     esim   ESIM handle
 * @param[in,out] tx     Transaction
 *
 * @return ES_OK on success
 */
__attribute__ ((visibility("hidden")))
int
es_tx_one_shm_mmr(es_state *esim, es_transaction *tx)
{
  int reg, n;
  uint32_t *target;
  sim_cpu *current_cpu;

  current_cpu = tx->sim_addr.cpu;

  target = (uint32_t *) tx->target;

  /*
   * @todo Writes are racy by design. We need to verify that this is the
   * correct behavior when we get access to the real hardware.
  */

  /* Alignment was checked in es_addr_translate.
   * Hardware doesn't seem to support reading partial regs so neither do we.
   */
  if (tx->remaining < 4)
    return -EINVAL;

  reg = tx->sim_addr.reg;

  switch (tx->type)
    {
    case ES_REQ_LOAD:
      if (reg < ES_EPIPHANY_NUM_GPRS &&
	  tx->sim_addr.coreid != esim->coreid &&
	  epiphany_cpu_is_active(current_cpu))
	{
	  /* Reading directly from the general-purpose registers by an external
	   * agent is not supported while the CPU is active.
	   * @todo It is unclear if this is allowed from local core so allow it
	   * for now.
	   */
	  n = -EINVAL;
	}
      else
	{
	  *target = epiphanybf_h_all_registers_get(current_cpu, reg);
	  n = 4;
	}
      break;
    case ES_REQ_STORE:
      /* If target cpu is local cpu, we can do the write immediately,
       * otherwise we need to serialize it on the target */
      if (tx->sim_addr.coreid == esim->coreid)
	epiphanybf_h_all_registers_set(current_cpu, reg, *target);
      else
	{
	  CPU_SCR_WRITESLOT_LOCK();
	  while (!CPU_SCR_WRITESLOT_EMPTY())
	    CPU_SCR_WRITESLOT_WAIT();
	  current_cpu->scr_remote_write_reg = reg;
	  current_cpu->scr_remote_write_val = *target;
	  CPU_SCR_WAKEUP_SIGNAL();
	  CPU_SCR_WRITESLOT_RELEASE();
	}

      n = 4;
      break;
    /*! @todo Implement (if supported by hardware?) */
    /* case ES_REQ_TESTSET: */
    default:
      n = -EINVAL;
    }
  if (n != 4)
    {
      return -EINVAL;
    }
  tx->target += n;
  tx->remaining -= n;

  /** @todo Should we return nr of bytes ? */
  return ES_OK;
}

/*! Perform one portion of transaction (might span more than one region)
 *
 * @param[in]     esim   ESIM handle
 * @param[in,out] tx     Transaction
 *
 * @return ES_OK on success
 */
static int
es_tx_one(es_state *esim, es_transaction *tx)
{
  /** @todo Use function vtable instead? */
  switch (tx->sim_addr.location)
    {
    case ES_LOC_SHM:
    case ES_LOC_RAM:
      switch (tx->type)
	{
	case ES_REQ_LOAD:
	  return es_tx_one_shm_load(esim, tx);
	case ES_REQ_STORE:
	  return es_tx_one_shm_store(esim, tx);
	case ES_REQ_TESTSET:
	  return es_tx_one_shm_testset(esim, tx);
	default:
#ifdef ES_DEBUG
	  fprintf(stderr, "es_tx_one: BUG\n");
#endif
	  return -EINVAL;
	}

      break;

    case ES_LOC_SHM_MMR:
      return es_tx_one_shm_mmr(esim, tx);
      break;

#if WITH_EMESH_NET
    case ES_LOC_NET:
    case ES_LOC_NET_MMR:
    case ES_LOC_NET_RAM:
      return es_net_tx_one(esim, tx);
      break;
#endif

    default:
#ifdef ES_DEBUG
      fprintf(stderr, "es_tx_one: invalid memory location\n");
#endif
      return -EINVAL;
      break;
    }
#ifdef ES_DEBUG
      fprintf(stderr, "es_tx_one: BUG.\n");
#endif
  return -EINVAL;
}


/*! Perform transaction (memory access request)
 *
 * @param[in]     esim   ESIM handle
 * @param[in,out] tx     Transaction
 *
 * @return ES_OK on success
 */
static int
es_tx_run(es_state *esim, es_transaction *tx)
{
  int ret;

  es_addr_translate(esim, &tx->sim_addr, tx->addr);
  while (1)
    {
      ret = es_tx_one(esim, tx);
      if (ret != ES_OK || !tx->remaining)
	break;
      es_addr_translate_next_region(esim, &tx->sim_addr);
    }
  return ret;
}

/*! Write to memory
 *
 * @param[in] esim   ESIM handle
 * @param[in] addr   Target (Epiphany) address
 * @param[in] size   Number of bytes
 * @param[in] src    Source buffer
 *
 * @return ES_OK on success
 */
int
es_mem_store(es_state *esim, uint32_t addr, uint32_t size, uint8_t *src)
{
  es_transaction tx = {
    ES_REQ_STORE,
    src,
    addr,
    size,
    size,
    ES_TRANSL_INIT
  };
  return es_tx_run(esim, &tx);
}

/*! Read from memory
 *
 * @param[in]  esim   ESIM handle
 * @param[in]  addr   Target (Epiphany) address
 * @param[in]  size   Number of bytes
 * @param[out] dst    Destination buffer
 *
 * @return ES_OK on success
 */
int
es_mem_load(es_state *esim, uint32_t addr, uint32_t size, uint8_t *dst)
{
  es_transaction tx = {
    ES_REQ_LOAD,
    dst,
    addr,
    size,
    size,
    ES_TRANSL_INIT
  };
  return es_tx_run(esim, &tx);
}

/*! Perform TESTSET on memory address
 *
 * @param[in]  esim   ESIM handle
 * @param[in]  addr   Target (Epiphany) address
 * @param[in]  size   Number of bytes
 * @param[out] dst    Destination buffer
 *
 * @return ES_OK on success
 */
int
es_mem_testset(es_state *esim, uint32_t addr, uint32_t size, uint8_t *dst)
{
  es_transaction tx = {
    ES_REQ_TESTSET,
    dst,
    addr,
    size,
    size,
    ES_TRANSL_INIT
  };
  return es_tx_run(esim, &tx);
}

/*! Validate cluster configuration
 *
 * @param[in] c Cluster configuration
 *
 * @return ES_OK on success
 */
static int
es_validate_cluster_cfg(const es_cluster_cfg *c)
{
  unsigned row, begin, end, mem_coreid_base;
  unsigned cores, nodes;

  cores = c->rows * c->cols;

#define FAIL_IF(Expr, Error_string)\
  if ((Expr))\
    {\
      fprintf(stderr, "ESIM: Invalid config: %s\n", (Error_string));\
      return -EINVAL;\
    }

  FAIL_IF(!c->rows,         "Rows cannot be zero");
  FAIL_IF(!c->cols,         "Cols cannot be zero");
  FAIL_IF((cores != 1) && cores & 1,
			    "Number of cores must be even (or exactly 1)");

  FAIL_IF(c->col_base & 1,  "Col base must be even");
  FAIL_IF(c->row_base+c->rows > 64,
			    "Bottommost core row must be less than 64");
  FAIL_IF(c->col_base+c->cols > 64,
			    "Rightmost core col must be less than 64");

  FAIL_IF((ES_COREID(c->row_base+c->rows-1, c->col_base+c->col_base-1)) > 4095,
			    "At least one of core in mesh has coreid > 4095");
  /** @todo Only support 1M for now */
  FAIL_IF(c->core_mem_region != (1<<20),
			    "Currently only 1M core region is supported");
  FAIL_IF(!c->core_mem_region,
			    "Core memory region size is zero");
  FAIL_IF(c->core_mem_region & (c->core_mem_region-1),
			    "Core memory region size must be power of two");

  /* Only support up to 4GB for now */
  FAIL_IF((uint64_t) c->ext_ram_size > (1ULL<<32ULL),
			    "External RAM size too large. Max is 4GB");

  FAIL_IF((address_word)
    (c->ext_ram_base + c->ext_ram_size) < (address_word) c->ext_ram_base &&
    !(c->ext_ram_base && (address_word) (c->ext_ram_base + c->ext_ram_size) == 0),
			    "External RAM would overflow address space");

  FAIL_IF(c->ext_ram_size && (c->ext_ram_size & (c->core_mem_region-1)),
			    "External ram size must be multiple of core mem"
			    " region size.");

  FAIL_IF(c->ext_ram_size && (c->ext_ram_base & (c->core_mem_region-1)),
			    "External ram base must be aligned to core mem"
			    " region size.");

  /** @todo Require external RAM to be on node 0 for now */
  FAIL_IF(c->ext_ram_node != 0,
			    "External RAM must reside on node 0");

  /* WARN: This only works with 1M core mem region size */
  if (c->ext_ram_size)
    {
      /* First core memory shadows */
      mem_coreid_base = c->ext_ram_base / c->core_mem_region;

      for (row = c->row_base; row < c->row_base+c->rows; row++)
	{
	  begin = ES_COREID(row, c->col_base);
	  end = begin + c->cols;
	  FAIL_IF(begin <= mem_coreid_base && mem_coreid_base < end,
				"External RAM shadows core memory");
	}
    }

#undef FAIL_IF
  return ES_OK;
}

/*! Calculate and fill in internal cluster configuration values not specified
 *  by user.
 *
 * @warning This must be called *after* es_validate_config
 *
 * @param[in]     esim     ESIM handle
 */
static void
es_fill_in_internal_cluster_cfg_values(es_state *esim)
{
  unsigned cols_per_node, rows_per_node;
  float ratio, best_ratio;

#if (!WITH_EMESH_NET) && !defined (ESIM_TEST)
  /* Without networking there can be only one node */
  ES_CLUSTER_CFG.nodes = 1;
  ES_CLUSTER_CFG.ext_ram_node = 0;
#endif

  /* Cluster settings */
  ES_CLUSTER_CFG.cores = ES_CLUSTER_CFG.rows * ES_CLUSTER_CFG.cols;
  ES_CLUSTER_CFG.cores_per_node = ES_CLUSTER_CFG.cores / ES_CLUSTER_CFG.nodes;

  /* Calculate number of columns and rows per node.
   * Optimize for most square-like configuration.
   */
  if (ES_CLUSTER_CFG.nodes == 1)
    {
      /* Trivial case */
      ES_CLUSTER_CFG.rows_per_node = ES_CLUSTER_CFG.rows;
      ES_CLUSTER_CFG.cols_per_node = ES_CLUSTER_CFG.cols;
    }
  else
    {
      ES_CLUSTER_CFG.cols_per_node = 0;
      ES_CLUSTER_CFG.rows_per_node = 0;

      /* Initialize with value worse than worst case */
      best_ratio =
       (float) (1 + max (ES_CLUSTER_CFG.cols, ES_CLUSTER_CFG.rows));

      cols_per_node = min(ES_CLUSTER_CFG.cols, ES_CLUSTER_CFG.cores_per_node);
      for (; cols_per_node >= 1; cols_per_node--)
	{
	  rows_per_node = ES_CLUSTER_CFG.cores_per_node / cols_per_node;
	  ratio = ( max ( ((float)cols_per_node), ((float)rows_per_node) ) ) /
		  ( min ( ((float)cols_per_node), ((float)rows_per_node) ) );

	  if (ratio >= best_ratio)
	    break;
	  if (ES_CLUSTER_CFG.cols % cols_per_node)
	    continue;
	  if (ES_CLUSTER_CFG.rows % rows_per_node)
	    continue;
	  if (ES_CLUSTER_CFG.cores_per_node % cols_per_node)
	    continue;
	  if ((rows_per_node * ES_CLUSTER_CFG.nodes * cols_per_node) /
	      ES_CLUSTER_CFG.cols != ES_CLUSTER_CFG.rows)
	    continue;

	  /* Found better candidate */
	  best_ratio = ratio;
	  ES_CLUSTER_CFG.cols_per_node = cols_per_node;
	  ES_CLUSTER_CFG.rows_per_node = rows_per_node;
	}
    }

}

/*! Calculate and fill in internal node configuration values not specified
 *  by user.
 *
 * @warning This must be called *after* es_validate_config and
 * es_fill_in_internal_node_cfg_values.
 *
 * @param[in]     esim     ESIM handle
 * @param[in,out] node     Node configuration
 * @param[in,out] cluster  Cluster configuration
 */
static void
es_fill_in_internal_node_cfg_values(es_state *esim)
{
  /* Node settings */
#if WITH_EMESH_NET
  ES_NODE_CFG.rank = esim->net.rank / ES_CLUSTER_CFG.cores_per_node;
  ES_CLUSTER_CFG.ext_ram_rank =
    ES_CLUSTER_CFG.ext_ram_node * ES_CLUSTER_CFG.cores_per_node;
#else
  ES_NODE_CFG.rank = 0;
  ES_CLUSTER_CFG.ext_ram_rank = 0;
#endif

  {
    unsigned node_row =
     (ES_NODE_CFG.rank * ES_CLUSTER_CFG.cols_per_node) / ES_CLUSTER_CFG.cols;
    ES_NODE_CFG.row_base = ES_CLUSTER_CFG.row_base +
      (ES_CLUSTER_CFG.rows_per_node * node_row);
    ES_NODE_CFG.col_base = ES_CLUSTER_CFG.col_base +
      (ES_CLUSTER_CFG.cols_per_node  * ES_NODE_CFG.rank) % ES_CLUSTER_CFG.cols;
  }
}

/*! Open ESIM shared memory file
 *
 * Open SHM file shared between simulator processes on this node.
 * Use advisory file locking to avoid problem with stale SHM file due to crash.
 *
 * @param[out]    esim     ESIM handle
 * @param[in]     name     name of shm file
 * @param[in,out] flock    Advisory file lock
 *
 * @return ES_OK on success
 */
static int
es_open_shm_file(es_state *esim, char *name, struct flock *flock)
{
  unsigned creator;
  int fd, error, oflag;

  creator = 0;
  fd = -1;
  error = 0;

  /* File must exist when connecting as client */
  oflag = esim->is_client ? (O_RDWR) : (O_RDWR|O_CREAT);

  fd = shm_open(name, oflag, S_IRUSR|S_IWUSR);
  if (fd == -1)
    return -errno;

  if (esim->is_client)
    goto out;

  /* Try to get exclusive lock on shm file */
  flock->l_type   = F_WRLCK;
  error = fcntl(fd, F_SETLK, flock);

  if (!error)
    {
      /* We got exclusive lock */
      creator = 1;

      /* Truncate to 0 to remove any old state */
      if (ftruncate(fd, 0) == -1)
	return -errno;
    }
  else if (error == -1 && (errno == EACCES || errno == EAGAIN))
    {
      creator = 0;
    }
  else
    {
#ifdef ES_DEBUG
      fprintf(stderr, "es_init:shm_open: errno=%d\n", errno);
#endif
      return -errno;
    }

out:
  strncpy(esim->shm_name, name, sizeof(esim->shm_name)-1);
  esim->fd = fd;
  esim->creator = creator;

  return ES_OK;
}

/*! Truncate ESIM SHM file to right size
 *
 * Truncate ESIM SHM file to right size to accommodate cluster configuration,
 * node configuration, core's state and core's memory.
 *
 * @param[in,out] esim     ESIM handle
 * @param[in]     n        Node configuration
 * @param[in]     c        Cluster configuration
 *
 * @return ES_OK on success
 */
static int
es_truncate_shm_file(es_state *esim, es_node_cfg *n, es_cluster_cfg *c)
{
  size_t size, per_core, cores;

  /* Calculate MMAP file size. */
#if WITH_EMESH_NET
  /* This function is called before es_net_init(), so we don't know how many
   * nodes there are in the cluster. Assume worst case (1 node) and allocate
   * memory for all cores + external RAM.
   */
#endif
  cores = c->rows * c->cols;
  per_core = c->core_mem_region + ES_SHM_CORE_STATE_SIZE;
  size = ES_SHM_CONFIG_SIZE + (cores * per_core) + c->ext_ram_size;

  if (ftruncate(esim->fd, size) == -1)
    {
#ifdef ES_DEBUG
      fprintf(stderr, "es_init:ftruncate: errno=%d\n", errno);
#endif
      return -errno;
    }
  esim->shm_size = size;

  return ES_OK;
}

/*! Wait for creating process to truncate SHM file to correct size
 *
 * Wait for creating sim process (the one with excluse lock) to truncate SHM
 * file.
 *
 * @param[in,out] esim   ESIM handle
 * @param[in,out] flock  advisory file lock to use
 *
 * @return ES_OK on success
 */
static int
es_wait_truncate_shm_file(es_state *esim, struct flock *flock)
{
  struct stat st;

  /* Wait until creating process has downgraded lock
     (and truncated shm file) */
  flock->l_type = F_RDLCK;

  if (fcntl(esim->fd, F_SETLKW, flock))
    {
      return -errno;
    }
  if (fstat(esim->fd, &st) == -1)
    {
#ifdef ES_DEBUG
      fprintf(stderr, "es_init:stat: errno=%d\n", errno);
#endif
      return -errno;
    }

  esim->shm_size = st.st_size;
  return ES_OK;

}

/*! Reset esim state
 *
 * @param[out] esim     ESIM handle
 */
inline static void
es_state_reset(es_state *esim)
{
  memset((void*) esim, 0, sizeof(es_state));
  esim->fd = -1;
}

/*! Initialize esim
 *
 * Actual implementation.
 *
 * @param[in,out] esim          pointer to ESIM handle
 * @param[in]     cluster       Cluster configuration
 * @param[in]     coreid_hint   Coreid hint (not used w. esim-net)
 * @param[in]     client         If true, connect as client.
 *
 * @return On success returns ES_OK and sets handle to allocated
 *         esim structure. On error returns a negative error number and sets
 *         handle to NULL.
 */
static int
es_init_impl(es_state **handle,
	es_cluster_cfg cluster,
	unsigned coreid_hint,
	int client)
{
  int error;
  char shm_name[256];
  es_node_cfg node;
  es_state *esim;
  volatile es_shm_header *shm;
  unsigned msecs_wait;
  unsigned have_core_0;   /* Special case when node first core and row is 0 */
  unsigned sim_processes; /* On this node, core 0 does not have sim proc */
  struct flock flock;      /* Used when opening shm file */

  error = 0;
  msecs_wait = 0;

  flock.l_whence = SEEK_SET;
  flock.l_start  = 0;
  flock.l_len    = 16;      /* Whatever, but must be same in all processes */

  *handle = NULL;
  esim = (es_state *) malloc(sizeof(es_state));
  if (esim == NULL)
    {
      fprintf(stderr, "ESIM: Out of memory\n");
      error = -ENOMEM;
      goto err_out;
    }
  es_state_reset(esim);

  esim->is_client = client;

  snprintf(shm_name, sizeof(shm_name)/sizeof(char)-1, "/esim.%d", getuid());

  msecs_wait = 0;
  do
    {
      if ((error = es_open_shm_file(esim, shm_name, &flock)) == ES_OK)
	break;

      if (!esim->is_client)
	break;

      /* Notify user we're waiting once */
      if (msecs_wait == 0)
	fprintf(stderr, "ESIM: Will wait 10s for core simulators\n");

      usleep(200000);
      msecs_wait += 200;
    }
  while (msecs_wait <= 10000);
  if (error != ES_OK)
    {
      fprintf(stderr, "ESIM: Could not open esim file `/dev/shm%s'\n", shm_name);
      goto err_out;
    }

#if WITH_EMESH_NET
  /* Initialize networking */
  if ((error = es_net_init(esim, &cluster)) != ES_OK)
    goto err_out;
#endif

  /* If this process created the file, set its size */
  if (esim->creator)
    {
      if ((error = es_validate_cluster_cfg(&cluster)) != ES_OK)
	{
	  goto err_out;
	}

      if ((error = es_truncate_shm_file(esim, &node, &cluster)) != ES_OK)
	{
	  fprintf(stderr, "ESIM: Could not truncate  esim file `/dev/shm%s'\n",
		  shm_name);
	  goto err_out;
	}

      /* Downgrade exclusive lock to shared lock */
      flock.l_type = F_RDLCK;
      if (fcntl(esim->fd, F_SETLK, &flock))
	{
	  error = -errno;
	  goto err_out;
	}
    }

  else /* if (!creator) */
    {
      if ((error = es_wait_truncate_shm_file(esim, &flock)) != ES_OK)
	goto err_out;
    }

  shm = (es_shm_header*) mmap(NULL,
			      esim->shm_size,
			      PROT_READ|PROT_WRITE, MAP_SHARED,
			      esim->fd,
			      (off_t) 0);
  if (shm == MAP_FAILED)
    {
      fprintf(stderr, "ESIM: mmap failed\n");
      error = -EINVAL;
      goto err_out;
    }

  esim->shm = shm;
  esim->coreid = 0;
  esim->cores_mem = ((uint8_t *) shm) + ES_SHM_CONFIG_SIZE;

  if (esim->creator)
    {
      /* Copy over cluster and node config structs to shared memory */
      memmove((void *) &ES_CLUSTER_CFG, (void *) &cluster,
	     sizeof(es_cluster_cfg));
      memmove((void *) &ES_NODE_CFG, (void *) &node,
	     sizeof(es_node_cfg));

      /* Signal waiting processes that shared memory is ready */
      shm->shm_initialized = 1;
    }
  else /* if (!creator) */
    {
      /* Busy wait for creating process */
      msecs_wait = 0;
      while (!shm->shm_initialized && msecs_wait <= 3000)
	{
	  usleep(5000);
	  msecs_wait += 5;
	}
      if (!shm->shm_initialized)
	{
	  fprintf(stderr, "ESIM: Timed out waiting on shared memory.\n");
	  error = -ETIME;
	  goto err_out;
	}
    }

  if (esim->creator)
    {
      es_fill_in_internal_cluster_cfg_values(esim);
      es_fill_in_internal_node_cfg_values(esim);

      /** @todo Determine what to do with this edge-case and WITH_EMESH_NET. */
      have_core_0 = (!ES_NODE_CFG.col_base && !ES_NODE_CFG.row_base);

      /* Coreid 0 is invalid so we should not wait for it */
      sim_processes = have_core_0 ?
	ES_CLUSTER_CFG.cores_per_node-1 :
	ES_CLUSTER_CFG.cores_per_node;

      /* Initialize pthread barriers */
      {
	pthread_barrierattr_t barr_attr;
	pthread_mutexattr_t   mutex_attr;
	pthread_condattr_t    cond_attr;

	/* Need shared process attributes */
	pthread_barrierattr_init(&barr_attr);
	pthread_barrierattr_setpshared(&barr_attr, PTHREAD_PROCESS_SHARED);
	pthread_mutexattr_init(&mutex_attr);
	pthread_mutexattr_setpshared(&mutex_attr, PTHREAD_PROCESS_SHARED);
	pthread_condattr_init(&cond_attr);
	pthread_condattr_setpshared(&cond_attr, PTHREAD_PROCESS_SHARED);

	/* Initialize barriers */
	pthread_barrier_init((pthread_barrier_t *) &esim->shm->run_barrier,
			     &barr_attr,
			     sim_processes);
	pthread_barrier_init((pthread_barrier_t *) &esim->shm->exit_barrier,
			     &barr_attr,
			     sim_processes);

	/* Initialize client mutex */
	pthread_mutex_init((pthread_mutex_t *) &esim->shm->client_mtx,
			   &mutex_attr);

	/* ... and client cond vars */
	pthread_cond_init((pthread_cond_t *) &esim->shm->client_exit_cond,
			  &cond_attr);
	pthread_cond_init((pthread_cond_t *) &esim->shm->client_run_cond,
			  &cond_attr);


	/* Cleanup */
	pthread_barrierattr_destroy(&barr_attr);
	pthread_mutexattr_destroy(&mutex_attr);
	pthread_condattr_destroy(&cond_attr);
      }

      /* Signal waiting processes that (shared) configuration is ready */
      shm->cfg_initialized = 1;
    }
  else /* if (!creator) */
    {
      /* Busy wait for creating process */
      msecs_wait = 0;
      while (!shm->cfg_initialized && msecs_wait <= 3000)
	{
	  usleep(5000);
	  msecs_wait += 5;
	}
      if (!shm->cfg_initialized)
	{
	  fprintf(stderr, "ESIM: Timed out waiting on config.\n");
	  error = -ETIME;
	  goto err_out;
	}
    }

  /* If external RAM is on this node, set up pointer */
  if (ES_CLUSTER_CFG.ext_ram_node == ES_NODE_CFG.rank)
    {
      esim->ext_ram = ((uint8_t *) shm) + ES_SHM_CONFIG_SIZE +
	ES_CLUSTER_CFG.cores *
	  (ES_CLUSTER_CFG.core_mem_region + ES_SHM_CORE_STATE_SIZE);
    }

  /* Set coreid */
  if (!esim->is_client)
    {
#if WITH_EMESH_NET
      /* Calculate coreid from MPI rank */
      if ((error = es_net_set_coreid_from_rank(esim)) != ES_OK)
	{
	  fprintf(stderr, "ESIM: Could not set coreid.\n");
	  goto err_out;
	}
#else
      /* Set coreid from hint */
      if ((error = es_set_coreid(esim, coreid_hint)) != ES_OK)
	{
	  if (error == -EADDRINUSE)
	    {
	      fprintf(stderr,
		      "ESIM: Could not set coreid to `%u'. Already "
		      "reserved by another simulator process\n",
		      coreid_hint);
	    }
	  else
	    {
	      fprintf(stderr,
		      "ESIM: Could not set coreid to `%u'.\n",
		      coreid_hint);
	    }
	  goto err_out;
	}
#endif
    }

#if WITH_EMESH_NET
  /* Need coreid and this_core_cpu_state */
  if ((error = es_net_init_mmr(esim)) != ES_OK)
    {
      goto err_out;
    }
  /* Now when coreid is set, we can expose SRAM to other processes */
  if ((error = es_net_init_mpi_win(esim)) != ES_OK)
    {
      goto err_out;
    }
#endif

#if !WITH_EMESH_NET
  /* Notify sim processes client is connected */
  if (esim->is_client)
    {
      pthread_mutex_lock((pthread_mutex_t *) &shm->client_mtx);

      /* Fail early if any core is in the process of exiting. */
      if (esim->shm->exiting)
	{
	  if (!esim->shm->clients)
	    pthread_cond_broadcast((pthread_cond_t *) &shm->client_exit_cond);

	  pthread_mutex_unlock((pthread_mutex_t *) &shm->client_mtx);

	  fprintf(stderr, "ESIM: Remote is exiting.\n");
	  error = -EPIPE;
	  goto err_out;
	}

      /* Only support one client for now */
      if (esim->shm->clients)
	{
	  pthread_mutex_unlock((pthread_mutex_t *) &shm->client_mtx);

	  fprintf(stderr, "ESIM: Maximum number of clients already connected.\n");
	  error = -EBUSY;
	  goto err_out;
	}

      esim->shm->clients += 1;

      pthread_mutex_unlock((pthread_mutex_t *) &shm->client_mtx);
    }
#endif

#ifdef ES_DEBUG
  fprintf(stderr,
	  "es_init: shm=0x%lx shm_size=%ld fd=%d coreid=%d shm_name=\"%s\"\n",
	  (unsigned long int) esim->shm, esim->shm_size, esim->fd,
	  esim->coreid, esim->shm_name);
#endif

ok_out:
  esim->initialized = 1;
  *handle = esim;
  return ES_OK;

err_out:
  es_fini(esim);
  return error;
}


/*! Initialize esim
 *
 * @param[in,out] handle        pointer to ESIM handle
 * @param[in]     cluster       Cluster configuration
 * @param[in]     coreid_hint   Coreid hint (not used w. esim-net)
 * @param[in]     client         If true, connect as client.
 *
 * @return On success returns ES_OK and sets handle to allocated
 *         esim structure. On error returns a negative error number and sets
 *         handle to NULL.
 */
int
es_init(es_state **handle, es_cluster_cfg cluster, unsigned coreid_hint)
{
  return es_init_impl(handle, cluster, coreid_hint, 0);
}

/*! Connect to eMesh simulator as a client
 *
 * @param[in,out] handle          pointer to ESIM handle
 *
 * @return On success returns ES_OK and sets handle to allocated
 *         esim structure. On error returns a negative error number and sets
 *         handle to NULL.
 */
int
es_client_connect(es_state **handle)
{
  int rc;
  es_cluster_cfg cluster;

  if ((rc = es_init_impl(handle, cluster, 0, 1)) != ES_OK)
    return rc;

  es_wait_run(*handle);

  return ES_OK;
}

/*! Disconnect client from eMesh simulator
 *
 * @param[in,out] esim          pointer to ESIM handle
 */
void
es_client_disconnect(es_state *esim)
{
  if (!esim)
    return;

  es_wait_exit(esim);
  es_fini(esim);
}


/*! Check if ESIM is initialized
 *
 * @param[in] esim     ESIM handle
 *
 * @return ES_OK if ESIM is initialized, -EINVAL otherwise.
 */
int inline
es_initialized(const es_state* esim)
{
  return ((esim && esim->initialized == 1) ? ES_OK : -EINVAL);
}

/*! Cleanup after ESIM
 *
 * Unmaps mmaped memory, closes SHM file and resets esim handle
 *
 * @param[in,out] esim     ESIM handle
 */
void
es_fini(es_state *esim)
{
#ifdef ES_DEBUG
  fprintf(stderr, "es_fini\n");
#endif

  if (!esim)
    return;

#if WITH_EMESH_NET
  es_net_fini(esim);
#endif

  if (esim->shm)
    munmap((void *) esim->shm, esim->shm_size);

  /* Unlink before close, to avoid race in between file locks are released and
   * unlink.
   */
  if (esim->creator)
    shm_unlink(esim->shm_name);

  /* Close file, will also release all advisory file locks */
  if (esim->fd >= 0)
    close(esim->fd);

  es_state_reset(esim);
  free(esim);
}

static void
es_set_ready(es_state *esim)
{
  if (esim->ready)
      return;

  esim->ready = 1;
  if (!esim->is_client)
    es_atomic_incr32((uint32_t *) &esim->shm->node_core_sims_ready);
}

/*! Wait on other sim processes before starting simulation
 *
 * @param[in,out] esim     ESIM handle
 */
void
es_wait_run(es_state *esim)
{
  /** @todo Would be nice to support Ctrl-C here */

  es_set_ready(esim);

#if WITH_EMESH_NET
      es_net_wait_run(esim);
#else
  if (!esim->is_client)
    {
      pthread_barrier_wait((pthread_barrier_t *) &esim->shm->run_barrier);
      if (!(esim->coreid % ES_CLUSTER_CFG.cores_per_node))
	{
	  pthread_mutex_lock((pthread_mutex_t *) &esim->shm->client_mtx);
	  pthread_cond_broadcast((pthread_cond_t *) &esim->shm->client_run_cond);
	  pthread_mutex_unlock((pthread_mutex_t *) &esim->shm->client_mtx);
	}
    }
  else /* esim->is_client */
    {
      if (esim->shm->node_core_sims_ready < ES_CLUSTER_CFG.cores_per_node)
	{
	  pthread_mutex_lock((pthread_mutex_t *) &esim->shm->client_mtx);
	  pthread_cond_wait((pthread_cond_t *) &esim->shm->client_run_cond,
			    (pthread_mutex_t *) &esim->shm->client_mtx);
	  pthread_mutex_unlock((pthread_mutex_t *) &esim->shm->client_mtx);
	}
      es_set_ready(esim);
    }
#endif
}

/*! Wait on other sim processes before exiting after simulation
 *
 * @param[in] esim     ESIM handle
 */
void
es_wait_exit(es_state *esim)
{
  /** @todo Would be nice to support Ctrl-C here */

#if WITH_EMESH_NET
  es_net_wait_exit(esim);
#else

  /* Exit early */
  if (!esim->ready && !esim->is_client)
    return;

  if (!esim->is_client)
    {
      /* Inform any connecting client we want to exit */
      esim->shm->exiting = 1;

      /* Wait for clients */
      pthread_mutex_lock((pthread_mutex_t *) &esim->shm->client_mtx);
      if (esim->shm->clients)
	{
	  pthread_cond_wait((pthread_cond_t *) &esim->shm->client_exit_cond,
			    (pthread_mutex_t *) &esim->shm->client_mtx);
	}
      pthread_mutex_unlock((pthread_mutex_t *) &esim->shm->client_mtx);

      /* Wait for other sim processes */
      pthread_barrier_wait((pthread_barrier_t *) &esim->shm->exit_barrier);
    }
  else
    {
      pthread_mutex_lock((pthread_mutex_t *) &esim->shm->client_mtx);
      esim->shm->clients -= 1;
      if (esim->shm->exiting && !esim->shm->clients)
	pthread_cond_broadcast((pthread_cond_t *) &esim->shm->client_exit_cond);
      pthread_mutex_unlock((pthread_mutex_t *) &esim->shm->client_mtx);
    }
#endif
}

/*! Check whether a given core-id is valid for current configuration
 *
 * @param[in] esim     ESIM handle
 * @param[in] coreid   Coreid
 *
 * @return ES_OK on success, otherwise -EINVAL
 */
int
es_valid_coreid(const es_state *esim, unsigned coreid)
{
  unsigned row = ES_CORE_ROW(coreid);
  unsigned col = ES_CORE_COL(coreid);
  int valid = (coreid &&
	  ES_NODE_CFG.row_base <= row &&
	  row < ES_NODE_CFG.row_base + ES_CLUSTER_CFG.rows_per_node &&
	  ES_NODE_CFG.col_base <= col &&
	  col < ES_NODE_CFG.col_base + ES_CLUSTER_CFG.cols_per_node);

  return valid ? ES_OK : -EINVAL;
}

/*! Set coreid for this sim process
 *
 * Set coreid for this sim process
 * This can be done at most once.
 *
 * @param[in,out] esim     ESIM handle
 * @param[in]     coreid   Coreid
 *
 * @return ES_OK on success
 */
int
es_set_coreid(es_state *esim, unsigned coreid)
{
  es_shm_core_state_header *header;
  int rc;

  /* Verify that coreid was not already set */
  if (esim->coreid != 0)
    return -EINVAL;

  if (es_valid_coreid(esim, coreid) != ES_OK)
    return -EINVAL;

  header = (es_shm_core_state_header *) es_shm_core_base(esim, coreid);

  if (!header)
    return -EINVAL;

  if (es_cas32(&header->reserved, 0, 1))
    return -EADDRINUSE;

  esim->coreid = coreid;

  esim->this_core_state_header = (es_shm_core_state_header *) header;
  esim->this_core_cpu_state = es_shm_core_base(esim, coreid) +
			      ES_SHM_CORE_STATE_HEADER_SIZE;
  esim->this_core_mem = (uint8_t *) header + ES_SHM_CORE_STATE_SIZE;

  return ES_OK;
}

/*! Set (overwrite) CPU state for this sim process
 *
 * @param[in,out] esim     ESIM handle
 * @param[in]     cpu      Pointer to new CPU data
 * @param[in]     size     Size of CPU data
 *
 * @return Pointer to CPU state address or NULL
 */
volatile void *
es_set_cpu_state(es_state *esim, void *cpu, size_t size)
{

  if (es_valid_coreid(esim, esim->coreid) != ES_OK)
    return NULL;

  if (esim->this_core_cpu_state == cpu)
    return cpu;

  memset((void *)esim->this_core_cpu_state, 0,
	 ES_SHM_CORE_STATE_SIZE - ES_SHM_CORE_STATE_HEADER_SIZE);
  memmove((void *)esim->this_core_cpu_state, cpu, size);

  return esim->this_core_cpu_state;
}

/*! Dump node and cluster configuration
 *
 * @param[in] esim     ESIM handle
 */
void
es_dump_config(const es_state *esim)
{
  fprintf(stderr,
	  "es_cluster_cfg = {\n"
	  "  .row_base        = %d\n"
	  "  .col_base        = %d\n"
	  "  .rows            = %d\n"
	  "  .cols            = %d\n"
	  "  .core_mem_region = %zu\n"
	  "  .ext_ram_node    = %d\n"
	  "  .ext_ram_base    = 0x%.8x\n"
	  "  .ext_ram_size    = %zu\n"
	  "  .cores           = %d\n"
	  "  .nodes           = %d\n"
	  "  .cores_per_node  = %d\n"
	  "  .rows_per_node   = %d\n"
	  "  .cols_per_node   = %d\n"
	  "  .ext_ram_rank    = %d\n"
	  "}\n",
	  ES_CLUSTER_CFG.row_base,
	  ES_CLUSTER_CFG.col_base,
	  ES_CLUSTER_CFG.rows,
	  ES_CLUSTER_CFG.cols,
	  ES_CLUSTER_CFG.core_mem_region,
	  ES_CLUSTER_CFG.ext_ram_node,
	  ES_CLUSTER_CFG.ext_ram_base,
	  ES_CLUSTER_CFG.ext_ram_size,
	  ES_CLUSTER_CFG.cores,
	  ES_CLUSTER_CFG.nodes,
	  ES_CLUSTER_CFG.cores_per_node,
	  ES_CLUSTER_CFG.rows_per_node,
	  ES_CLUSTER_CFG.cols_per_node,
	  ES_CLUSTER_CFG.ext_ram_rank);
  fprintf(stderr,
	  "es_node_cfg = {\n"
	  "  .rank     = %d\n"
	  "  .row_base = %d\n"
	  "  .col_base = %d\n"
	  "}\n",
	  ES_NODE_CFG.rank,
	  ES_NODE_CFG.row_base,
	  ES_NODE_CFG.col_base);
  fprintf(stderr,
	  ".esim = {\n"
	  "  .initialized            = %d\n"
	  "  .ready                  = %d\n"
	  "  .coreid                 = %d\n"
	  "  .fd                     = %d\n"
	  "  .creator                = %d\n"
	  "  .shm_name               = %s\n"
	  "  .shm_size               = %lu\n"
	  "  .shm                    = 0x%p\n"
	  "  .cores_mem              = 0x%p\n"
	  "  .this_core_mem          = 0x%p\n"
	  "  .this_core_state_header = 0x%p\n"
	  "  .this_core_cpu_state    = 0x%p\n"
	  "  .ext_ram                = 0x%p\n"
	  "}\n",
	  esim->initialized,
	  esim->ready,
	  esim->coreid,
	  esim->fd,
	  esim->creator,
	  esim->shm_name,
	  esim->shm_size,
	  esim->shm,
	  esim->cores_mem,
	  esim->this_core_mem,
	  esim->this_core_state_header,
	  esim->this_core_cpu_state,
	  esim->ext_ram);
}

inline size_t
es_get_core_mem_region_size(const es_state *esim)
{
  return ES_CLUSTER_CFG.core_mem_region;
}
inline unsigned
es_get_coreid(const es_state *esim)
{
  return esim->coreid;
}

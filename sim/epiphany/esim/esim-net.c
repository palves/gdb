/* Epiphany eMesh functional simulator, network support
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


 /**
 * @todo Check consistency, might be to loose.
 *
 */

#if !WITH_EMESH_NET
#error "WITH_EMESH_NET=1 not set. This file should not be built"
#endif

#include "esim.h"
#include "esim-net.h"
#include "esim-int.h"


/* Need these for correct cpu struct */
#define WANT_CPU epiphanybf
#define WANT_CPU_EPIPHANYBF
#include "sim-main.h"

#include <mpi.h>
#include <stdio.h>
#include <errno.h>
#include <stdint.h>


/* Communicator to be used. */
#define ES_NET_COMM_WORLD esim->net.comm

static void es_net_state_reset(es_state *esim);
void *es_net_mmr_thread(void *);

static void
es_net_print_mpi_err(es_state *esim, char *function, int error)
{
  int mpi_err_len;
  char mpi_err_str[MPI_MAX_ERROR_STRING+1];
  mpi_err_str[MPI_MAX_ERROR_STRING] = '\0';

  if (MPI_Error_string(error, mpi_err_str, &mpi_err_len) == MPI_SUCCESS)
    fprintf(stderr, "ESIM:NET: %s: %s\n", function, mpi_err_str);
  else
    fprintf(stderr, "ESIM:NET: %s: Error code %d\n", function, error);
}

/*! Evaluate @Function. If it succeeds: evaluate @SuccAction.
 *  If it fails: print error description and evaluate @ErrAction.
 */
#define MPI_TRY_CATCH(Function, SuccAction, ErrAction)\
  do\
    {\
      int MPI_TRY_rc;\
      if ((MPI_TRY_rc = (Function)) == MPI_SUCCESS)\
	{\
	  (SuccAction);\
	}\
      else\
	{\
	  es_net_print_mpi_err(esim, (#Function), MPI_TRY_rc);\
	  (ErrAction);\
	}\
    }\
  while (0)


/*! Calculate which node a core belongs to */
static signed
es_net_coreid_to_node(const es_state *esim, unsigned coreid)
{
  signed node, row_offset, col_offset, node_row, node_col, nodes_per_row;

  row_offset = ES_CORE_ROW(coreid) - ES_CLUSTER_CFG.row_base;
  col_offset = ES_CORE_COL(coreid) - ES_CLUSTER_CFG.col_base;

  node_row = row_offset / ES_CLUSTER_CFG.rows_per_node;
  node_col = col_offset / ES_CLUSTER_CFG.cols_per_node;

  nodes_per_row = (ES_CLUSTER_CFG.cols / ES_CLUSTER_CFG.cols_per_node);

  node = (node_row * nodes_per_row) + node_col;

  if (row_offset < 0 || col_offset < 0)
    return -EINVAL;

  if (node < 0 || ES_CLUSTER_CFG.nodes <= node )
    return -EINVAL;

  return node;
}

/*! Calculate net (MPI) rank from coreid */
static signed
es_net_coreid_to_rank(const es_state *esim, unsigned coreid)
{
  signed row_offset, col_offset, node, rank, row_in_node, col_in_node;

  node = es_net_coreid_to_node(esim, coreid);
  if (node < 0)
    return -EINVAL;

  row_offset = ES_CORE_ROW(coreid) - ES_CLUSTER_CFG.row_base;
  col_offset = ES_CORE_COL(coreid) - ES_CLUSTER_CFG.col_base;

  row_in_node = row_offset % ES_CLUSTER_CFG.rows_per_node;
  col_in_node = col_offset % ES_CLUSTER_CFG.cols_per_node;

  rank = node * ES_CLUSTER_CFG.cores_per_node +
	 (row_in_node * ES_CLUSTER_CFG.cols_per_node) +
	 col_in_node;

  if (rank < 0 || ES_CLUSTER_CFG.cores <= rank)
    return -EINVAL;

  return rank;
}

static inline MPI_Datatype
mpi_type(size_t size)
{
  switch (size)
    {
    case 1: return MPI_UINT8_T;
    case 2: return MPI_UINT16_T;
    case 4: return MPI_UINT32_T;
    case 8: return MPI_UINT64_T;
    default: /* fall through */;
    }
  fprintf (stderr, "ESIM:NET: Internal error in es_net_mpi_datatype()\n");
  MPI_Abort(MPI_COMM_WORLD, EINVAL);
  return MPI_DATATYPE_NULL;
}
/*! Lookup corresponding MPI Integer datatype with same size as Type */
#define ES_NET_MPI_TYPE(Type) mpi_type(sizeof((Type)))


/*! Initialize ESIM networking.
 *
 *  @todo Support non-continous (per host) rank assignments.
 *
 *  @param[in] esim     ESIM handle
 *  @param[in,out]      cluster configuration
 *
 *  @return ES_OK on success
 */
int
es_net_init(es_state *esim, es_cluster_cfg *cluster)
{
  int rc;

  /* Reset state */
  es_net_state_reset(esim);

  /* Initialize MPI and request multi-threading support */
  {
    int provided;

    provided = 0;
    MPI_TRY_CATCH(MPI_Init_thread(NULL, NULL, MPI_THREAD_MULTIPLE, &provided),
		  {},
		  {
		    rc = -EINVAL;
		    goto err_out;
		  });
    esim->net.mpi_initialized = 1;

    /* We need multiple threads support. */
    if (provided != MPI_THREAD_MULTIPLE)
      {
	fprintf(stderr, "ESIM:NET: MPI library does not support threads\n");
	rc = -ENOTSUP;
	goto err_out;
      }

    /* Signal errors with return codes */
    MPI_TRY_CATCH(MPI_Comm_set_errhandler(MPI_COMM_WORLD, MPI_ERRORS_RETURN),
		  { },
		  {
		    rc = -EINVAL;
		    goto err_out;
		  });

  }


  /* Set up new communicator with correct ranks */
  {
    /* Reorder ranks with clients in tail */
    MPI_TRY_CATCH(MPI_Comm_split(MPI_COMM_WORLD,
				 0,
				 esim->is_client,
				 &esim->net.comm),
		  { },
		  {
		    rc = -EINVAL;
		    goto err_out;
		  });

    /* Signal errors with return codes */
    MPI_TRY_CATCH(MPI_Comm_set_errhandler(ES_NET_COMM_WORLD, MPI_ERRORS_RETURN),
		  { },
		  {
		    rc = -EINVAL;
		    goto err_out;
		  });

    MPI_TRY_CATCH(MPI_Comm_rank(ES_NET_COMM_WORLD, &esim->net.rank),
		  {},
		  {
		    rc = -EINVAL;
		    goto err_out;
		  });

    MPI_TRY_CATCH(MPI_Comm_size(ES_NET_COMM_WORLD, &esim->net.size),
		  {},
		  {
		    rc = -EINVAL;
		    goto err_out;
		  });
  }

  if (esim->is_client && esim->net.rank == 0)
    {
      fprintf(stderr, "ESIM:NET: Running a simulation with only clients is not"
	      " allowed (it does not make sense).\n");
      rc = -EINVAL;
      goto err_out;
    }

  /* Calculate total number of simulator processes (non-clients) */
  {
    MPI_Comm tmp_comm;
    int tmp_sz;

    MPI_TRY_CATCH(MPI_Comm_split(ES_NET_COMM_WORLD, esim->is_client, 0, &tmp_comm),
		  {},
		  {
		    rc = -EINVAL;
		    goto err_out;
		  });

    MPI_TRY_CATCH(MPI_Comm_size(tmp_comm, &tmp_sz),
		  {},
		  {
		    rc = -EINVAL;
		    goto err_out;
		  });

    MPI_TRY_CATCH(MPI_Barrier(tmp_comm),
		  {},
		  {
		    rc = -EINVAL;
		    goto err_out;
		  });

    MPI_TRY_CATCH(MPI_Comm_disconnect(&tmp_comm),
		  {},
		  {
		    rc = -EINVAL;
		    goto err_out;
		  });

    esim->net.sim_processes =
     esim->is_client ? esim->net.size - tmp_sz: tmp_sz;
  }

  /* Let process with rank 0 dictate cluster configuration */
  MPI_TRY_CATCH(MPI_Bcast((void *) cluster,
			  sizeof(es_cluster_cfg),
			  MPI_UINT8_T,
			  0,
			  ES_NET_COMM_WORLD),
		{},
		{
		  rc = -EINVAL;
		  goto err_out;
		});

  /* Calculate number of simulator processes per node */
  {
    int procs_per_node, cores_per_node, core_comm_sz;

    MPI_Comm node_comm; /* Processes on this node */
    MPI_Comm core_comm; /* Split in simulator processes and only clients */

    /* Get all procs on node */
    MPI_TRY_CATCH(MPI_Comm_split_type(ES_NET_COMM_WORLD,
				      MPI_COMM_TYPE_SHARED,
				      0,
				      MPI_INFO_NULL,
				      &node_comm),
		  {},
		  {
		    rc = -EINVAL;
		    goto err_out;
		  });

    /* Then split by sim-process / client */
    MPI_TRY_CATCH(MPI_Comm_split(node_comm, esim->is_client, 0, &core_comm),
		  {},
		  {
		    rc = -EINVAL;
		    goto err_out;
		  });

    MPI_TRY_CATCH(MPI_Comm_size(node_comm, &procs_per_node),
		  {},
		  {
		    rc = -EINVAL;
		    goto err_out;
		  });

    MPI_TRY_CATCH(MPI_Comm_size(core_comm, &core_comm_sz),
		  {},
		  {
		    rc = -EINVAL;
		    goto err_out;
		  });

    /* Wait for all (local) processes to get size */
    MPI_TRY_CATCH(MPI_Barrier(node_comm),
		  {},
		  {
		    rc = -EINVAL;
		    goto err_out;
		  });

    MPI_TRY_CATCH(MPI_Comm_disconnect(&core_comm),
		  {},
		  {
		    rc = -EINVAL;
		    goto err_out;
		  });

    MPI_TRY_CATCH(MPI_Comm_disconnect(&node_comm),
		  {},
		  {
		    rc = -EINVAL;
		    goto err_out;
		  });

    cluster->cores_per_node =
     esim->is_client ? (procs_per_node-core_comm_sz) : core_comm_sz;

    cluster->nodes = esim->net.sim_processes / cluster->cores_per_node;

  }

  /* Ensure that the configuration is homogeneous, i.e., same number of
   * simulator processes on all nodes. */
  {
    int leader_says;

    if (esim->net.rank == 0)
      leader_says = cluster->cores_per_node;

    MPI_TRY_CATCH(MPI_Bcast((void *) &leader_says,
			    1,
			    MPI_INTEGER,
			    0,
			    ES_NET_COMM_WORLD),
		  {},
		  {
		    rc = -EINVAL;
		    goto err_out;
		  });

    if (cluster->cores_per_node != leader_says)
      {
	fprintf(stderr, "ESIM:NET: Simulation must be run with the same number "
		"of simulator processes on all nodes.\n");
	rc = -EINVAL;
	goto err_out;
      }
  }

  /* Fail if there isn't exactly one sim process per core */
  {
    unsigned cores;

    cores = cluster->rows * cluster->cols;

    if (esim->net.sim_processes != cores)
      {
	fprintf(stderr, "ESIM:NET: Number of MPI processes (%u) doesn't match "
		"number of cores (%u)\n", esim->net.sim_processes, cores);
	rc = -EINVAL;
	goto err_out;
      }
  }

ok_out:
  return ES_OK;
err_out:
  es_net_fini(esim);
  return rc;
}

static void
es_net_state_reset(es_state *esim)
{
  int i;

  esim->net.rank = -1;
  esim->net.sim_processes = 0;

  esim->net.mem_win = MPI_WIN_NULL;
  esim->net.ext_ram_win = MPI_WIN_NULL;
  esim->net.ext_write_win = MPI_WIN_NULL;

  esim->net.mpi_initialized = 0;
}

void
es_net_fini(es_state *esim)
{
  if (esim->net.mem_win != MPI_WIN_NULL)
    MPI_TRY_CATCH(MPI_Win_free(&esim->net.mem_win), { }, { });
  if (esim->net.ext_ram_win != MPI_WIN_NULL)
    MPI_TRY_CATCH(MPI_Win_free(&esim->net.ext_ram_win), { }, { });
  if (esim->net.ext_write_win != MPI_WIN_NULL)
    MPI_TRY_CATCH(MPI_Win_free(&esim->net.ext_write_win), { }, { });

  if (esim->net.mpi_initialized)
    MPI_TRY_CATCH(MPI_Finalize(), { }, { });

  es_net_state_reset(esim);
}


/*! Calculate and set COREID based on MPI rank.
 *  Must be called *after* es_fill_in_internal_structs
 *
 *  @param[in] esim     ESIM handle
 *
 *  @return ES_OK on success
 */
int
es_net_set_coreid_from_rank(es_state *esim)
{
  unsigned rank_in_node, row, col, coreid;

  if (esim->net.rank < 0)
    return -EINVAL;

  rank_in_node = esim->net.rank -
   (ES_NODE_CFG.rank * ES_CLUSTER_CFG.cores_per_node);

  row = ES_NODE_CFG.row_base + (rank_in_node / ES_CLUSTER_CFG.cols_per_node);
  col = ES_NODE_CFG.col_base + (rank_in_node  % ES_CLUSTER_CFG.cols_per_node);
  coreid = ES_COREID(row, col);

  return es_set_coreid(esim, coreid);
}

/*! Use barrier to synchronize start time.
 */
void
es_net_wait_run(es_state *esim)
{
  MPI_TRY_CATCH(MPI_Win_fence(0, esim->net.mem_win), { }, { });
  MPI_TRY_CATCH(MPI_Win_fence(0, esim->net.ext_ram_win), { }, { });
  MPI_TRY_CATCH(MPI_Win_fence(0, esim->net.ext_write_win), { }, { });
  MPI_TRY_CATCH(MPI_Barrier(ES_NET_COMM_WORLD), { }, { });
}

/*! Wait for all processes to finish before we go ahead and finalize MPI.
 */
void
es_net_wait_exit(es_state *esim)
{
  MPI_TRY_CATCH(MPI_Win_fence(0, esim->net.mem_win), { }, { });
  MPI_TRY_CATCH(MPI_Win_fence(0, esim->net.ext_ram_win), { }, { });
  MPI_TRY_CATCH(MPI_Win_fence(0, esim->net.ext_write_win), { }, { });

  MPI_TRY_CATCH(MPI_Barrier(ES_NET_COMM_WORLD), { }, { });

  /* send exit msg to service mmr thread */
  if (!esim->is_client)
    {
      int rc;

      es_net_mmr_request req;
      MPI_Request mpi_req;

      req.type = ES_NET_MMR_REQ_EXIT;

      /* Use non-blocking send. Standard isn't really clear about what should
       * happen on blocking send to self.
       */
      MPI_TRY_CATCH(MPI_Isend((void *) &req,
			     sizeof(req),
			     MPI_UINT8_T,
			     esim->net.rank,
			     ES_NET_TAG_REQUEST,
			     ES_NET_COMM_WORLD,
			     &mpi_req),
		    {},
		    {});

      /* Wait for thread to exit */
      pthread_join(esim->net.mmr_thread, (void **) &rc);

      if (rc != ES_OK)
	fprintf(stderr, "ESIM:NET: Error in MMR helper thread.\n");
    }

  MPI_TRY_CATCH(MPI_Barrier(ES_NET_COMM_WORLD), { }, { });

}

/*! Initialize remote MMR access by spawning helper thread.
 *
 * @warn Must be called late in es_init(), after esim->coreid and
 * esim->this_core_cpu_state are set.
 */
int
es_net_init_mmr(es_state *esim)
{

  if (esim->is_client)
    return ES_OK;

  /* Create MMR access helper thread */
  if ((pthread_create(&esim->net.mmr_thread,
		      NULL,
		      es_net_mmr_thread,
		      ((void *) esim))) != 0)
    {
      fprintf(stderr, "ESIM:NET: Failed creating MMR helper thread\n");
      return -EINVAL;
    }
  return ES_OK;
}

static int
es_net_create_mpi_win(es_state *esim, MPI_Win *win, void *ptr, size_t size)
{
  /* Expose per core local SRAM to other MPI processes */
  MPI_TRY_CATCH(MPI_Win_create(ptr,
			       size,
			       1,
			       MPI_INFO_NULL,
			       ES_NET_COMM_WORLD,
			       win),
		{},
		{ return -EINVAL; });

  /* Signal errors with return codes */
  MPI_Win_set_errhandler(*win, MPI_ERRORS_RETURN);

  MPI_TRY_CATCH(MPI_Win_fence(0, *win),
		{},
		{ return -EINVAL; });

  return ES_OK;
}

/*! Create dummy MPI Windows for clients
 *
 */
static int
es_net_init_client_mpi_win(es_state *esim)
{
  int rc;

  if (ES_OK != (rc = es_net_create_mpi_win(esim, &esim->net.mem_win, NULL, 0)))
    return rc;

  if (ES_OK != (rc = es_net_create_mpi_win(esim,
					   &esim->net.ext_ram_win,
					   NULL,
					   0)))
    return rc;

  if (ES_OK != (rc = es_net_create_mpi_win(esim,
					   &esim->net.ext_write_win,
					   NULL,
					   0)))
    return rc;

  return ES_OK;
}

/*! Create MPI Windows for Remote Memory Access to core SRAM + external RAM
 *
 * @warn Must be called late in es_init(), after esim->coreid is set.
 */
int
es_net_init_mpi_win(es_state *esim)
{
  int rc;

  if (esim->is_client)
    return es_net_init_client_mpi_win(esim);

  /* Expose per core local SRAM to other MPI processes */
  if (ES_OK != (rc = es_net_create_mpi_win(esim,
					   &esim->net.mem_win,
					   (void *) esim->this_core_mem,
					   ES_CLUSTER_CFG.core_mem_region)))
    return rc;


  /* Expose external RAM to other MPI processes.
   * Let process with lowest rank on `ext_ram_node' provide the MPI window.
   * Because this is a collective call all other processes share a
   * NULL-window.
   */
    {
      void *ext_ram_ptr;
      size_t win_size;

      if (ES_CLUSTER_CFG.ext_ram_rank == esim->net.rank)
	{
	  ext_ram_ptr = (void *) esim->ext_ram;
	  win_size = ES_CLUSTER_CFG.ext_ram_size;
	}
      else
	{
	  ext_ram_ptr = NULL;
	  win_size = 0;
	}

      if (ES_OK != (rc = es_net_create_mpi_win(esim,
					       &esim->net.ext_ram_win,
					       ext_ram_ptr,
					       win_size)))
	return rc;
    }

  /* Expose external write flag */
    {
      sim_cpu *current_cpu;
      void *ext_write_ptr;
      size_t size;

      current_cpu = (sim_cpu *) esim->this_core_cpu_state;
      ext_write_ptr = (void *) &current_cpu->external_write;
      size = sizeof(current_cpu->external_write);

      if (ES_OK != (rc = es_net_create_mpi_win(esim,
					       &esim->net.ext_write_win,
					       ext_write_ptr,
					       size)))
	return rc;
    }

  return ES_OK;
}

void
es_net_addr_translate(const es_state *esim, es_transl *transl, uint32_t addr)
{
  if (ES_ADDR_IS_EXT_RAM(addr))
    {
      transl->location = ES_LOC_NET_RAM;
      transl->in_region = ES_CLUSTER_CFG.ext_ram_size -
       (addr % ES_CLUSTER_CFG.ext_ram_size);

      transl->net_rank = ES_CLUSTER_CFG.ext_ram_rank;
      transl->net_win = &esim->net.ext_ram_win;
      transl->net_offset = (addr % ES_CLUSTER_CFG.ext_ram_size);
    }
  else if (ES_ADDR_IS_MMR(addr))
    {
      if (addr % 4)
	{
	  /* Unaligned */
	  /*! @todo ES_LOC_UNALIGNED would be more accurate */
	  transl->location = ES_LOC_INVALID;
	}
      else
	{
	  transl->location = ES_LOC_NET_MMR;
	  transl->reg = (addr & (ES_CORE_MMR_SIZE-1)) >> 2;
	  /*! @todo Could optimize this so that entire region is one
	     transaction */
	  transl->in_region = 4;

	  transl->net_rank = es_net_coreid_to_rank(esim, transl->coreid);

	  /*! @todo Do we use a window for this? */
	  transl->net_win = NULL;
	  transl->net_offset = 0;
	}
    }
  else
    {
      transl->location = ES_LOC_NET;
      /** @todo We have to check on which side of the memory mapped
       * register we are and take that into account.
       */
      transl->in_region = (ES_CLUSTER_CFG.core_mem_region) -
       (addr % ES_CLUSTER_CFG.core_mem_region);

      transl->net_rank = es_net_coreid_to_rank(esim, transl->coreid);
      transl->net_offset = ES_ADDR_CORE_OFFSET(addr);
      transl->net_win = &esim->net.mem_win;
    }
}

static int
es_net_tx_one_mem_load(es_state *esim, es_transaction *tx)
{
  size_t n, dwords, leading, trailing;
  uint8_t leading_buf[8], trailing_buf[8];
  int do_leading_memmove_after_unlock;

  n = min(tx->remaining, tx->sim_addr.in_region);

  /** Read in 64-bit chunks as far as possible and fix any leading or trailing
    * bytes with separate fetches.
    * @todo What about alignment checking? Now we allow anything.
    */
  leading  = min (n, (8 - (tx->sim_addr.addr % 8)) % 8);
  trailing = (n - leading) % 8;
  dwords   = (n - (leading + trailing)) / 8;

  /* If possible, do memmove() for leading bytes after MPI_Win_unlock().
   * Saves one flush.
   */
  do_leading_memmove_after_unlock = (!dwords && leading);

  MPI_TRY_CATCH(MPI_Win_lock(MPI_LOCK_SHARED,
			     tx->sim_addr.net_rank,
			     MPI_MODE_NOCHECK,
			     *tx->sim_addr.net_win),
		{},
		{ return -EINVAL; });
  if (leading)
    {
      MPI_TRY_CATCH(MPI_Get_accumulate(NULL,
				       1, /* Can we say 0 ? */
				       MPI_UINT64_T,
				       (void *) leading_buf,
				       1,
				       MPI_UINT64_T,
				       tx->sim_addr.net_rank,
				       tx->sim_addr.net_offset & (~7),
				       1,
				       MPI_UINT64_T,
				       MPI_NO_OP,
				       *tx->sim_addr.net_win),
		    {},
		    { return -EINVAL; });

      if (!do_leading_memmove_after_unlock)
	{
	  MPI_TRY_CATCH(MPI_Win_flush_local(tx->sim_addr.net_rank,
					    *tx->sim_addr.net_win),
			{},
			{ return -EINVAL; });
	  memmove((void *) tx->target,
		  (void *) &leading_buf[8-leading],
		  leading);
	  tx->target              += leading;
	  tx->sim_addr.net_offset += leading;
	  tx->remaining           -= leading;
	}
    }
  if (dwords)
    {
      MPI_TRY_CATCH(MPI_Get_accumulate(NULL,
				       dwords, /* Can we say 0 ? */
				       MPI_UINT64_T,
				       (void *) tx->target,
				       dwords,
				       MPI_UINT64_T,
				       tx->sim_addr.net_rank,
				       tx->sim_addr.net_offset,
				       dwords,
				       MPI_UINT64_T,
				       MPI_NO_OP,
				       *tx->sim_addr.net_win),
		    {},
		    { return -EINVAL; });
      tx->target              += (dwords * 8);
      tx->sim_addr.net_offset += (dwords * 8);
      tx->remaining           -= (dwords * 8);
    }
  if (trailing)
    {
      MPI_TRY_CATCH(MPI_Get_accumulate(NULL,
				       1, /* Can we say 0 ? */
				       MPI_UINT64_T,
				       (void *) trailing_buf,
				       1,
				       MPI_UINT64_T,
				       tx->sim_addr.net_rank,
				       tx->sim_addr.net_offset,
				       1,
				       MPI_UINT64_T,
				       MPI_NO_OP,
				       *tx->sim_addr.net_win),
		    {},
		    { return -EINVAL; });
      /* Do actual copy after call to MPI_Win_unlock(). Saves one flush */
    }

  MPI_TRY_CATCH(MPI_Win_unlock(tx->sim_addr.net_rank, *tx->sim_addr.net_win),
		{},
		{ return -EINVAL; });

  if (do_leading_memmove_after_unlock)
    {
      memmove((void *) tx->target,
	      (void *) &leading_buf[8-leading],
	      leading);
      tx->target              += leading;
      tx->sim_addr.net_offset += leading;
      tx->remaining           -= leading;
    }
  if (trailing)
    {
      memmove((void *) tx->target, (void *) trailing_buf, trailing);
      tx->target              += trailing;
      tx->sim_addr.net_offset += trailing;
      tx->remaining           -= trailing;
    }

  return ES_OK;
}

static int
es_net_tx_one_mem_store(es_state *esim, es_transaction *tx)
{
  /*! @todo Relax locking for better performance */

  fieldtype_of(sim_cpu, external_write) one, dontcare;
  size_t n, dwords, leading, trailing;

  one = 1;

  n = min(tx->remaining, tx->sim_addr.in_region);

  /** Write in 64-bit chunks as far as possible and fix any leading or trailing
    * bytes with separate stores.
    * @todo What about alignment checking? Now we allow anything.
    */
  leading  = min (n, (8 - (tx->sim_addr.addr % 8)) % 8);
  trailing = (n - leading) % 8;
  dwords   = (n - (leading + trailing)) / 8;

  MPI_TRY_CATCH(MPI_Win_lock(MPI_LOCK_SHARED,
			     tx->sim_addr.net_rank,
			     MPI_MODE_NOCHECK,
			     *tx->sim_addr.net_win),
		{},
		{ return -EINVAL; });

#define ACCUM(N, Datatype)\
  do\
    {\
      MPI_TRY_CATCH(MPI_Accumulate((void *) tx->target,\
				   (N),\
				   mpi_type(sizeof(Datatype)),\
				   tx->sim_addr.net_rank,\
				   tx->sim_addr.net_offset,\
				   (N),\
				   mpi_type(sizeof(Datatype)),\
				   MPI_REPLACE,\
				   *tx->sim_addr.net_win),\
		    {},\
		    { return -EINVAL; });\
      tx->target              += sizeof(Datatype) * (N);\
      tx->sim_addr.net_offset += sizeof(Datatype) * (N);\
      tx->remaining           -= sizeof(Datatype) * (N);\
    }\
  while (0)


  if (leading & 1)
    ACCUM(1, uint8_t);
  if (leading & 2)
    ACCUM(1, uint16_t);
  if (leading & 4)
    ACCUM(1, uint32_t);

  if (dwords)
    ACCUM(dwords, uint64_t);

  if (trailing & 4)
    ACCUM(1, uint32_t);
  if (trailing & 2)
    ACCUM(1, uint16_t);
  if (trailing & 1)
    ACCUM(1, uint8_t);


#undef ACCUM

  MPI_TRY_CATCH(MPI_Win_unlock(tx->sim_addr.net_rank, *tx->sim_addr.net_win),
		{},
		{ return -EINVAL; });

  /*! We're done here if write was to external ram */
  if (tx->sim_addr.location == ES_LOC_NET_RAM)
    return ES_OK;

  /*! Update current_cpu.external_write on remote in remote cpu state to
   *  trigger cache scache flush */
  MPI_TRY_CATCH(MPI_Win_lock(MPI_LOCK_SHARED,
			     tx->sim_addr.net_rank,
			     MPI_MODE_NOCHECK,
			     esim->net.ext_write_win),
		{},
		{ return -EINVAL; });
  MPI_TRY_CATCH(MPI_Accumulate((void *) &one,
			       1,
			       ES_NET_MPI_TYPE(one),
			       tx->sim_addr.net_rank,
			       0,
			       1,
			       ES_NET_MPI_TYPE(one),
			       MPI_REPLACE,
			       esim->net.ext_write_win),
		{},
		{ return -EINVAL; });
  MPI_TRY_CATCH(MPI_Win_unlock(tx->sim_addr.net_rank, esim->net.ext_write_win),
		{},
		{ return -EINVAL; });

  return ES_OK;
}

static int
es_net_tx_one_mem_testset(es_state *esim, es_transaction *tx)
{
  uint32_t *target;
  uint32_t zero, one, tmp;

  zero = 0;
  one = 1;

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

  if (tx->sim_addr.location != ES_LOC_NET)
    return -EINVAL;

  MPI_TRY_CATCH(MPI_Win_lock(MPI_LOCK_SHARED,
			     tx->sim_addr.net_rank,
			     MPI_MODE_NOCHECK,
			     *tx->sim_addr.net_win),
		{},
		{ return -EINVAL; });

  MPI_TRY_CATCH(MPI_Compare_and_swap((void *) target,
				     (void *) &zero,
				     (void *) &tmp,
				     MPI_UINT32_T,
				     tx->sim_addr.net_rank,
				     tx->sim_addr.net_offset,
				     *tx->sim_addr.net_win),
		{},
		{ return -EINVAL; });

  MPI_TRY_CATCH(MPI_Win_unlock(tx->sim_addr.net_rank, *tx->sim_addr.net_win),
		{},
		{ return -EINVAL; });

  *target = tmp;

  tx->target += 4;
  tx->remaining -= 4;

  /*! Update current_cpu.external_write on remote in remote cpu state to
   *  trigger cache scache flush */
  MPI_TRY_CATCH(MPI_Win_lock(MPI_LOCK_SHARED,
			     tx->sim_addr.net_rank,
			     MPI_MODE_NOCHECK,
			     esim->net.ext_write_win),
		{},
		{ return -EINVAL; });
  MPI_TRY_CATCH(MPI_Accumulate((void *) &one,
			       1,
			       ES_NET_MPI_TYPE(one),
			       tx->sim_addr.net_rank,
			       0,
			       1,
			       ES_NET_MPI_TYPE(one),
			       MPI_REPLACE,
			       esim->net.ext_write_win),
		{},
		{ return -EINVAL; });
  MPI_TRY_CATCH(MPI_Win_unlock(tx->sim_addr.net_rank, esim->net.ext_write_win),
		{},
		{ return -EINVAL; });

  return ES_OK;

}

static int
es_net_tx_one_mmr(es_state *esim, es_transaction *tx)
{
  int reg, n;
  uint32_t *target;

  es_net_mmr_request req;
  es_net_mmr_reply reply;
  MPI_Status status;

  /* Alignment was checked in es_addr_translate.
   * Hardware doesn't seem to support reading partial regs so neither do we.
   */
  if (tx->remaining < 4)
    return -EINVAL;

  target = (uint32_t *) tx->target;

  req.reg = tx->sim_addr.reg;
  req.origin = esim->coreid;

  switch (tx->type)
    {
    case ES_REQ_LOAD:
      req.type = ES_NET_MMR_REQ_LOAD;
      break;
    case ES_REQ_STORE:
      req.type = ES_NET_MMR_REQ_STORE;
      req.value = *target;
      break;
    case ES_REQ_TESTSET:
      fprintf(stderr, "ESIM:NET: MMR TESTSET not implemented.\n");
      /* fall through */
    default:
      return -EINVAL;
    }

  MPI_TRY_CATCH(MPI_Send((void *) &req,
			 sizeof(req),
			 MPI_UINT8_T,
			 tx->sim_addr.net_rank,
			 ES_NET_TAG_REQUEST,
			 ES_NET_COMM_WORLD),
		{},
		{ return -EINVAL; });

  MPI_TRY_CATCH(MPI_Recv((void *) &reply,
			 sizeof(reply),
			 MPI_UINT8_T,
			 tx->sim_addr.net_rank,
			 ES_NET_TAG_REPLY,
			 ES_NET_COMM_WORLD,
			 &status),
		{},
		{ return -EINVAL; });

  if (tx->type == ES_REQ_LOAD)
    *target = reply.value;

  tx->remaining -= 4;
  tx->target += 4;

  return ES_OK;
}

int
es_net_tx_one(es_state *esim, es_transaction *tx)
{
  switch (tx->sim_addr.location)
    {
    case ES_LOC_NET:
    case ES_LOC_NET_RAM:
      switch (tx->type)
	{
	  case ES_REQ_LOAD:
	    return es_net_tx_one_mem_load(esim, tx);
	  case ES_REQ_STORE:
	    return es_net_tx_one_mem_store(esim, tx);
	  case ES_REQ_TESTSET:
	    return es_net_tx_one_mem_testset(esim, tx);
	}

    case ES_LOC_NET_MMR:
      return es_net_tx_one_mmr(esim, tx);

    default:
#if defined(ES_DEBUG) || defined(ES_NET_DEBUG)
      fprintf(stderr, "es_net_tx_one: BUG\n");
#endif
      return -EINVAL;
      break;
    }
}

/*! Remote MMR access thread
 *
 *  @todo Look this over when adding DMA support.
 */
void *
es_net_mmr_thread(void *p)
{
  es_net_mmr_request req;
  es_net_mmr_reply reply;
  MPI_Status status;
  int rc;
  unsigned real_coreid;
  es_state thread_esim_copy;
  es_state *esim;
  es_transaction tx;

  rc = ES_OK;
  esim = &thread_esim_copy;

  memmove((void *) &thread_esim_copy, p, sizeof(es_state));

  /* Save real coreid */
  real_coreid = esim->coreid;

  /* We're called before initialized is set in es_init(). */
  esim->initialized = 1;

  /* Main loop */
  while (1)
    {
      /* Reset source to invalid rank so we can detect if a response is needed
       * on error. */
      status.MPI_SOURCE = -0xBADC0DE;

      MPI_TRY_CATCH(MPI_Recv((void *) &req,
			     sizeof(req),
			     MPI_UINT8_T,
			     MPI_ANY_SOURCE,
			     ES_NET_TAG_REQUEST,
			     ES_NET_COMM_WORLD,
			     &status),
		    {},
		    {
		      rc = -EINVAL;
		      goto handle_error;
		    });

      /* Pretend to be originating core */
      esim->coreid = req.origin;

      /* Common transaction parameters */
      tx.sim_addr.cpu = (sim_cpu *) esim->this_core_cpu_state;
      tx.size = 4;
      tx.remaining = 4;
      tx.sim_addr.reg = req.reg;
      tx.sim_addr.coreid = real_coreid;
      tx.sim_addr.cpu = (sim_cpu *) esim->this_core_cpu_state;

      switch (req.type)
	{
	case ES_NET_MMR_REQ_EXIT:
	  /* Exit thread */
	  return (void *) ES_OK;
	  break;
	case ES_NET_MMR_REQ_LOAD:
	  tx.type = ES_REQ_LOAD;
	  tx.target = (uint8_t *) &reply.value;
	  break;
	case ES_NET_MMR_REQ_STORE:
	  tx.type = ES_REQ_STORE;
	  tx.target = (uint8_t *) &req.value;
	  break;
	/* case ES_NET_MMR_REQ_TESTSET: ??? */
	default:
	   rc = -EINVAL;
	   goto abort;
	}

      reply.rc = es_tx_one_shm_mmr(esim, &tx);

      MPI_TRY_CATCH(MPI_Send((void *) &reply,
			     sizeof(reply),
			     MPI_UINT8_T,
			     status.MPI_SOURCE,
			     ES_NET_TAG_REPLY,
			     ES_NET_COMM_WORLD),
		    {},
		    {
		      rc = -EINVAL;
		      goto abort;
		    });

      continue;

handle_error:
      {
	es_net_mmr_reply reply = { .rc = rc };

	/* Noone to report error to (== noone waiting?) */
	if (status.MPI_SOURCE < 0)
	  {
	    fprintf(stderr, "ESIM:NET:mmr_thread: Error in mainloop, continuing.\n");
	    continue;
	  }

	/* Signal error to waiting process */
	MPI_TRY_CATCH(MPI_Send((void *) &reply,
			       sizeof(reply),
			       MPI_UINT8_T,
			       status.MPI_SOURCE,
			       ES_NET_TAG_REPLY,
			       ES_NET_COMM_WORLD),
		      {},
		      {
			goto abort;
		      });
	continue;
      }
abort:
      /*! Abort when other end is stuck waiting for a reply.
       *  @todo Investigate if there is a way to recover from this.
       *  Maybe timeouts?
       */
      MPI_Abort(ES_NET_COMM_WORLD, EINVAL);
      return (void *) -EINVAL;
    }

  return (void *)ES_OK;
}

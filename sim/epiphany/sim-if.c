/* Main simulator entry points specific to the EPIPHANY.
   Copyright (C) 1996, 1997, 1998, 1999, 2003, 2007, 2008, 2011
   Free Software Foundation, Inc.
   Contributed by Embecosm on behalf of Adapteva.

   This file is part of GDB, the GNU debugger.

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

#include "sim-main.h"
#include "sim-options.h"

#if (WITH_HW)
#include "sim-hw.h"
#endif

#include "libiberty.h"
#include "bfd.h"

#ifdef HAVE_STRING_H
#include <string.h>
#else
#ifdef HAVE_STRINGS_H
#include <strings.h>
#endif
#endif

#include <stdlib.h>
#include <ctype.h>

#include "sim-options.h"

#if WITH_EMESH_SIM
#include <pthread.h>
#include "esim/esim.h"
#if HAVE_E_XML
#include <epiphany_xml_c.h>
#endif
#endif

/* Records simulator descriptor so utilities like epiphany_dump_regs can be
   called from gdb.  */
SIM_DESC current_state=0;
int is_sim_opened=0;

/* Cover function of sim_state_free to free the cpu buffers as well.  */

typedef enum {
  E_OPTION_XML_HDF = OPTION_START, /* Epiphany XML hardware description file */
  E_OPTION_EXT_RAM,
  E_OPTION_COREID,
  E_OPTION_NUM_COLS,
  E_OPTION_NUM_ROWS,
  E_OPTION_FIRST_CORE,
  E_OPTION_ADD_EXT_MEM,
  E_OPTION_EXT_RAM_BASE,
  E_OPTION_EXT_RAM_SIZE,
  /** @todo Add more options:
   * Check es_cluster_cfg in esim.h
   */
} EPIPHANY_OPTIONS;

struct emesh_params {
  /* Required */
  int coreid;
  int num_cols;
  int num_rows;
  int first_coreid;

  /* Extra */
  unsigned epiphany_add_ext_ram;
  int64_t ext_ram_base;
  int64_t ext_ram_size;

  char *xml_hdf_file;
};
static struct emesh_params emesh_params = {-1, -1, -1, -1, 1, -1, -1, NULL};

static void free_state (SIM_DESC);
static void print_epiphany_misc_cpu (SIM_CPU *cpu, int verbose);
static SIM_RC epiphany_option_handler (SIM_DESC, sim_cpu *, int, char *, int);

#ifdef WITH_EMESH_SIM
static SIM_RC sim_esim_cpu_relocate (SIM_DESC sd, int extra_bytes);
static SIM_RC sim_esim_set_options(SIM_DESC sd, sim_cpu *cpu);
static SIM_RC sim_esim_init(SIM_DESC sd);
#endif


static const OPTION options_epiphany[] =
{

  { {"e-external-memory", optional_argument, NULL, E_OPTION_EXT_RAM},
      'e', "off|on", "Turn off/on the external memory region",
      epiphany_option_handler },
#if EMESH_SIM
#if HAVE_E_XML
  { {"e-hdf", required_argument, NULL, E_OPTION_XML_HDF},
      '\0', "FILE", "Epiphany XML hardware description file",
      epiphany_option_handler },
#endif
#if WITH_EMESH_NET
  /* coreid is determined from MPI rank */
#else
  { {"e-coreid", required_argument, NULL, E_OPTION_COREID},
      '\0', "COREID", "Set coreid",
      epiphany_option_handler  },
#endif
  { {"e-cols", required_argument, NULL, E_OPTION_NUM_COLS},
      '\0', "n", "Number of core columns",
      epiphany_option_handler  },
  { {"e-rows", required_argument, NULL, E_OPTION_NUM_ROWS},
      '\0', "n", "Number of core rows",
      epiphany_option_handler  },
  { {"e-first-core", required_argument, NULL, E_OPTION_FIRST_CORE},
      '\0', "COREID", "Coreid of upper leftmost core",
      epiphany_option_handler  },
  { {"e-ext-ram-base", required_argument, NULL, E_OPTION_EXT_RAM_BASE},
      '\0', "address", "Base address of external RAM",
      epiphany_option_handler  },
  { {"e-ext-ram-size", required_argument, NULL, E_OPTION_EXT_RAM_SIZE},
      '\0', "MB", "Size of external RAM in MB",
      epiphany_option_handler  },
#endif
  { {NULL, no_argument, NULL, 0}, '\0', NULL, NULL, NULL, NULL }
};

static void
free_state (SIM_DESC sd)
{
  if (STATE_MODULES (sd) != NULL)
    sim_module_uninstall (sd);
#if WITH_EMESH_SIM
  es_fini(STATE_ESIM(sd));
#else
  sim_cpu_free_all (sd);
#endif
  sim_state_free (sd);
}

static SIM_RC
epiphany_option_handler (SIM_DESC sd, sim_cpu *cpu, int opt, char *arg,
			 int is_command)
{
  char *endp;
  unsigned long ul;
  unsigned value;
  int valid;

  ul = strtoul (arg, &endp, 0);
  valid = ((isdigit (arg[0]) && endp != arg));

  switch ((EPIPHANY_OPTIONS) opt)
    {
    case E_OPTION_EXT_RAM:
      if(strcmp(arg,"off") == 0 ) {
	      emesh_params.epiphany_add_ext_ram = 0;
      }
      if(strcmp(arg,"on") == 0 ) {
	      emesh_params.epiphany_add_ext_ram = 1;
      }
      return SIM_RC_OK;
      break;
#if WITH_EMESH_SIM

#define SET_OR_FAIL(Param, Name)\
  do \
    {\
      if (valid)\
	{\
	  emesh_params.Param = (unsigned) ul;\
	}\
      else\
	{\
	  sim_io_eprintf(sd, "%s: Invalid parameter `%s'\n", Name, arg);\
	  return SIM_RC_FAIL;\
	}\
    }\
  while (0)
#if HAVE_E_XML
    case E_OPTION_XML_HDF:
      emesh_params.xml_hdf_file = arg;
      break;
#endif
    case E_OPTION_COREID:
      SET_OR_FAIL(coreid, "e-coreid");
      break;
    case E_OPTION_NUM_COLS:
      SET_OR_FAIL(num_cols, "e-cols");
      break;
    case E_OPTION_NUM_ROWS:
      SET_OR_FAIL(num_rows, "e-rows");
      break;
    case E_OPTION_FIRST_CORE:
      SET_OR_FAIL(first_coreid, "e-first-core");
      break;
    case E_OPTION_EXT_RAM_BASE:
      SET_OR_FAIL(ext_ram_base, "e-ext-ram-base");
      break;
    case E_OPTION_EXT_RAM_SIZE:
      SET_OR_FAIL(ext_ram_size, "e-ext-ram-size");
      /* Specified in MB */
      emesh_params.ext_ram_size = emesh_params.ext_ram_size << 20;
      break;
#undef SET_OR_FAIL
#endif
    default:
      sim_io_eprintf (sd, "Unknown option %d `%s'\n", opt, arg);
      return SIM_RC_FAIL;
    }
#ifdef WITH_EMESH_SIM
  /* Update options */

  if (STATE_OPEN_KIND (sd) == SIM_OPEN_DEBUG)
    return sim_esim_set_options(sd, cpu);
  else
    return SIM_RC_OK;

#endif
    return SIM_RC_OK;
}



#if WITH_EMESH_SIM
/* Custom sim cpu alloc for emesh sim */
SIM_RC
sim_esim_cpu_relocate (SIM_DESC sd, int extra_bytes)
{
  static unsigned freed = 0; /* Original sim_cpu struct is malloced */
  sim_cpu *new_cpu;

  if (! (new_cpu = es_set_cpu_state(STATE_ESIM(sd), STATE_CPU(sd, 0),
			sizeof(sim_cpu) + extra_bytes)))
    {
      sim_io_eprintf (sd, "Could not set cpu state.\n");
      return SIM_RC_FAIL;
    }

  if (!freed)
    {
      sim_cpu_free(STATE_CPU(sd, 0));
      freed = 1;
    }
  STATE_CPU(sd, 0) = new_cpu;
  return SIM_RC_OK;
}


/* Return SIM_RC_OK if user specified required params, SIM_RC_FAIL otherwise
 * @todo This does not work so well in debugger mode. If e.g. e-cols is set
 * and then e-hdf is set after that, it gets stuck.
 */
static SIM_RC sim_esim_have_required_params(SIM_DESC sd)
{
#define FAIL_IF(Expr, Desc)\
  if (Expr)\
    {\
      if (emesh_params.xml_hdf_file != NULL ||\
	  STATE_OPEN_KIND (sd) == SIM_OPEN_STANDALONE) \
	sim_io_eprintf(sd, "%s\n", Desc);\
      return SIM_RC_FAIL;\
    }

#if WITH_EMESH_NET
  /* Coreid is determined by MPI RANK */
#else
  /* If there is only one core, we can determine coreid from first core, and
   * vice versa. */
  if (emesh_params.num_rows == 1 && emesh_params.num_cols == 1)
    {
      if (0 > emesh_params.coreid)
	emesh_params.coreid = emesh_params.first_coreid;

      if (0 > emesh_params.first_coreid)
	emesh_params.first_coreid = emesh_params.coreid;
    }

  FAIL_IF(0 > emesh_params.coreid      , "--e-coreid not set");
#endif

  /* Either use hardware definition file or other params */
  if (emesh_params.xml_hdf_file != NULL)
    {
      FAIL_IF(-1 != emesh_params.num_cols    ,
	      "Both --e-xml-file and --e-num-cols set");
      FAIL_IF(-1 != emesh_params.num_rows    ,
	      "Both --e-xml-file and --e-num-rows set");
      FAIL_IF(-1 != emesh_params.first_coreid,
	      "Both --e-xml-file and --e-first-core set");
      /** @todo Also check add_ext_ram */
    }
  else
    {
      FAIL_IF(0 > emesh_params.num_cols    , "--e-num-cols not set");
      FAIL_IF(0 > emesh_params.num_rows    , "--e-num-rows not set");
      FAIL_IF(0 > emesh_params.first_coreid, "--e-first-core not set");
    }
#undef FAIL_IF

  return SIM_RC_OK;
}

/* Only called from debugger */
static SIM_RC sim_esim_set_options(SIM_DESC sd, sim_cpu *cpu)
{
  if (sim_esim_have_required_params(sd) != SIM_RC_OK)
    return SIM_RC_OK;

  if (sim_esim_init(sd) != SIM_RC_OK)
    return SIM_RC_FAIL;

  return SIM_RC_OK;
}

#if HAVE_E_XML
static SIM_RC sim_esim_params_from_xml(SIM_DESC sd)
{
  e_xml_t xml;
  platform_definition_t* p;
  int i;

  xml = e_xml_new(emesh_params.xml_hdf_file);

#define FAIL_IF(Expr, Desc)\
  if ((Expr))\
    {\
      sim_io_eprintf(sd, "%s\n", (Desc));\
      goto err_out;\
    }

  if (e_xml_parse(xml))
    {
      sim_io_eprintf(sd, "Could not parse XML HDF file `%s'\n",
		     emesh_params.xml_hdf_file);
      goto err_out;
    }
  FAIL_IF((p = e_xml_get_platform(xml)) == NULL, "Internal error in e-xml.");
  FAIL_IF(p->num_chips != 1, "The simulator only supports one chip");

  emesh_params.num_rows = p->chips[0].num_rows;
  emesh_params.num_cols = p->chips[0].num_cols;
  emesh_params.first_coreid = (p->chips[0].yid << 6) + p->chips[0].xid;
  /** @todo */
  /* emesh_params.core_mem_size = p->chips[0].core_memory_size; */

  /* No external RAM unless specified in HDF file */
  emesh_params.epiphany_add_ext_ram = 0;

  for (i=0; i < p->num_banks; i++)
    {
      /** @todo Will mem naming always be the same ? */
      if (strncmp(p->ext_mem[i].name, "EXTERNAL_DRAM", 13) == 0)
	{
	  /* Fail if there already was an ext ram bank */
	  FAIL_IF(emesh_params.epiphany_add_ext_ram,
		  "The simulator only supports at most 1 memory bank");

	  emesh_params.epiphany_add_ext_ram = 1;

	  emesh_params.ext_ram_base = p->ext_mem[i].base;
	  emesh_params.ext_ram_size = p->ext_mem[i].size;
	}
    }

#undef FAIL_IF

out:
  e_xml_delete(xml);
  return SIM_RC_OK;
err_out:
  e_xml_delete(xml);
  return SIM_RC_FAIL;
}
#endif /* HAVE_E_XML */

static SIM_RC
sim_esim_init(SIM_DESC sd)
{
  es_cluster_cfg cluster;
  struct emesh_params *p;
  uint64_t ext_ram_size, ext_ram_base;

  if (es_initialized(STATE_ESIM(sd)) == ES_OK)
    return SIM_RC_OK;

  if (sim_esim_have_required_params(sd) != SIM_RC_OK)
    return SIM_RC_FAIL;

  p = &emesh_params;

  ext_ram_size = 32*1024*1024;
  ext_ram_base = 0x8e000000;

#if HAVE_E_XML
  /* Parse XML file, if specified */
  if (emesh_params.xml_hdf_file != NULL)
    {
      if (sim_esim_params_from_xml(sd) != SIM_RC_OK)
	return SIM_RC_FAIL;
    }
#endif

  memset(&cluster, 0, sizeof(cluster));

  cluster.col_base = p->first_coreid & ((1 << 6) -1);
  cluster.row_base = p->first_coreid >> 6;
  cluster.cols = p->num_cols;
  cluster.rows = p->num_rows;
  cluster.core_mem_region = 1024*1024;

  if (p->epiphany_add_ext_ram)
    {
      ext_ram_size = (0 <= p->ext_ram_size) ? p->ext_ram_size : ext_ram_size;
      ext_ram_base = (0 <= p->ext_ram_base) ? p->ext_ram_base : ext_ram_base;
    }
  else
    {
      ext_ram_size = 0;
      ext_ram_base = 0xffffffff;
    }
  cluster.ext_ram_size = ext_ram_size;
  cluster.ext_ram_base = ext_ram_base;
  cluster.ext_ram_node = 0;

  if (es_init(&STATE_ESIM(sd), cluster, p->coreid) != ES_OK)
    {
      return SIM_RC_FAIL;
    }

  if (sim_esim_cpu_relocate (sd, cgen_cpu_max_extra_bytes ()) != SIM_RC_OK)
    {
      return SIM_RC_FAIL;
    }

  /*! Set up lock and cond vars
   *  @todo Should be moved to esim
   */
  {
    SIM_CPU *current_cpu;
    pthread_mutexattr_t mutexattr;
    pthread_condattr_t condattr;

    current_cpu = STATE_CPU (sd, 0);

    pthread_mutexattr_init(&mutexattr);
    pthread_condattr_init(&condattr);

    pthread_mutexattr_setpshared(&mutexattr, PTHREAD_PROCESS_SHARED);
    pthread_condattr_setpshared(&condattr, PTHREAD_PROCESS_SHARED);

    pthread_mutex_init(&current_cpu->scr_lock, &mutexattr);
    pthread_cond_init(&current_cpu->scr_wakeup_cond, &condattr);
    pthread_cond_init(&current_cpu->scr_writeslot_cond, &condattr);

    current_cpu->scr_remote_write_reg = -1;
    current_cpu->scr_remote_write_val = 0xbaadbeef;

    pthread_condattr_destroy(&condattr);
    pthread_mutexattr_destroy(&mutexattr);
  }

  sim_io_eprintf(sd, "ESIM: Initialized successfully\n");

  return SIM_RC_OK;
}
#endif /* WITH_EMESH_SIM */

/* Create an instance of the simulator.  */

SIM_DESC
sim_open (kind, callback, abfd, argv)
     SIM_OPEN_KIND kind;
     host_callback *callback;
     struct bfd *abfd;
     char **argv;
{
  SIM_DESC sd = sim_state_alloc (kind, callback);
  char c;
  int i;

  /* The cpu data is kept in a separately allocated chunk of memory.  */
  if (sim_cpu_alloc_all (sd, 1, cgen_cpu_max_extra_bytes ()) != SIM_RC_OK)
    {
      free_state (sd);
      return 0;
    }

#if 0 /* FIXME: pc is in mach-specific struct */
  /* FIXME: watchpoints code shouldn't need this */
  {
    SIM_CPU *current_cpu = STATE_CPU (sd, 0);
    STATE_WATCHPOINTS (sd)->pc = &(PC);
    STATE_WATCHPOINTS (sd)->sizeof_pc = sizeof (PC);
  }
#endif

  if (sim_pre_argv_init (sd, argv[0]) != SIM_RC_OK)
    {
      free_state (sd);
      return 0;
    }

#if 0 /* FIXME: 'twould be nice if we could do this */
  /* These options override any module options.
     Obviously ambiguity should be avoided, however the caller may wish to
     augment the meaning of an option.  */
  if (extra_options != NULL)
    sim_add_option_table (sd, extra_options);
#endif


  sim_add_option_table (sd, NULL, options_epiphany);

  /* getopt will print the error message so we just have to exit if this fails.
     FIXME: Hmmm...  in the case of gdb we need getopt to call
     print_filtered.  */
  if (sim_parse_args (sd, argv) != SIM_RC_OK)
    {
      free_state (sd);
      return 0;
    }

#if WITH_EMESH_SIM
  if (STATE_OPEN_KIND (sd) == SIM_OPEN_STANDALONE)
    {
      if (sim_esim_init(sd) != SIM_RC_OK)
	return SIM_RC_FAIL;
    }
#endif

#if 0
  /* Allocate a handler for the control registers and other devices
     if no memory for that range has been allocated by the user.
     All are allocated in one chunk to keep things from being
     unnecessarily complicated.  */
  if (sim_core_read_buffer (sd, NULL, read_map, &c, EPIPHANY_DEVICE_ADDR, 1) == 0)
    sim_core_attach (sd, NULL,
		     0 /*level*/,
		     access_read_write,
		     0 /*space ???*/,
		     EPIPHANY_DEVICE_ADDR, EPIPHANY_DEVICE_LEN /*nr_bytes*/,
		     0 /*modulo*/,
		     &epiphany_devices,
		     NULL /*buffer*/);

#endif

  /* Allocate core managed memory if none specified by user.  */

#if (WITH_HW)
  sim_hw_parse (sd, "/epiphany_mem");
  /** @todo Need to be able to map external mem */
#else
  if (sim_core_read_buffer (sd, NULL, read_map, &c, 0, 1) == 0)
    sim_do_commandf (sd, "memory region 0,0x%x", EPIPHANY_DEFAULT_MEM_SIZE);

  if (emesh_params.epiphany_add_ext_ram)
    {
      if (sim_core_read_buffer (sd, NULL, read_map, &c,
				EPIPHANY_DEFAULT_EXT_MEM_BANK0_START, 1) == 0)
	sim_do_commandf (sd, "memory region 0x%x,0x%x",
			 EPIPHANY_DEFAULT_EXT_MEM_BANK0_START,
			 EPIPHANY_DEFAULT_EXT_MEM_BANK_SIZE);

      if (sim_core_read_buffer (sd, NULL, read_map, &c,
				EPIPHANY_DEFAULT_EXT_MEM_BANK1_START, 1) == 0)
	sim_do_commandf (sd, "memory region 0x%x,0x%x",
			 EPIPHANY_DEFAULT_EXT_MEM_BANK1_START,
			 EPIPHANY_DEFAULT_EXT_MEM_BANK_SIZE);

    }
#endif /* (WITH_HW) */

  /* check for/establish the reference program image */
  if (sim_analyze_program (sd,
			   (STATE_PROG_ARGV (sd) != NULL
			    ? *STATE_PROG_ARGV (sd)
			    : NULL),
			   abfd) != SIM_RC_OK)
    {
      free_state (sd);
      return 0;
    }

  /* Establish any remaining configuration options.  */
  if (sim_config (sd) != SIM_RC_OK)
    {
      free_state (sd);
      return 0;
    }

  if (sim_post_argv_init (sd) != SIM_RC_OK)
    {
      free_state (sd);
      return 0;
    }

  /* Open a copy of the cpu descriptor table.  */
  {
    CGEN_CPU_DESC cd = epiphany_cgen_cpu_open_1 (STATE_ARCHITECTURE (sd)->printable_name,
					     CGEN_ENDIAN_LITTLE);
    for (i = 0; i < MAX_NR_PROCESSORS; ++i)
      {
	SIM_CPU *cpu = STATE_CPU (sd, i);
	CPU_CPU_DESC (cpu) = cd;
	CPU_DISASSEMBLER (cpu) = sim_cgen_disassemble_insn;
      }
    epiphany_cgen_init_dis (cd);
  }

  /* Initialize various cgen things not done by common framework.
     Must be done after epiphany_cgen_cpu_open.  */
  cgen_init (sd);

  for (c = 0; c < MAX_NR_PROCESSORS; ++c)
    {
      /* Only needed for profiling, but the structure member is small.  */
      memset (CPU_EPIPHANY_MISC_PROFILE (STATE_CPU (sd, i)), 0,
	      sizeof (* CPU_EPIPHANY_MISC_PROFILE (STATE_CPU (sd, i))));
      /* Hook in callback for reporting these stats */
      PROFILE_INFO_CPU_CALLBACK (CPU_PROFILE_DATA (STATE_CPU (sd, i)))
	= print_epiphany_misc_cpu;
    }

  /* Store in a global so things like sparc32_dump_regs can be invoked
     from the gdb command line.  */
  current_state = sd;
  is_sim_opened = 1; /* To distinguish between HW and simulator target.  */

  {
    SIM_CPU *current_cpu;
    current_cpu = STATE_CPU (sd, 0);
    cgen_init_accurate_fpu (STATE_CPU (sd, 0), CGEN_CPU_FPU (current_cpu),
			    epiphany_fpu_error);
  }

  return sd;
}

void
sim_close (sd, quitting)
     SIM_DESC sd;
     int quitting;
{
  epiphany_cgen_cpu_close (CPU_CPU_DESC (STATE_CPU (sd, 0)));
#if WITH_EMESH_SIM
  if (es_initialized(STATE_ESIM(sd)) == ES_OK)
    {
      sim_io_eprintf(sd, "ESIM: Waiting for other cores...");
      es_wait_exit(STATE_ESIM(sd));
      sim_io_eprintf(sd, " done.\n");
    }
#endif
  sim_module_uninstall (sd);
  free_state(sd);
}

SIM_RC
sim_create_inferior (sd, abfd, argv, envp)
     SIM_DESC sd;
     struct bfd *abfd;
     char **argv;
     char **envp;
{
  SIM_CPU *current_cpu = STATE_CPU (sd, 0);
  SIM_ADDR addr;

#if WITH_EMESH_SIM
  if (es_initialized(STATE_ESIM(sd)) != ES_OK ||
      !es_get_coreid(STATE_ESIM(sd)))
    {
      if (STATE_OPEN_KIND (sd) == SIM_OPEN_STANDALONE)
	sim_io_eprintf(sd,
		       "ESIM: Missing parameters. Call gdb with \"--help\"\n");
      else
	sim_io_eprintf(sd, "ESIM: Missing parameters. Say \"sim help\"\n");
      return SIM_RC_FAIL;
    }
#endif


  if (abfd != NULL)
    addr = bfd_get_start_address (abfd);
  else
    addr = 0;
  sim_pc_set (current_cpu, addr);

#ifdef EPIPHANY_LINUX
  epiphanybf_h_cr_set (current_cpu,
		       epiphany_decode_gdb_ctrl_regnum(SPI_REGNUM), 0x1f00000);
  epiphanybf_h_cr_set (current_cpu,
		       epiphany_decode_gdb_ctrl_regnum(SPU_REGNUM), 0x1f00000);
#endif

#if 0
  STATE_ARGV (sd) = sim_copy_argv (argv);
  STATE_ENVP (sd) = sim_copy_argv (envp);
#endif

#if WITH_EMESH_SIM
  /* Set coreid in cpu register. Do it via backdoor since it is (should be)
   * read only.
   */
  epiphanybf_h_all_registers_set_raw(STATE_CPU(sd, 0), H_REG_MESH_COREID,
				 es_get_coreid(STATE_ESIM(sd)));

  if (STATE_ENVIRONMENT (sd) != OPERATING_ENVIRONMENT)
    {
      /* Start by triggering SYNC interrupt*/
      epiphanybf_h_all_registers_set(STATE_CPU(sd, 0), H_REG_SCR_ILATST, 1);
    }

#endif

  return SIM_RC_OK;
}

/* PROFILE_CPU_CALLBACK */

static void
print_epiphany_misc_cpu (SIM_CPU *cpu, int verbose)
{
  SIM_DESC sd = CPU_STATE (cpu);
  char buf[20];

  if (CPU_PROFILE_FLAGS (cpu) [PROFILE_INSN_IDX])
    {
      sim_io_printf (sd, "Miscellaneous Statistics\n\n");
      sim_io_printf (sd, "  %-*s %s\n\n",
		     PROFILE_LABEL_WIDTH, "Fill nops:",
		     sim_add_commas (buf, sizeof (buf),
				     CPU_EPIPHANY_MISC_PROFILE (cpu)->fillnop_count));
    }
}

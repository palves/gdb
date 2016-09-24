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

#ifndef __emesh_net_h__
#define __emesh_net_h__

/*
 * ESIM Networking support.
 *
 * Uses MPI.
 *
 * These are private API structures and functions, and should only be used
 * from within ESIM code.
 */

#if !WITH_EMESH_NET
#error "WITH_EMESH_NET=1 not set. This file should not be included"
#endif

#include <pthread.h>
#include <mpi.h>

#include "esim.h"

#define ES_CORE_MMR_SIZE 2048

typedef struct es_net_state_ {
  int       mpi_initialized;
  MPI_Comm  comm;            /*!< Communicator w/ right process rank order */
  int       rank;            /*!< This process' rank (in comm) */
  int       size;            /*!< Total number of MPI processes */
  int       sim_processes;   /*!< Total number of simulator processes */
  MPI_Win   mem_win;         /*!< MPI window for remote access local mem */
  MPI_Win   ext_ram_win;     /*!< MPI window for remote access to external ram */
  MPI_Win   ext_write_win;   /*!< Expose external write flag  */
  pthread_t mmr_thread;    /*!< MMR access remote helper thread */
} es_net_state;



/*! Type of memory request */
typedef enum es_net_mmr_req_t {
  ES_NET_MMR_REQ_LOAD,
  ES_NET_MMR_REQ_STORE,
  ES_NET_MMR_REQ_TESTSET,

  /* Send to instruct helper thread to exit */
  ES_NET_MMR_REQ_EXIT
} es_net_mmr_req_t;

typedef struct es_net_mmr_request_ {
  es_net_mmr_req_t type;
  unsigned         reg;
  uint32_t         value;
  unsigned         origin; /*! Originating coreid */
} es_net_mmr_request;

typedef struct es_net_mmr_reply_ {
  int      rc;
  uint32_t value;
} es_net_mmr_reply;

#define ES_NET_TAG_REQUEST         1
#define ES_NET_TAG_REPLY	   2

typedef struct es_transl_ es_transl;
typedef struct es_transaction_ es_transaction;

int es_net_init(es_state *esim, es_cluster_cfg *cluster);
void es_net_fini(es_state *esim);
int es_net_set_coreid_from_rank(es_state *esim);
void es_net_wait_exit(es_state *esim);
void es_net_wait_run(es_state *esim);
int es_net_init_mmr(es_state *esim);
int es_net_init_mpi_win(es_state *esim);
void es_net_addr_translate(const es_state *esim,
			   es_transl *transl,
			   uint32_t addr);
int es_net_tx_one(es_state *esim, es_transaction *tx);

#endif /* __emesh_net_h__ */

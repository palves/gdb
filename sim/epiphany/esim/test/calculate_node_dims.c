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

#include <stdio.h>
#include <string.h>

#define ESIM_TEST
#include "../esim.h"
/* Need to access internal structures */
#include "../esim.c"

void
test(unsigned rows, unsigned cols)
{
  es_state *esim;
  es_cluster_cfg cluster;
  es_node_cfg node;

  int i, rc, num_cores;

  memset(&node, 0, sizeof(node));
  memset(&cluster, 0, sizeof(cluster));

  node.rank = 0;
  cluster.col_base = 8;
  cluster.row_base = 32;
  cluster.core_mem_region = 1024*1024;
  cluster.ext_ram_size = 32*1024*1024;
  cluster.ext_ram_base = 0x8e000000;
  cluster.ext_ram_node = 0;

  cluster.rows = rows;
  cluster.cols = cols;
  num_cores = rows * cols;
  fprintf(stdout, "-----------------------------------\n");
  fprintf(stdout, "(rows, cols) = (%d, %d)\n", rows, cols);
  fprintf(stdout, "-----------------------------------\n");
  for (i=1; i <= num_cores; i++)
    {
      cluster.nodes = i;
      if (num_cores % i)
	{
#if 0
	  /* To noisy atm */
	  if ((rc = es_init(&esim, node, cluster)) == ES_OK)
	    {
	      fprintf(stderr, "Were supposed to fail but succeded"
		      " with %d nodes.\n", i);
	      exit(1);
	    }
	es_cleanup(esim);
#endif
	}
      else
	{
	  if ((rc = es_init(&esim, node, cluster)) != ES_OK)
	    {
	      fprintf(stderr, "Failed with %d nodes.\n", i);
	      exit(rc);
	    }
	  fprintf(stdout, "%4d nodes: (rows, cols) = (%2d, %2d)\n",
		  i,
		  esim->shm->cluster_cfg.rows_per_node,
		  esim->shm->cluster_cfg.cols_per_node);
	  es_cleanup(esim);
	}
    }
}

int
main()
{
  test(16, 16);
  test(10, 18);
  test(18, 10);
  test(12,  9);
  test( 9, 16);
  return 0;
}

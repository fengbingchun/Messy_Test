/* main.c */

/* Written by Andrew Makhorin <mao@gnu.org>, October 2015. */

/***********************************************************************
*  This program is a stand-alone solver intended for solving Symmetric
*  Traveling Salesman Problem (TSP) with the branch-and-bound method.
*
*  Please note that this program is only an illustrative example. It is
*  *not* a state-of-the-art code, so only small TSP instances (perhaps,
*  having up to 150-200 nodes) can be solved with this code.
*
*  To run this program use the following command:
*
*     tspsol tsp-file
*
*  where tsp-file specifies an input text file containing TSP data in
*  TSPLIB 95 format.
*
*  Detailed description of the input format recognized by this program
*  is given in the report: Gerhard Reinelt, "TSPLIB 95". This report as
*  well as TSPLIB, a library of sample TSP instances (and other related
*  problems), are freely available for research purposes at the webpage
*  <http://www.iwr.uni-heidelberg.de/groups/comopt/software/TSPLIB95/>.
*
*  Symmetric Traveling Salesman Problem
*  ------------------------------------
*  Let a complete undirected graph be given:
*
*     K = (V, E),                                                    (1)
*
*  where V = {1, ..., n} is a set of nodes, E = V cross V is a set of
*  edges. Let also each edge e = (i,j) be assigned a positive number
*  c[i,j], which is the length of e. The Symmetric Traveling Salesman
*  Problem (TSP) is to find a tour in K of minimal length.
*
*  Integer programming formulation of TSP
*  --------------------------------------
*  For a set of nodes W within V introduce the following notation:
*
*     d(W) = {(i,j):i in W and j not in W or i not in W and j in W}, (2)
*
*  i.e. d(W) is the set of edges which have exactly one endnode in W.
*  If W = {v}, i.e. W consists of the only node, we write simply d(v).
*
*  The integer programming formulation of TSP is the following:
*
*     minimize        sum c[i,j] * x[i,j]                            (3)
*                     i,j
*
*     subject to      sum      x[i,j]  = 2      for all v in V       (4)
*                (i,j) in d(v)
*
*                     sum      x[i,j] >= 2      for all W within V,  (5)
*                (i,j) in d(W)                  W != empty, W != V
*
*                x[i,j] in {0, 1}               for all i, j         (6)
*
*  The binary variables x[i,j] have conventional meaning: if x[i,j] = 1,
*  the edge (i,j) is included in the tour, otherwise, if x[i,j] = 0, the
*  edge is not included in the tour.
*
*  The constraints (4) are called degree constraints. They require that
*  for each node v in V there must be exactly two edges included in the
*  tour which are incident to v.
*
*  The constraints (5) are called subtour elimination constraints. They
*  are used to forbid subtours. Note that the number of the subtour
*  elimination constraints grows exponentially on the size of the TSP
*  instance, so these constraints are not included explicitly in the
*  IP, but generated dynamically during the B&B search.
***********************************************************************/

#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <glpk.h>
#include "maxflow.h"
#include "mincut.h"
#include "misc.h"
#include "tsplib.h"

int n;
/* number of nodes in the problem, n >= 2 */

int *c; /* int c[1+n*(n-1)/2]; */
/* upper triangle (without diagonal entries) of the (symmetric) matrix
 * C = (c[i,j]) in row-wise format, where c[i,j] specifies a length of
 * edge e = (i,j), 1 <= i < j <= n */

int *tour; /* int tour[1+n]; */
/* solution to TSP, which is a tour specified by the list of node
 * numbers tour[1] -> ... -> tour[nn] -> tour[1] in the order the nodes
 * are visited; note that any tour is a permutation of node numbers */

glp_prob *P;
/* integer programming problem object */

/***********************************************************************
*  loc - determine reduced index of element of symmetric matrix
*
*  Given indices i and j of an element of a symmetric nxn-matrix,
*  1 <= i, j <= n, i != j, this routine returns the index of that
*  element in an array, which is the upper triangle (without diagonal
*  entries) of the matrix in row-wise format. */

int loc(int i, int j)
{     xassert(1 <= i && i <= n);
      xassert(1 <= j && j <= n);
      xassert(i != j);
      if (i < j)
         return ((n - 1) + (n - i + 1)) * (i - 1) / 2 + (j - i);
      else
         return loc(j, i);
}

/***********************************************************************
*  read_data - read TSP data
*
*  This routine reads TSP data from a specified text file in TSPLIB 95
*  format. */

void read_data(const char *fname)
{     TSP *tsp;
      int i, j;
      tsp = tsp_read_data(fname);
      if (tsp == NULL)
      {  xprintf("TSP data file processing error\n");
         exit(EXIT_FAILURE);
      }
      if (tsp->type != TSP_TSP)
      {  xprintf("Invalid TSP data type\n");
         exit(EXIT_FAILURE);
      }
      n = tsp->dimension;
      xassert(n >= 2);
      if (n > 32768)
      {  xprintf("TSP instance too large\n");
         exit(EXIT_FAILURE);
      }
      c = xalloc(1+loc(n-1, n), sizeof(int));
      for (i = 1; i <= n; i++)
      {  for (j = i+1; j <= n; j++)
            c[loc(i, j)] = tsp_distance(tsp, i, j);
      }
      tsp_free_data(tsp);
      return;
}

/***********************************************************************
*  build_prob - build initial integer programming problem
*
*  This routine builds the initial integer programming problem, which
*  includes all variables (6), objective (3) and all degree constraints
*  (4). Subtour elimination constraints (5) are considered "lazy" and
*  not included in the initial problem. */

void build_prob(void)
{     int i, j, k, *ind;
      double *val;
      char name[50];
      /* create problem object */
      P = glp_create_prob();
      /* add all binary variables (6) */
      for (i = 1; i <= n; i++)
      {  for (j = i+1; j <= n; j++)
         {  k = glp_add_cols(P, 1);
            xassert(k == loc(i,j));
            sprintf(name, "x[%d,%d]", i, j);
            glp_set_col_name(P, k, name);
            glp_set_col_kind(P, k, GLP_BV);
            /* set objective coefficient (3) */
            glp_set_obj_coef(P, k, c[k]);
         }
      }
      /* add all degree constraints (4) */
      ind = xalloc(1+n, sizeof(int));
      val = xalloc(1+n, sizeof(double));
      for (i = 1; i <= n; i++)
      {  k = glp_add_rows(P, 1);
         xassert(k == i);
         sprintf(name, "v[%d]", i);
         glp_set_row_name(P, i, name);
         glp_set_row_bnds(P, i, GLP_FX, 2, 2);
         k = 0;
         for (j = 1; j <= n; j++)
         {  if (i != j)
               k++, ind[k] = loc(i,j), val[k] = 1;
         }
         xassert(k == n-1);
         glp_set_mat_row(P, i, n-1, ind, val);
      }
      xfree(ind);
      xfree(val);
      return;
}

/***********************************************************************
*  build_tour - build tour for corresponding solution to IP
*
*  Given a feasible solution to IP (3)-(6) this routine builds the
*  corresponding solution to TSP, which is a tour specified by the list
*  of node numbers tour[1] -> ... -> tour[nn] -> tour[1] in the order
*  the nodes are to be visited */

void build_tour(void)
{     int i, j, k, kk, *beg, *end;
      /* solution to MIP should be feasible */
      switch (glp_mip_status(P))
      {  case GLP_FEAS:
         case GLP_OPT:
            break;
         default:
            xassert(P != P);
      }
      /* build the list of edges included in the tour */
      beg = xalloc(1+n, sizeof(int));
      end = xalloc(1+n, sizeof(int));
      k = 0;
      for (i = 1; i <= n; i++)
      {  for (j = i+1; j <= n; j++)
         {  double x;
            x = glp_mip_col_val(P, loc(i,j));
            xassert(x == 0 || x == 1);
            if (x)
            {  k++;
               xassert(k <= n);
               beg[k] = i, end[k] = j;
            }
         }
      }
      xassert(k == n);
      /* reorder edges in the list as they follow in the tour */
      for (k = 1; k <= n; k++)
      {  /* find k-th edge of the tour */
         j = (k == 1 ? 1 : end[k-1]);
         for (kk = k; kk <= n; kk++)
         {  if (beg[kk] == j)
               break;
            if (end[kk] == j)
            {  end[kk] = beg[kk], beg[kk] = j;
               break;
            }
         }
         xassert(kk <= n);
         /* put the edge to k-th position in the list */
         i = beg[k], beg[k] = beg[kk], beg[kk] = i;
         j = end[k], end[k] = end[kk], end[kk] = j;
      }
      /* build the tour starting from node 1 */
      xassert(beg[1] == 1);
      for (k = 1; k <= n; k++)
      {  if (k > 1)
            xassert(end[k-1] == beg[k]);
         tour[k] = beg[k];
      }
      xassert(end[n] == 1);
      xfree(beg);
      xfree(end);
      return;
}

/***********************************************************************
*  tour_length - calculate tour length
*
*  This routine calculates the length of the specified tour, which is
*  the sum of corresponding edge lengths. */

int tour_length(const int tour[/*1+n*/])
{     int i, j, sum;
      sum = 0;
      for (i = 1; i <= n; i++)
      {  j = (i < n ? i+1 : 1);
         sum += c[loc(tour[i], tour[j])];
      }
      return sum;
}

/***********************************************************************
*  write_tour - write tour to text file in TSPLIB format
*
*  This routine writes the specified tour to a text file in TSPLIB
*  format. */

void write_tour(const char *fname, const int tour[/*1+n*/])
{     FILE *fp;
      int i;
      xprintf("Writing TSP solution to '%s'...\n", fname);
      fp = fopen(fname, "w");
      if (fp == NULL)
      {  xprintf("Unable to create '%s' - %s\n", fname,
            strerror(errno));
         return;
      }
      fprintf(fp, "NAME : %s\n", fname);
      fprintf(fp, "COMMENT : Tour length is %d\n", tour_length(tour));
      fprintf(fp, "TYPE : TOUR\n");
      fprintf(fp, "DIMENSION : %d\n", n);
      fprintf(fp, "TOUR_SECTION\n");
      for (i = 1; i <= n; i++)
         fprintf(fp, "%d\n", tour[i]);
      fprintf(fp, "-1\n");
      fprintf(fp, "EOF\n");
      fclose(fp);
      return;
}

/***********************************************************************
*  gen_subt_row - generate violated subtour elimination constraint
*
*  This routine is called from the MIP solver to generate a violated
*  subtour elimination constraint (5).
*
*  Constraints of this class has the form:
*
*     sum x[i,j] >= 2, i in W, j in V \ W,
*
*  for all W, where W is a proper nonempty subset of V, V is the set of
*  nodes of the given graph.
*
*  In order to find a violated constraint of this class this routine
*  finds a min cut in a capacitated network, which has the same sets of
*  nodes and edges as the original graph, and where capacities of edges
*  are values of variables x[i,j] in a basic solution to LP relaxation
*  of the current subproblem. */

void gen_subt(glp_tree *T)
{     int i, j, ne, nz, *beg, *end, *cap, *cut, *ind;
      double sum, *val;
      /* MIP preprocessor should not be used */
      xassert(glp_ios_get_prob(T) == P);
      /* if some variable x[i,j] is zero in basic solution, then the
       * capacity of corresponding edge in the associated network is
       * zero, so we may not include such edge in the network */
      /* count number of edges having non-zero capacity */
      ne = 0;
      for (i = 1; i <= n; i++)
      {  for (j = i+1; j <= n; j++)
         {  if (glp_get_col_prim(P, loc(i,j)) >= .001)
               ne++;
         }
      }
      /* build the capacitated network */
      beg = xalloc(1+ne, sizeof(int));
      end = xalloc(1+ne, sizeof(int));
      cap = xalloc(1+ne, sizeof(int));
      nz = 0;
      for (i = 1; i <= n; i++)
      {  for (j = i+1; j <= n; j++)
         {  if (glp_get_col_prim(P, loc(i,j)) >= .001)
            {  nz++;
               xassert(nz <= ne);
               beg[nz] = i, end[nz] = j;
               /* scale all edge capacities to make them integral */
               cap[nz] = ceil(1000 * glp_get_col_prim(P, loc(i,j)));
            }
         }
      }
      xassert(nz == ne);
      /* find minimal cut in the capacitated network */
      cut = xalloc(1+n, sizeof(int));
      min_cut(n, ne, beg, end, cap, cut);
      /* determine the number of non-zero coefficients in the subtour
       * elimination constraint and calculate its left-hand side which
       * is the (unscaled) capacity of corresponding min cut */
      ne = 0, sum = 0;
      for (i = 1; i <= n; i++)
      {  for (j = i+1; j <= n; j++)
         {  if (cut[i] && !cut[j] || !cut[i] && cut[j])
            {  ne++;
               sum += glp_get_col_prim(P, loc(i,j));
            }
         }
      }
      /* if the (unscaled) capacity of min cut is less than 2, the
       * corresponding subtour elimination constraint is violated */
      if (sum <= 1.999)
      {  /* build the list of non-zero coefficients */
         ind = xalloc(1+ne, sizeof(int));
         val = xalloc(1+ne, sizeof(double));
         nz = 0;
         for (i = 1; i <= n; i++)
         {  for (j = i+1; j <= n; j++)
            {  if (cut[i] && !cut[j] || !cut[i] && cut[j])
               {  nz++;
                  xassert(nz <= ne);
                  ind[nz] = loc(i,j);
                  val[nz] = 1;
               }
            }
         }
         xassert(nz == ne);
         /* add violated tour elimination constraint to the current
          * subproblem */
         i = glp_add_rows(P, 1);
         glp_set_row_bnds(P, i, GLP_LO, 2, 0);
         glp_set_mat_row(P, i, nz, ind, val);
         xfree(ind);
         xfree(val);
      }
      /* free working arrays */
      xfree(beg);
      xfree(end);
      xfree(cap);
      xfree(cut);
      return;
}

/***********************************************************************
*  cb_func - application callback routine
*
*  This routine is called from the MIP solver at various points of
*  the branch-and-cut algorithm. */

void cb_func(glp_tree *T, void *info)
{     xassert(info == info);
      switch (glp_ios_reason(T))
      {  case GLP_IROWGEN:
            /* generate one violated subtour elimination constraint */
            gen_subt(T);
            break;
      }
      return;
}

/***********************************************************************
*  main - TSP solver main program
*
*  This main program parses command-line arguments, reads specified TSP
*  instance from a text file, and calls the MIP solver to solve it. */

int main(int argc, char *argv[])
{     int j;
      char *in_file = NULL, *out_file = NULL;
      time_t start;
      glp_iocp iocp;
      /* parse command-line arguments */
#     define p(str) (strcmp(argv[j], str) == 0)
      for (j = 1; j < argc; j++)
      {  if (p("--output") || p("-o"))
         {  j++;
            if (j == argc || argv[j][0] == '\0' || argv[j][0] == '-')
            {  xprintf("No solution output file specified\n");
               exit(EXIT_FAILURE);
            }
            if (out_file != NULL)
            {  xprintf("Only one solution output file allowed\n");
               exit(EXIT_FAILURE);
            }
            out_file = argv[j];
         }
         else if (p("--help") || p("-h"))
         {  xprintf("Usage: %s [options...] tsp-file\n", argv[0]);
            xprintf("\n");
            xprintf("Options:\n");
            xprintf("   -o filename, --output filename\n");
            xprintf("                     write solution to filename\n")
               ;
            xprintf("   -h, --help        display this help information"
               " and exit\n");
            exit(EXIT_SUCCESS);
         }
         else if (argv[j][0] == '-' ||
                 (argv[j][0] == '-' && argv[j][1] == '-'))
         {  xprintf("Invalid option '%s'; try %s --help\n", argv[j],
               argv[0]);
            exit(EXIT_FAILURE);
         }
         else
         {  if (in_file != NULL)
            {  xprintf("Only one input file allowed\n");
               exit(EXIT_FAILURE);
            }
            in_file = argv[j];
         }
      }
      if (in_file == NULL)
      {  xprintf("No input file specified; try %s --help\n", argv[0]);
         exit(EXIT_FAILURE);
      }
#     undef p
      /* display program banner */
      xprintf("TSP Solver for GLPK %s\n", glp_version());
      /* remove output solution file specified in command-line */
      if (out_file != NULL)
         remove(out_file);
      /* read TSP instance from input data file */
      read_data(in_file);
      /* build initial IP problem */
      start = time(NULL);
      build_prob();
      tour = xalloc(1+n, sizeof(int));
      /* solve LP relaxation of initial IP problem */
      xprintf("Solving initial LP relaxation...\n");
      xassert(glp_simplex(P, NULL) == 0);
      xassert(glp_get_status(P) == GLP_OPT);
      /* solve IP problem with "lazy" constraints */
      glp_init_iocp(&iocp);
      iocp.br_tech = GLP_BR_MFV; /* most fractional variable */
      iocp.bt_tech = GLP_BT_BLB; /* best local bound */
      iocp.sr_heur = GLP_OFF; /* disable simple rounding heuristic */
      iocp.gmi_cuts = GLP_ON; /* enable Gomory cuts */
      iocp.cb_func = cb_func;
      glp_intopt(P, &iocp);
      build_tour();
      /* display some statistics */
      xprintf("Time used:   %.1f secs\n", difftime(time(NULL), start));
      {  size_t tpeak;
         glp_mem_usage(NULL, NULL, NULL, &tpeak);
         xprintf("Memory used: %.1f Mb (%.0f bytes)\n",
            (double)tpeak / 1048576.0, (double)tpeak);
      }
      /* write solution to output file, if required */
      if (out_file != NULL)
         write_tour(out_file, tour);
      /* deallocate working objects */
      xfree(c);
      xfree(tour);
      glp_delete_prob(P);
      /* check that no memory blocks are still allocated */
      {  int count;
         size_t total;
         glp_mem_usage(&count, NULL, &total, NULL);
         if (count != 0)
            xerror("Error: %d memory block(s) were lost\n", count);
         xassert(total == 0);
      }
      return 0;
}

/* eof */

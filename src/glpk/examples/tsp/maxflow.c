/* maxflow.c */

/* Written by Andrew Makhorin <mao@gnu.org>, October 2015. */

#include <math.h>

#include <glpk.h>
#include "maxflow.h"
#include "misc.h"

/***********************************************************************
*  NAME
*
*  max_flow - find max flow in undirected capacitated network
*
*  SYNOPSIS
*
*  #include "maxflow.h"
*  int max_flow(int nn, int ne, const int beg[], const int end[],
*     const int cap[], int s, int t, int x[]);
*
*  DESCRIPTION
*
*  This routine finds max flow in a given undirected network.
*
*  The undirected capacitated network is specified by the parameters
*  nn, ne, beg, end, and cap. The parameter nn specifies the number of
*  vertices (nodes), nn >= 2, and the parameter ne specifies the number
*  of edges, ne >= 0. The network edges are specified by triplets
*  (beg[k], end[k], cap[k]) for k = 1, ..., ne, where beg[k] < end[k]
*  are numbers of the first and second nodes of k-th edge, and
*  cap[k] > 0 is a capacity of k-th edge. Loops and multiple edges are
*  not allowed.
*
*  The parameter s is the number of a source node, and the parameter t
*  is the number of a sink node, s != t.
*
*  On exit the routine computes elementary flows thru edges and stores
*  their values to locations x[1], ..., x[ne]. Positive value of x[k]
*  means that the elementary flow goes from node beg[k] to node end[k],
*  and negative value means that the flow goes in opposite direction.
*
*  RETURNS
*
*  The routine returns the total maximum flow through the network. */

int max_flow(int nn, int ne, const int beg[/*1+ne*/],
      const int end[/*1+ne*/], const int cap[/*1+ne*/], int s, int t,
      int x[/*1+ne*/])
{     int k;
      /* sanity checks */
      xassert(nn >= 2);
      xassert(ne >= 0);
      xassert(1 <= s && s <= nn);
      xassert(1 <= t && t <= nn);
      xassert(s != t);
      for (k = 1; k <= ne; k++)
      {  xassert(1 <= beg[k] && beg[k] < end[k] && end[k] <= nn);
         xassert(cap[k] > 0);
      }
      /* find max flow */
      return max_flow_lp(nn, ne, beg, end, cap, s, t, x);
}

/***********************************************************************
*  NAME
*
*  max_flow_lp - find max flow with simplex method
*
*  SYNOPSIS
*
*  #include "maxflow.h"
*  int max_flow_lp(int nn, int ne, const int beg[], const int end[],
*     const int cap[], int s, int t, int x[]);
*
*  DESCRIPTION
*
*  This routine finds max flow in a given undirected network with the
*  simplex method.
*
*  Parameters of this routine have the same meaning as for the routine
*  max_flow (see above).
*
*  RETURNS
*
*  The routine returns the total maximum flow through the network. */

int max_flow_lp(int nn, int ne, const int beg[/*1+ne*/],
      const int end[/*1+ne*/], const int cap[/*1+ne*/], int s, int t,
      int x[/*1+ne*/])
{     glp_prob *lp;
      glp_smcp smcp;
      int i, k, nz, flow, *rn, *cn;
      double temp, *aa;
      /* create LP problem instance */
      lp = glp_create_prob();
      /* create LP rows; i-th row is the conservation condition of the
       * flow at i-th node, i = 1, ..., nn */
      glp_add_rows(lp, nn);
      for (i = 1; i <= nn; i++)
         glp_set_row_bnds(lp, i, GLP_FX, 0.0, 0.0);
      /* create LP columns; k-th column is the elementary flow thru
       * k-th edge, k = 1, ..., ne; the last column with the number
       * ne+1 is the total flow through the network, which goes along
       * a dummy feedback edge from the sink to the source */
      glp_add_cols(lp, ne+1);
      for (k = 1; k <= ne; k++)
      {  xassert(cap[k] > 0);
         glp_set_col_bnds(lp, k, GLP_DB, -cap[k], +cap[k]);
      }
      glp_set_col_bnds(lp, ne+1, GLP_FR, 0.0, 0.0);
      /* build the constraint matrix; structurally this matrix is the
       * incidence matrix of the network, so each its column (including
       * the last column for the dummy edge) has exactly two non-zero
       * entries */
      rn = xalloc(1+2*(ne+1), sizeof(int));
      cn = xalloc(1+2*(ne+1), sizeof(int));
      aa = xalloc(1+2*(ne+1), sizeof(double));
      nz = 0;
      for (k = 1; k <= ne; k++)
      {  /* x[k] > 0 means the elementary flow thru k-th edge goes from
          * node beg[k] to node end[k] */
         nz++, rn[nz] = beg[k], cn[nz] = k, aa[nz] = -1.0;
         nz++, rn[nz] = end[k], cn[nz] = k, aa[nz] = +1.0;
      }
      /* total flow thru the network goes from the sink to the source
       * along the dummy feedback edge */
      nz++, rn[nz] = t, cn[nz] = ne+1, aa[nz] = -1.0;
      nz++, rn[nz] = s, cn[nz] = ne+1, aa[nz] = +1.0;
      /* check the number of non-zero entries */
      xassert(nz == 2*(ne+1));
      /* load the constraint matrix into the LP problem object */
      glp_load_matrix(lp, nz, rn, cn, aa);
      xfree(rn);
      xfree(cn);
      xfree(aa);
      /* objective function is the total flow through the network to
       * be maximized */
      glp_set_obj_dir(lp, GLP_MAX);
      glp_set_obj_coef(lp, ne + 1, 1.0);
      /* solve LP instance with the (primal) simplex method */
      glp_term_out(0);
      glp_adv_basis(lp, 0);
      glp_term_out(1);
      glp_init_smcp(&smcp);
      smcp.msg_lev = GLP_MSG_ON;
      smcp.out_dly = 5000;
      xassert(glp_simplex(lp, &smcp) == 0);
      xassert(glp_get_status(lp) == GLP_OPT);
      /* obtain optimal elementary flows thru edges of the network */
      /* (note that the constraint matrix is unimodular and the data
       * are integral, so all elementary flows in basic solution should
       * also be integral) */
      for (k = 1; k <= ne; k++)
      {  temp = glp_get_col_prim(lp, k);
         x[k] = (int)floor(temp + .5);
         xassert(fabs(x[k] - temp) <= 1e-6);
      }
      /* obtain the maximum flow thru the original network which is the
       * flow thru the dummy feedback edge */
      temp = glp_get_col_prim(lp, ne+1);
      flow = (int)floor(temp + .5);
      xassert(fabs(flow - temp) <= 1e-6);
      /* delete LP problem instance */
      glp_delete_prob(lp);
      /* return to the calling program */
      return flow;
}

/* eof */

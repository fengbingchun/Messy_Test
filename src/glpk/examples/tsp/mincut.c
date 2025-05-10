/* mincut.c */

/* Written by Andrew Makhorin <mao@gnu.org>, October 2015. */

#include <limits.h>

#include "maxflow.h"
#include "mincut.h"
#include "misc.h"

/***********************************************************************
*  NAME
*
*  min_cut - find min cut in undirected capacitated network
*
*  SYNOPSIS
*
*  #include "mincut.h"
*  int min_cut(int nn, int ne, const int beg[], const int end[],
*     const cap[], int cut[]);
*
*  DESCRIPTION
*
*  This routine finds min cut in a given undirected network.
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
*  Let V be the set of nodes of the network and let W be an arbitrary
*  non-empty proper subset of V. A cut associated with the subset W is
*  a subset of all the edges, one node of which belongs to W and other
*  node belongs to V \ W. The capacity of a cut (W, V \ W) is the sum
*  of the capacities of all the edges, which belong to the cut. Minimal
*  cut is a cut, whose capacity is minimal.
*
*  On exit the routine stores flags of nodes v[i], i = 1, ..., nn, to
*  locations cut[i], where cut[i] = 1 means that v[i] belongs to W and
*  cut[i] = 0 means that v[i] belongs to V \ W, where W corresponds to
*  the minimal cut found.
*
*  RETURNS
*
*  The routine returns the capacity of the min cut found. */

int min_cut(int nn, int ne, const int beg[/*1+ne*/],
      const int end[/*1+ne*/], const cap[/*1+ne*/], int cut[/*1+nn*/])
{     int k;
      /* sanity checks */
      xassert(nn >= 2);
      xassert(ne >= 0);
      for (k = 1; k <= ne; k++)
      {  xassert(1 <= beg[k] && beg[k] < end[k] && end[k] <= nn);
         xassert(cap[k] > 0);
      }
      /* find min cut */
      return min_cut_sw(nn, ne, beg, end, cap, cut);
}

/***********************************************************************
*  NAME
*
*  min_st_cut - find min (s,t)-cut for known max flow
*
*  SYNOPSIS
*
*  #include "mincut.h"
*
*  DESCRIPTION
*
*  This routine finds min (s,t)-cut in a given undirected network that
*  corresponds to a known max flow from s to t in the network.
*
*  Parameters nn, ne, beg, end, and cap specify the network in the same
*  way as for the routine min_cut (see above).
*
*  Parameters s and t specify, resp., the number of the source node
*  and the number of the sink node, s != t, for which the min (s,t)-cut
*  has to be found.
*
*  Parameter x specifies the known max flow from s to t in the network,
*  where locations x[1], ..., x[ne] contains elementary flow thru edges
*  of the network (positive value of x[k] means that the elementary
*  flow goes from node beg[k] to node end[k], and negative value means
*  that the flow goes in opposite direction).
*
*  This routine splits the set of nodes V of the network into two
*  non-empty subsets V(s) and V(t) = V \ V(s), where the source node s
*  belongs to V(s), the sink node t belongs to V(t), and all edges, one
*  node of which belongs to V(s) and other one belongs to V(t), are
*  saturated (that is, x[k] = +cap[k] or x[k] = -cap[k]).
*
*  On exit the routine stores flags of the nodes v[i], i = 1, ..., nn,
*  to locations cut[i], where cut[i] = 1 means that v[i] belongs to V(s)
*  and cut[i] = 0 means that v[i] belongs to V(t) = V \ V(s).
*
*  RETURNS
*
*  The routine returns the capacity of min (s,t)-cut, which is the sum
*  of the capacities of all the edges, which belong to the cut. (Note
*  that due to theorem by Ford and Fulkerson this value is always equal
*  to corresponding max flow.)
*
*  ALGORITHM
*
*  To determine the set V(s) the routine simply finds all nodes, which
*  can be reached from the source node s via non-saturated edges. The
*  set V(t) is determined as the complement V \ V(s). */

int min_st_cut(int nn, int ne, const int beg[/*1+ne*/],
      const int end[/*1+ne*/], const int cap[/*1+ne*/], int s, int t,
      const int x[/*1+ne*/], int cut[/*1+nn*/])
{     int i, j, k, p, q, temp, *head1, *next1, *head2, *next2, *list;
      /* head1[i] points to the first edge with beg[k] = i
       * next1[k] points to the next edge with the same beg[k]
       * head2[i] points to the first edge with end[k] = i
       * next2[k] points to the next edge with the same end[k] */
      head1 = xalloc(1+nn, sizeof(int));
      head2 = xalloc(1+nn, sizeof(int));
      next1 = xalloc(1+ne, sizeof(int));
      next2 = xalloc(1+ne, sizeof(int));
      for (i = 1; i <= nn; i++)
         head1[i] = head2[i] = 0;
      for (k = 1; k <= ne; k++)
      {  i = beg[k], next1[k] = head1[i], head1[i] = k;
         j = end[k], next2[k] = head2[j], head2[j] = k;
      }
      /* on constructing the set V(s) list[1], ..., list[p-1] contain
       * nodes, which can be reached from source node and have been
       * visited, and list[p], ..., list[q] contain nodes, which can be
       * reached from source node but havn't been visited yet */
      list = xalloc(1+nn, sizeof(int));
      for (i = 1; i <= nn; i++)
         cut[i] = 0;
      p = q = 1, list[1] = s, cut[s] = 1;
      while (p <= q)
      {  /* pick next node, which is reachable from the source node and
          * has not visited yet, and visit it */
         i = list[p++];
         /* walk through edges with beg[k] = i */
         for (k = head1[i]; k != 0; k = next1[k])
         {  j = end[k];
            xassert(beg[k] == i);
            /* from v[i] we can reach v[j], if the elementary flow from
             * v[i] to v[j] is non-saturated */
            if (cut[j] == 0 && x[k] < +cap[k])
               list[++q] = j, cut[j] = 1;
         }
         /* walk through edges with end[k] = i */
         for (k = head2[i]; k != 0; k = next2[k])
         {  j = beg[k];
            xassert(end[k] == i);
            /* from v[i] we can reach v[j], if the elementary flow from
             * v[i] to v[j] is non-saturated */
            if (cut[j] == 0 && x[k] > -cap[k])
               list[++q] = j, cut[j] = 1;
         }
      }
      /* sink cannot belong to V(s) */
      xassert(!cut[t]);
      /* free working arrays */
      xfree(head1);
      xfree(head2);
      xfree(next1);
      xfree(next2);
      xfree(list);
      /* compute capacity of the minimal (s,t)-cut found */
      temp = 0;
      for (k = 1; k <= ne; k++)
      {  i = beg[k], j = end[k];
         if (cut[i] && !cut[j] || !cut[i] && cut[j])
            temp += cap[k];
      }
      /* return to the calling program */
      return temp;
}

/***********************************************************************
*  NAME
*
*  min_cut_sw - find min cut with Stoer and Wagner algorithm
*
*  SYNOPSIS
*
*  #include "mincut.h"
*  int min_cut_sw(int nn, int ne, const int beg[], const int end[],
*     const cap[], int cut[]);
*
*  DESCRIPTION
*
*  This routine find min cut in a given undirected network with the
*  algorithm proposed by Stoer and Wagner (see references below).
*
*  Parameters of this routine have the same meaning as for the routine
*  min_cut (see above).
*
*  RETURNS
*
*  The routine returns the capacity of the min cut found.
*
*  ALGORITHM
*
*  The basic idea of Stoer&Wagner algorithm is the following. Let G be
*  a capacitated network, and G(s,t) be a network, in which the nodes s
*  and t are merged into one new node, loops are deleted, but multiple
*  edges are retained. It is obvious that a minimum cut in G is the
*  minimum of two quantities: the minimum cut in G(s,t) and a minimum
*  cut that separates s and t. This allows to find a minimum cut in the
*  original network solving at most nn max flow problems.
*
*  REFERENCES
*
*  M. Stoer, F. Wagner. A Simple Min Cut Algorithm. Algorithms, ESA'94
*  LNCS 855 (1994), pp. 141-47.
*
*  J. Cheriyan, R. Ravi. Approximation Algorithms for Network Problems.
*  Univ. of Waterloo (1998), p. 147. */

int min_cut_sw(int nn, int ne, const int beg[/*1+ne*/],
      const int end[/*1+ne*/], const cap[/*1+ne*/], int cut[/*1+nn*/])
{     int i, j, k, min_cut, flow, temp, *head1, *next1, *head2, *next2;
      int I, J, K, S, T, DEG, NV, NE, *HEAD, *NEXT, *NUMB, *BEG, *END,
         *CAP, *X, *ADJ, *SUM, *CUT;
      /* head1[i] points to the first edge with beg[k] = i
       * next1[k] points to the next edge with the same beg[k]
       * head2[i] points to the first edge with end[k] = i
       * next2[k] points to the next edge with the same end[k] */
      head1 = xalloc(1+nn, sizeof(int));
      head2 = xalloc(1+nn, sizeof(int));
      next1 = xalloc(1+ne, sizeof(int));
      next2 = xalloc(1+ne, sizeof(int));
      for (i = 1; i <= nn; i++)
         head1[i] = head2[i] = 0;
      for (k = 1; k <= ne; k++)
      {  i = beg[k], next1[k] = head1[i], head1[i] = k;
         j = end[k], next2[k] = head2[j], head2[j] = k;
      }
      /* an auxiliary network used in the algorithm is resulted from
       * the original network by merging some nodes into one supernode;
       * all variables and arrays related to this auxiliary network are
       * denoted in CAPS */
      /* HEAD[I] points to the first node of the original network that
       * belongs to the I-th supernode
       * NEXT[i] points to the next node of the original network that
       * belongs to the same supernode as the i-th node
       * NUMB[i] is a supernode, which the i-th node belongs to */
      /* initially the auxiliary network is equivalent to the original
       * network, i.e. each supernode consists of one node */
      NV = nn;
      HEAD = xalloc(1+nn, sizeof(int));
      NEXT = xalloc(1+nn, sizeof(int));
      NUMB = xalloc(1+nn, sizeof(int));
      for (i = 1; i <= nn; i++)
         HEAD[i] = i, NEXT[i] = 0, NUMB[i] = i;
      /* number of edges in the auxiliary network is never greater than
       * in the original one */
      BEG = xalloc(1+ne, sizeof(int));
      END = xalloc(1+ne, sizeof(int));
      CAP = xalloc(1+ne, sizeof(int));
      X = xalloc(1+ne, sizeof(int));
      /* allocate some auxiliary arrays */
      ADJ = xalloc(1+nn, sizeof(int));
      SUM = xalloc(1+nn, sizeof(int));
      CUT = xalloc(1+nn, sizeof(int));
      /* currently no min cut is found so far */
      min_cut = INT_MAX;
      /* main loop starts here */
      while (NV > 1)
      {  /* build the set of edges of the auxiliary network */
         NE = 0;
         /* multiple edges are not allowed in the max flow algorithm,
          * so we can replace each multiple edge, which is the result
          * of merging nodes into supernodes, by a single edge, whose
          * capacity is the sum of capacities of particular edges;
          * these summary capacities will be stored in the array SUM */
         for (I = 1; I <= NV; I++)
            SUM[I] = 0.0;
         for (I = 1; I <= NV; I++)
         {  /* DEG is number of single edges, which connects I-th
             * supernode and some J-th supernode, where I < J */
            DEG = 0;
            /* walk thru nodes that belong to I-th supernode */
            for (i = HEAD[I]; i != 0; i = NEXT[i])
            {  /* i-th node belongs to I-th supernode */
               /* walk through edges with beg[k] = i */
               for (k = head1[i]; k != 0; k = next1[k])
               {  j = end[k];
                  /* j-th node belongs to J-th supernode */
                  J = NUMB[j];
                  /* ignore loops and edges with I > J */
                  if (I >= J)
                     continue;
                  /* add an edge that connects I-th and J-th supernodes
                   * (if not added yet) */
                  if (SUM[J] == 0.0)
                     ADJ[++DEG] = J;
                  /* sum up the capacity of the original edge */
                  xassert(cap[k] > 0.0);
                  SUM[J] += cap[k];
               }
               /* walk through edges with end[k] = i */
               for (k = head2[i]; k != 0; k = next2[k])
               {  j = beg[k];
                  /* j-th node belongs to J-th supernode */
                  J = NUMB[j];
                  /* ignore loops and edges with I > J */
                  if (I >= J)
                     continue;
                  /* add an edge that connects I-th and J-th supernodes
                   * (if not added yet) */
                  if (SUM[J] == 0.0)
                     ADJ[++DEG] = J;
                  /* sum up the capacity of the original edge */
                  xassert(cap[k] > 0.0);
                  SUM[J] += cap[k];
               }
            }
            /* add single edges connecting I-th supernode with other
             * supernodes to the auxiliary network; restore the array
             * SUM for subsequent use */
            for (K = 1; K <= DEG; K++)
            {  NE++;
               xassert(NE <= ne);
               J = ADJ[K];
               BEG[NE] = I, END[NE] = J, CAP[NE] = SUM[J];
               SUM[J] = 0.0;
            }
         }
         /* choose two arbitrary supernodes of the auxiliary network,
          * one of which is the source and other is the sink */
         S = 1, T = NV;
         /* determine max flow from S to T */
         flow = max_flow(NV, NE, BEG, END, CAP, S, T, X);
         /* if the min cut that separates supernodes S and T is less
          * than the currently known, remember it */
         if (min_cut > flow)
         {  min_cut = flow;
            /* find min (s,t)-cut in the auxiliary network */
            temp = min_st_cut(NV, NE, BEG, END, CAP, S, T, X, CUT);
            /* (Ford and Fulkerson insist on this) */
            xassert(flow == temp);
            /* build corresponding min cut in the original network */
            for (i = 1; i <= nn; i++) cut[i] = CUT[NUMB[i]];
            /* if the min cut capacity is zero (i.e. the network has
             * unconnected components), the search can be prematurely
             * terminated */
            if (min_cut == 0)
               break;
         }
         /* now merge all nodes of the original network, which belong
          * to the supernodes S and T, into one new supernode; this is
          * attained by carrying all nodes from T to S (for the sake of
          * convenience T should be the last supernode) */
         xassert(T == NV);
         /* assign new references to nodes from T */
         for (i = HEAD[T]; i != 0; i = NEXT[i])
            NUMB[i] = S;
         /* find last entry in the node list of S */
         i = HEAD[S];
         xassert(i != 0);
         while (NEXT[i] != 0)
            i = NEXT[i];
         /* and attach to it the node list of T */
         NEXT[i] = HEAD[T];
         /* decrease number of nodes in the auxiliary network */
         NV--;
      }
      /* free working arrays */
      xfree(HEAD);
      xfree(NEXT);
      xfree(NUMB);
      xfree(BEG);
      xfree(END);
      xfree(CAP);
      xfree(X);
      xfree(ADJ);
      xfree(SUM);
      xfree(CUT);
      xfree(head1);
      xfree(head2);
      xfree(next1);
      xfree(next2);
      /* return to the calling program */
      return min_cut;
}

/* eof */

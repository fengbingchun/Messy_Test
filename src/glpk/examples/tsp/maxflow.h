/* maxflow.h */

/* Written by Andrew Makhorin <mao@gnu.org>, October 2015. */

#ifndef MAXFLOW_H
#define MAXFLOW_H

int max_flow(int nn, int ne, const int beg[/*1+ne*/],
      const int end[/*1+ne*/], const int cap[/*1+ne*/], int s, int t,
      int x[/*1+ne*/]);
/* find max flow in undirected capacitated network */

int max_flow_lp(int nn, int ne, const int beg[/*1+ne*/],
      const int end[/*1+ne*/], const int cap[/*1+ne*/], int s, int t,
      int x[/*1+ne*/]);
/* find max flow with simplex method */

#endif

/* eof */

/* mincut.c */

/* Written by Andrew Makhorin <mao@gnu.org>, October 2015. */

#ifndef MINCUT_H
#define MINCUT_H

int min_cut(int nn, int ne, const int beg[/*1+ne*/],
      const int end[/*1+ne*/], const cap[/*1+ne*/], int cut[/*1+nn*/]);
/* find min cut in undirected capacitated network */

int min_st_cut(int nn, int ne, const int beg[/*1+ne*/],
      const int end[/*1+ne*/], const int cap[/*1+ne*/], int s, int t,
      const int x[/*1+ne*/], int cut[/*1+nn*/]);
/* find min (s,t)-cut for known max flow */

int min_cut_sw(int nn, int ne, const int beg[/*1+ne*/],
      const int end[/*1+ne*/], const cap[/*1+ne*/], int cut[/*1+nn*/]);
/* find min cut with Stoer and Wagner algorithm */

#endif

/* eof */

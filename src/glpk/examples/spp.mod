/* SPP, Shortest Path Problem */

/* Written in GNU MathProg by Andrew Makhorin <mao@gnu.org> */

/* Given a directed graph G = (V,E), its edge lengths c(i,j) for all
   (i,j) in E, and two nodes s, t in V, the Shortest Path Problem (SPP)
   is to find a directed path from s to t whose length is minimal. */

param n, integer, > 0;
/* number of nodes */

set E, within {i in 1..n, j in 1..n};
/* set of edges */

param c{(i,j) in E};
/* c[i,j] is length of edge (i,j); note that edge lengths are allowed
   to be of any sign (positive, negative, or zero) */

param s, in {1..n};
/* source node */

param t, in {1..n};
/* target node */

var x{(i,j) in E}, >= 0;
/* x[i,j] = 1 means that edge (i,j) belong to shortest path;
   x[i,j] = 0 means that edge (i,j) does not belong to shortest path;
   note that variables x[i,j] are binary, however, there is no need to
   declare them so due to the totally unimodular constraint matrix */

s.t. r{i in 1..n}: sum{(j,i) in E} x[j,i] + (if i = s then 1) =
                   sum{(i,j) in E} x[i,j] + (if i = t then 1);
/* conservation conditions for unity flow from s to t; every feasible
   solution is a path from s to t */

minimize Z: sum{(i,j) in E} c[i,j] * x[i,j];
/* objective function is the path length to be minimized */

data;

/* Optimal solution is 20 that corresponds to the following shortest
   path: s = 1 -> 2 -> 4 -> 8 -> 6 = t */

param n := 8;

param s := 1;

param t := 6;

param : E :   c :=
       1 2    1
       1 4    8
       1 7    6
       2 4    2
       3 2   14
       3 4   10
       3 5    6
       3 6   19
       4 5    8
       4 8   13
       5 8   12
       6 5    7
       7 4    5
       8 6    4
       8 7   10;

end;

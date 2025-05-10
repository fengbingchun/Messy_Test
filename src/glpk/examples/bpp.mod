/* BPP, Bin Packing Problem */

/* Written in GNU MathProg by Andrew Makhorin <mao@gnu.org> */

/* Given a set of items I = {1,...,m} with weight w[i] > 0, the Bin
   Packing Problem (BPP) is to pack the items into bins of capacity c
   in such a way that the number of bins used is minimal. */

param m, integer, > 0;
/* number of items */

set I := 1..m;
/* set of items */

param w{i in 1..m}, > 0;
/* w[i] is weight of item i */

param c, > 0;
/* bin capacity */

/* We need to estimate an upper bound of the number of bins sufficient
   to contain all items. The number of items m can be used, however, it
   is not a good idea. To obtain a more suitable estimation an easy
   heuristic is used: we put items into a bin while it is possible, and
   if the bin is full, we use another bin. The number of bins used in
   this way gives us a more appropriate estimation. */

param z{i in I, j in 1..m} :=
/* z[i,j] = 1 if item i is in bin j, otherwise z[i,j] = 0 */

   if i = 1 and j = 1 then 1
   /* put item 1 into bin 1 */

   else if exists{jj in 1..j-1} z[i,jj] then 0
   /* if item i is already in some bin, do not put it into bin j */

   else if sum{ii in 1..i-1} w[ii] * z[ii,j] + w[i] > c then 0
   /* if item i does not fit into bin j, do not put it into bin j */

   else 1;
   /* otherwise put item i into bin j */

check{i in I}: sum{j in 1..m} z[i,j] = 1;
/* each item must be exactly in one bin */

check{j in 1..m}: sum{i in I} w[i] * z[i,j] <= c;
/* no bin must be overflowed */

param n := sum{j in 1..m} if exists{i in I} z[i,j] then 1;
/* determine the number of bins used by the heuristic; obviously it is
   an upper bound of the optimal solution */

display n;

set J := 1..n;
/* set of bins */

var x{i in I, j in J}, binary;
/* x[i,j] = 1 means item i is in bin j */

var used{j in J}, binary;
/* used[j] = 1 means bin j contains at least one item */

s.t. one{i in I}: sum{j in J} x[i,j] = 1;
/* each item must be exactly in one bin */

s.t. lim{j in J}: sum{i in I} w[i] * x[i,j] <= c * used[j];
/* if bin j is used, it must not be overflowed */

minimize obj: sum{j in J} used[j];
/* objective is to minimize the number of bins used */

data;

/* The optimal solution is 3 bins */

param m := 6;

param w := 1 50, 2 60, 3 30, 4 70, 5 50, 6 40;

param c := 100;

end;

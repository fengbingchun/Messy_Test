/* FCTP, Fixed-Charge Transportation Problem */

/* Written in GNU MathProg by Andrew Makhorin <mao@gnu.org> */

/* The Fixed-Charge Transportation Problem (FCTP) is obtained from
   classical transportation problem by imposing a fixed cost on each
   transportation link if there is a positive flow on that link. */

param m, integer, > 0;
/* number of sources */

param n, integer, > 0;
/* number of customers */

set I := 1..m;
/* set of sources */

set J := 1..n;
/* set of customers */

param supply{i in I}, >= 0;
/* supply at source i */

param demand{j in J}, >= 0;
/* demand at customer j */

param varcost{i in I, j in J}, >= 0;
/* variable cost (a cost per one unit shipped from i to j) */

param fixcost{i in I, j in J}, >= 0;
/* fixed cost (a cost for shipping any amount from i to j) */

var x{i in I, j in J}, >= 0;
/* amount shipped from source i to customer j */

s.t. f{i in I}: sum{j in J} x[i,j] = supply[i];
/* observe supply at source i */

s.t. g{j in J}: sum{i in I} x[i,j] = demand[j];
/* satisfy demand at customer j */

var y{i in I, j in J}, binary;
/* y[i,j] = 1 means some amount is shipped from i to j */

s.t. h{i in I, j in J}: x[i,j] <= min(supply[i], demand[j]) * y[i,j];
/* if y[i,j] is 0, force x[i,j] to be 0 (may note that supply[i] and
   demand[j] are implicit upper bounds for x[i,j] as follows from the
   constraints f[i] and g[j]) */

minimize cost: sum{i in I, j in J} varcost[i,j] * x[i,j] +
               sum{i in I, j in J} fixcost[i,j] * y[i,j];
/* total transportation costs */

data;

/* These data correspond to the instance bal8x12 from [Balinski]. */

/* The optimal solution is 471.55 */

param m := 8;

param n := 12;

param supply := 1 15.00,  2 20.00,  3 45.00,  4 35.00,
                5 25.00,  6 35.00,  7 10.00,  8 25.00;

param demand := 1 20.00,  2 15.00,  3 20.00,  4 15.00,
                5  5.00,  6 20.00,  7 30.00,  8 10.00,
                9 35.00, 10 25.00, 11 10.00, 12  5.00;

param varcost
      :   1    2    3    4    5    6    7    8    9    10   11   12  :=
      1  0.69 0.64 0.71 0.79 1.70 2.83 2.02 5.64 5.94 5.94 5.94 7.68
      2  1.01 0.75 0.88 0.59 1.50 2.63 2.26 5.64 5.85 5.62 5.85 4.94
      3  1.05 1.06 1.08 0.64 1.22 2.37 1.66 5.64 5.91 5.62 5.91 4.94
      4  1.94 1.50 1.56 1.22 1.98 1.98 1.36 6.99 6.99 6.99 6.99 3.68
      5  1.61 1.40 1.61 1.33 1.68 2.83 1.54 4.26 4.26 4.26 4.26 2.99
      6  5.29 5.94 6.08 5.29 5.96 6.77 5.08 0.31 0.21 0.17 0.31 1.53
      7  5.29 5.94 6.08 5.29 5.96 6.77 5.08 0.55 0.35 0.40 0.19 1.53
      8  5.29 6.08 6.08 5.29 5.96 6.45 5.08 2.43 2.30 2.33 1.81 2.50 ;

param fixcost
      :   1    2    3    4    5    6    7    8    9    10   11   12  :=
      1  11.0 16.0 18.0 17.0 10.0 20.0 17.0 13.0 15.0 12.0 14.0 14.0
      2  14.0 17.0 17.0 13.0 15.0 13.0 16.0 11.0 20.0 11.0 15.0 10.0
      3  12.0 13.0 20.0 17.0 13.0 15.0 16.0 13.0 12.0 13.0 10.0 18.0
      4  16.0 19.0 16.0 11.0 15.0 12.0 18.0 12.0 18.0 13.0 13.0 14.0
      5  19.0 18.0 15.0 16.0 12.0 14.0 20.0 19.0 11.0 17.0 16.0 18.0
      6  13.0 20.0 20.0 17.0 15.0 12.0 14.0 11.0 12.0 19.0 15.0 16.0
      7  11.0 12.0 15.0 10.0 17.0 11.0 11.0 16.0 10.0 18.0 17.0 12.0
      8  17.0 10.0 20.0 12.0 17.0 20.0 16.0 15.0 10.0 12.0 16.0 18.0 ;

end;

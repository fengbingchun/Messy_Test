/* min01ks.mod - finding minimal equivalent 0-1 knapsack inequality */

/* Written in GNU MathProg by Andrew Makhorin <mao@gnu.org> */

/* It is obvious that for a given 0-1 knapsack inequality

      a[1] x[1] + ... + a[n] x[n] <= b,  x[j] in {0, 1}              (1)

   there exist infinitely many equivalent inequalities with exactly the
   same feasible solutions.

   Given a[j]'s and b this model allows to find an inequality

      alfa[1] x[1] + ... + alfa[n] x[n] <= beta,  x[j] in {0, 1},    (2)

   which is equivalent to (1) and where alfa[j]'s and beta are smallest
   non-negative integers.

   This model has the following formulation:

      minimize

         z = |alfa[1]| + ... + |alfa[n]| + |beta| =                  (3)

           = alfa[1] + ... + alfa[n] + beta

      subject to

         alfa[1] x[1] + ... + alfa[n] x[n] <= beta                   (4)

                              for all x satisfying to (1)

         alfa[1] x[1] + ... + alfa[n] x[n] >= beta + 1               (5)

                              for all x not satisfying to (1)

         alfa[1], ..., alfa[n], beta are non-negative integers.

   Note that this model has n+1 variables and 2^n constraints.

   It is interesting, as noticed in [1] and explained in [2], that
   in most cases LP relaxation of the MIP formulation above has integer
   optimal solution.

   References

   1. G.H.Bradley, P.L.Hammer, L.Wolsey, "Coefficient Reduction for
      Inequalities in 0-1 Variables", Math.Prog.7 (1974), 263-282.

   2. G.J.Koehler, "A Study on Coefficient Reduction of Binary Knapsack
      Inequalities", University of Florida, 2001. */

param n, integer, > 0;
/* number of variables in the knapsack inequality */

set N := 1..n;
/* set of knapsack items */

/* all binary n-vectors are numbered by 0, 1, ..., 2^n-1, where vector
   0 is 00...00, vector 1 is 00...01, etc. */

set U := 0..2^n-1;
/* set of numbers of all binary n-vectors */

param x{i in U, j in N}, binary, := (i div 2^(j-1)) mod 2;
/* x[i,j] is j-th component of i-th binary n-vector */

param a{j in N}, >= 0;
/* original coefficients */

param b, >= 0;
/* original right-hand side */

set D := setof{i in U: sum{j in N} a[j] * x[i,j] <= b} i;
/* set of numbers of binary n-vectors, which (vectors) are feasible,
   i.e. satisfy to the original knapsack inequality (1) */

var alfa{j in N}, integer, >= 0;
/* coefficients to be found */

var beta, integer, >= 0;
/* right-hand side to be found */

minimize z: sum{j in N} alfa[j] + beta; /* (3) */

phi{i in D}: sum{j in N} alfa[j] * x[i,j] <= beta; /* (4) */

psi{i in U diff D}: sum{j in N} alfa[j] * x[i,j] >= beta + 1; /* (5) */

solve;

printf "\nOriginal 0-1 knapsack inequality:\n";
for {j in 1..n} printf (if j = 1 then "" else " + ") & "%g x%d",
   a[j], j;
printf " <= %g\n", b;
printf "\nMinimized equivalent inequality:\n";
for {j in 1..n} printf (if j = 1 then "" else " + ") & "%g x%d",
   alfa[j], j;
printf " <= %g\n\n", beta;

data;

/* These data correspond to the very first example from [1]. */

param n := 8;

param a := [1]65, [2]64, [3]41, [4]22, [5]13, [6]12, [7]8, [8]2;

param b := 80;

end;

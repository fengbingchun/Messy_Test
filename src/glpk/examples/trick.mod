/* TRICK, A Transportation Design Problem */

/* Translated from the Mosel modeling language to GNU MathProg by
   Andrew Makhorin <mao@gnu.org> */

/* This example model is described in the article "Formulations and
   Reformulations in Integer Programming" by Michael Trick (it is
   publicly available at http://mat.gsia.cmu.edu/trick/formul04.pdf).

   This model demonstrates an amazing effect when including in the
   formulation an additional constraint, which is redundant even for
   LP relaxation, makes the model easy for solving with the B&B. */

set TRUCKS := 1..10;

set PACKAGES := 1..20;

param capacity{TRUCKS};

param size{PACKAGES};

param cost{TRUCKS};

param can_use{PACKAGES, TRUCKS};

var x{PACKAGES, TRUCKS}, binary;

var y{TRUCKS}, binary;

minimize total: sum{i in TRUCKS} cost[i] * y[i];

f1{i in TRUCKS}:
      sum{j in PACKAGES} size[j] * x[j,i] <= capacity[i] * y[i];

f2{i in TRUCKS, j in PACKAGES}:
      x[j,i] <= y[i];

f3{j in PACKAGES}:
      sum{i in TRUCKS} can_use[j,i] * x[j,i] = 1;

redundant_constraint:
      sum{i in TRUCKS} capacity[i] * y[i] >= sum{j in PACKAGES} size[j];

data;

param capacity :=
      [1] 100 [2] 200 [3] 100 [4] 200 [5] 100 [6] 200 [7] 100 [8] 200
      [9] 100 [10] 200;

param size :=
      [1] 17 [2] 21 [3] 54 [4] 45 [5] 87 [6] 34 [7] 23 [8] 45 [9] 12
      [10] 43 [11] 54 [12] 39 [13] 31 [14] 26 [15] 75 [16] 48 [17] 16
      [18] 32 [19] 45 [20] 55;

param cost :=
      [1] 1 [2] 1.8 [3] 1 [4] 1.8 [5] 1 [6] 1.8 [7] 1 [8] 1.8 [9] 1
      [10] 1.8;

param can_use (tr):
      1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 17 18 19 20 :=
   1  1  1  1  1  1  1  0  0  0  0  1  1  1  1  0  0  0  0  0  0
   2  1  1  1  1  1  1  1  1  0  0  1  1  1  1  1  1  1  0  0  0
   3  0  1  1  1  1  0  0  0  0  0  0  1  1  1  1  1  1  0  0  0
   4  0  0  1  1  1  1  1  1  1  1  0  0  1  1  1  1  1  1  0  0
   5  0  0  1  1  1  1  0  0  0  0  0  0  0  1  1  1  1  1  1  0
   6  0  0  0  1  1  1  1  0  0  0  0  0  0  1  1  1  0  0  0  0
   7  0  0  0  0  1  1  1  1  1  0  0  0  0  0  1  1  1  1  0  0
   8  0  0  0  0  1  1  1  1  1  1  0  0  0  0  0  1  1  1  1  1
   9  0  0  0  0  0  1  1  1  1  0  0  0  0  0  0  0  1  1  1  1
  10  0  0  0  0  0  0  0  1  1  1  0  0  0  0  0  0  0  0  1  1;

end;

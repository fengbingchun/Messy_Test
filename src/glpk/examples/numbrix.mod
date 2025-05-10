/* Numbrix, Number Placement Puzzle */

/* Written in GNU MathProg by Robert Wood <rwood@targus.com>  */

/* Numbrix is a logic-based number-placement puzzle.[1]
 * The objective is to fill the grid so that each cell contains
 * digits in sequential order taking a horizontal or vertical
 * path; diagonal paths are not allowed. The puzzle setter
 * provides a grid often with the outer most cells completed.
 *
 * Completed Numbrix puzzles are usually a square of numbers
 * in order from 1 to 64 (8x8 grid) or from 1 to 81 (9x9 grid),
 * following a continuous path in sequence.
 *
 * The modern puzzle was invented by Marilyn vos Savant in 2008
 * and published by Parade Magazine under the name "Numbrix",
 * near her weekly Ask Marilyn article.
 *
 *    http://en.wikipedia.org/wiki/Numbrix  */

set I := {1..9};
set J := {1..9};
set VALS := {1..81};

param givens{I, J}, integer, >= 0, <= 81, default 0;
/* the "givens" */

param neighbors{i in I,j in J, i2 in I, j2 in J} , binary :=
(if abs(i - i2) + abs(j -j2) == 1 then
     1
 else
     0
);
/*  defines which spots are the boards are neighbors */

var x{i in I, j in J, k in VALS}, binary;
/* x[i,j,k] = 1 means cell [i,j] is assigned number k */

s.t. fa{i in I, j in J, k in VALS: givens[i,j] != 0}:
     x[i,j,k] = (if givens[i,j] = k then 1 else 0);
/* assign pre-defined numbers using the "givens" */

s.t. fb{i in I, j in J}: sum{k in VALS} x[i,j,k] = 1;
/* each cell must be assigned exactly one number */

s.t. singleNum {k in VALS}:  sum{i in I, j in J} x[i,j,k] = 1;
/*  a value can only occur once */

s.t. neighborContraint {i in I, j in J, k in 1..80}:
        x[i,j,k] <= sum{i2 in I, j2 in J} x[i2,j2,k+1] * neighbors[i,j,i2,j2];
/* each cell must have a neighbor with the next higher value */


/* there is no need for an objective function here */


solve;

for {i in I}
{  for {0..0: i = 1 or i = 4 or i = 7}
      printf " +----------+----------+----------+\n";
   for {j in J}
   {  for {0..0: j = 1 or j = 4 or j = 7} printf(" |");
      printf " %2d", sum{k in VALS} x[i,j,k] * k;
      for {0..0: j = 9} printf(" |\n");
   }
   for {0..0: i = 9}
      printf " +----------+----------+----------+\n";
}

data;

param givens : 1 2 3 4 5 6 7 8 9 :=
           1   . . . . . . . . .
           2   . 11 12 15 18 21 62 61 .
           3   .  6 . . . . . 60 .
           4   . 33 . . . . . 57 .
           5   . 32 . . . . . 56 .
           6   . 37 . . . . . 73 .
           7   . 38 . . . . . 72 .
           8   . 43 44 47 48 51 76 77 .
           9   . . . . . . . . . ;

end;

/* QUEENS, a classic combinatorial optimization problem */

/* Written in GNU MathProg by Andrew Makhorin <mao@gnu.org> */

/* The Queens Problem is to place as many queens as possible on the 8x8
   (or more generally, nxn) chess board in a way that they do not fight
   each other. This problem is probably as old as the chess game itself,
   and thus its origin is not known, but it is known that Gauss studied
   this problem. */

param n, integer, > 0, default 8;
/* size of the chess board */

var x{1..n, 1..n}, binary;
/* x[i,j] = 1 means that a queen is placed in square [i,j] */

s.t. a{i in 1..n}: sum{j in 1..n} x[i,j] <= 1;
/* at most one queen can be placed in each row */

s.t. b{j in 1..n}: sum{i in 1..n} x[i,j] <= 1;
/* at most one queen can be placed in each column */

s.t. c{k in 2-n..n-2}: sum{i in 1..n, j in 1..n: i-j == k} x[i,j] <= 1;
/* at most one queen can be placed in each "\"-diagonal */

s.t. d{k in 3..n+n-1}: sum{i in 1..n, j in 1..n: i+j == k} x[i,j] <= 1;
/* at most one queen can be placed in each "/"-diagonal */

maximize obj: sum{i in 1..n, j in 1..n} x[i,j];
/* objective is to place as many queens as possible */

/* solve the problem */
solve;

/* and print its optimal solution */
for {i in 1..n}
{  for {j in 1..n} printf " %s", if x[i,j] then "Q" else ".";
   printf("\n");
}

end;

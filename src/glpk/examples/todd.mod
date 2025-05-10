/* TODD, a class of hard instances of zero-one knapsack problems */

/* Written in GNU MathProg by Andrew Makhorin <mao@gnu.org> */

/* Chvatal describes a class of instances of zero-one knapsack problems
   due to Todd. He shows that a wide class of algorithms - including all
   based on branch and bound or dynamic programming - find it difficult
   to solve problems in the Todd class. More exactly, the time required
   by these algorithms to solve instances of problems that belong to the
   Todd class grows as an exponential function of the problem size.

   Reference:
   Chvatal V. (1980), Hard knapsack problems, Op. Res. 28, 1402-1411. */

param n > 0 integer;

param log2_n := log(n) / log(2);

param k := floor(log2_n);

param a{j in 1..n} := 2 ** (k + n + 1) + 2 ** (k + n + 1 - j) + 1;

param b := 0.5 * floor(sum{j in 1..n} a[j]);

var x{1..n} binary;

maximize obj: sum{j in 1..n} a[j] * x[j];

s.t. cap: sum{j in 1..n} a[j] * x[j] <= b;

data;

param n := 15;
/* change this parameter to choose a particular instance */

end;

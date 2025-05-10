/*

  Curve fitting problem 12.11(b) H P Williams "Model Building in Mathematical Programming"

  Dr. H J Mackenzie
  HARD software
  hjm@hardsoftware.com

  2006-01-23

 */

# set of points

set I;

# independent variable

param x {i in I};

# dependent variable

param y {i in I};

# output input values

printf {i in I} "x = %.1f; y = %.1f\n", x[i], y[i];

# define equation variables

var a;

var b;

var u {i in I}, >= 0;

var v {i in I}, >= 0;

var z;

# define objective function

minimize deviation: z;

# define equation constraint

s.t. equation {i in I} : b * x[i] + a + u[i] - v[i] = y[i];

# define deviation constrains

s.t. u_deviation {i in I} : z - u[i] >= 0;
s.t. v_deviation {i in I} : z - v[i] >= 0;

solve;

printf "y = %.4fx + %.4f Max deviation = %.4f\n", b, a, z;

/*
 *
 * DATA section
 *
 */

data;

param : I :   x    y :=
        1     0    1
        2   0.5  0.9
        3     1  0.7
        4   1.5  1.5
        5   1.9    2
        6   2.5  2.4
        7     3  3.2
        8   3.5    2
        9     4  2.7
       10   4.5  3.5
       11     5    1
       12   5.5    4
       13     6  3.6
       14   6.6  2.7
       15     7  5.7
       16   7.6  4.6
       17   8.5    6
       18     9  6.8
       19    10  7.3
;

end;

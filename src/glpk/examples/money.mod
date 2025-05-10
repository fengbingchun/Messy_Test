/* MONEY, a crypto-arithmetic puzzle */

/* Written in GNU MathProg by Andrew Makhorin <mao@gnu.org> */

/* This is the classic example of a crypto-arithmetic puzzle published
   in the Strand Magazine by Henry Dudeney:

        S E N D
      +
        M O R E
      ---------
      M O N E Y

   In this puzzle the same letters mean the same digits. The question
   is: how to replace all the letters with the respective digits that
   makes the calculation correct?

   The solution to this puzzle is:
   O = 0, M = 1, Y = 2, E = 5, N = 6, D = 7, R = 8, and S = 9.

   References:
   H. E. Dudeney, in Strand Magazine vol. 68 (July 1924), pp. 97, 214.

   (From Wikipedia, the free encyclopedia.) */

set LETTERS := { 'D', 'E', 'M', 'N', 'O', 'R', 'S', 'Y' };
/* set of letters */

set DIGITS := 0..9;
/* set of digits */

var x{i in LETTERS, d in DIGITS}, binary;
/* x[i,d] = 1 means that letter i is digit d */

s.t. one{i in LETTERS}: sum{d in DIGITS} x[i,d] = 1;
/* each letter must correspond exactly to one digit */

s.t. alldiff{d in DIGITS}: sum{i in LETTERS} x[i,d] <= 1;
/* different letters must correspond to different digits; note that
   some digits may not correspond to any letters at all */

var dig{i in LETTERS};
/* dig[i] is a digit corresponding to letter i */

s.t. map{i in LETTERS}: dig[i] = sum{d in DIGITS} d * x[i,d];

var carry{1..3}, binary;
/* carry bits */

s.t. sum1: dig['D'] + dig['E']            = dig['Y'] + 10 * carry[1];
s.t. sum2: dig['N'] + dig['R'] + carry[1] = dig['E'] + 10 * carry[2];
s.t. sum3: dig['E'] + dig['O'] + carry[2] = dig['N'] + 10 * carry[3];
s.t. sum4: dig['S'] + dig['M'] + carry[3] = dig['O'] + 10 * dig['M'];
s.t. note: dig['M'] >= 1; /* M must not be 0 */

solve;
/* solve the puzzle */

display dig;
/* and display its solution */

end;

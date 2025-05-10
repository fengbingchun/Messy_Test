/* CRYPTO, a crypto-arithmetic puzzle */

/* Written in GNU MathProg by Andrew Makhorin <mao@gnu.org> */

/* This problem comes from the newsgroup rec.puzzle.
   The numbers from 1 to 26 are assigned to the letters of the alphabet.
   The numbers beside each word are the total of the values assigned to
   the letters in the word (e.g. for LYRE: L, Y, R, E might be to equal
   5, 9, 20 and 13, or any other combination that add up to 47).
   Find the value of each letter under the equations:

   BALLET  45     GLEE  66     POLKA      59     SONG     61
   CELLO   43     JAZZ  58     QUARTET    50     SOPRANO  82
   CONCERT 74     LYRE  47     SAXOPHONE 134     THEME    72
   FLUTE   30     OBOE  53     SCALE      51     VIOLIN  100
   FUGUE   50     OPERA 65     SOLO       37     WALTZ    34

   Solution:
   A, B,C, D, E,F, G, H, I, J, K,L,M, N, O, P,Q, R, S,T,U, V,W, X, Y, Z
   5,13,9,16,20,4,24,21,25,17,23,2,8,12,10,19,7,11,15,3,1,26,6,22,14,18

   Reference:
   Koalog Constraint Solver <http://www.koalog.com/php/jcs.php>,
   Simple problems, the crypto-arithmetic puzzle ALPHACIPHER. */

set LETTERS :=
{     'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
      'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'
};
/* set of letters */

set VALUES := 1..card(LETTERS);
/* set of values assigned to the letters */

set WORDS;
/* set of words */

param total{word in WORDS};
/* total[word] is the total of the values assigned to the letters in
   the word */

var x{i in LETTERS, j in VALUES}, binary;
/* x[i,j] = 1 means that letter i is assigned value j */

s.t. phi{i in LETTERS}: sum{j in VALUES} x[i,j] = 1;

s.t. psi{j in VALUES}: sum{i in LETTERS} x[i,j] = 1;

s.t. eqn{word in WORDS}: sum{k in 1..length(word), j in VALUES}
      j * x[substr(word,k,1), j] = total[word];

solve;

printf{i in LETTERS} "  %s", i;
printf "\n";

printf{i in LETTERS} " %2d", sum{j in VALUES} j * x[i,j];
printf "\n";

data;

param :  WORDS :   total :=
         BALLET       45
         CELLO        43
         CONCERT      74
         FLUTE        30
         FUGUE        50
         GLEE         66
         JAZZ         58
         LYRE         47
         OBOE         53
         OPERA        65
         POLKA        59
         QUARTET      50
         SAXOPHONE   134
         SCALE        51
         SOLO         37
         SONG         61
         SOPRANO      82
         THEME        72
         VIOLIN      100
         WALTZ        34 ;

end;

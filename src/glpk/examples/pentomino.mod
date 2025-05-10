/* PENTOMINO, a geometric placement puzzle */

/* Written in GNU MathProg by Andrew Makhorin <mao@gnu.org> */

/* A pentomino is a plane geometric figure by joining five equal
   squares edge to edge. It is a polyomino with five cells. Pentominoes
   were defined by Prof. Solomon W. Golomb in his book "Polyominoes:
   Puzzles, Patterns, Problems, and Packings."

   There are twelve pentominoes, not counting rotations and reflections
   as distinct:

                    +---+
                    |   |
                    +---+    +---+            +---+
                    |   |    |   |            |   |
       +---+---+    +---+    +---+            +---+
       |   |   |    |   |    |   |            |   |
   +---+---+---+    +---+    +---+        +---+---+
   |   |   |        |   |    |   |        |   |   |
   +---+---+        +---+    +---+---+    +---+---+
       |   |        |   |    |   |   |    |   |
       +---+        +---+    +---+---+    +---+
         F            I          L            N

   +---+---+    +---+---+---+                     +---+
   |   |   |    |   |   |   |                     |   |
   +---+---+    +---+---+---+    +---+   +---+    +---+
   |   |   |        |   |        |   |   |   |    |   |
   +---+---+        +---+        +---+---+---+    +---+---+---+
   |   |            |   |        |   |   |   |    |   |   |   |
   +---+            +---+        +---+---+---+    +---+---+---+
       P              T                U                V

                                         +---+
                                         |   |
   +---+                +---+        +---+---+    +---+---+
   |   |                |   |        |   |   |    |   |   |
   +---+---+        +---+---+---+    +---+---+    +---+---+
   |   |   |        |   |   |   |        |   |        |   |
   +---+---+---+    +---+---+---+        +---+        +---+---+
       |   |   |        |   |            |   |        |   |   |
       +---+---+        +---+            +---+        +---+---+
         W                X              Y              Z


   A classic pentomino puzzle is to tile a given outline, i.e. cover
   it without overlap and without gaps. Each of 12 pentominoes has an
   area of 5 unit squares, so the outline must have area of 60 units.
   Note that it is allowed to rotate and reflect the pentominoes.

   (From Wikipedia, the free encyclopedia.) */

set A;
check card(A) = 12;
/* basic set of pentominoes */

set B{a in A};
/* B[a] is a set of distinct versions of pentomino a obtained by its
   rotations and reflections */

set C := setof{a in A, b in B[a]} b;
check card(C) = 63;
/* set of distinct versions of all pentominoes */

set D{c in C}, within {0..4} cross {0..4};
/* D[c] is a set of squares (i,j), relative to (0,0), that constitute
   a distinct version of pentomino c */

param m, default 6;
/* number of rows in the outline */

param n, default 10;
/* number of columns in the outline */

set R, default {1..m} cross {1..n};
/* set of squares (i,j), relative to (1,1), of the outline to be tiled
   with the pentominoes */

check card(R) = 60;
/* the outline must have exactly 60 squares */

set S := setof{c in C, i in 1..m, j in 1..n:
         forall{(ii,jj) in D[c]} ((i+ii,j+jj) in R)} (c,i,j);
/* set of all possible placements, where triplet (c,i,j) means that
   the base square (0,0) of a distinct version of pentomino c is placed
   at square (i,j) of the outline */

var x{(c,i,j) in S}, binary;
/* x[c,i,j] = 1 means that placement (c,i,j) is used in the tiling */

s.t. use{a in A}: sum{(c,i,j) in S: substr(c,1,1) = a} x[c,i,j] = 1;
/* every pentomino must be used exactly once */

s.t. cov{(i,j) in R}:
     sum{(c,ii,jj) in S: (i-ii, j-jj) in D[c]} x[c,ii,jj] = 1;
/* every square of the outline must be covered exactly once */

/* this is a feasibility problem, so no objective is needed */

solve;

for {i in 1..m}
{  for {j in 1..n}
   {  for {0..0: (i,j) in R}
      {  for {(c,ii,jj) in S: (i-ii,j-jj) in D[c] and x[c,ii,jj]}
            printf " %s", substr(c,1,1);
      }
      for {0..0: (i,j) not in R}
         printf " .";
   }
   printf "\n";
}

data;

/* These data correspond to a puzzle from the book "Pentominoes" by
   Jon Millington */

param m := 8;

param n := 15;

set R :  1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 :=
      1  - - - - - - - + - - - - - - -
      2  - - - - - - + + + - - - - - -
      3  - - - - - + + + + + - - - - -
      4  - - - - + + + - + + + - - - -
      5  - - - + + + + - + + + + - - -
      6  - - + + + + + - + + + + + - -
      7  - + + + + + + - + + + + + + -
      8  + + + + + + + + + + + + + + + ;

/* DO NOT CHANGE ANY DATA BELOW! */

set A := F, I, L, N, P, T, U, V, W, X, Y, Z;

set B[F] := F1, F2, F3, F4, F5, F6, F7, F8;
set B[I] := I1, I2;
set B[L] := L1, L2, L3, L4, L5, L6, L7, L8;
set B[N] := N1, N2, N3, N4, N5, N6, N7, N8;
set B[P] := P1, P2, P3, P4, P5, P6, P7, P8;
set B[T] := T1, T2, T3, T4;
set B[U] := U1, U2, U3, U4;
set B[V] := V1, V2, V3, V4;
set B[W] := W1, W2, W3, W4;
set B[X] := X;
set B[Y] := Y1, Y2, Y3, Y4, Y5, Y6, Y7, Y8;
set B[Z] := Z1, Z2, Z3, Z4;

set D[F1] :    0 1 2 :=
             0 - + +
             1 + + -
             2 - + - ;

set D[F2] :    0 1 2 :=
             0 - + -
             1 + + +
             2 - - + ;

set D[F3] :    0 1 2 :=
             0 - + -
             1 - + +
             2 + + - ;

set D[F4] :    0 1 2 :=
             0 + - -
             1 + + +
             2 - + - ;

set D[F5] :    0 1 2 :=
             0 + + -
             1 - + +
             2 - + - ;

set D[F6] :    0 1 2 :=
             0 - - +
             1 + + +
             2 - + - ;

set D[F7] :    0 1 2 :=
             0 - + -
             1 + + -
             2 - + + ;

set D[F8] :    0 1 2 :=
             0 - + -
             1 + + +
             2 + - - ;

set D[I1] :    0 :=
             0 +
             1 +
             2 +
             3 +
             4 + ;

set D[I2] :    0 1 2 3 4 :=
             0 + + + + + ;

set D[L1] :    0 1 :=
             0 + -
             1 + -
             2 + -
             3 + + ;

set D[L2] :    0 1 2 3 :=
             0 + + + +
             1 + - - - ;

set D[L3] :    0 1 :=
             0 + +
             1 - +
             2 - +
             3 - + ;

set D[L4] :    0 1 2 3 :=
             0 - - - +
             1 + + + + ;

set D[L5] :    0 1 :=
             0 - +
             1 - +
             2 - +
             3 + + ;

set D[L6] :    0 1 2 3 :=
             0 + - - -
             1 + + + + ;

set D[L7] :    0 1 :=
             0 + +
             1 + -
             2 + -
             3 + - ;

set D[L8] :    0 1 2 3 :=
             0 + + + +
             1 - - - + ;

set D[N1] :    0 1 :=
             0 + -
             1 + -
             2 + +
             3 - + ;

set D[N2] :    0 1 2 3 :=
             0 - + + +
             1 + + - - ;

set D[N3] :    0 1 :=
             0 + -
             1 + +
             2 - +
             3 - + ;

set D[N4] :    0 1 2 3 :=
             0 - - + +
             1 + + + - ;

set D[N5] :    0 1 :=
             0 - +
             1 - +
             2 + +
             3 + - ;

set D[N6] :    0 1 2 3 :=
             0 + + - -
             1 - + + + ;

set D[N7] :    0 1 :=
             0 - +
             1 + +
             2 + -
             3 + - ;

set D[N8] :    0 1 2 3 :=
             0 + + + -
             1 - - + + ;

set D[P1] :    0 1 :=
             0 + +
             1 + +
             2 + - ;

set D[P2] :    0 1 2 :=
             0 + + +
             1 - + + ;

set D[P3] :    0 1 :=
             0 - +
             1 + +
             2 + + ;

set D[P4] :    0 1 2 :=
             0 + + -
             1 + + + ;

set D[P5] :    0 1 :=
             0 + +
             1 + +
             2 - + ;

set D[P6] :    0 1 2 :=
             0 - + +
             1 + + + ;

set D[P7] :    0 1 :=
             0 + -
             1 + +
             2 + + ;

set D[P8] :    0 1 2 :=
             0 + + +
             1 + + - ;

set D[T1] :    0 1 2 :=
             0 + + +
             1 - + -
             2 - + - ;

set D[T2] :    0 1 2 :=
             0 - - +
             1 + + +
             2 - - + ;

set D[T3] :    0 1 2 :=
             0 - + -
             1 - + -
             2 + + + ;

set D[T4] :    0 1 2 :=
             0 + - -
             1 + + +
             2 + - - ;

set D[U1] :    0 1 2 :=
             0 + - +
             1 + + + ;

set D[U2] :    0 1 :=
             0 + +
             1 + -
             2 + + ;

set D[U3] :    0 1 2 :=
             0 + + +
             1 + - + ;

set D[U4] :    0 1 :=
             0 + +
             1 - +
             2 + + ;

set D[V1] :    0 1 2 :=
             0 - - +
             1 - - +
             2 + + + ;

set D[V2] :    0 1 2 :=
             0 + - -
             1 + - -
             2 + + + ;

set D[V3] :    0 1 2 :=
             0 + + +
             1 + - -
             2 + - - ;

set D[V4] :    0 1 2 :=
             0 + + +
             1 - - +
             2 - - + ;

set D[W1] :    0 1 2 :=
             0 - - +
             1 - + +
             2 + + - ;

set D[W2] :    0 1 2 :=
             0 + - -
             1 + + -
             2 - + + ;

set D[W3] :    0 1 2 :=
             0 - + +
             1 + + -
             2 + - - ;

set D[W4] :    0 1 2 :=
             0 + + -
             1 - + +
             2 - - + ;

set D[X] :     0 1 2 :=
             0 - + -
             1 + + +
             2 - + - ;

set D[Y1] :    0 1 :=
             0 + -
             1 + -
             2 + +
             3 + - ;

set D[Y2] :    0 1 2 3 :=
             0 + + + +
             1 - + - - ;

set D[Y3] :    0 1 :=
             0 - +
             1 + +
             2 - +
             3 - + ;

set D[Y4] :    0 1 2 3 :=
             0 - - + -
             1 + + + + ;

set D[Y5] :    0 1 :=
             0 - +
             1 - +
             2 + +
             3 - + ;

set D[Y6] :    0 1 2 3 :=
             0 - + - -
             1 + + + + ;

set D[Y7] :    0 1 :=
             0 + -
             1 + +
             2 + -
             3 + - ;

set D[Y8] :    0 1 2 3 :=
             0 + + + +
             1 - - + - ;

set D[Z1] :    0 1 2 :=
             0 - + +
             1 - + -
             2 + + - ;

set D[Z2] :    0 1 2 :=
             0 + - -
             1 + + +
             2 - - + ;

set D[Z3] :    0 1 2 :=
             0 + + -
             1 - + -
             2 - + + ;

set D[Z4] :    0 1 2 :=
             0 - - +
             1 + + +
             2 + - - ;

end;

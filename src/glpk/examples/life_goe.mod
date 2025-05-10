/* Conway's Game of Life garden of eden checker */

/* Written and converted to GNU MathProg by NASZVADI, Peter, 199x-2017
   <vuk@cs.elte.hu> */

/*
   Conway's Game of Life (ref'd: CGoL) is a Cellular Automata described and
   inspected by John H. Conway in the 1970s. CGoL is nothing but a 0-player
   game on an infinite two-dimensional Euclydean grid. In the beginning of
   the "game", some 1 values are put on some of the grid vertices, and all
   others are set to 0. Grid vertices with values are called cells, and a
   cell is called "alive", if its value is 1, and called "dead" otherwise,
   these are the two "states". The game then turns to an infinite repetitive
   process: all cells change together independently at the same time their
   states depending only on their actual state and the actual number of
   living cells in their so called Moore-neighbourhood: the 4 orthogonal and
   4 diagonal neighbouring cells. Conway also defined the transitions rule:
   dead cell become alive if it has exactly 3 living adjacents, and an alive
   cell survives only if it has 2 or 3 living neighbours. After executing a
   transition for all cells, the two patterns are in a relationship: the
   older is the father, the newer is the child.

   It is an interesting problem both in Mathematics and Phylosophy if
   there is a fatherless pattern (in CGoL). Fairly trivial existence
   proofs had been published since then, and immediately explicit
   constructions are followed.

   This GMPL model searches for a father pattern of the pattern specified in
   the c parameter matrix, and prints the found one if any both in human
   readable format and in RLE format, which could be open with some Cellular
   Automata simulators like Golly, for example.

   See more about Garden of Edens:
   http://conwaylife.com/wiki/Garden_of_Eden

   Golly CA simulator:
   http://golly.sourceforge.net/

   Tip for running with the example pattern:
   glpsol --math life_goe.mod --cuts --last

   WARNING: Rather CPU- and memory-intensive process to find out if a given
   pattern is a GOE if it really is!
*/

param height, integer, > 0;
/* height of the successor pattern */

param width, integer, > 0;
/* width of the successor pattern */

set ROWS := 0..height + 1;
/* set of rows of the predecessor */

set COLUMNS := 0..width + 1;
/* set of columns of the predecessor */

set MOORE := {(0, 1), (0, -1), (1, 0), (-1, 0), (1, 1), (-1, 1), (1, -1),
    (-1, -1)};
/* Moore-neighbourhood relative coordinates */

param c{ROWS, COLUMNS}, >= 0;
/* Denotes the cellspace of 1st generation, where 0, 1 and 2 means dead,
   alive or arbitrary cell values respectively. Usually the frame values
   must be set to "2", and also "2" is allowed in the inner rectangle. */

set IJalive := setof{(i, j) in ROWS cross COLUMNS: c[i, j] = 1}(i, j);
/* set of alive cells in the child */

set IJdead := setof{(i, j) in ROWS cross COLUMNS: c[i, j] = 0}(i, j);
/* set of dead cells in the child */

set IJ := IJalive union IJdead;
/* set of cells in the child with enforced states */

var x{ROWS, COLUMNS}, binary;
/* father's states */

var dpos{ROWS, COLUMNS}, >= 0;
/* positive part of the distances from 6 */

var dneg{ROWS, COLUMNS}, >= 0;
/* negative part of the distances from 6 */

var dposup{ROWS, COLUMNS}, binary;
/* positive part's upper bound enforcement */

var dnegup{ROWS, COLUMNS}, binary;
/* negative part's upper bound enforcement */

s.t. maincons{(i, j) in IJ}:
    x[i, j] + sum{(a, b) in MOORE} (2 * x[i + a, j + b]) =
        6 + dpos[i,j] - dneg[i,j];
/* in the LHS, there is a function that maps from all possible 512 state
   combinations of a father cell and its Moore-neighbourhood to [0..17].
   And for CGoL, if the child is alive, then it should be between 5 and 7.
   Also implicit introduced "d" as distance from 6 in RHS, and immediately
   decomposed "d" into positive and negative parts denoted dpos and dneg. */

s.t. posbound{(i,j) in IJ}: dpos[i,j] <= 11 * dposup[i,j];
/* constraining positive part of distance */

s.t. negbound{(i,j) in IJ}: dneg[i,j] <= 6 * dnegup[i,j];
/* constraining negative part of distance */

s.t. mutex{(i,j) in IJ}: dposup[i,j] + dnegup[i,j] = 1;
/* Ensuring that at most one is positive among the pos./neg. parts */

s.t. alive{(i,j) in IJalive}: dpos[i,j] + dneg[i,j] <= 1;
/* LHS of maincons must be 5, 6 or 7 either due to child cell is alive */

s.t. dead{(i,j) in IJdead}: dpos[i,j] + dneg[i,j] >= 2;
/* LHS of maincons must be at most 4 or at least 8 */

/* This is a feasibility problem, so no objective is needed */

solve;

printf '\nFound a father pattern:\n\n';
for{i in ROWS}{
    for{j in COLUMNS}{
        printf '%s%s', if j then ' ' else '', x[i, j].val;
    }
    printf '\n';
}

printf '\nThe father pattern in rle format:\n\n';
for{i in ROWS}{
    for{j in COLUMNS}{
        printf '%s', if x[i, j].val then 'o' else 'b';
    }
    printf '$';
}
printf '!\n\n';

data;
/*
   This example is a halved of a 10x10 garden of eden pattern from:
   http://wwwhomes.uni-bielefeld.de/achim/orphan_7th.html
   It has a 90 degree rotational symmetry, so if having enough resources,
   just comment the line denoted with "8", and uncomment the following part!
   And also do not forget to increase height parameter, respectively!
*/

param height := 7;

param width := 10;

param c : 0  1  2  3  4  5  6  7  8  9 10 11 :=
       0  2  2  2  2  2  2  2  2  2  2  2  2
       1  2  0  1  0  1  1  1  0  1  0  0  2
       2  2  0  0  1  0  1  0  1  0  0  1  2
       3  2  1  0  1  1  1  0  0  1  1  0  2
       4  2  0  1  0  1  1  1  1  1  0  1  2
       5  2  1  0  0  1  0  0  1  1  1  1  2
       6  2  1  1  1  1  0  0  1  0  0  1  2
       7  2  1  0  1  1  1  1  1  0  1  0  2
       8  2  2  2  2  2  2  2  2  2  2  2  2;

/*     8  2  0  1  1  0  0  1  1  1  0  1  2
       9  2  1  0  0  1  0  1  0  1  0  0  2
      10  2  0  0  1  0  1  1  1  0  1  0  2
      11  2  2  2  2  2  2  2  2  2  2  2  2; */

end;

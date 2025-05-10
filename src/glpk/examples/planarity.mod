/* PLANARITY, Graph Planarity Testing */

/* Written in GNU MathProg by Andrew Makhorin <mao@gnu.org> */

/* Given a graph G = (V, E), where V is a set of vertices and E is
   a set of edges (unordered pairs of vertices), this model tests if
   G is planar, and if it is, finds its faces for some embedding.
   It is assumed that G is loopless and the degree of any its vertex
   is at least 2.

   Though there exist linear-time algorithms to test graph planarity,
   this MIP feasibility model may be used, for example, to find
   an embedding subject to some additional constraints or an "optimal"
   embedding.

   This model is based on Mac Lane's planarity characterization that
   states that a finite undirected graph is planar iff the cycle space
   of the graph (in GF(2)) has a cycle basis in which each edge of the
   graph participates in at most two basis vectors. */

param nv;
/* number of vertices */

set V := 1..nv;
/* set of vertices */

set E, within V cross V;
/* set of edges */

check{(i,j) in E} i <> j;
/* graph must have no loops */

set A := E union setof{(i,j) in E} (j,i);
/* set of arcs, where every edge (i,j) gives two arcs i->j and j->i */

check{i in V} sum{(i,j) in A} 1 >= 2;
/* degree of any vertex must be at least 2 */

param nf := 2 - nv + card(E);
/* number of faces (including outer face) */

set F := 1..nf;
/* set of faces = set of vertices of dual graph */

/* Let every face be assigned a unique color. Below we say that arc
   i->j has color f if on moving from vertex i to vertex j face f is
   located on the left to that arc. (Note that every face is defined
   by a cycle mentioned in Mac Lane's characterization. In this model
   cycles are constructed explicitly from arcs.) */

var x{(i,j) in A, f in F}, binary;
/* x[i,j,f] = 1 means that arc i->j has color f */

s.t. r1{(i,j) in A}: sum{f in F} x[i,j,f] = 1;
/* every arc must have exactly one color */

s.t. r2{j in V, f in F}: sum{(i,j) in A} x[i,j,f] <= 1;
/* two or more arcs of the same color must not enter the same vertex */

s.t. r3{j in V, f in F}:
     sum{(i,j) in A} x[i,j,f] = sum{(j,i) in A} x[j,i,f];
/* if arc of color f enters some vertex, exactly one arc of the same
   color must leave that vertex */

s.t. r4{(i,j) in E, f in F}: x[i,j,f] + x[j,i,f] <= 1;
/* arcs that correspond to the same edge must have different colors
   (to avoid invalid faces i->j->i) */

s.t. r5{f in F}: sum{(i,j) in A} x[i,j,f] >= 1;
/* every color must be used at least once */

/* this is a feasibility problem, so no objective is needed */

solve;

printf "number of vertices = %d\n", nv;
printf "number of edges    = %d\n", card(A) / 2;
printf "number of faces    = %d\n", nf;

for {f in F}
{  printf "face %d:", f;
   printf {(i,j) in A: x[i,j,f] = 1} " %d->%d", i, j;
   printf "\n";
}

data;

/* The data below correspond to the following (planar) graph:

               1 - 2 - - 3 - - 4
               |         |     |
               |         |     |
               5 - 6     |     |
               |     \   |     |
               |       \ |     |
               7 - - - - 8 - - 9 - - - - 10- - -11
               |       / |       \       |      |
               |     /   |         \     |      |
               |   /     |           \   |      |
               | /       |             \ |      |
              12 - - - -13 - - - - - - - 14- - -15                   */

param nv := 15;

set E := (1,2) (1,5) (2,3) (3,4) (3,8) (4,9) (5,6) (5,7) (6,8)
         (7,8) (7,12) (8,9) (8,12) (8,13) (9,10) (9,14) (10,11)
         (10,14) (11,15) (12,13) (13,14) (14,15) ;

end;

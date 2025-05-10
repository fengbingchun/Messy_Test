/* COLOR, Graph Coloring Problem */

/* Written in GNU MathProg by Andrew Makhorin <mao@gnu.org> */

/* Given an undirected loopless graph G = (V, E), where V is a set of
   nodes, E <= V x V is a set of arcs, the Graph Coloring Problem is to
   find a mapping (coloring) F: V -> C, where C = {1, 2, ... } is a set
   of colors whose cardinality is as small as possible, such that
   F(i) != F(j) for every arc (i,j) in E, that is adjacent nodes must
   be assigned different colors. */

param n, integer, >= 2;
/* number of nodes */

set V := {1..n};
/* set of nodes */

set E, within V cross V;
/* set of arcs */

check{(i,j) in E}: i != j;
/* there must be no loops */

/* We need to estimate an upper bound of the number of colors |C|.
   The number of nodes |V| can be used, however, for sparse graphs such
   bound is not very good. To obtain a more suitable estimation we use
   an easy "greedy" heuristic. Let nodes 1, ..., i-1 are already
   assigned some colors. To assign a color to node i we see if there is
   an existing color not used for coloring nodes adjacent to node i. If
   so, we use this color, otherwise we introduce a new color. */

set EE := setof{(i,j) in E} (i,j) union setof{(i,j) in E} (j,i);
/* symmetrisized set of arcs */

param z{i in V, case in 0..1} :=
/* z[i,0] = color index assigned to node i
   z[i,1] = maximal color index used for nodes 1, 2, ..., i-1 which are
            adjacent to node i */
(  if case = 0 then
   (  /* compute z[i,0] */
      min{c in 1..z[i,1]}
      (  if not exists{j in V: j < i and (i,j) in EE} z[j,0] = c then
            c
         else
            z[i,1] + 1
      )
   )
   else
   (  /* compute z[i,1] */
      if not exists{j in V: j < i} (i,j) in EE then
         1
      else
         max{j in V: j < i and (i,j) in EE} z[j,0]
   )
);

check{(i,j) in E}: z[i,0] != z[j,0];
/* check that all adjacent nodes are assigned distinct colors */

param nc := max{i in V} z[i,0];
/* number of colors used by the heuristic; obviously, it is an upper
   bound of the optimal solution */

display nc;

var x{i in V, c in 1..nc}, binary;
/* x[i,c] = 1 means that node i is assigned color c */

var u{c in 1..nc}, binary;
/* u[c] = 1 means that color c is used, i.e. assigned to some node */

s.t. map{i in V}: sum{c in 1..nc} x[i,c] = 1;
/* each node must be assigned exactly one color */

s.t. arc{(i,j) in E, c in 1..nc}: x[i,c] + x[j,c] <= u[c];
/* adjacent nodes cannot be assigned the same color */

minimize obj: sum{c in 1..nc} u[c];
/* objective is to minimize the number of colors used */

data;

/* These data correspond to the instance myciel3.col from:
   http://mat.gsia.cmu.edu/COLOR/instances.html */

/* The optimal solution is 4 */

param n := 11;

set E :=
 1 2
 1 4
 1 7
 1 9
 2 3
 2 6
 2 8
 3 5
 3 7
 3 10
 4 5
 4 6
 4 10
 5 8
 5 9
 6 11
 7 11
 8 11
 9 11
 10 11
;

end;

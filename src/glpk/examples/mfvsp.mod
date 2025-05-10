/* MFVSP, Minimum Feedback Vertex Set Problem */

/* Written in GNU MathProg by Andrew Makhorin <mao@gnu.org> */

/* The Minimum Feedback Vertex Set Problem for a given directed graph
   G = (V, E), where V is a set of vertices and E is a set of arcs, is
   to find a minimal subset of vertices, which being removed from the
   graph make it acyclic.

   Reference:
   Garey, M.R., and Johnson, D.S. (1979), Computers and Intractability:
   A guide to the theory of NP-completeness [Graph Theory, Covering and
   Partitioning, Minimum Feedback Vertex Set, GT8]. */

param n, integer, >= 0;
/* number of vertices */

set V, default 1..n;
/* set of vertices */

set E, within V cross V,
default setof{i in V, j in V: i <> j and Uniform(0,1) <= 0.15} (i,j);
/* set of arcs */

printf "Graph has %d vertices and %d arcs\n", card(V), card(E);

var x{i in V}, binary;
/* x[i] = 1 means that i is a feedback vertex */

/* It is known that a digraph G = (V, E) is acyclic if and only if its
   vertices can be assigned numbers from 1 to |V| in such a way that
   k[i] + 1 <= k[j] for every arc (i->j) in E, where k[i] is a number
   assigned to vertex i. We may use this condition to require that the
   digraph G = (V, E \ E'), where E' is a subset of feedback arcs, is
   acyclic. */

var k{i in V}, >= 1, <= card(V);
/* k[i] is a number assigned to vertex i */

s.t. r{(i,j) in E}: k[j] - k[i] >= 1 - card(V) * (x[i] + x[j]);
/* note that x[i] = 1 or x[j] = 1 leads to a redundant constraint */

minimize obj: sum{i in V} x[i];
/* the objective is to minimize the cardinality of a subset of feedback
   vertices */

solve;

printf "Minimum feedback vertex set:\n";
printf{i in V: x[i]} "%d\n", i;

data;

/* The optimal solution is 3 */

param n := 15;

set E := 1 2, 2 3, 3 4, 3 8, 4 9, 5 1, 6 5, 7 5, 8 6, 8 7, 8 9, 9 10,
         10 11, 10 14, 11 15, 12 7, 12 8, 12 13, 13 8, 13 12, 13 14,
         14 9, 15 14;

end;

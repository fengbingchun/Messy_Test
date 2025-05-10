/* MVCP, Minimum Vertex Cover Problem */

/* Written in GNU MathProg by Andrew Makhorin <mao@gnu.org> */

/* The Minimum Vertex Cover Problem in a network G = (V, E), where V
   is a set of nodes, E is a set of arcs, is to find a subset V' within
   V such that each edge (i,j) in E has at least one its endpoint in V'
   and which minimizes the sum of node weights w(i) over V'.

   Reference:
   Garey, M.R., and Johnson, D.S. (1979), Computers and Intractability:
   A guide to the theory of NP-completeness [Graph Theory, Covering and
   Partitioning, Minimum Vertex Cover, GT1]. */

set E, dimen 2;
/* set of edges */

set V := (setof{(i,j) in E} i) union (setof{(i,j) in E} j);
/* set of nodes */

param w{i in V}, >= 0, default 1;
/* w[i] is weight of vertex i */

var x{i in V}, binary;
/* x[i] = 1 means that node i is included into V' */

s.t. cov{(i,j) in E}: x[i] + x[j] >= 1;
/* each edge (i,j) must have node i or j (or both) in V' */

minimize z: sum{i in V} w[i] * x[i];
/* we need to minimize the sum of node weights over V' */

data;

/* These data correspond to an example from [Papadimitriou]. */

/* Optimal solution is 6 (greedy heuristic gives 13) */

set E := a1 b1, b1 c1, a1 b2, b2 c2, a2 b3, b3 c3, a2 b4, b4 c4, a3 b5,
         b5 c5, a3 b6, b6 c6, a4 b1, a4 b2, a4 b3, a5 b4, a5 b5, a5 b6,
         a6 b1, a6 b2, a6 b3, a6 b4, a7 b2, a7 b3, a7 b4, a7 b5, a7 b6;

end;

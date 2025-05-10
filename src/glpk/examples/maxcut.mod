/* MAXCUT, Maximum Cut Problem */

/* Written in GNU MathProg by Andrew Makhorin <mao@gnu.org> */

/* The Maximum Cut Problem in a network G = (V, E), where V is a set
   of nodes, E is a set of edges, is to find the partition of V into
   disjoint sets V1 and V2, which maximizes the sum of edge weights
   w(e), where edge e has one endpoint in V1 and other endpoint in V2.

   Reference:
   Garey, M.R., and Johnson, D.S. (1979), Computers and Intractability:
   A guide to the theory of NP-completeness [Network design, Cuts and
   Connectivity, Maximum Cut, ND16]. */

set E, dimen 2;
/* set of edges */

param w{(i,j) in E}, >= 0, default 1;
/* w[i,j] is weight of edge (i,j) */

set V := (setof{(i,j) in E} i) union (setof{(i,j) in E} j);
/* set of nodes */

var x{i in V}, binary;
/* x[i] = 0 means that node i is in set V1
   x[i] = 1 means that node i is in set V2 */

/* We need to include in the objective function only that edges (i,j)
   from E, for which x[i] != x[j]. This can be modeled through binary
   variables s[i,j] as follows:

      s[i,j] = x[i] xor x[j] = (x[i] + x[j]) mod 2,                  (1)

   where s[i,j] = 1 iff x[i] != x[j], that leads to the following
   objective function:

      z = sum{(i,j) in E} w[i,j] * s[i,j].                           (2)

   To describe "exclusive or" (1) we could think that s[i,j] is a minor
   bit of the sum x[i] + x[j]. Then introducing binary variables t[i,j],
   which represent a major bit of the sum x[i] + x[j], we can write:

      x[i] + x[j] = s[i,j] + 2 * t[i,j].                             (3)

   An easy check shows that conditions (1) and (3) are equivalent.

   Note that condition (3) can be simplified by eliminating variables
   s[i,j]. Indeed, from (3) it follows that:

      s[i,j] = x[i] + x[j] - 2 * t[i,j].                             (4)

   Since the expression in the right-hand side of (4) is integral, this
   condition can be rewritten in the equivalent form:

      0 <= x[i] + x[j] - 2 * t[i,j] <= 1.                            (5)

   (One might note that (5) means t[i,j] = x[i] and x[j].)

   Substituting s[i,j] from (4) to (2) leads to the following objective
   function:

      z = sum{(i,j) in E} w[i,j] * (x[i] + x[j] - 2 * t[i,j]),       (6)

   which does not include variables s[i,j]. */

var t{(i,j) in E}, binary;
/* t[i,j] = x[i] and x[j] = (x[i] + x[j]) div 2 */

s.t. xor{(i,j) in E}: 0 <= x[i] + x[j] - 2 * t[i,j] <= 1;
/* see (4) */

maximize z: sum{(i,j) in E} w[i,j] * (x[i] + x[j] - 2 * t[i,j]);
/* see (6) */

data;

/* In this example the network has 15 nodes and 22 edges. */

/* Optimal solution is 20 */

set E :=
   1 2, 1 5, 2 3, 2 6, 3 4, 3 8, 4 9, 5 6, 5 7, 6 8, 7 8, 7 12, 8 9,
   8 12, 9 10, 9 14, 10 11, 10 14, 11 15, 12 13, 13 14, 14 15;

end;

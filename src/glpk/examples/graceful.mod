/* Graceful Tree Labeling Problem */

/* Author: Mike Appleby <mike@app.leby.org> */

/* The Graceful Labeling Problem for a tree G = (V, E), where V is the
   set of vertices and E is the set of edges, is to find a labeling of
   the vertices with the integers between 1 and |V| inclusive, such
   that no two vertices share a label, and such that each edge is
   uniquely identified by the positive, or absolute difference between
   the labels of its endpoints.

   In other words, if vl are the vertex labels and el are the edge
   labels, then for every edge (u,v) in E, el[u,v]=abs(vl[u] - vl[v]).

   https://en.wikipedia.org/wiki/Graceful_labeling */

set V;
/* set of vertices */

set E within V cross V;
/* set of edges */

set N := 1..card(V);
/* vertex labels */

set M := 1..card(V)-1;
/* edge labels */

var vx{V, N}, binary;
/* binary encoding of vertex labels.
   vx[v,n] == 1 means vertex v has label n. */

s.t. vxa{v in V}: sum{n in N} vx[v,n] = 1;
/* each vertex is assigned exactly one label. */

s.t. vxb{n in N}: sum{v in V} vx[v,n] = 1;
/* each label is assigned to exactly one vertex. */

var vl{V}, integer, >= 1, <= card(V);
/* integer encoding of vertex labels.
   vl[v] == n means vertex v has label n. */

s.t. vla{v in V}: vl[v] = sum{n in N} n * vx[v,n];
/* by constraint vxa, exactly one of vx[v,n] == 1 and the rest are
   zero. So if vx[v,3] == 1, then vl[v] = 3. */

var ex{E, M}, binary;
/* binary encoding of edge labels.
   ex[u,v,n] == 1 means edge (u,v) has label n. */

s.t. exa{(u,v) in E}: sum{m in M} ex[u,v,m] = 1;
/* each edge is assigned exactly one label. */

s.t. exb{m in M}: sum{(u,v) in E} ex[u,v,m] = 1;
/* each label is assigned to exactly one edge. */

var el{E}, integer, >= 1, <= card(E);
/* integer encoding of edge labels.
   el[u,v] == n means edge (u,v) has label n. */

s.t. ela{(u,v) in E}: el[u,v] = sum{m in M} m * ex[u,v,m];
/* similar to vla above, define integer encoding of edge labels in
   terms of the corresponding binary variable. */

var gt{E}, binary;
/* gt[u,v] = 1 if vl[u] > vl[v] else 0.
   gt helps encode the absolute value constraint, below. */

s.t. elb{(u,v) in E}: el[u,v] >= vl[u] - vl[v];
s.t. elc{(u,v) in E}: el[u,v] <= vl[u] - vl[v] + 2*card(V)*(1-gt[u,v]);
s.t. eld{(u,v) in E}: el[u,v] >= vl[v] - vl[u];
s.t. ele{(u,v) in E}: el[u,v] <= vl[v] - vl[u] + 2*card(V)*gt[u,v];

/* These four constraints together model the absolute value constraint
   of the graceful labeling problem: el[u,v] == abs(vl[u] - vl[v]).
   However, since the absolute value is a non-linear function, we
   transform it into a series of linear constraints, as above.

   To see that these four constraints model the absolute value
   condition, consider the following cases:

   if vl[u] > vl[v] and gt[u,v] == 0 then
       - ele is unsatisfiable, since the constraint ele amounts to

             el[u,v] <= vl[v] - vl[u] + 0 (since gt[u,v] == 0)
                     <= -1                (since vl[u] > vl[v])

         but el[u,v] is declared with lower bound >= 1; hence, the
         constraints cannot be satisfied if vl[u] > vl[v] and
         gt[u,v] == 0.

   if vl[u] > vl[v] and gt[u,v] == 1 then
       - elb and elc together are equivalent to

             vl[u] - vl[v] <= el[u,v] <= vl[u] - vl[v], i.e.
             el[u,v] = vl[u] - vl[v]
                     = abs(vl[u] - vl[v]) (since vl[u] > vl[v])

       - eld and elc together are equivalent to

             vl[v] - vl[u] <= el[u,v] <= vl[v] - vl[u] + 2|V|

         the tightest possible bounds are

             -1 <= el[u,v] <= |V|+1

         which is satisfied since both bounds are looser than the
         constraints on el's variable declaration, namely

             var el{E}, integer, >= 1, <= card(E);

         where |E| = |V|-1

   The cases for vl[v] > vl[u] are similar, but with roles reversed
   for elb/elc and eld/ele.

   In other words, when vl[u] > vl[v], then gt[u,v] == 1, elb and elc
   together model the absolute value constraint, and ele and eld are
   satisfied due to bounds constraints on el. When vl[v] > vl[u], then
   gt[u,v] == 0, ele and eld model the absolute value constraint, and
   elb and elc are satisfied due to bounds constraints on el.

   Note that vl[u] != vl[v], by a combination of constraints vxa, vxb,
   and vla. */

solve;

check 0 = card(N symdiff setof{v in V} vl[v]);
/* every vertex label is assigned to one vertex */

check 0 = card(M symdiff setof{(u,v) in E} el[u,v]);
/* every edge label is assigned to one edge */

check {(u,v) in E} el[u,v] = abs(vl[u] - vl[v]);
/* every edge label for every edge (u,v) == abs(vl[u] - vl[v]) */

printf "vertices:\n";
for{v in V} { printf "\t%s: %d\n", v, vl[v]; }

printf "edges:\n";
printf "\torig\tvlabel\telabel\tabs(u-v)\n";
for{(u,v) in E} {
	printf "\t(%s,%s)\t(%d,%d)\t%d\t%d\n",
           u, v, vl[u], vl[v], el[u,v], abs(vl[u]-vl[v]);
}

data;

set V := a b c d e f g;
set E := a b, a d, a g, b c, b e, e f;

end;

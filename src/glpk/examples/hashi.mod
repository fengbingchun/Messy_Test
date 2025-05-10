/* A solver for the Japanese number-puzzle Hashiwokakero
 * (http://en.wikipedia.org/wiki/Hashiwokakero)
 *
 * Sebastian Nowozin <nowozin@gmail.com>, 13th January 2009
 */

param n := 25;
set rows := 1..n;
set cols := 1..n;
param givens{rows, cols}, integer, >= 0, <= 8, default 0;

/* Set of vertices as (row,col) coordinates */
set V := { (i,j) in { rows, cols }: givens[i,j] != 0 };

/* Set of feasible horizontal edges from (i,j) to (k,l) rightwards */
set Eh := { (i,j,k,l) in { V, V }:
        i = k and j < l and             # Same row and left to right
        card({ (s,t) in V: s = i and t > j and t < l }) = 0             # No vertex inbetween
        };

/* Set of feasible vertical edges from (i,j) to (k,l) downwards */
set Ev := { (i,j,k,l) in { V, V }:
        j = l and i < k and             # Same column and top to bottom
        card({ (s,t) in V: t = j and s > i and s < k }) = 0             # No vertex inbetween
        };

set E := Eh union Ev;

/* Indicators: use edge once/twice */
var xe1{E}, binary;
var xe2{E}, binary;

/* Constraint: Do not use edge or do use once or do use twice */
s.t. edge_sel{(i,j,k,l) in E}:
        xe1[i,j,k,l] + xe2[i,j,k,l] <= 1;

/* Constraint: There must be as many edges used as the node value */
s.t. satisfy_vertex_demand{(s,t) in V}:
        sum{(i,j,k,l) in E: (i = s and j = t) or (k = s and l = t)}
                (xe1[i,j,k,l] + 2.0*xe2[i,j,k,l]) = givens[s,t];

/* Constraint: No crossings */
s.t. no_crossing1{(i,j,k,l) in Eh, (s,t,u,v) in Ev:
        s < i and u > i and j < t and l > t}:
        xe1[i,j,k,l] + xe1[s,t,u,v] <= 1;
s.t. no_crossing2{(i,j,k,l) in Eh, (s,t,u,v) in Ev:
        s < i and u > i and j < t and l > t}:
        xe1[i,j,k,l] + xe2[s,t,u,v] <= 1;
s.t. no_crossing3{(i,j,k,l) in Eh, (s,t,u,v) in Ev:
        s < i and u > i and j < t and l > t}:
        xe2[i,j,k,l] + xe1[s,t,u,v] <= 1;
s.t. no_crossing4{(i,j,k,l) in Eh, (s,t,u,v) in Ev:
        s < i and u > i and j < t and l > t}:
        xe2[i,j,k,l] + xe2[s,t,u,v] <= 1;


/* Model connectivity by auxiliary network flow problem:
 * One vertex becomes a target node and all other vertices send a unit flow
 * to it.  The edge selection variables xe1/xe2 are VUB constraints and
 * therefore xe1/xe2 select the feasible graph for the max-flow problems.
 */
set node_target := { (s,t) in V:
        card({ (i,j) in V: i < s or (i = s and j < t) }) = 0};
set node_sources := { (s,t) in V: (s,t) not in node_target };

var flow_forward{ E }, >= 0;
var flow_backward{ E }, >= 0;
s.t. flow_conservation{ (s,t) in node_target, (p,q) in V }:
        /* All incoming flows */
        - sum{(i,j,k,l) in E: k = p and l = q} flow_forward[i,j,k,l]
        - sum{(i,j,k,l) in E: i = p and j = q} flow_backward[i,j,k,l]
        /* All outgoing flows */
        + sum{(i,j,k,l) in E: k = p and l = q} flow_backward[i,j,k,l]
        + sum{(i,j,k,l) in E: i = p and j = q} flow_forward[i,j,k,l]
        = 0 + (if (p = s and q = t) then card(node_sources) else -1);

/* Variable-Upper-Bound (VUB) constraints: xe1/xe2 bound the flows.
 */
s.t. connectivity_vub1{(i,j,k,l) in E}:
        flow_forward[i,j,k,l] <= card(node_sources)*(xe1[i,j,k,l] + xe2[i,j,k,l]);
s.t. connectivity_vub2{(i,j,k,l) in E}:
        flow_backward[i,j,k,l] <= card(node_sources)*(xe1[i,j,k,l] + xe2[i,j,k,l]);

/* A feasible solution is enough
 */
minimize cost: 0;

solve;

/* Output solution graphically */
printf "\nSolution:\n";
for { row in rows } {
        for { col in cols } {
                /* First print this cell information: givens or space */
                printf{0..0: givens[row,col] != 0} "%d", givens[row,col];
                printf{0..0: givens[row,col] = 0 and
                        card({(i,j,k,l) in Eh: i = row and col >= j and col < l and
                                xe1[i,j,k,l] = 1}) = 1} "-";
                printf{0..0: givens[row,col] = 0 and
                        card({(i,j,k,l) in Eh: i = row and col >= j and col < l and
                                xe2[i,j,k,l] = 1}) = 1} "=";
                printf{0..0: givens[row,col] = 0
                        and card({(i,j,k,l) in Ev: j = col and row >= i and row < k and
                                xe1[i,j,k,l] = 1}) = 1} "|";
                printf{0..0: givens[row,col] = 0
                        and card({(i,j,k,l) in Ev: j = col and row >= i and row < k and
                                xe2[i,j,k,l] = 1}) = 1} '"';
                printf{0..0: givens[row,col] = 0
                        and card({(i,j,k,l) in Eh: i = row and col >= j and col < l and
                                (xe1[i,j,k,l] = 1 or xe2[i,j,k,l] = 1)}) = 0
                        and card({(i,j,k,l) in Ev: j = col and row >= i and row < k and
                                (xe1[i,j,k,l] = 1 or xe2[i,j,k,l] = 1)}) = 0} " ";

                /* Now print any edges */
                printf{(i,j,k,l) in Eh: i = row and col >= j and col < l and xe1[i,j,k,l] = 1} "-";
                printf{(i,j,k,l) in Eh: i = row and col >= j and col < l and xe2[i,j,k,l] = 1} "=";

                printf{(i,j,k,l) in Eh: i = row and col >= j and col < l and
                        xe1[i,j,k,l] = 0 and xe2[i,j,k,l] = 0} " ";
                printf{0..0: card({(i,j,k,l) in Eh: i = row and col >= j and col < l}) = 0} " ";
        }
        printf "\n";
        for { col in cols } {
                printf{(i,j,k,l) in Ev: j = col and row >= i and row < k and xe1[i,j,k,l] = 1} "|";
                printf{(i,j,k,l) in Ev: j = col and row >= i and row < k and xe2[i,j,k,l] = 1} '"';
                printf{(i,j,k,l) in Ev: j = col and row >= i and row < k and
                        xe1[i,j,k,l] = 0 and xe2[i,j,k,l] = 0} " ";
                /* No vertical edges: skip also a field */
                printf{0..0: card({(i,j,k,l) in Ev: j = col and row >= i and row < k}) = 0} " ";
                printf " ";
        }
        printf "\n";
}

data;

/* This is a difficult 25x25 Hashiwokakero.
 */
param givens : 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24
25 :=
           1   2 . 2 . 2 . . 2 . 2 . . 2 . . . . 2 . 2 . 2 . 2 .
           2   . 1 . . . . 2 . . . 4 . . 5 . 2 . . 1 . 2 . 2 . 1
           3   2 . . 5 . 4 . . 3 . . . . . 1 . . 4 . 5 . 1 . 1 .
           4   . . . . . . . . . . . 1 . 3 . . 1 . . . . . . . .
           5   2 . . 6 . 6 . . 8 . 5 . 2 . . 3 . 5 . 7 . . 2 . .
           6   . 1 . . . . . . . . . 1 . . 2 . . . . . 1 . . . 3
           7   2 . . . . 5 . . 6 . 4 . . 2 . . . 2 . 5 . 4 . 2 .
           8   . 2 . 2 . . . . . . . . . . . 3 . . 3 . . . 1 . 2
           9   . . . . . . . . . . 4 . 2 . 2 . . 1 . . . 3 . 1 .
          10   2 . 3 . . 6 . . 2 . . . . . . . . . . 3 . . . . .
          11   . . . . 1 . . 2 . . 5 . . 1 . 4 . 3 . . . . 2 . 4
          12   . . 2 . . 1 . . . . . . 5 . 4 . . . . 4 . 3 . . .
          13   2 . . . 3 . 1 . . . . . . . . 3 . . 5 . 5 . . 2 .
          14   . . . . . 2 . 5 . . 7 . 5 . 3 . 1 . . 1 . . 1 . 4
          15   2 . 5 . 3 . . . . 1 . 2 . 1 . . . . 2 . 4 . . 2 .
          16   . . . . . 1 . . . . . . . . . . 2 . . 2 . 1 . . 3
          17   2 . 6 . 6 . . 2 . . 2 . 2 . 5 . . . . . 2 . . . .
          18   . . . . . 1 . . . 3 . . . . . 1 . . 1 . . 4 . 3 .
          19   . . 4 . 5 . . 2 . . . 2 . . 6 . 6 . . 3 . . . . 3
          20   2 . . . . . . . . . 2 . . 1 . . . . . . 1 . . 1 .
          21   . . 3 . . 3 . 5 . 5 . . 4 . 6 . 7 . . 4 . 6 . . 4
          22   2 . . . 3 . 5 . 2 . 1 . . . . . . . . . . . . . .
          23   . . . . . . . . . 1 . . . . . . 3 . 2 . . 5 . . 5
          24   2 . 3 . 3 . 5 . 4 . 3 . 3 . 4 . . 2 . 2 . . . 1 .
          25   . 1 . 2 . 2 . . . 2 . 2 . . . 2 . . . . 2 . 2 . 2
           ;

end;

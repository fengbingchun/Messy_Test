/* GAP, Generalized Assignment Problem */

/* Written in GNU MathProg by Andrew Makhorin <mao@gnu.org> */

/* The Generalized Assignment Problem (GAP) is to assign a set of jobs
   to a set of agents subject to the constraints that each job must be
   assigned exactly to one agent and the total resources consumed by all
   jobs assigned to an agent must not exceed the agent's capacity. */

param m, integer, > 0;
/* number of agents */

param n, integer, > 0;
/* number of jobs */

set I := 1..m;
/* set of agents */

set J := 1..n;
/* set of jobs */

param a{i in I, j in J}, >= 0;
/* resource consumed in allocating job j to agent i */

param b{i in I}, >= 0;
/* resource capacity of agent i */

param c{i in I, j in J}, >= 0;
/* cost of allocating job j to agent i */

var x{i in I, j in J}, binary;
/* x[i,j] = 1 means job j is assigned to agent i */

s.t. one{j in J}: sum{i in I} x[i,j] = 1;
/* job j must be assigned exactly to one agent */

s.t. lim{i in I}: sum{j in J} a[i,j] * x[i,j] <= b[i];
/* total amount of resources consumed by all jobs assigned to agent i
   must not exceed the agent's capacity */

minimize obj: sum{i in I, j in J} c[i,j] * x[i,j];
/* the objective is to find cheapest assignment (note that gap can also
   be formulated as maximization problem) */

data;

/* These data correspond to the instance c515-1 (gap1) from:

   I.H. Osman, "Heuristics for the Generalised Assignment Problem:
   Simulated Annealing and Tabu Search Approaches", OR Spektrum, Volume
   17, 211-225, 1995

   D. Cattrysse, M. Salomon and L.N. Van Wassenhove, "A set partitioning
   heuristic for the generalized assignment problem", European Journal
   of Operational Research, Volume 72, 167-174, 1994 */

/* The optimal solution is 261 (minimization) or 336 (maximization) */

param m := 5;

param n := 15;

param a :  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 :=
      1    8 15 14 23  8 16  8 25  9 17 25 15 10  8 24
      2   15  7 23 22 11 11 12 10 17 16  7 16 10 18 22
      3   21 20  6 22 24 10 24  9 21 14 11 14 11 19 16
      4   20 11  8 14  9  5  6 19 19  7  6  6 13  9 18
      5    8 13 13 13 10 20 25 16 16 17 10 10  5 12 23 ;

param b := 1 36, 2 34, 3 38, 4 27, 5 33;

param c :  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 :=
      1   17 21 22 18 24 15 20 18 19 18 16 22 24 24 16
      2   23 16 21 16 17 16 19 25 18 21 17 15 25 17 24
      3   16 20 16 25 24 16 17 19 19 18 20 16 17 21 24
      4   19 19 22 22 20 16 19 17 21 19 25 23 25 25 25
      5   18 19 15 15 21 25 16 16 23 15 22 17 19 22 24 ;

end;

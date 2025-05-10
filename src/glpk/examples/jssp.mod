/* JSSP, Job-Shop Scheduling Problem */

/* Written in GNU MathProg by Andrew Makhorin <mao@gnu.org> */

/* The Job-Shop Scheduling Problem (JSSP) is to schedule a set of jobs
   on a set of machines, subject to the constraint that each machine can
   handle at most one job at a time and the fact that each job has a
   specified processing order through the machines. The objective is to
   schedule the jobs so as to minimize the maximum of their completion
   times.

   Reference:
   D. Applegate and W. Cook, "A Computational Study of the Job-Shop
   Scheduling Problem", ORSA J. On Comput., Vol. 3, No. 2, Spring 1991,
   pp. 149-156. */

param n, integer, > 0;
/* number of jobs */

param m, integer, > 0;
/* number of machines */

set J := 1..n;
/* set of jobs */

set M := 1..m;
/* set of machines */

param sigma{j in J, t in 1..m}, in M;
/* permutation of the machines, which represents the processing order
   of j through the machines: j must be processed first on sigma[j,1],
   then on sigma[j,2], etc. */

check{j in J, t1 in 1..m, t2 in 1..m: t1 <> t2}:
      sigma[j,t1] != sigma[j,t2];
/* sigma must be permutation */

param p{j in J, a in M}, >= 0;
/* processing time of j on a */

var x{j in J, a in M}, >= 0;
/* starting time of j on a */

s.t. ord{j in J, t in 2..m}:
      x[j, sigma[j,t]] >= x[j, sigma[j,t-1]] + p[j, sigma[j,t-1]];
/* j can be processed on sigma[j,t] only after it has been completely
   processed on sigma[j,t-1] */

/* The disjunctive condition that each machine can handle at most one
   job at a time is the following:

      x[i,a] >= x[j,a] + p[j,a]  or  x[j,a] >= x[i,a] + p[i,a]

   for all i, j in J, a in M. This condition is modeled through binary
   variables Y as shown below. */

var Y{i in J, j in J, a in M}, binary;
/* Y[i,j,a] is 1 if i scheduled before j on machine a, and 0 if j is
   scheduled before i */

param K := sum{j in J, a in M} p[j,a];
/* some large constant */

display K;

s.t. phi{i in J, j in J, a in M: i <> j}:
      x[i,a] >= x[j,a] + p[j,a] - K * Y[i,j,a];
/* x[i,a] >= x[j,a] + p[j,a] iff Y[i,j,a] is 0 */

s.t. psi{i in J, j in J, a in M: i <> j}:
      x[j,a] >= x[i,a] + p[i,a] - K * (1 - Y[i,j,a]);
/* x[j,a] >= x[i,a] + p[i,a] iff Y[i,j,a] is 1 */

var z;
/* so-called makespan */

s.t. fin{j in J}: z >= x[j, sigma[j,m]] + p[j, sigma[j,m]];
/* which is the maximum of the completion times of all the jobs */

minimize obj: z;
/* the objective is to make z as small as possible */

data;

/* These data correspond to the instance ft06 (mt06) from:

   H. Fisher, G.L. Thompson (1963), Probabilistic learning combinations
   of local job-shop scheduling rules, J.F. Muth, G.L. Thompson (eds.),
   Industrial Scheduling, Prentice Hall, Englewood Cliffs, New Jersey,
   225-251 */

/* The optimal solution is 55 */

param n := 6;

param m := 6;

param sigma :  1  2  3  4  5  6 :=
          1    3  1  2  4  6  5
          2    2  3  5  6  1  4
          3    3  4  6  1  2  5
          4    2  1  3  4  5  6
          5    3  2  5  6  1  4
          6    2  4  6  1  5  3 ;

param p     :  1  2  3  4  5  6 :=
          1    3  6  1  7  6  3
          2   10  8  5  4 10 10
          3    9  1  5  4  7  8
          4    5  5  5  3  8  9
          5    3  3  9  1  5  4
          6   10  3  1  3  4  9 ;

end;

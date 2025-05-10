/* CPP, Critical Path Problem */

/* Written in GNU MathProg by Andrew Makhorin <mao@gnu.org> */

/* Note: Reduced costs of auxiliary variables phi[j,k] (see below)
         can be only zero or one. The critical path is defined by the
         constraints, whose reduced cost is one. */

set J;
/* set of jobs (activities) */

set P{j in J}, in J, default {};
/* P[j] is a subset of jobs that immediately precede job j */

param t{j in J}, >= 0;
/* duration required to perform job j */

var x{j in J}, >= 0;
/* starting time of job j */

s.t. phi{j in J, k in P[j]}: x[j] >= x[k] + t[k];
/* job j can start only after all immediately preceding jobs have been
   completely performed */

var z;
/* project makespan */

s.t. fin{j in J}: z >= x[j] + t[j];
/* which is the maximum of the completion times of all the jobs */

minimize obj: z;
/* the objective is make z as small as possible */

data;

/* The optimal solution is 46 */

param : J :  t :=
        A    3    /* Excavate */
        B    4    /* Lay foundation */
        C    3    /* Rough plumbing */
        D   10    /* Frame */
        E    8    /* Finish exterior */
        F    4    /* Install HVAC */
        G    6    /* Rough electric */
        H    8    /* Sheet rock */
        I    5    /* Install cabinets */
        J    5    /* Paint */
        K    4    /* Final plumbing */
        L    2    /* Final electric */
        M    4    /* Install flooring */
;

set P[B] := A;
set P[C] := B;
set P[D] := B;
set P[E] := D;
set P[F] := D;
set P[G] := D;
set P[H] := C E F G;
set P[I] := H;
set P[J] := H;
set P[K] := I;
set P[L] := J;
set P[M] := K L;

end;

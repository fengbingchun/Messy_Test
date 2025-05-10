/* Any Wolfram elementary CA in 6D eucl. Neumann CA grid emulator generator */

/* Implemented, inspected, written and converted to GNU MathProg
   by NASZVADI, Peter, 2016-2017 <vuk@cs.elte.hu> */

/* see background info and more details in wolfra6d.lp */

/* each axis has this two endpoints */
set V := 0..1;

/* this model processes a hypercube in 6d, so 6+1 parallel planes intersect  */
set H := 0..6;

/* denoting all vertices in the 6d unit hypercube */
set Cells := V cross V cross V cross V cross V cross V;


/* input parameters, bup/bdn = number of upper/lower neighbour 6d cells of a (cyclic) segment */
param bup{i in H}, default 1;
param bdn{i in H}, default 2;

/* boolean meaning if a vertex is chosen */
var x{Cells}, binary;

/* temporary calculations to enforce bup/bdn */
var up{Cells}, >=0;
var dn{Cells}, >=0;

/* the total weight of selected cells near the main diagonal */
var obj;

/* up/dn vars denote the number of selected upper/lower neighbours */
s.t. cup{(v1,v2,v3,v4,v5,v6) in Cells: v1+v2+v3+v4+v5+v6<6}:
    sum{(w1,w2,w3,w4,w5,w6) in Cells: max(v1-w1,v2-w2,v3-w3,v4-w4,v5-w5,v6-w6)<=0}
        if (w1+w2+w3+w4+w5+w6) = (1+v1+v2+v3+v4+v5+v6) then x[w1,w2,w3,w4,w5,w6] else 0 =
        up[v1,v2,v3,v4,v5,v6];

s.t. cdn{(v1,v2,v3,v4,v5,v6) in Cells: v1+v2+v3+v4+v5+v6>0}:
    sum{(w1,w2,w3,w4,w5,w6) in Cells: min(v1-w1,v2-w2,v3-w3,v4-w4,v5-w5,v6-w6)>=0}
        if (w1+w2+w3+w4+w5+w6) = (-1+v1+v2+v3+v4+v5+v6) then x[w1,w2,w3,w4,w5,w6] else 0 =
        dn[v1,v2,v3,v4,v5,v6];

/* 4 helper constraints, hences the leading "c" */
s.t. cbup1{(v1,v2,v3,v4,v5,v6) in Cells: v1+v2+v3+v4+v5+v6<6}:
    up[v1,v2,v3,v4,v5,v6] >= bup[v1+v2+v3+v4+v5+v6] * x[v1,v2,v3,v4,v5,v6];

s.t. cbup2{(v1,v2,v3,v4,v5,v6) in Cells: v1+v2+v3+v4+v5+v6<6}:
    up[v1,v2,v3,v4,v5,v6] + (2**6) * x[v1,v2,v3,v4,v5,v6] <= (2**6) + bup[v1+v2+v3+v4+v5+v6];

s.t. cbdn1{(v1,v2,v3,v4,v5,v6) in Cells: v1+v2+v3+v4+v5+v6>0}:
    dn[v1,v2,v3,v4,v5,v6] >= bdn[v1+v2+v3+v4+v5+v6] * x[v1,v2,v3,v4,v5,v6];

s.t. cbdn2{(v1,v2,v3,v4,v5,v6) in Cells: v1+v2+v3+v4+v5+v6>0}:
    dn[v1,v2,v3,v4,v5,v6] + (2**6) * x[v1,v2,v3,v4,v5,v6] <= (2**6) + bdn[v1+v2+v3+v4+v5+v6];

/* these two promoted points should be selected */
s.t. initdiag: x[0,0,0,0,0,0] + x[1,1,1,1,1,1] = 2;

/* obvious */
s.t. sumx: sum{(v1,v2,v3,v4,v5,v6) in Cells} x[v1,v2,v3,v4,v5,v6] = obj;

minimize cobj: obj;

solve;

/* pretty-printing hopefully nontrivial solution */
printf "\nChosen vertex subset:\n";
for{i in H}: {
    printf "Weight=%s\n", i;
    printf{(v1,v2,v3,v4,v5,v6) in Cells: v1+v2+v3+v4+v5+v6 = i+(8-8*x[v1,v2,v3,v4,v5,v6])}
        " %s%s%s%s%s%s\n",v1,v2,v3,v4,v5,v6;
}
printf "\nTotal number of selected cells in the hypercube: %g\n\n", obj;

data;

/* these parameters were chosen in the first run that yielded a solution */
param bup := 0 6
             1 2
             2 3
             3 2
             4 1
             5 1
             6 6;

param bdn := 0 3
             1 1
             2 2
             3 1
             4 4
             5 3
             6 3;

end;

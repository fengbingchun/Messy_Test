/* SAT, Satisfiability Problem */

/* Written in GNU MathProg by Andrew Makhorin <mao@gnu.org> */

param m, integer, > 0;
/* number of clauses */

param n, integer, > 0;
/* number of variables */

set C{1..m};
/* clauses; each clause C[i], i = 1, ..., m, is disjunction of some
   variables or their negations; in the data section each clause is
   coded as a set of indices of corresponding variables, where negative
   indices mean negation; for example, the clause (x3 or not x7 or x11)
   is coded as the set { 3, -7, 11 } */

var x{1..n}, binary;
/* main variables */

/* To solve the satisfiability problem means to determine all variables
   x[j] such that conjunction of all clauses C[1] and ... and C[m] takes
   on the value true, i.e. all clauses are satisfied.

   Let the clause C[i] be (t or t' or ... or t''), where t, t', ..., t''
   are either variables or their negations. The condition of satisfying
   C[i] can be most naturally written as:

      t + t' + ... + t'' >= 1,                                       (1)

   where t, t', t'' have to be replaced by either x[j] or (1 - x[j]).
   The formulation (1) leads to the mip problem with no objective, i.e.
   to a feasibility problem.

   Another, more practical way is to write the condition for C[i] as:

      t + t' + ... + t'' + y[i] >= 1,                                (2)

   where y[i] is an auxiliary binary variable, and minimize the sum of
   y[i]. If the sum is zero, all y[i] are also zero, and therefore all
   clauses are satisfied. If the sum is minimal but non-zero, its value
   shows the number of clauses which cannot be satisfied. */

var y{1..m}, binary, >= 0;
/* auxiliary variables */

s.t. c{i in 1..m}:
      sum{j in C[i]} (if j > 0 then x[j] else (1 - x[-j])) + y[i] >= 1;
/* the condition (2) */

minimize unsat: sum{i in 1..m} y[i];
/* number of unsatisfied clauses */

data;

/* These data correspond to the instance hole6 (pigeon hole problem for
   6 holes) from SATLIB, the Satisfiability Library, which is part of
   the collection at the Forschungsinstitut fuer anwendungsorientierte
   Wissensverarbeitung in Ulm Germany */

/* The optimal solution is 1 (one clause cannot be satisfied) */

param m := 133;

param n := 42;

set C[1] := -1 -7;
set C[2] := -1 -13;
set C[3] := -1 -19;
set C[4] := -1 -25;
set C[5] := -1 -31;
set C[6] := -1 -37;
set C[7] := -7 -13;
set C[8] := -7 -19;
set C[9] := -7 -25;
set C[10] := -7 -31;
set C[11] := -7 -37;
set C[12] := -13 -19;
set C[13] := -13 -25;
set C[14] := -13 -31;
set C[15] := -13 -37;
set C[16] := -19 -25;
set C[17] := -19 -31;
set C[18] := -19 -37;
set C[19] := -25 -31;
set C[20] := -25 -37;
set C[21] := -31 -37;
set C[22] := -2 -8;
set C[23] := -2 -14;
set C[24] := -2 -20;
set C[25] := -2 -26;
set C[26] := -2 -32;
set C[27] := -2 -38;
set C[28] := -8 -14;
set C[29] := -8 -20;
set C[30] := -8 -26;
set C[31] := -8 -32;
set C[32] := -8 -38;
set C[33] := -14 -20;
set C[34] := -14 -26;
set C[35] := -14 -32;
set C[36] := -14 -38;
set C[37] := -20 -26;
set C[38] := -20 -32;
set C[39] := -20 -38;
set C[40] := -26 -32;
set C[41] := -26 -38;
set C[42] := -32 -38;
set C[43] := -3 -9;
set C[44] := -3 -15;
set C[45] := -3 -21;
set C[46] := -3 -27;
set C[47] := -3 -33;
set C[48] := -3 -39;
set C[49] := -9 -15;
set C[50] := -9 -21;
set C[51] := -9 -27;
set C[52] := -9 -33;
set C[53] := -9 -39;
set C[54] := -15 -21;
set C[55] := -15 -27;
set C[56] := -15 -33;
set C[57] := -15 -39;
set C[58] := -21 -27;
set C[59] := -21 -33;
set C[60] := -21 -39;
set C[61] := -27 -33;
set C[62] := -27 -39;
set C[63] := -33 -39;
set C[64] := -4 -10;
set C[65] := -4 -16;
set C[66] := -4 -22;
set C[67] := -4 -28;
set C[68] := -4 -34;
set C[69] := -4 -40;
set C[70] := -10 -16;
set C[71] := -10 -22;
set C[72] := -10 -28;
set C[73] := -10 -34;
set C[74] := -10 -40;
set C[75] := -16 -22;
set C[76] := -16 -28;
set C[77] := -16 -34;
set C[78] := -16 -40;
set C[79] := -22 -28;
set C[80] := -22 -34;
set C[81] := -22 -40;
set C[82] := -28 -34;
set C[83] := -28 -40;
set C[84] := -34 -40;
set C[85] := -5 -11;
set C[86] := -5 -17;
set C[87] := -5 -23;
set C[88] := -5 -29;
set C[89] := -5 -35;
set C[90] := -5 -41;
set C[91] := -11 -17;
set C[92] := -11 -23;
set C[93] := -11 -29;
set C[94] := -11 -35;
set C[95] := -11 -41;
set C[96] := -17 -23;
set C[97] := -17 -29;
set C[98] := -17 -35;
set C[99] := -17 -41;
set C[100] := -23 -29;
set C[101] := -23 -35;
set C[102] := -23 -41;
set C[103] := -29 -35;
set C[104] := -29 -41;
set C[105] := -35 -41;
set C[106] := -6 -12;
set C[107] := -6 -18;
set C[108] := -6 -24;
set C[109] := -6 -30;
set C[110] := -6 -36;
set C[111] := -6 -42;
set C[112] := -12 -18;
set C[113] := -12 -24;
set C[114] := -12 -30;
set C[115] := -12 -36;
set C[116] := -12 -42;
set C[117] := -18 -24;
set C[118] := -18 -30;
set C[119] := -18 -36;
set C[120] := -18 -42;
set C[121] := -24 -30;
set C[122] := -24 -36;
set C[123] := -24 -42;
set C[124] := -30 -36;
set C[125] := -30 -42;
set C[126] := -36 -42;
set C[127] := 6 5 4 3 2 1;
set C[128] := 12 11 10 9 8 7;
set C[129] := 18 17 16 15 14 13;
set C[130] := 24 23 22 21 20 19;
set C[131] := 30 29 28 27 26 25;
set C[132] := 36 35 34 33 32 31;
set C[133] := 42 41 40 39 38 37;

end;

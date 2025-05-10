/* PBN, Paint-By-Numbers Puzzle */

/* Written in GNU MathProg by Andrew Makhorin <mao@gnu.org> */

/* NOTE: See also the document "Solving Paint-By-Numbers Puzzles with
         GLPK", which is included in the GLPK distribution. */

/* A paint-by-numbers puzzle consists of an m*n grid of pixels (the
   canvas) together with m+n cluster-size sequences, one for each row
   and column. The goal is to paint the canvas with a picture that
   satisfies the following constraints:

   1. Each pixel must be blank or white.

   2. If a row or column has cluster-size sequence s1, s2, ..., sk,
      then it must contain k clusters of black pixels - the first with
      s1 black pixels, the second with s2 black pixels, and so on.

   It should be noted that "first" means "leftmost" for rows and
   "topmost" for columns, and that rows and columns need not begin or
   end with black pixels.

   Example:
                  1   1
                  1   1
              2 1 1 1 1 1 2 3
              3 2 1 2 1 2 3 4 8 9

        3 6   # # # . # # # # # #
        1 4   # . . . . . # # # #
      1 1 3   . . # . # . . # # #
          2   . . . . . . . . # #
        3 3   . . # # # . . # # #
        1 4   # . . . . . # # # #
        2 5   # # . . . # # # # #
        2 5   # # . . . # # # # #
        1 1   . . . # . . . . . #
          3   . . # # # . . . . .

   (In Russia such puzzles are known as "Japanese crosswords".)

   References:
   Robert A. Bosch, "Painting by Numbers", 2000.
   <http://www.oberlin.edu/~math/faculty/bosch/pbn-page.html> */

/*--------------------------------------------------------------------*/
/* Main part based on the formulation proposed by Robert Bosch. */

param m, integer, >= 1;
/* the number of rows */

param n, integer, >= 1;
/* the number of columns */

param row{i in 1..m, 1..(n+1) div 2}, integer, >= 0, default 0;
/* the cluster-size sequence for row i (raw data) */

param col{j in 1..n, 1..(m+1) div 2}, integer, >= 0, default 0;
/* the cluster-size sequence for column j (raw data) */

param kr{i in 1..m} := sum{t in 1..(n+1) div 2: row[i,t] > 0} 1;
/* the number of clusters in row i */

param kc{j in 1..n} := sum{t in 1..(m+1) div 2: col[j,t] > 0} 1;
/* the number of clusters in column j */

param sr{i in 1..m, t in 1..kr[i]} := row[i,t], integer, >= 1;
/* the cluster-size sequence for row i */

param sc{j in 1..n, t in 1..kc[j]} := col[j,t], integer, >= 1;
/* the cluster-size sequence for column j */

check{i in 1..m}: sum{t in 1..kr[i]} sr[i,t] <= n - (kr[i] - 1);
/* check that the sum of the cluster sizes in each row is valid */

check{j in 1..n}: sum{t in 1..kc[j]} sc[j,t] <= m - (kc[j] - 1);
/* check that the sum of the cluster sizes in each column is valid */

check: sum{i in 1..m, t in 1..kr[i]} sr[i,t] =
       sum{j in 1..n, t in 1..kc[j]} sc[j,t];
/* check that the sum of the cluster sizes in all rows is equal to the
   sum of the cluster sizes in all columns */

param er{i in 1..m, t in 1..kr[i]} :=
   if t = 1 then 1 else er[i,t-1] + sr[i,t-1] + 1;
/* the smallest value of j such that row i's t-th cluster can be
   placed in row i with its leftmost pixel occupying pixel j */

param lr{i in 1..m, t in 1..kr[i]} :=
   if t = kr[i] then n + 1 - sr[i,t] else lr[i,t+1] - sr[i,t] - 1;
/* the largest value of j such that row i's t-th cluster can be
   placed in row i with its leftmost pixel occupying pixel j */

param ec{j in 1..n, t in 1..kc[j]} :=
   if t = 1 then 1 else ec[j,t-1] + sc[j,t-1] + 1;
/* the smallest value of i such that column j's t-th cluster can be
   placed in column j with its topmost pixel occupying pixel i */

param lc{j in 1..n, t in 1..kc[j]} :=
   if t = kc[j] then m + 1 - sc[j,t] else lc[j,t+1] - sc[j,t] - 1;
/* the largest value of i such that column j's t-th cluster can be
   placed in column j with its topmost pixel occupying pixel i */

var z{i in 1..m, j in 1..n}, binary;
/* z[i,j] = 1, if row i's j-th pixel is painted black
   z[i,j] = 0, if row i's j-th pixel is painted white */

var y{i in 1..m, t in 1..kr[i], j in er[i,t]..lr[i,t]}, binary;
/* y[i,t,j] = 1, if row i's t-th cluster is placed in row i with its
                 leftmost pixel occupying pixel j
   y[i,t,j] = 0, if not */

var x{j in 1..n, t in 1..kc[j], i in ec[j,t]..lc[j,t]}, binary;
/* x[j,t,i] = 1, if column j's t-th cluster is placed in column j with
                 its topmost pixel occupying pixel i
   x[j,t,i] = 0, if not */

s.t. fa{i in 1..m, t in 1..kr[i]}:
     sum{j in er[i,t]..lr[i,t]} y[i,t,j] = 1;
/* row i's t-th cluster must appear in row i exactly once */

s.t. fb{i in 1..m, t in 1..kr[i]-1, j in er[i,t]..lr[i,t]}:
     y[i,t,j] <= sum{jp in j+sr[i,t]+1..lr[i,t+1]} y[i,t+1,jp];
/* row i's (t+1)-th cluster must be placed to the right of its t-th
   cluster */

s.t. fc{j in 1..n, t in 1..kc[j]}:
     sum{i in ec[j,t]..lc[j,t]} x[j,t,i] = 1;
/* column j's t-th cluster must appear in column j exactly once */

s.t. fd{j in 1..n, t in 1..kc[j]-1, i in ec[j,t]..lc[j,t]}:
     x[j,t,i] <= sum{ip in i+sc[j,t]+1..lc[j,t+1]} x[j,t+1,ip];
/* column j's (t+1)-th cluster must be placed below its t-th cluster */

s.t. fe{i in 1..m, j in 1..n}:
     z[i,j] <= sum{t in 1..kr[i], jp in er[i,t]..lr[i,t]:
                   j-sr[i,t]+1 <= jp and jp <= j} y[i,t,jp];
/* the double coverage constraint stating that if row i's j-th pixel
   is painted black, then at least one of row i's clusters must be
   placed in such a way that it covers row i's j-th pixel */

s.t. ff{i in 1..m, j in 1..n}:
     z[i,j] <= sum{t in 1..kc[j], ip in ec[j,t]..lc[j,t]:
                   i-sc[j,t]+1 <= ip and ip <= i} x[j,t,ip];
/* the double coverage constraint making sure that if row i's j-th
   pixel is painted black, then at least one of column j's clusters
   covers it */

s.t. fg{i in 1..m, j in 1..n, t in 1..kr[i], jp in er[i,t]..lr[i,t]:
     j-sr[i,t]+1 <= jp and jp <= j}: z[i,j] >= y[i,t,jp];
/* the constraint to prevent white pixels from being covered by the
   row clusters */

s.t. fh{i in 1..m, j in 1..n, t in 1..kc[j], ip in ec[j,t]..lc[j,t]:
     i-sc[j,t]+1 <= ip and ip <= i}: z[i,j] >= x[j,t,ip];
/* the constraint to prevent white pixels from being covered by the
   column clusters */

/* this is a feasibility problem, so no objective is needed */

/*--------------------------------------------------------------------*/
/* The following part is used only to check for multiple solutions. */

param zz{i in 1..m, j in 1..n}, binary, default 0;
/* zz[i,j] is z[i,j] for a previously found solution */

s.t. fz{1..1 : sum{i in 1..m, j in 1..n} zz[i,j] > 0}:
     sum{i in 1..m, j in 1..n}
         (if zz[i,j] then (1 - z[i,j]) else z[i,j]) >= 1;
/* the constraint to forbid finding a solution, which is identical to
   the previously found one; this constraint is included in the model
   only if the previously found solution specified by the parameter zz
   is provided in the data section */

solve;

/*--------------------------------------------------------------------*/
/* Print solution to the standard output. */

for {i in 1..m}
{  printf{j in 1..n} " %s", if z[i,j] then "#" else ".";
   printf "\n";
}

/*--------------------------------------------------------------------*/
/* Write solution to a text file in PostScript format. */

param ps, symbolic, default "solution.ps";

printf "%%!PS-Adobe-3.0\n" > ps;
printf "%%%%Creator: GLPK (pbn.mod)\n" >> ps;
printf "%%%%BoundingBox: 0 0 %d %d\n",
       6 * (n + 2), 6 * (m + 2) >> ps;
printf "%%%%EndComments\n" >> ps;
printf "<</PageSize [%d %d]>> setpagedevice\n",
       6 * (n + 2), 6 * (m + 2) >> ps;
printf "0.1 setlinewidth\n" >> ps;
printf "/A { 2 copy 2 copy 2 copy newpath moveto exch 6 add exch line" &
       "to\n" >> ps;
printf "exch 6 add exch 6 add lineto 6 add lineto closepath } bind de" &
       "f\n" >> ps;
printf "/W { A stroke } def\n" >> ps;
printf "/B { A fill } def\n" >> ps;
printf {i in 1..m, j in 1..n} "%d %d %s\n",
       (j - 1) * 6 + 6, (m - i) * 6 + 6,
       if z[i,j] then "B" else "W" >> ps;
printf "%%%%EOF\n" >> ps;

printf "Solution has been written to file %s\n", ps;

/*--------------------------------------------------------------------*/
/* Write solution to a text file in the form of MathProg data section,
   which can be used later to check for multiple solutions. */

param dat, symbolic, default "solution.dat";

printf "data;\n" > dat;
printf "\n" >> dat;
printf "param zz :" >> dat;
printf {j in 1..n} " %d", j >> dat;
printf " :=\n" >> dat;
for {i in 1..m}
{  printf " %2d", i >> dat;
   printf {j in 1..n} " %s", if z[i,j] then "1" else "." >> dat;
   printf "\n" >> dat;
}
printf ";\n" >> dat;
printf "\n" >> dat;
printf "end;\n" >> dat;

printf "Solution has also been written to file %s\n", dat;

/*--------------------------------------------------------------------*/
/* The following data correspond to the example above. */

data;

param m := 10;

param n := 10;

param row : 1  2  3  :=
      1     3  6  .
      2     1  4  .
      3     1  1  3
      4     2  .  .
      5     3  3  .
      6     1  4  .
      7     2  5  .
      8     2  5  .
      9     1  1  .
      10    3  .  .
;

param col : 1  2  3  4  :=
      1     2  3  .  .
      2     1  2  .  .
      3     1  1  1  1
      4     1  2  .  .
      5     1  1  1  1
      6     1  2  .  .
      7     2  3  .  .
      8     3  4  .  .
      9     8  .  .  .
      10    9  .  .  .
;

end;

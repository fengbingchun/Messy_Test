# A TRANSPORTATION PROBLEM
#
# This problem finds a least cost shipping schedule that meets
# requirements at markets and supplies at factories.
#
#  References:
#              Dantzig G B, "Linear Programming and Extensions."
#              Princeton University Press, Princeton, New Jersey, 1963,
#              Chapter 3-3.

set I;
/* canning plants */

param a{i in I};
/* capacity of plant i in cases */

table plants IN "ODBC"
  'DRIVER={Microsoft Access Driver (*.mdb)};dbq=glpk.mdb'
  'SELECT PLANT, CAPA AS CAPACITY'
  'FROM transp_capa' :
   I <- [ PLANT ], a ~ CAPACITY;

set J;
/* markets */

param b{j in J};
/* demand at market j in cases */

table markets IN "ODBC"
  'DRIVER={Microsoft Access Driver (*.mdb)};dbq=glpk.mdb'
  'transp_demand' :
  J <- [ MARKET ], b ~ DEMAND;

param d{i in I, j in J};
/* distance in thousands of miles */

table dist IN "iODBC"
  'DSN=glpk;UID=glpk;PWD=gnu'
  'transp_dist' :
  [ LOC1, LOC2 ], d ~ DIST;

param f;
/* freight in dollars per case per thousand miles */

param c{i in I, j in J} := f * d[i,j] / 1000;
/* transport cost in thousands of dollars per case */

var x{i in I, j in J} >= 0;
/* shipment quantities in cases */

minimize cost: sum{i in I, j in J} c[i,j] * x[i,j];
/* total transportation costs in thousands of dollars */

s.t. supply{i in I}: sum{j in J} x[i,j] <= a[i];
/* observe supply limit at plant i */

s.t. demand{j in J}: sum{i in I} x[i,j] >= b[j];
/* satisfy demand at market j */

solve;

table result{i in I, j in J: x[i,j]} OUT "ODBC"
  'DRIVER={Microsoft Access Driver (*.mdb)};dbq=glpk.mdb'
  'DELETE FROM transp_result;'
  'INSERT INTO transp_result VALUES (?,?,?)' :
  i ~ LOC1, j ~ LOC2, x[i,j] ~ QUANTITY;

data;

param f := 90;

end;

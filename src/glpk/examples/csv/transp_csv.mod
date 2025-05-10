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

set J;
/* markets */

set K dimen 2;
/* transportation lane */

set L;
/* parameters */

param a{i in I};
/* capacity of plant i in cases */

param b{j in J};
/* demand at market j in cases */

param d{i in I, j in J};
/* distance in thousands of miles */

param e{l in L};
/* parameters */

param f;
/* freight in dollars per case per thousand miles */

table tab_plant IN "CSV" "plants.csv" :
  I <- [plant], a ~ capacity;

table tab_market IN "CSV" "markets.csv" :
  J <- [market], b ~ demand;

table tab_distance IN "CSV" "distances.csv" :
  K <- [plant, market], d ~ distance;

table tab_parameter IN "CSV" "parameters.csv" :
  L <- [parameter], e ~ value ;

param c{i in I, j in J} := e['transport cost'] * d[i,j] / 1000;
/* transport cost in thousands of dollars per case */

var x{(i,j) in K} >= 0;
/* shipment quantities in cases */

minimize cost: sum{(i,j) in K} c[i,j] * x[i,j];
/* total transportation costs in thousands of dollars */

s.t. supply{i in I}: sum{(i,j) in K} x[i,j] <= a[i];
/* observe supply limit at plant i */

s.t. demand{j in J}: sum{(i,j) in K} x[i,j] >= b[j];
/* satisfy demand at market j */

solve;

table tab_result{(i,j) in K} OUT "CSV" "result.csv" :
  i ~ plant, j ~ market, x[i,j] ~ shipment;

end;

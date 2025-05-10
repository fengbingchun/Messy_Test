/*Extended Yet Another Curve Fitting Solution (The poor man's RMA)

  An extension of yacfs.mod adding a Weight parameter:
    When set to 1 the model produces best fit by least squares with all error in y and none in x (YonX);
    When set to zero the model produces best fit by least squares with all error in x and none in y (XonY);
    When set to 0.5 the model assumes equal error in x and y producing results similar to fitting by Reduced Major Axis Analysis.

  Nigel_Galloway@operamail.com
  November 5th., 2009
*/
set Sample;
param Sx {z in Sample};
param Sy {z in Sample};
param Weight := 0.5;

var a;
var b;
var p;
var q;

XonY1 :sum{z in Sample} q*Sy[z]*Sy[z] + sum{z in Sample} p*Sy[z] = sum{z in Sample} Sy[z]*Sx[z];
XonY2 :sum{z in Sample} q*Sy[z] + sum{z in Sample} p = sum{z in Sample} Sx[z];
YonX1 :sum{z in Sample} a*Sx[z]*Sx[z] + sum{z in Sample} b*Sx[z] = sum{z in Sample} Sy[z]*Sx[z];
YonX2 :sum{z in Sample} a*Sx[z] + sum{z in Sample} b = sum{z in Sample} Sy[z];

solve;

param W := Weight*a + (1-Weight)*(1/q);
printf "\nbest linear fit is:\n\ty = %f %s %fx\n\n", b*Weight - (1-Weight)*(p/q), if W < 0 then "-" else "+", abs(W);

data;

param:
Sample:   Sx    Sy :=
  1         0    1
  2       0.5  0.9
  3         1  0.7
  4       1.5  1.5
  5       1.9    2
  6       2.5  2.4
  7         3  3.2
  8       3.5    2
  9         4  2.7
 10       4.5  3.5
 11         5    1
 12       5.5    4
 13         6  3.6
 14       6.6  2.7
 15         7  5.7
 16       7.6  4.6
 17       8.5    6
 18         9  6.8
 19        10  7.3
;

end;

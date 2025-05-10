/*Curve fitting problem by Least Squares
  Nigel_Galloway@operamail.com
  October 1st., 2007
*/
set Sample;
param Sx {z in Sample};
param Sy {z in Sample};

var X;
var Y;
var Ex{z in Sample};
var Ey{z in Sample};

/* sum of variances is zero for Sx*/
variencesX{z in Sample}: X + Ex[z] = Sx[z];
zumVariancesX: sum{z in Sample} Ex[z] = 0;
/* sum of variances is zero for Sy*/
variencesY{z in Sample}: Y + Ey[z] = Sy[z];
zumVariancesY: sum{z in Sample} Ey[z] = 0;

solve;

param b1 := (sum{z in Sample} Ex[z]*Ey[z])/(sum{z in Sample} Ex[z]*Ex[z]);
printf "\nbest linear fit is:\n\ty = %f %s %fx\n\n", Y-b1*X, if b1 < 0 then "-" else "+", abs(b1);

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

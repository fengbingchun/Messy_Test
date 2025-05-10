/* graph.mod - graph visualization */

/* Written in GNU MathProg by Andrew Makhorin <mao@gnu.org> */

/* This model creates a picture in EPS format to visualize a graph. */

param file, symbolic, default "graph.eps";
/* output file to write the picture */

param R, default 2;
/* radius to draw vertices, in mm */

param n, integer, > 0;
/* number of vertices */

set V, default 1..n;
/* set of vertices */

set E, within V cross V;
/* set of edges */

param x{i in V}, default 50 * cos((i - 1) / card(V) * 8 * atan(1));
param y{i in V}, default 50 * sin((i - 1) / card(V) * 8 * atan(1));
/* x[i] and y[i] are coordinates of node i, in mm */

param x0 := (min{i in V} x[i]) - R - 3.0;
param y0 := (min{i in V} y[i]) - R - 3.0;
param x1 := (max{i in V} x[i]) + R + 3.0;
param y1 := (max{i in V} y[i]) + R + 3.0;

printf "%%!PS-Adobe-3.0 EPSF-3.0\n" > file;
printf "%%%%BoundingBox: 0 0 %d %d\n",
      (72 / 25.4) * (x1 - x0), (72 / 25.4) * (y1 - y0) >> file;
printf "/Helvetica findfont 6 scalefont setfont\n" >> file;
printf "/mm { 72 mul 25.4 div } def\n" >> file;

for {(i,j) in E}
{     printf "newpath\n" >> file;
      printf "%g mm %g mm moveto\n", x[i] - x0, y[i] - y0 >> file;
      printf "%g mm %g mm lineto\n", x[j] - x0, y[j] - y0 >> file;
      printf "closepath\n" >> file;
      printf "stroke\n" >> file;
}

for {i in V}
{     printf "newpath\n" >> file;
      printf "%g mm %g mm %g mm 0 360 arc\n",
         x[i] - x0, y[i] - y0, R >> file;
      printf "closepath\n" >> file;
      printf "gsave 1 1 1 setrgbcolor fill grestore\n" >> file;
      printf "stroke\n" >> file;
      printf "%g mm %g mm moveto\n",
         x[i] - (if i <= 9 then 1.2 else 1.8) - x0,
         y[i] - 0.8 - y0 >> file;
      printf "( %d ) show\n", i >> file;
}

printf "showpage\n" >> file;
printf "%%%%EOF\n" >> file;

data;

param
:  V  :  x     y :=
   1     0    40
   2    38    12
   3    24   -32
   4   -24   -32
   5   -38    12
   6   -19    26
   7    19    26
   8    31   -10
   9     0   -32
  10   -31   -10
  11    -9    12
  12     9    12
  13    14    -5
  14     0   -15
  15   -14    -5
  16     0     0 ;

set E :=
   (1,*)  6 10 16 12  7
   (2,*)  7  6 16 13  8
   (3,*)  8  7 16 14  9
   (4,*)  9  8 16 15 10
   (5,*) 10  9 16 11  6
   (6,*) 14
   (7,*) 15
   (8,*) 11
   (9,*) 12
  (10,*) 13
  (11,*) 12 15
  (12,*) 13
  (13,*) 14
  (14,*) 15 ;

end;

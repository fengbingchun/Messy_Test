
/* This example shows how to access an Excel files via ODBC from
   GLPK. The connection string is depending on the version of the
   ODBC driver.

   Microsoft Office 2000:
   Microsoft Access-Treiber (*.mdb)

   Microsoft Office 2007:
   Microsoft Access Driver (*.mdb, *.accdb)

   Please adjust the table statements accordingly */

/* SUDOKU, Number Placement Puzzle */

/* Written in GNU MathProg by Andrew Makhorin <mao@mai2.rcnet.ru> */

/* This example shows how to use the table statement.
   The sudoku to be solves is read from file sudoku_in.csv.
   The solution is written to sudoku_out.csv.
   The file format is CSV as defined in
     RFC 4180 - Common Format and MIME Type for
     Comma-Separated Values (CSV) Files */

/* Sudoku, also known as Number Place, is a logic-based placement
   puzzle. The aim of the canonical puzzle is to enter a numerical
   digit from 1 through 9 in each cell of a 9x9 grid made up of 3x3
   subgrids (called "regions"), starting with various digits given in
   some cells (the "givens"). Each row, column, and region must contain
   only one instance of each numeral.

   Example:

   +-------+-------+-------+
   | 5 3 . | . 7 . | . . . |
   | 6 . . | 1 9 5 | . . . |
   | . 9 8 | . . . | . 6 . |
   +-------+-------+-------+
   | 8 . . | . 6 . | . . 3 |
   | 4 . . | 8 . 3 | . . 1 |
   | 7 . . | . 2 . | . . 6 |
   +-------+-------+-------+
   | . 6 . | . . . | 2 8 . |
   | . . . | 4 1 9 | . . 5 |
   | . . . | . 8 . | . 7 9 |
   +-------+-------+-------+

   (From Wikipedia, the free encyclopedia.) */
set fields dimen 2;

param id;

param givens{1..9, 1..9}, integer, >= 0, <= 9, default 0;
/* the "givens" */

table ti IN 'ODBC'
  'DRIVER={Microsoft Access Driver (*.mdb)};dbq=glpk.mdb'
  'SELECT * FROM sudoku'
  'WHERE ID = ' & id :
  fields <- [COL, LIN], givens ~ VAL;

var x{i in 1..9, j in 1..9, k in 1..9}, binary;
/* x[i,j,k] = 1 means cell [i,j] is assigned number k */

s.t. fa{i in 1..9, j in 1..9, k in 1..9: givens[i,j] != 0}:
     x[i,j,k] = (if givens[i,j] = k then 1 else 0);
/* assign pre-defined numbers using the "givens" */

s.t. fb{i in 1..9, j in 1..9}: sum{k in 1..9} x[i,j,k] = 1;
/* each cell must be assigned exactly one number */

s.t. fc{i in 1..9, k in 1..9}: sum{j in 1..9} x[i,j,k] = 1;
/* cells in the same row must be assigned distinct numbers */

s.t. fd{j in 1..9, k in 1..9}: sum{i in 1..9} x[i,j,k] = 1;
/* cells in the same column must be assigned distinct numbers */

s.t. fe{I in 1..9 by 3, J in 1..9 by 3, k in 1..9}:
     sum{i in I..I+2, j in J..J+2} x[i,j,k] = 1;
/* cells in the same region must be assigned distinct numbers */

/* there is no need for an objective function here */


solve;

table ta {(i, j) in {i1 in 1..9} cross {i2 in 1..9}} OUT 'ODBC'
  'DRIVER={Microsoft Access Driver (*.mdb)};dbq=glpk.mdb'
  'DELETE FROM sudoku_solution'
  'WHERE ID = ' & id & ';'
  'INSERT INTO sudoku_solution'
  '(ID, COL, LIN, VAL)'
  'VALUES(?, ?, ?, ?);' :
  id ~ ID, i ~ COL, j ~ LIN, (sum{k in 1..9} x[i,j,k] * k) ~ VAL;

printf "\nSudoku to be solved\n";
for {i in 1..9}
{  for {0..0: i = 1 or i = 4 or i = 7}
     printf " +-------+-------+-------+\n";
   for {j in 1..9}
   {  for {0..0: j = 1 or j = 4 or j = 7} printf(" |");
      printf " %d", givens[i,j];
      for {0..0: j = 9} printf(" |\n");
   }
   for {0..0: i = 9}
   printf " +-------+-------+-------+\n";
   }
printf "\nSolution\n";
for {i in 1..9}
{  for {0..0: i = 1 or i = 4 or i = 7}
      printf " +-------+-------+-------+\n";
   for {j in 1..9}
   {  for {0..0: j = 1 or j = 4 or j = 7} printf(" |");
      printf " %d", sum{k in 1..9} x[i,j,k] * k;
      for {0..0: j = 9} printf(" |\n");
   }
   for {0..0: i = 9}
      printf " +-------+-------+-------+\n";
}

data;

param id := 1;
end;

/* File: shiftcover.mod */

/* WORKFORCE SHIFT COVERAGE assignment problem */

/* Written by Larry D'Agostino <larrydag -at- sbcglobal -dot- com>
     
     Maximize Productivity with Industrial Engineer and Operations Research Tools
     http://industrialengineertools.blogspot.com


/* The WORKFORCE SHIFT COVERAGE is an assigment problem that determines
   the schedule of crew given available time and shifts.  
   
   The objective is to cover the available time given hourly demand with the minimum 
    number of crew members.
   
    This is a set covering problem that is very common among finding crew
     and shift allocations.  Notice in the data section the workforce shift allocation
     per day of the week.*/


/* ----- Model PARAMTERS and SETS -----*/

param numhrs;
/* number of hours of operations in a given day */

param dys;
/* number of days in a week */

set S;
/* set of crew shifts */

set H := 1..numhrs;
/* set of hours of a day*/

set D;
/* set of days of a week*/

param dmnd{h in H, d in D};
/* demand for crew members given h hour and d day */

param shifts{d in D, h in H, s in S};
/* shifts to assign to crew members given d day, h hour, and s shift schedule

/*----- Model VARIABLES -----*/

var crew{s in S}, integer, >=0;
/*  number of crew assigned to shift S */


/*----- Model CONSTRAINTS -----*/

s.t. Coverage{h in H, d in D}: sum{s in S} crew[s]*shifts[d,h,s] >= dmnd[h,d];
/* number of crew to cover with a shift  given hourly demand and day */


/*----- Model OBJECTIVE -----*/

minimize obj: sum{s in S} crew[s];
/* minimize number of crew to cover demand*/

solve;
display crew;

printf "\n";
printf "Total Crew: %3d\n\n", sum{s in S} crew[s];



printf "\n\n";
printf "Weekly Crew Schedule\n\n";
printf "Hour ";
printf{d in D} "  %s  ", d;
printf "\n";
for {h in H} {
  printf " %2s  ",h;
  printf{d in D} " %3d   ", sum{s in S} crew[s]*shifts[d,h,s];
  printf "\n";
}
printf"\n";



data;

param numhrs := 16;

set D := SUN, MON, TUE, WED, THU, FRI, SAT;

set S := Sh1, Sh2, Sh3, Sh4, Sh5, Sh6, Sh7, Sh8, Sh9;

param dmnd :   SUN  MON     TUE     WED     THU     FRI     SAT :=
1               0   3       3       4       3       2       0
2               0   14      14      16      14      12      12
3               0   24      24      27      24      20      15
4               0   28      28      32      28      23      15
5               0   33      33      37      33      24      16
6               0   34      34      38      34      24      15
7               0   35      35      39      35      25      11
8               0   35      35      40      35      27      0
9               0   34      34      39      34      25      0
10              0   31      31      35      31      24      0
11              2   24      24      27      24      25      0
12              3   19      19      21      19      21      0
13              2   24      24      27      24      13      0
14              2   16      16      18      16      0       0
15              0   7       7       7       7       0       0
16              0   5       5       5       5       0       0;


param shifts := 
['SUN',*,*]:
                   Sh1  Sh2  Sh3  Sh4  Sh5  Sh6  Sh7  Sh8  Sh9 :=
1                   0    0    0    0    0    0    0    0    0
2                   0    0    0    0    0    0    0    0    0
3                   0    0    0    0    0    0    0    0    0
4                   0    0    0    0    0    0    0    0    0
5                   0    0    0    0    0    0    0    0    0
6                   0    0    0    0    0    0    0    0    0
7                   0    0    0    0    0    0    0    0    0
8                   0    0    0    0    0    0    0    0    0
9                   0    0    0    0    0    0    0    0    0
10                  0    0    0    0    0    0    0    0    0
11                  0    0    0    0    0    0    0    0    1
12                  0    0    0    0    0    0    0    0    1
13                  0    0    0    0    0    0    0    0    1
14                  0    0    0    0    0    0    0    0    1
15                  0    0    0    0    0    0    0    0    0
16                  0    0    0    0    0    0    0    0    0


['MON',*,*]:
                   Sh1  Sh2  Sh3  Sh4  Sh5  Sh6  Sh7  Sh8  Sh9 :=
1                   1    0    0    0    0    0    0    0    0
2                   1    1    0    0    0    0    0    0    0
3                   1    1    1    0    0    0    0    0    0
4                   1    1    1    1    0    0    0    0    0
5                   0    1    1    1    1    0    0    0    0
6                   1    0    1    1    1    1    0    0    1
7                   1    1    0    1    1    1    1    0    1
8                   1    1    1    0    1    1    1    1    1
9                   1    1    1    1    0    1    1    1    1
10                  0    1    1    1    1    0    1    1    1
11                  0    0    1    1    1    1    0    1    0
12                  0    0    0    1    1    1    1    0    1
13                  0    0    0    0    1    1    1    1    1
14                  0    0    0    0    0    1    1    1    1
15                  0    0    0    0    0    0    1    1    1
16                  0    0    0    0    0    0    0    1    1

['TUE',*,*]:
                   Sh1  Sh2  Sh3  Sh4  Sh5  Sh6  Sh7  Sh8  Sh9 :=
1                   1    0    0    0    0    0    0    0    0
2                   1    1    0    0    0    0    0    0    0
3                   1    1    1    0    0    0    0    0    0
4                   1    1    1    1    0    0    0    0    0
5                   0    1    1    1    1    0    0    0    0
6                   1    0    1    1    1    1    0    0    1
7                   1    1    0    1    1    1    1    0    1
8                   1    1    1    0    1    1    1    1    1
9                   1    1    1    1    0    1    1    1    1
10                  0    1    1    1    1    0    1    1    1
11                  0    0    1    1    1    1    0    1    0
12                  0    0    0    1    1    1    1    0    1
13                  0    0    0    0    1    1    1    1    1
14                  0    0    0    0    0    1    1    1    1
15                  0    0    0    0    0    0    1    1    1
16                  0    0    0    0    0    0    0    1    1

['WED',*,*]:
                   Sh1  Sh2  Sh3  Sh4  Sh5  Sh6  Sh7  Sh8  Sh9 :=
1                   1    0    0    0    0    0    0    0    0
2                   1    1    0    0    0    0    0    0    0
3                   1    1    1    0    0    0    0    0    0
4                   1    1    1    1    0    0    0    0    0
5                   0    1    1    1    1    0    0    0    0
6                   1    0    1    1    1    1    0    0    1
7                   1    1    0    1    1    1    1    0    1
8                   1    1    1    0    1    1    1    1    1
9                   1    1    1    1    0    1    1    1    1
10                  0    1    1    1    1    0    1    1    1
11                  0    0    1    1    1    1    0    1    0
12                  0    0    0    1    1    1    1    0    1
13                  0    0    0    0    1    1    1    1    1
14                  0    0    0    0    0    1    1    1    1
15                  0    0    0    0    0    0    1    1    1
16                  0    0    0    0    0    0    0    1    1

['THU',*,*]:
                   Sh1  Sh2  Sh3  Sh4  Sh5  Sh6  Sh7  Sh8  Sh9 :=
1                   1    0    0    0    0    0    0    0    0
2                   1    1    0    0    0    0    0    0    0
3                   1    1    1    0    0    0    0    0    0
4                   1    1    1    1    0    0    0    0    0
5                   0    1    1    1    1    0    0    0    0
6                   1    0    1    1    1    1    0    0    0
7                   1    1    0    1    1    1    1    0    0
8                   1    1    1    0    1    1    1    1    0
9                   1    1    1    1    0    1    1    1    0
10                  0    1    1    1    1    0    1    1    0
11                  0    0    1    1    1    1    0    1    0
12                  0    0    0    1    1    1    1    0    0
13                  0    0    0    0    1    1    1    1    0
14                  0    0    0    0    0    1    1    1    0
15                  0    0    0    0    0    0    1    1    0
16                  0    0    0    0    0    0    0    1    0

['FRI',*,*]:
                   Sh1  Sh2  Sh3  Sh4  Sh5  Sh6  Sh7  Sh8  Sh9 :=
1                   1    0    0    0    0    0    0    0    0
2                   1    1    0    0    0    0    0    0    0
3                   1    1    1    0    0    0    0    0    0
4                   1    1    1    1    0    0    0    0    0
5                   0    1    1    1    1    0    0    0    0
6                   1    0    1    1    1    1    0    0    0
7                   1    1    0    1    1    1    1    0    0
8                   1    1    1    0    1    1    1    1    0
9                   1    1    1    1    0    1    1    1    0
10                  0    1    1    1    1    0    1    1    0
11                  0    0    1    1    1    1    0    1    0
12                  0    0    0    1    1    1    1    0    0
13                  0    0    0    0    1    1    1    1    0
14                  0    0    0    0    0    1    1    1    0
15                  0    0    0    0    0    0    1    1    0
16                  0    0    0    0    0    0    0    1    0

['SAT',*,*]:
                   Sh1  Sh2  Sh3  Sh4  Sh5  Sh6  Sh7  Sh8  Sh9 :=
1                   0    0    0    0    0    0    0    0    0
2                   0    0    0    0    0    0    0    0    1
3                   0    0    0    0    0    0    0    0    1
4                   0    0    0    0    0    0    0    0    1
5                   0    0    0    0    0    0    0    0    1
6                   0    0    0    0    0    0    0    0    1
7                   0    0    0    0    0    0    0    0    1
8                   0    0    0    0    0    0    0    0    0
9                   0    0    0    0    0    0    0    0    0
10                  0    0    0    0    0    0    0    0    0
11                  0    0    0    0    0    0    0    0    0
12                  0    0    0    0    0    0    0    0    0
13                  0    0    0    0    0    0    0    0    0
14                  0    0    0    0    0    0    0    0    0
15                  0    0    0    0    0    0    0    0    0
16                  0    0    0    0    0    0    0    0    0;

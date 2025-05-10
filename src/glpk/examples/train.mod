# TRAIN, a model of railroad passenger car allocation
#
# References:
# Robert Fourer, David M. Gay and Brian W. Kernighan, "A Modeling Language
# for Mathematical Programming." Management Science 36 (1990) 519-554.

###  SCHEDULE SETS AND PARAMETERS  ###

set cities;

set links within {c1 in cities, c2 in cities: c1 <> c2};

                        # Set of cities, and set of intercity links

param last > 0 integer; # Number of time intervals in a day

set times := 1..last;   # Set of time intervals in a day

set schedule within
      {c1 in cities, t1 in times,
       c2 in cities, t2 in times: (c1,c2) in links};

                        # Member (c1,t1,c2,t2) of this set represents
                        # a train that leaves city c1 at time t1
                        # and arrives in city c2 at time t2

###  DEMAND PARAMETERS  ###

param section > 0 integer;

                        # Maximum number of cars in one section of a train

param demand {schedule} > 0;

                        # For each scheduled train:
                        # the smallest number of cars that
                        # can meet demand for the train

param low {(c1,t1,c2,t2) in schedule} := ceil(demand[c1,t1,c2,t2]);

                        # Minimum number of cars needed to meet demand

param high {(c1,t1,c2,t2) in schedule}

   := max (2, min (ceil(2*demand[c1,t1,c2,t2]),
                   section*ceil(demand[c1,t1,c2,t2]/section) ));

                        # Maximum number of cars allowed on a train:
                        # 2 if demand is for less than one car;
                        # otherwise, lesser of
                        # number of cars needed to hold twice the demand, and
                        # number of cars in minimum number of sections needed

###  DISTANCE PARAMETERS  ###

param dist_table {links} >= 0 default 0.0;

param distance {(c1,c2) in links} > 0
   := if dist_table[c1,c2] > 0 then dist_table[c1,c2] else dist_table[c2,c1];

                        # Inter-city distances: distance[c1,c2] is miles
                        # between city c1 and city c2

###  VARIABLES  ###

var U 'cars stored' {cities,times} >= 0;

                        # u[c,t] is the number of unused cars stored
                        # at city c in the interval beginning at time t

var X 'cars in train' {schedule} >= 0;

                        # x[c1,t1,c2,t2] is the number of cars assigned to
                        # the scheduled train that leaves c1 at t1 and
                        # arrives in c2 at t2

###  OBJECTIVES  ###

minimize cars:
       sum {c in cities} U[c,last] +
       sum {(c1,t1,c2,t2) in schedule: t2 < t1} X[c1,t1,c2,t2];

                        # Number of cars in the system:
                        # sum of unused cars and cars in trains during
                        # the last time interval of the day

minimize miles:
       sum {(c1,t1,c2,t2) in schedule} distance[c1,c2] * X[c1,t1,c2,t2];

                        # Total car-miles run by all scheduled trains in a day

###  CONSTRAINTS  ###

account {c in cities, t in times}:

  U[c,t] = U[c, if t > 1 then t-1 else last] +

      sum {(c1,t1,c,t) in schedule} X[c1,t1,c,t] -
      sum {(c,t,c2,t2) in schedule} X[c,t,c2,t2];

                        # For every city and time:
                        # unused cars in the present interval must equal
                        # unused cars in the previous interval,
                        # plus cars just arriving in trains,
                        # minus cars just leaving in trains

satisfy {(c1,t1,c2,t2) in schedule}:

       low[c1,t1,c2,t2] <= X[c1,t1,c2,t2] <= high[c1,t1,c2,t2];

                        # For each scheduled train:
                        # number of cars must meet demand,
                        # but must not be so great that unnecessary
                        # sections are run

###  DATA  ###

data;

set cities := BO NY PH WA ;

set links := (BO,NY) (NY,PH) (PH,WA)
             (NY,BO) (PH,NY) (WA,PH) ;

param dist_table := [*,*]  BO NY  232
                           NY PH   90
                           PH WA  135 ;

param last := 48 ;

param section := 14 ;

set schedule :=

   (WA,*,PH,*)   2  5     6  9     8 11    10 13
                12 15    13 16    14 17    15 18
                16 19    17 20    18 21    19 22
                20 23    21 24    22 25    23 26
                24 27    25 28    26 29    27 30
                28 31    29 32    30 33    31 34
                32 35    33 36    34 37    35 38
                36 39    37 40    38 41    39 42
                40 43    41 44    42 45    44 47
                46  1

   (PH,*,NY,*)   1  3     5  7     9 11    11 13
                13 15    14 16    15 17    16 18
                17 19    18 20    19 21    20 22
                21 23    22 24    23 25    24 26
                25 27    26 28    27 29    28 30
                29 31    30 32    31 33    32 34
                33 35    34 36    35 37    36 38
                37 39    38 40    39 41    40 42
                41 43    42 44    43 45    44 46
                45 47    47  1

   (NY,*,BO,*)  10 16    12 18    14 20    15 21
                16 22    17 23    18 24    19 25
                20 26    21 27    22 28    23 29
                24 30    25 31    26 32    27 33
                28 34    29 35    30 36    31 37
                32 38    33 39    34 40    35 41
                36 42    37 43    38 44    39 45
                40 46    41 47    42 48    43  1
                44  2    45  3    46  4    48  6

   (BO,*,NY,*)   7 13     9 15    11 17    12 18
                13 19    14 20    15 21    16 22
                17 23    18 24    19 25    20 26
                21 27    22 28    23 29    24 30
                25 31    26 32    27 33    28 34
                29 35    30 36    31 37    32 38
                33 39    34 40    35 41    36 42
                37 43    38 44    39 45    40 46
                41 47    43  1    45  3    47  5

   (NY,*,PH,*)   1  3    12 14    13 15    14 16
                15 17    16 18    17 19    18 20
                19 21    20 22    21 23    22 24
                23 25    24 26    25 27    26 28
                27 29    28 30    29 31    30 32
                31 33    32 34    33 35    34 36
                35 37    36 38    37 39    38 40
                39 41    40 42    41 43    42 44
                43 45    44 46    45 47    46 48
                47  1

   (PH,*,WA,*)   1  4    14 17    15 18    16 19
                17 20    18 21    19 22    20 23
                21 24    22 25    23 26    24 27
                25 28    26 29    27 30    28 31
                29 32    30 33    31 34    32 35
                33 36    34 37    35 38    36 39
                37 40    38 41    39 42    40 43
                41 44    42 45    43 46    44 47
                45 48    46  1    47  2    ;

param demand :=

 [WA,*,PH,*]   2  5    .55      6  9    .01      8 11    .01
              10 13    .13     12 15   1.59     13 16   1.69
              14 17   5.19     15 18   3.55     16 19   6.29
              17 20   4.00     18 21   5.80     19 22   3.40
              20 23   4.88     21 24   2.92     22 25   4.37
              23 26   2.80     24 27   4.23     25 28   2.88
              26 29   4.33     27 30   3.11     28 31   4.64
              29 32   3.44     30 33   4.95     31 34   3.73
              32 35   5.27     33 36   3.77     34 37   4.80
              35 38   3.31     36 39   3.89     37 40   2.65
              38 41   3.01     39 42   2.04     40 43   2.31
              41 44   1.52     42 45   1.75     44 47   1.88
              46  1   1.05

 [PH,*,NY,*]   1  3   1.05      5  7    .43      9 11    .20
              11 13    .21     13 15    .40     14 16   6.49
              15 17  16.40     16 18   9.48     17 19  17.15
              18 20   9.31     19 21  15.20     20 22   8.21
              21 23  13.32     22 24   7.35     23 25  11.83
              24 26   6.61     25 27  10.61     26 28   6.05
              27 29   9.65     28 30   5.61     29 31   9.25
              30 32   5.40     31 33   8.24     32 34   4.84
              33 35   7.44     34 36   4.44     35 37   6.80
              36 38   4.11     37 39   6.25     38 40   3.69
              39 41   5.55     40 42   3.29     41 43   4.77
              42 44   2.91     43 45   4.19     44 46   2.53
              45 47   4.00     47 1    1.65

 [NY,*,BO,*]  10 16   1.23     12 18   3.84     14 20   4.08
              15 21   1.47     16 22   2.96     17 23   1.60
              18 24   2.95     19 25   1.71     20 26   2.81
              21 27   1.77     22 28   2.87     23 29   1.84
              24 30   2.95     25 31   1.91     26 32   3.12
              27 33   1.93     28 34   3.31     29 35   2.00
              30 36   3.40     31 37   2.08     32 38   3.41
              33 39   2.69     34 40   4.45     35 41   2.32
              36 42   3.40     37 43   1.80     38 44   2.63
              39 45   1.52     40 46   2.23     41 47   1.25
              42 48   1.79     43  1    .97     44  2   1.28
              45  3    .48     46  4    .68     48  6    .08

 [BO,*,NY,*]   7 13    .03      9 15   1.29     11 17   4.59
              12 18   2.56     13 19   3.92     14 20   2.37
              15 21   3.81     16 22   2.24     17 23   3.51
              18 24   2.13     19 25   3.28     20 26   2.05
              21 27   3.15     22 28   1.99     23 29   3.09
              24 30   1.93     25 31   3.19     26 32   1.91
              27 33   3.21     28 34   1.85     29 35   3.21
              30 36   1.71     31 37   3.04     32 38   2.08
              33 39   3.13     34 40   1.96     35 41   2.53
              36 42   1.43     37 43   2.04     38 44   1.12
              39 45   1.71     40 46    .91     41 47   1.32
              43  1   1.80     45  3   1.13     47  5    .23

 [NY,*,PH,*]   1  3    .04     12 14   4.68     13 15   5.61
              14 16   3.56     15 17   5.81     16 18   3.81
              17 19   6.31     18 20   4.07     19 21   7.33
              20 22   4.55     21 23   7.37     22 24   4.73
              23 25   7.61     24 26   4.92     25 27   7.91
              26 28   5.19     27 29   8.40     28 30   5.53
              29 31   9.32     30 32   5.51     31 33  10.33
              32 34   9.21     33 35  18.95     34 36  11.23
              35 37  16.85     36 38   7.29     37 39  10.89
              38 40   5.41     39 41   8.21     40 42   4.52
              41 43   6.99     42 44   3.92     43 45   6.21
              44 46   3.44     45 47   5.17     46 48   2.55
              47  1   1.24

 [PH,*,WA,*]   1  4    .20     14 17   4.49     15 18   3.53
              16 19   2.67     17 20   3.83     18 21   3.01
              19 22   4.12     20 23   3.15     21 24   4.67
              22 25   3.20     23 26   4.23     24 27   2.87
              25 28   3.84     26 29   2.60     27 30   3.80
              28 31   2.77     29 32   4.31     30 33   3.16
              31 34   4.88     32 35   3.45     33 36   5.55
              34 37   3.52     35 38   6.11     36 39   3.32
              37 40   5.53     38 41   3.03     39 42   4.51
              40 43   2.53     41 44   3.39     42 45   1.93
              43 46   2.52     44 47   1.20     45 48   1.75
              46  1    .88     47  2    .87     ;

end;

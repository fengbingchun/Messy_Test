# DIST, a product distribution model
#
# References:
# Robert Fourer, David M. Gay and Brian W. Kernighan, "A Modeling Language
# for Mathematical Programming." Management Science 36 (1990) 519-554.

###  SHIPPING SETS AND PARAMETERS  ###

set whse 'warehouses';  # Locations from which demand is satisfied

set dctr 'distribution centers' within whse;

                        # Locations from which product may be shipped

param sc 'shipping cost' {dctr,whse} >= 0;

                        # Shipping costs, to whse from dctr, in $ / 100 lb

param huge 'largest shipping cost' > 0;

                        # Largest cost allowed for a usable shipping route

param msr 'minimum size restriction' {dctr,whse} logical;

                        # True indicates a minimum-size restriction on
                        # direct shipments using this dctr --> whse route

param dsr 'direct shipment requirement' {dctr} >= 0;

                        # Minimum total demand, in pallets, needed to
                        # allow shipment on routes subject to the
                        # minimum size restriction

###  PLANT SETS AND PARAMETERS  ###

set fact 'factories' within dctr;

                        # Locations where product is manufactured

param rtmin 'regular-time total minimum' >= 0;

                        # Lower limit on (average) total regular-time
                        # crews employed at all factories

param rtmax 'regular-time total maximum' >= rtmin;

                        # Upper limit on (average) total regular-time
                        # crews employed at all factories

param otmin 'overtime total minimum' >= 0;

                        # Lower limit on total overtime hours at all factories

param otmax 'overtime total maximum' >= otmin;

                        # Upper limit on total overtime hours at all factories

param rmin 'regular-time minimums' {fact} >= 0;

                        # Lower limits on (average) regular-time crews

param rmax 'regular-time maximums' {f in fact} >= rmin[f];

                        # Upper limits on (average) regular-time crews

param omin 'overtime minimums' {fact} >= 0;

                        # Lower limits on overtime hours

param omax 'overtime maximums' {f in fact} >= omin[f];

                        # Upper limits on overtime hours

param hd 'hours per day' {fact} >= 0;

                        # Regular-time hours per working day

param dp 'days in period' {fact} > 0;

                        # Working days in the current planning period

###  PRODUCT SETS AND PARAMETERS  ###

set prd 'products';     # Elements of the product group

param wt 'weight' {prd} > 0;

                        # Weight in 100 lb / 1000 cases

param cpp 'cases per pallet' {prd} > 0;

                        # Cases of product per shipping pallet

param tc 'transshipment cost' {prd} >= 0;

                        # Transshipment cost in $ / 1000 cases

param pt 'production time' {prd,fact} >= 0;

                        # Crew-hours to produce 1000 cases

param rpc 'regular-time production cost' {prd,fact} >= 0;

                        # Cost of production on regular time,
                        # in $ / 1000 cases

param opc 'overtime production cost' {prd,fact} >= 0;

                        # Cost of production on overtime, in $ / 1000 cases

###  DEMAND SETS AND PARAMETERS  ###

param dt 'total demand' {prd} >= 0;

                        # Total demands for products, in 1000s

param ds 'demand shares' {prd,whse} >= 0.0, <= 1.0;

                        # Historical demand data, from which each
                        # warehouse's share of total demand is deduced

param dstot {p in prd} := sum {w in whse} ds[p,w];

                        # Total of demand shares; should be 1, but often isn't

param dem 'demand' {p in prd, w in whse} := dt[p] * ds[p,w] / dstot[p];

                        # Projected demands to be satisfied, in 1000s

set rt 'shipping routes available' :=

 {d in dctr, w in whse:
         d <> w  and  sc[d,w] < huge  and
         (w in dctr or sum {p in prd} dem[p,w] > 0)  and
         not (msr[d,w] and sum {p in prd} 1000*dem[p,w]/cpp[p] < dsr[d]) };

                        # List of ordered pairs that represent routes
                        # on which shipments are allowed

###  VARIABLES  ###

var Rprd 'regular-time production' {prd,fact} >= 0;

                        # Regular-time production of each product
                        # at each factory, in 1000s of cases

var Oprd 'overtime production' {prd,fact} >= 0;

                        # Overtime production of each product
                        # at each factory, in 1000s of cases

var Ship 'shipments' {prd,rt} >= 0;

                        # Shipments of each product on each allowed route,
                        # in 1000s of cases

var Trans 'transshipments' {prd,dctr} >= 0;

                        # Transshipments of each product at each
                        # distribution center, in 1000s of cases

###  OBJECTIVE  ###

minimize cost:  sum {p in prd, f in fact} rpc[p,f] * Rprd[p,f] +
                sum {p in prd, f in fact} opc[p,f] * Oprd[p,f] +
                sum {p in prd, (d,w) in rt} sc[d,w] * wt[p] * Ship[p,d,w] +
                sum {p in prd, d in dctr} tc[p] * Trans[p,d];

                        # Total cost:  regular production, overtime
                        # production, shipping, and transshipment

###  CONSTRAINTS  ###

rtlim 'regular-time total limits':

    rtmin <= sum {p in prd, f in fact}
                        (pt[p,f] * Rprd[p,f]) / (dp[f] * hd[f]) <= rtmax;

                        # Total crews must lie between limits

otlim 'overtime total limits':

    otmin <= sum {p in prd, f in fact} pt[p,f] * Oprd[p,f] <= otmax;

                        # Total overtime must lie between limits

rlim 'regular-time limits' {f in fact}:

    rmin[f] <= sum {p in prd}
                        (pt[p,f] * Rprd[p,f]) / (dp[f] * hd[f]) <= rmax[f];

                        # Crews at each factory must lie between limits

olim 'overtime limits' {f in fact}:

    omin[f] <= sum {p in prd} pt[p,f] * Oprd[p,f] <= omax[f];

                        # Overtime at each factory must lie between limits

noRprd 'no regular production' {p in prd, f in fact: rpc[p,f] = 0}:

    Rprd[p,f] = 0;

noOprd 'no overtime production' {p in prd, f in fact: opc[p,f] = 0}:

    Oprd[p,f] = 0;      # Do not produce where specified cost is zero

bal 'material balance' {p in prd, w in whse}:

    sum {(v,w) in rt}
       Ship [p,v,w] + (if w in fact then Rprd[p,w] + Oprd[p,w]) =

    dem[p,w] + (if w in dctr then sum {(w,v) in rt} Ship[p,w,v]);

                        # Demand is satisfied by shipment into warehouse
                        # plus production (if it is a factory)
                        # minus shipment out (if it is a distn. center)

trdef 'transshipment definition' {p in prd, d in dctr}:

    Trans[p,d] >= sum {(d,w) in rt} Ship [p,d,w] -
                  (if d in fact then Rprd[p,d] + Oprd[p,d]);

                        # Transshipment at a distribution center is
                        # shipments out less production (if any)

###  DATA -- 3 PRODUCTS  ###

data;

set prd := 18REG 24REG 24PRO ;

set whse := w01 w02 w03 w04 w05 w06 w08 w09 w12 w14 w15 w17
            w18 w19 w20 w21 w24 w25 w26 w27 w28 w29 w30 w31
            w32 w33 w34 w35 w36 w37 w38 w39 w40 w41 w42 w43
            w44 w45 w46 w47 w48 w49 w50 w51 w53 w54 w55 w56
            w57 w59 w60 w61 w62 w63 w64 w65 w66 w68 w69 w71
            w72 w73 w74 w75 w76 w77 w78 w79 w80 w81 w82 w83
            w84 w85 w86 w87 w89 w90 w91 w92 w93 w94 w95 w96
            w98 x22 x23 ;

set dctr := w01 w02 w03 w04 w05 w62 w76 w96 ;

set fact := w01 w05 w96 ;

param huge := 99. ;

param rtmin := 0.0 ;
param rtmax := 8.0 ;

param otmin :=  0.0 ;
param otmax := 96.0 ;

param rmin  :=  w01 0.00   w05 0.00   w96 0.00 ;
param rmax  :=  w01 3.00   w05 2.00   w96 3.00 ;

param omin  :=  w01  0.0   w05  0.0   w96  0.0 ;
param omax  :=  w01 48.0   w05  0.0   w96 48.0 ;

param hd    :=  w01  8.0   w05  8.0   w96  8.0 ;

param dp    :=  w01 19.0   w05 19.0   w96 19.0 ;

param wt  :=  18REG  47.3    24REG  63.0    24PRO  63.0 ;

param tc  :=  18REG  40.00   24REG  45.00   24PRO  45.00 ;

param dt  :=  18REG 376.0    24REG 172.4    24PRO 316.3 ;

param cpp :=  18REG 102.     24REG  91.     24PRO  91. ;

param dsr := w01 96.  w02 96.  w03 96.  w04 96.  w05 96.
             w62 96.  w76 96.  w96 96. ;

param pt (tr) :

       18REG     24REG     24PRO    :=

w01    1.194     1.429     1.429
w05    1.194     1.509     1.509
w96    0.000     1.600     1.600    ;

param rpc (tr) :

       18REG     24REG     24PRO    :=

w01    2119.       2653.    2617.
w05    2489.       3182.    3176.
w96       0.       2925.    2918.   ;

param opc (tr) :

       18REG     24REG     24PRO    :=

w01    2903.     3585.     3579.
w05       0.        0.        0.
w96       0.     3629.     3622.    ;

param sc  default 99.99 (tr) :

         w01     w02     w03     w04     w05     w62     w76     w96  :=

w01      .      2.97    1.14    2.08    2.37    1.26    2.42    1.43
w02     4.74     .      4.17    6.12    7.41    3.78    7.04    5.21
w03     2.45    4.74     .      3.67    2.84    0.90    2.41    2.55
w04     1.74    5.03    2.43     .      3.19    2.45    2.69    0.58
w05     2.70    5.16    2.84    2.85     .      3.26    3.34    2.71
w06     1.99    4.17    2.13    2.19    2.52    2.06    2.00    1.51
w08     0.21    2.92    1.24    2.07    2.29    1.25    2.32    1.55
w09     0.66    3.76    1.41    2.47    1.82    1.66     .      1.87
w12     1.38    3.83    1.68    2.53    2.39     .      1.96    1.94
w14     2.47    1.58    2.40    3.59    3.85    2.25     .      3.05
w15     1.06    4.95    2.48    1.39    3.41    1.96     .      1.02
w17     0.88    3.39    1.46    2.00    2.67    1.45     .      1.46
w18     7.90    6.57    7.79    9.59    10.81    .       .      6.70
w19     1.42    4.12    1.96    1.99    3.52    1.88     .      1.26
w20     3.03    1.59    2.34    4.76    3.98    1.88     .      3.73
w24     1.58    2.80    2.27    2.87    3.19    1.31     .      2.05
w25     1.51    5.05    2.74    0.57    2.98     .      2.95    0.27
w26     1.75    3.61    2.70    1.54    4.07    3.52     .      1.03
w27     2.48    6.87    3.17    1.59    2.08    3.45     .      0.99
w28     2.05    6.83    2.97    1.13    2.91     .       .      1.26
w29     4.03    3.68    4.46    3.20    5.50     .       .      3.20
w30     2.48    5.78    2.99    2.24    1.79    3.10     .      1.39
w31     2.34    5.41    2.87    1.67    1.66     .       .      1.39
w32     14.36    .       .       .       .       .       .       .
w33     3.87    4.27    5.11    3.48    5.66    4.03     .      3.05
w34     3.26    4.80    3.21    2.70    4.14     .       .      1.77
w35     2.34    2.84    2.89    3.35    3.78    2.68     .      2.52
w36     2.43    5.69    2.96    2.95    1.02    2.61    1.07    2.54
w37     2.23    4.64    2.41    1.99    4.30    2.61     .      1.44
w38     4.66    4.36    5.23    3.04    4.46     .       .      3.82
w39     1.11    3.51    1.10    2.53    3.07    1.12     .      2.23
w40     2.99    4.78    4.23    1.57    3.92     .       .      1.80
w41     4.93    4.00    5.43    4.45    6.31     .       .      3.81
w42     3.86    6.55    5.03    2.11    4.41     .       .      2.63
w43     4.61    4.45    3.77    1.22    4.31     .       .      2.35
w44     2.05    4.48    1.06    3.70    3.46    1.10     .      3.21
w45     0.92    3.42    1.58    3.04    1.82    1.94     .      2.52
w46     1.36    2.44    0.95    3.08    2.78    0.39    2.16    2.37
w47     1.30    3.39    1.60    2.49    4.29    2.04     .      1.68
w48     1.65    3.78    1.03    2.97    2.21    1.31     .      2.74
w49     1.96    3.00    1.50    3.24    3.68    1.00     .      2.99
w50     0.90    4.14    1.60    1.95    3.61    1.61     .      1.52
w51     1.59    3.95    0.25    2.96    2.58    1.00    2.41    2.71
w53     1.59    3.79    1.28    3.12    3.10    0.89     .      2.98
w54     1.72    4.36    1.61    2.92    2.34    1.91    1.97    3.05
w55     2.45    2.73    2.21    4.47    4.30    2.57     .      4.48
w56     1.10    3.73    1.59    2.74    2.33    1.45     .      2.44
w57     0.95    3.39    1.37    2.30    2.47    1.15     .      1.95
w59     3.29    5.35    3.32    3.81    1.52    3.38    1.34    4.08
w60     2.41    6.12    2.46    3.65    2.35     .      1.37    4.06
w61     3.32    5.50    3.41    3.38    1.23     .      0.99    4.28
w62     1.12    3.00    0.82    3.22    2.95     .      3.33    2.53
w63     3.59    6.36    3.25    4.12    1.84    3.59    1.46    4.03
w64     1.85    4.45    2.17    3.43    2.13    2.03     .      4.02
w65     2.78    4.79    2.81    2.94    1.54    2.90    1.07    2.94
w66     3.90    5.79    3.05    3.65    1.36    3.39    1.22    3.57
w68     2.61    5.20    2.90    2.34    1.68    3.19    1.48    2.31
w69     2.94    5.21    2.78    3.43    0.21    3.26    0.68    2.54
w71     2.06    4.98    2.38    2.44    1.59    2.97    1.05    2.55
w72     2.61    5.50    2.83    3.12    1.35    3.23    0.88    2.99
w73     8.52    6.16    8.03    8.83    10.44   7.38    10.26    .
w74     6.11    5.46    9.07    9.38    10.80    .       .      8.25
w75     2.66    4.94    2.87    3.69    1.52    3.15    1.24    4.00
w76     1.99    5.26    2.23    3.36    0.58    3.17     .      2.50
w77     4.32    3.07    5.05    3.88    6.04     .       .      4.15
w78     5.60    2.59    5.78    5.56    7.10     .       .      5.60
w79     4.25    2.32    4.93    4.57    6.04     .       .      4.58
w80     5.94    4.00    5.60    7.02    9.46     .       .      7.51
w81     5.39    2.21    5.10    6.22    6.46     .       .      6.58
w82     8.80    5.69    9.29    9.88    11.69   8.63    11.52    .
w83     4.40     .      5.24    5.21    5.81    3.91    7.04    5.33
w84     5.87    5.43    6.17    5.70    7.63     .       .      5.70
w85     3.90    3.65    3.38    4.57    5.64    3.05     .      5.04
w86     5.48    2.10    5.70    6.37    7.33     .       .      6.19
w87     8.88    5.54    9.50    9.71    11.64   8.85    11.68    .
w89     4.62    4.01    4.03    6.30    6.30    3.81     .      7.77
w90     4.35    2.72    4.61    4.01    5.60     .       .      3.20
w91     7.61    4.42    7.83    6.85    8.79     .       .      7.66
w92     7.15    2.69    6.91    7.20     .       .       .      7.06
w93     3.17    3.95    4.37    3.74    5.05     .       .      2.40
w94     1.21    3.07    0.90    2.74    3.17     .      2.63    2.39
w95     5.82    3.29    6.55    7.06    11.47    .       .      7.83
w96     1.77    5.20    2.72    0.59    3.47    2.48     .       .
w98     3.04    1.92    3.64    3.70    4.90    3.05     .      3.88
x22     4.08    6.25    4.15    4.30    1.77     .      1.77     .
x23     3.39    5.74    3.55    4.08    1.69     .      1.47     .      ;

param msr (tr) :

         w01     w02     w03     w04     w05     w62     w76     w96    :=

w01        0       0       0       0       0       0       1       0
w02        0       0       0       0       0       0       1       0
w03        0       0       0       0       0       0       1       0
w04        0       0       0       0       0       0       1       0
w05        0       0       0       0       0       0       0       0
w06        0       1       1       1       1       1       1       1
w08        0       1       1       1       1       1       1       1
w09        0       1       1       1       1       1       0       1
w12        0       1       1       1       1       0       1       1
w14        1       1       1       1       1       0       0       1
w15        0       1       1       1       1       1       0       1
w17        0       1       1       1       1       1       0       1
w18        0       1       1       1       1       0       0       1
w19        0       1       1       1       1       0       0       1
w20        1       1       1       1       1       0       0       1
w24        0       1       1       1       1       0       0       1
w25        0       1       1       1       1       0       1       0
w26        1       1       1       0       1       1       0       1
w27        1       1       1       0       1       1       0       1
w28        1       1       1       0       1       0       0       1
w29        0       1       1       1       1       0       0       1
w30        1       1       1       0       1       1       0       1
w31        1       1       1       0       1       0       0       1
w32        0       0       0       0       0       0       0       0
w33        1       0       1       1       1       1       0       1
w34        1       1       1       0       1       0       0       1
w35        1       1       1       1       1       0       0       1
w36        0       1       1       1       0       1       1       1
w37        1       1       1       0       1       1       0       1
w38        1       1       1       0       1       0       0       1
w39        0       1       1       1       1       1       0       1
w40        1       1       1       0       1       0       0       1
w41        1       0       1       1       1       0       0       1
w42        1       1       1       0       1       0       0       1
w43        1       1       1       0       1       0       0       1
w44        1       1       1       1       1       0       0       1
w45        0       1       1       1       1       1       0       1
w46        0       1       1       1       1       0       1       1
w47        0       1       1       1       1       1       0       1
w48        0       1       1       1       1       0       0       1
w49        1       1       1       1       1       0       0       1
w50        0       1       1       1       1       1       0       1
w51        0       1       1       1       1       0       1       1
w53        1       1       1       1       1       0       0       1
w54        0       1       1       1       1       1       1       1
w55        0       1       1       1       1       0       0       1
w56        0       1       1       1       1       1       0       1
w57        0       1       1       1       1       1       0       1
w59        0       1       1       1       0       1       1       1
w60        0       1       1       1       1       0       1       1
w61        0       1       1       1       0       0       1       1
w62        0       0       0       0       0       0       1       0
w63        0       1       1       1       0       1       1       1
w64        0       1       1       1       1       1       0       1
w65        0       1       1       1       0       1       1       1
w66        0       1       1       1       0       1       1       1
w68        0       1       1       1       0       1       1       1
w69        0       1       1       1       0       1       1       1
w71        0       1       1       1       0       1       1       1
w72        0       1       1       1       0       1       1       1
w73        0       1       1       1       0       1       1       0
w74        0       1       1       1       0       0       0       1
w75        0       1       1       1       0       1       1       1
w76        0       0       0       0       0       0       0       0
w77        1       0       1       1       1       0       0       1
w78        1       0       1       1       1       0       0       1
w79        1       0       1       1       1       0       0       1
w80        1       0       1       1       1       0       0       1
w81        1       0       1       1       1       0       0       1
w82        1       0       1       1       1       1       1       0
w83        1       0       1       1       1       0       1       1
w84        1       0       1       1       1       0       0       1
w85        1       1       1       1       1       0       0       1
w86        1       0       1       1       1       0       0       1
w87        1       0       1       1       1       1       1       0
w89        1       0       1       1       1       1       0       1
w90        0       1       1       1       1       0       0       1
w91        1       0       1       1       1       0       0       1
w92        1       0       1       1       1       0       0       1
w93        1       1       1       0       1       0       0       1
w94        0       0       1       1       1       0       1       1
w95        1       0       1       1       1       0       0       1
w96        0       0       0       0       0       0       0       0
w98        1       0       1       1       1       1       0       1
x22        1       1       1       1       0       0       1       0
x23        1       1       1       1       0       0       1       0    ;

param ds default 0.000 (tr) :

         18REG     24REG     24PRO    :=

w01      0.000     0.000     0.008
w02      0.004     0.000     0.000
w03      0.000     0.000     0.000
w04      0.010     0.002     0.000
w05      0.000     0.000     0.000
w06      0.010     0.008     0.008
w08      0.030     0.024     0.024
w09      0.014     0.018     0.020
w12      0.014     0.012     0.010
w14      0.007     0.007     0.012
w15      0.010     0.019     0.018
w17      0.013     0.010     0.011
w19      0.015     0.012     0.009
w20      0.012     0.021     0.022
w21      0.000     0.000     0.000
w24      0.012     0.022     0.018
w25      0.019     0.025     0.020
w26      0.006     0.015     0.021
w27      0.008     0.010     0.015
w28      0.011     0.016     0.019
w29      0.008     0.020     0.013
w30      0.011     0.013     0.015
w31      0.011     0.013     0.017
w32      0.006     0.000     0.000
w33      0.000     0.015     0.014
w34      0.008     0.007     0.005
w35      0.002     0.006     0.014
w36      0.015     0.013     0.005
w37      0.017     0.016     0.015
w38      0.015     0.009     0.012
w39      0.007     0.017     0.022
w40      0.009     0.014     0.020
w41      0.003     0.014     0.011
w42      0.017     0.011     0.012
w43      0.009     0.013     0.011
w44      0.002     0.012     0.012
w45      0.016     0.025     0.028
w46      0.038     0.062     0.040
w47      0.007     0.010     0.010
w48      0.003     0.015     0.016
w49      0.005     0.016     0.017
w50      0.011     0.008     0.007
w51      0.010     0.022     0.021
w53      0.004     0.026     0.020
w54      0.020     0.017     0.025
w55      0.004     0.019     0.028
w56      0.004     0.010     0.008
w57      0.014     0.020     0.018
w59      0.012     0.006     0.007
w60      0.019     0.010     0.009
w61      0.028     0.010     0.012
w62      0.000     0.000     0.000
w63      0.070     0.027     0.037
w64      0.009     0.004     0.005
w65      0.022     0.015     0.016
w66      0.046     0.017     0.020
w68      0.005     0.012     0.016
w69      0.085     0.036     0.039
w71      0.011     0.013     0.010
w72      0.089     0.031     0.034
w75      0.026     0.012     0.010
w77      0.001     0.004     0.002
w78      0.002     0.004     0.002
w79      0.001     0.004     0.002
w80      0.001     0.001     0.002
w81      0.001     0.003     0.002
w83      0.009     0.010     0.008
w84      0.001     0.002     0.002
w85      0.001     0.004     0.005
w86      0.001     0.002     0.002
w87      0.002     0.003     0.000
w89      0.001     0.001     0.002
w90      0.006     0.017     0.013
w91      0.002     0.010     0.013
w92      0.000     0.003     0.002
w93      0.002     0.006     0.007
w95      0.001     0.007     0.007
w96      0.000     0.000     0.000
w98      0.006     0.005     0.002    ;

end;

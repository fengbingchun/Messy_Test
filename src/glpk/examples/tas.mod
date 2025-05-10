/* TAS, Tail Assignment Problem */

/* Written in GNU MathProg by Andrew Makhorin <mao@gnu.org> */

/* The Tail Assignment Problem (TAS) is to construct rosters for a set
   of aircrafts (tails), which cover all flights for a given scheduling
   period.

   This model includes only flight connection constraints while other
   constraints (for example, maintenance constraints) are ignored. Such
   simplification allows using a single commodity network to model the
   problem, where commodity corresponds to the set of aircrafts.

   Nodes of the network are activities. They include all flights plus
   two dummy nodes (activities): source node, s, corresponding to
   initial activity of each aircraft, and sink node t, corresponding to
   final activity of each aircraft. Arc v->v' exists in the network if
   and only if the same aircraft is able to operate activity v and then
   immediately activity v'. In partucular, arcs s->f and f->t exist for
   all flights f. Arcs f->f', where f and f' are some flights, exist
   only if the connection time (which is the difference between the
   departure time of f' and the arrival time of f) is not less than a
   given minimal connection time.

   Reference:
   M. Groenkvist, "The Tail Assignment Problem," Dept. of Comp. Sci.
   and Eng., Chalmers University of Technology and Goeteborg University,
   Goeteborg, Sweden, August 2005. */

########################################################################

param nf, integer, > 0;
/* number of flights */

set F := 1..nf;
/* set of flights (for a given period from timetable) */

param hub{f in F}, in {1, 2};
/* hub[f] = 1: Sheremetyevo-1
   hub[f] = 2: Sheremetyevo-2 */

param dest{f in F}, symbolic;
/* destination airport (IATA code) */

param fno1{f in F}, integer;
/* first leg flight number */

param dep1{f in F}, integer, >= 0;
/* departure time from Sheremetyevo airport, in minutes */

check{f in F: f < nf}: dep1[f] <= dep1[f+1];
/* all flights must be ordered by ascending of the departure time */

param arr1{f in F}, integer, >= 0;
/* arrival time to destination airport, in minutes */

param fno2{f in F}, integer;
/* second leg flight number */

param dep2{f in F}, integer, >= 0;
/* departure time from destination airport, in minutes */

param arr2{f in F}, integer, >= 0;
/* arrival time to Sheremetyevo airport, in minutes */

param mct1, integer, >= 0, default 80;
/* minimal connection time (within SVO1 or SVO2), in minutes */

param mct2, integer, >= 0, default 150;
/* minimal connection time (between SVO1 and SVO2), in minutes */

set E := setof{f in F, ff in F: arr2[f] + (if hub[f] = hub[ff] then
   mct1 else mct2) <= dep1[ff]} (f, ff);
/* connection network; arc f->ff is in E, iff the same aircraft can be
   assigned to flight f and then immediately to flight ff */

var s{f in F}, >= 0;
/* s[f] is a flow from source node to node f */

var x{(f,ff) in E}, >= 0;
/* x[f,ff] is a flow from node f to node ff */

var t{f in F}, >= 0;
/* t[f] is a flow from node f to sink node */

s.t. into{f in F}: s[f] + sum{(ff,f) in E} x[ff,f] = 1;
/* exactly one aircraft must come into each node f */

s.t. from{f in F}: t[f] + sum{(f,ff) in E} x[f,ff] = 1;
/* exactly one aircraft must come from each node f */

minimize obj: sum{f in F} s[f];
/* minimize the number aircrafts sufficient to cover all flights */

solve;

########################################################################

param na := floor(sum{f in F} s[f] + .5);
/* minimal number of aircrafts found */

printf "At least %d aircrafts needed\n", na;

set A := 1..na;
/* set of aircrafts */

printf "Building rosters...\n";

param tail{f in F}, in A, :=
/* tail[f] is the number of an aircraft assigned to flight f */

   if f = 1 then 1
   /* assign aircraft 1 to the earliest flight */

   else if s[f] >= 0.9 then (max{ff in 1..f-1} tail[ff]) + 1
   /* if f is the first flight in a roster, assign to it a next
      aircraft */

   else sum{(ff,f) in E} tail[ff] * (if x[ff,f] >= 0.9 then 1);
   /* otherwise, assign to flight f the same aircraft, which is
      assigned to a preceding flight in the roster */

########################################################################

param file, symbolic, default "tas.ps";
/* file to output the assignment chart in postscript format */

param title, symbolic, default "(no title)";
/* chart title */

param left, default 25;
/* left margin, in mm */

param top, default 25;
/* top margin, in mm */

param right, default 20;
/* right margin, in mm */

param bottom, default 15;
/* bottom margin, in mm */

param sx := 297 - left - right;
/* chart area horizontal size, in mm */

param sy := 210 - top - bottom;
/* chart area vertical size, in mm */

param gap, default sy / (na - 1);
/* gap between rosters, in mm */

printf "Writing assignment chart to %s...\n", file;

printf "%%!PS-Adobe-3.0\n" > file;
printf "%%%%Title: Tail Assignment Chart\n" >> file;
printf "%%%%Creator: GLPK MathProg\n" >> file;
printf "%%%%BoundingBox: 0 0 595 842\n" >> file;
printf "%%%%EndComments\n" >> file;
printf "<</PageSize [595 842]>> setpagedevice\n" >> file;
printf "72 25.4 div dup scale\n" >> file;
printf "210 %.3f sub %.3f translate\n", bottom, left >> file;
printf "90 rotate\n" >> file;

printf "/HelveticaBold findfont 5 scalefont setfont\n" >> file;
printf "%.3f %.3f moveto (%s) dup show\n", 0, sy + 5, title >> file;

param period := floor((max{f in F} arr2[f]) / 60. + .5);
/* period duration, in hours */

/* vertical bars */
printf ".8 .8 .8 setrgbcolor\n" >> file;
for {tt in 0..period}
{  printf "%s setlinewidth\n",
      if tt mod 24 = 0 then ".5" else "0" >> file;
   printf "newpath %.3f %.3f moveto %.3f %.3f lineto stroke\n",
      tt * (sx / period), 0, tt * (sx / period),
      sy + (if tt mod 24 = 0 then 2) >> file;
}

/* rosters */
for {a in A}
{  printf "0 0 0 setrgbcolor\n" >> file;
   printf "0 setlinewidth\n" >> file;
   printf "newpath %.3f %.3f moveto %.3f %.3f lineto stroke\n",
      0, sy - gap * (a - 1), sx, sy - gap * (a - 1) >> file;
   printf "/Dingbats findfont 4 scalefont setfont\n" >> file;
   printf "%.3f %.3f moveto <28> dup show\n",
      -4, sy - gap * (a - 1) - 1.4, a >> file;
   printf "/Helvetica findfont 3 scalefont setfont\n" >> file;
   printf "%.3f %.3f moveto (%2d) dup show\n",
      -9, sy - gap * (a - 1) - 1.2, a >> file;
   for {f in F: tail[f] == a}
   {  printf "0 0 %s setrgbcolor\n",
         if hub[f] = 1 then "0" else ".8" >> file;
      printf "1 setlinewidth\n" >> file;
      printf "newpath %.3f %.3f moveto %.3f %.3f lineto stroke\n",
         dep1[f] / 60 * (sx / period), sy - gap * (a - 1),
         arr2[f] / 60 * (sx / period), sy - gap * (a - 1) >> file;
      printf "/Helvetica findfont 1.8 scalefont setfont\n" >> file;
      printf "%.3f %.3f moveto (%02d:%02d %s) dup show\n",
         dep1[f] / 60 * (sx / period), sy - gap * (a - 1) + .8,
         (dep1[f] mod 1440) div 60, (dep1[f] mod 1440) mod 60,
         dest[f] >> file;
      printf "%.3f %.3f moveto (%d %02d:%02d) dup show\n",
         dep1[f] / 60 * (sx / period), sy - gap * (a - 1) - 2.1,
         fno1[f],
         (arr2[f] mod 1440) div 60, (arr2[f] mod 1440) mod 60 >> file;
   }
}

printf "showpage\n" >> file;
printf "%%%%EOF\n" >> file;

########################################################################

data;

param title := "Tu-154 [from 2008-08-18 to 2008-08-24]";

param nf := 261;

param : hub dest fno1 dep1  arr1  fno2 dep2  arr2 :=
      1  1  IKT  743   195   520  744   610   970
      2  1  OMS  815   205   405  816   485   700
      3  1  CEK  897   205   360  898   430   595
      4  1  KRR  763   260   400  764   480   610
      5  2  SIP  133   280   420  134   500   620
      6  2  BUD  131   290   450  132   520   675
      7  1  AAQ  701   305   440  702   510   640
      8  1  MRV  785   310   440  786   520   650
      9  2  WAW  101   355   475  102   540   660
     10  2  GYD  147   370   550  148   675   860
     11  1  AER  869   385   530  870   655   795
     12  1  KRR  765   430   560  766   630   760
     13  1  AAQ  703   520   660  704   740   850
     14  1  LED  845   530   620  846   690   775
     15  1  KRR  767   540   675  768   765   895
     16  2  KBP  183   665   760  184   850   940
     17  1  MRV  787   755   905  788   985  1135
     18  1  KRR  771   810   940  772  1030  1165
     19  1  LED  849   825   900  850   960  1095
     20  2  IST  209   880  1050  210  1120  1280
     21  1  AER  873   885  1030  874  1760  1900
     22  1  ASF  711   995  1145  712  1640  1795
     23  2  ULN  563   995  1335  564  1415  1815
     24  2  OTP  151  1020  1175  152  1800  1940
     25  2  BEY  509  1025  1265  510  1350  1580
     26  2  OSL  211  1060  1220  212  1860  2015
     27  1  IKT  739  1085  1420  740  1510  1870
     28  1  KRR  773  1095  1240  774  1620  1765
     29  1  SGC  877  1120  1315  878  1395  1625
     30  1  LED  857  1150  1230  858  1610  1690
     31  1  CEK  899  1230  1385  900  1455  1620
     32  1  PEE  821  1235  1390  822  1450  1600
     33  2  TBS  197  1240  1405  198  1560  1715
     34  1  UFA  891  1275  1405  892  1475  1610
     35  1  KJA  781  1300  1570  782  1680  1990
     36  1  IKT  743  1635  1960  744  2050  2410
     37  1  OMS  815  1645  1845  816  1925  2140
     38  1  CEK  897  1645  1800  898  1870  2035
     39  1  KRR  763  1700  1840  764  1920  2050
     40  2  SIP  133  1720  1860  134  1940  2060
     41  2  BUD  131  1730  1890  132  1960  2115
     42  1  AAQ  701  1745  1880  702  1950  2080
     43  1  MRV  785  1750  1880  786  1960  2090
     44  2  WAW  101  1795  1915  102  1980  2100
     45  2  GYD  147  1810  1990  148  2115  2300
     46  1  AER  869  1825  1970  870  2095  2235
     47  2  EVN  193  1850  2030  194  2105  2275
     48  1  KRR  765  1870  2000  766  2070  2200
     49  1  AAQ  703  1960  2100  704  2180  2290
     50  1  LED  845  1970  2060  846  2130  2215
     51  1  KRR  767  1980  2115  768  2205  2335
     52  2  KBP  183  2105  2200  184  2290  2380
     53  1  MRV  787  2195  2345  788  2425  2575
     54  1  KRR  771  2250  2380  772  2470  2605
     55  1  LED  849  2265  2340  850  2400  2535
     56  2  IST  209  2320  2490  210  2560  2720
     57  1  AER  873  2325  2470  874  3200  3340
     58  2  ULN  563  2435  2775  564  2855  3255
     59  1  ASF  711  2435  2585  712  3080  3235
     60  2  DAM  517  2465  2705  518  2790  3020
     61  2  OSL  211  2500  2660  212  3300  3455
     62  2  KBP  185  2510  2610  186  3160  3250
     63  1  IKT  739  2525  2860  740  2950  3310
     64  1  KRR  773  2535  2680  774  3060  3205
     65  1  SGC  877  2560  2755  878  2835  3065
     66  1  LED  857  2590  2670  858  3050  3130
     67  1  CEK  899  2670  2825  900  2895  3060
     68  1  PEE  821  2675  2830  822  2890  3040
     69  2  TBS  197  2680  2845  198  3000  3155
     70  1  UFA  891  2715  2845  892  2915  3050
     71  1  KJA  781  2740  3010  782  3120  3430
     72  1  IKT  743  3075  3400  744  3490  3850
     73  1  CEK  897  3085  3240  898  3310  3475
     74  1  OMS  815  3085  3285  816  3365  3580
     75  1  KRR  763  3140  3280  764  3360  3490
     76  2  SIP  133  3160  3300  134  3380  3500
     77  2  BUD  131  3170  3330  132  3400  3555
     78  1  AAQ  701  3185  3320  702  3390  3520
     79  1  MRV  785  3190  3320  786  3400  3530
     80  2  WAW  101  3235  3355  102  3420  3540
     81  2  FRU  181  3245  3495  182  3590  3860
     82  2  GYD  147  3250  3430  148  3555  3740
     83  1  AER  869  3265  3410  870  3535  3675
     84  1  KRR  765  3310  3440  766  3510  3640
     85  1  AAQ  703  3400  3540  704  3620  3730
     86  1  LED  845  3410  3500  846  3570  3655
     87  1  KRR  767  3420  3555  768  3645  3775
     88  2  KBP  183  3545  3640  184  3730  3820
     89  1  MRV  787  3635  3785  788  3865  4015
     90  1  KRR  771  3690  3820  772  3910  4045
     91  1  LED  849  3705  3780  850  3840  3975
     92  2  IST  209  3760  3930  210  4000  4160
     93  1  AER  873  3765  3910  874  4640  4780
     94  2  ULN  563  3875  4215  564  4295  4695
     95  1  ASF  711  3875  4025  712  4520  4675
     96  2  OTP  151  3900  4055  152  4680  4820
     97  2  BEY  509  3905  4145  510  4230  4460
     98  2  OSL  211  3940  4100  212  4740  4895
     99  2  KBP  185  3950  4050  186  4600  4690
    100  1  IKT  739  3965  4300  740  4390  4750
    101  1  KRR  773  3975  4120  774  4500  4645
    102  1  SGC  877  4000  4195  878  4275  4505
    103  1  LED  857  4030  4110  858  4490  4570
    104  1  CEK  899  4110  4265  900  4335  4500
    105  1  PEE  821  4115  4270  822  4330  4480
    106  2  TBS  197  4120  4285  198  4440  4595
    107  1  UFA  891  4155  4285  892  4355  4490
    108  1  KJA  781  4180  4450  782  4560  4870
    109  1  IKT  743  4515  4840  744  4930  5290
    110  1  OMS  815  4525  4725  816  4805  5020
    111  1  CEK  897  4525  4680  898  4750  4915
    112  1  KRR  763  4580  4720  764  4800  4930
    113  2  SIP  133  4600  4740  134  4820  4940
    114  2  BUD  131  4610  4770  132  4840  4995
    115  1  AAQ  701  4625  4760  702  4830  4960
    116  1  MRV  785  4630  4760  786  4840  4970
    117  2  WAW  101  4675  4795  102  4860  4980
    118  2  GYD  147  4690  4870  148  4995  5180
    119  1  AER  869  4705  4850  870  4975  5115
    120  2  EVN  193  4730  4910  194  4985  5155
    121  1  KRR  765  4750  4880  766  4950  5080
    122  1  AAQ  703  4840  4980  704  5060  5170
    123  1  LED  845  4850  4940  846  5010  5095
    124  1  KRR  767  4860  4995  768  5085  5215
    125  2  KBP  183  4985  5080  184  5170  5260
    126  1  MRV  787  5075  5225  788  5305  5455
    127  1  KRR  771  5130  5260  772  5350  5485
    128  1  LED  849  5145  5220  850  5280  5415
    129  2  IST  209  5200  5370  210  5440  5600
    130  1  AER  873  5205  5350  874  6080  6220
    131  1  ASF  711  5315  5465  712  5960  6115
    132  2  ULN  563  5315  5655  564  5735  6135
    133  2  DAM  517  5345  5585  518  5670  5900
    134  2  OSL  211  5380  5540  212  6180  6335
    135  2  KBP  185  5390  5490  186  6040  6130
    136  1  IKT  739  5405  5740  740  5830  6190
    137  1  KRR  773  5415  5560  774  5940  6085
    138  1  SGC  877  5440  5635  878  5715  5945
    139  1  LED  857  5470  5550  858  5930  6010
    140  1  CEK  899  5550  5705  900  5775  5940
    141  1  PEE  821  5555  5710  822  5770  5920
    142  2  TBS  197  5560  5725  198  5880  6035
    143  1  UFA  891  5595  5725  892  5795  5930
    144  1  KJA  781  5620  5890  782  6000  6310
    145  1  IKT  743  5955  6280  744  6370  6730
    146  1  OMS  815  5965  6165  816  6245  6460
    147  1  CEK  897  5965  6120  898  6190  6355
    148  1  KRR  763  6020  6160  764  6240  6370
    149  2  SIP  133  6040  6180  134  6260  6380
    150  2  BUD  131  6050  6210  132  6280  6435
    151  1  AAQ  701  6065  6200  702  6270  6400
    152  1  MRV  785  6070  6200  786  6280  6410
    153  2  WAW  101  6115  6235  102  6300  6420
    154  2  FRU  181  6125  6375  182  6470  6740
    155  2  GYD  147  6130  6310  148  6435  6620
    156  1  AER  869  6145  6290  870  6415  6555
    157  2  EVN  193  6170  6350  194  6425  6595
    158  1  KRR  765  6190  6320  766  6390  6520
    159  1  AAQ  703  6280  6420  704  6500  6610
    160  1  LED  845  6290  6380  846  6450  6535
    161  1  KRR  767  6300  6435  768  6525  6655
    162  2  KBP  183  6425  6520  184  6610  6700
    163  2  AYT  223  6500  6690  224  6750  6940
    164  1  AER  867  6510  6660  868  6730  6880
    165  1  MRV  787  6515  6665  788  6745  6895
    166  1  KRR  771  6570  6700  772  6790  6925
    167  1  LED  849  6585  6660  850  6720  6855
    168  2  IST  209  6640  6810  210  6880  7040
    169  1  AER  873  6645  6790  874  7520  7660
    170  1  ASF  711  6755  6905  712  7400  7555
    171  2  ULN  563  6755  7095  564  7175  7575
    172  2  OTP  151  6780  6935  152  7560  7700
    173  2  BEY  509  6785  7025  510  7110  7340
    174  2  OSL  211  6820  6980  212  7620  7775
    175  2  KBP  185  6830  6930  186  7480  7570
    176  1  IKT  739  6845  7180  740  7270  7630
    177  1  KRR  773  6855  7000  774  7380  7525
    178  1  SGC  877  6880  7075  878  7155  7385
    179  1  LED  857  6910  6990  858  7370  7450
    180  1  CEK  899  6990  7145  900  7215  7380
    181  1  PEE  821  6995  7150  822  7210  7360
    182  2  TBS  197  7000  7165  198  7320  7475
    183  1  UFA  891  7035  7165  892  7235  7370
    184  1  KJA  781  7060  7330  782  7440  7750
    185  1  IKT  743  7395  7720  744  7810  8170
    186  1  CEK  897  7405  7560  898  7630  7795
    187  1  KRR  763  7460  7600  764  7680  7810
    188  2  SIP  133  7480  7620  134  7700  7820
    189  2  BUD  131  7490  7650  132  7720  7875
    190  1  AAQ  701  7505  7640  702  7710  7840
    191  1  MRV  785  7510  7640  786  7720  7850
    192  2  IST  207  7545  7720  208  7795  7985
    193  2  WAW  101  7555  7675  102  7740  7860
    194  2  GYD  147  7570  7750  148  7875  8060
    195  1  AER  869  7585  7730  870  7855  7995
    196  2  AYT  221  7610  7800  222  7895  8085
    197  2  EVN  193  7610  7790  194  7865  8035
    198  1  KRR  765  7630  7760  766  7830  7960
    199  1  AAQ  703  7720  7860  704  7940  8050
    200  1  LED  845  7730  7820  846  7890  7975
    201  1  KRR  767  7740  7875  768  7965  8095
    202  2  KBP  183  7865  7960  184  8050  8140
    203  2  AYT  223  7940  8130  224  8190  8380
    204  1  MRV  787  7955  8105  788  8185  8335
    205  1  KRR  771  8010  8140  772  8230  8365
    206  1  LED  849  8025  8100  850  8160  8295
    207  2  IST  209  8080  8250  210  8320  8480
    208  1  AER  873  8085  8230  874  8960  9100
    209  1  ASF  711  8195  8345  712  8840  8995
    210  2  ULN  563  8195  8535  564  8615  9015
    211  1  KJA  779  8230  8500  780  8575  8870
    212  2  OSL  211  8260  8420  212  9060  9215
    213  2  KBP  185  8270  8370  186  8920  9010
    214  1  IKT  739  8285  8620  740  8710  9070
    215  1  KRR  773  8295  8440  774  8820  8965
    216  1  SGC  877  8320  8515  878  8595  8825
    217  1  LED  857  8350  8430  858  8810  8890
    218  1  CEK  899  8430  8585  900  8655  8820
    219  1  PEE  821  8435  8590  822  8650  8800
    220  2  TBS  197  8440  8605  198  8760  8915
    221  1  UFA  891  8475  8605  892  8675  8810
    222  1  KJA  781  8500  8770  782  8880  9190
    223  1  IKT  743  8835  9160  744  9250  9610
    224  1  OMS  815  8845  9045  816  9125  9340
    225  1  CEK  897  8845  9000  898  9070  9235
    226  1  KRR  763  8900  9040  764  9120  9250
    227  2  SIP  133  8920  9060  134  9140  9260
    228  2  BUD  131  8930  9090  132  9160  9315
    229  1  AAQ  701  8945  9080  702  9150  9280
    230  1  MRV  785  8950  9080  786  9160  9290
    231  2  IST  207  8985  9160  208  9235  9425
    232  2  WAW  101  8995  9115  102  9180  9300
    233  2  FRU  181  9005  9255  182  9350  9620
    234  2  GYD  147  9010  9190  148  9315  9500
    235  1  AER  869  9025  9170  870  9295  9435
    236  2  EVN  193  9050  9230  194  9305  9475
    237  1  KRR  765  9070  9200  766  9270  9400
    238  1  AAQ  703  9160  9300  704  9380  9490
    239  1  LED  845  9170  9260  846  9330  9415
    240  1  KRR  767  9180  9315  768  9405  9535
    241  2  KBP  183  9305  9400  184  9490  9580
    242  2  AYT  223  9380  9570  224  9630  9820
    243  1  MRV  787  9395  9545  788  9625  9775
    244  1  KRR  771  9450  9580  772  9670  9805
    245  1  LED  849  9465  9540  850  9600  9735
    246  2  IST  209  9520  9690  210  9760  9920
    247  1  AER  873  9525  9670  874 10400 10540
    248  1  ASF  711  9635  9785  712 10280 10435
    249  2  ULN  563  9635  9975  564 10055 10455
    250  2  OTP  151  9660  9815  152 10440 10580
    251  2  DAM  517  9665  9905  518  9990 10220
    252  2  OSL  211  9700  9860  212 10500 10655
    253  2  KBP  185  9710  9810  186 10360 10450
    254  1  IKT  739  9725 10060  740 10150 10510
    255  1  KRR  773  9735  9880  774 10260 10405
    256  1  SGC  877  9760  9955  878 10035 10265
    257  1  LED  857  9790  9870  858 10250 10330
    258  1  CEK  899  9870 10025  900 10095 10260
    259  1  PEE  821  9875 10030  822 10090 10240
    260  1  UFA  891  9915 10045  892 10115 10250
    261  1  KJA  781  9940 10210  782 10320 10630
;

end;

/* STIGLER, original Stigler's 1939 diet problem */

/* The Stigler Diet is an optimization problem named for George Stigler,
   a 1982 Nobel Laureate in economics, who posed the following problem:
   For a moderately active man weighing 154 pounds, how much of each of
   77 foods should be eaten on a daily basis so that the man's intake of
   nine nutrients will be at least equal to the recommended dietary
   allowances (RDSs) suggested by the National Research Council in 1943,
   with the cost of the diet being minimal?

   The nutrient RDAs required to be met in Stigler's experiment were
   calories, protein, calcium, iron, vitamin A, thiamine, riboflavin,
   niacin, and ascorbic acid. The result was an annual budget allocated
   to foods such as evaporated milk, cabbage, dried navy beans, and beef
   liver at a cost of approximately $0.11 a day in 1939 U.S. dollars.

   While the name "Stigler Diet" was applied after the experiment by
   outsiders, according to Stigler, "No one recommends these diets for
   anyone, let alone everyone." The Stigler diet has been much ridiculed
   for its lack of variety and palatability, however his methodology has
   received praise and is considered to be some of the earliest work in
   linear programming.

   The Stigler diet question is a linear programming problem. Lacking
   any sophisticated method of solving such a problem, Stigler was
   forced to utilize heuristic methods in order to find a solution. The
   diet question originally asked in which quantities a 154 pound male
   would have to consume 77 different foods in order to fulfill the
   recommended intake of 9 different nutrients while keeping expense at
   a minimum. Through "trial and error, mathematical insight and
   agility," Stigler was able to eliminate 62 of the foods from the
   original 77 (these foods were removed based because they lacked
   nutrients in comparison to the remaining 15). From the reduced list,
   Stigler calculated the required amounts of each of the remaining 15
   foods to arrive at a cost-minimizing solution to his question.
   According to Stigler's calculations, the annual cost of his solution
   was $39.93 in 1939 dollars. When corrected for inflation using the
   consumer price index, the cost of the diet in 2005 dollars is
   $561.43. The specific combination of foods and quantities is as
   follows:

   Stigler's 1939 Diet

   Food             Annual Quantities Annual Cost
   ---------------- ----------------- -----------
   Wheat Flour           370 lb.         $13.33
   Evaporated Milk        57 cans          3.84
   Cabbage               111 lb.           4.11
   Spinach                23 lb.           1.85
   Dried Navy Beans      285 lb.          16.80
   ----------------------------------------------
   Total Annual Cost                     $39.93

   The 9 nutrients that Stigler's diet took into consideration and their
   respective recommended daily amounts were:

   Table of nutrients considered in Stigler's diet

   Nutrient                  Daily Recommended Intake
   ------------------------- ------------------------
   Calories                       3,000 Calories
   Protein                           70 grams
   Calcium                           .8 grams
   Iron                              12 milligrams
   Vitamin A                      5,000 IU
   Thiamine (Vitamin B1)            1.8 milligrams
   Riboflavin (Vitamin B2)          2.7 milligrams
   Niacin                            18 milligrams
   Ascorbic Acid (Vitamin C)         75 milligrams

   Seven years after Stigler made his initial estimates, the development
   of George Dantzig's Simplex algorithm made it possible to solve the
   problem without relying on heuristic methods. The exact value was
   determined to be $39.69 (using the original 1939 data). Dantzig's
   algorithm describes a method of traversing the vertices of a polytope
   of N+1 dimensions in order to find the optimal solution to a specific
   situation.

   (From Wikipedia, the free encyclopedia.) */

/* Translated from GAMS by Andrew Makhorin <mao@gnu.org>.

   For the original GAMS model stigler1939.gms see [3].

   References:

   1. George J. Stigler, "The Cost of Subsistence," J. Farm Econ. 27,
      1945, pp. 303-14.

   2. National Research Council, "Recommended Daily Allowances," Reprint
      and Circular Series No. 115, January, 1943.

   3. Erwin Kalvelagen, "Model building with GAMS," Chapter 2, "Building
      linear programming models," pp. 128-34. */

set C;
/* commodities */

check card(C) = 77;
/* there must be 77 commodities */

set N;
/* nutrients */

param data{c in C, {"price", "weight"} union N};
/* nutritive values per dollar of expenditure */

param allowance{n in N};
/* recommended daily allowance for a moderately active man */

var x{c in C}, >= 0;
/* dollars of food to be purchased daily */

s.t. nb{n in N}: sum{c in C} data[c,n] * x[c] >= allowance[n];
/* nutrient balance */

minimize cost: sum{c in C} x[c];
/* total food bill */

solve;

param days := 365.25;
/* days in a year */

param commodity{c in C}, symbolic;

param unit{c in C}, symbolic;

printf "\n";
printf "MINIMUM COST ANNUAL DIET\n";
printf "\n";
printf "        Commodity            Unit     Quantity     Cost   \n";
printf "------------------------- ---------- ---------- ----------\n";
printf{c in C: x[c] != 0} "%-25s %10s %10.2f   $%7.2f\n", commodity[c],
   unit[c], 100 * days * x[c] / data[c,"price"], days * x[c];
printf "                                         -----------------\n";
printf "                                         Total:   $%7.2f\n",
   days * sum{c in C} x[c];
printf "\n";

data;

param : C :    commodity                   unit :=
flour          "Wheat Flour (Enriched)"    "10 lb."
macaroni       "Macaroni"                  "1 lb."
cereal         "Wheat Cereal (Enriched)"   "28 oz."
cornflakes     "Corn Flakes"               "8 oz."
cornmeal       "Corn Meal"                 "1 lb."
grits          "Hominy Grits"              "24 oz."
rice           "Rice"                      "1 lb."
oats           "Rolled Oats"               "1 lb."
whitebread     "White Bread (Enriched)"    "1 lb."
wheatbread     "Whole Wheat Bread"         "1 lb."
ryebread       "Rye Bread"                 "1 lb."
poundcake      "Pound Cake"                "1 lb."
crackers       "Soda Crackers"             "1 lb."
milk           "Milk"                      "1 qt."
evapmild       "Evaporated Milk (can)"     "14.5 oz."
butter         "Butter"                    "1 lb."
margarine      "Oleomargarine"             "1 lb."
eggs           "Eggs"                      "1 doz."
cheese         "Cheese (Cheddar)"          "1 lb."
cream          "Cream"                     "1/2 pt."
peanutbutter   "Peanut Butter"             "1 lb."
mayonnaise     "Mayonnaise"                "1/2 pt."
crisco         "Crisco"                    "1 lb."
lard           "Lard"                      "1 lb."
sirloinsteak   "Sirloin Steak"             "1 lb."
roundsteak     "Round Steak"               "1 lb."
ribroast       "Rib Roast"                 "1 lb."
chuckroast     "Chuck Roast"               "1 lb."
plate          "Plate"                     "1 lb."
liver          "Liver (Beef)"              "1 lb."
lambleg        "Leg of Lamb"               "1 lb."
lambchops      "Lamb Chops (Rib)"          "1 lb."
porkchops      "Pork Chops"                "1 lb."
porkroast      "Pork Loin Roast"           "1 lb."
bacon          "Bacon"                     "1 lb."
ham            "Ham - smoked"              "1 lb."
saltpork       "Salt Pork"                 "1 lb."
chicken        "Roasting Chicken"          "1 lb."
veal           "Veal Cutlets"              "1 lb."
salmon         "Salmon, Pink (can)"        "16 oz."
apples         "Apples"                    "1 lb."
bananas        "Bananas"                   "1 lb."
lemons         "Lemons"                    "1 doz."
oranges        "Oranges"                   "1 doz."
greenbeans     "Green Beans"               "1 lb."
cabbage        "Cabbage"                   "1 lb."
carrots        "Carrots"                   "1 bunch"
celery         "Celery"                    "1 stalk"
lettuce        "Lettuce"                   "1 head"
onions         "Onions"                    "1 lb."
potatoes       "Potatoes"                  "15 lb."
spinach        "Spinach"                   "1 lb."
sweetpotato    "Sweet Potatoes"            "1 lb."
peaches        "Peaches (can)"             "No. 2 1/2"
pears          "Pears (can)"               "No. 2 1/2"
pineapple      "Pineapple (can)"           "No. 2 1/2"
asparagus      "Asparagus (can)"           "No. 2"
cannedgrbn     "Grean Beans (can)"         "No. 2"
porkbeans      "Pork and Beans (can)"      "16 oz."
corn           "Corn (can)"                "No. 2"
peas           "Peas (can)"                "No. 2"
tomatoes       "Tomatoes (can)"            "No. 2"
tomatosoup     "Tomato Soup (can)"         "10 1/2 oz."
driedpeach     "Peaches, Dried"            "1 lb."
prunes         "Prunes, Dried"             "1 lb."
raisins        "Raisins, Dried"            "15 oz."
driedpeas      "Peas, Dried"               "1 lb."
limabeans      "Lima Beans, Dried"         "1 lb."
navybeans      "Navy Beans, Dried"         "1 lb."
coffee         "Coffee"                    "1 lb."
tea            "Tea"                       "1/4 lb."
cocoa          "Cocoa"                     "8 oz."
chocolate      "Chocolate"                 "8 oz."
sugar          "Sugar"                     "10 lb."
cornsirup      "Corn Sirup"                "24 oz."
molasses       "Molasses"                  "18 oz."
strawberry     "Strawberry Preserve"       "1 lb."
;

set N :=
calories       /* Calories, unit = 1000 */
protein        /* Protein, unit = grams */
calcium        /* Calcium, unit = grams */
iron           /* Iron, unit = milligrams */
vitaminA       /* Vitamin A, unit = 1000 International Units */
thiamine       /* Thiamine, Vit. B1, unit = milligrams */
riboflavin     /* Riboflavin, Vit. B2, unit = milligrams */
niacin         /* Niacin (Nicotinic Acid), unit = milligrams */
ascorbicAcid   /* Ascorbic Acid, Vit. C, unit = milligrams */
;

param data
:             price   weight calories protein  calcium   iron :=
#            aug. 15  edible
#             1939    per $1
#           (cents)   (grams) (1000)  (grams)  (grams)   (mg.)
flour         36.0    12600    44.7     1411     2.0      365
macaroni      14.1     3217    11.6      418      .7       54
cereal        24.2     3280    11.8      377    14.4      175
cornflakes     7.1     3194    11.4      252      .1       56
cornmeal       4.6     9861    36.0      897     1.7       99
grits          8.5     8005    28.6      680      .8       80
rice           7.5     6048    21.2      460      .6       41
oats           7.1     6389    25.3      907     5.1      341
whitebread     7.9     5742    15.6      488     2.5      115
wheatbread     9.1     4985    12.2      484     2.7      125
ryebread       9.2     4930    12.4      439     1.1       82
poundcake     24.8     1829     8.0      130      .4       31
crackers      15.1     3004    12.5      288      .5       50
milk          11.0     8867     6.1      310    10.5       18
evapmild       6.7     6035     8.4      422    15.1        9
butter        20.8     1473    10.8        9      .2        3
margarine     16.1     2817    20.6       17      .6        6
eggs          32.6     1857     2.9      238     1.0       52
cheese        24.2     1874     7.4      448    16.4       19
cream         14.1     1689     3.5       49     1.7        3
peanutbutter  17.9     2534    15.7      661     1.0       48
mayonnaise    16.7     1198     8.6       18      .2        8
crisco        20.3     2234    20.1        0      .0        0
lard           9.8     4628    41.7        0      .0        0
sirloinsteak  39.6     1145     2.9      166      .1       34
roundsteak    36.4     1246     2.2      214      .1       32
ribroast      29.2     1553     3.4      213      .1       33
chuckroast    22.6     2007     3.6      309      .2       46
plate         14.6     3107     8.5      404      .2       62
liver         26.8     1692     2.2      333      .2      139
lambleg       27.6     1643     3.1      245      .1       20
lambchops     36.6     1239     3.3      140      .1       15
porkchops     30.7     1477     3.5      196      .2       80
porkroast     24.2     1874     4.4      249      .3       37
bacon         25.6     1772    10.4      152      .2       23
ham           27.4     1655     6.7      212      .2       31
saltpork      16.0     2835    18.8      164      .1       26
chicken       30.3     1497     1.8      184      .1       30
veal          42.3     1072     1.7      156      .1       24
salmon        13.0     3489     5.8      705     6.8       45
apples         4.4     9072     5.8       27      .5       36
bananas        6.1     4982     4.9       60      .4       30
lemons        26.0     2380     1.0       21      .5       14
oranges       30.9     4439     2.2       40     1.1       18
greenbeans     7.1     5750     2.4      138     3.7       80
cabbage        3.7     8949     2.6      125     4.0       36
carrots        4.7     6080     2.7       73     2.8       43
celery         7.3     3915      .9       51     3.0       23
lettuce        8.2     2247      .4       27     1.1       22
onions         3.6    11844     5.8      166     3.8       59
potatoes      34.0    16810    14.3      336     1.8      118
spinach        8.1     4592     1.1      106      .0      138
sweetpotato    5.1     7649     9.6      138     2.7       54
peaches       16.8     4894     3.7       20      .4       10
pears         20.4     4030     3.0        8      .3        8
pineapple     21.3     3993     2.4       16      .4        8
asparagus     27.7     1945      .4       33      .3       12
cannedgrbn    10.0     5386     1.0       54     2.0       65
porkbeans      7.1     6389     7.5      364     4.0      134
corn          10.4     5452     5.2      136      .2       16
peas          13.8     4109     2.3      136      .6       45
tomatoes       8.6     6263     1.3       63      .7       38
tomatosoup     7.6     3917     1.6       71      .6       43
driedpeach    15.7     2889     8.5       87     1.7      173
prunes         9.0     4284    12.8       99     2.5      154
raisins        9.4     4524    13.5      104     2.5      136
driedpeas      7.9     5742    20.0     1367     4.2      345
limabeans      8.9     5097    17.4     1055     3.7      459
navybeans      5.9     7688    26.9     1691    11.4      792
coffee        22.4     2025      .0        0      .0        0
tea           17.4      652      .0        0      .0        0
cocoa          8.6     2637     8.7      237     3.0       72
chocolate     16.2     1400     8.0       77     1.3       39
sugar         51.7     8773    34.9        0      .0        0
cornsirup     13.7     4996    14.7        0      .5       74
molasses      13.6     3752     9.0        0    10.3      244
strawberry    20.5     2213     6.4       11      .4        7

:           vitaminA thiamine riboflavin  niacin  ascorbicAcid :=
#          (1000 IU)  (mg.)      (mg.)     (mg.)     (mg.)
flour           .0    55.4       33.3       441         0
macaroni        .0     3.2        1.9        68         0
cereal          .0    14.4        8.8       114         0
cornflakes      .0    13.5        2.3        68         0
cornmeal      30.9    17.4        7.9       106         0
grits           .0    10.6        1.6       110         0
rice            .0     2.0        4.8        60         0
oats            .0    37.1        8.9        64         0
whitebread      .0    13.8        8.5       126         0
wheatbread      .0    13.9        6.4       160         0
ryebread        .0     9.9        3.0        66         0
poundcake     18.9     2.8        3.0        17         0
crackers        .0      .0         .0         0         0
milk          16.8     4.0       16.0         7       177
evapmild      26.0     3.0       23.5        11        60
butter        44.2      .0         .2         2         0
margarine     55.8      .2         .0         0         0
eggs          18.6     2.8        6.5         1         0
cheese        28.1      .8       10.3         4         0
cream         16.9      .6        2.5         0        17
peanutbutter    .0     9.6        8.1       471         0
mayonnaise     2.7      .4         .5         0         0
crisco          .0      .0         .0         0         0
lard            .2      .0         .5         5         0
sirloinsteak    .2     2.1        2.9        69         0
roundsteak      .4     2.5        2.4        87         0
ribroast        .0      .0        2.0         0         0
chuckroast      .4     1.0        4.0       120         0
plate           .0      .9         .0         0         0
liver        169.2     6.4       50.8       316       525
lambleg         .0     2.8        3.0        86         0
lambchops       .0     1.7        2.7        54         0
porkchops       .0    17.4        2.7        60         0
porkroast       .0    18.2        3.6        79         0
bacon           .0     1.8        1.8        71         0
ham             .0     9.9        3.3        50         0
saltpork        .0     1.4        1.8         0         0
chicken         .1      .9        1.8        68        46
veal            .0     1.4        2.4        57         0
salmon         3.5     1.0        4.9       209         0
apples         7.3     3.6        2.7         5       544
bananas       17.4     2.5        3.5        28       498
lemons          .0      .5         .0         4       952
oranges       11.1     3.6        1.3        10      1993
greenbeans    69.0     4.3        5.8        37       862
cabbage        7.2     9.0        4.5        26      5369
carrots      188.5     6.1        4.3        89       608
celery          .9     1.4        1.4         9       313
lettuce      112.4     1.8        3.4        11       449
onions        16.6     4.7        5.9        21      1184
potatoes       6.7    29.4        7.1       198      2522
spinach      918.4     5.7       13.8        33      2755
sweetpotato  290.7     8.4        5.4        83      1912
peaches       21.5      .5        1.0        31       196
pears           .8      .8         .8         5        81
pineapple      2.0     2.8         .8         7       399
asparagus     16.3     1.4        2.1        17       272
cannedgrbn    53.9     1.6        4.3        32       431
porkbeans      3.5     8.3        7.7        56         0
corn          12.0     1.6        2.7        42       218
peas          34.9     4.9        2.5        37       370
tomatoes      53.2     3.4        2.5        36      1253
tomatosoup    57.9     3.5        2.4        67       862
driedpeach    86.8     1.2        4.3        55        57
prunes        85.7     3.9        4.3        65       257
raisins        4.5     6.3        1.4        24       136
driedpeas      2.9    28.7       18.4       162         0
limabeans      5.1    26.9       38.2        93         0
navybeans       .0    38.4       24.6       217         0
coffee          .0     4.0        5.1        50         0
tea             .0      .0        2.3        42         0
cocoa           .0     2.0       11.9        40         0
chocolate       .0      .9        3.4        14         0
sugar           .0      .0         .0         0         0
cornsirup       .0      .0         .0         5         0
molasses        .0     1.9        7.5       146         0
strawberry      .2      .2         .4         3         0
;

param allowance :=
calories       3
protein       70
calcium         .8
iron          12
vitaminA       5
thiamine       1.8
riboflavin     2.7
niacin        18
ascorbicAcid  75
;

end;

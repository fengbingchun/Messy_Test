/* Food Manufacture 1, section 12.1 in
 * Williams, "Model Building in Mathematical Programming"
 *
 * Sebastian Nowozin <nowozin@gmail.com>
 */

set oils;
set month;

/* Buying prices of the raw oils in the next six month. */
param buyingprices{month,oils};

/* Actual amount bought in each month. */
var buys{month,oils} >= 0;

/* Stock for each oil. */
var stock{month,oils} >= 0;

/* Price of the produced product */
param productprice >= 0;
param storagecost;

param oilhardness{oils} >= 0;

/* Actual amount of output oil produced in each month */
var production{m in month} >= 0;
var useoil{m in month, o in oils} >= 0;

maximize totalprofit:
    sum{m in month} productprice*production[m]
    - sum{m in month, o in oils} buyingprices[m,o]*buys[m,o]
    - sum{m in month, o in oils} storagecost*stock[m,o];

/* Constraints */

/* 1. Starting stock */
s.t. startstock{o in oils}:
    stock[1,o] = 500;
s.t. endstock{o in oils}:
    stock[6,o] + buys[6,o] - useoil[6,o] >= 500;

/* 2. Stock constraints */
s.t. stocklimit{m in month, o in oils}:
    stock[m,o] <= 1000;

s.t. production1{m in month, o in oils}:
    useoil[m,o] <= stock[m,o] + buys[m,o];
s.t. production2{m1 in month, m2 in month, o in oils : m2 = m1+1}:
    stock[m2,o] = stock[m1,o] + buys[m1,o] - useoil[m1,o];

s.t. production3a{m in month}:
    sum{o in oils} oilhardness[o]*useoil[m,o] >= 3*production[m];
s.t. production3b{m in month}:
    sum{o in oils} oilhardness[o]*useoil[m,o] <= 6*production[m];

s.t. production4{m in month}:
    production[m] = sum{o in oils} useoil[m,o];

/* 3. Refining constraints */
s.t. refine1{m in month}:
    useoil[m,"VEG1"]+useoil[m,"VEG2"] <= 200;
s.t. refine2{m in month}:
    useoil[m,"OIL1"]+useoil[m,"OIL2"]+useoil[m,"OIL3"] <= 250;

solve;

for {m in month} {
    printf "Month %d\n", m;
    printf "PRODUCE %4.2f tons, hardness %4.2f\n", production[m],
        (sum{o in oils} oilhardness[o]*useoil[m,o]) / (sum{o in oils} useoil[m,o]);

    printf "\tVEG1\tVEG2\tOIL1\tOIL2\tOIL3\n";
    printf "STOCK";
    printf "%d", m;
    for {o in oils} {
        printf "\t%4.2f", stock[m,o];
    }
    printf "\nBUY";
    for {o in oils} {
        printf "\t%4.2f", buys[m,o];
    }
    printf "\nUSE";
    printf "%d", m;
    for {o in oils} {
        printf "\t%4.2f", useoil[m,o];
    }
    printf "\n";
    printf "\n";
}
printf "Total profit: %4.2f\n",
    (sum{m in month} productprice*production[m]
    - sum{m in month, o in oils} buyingprices[m,o]*buys[m,o]
    - sum{m in month, o in oils} storagecost*stock[m,o]);
printf "      turnover: %4.2f\n",
    sum{m in month} productprice*production[m];
printf "      buying costs: %4.2f\n",
    sum{m in month, o in oils} buyingprices[m,o]*buys[m,o];
printf "      storage costs: %4.2f\n",
    sum{m in month, o in oils} storagecost*stock[m,o];


data;

param : oils : oilhardness :=
    VEG1    8.8
    VEG2    6.1
    OIL1    2.0
    OIL2    4.2
    OIL3    5.0 ;

set month := 1 2 3 4 5 6;

param buyingprices

:           VEG1    VEG2    OIL1    OIL2    OIL3    :=

1           110     120     130     110     115
2           130     130     110     90      115
3           110     140     130     100     95
4           120     110     120     120     125
5           100     120     150     110     105
6           90      100     140     80      135 ;

param productprice := 150;
param storagecost := 5;

end;

#  Model I Forest Estate Modelling using GLPK/MathProg
#  Reading and writing dbf files

#  by Noli Sicad --- nsicad@gmail.com
# 18 December 2009

#  Forest Management 4th Edition 
#  by Lawrence Davis, K. Norman Johnson, Pete Bettinger, Theodore Howard
#  Chapter 11 - Daniel Pickett 
#  http://warnell.forestry.uga.edu/Warnell/Bettinger/mgtbook/index.htm

#  Model I Formulation

/*  Note: This is not the full LP model mentioned in the book.
Some of the constraints are deliberately omitted in this model for the purpose of clarity.

The features of MathProg in this example are:
* reading and writing dbf from regular dbf files,
* reading dbf file (database of shapefile (stands.shp)) (e.g. area parameter),
* using the area data in the constraints and
* writing dbf file from result of LP model.

Model I - Harvest Scheduling formulation for Sustainable Forest Management (SFM)

Features are:
* Net Present Value for the objective function (Revenue - Cost)
* Harvest Constraints by period - Sustainable Yield per Period
* Even-Flow Constraint / Volume - Harvest Flow Constraint -  Alpha (1-Apha)
* Even-Flow Constraint / Volume - Harvest Flow Constraint - Beta  (1 +Beta)
* Forest / Land Constraint -- Total Area of the forest
* Forest Stand Constraint  -- Individual stands

What is next? -- Forest Mgt Carbon Accounting for Climate Change

Note: The model file that the data containing in
the dbf files is public domain material (so it is compatible with the
GNU GPL) and data can be found in 
http://warnell.forestry.uga.edu/Warnell/Bettinger/mgtbook/index.htm

# Noli Sicad --- nsicad@gmail.com

*/

set G_STAND_TYPE; # A, B, C

set I_CULTURAL_PRES; 
set J_MGT_YEAR; 

param K_PERIOD;
param Forest_Cost{G_STAND_TYPE,I_CULTURAL_PRES, J_MGT_YEAR}; # cost

param Yield_Table_Vol{G_STAND_TYPE, I_CULTURAL_PRES, J_MGT_YEAR, 1..K_PERIOD} >= 0;


param Alpha >= 0;
param Beta >= 0;

param TCost_Table{G_STAND_TYPE, I_CULTURAL_PRES, J_MGT_YEAR, 1..K_PERIOD} >= 0;

param NetRev_Table{G_STAND_TYPE, I_CULTURAL_PRES, J_MGT_YEAR, 1..K_PERIOD};


var XForestLand{g in G_STAND_TYPE, i in I_CULTURAL_PRES, j in J_MGT_YEAR} >= 0;


#reading dbf tables
table tab IN "xBASE" "standtype.dbf": G_STAND_TYPE <- [STAND];
display G_STAND_TYPE;


table tab2 IN "xBASE" "cultural_pres.dbf": I_CULTURAL_PRES <- [CUL_PRES];
display I_CULTURAL_PRES;

table tab3 IN "xBASE" "mgt_year.dbf": J_MGT_YEAR <- [MGT_YEAR];
display J_MGT_YEAR;

/*
param Forest_Cost{G_STAND_TYPE,I_CULTURAL_PRES, J_MGT_YEAR} default 0; # cost
*/

set S1, dimen 3;
table tab4 IN "xBASE" "Forest_Cost.dbf": S1 <- [STAND, CUL_PRES, MGT_YEAR],Forest_Cost ~FCOST;
display Forest_Cost;

set S2, dimen 4;
table tab5 IN "xBASE" "Yield_Table_Vol.dbf": S2 <- [STAND, CUL_PRES, MGT_YEAR, PERIOD],Yield_Table_Vol ~YIELD;
display Yield_Table_Vol;

set S3, dimen 4;
table tab5 IN "xBASE" "TCost_Table.dbf": S3 <- [STAND, CUL_PRES, MGT_YEAR, PERIOD],TCost_Table ~TCOST;
display TCost_Table;


set S4, dimen 4;
table tab5 IN "xBASE" "NetRev_Table.dbf": S4 <- [STAND, CUL_PRES, MGT_YEAR, PERIOD],NetRev_Table ~NETREV;
display NetRev_Table;


param MGT;

param Area_Stand_Indi{g in G_STAND_TYPE, m in 1..MGT} default 0; 

set ST, dimen 2;
table tab5 IN "xBASE" "stands.dbf": ST <- [VEG_TYPE, MGT], Area_Stand_Indi ~ACRES;
display Area_Stand_Indi;

param Area_Stand_Type{g in G_STAND_TYPE}:= sum {m in 1..MGT } Area_Stand_Indi[g,m];
display Area_Stand_Type;


param Total_Area := sum {g in G_STAND_TYPE, m in 1..MGT } Area_Stand_Indi[g,m];
display Total_Area;

param Harvest_Min_Vol_Period;


var NetPresentValue;

# Objective function
maximize Net_Present_Value: NetPresentValue;

subject to NPV:
   NetPresentValue = sum {g in G_STAND_TYPE, i in I_CULTURAL_PRES, j in J_MGT_YEAR} Forest_Cost[g,i,j] * XForestLand[g,i,j];

# Harvest Constraint by Period
subject to Harvest_Period_H {k in 1..K_PERIOD}:
   sum {g in G_STAND_TYPE, i in I_CULTURAL_PRES, j in J_MGT_YEAR} Yield_Table_Vol[g,i,j,k] * XForestLand[g,i,j] >= Harvest_Min_Vol_Period;
   

#Even-Flow Constraint / Volume - Harvest Flow Constraint - Alpha
subject to Even_Flow_Constaints_Alpha {k in 6..K_PERIOD-1}:
    (1 - Alpha) * sum {g in G_STAND_TYPE, i in I_CULTURAL_PRES, j in J_MGT_YEAR} Yield_Table_Vol[g,i,j,k] * XForestLand[g,i,j] -
    sum {g in G_STAND_TYPE,i in I_CULTURAL_PRES, j in J_MGT_YEAR} Yield_Table_Vol[g,i,j,k+1] * XForestLand[g,i,j] <= 0;

# Even-Flow Constraint / Volume - Harvest Flow Constraint - Beta
subject to Even_Flow_Constaints_Beta {k in 6..K_PERIOD-1}:
    (1 + Beta) * sum {g in G_STAND_TYPE, i in I_CULTURAL_PRES, j in J_MGT_YEAR} Yield_Table_Vol[g,i,j,k] * XForestLand[g,i,j] -
    sum {g in G_STAND_TYPE,i in I_CULTURAL_PRES, j in J_MGT_YEAR} Yield_Table_Vol[g,i,j,k+1] * XForestLand[g,i,j] >= 0;
   
# Forest / Land Constraints
subject to Total_Area_Constraint: 
  sum {g in G_STAND_TYPE, i in I_CULTURAL_PRES, j in J_MGT_YEAR} XForestLand[g,i,j] <= Total_Area;
display Total_Area;   

# Forest / Land Constraints for A B C
subject to Area {g in G_STAND_TYPE}:
   sum {i in I_CULTURAL_PRES,j in J_MGT_YEAR} XForestLand[g,i,j] = Area_Stand_Type[g];



solve;
#RESULT SECTION
printf '#################################\n';
printf 'Forest Management Model I - Noli Sicad\n';
printf '\n';
printf 'Net Present Value = %.2f\n', NetPresentValue;
printf '\n';

printf '\n';
printf 'Variables\n';
printf 'Stand_Type  Age_Class  Mgt_Presc  Sign Value \n';
printf{g in G_STAND_TYPE, i in I_CULTURAL_PRES, j in J_MGT_YEAR}:'%5s %10s %11s = %10.2f\n', g,i,j, XForestLand[g,i,j]; 
printf '\n';

printf 'Constraints\n';
printf 'Period Harvest Sign \n';
for {k in 1..K_PERIOD} {
 printf '%5s %10.2f >= %.3f\n', k, sum {g in G_STAND_TYPE, i in I_CULTURAL_PRES, j in J_MGT_YEAR} Yield_Table_Vol[g,i,j,k] * XForestLand[g,i,j], Harvest_Min_Vol_Period;
   }

# xbase (dbf) output
table Harvest{k in 1..K_PERIOD} OUT "xBASE" "HarvestArea1.dbf" "N(5)N(15,2)" :  k ~ Period, (sum {g in G_STAND_TYPE, i in I_CULTURAL_PRES, j in J_MGT_YEAR} Yield_Table_Vol[g,i,j,k] * XForestLand[g,i,j]) ~ H_Area;

# xbase (dbf) read
set S, dimen 2;
table tab2 IN "xBASE" "HarvestArea1.dbf": S <- [Period, H_Area];
display S;




printf '\n';
printf 'Constraint\n';
printf 'Harvest Period\n';
printf 'Type AgeClass  PrescMgt Period    Value\n';
printf{g in G_STAND_TYPE, i in I_CULTURAL_PRES, j in J_MGT_YEAR, k in 1..K_PERIOD}:'%5s %11s %11s %5s %10.2f\n', g,i,j, k, (Yield_Table_Vol[g,i,j,k] * XForestLand[g,i,j]); 


printf 'Even_Flow_Constaint_Alpha (1-Alpha)\n';
printf 'Period Sign \n';
for {k in 6..K_PERIOD-1} {
   printf "%s %10.2f <= %s\n", k, ((1 - Alpha) * sum {g in G_STAND_TYPE, i in I_CULTURAL_PRES, j in J_MGT_YEAR} Yield_Table_Vol[g,i,j,k] * XForestLand[g,i,j] - sum {g in G_STAND_TYPE,i in I_CULTURAL_PRES, j in J_MGT_YEAR} Yield_Table_Vol[g,i,j,k+1] * XForestLand[g,i,j]),0;
  }
printf '\n';


# Forest / Land Constraints
printf '\n';  
printf 'Total Area Constraint\n';
printf 'Type AgeClass  PrescMgt  Value Sign Total_Area \n';
printf '%5s <= %.3f\n',sum {g in G_STAND_TYPE, i in I_CULTURAL_PRES, j in J_MGT_YEAR} XForestLand[g,i,j], Total_Area;

printf 'Area\n';
printf 'Area Value Sign Areas_Stand\n';
for {g in G_STAND_TYPE} {
  printf '%5s %10.2f <= %.3f\n', g, sum {i in I_CULTURAL_PRES,j in J_MGT_YEAR} XForestLand[g,i,j],  Area_Stand_Type[g];
   }


#DATA SECTION 
      
data;

# Most of the data has been moved to dbf format

param MGT:=31;

param K_PERIOD:= 7;

param Alpha:= 0.20;
param Beta:= 0.20;

param Harvest_Min_Vol_Period:= 12000;

end;


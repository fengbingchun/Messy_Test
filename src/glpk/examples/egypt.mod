# EGYPT, a static model of fertilizer production
#
# References:
# Robert Fourer, David M. Gay and Brian W. Kernighan, "A Modeling Language
# for Mathematical Programming." Management Science 36 (1990) 519-554.

###  SETS  ###

set center;                # Locations from which final product may be shipped
set port within center;    # Locations at which imports can be received
set plant within center;   # Locations of plants

set region;                # Demand regions

set unit;                  # Productive units
set proc;                  # Processes

set nutr;                  # Nutrients

set c_final;               # Final products (fertilizers)
set c_inter;               # Intermediate products
set c_ship within c_inter; # Intermediates for shipment
set c_raw;                 # Domestic raw materials and miscellaneous inputs

set commod := c_final union c_inter union c_raw;

                           # All commodities

###  PARAMETERS  ###

param cf75 {region,c_final} >= 0;

                           # Consumption of fertilizer 1974-75 (1000 tpy)

param fn {c_final,nutr} >= 0;

                           # Nutrient content of fertilizers

param cn75 {r in region, n in nutr} := sum {c in c_final} cf75[r,c] * fn[c,n];

                           # Consumption of nutrients 1974-75 (1000 tpy)

param road {region,center} >= 0;

                           # Road distances

param rail_half {plant,plant} >= 0;
param rail {p1 in plant, p2 in plant} :=
    if rail_half[p1,p2] > 0 then rail_half[p1,p2] else rail_half[p2,p1];

                           # Interplant rail distances (kms)

param impd_barg {plant} >= 0;
param impd_road {plant} >= 0;

                           # Import distances (kms) by barge and road

param tran_final {pl in plant, r in region} :=
              if road[r,pl] > 0 then .5 + .0144 * road[r,pl] else 0;

param tran_import {r in region, po in port} :=
              if road[r,po] > 0 then .5 + .0144 * road[r,po] else 0;

param tran_inter {p1 in plant, p2 in plant} :=
              if rail[p1,p2] > 0 then 3.5 + .03 * rail[p1,p2] else 0;

param tran_raw {pl in plant} :=
            (if impd_barg[pl] > 0 then 1.0 + .0030 * impd_barg[pl] else 0)
          + (if impd_road[pl] > 0 then 0.5 + .0144 * impd_road[pl] else 0);

                           # Transport cost (le per ton) for:
                           #   final products, imported final products,
                           #   interplant shipment, imported raw materials

param io {commod,proc};    # Input-output coefficients

param util {unit,proc} >= 0;

                           # Capacity utilization coefficients

param p_imp {commod} >= 0; # Import Price (cif US$ per ton 1975)

param p_r {c_raw} >= 0;
param p_pr {plant,c_raw} >= 0;

param p_dom {pl in plant, c in c_raw} :=
              if p_r[c] > 0 then p_r[c] else p_pr[pl,c];

                           # Domestic raw material prices

param dcap {plant,unit} >= 0;

                           # Design capacity of plants (t/day)

param icap {u in unit, pl in plant} := 0.33 * dcap[pl,u];

                           # Initial capacity of plants (t/day)

param exch := 0.4;         # Exchange rate

param util_pct := 0.85;    # Utilization percent for initial capacity

###  DERIVED SETS OF "POSSIBILITIES"  ###

set m_pos {pl in plant} := {u in unit: icap[u,pl] > 0};

                           # At each plant, set of units for which there is
                           # initial capacity

set p_cap {pl in plant} :=
             {pr in proc: forall {u in unit: util[u,pr] > 0} u in m_pos[pl] };

                           # At each plant, set of processes for which
                           # all necessary units have some initial capacity

set p_except {plant} within proc;

                           # At each plant, list of processes that are
                           # arbitrarily ruled out

set p_pos {pl in plant} := p_cap[pl] diff p_except[pl];

                           # At each plant, set of possible processes

set cp_pos {c in commod} := {pl in plant: sum {pr in p_pos[pl]} io[c,pr] > 0};

set cc_pos {c in commod} := {pl in plant: sum {pr in p_pos[pl]} io[c,pr] < 0};

set c_pos {c in commod} := cp_pos[c] union cc_pos[c];

                           # For each commodity, set of plants that can
                           # produce it (cp_pos) or consume it (cc_pos),
                           # and their union (c_pos)

###  VARIABLES  ###

var Z {pl in plant, p_pos[pl]} >= 0;

                           # Z[pl,pr] is level of process pr at plant pl

var Xf {c in c_final, cp_pos[c], region} >= 0;

                           # Xf[c,pl,r] is amount of final product c
                           # shipped from plant pl to region r

var Xi {c in c_ship, cp_pos[c], cc_pos[c]} >= 0;

                           # Xi[c,p1,p2] is amount of intermediate c
                           # shipped from plant p1 to plant p2

var Vf {c_final,region,port} >= 0;

                           # Vf[c,r,po] is amount of final product c
                           # imported by region r from port po

var Vr {c in c_raw, cc_pos[c]} >= 0;

                           # Vr[c,pl] is amount of raw material c
                           # imported for use at plant pl

var U {c in c_raw, cc_pos[c]} >= 0;

                           # U[c,pl] is amount of raw material c
                           # purchased domestically for use at plant pl

var Psip;                  # Domestic recurrent cost
var Psil;                  # Transport cost
var Psii;                  # Import cost

###  OBJECTIVE  ###

minimize Psi:  Psip + Psil + Psii;

###  CONSTRAINTS  ###

subject to mbd {n in nutr, r in region}:

    sum {c in c_final} fn[c,n] *
                (sum {po in port} Vf[c,r,po] +
                 sum {pl in cp_pos[c]} Xf[c,pl,r])  >=  cn75[r,n];

                           # Total nutrients supplied to a region by all
                           # final products (sum of imports plus internal
                           # shipments from plants) must meet requirements

subject to mbdb {c in c_final, r in region: cf75[r,c] > 0}:

    sum {po in port} Vf[c,r,po] +
    sum {pl in cp_pos[c]} Xf[c,pl,r]  >=  cf75[r,c];

                           # Total of each final product supplied to each
                           # region (as in previous constraint) must meet
                           # requirements

subject to mb {c in commod, pl in plant}:

    sum {pr in p_pos[pl]} io[c,pr] * Z[pl,pr]

   + ( if c in c_ship then
                ( if pl in cp_pos[c] then sum {p2 in cc_pos[c]} Xi[c,pl,p2] )
              - ( if pl in cc_pos[c] then sum {p2 in cp_pos[c]} Xi[c,p2,pl] ))

   + ( if (c in c_raw and pl in cc_pos[c]) then
                 (( if p_imp[c] > 0 then Vr[c,pl] )
                + ( if p_dom[pl,c] > 0 then U[c,pl] )))

  >= if (c in c_final and pl in cp_pos[c]) then sum {r in region} Xf[c,pl,r];

                           # For each commodity at each plant:  sum of
                           #   (1) production or consumption at plant,
                           #   (2) inter-plant shipments in or out,
                           #   (3) import and domestic purchases (raw only)
                           # is >= 0 for raw materials and intermediates;
                           # is >= the total shipped for final products

subject to cc {pl in plant, u in m_pos[pl]}:

    sum {pr in p_pos[pl]} util[u,pr] * Z[pl,pr]  <=  util_pct * icap[u,pl];

                           # For each productive unit at each plant,
                           # total utilization by all processes
                           # may not exceed the unit's capacity

subject to ap:

    Psip  =  sum {c in c_raw, pl in cc_pos[c]} p_dom[pl,c] * U[c,pl];

                           # Psip is the cost of domestic raw materials,
                           # summed over all plants that consume them

subject to al:

    Psil  =  sum {c in c_final} (

               sum {pl in cp_pos[c], r in region}
                                              tran_final[pl,r] * Xf[c,pl,r]

             + sum {po in port, r in region} tran_import[r,po] * Vf[c,r,po] )

           + sum {c in c_ship, p1 in cp_pos[c], p2 in cc_pos[c]}
                                               tran_inter[p1,p2] * Xi[c,p1,p2]

           + sum {c in c_raw, pl in cc_pos[c]: p_imp[c] > 0}
                                                    tran_raw[pl] * Vr[c,pl];

                           # Total transport cost is sum of shipping costs for
                           #   (1) all final products from all plants,
                           #   (2) all imports of final products,
                           #   (3) all intermediates shipped between plants,
                           #   (4) all imports of raw materials

subject to ai:

    Psii / exch  =  sum {c in c_final, r in region, po in port}
                                                      p_imp[c] * Vf[c,r,po]

                  + sum {c in c_raw, pl in cc_pos[c]} p_imp[c] * Vr[c,pl];

                           # Total import cost -- at exchange rate --
                           # is sum of import costs for final products
                           # in each region and raw materials at each plant

###  DATA  ###

data;

set center := ASWAN HELWAN ASSIOUT KAFR_EL_ZT ABU_ZAABAL ABU_KIR TALKHA SUEZ ;

set port := ABU_KIR ;

set plant := ASWAN HELWAN ASSIOUT KAFR_EL_ZT ABU_ZAABAL ;

set region := ALEXANDRIA BEHERA GHARBIA KAFR_EL_SH DAKAHLIA DAMIETTA
              SHARKIA ISMAILIA SUEZ MENOUFIA KALUBIA GIZA BENI_SUEF FAYOUM
              MINIA ASSIOUT NEW_VALLEY SOHAG QUENA ASWAN ;

set unit := SULF_A_S SULF_A_P NITR_ACID AMM_ELEC AMM_C_GAS C_AMM_NITR
            AMM_SULF SSP ;

set proc := SULF_A_S SULF_A_P NITR_ACID AMM_ELEC AMM_C_GAS CAN_310 CAN_335
            AMM_SULF SSP_155 ;

set nutr := N P205 ;

set c_final := UREA CAN_260 CAN_310 CAN_335 AMM_SULF DAP SSP_155 C_250_55
               C_300_100 ;

set c_inter := AMMONIA NITR_ACID SULF_ACID ;

set c_ship := AMMONIA SULF_ACID ;

set c_raw := EL_ASWAN COKE_GAS PHOS_ROCK LIMESTONE EL_SULFUR PYRITES
             ELECTRIC BF_GAS WATER STEAM BAGS ;

set p_except[ASWAN] := CAN_335 ;
set p_except[HELWAN] := CAN_310 ;
set p_except[ASSIOUT] := ;
set p_except[KAFR_EL_ZT] := ;
set p_except[ABU_ZAABAL] := ;

param cf75  default 0.0  :

               CAN_260    CAN_310    CAN_335    AMM_SULF     UREA   :=

ALEXANDRIA        .           .         5.0        3.0        1.0
ASSIOUT          1.0        20.0       26.0        1.0       27.0
ASWAN             .         40.0         .          .          .
BEHERA           1.0          .        25.0       90.0       35.0
BENI_SUEF        1.0          .        15.0        1.0       20.0
DAKAHLIA         1.0          .        26.0       60.0       20.0
DAMIETTA          .           .         2.0       15.0        8.0
FAYOUM           1.0          .        20.0        6.0       20.0
GHARBIA           .           .        17.0       60.0       28.0
GIZA              .           .        40.0        6.0        2.0
ISMAILIA          .           .         4.0        6.0        2.0
KAFR_EL_SH       1.0          .        10.0       45.0       22.0
KALUBIA           .           .        25.0       16.0        7.0
MENOUFIA         1.0          .        24.0       21.0       30.0
MINIA            2.0        15.0       35.0        1.0       41.0
NEW_VALLEY        .           .          .          .         1.0
QUENA             .         95.0        2.0         .         3.0
SHARKIA          1.0          .        31.0       50.0       28.0
SOHAG             .         65.0        3.0         .         7.0
SUEZ              .           .         1.0         .          .

   :          SSP_155    C_250_55   C_300_100    DAP   :=

ALEXANDRIA       8.0         .          .         .
ASSIOUT         35.0        5.0         .1        .
ASWAN            8.0         .          .         .
BEHERA          64.0        1.0         .1        .1
BENI_SUEF       13.0        3.0         .         .
DAKAHLIA        52.0        1.0         .         .
DAMIETTA         5.0         .          .         .
FAYOUM          17.0        1.0         .         .
GHARBIA         57.0        1.0         .2        .1
GIZA            14.0        1.0         .1        .
ISMAILIA         4.0         .          .         .
KAFR_EL_SH      25.0        2.0         .1        .
KALUBIA         22.0        1.0         .         .1
MENOUFIA        33.0        2.0         .1        .1
MINIA           50.0        3.0         .2        .1
NEW_VALLEY       1.0         .          .         .
QUENA            8.0         .          .         .
SHARKIA         43.0        1.0         .1        .
SOHAG           20.0        1.0         .         .
SUEZ             1.0         .          .         .        ;

param fn  default 0.0 :      N     P205    :=

            AMM_SULF       .206     .
            CAN_260        .26      .
            CAN_310        .31      .
            CAN_335        .335     .
            C_250_55       .25      .055
            C_300_100      .30      .10
            DAP            .18      .46
            SSP_155        .        .15
            UREA           .46      .      ;

param road  default 0.0  :

            ABU_KIR ABU_ZAABAL ASSIOUT ASWAN HELWAN KAFR_EL_ZT SUEZ TALKHA :=

ALEXANDRIA      16     210       607    1135   244      119     362   187
ASSIOUT        616     420         .     518   362      504     527   518
ASWAN         1134     938       518       .   880     1022    1045  1036
BEHERA          76      50       547    1065   184       42     288   120
BENI_SUEF      359     163       257     775   105      248     270   261
DAKAHLIA       208     138       515    1033   152       58     219     3
DAMIETTA       267     216       596    1114   233      131     286    66
FAYOUM         341     145       308     826    88      230     252   243
GHARBIA        150      65       485    1003   122       20     226    55
GIZA           287      48       372     890    .9      133     169   146
ISMAILIA       365     142       536    1054   173      241      89   146
KAFR_EL_SH     145     105       525    1043   162       20     266    35
KALUBIA        190      97       439     957    76       66     180    81
MENOUFIA       157     154       472     990   109       33     213    90
MINIA          384     288       132     650   230      372     394   386
NEW_VALLEY     815     619       199     519   561      703     726   717
QUENA          858     662       242     276   604      746     769   760
SHARKIA        240      60       473     991   110       78     214    58
SOHAG          715     519        99     419   461      603     626   617
SUEZ           370     224       541    1059   178      246       .   298  ;

param rail_half  default 0  :

              KAFR_EL_ZT   ABU_ZAABAL    HELWAN     ASSIOUT   :=

ABU_ZAABAL         85            .           .          .
HELWAN            142           57           .          .
ASSIOUT           504          420         362          .
ASWAN            1022          938         880        518     ;

param :            impd_barg   impd_road :=

ABU_ZAABAL            210          .1
ASSIOUT               583         0
ASWAN                1087        10
HELWAN                183         0
KAFR_EL_ZT            104         6 ;

param io  default 0.0  :=

   [*,AMM_C_GAS]  AMMONIA        1.0
                  BF_GAS      -609.
                  COKE_GAS      -2.0
                  ELECTRIC   -1960.
                  STEAM         -4.
                  WATER       -700.

   [*,AMM_ELEC]   AMMONIA        1.0
                  EL_ASWAN     -12.0

   [*,AMM_SULF]   AMMONIA        -.26
                  AMM_SULF       1.0
                  BAGS         -22.
                  ELECTRIC     -19.
                  SULF_ACID      -.76
                  WATER        -17.

   [*,CAN_310]    AMMONIA        -.20
                  BAGS         -23.
                  CAN_310        1.0
                  LIMESTONE      -.12
                  NITR_ACID      -.71
                  STEAM          -.4
                  WATER        -49.

   [*,CAN_335]    AMMONIA        -.21
                  BAGS         -23.
                  CAN_335        1.0
                  LIMESTONE      -.04
                  NITR_ACID      -.76
                  STEAM          -.4
                  WATER        -49.

   [*,NITR_ACID]  AMMONIA        -.292
                  ELECTRIC    -231.
                  NITR_ACID      1.0
                  WATER          -.6

   [*,SSP_155]    BAGS         -22.
                  ELECTRIC     -14.
                  PHOS_ROCK      -.62
                  SSP_155        1.0
                  SULF_ACID      -.41
                  WATER         -6.

   [*,SULF_A_P]   ELECTRIC     -75.
                  PYRITES        -.826
                  SULF_ACID      1.0
                  WATER        -60.

   [*,SULF_A_S]   ELECTRIC     -50.
                  EL_SULFUR      -.334
                  SULF_ACID      1.0
                  WATER        -20. ;

param util  default 0  :=

   [*,*]   SULF_A_S SULF_A_S    1      SULF_A_P SULF_A_P   1
           NITR_ACID NITR_ACID  1      AMM_ELEC AMM_ELEC   1
           AMM_C_GAS AMM_C_GAS  1      SSP SSP_155         1
           C_AMM_NITR CAN_310   1      C_AMM_NITR CAN_335  1
           AMM_SULF AMM_SULF    1 ;

param p_imp  default 0.0  :=

     PYRITES       17.5           AMM_SULF      75.
     EL_SULFUR     55.            DAP          175.
     UREA         150.            SSP_155       80.
     CAN_260       75.            C_250_55     100.
     CAN_310       90.            C_300_100    130.
     CAN_335      100.   ;

param p_r  default 0.0  :=

     ELECTRIC     .007
     BF_GAS       .007
     WATER        .031
     STEAM       1.25
     BAGS         .28   ;

param p_pr  default 0.0  :=

 [HELWAN,COKE_GAS]              16.0
 [ASWAN,EL_ASWAN]                1.0

 [*,LIMESTONE]      ASWAN        1.2
                    HELWAN       1.2

 [*,PHOS_ROCK]      ABU_ZAABAL   4.0
                    ASSIOUT      3.5
                    KAFR_EL_ZT   5.0   ;

param dcap  default 0.0  :=

   [ABU_ZAABAL,*]   SSP          600
                    SULF_A_P     227
                    SULF_A_S     242

   [ASSIOUT,*]      SSP          600
                    SULF_A_S     250

   [ASWAN,*]        AMM_ELEC     450
                    C_AMM_NITR  1100
                    NITR_ACID    800

   [HELWAN,*]       AMM_C_GAS    172
                    AMM_SULF      24
                    C_AMM_NITR   364
                    NITR_ACID    282

   [KAFR_EL_ZT,*]   SSP          600
                    SULF_A_P      50
                    SULF_A_S     200  ;

end;

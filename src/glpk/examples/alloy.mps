*NAME:         ALLOY
*ROWS:         22
*COLUMNS:      20
*NONZERO:      203
*OPT SOLN:     2149.247891
*SOURCE:       Linear Programming--Aluminium Alloy Blending
*              Data Processing Application. N.Y.: IBM Corp.
*APPLICATION:  Aluminium Alloy Blending
*COMMENTS:     fixed MPS format
*              encoded by Andrew Makhorin <mao@gnu.org>
*
NAME          ALLOY
ROWS
 N  COST      $ Cost                   $
 G  ZN        $ Zinc Minimum           lbs
 L  ZX        $ Zinc Maximum           lbs
 G  CN        $ Copper Minimum         lbs
 L  CX        $ Copper Maximum         lbs
 G  MN        $ Magnesium Minimum      lbs
 L  MX        $ Magnesium Maximum      lbs
 G  CHN       $ Chromium Minimum       lbs
 L  CHX       $ Chromium Maximum       lbs
 G  BN        $ Beryllium Minimum      lbs
 L  BX        $ Beryllium Maximum      lbs
 L  IX        $ Iron Maximum           lbs
 L  SX        $ Silicon Maximum        lbs
 L  MGX       $ Manganese Maximum      lbs
 L  NX        $ Nickel Maximum         lbs
 L  TX        $ Titanium Maximum       lbs
 L  LX        $ Lead Maximum           lbs
 L  TNX       $ Tin Maximum            lbs
 L  BIX       $ Bismuth Maximum        lbs
 L  GX        $ General Impurities     lbs
 L  SCX       $ Scrap 1 Limit          lbs
 G  FL        $ Furnance Load          lbs
COLUMNS
* Pure Aluminium 1
    A1        COST             .28
              IX               .0004
              SX               .0005
              FL              1.0
* Pure Aluminium 2
    A2        COST             .26
              IX               .0006
              SX               .0006
              FL              1.0
* Pure Aluminium 3
    A3        COST             .25
              IX               .0011
              SX               .0007
              FL              1.0
* Pure Aluminium 4
    A4        COST             .23
              IX               .0026
              SX               .0012
              FL              1.0
* Pure Copper
    C         COST             .31
              CN              1.00
              CX              1.00
              FL              1.0
* Pure Magnesium
    M         COST             .38
              MN              1.00
              MX              1.00
              FL              1.0
* Beryllium/Aluminium Alloy
    B/A       COST            3.60
              BN              0.0600
              BX              0.0600
              FL              1.0
* Pure Zinc
    Z         COST             .22
              ZN               .95
              ZX               .95
              FL              1.0
* Chromium Aluminium Alloy
    C/A       COST             .27
              CHN              .0300
              CHX              .0300
              FL              1.0
* Scrap 1
    SC1       COST             .21
              ZN               .0009
              ZX               .0009
              CN               .0444
              CX               .0444
              MN               .0042
              MX               .0042
              CHN              .0001
              CHX              .0001
              IX               .0024
              SX               .0101
              MGX              .0079
              NX               .0001
              TX               .0004
              LX               .0001
              TNX              .0001
              GX               .0001
              SCX             1.00
              FL              1.0
* Scrap 2
    SC2       COST             .20
              ZN               .0012
              ZX               .0012
              CN               .0026
              CX               .0026
              MN               .0060
              MX               .0060
              CHN              .0018
              CHX              .0018
              IX               .0026
              SX               .0106
              MGX              .0003
              NX               .0002
              TX               .0004
              LX               .0001
              TNX              .0001
              GX               .0002
              FL              1.0
* Scrap 3
    SC3       COST             .21
              ZN               .0568
              ZX               .0568
              CN               .0152
              CX               .0152
              MN               .0248
              MX               .0248
              CHN              .0020
              CHX              .0020
              IX               .0016
              SX               .0013
              MGX              .0005
              TX               .0004
              LX               .0003
              TNX              .0003
              FL              1.0
* Scrap 4
    SC4       COST             .20
              ZN               .0563
              ZX               .0563
              CN               .0149
              CX               .0149
              MN               .0238
              MX               .0238
              CHN              .0019
              CHX              .0019
              IX               .0019
              SX               .0011
              MGX              .0004
              TX               .0004
              LX               .0003
              TNX              .0003
              FL              1.0
* Scrap 5
    SC5       COST             .21
              ZN               .0460
              ZX               .0460
              CN               .0071
              CX               .0071
              MN               .0343
              MX               .0343
              CHN              .0013
              CHX              .0013
              IX               .0017
              SX               .0013
              MGX              .0018
              TX               .0002
              LX               .0002
              TNX              .0002
              FL              1.0
* Scrap 6
    SC6       COST             .20
              ZN               .0455
              ZX               .0455
              CN               .0071
              CX               .0071
              MN               .0343
              MX               .0343
              IX               .0016
              SX               .0011
              MGX              .0017
              TX               .0002
              LX               .0002
              TNX              .0002
              FL              1.0
* Scrap 7
    SC7       COST             .21
              ZN               .0009
              ZX               .0009
              CN               .0447
              CX               .0447
              MN               .0143
              MX               .0143
              IX               .0026
              SX               .0013
              MGX              .0052
              TX               .0003
              LX               .0001
              TNX              .0001
              FL              1.0
* Scrap 8
    SC8       COST             .20
              ZN               .0006
              ZX               .0006
              CN               .0623
              CX               .0623
              IX               .0017
              SX               .0010
              MGX              .0025
              TX               .0005
              LX               .0001
              TNX              .0001
              GX               .0025
              FL              1.0
* Scrap 9
    SC9       COST             .21
              ZN               .0009
              ZX               .0009
              CN               .0034
              CX               .0034
              MN               .0093
              MX               .0093
              CHN              .0019
              CHX              .0019
              IX               .0030
              SX               .0062
              MGX              .0002
              TX               .0003
              BIX              .0005
              FL              1.0
* Scrap 10
    SC10      COST             .20
              ZN               .0008
              ZX               .0008
              CN               .0003
              CX               .0003
              MN               .0249
              MX               .0249
              CHN              .0016
              CHX              .0016
              IX               .0015
              SX               .0011
              MGX              .0002
              FL              1.0
* Scrap 11
    SC11      COST             .21
              ZN               .0675
              ZX               .0675
              CN               .0195
              CX               .0195
              MN               .0265
              MX               .0265
              CHN              .0020
              CHX              .0020
              IX               .0014
              SX               .0008
              MGX              .0002
              FL              1.0
RHS
              ZN            555.
              ZX            590.
              CN            140.0
              CX            190.0
              MN            245.0
              MX            275.0
              CHN            19.0
              CHX            22.0
              BN              2.0
              BX              4.0
              IX             15.0
              SX             10.0
              MGX             3.0
              NX              2.0
              TX              2.0
              LX              2.0
              TNX             2.0
              BIX             8.0
              GX              8.0
              SCX           900.0
              FL          10000.
ENDATA

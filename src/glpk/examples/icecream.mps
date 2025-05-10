*NAME:         ICECREAM
*ROWS:         17
*COLUMNS:      27
*NONZERO:      264
*OPT SOLN:     962.8214691
*SOURCE:       Linear Programming--Ice Cream Blending
*              Data Processing Application. N.Y.: IBM Corp.
*APPLICATION:  Ice Cream Blending
*COMMENTS:     fixed MPS format
*              encoded by Andrew Makhorin <mao@gnu.org>
*
NAME          ICECREAM
ROWS
 N  COST      $ Minimum cost           $
 G  MIN.BF    $ Butterfat              lbs
 L  MAX.BF
 G  MIN.MSNF  $ Milk solids (nonfat)   lbs
 L  MAX.MSNF
 G  MIN.TMS   $ Total milk solids      lbs
 L  MAX.TMS
 G  MIN.SUG   $ Sweetness              lbs
 L  MAX.SUG
 L  CSS       $ Corn syrup solids      lbs
 G  MIN.TS    $ Total solids           lbs
 L  MAX.TS
 G  MIN.H2O   $ Water                  lbs
 L  MAX.H2O
 E  STAB      $ Stabilizer             lbs
 E  EMUL      $ Emulsifier             lbs
 E  YIELD     $ Amount to be made      lbs
COLUMNS
* Cream (40%)
    I1        COST           27.9
              MIN.BF           .40
              MAX.BF           .40
              MIN.MSNF         .054
              MAX.MSNF         .054
              MIN.TMS          .454
              MAX.TMS          .454
              MIN.TS           .454
              MAX.TS           .454
              MIN.H2O          .546
              MAX.H2O          .546
              YIELD           1
* Cream (38%)
    I2        COST           26.3
              MIN.BF           .38
              MAX.BF           .38
              MIN.MSNF         .056
              MAX.MSNF         .056
              MIN.TMS          .436
              MAX.TMS          .436
              MIN.TS           .436
              MAX.TS           .436
              MIN.H2O          .564
              MAX.H2O          .564
              YIELD           1
* Milk (3.2%)
    I3        COST            3.2
              MIN.BF           .032
              MAX.BF           .032
              MIN.MSNF         .087
              MAX.MSNF         .087
              MIN.TMS          .119
              MAX.TMS          .119
              MIN.TS           .119
              MAX.TS           .119
              MIN.H2O          .881
              MAX.H2O          .881
              YIELD           1
* Milk (3.4%)
    I4        COST            3.2
              MIN.BF           .034
              MAX.BF           .034
              MIN.MSNF         .087
              MAX.MSNF         .087
              MIN.TMS          .121
              MAX.TMS          .121
              MIN.TS           .121
              MAX.TS           .121
              MIN.H2O          .879
              MAX.H2O          .879
              YIELD           1
* Milk (3.5%)
    I5        COST            3.3
              MIN.BF           .035
              MAX.BF           .035
              MIN.MSNF         .087
              MAX.MSNF         .087
              MIN.TMS          .122
              MAX.TMS          .122
              MIN.TS           .122
              MAX.TS           .122
              MIN.H2O          .879
              MAX.H2O          .879
              YIELD           1
* Milk (3.6%)
    I6        COST            3.3
              MIN.BF           .036
              MAX.BF           .036
              MIN.MSNF         .087
              MAX.MSNF         .087
              MIN.TMS          .123
              MAX.TMS          .123
              MIN.TS           .123
              MAX.TS           .123
              MIN.H2O          .877
              MAX.H2O          .877
              YIELD           1
* Milk (3.7%)
    I7        COST            3.4
              MIN.BF           .037
              MAX.BF           .037
              MIN.MSNF         .087
              MAX.MSNF         .087
              MIN.TMS          .124
              MAX.TMS          .124
              MIN.TS           .124
              MAX.TS           .124
              MIN.H2O          .876
              MAX.H2O          .876
              YIELD           1
* Milk (3.8%)
    I8        COST            3.5
              MIN.BF           .038
              MAX.BF           .038
              MIN.MSNF         .087
              MAX.MSNF         .087
              MIN.TMS          .125
              MAX.TMS          .125
              MIN.TS           .125
              MAX.TS           .125
              MIN.H2O          .875
              MAX.H2O          .875
              YIELD           1
* Milk (3.9%)
    I9        COST            3.5
              MIN.BF           .039
              MAX.BF           .039
              MIN.MSNF         .086
              MAX.MSNF         .086
              MIN.TMS          .125
              MAX.TMS          .125
              MIN.TS           .125
              MAX.TS           .125
              MIN.H2O          .875
              MAX.H2O          .875
              YIELD           1
* Milk (4.0%)
    I10       COST            3.6
              MIN.BF           .040
              MAX.BF           .040
              MIN.MSNF         .086
              MAX.MSNF         .086
              MIN.TMS          .126
              MAX.TMS          .126
              MIN.TS           .126
              MAX.TS           .126
              MIN.H2O          .874
              MAX.H2O          .874
              YIELD           1
* Milk (4.2%)
    I11       COST            3.7
              MIN.BF           .042
              MAX.BF           .042
              MIN.MSNF         .086
              MAX.MSNF         .086
              MIN.TMS          .128
              MAX.TMS          .128
              MIN.TS           .128
              MAX.TS           .128
              MIN.H2O          .872
              MAX.H2O          .872
              YIELD           1
* Skim Milk
    I12       COST            1.8
              MIN.MSNF         .09
              MAX.MSNF         .09
              MIN.TMS          .09
              MAX.TMS          .09
              MIN.TS           .09
              MAX.TS           .09
              MIN.H2O          .91
              MAX.H2O          .91
              YIELD           1
* Condensed Whole Milk
    I13       COST            7.6
              MIN.BF           .08
              MAX.BF           .08
              MIN.MSNF         .2
              MAX.MSNF         .2
              MIN.TMS          .28
              MAX.TMS          .28
              MIN.TS           .28
              MAX.TS           .28
              MIN.H2O          .72
              MAX.H2O          .72
              YIELD           1
* Condensed Skim Milk (28%)
    I14       COST            3.9
              MIN.MSNF         .28
              MAX.MSNF         .28
              MIN.TMS          .28
              MAX.TMS          .28
              MIN.TS           .28
              MAX.TS           .28
              MIN.H2O          .72
              MAX.H2O          .72
              YIELD           1
* Condensed Skim Milk (30%)
    I15       COST            4.9
              MIN.MSNF         .3
              MAX.MSNF         .3
              MIN.TMS          .3
              MAX.TMS          .3
              MIN.TS           .3
              MAX.TS           .3
              MIN.H2O          .7
              MAX.H2O          .7
              YIELD           1
* Condensed Skim Milk (32%)
    I16       COST            4.5
              MIN.MSNF         .32
              MAX.MSNF         .32
              MIN.TMS          .32
              MAX.TMS          .32
              MIN.TS           .32
              MAX.TS           .32
              MIN.H2O          .68
              MAX.H2O          .68
              YIELD           1
* Dry Skim Milk
    I17       COST           14.8
              MIN.BF           .01
              MAX.BF           .01
              MIN.MSNF         .96
              MAX.MSNF         .96
              MIN.TMS          .97
              MAX.TMS          .97
              MIN.TS           .97
              MAX.TS           .97
              MIN.H2O          .03
              MAX.H2O          .03
              YIELD           1
* Dry Buttermilk
    I18       COST           15.0
              MIN.BF           .05
              MAX.BF           .05
              MIN.MSNF         .92
              MAX.MSNF         .92
              MIN.TMS          .97
              MAX.TMS          .97
              MIN.TS           .97
              MAX.TS           .97
              MIN.H2O          .03
              MAX.H2O          .03
              YIELD           1
* Dry Whey Solids
    I19       COST           10.7
              MIN.MSNF         .95
              MAX.MSNF         .95
              MIN.TMS          .95
              MAX.TMS          .95
              MIN.TS           .95
              MAX.TS           .95
              MIN.H2O          .05
              MAX.H2O          .05
              YIELD           1
* Dry Sucrose
    I20       COST           10.2
              MIN.SUG         1.0
              MAX.SUG         1.0
              MIN.TS          1.0
              MAX.TS          1.0
              YIELD           1
* Cane Syrup
    I21       COST            9.9
              MIN.SUG          .67
              MAX.SUG          .67
              MIN.TS           .67
              MAX.TS           .67
              MIN.H2O          .33
              MAX.H2O          .33
              YIELD           1
* Corn Sgr. Solids (50% Sweetness)
    I22       COST            7.0
              MIN.SUG          .5
              MAX.SUG          .5
              CSS             1.0
              MIN.TS          1.0
              MAX.TS          1.0
              YIELD           1
* Corn Sgr. Solids (45% Sweetness)
    I23       COST            9.0
              MIN.SUG          .45
              MAX.SUG          .45
              CSS             1.0
              MIN.TS          1.0
              MAX.TS          1.0
              YIELD           1
* Corn Syrup
    I24       COST            6.6
              MIN.SUG          .4
              MAX.SUG          .4
              CSS              .8
              MIN.TS           .8
              MAX.TS           .8
              MIN.H2O          .2
              MAX.H2O          .2
              YIELD           1
* Stabilizer
    I25       COST           55.0
              STAB            1.0
              YIELD           1
* Emulsifier
    I26       COST           78.0
              EMUL            1.0
              YIELD           1
* Water
    I27       COST            0
              MIN.H2O         1.0
              MAX.H2O         1.0
              YIELD           1
RHS
              MIN.BF         10
              MAX.BF         16
              MIN.MSNF       10.5
              MAX.MSNF       13
              MIN.TMS        20.5
              MAX.TMS        25
              MIN.SUG        11
              MAX.SUG        17
              CSS             6
              MIN.TS         37.5
              MAX.TS         41.5
              MIN.H2O        58.5
              MAX.H2O        62.5
              STAB             .37
              EMUL             .01
              YIELD         100
BOUNDS
 UP           I1             10
 LO           I6             40
 UP           I19             4
ENDATA

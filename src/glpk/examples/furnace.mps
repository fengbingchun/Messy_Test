*NAME:         FURNACE
*ROWS:         18
*COLUMNS:      18
*NONZERO:      90
*OPT SOLN:     2141.923551
*SOURCE:       Linear Programming--Electric-Arc Furnace Steelmaking
*              Data Processing Application. N.Y.: IBM Corp.
*APPLICATION:  Electric-Arc Furnace Steelmaking
*COMMENTS:     fixed MPS format
*              encoded by Andrew Makhorin <mao@gnu.org>
*
NAME          FURNACE
ROWS
 N  VALUE     $ Price per pound (of initial charge materials)
 E  CR        $ Chromium
 E  MN        $ Manganese
 E  SI        $ Silicon
 E  C         $ Carbon
 E  FE        $ Iron
 E  TOTCHG    $ Total elements charged
 E  CRSLAG    $ Chromium-oxidized-to-slag relationship
 E  TOTCRS    $ Total modified chromium specification constraint
 E  MN/CR     $ Total manganese specification constraint
 E  FESLAG    $ Iron-oxidized-to-slag relationship
 G  ENDFE     $ Total iron specification constraint
 L  CSPEC     $ Total carbon specification constraint
 E  BASE      $ Basicity relationship
 L  SISPEC    $ Total silicon specification constraint
 G  TOTAL     $ Total end metal
 L  TOTRS4    $ Inventory limitation on 430 grade scrap
 L  TOTRCF    $ Inventory limitation on low-carbon ferrochrome
COLUMNS
* Steel scrap
    STSCP     VALUE            .02
              CR              0
              MN               .01
              SI               .002
              C                .006
              FE               .982
* 430 grade scrap
    SP430     VALUE            .075
              CR               .16
              MN               .01
              SI               .0095
              C                .0012
              FE               .8143
              TOTRS4          1
* High-carbon ferrochrome
    HCFCR     VALUE            .27
              CR               .556
              MN              0
              SI               .02
              C                .08
              FE               .334
* Low-carbon ferrochrome
    LCFCR     VALUE            .40
              CR               .65
              MN              0
              SI               .01
              C                .0009
              FE               .3391
              TOTRCF          1
* Chromium initially charged
    CRIT      VALUE           0
              CR             -1
              TOTCHG          1
              CRSLAG          1
* Manganese initially charged
    MNIT      VALUE           0
              MN             -1
              TOTCHG          1
              CRSLAG          1
              MN/CR            .98
* Silicon initially charged
    SIIT      VALUE           0
              SI             -1
              TOTCHG          1
              CSPEC          -5
              BASE            2.14
              TOTAL          -1
* Carbon initially charged
    CEIT      VALUE           0
              C              -1
              TOTCHG          1
              TOTAL          -1
* Iron initially charged
    FEIT      VALUE           0
              FE             -1
              TOTCHG          1
              ENDFE           1
* Total initial charge weight
    TICW      VALUE           0
              TOTCHG         -1
              CRSLAG          -.074
              TOTCRS           .074
              FESLAG           .075
              CSPEC           5
              TOTAL           1
* Modified chromium in the slag
    ISCR      VALUE           0
              CRSLAG         -1
              TOTCRS           .95
              FESLAG         -1
              CSPEC           -.25
              SISPEC          -.395
              TOTAL           -.05
* Chrome silicide additive at refining stage
    CRSI      VALUE            .27
              TOTCRS           .39
              ENDFE            .18
              BASE            2.7606
              SISPEC           .43
              TOTAL            .57
* 430 grade scrap at refining stage
    RS430     VALUE            .075
              TOTCRS           .17
              MN/CR            .01
              ENDFE            .8143
              CSPEC          12
              SISPEC           .0095
              TOTAL           1
              TOTRS4          1
* Low-carbon ferrochrome at refining stage
    RCFCR     VALUE            .40
              TOTCRS           .65
              ENDFE            .3391
              CSPEC           9
              SISPEC           .01
              TOTAL           1
              TOTRCF          1
* Iron in the slag
    ISFE      VALUE           0
              FESLAG         -1
              ENDFE           -.05
              CSPEC           -.25
              SISPEC          -.238
              TOTAL           -.05
* Lime at refining stage
    LIME      VALUE            .01
              BASE           -2
* Low-carbon ferrochrome at finishing stage
    FCFCR     VALUE            .40
              TOTCRS           .65
              ENDFE            .3391
              CSPEC           9
              SISPEC           .01
              TOTAL           1
              TOTRCF          1
* Slack in the chromium and manganese specifications
    SIS       VALUE           0
              TOTCRS          1
              MN/CR           1
RHS
              TOTCRS       3400
              MN/CR         200
              ENDFE       16200
              CSPEC      100000
              SISPEC        200
              TOTAL       20000
              TOTRS4       2000
              TOTRCF       2000
BOUNDS
 UP           HCFCR        2000
ENDATA

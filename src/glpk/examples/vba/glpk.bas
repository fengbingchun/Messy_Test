Attribute VB_Name = "glpk"
' glpk.bas
'
' Copyright (C) 2017, Heinrich Schuchardt <xypron.glpk@gmx.de>

' Copyright (C) 2000, 2001, 2002, 2003, 2004, 2005, 2006, 2007, 2008,
' 2009, 2010, 2011, 2013, 2014, 2015, 2016 Andrew Makhorin, Department
' for Applied Informatics, Moscow Aviation Institute, Moscow, Russia.
' All rights reserved. E-mail: <mao@gnu.org>.
'
' This program is free software: you can redistribute it and/or modify
' it under the terms of the GNU General Public License as published by
' the Free Software Foundation, either version 3 of the License, or
' (at your option) any later version.
'
' This program is distributed in the hope that it will be useful,
' but WITHOUT ANY WARRANTY; without even the implied warranty of
' MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
' GNU General Public License for more details.
'
' You should have received a copy of the GNU General Public License
' along with this program.  If not, see <http://www.gnu.org/licenses/>.
' You should have received a copy of the GNU General Public License
' along with GLPK. If not, see <http://www.gnu.org/licenses/>.

Option Explicit
' error handling
Public Const GLPK_LIB_ERROR = &HE77  ' Error in GLPK library

' optimization direction flag:
Public Const GLP_MIN = 1             ' minimization
Public Const GLP_MAX = 2             ' maximization

' kind of structural variable:
Public Const GLP_CV = 1              ' continuous variable
Public Const GLP_IV = 2              ' long variable
Public Const GLP_BV = 3              ' binary variable

' type of auxiliary/structural variable:
Public Const GLP_FR = 1              ' free variable
Public Const GLP_LO = 2              ' variable with lower bound
Public Const GLP_UP = 3              ' variable with upper bound
Public Const GLP_DB = 4              ' double-bounded variable
Public Const GLP_FX = 5              ' fixed variable

' status of auxiliary/structural variable:
Public Const GLP_BS = 1              ' basic variable
Public Const GLP_NL = 2              ' non-basic variable on lower bound
Public Const GLP_NU = 3              ' non-basic variable on upper bound
Public Const GLP_NF = 4              ' non-basic free variable
Public Const GLP_NS = 5              ' non-basic fixed variable

' scaling options:
Public Const GLP_SF_GM = &H1         ' perform geometric mean scaling
Public Const GLP_SF_EQ = &H10        ' perform equilibration scaling
Public Const GLP_SF_2N = &H20        ' round scale factors to power of two
Public Const GLP_SF_SKIP = &H40      ' skip if problem is well scaled
Public Const GLP_SF_AUTO = &H80      ' choose scaling options automatically

' solution indicator:
Public Const GLP_SOL = 1             ' basic solution
Public Const GLP_IPT = 2             ' interior-point solution
Public Const GLP_MIP = 3             ' mixed long solution

' solution status:
Public Const GLP_UNDEF = 1           ' solution is undefined
Public Const GLP_FEAS = 2            ' solution is feasible
Public Const GLP_INFEAS = 3          ' solution is infeasible
Public Const GLP_NOFEAS = 4          ' no feasible solution exists
Public Const GLP_OPT = 5             ' solution is optimal
Public Const GLP_UNBND = 6           ' solution is unbounded

' factorization type:
Public Const GLP_BF_LUF = &H0        ' plain LU-factorization
Public Const GLP_BF_BTF = &H10       ' block triangular LU-factorization
Public Const GLP_BF_FT = &H1         ' LUF + Forrest-Tomlin
Public Const GLP_BF_BG = &H2         ' LUF + Schur compl. + Bartels-Golub
Public Const GLP_BF_GR = &H3         ' LUF + Schur compl. + Givens rotation

' message level:
Public Const GLP_MSG_OFF = 0         ' no output
Public Const GLP_MSG_ERR = 1         ' warning and error messages only
Public Const GLP_MSG_ON = 2          ' normal output
Public Const GLP_MSG_ALL = 3         ' full output
Public Const GLP_MSG_DBG = 4         ' debug output

' simplex method:
Public Const GLP_PRIMAL = 1          ' use primal simplex
Public Const GLP_DUALP = 2           ' use dual if it fails, use primal
Public Const GLP_DUAL = 3            ' use dual simplex

' pricing technique:
Public Const GLP_PT_STD = &H11       ' standard (Dantzig rule)
Public Const GLP_PT_PSE = &H22       ' projected steepest edge

' ratio test technique:
Public Const GLP_RT_STD = &H11       ' standard (textbook)
Public Const GLP_RT_HAR = &H22       ' two-pass Harris' ratio test
Public Const GLP_RT_FLIP = &H33      ' long-step (flip-flop) ratio test

' option to use A or N:
Public Const GLP_USE_AT = 1          ' use A matrix in row-wise format
Public Const GLP_USE_NT = 2          ' use N matrix in row-wise format

' ordering algorithm
Public Const GLP_ORD_NONE = 0        ' natural (original) ordering
Public Const GLP_ORD_QMD = 1         ' quotient minimum degree (QMD)
Public Const GLP_ORD_AMD = 2         ' approx. minimum degree (AMD)
Public Const GLP_ORD_SYMAMD = 3      ' approx. minimum degree (SYMAMD)

' branching technique:
Public Const GLP_BR_FFV = 1          ' first fractional variable
Public Const GLP_BR_LFV = 2          ' last fractional variable
Public Const GLP_BR_MFV = 3          ' most fractional variable
Public Const GLP_BR_DTH = 4          ' heuristic by Driebeck and Tomlin
Public Const GLP_BR_PCH = 5          ' hybrid pseudocost heuristic

' backtracking technique:
Public Const GLP_BT_DFS = 1          ' depth first search
Public Const GLP_BT_BFS = 2          ' breadth first search
Public Const GLP_BT_BLB = 3          ' best local bound
Public Const GLP_BT_BPH = 4          ' best projection heuristic

' preprocessing technique:
Public Const GLP_PP_NONE = 0         ' disable preprocessing
Public Const GLP_PP_ROOT = 1         ' preprocessing only on root level
Public Const GLP_PP_ALL = 2          ' preprocessing on all levels

' row origin flag:
Public Const GLP_RF_REG = 0           ' regular constraint
Public Const GLP_RF_LAZY = 1          ' "lazy" constraint
Public Const GLP_RF_CUT = 2           ' cutting plane constraint

' row class descriptor:
Public Const GLP_RF_GMI = 1           ' Gomory's mixed integer cut
Public Const GLP_RF_MIR = 2           ' mixed integer rounding cut
Public Const GLP_RF_COV = 3           ' mixed cover cut
Public Const GLP_RF_CLQ = 4           ' clique cut

' enable/disable flag:
Public Const GLP_ON = 1              ' enable something
Public Const GLP_OFF = 0             ' disable something

' reason codes:
Public Const GLP_IROWGEN = &H1       ' request for row generation
Public Const GLP_IBINGO = &H2        ' better long solution found
Public Const GLP_IHEUR = &H3         ' request for heuristic solution
Public Const GLP_ICUTGEN = &H4       ' request for cut generation
Public Const GLP_IBRANCH = &H5       ' request for branching
Public Const GLP_ISELECT = &H6       ' request for subproblem selection
Public Const GLP_IPREPRO = &H7       ' request for preprocessing

' branch selection indicator:
Public Const GLP_NO_BRNCH = 0        ' select no branch
Public Const GLP_DN_BRNCH = 1        ' select down-branch
Public Const GLP_UP_BRNCH = 2        ' select up-branch

' return codes:
Public Const GLP_EBADB = &H1         ' invalid basis
Public Const GLP_ESING = &H2         ' singular matrix
Public Const GLP_ECOND = &H3         ' ill-conditioned matrix
Public Const GLP_EBOUND = &H4        ' invalid bounds
Public Const GLP_EFAIL = &H5         ' solver failed
Public Const GLP_EOBJLL = &H6        ' objective lower limit reached
Public Const GLP_EOBJUL = &H7        ' objective upper limit reached
Public Const GLP_EITLIM = &H8        ' iteration limit exceeded
Public Const GLP_ETMLIM = &H9        ' time limit exceeded
Public Const GLP_ENOPFS = &HA        ' no primal feasible solution
Public Const GLP_ENODFS = &HB        ' no dual feasible solution
Public Const GLP_EROOT = &HC         ' root LP optimum not provided
Public Const GLP_ESTOP = &HD         ' search terminated by application
Public Const GLP_EMIPGAP = &HE       ' relative mip gap tolerance reached
Public Const GLP_ENOFEAS = &HF       ' no primal/dual feasible solution
Public Const GLP_ENOCVG = &H10       ' no convergence
Public Const GLP_EINSTAB = &H11      ' numerical instability
Public Const GLP_EDATA = &H12        ' invalid data
Public Const GLP_ERANGE = &H13       ' result out of range

' condition indicator:
Public Const GLP_KKT_PE = 1          ' primal equalities
Public Const GLP_KKT_PB = 2          ' primal bounds
Public Const GLP_KKT_DE = 3          ' dual equalities
Public Const GLP_KKT_DB = 4          ' dual bounds
Public Const GLP_KKT_CS = 5          ' complementary slackness

' MPS file format:
Public Const GLP_MPS_DECK = 1        ' fixed (ancient)
Public Const GLP_MPS_FILE = 2        ' free (modern)

Public Type glp_bfcp
  ' basis factorization control parameters
  msg_lev As Long                    ' (reserved)
  typ As Long                       ' factorization type
  lu_size As Long                    ' luf.sv_size
  align_1 As Long                    ' only used for alignment
  piv_tol As Double                  ' luf.piv_tol
  piv_lim As Long                    ' luf.piv_lim
  suhl As Long                       ' luf.suhl
  eps_tol As Double                  ' luf.eps_tol
  max_gro As Double                  ' luf.max_gro
  nfs_max As Long                    ' fhv.hh_max
  align_2 As Long                    ' only used for alignment
  upd_tol As Double                  ' fhv.upd_tol
  nrs_max As Long                    ' lpf.n_max
  rs_size As Long                    ' lpf.v_size
  foo_bar(37) As Double              ' (reserved)
End Type

Public Type glp_smcp
  ' simplex method control parameters
  msg_lev As Long                    ' message level:
  meth As Long                       ' simplex method option:
  pricing As Long                    ' pricing technique:
  r_test As Long                     ' ratio test technique:
  tol_bnd As Double                  ' spx.tol_bnd
  tol_dj As Double                   ' spx.tol_dj
  tol_piv As Double                  ' spx.tol_piv
  obj_ll As Double                   ' spx.obj_ll
  obj_ul As Double                   ' spx.obj_ul
  it_lim As Long                     ' spx.it_lim
  tm_lim As Long                     ' spx.tm_lim (milliseconds)
  out_frq As Long                    ' spx.out_frq
  out_dly As Long                    ' spx.out_dly (milliseconds)
  presolve As Long                   ' enable/disable using LP presolver
  excl As Long                       ' exclude fixed non-basic variables
  shift As Long                      ' shift bounds of variables to zero
  aorn As Long                       ' option to use A or N
  foo_bar(32) As Double              ' (reserved)
End Type

Public Type glp_iptcp
  ' interior-point solver control parameters
  msg_lev As Long                    ' message level (see glp_smcp)
  ord_alg As Long                    ' ordering algorithm:
  foo_bar(47) As Double              ' (reserved)
End Type

Public Type glp_iocp
  ' integer optimizer control parameters
  msg_lev As Long                    ' message level
  br_tech As Long                    ' branching technique:
  bt_tech As Long                    ' backtracking technique:
  align_1 As Long                    ' only used for alignment
  tol_int As Double                  ' mip.tol_int
  tol_obj As Double                  ' mip.tol_obj
  tm_lim As Long                     ' mip.tm_lim (milliseconds)
  out_frq As Long                    ' mip.out_frq (milliseconds)
  out_dly As Long                    ' mip.out_dly (milliseconds)
#If Win64 Then
  align_2 As Long                    ' only used for alignment
#End If
  cb_func As LongPtr                 ' mip.cb_func
  cb_info As LongPtr                 ' mip.cb_info
  cb_size As Long                    ' mip.cb_size
  pp_tech As Long                    ' preprocessing technique:
#If Win64 Then
#Else
  align_2 As Long                    ' only used for alignment
#End If
  mip_gap As Double                  ' relative MIP gap tolerance
  mir_cuts As Long                   ' MIR cuts       (GLP_ON/GLP_OFF)
  gmi_cuts As Long                   ' Gomory's cuts  (GLP_ON/GLP_OFF)
  cov_cuts As Long                   ' cover cuts     (GLP_ON/GLP_OFF)
  clq_cuts As Long                   ' clique cuts    (GLP_ON/GLP_OFF)
  presolve As Long                   ' enable/disable using MIP presolver
  binarize As Long                   ' try to binarize long variables
  fp_heur As Long                    ' feasibility pump heuristic
  ps_heur As Long                    ' proximity search heuristic
  ps_tm_lim As Long                  ' proxy time limit, milliseconds
  sr_heur As Long                    ' simple rounding heuristic
  use_sol As Long                    ' use existing solution
#If Win64 Then
  align_3 As Long                    ' only used for alignment
#End If
  save_sol As LongPtr                ' filename to save every new solution
  alien As Long                      ' use alien solver
  flip As Long                       ' use long-step dual simplex
  foo_bar(22) As Double              ' (reserved)
End Type

Public Type glp_attr
  ' additional row attributes
  level As Long                      ' subproblem level at which the row was added
  origin As Long                     ' the row origin flag:
  klass As Long                      ' the row class descriptor:
  align_1 As Long                    ' only used for alignment
  foo_bar(6) As Double               ' (reserved)
End Type

Public Type glp_mpscp
  'MPS format control parameters
  blank As Long                      ' character code to replace blanks in symbolic names
#If Win64 Then
  align_1 As Long                    ' only used for alignment
#End If
  obj_name As LongPtr                ' objective row name
  tol_mps As Double                  ' zero tolerance for MPS data
  foo_bar(16) As Double              ' (reserved for use in the future)
End Type

Public Type glp_cpxcp
  ' CPLEX LP format control parameters
  foo_bar(19) As Double              ' (reserved for use in the future)
End Type

' Problem creating and modifying routines
' create problem object
Declare PtrSafe Function glp_create_prob Lib "glpk.dll" () As LongPtr
' assign (change) problem name
Declare PtrSafe Sub glp_set_prob_name Lib "glpk.dll" (ByVal lp As LongPtr, ByRef name As Byte)
' assign (change) objective function name
Declare PtrSafe Sub glp_set_obj_name Lib "glpk.dll" (ByVal lp As LongPtr, ByRef name As Byte)
' set change) optimization direction flag
Declare PtrSafe Sub glp_set_obj_dir Lib "glpk.dll" (ByVal lp As LongPtr, ByVal dir As Long)
' add new rows to problem object
Declare PtrSafe Function glp_add_rows Lib "glpk.dll" (ByVal lp As LongPtr, ByVal count As Long) As Long
' add new columns to problem object
Declare PtrSafe Function glp_add_cols Lib "glpk.dll" (ByVal lp As LongPtr, ByVal count As Long) As Long
' assign (change) row name
Declare PtrSafe Sub glp_set_row_name Lib "glpk.dll" (ByVal lp As LongPtr, ByVal row As Long, ByRef name As Byte)
' assign (change) column name
Declare PtrSafe Sub glp_set_col_name Lib "glpk.dll" (ByVal lp As LongPtr, ByVal col As Long, ByRef name As Byte)
' set (change) row bounds
Declare PtrSafe Sub glp_set_row_bnds Lib "glpk.dll" (ByVal lp As LongPtr, _
  ByVal row As Long, ByVal typ As Long, ByVal lb As Double, ByVal ub As Double)
' set (change) column bounds
Declare PtrSafe Sub glp_set_col_bnds Lib "glpk.dll" (ByVal lp As LongPtr, _
  ByVal col As Long, ByVal typ As Long, ByVal lb As Double, ByVal ub As Double)
' set (change) obj. coefficient or constant term
Declare PtrSafe Sub glp_set_obj_coef Lib "glpk.dll" (ByVal lp As LongPtr, ByVal col As Long, ByVal val As Double)
' set (replace) row of the constraint matrix
Declare PtrSafe Sub glp_set_mat_row Lib "glpk.dll" ( _
  ByVal lp As LongPtr, ByVal i As Long, ByVal length As Long, ByRef ind As Long, ByRef val As Double)
' set (replace) column of the constraint matrix
Declare PtrSafe Sub glp_set_mat_col Lib "glpk.dll" ( _
  ByVal lp As LongPtr, ByVal j As Long, ByVal length As Long, ByRef ind As Long, ByRef val As Double)
' load (replace) the whole constraint matrix
Declare PtrSafe Sub glp_load_matrix Lib "glpk.dll" ( _
  ByVal lp As LongPtr, ByVal ne As Long, ByRef ia As Long, ByRef ja As Long, ByRef val As Double)
' check for duplicate elements in sparse matrix
Declare PtrSafe Function glp_check_dup Lib "glpk.dll" ( _
  ByVal m As Long, ByVal n As Long, ByVal ne As Long, ByRef ia As Long, ByRef ja As Long) As Long
' sort elements of the constraint matrix
Declare PtrSafe Sub glp_sort_matrix Lib "glpk.dll" (ByVal lp As LongPtr)
' delete specified rows from problem object
Declare PtrSafe Sub glp_del_rows Lib "glpk.dll" (ByVal lp As LongPtr, ByVal nrs As Long, ByRef num As Long)
' delete specified columns from problem object
Declare PtrSafe Sub glp_del_cols Lib "glpk.dll" (ByVal lp As LongPtr, ByVal ncs As Long, ByRef num As Long)
' copy problem object content
Declare PtrSafe Sub glp_copy_prob Lib "glpk.dll" (ByVal dest As LongPtr, ByVal prob As LongPtr, ByVal names As Long)
' erase problem object
Declare PtrSafe Sub glp_erase_prob Lib "glpk.dll" (ByVal lp As LongPtr)
' delete problem object
Declare PtrSafe Sub glp_delete_prob Lib "glpk.dll" (ByVal lp As LongPtr)
' set (change) row status
Declare PtrSafe Sub glp_set_row_stat Lib "glpk.dll" (ByVal lp As LongPtr, ByVal i As Long, ByVal stat As Long)
' set (change) column status
Declare PtrSafe Sub glp_set_col_stat Lib "glpk.dll" (ByVal lp As LongPtr, ByVal j As Long, ByVal stat As Long)

' Problem scaling routines
' set (change) row scale factor
Declare PtrSafe Sub glp_set_rii Lib "glpk.dll" (ByVal lp As LongPtr, ByVal i As Long, ByVal rii As Double)
' set (change) column factor
Declare PtrSafe Sub glp_set_sjj Lib "glpk.dll" (ByVal lp As LongPtr, ByVal j As Long, ByVal sjj As Double)
' retrieve row scale factor
Declare PtrSafe Function glp_get_rii Lib "glpk.dll" (ByVal lp As LongPtr, ByVal i As Long) As Double
' retrieve column factor
Declare PtrSafe Function glp_get_sjj Lib "glpk.dll" (ByVal lp As LongPtr, ByVal j As Long) As Double
' scale problem data
Declare PtrSafe Sub glp_scale_prob Lib "glpk.dll" (ByVal lp As LongPtr, ByVal flags As Long)
' unscale problem data
Declare PtrSafe Sub glp_unscale_prob Lib "glpk.dll" (ByVal lp As LongPtr)

' LP basis construction routines
' construct advanced initial LP basis
Declare PtrSafe Sub glp_adv_basis Lib "glpk.dll" (ByVal lp As LongPtr, ByVal flags As Long)
' construct Bixby's initial LP basis
Declare PtrSafe Sub glp_cpx_basis Lib "glpk.dll" (ByVal lp As LongPtr)
' construct standard initial LP basis
Declare PtrSafe Sub glp_std_basis Lib "glpk.dll" (ByVal lp As LongPtr)

' Simplex method routines
' initialize simplex method control parameters
Declare PtrSafe Function glp_init_smcp Lib "glpk.dll" (ByRef smcp As glp_smcp) As Long
' solve LP problem with the simplex method
Declare PtrSafe Function glp_simplex Lib "glpk.dll" (ByVal lp As LongPtr, ByRef smcp As glp_smcp) As Long
' retrieve generic status of basic solution
Declare PtrSafe Function glp_get_status Lib "glpk.dll" (ByVal lp As LongPtr) As Long
' retrieve status of primal basic solution
Declare PtrSafe Function glp_get_prim_stat Lib "glpk.dll" (ByVal lp As LongPtr) As Long
' retrieve status of dual basic solution
Declare PtrSafe Function glp_get_dual_stat Lib "glpk.dll" (ByVal lp As LongPtr) As Long
' retrieve objective value (basic solution)
Declare PtrSafe Function glp_get_obj_val Lib "glpk.dll" (ByVal lp As LongPtr) As Double
' retrieve row primal value (basic solution)
Declare PtrSafe Function glp_get_row_prim Lib "glpk.dll" (ByVal lp As LongPtr, ByVal i As Long) As Double
' retrieve row dual value (basic solution)
Declare PtrSafe Function glp_get_row_dual Lib "glpk.dll" (ByVal lp As LongPtr, ByVal i As Long) As Double
' retrieve column primal value (basic solution)
Declare PtrSafe Function glp_get_col_prim Lib "glpk.dll" (ByVal lp As LongPtr, ByVal j As Long) As Double
' retrieve column dual value (basic solution)
Declare PtrSafe Function glp_get_col_dual Lib "glpk.dll" (ByVal lp As LongPtr, ByVal j As Long) As Double
' determine variable causing unboundedness
Declare PtrSafe Function glp_get_unbnd_ray Lib "glpk.dll" (ByVal lp As LongPtr) As Long

' Mixed long programming routines
' set (change) column kind
Declare PtrSafe Sub glp_set_col_kind Lib "glpk.dll" (ByVal lp As LongPtr, ByVal j As Long, ByVal kind As Long)
' get column kind
Declare PtrSafe Function glp_col_kind Lib "glpk.dll" (ByVal lp As LongPtr, ByVal j As Long) As Long
' retrieve number of integer columns
Declare PtrSafe Function glp_num_int Lib "glpk.dll" (ByVal lp As LongPtr) As Long
' retrieve number of binary columns
Declare PtrSafe Function glp_num_bin Lib "glpk.dll" (ByVal lp As LongPtr) As Long
' solve MIP problem with the branch-and-bound method
Declare PtrSafe Function glp_intopt Lib "glpk.dll" (ByVal lp As LongPtr, ByRef iocp As glp_iocp) As Long
' initialize integer optimizer control parameters
Declare PtrSafe Sub glp_init_iocp Lib "glpk.dll" (ByRef smcp As glp_iocp)
' retrieve status of MIP solution
Declare PtrSafe Function glp_mip_status Lib "glpk.dll" (ByVal lp As LongPtr) As Long
' retrieve objective value (MIP solution)
Declare PtrSafe Function glp_mip_obj_val Lib "glpk.dll" (ByVal lp As LongPtr) As Double
' retrieve row value (MIP solution)
Declare PtrSafe Function glp_mip_row_val Lib "glpk.dll" (ByVal lp As LongPtr, ByVal i As Long) As Double
' retrieve column value (MIP solution)
Declare PtrSafe Function glp_mip_col_val Lib "glpk.dll" (ByVal lp As LongPtr, ByVal j As Long) As Double

' Problem retrieving functions
' retrieve problem name
Declare PtrSafe Function glp_get_prob_name Lib "glpk.dll" (ByVal lp As LongPtr) As LongPtr
' retrieve objective function name
Declare PtrSafe Function glp_get_obj_name Lib "glpk.dll" (ByVal lp As LongPtr) As LongPtr
' retrieve optimization direction flag
Declare PtrSafe Function glp_get_obj_dir Lib "glpk.dll" (ByVal lp As LongPtr) As Long
' retrieve number of rows
Declare PtrSafe Function glp_get_num_rows Lib "glpk.dll" (ByVal lp As LongPtr) As Long
' retrieve number of columns
Declare PtrSafe Function glp_get_num_cols Lib "glpk.dll" (ByVal lp As LongPtr) As Long
' retrieve row name
Declare PtrSafe Function glp_get_row_name Lib "glpk.dll" (ByVal lp As LongPtr, ByVal i As Long) As LongPtr
' retrieve column name
Declare PtrSafe Function glp_get_col_name Lib "glpk.dll" (ByVal lp As LongPtr, ByVal j As Long) As LongPtr
' retrieve row type
Declare PtrSafe Function glp_get_row_type Lib "glpk.dll" (ByVal lp As LongPtr, ByVal i As Long) As Long
' retrieve column type
Declare PtrSafe Function glp_get_col_type Lib "glpk.dll" (ByVal lp As LongPtr, ByVal j As Long) As Long
' get row lower bound
Declare PtrSafe Function glp_get_row_lb Lib "glpk.dll" (ByVal lp As LongPtr, ByVal i As Long) As Double
' get column lower bound
Declare PtrSafe Function glp_get_col_lb Lib "glpk.dll" (ByVal lp As LongPtr, ByVal j As Long) As Double
' get row upper bound
Declare PtrSafe Function glp_get_row_ub Lib "glpk.dll" (ByVal lp As LongPtr, ByVal i As Long) As Double
' get column upper bound
Declare PtrSafe Function glp_get_col_ub Lib "glpk.dll" (ByVal lp As LongPtr, ByVal j As Long) As Double
' retrieve obj. coefficient or constant term
Declare PtrSafe Function glp_get_obj_coef Lib "glpk.dll" (ByVal lp As LongPtr, ByVal j As Long) As Double
' retrieve number of constraint coefficients
Declare PtrSafe Function glp_get_numz Lib "glpk.dll" (ByVal lp As LongPtr) As Long
' retrieve row of the constraint matrix
Declare PtrSafe Sub glp_get_mat_row Lib "glpk.dll" ( _
  ByVal lp As LongPtr, ByVal i As Long, ByVal length As Long, ByRef ind As Long, ByRef val As Double)
' retrieve column of the constraint matrix
Declare PtrSafe Sub glp_get_mat_col Lib "glpk.dll" ( _
  ByVal lp As LongPtr, ByVal j As Long, ByVal length As Long, ByRef ind As Long, ByRef val As Double)
' create the name index
Declare PtrSafe Sub glp_create_index Lib "glpk.dll" (ByVal lp As LongPtr)
' find row by its name
Declare PtrSafe Function glp_find_row Lib "glpk.dll" (ByVal lp As LongPtr, ByVal row As Long, ByRef name As Byte) As Long
' find column by its name
Declare PtrSafe Function glp_find_col Lib "glpk.dll" (ByVal lp As LongPtr, ByVal row As Long, ByRef name As Byte) As Long
' delete the name index
Declare PtrSafe Sub glp_delete_index Lib "glpk.dll" (ByVal lp As LongPtr)

' Problem reading/writing routines
' read problem data in CPLEX LP format
Declare PtrSafe Function glp_read_lp Lib "glpk.dll" (ByVal lp As LongPtr, ByVal parm As Long, ByRef name As Byte) As Long
' write problem data in CPLEX LP format
Declare PtrSafe Function glp_write_lp Lib "glpk.dll" (ByVal lp As LongPtr, ByVal parm As Long, ByRef name As Byte) As Long
' read problem data in MPS format
Declare PtrSafe Function glp_read_mps Lib "glpk.dll" (ByVal lp As LongPtr, ByVal parm As Long, ByRef name As Byte) As Long
' write problem data in MPS format
Declare PtrSafe Function glp_write_mps Lib "glpk.dll" (ByVal lp As LongPtr, ByVal parm As Long, ByRef name As Byte) As Long
' read problem data in GLPK format
Declare PtrSafe Function glp_read_prob Lib "glpk.dll" (ByVal lp As LongPtr, ByVal parm As Long, ByRef name As Byte) As Long
' write problem data in GLPK format
Declare PtrSafe Function glp_write_prob Lib "glpk.dll" (ByVal lp As LongPtr, ByVal parm As Long, ByRef name As Byte) As Long

' Routines for processing MathProg models
' allocate the MathProg translator workspace
Declare PtrSafe Function glp_mpl_alloc_wksp Lib "glpk.dll" () As LongPtr
' read and translate model section
Declare PtrSafe Function glp_mpl_read_model Lib "glpk.dll" (ByVal tran As LongPtr, ByRef fname As Byte, skip As Long) As Long
' read and translate data section
Declare PtrSafe Function glp_mpl_read_data Lib "glpk.dll" (ByVal tran As LongPtr, ByRef fname As Byte) As Long
' generate the model
Declare PtrSafe Function glp_mpl_generate Lib "glpk.dll" (ByVal tran As LongPtr, ByVal fname As LongPtr) As Long
' build LP/MIP problem instance from the model
Declare PtrSafe Function glp_mpl_build_prob Lib "glpk.dll" (ByVal tran As LongPtr, ByVal lp As LongPtr) As Long
' postsolve the model
Declare PtrSafe Function glp_mpl_postsolve Lib "glpk.dll" (ByVal tran As LongPtr, ByVal lp As LongPtr, ByVal sol As Long) As Long
' free the MathProg translator workspace
Declare PtrSafe Sub glp_mpl_free_wksp Lib "glpk.dll" (ByVal tran As LongPtr)

' Branch-and-cut API routines
' determine reason for calling the callback routine
Declare PtrSafe Function glp_ios_reason Lib "glpk.dll" (ByVal tree As LongPtr) As Long
' access the problem object
Declare PtrSafe Function glp_ios_get_problem Lib "glpk.dll" (ByVal tree As LongPtr) As LongPtr
' determine additional row attributes
Declare PtrSafe Sub glp_ios_row_attr Lib "glpk.dll" (ByVal tree As LongPtr, ByVal i As Long, ByRef attr As glp_attr)
' compute relative MIP gap
Declare PtrSafe Function glp_ios_mip_gap Lib "glpk.dll" (ByVal tree As LongPtr) As Double
' select subproblem to continue the search
Declare PtrSafe Sub glp_ios_select_node Lib "glpk.dll" (ByVal tree As LongPtr, ByVal p As Long)
' provide solution found by heuristic
Declare PtrSafe Function glp_ios_heur_sol Lib "glpk.dll" (ByVal tree As LongPtr, ByRef x As Double) As Long
' check if can branch upon specied variable
Declare PtrSafe Function glp_ios_can_branch Lib "glpk.dll" (ByVal tree As LongPtr, ByVal j As Long) As Long
' choose variable to branch upon
Declare PtrSafe Sub glp_ios_branch_upon Lib "glpk.dll" (ByVal tree As LongPtr, ByVal j As Long, ByVal sel As Long)
' terminate the solution process
Declare PtrSafe Sub glp_ios_terminate Lib "glpk.dll" (ByVal tree As LongPtr)

' Search tree exploring routines
' determine size of search tree
Declare PtrSafe Sub glp_ios_tree_size Lib "glpk.dll" (ByVal tree As LongPtr, ByRef a_cnt As Long, ByRef n_cnt As Long, ByRef t_cnt As Long)
' determine current active subproblem
Declare PtrSafe Function glp_ios_curr_node Lib "glpk.dll" (ByVal tree As LongPtr) As Long
' determine next active subproblem
Declare PtrSafe Function glp_ios_next_node Lib "glpk.dll" (ByVal tree As LongPtr, ByVal p As Long) As Long
' determine previous active subproblem
Declare PtrSafe Function glp_ios_prev_node Lib "glpk.dll" (ByVal tree As LongPtr, ByVal p As Long) As Long
' determine parent subproblem
Declare PtrSafe Function glp_ios_up_node Lib "glpk.dll" (ByVal tree As LongPtr, ByVal p As Long) As Long
' determine subproblem level
Declare PtrSafe Function glp_ios_node_level Lib "glpk.dll" (ByVal tree As LongPtr, ByVal p As Long) As Long
' determine subproblem local bound
Declare PtrSafe Function glp_ios_node_bound Lib "glpk.dll" (ByVal tree As LongPtr, ByVal p As Long) As Double
' determine active subproblem with best local bound
Declare PtrSafe Function glp_ios_best_node Lib "glpk.dll" (ByVal tree As LongPtr) As Long

' GLPK environment routines
' initialize GLPK environment
Declare PtrSafe Function glp_init_env Lib "glpk.dll" () As Long
' determine library version
Declare PtrSafe Function glp_version Lib "glpk.dll" () As LongPtr
' free GLPK environment
Declare PtrSafe Function glp_free_env Lib "glpk.dll" () As Long
' enable/disable terminal output
Declare PtrSafe Function glp_term_out Lib "glpk.dll" (ByVal flag As Long) As Long
' intercept terminal output
' BEWARE: info has to be a variant variable that is valid until the terminal hook function is set to 0.!
Declare PtrSafe Sub glp_term_hook Lib "glpk.dll" (ByVal func As LongPtr, Optional ByRef info As Variant)
' start copying terminal output
Declare PtrSafe Function glp_open_tee Lib "glpk.dll" (ByRef fname As Byte) As Long
' start copying terminal output
Declare PtrSafe Function glp_close_tee Lib "glpk.dll" () As Long
' display fatal error message and terminate execution
Declare PtrSafe Sub glp_error_ Lib "glpk.dll" (ByRef file As Byte, line As Long)
' check for error state
Declare PtrSafe Function glp_at_error Lib "glpk.dll" () As Long
' install hook to intercept abnormal termination
' BEWARE: info has to be a variant variable that is valid until the error hook function is set to 0.!
Declare PtrSafe Sub glp_error_hook Lib "glpk.dll" (ByVal func As LongPtr, Optional ByRef info As Variant)
' get memory usage information
Declare PtrSafe Sub glp_mem_usage Lib "glpk.dll" (ByRef count As Long, ByRef cpeak As Long, ByRef total As LongPtr, ByRef tpeak As LongPtr)
' set memory usage limit
Declare PtrSafe Sub glp_mem_limit Lib "glpk.dll" (ByVal limit As Long)

' Converts a C string to a byte array.
Declare PtrSafe Function SysAllocStringByteLen Lib "oleaut32" (ByVal pwsz As LongPtr, ByVal length As Long) As String

' Catches GLPK library errors and raises VBA error.
' You can pass this function to glp_error_hook.
Function error_hook(ByRef info As Variant)
  glp_free_env
  Err.Raise GLPK_LIB_ERROR, "error_hook", "Error when calling GLPK library"
End Function

' Echos terminal output to debug console.
' This function can be passed to glp_term_hook.
'
' @param info info variable passed to glp_term_hook
' @param textptr pointer to C string with the text to output
' @return 1 for no output
Function term_hook(ByRef info As Variant, ByVal textptr As LongPtr) As Long
  Dim text As String
  If glp_at_error() Then
    Debug.Print ">>> ";
  End If
  text = SysAllocStringByteLen(textptr, 512)
  text = Left$(text, InStr(text, Chr$(0)) - 1)
  Debug.Print text;
  term_hook = 1
End Function

Function str2bytes(name As String) As Byte()
    str2bytes = StrConv(name & Chr(0), vbFromUnicode)
End Function

' Writes simplex solution to debug console
' @param lp problem
Sub write_lp_solution(lp As LongPtr)
  Dim i, n As Long
  Dim textptr As LongPtr
  Dim name As String
  Dim val As Double
        
  textptr = glp_version()
  name = SysAllocStringByteLen(textptr, 512)
  name = Left$(name, InStr(name, Chr$(0)) - 1)
  Debug.Print "GLPK " & name
  
  textptr = glp_get_prob_name(lp)
  name = SysAllocStringByteLen(textptr, 512)
  name = Left$(name, InStr(name, Chr$(0)) - 1)
  Debug.Print "Solution of " & name
          
  textptr = glp_get_obj_name(lp)
  name = SysAllocStringByteLen(textptr, 512)
  name = Left$(name, InStr(name, Chr$(0)) - 1)
  val = glp_get_obj_val(lp)
  Debug.Print name & " = " & val
          
  n = glp_get_num_cols(lp)
  For i = 1 To n
     textptr = glp_get_col_name(lp, i)
     name = SysAllocStringByteLen(textptr, 512)
     name = Left$(name, InStr(name, Chr$(0)) - 1)
     val = glp_get_col_prim(lp, i)
     Debug.Print name & " = " & val
   Next i
End Sub

' Writes mixed integer solution to debug console
' @param lp problem
Sub write_mip_solution(lp As LongPtr)
  Dim i, n As Long
  Dim textptr As LongPtr
  Dim name As String
  Dim val As Double
        
  textptr = glp_version()
  name = SysAllocStringByteLen(textptr, 512)
  name = Left$(name, InStr(name, Chr$(0)) - 1)
  Debug.Print "GLPK " & name
  
  textptr = glp_get_prob_name(lp)
  name = SysAllocStringByteLen(textptr, 512)
  name = Left$(name, InStr(name, Chr$(0)) - 1)
  Debug.Print "Solution of " & name
          
  textptr = glp_get_obj_name(lp)
  name = SysAllocStringByteLen(textptr, 512)
  name = Left$(name, InStr(name, Chr$(0)) - 1)
  val = glp_mip_obj_val(lp)
  Debug.Print name & " = " & val
          
  n = glp_get_num_cols(lp)
  For i = 1 To n
     textptr = glp_get_col_name(lp, i)
     name = SysAllocStringByteLen(textptr, 512)
     name = Left$(name, InStr(name, Chr$(0)) - 1)
     val = glp_mip_col_val(lp, i)
     Debug.Print name & " = " & val
   Next i
End Sub

' Returns function address.
' This conversion routine is needed because AddressOf
' cannot be used in assignments.
'
' @param func function passed with AddressOf operator
' @returns address of function   func
Public Function glpk_addressof(func As LongPtr) As LongPtr
  glpk_addressof = func
End Function

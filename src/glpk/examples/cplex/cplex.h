/* cplex.h (CPLEX-like interface to GLPK API) */

/***********************************************************************
*  This code is part of GLPK (GNU Linear Programming Kit).
*
*  Copyright (C) 2000, 2001, 2002, 2003, 2004, 2005, 2006, 2007, 2008,
*  2009, 2010, 2011, 2013 Andrew Makhorin, Department for Applied
*  Informatics, Moscow Aviation Institute, Moscow, Russia. All rights
*  reserved. E-mail: <mao@gnu.org>.
*
*  GLPK is free software: you can redistribute it and/or modify it
*  under the terms of the GNU General Public License as published by
*  the Free Software Foundation, either version 3 of the License, or
*  (at your option) any later version.
*
*  GLPK is distributed in the hope that it will be useful, but WITHOUT
*  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
*  or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public
*  License for more details.
*
*  You should have received a copy of the GNU General Public License
*  along with GLPK. If not, see <http://www.gnu.org/licenses/>.
***********************************************************************/

#ifndef _CPLEX_H
#define _CPLEX_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct CPXENV CPXENV, *CPXENVptr;
typedef struct CPXLP CPXLP, *CPXLPptr;

#define CPX_VERSION                 900

#define CPX_OFF                     0
#define CPX_ON                      1

#define CPX_INFBOUND                1e20

/* error codes: */
#define CPXERR_NO_MEMORY            1001
#define CPXERR_NO_ENVIRONMENT       1002
#define CPXERR_BAD_ARGUMENT         1003
#define CPXERR_NULL_POINTER         1004
#define CPXERR_NO_PROBLEM           1009
#define CPXERR_BAD_PARAM_NUM        1013
#define CPXERR_PARAM_TOO_SMALL      1014
#define CPXERR_PARAM_TOO_BIG        1015
#define CPXERR_INDEX_RANGE          1200
#define CPXERR_COL_INDEX_RANGE      1201
#define CPXERR_ROW_INDEX_RANGE      1203
#define CPXERR_NEGATIVE_SURPLUS     1207
#define CPXERR_BAD_SENSE            1215
#define CPXERR_NO_SOLN              1217
#define CPXERR_NOT_FIXED            1221
#define CPXERR_DUP_ENTRY            1222
#define CPXERR_NULL_NAME            1224
#define CPXERR_ARRAY_NOT_ASCENDING  1226
#define CPXERR_COUNT_RANGE          1227
#define CPXERR_BAD_LUB              1229
#define CPXERR_BAD_STATUS           1253
#define CPXERR_NO_BASIC_SOLN        1261
#define CPXERR_NO_FILENAME          1421
#define CPXERR_FAIL_OPEN_WRITE      1422
#define CPXERR_BAD_FILETYPE         1424
#define CPXERR_BAD_CTYPE            3021

/* control parameters: */
#define CPX_PARAM_ADVIND            1001
#define CPX_PARAM_AGGIND            1003
#define CPX_PARAM_DPRIIND           1009
#define CPX_PARAM_EPOPT             1014
#define CPX_PARAM_EPPER             1015
#define CPX_PARAM_EPRHS             1016
#define CPX_PARAM_FASTMIP           1017 /* ??? */
#define CPX_PARAM_SIMDISPLAY        1019
#define CPX_PARAM_ITLIM             1020
#define CPX_PARAM_OBJLLIM           1025
#define CPX_PARAM_OBJULIM           1026
#define CPX_PARAM_PERIND            1027
#define CPX_PARAM_PPRIIND           1029
#define CPX_PARAM_PREIND            1030
#define CPX_PARAM_REINV             1031
#define CPX_PARAM_SCRIND            1035
#define CPX_PARAM_DATACHECK         1056

/* CPX_PARAM_DPRIIND: */
#define CPX_DPRIIND_AUTO            0
#define CPX_DPRIIND_FULL            1
#define CPX_DPRIIND_STEEP           2
#define CPX_DPRIIND_FULL_STEEP      3
#define CPX_DPRIIND_STEEPQSTART     4
#define CPX_DPRIIND_DEVEX           5

/* CPX_PARAM_PPRIIND: */
#define CPX_PPRIIND_PARTIAL         (-1)
#define CPX_PPRIIND_AUTO            0
#define CPX_PPRIIND_DEVEX           1
#define CPX_PPRIIND_STEEP           2
#define CPX_PPRIIND_STEEPQSTART     3
#define CPX_PPRIIND_FULL            4

/* CPXgetprobtype: */
#define CPXPROB_LP                  0
#define CPXPROB_MIP                 1
#define CPXPROB_RELAXED             2
#define CPXPROB_FIXED               3
#define CPXPROB_QP                  5
#define CPXPROB_ZEROEDQP            6

/* CPXgetobjsen: */
#define CPX_MIN                     1
#define CPX_MAX                     (-1)

/* CPXgetbase: */
#define CPX_AT_LOWER                0
#define CPX_BASIC                   1
#define CPX_AT_UPPER                2
#define CPX_FREE_SUPER              3

/* CPXgetstat: */
#define CPX_STAT_OPTIMAL            1
#define CPX_STAT_UNBOUNDED          2
#define CPX_STAT_INFEASIBLE         3
#define CPX_STAT_INForUNBD          4
#define CPX_STAT_OPTIMAL_INFEAS     5
#define CPX_STAT_ABORT_IT_LIM       10
#define CPX_STAT_ABORT_OBJ_LIM      12

/* CPXgetmethod: */
#define CPX_ALG_NONE                0
#define CPX_ALG_PRIMAL              1
#define CPX_ALG_DUAL                2
#define CPX_ALG_BARRIER             4

/* CPXsolninfo: */
#define CPX_NO_SOLN                 0
#define CPX_BASIC_SOLN              1
#define CPX_NONBASIC_SOLN           2
#define CPX_PRIMAL_SOLN             3

int CPXaddcols(CPXENV *env, CPXLP *lp, int ccnt, int nzcnt,
      const double obj[], const int cmatbeg[], const int cmatind[],
      const double cmatval[], const double lb[], const double ub[],
      char *colname[]);

int CPXaddrows(CPXENV *env, CPXLP *lp, int ccnt, int rcnt, int nzcnt,
      const double rhs[], const char sense[], const int rmatbeg[],
      const int rmatind[], const double rmatval[], char *colname[],
      char *rowname[]);

int CPXbaropt(CPXENV *env, CPXLP *lp);

int CPXbinvrow(CPXENV *env, CPXLP *lp, int i, double y[]);

int CPXchgbds(CPXENV *env, CPXLP *lp, int cnt, const int indices[],
      const char lu[], const double bd[]);

int CPXchgcoeflist(CPXENV *env, CPXLP *lp, int numcoefs,
      const int rowlist[], const int collist[], const double vallist[]);

void CPXchgobjsen(CPXENV *env, CPXLP *lp, int maxormin);

int CPXchgsense(CPXENV *env, CPXLP *lp, int cnt, const int indices[],
      const char sense[]);

int CPXcloseCPLEX(CPXENV **env);

int CPXcopybase(CPXENV *env, CPXLP *lp, const int cstat[],
      const int rstat[]);

int CPXcopybasednorms(CPXENV *env, CPXLP *lp, const int cstat[],
      const int rstat[], const double dnorm[]);

int CPXcopylp(CPXENV *env, CPXLP *lp, int numcols, int numrows,
      int objsen, const double obj[], const double rhs[],
      const char sense[], const int matbeg[], const int matcnt[],
      const int matind[], const double matval[], const double lb[],
      const double ub[], const double rngval[]);

int CPXcopylpwnames(CPXENV *env, CPXLP *lp, int numcols, int numrows,
      int objsen, const double obj[], const double rhs[],
      const char sense[], const int matbeg[], const int matcnt[],
      const int matind[], const double matval[], const double lb[],
      const double ub[], const double rngval[], char *colname[],
      char *rowname[]);

CPXLP *CPXcreateprob(CPXENV *env, int *status, const char *probname);

int CPXdelcols(CPXENV *env, CPXLP *lp, int begin, int end);

int CPXdelrows(CPXENV *env, CPXLP *lp, int begin, int end);

int CPXdelsetcols(CPXENV *env, CPXLP *lp, int delstat[]);

int CPXdelsetrows(CPXENV *env, CPXLP *lp, int delstat[]);

int CPXdualopt(CPXENV *env, CPXLP *lp);

int CPXfreeprob(CPXENV *env, CPXLP **lp);

int CPXgetbase(CPXENV *env, CPXLP *lp, int cstat[], int rstat[]);

int CPXgetbasednorms(CPXENV *env, CPXLP *lp, int cstat[], int rstat[],
      double dnorm[]);

int CPXgetbhead(CPXENV *env, CPXLP *lp, int head[], double x[]);

int CPXgetdblparam(CPXENV *env, int whichparam, double *value);

int CPXgetdj(CPXENV *env, CPXLP *lp, double dj[], int begin, int end);

char *CPXgeterrorstring(CPXENV *env, int errcode, char *buffer);

int CPXgetijdiv(CPXENV *env, CPXLP *lp, int *idiv, int *jdiv);

int CPXgetintparam(CPXENV *env, int whichparam, int *value);

int CPXgetlb(CPXENV *env, CPXLP *lp, double lb[], int begin, int end);

int CPXgetmethod(CPXENV *env, CPXLP *lp);

int CPXgetnumcols(CPXENV *env, CPXLP *lp);

int CPXgetnumnz(CPXENV *env, CPXLP *lp);

int CPXgetnumrows(CPXENV *env, CPXLP *lp);

int CPXgetobjval(CPXENV *env, CPXLP *lp, double *objval);

int CPXgetpi(CPXENV *env, CPXLP *lp, double pi[], int begin, int end);

int CPXgetsense(CPXENV *env, CPXLP *lp, char sense[], int begin,
      int end);

int CPXgetslack(CPXENV *env, CPXLP *lp, double slack[], int begin,
      int end);

int CPXgetstat(CPXENV *env, CPXLP *lp);

int CPXgetub(CPXENV *env, CPXLP *lp, double ub[], int begin, int end);

int CPXgetweight(CPXENV *env, CPXLP *lp, int rcnt, const int rmatbeg[],
      const int rmatind[], const double rmatval[], double weight[],
      int dpriind);

int CPXgetx(CPXENV *env, CPXLP *lp, double x[], int begin, int end);

int CPXinfodblparam(CPXENV *env, int whichparam, double *defvalue,
      double *minvalue, double *maxvalue);

int CPXinfointparam(CPXENV *env, int whichparam, int *defvalue,
      int *minvalue, int *maxvalue);

int CPXlpopt(CPXENV *env, CPXLP *lp);

int CPXmdleave(const CPXENV *env, CPXLP *lp, const int goodlist[],
      int goodlen, double downratio[], double upratio[]);

int CPXnewcols(CPXENV *env, CPXLP *lp, int ccnt, const double obj[],
      const double lb[], const double ub[], const char ctype[],
      char *colname[]);

int CPXnewrows(CPXENV *env, CPXLP *lp, int rcnt, const double rhs[],
      const char sense[], const double rngval[], char *rowname[]);

CPXENV *CPXopenCPLEX(int *status);

int CPXpivotin(CPXENV *env, CPXLP *lp, const int rlist[], int rlen);

int CPXpivotout(CPXENV *env, CPXLP *lp, const int clist[], int clen);

int CPXprimopt(CPXENV *env, CPXLP *lp);

int CPXsavwrite(CPXENV *env, CPXLP *lp, const char *filename);

int CPXsetdblparam(CPXENV *env, int whichparam, double newvalue);

int CPXsetintparam(CPXENV *env, int whichparam, int newvalue);

int CPXsolninfo(CPXENV *env, CPXLP *lp, int *solnmethod, int *solntype,
      int *pfeasind, int *dfeasind);

int CPXsolution(CPXENV *env, CPXLP *lp, int *lpstat, double *objval,
      double x[], double pi[], double slack[], double dj[]);

int CPXstrongbranch(CPXENV *env, CPXLP *lp, const int goodlist[],
      int goodlen, double downpen[], double uppen[], int itlim);

int CPXwriteprob(CPXENV *env, CPXLP *lp, const char *filename,
      const char *filetype);

#ifdef __cplusplus
}
#endif

#endif

/* eof */

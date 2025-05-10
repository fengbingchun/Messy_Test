/* cplex.c (CPLEX-like interface to GLPK API) */

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

#include <ctype.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glpk.h>
#include "cplex.h"

struct CPXENV
{     /* environment block */
      CPXLP *list;
      /* linked list of problem objects */
      int *intparam; /* int intparam[]; */
      /* integer control parameters */
      double *dblparam; /* double dblparam[]; */
      /* floating-point control parameters */
};

struct CPXLP
{     /* problem object */
      CPXENV *env;
      /* pointer to environment block */
      glp_prob *prob;
      /* pointer to underlying GLPK problem object */
      int rflen;
      /* length of the array rflag */
      char *rflag; /* char rflag[rflen]; */
      /* rflag[i], i = 0,...,nrows-1, is a flag of i-th row: */
#define RF_NOT_RANGED   0  /* not ranged */
#define RF_RANGED_POS   1  /* ranged, RHS = lower bound */
#define RF_RANGED_NEG   2  /* ranged, RHS = upper bound */
      int stat;
      /* solution status reported by CPXgetstat; zero means no solution
         exists */
      int meth;
      /* method indicator reported by CPXgetmethod */
      int iwlen;
      /* length of the working array */
      int *iwork; /* int iwork[iwlen] */
      /* working array initialized by binary zeros */
      CPXLP *link;
      /* pointer to another problem object */
};

struct intparam
{     int which;
      int defv;
      int minv;
      int maxv;
};

struct dblparam
{     int which;
      double defv;
      double minv;
      double maxv;
};

struct errstring
{     int code;
      const char *string;
};

#define BIGINT 2100000000
#define BIGDBL 1e75

static const struct intparam intparam[] =
{     {CPX_PARAM_ADVIND, 0, 0, 2},
      {CPX_PARAM_AGGIND, -1, -1, BIGINT},
      {CPX_PARAM_DATACHECK, CPX_OFF, CPX_OFF, CPX_ON},
      {CPX_PARAM_DPRIIND, CPX_DPRIIND_AUTO, CPX_DPRIIND_AUTO,
         CPX_DPRIIND_DEVEX},
      {CPX_PARAM_FASTMIP, CPX_OFF, CPX_OFF, CPX_ON}, /* ??? */
      {CPX_PARAM_ITLIM, BIGINT, 0, BIGINT},
      {CPX_PARAM_PERIND, CPX_OFF, CPX_OFF, CPX_ON},
      {CPX_PARAM_PPRIIND, CPX_PPRIIND_AUTO, CPX_PPRIIND_PARTIAL,
         CPX_PPRIIND_FULL},
      {CPX_PARAM_PREIND, CPX_ON, CPX_OFF, CPX_ON},
      {CPX_PARAM_REINV, 0, 0, 10000},
      {CPX_PARAM_SCRIND, CPX_OFF, CPX_OFF, CPX_ON},
      {CPX_PARAM_SIMDISPLAY, 1, 0, 2},
};

static const struct dblparam dblparam[] =
{     {CPX_PARAM_EPOPT, 1e-6, 1e-9, 1e-1},
      {CPX_PARAM_EPPER, 1e-6, 1e-8, BIGDBL},
      {CPX_PARAM_EPRHS, 1e-6, 1e-9, 1e-1},
      {CPX_PARAM_OBJLLIM, -BIGDBL, -BIGDBL, +BIGDBL},
      {CPX_PARAM_OBJULIM, +BIGDBL, -BIGDBL, +BIGDBL},
};

static const struct errstring errstring[] =
{     {CPXERR_ARRAY_NOT_ASCENDING, "Array entry %d not ascending"},
      {CPXERR_BAD_ARGUMENT, "Invalid argument"},
      {CPXERR_BAD_CTYPE, "Invalid ctype entry %d"},
      {CPXERR_BAD_FILETYPE, "Invalid filetype"},
      {CPXERR_BAD_LUB, "Invalid bound change indicator entry %d"},
      {CPXERR_BAD_PARAM_NUM, "Invalid parameter number"},
      {CPXERR_BAD_SENSE, "Invalid sense entry %d"},
      {CPXERR_BAD_STATUS, "Invalid status entry %d for basis specificat"
         "ion"},
      {CPXERR_COL_INDEX_RANGE, "Column index %d out of range"},
      {CPXERR_COUNT_RANGE, "Count entry %d negative or larger than allo"
         "wed"},
      {CPXERR_DUP_ENTRY, "Duplicate entry"},
      {CPXERR_FAIL_OPEN_WRITE, "Could not open file '%s' for writing"},
      {CPXERR_INDEX_RANGE, "Index is outside range of valid values"},
      {CPXERR_NEGATIVE_SURPLUS, "Insufficient array length"},
      {CPXERR_NO_BASIC_SOLN, "No basic solution exists"},
      {CPXERR_NO_ENVIRONMENT, "No environment exists"},
      {CPXERR_NO_FILENAME, "File name not specified"},
      {CPXERR_NO_MEMORY, "Out of memory"},
      {CPXERR_NO_PROBLEM, "No problem exists"},
      {CPXERR_NO_SOLN, "No solution exists"},
      {CPXERR_NOT_FIXED, "Only fixed variables are pivoted out"},
      {CPXERR_NULL_NAME, "Null pointer %d in name array"},
      {CPXERR_NULL_POINTER, "Null pointer for required data"},
      {CPXERR_PARAM_TOO_BIG, "Parameter value too big"},
      {CPXERR_PARAM_TOO_SMALL, "Parameter value too small"},
      {CPXERR_ROW_INDEX_RANGE, "Row index %d out of range"},
};

/**********************************************************************/

#define xassert glp_assert
#define xprintf glp_printf
#define xmalloc glp_malloc
#define xcalloc glp_calloc
#define xfree   glp_free

/**********************************************************************/

static int findintparam(int whichparam)
{     int k, card;
      card = sizeof(intparam) / sizeof(struct intparam);
      for (k = 0; k < card; k++)
         if (intparam[k].which == whichparam) return k;
      return -1;
}

static int getintparam(CPXENV *env, int whichparam)
{     int k;
      xassert(env != NULL);
      k = findintparam(whichparam);
      xassert(k >= 0);
      return env->intparam[k];
}

static int finddblparam(int whichparam)
{     int k, card;
      card = sizeof(dblparam) / sizeof(struct dblparam);
      for (k = 0; k < card; k++)
         if (dblparam[k].which == whichparam) return k;
      return -1;
}

static double getdblparam(CPXENV *env, int whichparam)
{     int k;
      xassert(env != NULL);
      k = finddblparam(whichparam);
      xassert(k >= 0);
      return env->dblparam[k];
}

static const char *finderrstring(int errcode)
{     int k, card;
      card = sizeof(errstring) / sizeof(struct errstring);
      for (k = 0; k < card; k++)
      {  if (errstring[k].code == errcode)
            return errstring[k].string;
      }
      return NULL;
}

static int error(CPXENV *env, int errcode, ...)
{     va_list arg;
      char buffer[510];
      xassert(env != NULL);
      if (getintparam(env, CPX_PARAM_SCRIND) == CPX_ON)
      {  xassert(CPXgeterrorstring(env, errcode, buffer) == buffer);
         va_start(arg, errcode);
         vprintf(buffer, arg);
         va_end(arg);
      }
      return errcode;
}

static int checkenv(CPXENV *env)
{     int errcode;
      if (env == NULL)
         errcode = CPXERR_NO_ENVIRONMENT;
      else
         errcode = 0;
      return errcode;
}

static checklp(CPXENV *env, CPXLP *lp)
{     int errcode;
      errcode = checkenv(env);
      if (errcode) goto done;
      if (lp == NULL)
         errcode = error(env, CPXERR_NO_PROBLEM);
done: return errcode;
}

static void invalidate(CPXLP *lp)
{     lp->stat = 0;
      lp->meth = CPX_ALG_NONE;
      return;
}

static void enlargerflag(CPXLP *lp)
{     int m;
      xassert(lp != NULL);
      m = glp_get_num_rows(lp->prob);
      if (lp->rflen < m)
      {  int rflen = lp->rflen;
         char *rflag = lp->rflag;
         while (lp->rflen < m)
         {  lp->rflen += lp->rflen;
            xassert(lp->rflen > 0);
         }
         lp->rflag = xcalloc(lp->rflen, sizeof(char));
         memcpy(lp->rflag, rflag, rflen);
         xfree(rflag);
      }
      return;
}

static void enlargeiwork(CPXLP *lp, int len)
{     xassert(len >= 0);
      if (lp->iwlen < len)
      {  xfree(lp->iwork);
         while (lp->iwlen < len)
         {  lp->iwlen += lp->iwlen;
            xassert(lp->iwlen > 0);
         }
         lp->iwork = xcalloc(lp->iwlen, sizeof(int));
         memset(lp->iwork, 0, lp->iwlen * sizeof(int));
      }
      return;
}

/**********************************************************************/

int CPXaddcols(CPXENV *env, CPXLP *lp, int ccnt, int nzcnt,
      const double obj[], const int cmatbeg[], const int cmatind[],
      const double cmatval[], const double lb[], const double ub[],
      char *colname[])
{     int j, k, m, n, beg, end, type, errcode;
      double lbnd, ubnd;
      errcode = checklp(env, lp);
      if (errcode) goto done;
      if (ccnt < 0 || nzcnt < 0)
      {  errcode = error(env, CPXERR_BAD_ARGUMENT);
         goto done;
      }
      if (ccnt > 0)
      {  if (cmatbeg == NULL || cmatind == NULL || cmatval == NULL)
         {  errcode = error(env, CPXERR_NULL_POINTER);
            goto done;
         }
      }
      m = glp_get_num_rows(lp->prob);
      n = glp_get_num_cols(lp->prob);
      enlargeiwork(lp, m);
      for (j = 0; j < ccnt; j++)
      {  beg = cmatbeg[j];
         if (j > 0 && !(cmatbeg[j-1] <= beg))
         {  errcode = error(env, CPXERR_ARRAY_NOT_ASCENDING, j);
            goto done;
         }
         if (!(0 <= beg && beg <= nzcnt))
         {  errcode = error(env, CPXERR_INDEX_RANGE);
            goto done;
         }
         end = (j < ccnt-1 ? cmatbeg[j+1] : nzcnt);
         for (k = beg; k < end; k++)
         {  if (!(0 <= cmatind[k] && cmatind[k] < m))
            {  errcode = error(env, CPXERR_ROW_INDEX_RANGE, k);
               goto done;
            }
         }
         errcode = 0;
         for (k = beg; k < end; k++)
         {  if (lp->iwork[cmatind[k]])
            {  errcode = error(env, CPXERR_DUP_ENTRY);
               break;
            }
            lp->iwork[cmatind[k]] = 1;
         }
         for (k = beg; k < end; k++)
            lp->iwork[cmatind[k]] = 0;
         if (errcode) goto done;
         if (colname != NULL)
         {  if (colname[j] == NULL)
            {  errcode = error(env, CPXERR_NULL_NAME, j);
               goto done;
            }
         }
      }
      errcode = 0;
      invalidate(lp);
      if (ccnt > 0)
         glp_add_cols(lp->prob, ccnt);
      for (j = 0; j < ccnt; j++)
      {  if (colname != NULL)
            glp_set_col_name(lp->prob, n+j+1, colname[j]);
         lbnd = (lb == NULL ? 0.0 : lb[j]);
         ubnd = (ub == NULL ? +CPX_INFBOUND : ub[j]);
         if (lbnd <= -CPX_INFBOUND && ubnd >= +CPX_INFBOUND)
            type = GLP_FR;
         else if (ubnd >= +CPX_INFBOUND)
            type = GLP_LO;
         else if (lbnd <= -CPX_INFBOUND)
            type = GLP_UP;
         else if (lbnd != ubnd)
            type = GLP_DB;
         else
            type = GLP_FX;
         glp_set_col_bnds(lp->prob, n+j+1, type, lbnd, ubnd);
         if (obj != NULL)
            glp_set_obj_coef(lp->prob, n+j+1, obj[j]);
         beg = cmatbeg[j];
         end = (j < ccnt-1 ? cmatbeg[j+1] : nzcnt);
         for (k = beg; k < end; k++)
            lp->iwork[k-beg] = cmatind[k]+1;
         glp_set_mat_col(lp->prob, n+j+1, end-beg, lp->iwork-1,
            cmatval+beg-1);
         for (k = beg; k < end; k++)
            lp->iwork[k-beg] = 0;
      }
done: return errcode;
}

int CPXaddrows(CPXENV *env, CPXLP *lp, int ccnt, int rcnt, int nzcnt,
      const double rhs[], const char sense[], const int rmatbeg[],
      const int rmatind[], const double rmatval[], char *colname[],
      char *rowname[])
{     int i, j, k, m, n, beg, end, type, errcode;
      double temp;
      errcode = checklp(env, lp);
      if (errcode) goto done;
      if (ccnt < 0 || rcnt < 0 || nzcnt < 0)
      {  errcode = error(env, CPXERR_BAD_ARGUMENT);
         goto done;
      }
      if (rcnt > 0)
      {  if (rmatbeg == NULL || rmatind == NULL || rmatval == NULL)
         {  errcode = error(env, CPXERR_NULL_POINTER);
            goto done;
         }
      }
      m = glp_get_num_rows(lp->prob);
      n = glp_get_num_cols(lp->prob);
      enlargeiwork(lp, n+ccnt);
      for (i = 0; i < rcnt; i++)
      {  if (sense != NULL)
         {  if (!(sense[i] == 'L' || sense[i] == 'E' ||
                  sense[i] == 'G' || sense[i] == 'R'))
            {  errcode = error(env, CPXERR_BAD_SENSE, i);
               goto done;
            }
         }
         beg = rmatbeg[i];
         if (i > 0 && !(rmatbeg[i-1] <= beg))
         {  errcode = error(env, CPXERR_ARRAY_NOT_ASCENDING, i);
            goto done;
         }
         if (!(0 <= beg && beg <= nzcnt))
         {  errcode = error(env, CPXERR_INDEX_RANGE);
            goto done;
         }
         end = (i < rcnt-1 ? rmatbeg[i+1] : nzcnt);
         for (k = beg; k < end; k++)
         {  if (!(0 <= rmatind[k] && rmatind[k] < n+ccnt))
            {  errcode = error(env, CPXERR_COL_INDEX_RANGE, k);
               goto done;
            }
         }
         errcode = 0;
         for (k = beg; k < end; k++)
         {  if (lp->iwork[rmatind[k]])
            {  errcode = error(env, CPXERR_DUP_ENTRY);
               break;
            }
            lp->iwork[rmatind[k]] = 1;
         }
         for (k = beg; k < end; k++)
            lp->iwork[rmatind[k]] = 0;
         if (errcode) goto done;
         if (rowname != NULL)
         {  if (rowname[i] == NULL)
            {  errcode = error(env, CPXERR_NULL_NAME, i);
               goto done;
            }
         }
      }
      for (j = 0; j < ccnt; j++)
      {  if (colname != NULL)
         {  if (colname[j] == NULL)
            {  errcode = error(env, CPXERR_NULL_NAME, j);
               goto done;
            }
         }
      }
      errcode = 0;
      invalidate(lp);
      if (rcnt > 0)
         glp_add_rows(lp->prob, rcnt);
      if (ccnt > 0)
         glp_add_cols(lp->prob, ccnt);
      enlargerflag(lp);
      for (i = 0; i < rcnt; i++)
      {  if (rowname != NULL)
            glp_set_row_name(lp->prob, m+i+1, rowname[i]);
         temp = (rhs == NULL ? 0.0 : rhs[i]);
         if (sense == NULL || sense[i] == 'E')
         {  lp->rflag[m+i] = RF_NOT_RANGED;
            type = GLP_FX;
         }
         else if (sense[i] == 'L')
         {  lp->rflag[m+i] = RF_NOT_RANGED;
            type = GLP_UP;
         }
         else if (sense[i] == 'G')
         {  lp->rflag[m+i] = RF_NOT_RANGED;
            type = GLP_LO;
         }
         else if (sense[i] == 'R')
         {  lp->rflag[m+i] = RF_RANGED_POS;
            type = GLP_FX;
         }
         else
            xassert(sense != sense);
         glp_set_row_bnds(lp->prob, m+i+1, type, temp, temp);
         beg = rmatbeg[i];
         end = (i < rcnt-1 ? rmatbeg[i+1] : nzcnt);
         for (k = beg; k < end; k++)
            lp->iwork[k-beg] = rmatind[k]+1;
         glp_set_mat_row(lp->prob, m+i+1, end-beg, lp->iwork-1,
            rmatval+beg-1);
         for (k = beg; k < end; k++)
            lp->iwork[k-beg] = 0;
      }
      for (j = 0; j < ccnt; j++)
      {  if (colname != NULL)
            glp_set_col_name(lp->prob, n+j+1, colname[j]);
         glp_set_col_bnds(lp->prob, n+j+1, GLP_LO, 0.0, 0.0);
      }
done: return errcode;
}

int CPXbaropt(CPXENV *env, CPXLP *lp)
{     xassert(env == env);
      xassert(lp == lp);
      xprintf("CPXbaropt: not implemented yet\n");
      exit(EXIT_FAILURE);
      return -1;
}

int CPXbinvrow(CPXENV *env, CPXLP *lp, int i, double y[])
{     xassert(env == env);
      xassert(lp == lp);
      xassert(i == i);
      xassert(y == y);
      xprintf("CPXbinvrow: not implemented yet\n");
      exit(EXIT_FAILURE);
      return -1;
}

int CPXchgbds(CPXENV *env, CPXLP *lp, int cnt, const int indices[],
      const char lu[], const double bd[])
{     int j, n, type, errcode;
      double lbnd, ubnd;
      errcode = checklp(env, lp);
      if (errcode) goto done;
      if (cnt < 0)
      {  errcode = error(env, CPXERR_BAD_ARGUMENT);
         goto done;
      }
      if (cnt > 0)
      {  if (indices == NULL || lu == NULL || bd == NULL)
         {  errcode = error(env, CPXERR_NULL_POINTER);
            goto done;
         }
      }
      n = glp_get_num_cols(lp->prob);
      for (j = 0; j < cnt; j++)
      {  if (!(0 <= indices[j] && indices[j] < n))
         {  errcode = error(env, CPXERR_COL_INDEX_RANGE, j);
            goto done;
         }
         if (!(lu[j] == 'L' || lu[j] == 'U' || lu[j] == 'B'))
         {  errcode = error(env, CPXERR_BAD_LUB, j);
            goto done;
         }
      }
      errcode = 0;
      invalidate(lp);
      for (j = 0; j < cnt; j++)
      {  type = glp_get_col_type(lp->prob, indices[j]+1);
         lbnd = glp_get_col_lb(lp->prob, indices[j]+1);
         ubnd = glp_get_col_ub(lp->prob, indices[j]+1);
         if (type == GLP_FR || type == GLP_UP)
            lbnd = -CPX_INFBOUND;
         if (type == GLP_FR || type == GLP_LO)
            ubnd = +CPX_INFBOUND;
         if (lu[j] == 'L')
            lbnd = bd[j];
         else if (lu[j] == 'U')
            ubnd = bd[j];
         else if (lu[j] == 'B')
            lbnd = ubnd = bd[j];
         else
            xassert(lu != lu);
         if (lbnd <= -CPX_INFBOUND && ubnd >= +CPX_INFBOUND)
            type = GLP_FR;
         else if (ubnd >= +CPX_INFBOUND)
            type = GLP_LO;
         else if (lbnd <= -CPX_INFBOUND)
            type = GLP_UP;
         else if (lbnd != ubnd)
            type = GLP_DB;
         else
            type = GLP_FX;
         glp_set_col_bnds(lp->prob, indices[j]+1, type, lbnd, ubnd);
      }
done: return errcode;
}

int CPXchgcoeflist(CPXENV *env, CPXLP *lp, int numcoefs,
      const int rowlist[], const int collist[], const double vallist[])
{     int i, j, k, m, n, rcnt, ccnt, len, ptr, errcode;
      int *head, *next, *ind;
      double *val;
      errcode = checklp(env, lp);
      if (errcode) goto done;
      if (numcoefs < 0)
      {  errcode = error(env, CPXERR_BAD_ARGUMENT);
         goto done;
      }
      if (numcoefs == 0)
      {  errcode = 0;
         goto done;
      }
      if (rowlist == NULL || collist == NULL || vallist == NULL)
      {  errcode = error(env, CPXERR_NULL_POINTER);
         goto done;
      }
      /* check triplets and determine the number of rows and columns
         to be changed */
      m = glp_get_num_rows(lp->prob);
      n = glp_get_num_cols(lp->prob);
      enlargeiwork(lp, m);
      enlargeiwork(lp, n);
      rcnt = ccnt = 0;
      for (k = 0; k < numcoefs; k++)
      {  i = rowlist[k];
         if (!(0 <= i && i < m))
         {  errcode = error(env, CPXERR_ROW_INDEX_RANGE, i);
            goto done;
         }
         if (!(lp->iwork[i] & 0x01))
            rcnt++, lp->iwork[i] |= 0x01;
         j = collist[k];
         if (!(0 <= j && j < n))
         {  errcode = error(env, CPXERR_COL_INDEX_RANGE, j);
            goto done;
         }
         if (!(lp->iwork[j] & 0x02))
            ccnt++, lp->iwork[j] |= 0x02;
      }
      memset(lp->iwork, 0, m * sizeof(int));
      memset(lp->iwork, 0, n * sizeof(int));
      errcode = 0;
      invalidate(lp);
      if (rcnt <= ccnt)
      {  /* change the matrix by rows */
         /* build the linked list of triplets:
            head[i] is a pointer to first triplet for row i
            next[k] is a pointer to next triplet for the same row */
         head = xcalloc(m, sizeof(int));
         for (i = 0; i < m; i++)
            head[i] = -1;
         next = xcalloc(numcoefs, sizeof(int));
         for (k = 0; k < numcoefs; k++)
         {  i = rowlist[k];
            next[k] = head[i];
            head[i] = k;
         }
         /* check duplicate columns */
         for (i = 0; i < m; i++)
         {  for (k = head[i]; k >= 0; k = next[k])
            {  j = collist[k];
               if (lp->iwork[j])
               {  xfree(head);
                  xfree(next);
                  errcode = error(env, CPXERR_DUP_ENTRY);
                  goto done;
               }
               lp->iwork[j] = 1;
            }
            for (k = head[i]; k >= 0; k = next[k])
               lp->iwork[collist[k]] = 0;
         }
         /* perform operation */
         ind = xcalloc(1+n, sizeof(int));
         val = xcalloc(1+n, sizeof(double));
         for (i = 0; i < m; i++)
         {  if (head[i] < 0) continue;
            len = glp_get_mat_row(lp->prob, i+1, ind, val);
            for (ptr = 1; ptr <= len; ptr++)
            {  j = ind[ptr]-1;
               xassert(lp->iwork[j] == 0);
               lp->iwork[j] = ptr;
            }
            for (k = head[i]; k >= 0; k = next[k])
            {  j = collist[k];
               if (lp->iwork[j] == 0)
                  lp->iwork[j] = ++len;
               ptr = lp->iwork[j];
               ind[ptr] = j+1, val[ptr] = vallist[k];
            }
            glp_set_mat_row(lp->prob, i+1, len, ind, val);
            for (ptr = 1; ptr <= len; ptr++)
               lp->iwork[ind[ptr]-1] = 0;
         }
      }
      else
      {  /* change the matrix by columns */
         /* build the linked lists of triplets:
            head[j] is a pointer to first triplet for column j
            next[k] is a pointer to next triplet for the same column */
         head = xcalloc(n, sizeof(int));
         for (j = 0; j < n; j++)
            head[j] = -1;
         next = xcalloc(numcoefs, sizeof(int));
         for (k = 0; k < numcoefs; k++)
         {  j = collist[k];
            next[k] = head[j];
            head[j] = k;
         }
         /* check duplicate rows */
         for (j = 0; j < n; j++)
         {  for (k = head[j]; k >= 0; k = next[k])
            {  i = rowlist[k];
               if (lp->iwork[i])
               {  xfree(head);
                  xfree(next);
                  errcode = error(env, CPXERR_DUP_ENTRY);
                  goto done;
               }
               lp->iwork[i] = 1;
            }
            for (k = head[j]; k >= 0; k = next[k])
               lp->iwork[rowlist[k]] = 0;
         }
         /* perform operation */
         ind = xcalloc(1+m, sizeof(int));
         val = xcalloc(1+m, sizeof(double));
         for (j = 0; j < n; j++)
         {  if (head[j] < 0) continue;
            len = glp_get_mat_col(lp->prob, j+1, ind, val);
            for (ptr = 1; ptr <= len; ptr++)
            {  i = ind[ptr]-1;
               xassert(lp->iwork[i] == 0);
               lp->iwork[i] = ptr;
            }
            for (k = head[j]; k >= 0; k = next[k])
            {  i = rowlist[k];
               if (lp->iwork[i] == 0)
                  lp->iwork[i] = ++len;
               ptr = lp->iwork[i];
               ind[ptr] = i+1, val[ptr] = vallist[k];
            }
            glp_set_mat_col(lp->prob, j+1, len, ind, val);
            for (ptr = 1; ptr <= len; ptr++)
               lp->iwork[ind[ptr]-1] = 0;
         }
      }
      xfree(head);
      xfree(next);
      xfree(ind);
      xfree(val);
done: return errcode;
}

void CPXchgobjsen(CPXENV *env, CPXLP *lp, int maxormin)
{     int errcode;
      errcode = checklp(env, lp);
      if (errcode) goto done;
      if (!(maxormin == CPX_MIN || maxormin == CPX_MAX))
      {  errcode = error(env, CPXERR_BAD_ARGUMENT);
         goto done;
      }
      errcode = 0;
      invalidate(lp);
      if (maxormin == CPX_MIN)
         glp_set_obj_dir(lp->prob, GLP_MIN);
      else
         glp_set_obj_dir(lp->prob, GLP_MAX);
done: xassert(errcode == errcode);
      return;
}

int CPXchgsense(CPXENV *env, CPXLP *lp, int cnt, const int indices[],
      const char sense[])
{     int i, m, type, errcode;
      double rhs;
      errcode = checklp(env, lp);
      if (errcode) goto done;
      if (cnt < 0)
      {  errcode = error(env, CPXERR_BAD_ARGUMENT);
         goto done;
      }
      if (cnt > 0 && (indices == NULL || sense == NULL))
      {  errcode = error(env, CPXERR_NULL_POINTER);
         goto done;
      }
      m = glp_get_num_rows(lp->prob);
      for (i = 0; i < cnt; i++)
      {  if (!(0 <= indices[i] && indices[i] < m))
         {  errcode = error(env, CPXERR_ROW_INDEX_RANGE, i);
            goto done;
         }
         if (!(sense[i] == 'L' || sense[i] == 'E' || sense[i] == 'G' ||
               sense[i] == 'R'))
         {  errcode = error(env, CPXERR_BAD_SENSE, i);
            goto done;
         }
      }
      errcode = 0;
      invalidate(lp);
      for (i = 0; i < cnt; i++)
      {  type = glp_get_row_type(lp->prob, indices[i]+1);
         if (lp->rflag[indices[i]] == RF_NOT_RANGED)
         {  if (type == GLP_LO || type == GLP_FX)
               rhs = glp_get_row_lb(lp->prob, indices[i]+1);
            else if (type == GLP_UP)
               rhs = glp_get_row_ub(lp->prob, indices[i]+1);
            else
               xassert(type != type);
         }
         else if (lp->rflag[indices[i]] == RF_RANGED_POS)
         {  xassert(type == GLP_DB || type == GLP_FX);
            rhs = glp_get_row_lb(lp->prob, indices[i]+1);
         }
         else if (lp->rflag[indices[i]] == RF_RANGED_NEG)
         {  xassert(type == GLP_DB);
            rhs = glp_get_row_ub(lp->prob, indices[i]+1);
         }
         else
            xassert(lp != lp);
         if (sense[i] == 'L')
         {  lp->rflag[indices[i]] = RF_NOT_RANGED;
            type = GLP_UP;
         }
         else if (sense[i] == 'E')
         {  lp->rflag[indices[i]] = RF_NOT_RANGED;
            type = GLP_FX;
         }
         else if (sense[i] == 'G')
         {  lp->rflag[indices[i]] = RF_NOT_RANGED;
            type = GLP_LO;
         }
         else if (sense[i] == 'R')
         {  lp->rflag[indices[i]] = RF_RANGED_POS;
            type = GLP_FX;
         }
         else
            xassert(sense != sense);
         glp_set_row_bnds(lp->prob, indices[i]+1, type, rhs, rhs);
      }
done: return errcode;
}

int CPXcloseCPLEX(CPXENV **_env)
{     CPXENV *env;
      CPXLP *lp;
      int errcode;
      if (_env == NULL)
      {  errcode = CPXERR_NULL_POINTER;
         goto done;
      }
      env = *_env;
      errcode = checkenv(env);
      if (errcode) goto done;
      while (env->list != NULL)
      {  lp = env->list;
         errcode = CPXfreeprob(env, &lp);
         xassert(!errcode);
      }
      xfree(env->intparam);
      xfree(env->dblparam);
      xfree(env);
      *_env = NULL;
      errcode = 0;
done: return errcode;
}

int CPXcopybase(CPXENV *env, CPXLP *lp, const int cstat[],
      const int rstat[])
{     int i, j, m, n, stat, errcode;
      errcode = checklp(env, lp);
      if (errcode) goto done;
      m = glp_get_num_rows(lp->prob);
      n = glp_get_num_cols(lp->prob);
      if (m > 0 && rstat == NULL || n > 0 && cstat == NULL)
      {  errcode = error(env, CPXERR_NULL_POINTER);
         goto done;
      }
      for (i = 0; i < m; i++)
      {  if (!(rstat[i] == CPX_AT_LOWER || rstat[i] == CPX_BASIC ||
               rstat[i] == CPX_AT_UPPER))
         {  errcode = error(env, CPXERR_BAD_STATUS, i);
            goto done;
         }
      }
      for (j = 0; j < n; j++)
      {  if (!(cstat[j] == CPX_AT_LOWER || cstat[j] == CPX_BASIC ||
               cstat[j] == CPX_AT_UPPER || cstat[j] == CPX_FREE_SUPER))
         {  errcode = error(env, CPXERR_BAD_STATUS, j);
            goto done;
         }
      }
      errcode = 0;
      invalidate(lp);
      for (i = 0; i < m; i++)
      {  if (rstat[i] == CPX_AT_LOWER)
            stat = GLP_NL;
         else if (rstat[i] == CPX_BASIC)
            stat = GLP_BS;
         else if (rstat[i] == CPX_AT_UPPER)
            stat = GLP_NU;
         else
            xassert(rstat != rstat);
         glp_set_row_stat(lp->prob, i+1, stat);
      }
      for (j = 0; j < n; j++)
      {  if (cstat[j] == CPX_AT_LOWER)
            stat = GLP_NL;
         else if (cstat[j] == CPX_BASIC)
            stat = GLP_BS;
         else if (cstat[j] == CPX_AT_UPPER)
            stat = GLP_NU;
         else if (cstat[j] == CPX_FREE_SUPER)
            stat = GLP_NF;
         else
            xassert(cstat != cstat);
         glp_set_col_stat(lp->prob, j+1, stat);
      }
done: return errcode;
}

int CPXcopybasednorms(CPXENV *env, CPXLP *lp, const int cstat[],
      const int rstat[], const double dnorm[])
{     int errcode;
      errcode = CPXcopybase(env, lp, cstat, rstat);
      xassert(dnorm == dnorm);
      return errcode;
}

int CPXcopylp(CPXENV *env, CPXLP *lp, int numcols, int numrows,
      int objsen, const double obj[], const double rhs[],
      const char sense[], const int matbeg[], const int matcnt[],
      const int matind[], const double matval[], const double lb[],
      const double ub[], const double rngval[])
{     int errcode;
      errcode = CPXcopylpwnames(env, lp, numcols, numrows, objsen, obj,
         rhs, sense, matbeg, matcnt, matind, matval, lb, ub, rngval,
         NULL, NULL);
      return errcode;
}

int CPXcopylpwnames(CPXENV *env, CPXLP *lp, int numcols, int numrows,
      int objsen, const double obj[], const double rhs[],
      const char sense[], const int matbeg[], const int matcnt[],
      const int matind[], const double matval[], const double lb[],
      const double ub[], const double rngval[], char *colname[],
      char *rowname[])
{     int i, j, k, beg, end, type, errcode;
      double lbnd, ubnd;
      char name[255+1];
      errcode = checklp(env, lp);
      if (errcode) goto done;
      if (numcols < 0 || numrows < 0)
      {  errcode = error(env, CPXERR_BAD_ARGUMENT);
         goto done;
      }
      if (!(objsen == CPX_MIN || objsen == CPX_MAX))
      {  errcode = error(env, CPXERR_BAD_ARGUMENT);
         goto done;
      }
      if (numcols > 0)
      {  if (matbeg == NULL || matcnt == NULL || matind == NULL ||
               matval == NULL)
         {  errcode = error(env, CPXERR_NULL_POINTER);
            goto done;
         }
      }
      for (i = 0; i < numrows; i++)
      {  if (sense != NULL)
         {  if (!(sense[i] == 'L' || sense[i] == 'E' ||
                  sense[i] == 'G' || sense[i] == 'R'))
            {  errcode = error(env, CPXERR_BAD_SENSE, i);
               goto done;
            }
         }
         if (rowname != NULL)
         {  if (rowname[i] == NULL)
            {  errcode = error(env, CPXERR_NULL_NAME, i);
               goto done;
            }
         }
      }
      enlargeiwork(lp, numrows);
      for (j = 0; j < numcols; j++)
      {  beg = matbeg[j];
         if (j > 0 && !(matbeg[j-1] <= beg))
         {  errcode = error(env, CPXERR_ARRAY_NOT_ASCENDING, j);
            goto done;
         }
         if (beg < 0)
         {  errcode = error(env, CPXERR_INDEX_RANGE);
            goto done;
         }
         end = beg + matcnt[j];
         if (!(beg <= end) || j < numcols-1 && !(end <= matbeg[j+1]))
         {  errcode = error(env, CPXERR_COUNT_RANGE, j);
            goto done;
         }
         for (k = beg; k < end; k++)
         {  if (!(0 <= matind[k] && matind[k] < numrows))
            {  errcode = error(env, CPXERR_ROW_INDEX_RANGE, k);
               goto done;
            }
         }
         errcode = 0;
         for (k = beg; k < end; k++)
         {  if (lp->iwork[matind[k]])
            {  errcode = error(env, CPXERR_DUP_ENTRY);
               break;
            }
            lp->iwork[matind[k]] = 1;
         }
         for (k = beg; k < end; k++)
            lp->iwork[matind[k]] = 0;
         if (errcode) goto done;
         if (colname != NULL)
         {  if (colname[j] != NULL)
            {  errcode = error(env, CPXERR_NULL_NAME, j);
               goto done;
            }
         }
      }
      errcode = 0;
      invalidate(lp);
      if (glp_get_prob_name(lp->prob) == NULL)
         name[0] = '\0';
      else
         strcpy(name, glp_get_prob_name(lp->prob));
      glp_erase_prob(lp->prob);
      glp_set_prob_name(lp->prob, name);
      if (objsen == CPX_MIN)
         glp_set_obj_dir(lp->prob, GLP_MIN);
      else if (objsen == CPX_MAX)
         glp_set_obj_dir(lp->prob, GLP_MAX);
      else
         xassert(objsen != objsen);
      if (numrows > 0)
         glp_add_rows(lp->prob, numrows);
      enlargerflag(lp);
      for (i = 0; i < numrows; i++)
      {  if (rowname != NULL)
            glp_set_row_name(lp->prob, i+1, rowname[i]);
         lbnd = ubnd = (rhs == NULL ? 0.0 : rhs[i]);
         if (sense == NULL || sense[i] == 'E')
         {  lp->rflag[i] = RF_NOT_RANGED;
            type = GLP_FX;
         }
         else if (sense[i] == 'L')
         {  lp->rflag[i] = RF_NOT_RANGED;
            type = GLP_UP;
         }
         else if (sense[i] == 'G')
         {  lp->rflag[i] = RF_NOT_RANGED;
            type = GLP_LO;
         }
         else if (sense[i] == 'R')
         {  if (rngval == NULL || rngval[i] == 0.0)
            {  lp->rflag[i] = RF_RANGED_POS;
               type = GLP_FX;
            }
            else if (rngval[i] > 0.0)
            {  lp->rflag[i] = RF_RANGED_POS;
               type = GLP_DB;
               ubnd += rngval[i];
            }
            else /* rngval[i] < 0.0 */
            {  lp->rflag[i] = RF_RANGED_NEG;
               type = GLP_DB;
               lbnd += rngval[i];
            }
         }
         else
            xassert(sense != sense);
         glp_set_row_bnds(lp->prob, i+1, type, lbnd, ubnd);
      }
      if (numcols > 0)
         glp_add_cols(lp->prob, numcols);
      for (j = 0; j < numcols; j++)
      {  if (colname != NULL)
            glp_set_col_name(lp->prob, j+1, colname[j]);
         lbnd = (lb == NULL ? 0.0 : lb[j]);
         ubnd = (ub == NULL ? +CPX_INFBOUND : ub[j]);
         if (lbnd <= -CPX_INFBOUND && ubnd >= +CPX_INFBOUND)
            type = GLP_FR;
         else if (ubnd >= +CPX_INFBOUND)
            type = GLP_LO;
         else if (lbnd <= -CPX_INFBOUND)
            type = GLP_UP;
         else if (lbnd != ubnd)
            type = GLP_DB;
         else
            type = GLP_FX;
         glp_set_col_bnds(lp->prob, j+1, type, lbnd, ubnd);
         if (obj != NULL)
            glp_set_obj_coef(lp->prob, j+1, obj[j]);
         beg = matbeg[j];
         end = beg + matcnt[j];
         for (k = beg; k < end; k++)
            lp->iwork[k-beg] = matind[k]+1;
         glp_set_mat_col(lp->prob, j+1, end-beg, lp->iwork-1,
            matval+beg-1);
         for (k = beg; k < end; k++)
            lp->iwork[k-beg] = 0;
      }
done: return errcode;
}

CPXLP *CPXcreateprob(CPXENV *env, int *status, const char *probname)
{     CPXLP *lp = NULL;
      int errcode;
      errcode = checkenv(env);
      if (errcode) goto done;
      lp = xmalloc(sizeof(struct CPXLP));
      lp->env = env;
      lp->prob = glp_create_prob();
      glp_set_prob_name(lp->prob, probname);
      lp->rflen = 100;
      lp->rflag = xcalloc(lp->rflen, sizeof(char));
      lp->iwlen = 100;
      lp->iwork = xcalloc(lp->iwlen, sizeof(int));
      memset(lp->iwork, 0, lp->iwlen * sizeof(int));
      lp->link = env->list;
      env->list = lp;
      invalidate(lp);
done: if (status != NULL) *status = errcode;
      return lp;
}

int CPXdelcols(CPXENV *env, CPXLP *lp, int begin, int end)
{     int j, n, errcode;
      errcode = checklp(env, lp);
      if (errcode) goto done;
      n = glp_get_num_cols(lp->prob);
      if (!(0 <= begin && begin <= end && end < n))
      {  errcode = error(env, CPXERR_INDEX_RANGE);
         goto done;
      }
      errcode = 0;
      invalidate(lp);
      enlargeiwork(lp, end-begin+1);
      for (j = begin; j <= end; j++)
         lp->iwork[j-begin] = j+1;
      glp_del_cols(lp->prob, end-begin+1, lp->iwork-1);
      for (j = begin; j <= end; j++)
         lp->iwork[j-begin] = 0;
done: return errcode;
}

int CPXdelrows(CPXENV *env, CPXLP *lp, int begin, int end)
{     int i, m, errcode;
      errcode = checklp(env, lp);
      if (errcode) goto done;
      m = glp_get_num_rows(lp->prob);
      if (!(0 <= begin && begin <= end && end < m))
      {  errcode = error(env, CPXERR_INDEX_RANGE);
         goto done;
      }
      errcode = 0;
      invalidate(lp);
      enlargeiwork(lp, end-begin+1);
      for (i = begin; i <= end; i++)
         lp->iwork[i-begin] = i+1;
      glp_del_rows(lp->prob, end-begin+1, lp->iwork-1);
      for (i = begin; i <= end; i++)
         lp->iwork[i-begin] = 0;
      for (i = end+1; i < m; i++)
         lp->rflag[i-(end-begin+1)] = lp->rflag[i];
done: return errcode;
}

int CPXdelsetcols(CPXENV *env, CPXLP *lp, int delstat[])
{     xassert(env == env);
      xassert(lp == lp);
      xassert(delstat == delstat);
      xprintf("CPXdelsetcols: not implemented yet\n");
      exit(EXIT_FAILURE);
      return -1;
}

int CPXdelsetrows(CPXENV *env, CPXLP *lp, int delstat[])
{     int i, m, cnt, ind, errcode;
      errcode = checklp(env, lp);
      if (errcode) goto done;
      m = glp_get_num_rows(lp->prob);
      if (m > 0 && delstat == NULL)
      {  errcode = error(env, CPXERR_NULL_POINTER);
         goto done;
      }
      errcode = 0;
      invalidate(lp);
      enlargeiwork(lp, m);
      cnt = ind = 0;
      for (i = 0; i < m; i++)
      {  if (delstat[i] == 1)
         {  delstat[i] = -1;
            lp->iwork[cnt++] = i+1;
         }
         else
         {  delstat[i] = ind;
            lp->rflag[ind++] = lp->rflag[i];
         }
      }
      if (cnt > 0)
         glp_del_rows(lp->prob, cnt, lp->iwork-1);
      for (i = 0; i < cnt; i++)
         lp->iwork[i] = 0;
done: return errcode;
}

int CPXdualopt(CPXENV *env, CPXLP *lp);

int CPXfreeprob(CPXENV *env, CPXLP **_lp)
{     CPXLP *lp;
      int errcode;
      errcode = checkenv(env);
      if (errcode) goto done;
      if (_lp == NULL)
      {  errcode = error(env, CPXERR_NULL_POINTER);
         goto done;
      }
      lp = *_lp;
      errcode = checklp(env, lp);
      if (errcode) goto done;
      errcode = 0;
      env = lp->env;
      if (env->list == lp)
         env->list = lp->link;
      else
      {  CPXLP *pp;
         for (pp = env->list; pp != NULL; pp = pp->link)
            if (pp->link == lp) break;
         xassert(pp != NULL);
         pp->link = lp->link;
      }
      glp_delete_prob(lp->prob);
      xfree(lp->rflag);
      xfree(lp->iwork);
      xfree(lp);
      *_lp = NULL;
done: return errcode;
}

int CPXgetbase(CPXENV *env, CPXLP *lp, int cstat[], int rstat[])
{     int i, j, m, n, stat, errcode;
      errcode = checklp(env, lp);
      if (errcode) goto done;
      if (!lp->stat)
      {  errcode = error(env, CPXERR_NO_SOLN);
         goto done;
      }
      if (lp->meth == CPX_ALG_PRIMAL || lp->meth == CPX_ALG_DUAL)
         ;
      else
      {  errcode = error(env, CPXERR_NO_BASIC_SOLN);
         goto done;
      }
      errcode = 0;
      if (rstat != NULL)
      {  m = glp_get_num_rows(lp->prob);
         for (i = 0; i < m; i++)
         {  stat = glp_get_row_stat(lp->prob, i+1);
            if (stat == GLP_BS)
               rstat[i] = CPX_BASIC;
            else if (lp->rflag[i] == RF_NOT_RANGED || stat != GLP_NU)
               rstat[i] = CPX_AT_LOWER;
            else
               rstat[i] = CPX_AT_UPPER;
         }
      }
      if (cstat != NULL)
      {  n = glp_get_num_cols(lp->prob);
         for (j = 0; j < n; j++)
         {  stat = glp_get_col_stat(lp->prob, j+1);
            if (stat == GLP_BS)
               cstat[j] = CPX_BASIC;
            else if (stat == GLP_NU)
               cstat[j] = CPX_AT_UPPER;
            else if (stat == GLP_NF)
               cstat[j] = CPX_FREE_SUPER;
            else
               cstat[j] = CPX_AT_LOWER;
         }
      }
done: return errcode;
}

int CPXgetbasednorms(CPXENV *env, CPXLP *lp, int cstat[], int rstat[],
      double dnorm[])
{     int i, m, errcode;
      errcode = CPXgetbase(env, lp, cstat, rstat);
      if (errcode) goto done;
      if (dnorm != NULL)
      {  m = glp_get_num_rows(lp->prob);
         for (i = 0; i < m; i++) dnorm[i] = 1.0;
      }
done: return errcode;
}

int CPXgetbhead(CPXENV *env, CPXLP *lp, int head[], double x[])
{     xassert(env == env);
      xassert(lp == lp);
      xassert(head == head);
      xassert(x == x);
      xprintf("CPXgetbhead: not implemented yet\n");
      exit(EXIT_FAILURE);
      return -1;
}

int CPXgetdblparam(CPXENV *env, int whichparam, double *value)
{     int k, errcode;
      errcode = checkenv(env);
      if (errcode) goto done;
      k = finddblparam(whichparam);
      if (k < 0)
      {  errcode = error(env, CPXERR_BAD_PARAM_NUM);
         goto done;
      }
      errcode = 0;
      if (value != NULL)
         *value = env->dblparam[k];
done: return errcode;
}

int CPXgetdj(CPXENV *env, CPXLP *lp, double dj[], int begin, int end)
{     int j, n, errcode;
      errcode = checklp(env, lp);
      if (errcode) goto done;
      n = glp_get_num_cols(lp->prob);
      if (!(0 <= begin && begin <= end && end < n))
      {  errcode = error(env, CPXERR_INDEX_RANGE);
         goto done;
      }
      if (!lp->stat)
      {  errcode = error(env, CPXERR_NO_SOLN);
         goto done;
      }
      errcode = 0;
      if (lp->meth == CPX_ALG_PRIMAL || lp->meth == CPX_ALG_DUAL)
      {  if (dj != NULL)
         {  for (j = begin; j <= end; j++)
               dj[j-begin] = glp_get_col_dual(lp->prob, j+1);
         }
      }
      else
         xassert(lp != lp);
done: return errcode;
}

char *CPXgeterrorstring(CPXENV *env, int errcode, char *buffer)
{     const char *string;
      xassert(env == env);
      string = finderrstring(errcode);
      if (string == NULL)
         buffer = NULL;
      else
         sprintf(buffer, "CPLEX Error %5d:  %s.\n", errcode, string);
      return buffer;
}

int CPXgetijdiv(CPXENV *env, CPXLP *lp, int *idiv, int *jdiv)
{     xassert(env == env);
      xassert(lp == lp);
      xassert(idiv == idiv);
      xassert(jdiv == jdiv);
      xprintf("CPXgetijdiv: not implemented yet\n");
      exit(EXIT_FAILURE);
      return -1;
}

int CPXgetintparam(CPXENV *env, int whichparam, int *value)
{     int k, errcode;
      errcode = checkenv(env);
      if (errcode) goto done;
      k = findintparam(whichparam);
      if (k < 0)
      {  errcode = error(env, CPXERR_BAD_PARAM_NUM);
         goto done;
      }
      errcode = 0;
      if (value != NULL)
         *value = env->intparam[k];
done: return errcode;
}

int CPXgetlb(CPXENV *env, CPXLP *lp, double lb[], int begin, int end)
{     xassert(env == env);
      xassert(lp == lp);
      xassert(lb == lb);
      xassert(begin == begin);
      xassert(end == end);
      xprintf("CPXgetlb: not implemented yet\n");
      exit(EXIT_FAILURE);
      return -1;
}

int CPXgetmethod(CPXENV *env, CPXLP *lp)
{     int method;
      if (checklp(env, lp))
         method = CPX_ALG_NONE;
      else
         method = lp->meth;
      return method;
}

int CPXgetnumcols(CPXENV *env, CPXLP *lp)
{     int numcols;
      if (checklp(env, lp))
         numcols = 0;
      else
         numcols = glp_get_num_cols(lp->prob);
      return numcols;
}

int CPXgetnumnz(CPXENV *env, CPXLP *lp)
{     int numnz;
      if (checklp(env, lp))
         numnz = 0;
      else
         numnz = glp_get_num_nz(lp->prob);
      return numnz;
}

int CPXgetnumrows(CPXENV *env, CPXLP *lp)
{     int numrows;
      if (checklp(env, lp))
         numrows = 0;
      else
         numrows = glp_get_num_rows(lp->prob);
      return numrows;
}

int CPXgetobjval(CPXENV *env, CPXLP *lp, double *objval)
{     int errcode;
      errcode = checklp(env, lp);
      if (errcode) goto done;
      if (!lp->stat)
      {  errcode = error(env, CPXERR_NO_SOLN);
         goto done;
      }
      errcode = 0;
      if (lp->meth == CPX_ALG_PRIMAL || lp->meth == CPX_ALG_DUAL)
      {  if (objval != NULL)
            *objval = glp_get_obj_val(lp->prob);
      }
      else
         xassert(lp != lp);
done: return errcode;
}

int CPXgetpi(CPXENV *env, CPXLP *lp, double pi[], int begin, int end)
{     int i, m, errcode;
      errcode = checklp(env, lp);
      if (errcode) goto done;
      m = glp_get_num_rows(lp->prob);
      if (!(0 <= begin && begin <= end && end < m))
      {  errcode = error(env, CPXERR_INDEX_RANGE);
         goto done;
      }
      if (!lp->stat)
      {  errcode = error(env, CPXERR_NO_SOLN);
         goto done;
      }
      errcode = 0;
      if (lp->meth == CPX_ALG_PRIMAL || lp->meth == CPX_ALG_DUAL)
      {  if (pi != NULL)
         {  for (i = begin; i <= end; i++)
               pi[i-begin] = glp_get_row_dual(lp->prob, i+1);
         }
      }
      else
         xassert(lp != lp);
done: return errcode;
}

int CPXgetsense(CPXENV *env, CPXLP *lp, char sense[], int begin,
      int end)
{     xassert(env == env);
      xassert(lp == lp);
      xassert(sense == sense);
      xassert(begin == begin);
      xassert(end == end);
      xprintf("CPXgetsense: not implemented yet\n");
      exit(EXIT_FAILURE);
      return -1;
}

int CPXgetslack(CPXENV *env, CPXLP *lp, double slack[], int begin,
      int end)
{     int i, m, type, errcode;
      double temp;
      errcode = checklp(env, lp);
      if (errcode) goto done;
      m = glp_get_num_rows(lp->prob);
      if (!(0 <= begin && begin <= end && end < m))
      {  errcode = error(env, CPXERR_INDEX_RANGE);
         goto done;
      }
      if (!lp->stat)
      {  errcode = error(env, CPXERR_NO_SOLN);
         goto done;
      }
      errcode = 0;
      if (lp->meth == CPX_ALG_PRIMAL || lp->meth == CPX_ALG_DUAL)
      {  if (slack != NULL)
         {  for (i = begin; i <= end; i++)
            {  type = glp_get_row_type(lp->prob, i+1);
               temp = glp_get_row_prim(lp->prob, i+1);
               if (lp->rflag[i] == RF_NOT_RANGED)
               {  if (type == GLP_LO || type == GLP_FX)
                     slack[i-begin] =
                        glp_get_row_lb(lp->prob, i+1) - temp;
                  else if (type == GLP_UP)
                     slack[i-begin] =
                        glp_get_row_ub(lp->prob, i+1) - temp;
                  else
                     xassert(type != type);
               }
               else if (lp->rflag[i] == RF_RANGED_POS)
               {  xassert(type == GLP_DB || type == GLP_FX);
                  slack[i-begin] =
                     temp - glp_get_row_lb(lp->prob, i+1);
               }
               else if (lp->rflag[i] == RF_RANGED_NEG)
               {  xassert(type == GLP_DB);
                  slack[i-begin] =
                     temp - glp_get_row_ub(lp->prob, i+1);
               }
               else
                  xassert(lp != lp);
            }
         }
      }
      else
         xassert(lp != lp);
done: return errcode;
}

int CPXgetstat(CPXENV *env, CPXLP *lp)
{     int stat;
      if (checklp(env, lp))
         stat = 0;
      else
         stat = lp->stat;
      return stat;
}

int CPXgetub(CPXENV *env, CPXLP *lp, double ub[], int begin, int end)
{     xassert(env == env);
      xassert(lp == lp);
      xassert(ub == ub);
      xassert(begin == begin);
      xassert(end == end);
      xprintf("CPXgetub: not implemented yet\n");
      exit(EXIT_FAILURE);
      return -1;
}

int CPXgetweight(CPXENV *env, CPXLP *lp, int rcnt, const int rmatbeg[],
      const int rmatind[], const double rmatval[], double weight[],
      int dpriind)
{     xassert(env == env);
      xassert(lp == lp);
      xassert(rcnt == rcnt);
      xassert(rmatbeg == rmatbeg);
      xassert(rmatind == rmatind);
      xassert(rmatval == rmatval);
      xassert(weight == weight);
      xassert(dpriind == dpriind);
      xprintf("CPXgetweight: not implemented yet\n");
      exit(EXIT_FAILURE);
      return -1;
}

int CPXgetx(CPXENV *env, CPXLP *lp, double x[], int begin, int end)
{     int j, n, errcode;
      errcode = checklp(env, lp);
      if (errcode) goto done;
      n = glp_get_num_cols(lp->prob);
      if (!(0 <= begin && begin <= end && end < n))
      {  errcode = error(env, CPXERR_INDEX_RANGE);
         goto done;
      }
      if (!lp->stat)
      {  errcode = error(env, CPXERR_NO_SOLN);
         goto done;
      }
      errcode = 0;
      if (lp->meth == CPX_ALG_PRIMAL || lp->meth == CPX_ALG_DUAL)
      {  if (x != NULL)
         {  for (j = begin; j <= end; j++)
               x[j-begin] = glp_get_col_prim(lp->prob, j+1);
         }
      }
      else
         xassert(lp != lp);
done: return errcode;
}

int CPXinfodblparam(CPXENV *env, int whichparam, double *defvalue,
      double *minvalue, double *maxvalue)
{     int k, errcode;
      errcode = checkenv(env);
      if (errcode) goto done;
      k = finddblparam(whichparam);
      if (k < 0)
      {  errcode = error(env, CPXERR_BAD_PARAM_NUM);
         goto done;
      }
      errcode = 0;
      if (defvalue != NULL)
         *defvalue = dblparam[k].defv;
      if (minvalue != NULL)
         *minvalue = dblparam[k].minv;
      if (maxvalue != NULL)
         *maxvalue = dblparam[k].maxv;
done: return errcode;
}

int CPXinfointparam(CPXENV *env, int whichparam, int *defvalue,
      int *minvalue, int *maxvalue)
{     int k, errcode;
      errcode = checkenv(env);
      if (errcode) goto done;
      k = findintparam(whichparam);
      if (k < 0)
      {  errcode = error(env, CPXERR_BAD_PARAM_NUM);
         goto done;
      }
      errcode = 0;
      if (defvalue != NULL)
         *defvalue = intparam[k].defv;
      if (minvalue != NULL)
         *minvalue = intparam[k].minv;
      if (maxvalue != NULL)
         *maxvalue = intparam[k].maxv;
done: return errcode;
}

int CPXmdleave(const CPXENV *env, CPXLP *lp, const int goodlist[],
      int goodlen, double downratio[], double upratio[])
{     int k;
      xassert(env == env);
      xassert(lp == lp);
      xassert(goodlist == goodlist);
      xassert(goodlen >= 0);
      xassert(downratio != NULL);
      xassert(upratio != NULL);
      /* not implemented yet */
      for (k = 0; k < goodlen; k++)
         downratio[k] = upratio[k] = 0.0;
      return 0;
}

int CPXnewcols(CPXENV *env, CPXLP *lp, int ccnt, const double obj[],
      const double lb[], const double ub[], const char ctype[],
      char *colname[])
{     int j, n, kind, type, errcode;
      double lbnd, ubnd;
      errcode = checklp(env, lp);
      if (errcode) goto done;
      if (ccnt < 0)
      {  errcode = error(env, CPXERR_BAD_ARGUMENT);
         goto done;
      }
      for (j = 0; j < ccnt; j++)
      {  if (ctype != NULL)
         {  if (!(ctype[j] == 'C' || ctype[j] == 'B' ||
                  ctype[j] == 'I'))
            {  errcode = error(env, CPXERR_BAD_CTYPE, j);
               goto done;
            }
         }
         if (colname != NULL)
         {  if (colname[j] == NULL)
            {  errcode = error(env, CPXERR_NULL_NAME, j);
               goto done;
            }
         }
      }
      errcode = 0;
      invalidate(lp);
      n = glp_get_num_cols(lp->prob);
      if (ccnt > 0)
         glp_add_cols(lp->prob, ccnt);
      for (j = 0; j < ccnt; j++)
      {  if (colname != NULL)
            glp_set_col_name(lp->prob, n+j+1, colname[j]);
         if (obj != NULL)
            glp_set_obj_coef(lp->prob, n+j+1, obj[j]);
         lbnd = (lb == NULL ? 0.0 : lb[j]);
         ubnd = (ub == NULL ? 0.0 : ub[j]);
         if (lbnd <= -CPX_INFBOUND && ubnd >= +CPX_INFBOUND)
            type = GLP_FR;
         else if (ubnd >= +CPX_INFBOUND)
            type = GLP_LO;
         else if (lbnd <= -CPX_INFBOUND)
            type = GLP_UP;
         else if (lbnd != ubnd)
            type = GLP_DB;
         else
            type = GLP_FX;
         glp_set_col_bnds(lp->prob, n+j+1, type, lbnd, ubnd);
         if (ctype != NULL)
         {  if (ctype[j] == 'C')
               kind = GLP_CV;
            else if (ctype[j] == 'B')
               kind = GLP_BV;
            else if (ctype[j] == 'I')
               kind = GLP_IV;
            else
               xassert(ctype != ctype);
            glp_set_col_kind(lp->prob, n+j+1, kind);
         }
      }
done: return errcode;
}

int CPXnewrows(CPXENV *env, CPXLP *lp, int rcnt, const double rhs[],
      const char sense[], const double rngval[], char *rowname[])
{     int i, m, type, errcode;
      double lbnd, ubnd;
      errcode = checklp(env, lp);
      if (errcode) goto done;
      if (rcnt < 0)
      {  errcode = error(env, CPXERR_BAD_ARGUMENT);
         goto done;
      }
      for (i = 0; i < rcnt; i++)
      {  if (sense != NULL)
         {  if (!(sense[i] == 'L' || sense[i] == 'E' ||
                  sense[i] == 'G' || sense[i] == 'R'))
            {  errcode = error(env, CPXERR_BAD_SENSE, i);
               goto done;
            }
         }
         if (rowname != NULL)
         {  if (rowname[i] == NULL)
            {  errcode = error(env, CPXERR_NULL_NAME, i);
               goto done;
            }
         }
      }
      errcode = 0;
      invalidate(lp);
      m = glp_get_num_rows(lp->prob);
      if (rcnt > 0)
         glp_add_rows(lp->prob, rcnt);
      enlargerflag(lp);
      for (i = 0; i < rcnt; i++)
      {  if (rowname != NULL)
            glp_set_row_name(lp->prob, m+i+1, rowname[i]);
         lbnd = ubnd = (rhs == NULL ? 0.0 : rhs[i]);
         if (sense == NULL || sense[i] == 'E')
         {  lp->rflag[m+i] = RF_NOT_RANGED;
            type = GLP_FX;
         }
         else if (sense[i] == 'L')
         {  lp->rflag[m+i] = RF_NOT_RANGED;
            type = GLP_UP;
         }
         else if (sense[i] == 'G')
         {  lp->rflag[m+i] = RF_NOT_RANGED;
            type = GLP_LO;
         }
         else if (sense[i] == 'R')
         {  if (rngval == NULL || rngval[i] == 0.0)
            {  lp->rflag[m+i] = RF_RANGED_POS;
               type = GLP_FX;
            }
            else if (rngval[i] > 0.0)
            {  lp->rflag[m+i] = RF_RANGED_POS;
               type = GLP_DB;
               ubnd += rngval[i];
            }
            else /* rngval[i] < 0.0 */
            {  lp->rflag[m+i] = RF_RANGED_NEG;
               type = GLP_DB;
               lbnd += rngval[i];
            }
         }
         else
            xassert(sense != sense);
         glp_set_row_bnds(lp->prob, m+i+1, type, lbnd, ubnd);
      }
done: return errcode;
}

CPXENV *CPXopenCPLEX(int *status)
{     CPXENV *env;
      int k, card;
      env = xmalloc(sizeof(CPXENV));
      env->list = NULL;
      card = sizeof(intparam) / sizeof(struct intparam);
      env->intparam = xcalloc(card, sizeof(int));
      for (k = 0; k < card; k++)
         env->intparam[k] = intparam[k].defv;
      card = sizeof(dblparam) / sizeof(struct dblparam);
      env->dblparam = xcalloc(card, sizeof(double));
      for (k = 0; k < card; k++)
         env->dblparam[k] = dblparam[k].defv;
      if (status != NULL) *status = 0;
      return env;
}

int CPXpivotin(CPXENV *env, CPXLP *lp, const int rlist[], int rlen)
{     int i, m, errcode;
      errcode = checklp(env, lp);
      if (errcode) goto done;
      if (rlen < 0)
      {  errcode = error(env, CPXERR_BAD_ARGUMENT);
         goto done;
      }
      if (rlen > 0 && rlist == NULL)
      {  errcode = error(env, CPXERR_NULL_POINTER);
         goto done;
      }
      m = glp_get_num_rows(lp->prob);
      for (i = 0; i < rlen; i++)
      {  if (!(0 <= rlist[i] && rlist[i] < m))
         {  errcode = error(env, CPXERR_ROW_INDEX_RANGE, i);
            goto done;
         }
      }
      errcode = 0;
      for (i = 0; i < rlen; i++)
      {  if (glp_get_row_type(lp->prob, rlist[i]+1) != GLP_FX)
         {  if (glp_get_row_stat(lp->prob, rlist[i]+1) != GLP_BS)
            {  /* not implemented yet */
               break;
            }
         }
      }
done: return errcode;
}

int CPXpivotout(CPXENV *env, CPXLP *lp, const int clist[], int clen)
{     int j, n, errcode;
      errcode = checklp(env, lp);
      if (errcode) goto done;
      if (clen < 0)
      {  errcode = error(env, CPXERR_BAD_ARGUMENT);
         goto done;
      }
      if (clen > 0 && clist == NULL)
      {  errcode = error(env, CPXERR_NULL_POINTER);
         goto done;
      }
      n = glp_get_num_cols(lp->prob);
      for (j = 0; j < clen; j++)
      {  if (!(0 <= clist[j] && clist[j] < n))
         {  errcode = error(env, CPXERR_COL_INDEX_RANGE, j);
            goto done;
         }
         if (glp_get_col_type(lp->prob, clist[j]+1) != GLP_FX)
         {  errcode = error(env, CPXERR_NOT_FIXED);
            goto done;
         }
      }
      errcode = 0;
      for (j = 0; j < clen; j++)
      {  if (glp_get_col_stat(lp->prob, clist[j]+1) == GLP_BS)
         {  /* not implemented yet */
            break;
         }
      }
done: return errcode;
}

int CPXprimopt(CPXENV *env, CPXLP *lp);

int CPXsavwrite(CPXENV *env, CPXLP *lp, const char *filename)
{     xassert(env == env);
      xassert(lp == lp);
      xassert(filename == filename);
      xprintf("CPXsavwrite: not implemented yet\n");
      exit(EXIT_FAILURE);
      return -1;
}

int CPXsetdblparam(CPXENV *env, int whichparam, double newvalue)
{     int k, errcode;
      errcode = checkenv(env);
      if (errcode) goto done;
      k = finddblparam(whichparam);
      if (k < 0)
      {  errcode = error(env, CPXERR_BAD_PARAM_NUM);
         goto done;
      }
      if (newvalue < dblparam[k].minv)
      {  errcode = error(env, CPXERR_PARAM_TOO_SMALL);
         goto done;
      }
      if (newvalue > dblparam[k].maxv)
      {  errcode = error(env, CPXERR_PARAM_TOO_BIG);
         goto done;
      }
      errcode = 0;
      env->dblparam[k] = newvalue;
done: return errcode;
}

int CPXsetintparam(CPXENV *env, int whichparam, int newvalue)
{     int k, errcode;
      errcode = checkenv(env);
      if (errcode) goto done;
      k = findintparam(whichparam);
      if (k < 0)
      {  errcode = error(env, CPXERR_BAD_PARAM_NUM);
         goto done;
      }
      if (newvalue < intparam[k].minv)
      {  errcode = error(env, CPXERR_PARAM_TOO_SMALL);
         goto done;
      }
      if (newvalue > intparam[k].maxv)
      {  errcode = error(env, CPXERR_PARAM_TOO_BIG);
         goto done;
      }
      errcode = 0;
      env->intparam[k] = newvalue;
done: return errcode;
}

int CPXsolninfo(CPXENV *env, CPXLP *lp, int *solnmethod, int *solntype,
      int *pfeasind, int *dfeasind)
{     int type, pfeas, dfeas, errcode;
      errcode = checklp(env, lp);
      if (errcode) goto done;
      errcode = 0;
      if (!lp->stat)
         type = CPX_NO_SOLN, pfeas = dfeas = 0;
      else if (lp->meth == CPX_ALG_PRIMAL || lp->meth == CPX_ALG_DUAL)
      {  type = CPX_BASIC_SOLN;
         pfeas = (glp_get_prim_stat(lp->prob) == GLP_FEAS);
         dfeas = (glp_get_dual_stat(lp->prob) == GLP_FEAS);
      }
      else
         xassert(lp != lp);
      if (solnmethod != NULL)
         *solnmethod = lp->meth;
      if (solntype != NULL)
         *solntype = type;
      if (pfeasind != NULL)
         *pfeasind = pfeas;
      if (dfeasind != NULL)
         *dfeasind = dfeas;
done: return errcode;
}

int CPXsolution(CPXENV *env, CPXLP *lp, int *lpstat, double *objval,
      double x[], double pi[], double slack[], double dj[])
{     int m, n, errcode;
      errcode = checklp(env, lp);
      if (errcode) goto done;
      if (!lp->stat)
      {  errcode = error(env, CPXERR_NO_SOLN);
         goto done;
      }
      errcode = 0;
      m = glp_get_num_rows(lp->prob);
      n = glp_get_num_cols(lp->prob);
      if (lp->meth == CPX_ALG_PRIMAL || lp->meth == CPX_ALG_DUAL)
      {  if (lpstat != NULL)
            *lpstat = CPXgetstat(env, lp);
         if (objval != NULL)
            xassert(CPXgetobjval(env, lp, objval) == 0);
         if (x != NULL)
            xassert(CPXgetx(env, lp, x, 0, n-1) == 0);
         if (pi != NULL)
            xassert(CPXgetpi(env, lp, pi, 0, m-1) == 0);
         if (slack != NULL)
            xassert(CPXgetslack(env, lp, slack, 0, m-1) == 0);
         if (dj != NULL)
            xassert(CPXgetdj(env, lp, dj, 0, n-1) == 0);
      }
      else
         xassert(lp != lp);
done: return errcode;
}

int CPXstrongbranch(CPXENV *env, CPXLP *lp, const int goodlist[],
      int goodlen, double downpen[], double uppen[], int itlim)
{     int k;
      xassert(env == env);
      xassert(lp == lp);
      xassert(goodlist == goodlist);
      xassert(goodlen >= 0);
      xassert(downpen != NULL);
      xassert(uppen != NULL);
      xassert(itlim == itlim);
      /* not implemented yet */
      for (k = 0; k < goodlen; k++)
         downpen[k] = uppen[k] = 0.0;
      return 0;
}

static int xstrcasecmp(const char *s1, const char *s2)
{     int c1, c2;
      for (;;)
      {  c1 = toupper((unsigned char)*s1++);
         c2 = toupper((unsigned char)*s2++);
         if (c1 == '\0' || c1 != c2) break;
      }
      return c1 - c2;
}

static void getfiletype(const char *filename, char type[3+1])
{     /* determine filetype from filename */
      int beg, end;
      beg = end = strlen(filename);
      while (beg > 0 && filename[beg-1] != '.' && end - beg < 3)
         beg--;
      if (beg > 0 && filename[beg-1] == '.' &&
          xstrcasecmp(&filename[beg], "gz") == 0)
      {  end = --beg;
         while (beg > 0 && filename[beg-1] != '.' && end - beg < 3)
            beg--;
      }
      if (beg > 0 && filename[beg-1] == '.')
      {  memcpy(type, &filename[beg], end - beg);
         type[end - beg] = '\0';
      }
      else
         type[0] = '\0';
      return;
}

int CPXwriteprob(CPXENV *env, CPXLP *lp, const char *filename,
      const char *filetype)
{     glp_prob *copy;
      int errcode;
      char type[3+1];
      errcode = checklp(env, lp);
      if (errcode) goto done;
      if (filename == NULL)
      {  errcode = error(env, CPXERR_NO_FILENAME);
         goto done;
      }
      if (filetype == NULL)
         getfiletype(filename, type), filetype = type;
      if (xstrcasecmp(filetype, "MPS") == 0)
      {  glp_term_out(GLP_OFF);
         errcode = glp_write_mps(lp->prob, GLP_MPS_FILE, NULL, filename)
            ;
         glp_term_out(GLP_ON);
      }
      else if (xstrcasecmp(filetype, "LP") == 0)
      {  glp_term_out(GLP_OFF);
         errcode = glp_write_lp(lp->prob, NULL, filename);
         glp_term_out(GLP_ON);
      }
      else if (xstrcasecmp(filetype, "RMP") == 0 ||
               xstrcasecmp(filetype, "REW") == 0)
      {  copy = glp_create_prob();
         glp_copy_prob(copy, lp->prob, GLP_OFF);
         glp_term_out(GLP_OFF);
         errcode = glp_write_mps(copy, GLP_MPS_DECK, NULL, filename);
         glp_term_out(GLP_ON);
         glp_delete_prob(copy);
      }
      else if (xstrcasecmp(filetype, "RLP") == 0)
      {  copy = glp_create_prob();
         glp_copy_prob(copy, lp->prob, GLP_OFF);
         glp_term_out(GLP_OFF);
         errcode = glp_write_lp(copy, NULL, filename);
         glp_term_out(GLP_ON);
         glp_delete_prob(copy);
      }
      else
      {  errcode = error(env, CPXERR_BAD_FILETYPE);
         goto done;
      }
      if (errcode)
         errcode = error(env, CPXERR_FAIL_OPEN_WRITE, filename);
done: return errcode;
}

/**********************************************************************/

static int solvelp(CPXENV *env, CPXLP *lp, int meth)
{     glp_smcp parm;
      int errcode;
      errcode = checklp(env, lp);
      if (errcode) goto done;
      errcode = 0;
      invalidate(lp);
      glp_init_smcp(&parm);
      switch (meth)
      {  case CPX_ALG_PRIMAL:
            parm.meth = GLP_PRIMAL;
            break;
         case CPX_ALG_DUAL:
            parm.meth = GLP_DUAL;
            break;
         default:
            xassert(meth != meth);
      }
      switch (getintparam(env, CPX_PARAM_SIMDISPLAY))
      {  case 0:
            parm.msg_lev = GLP_MSG_OFF;
            break;
         case 1:
            parm.msg_lev = GLP_MSG_ALL;
            break;
         case 2:
            parm.msg_lev = GLP_MSG_ALL;
            parm.out_frq = 1;
            break;
         default:
            xassert(env != env);
      }
      xassert(getdblparam == getdblparam);
      switch (getintparam(env, CPX_PARAM_ADVIND))
      {  case 0:
            glp_term_out(GLP_OFF);
            glp_adv_basis(lp->prob, 0);
            glp_term_out(GLP_ON);
            break;
         case 1:
         case 2:
            break;
         default:
            xassert(env != env);
      }
      if (!glp_bf_exists(lp->prob))
      {  if (glp_factorize(lp->prob) != 0)
         {  glp_term_out(GLP_OFF);
            glp_adv_basis(lp->prob, 0);
            glp_term_out(GLP_ON);
            if (glp_factorize(lp->prob) != 0)
               glp_std_basis(lp->prob);
         }
      }
      xassert(glp_simplex(lp->prob, &parm) == 0);
      switch (glp_get_status(lp->prob))
      {  case GLP_OPT:
            lp->stat = CPX_STAT_OPTIMAL;
            lp->meth = meth;
            break;
         case GLP_NOFEAS:
            lp->stat = CPX_STAT_INFEASIBLE;
            lp->meth = meth;
            break;
         case GLP_UNBND:
            lp->stat = CPX_STAT_UNBOUNDED;
            lp->meth = meth;
            break;
         default:
            xassert(lp != lp);
      }
done: return errcode;
}

int CPXprimopt(CPXENV *env, CPXLP *lp)
{     int errcode;
      errcode = solvelp(env, lp, CPX_ALG_PRIMAL);
      return errcode;
}

int CPXdualopt(CPXENV *env, CPXLP *lp)
{     int errcode;
      errcode = solvelp(env, lp, CPX_ALG_DUAL);
      return errcode;
}

int CPXlpopt(CPXENV *env, CPXLP *lp)
{     int errcode;
      errcode = solvelp(env, lp, CPX_ALG_PRIMAL);
      return errcode;
}

/* eof */

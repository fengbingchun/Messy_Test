/* tsplib.c */

/* Written by Andrew Makhorin <mao@gnu.org>, October 2015. */

#include <ctype.h>
#include <errno.h>
#include <float.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "misc.h"
#include "tsplib.h"

/***********************************************************************
*  NAME
*
*  tsp_read_data - read TSP instance data
*
*  SYNOPSIS
*
*  #include "tsplib.h"
*  TSP *tsp_read_data(const char *fname);
*
*  DESCRIPTION
*
*  The routine tsp_read_data reads a TSP (or related problem) instance
*  data from a text file, whose name is the character string fname.
*
*  For detailed description of the format recognized by the routine see
*  the report: G.Reinelt, TSPLIB 95.
*
*  RETURNS
*
*  If no error occurred, the routine tsp_read_data returns a pointer to
*  the TSP instance data block, which contains loaded data. In the case
*  of error the routine prints an error message and returns NULL. */

struct csa
{     /* common storage area used by the routine tsp_read_data */
      const char *fname;
      /* name of the input text file */
      FILE *fp;
      /* stream assigned to the input text file */
      int seqn;
      /* line sequential number */
      int c;
      /* current character */
      char token[255+1];
      /* current token */
};

static int get_char(struct csa *csa)
{     csa->c = fgetc(csa->fp);
      if (ferror(csa->fp))
      {  xprintf("%s:%d: read error - %s\n", csa->fname, csa->seqn,
            strerror(errno));
         return 1;
      }
      if (feof(csa->fp))
         csa->c = EOF;
      else if (csa->c == '\n')
         csa->seqn++;
      else if (isspace(csa->c))
         csa->c = ' ';
      else if (iscntrl(csa->c))
      {  xprintf("%s:%d: invalid control character 0x%02X\n",
            csa->fname, csa->seqn, csa->c);
         return 1;
      }
      return 0;
}

static int skip_spaces(struct csa *csa, int across)
{     while (csa->c == ' ' || (across && csa->c == '\n'))
         if (get_char(csa)) return 1;
      return 0;
}

static int scan_keyword(struct csa *csa)
{     int len = 0;
      if (skip_spaces(csa, 0))
         return 1;
      if (csa->c == EOF)
      {  xprintf("%s:%d: warning: missing EOF inserted\n", csa->fname,
            csa->seqn);
         strcpy(csa->token, "EOF");
         return 0;
      }
      csa->token[0] = '\0';
      while (isalnum(csa->c) || csa->c == '_')
      {  if (len == 31)
         {  xprintf("%s:%d: keyword '%s...' too long\n", csa->fname,
               csa->seqn, csa->token);
            return 1;
         }
         csa->token[len++] = (char)csa->c, csa->token[len] = '\0';
         if (get_char(csa))
            return 1;
      }
      if (len == 0)
      {  xprintf("%s:%d: missing keyword\n", csa->fname, csa->seqn);
         return 1;
      }
      return 0;
}

static int check_colon(struct csa *csa)
{     if (skip_spaces(csa, 0))
         return 1;
      if (csa->c != ':')
      {  xprintf("%s:%d: missing colon after '%s'\n", csa->fname,
            csa->seqn, csa->token);
         return 1;
      }
      if (get_char(csa))
         return 1;
      return 0;
}

static int scan_token(struct csa *csa, int across)
{     int len = 0;
      if (skip_spaces(csa, across))
         return 1;
      csa->token[0] = '\0';
      while (!(csa->c == EOF || csa->c == '\n' || csa->c == ' '))
      {  if (len == 255)
         {  csa->token[31] = '\0';
            xprintf("%s:%d: token '%s...' too long\n", csa->fname,
               csa->seqn, csa->token);
            return 1;
         }
         csa->token[len++] = (char)csa->c, csa->token[len] = '\0';
         if (get_char(csa))
            return 1;
      }
      return 0;
}

static int check_newline(struct csa *csa)
{     if (skip_spaces(csa, 0))
         return 1;
      if (!(csa->c == EOF || csa->c == '\n'))
      {  xprintf("%s:%d: extra symbols detected\n", csa->fname,
            csa->seqn);
         return 1;
      }
      if (get_char(csa))
         return 1;
      return 0;
}

static int scan_comment(struct csa *csa)
{     int len = 0;
      if (skip_spaces(csa, 0))
         return 1;
      csa->token[0] = '\0';
      while (!(csa->c == EOF || csa->c == '\n'))
      {  if (len == 255)
         {  xprintf("%s:%d: comment too long\n", csa->fname, csa->seqn);
            return 1;
         }
         csa->token[len++] = (char)csa->c, csa->token[len] = '\0';
         if (get_char(csa))
            return 1;
      }
      return 0;
}

static int scan_integer(struct csa *csa, int across, int *val)
{     if (scan_token(csa, across))
         return 1;
      if (strlen(csa->token) == 0)
      {  xprintf("%s:%d: missing integer\n", csa->fname, csa->seqn);
         return 1;
      }
      if (str2int(csa->token, val))
      {  xprintf("%s:%d: integer '%s' invalid\n", csa->fname, csa->seqn,
            csa->token);
         return 1;
      }
      return 0;
}

static int scan_number(struct csa *csa, int across, double *val)
{     if (scan_token(csa, across))
         return 1;
      if (strlen(csa->token) == 0)
      {  xprintf("%s:%d: missing number\n", csa->fname, csa->seqn);
         return 1;
      }
      if (str2num(csa->token, val))
      {  xprintf("%s:%d: number '%s' invalid\n", csa->fname, csa->seqn,
            csa->token);
         return 1;
      }
      return 0;
}

TSP *tsp_read_data(const char *fname)
{     struct csa _dsa, *csa = &_dsa;
      TSP *tsp = NULL;
      csa->fname = fname;
      xprintf("Reading TSP data from '%s'...\n", csa->fname);
      csa->fp = fopen(csa->fname, "r");
      if (csa->fp == NULL)
      {  xprintf("Unable to open '%s' - %s\n", csa->fname,
            strerror(errno));
         goto fail;
      }
      tsp = xalloc(1, sizeof(TSP));
      tsp->name = NULL;
      tsp->type = TSP_UNDEF;
      tsp->comment = NULL;
      tsp->dimension = 0;
      tsp->edge_weight_type = TSP_UNDEF;
      tsp->edge_weight_format = TSP_UNDEF;
      tsp->display_data_type = TSP_UNDEF;
      tsp->node_x_coord = NULL;
      tsp->node_y_coord = NULL;
      tsp->dply_x_coord = NULL;
      tsp->dply_y_coord = NULL;
      tsp->tour = NULL;
      tsp->edge_weight = NULL;
      csa->seqn = 1;
      if (get_char(csa))
         goto fail;
loop: if (scan_keyword(csa))
         goto fail;
      if (strcmp(csa->token, "NAME") == 0)
      {  if (tsp->name != NULL)
         {  xprintf("%s:%d: NAME entry multiply defined\n", csa->fname,
               csa->seqn);
            goto fail;
         }
         if (check_colon(csa))
            goto fail;
         if (scan_token(csa, 0))
            goto fail;
         if (strlen(csa->token) == 0)
         {  xprintf("%s:%d: NAME entry incomplete\n", csa->fname,
               csa->seqn);
            goto fail;
         }
         tsp->name = xalloc(strlen(csa->token)+1, sizeof(char));
         strcpy(tsp->name, csa->token);
         xprintf("NAME: %s\n", tsp->name);
         if (check_newline(csa))
            goto fail;
      }
      else if (strcmp(csa->token, "TYPE") == 0)
      {  if (tsp->type != TSP_UNDEF)
         {  xprintf("%s:%d: TYPE entry multiply defined\n", csa->fname,
               csa->seqn);
            goto fail;
         }
         if (check_colon(csa))
            goto fail;
         if (scan_keyword(csa))
            goto fail;
         if (strcmp(csa->token, "TSP") == 0)
            tsp->type = TSP_TSP;
         else if (strcmp(csa->token, "ATSP") == 0)
            tsp->type = TSP_ATSP;
         else if (strcmp(csa->token, "TOUR") == 0)
            tsp->type = TSP_TOUR;
         else
         {  xprintf("%s:%d: data type '%s' not recognized\n",
               csa->fname, csa->seqn, csa->token);
            goto fail;
         }
         xprintf("TYPE: %s\n", csa->token);
         if (check_newline(csa))
            goto fail;
      }
      else if (strcmp(csa->token, "COMMENT") == 0)
      {  if (check_colon(csa))
            goto fail;
         if (scan_comment(csa))
            goto fail;
         xprintf("COMMENT: %s\n", csa->token);
         if (tsp->comment == NULL)
         {  tsp->comment = xalloc(strlen(csa->token)+1, sizeof(char));
            strcpy(tsp->comment, csa->token);
         }
         else
         {  xprintf("%s:%d: warning: extra COMMENT entry ignored\n",
               csa->fname, csa->seqn);
         }
         if (check_newline(csa))
            goto fail;
      }
      else if (strcmp(csa->token, "DIMENSION") == 0)
      {  if (tsp->dimension != 0)
         {  xprintf("%s:%d: DIMENSION entry multiply defined\n",
               csa->fname, csa->seqn);
            goto fail;
         }
         if (check_colon(csa))
            goto fail;
         if (scan_integer(csa, 0, &tsp->dimension))
            goto fail;
         if (tsp->dimension < 1)
         {  xprintf("%s:%d: invalid dimension\n", csa->fname,
               csa->seqn);
            goto fail;
         }
         xprintf("DIMENSION: %d\n", tsp->dimension);
         if (check_newline(csa))
            goto fail;
      }
      else if (strcmp(csa->token, "EDGE_WEIGHT_TYPE") == 0)
      {  if (tsp->edge_weight_type != TSP_UNDEF)
         {  xprintf("%s:%d: EDGE_WEIGHT_TYPE entry multiply defined\n",
               csa->fname, csa->seqn);
            goto fail;
         }
         if (check_colon(csa))
            goto fail;
         if (scan_keyword(csa))
            goto fail;
         if (strcmp(csa->token, "GEO") == 0)
            tsp->edge_weight_type = TSP_GEO;
         else if (strcmp(csa->token, "EUC_2D") == 0)
            tsp->edge_weight_type = TSP_EUC_2D;
         else if (strcmp(csa->token, "ATT") == 0)
            tsp->edge_weight_type = TSP_ATT;
         else if (strcmp(csa->token, "EXPLICIT") == 0)
            tsp->edge_weight_type = TSP_EXPLICIT;
         else if (strcmp(csa->token, "CEIL_2D") == 0)
            tsp->edge_weight_type = TSP_CEIL_2D;
         else
         {  xprintf("%s:%d: edge weight type '%s' not recognized\n",
               csa->fname, csa->seqn, csa->token);
            goto fail;
         }
         xprintf("EDGE_WEIGHT_TYPE: %s\n", csa->token);
         if (check_newline(csa))
            goto fail;
      }
      else if (strcmp(csa->token, "EDGE_WEIGHT_FORMAT") == 0)
      {  if (tsp->edge_weight_format != TSP_UNDEF)
         {  xprintf("%s:%d: EDGE_WEIGHT_FORMAT entry multiply defined\n"
               , csa->fname, csa->seqn);
            goto fail;
         }
         if (check_colon(csa))
            goto fail;
         if (scan_keyword(csa))
            goto fail;
         if (strcmp(csa->token, "UPPER_ROW") == 0)
            tsp->edge_weight_format = TSP_UPPER_ROW;
         else if (strcmp(csa->token, "FULL_MATRIX") == 0)
            tsp->edge_weight_format = TSP_FULL_MATRIX;
         else if (strcmp(csa->token, "FUNCTION") == 0)
            tsp->edge_weight_format = TSP_FUNCTION;
         else if (strcmp(csa->token, "LOWER_DIAG_ROW") == 0)
            tsp->edge_weight_format = TSP_LOWER_DIAG_ROW;
         else
         {  xprintf("%s:%d: edge weight format '%s' not recognized\n",
               csa->fname, csa->seqn, csa->token);
            goto fail;
         }
         xprintf("EDGE_WEIGHT_FORMAT: %s\n", csa->token);
         if (check_newline(csa))
            goto fail;
      }
      else if (strcmp(csa->token, "DISPLAY_DATA_TYPE") == 0)
      {  if (tsp->display_data_type != TSP_UNDEF)
         {  xprintf("%s:%d: DISPLAY_DATA_TYPE entry multiply defined\n",
               csa->fname, csa->seqn);
            goto fail;
         }
         if (check_colon(csa))
            goto fail;
         if (scan_keyword(csa))
            goto fail;
         if (strcmp(csa->token, "COORD_DISPLAY") == 0)
            tsp->display_data_type = TSP_COORD_DISPLAY;
         else if (strcmp(csa->token, "TWOD_DISPLAY") == 0)
            tsp->display_data_type = TSP_TWOD_DISPLAY;
         else
         {  xprintf("%s:%d: display data type '%s' not recognized\n",
               csa->fname, csa->seqn, csa->token);
            goto fail;
         }
         xprintf("DISPLAY_DATA_TYPE: %s\n", csa->token);
         if (check_newline(csa))
            goto fail;
      }
      else if (strcmp(csa->token, "NODE_COORD_SECTION") == 0)
      {  int n = tsp->dimension, k, node;
         if (n == 0)
         {  xprintf("%s:%d: DIMENSION entry not specified\n",
               csa->fname, csa->seqn);
            goto fail;
         }
         if (tsp->node_x_coord != NULL)
         {  xprintf("%s:%d: NODE_COORD_SECTION multiply specified\n",
               csa->fname, csa->seqn);
            goto fail;
         }
         if (check_newline(csa))
            goto fail;
         tsp->node_x_coord = xalloc(1+n, sizeof(double));
         tsp->node_y_coord = xalloc(1+n, sizeof(double));
         for (node = 1; node <= n; node++)
            tsp->node_x_coord[node] = tsp->node_y_coord[node] = DBL_MAX;
         for (k = 1; k <= n; k++)
         {  if (scan_integer(csa, 0, &node))
               goto fail;
            if (!(1 <= node && node <= n))
            {  xprintf("%s:%d: invalid node number %d\n", csa->fname,
                  csa->seqn, node);
               goto fail;
            }
            if (tsp->node_x_coord[node] != DBL_MAX)
            {  xprintf("%s:%d: node number %d multiply specified\n",
                  csa->fname, csa->seqn, node);
               goto fail;
            }
            if (scan_number(csa, 0, &tsp->node_x_coord[node]))
               goto fail;
            if (scan_number(csa, 0, &tsp->node_y_coord[node]))
               goto fail;
            if (check_newline(csa))
               goto fail;
         }
      }
      else if (strcmp(csa->token, "DISPLAY_DATA_SECTION") == 0)
      {  int n = tsp->dimension, k, node;
         if (n == 0)
         {  xprintf("%s:%d: DIMENSION entry not specified\n",
               csa->fname, csa->seqn);
            goto fail;
         }
         if (tsp->dply_x_coord != NULL)
         {  xprintf("%s:%d: DISPLAY_DATA_SECTION multiply specified\n",
               csa->fname, csa->seqn);
            goto fail;
         }
         if (check_newline(csa))
            goto fail;
         tsp->dply_x_coord = xalloc(1+n, sizeof(double));
         tsp->dply_y_coord = xalloc(1+n, sizeof(double));
         for (node = 1; node <= n; node++)
            tsp->dply_x_coord[node] = tsp->dply_y_coord[node] = DBL_MAX;
         for (k = 1; k <= n; k++)
         {  if (scan_integer(csa, 0, &node))
               goto fail;
            if (!(1 <= node && node <= n))
            {  xprintf("%s:%d: invalid node number %d\n", csa->fname,
                  csa->seqn, node);
               goto fail;
            }
            if (tsp->dply_x_coord[node] != DBL_MAX)
            {  xprintf("%s:%d: node number %d multiply specified\n",
                  csa->fname, csa->seqn, node);
               goto fail;
            }
            if (scan_number(csa, 0, &tsp->dply_x_coord[node]))
               goto fail;
            if (scan_number(csa, 0, &tsp->dply_y_coord[node]))
               goto fail;
            if (check_newline(csa))
               goto fail;
         }
      }
      else if (strcmp(csa->token, "TOUR_SECTION") == 0)
      {  int n = tsp->dimension, k, node;
         if (n == 0)
         {  xprintf("%s:%d: DIMENSION entry not specified\n",
               csa->fname, csa->seqn);
            goto fail;
         }
         if (tsp->tour != NULL)
         {  xprintf("%s:%d: TOUR_SECTION multiply specified\n",
               csa->fname, csa->seqn);
            goto fail;
         }
         if (check_newline(csa))
            goto fail;
         tsp->tour = xalloc(1+n, sizeof(int));
         for (k = 1; k <= n; k++)
         {  if (scan_integer(csa, 1, &node))
               goto fail;
            if (!(1 <= node && node <= n))
            {  xprintf("%s:%d: invalid node number %d\n", csa->fname,
                  csa->seqn, node);
               goto fail;
            }
            tsp->tour[k] = node;
         }
         if (scan_integer(csa, 1, &node))
            goto fail;
         if (node != -1)
         {  xprintf("%s:%d: extra node(s) detected\n", csa->fname,
               csa->seqn);
            goto fail;
         }
         if (check_newline(csa))
            goto fail;
      }
      else if (strcmp(csa->token, "EDGE_WEIGHT_SECTION") == 0)
      {  int n = tsp->dimension, i, j, temp;
         if (n == 0)
         {  xprintf("%s:%d: DIMENSION entry not specified\n",
               csa->fname, csa->seqn);
            goto fail;
         }
         if (tsp->edge_weight_format == TSP_UNDEF)
         {  xprintf("%s:%d: EDGE_WEIGHT_FORMAT entry not specified\n",
               csa->fname, csa->seqn);
            goto fail;
         }
         if (tsp->edge_weight != NULL)
         {  xprintf("%s:%d: EDGE_WEIGHT_SECTION multiply specified\n",
               csa->fname, csa->seqn);
            goto fail;
         }
         if (check_newline(csa))
            goto fail;
         tsp->edge_weight = xalloc(1+n*n, sizeof(int));
         switch (tsp->edge_weight_format)
         {  case TSP_FULL_MATRIX:
               for (i = 1; i <= n; i++)
               {  for (j = 1; j <= n; j++)
                  {  if (scan_integer(csa, 1, &temp))
                        goto fail;
                     tsp->edge_weight[(i - 1) * n + j] = temp;
                  }
               }
               break;
            case TSP_UPPER_ROW:
               for (i = 1; i <= n; i++)
               {  tsp->edge_weight[(i - 1) * n + i] = 0;
                  for (j = i + 1; j <= n; j++)
                  {  if (scan_integer(csa, 1, &temp))
                        goto fail;
                     tsp->edge_weight[(i - 1) * n + j] = temp;
                     tsp->edge_weight[(j - 1) * n + i] = temp;
                  }
               }
               break;
            case TSP_LOWER_DIAG_ROW:
               for (i = 1; i <= n; i++)
               {  for (j = 1; j <= i; j++)
                  {  if (scan_integer(csa, 1, &temp))
                        goto fail;
                     tsp->edge_weight[(i - 1) * n + j] = temp;
                     tsp->edge_weight[(j - 1) * n + i] = temp;
                  }
               }
               break;
            default:
               goto fail;
         }
         if (check_newline(csa))
            goto fail;
      }
      else if (strcmp(csa->token, "EOF") == 0)
      {  if (check_newline(csa))
            goto fail;
         goto done;
      }
      else
      {  xprintf("%s:%d: keyword '%s' not recognized\n", csa->fname,
            csa->seqn, csa->token);
         goto fail;
      }
      goto loop;
done: xprintf("%d lines were read\n", csa->seqn-1);
      fclose(csa->fp);
      return tsp;
fail: if (tsp != NULL)
      {  if (tsp->name != NULL)
            xfree(tsp->name);
         if (tsp->comment != NULL)
            xfree(tsp->comment);
         if (tsp->node_x_coord != NULL)
            xfree(tsp->node_x_coord);
         if (tsp->node_y_coord != NULL)
            xfree(tsp->node_y_coord);
         if (tsp->dply_x_coord != NULL)
            xfree(tsp->dply_x_coord);
         if (tsp->dply_y_coord != NULL)
            xfree(tsp->dply_y_coord);
         if (tsp->tour != NULL)
            xfree(tsp->tour);
         if (tsp->edge_weight != NULL)
            xfree(tsp->edge_weight);
         xfree(tsp);
      }
      if (csa->fp != NULL)
         fclose(csa->fp);
      return NULL;
}

/***********************************************************************
*  NAME
*
*  tsp_distance - compute distance between two nodes
*
*  SYNOPSIS
*
*  #include "tsplib.h"
*  int tsp_distance(TSP *tsp, int i, int j);
*
*  DESCRIPTION
*
*  The routine tsp_distance computes the distance between i-th and j-th
*  nodes for the TSP instance, which tsp points to.
*
*  RETURNS
*
*  The routine tsp_distance returns the computed distance. */

#define nint(x) ((int)((x) + 0.5))

static double rad(double x)
{     /* convert input coordinate to longitude/latitude, in radians */
      double pi = 3.141592, deg, min;
      deg = (int)x;
      min = x - deg;
      return pi * (deg + 5.0 * min / 3.0) / 180.0;
}

int tsp_distance(const TSP *tsp, int i, int j)
{     int n = tsp->dimension, dij;
      if (!(tsp->type == TSP_TSP || tsp->type == TSP_ATSP))
         xerror("tsp_distance: invalid TSP instance\n");
      if (!(1 <= i && i <= n && 1 <= j && j <= n))
         xerror("tsp_distance: node number out of range\n");
      switch (tsp->edge_weight_type)
      {  case TSP_UNDEF:
            xerror("tsp_distance: edge weight type not specified\n");
         case TSP_EXPLICIT:
            if (tsp->edge_weight == NULL)
               xerror("tsp_distance: edge weights not specified\n");
            dij = tsp->edge_weight[(i - 1) * n + j];
            break;
         case TSP_EUC_2D:
            if (tsp->node_x_coord == NULL || tsp->node_y_coord == NULL)
               xerror("tsp_distance: node coordinates not specified\n");
            {  double xd, yd;
               xd = tsp->node_x_coord[i] - tsp->node_x_coord[j];
               yd = tsp->node_y_coord[i] - tsp->node_y_coord[j];
               dij = nint(sqrt(xd * xd + yd * yd));
            }
            break;
         case TSP_CEIL_2D:
            if (tsp->node_x_coord == NULL || tsp->node_y_coord == NULL)
               xerror("tsp_distance: node coordinates not specified\n");
            {  double xd, yd;
               xd = tsp->node_x_coord[i] - tsp->node_x_coord[j];
               yd = tsp->node_y_coord[i] - tsp->node_y_coord[j];
               dij = (int)ceil(sqrt(xd * xd + yd * yd));
            }
            break;
         case TSP_GEO:
            if (tsp->node_x_coord == NULL || tsp->node_y_coord == NULL)
               xerror("tsp_distance: node coordinates not specified\n");
            {  double rrr = 6378.388;
               double latitude_i = rad(tsp->node_x_coord[i]);
               double latitude_j = rad(tsp->node_x_coord[j]);
               double longitude_i = rad(tsp->node_y_coord[i]);
               double longitude_j = rad(tsp->node_y_coord[j]);
               double q1 = cos(longitude_i - longitude_j);
               double q2 = cos(latitude_i - latitude_j);
               double q3 = cos(latitude_i + latitude_j);
               dij = (int)(rrr * acos(0.5 * ((1.0 + q1) * q2 -
                  (1.0 - q1) *q3)) + 1.0);
            }
            break;
         case TSP_ATT:
            if (tsp->node_x_coord == NULL || tsp->node_y_coord == NULL)
               xerror("tsp_distance: node coordinates not specified\n");
            {  int tij;
               double xd, yd, rij;
               xd = tsp->node_x_coord[i] - tsp->node_x_coord[j];
               yd = tsp->node_y_coord[i] - tsp->node_y_coord[j];
               rij = sqrt((xd * xd + yd * yd) / 10.0);
               tij = nint(rij);
               if (tij < rij) dij = tij + 1; else dij = tij;
            }
            break;
         default:
            xassert(tsp->edge_weight_type != tsp->edge_weight_type);
      }
      return dij;
}

/***********************************************************************
*  NAME
*
*  tsp_free_data - free TSP instance data
*
*  SYNOPSIS
*
*  #include "tsplib.h"
*  void tsp_free_data(TSP *tsp);
*
*  DESCRIPTION
*
*  The routine tsp_free_data frees all the memory allocated to the TSP
*  instance data block, which the parameter tsp points to. */

void tsp_free_data(TSP *tsp)
{     if (tsp->name != NULL)
         xfree(tsp->name);
      if (tsp->comment != NULL)
         xfree(tsp->comment);
      if (tsp->node_x_coord != NULL)
         xfree(tsp->node_x_coord);
      if (tsp->node_y_coord != NULL)
         xfree(tsp->node_y_coord);
      if (tsp->dply_x_coord != NULL)
         xfree(tsp->dply_x_coord);
      if (tsp->dply_y_coord != NULL)
         xfree(tsp->dply_y_coord);
      if (tsp->tour != NULL)
         xfree(tsp->tour);
      if (tsp->edge_weight != NULL)
         xfree(tsp->edge_weight);
      xfree(tsp);
      return;
}

/* eof */

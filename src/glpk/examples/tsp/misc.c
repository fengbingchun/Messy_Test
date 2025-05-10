/* misc.c */

/* Written by Andrew Makhorin <mao@gnu.org>, October 2015. */

#include <ctype.h>
#include <float.h>
#include <limits.h>
#include <stdlib.h>
#include "misc.h"

/***********************************************************************
*  NAME
*
*  str2int - convert character string to value of int type
*
*  SYNOPSIS
*
*  #include "misc.h"
*  int str2int(const char *str, int *val);
*
*  DESCRIPTION
*
*  The routine str2int converts the character string str to a value of
*  integer type and stores the value into location, which the parameter
*  val points to (in the case of error content of this location is not
*  changed).
*
*  RETURNS
*
*  The routine returns one of the following error codes:
*
*  0 - no error;
*  1 - value out of range;
*  2 - character string is syntactically incorrect. */

int str2int(const char *str, int *val_)
{     int d, k, s, val = 0;
      /* scan optional sign */
      if (str[0] == '+')
         s = +1, k = 1;
      else if (str[0] == '-')
         s = -1, k = 1;
      else
         s = +1, k = 0;
      /* check for the first digit */
      if (!isdigit((unsigned char)str[k]))
         return 2;
      /* scan digits */
      while (isdigit((unsigned char)str[k]))
      {  d = str[k++] - '0';
         if (s > 0)
         {  if (val > INT_MAX / 10)
               return 1;
            val *= 10;
            if (val > INT_MAX - d)
               return 1;
            val += d;
         }
         else /* s < 0 */
         {  if (val < INT_MIN / 10)
               return 1;
            val *= 10;
            if (val < INT_MIN + d)
               return 1;
            val -= d;
         }
      }
      /* check for terminator */
      if (str[k] != '\0')
         return 2;
      /* conversion has been done */
      *val_ = val;
      return 0;
}

/***********************************************************************
*  NAME
*
*  str2num - convert character string to value of double type
*
*  SYNOPSIS
*
*  #include "misc.h"
*  int str2num(const char *str, double *val);
*
*  DESCRIPTION
*
*  The routine str2num converts the character string str to a value of
*  double type and stores the value into location, which the parameter
*  val points to (in the case of error content of this location is not
*  changed).
*
*  RETURNS
*
*  The routine returns one of the following error codes:
*
*  0 - no error;
*  1 - value out of range;
*  2 - character string is syntactically incorrect. */

int str2num(const char *str, double *val_)
{     int k;
      double val;
      /* scan optional sign */
      k = (str[0] == '+' || str[0] == '-' ? 1 : 0);
      /* check for decimal point */
      if (str[k] == '.')
      {  k++;
         /* a digit should follow it */
         if (!isdigit((unsigned char)str[k]))
            return 2;
         k++;
         goto frac;
      }
      /* integer part should start with a digit */
      if (!isdigit((unsigned char)str[k]))
         return 2;
      /* scan integer part */
      while (isdigit((unsigned char)str[k]))
         k++;
      /* check for decimal point */
      if (str[k] == '.') k++;
frac: /* scan optional fraction part */
      while (isdigit((unsigned char)str[k]))
         k++;
      /* check for decimal exponent */
      if (str[k] == 'E' || str[k] == 'e')
      {  k++;
         /* scan optional sign */
         if (str[k] == '+' || str[k] == '-')
            k++;
         /* a digit should follow E, E+ or E- */
         if (!isdigit((unsigned char)str[k]))
            return 2;
      }
      /* scan optional exponent part */
      while (isdigit((unsigned char)str[k]))
         k++;
      /* check for terminator */
      if (str[k] != '\0')
         return 2;
      /* perform conversion */
      {  char *endptr;
         val = strtod(str, &endptr);
         if (*endptr != '\0')
            return 2;
      }
      /* check for overflow */
      if (!(-DBL_MAX <= val && val <= +DBL_MAX))
         return 1;
      /* check for underflow */
      if (-DBL_MIN < val && val < +DBL_MIN)
         val = 0.0;
      /* conversion has been done */
      *val_ = val;
      return 0;
}

/* eof */

/* misc.h */

/* Written by Andrew Makhorin <mao@gnu.org>, October 2015. */

#ifndef MISC_H
#define MISC_H

#include <glpk.h>

#define xprintf glp_printf
#define xerror  glp_error
#define xassert glp_assert
#define xalloc  glp_alloc
#define xfree   glp_free

int str2int(const char *str, int *val);
/* convert character string to value of int type */

int str2num(const char *str, double *val);
/* convert character string to value of double type */

#endif

/* eof */

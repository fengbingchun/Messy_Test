/* lpxsamp.c */

#include <stdio.h>
#include <stdlib.h>
#include "lpx.h"

int main(void)
{     LPX *lp;
      int ia[1+1000], ja[1+1000];
      double ar[1+1000], Z, x1, x2, x3;
s1:   lp = lpx_create_prob();
s2:   lpx_set_prob_name(lp, "sample");
s3:   lpx_set_obj_dir(lp, LPX_MAX);
s4:   lpx_add_rows(lp, 3);
s5:   lpx_set_row_name(lp, 1, "p");
s6:   lpx_set_row_bnds(lp, 1, LPX_UP, 0.0, 100.0);
s7:   lpx_set_row_name(lp, 2, "q");
s8:   lpx_set_row_bnds(lp, 2, LPX_UP, 0.0, 600.0);
s9:   lpx_set_row_name(lp, 3, "r");
s10:  lpx_set_row_bnds(lp, 3, LPX_UP, 0.0, 300.0);
s11:  lpx_add_cols(lp, 3);
s12:  lpx_set_col_name(lp, 1, "x1");
s13:  lpx_set_col_bnds(lp, 1, LPX_LO, 0.0, 0.0);
s14:  lpx_set_obj_coef(lp, 1, 10.0);
s15:  lpx_set_col_name(lp, 2, "x2");
s16:  lpx_set_col_bnds(lp, 2, LPX_LO, 0.0, 0.0);
s17:  lpx_set_obj_coef(lp, 2, 6.0);
s18:  lpx_set_col_name(lp, 3, "x3");
s19:  lpx_set_col_bnds(lp, 3, LPX_LO, 0.0, 0.0);
s20:  lpx_set_obj_coef(lp, 3, 4.0);
s21:  ia[1] = 1, ja[1] = 1, ar[1] =  1.0; /* a[1,1] =  1 */
s22:  ia[2] = 1, ja[2] = 2, ar[2] =  1.0; /* a[1,2] =  1 */
s23:  ia[3] = 1, ja[3] = 3, ar[3] =  1.0; /* a[1,3] =  1 */
s24:  ia[4] = 2, ja[4] = 1, ar[4] = 10.0; /* a[2,1] = 10 */
s25:  ia[5] = 3, ja[5] = 1, ar[5] =  2.0; /* a[3,1] =  2 */
s26:  ia[6] = 2, ja[6] = 2, ar[6] =  4.0; /* a[2,2] =  4 */
s27:  ia[7] = 3, ja[7] = 2, ar[7] =  2.0; /* a[3,2] =  2 */
s28:  ia[8] = 2, ja[8] = 3, ar[8] =  5.0; /* a[2,3] =  5 */
s29:  ia[9] = 3, ja[9] = 3, ar[9] =  6.0; /* a[3,3] =  6 */
s30:  lpx_load_matrix(lp, 9, ia, ja, ar);
s31:  lpx_simplex(lp);
s32:  Z = lpx_get_obj_val(lp);
s33:  x1 = lpx_get_col_prim(lp, 1);
s34:  x2 = lpx_get_col_prim(lp, 2);
s35:  x3 = lpx_get_col_prim(lp, 3);
s36:  printf("\nZ = %g; x1 = %g; x2 = %g; x3 = %g\n", Z, x1, x2, x3);
s37:  lpx_delete_prob(lp);
      return 0;
}

/* eof */

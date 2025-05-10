/* mplsamp2.c */

#include <stdio.h>
#include <stdlib.h>
#include <glpk.h>

int main(void)
{     glp_prob *mip;
      glp_tran *tran;
      int ret;
      mip = glp_create_prob();
      tran = glp_mpl_alloc_wksp();
      ret = glp_mpl_read_model(tran, "sudoku.mod", 1);
      if (ret != 0)
      {  fprintf(stderr, "Error on translating model\n");
         goto skip;
      }
      ret = glp_mpl_read_data(tran, "sudoku.dat");
      if (ret != 0)
      {  fprintf(stderr, "Error on translating data\n");
         goto skip;
      }
      ret = glp_mpl_generate(tran, NULL);
      if (ret != 0)
      {  fprintf(stderr, "Error on generating model\n");
         goto skip;
      }
      glp_mpl_build_prob(tran, mip);
      glp_simplex(mip, NULL);
      glp_intopt(mip, NULL);
      ret = glp_mpl_postsolve(tran, mip, GLP_MIP);
      if (ret != 0)
         fprintf(stderr, "Error on postsolving model\n");
skip: glp_mpl_free_wksp(tran);
      glp_delete_prob(mip);
      return 0;
}

/* eof */

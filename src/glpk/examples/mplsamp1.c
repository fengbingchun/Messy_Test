/* mplsamp1.c */

#include <stdio.h>
#include <stdlib.h>
#include <glpk.h>

int main(void)
{     glp_prob *lp;
      glp_tran *tran;
      int ret;
      lp = glp_create_prob();
      tran = glp_mpl_alloc_wksp();
      ret = glp_mpl_read_model(tran, "egypt.mod", 0);
      if (ret != 0)
      {  fprintf(stderr, "Error on translating model\n");
         goto skip;
      }
      ret = glp_mpl_generate(tran, NULL);
      if (ret != 0)
      {  fprintf(stderr, "Error on generating model\n");
         goto skip;
      }
      glp_mpl_build_prob(tran, lp);
      ret = glp_write_mps(lp, GLP_MPS_FILE, NULL, "egypt.mps");
      if (ret != 0)
         fprintf(stderr, "Error on writing MPS file\n");
skip: glp_mpl_free_wksp(tran);
      glp_delete_prob(lp);
      return 0;
}

/* eof */

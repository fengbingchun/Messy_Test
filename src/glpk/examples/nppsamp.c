/* nppsamp.c */

#include <stdio.h>
#include <stdlib.h>
#include <glpk.h>

int main(void)
{     glp_prep *prep;
      glp_prob *P, *Q;
      int ret;
      prep = glp_npp_alloc_wksp();
      P = glp_create_prob();
      ret = glp_read_mps(P, GLP_MPS_DECK, NULL, "murtagh.mps");
      if (ret != 0)
      {  printf("Error on reading problem data\n");
         goto skip;
      }
      glp_set_obj_dir(P, GLP_MAX);
      glp_npp_load_prob(prep, P, GLP_SOL, GLP_ON);
      ret = glp_npp_preprocess1(prep, 0);
      switch (ret)
      {  case 0:
            break;
         case GLP_ENOPFS:
            printf("LP has no primal feasible solution\n");
            goto skip;
         case GLP_ENODFS:
            printf("LP has no dual feasible solution\n");
            goto skip;
         default:
            glp_assert(ret != ret);
      }
      Q = glp_create_prob();
      glp_npp_build_prob(prep, Q);
      ret = glp_simplex(Q, NULL);
      if (ret == 0 && glp_get_status(Q) == GLP_OPT)
      {  glp_npp_postprocess(prep, Q);
         glp_npp_obtain_sol(prep, P);
      }
      else
         printf("Unable to recover non-optimal solution\n");
      glp_delete_prob(Q);
skip: glp_npp_free_wksp(prep);
      glp_delete_prob(P);
      return 0;
}

/* eof */

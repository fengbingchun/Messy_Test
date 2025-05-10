/* spxsamp2.c */

#include <stdio.h>
#include <stdlib.h>
#include <glpk.h>

int main(void)
{     glp_prob *P;
      glp_smcp parm;
      P = glp_create_prob();
      glp_read_mps(P, GLP_MPS_DECK, NULL, "25fv47.mps");
      glp_init_smcp(&parm);
      parm.meth = GLP_DUAL;
      glp_simplex(P, &parm);
      glp_print_sol(P, "25fv47.txt");
      glp_delete_prob(P);
      return 0;
}

/* eof */

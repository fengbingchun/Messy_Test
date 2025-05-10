/* iptsamp.c */

#include <stdio.h>
#include <stdlib.h>
#include <glpk.h>

int main(void)
{     glp_prob *P;
      P = glp_create_prob();
      glp_read_mps(P, GLP_MPS_DECK, NULL, "25fv47.mps");
      glp_interior(P, NULL);
      glp_print_ipt(P, "25fv47.txt");
      glp_delete_prob(P);
      return 0;
}

/* eof */

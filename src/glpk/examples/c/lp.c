/**
 * @file lp.c
 * @author Heinrich Schuchardt <xypron.glpk@gmx.de>
 *
 * This example demonstrates how to solve a linear
 * programming problem using the GLPK library.
 */

#include <setjmp.h>
#include <stdlib.h>
#include <stdio.h>
#include "glpk.h"

/**
 * Processes error occuring when calling the glpk library.
 *
 * @param in pointer to long jump environment
 */
void hook(void *in) 
{
  /* free GLPK memory */
  glp_free_env();
  /* safely return */
  longjmp(*((jmp_buf*)in), 1);
}

/**
 * Writes simplex solution.
 *
 * @param lp problem
 */
void write_lp_solution (glp_prob *lp)
{
  int i;
  int n;
  const char *name;
  double val;

  name = glp_get_obj_name(lp);
  val = glp_get_obj_val(lp);
  printf ("%s", name);
  printf (" = ");
  printf("%5.3f\n", val);
  n = glp_get_num_cols (lp);
  for (i = 1; i <= n; i++) {
    name = glp_get_col_name(lp, i);
    val = glp_get_col_prim(lp, i);
    printf("%s", name);
    printf(" = ");
    printf("%5.3f\n", val);
  }
}

/**
 * Solves a linear problem.
 *
 * The problem to solve is
 * <pre>
 * var x1, >=0, <= .5;
 * var x2, >=0, <= .5;
 * var x3, >=0, <= .5;
 *
 * minimize z : 1.0  - 0.5 * x1 + 0.5 * x2 - 1.0 * x3       ;
 * s.t. c1    : 0.0 <= 1.0 * x1 - 0.5 * x2            <= 0.2;
 * s.t. c2    :                   1.0 * x2 + 1.0 * x3 <= 0.4;
 * </pre>
 *
 * @param argc number of command line arguments
 * @param argv command line arguments
 */
int main(int argc, char *argv[])
{
  glp_prob *lp;
  glp_smcp parm;
  int *ind;
  double *val;
  int ret;
  jmp_buf env;

  // Set up error hook to safely catch errors occuring
  // in the GLPK librray.
  if (setjmp(env)) {
    fprintf(stderr, "error in GLPK library call\n");
    return EXIT_FAILURE;
  }
  glp_error_hook(hook, env);

  // Create problem object.
  lp = glp_create_prob();

  // Define columns.
  glp_add_cols(lp, 3);
  glp_set_col_name(lp, 1, "x1");
  glp_set_col_kind(lp, 1, GLP_CV);
  glp_set_col_bnds(lp, 1, GLP_DB, 0, .5);
  glp_set_col_name(lp, 2, "x2");
  glp_set_col_kind(lp, 2, GLP_CV);
  glp_set_col_bnds(lp, 2, GLP_DB, 0, .5);
  glp_set_col_name(lp, 3, "x3");
  glp_set_col_kind(lp, 3, GLP_CV);
  glp_set_col_bnds(lp, 3, GLP_DB, 0, .5);

  // Create constraints.

  // Allocate memory.
  ind = calloc(3, sizeof(int));
  val = calloc(3, sizeof(double));

  // Create rows.
  glp_add_rows(lp, 2);

  // Set row details.
  glp_set_row_name(lp, 1, "c1");
  glp_set_row_bnds(lp, 1, GLP_DB, 0, 0.2);
  ind[1] = 1;
  ind[2] = 2;
  val[1] = 1.0;
  val[2] = -.5;
  glp_set_mat_row(lp, 1, 2, ind, val);

  glp_set_row_name(lp, 2, "c2");
  glp_set_row_bnds(lp, 2, GLP_UP, 0, 0.4);
  ind[1] = 2;
  ind[2] = 3;
  val[1] = -1.0;
  val[2] = 1.0;
  glp_set_mat_row(lp, 2, 2, ind, val);

  // Free memory.
  free(ind);
  free(val);

  // Define objective.
  glp_set_obj_name(lp, "z");
  glp_set_obj_dir(lp, GLP_MIN);
  glp_set_obj_coef(lp, 0, 1.0);
  glp_set_obj_coef(lp, 1, -.5);
  glp_set_obj_coef(lp, 2, .5);
  glp_set_obj_coef(lp, 3, -1);

  // Solve model.
  glp_init_smcp(&parm);
  ret = glp_simplex(lp, &parm);

  // Retrieve solution.
  if (ret == 0) {
    write_lp_solution(lp);
  } else {
    printf("The problem could not be solved\n");
    ret = EXIT_FAILURE;
  }

  // Free memory.
  glp_delete_prob(lp);

  return ret;
}

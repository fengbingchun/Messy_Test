/**
 * @file glp_error_hook_demo.c
 *
 * This example file demonstrates how to safely treat errors when
 * calling the glpk library.
 *
 * It creates a problem and alternativly adds 1 or -1 columns.
 * Trying to add -1 columns will cause an error to occur.
 */

#include <stdio.h>
#include <stdlib.h>
#include <setjmp.h>
#include "glpk.h"

void errorHook(void *in);
void buildModel(int forceError);

#define INFO struct sinfo

struct sinfo {
    char    *text;
    jmp_buf env;
};

/**
 * This is the main function.
 */
int main(int argc, char** argv) {
    int i;
    printf("GLPK version: %s\n", glp_version());
    for (i = 1; i < 5; i++) {
        printf ("\nIteration %d", i);
        if (i & 1) {
            printf(", error expected to occur.\n");
        } else {
            printf(", success expected.\n");
        }
        if (runOptimizer(i)) {
            printf("An error has occured.\n");
        } else {
            printf("Successful execution.\n");
        }
    }
    return (EXIT_SUCCESS);
}

/**
 * Calls glpk functions using an error hook.
 * 
 * @param forceError force error if bit 0 = 1
 * @return ok code: 1 failure, 2 out of memory
 */
int runOptimizer(int forceError) {
    int ret = 0;
    INFO *info;
    info = malloc(sizeof(INFO));
    if (info == NULL) {
        return 2;
    }
    info->text = "This information was passed to the hook function.";
    if (setjmp(info->env)) {
        printf("Post treatment of error.\n");
        ret = 1;
    } else {
        glp_error_hook(errorHook, info);
        buildModel(forceError);
    }
    glp_error_hook(NULL, NULL);
    free(info);
    return ret;
}

/**
 * Builds a model with one column.
 *
 * @param forceError force error if bit 0 = 1
 */
void buildModel(int forceError) {
    glp_prob *lp;
    /* create problem */
    lp = glp_create_prob();
    if (forceError & 1) {
        /* add -1 column
         * this will cause an error.
         */
        glp_add_cols(lp, -1);
    } else {
        /* add 1 column */
        glp_add_cols(lp, 1);
    }
    /* delete problem */
    glp_delete_prob(lp);
}

/**
 * Handles error occuring when calling the glpk library.
 */
void errorHook(void *in) {
    INFO *info;
    info = (INFO *) in;
    printf("%s\n",info->text);
    /* free glpk memory */
    glp_free_env();
    /* safely return */
    longjmp(info->env, 1);
}

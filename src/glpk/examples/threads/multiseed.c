/* multiseed.c (multithreading demo) */

/***********************************************************************
*  This code is part of GLPK (GNU Linear Programming Kit).
*
*  Author: Heinrich Schuchardt <xypron.glpk@gmx.de>
*
*  Copyright (C) 2017 Andrew Makhorin, Department for Applied
*  Informatics, Moscow Aviation Institute, Moscow, Russia. All rights
*  reserved. E-mail: <mao@gnu.org>.
*
*  GLPK is free software: you can redistribute it and/or modify it
*  under the terms of the GNU General Public License as published by
*  the Free Software Foundation, either version 3 of the License, or
*  (at your option) any later version.
*
*  GLPK is distributed in the hope that it will be useful, but WITHOUT
*  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
*  or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public
*  License for more details.
*
*  You should have received a copy of the GNU General Public License
*  along with GLPK. If not, see <http://www.gnu.org/licenses/>.
***********************************************************************/

/*
 * This program demonstrates running the GLPK library with multiple threads.
 *
 * When called the program requires two arguments:
 *
 * filename - the name of the MathProg model to be solved
 * threads  - the count of parallel threads to be run.
 *
 * Each thread is run with a different seed for the random number generator
 * provided by the GLPK library.
 */

#include <glpk.h>
#include <malloc.h>
#include <setjmp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "thread.h"

#define BUFLEN 256

/* Task descriptor */
struct task {
   pthread_t tid;
   char *filename;
   int seed;
   size_t pos;
   char buf[BUFLEN + 1];
   int line;
   jmp_buf jmp;
};

/* Mutex for console output */
pthread_mutex_t mutex;

/* Console output handler */
int term_hook(void *info, const char *text)
{
   struct task *task = (struct task *) info;
   size_t len = strlen(text);

   /* Lock mutex so this is the only task creating console output. */
   pthread_mutex_lock(&mutex);

   /* Append the new text to the buffer. */
   if (task->pos + len > BUFLEN) {
      printf("%02d-%05d %s%s", task->seed, ++task->line, task->buf, text);
      task->pos = 0;
      task->buf[0] = 0;
   } else {
      strcpy(task->buf + task->pos, text);
      task->pos += len;
   }

   /* If a complete line is available, send it to the console. */
   if (strchr(task->buf, '\n')) {
      printf("%02d-%05d %s", task->seed, ++task->line, task->buf);
      task->pos = 0;
      task->buf[0] = 0;
   }

   /* Unlock the mutex. */
   pthread_mutex_unlock(&mutex);

   /* Disable default output. */
   return -1;
}

/* Error handler */
void error_hook(void *info)
{
   struct task *task = (struct task *) info;

   term_hook(task, "Error caught\n");
   glp_free_env();
   longjmp(task->jmp, 1);
}

void worker(void *arg)
{
   struct task *task = (struct task *) arg;
   int ret;
   glp_prob *lp;
   glp_tran *tran;
   glp_iocp iocp;

   if (setjmp(task->jmp)) {
      /* If an error is caught leave the function. */
      return;
   }

   /* Set the error handler. */
   glp_error_hook(error_hook, task);

   /* Set the console output handler. */
   glp_term_hook(term_hook, arg);

   glp_printf("Seed %02d\n", task->seed);

   /* Create the problem object. */
   lp = glp_create_prob();
   if (!lp) {
      glp_error("Out of memory\n");
   }

   /* Create the MathProg translator workspace. */
   tran = glp_mpl_alloc_wksp();
   if (!lp) {
      glp_error("Out of memory\n");
   }

   /* Set the pseudo random number generator seed. */
   glp_mpl_init_rand(tran, task->seed);

   /* Read the model file. */
   ret = glp_mpl_read_model (tran, task->filename, GLP_OFF);
   if (ret != 0) {
      glp_error("Model %s is not valid\n", task->filename);
   }

   /* Generate the model. */
   ret = glp_mpl_generate(tran, NULL);
   if (ret != 0) {
      glp_error("Cannot generate model %s\n", task->filename);
   }

   /* Build the problem. */
   glp_mpl_build_prob(tran, lp);

   /* Solve the problem. */
   glp_init_iocp(&iocp);
   iocp.presolve = GLP_ON;
   ret = glp_intopt(lp, &iocp);
   if (ret == 0) {
      /* Execute the post solve part of the model. */
      glp_mpl_postsolve(tran, lp, GLP_MIP);
   }

   /* Release the memory. */
   glp_mpl_free_wksp (tran);
   glp_delete_prob(lp);

   if (0 == task->seed % 3) {
      glp_error("Voluntarily throwing an error in %s at line %d\n",
                __FILE__, __LINE__);
   }

   glp_term_hook(NULL, NULL);

   glp_error_hook(NULL, NULL);

   glp_free_env();
}

#ifdef __WOE__
DWORD run(void *arg)
{
#else
void *run(void *arg)
{
#endif
   worker(arg);
   pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
   int i, n, rc;
   struct task *tasks;

   /* Make sure thread local memory is used by the GLPK library. */
   if (!glp_config("TLS")) {
      printf("The loaded GLPK library does not support thread local memory.\n"
        "You need a version of the library configured with "
	"--enable-reentrant=yes to run this program.\n");
      exit(EXIT_FAILURE);
   }

   /* Check program arguments. */
   if (argc != 3) {
      printf("Usage %s filename threads\n"
             "  filename - MathProg model file\n"
             "  threads  - number of threads\n",
             argv[0]);
      exit(EXIT_FAILURE);
   }

   /* Parse the arguments. */
   n = atoi(argv[2]);
   if (n > 50) {
      printf("Number of threads is to high (> 50).\n");
      exit(EXIT_FAILURE);
   }
   if (n <= 1) {
      printf("Need positive number of threads\n");
      exit(EXIT_FAILURE);
   }

   /* Allocate memory for the task descriptors. */
   tasks = calloc(n, sizeof(struct task));
   if (!tasks) {
      printf("Out of memory");
      exit(EXIT_FAILURE);
   }

   /* Create a mutex for console output. */
   pthread_mutex_init(&mutex, NULL);

   /* Create the threads. */
   for (i = 0; i < n; ++i) {
      tasks[i].filename = argv[1];
      tasks[i].seed = i + 1;
      tasks[i].pos = 0;
      tasks[i].buf[0] = 0;
      tasks[i].line = 0;
      rc = pthread_create(&tasks[i].tid, NULL, run, &tasks[i]);
      if (rc) {
         printf("ERROR; return code from pthread_create() is %d\n", rc);
         exit(EXIT_FAILURE);
      }
   }

   /* Wait for all threads to complete. */
   for (i = 0; i < n; ++i) {
      pthread_join(tasks[i].tid, NULL);
   }

   /* Destroy the mutex. */
   pthread_mutex_destroy(&mutex);

   return EXIT_SUCCESS;
}

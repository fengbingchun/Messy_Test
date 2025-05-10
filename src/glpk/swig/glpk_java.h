/* File glpk_java.h
 * 
 * This file contains definitions that are needed for compiling code explicitly
 * added to GLPK for Java, and which shall be wrapped by Swig.
 */
#ifndef GLPK_JAVA_H
#define GLPK_JAVA_H

#define GLP_JAVA_MSG_LVL_OFF 0
#define GLP_JAVA_MSG_LVL_ALL 1
void glp_java_error(char *message);
void glp_java_set_msg_lvl(int msg_lvl);
void glp_java_set_numeric_locale(const char *locale);

typedef struct {
   double cap;  // arc capacity
   double cost; // arc cost
   double low;  // lower bound
   double rc;   // reduced cost
   double x;    // arc flow
} glp_java_arc_data;

typedef struct  {
   int    cut; // 0: node is unlabeled, 1: node is labeled
   double pi;  // node potential
   double rhs; // supply/demand value
   int    set; // 0: vertex is in set R, 1: vertex is in set S
} glp_java_vertex_data;

glp_java_arc_data *glp_java_arc_get_data(const glp_arc *arc);
glp_java_vertex_data *glp_java_vertex_data_get( const glp_graph *G, const int i);
glp_java_vertex_data *glp_java_vertex_get_data( const glp_vertex *v);
glp_vertex *glp_java_vertex_get( const glp_graph *G, const int i );

struct glp_prob {
    int hidden_internal;
};
struct glp_tran {
    int hidden_internal;
};
struct glp_tree {
    int hidden_internal;
};

#endif // GLPK_JAVA_H

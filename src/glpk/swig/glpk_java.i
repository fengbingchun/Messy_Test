/* File glpk_java.i
 *
 * This file contains definitions that are needed to generate Swig
 * code that is specific for GLPK for Java.
 */

%constant int GLP_JAVA_A_CAP  = offsetof(glp_java_arc_data, cap);
%constant int GLP_JAVA_A_COST = offsetof(glp_java_arc_data, cost);
%constant int GLP_JAVA_A_LOW  = offsetof(glp_java_arc_data, low);
%constant int GLP_JAVA_A_RC   = offsetof(glp_java_arc_data, rc);
%constant int GLP_JAVA_A_X    = offsetof(glp_java_arc_data, x);
%constant int GLP_JAVA_A_SIZE = sizeof(glp_java_arc_data);

%constant int GLP_JAVA_V_CUT  = offsetof(glp_java_vertex_data, cut);
%constant int GLP_JAVA_V_PI   = offsetof(glp_java_vertex_data, pi);
%constant int GLP_JAVA_V_RHS  = offsetof(glp_java_vertex_data, rhs);
%constant int GLP_JAVA_V_SET  = offsetof(glp_java_vertex_data, set);
%constant int GLP_JAVA_V_SIZE = sizeof(glp_java_vertex_data);

%javamethodmodifiers glp_java_arc_get_data(const glp_arc *arc)"
/**
 * Get arc data.
 *
 * @param arc arc
 * @return data
 */
public";

%javamethodmodifiers glp_java_vertex_get(const glp_graph *G, const int i)"
/**
 * Get vertex.
 *
 * @param G graph
 * @param i index
 * @return vertex
 */
public";

%javamethodmodifiers glp_java_vertex_data_get(const glp_graph *G, const int i)"
/**
 * Get vertex data.
 *
 * @param G graph
 * @param i index to vertex
 * @return data
 */
public";

%javamethodmodifiers glp_java_vertex_get_data (const glp_vertex *v)"
/**
 * Get vertex data.
 *
 * @param v vertex
 * @return data
 */
public";

%javamethodmodifiers glp_java_error(char *message)"
/**
 * Abort GLPK library with error message. This method can be used to stop the
 * solver using a GlpkTerminalListener.
 *
 * @param message message
 */
public";

%javamethodmodifiers glp_java_set_msg_lvl(int msg_lvl)"
/**
 * Sets the message level. This method enables and disables debug output of
 * GLPK for Java.
 *
 * @param msg_lvl message level
 *
 * @see GLPKConstants#GLP_JAVA_MSG_LVL_OFF
 * @see GLPKConstants#GLP_JAVA_MSG_LVL_ALL
 */
public";

%javamethodmodifiers glp_java_set_numeric_locale(char *locale)"
/**
 * Sets the locale for number formatting.
 * GLPK requires locale \"C\" for importing model files. Use the following code
 * to set the locale.
 * <pre>
 * GLPK.glp_java_set_numeric_locale(\"C\");
 * </pre>
 *
 * @param locale locale
 */
public";

%include "glpk_java.h"

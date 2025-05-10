/* File glpk_cli.i
 *
 * This file contains definitions that are needed to generate Swig
 * code that is specific for GLPK for CLI.
 */

%constant int GLP_CLI_A_CAP  = offsetof(glp_cli_arc_data, cap);
%constant int GLP_CLI_A_COST = offsetof(glp_cli_arc_data, cost);
%constant int GLP_CLI_A_LOW  = offsetof(glp_cli_arc_data, low);
%constant int GLP_CLI_A_RC   = offsetof(glp_cli_arc_data, rc);
%constant int GLP_CLI_A_X    = offsetof(glp_cli_arc_data, x);
%constant int GLP_CLI_A_SIZE = sizeof(glp_cli_arc_data);

%constant int GLP_CLI_V_CUT  = offsetof(glp_cli_vertex_data, cut);
%constant int GLP_CLI_V_PI   = offsetof(glp_cli_vertex_data, pi);
%constant int GLP_CLI_V_RHS  = offsetof(glp_cli_vertex_data, rhs);
%constant int GLP_CLI_V_SET  = offsetof(glp_cli_vertex_data, set);
%constant int GLP_CLI_V_SIZE = sizeof(glp_cli_vertex_data);

%csmethodmodifiers glp_cli_arc_get_data(const glp_arc *arc)"
/**
 * Get arc data.
 *
 * @param arc arc
 * @return data
 */
public";

%csmethodmodifiers glp_cli_vertex_get(const glp_graph *G, const int i)"
/**
 * Get vertex.
 *
 * @param G graph
 * @param i index
 * @return vertex
 */
public";

%csmethodmodifiers glp_cli_vertex_data_get(const glp_graph *G, const int i)"
/**
 * Get vertex data.
 *
 * @param G graph
 * @param i index to vertex
 * @return data
 */
public";

%csmethodmodifiers glp_cli_vertex_get_data (const glp_vertex *v)"
/**
 * Get vertex data.
 *
 * @param v vertex
 * @return data
 */
public";

%csmethodmodifiers glp_cli_error(char *message)"
/**
 * Abort GLPK library with error message. This method can be used to stop the
 * solver using a GlpkTerminalListener.
 *
 * @param message message
 */
public";

%csmethodmodifiers glp_cli_set_msg_lvl(int msg_lvl)"
/**
 * Sets the message level. This method enables and disables debug output of
 * GLPK for Java.
 *
 * @param msg_lvl message level
 *
 * @see GLPKConstants#GLP_CLI_MSG_LVL_OFF
 * @see GLPKConstants#GLP_CLI_MSG_LVL_ALL
 */
public";

%csmethodmodifiers glp_cli_set_numeric_locale(char *locale)"
/**
 * Sets the locale for number formatting.
 * GLPK requires locale \"C\" for importing model files. Use the following code
 * to set the locale.
 * <pre>
 * GLPK.glp_cli_set_numeric_locale(\"C\");
 * </pre>
 *
 * @param locale locale
 */
public";

%csattributes hidden_internal "
/**
 * Hides internal structure.
 *
 * The internal fields of this structure cannot be accessed
 * directly. Use the library methods.
 */"
%typemap(csvarout, excode=SWIGEXCODE) (int hidden_internal) %{
  /**
   * Always returns zero.
   *
   * @return 0
   */
  get {
    $excode
    return 0;
  }
%}
%typemap(csvarin, excode=SWIGEXCODE) (int hidden_internal) %{
  /**
   * Does nothing.
   */
  set {
    $excode
    return;
  }
%}


%include "glpk_cli.h"

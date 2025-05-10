using System;
using org.gnu.glpk;

/**
 * The program reads a minimum cost problem instance in DIMACS format from file,
 * solves it by using the routine glp_mincost_relax4, and writes the solution
 * found on the standard output.
 */
public class Relax4
{

	static void Main (string[] args)
	{
		glp_graph g = null;
		int ret;
		int exitCode = 1;
		String filename;
		SWIGTYPE_p_double sol;
		if (1 != args.Length) {
			Console.WriteLine ("Usage: cli Relax4 model.min");
			Environment.Exit (1);
		}
		GLPK.glp_cli_set_numeric_locale ("C");

		filename = args [0];

		sol = GLPK.new_doubleArray (1);
		try {
			g = GLPK.glp_create_graph (
				GLPK.GLP_CLI_V_SIZE,
				GLPK.GLP_CLI_A_SIZE);
			do {
				GLPK.glp_cli_set_numeric_locale ("C");
				ret = GLPK.glp_read_mincost (
					g,
					GLPK.GLP_CLI_V_RHS,
					GLPK.GLP_CLI_A_LOW,
					GLPK.GLP_CLI_A_CAP,
					GLPK.GLP_CLI_A_COST,
					filename);
				if (ret != 0) {
					break;
				}
				ret = GLPK.glp_mincost_relax4 (
					g,
					GLPK.GLP_CLI_V_RHS,
					GLPK.GLP_CLI_A_LOW,
					GLPK.GLP_CLI_A_CAP,
					GLPK.GLP_CLI_A_COST,
					0,
					sol,
					GLPK.GLP_CLI_A_X,
					GLPK.GLP_CLI_A_RC);
				Console.WriteLine (
					"ret = {0}; sol = {1}", ret,
					GLPK.doubleArray_getitem (sol, 0));
				if (ret != 0) {
					break;
				}
				for (int i = 1; i < g.nv; i++) {
					glp_vertex v = GLPK.glp_cli_vertex_get (g, i);
					for (glp_arc a = v.out_; a != null;
					     a = a.t_next) {
						glp_vertex w = a.head;
						Console.WriteLine (
							"arc {0}->{1}: x = {2}; rc = {3}",
							v.i, w.i,
							GLPK.glp_cli_arc_get_data (a).x,
							GLPK.glp_cli_arc_get_data (a).rc);
					}
				}
				// signal success
				exitCode = 0;
			} while (false);
		} catch (GlpkException e) {
			// print error message
			Console.Error.WriteLine (e.Message);
			// signal failure
			GLPK.delete_doubleArray (sol);
			Environment.Exit (1);
		} finally {
			if (g != null) {
				GLPK.glp_delete_graph (g);
			}
		}
		GLPK.delete_doubleArray (sol);
		Environment.Exit (exitCode);
	}
}

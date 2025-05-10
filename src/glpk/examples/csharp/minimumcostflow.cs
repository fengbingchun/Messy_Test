using System;
using org.gnu.glpk;

/**
 * Minimum Cost Flow.
 *
 */
public class MinimumCostFlow {

    /**
     * Main method.
     * @param args Command line arguments
     */
	static void Main (string[] args) {
		glp_prob lp;
		glp_arc arc;
		glp_cli_arc_data adata;
		glp_cli_vertex_data vdata;

		try {
			glp_graph graph =
				GLPK.glp_create_graph(
					GLPK.GLP_CLI_V_SIZE,
					GLPK.GLP_CLI_A_SIZE);
			GLPK.glp_set_graph_name(graph, "MinimumCostFlow");

			GLPK.glp_add_vertices(graph, 9);

			GLPK.glp_set_vertex_name(graph, 1, "v1");
			GLPK.glp_set_vertex_name(graph, 2, "v2");
			GLPK.glp_set_vertex_name(graph, 3, "v3");
			GLPK.glp_set_vertex_name(graph, 4, "v4");
			GLPK.glp_set_vertex_name(graph, 5, "v5");
			GLPK.glp_set_vertex_name(graph, 6, "v6");
			GLPK.glp_set_vertex_name(graph, 7, "v7");
			GLPK.glp_set_vertex_name(graph, 8, "v8");
			GLPK.glp_set_vertex_name(graph, 9, "v9");

			vdata = GLPK.glp_cli_vertex_data_get(graph, 1);
			vdata.rhs = 20;
			vdata = GLPK.glp_cli_vertex_data_get(graph, 9);
			vdata.rhs = -20;

			arc = GLPK.glp_add_arc(graph, 1, 2);
			adata = GLPK.glp_cli_arc_get_data(arc);
			adata.low = 0; adata.cap = 14; adata.cost = 0;

			arc = GLPK.glp_add_arc(graph, 1, 4);
			adata = GLPK.glp_cli_arc_get_data(arc);
			adata.low = 0; adata.cap = 23; adata.cost = 0;

			arc = GLPK.glp_add_arc(graph, 2, 4);
			adata = GLPK.glp_cli_arc_get_data(arc);
			adata.low = 0; adata.cap = 9; adata.cost = 3;

			arc = GLPK.glp_add_arc(graph, 2, 3);
			adata = GLPK.glp_cli_arc_get_data(arc);
			adata.low = 0; adata.cap = 10; adata.cost = 2;

			arc = GLPK.glp_add_arc(graph, 4, 5);
			adata = GLPK.glp_cli_arc_get_data(arc);
			adata.low = 0; adata.cap = 26; adata.cost = 0;

			arc = GLPK.glp_add_arc(graph, 5, 2);
			adata = GLPK.glp_cli_arc_get_data(arc);
			adata.low = 0; adata.cap = 11; adata.cost = 1;

			arc = GLPK.glp_add_arc(graph, 3, 8);
			adata = GLPK.glp_cli_arc_get_data(arc);
			adata.low = 0; adata.cap = 18; adata.cost = 0;

			arc = GLPK.glp_add_arc(graph, 3, 5);
			adata = GLPK.glp_cli_arc_get_data(arc);
			adata.low = 2; adata.cap = 12; adata.cost = 1;

			arc = GLPK.glp_add_arc(graph, 5, 6);
			adata = GLPK.glp_cli_arc_get_data(arc);
			adata.low = 0; adata.cap = 25; adata.cost = 5;

			arc = GLPK.glp_add_arc(graph, 5, 7);
			adata = GLPK.glp_cli_arc_get_data(arc);
			adata.low = 0; adata.cap = 4; adata.cost = 7;

			arc = GLPK.glp_add_arc(graph, 6, 7);
			adata = GLPK.glp_cli_arc_get_data(arc);
			adata.low = 0; adata.cap = 7; adata.cost = 0;

			arc = GLPK.glp_add_arc(graph, 6, 8);
			adata = GLPK.glp_cli_arc_get_data(arc);
			adata.low = 4; adata.cap = 8; adata.cost = 0;

			arc = GLPK.glp_add_arc(graph, 8, 9);
			adata = GLPK.glp_cli_arc_get_data(arc);
			adata.low = 0; adata.cap = 20; adata.cost = 9;

			arc = GLPK.glp_add_arc(graph, 7, 9);
			adata = GLPK.glp_cli_arc_get_data(arc);
			adata.low = 0; adata.cap = 15; adata.cost = 3;

			GLPK.glp_write_mincost(graph, 
			                       GLPK.GLP_CLI_V_RHS,
			                       GLPK.GLP_CLI_A_LOW,
			                       GLPK.GLP_CLI_A_CAP,
			                       GLPK.GLP_CLI_A_COST,
			                       "mincost.dimacs");
			lp = GLPK.glp_create_prob();
			GLPK.glp_mincost_lp(lp, graph, 
			                    GLPK.GLP_ON, // use symbolic names
			                    GLPK.GLP_CLI_V_RHS,
			                    GLPK.GLP_CLI_A_LOW,
			                    GLPK.GLP_CLI_A_CAP,
			                    GLPK.GLP_CLI_A_COST);
			GLPK.glp_delete_graph(graph);
			GLPK.glp_write_lp(lp, null, "mincost.lp");
			GLPK.glp_delete_prob(lp);
        } catch (org.gnu.glpk.GlpkException ex) {
			Console.WriteLine(ex.Message);
			Environment.Exit(1);
        }
    }
}

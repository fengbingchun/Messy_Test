import org.gnu.glpk.*;

/**
 * Minimum Cost Flow.
 *
 */
public class MinimumCostFlow {

    /**
     * Main method.
     * @param args Command line arguments
     */
    public static void main(String[] args) {
        glp_prob lp;
        glp_arc arc;
        glp_java_arc_data adata;
        glp_java_vertex_data vdata;

        try {
            glp_graph graph =
                    GLPK.glp_create_graph(
                    GLPKConstants.GLP_JAVA_V_SIZE,
                    GLPKConstants.GLP_JAVA_A_SIZE);
            GLPK.glp_set_graph_name(graph,
                    MinimumCostFlow.class.getName());

            int ret = GLPK.glp_add_vertices(graph, 9);

            GLPK.glp_set_vertex_name(graph, 1, "v1");
            GLPK.glp_set_vertex_name(graph, 2, "v2");
            GLPK.glp_set_vertex_name(graph, 3, "v3");
            GLPK.glp_set_vertex_name(graph, 4, "v4");
            GLPK.glp_set_vertex_name(graph, 5, "v5");
            GLPK.glp_set_vertex_name(graph, 6, "v6");
            GLPK.glp_set_vertex_name(graph, 7, "v7");
            GLPK.glp_set_vertex_name(graph, 8, "v8");
            GLPK.glp_set_vertex_name(graph, 9, "v9");
           
            vdata = GLPK.glp_java_vertex_data_get(graph, 1);
            vdata.setRhs(20);
            vdata = GLPK.glp_java_vertex_data_get(graph, 9);
            vdata.setRhs(-20);
        
            arc = GLPK.glp_add_arc(graph, 1, 2);
            adata = GLPK.glp_java_arc_get_data(arc);
            adata.setLow(0); adata.setCap(14); adata.setCost(0);
            
            arc = GLPK.glp_add_arc(graph, 1, 4);
            adata = GLPK.glp_java_arc_get_data(arc);
            adata.setLow(0); adata.setCap(23); adata.setCost(0);

            arc = GLPK.glp_add_arc(graph, 2, 4);
            adata = GLPK.glp_java_arc_get_data(arc);
            adata.setLow(0); adata.setCap(9); adata.setCost(3);
            
            arc = GLPK.glp_add_arc(graph, 2, 3);
            adata = GLPK.glp_java_arc_get_data(arc);
            adata.setLow(0); adata.setCap(10); adata.setCost(2);
            
            arc = GLPK.glp_add_arc(graph, 4, 5);
            adata = GLPK.glp_java_arc_get_data(arc);
            adata.setLow(0); adata.setCap(26); adata.setCost(0);
            
            arc = GLPK.glp_add_arc(graph, 5, 2);
            adata = GLPK.glp_java_arc_get_data(arc);
            adata.setLow(0); adata.setCap(11); adata.setCost(1);
            
            arc = GLPK.glp_add_arc(graph, 3, 8);
            adata = GLPK.glp_java_arc_get_data(arc);
            adata.setLow(0); adata.setCap(18); adata.setCost(0);
            
            arc = GLPK.glp_add_arc(graph, 3, 5);
            adata = GLPK.glp_java_arc_get_data(arc);
            adata.setLow(2); adata.setCap(12); adata.setCost(1);
            
            arc = GLPK.glp_add_arc(graph, 5, 6);
            adata = GLPK.glp_java_arc_get_data(arc);
            adata.setLow(0); adata.setCap(25); adata.setCost(5);
            
            arc = GLPK.glp_add_arc(graph, 5, 7);
            adata = GLPK.glp_java_arc_get_data(arc);
            adata.setLow(0); adata.setCap(4); adata.setCost(7);
            
            arc = GLPK.glp_add_arc(graph, 6, 7);
            adata = GLPK.glp_java_arc_get_data(arc);
            adata.setLow(0); adata.setCap(7); adata.setCost(0);
            
            arc = GLPK.glp_add_arc(graph, 6, 8);
            adata = GLPK.glp_java_arc_get_data(arc);
            adata.setLow(4); adata.setCap(8); adata.setCost(0);

            arc = GLPK.glp_add_arc(graph, 8, 9);
            adata = GLPK.glp_java_arc_get_data(arc);
            adata.setLow(0); adata.setCap(20); adata.setCost(9);
            
            arc = GLPK.glp_add_arc(graph, 7, 9);
            adata = GLPK.glp_java_arc_get_data(arc);
            adata.setLow(0); adata.setCap(15); adata.setCost(3);
            
            GLPK.glp_write_mincost(graph, 
                    GLPKConstants.GLP_JAVA_V_RHS,
                    GLPKConstants.GLP_JAVA_A_LOW,
                    GLPKConstants.GLP_JAVA_A_CAP,
                    GLPKConstants.GLP_JAVA_A_COST,
                    "mincost.dimacs");
            lp = GLPK.glp_create_prob();
            GLPK.glp_mincost_lp(lp, graph, 
                    GLPKConstants.GLP_ON, // use symbolic names
                    GLPKConstants.GLP_JAVA_V_RHS,
                    GLPKConstants.GLP_JAVA_A_LOW,
                    GLPKConstants.GLP_JAVA_A_CAP,
                    GLPKConstants.GLP_JAVA_A_COST);
            GLPK.glp_delete_graph(graph);
            GLPK.glp_write_lp(lp, null, "mincost.lp");
            GLPK.glp_delete_prob(lp);
        } catch (org.gnu.glpk.GlpkException ex) {
            System.out.println(ex.getMessage());
            System.exit(1);
        }
    }
}

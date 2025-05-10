
import org.gnu.glpk.GLPK;
import org.gnu.glpk.GLPKConstants;
import org.gnu.glpk.GlpkException;
import org.gnu.glpk.glp_arc;
import org.gnu.glpk.glp_graph;
import org.gnu.glpk.glp_vertex;
import org.gnu.glpk.SWIGTYPE_p_double;

/**
 * The program reads a minimum cost problem instance in DIMACS format from file,
 * solves it by using the routine glp_mincost_relax4, and writes the solution
 * found on the standard output.
 */
public class Relax4 {

    public static void main(String[] arg) {
        glp_graph g = null;
        int ret;
        int exitCode = 1;
        String filename;
        SWIGTYPE_p_double sol;
        if (1 != arg.length) {
            System.out.println("Usage: java Relax4 model.min");
            System.exit(1);
        }
        GLPK.glp_java_set_numeric_locale("C");

        filename = arg[0];

        sol = GLPK.new_doubleArray(1);
        try {
            g = GLPK.glp_create_graph(
                    GLPKConstants.GLP_JAVA_V_SIZE,
                    GLPKConstants.GLP_JAVA_A_SIZE);
            do {
                GLPK.glp_java_set_numeric_locale("C");
                ret = GLPK.glp_read_mincost(g,
                        GLPKConstants.GLP_JAVA_V_RHS,
                        GLPKConstants.GLP_JAVA_A_LOW,
                        GLPKConstants.GLP_JAVA_A_CAP,
                        GLPKConstants.GLP_JAVA_A_COST,
                        filename);
                if (ret != 0) {
                    break;
                }
                ret = GLPK.glp_mincost_relax4(g,
                        GLPKConstants.GLP_JAVA_V_RHS,
                        GLPKConstants.GLP_JAVA_A_LOW,
                        GLPKConstants.GLP_JAVA_A_CAP,
                        GLPKConstants.GLP_JAVA_A_COST,
                        0,
                        sol,
                        GLPKConstants.GLP_JAVA_A_X,
                        GLPKConstants.GLP_JAVA_A_RC);
                System.out.printf("ret = %d; sol = %5g\n", ret,
                        GLPK.doubleArray_getitem(sol, 0));
                if (ret != 0) {
                    break;
                }
                for (int i = 1; i < g.getNv(); i++) {
                    glp_vertex v = GLPK.glp_java_vertex_get(g, i);
                    for (glp_arc a = v.getOut(); a != null;
		           a = a.getT_next()) {
                        glp_vertex w = a.getHead();
			System.out.printf("arc %d->%d: x = %5g; rc = %5g\n",
			v.getI(), w.getI(),
			GLPK.glp_java_arc_get_data(a).getX(),
			GLPK.glp_java_arc_get_data(a).getRc());
                    }
                }
                // signal success
                exitCode = 0;
            } while (false);
        } catch (GlpkException e) {
            // print error message
            System.err.println(e.getMessage());
            // signal failure
            GLPK.delete_doubleArray(sol);
            System.exit(1);
        } finally {
            if (g != null) {
                GLPK.glp_delete_graph(g);
            }
        }
        GLPK.delete_doubleArray(sol);
        System.exit(exitCode);
    }
}

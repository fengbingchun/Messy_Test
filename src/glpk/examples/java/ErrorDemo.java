
import org.gnu.glpk.GLPK;
import org.gnu.glpk.GLPKConstants;
import org.gnu.glpk.GlpkCallback;
import org.gnu.glpk.GlpkCallbackListener;
import org.gnu.glpk.GlpkException;
import org.gnu.glpk.SWIGTYPE_p_double;
import org.gnu.glpk.SWIGTYPE_p_int;
import org.gnu.glpk.glp_iocp;
import org.gnu.glpk.glp_prob;
import org.gnu.glpk.glp_tree;

/**
 * This example file demonstrates how to safely treat errors when calling the
 * glpk library, if the error occurs in the callback function.
 *
 * It creates a problem and tries to add -1 row in the callback function. This
 * will cause an error to occur.
 */
public class ErrorDemo implements GlpkCallbackListener {

    static boolean forceError = true;

    public void callback(glp_tree tree) {
        glp_prob prob;
        if (GLPK.glp_ios_reason(tree) == GLPKConstants.GLP_IROWGEN) {
            prob = GLPK.glp_ios_get_prob(tree);
            if (forceError) {
                GLPK.glp_java_set_msg_lvl(GLPKConstants.GLP_JAVA_MSG_LVL_ALL);
                try {
                    GLPK.glp_add_rows(prob, -1);
                } catch (GlpkException ex) {
                    System.out.println("Error in callback: " + ex.getMessage());
                }
                GLPK.glp_java_set_msg_lvl(GLPKConstants.GLP_JAVA_MSG_LVL_OFF);
            }
        }
    }

    /**
     * This is the main function.
     */
    public static void main(String[] args) {
        ErrorDemo d = new ErrorDemo();
        System.out.println("GLPK version: " + GLPK.glp_version());

        GlpkCallback.addListener(d);

        for (int i = 1; i < 5; i++) {
            forceError = !forceError;
            System.out.print("\nIteration " + i);
            if (forceError) {
                System.out.println(", error expected to occur.");
            } else {
                System.out.println(", success expected.");
            }
            if (d.run()) {
                System.out.println("An error has occured.");
                if (!forceError) {
                    System.exit(1);
                }
            } else {
                System.out.println("Successful execution.");
                if (forceError) {
                    System.exit(1);
                }
            }
        }
    }

    /**
     * Build a model with one column
     *
     * @return error error occurred
     */
    private boolean run() {
        glp_prob lp;
        glp_iocp iocp;
        SWIGTYPE_p_int ind;
        SWIGTYPE_p_double val;
        boolean ret = false;

        try {
            //  Create problem
            lp = GLPK.glp_create_prob();
            System.out.println("Problem created");
            GLPK.glp_set_prob_name(lp, "myProblem");

            //  Define columns
            GLPK.glp_add_cols(lp, 2);
            GLPK.glp_set_col_name(lp, 1, "x1");
            GLPK.glp_set_col_kind(lp, 1, GLPKConstants.GLP_IV);
            GLPK.glp_set_col_bnds(lp, 1, GLPKConstants.GLP_LO, 0, 0);
            GLPK.glp_set_col_name(lp, 2, "x2");
            GLPK.glp_set_col_kind(lp, 2, GLPKConstants.GLP_IV);
            GLPK.glp_set_col_bnds(lp, 2, GLPKConstants.GLP_LO, 0, 0);

            //  Create constraints
            GLPK.glp_add_rows(lp, 2);
            GLPK.glp_set_row_name(lp, 1, "c1");
            GLPK.glp_set_row_bnds(lp, 1, GLPKConstants.GLP_UP, 0, 40);
            ind = GLPK.new_intArray(3);
            GLPK.intArray_setitem(ind, 1, 1);
            GLPK.intArray_setitem(ind, 2, 2);
            val = GLPK.new_doubleArray(3);
            GLPK.doubleArray_setitem(val, 1, 10);
            GLPK.doubleArray_setitem(val, 2, 7);
            GLPK.glp_set_mat_row(lp, 1, 2, ind, val);
            GLPK.delete_intArray(ind);
            GLPK.delete_doubleArray(val);

            ind = GLPK.new_intArray(3);
            GLPK.intArray_setitem(ind, 1, 1);
            GLPK.intArray_setitem(ind, 2, 2);
            val = GLPK.new_doubleArray(3);
            GLPK.glp_set_row_name(lp, 2, "c2");
            GLPK.glp_set_row_bnds(lp, 2, GLPKConstants.GLP_UP, 0, 5);
            GLPK.doubleArray_setitem(val, 1, 1);
            GLPK.doubleArray_setitem(val, 2, 1);
            GLPK.glp_set_mat_row(lp, 2, 2, ind, val);
            GLPK.delete_intArray(ind);
            GLPK.delete_doubleArray(val);

            //  Define objective
            GLPK.glp_set_obj_name(lp, "obj");
            GLPK.glp_set_obj_dir(lp, GLPKConstants.GLP_MAX);
            GLPK.glp_set_obj_coef(lp, 0, 0);
            GLPK.glp_set_obj_coef(lp, 1, 17);
            GLPK.glp_set_obj_coef(lp, 2, 12);

            //  solve model
            iocp = new glp_iocp();
            GLPK.glp_init_iocp(iocp);
            iocp.setPresolve(GLPKConstants.GLP_ON);
            iocp.setMsg_lev(GLPKConstants.GLP_MSG_OFF);
            GLPK.glp_intopt(lp, iocp);

            // free memory
            GLPK.glp_delete_prob(lp);
        } catch (GlpkException ex) {
            System.out.println(ex.getMessage());
            ret = true;
        }
        return ret;
    }
}

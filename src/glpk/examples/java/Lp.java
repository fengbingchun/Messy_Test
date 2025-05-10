
import org.gnu.glpk.GLPK;
import org.gnu.glpk.GLPKConstants;
import org.gnu.glpk.GlpkException;
import org.gnu.glpk.SWIGTYPE_p_double;
import org.gnu.glpk.SWIGTYPE_p_int;
import org.gnu.glpk.glp_prob;
import org.gnu.glpk.glp_smcp;

public class Lp {
    //	Minimize z = -.5 * x1 + .5 * x2 - x3 + 1
    //
    //	subject to
    //	0.0 <= x1 - .5 * x2 <= 0.2
    //  -x2 + x3 <= 0.4
    //	where,
    //	0.0 <= x1 <= 0.5
    //	0.0 <= x2 <= 0.5
    //  0.0 <= x3 <= 0.5

    public static void main(String[] arg) {
        glp_prob lp;
        glp_smcp parm;
        SWIGTYPE_p_int ind;
        SWIGTYPE_p_double val;
        int ret;

        try {
            // Create problem
            lp = GLPK.glp_create_prob();
            System.out.println("Problem created");
            GLPK.glp_set_prob_name(lp, "myProblem");

            // Define columns
            GLPK.glp_add_cols(lp, 3);
            GLPK.glp_set_col_name(lp, 1, "x1");
            GLPK.glp_set_col_kind(lp, 1, GLPKConstants.GLP_CV);
            GLPK.glp_set_col_bnds(lp, 1, GLPKConstants.GLP_DB, 0, .5);
            GLPK.glp_set_col_name(lp, 2, "x2");
            GLPK.glp_set_col_kind(lp, 2, GLPKConstants.GLP_CV);
            GLPK.glp_set_col_bnds(lp, 2, GLPKConstants.GLP_DB, 0, .5);
            GLPK.glp_set_col_name(lp, 3, "x3");
            GLPK.glp_set_col_kind(lp, 3, GLPKConstants.GLP_CV);
            GLPK.glp_set_col_bnds(lp, 3, GLPKConstants.GLP_DB, 0, .5);

            // Create constraints

            // Allocate memory
            ind = GLPK.new_intArray(3);
            val = GLPK.new_doubleArray(3);

            // Create rows
            GLPK.glp_add_rows(lp, 2);

            // Set row details
            GLPK.glp_set_row_name(lp, 1, "c1");
            GLPK.glp_set_row_bnds(lp, 1, GLPKConstants.GLP_DB, 0, 0.2);
            GLPK.intArray_setitem(ind, 1, 1);
            GLPK.intArray_setitem(ind, 2, 2);
            GLPK.doubleArray_setitem(val, 1, 1.);
            GLPK.doubleArray_setitem(val, 2, -.5);
            GLPK.glp_set_mat_row(lp, 1, 2, ind, val);

            GLPK.glp_set_row_name(lp, 2, "c2");
            GLPK.glp_set_row_bnds(lp, 2, GLPKConstants.GLP_UP, 0, 0.4);
            GLPK.intArray_setitem(ind, 1, 2);
            GLPK.intArray_setitem(ind, 2, 3);
            GLPK.doubleArray_setitem(val, 1, -1.);
            GLPK.doubleArray_setitem(val, 2, 1.);
            GLPK.glp_set_mat_row(lp, 2, 2, ind, val);

            // Free memory
            GLPK.delete_intArray(ind);
            GLPK.delete_doubleArray(val);

            // Define objective
            GLPK.glp_set_obj_name(lp, "z");
            GLPK.glp_set_obj_dir(lp, GLPKConstants.GLP_MIN);
            GLPK.glp_set_obj_coef(lp, 0, 1.);
            GLPK.glp_set_obj_coef(lp, 1, -.5);
            GLPK.glp_set_obj_coef(lp, 2, .5);
            GLPK.glp_set_obj_coef(lp, 3, -1);

            // Write model to file
            // GLPK.glp_write_lp(lp, null, "lp.lp");

            // Solve model
            parm = new glp_smcp();
            GLPK.glp_init_smcp(parm);
            ret = GLPK.glp_simplex(lp, parm);

            // Retrieve solution
            if (ret == 0) {
                write_lp_solution(lp);
            } else {
                System.out.println("The problem could not be solved");
            }

            // Free memory
            GLPK.glp_delete_prob(lp);
        } catch (GlpkException ex) {
            ex.printStackTrace();
	    ret = 1;
        }
	System.exit(ret);
    }

    /**
     * write simplex solution
     * @param lp problem
     */
    static void write_lp_solution(glp_prob lp) {
        int i;
        int n;
        String name;
        double val;

        name = GLPK.glp_get_obj_name(lp);
        val = GLPK.glp_get_obj_val(lp);
        System.out.print(name);
        System.out.print(" = ");
        System.out.println(val);
        n = GLPK.glp_get_num_cols(lp);
        for (i = 1; i <= n; i++) {
            name = GLPK.glp_get_col_name(lp, i);
            val = GLPK.glp_get_col_prim(lp, i);
            System.out.print(name);
            System.out.print(" = ");
            System.out.println(val);
        }
    }
}

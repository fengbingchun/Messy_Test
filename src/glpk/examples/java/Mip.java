import org.gnu.glpk.GLPK;
import org.gnu.glpk.GLPKConstants;
import org.gnu.glpk.GlpkException;
import org.gnu.glpk.SWIGTYPE_p_double;
import org.gnu.glpk.SWIGTYPE_p_int;
import org.gnu.glpk.glp_prob;
import org.gnu.glpk.glp_iocp;

public class Mip {
    // Maximize z =  17 * x1 + 12* x2
    // subject to
    //   10 x1 + 7 x2 <= 40
    //      x1 +   x2 <=  5
    // where,
    //   0.0 <= x1  integer
    //   0.0 <= x2  integer

    public static void main(String[] arg) {
        glp_prob lp;
        glp_iocp iocp;
        SWIGTYPE_p_int ind;
        SWIGTYPE_p_double val;
        int ret;

        try {
            // Create problem
            lp = GLPK.glp_create_prob();
            System.out.println("Problem created");
            GLPK.glp_set_prob_name(lp, "myProblem");

            // Define columns
            GLPK.glp_add_cols(lp, 2);
            GLPK.glp_set_col_name(lp, 1, "x1");
            GLPK.glp_set_col_kind(lp, 1, GLPKConstants.GLP_IV);
            GLPK.glp_set_col_bnds(lp, 1, GLPKConstants.GLP_LO, 0, 0);
            GLPK.glp_set_col_name(lp, 2, "x2");
            GLPK.glp_set_col_kind(lp, 2, GLPKConstants.GLP_IV);
            GLPK.glp_set_col_bnds(lp, 2, GLPKConstants.GLP_LO, 0, 0);

            // Create constraints
            GLPK.glp_add_rows(lp, 2);
            GLPK.glp_set_row_name(lp, 1, "c1");
            GLPK.glp_set_row_bnds(lp, 1, GLPKConstants.GLP_UP, 0, 40);

            ind = GLPK.new_intArray(3);
            val = GLPK.new_doubleArray(3);

            GLPK.intArray_setitem(ind, 1, 1);
            GLPK.intArray_setitem(ind, 2, 2);
            GLPK.doubleArray_setitem(val, 1, 10);
            GLPK.doubleArray_setitem(val, 2,  7);
            GLPK.glp_set_mat_row(lp, 1, 2, ind, val);

            GLPK.glp_set_row_name(lp, 2, "c2");
            GLPK.glp_set_row_bnds(lp, 2, GLPKConstants.GLP_UP, 0, 5);

            GLPK.intArray_setitem(ind, 1, 1);
            GLPK.intArray_setitem(ind, 2, 2);
            GLPK.doubleArray_setitem(val, 1, 1);
            GLPK.doubleArray_setitem(val, 2, 1);
            GLPK.glp_set_mat_row(lp, 2, 2, ind, val);

            GLPK.delete_doubleArray(val);
            GLPK.delete_intArray(ind);

            // Define objective
            GLPK.glp_set_obj_name(lp, "obj");
            GLPK.glp_set_obj_dir(lp, GLPKConstants.GLP_MAX);
            GLPK.glp_set_obj_coef(lp, 0, 0);
            GLPK.glp_set_obj_coef(lp, 1, 17);
            GLPK.glp_set_obj_coef(lp, 2, 12);

            // Solve model
            iocp = new glp_iocp();
            GLPK.glp_init_iocp(iocp);
            iocp.setPresolve(GLPKConstants.GLP_ON);
            ret = GLPK.glp_intopt(lp, iocp);

            // Retrieve solution
            if (ret == 0) {
                write_mip_solution(lp);
            } else {
                System.out.println("The problem could not be solved");
            };

            // free memory
            GLPK.glp_delete_prob(lp);
        } catch (GlpkException ex) {
            ex.printStackTrace();
            ret = 1;
        }
        System.exit(ret);
    }

    /**
     * write integer solution
     * @param mip problem
     */
    static void write_mip_solution(glp_prob lp) {
        int i;
        int n;
        String name;
        double val;

        name = GLPK.glp_get_obj_name(lp);
        val  = GLPK.glp_mip_obj_val(lp);
        System.out.print(name);
        System.out.print(" = ");
        System.out.println(val);
        n = GLPK.glp_get_num_cols(lp);
        for(i=1; i <= n; i++) {
            name = GLPK.glp_get_col_name(lp, i);
            val  = GLPK.glp_mip_col_val(lp, i);
            System.out.print(name);
            System.out.print(" = ");
            System.out.println(val);
        }
    }
}


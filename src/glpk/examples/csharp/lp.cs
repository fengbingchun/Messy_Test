using System;
using org.gnu.glpk;

class Program
{
	static void Main (string[] args)
	{
		glp_prob lp;
		glp_smcp parm;
		SWIGTYPE_p_int ind;
		SWIGTYPE_p_double val;
		int ret;

		try {

			lp = GLPK.glp_create_prob ();
			Console.WriteLine ("Problem created");

			// Define columns
			GLPK.glp_add_cols (lp, 3);
			GLPK.glp_set_col_name (lp, 1, "x1");
			GLPK.glp_set_col_kind (lp, 1, GLPK.GLP_CV);
			GLPK.glp_set_col_bnds (lp, 1, GLPK.GLP_DB, 0, .5);
			GLPK.glp_set_col_name (lp, 2, "x2");
			GLPK.glp_set_col_kind (lp, 2, GLPK.GLP_CV);
			GLPK.glp_set_col_bnds (lp, 2, GLPK.GLP_DB, 0, .5);
			GLPK.glp_set_col_name (lp, 3, "x3");
			GLPK.glp_set_col_kind (lp, 3, GLPK.GLP_CV);
			GLPK.glp_set_col_bnds (lp, 3, GLPK.GLP_DB, 0, .5);

			// Create constraints

			// Allocate memory
			ind = GLPK.new_intArray (3);
			val = GLPK.new_doubleArray (3);

			// Create rows
			GLPK.glp_add_rows (lp, 2);

			// Set row details
			GLPK.glp_set_row_name (lp, 1, "c1");
			GLPK.glp_set_row_bnds (lp, 1, GLPK.GLP_DB, 0, 0.2);
			GLPK.intArray_setitem (ind, 1, 1);
			GLPK.intArray_setitem (ind, 2, 2);
			GLPK.doubleArray_setitem (val, 1, 1.0);
			GLPK.doubleArray_setitem (val, 2, -.5);
			GLPK.glp_set_mat_row (lp, 1, 2, ind, val);

			GLPK.glp_set_row_name (lp, 2, "c2");
			GLPK.glp_set_row_bnds (lp, 2, GLPK.GLP_UP, 0, 0.4);
			GLPK.intArray_setitem (ind, 1, 2);
			GLPK.intArray_setitem (ind, 2, 3);
			GLPK.doubleArray_setitem (val, 1, -1.0);
			GLPK.doubleArray_setitem (val, 2, 1.0);
			GLPK.glp_set_mat_row (lp, 2, 2, ind, val);

			// Free memory
			GLPK.delete_intArray (ind);
			GLPK.delete_doubleArray (val);

			// Define objective
			GLPK.glp_set_obj_name (lp, "z");
			GLPK.glp_set_obj_dir (lp, GLPK.GLP_MIN);
			GLPK.glp_set_obj_coef (lp, 0, 1.0);
			GLPK.glp_set_obj_coef (lp, 1, -.5);
			GLPK.glp_set_obj_coef (lp, 2, .5);
			GLPK.glp_set_obj_coef (lp, 3, -1);

			// Solve model
			parm = new glp_smcp ();
			GLPK.glp_init_smcp (parm);
			ret = GLPK.glp_simplex (lp, parm);

			// Retrieve solution
			if (ret == 0) {
				write_lp_solution (lp);
			} else {
				Console.WriteLine ("The problem could not be solved");
			}

			// Free memory
			GLPK.glp_delete_prob (lp);

		} catch (GlpkException) {
			Console.WriteLine ("Error caught");
			ret = 1;
		}

		Environment.Exit (ret);
	}

	/**
    * write simplex solution
    * @param lp problem
    */
	static void write_lp_solution (glp_prob lp)
	{
		int i;
		int n;
		String name;
		double val;

		name = GLPK.glp_get_obj_name (lp);
		val = GLPK.glp_get_obj_val (lp);
		Console.Write (name);
		Console.Write (" = ");
		Console.WriteLine (val);
		n = GLPK.glp_get_num_cols (lp);
		for (i = 1; i <= n; i++) {
			name = GLPK.glp_get_col_name (lp, i);
			val = GLPK.glp_get_col_prim (lp, i);
			Console.Write (name);
			Console.Write (" = ");
			Console.WriteLine (val);
		}
	}
}

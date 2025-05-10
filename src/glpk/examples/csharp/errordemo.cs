using System;
using org.gnu.glpk;

/**
 * This example file demonstrates how to safely treat errors when calling the
 * glpk library, if the error occurs in the callback function.
 */
public class ErrorDemo : IGlpkCallbackListener
{

	static bool forceError = true;

	public void callback (glp_tree tree)
	{
		glp_prob prob;
		if (GLPK.glp_ios_reason (tree) == GLPK.GLP_IROWGEN) {
			prob = GLPK.glp_ios_get_prob (tree);
			if (forceError) {
				GLPK.glp_cli_set_msg_lvl (GLPK.GLP_CLI_MSG_LVL_ALL);
				try {
					GLPK.glp_add_rows (prob, -1);
				} catch (GlpkException ex) {
					Console.WriteLine ("Error in callback: " + ex.Message);
				}
				GLPK.glp_cli_set_msg_lvl (GLPK.GLP_CLI_MSG_LVL_OFF);
			}
		}
	}

	/**
     * This is the main function.
     */
	static void Main (string[] args)
	{
		ErrorDemo d = new ErrorDemo ();
		GlpkCallback.addListener (d);
		Console.WriteLine ("GLPK version: " + GLPK.glp_version ());

		for (int i = 1; i < 5; i++) {
			forceError = !forceError;
			Console.Write ("\nIteration " + i);
			if (forceError) {
				Console.WriteLine (", error expected to occur.");
			} else {
				Console.WriteLine (", success expected.");
			}
			if (d.run ()) {
				Console.WriteLine ("An error has occured.");
				if (!forceError) {
					Environment.Exit (1);
				}
			} else {
				Console.WriteLine ("Successful execution.");
				if (forceError) {
					Environment.Exit (1);
				}
			}
		}
	}

	/**
     * Build a model with one column
     *
     * @return error error occurred
     */
	private bool run ()
	{
		glp_prob lp;
		glp_iocp iocp;
		SWIGTYPE_p_int ind;
		SWIGTYPE_p_double val;
		bool ret = false;

		try {
			//  Create problem
			lp = GLPK.glp_create_prob ();
			Console.WriteLine ("Problem created");
			GLPK.glp_set_prob_name (lp, "myProblem");

			//  Define columns
			GLPK.glp_add_cols (lp, 2);
			GLPK.glp_set_col_name (lp, 1, "x1");
			GLPK.glp_set_col_kind (lp, 1, GLPK.GLP_IV);
			GLPK.glp_set_col_bnds (lp, 1, GLPK.GLP_LO, 0, 0);
			GLPK.glp_set_col_name (lp, 2, "x2");
			GLPK.glp_set_col_kind (lp, 2, GLPK.GLP_IV);
			GLPK.glp_set_col_bnds (lp, 2, GLPK.GLP_LO, 0, 0);

			//  Create constraints
			GLPK.glp_add_rows (lp, 2);
			GLPK.glp_set_row_name (lp, 1, "c1");
			GLPK.glp_set_row_bnds (lp, 1, GLPK.GLP_UP, 0, 40);
			ind = GLPK.new_intArray (3);
			GLPK.intArray_setitem (ind, 1, 1);
			GLPK.intArray_setitem (ind, 2, 2);
			val = GLPK.new_doubleArray (3);
			GLPK.doubleArray_setitem (val, 1, 10);
			GLPK.doubleArray_setitem (val, 2, 7);
			GLPK.glp_set_mat_row (lp, 1, 2, ind, val);
			GLPK.delete_intArray (ind);
			GLPK.delete_doubleArray (val);

			ind = GLPK.new_intArray (3);
			GLPK.intArray_setitem (ind, 1, 1);
			GLPK.intArray_setitem (ind, 2, 2);
			val = GLPK.new_doubleArray (3);
			GLPK.glp_set_row_name (lp, 2, "c2");
			GLPK.glp_set_row_bnds (lp, 2, GLPK.GLP_UP, 0, 5);
			GLPK.doubleArray_setitem (val, 1, 1);
			GLPK.doubleArray_setitem (val, 2, 1);
			GLPK.glp_set_mat_row (lp, 2, 2, ind, val);
			GLPK.delete_intArray (ind);
			GLPK.delete_doubleArray (val);

			//  Define objective
			GLPK.glp_set_obj_name (lp, "obj");
			GLPK.glp_set_obj_dir (lp, GLPK.GLP_MAX);
			GLPK.glp_set_obj_coef (lp, 0, 0);
			GLPK.glp_set_obj_coef (lp, 1, 17);
			GLPK.glp_set_obj_coef (lp, 2, 12);

			//  solve model
			iocp = new glp_iocp ();
			GLPK.glp_init_iocp (iocp);
			iocp.presolve = GLPK.GLP_ON;
			iocp.msg_lev = GLPK.GLP_MSG_OFF;
			GLPK.glp_intopt (lp, iocp);

			// free memory
			GLPK.glp_delete_prob (lp);
		} catch (GlpkException ex) {
			Console.WriteLine (ex.Message);
			ret = true;
		}
		return ret;
	}
}
using System;
using org.gnu.glpk;

public class Gmpl : IGlpkCallbackListener, IGlpkTerminalListener
{
	private bool hookUsed = false;

	public static void Main (string[] arg)
	{
		if (1 != arg.Length) {
			Console.WriteLine ("Usage: gmpl.exe model.mod");
			return;
		}
		GLPK.glp_cli_set_numeric_locale ("C");
		new Gmpl ().solve (arg);
	}

	public void solve (string[] arg)
	{
		glp_prob lp;
		glp_tran tran;
		glp_iocp iocp;

		String fname;
		int skip = 0;
		int ret;

		// listen to callbacks
		GlpkCallback.addListener (this);

		// listen to terminal output
		GlpkTerminal.addListener (this);

		try {

			// create problem
			lp = GLPK.glp_create_prob ();

			// allocate workspace
			tran = GLPK.glp_mpl_alloc_wksp ();

			// read model
			fname = arg [0];
			ret = GLPK.glp_mpl_read_model (tran, fname, skip);
			if (ret != 0) {
				GLPK.glp_mpl_free_wksp (tran);
				GLPK.glp_delete_prob (lp);
				throw new ApplicationException ("Model file not valid: " + fname);
			}

			// generate model
			ret = GLPK.glp_mpl_generate (tran, null);
			if (ret != 0) {
				GLPK.glp_mpl_free_wksp (tran);
				GLPK.glp_delete_prob (lp);
				throw new ApplicationException ("Cannot generate model: " + fname);
			}

			// build model
			GLPK.glp_mpl_build_prob (tran, lp);

			// set solver parameters
			iocp = new glp_iocp ();
			GLPK.glp_init_iocp (iocp);
			iocp.presolve = GLPK.GLP_ON;

			// do not listen to output anymore
			GlpkTerminal.removeListener (this);

			// solve model
			ret = GLPK.glp_intopt (lp, iocp);

			// postsolve model
			if (ret == 0) {
				GLPK.glp_mpl_postsolve (tran, lp, GLPK.GLP_MIP);
			}

			// free memory
			GLPK.glp_mpl_free_wksp (tran);
			GLPK.glp_delete_prob (lp);

		} catch (org.gnu.glpk.GlpkException e) {
			Console.Error.WriteLine ("An error inside the GLPK library occured.");
			Console.Error.WriteLine (e.Message);
		} catch (ApplicationException e) {
			Console.Error.WriteLine (e.Message);
		}

		// do not listen for callbacks anymore
		GlpkCallback.removeListener (this);

		// check that the terinal hook function has been used
		if (!hookUsed) {
			throw new ApplicationException (
				"The terminal output hook was not used.");
		}
	}

	public bool output (string str)
	{
		hookUsed = true;
		Console.Write (str);
		return false;
	}

	public void callback (glp_tree tree)
	{
		int reason = GLPK.glp_ios_reason (tree);
		if (reason == GLPK.GLP_IBINGO) {
			Console.WriteLine ("Better solution found");
		}
	}
}

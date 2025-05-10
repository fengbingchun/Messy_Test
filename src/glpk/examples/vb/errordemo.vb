Imports System
Imports org.gnu.glpk

' This example file demonstrates how to safely treat errors when calling the
' glpk library, if the error occurs in the callback function.
Module module1

    ' This is the main function.
	Function Main(ByVal cmdArgs() As String) As Integer
		Dim d As ErrorDemo
		Dim i As Integer
		
		d = new ErrorDemo ()
		GlpkCallback.addListener (d)
		Console.WriteLine ("GLPK version: " + GLPK.glp_version ())

		For i = 1 to 4
			d.forceError = Not d.forceError
			Console.Write (vbCrLf & "Iteration " & i)
			If d.forceError
				Console.WriteLine (", error expected to occur.")
			Else
				Console.WriteLine (", success expected.")
			End If
			If d.run() Then
				Console.WriteLine ("An error has occured.")
				If Not d.forceError Then
					Environment.Exit (1)
				End If
			Else
				Console.WriteLine ("Successful execution.")
				If d.forceError
					Environment.Exit (1)
				End If
			End If
		Next i
	End Function
End Module

Public Class ErrorDemo
    Implements IGlpkCallbackListener

	Private pForceError As Boolean
	
	Public Sub New()
	    forceError = false
	End Sub
	
	Public Property forceError() As Boolean
	    Get
    	    return pForceError
    	End Get
    	
    	Set(ByVal value As Boolean)
    	    pForceError = value
    	End Set
	End Property

	Public Sub callback (tree As glp_tree) _
	    Implements IGlpkCallbackListener.callback

		Dim prob As glp_prob

		If GLPK.glp_ios_reason (tree) = GLPK.GLP_IROWGEN Then
			prob = GLPK.glp_ios_get_prob (tree)
			If pForceError Then
				GLPK.glp_cli_set_msg_lvl (GLPK.GLP_CLI_MSG_LVL_ALL)
				Try
					GLPK.glp_add_rows (prob, -1)
				Catch ex As GlpkException
					Console.WriteLine ("Error in callback: " + ex.Message)
				End Try
				GLPK.glp_cli_set_msg_lvl (GLPK.GLP_CLI_MSG_LVL_OFF)
			End If
		End If
	End Sub


     ' Build a model with one column
     ' @return error error occurred

	Public Function run () As Boolean
		Dim lp As glp_prob
		Dim iocp As glp_iocp
		Dim ind As SWIGTYPE_p_int
		Dim val As SWIGTYPE_p_double
		Dim ret As Boolean = false

		Try
			'  Create problem
			lp = GLPK.glp_create_prob ()
			Console.WriteLine ("Problem created")
			GLPK.glp_set_prob_name (lp, "myProblem")

			'  Define columns
			GLPK.glp_add_cols (lp, 2)
			GLPK.glp_set_col_name (lp, 1, "x1")
			GLPK.glp_set_col_kind (lp, 1, GLPK.GLP_IV)
			GLPK.glp_set_col_bnds (lp, 1, GLPK.GLP_LO, 0, 0)
			GLPK.glp_set_col_name (lp, 2, "x2")
			GLPK.glp_set_col_kind (lp, 2, GLPK.GLP_IV)
			GLPK.glp_set_col_bnds (lp, 2, GLPK.GLP_LO, 0, 0)

			'  Create constraints
			GLPK.glp_add_rows (lp, 2)
			GLPK.glp_set_row_name (lp, 1, "c1")
			GLPK.glp_set_row_bnds (lp, 1, GLPK.GLP_UP, 0, 40)
			ind = GLPK.new_intArray (3)
			GLPK.intArray_setitem (ind, 1, 1)
			GLPK.intArray_setitem (ind, 2, 2)
			val = GLPK.new_doubleArray (3)
			GLPK.doubleArray_setitem (val, 1, 10)
			GLPK.doubleArray_setitem (val, 2, 7)
			GLPK.glp_set_mat_row (lp, 1, 2, ind, val)
			GLPK.delete_intArray (ind)
			GLPK.delete_doubleArray (val)

			ind = GLPK.new_intArray (3)
			GLPK.intArray_setitem (ind, 1, 1)
			GLPK.intArray_setitem (ind, 2, 2)
			val = GLPK.new_doubleArray (3)
			GLPK.glp_set_row_name (lp, 2, "c2")
			GLPK.glp_set_row_bnds (lp, 2, GLPK.GLP_UP, 0, 5)
			GLPK.doubleArray_setitem (val, 1, 1)
			GLPK.doubleArray_setitem (val, 2, 1)
			GLPK.glp_set_mat_row (lp, 2, 2, ind, val)
			GLPK.delete_intArray (ind)
			GLPK.delete_doubleArray (val)

			'  Define objective
			GLPK.glp_set_obj_name (lp, "obj")
			GLPK.glp_set_obj_dir (lp, GLPK.GLP_MAX)
			GLPK.glp_set_obj_coef (lp, 0, 0)
			GLPK.glp_set_obj_coef (lp, 1, 17)
			GLPK.glp_set_obj_coef (lp, 2, 12)

			'  solve model
			iocp = new glp_iocp ()
			GLPK.glp_init_iocp (iocp)
			iocp.presolve = GLPK.GLP_ON
			iocp.msg_lev = GLPK.GLP_MSG_OFF
			GLPK.glp_intopt (lp, iocp)

			' free memory
			GLPK.glp_delete_prob (lp)
		Catch ex As GlpkException
			Console.WriteLine (ex.Message)
			ret = true
		End Try
		Return ret
	End Function
End Class

Imports System
Imports org.gnu.glpk

Module module1
	Function Main(ByVal cmdArgs() As String) As Integer
	    Dim problem As clsGmpl
	    
		If 1 <> cmdArgs.Length Then
			Console.WriteLine ("Usage: gmpl.exe model.mod")
			Return 1
		End If
		problem = new clsGmpl ()
		Problem.solve (cmdArgs)
	End Function
End Module

Public Class clsGmpl
	Implements IGlpkCallbackListener, IGlpkTerminalListener

	Private hookUsed As Boolean = false

	Public Sub New()
	End Sub

	Sub solve (arg() As string)
		Dim lp As glp_prob
		Dim tran As glp_tran
		Dim iocp As glp_iocp

		Dim fname As String
		Dim skip As Integer = 0
		Dim ret As Integer

		GLPK.glp_cli_set_numeric_locale ("C")

		' listen to callbacks
		GlpkCallback.addListener (Me)

		' listen to terminal output
		GlpkTerminal.addListener (Me)

		Try

			' create problem
			lp = GLPK.glp_create_prob ()

			' allocate workspace
			tran = GLPK.glp_mpl_alloc_wksp ()

			' read model
			fname = arg(0)
			ret = GLPK.glp_mpl_read_model (tran, fname, skip)
			If ret <> 0 Then
				GLPK.glp_mpl_free_wksp (tran)
				GLPK.glp_delete_prob (lp)
				throw new ApplicationException ( _
					"Model file not valid: " + fname)
			End If

			' generate model
			ret = GLPK.glp_mpl_generate (tran, Nothing)
			If ret <> 0 Then
				GLPK.glp_mpl_free_wksp (tran)
				GLPK.glp_delete_prob (lp)
				throw new ApplicationException ( _
					"Cannot generate model: " + fname)
			End If

			' build model
			GLPK.glp_mpl_build_prob (tran, lp)

			' set solver parameters
			iocp = new glp_iocp ()
			GLPK.glp_init_iocp (iocp)
			iocp.presolve = GLPK.GLP_ON

			' do not listen to output anymore
			GlpkTerminal.removeListener (Me)

			' solve model
			ret = GLPK.glp_intopt (lp, iocp)

			' postsolve model
			If ret = 0 Then
				GLPK.glp_mpl_postsolve (tran, lp, GLPK.GLP_MIP)
			End If

			' free memory
			GLPK.glp_mpl_free_wksp (tran)
			GLPK.glp_delete_prob (lp)

		Catch e As org.gnu.glpk.GlpkException
			Console.Error.WriteLine ( _
				"An error inside the GLPK library occured.")
			Console.Error.WriteLine (e.Message)
		Catch e As ApplicationException
			Console.Error.WriteLine ( _
				"Applicaiton Exception")
			Console.Error.WriteLine (e.Message)
		End Try

		' do not listen for callbacks anymore
		GlpkCallback.removeListener (Me)

		' check that the terinal hook function has been used
		If Not hookUsed Then
			throw new ApplicationException ( _
				"The terminal output hook was not used.")
		End If
	End Sub

	Public Function output (str As string) As Boolean _
	    Implements IGlpkTerminalListener.output

		hookUsed = true
		Console.Write (str)
		return false
	End Function

	Public Sub callback (tree As glp_tree) _
	    Implements IGlpkCallbackListener.callback
	    
	    Dim reason as Integer
		reason = GLPK.glp_ios_reason (tree)
		If reason = GLPK.GLP_IBINGO Then
			Console.WriteLine ("Better solution found")
		End If
	End Sub
End Class

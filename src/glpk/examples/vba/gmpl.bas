Attribute VB_Name = "gmpl"
' gmpl.bas
'
' Copyright (C) 2017, Heinrich Schuchardt <xypron.glpk@gmx.de>.
'
' This program is free software: you can redistribute it and/or modify
' it under the terms of the GNU General Public License as published by
' the Free Software Foundation, either version 3 of the License, or
' (at your option) any later version.
'
' This program is distributed in the hope that it will be useful,
' but WITHOUT ANY WARRANTY; without even the implied warranty of
' MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
' GNU General Public License for more details.
'
' You should have received a copy of the GNU General Public License
' along with this program.  If not, see <http://www.gnu.org/licenses/>.
' You should have received a copy of the GNU General Public License
' along with GLPK. If not, see <http://www.gnu.org/licenses/>.

Option Explicit

' Load a MathProg model file and solve the problem.
' Usage of a callback routine is demonstrated.
Public Sub gmpl_main(fname As String)
  Dim lp As LongPtr
  Dim tran As LongPtr
  Dim iocp As glp_iocp
  Dim name() As Byte
  
  Dim ret As Long
  
  ' Register error hook function
  glp_error_hook AddressOf error_hook
  
  ' Register terminal hook function
  glp_term_hook AddressOf term_hook
  
  ' Create problem object
  lp = glp_create_prob()
  
  ' Create MathProg translator workspace
  tran = glp_mpl_alloc_wksp()
  
  ' Read the MathProg model
  name = str2bytes(fname)
  ret = glp_mpl_read_model(tran, name(0), GLP_OFF)
  If ret <> 0 Then
      glp_mpl_free_wksp (tran)
    glp_delete_prob (lp)
    Err.Raise 1004, "Model file not valid: " & fname
  End If
  
  ' Generate the model
  ret = glp_mpl_generate(tran, 0)
  If ret <> 0 Then
    glp_mpl_free_wksp (tran)
    glp_delete_prob (lp)
    Err.Raise 1004, "Cannot generate model: " & fname
  End If
  
  ' Build the model
  glp_mpl_build_prob tran, lp

  ' Set solver parameters
  glp_init_iocp iocp
  iocp.presolve = GLP_ON
  iocp.cb_func = glpk_addressof(AddressOf gmpl_cb)
  
  ' Solve the model
  ret = glp_intopt(lp, iocp)

  ' Postsolve the model
  If ret = 0 Then
    ret = glp_mpl_postsolve(tran, lp, GLP_MIP)
  End If
  
  ' Free memory
    glp_mpl_free_wksp (tran)
    glp_delete_prob lp
  
  ' Deregister error hook function
  glp_error_hook 0, 0

  Exit Sub

error0:
  Debug.Print Format(Err.Number, "0 - "); Err.Description

  If Err.Number <> GLPK_LIB_ERROR Then
    On Error GoTo 0
    Resume
  End If
End Sub

' Callback routine.
'
' @param tree branch and bound tree
' @param info variable passed as cb_info to glp_intopt
Public Sub gmpl_cb(ByVal tree As LongPtr, ByRef info As Variant)
  Dim reason As Long
  
  reason = glp_ios_reason(tree)
  If reason = GLP_IBINGO Then
     Debug.Print "Better solution found"
  End If
End Sub

Attribute VB_Name = "errdemo"
' errdemo.bas
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

Sub errdemo()
  lp False
  lp True
  lp False
  lp True
End Sub

Private Sub lp(force_error As Boolean)
  Dim lp As LongPtr
  Dim smcp As glp_smcp
  Dim ret As Long
  Dim name() As Byte
  Dim ind(2) As Long
  Dim val(2) As Double
  
  On Error GoTo error0
  
  ' Register error hook function
  glp_error_hook AddressOf error_hook
  
  ' Register terminal hook function
  glp_term_hook AddressOf term_hook
  
  ' Create problem
  lp = glp_create_prob()
  name = str2bytes("Linear Problem")
  glp_set_prob_name lp, name(0)
  
  If force_error Then
    glp_add_cols lp, -1
  End If
  
  ' Create columns
  glp_add_cols lp, 1
  name = str2bytes("x1")
  glp_set_col_name lp, 1, name(0)
  glp_set_col_kind lp, 1, GLP_CV
  glp_set_col_bnds lp, 1, GLP_UP, 0#, 1#
  
  ' Define objective
  name = str2bytes("obj")
  glp_set_obj_name lp, name(0)
  glp_set_obj_dir lp, GLP_MAX
  glp_set_obj_coef lp, 1, 1

  ' Solve model
  ret = glp_init_smcp(smcp)
  ret = glp_simplex(lp, smcp)
  
  'Retrieve solution
  If ret = 0 Then
    write_lp_solution (lp)
  End If
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

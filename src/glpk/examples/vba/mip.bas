Attribute VB_Name = "mip"
' mip.bas
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

' Maximize z =  17 * x1 + 12* x2
' subject to
'   10 x1 + 7 x2 <= 40
'      x1 +   x2 <=  5
' where,
'   0.0 <= x1  integer
'   0.0 <= x2  integer
Sub mip()
  Dim lp As LongPtr
  Dim iocp As glp_iocp
  Dim ind(2) As Long
  Dim val(2) As Double
  Dim ret As Integer
  Dim name() As Byte

  On Error GoTo error0
  
  ' Register error hook function
  glp_error_hook AddressOf error_hook
  
  ' Register terminal hook function
  glp_term_hook AddressOf term_hook
  
  ' Create problem
  lp = glp_create_prob()
  name = str2bytes("Mixed Integer Problem")
  glp_set_prob_name lp, name(0)

  ' Define columns
  glp_add_cols lp, 2
  name = str2bytes("x1")
  glp_set_col_name lp, 1, name(0)
  glp_set_col_kind lp, 1, GLP_IV
  glp_set_col_bnds lp, 1, GLP_LO, 0#, 0#
  name = str2bytes("x2")
  glp_set_col_name lp, 2, name(0)
  glp_set_col_kind lp, 2, GLP_IV
  glp_set_col_bnds lp, 2, GLP_LO, 0#, 0#

  ' Create constraints
  glp_add_rows lp, 2
  
  name = str2bytes("c1")
  glp_set_row_name lp, 1, name(0)
  glp_set_row_bnds lp, 1, GLP_UP, 0, 40#
  ind(1) = 1
  ind(2) = 2
  val(1) = 10#
  val(2) = 7#
  glp_set_mat_row lp, 1, 2, ind(0), val(0)

  name = str2bytes("c2")
  glp_set_row_name lp, 2, name(0)
  glp_set_row_bnds lp, 2, GLP_UP, 0, 5#
  ind(1) = 1
  ind(2) = 2
  val(1) = 1#
  val(2) = 1#
  glp_set_mat_row lp, 2, 2, ind(0), val(0)

  ' Define objective
  name = str2bytes("obj")
  glp_set_obj_name lp, name(0)
  glp_set_obj_dir lp, GLP_MAX
  glp_set_obj_coef lp, 0, 0#
  glp_set_obj_coef lp, 1, 17#
  glp_set_obj_coef lp, 2, 12#

  ' Write model to file
  ' name = str2bytes("c:\temp\mip.lp")
  ' ret = glp_write_lp(lp, 0, name(0))

  ' Solve model
  glp_init_iocp iocp
  iocp.presolve = GLP_ON
  ret = glp_intopt(lp, iocp)
    
  ' Retrieve solution
  If ret = 0 Then
    write_mip_solution (lp)
  Else
    Debug.Print "The problem could not be solved"
  End If

  ' Free memory
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

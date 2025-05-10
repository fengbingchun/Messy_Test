
%csmethodmodifiers AMD_aat(Int n, const Int Ap[], const Int Ai[], Int Len[], Int Tp[], double Info[]) "
/**
 */
public";

%csmethodmodifiers bigmul(int n, int m, unsigned short x[], unsigned short y[]) "
/**
 * bigmul - multiply unsigned integer numbers of arbitrary precision .
 * <p>SYNOPSIS</p>
 * <p>#include \"bignum.h\" void bigmul(int n, int m, unsigned short x[], unsigned short y[]);</p>
 * <p>DESCRIPTION</p>
 * <p>The routine bigmul multiplies unsigned integer numbers of arbitrary precision.</p>
 * <p>n is the number of digits of multiplicand, n &gt;= 1;</p>
 * <p>m is the number of digits of multiplier, m &gt;= 1;</p>
 * <p>x is an array containing digits of the multiplicand in elements x[m], x[m+1], ..., x[n+m-1]. Contents of x[0], x[1], ..., x[m-1] are ignored on entry.</p>
 * <p>y is an array containing digits of the multiplier in elements y[0], y[1], ..., y[m-1].</p>
 * <p>On exit digits of the product are stored in elements x[0], x[1], ..., x[n+m-1]. The array y is not changed. </p>
 */
public";

%csmethodmodifiers bigdiv(int n, int m, unsigned short x[], unsigned short y[]) "
/**
 * bigdiv - divide unsigned integer numbers of arbitrary precision .
 * <p>SYNOPSIS</p>
 * <p>#include \"bignum.h\" void bigdiv(int n, int m, unsigned short x[], unsigned short y[]);</p>
 * <p>DESCRIPTION</p>
 * <p>The routine bigdiv divides one unsigned integer number of arbitrary precision by another with the algorithm described in [1].</p>
 * <p>n is the difference between the number of digits of dividend and the number of digits of divisor, n &gt;= 0.</p>
 * <p>m is the number of digits of divisor, m &gt;= 1.</p>
 * <p>x is an array containing digits of the dividend in elements x[0], x[1], ..., x[n+m-1].</p>
 * <p>y is an array containing digits of the divisor in elements y[0], y[1], ..., y[m-1]. The highest digit y[m-1] must be non-zero.</p>
 * <p>On exit n+1 digits of the quotient are stored in elements x[m], x[m+1], ..., x[n+m], and m digits of the remainder are stored in elements x[0], x[1], ..., x[m-1]. The array y is changed but then restored.</p>
 * <p>REFERENCES</p>
 * <p>
D. Knuth. The Art of Computer Programming. Vol. 2: Seminumerical Algorithms. Stanford University, 1969. 
</p>
 */
public";

%csmethodmodifiers sub(struct csa *csa, int ct, int table[], int level, int weight, int l_weight) "
/**
 */
public";

%csmethodmodifiers wclique(int n_, const int w[], const unsigned char a_[], int ind[]) "
/**
 */
public";

%csmethodmodifiers AMD_1(Int n, const Int Ap[], const Int Ai[], Int P[], Int Pinv[], Int Len[], Int slen, Int S[], double Control[], double Info[]) "
/**
 */
public";

%csmethodmodifiers set_penalty(struct csa *csa, double tol, double tol1) "
/**
 */
public";

%csmethodmodifiers check_feas(struct csa *csa, int phase, double tol, double tol1) "
/**
 */
public";

%csmethodmodifiers adjust_penalty(struct csa *csa, double tol, double tol1) "
/**
 */
public";

%csmethodmodifiers choose_pivot(struct csa *csa) "
/**
 */
public";

%csmethodmodifiers sum_infeas(SPXLP *lp, const double beta[]) "
/**
 */
public";

%csmethodmodifiers display(struct csa *csa, int spec) "
/**
 */
public";

%csmethodmodifiers primal_simplex(struct csa *csa) "
/**
 */
public";

%csmethodmodifiers spx_primal(glp_prob *P, const glp_smcp *parm) "
/**
 */
public";

%csmethodmodifiers xdlopen(const char *module) "
/**
 */
public";

%csmethodmodifiers xdlsym(void *h, const char *symbol) "
/**
 */
public";

%csmethodmodifiers xdlclose(void *h) "
/**
 */
public";
%csmethodmodifiers fn_gmtime(MPL *mpl) "
/**
 */
public";

%csmethodmodifiers error1(MPL *mpl, const char *str, const char *s, const char *fmt, const char *f, const char *msg) "
/**
 */
public";

%csmethodmodifiers fn_str2time(MPL *mpl, const char *str, const char *fmt) "
/**
 */
public";

%csmethodmodifiers error2(MPL *mpl, const char *fmt, const char *f, const char *msg) "
/**
 */
public";

%csmethodmodifiers weekday(int j) "
/**
 */
public";

%csmethodmodifiers firstday(int year) "
/**
 */
public";

%csmethodmodifiers fn_time2str(MPL *mpl, char *str, double t, const char *fmt) "
/**
 */
public";

%csmethodmodifiers glp_puts(const char *s) "
/**
 * glp_puts - write string on terminal .
 * <p>SYNOPSIS</p>
 * <p>void glp_puts(const char *s);</p>
 * <p>The routine glp_puts writes the string s on the terminal. </p>
 */
public";

%csmethodmodifiers glp_printf(const char *fmt,...) "
/**
 * glp_printf - write formatted output on terminal .
 * <p>SYNOPSIS</p>
 * <p>void glp_printf(const char *fmt, ...);</p>
 * <p>DESCRIPTION</p>
 * <p>The routine glp_printf uses the format control string fmt to format its parameters and writes the formatted output on the terminal. </p>
 */
public";

%csmethodmodifiers glp_vprintf(const char *fmt, va_list arg) "
/**
 * glp_vprintf - write formatted output on terminal .
 * <p>SYNOPSIS</p>
 * <p>void glp_vprintf(const char *fmt, va_list arg);</p>
 * <p>DESCRIPTION</p>
 * <p>The routine glp_vprintf uses the format control string fmt to format its parameters specified by the list arg and writes the formatted output on the terminal. </p>
 */
public";

%csmethodmodifiers glp_term_out(int flag) "
/**
 * glp_term_out - enable/disable terminal output .
 * <p>SYNOPSIS</p>
 * <p>int glp_term_out(int flag);</p>
 * <p>DESCRIPTION</p>
 * <p>Depending on the parameter flag the routine glp_term_out enables or disables terminal output performed by glpk routines:</p>
 * <p>GLP_ON - enable terminal output; GLP_OFF - disable terminal output.</p>
 * <p>RETURNS</p>
 * <p>The routine glp_term_out returns the previous value of the terminal output flag. </p>
 */
public";

%csmethodmodifiers glp_term_hook(int(*func)(void *info, const char *s), void *info) "
/**
 * glp_term_hook - install hook to intercept terminal output .
 * <p>SYNOPSIS</p>
 * <p>void glp_term_hook(int (*func)(void *info, const char *s), void *info);</p>
 * <p>DESCRIPTION</p>
 * <p>The routine glp_term_hook installs a user-defined hook routine to intercept all terminal output performed by glpk routines.</p>
 * <p>This feature can be used to redirect the terminal output to other destination, for example to a file or a text window.</p>
 * <p>The parameter func specifies the user-defined hook routine. It is called from an internal printing routine, which passes to it two parameters: info and s. The parameter info is a transit pointer, specified in the corresponding call to the routine glp_term_hook; it may be used to pass some information to the hook routine. The parameter s is a pointer to the null terminated character string, which is intended to be written to the terminal. If the hook routine returns zero, the printing routine writes the string s to the terminal in a usual way; otherwise, if the hook routine returns non-zero, no terminal output is performed.</p>
 * <p>To uninstall the hook routine the parameters func and info should be specified as NULL. </p>
 */
public";

%csmethodmodifiers glp_open_tee(const char *name) "
/**
 * glp_open_tee - start copying terminal output to text file .
 * <p>SYNOPSIS</p>
 * <p>int glp_open_tee(const char *name);</p>
 * <p>DESCRIPTION</p>
 * <p>The routine glp_open_tee starts copying all the terminal output to an output text file, whose name is specified by the character string name.</p>
 * <p>RETURNS</p>
 * <p>0 - operation successful 1 - copying terminal output is already active 2 - unable to create output file </p>
 */
public";

%csmethodmodifiers glp_close_tee(void) "
/**
 * glp_close_tee - stop copying terminal output to text file .
 * <p>SYNOPSIS</p>
 * <p>int glp_close_tee(void);</p>
 * <p>DESCRIPTION</p>
 * <p>The routine glp_close_tee stops copying the terminal output to the output text file previously open by the routine glp_open_tee closing that file.</p>
 * <p>RETURNS</p>
 * <p>0 - operation successful 1 - copying terminal output was not started </p>
 */
public";

%csmethodmodifiers gen_cut(glp_tree *tree, struct worka *worka, int j) "
/**
 */
public";

%csmethodmodifiers fcmp(const void *p1, const void *p2) "
/**
 */
public";

%csmethodmodifiers ios_gmi_gen(glp_tree *tree) "
/**
 */
public";

%csmethodmodifiers strtrim(char *str) "
/**
 * strtrim - remove trailing spaces from character string .
 * <p>SYNOPSIS</p>
 * <p>#include \"misc.h\" char *strtrim(char *str);</p>
 * <p>DESCRIPTION</p>
 * <p>The routine strtrim removes trailing spaces from the character string str.</p>
 * <p>RETURNS</p>
 * <p>The routine returns a pointer to the character string.</p>
 * <p>EXAMPLES</p>
 * <p>strtrim(\"Errare humanum est   \") => \"Errare humanum est\"</p>
 * <p>strtrim(\"      \") => \"\" </p>
 */
public";

%csmethodmodifiers create_prob(glp_prob *lp) "
/**
 * glp_create_prob - create problem object .
 * <p>SYNOPSIS</p>
 * <p>glp_prob *glp_create_prob(void);</p>
 * <p>DESCRIPTION</p>
 * <p>The routine glp_create_prob creates a new problem object, which is initially \"empty\", i.e. has no rows and columns.</p>
 * <p>RETURNS</p>
 * <p>The routine returns a pointer to the object created, which should be used in any subsequent operations on this object. </p>
 */
public";

%csmethodmodifiers glp_create_prob(void) "
/**
 */
public";

%csmethodmodifiers glp_set_prob_name(glp_prob *lp, const char *name) "
/**
 * glp_set_prob_name - assign (change) problem name .
 * <p>SYNOPSIS</p>
 * <p>void glp_set_prob_name(glp_prob *lp, const char *name);</p>
 * <p>DESCRIPTION</p>
 * <p>The routine glp_set_prob_name assigns a given symbolic name (1 up to 255 characters) to the specified problem object.</p>
 * <p>If the parameter name is NULL or empty string, the routine erases an existing symbolic name of the problem object. </p>
 */
public";

%csmethodmodifiers glp_set_obj_name(glp_prob *lp, const char *name) "
/**
 * glp_set_obj_name - assign (change) objective function name .
 * <p>SYNOPSIS</p>
 * <p>void glp_set_obj_name(glp_prob *lp, const char *name);</p>
 * <p>DESCRIPTION</p>
 * <p>The routine glp_set_obj_name assigns a given symbolic name (1 up to 255 characters) to the objective function of the specified problem object.</p>
 * <p>If the parameter name is NULL or empty string, the routine erases an existing name of the objective function. </p>
 */
public";

%csmethodmodifiers glp_set_obj_dir(glp_prob *lp, int dir) "
/**
 * glp_set_obj_dir - set (change) optimization direction flag .
 * <p>SYNOPSIS</p>
 * <p>void glp_set_obj_dir(glp_prob *lp, int dir);</p>
 * <p>DESCRIPTION</p>
 * <p>The routine glp_set_obj_dir sets (changes) optimization direction flag (i.e. \"sense\" of the objective function) as specified by the parameter dir:</p>
 * <p>GLP_MIN - minimization; GLP_MAX - maximization. </p>
 */
public";

%csmethodmodifiers glp_add_rows(glp_prob *lp, int nrs) "
/**
 * glp_add_rows - add new rows to problem object .
 * <p>SYNOPSIS</p>
 * <p>int glp_add_rows(glp_prob *lp, int nrs);</p>
 * <p>DESCRIPTION</p>
 * <p>The routine glp_add_rows adds nrs rows (constraints) to the specified problem object. New rows are always added to the end of the row list, so the ordinal numbers of existing rows remain unchanged.</p>
 * <p>Being added each new row is initially free (unbounded) and has empty list of the constraint coefficients.</p>
 * <p>RETURNS</p>
 * <p>The routine glp_add_rows returns the ordinal number of the first new row added to the problem object. </p>
 */
public";

%csmethodmodifiers glp_add_cols(glp_prob *lp, int ncs) "
/**
 * glp_add_cols - add new columns to problem object .
 * <p>SYNOPSIS</p>
 * <p>int glp_add_cols(glp_prob *lp, int ncs);</p>
 * <p>DESCRIPTION</p>
 * <p>The routine glp_add_cols adds ncs columns (structural variables) to the specified problem object. New columns are always added to the end of the column list, so the ordinal numbers of existing columns remain unchanged.</p>
 * <p>Being added each new column is initially fixed at zero and has empty list of the constraint coefficients.</p>
 * <p>RETURNS</p>
 * <p>The routine glp_add_cols returns the ordinal number of the first new column added to the problem object. </p>
 */
public";

%csmethodmodifiers glp_set_row_name(glp_prob *lp, int i, const char *name) "
/**
 * glp_set_row_name - assign (change) row name .
 * <p>SYNOPSIS</p>
 * <p>void glp_set_row_name(glp_prob *lp, int i, const char *name);</p>
 * <p>DESCRIPTION</p>
 * <p>The routine glp_set_row_name assigns a given symbolic name (1 up to 255 characters) to i-th row (auxiliary variable) of the specified problem object.</p>
 * <p>If the parameter name is NULL or empty string, the routine erases an existing name of i-th row. </p>
 */
public";

%csmethodmodifiers glp_set_col_name(glp_prob *lp, int j, const char *name) "
/**
 * glp_set_col_name - assign (change) column name .
 * <p>SYNOPSIS</p>
 * <p>void glp_set_col_name(glp_prob *lp, int j, const char *name);</p>
 * <p>DESCRIPTION</p>
 * <p>The routine glp_set_col_name assigns a given symbolic name (1 up to 255 characters) to j-th column (structural variable) of the specified problem object.</p>
 * <p>If the parameter name is NULL or empty string, the routine erases an existing name of j-th column. </p>
 */
public";

%csmethodmodifiers glp_set_row_bnds(glp_prob *lp, int i, int type, double lb, double ub) "
/**
 * glp_set_row_bnds - set (change) row bounds .
 * <p>SYNOPSIS</p>
 * <p>void glp_set_row_bnds(glp_prob *lp, int i, int type, double lb, double ub);</p>
 * <p>DESCRIPTION</p>
 * <p>The routine glp_set_row_bnds sets (changes) the type and bounds of i-th row (auxiliary variable) of the specified problem object.</p>
 * <p>Parameters type, lb, and ub specify the type, lower bound, and upper bound, respectively, as follows:</p>
 * <p>Type Bounds Comments 
</p>
 * <p>GLP_FR -inf &lt; x &lt; +inf Free variable GLP_LO lb &lt;= x &lt; +inf Variable with lower bound GLP_UP -inf &lt; x &lt;= ub Variable with upper bound GLP_DB lb &lt;= x &lt;= ub Double-bounded variable GLP_FX x = lb Fixed variable</p>
 * <p>where x is the auxiliary variable associated with i-th row.</p>
 * <p>If the row has no lower bound, the parameter lb is ignored. If the row has no upper bound, the parameter ub is ignored. If the row is an equality constraint (i.e. the corresponding auxiliary variable is of fixed type), only the parameter lb is used while the parameter ub is ignored. </p>
 */
public";

%csmethodmodifiers glp_set_col_bnds(glp_prob *lp, int j, int type, double lb, double ub) "
/**
 * glp_set_col_bnds - set (change) column bounds .
 * <p>SYNOPSIS</p>
 * <p>void glp_set_col_bnds(glp_prob *lp, int j, int type, double lb, double ub);</p>
 * <p>DESCRIPTION</p>
 * <p>The routine glp_set_col_bnds sets (changes) the type and bounds of j-th column (structural variable) of the specified problem object.</p>
 * <p>Parameters type, lb, and ub specify the type, lower bound, and upper bound, respectively, as follows:</p>
 * <p>Type Bounds Comments 
</p>
 * <p>GLP_FR -inf &lt; x &lt; +inf Free variable GLP_LO lb &lt;= x &lt; +inf Variable with lower bound GLP_UP -inf &lt; x &lt;= ub Variable with upper bound GLP_DB lb &lt;= x &lt;= ub Double-bounded variable GLP_FX x = lb Fixed variable</p>
 * <p>where x is the structural variable associated with j-th column.</p>
 * <p>If the column has no lower bound, the parameter lb is ignored. If the column has no upper bound, the parameter ub is ignored. If the column is of fixed type, only the parameter lb is used while the parameter ub is ignored. </p>
 */
public";

%csmethodmodifiers glp_set_obj_coef(glp_prob *lp, int j, double coef) "
/**
 * glp_set_obj_coef - set (change) obj. .
 * <p>coefficient or constant term</p>
 * <p>SYNOPSIS</p>
 * <p>void glp_set_obj_coef(glp_prob *lp, int j, double coef);</p>
 * <p>DESCRIPTION</p>
 * <p>The routine glp_set_obj_coef sets (changes) objective coefficient at j-th column (structural variable) of the specified problem object.</p>
 * <p>If the parameter j is 0, the routine sets (changes) the constant term (\"shift\") of the objective function. </p>
 */
public";

%csmethodmodifiers glp_set_mat_row(glp_prob *lp, int i, int len, const int ind[], const double val[]) "
/**
 * glp_set_mat_row - set (replace) row of the constraint matrix .
 * <p>SYNOPSIS</p>
 * <p>void glp_set_mat_row(glp_prob *lp, int i, int len, const int ind[], const double val[]);</p>
 * <p>DESCRIPTION</p>
 * <p>The routine glp_set_mat_row stores (replaces) the contents of i-th row of the constraint matrix of the specified problem object.</p>
 * <p>Column indices and numeric values of new row elements must be placed in locations ind[1], ..., ind[len] and val[1], ..., val[len], where 0 &lt;= len &lt;= n is the new length of i-th row, n is the current number of columns in the problem object. Elements with identical column indices are not allowed. Zero elements are allowed, but they are not stored in the constraint matrix.</p>
 * <p>If the parameter len is zero, the parameters ind and/or val can be specified as NULL. </p>
 */
public";

%csmethodmodifiers glp_set_mat_col(glp_prob *lp, int j, int len, const int ind[], const double val[]) "
/**
 * glp_set_mat_col - set (replace) column of the constraint matrix .
 * <p>SYNOPSIS</p>
 * <p>void glp_set_mat_col(glp_prob *lp, int j, int len, const int ind[], const double val[]);</p>
 * <p>DESCRIPTION</p>
 * <p>The routine glp_set_mat_col stores (replaces) the contents of j-th column of the constraint matrix of the specified problem object.</p>
 * <p>Row indices and numeric values of new column elements must be placed in locations ind[1], ..., ind[len] and val[1], ..., val[len], where 0 &lt;= len &lt;= m is the new length of j-th column, m is the current number of rows in the problem object. Elements with identical column indices are not allowed. Zero elements are allowed, but they are not stored in the constraint matrix.</p>
 * <p>If the parameter len is zero, the parameters ind and/or val can be specified as NULL. </p>
 */
public";

%csmethodmodifiers glp_load_matrix(glp_prob *lp, int ne, const int ia[], const int ja[], const double ar[]) "
/**
 * glp_load_matrix - load (replace) the whole constraint matrix .
 * <p>SYNOPSIS</p>
 * <p>void glp_load_matrix(glp_prob *lp, int ne, const int ia[], const int ja[], const double ar[]);</p>
 * <p>DESCRIPTION</p>
 * <p>The routine glp_load_matrix loads the constraint matrix passed in the arrays ia, ja, and ar into the specified problem object. Before loading the current contents of the constraint matrix is destroyed.</p>
 * <p>Constraint coefficients (elements of the constraint matrix) must be specified as triplets (ia[k], ja[k], ar[k]) for k = 1, ..., ne, where ia[k] is the row index, ja[k] is the column index, ar[k] is a numeric value of corresponding constraint coefficient. The parameter ne specifies the total number of (non-zero) elements in the matrix to be loaded. Coefficients with identical indices are not allowed. Zero coefficients are allowed, however, they are not stored in the constraint matrix.</p>
 * <p>If the parameter ne is zero, the parameters ia, ja, and ar can be specified as NULL. </p>
 */
public";

%csmethodmodifiers glp_check_dup(int m, int n, int ne, const int ia[], const int ja[]) "
/**
 * glp_check_dup - check for duplicate elements in sparse matrix .
 * <p>SYNOPSIS</p>
 * <p>int glp_check_dup(int m, int n, int ne, const int ia[], const int ja[]);</p>
 * <p>DESCRIPTION</p>
 * <p>The routine glp_check_dup checks for duplicate elements (that is, elements with identical indices) in a sparse matrix specified in the coordinate format.</p>
 * <p>The parameters m and n specifies, respectively, the number of rows and columns in the matrix, m &gt;= 0, n &gt;= 0.</p>
 * <p>The parameter ne specifies the number of (structurally) non-zero elements in the matrix, ne &gt;= 0.</p>
 * <p>Elements of the matrix are specified as doublets (ia[k],ja[k]) for k = 1,...,ne, where ia[k] is a row index, ja[k] is a column index.</p>
 * <p>The routine glp_check_dup can be used prior to a call to the routine glp_load_matrix to check that the constraint matrix to be loaded has no duplicate elements.</p>
 * <p>RETURNS</p>
 * <p>The routine glp_check_dup returns one of the following values:</p>
 * <p>0 - the matrix has no duplicate elements;</p>
 * <p>-k - indices ia[k] or/and ja[k] are out of range;</p>
 * <p>+k - element (ia[k],ja[k]) is duplicate. </p>
 */
public";

%csmethodmodifiers glp_sort_matrix(glp_prob *P) "
/**
 * glp_sort_matrix - sort elements of the constraint matrix .
 * <p>SYNOPSIS</p>
 * <p>void glp_sort_matrix(glp_prob *P);</p>
 * <p>DESCRIPTION</p>
 * <p>The routine glp_sort_matrix sorts elements of the constraint matrix rebuilding its row and column linked lists. On exit from the routine the constraint matrix is not changed, however, elements in the row linked lists become ordered by ascending column indices, and the elements in the column linked lists become ordered by ascending row indices. </p>
 */
public";

%csmethodmodifiers glp_del_rows(glp_prob *lp, int nrs, const int num[]) "
/**
 * glp_del_rows - delete rows from problem object .
 * <p>SYNOPSIS</p>
 * <p>void glp_del_rows(glp_prob *lp, int nrs, const int num[]);</p>
 * <p>DESCRIPTION</p>
 * <p>The routine glp_del_rows deletes rows from the specified problem object. Ordinal numbers of rows to be deleted should be placed in locations num[1], ..., num[nrs], where nrs &gt; 0.</p>
 * <p>Note that deleting rows involves changing ordinal numbers of other rows remaining in the problem object. New ordinal numbers of the remaining rows are assigned under the assumption that the original order of rows is not changed. </p>
 */
public";

%csmethodmodifiers glp_del_cols(glp_prob *lp, int ncs, const int num[]) "
/**
 * glp_del_cols - delete columns from problem object .
 * <p>SYNOPSIS</p>
 * <p>void glp_del_cols(glp_prob *lp, int ncs, const int num[]);</p>
 * <p>DESCRIPTION</p>
 * <p>The routine glp_del_cols deletes columns from the specified problem object. Ordinal numbers of columns to be deleted should be placed in locations num[1], ..., num[ncs], where ncs &gt; 0.</p>
 * <p>Note that deleting columns involves changing ordinal numbers of other columns remaining in the problem object. New ordinal numbers of the remaining columns are assigned under the assumption that the original order of columns is not changed. </p>
 */
public";

%csmethodmodifiers glp_copy_prob(glp_prob *dest, glp_prob *prob, int names) "
/**
 * glp_copy_prob - copy problem object content .
 * <p>SYNOPSIS</p>
 * <p>void glp_copy_prob(glp_prob *dest, glp_prob *prob, int names);</p>
 * <p>DESCRIPTION</p>
 * <p>The routine glp_copy_prob copies the content of the problem object prob to the problem object dest.</p>
 * <p>The parameter names is a flag. If it is non-zero, the routine also copies all symbolic names; otherwise, if it is zero, symbolic names are not copied. </p>
 */
public";

%csmethodmodifiers delete_prob(glp_prob *lp) "
/**
 * glp_erase_prob - erase problem object content .
 * <p>glp_delete_prob - delete problem object</p>
 * <p>SYNOPSIS</p>
 * <p>void glp_erase_prob(glp_prob *lp);</p>
 * <p>DESCRIPTION</p>
 * <p>The routine glp_erase_prob erases the content of the specified problem object. The effect of this operation is the same as if the problem object would be deleted with the routine glp_delete_prob and then created anew with the routine glp_create_prob, with exception that the handle (pointer) to the problem object remains valid.</p>
 * <p>SYNOPSIS</p>
 * <p>void glp_delete_prob(glp_prob *lp);</p>
 * <p>DESCRIPTION</p>
 * <p>The routine glp_delete_prob deletes the specified problem object and frees all the memory allocated to it. </p>
 */
public";

%csmethodmodifiers glp_erase_prob(glp_prob *lp) "
/**
 */
public";

%csmethodmodifiers glp_delete_prob(glp_prob *lp) "
/**
 */
public";
%csmethodmodifiers spy_chuzr_sel(SPXLP *lp, const double beta[], double tol, double tol1, int list[]) "
/**
 */
public";

%csmethodmodifiers spy_chuzr_std(SPXLP *lp, const double beta[], int num, const int list[]) "
/**
 */
public";

%csmethodmodifiers spy_alloc_se(SPXLP *lp, SPYSE *se) "
/**
 */
public";

%csmethodmodifiers spy_reset_refsp(SPXLP *lp, SPYSE *se) "
/**
 */
public";

%csmethodmodifiers spy_eval_gamma_i(SPXLP *lp, SPYSE *se, int i) "
/**
 */
public";

%csmethodmodifiers spy_chuzr_pse(SPXLP *lp, SPYSE *se, const double beta[], int num, const int list[]) "
/**
 */
public";

%csmethodmodifiers spy_update_gamma(SPXLP *lp, SPYSE *se, int p, int q, const double trow[], const double tcol[]) "
/**
 */
public";

%csmethodmodifiers spy_free_se(SPXLP *lp, SPYSE *se) "
/**
 */
public";

%csmethodmodifiers spx_init_lp(SPXLP *lp, glp_prob *P, int excl) "
/**
 */
public";

%csmethodmodifiers spx_alloc_lp(SPXLP *lp) "
/**
 */
public";

%csmethodmodifiers spx_build_lp(SPXLP *lp, glp_prob *P, int excl, int shift, int map[]) "
/**
 */
public";

%csmethodmodifiers spx_build_basis(SPXLP *lp, glp_prob *P, const int map[]) "
/**
 */
public";

%csmethodmodifiers spx_store_basis(SPXLP *lp, glp_prob *P, const int map[], int daeh[]) "
/**
 */
public";

%csmethodmodifiers spx_store_sol(SPXLP *lp, glp_prob *P, int shift, const int map[], const int daeh[], const double beta[], const double pi[], const double d[]) "
/**
 */
public";

%csmethodmodifiers spx_free_lp(SPXLP *lp) "
/**
 */
public";

%csmethodmodifiers AMD_defaults(double Control[]) "
/**
 */
public";

%csmethodmodifiers lufint_create(void) "
/**
 */
public";

%csmethodmodifiers lufint_factorize(LUFINT *fi, int n, int(*col)(void *info, int j, int ind[], double val[]), void *info) "
/**
 */
public";

%csmethodmodifiers lufint_delete(LUFINT *fi) "
/**
 */
public";

%csmethodmodifiers ios_proxy_heur(glp_tree *T) "
/**
 */
public";

%csmethodmodifiers glp_ios_reason(glp_tree *tree) "
/**
 * glp_ios_reason - determine reason for calling the callback routine .
 * <p>SYNOPSIS</p>
 * <p>glp_ios_reason(glp_tree *tree);</p>
 * <p>RETURNS</p>
 * <p>The routine glp_ios_reason returns a code, which indicates why the user-defined callback routine is being called. </p>
 */
public";

%csmethodmodifiers glp_ios_get_prob(glp_tree *tree) "
/**
 * glp_ios_get_prob - access the problem object .
 * <p>SYNOPSIS</p>
 * <p>glp_prob *glp_ios_get_prob(glp_tree *tree);</p>
 * <p>DESCRIPTION</p>
 * <p>The routine glp_ios_get_prob can be called from the user-defined callback routine to access the problem object, which is used by the MIP solver. It is the original problem object passed to the routine glp_intopt if the MIP presolver is not used; otherwise it is an internal problem object built by the presolver. If the current subproblem exists, LP segment of the problem object corresponds to its LP relaxation.</p>
 * <p>RETURNS</p>
 * <p>The routine glp_ios_get_prob returns a pointer to the problem object used by the MIP solver. </p>
 */
public";

%csmethodmodifiers glp_ios_tree_size(glp_tree *tree, int *a_cnt, int *n_cnt, int *t_cnt) "
/**
 * glp_ios_tree_size - determine size of the branch-and-bound tree .
 * <p>SYNOPSIS</p>
 * <p>void glp_ios_tree_size(glp_tree *tree, int *a_cnt, int *n_cnt, int *t_cnt);</p>
 * <p>DESCRIPTION</p>
 * <p>The routine glp_ios_tree_size stores the following three counts which characterize the current size of the branch-and-bound tree:</p>
 * <p>a_cnt is the current number of active nodes, i.e. the current size of the active list;</p>
 * <p>n_cnt is the current number of all (active and inactive) nodes;</p>
 * <p>t_cnt is the total number of nodes including those which have been already removed from the tree. This count is increased whenever a new node appears in the tree and never decreased.</p>
 * <p>If some of the parameters a_cnt, n_cnt, t_cnt is a null pointer, the corresponding count is not stored. </p>
 */
public";

%csmethodmodifiers glp_ios_curr_node(glp_tree *tree) "
/**
 * glp_ios_curr_node - determine current active subproblem .
 * <p>SYNOPSIS</p>
 * <p>int glp_ios_curr_node(glp_tree *tree);</p>
 * <p>RETURNS</p>
 * <p>The routine glp_ios_curr_node returns the reference number of the current active subproblem. However, if the current subproblem does not exist, the routine returns zero. </p>
 */
public";

%csmethodmodifiers glp_ios_next_node(glp_tree *tree, int p) "
/**
 * glp_ios_next_node - determine next active subproblem .
 * <p>SYNOPSIS</p>
 * <p>int glp_ios_next_node(glp_tree *tree, int p);</p>
 * <p>RETURNS</p>
 * <p>If the parameter p is zero, the routine glp_ios_next_node returns the reference number of the first active subproblem. However, if the tree is empty, zero is returned.</p>
 * <p>If the parameter p is not zero, it must specify the reference number of some active subproblem, in which case the routine returns the reference number of the next active subproblem. However, if there is no next active subproblem in the list, zero is returned.</p>
 * <p>All subproblems in the active list are ordered chronologically, i.e. subproblem A precedes subproblem B if A was created before B. </p>
 */
public";

%csmethodmodifiers glp_ios_prev_node(glp_tree *tree, int p) "
/**
 * glp_ios_prev_node - determine previous active subproblem .
 * <p>SYNOPSIS</p>
 * <p>int glp_ios_prev_node(glp_tree *tree, int p);</p>
 * <p>RETURNS</p>
 * <p>If the parameter p is zero, the routine glp_ios_prev_node returns the reference number of the last active subproblem. However, if the tree is empty, zero is returned.</p>
 * <p>If the parameter p is not zero, it must specify the reference number of some active subproblem, in which case the routine returns the reference number of the previous active subproblem. However, if there is no previous active subproblem in the list, zero is returned.</p>
 * <p>All subproblems in the active list are ordered chronologically, i.e. subproblem A precedes subproblem B if A was created before B. </p>
 */
public";

%csmethodmodifiers glp_ios_up_node(glp_tree *tree, int p) "
/**
 * glp_ios_up_node - determine parent subproblem .
 * <p>SYNOPSIS</p>
 * <p>int glp_ios_up_node(glp_tree *tree, int p);</p>
 * <p>RETURNS</p>
 * <p>The parameter p must specify the reference number of some (active or inactive) subproblem, in which case the routine iet_get_up_node returns the reference number of its parent subproblem. However, if the specified subproblem is the root of the tree and, therefore, has no parent, the routine returns zero. </p>
 */
public";

%csmethodmodifiers glp_ios_node_level(glp_tree *tree, int p) "
/**
 * glp_ios_node_level - determine subproblem level .
 * <p>SYNOPSIS</p>
 * <p>int glp_ios_node_level(glp_tree *tree, int p);</p>
 * <p>RETURNS</p>
 * <p>The routine glp_ios_node_level returns the level of the subproblem, whose reference number is p, in the branch-and-bound tree. (The root subproblem has level 0, and the level of any other subproblem is the level of its parent plus one.) </p>
 */
public";

%csmethodmodifiers glp_ios_node_bound(glp_tree *tree, int p) "
/**
 * glp_ios_node_bound - determine subproblem local bound .
 * <p>SYNOPSIS</p>
 * <p>double glp_ios_node_bound(glp_tree *tree, int p);</p>
 * <p>RETURNS</p>
 * <p>The routine glp_ios_node_bound returns the local bound for (active or inactive) subproblem, whose reference number is p.</p>
 * <p>COMMENTS</p>
 * <p>The local bound for subproblem p is an lower (minimization) or upper (maximization) bound for integer optimal solution to this subproblem (not to the original problem). This bound is local in the sense that only subproblems in the subtree rooted at node p cannot have better integer feasible solutions.</p>
 * <p>On creating a subproblem (due to the branching step) its local bound is inherited from its parent and then may get only stronger (never weaker). For the root subproblem its local bound is initially set to -DBL_MAX (minimization) or +DBL_MAX (maximization) and then improved as the root LP relaxation has been solved.</p>
 * <p>Note that the local bound is not necessarily the optimal objective value to corresponding LP relaxation; it may be stronger. </p>
 */
public";

%csmethodmodifiers glp_ios_best_node(glp_tree *tree) "
/**
 * glp_ios_best_node - find active subproblem with best local bound .
 * <p>SYNOPSIS</p>
 * <p>int glp_ios_best_node(glp_tree *tree);</p>
 * <p>RETURNS</p>
 * <p>The routine glp_ios_best_node returns the reference number of the active subproblem, whose local bound is best (i.e. smallest in case of minimization or largest in case of maximization). However, if the tree is empty, the routine returns zero.</p>
 * <p>COMMENTS</p>
 * <p>The best local bound is an lower (minimization) or upper (maximization) bound for integer optimal solution to the original MIP problem. </p>
 */
public";

%csmethodmodifiers glp_ios_mip_gap(glp_tree *tree) "
/**
 * glp_ios_mip_gap - compute relative MIP gap .
 * <p>SYNOPSIS</p>
 * <p>double glp_ios_mip_gap(glp_tree *tree);</p>
 * <p>DESCRIPTION</p>
 * <p>The routine glp_ios_mip_gap computes the relative MIP gap with the following formula:</p>
 * <p>gap = |best_mip - best_bnd| / (|best_mip| + DBL_EPSILON),</p>
 * <p>where best_mip is the best integer feasible solution found so far, best_bnd is the best (global) bound. If no integer feasible solution has been found yet, gap is set to DBL_MAX.</p>
 * <p>RETURNS</p>
 * <p>The routine glp_ios_mip_gap returns the relative MIP gap. </p>
 */
public";

%csmethodmodifiers glp_ios_node_data(glp_tree *tree, int p) "
/**
 * glp_ios_node_data - access subproblem application-specific data .
 * <p>SYNOPSIS</p>
 * <p>void *glp_ios_node_data(glp_tree *tree, int p);</p>
 * <p>DESCRIPTION</p>
 * <p>The routine glp_ios_node_data allows the application accessing a memory block allocated for the subproblem (which may be active or inactive), whose reference number is p.</p>
 * <p>The size of the block is defined by the control parameter cb_size passed to the routine glp_intopt. The block is initialized by binary zeros on creating corresponding subproblem, and its contents is kept until the subproblem will be removed from the tree.</p>
 * <p>The application may use these memory blocks to store specific data for each subproblem.</p>
 * <p>RETURNS</p>
 * <p>The routine glp_ios_node_data returns a pointer to the memory block for the specified subproblem. Note that if cb_size = 0, the routine returns a null pointer. </p>
 */
public";

%csmethodmodifiers glp_ios_row_attr(glp_tree *tree, int i, glp_attr *attr) "
/**
 * glp_ios_row_attr - retrieve additional row attributes .
 * <p>SYNOPSIS</p>
 * <p>void glp_ios_row_attr(glp_tree *tree, int i, glp_attr *attr);</p>
 * <p>DESCRIPTION</p>
 * <p>The routine glp_ios_row_attr retrieves additional attributes of row i and stores them in the structure glp_attr. </p>
 */
public";

%csmethodmodifiers glp_ios_pool_size(glp_tree *tree) "
/**
 */
public";

%csmethodmodifiers glp_ios_add_row(glp_tree *tree, const char *name, int klass, int flags, int len, const int ind[], const double val[], int type, double rhs) "
/**
 */
public";

%csmethodmodifiers glp_ios_del_row(glp_tree *tree, int i) "
/**
 */
public";

%csmethodmodifiers glp_ios_clear_pool(glp_tree *tree) "
/**
 */
public";

%csmethodmodifiers glp_ios_can_branch(glp_tree *tree, int j) "
/**
 * glp_ios_can_branch - check if can branch upon specified variable .
 * <p>SYNOPSIS</p>
 * <p>int glp_ios_can_branch(glp_tree *tree, int j);</p>
 * <p>RETURNS</p>
 * <p>If j-th variable (column) can be used to branch upon, the routine glp_ios_can_branch returns non-zero, otherwise zero. </p>
 */
public";

%csmethodmodifiers glp_ios_branch_upon(glp_tree *tree, int j, int sel) "
/**
 * glp_ios_branch_upon - choose variable to branch upon .
 * <p>SYNOPSIS</p>
 * <p>void glp_ios_branch_upon(glp_tree *tree, int j, int sel);</p>
 * <p>DESCRIPTION</p>
 * <p>The routine glp_ios_branch_upon can be called from the user-defined callback routine in response to the reason GLP_IBRANCH to choose a branching variable, whose ordinal number is j. Should note that only variables, for which the routine glp_ios_can_branch returns non-zero, can be used to branch upon.</p>
 * <p>The parameter sel is a flag that indicates which branch (subproblem) should be selected next to continue the search:</p>
 * <p>GLP_DN_BRNCH - select down-branch; GLP_UP_BRNCH - select up-branch; GLP_NO_BRNCH - use general selection technique. </p>
 */
public";

%csmethodmodifiers glp_ios_select_node(glp_tree *tree, int p) "
/**
 * glp_ios_select_node - select subproblem to continue the search .
 * <p>SYNOPSIS</p>
 * <p>void glp_ios_select_node(glp_tree *tree, int p);</p>
 * <p>DESCRIPTION</p>
 * <p>The routine glp_ios_select_node can be called from the user-defined callback routine in response to the reason GLP_ISELECT to select an active subproblem, whose reference number is p. The search will be continued from the subproblem selected. </p>
 */
public";

%csmethodmodifiers glp_ios_heur_sol(glp_tree *tree, const double x[]) "
/**
 * glp_ios_heur_sol - provide solution found by heuristic .
 * <p>SYNOPSIS</p>
 * <p>int glp_ios_heur_sol(glp_tree *tree, const double x[]);</p>
 * <p>DESCRIPTION</p>
 * <p>The routine glp_ios_heur_sol can be called from the user-defined callback routine in response to the reason GLP_IHEUR to provide an integer feasible solution found by a primal heuristic.</p>
 * <p>Primal values of all variables (columns) found by the heuristic should be placed in locations x[1], ..., x[n], where n is the number of columns in the original problem object. Note that the routine glp_ios_heur_sol does not check primal feasibility of the solution provided.</p>
 * <p>Using the solution passed in the array x the routine computes value of the objective function. If the objective value is better than the best known integer feasible solution, the routine computes values of auxiliary variables (rows) and stores all solution components in the problem object.</p>
 * <p>RETURNS</p>
 * <p>If the provided solution is accepted, the routine glp_ios_heur_sol returns zero. Otherwise, if the provided solution is rejected, the routine returns non-zero. </p>
 */
public";

%csmethodmodifiers glp_ios_terminate(glp_tree *tree) "
/**
 * glp_ios_terminate - terminate the solution process. .
 * <p>SYNOPSIS</p>
 * <p>void glp_ios_terminate(glp_tree *tree);</p>
 * <p>DESCRIPTION</p>
 * <p>The routine glp_ios_terminate sets a flag indicating that the MIP solver should prematurely terminate the search. </p>
 */
public";

%csmethodmodifiers spx_chuzc_sel(SPXLP *lp, const double d[], double tol, double tol1, int list[]) "
/**
 */
public";

%csmethodmodifiers spx_chuzc_std(SPXLP *lp, const double d[], int num, const int list[]) "
/**
 */
public";

%csmethodmodifiers spx_alloc_se(SPXLP *lp, SPXSE *se) "
/**
 */
public";

%csmethodmodifiers spx_reset_refsp(SPXLP *lp, SPXSE *se) "
/**
 */
public";

%csmethodmodifiers spx_eval_gamma_j(SPXLP *lp, SPXSE *se, int j) "
/**
 */
public";

%csmethodmodifiers spx_chuzc_pse(SPXLP *lp, SPXSE *se, const double d[], int num, const int list[]) "
/**
 */
public";

%csmethodmodifiers spx_update_gamma(SPXLP *lp, SPXSE *se, int p, int q, const double trow[], const double tcol[]) "
/**
 */
public";

%csmethodmodifiers spx_free_se(SPXLP *lp, SPXSE *se) "
/**
 */
public";

%csmethodmodifiers branch_first(glp_tree *T, int *next) "
/**
 * ios_choose_var - select variable to branch on .
 * <p>SYNOPSIS</p>
 * <p>#include \"glpios.h\" int ios_choose_var(glp_tree *T, int *next);</p>
 * <p>The routine ios_choose_var chooses a variable from the candidate list to branch on. Additionally the routine provides a flag stored in the location next to suggests which of the child subproblems should be solved next.</p>
 * <p>RETURNS</p>
 * <p>The routine ios_choose_var returns the ordinal number of the column choosen. </p>
 */
public";

%csmethodmodifiers branch_last(glp_tree *T, int *next) "
/**
 */
public";

%csmethodmodifiers branch_mostf(glp_tree *T, int *next) "
/**
 */
public";

%csmethodmodifiers branch_drtom(glp_tree *T, int *next) "
/**
 */
public";

%csmethodmodifiers ios_choose_var(glp_tree *T, int *next) "
/**
 */
public";

%csmethodmodifiers ios_pcost_init(glp_tree *tree) "
/**
 */
public";

%csmethodmodifiers eval_degrad(glp_prob *P, int j, double bnd) "
/**
 */
public";

%csmethodmodifiers ios_pcost_update(glp_tree *tree) "
/**
 */
public";

%csmethodmodifiers ios_pcost_free(glp_tree *tree) "
/**
 */
public";

%csmethodmodifiers eval_psi(glp_tree *T, int j, int brnch) "
/**
 */
public";

%csmethodmodifiers progress(glp_tree *T) "
/**
 */
public";

%csmethodmodifiers ios_pcost_branch(glp_tree *T, int *_next) "
/**
 */
public";

%csmethodmodifiers clear_flag(Int wflg, Int wbig, Int W[], Int n) "
/**
 */
public";

%csmethodmodifiers AMD_2(Int n, Int Pe[], Int Iw[], Int Len[], Int iwlen, Int pfree, Int Nv[], Int Next[], Int Last[], Int Head[], Int Elen[], Int Degree[], Int W[], double Control[], double Info[]) "
/**
 */
public";

%csmethodmodifiers errfunc(const char *fmt,...) "
/**
 * glp_error - display fatal error message and terminate execution .
 * <p>SYNOPSIS</p>
 * <p>void glp_error(const char *fmt, ...);</p>
 * <p>DESCRIPTION</p>
 * <p>The routine glp_error (implemented as a macro) formats its parameters using the format control string fmt, writes the formatted message on the terminal, and abnormally terminates the program. </p>
 */
public";

%csmethodmodifiers glp_error_(const char *file, int line) "
/**
 */
public";

%csmethodmodifiers glp_at_error(void) "
/**
 * glp_at_error - check for error state .
 * <p>SYNOPSIS</p>
 * <p>int glp_at_error(void);</p>
 * <p>DESCRIPTION</p>
 * <p>The routine glp_at_error checks if the GLPK environment is at error state, i.e. if the call to the routine is (indirectly) made from the glp_error routine via an user-defined hook routine.</p>
 * <p>RETURNS</p>
 * <p>If the GLPK environment is at error state, the routine glp_at_error returns non-zero, otherwise zero. </p>
 */
public";

%csmethodmodifiers glp_assert_(const char *expr, const char *file, int line) "
/**
 * glp_assert - check for logical condition .
 * <p>SYNOPSIS</p>
 * <p>void glp_assert(int expr);</p>
 * <p>DESCRIPTION</p>
 * <p>The routine glp_assert (implemented as a macro) checks for a logical condition specified by the parameter expr. If the condition is false (i.e. the value of expr is zero), the routine writes a message on the terminal and abnormally terminates the program. </p>
 */
public";

%csmethodmodifiers glp_error_hook(void(*func)(void *info), void *info) "
/**
 * glp_error_hook - install hook to intercept abnormal termination .
 * <p>SYNOPSIS</p>
 * <p>void glp_error_hook(void (*func)(void *info), void *info);</p>
 * <p>DESCRIPTION</p>
 * <p>The routine glp_error_hook installs a user-defined hook routine to intercept abnormal termination.</p>
 * <p>The parameter func specifies the user-defined hook routine. It is called from the routine glp_error before the latter calls the abort function to abnormally terminate the application program because of fatal error. The parameter info is a transit pointer, specified in the corresponding call to the routine glp_error_hook; it may be used to pass some information to the hook routine.</p>
 * <p>To uninstall the hook routine the parameters func and info should be both specified as NULL. </p>
 */
public";

%csmethodmodifiers put_err_msg(const char *msg) "
/**
 * put_err_msg - provide error message string .
 * <p>SYNOPSIS</p>
 * <p>#include \"env.h\" void put_err_msg(const char *msg);</p>
 * <p>DESCRIPTION</p>
 * <p>The routine put_err_msg stores an error message string pointed to by msg to the environment block. </p>
 */
public";

%csmethodmodifiers get_err_msg(void) "
/**
 * get_err_msg - obtain error message string .
 * <p>SYNOPSIS</p>
 * <p>#include \"env.h\" const char *get_err_msg(void);</p>
 * <p>RETURNS</p>
 * <p>The routine get_err_msg returns a pointer to an error message string previously stored by the routine put_err_msg. </p>
 */
public";

%csmethodmodifiers create_graph(glp_graph *G, int v_size, int a_size) "
/**
 * glp_create_graph - create graph .
 * <p>SYNOPSIS</p>
 * <p>glp_graph *glp_create_graph(int v_size, int a_size);</p>
 * <p>DESCRIPTION</p>
 * <p>The routine creates a new graph, which initially is empty, i.e. has no vertices and arcs.</p>
 * <p>The parameter v_size specifies the size of data associated with each vertex of the graph (0 to 256 bytes).</p>
 * <p>The parameter a_size specifies the size of data associated with each arc of the graph (0 to 256 bytes).</p>
 * <p>RETURNS</p>
 * <p>The routine returns a pointer to the graph created. </p>
 */
public";

%csmethodmodifiers glp_create_graph(int v_size, int a_size) "
/**
 */
public";

%csmethodmodifiers glp_set_graph_name(glp_graph *G, const char *name) "
/**
 * glp_set_graph_name - assign (change) graph name .
 * <p>SYNOPSIS</p>
 * <p>void glp_set_graph_name(glp_graph *G, const char *name);</p>
 * <p>DESCRIPTION</p>
 * <p>The routine glp_set_graph_name assigns a symbolic name specified by the character string name (1 to 255 chars) to the graph.</p>
 * <p>If the parameter name is NULL or an empty string, the routine erases the existing symbolic name of the graph. </p>
 */
public";

%csmethodmodifiers glp_add_vertices(glp_graph *G, int nadd) "
/**
 * glp_add_vertices - add new vertices to graph .
 * <p>SYNOPSIS</p>
 * <p>int glp_add_vertices(glp_graph *G, int nadd);</p>
 * <p>DESCRIPTION</p>
 * <p>The routine glp_add_vertices adds nadd vertices to the specified graph. New vertices are always added to the end of the vertex list, so ordinal numbers of existing vertices remain unchanged.</p>
 * <p>Being added each new vertex is isolated (has no incident arcs).</p>
 * <p>RETURNS</p>
 * <p>The routine glp_add_vertices returns an ordinal number of the first new vertex added to the graph. </p>
 */
public";

%csmethodmodifiers glp_set_vertex_name(glp_graph *G, int i, const char *name) "
/**
 */
public";

%csmethodmodifiers glp_add_arc(glp_graph *G, int i, int j) "
/**
 * glp_add_arc - add new arc to graph .
 * <p>SYNOPSIS</p>
 * <p>glp_arc *glp_add_arc(glp_graph *G, int i, int j);</p>
 * <p>DESCRIPTION</p>
 * <p>The routine glp_add_arc adds a new arc to the specified graph.</p>
 * <p>The parameters i and j specify the ordinal numbers of, resp., tail and head vertices of the arc. Note that self-loops and multiple arcs are allowed.</p>
 * <p>RETURNS</p>
 * <p>The routine glp_add_arc returns a pointer to the arc added. </p>
 */
public";

%csmethodmodifiers glp_del_vertices(glp_graph *G, int ndel, const int num[]) "
/**
 * glp_del_vertices - delete vertices from graph .
 * <p>SYNOPSIS</p>
 * <p>void glp_del_vertices(glp_graph *G, int ndel, const int num[]);</p>
 * <p>DESCRIPTION</p>
 * <p>The routine glp_del_vertices deletes vertices along with all incident arcs from the specified graph. Ordinal numbers of vertices to be deleted should be placed in locations num[1], ..., num[ndel], ndel &gt; 0.</p>
 * <p>Note that deleting vertices involves changing ordinal numbers of other vertices remaining in the graph. New ordinal numbers of the remaining vertices are assigned under the assumption that the original order of vertices is not changed. </p>
 */
public";

%csmethodmodifiers glp_del_arc(glp_graph *G, glp_arc *a) "
/**
 * glp_del_arc - delete arc from graph .
 * <p>SYNOPSIS</p>
 * <p>void glp_del_arc(glp_graph *G, glp_arc *a);</p>
 * <p>DESCRIPTION</p>
 * <p>The routine glp_del_arc deletes an arc from the specified graph. The arc to be deleted must exist. </p>
 */
public";

%csmethodmodifiers delete_graph(glp_graph *G) "
/**
 * glp_erase_graph - erase graph content .
 * <p>SYNOPSIS</p>
 * <p>void glp_erase_graph(glp_graph *G, int v_size, int a_size);</p>
 * <p>DESCRIPTION</p>
 * <p>The routine glp_erase_graph erases the content of the specified graph. The effect of this operation is the same as if the graph would be deleted with the routine glp_delete_graph and then created anew with the routine glp_create_graph, with exception that the handle (pointer) to the graph remains valid. </p>
 */
public";

%csmethodmodifiers glp_erase_graph(glp_graph *G, int v_size, int a_size) "
/**
 */
public";

%csmethodmodifiers glp_delete_graph(glp_graph *G) "
/**
 * glp_delete_graph - delete graph .
 * <p>SYNOPSIS</p>
 * <p>void glp_delete_graph(glp_graph *G);</p>
 * <p>DESCRIPTION</p>
 * <p>The routine glp_delete_graph deletes the specified graph and frees all the memory allocated to this program object. </p>
 */
public";

%csmethodmodifiers glp_create_v_index(glp_graph *G) "
/**
 */
public";

%csmethodmodifiers glp_find_vertex(glp_graph *G, const char *name) "
/**
 */
public";

%csmethodmodifiers glp_delete_v_index(glp_graph *G) "
/**
 */
public";

%csmethodmodifiers glp_read_graph(glp_graph *G, const char *fname) "
/**
 * glp_read_graph - read graph from plain text file .
 * <p>SYNOPSIS</p>
 * <p>int glp_read_graph(glp_graph *G, const char *fname);</p>
 * <p>DESCRIPTION</p>
 * <p>The routine glp_read_graph reads a graph from a plain text file.</p>
 * <p>RETURNS</p>
 * <p>If the operation was successful, the routine returns zero. Otherwise it prints an error message and returns non-zero. </p>
 */
public";

%csmethodmodifiers glp_write_graph(glp_graph *G, const char *fname) "
/**
 * glp_write_graph - write graph to plain text file .
 * <p>SYNOPSIS</p>
 * <p>int glp_write_graph(glp_graph *G, const char *fname).</p>
 * <p>DESCRIPTION</p>
 * <p>The routine glp_write_graph writes the specified graph to a plain text file.</p>
 * <p>RETURNS</p>
 * <p>If the operation was successful, the routine returns zero. Otherwise it prints an error message and returns non-zero. </p>
 */
public";

%csmethodmodifiers str2num(const char *str, double *val_) "
/**
 * str2num - convert character string to value of double type .
 * <p>SYNOPSIS</p>
 * <p>#include \"misc.h\" int str2num(const char *str, double *val);</p>
 * <p>DESCRIPTION</p>
 * <p>The routine str2num converts the character string str to a value of double type and stores the value into location, which the parameter val points to (in the case of error content of this location is not changed).</p>
 * <p>RETURNS</p>
 * <p>The routine returns one of the following error codes:</p>
 * <p>0 - no error; 1 - value out of range; 2 - character string is syntactically incorrect. </p>
 */
public";

%csmethodmodifiers assign_capacities(struct csa *csa) "
/**
 */
public";

%csmethodmodifiers assign_costs(struct csa *csa) "
/**
 */
public";

%csmethodmodifiers assign_imbalance(struct csa *csa) "
/**
 */
public";

%csmethodmodifiers exponential(struct csa *csa, double lambda[1]) "
/**
 */
public";

%csmethodmodifiers gen_additional_arcs(struct csa *csa, struct arcs *arc_ptr) "
/**
 */
public";

%csmethodmodifiers gen_basic_grid(struct csa *csa, struct arcs *arc_ptr) "
/**
 */
public";

%csmethodmodifiers gen_more_arcs(struct csa *csa, struct arcs *arc_ptr) "
/**
 */
public";

%csmethodmodifiers generate(struct csa *csa) "
/**
 */
public";

%csmethodmodifiers output(struct csa *csa) "
/**
 */
public";

%csmethodmodifiers randy(struct csa *csa) "
/**
 */
public";

%csmethodmodifiers select_source_sinks(struct csa *csa) "
/**
 */
public";

%csmethodmodifiers uniform(struct csa *csa, double a[2]) "
/**
 */
public";

%csmethodmodifiers glp_gridgen(glp_graph *G_, int _v_rhs, int _a_cap, int _a_cost, const int parm[1+14]) "
/**
 */
public";

%csmethodmodifiers fp2rat(double x, double eps, double *p, double *q) "
/**
 * fp2rat - convert floating-point number to rational number .
 * <p>SYNOPSIS</p>
 * <p>#include \"misc.h\" int fp2rat(double x, double eps, double *p, double *q);</p>
 * <p>DESCRIPTION</p>
 * <p>Given a floating-point number 0 &lt;= x &lt; 1 the routine fp2rat finds its \"best\" rational approximation p / q, where p &gt;= 0 and q &gt; 0 are integer numbers, such that |x - p / q| &lt;= eps.</p>
 * <p>RETURNS</p>
 * <p>The routine fp2rat returns the number of iterations used to achieve the specified precision eps.</p>
 * <p>EXAMPLES</p>
 * <p>For x = sqrt(2) - 1 = 0.414213562373095 and eps = 1e-6 the routine gives p = 408 and q = 985, where 408 / 985 = 0.414213197969543.</p>
 * <p>BACKGROUND</p>
 * <p>It is well known that every positive real number x can be expressed as the following continued fraction:</p>
 * <p>x = b[0] + a[1] 
</p>
 * <p>b[1] + a[2] 
</p>
 * <p>b[2] + a[3] 
</p>
 * <p>b[3] + ...</p>
 * <p>where:</p>
 * <p>a[k] = 1, k = 0, 1, 2, ...</p>
 * <p>b[k] = floor(x[k]), k = 0, 1, 2, ...</p>
 * <p>x[0] = x,</p>
 * <p>x[k] = 1 / frac(x[k-1]), k = 1, 2, 3, ...</p>
 * <p>To find the \"best\" rational approximation of x the routine computes partial fractions f[k] by dropping after k terms as follows:</p>
 * <p>f[k] = A[k] / B[k],</p>
 * <p>where:</p>
 * <p>A[-1] = 1, A[0] = b[0], B[-1] = 0, B[0] = 1,</p>
 * <p>A[k] = b[k] * A[k-1] + a[k] * A[k-2],</p>
 * <p>B[k] = b[k] * B[k-1] + a[k] * B[k-2].</p>
 * <p>Once the condition</p>
 * <p>|x - f[k]| &lt;= eps</p>
 * <p>has been satisfied, the routine reports p = A[k] and q = B[k] as the final answer.</p>
 * <p>In the table below here is some statistics obtained for one million random numbers uniformly distributed in the range [0, 1). eps      max p   mean p      max q    mean q  max k   mean k
 
 1e-1 8 1.6 9 3.2 3 1.4 1e-2 98 6.2 99 12.4 5 2.4 1e-3 997 20.7 998 41.5 8 3.4 1e-4 9959 66.6 9960 133.5 10 4.4 1e-5 97403 211.7 97404 424.2 13 5.3 1e-6 479669 669.9 479670 1342.9 15 6.3 1e-7 1579030 2127.3 3962146 4257.8 16 7.3 1e-8 26188823 6749.4 26188824 13503.4 19 8.2</p>
 * <p>REFERENCES</p>
 * <p>W. B. Jones and W. J. Thron, \"Continued Fractions: Analytic Theory
and Applications,\" Encyclopedia on Mathematics and Its Applications, Addison-Wesley, 1980. </p>
 */
public";

%csmethodmodifiers scfint_create(int type) "
/**
 */
public";

%csmethodmodifiers scfint_factorize(SCFINT *fi, int n, int(*col)(void *info, int j, int ind[], double val[]), void *info) "
/**
 */
public";

%csmethodmodifiers scfint_update(SCFINT *fi, int upd, int j, int len, const int ind[], const double val[]) "
/**
 */
public";

%csmethodmodifiers scfint_ftran(SCFINT *fi, double x[]) "
/**
 */
public";

%csmethodmodifiers scfint_btran(SCFINT *fi, double x[]) "
/**
 */
public";

%csmethodmodifiers scfint_estimate(SCFINT *fi) "
/**
 */
public";

%csmethodmodifiers scfint_delete(SCFINT *fi) "
/**
 */
public";

%csmethodmodifiers set_row_attrib(glp_tree *tree, struct MIR *mir) "
/**
 * ios_mir_init - initialize MIR cut generator .
 * <p>SYNOPSIS</p>
 * <p>#include \"glpios.h\" void *ios_mir_init(glp_tree *tree);</p>
 * <p>DESCRIPTION</p>
 * <p>The routine ios_mir_init initializes the MIR cut generator assuming that the current subproblem is the root subproblem.</p>
 * <p>RETURNS</p>
 * <p>The routine ios_mir_init returns a pointer to the MIR cut generator working area. </p>
 */
public";

%csmethodmodifiers set_col_attrib(glp_tree *tree, struct MIR *mir) "
/**
 */
public";

%csmethodmodifiers set_var_bounds(glp_tree *tree, struct MIR *mir) "
/**
 */
public";

%csmethodmodifiers mark_useless_rows(glp_tree *tree, struct MIR *mir) "
/**
 */
public";

%csmethodmodifiers ios_mir_init(glp_tree *tree) "
/**
 */
public";

%csmethodmodifiers get_current_point(glp_tree *tree, struct MIR *mir) "
/**
 * ios_mir_gen - generate MIR cuts .
 * <p>SYNOPSIS</p>
 * <p>#include \"glpios.h\" void ios_mir_gen(glp_tree *tree, void *gen, IOSPOOL *pool);</p>
 * <p>DESCRIPTION</p>
 * <p>The routine ios_mir_gen generates MIR cuts for the current point and adds them to the cut pool. </p>
 */
public";

%csmethodmodifiers initial_agg_row(glp_tree *tree, struct MIR *mir, int i) "
/**
 */
public";

%csmethodmodifiers subst_fixed_vars(struct MIR *mir) "
/**
 */
public";

%csmethodmodifiers bound_subst_heur(struct MIR *mir) "
/**
 */
public";

%csmethodmodifiers build_mod_row(struct MIR *mir) "
/**
 */
public";

%csmethodmodifiers mir_ineq(const int n, const double a[], const double b, double alpha[], double *beta, double *gamma) "
/**
 */
public";

%csmethodmodifiers cmir_ineq(const int n, const double a[], const double b, const double u[], const char cset[], const double delta, double alpha[], double *beta, double *gamma) "
/**
 */
public";

%csmethodmodifiers cmir_cmp(const void *p1, const void *p2) "
/**
 */
public";

%csmethodmodifiers cmir_sep(const int n, const double a[], const double b, const double u[], const double x[], const double s, double alpha[], double *beta, double *gamma) "
/**
 */
public";

%csmethodmodifiers generate(struct MIR *mir) "
/**
 */
public";

%csmethodmodifiers back_subst(struct MIR *mir) "
/**
 */
public";

%csmethodmodifiers subst_aux_vars(glp_tree *tree, struct MIR *mir) "
/**
 */
public";

%csmethodmodifiers add_cut(glp_tree *tree, struct MIR *mir) "
/**
 */
public";

%csmethodmodifiers aggregate_row(glp_tree *tree, struct MIR *mir) "
/**
 */
public";

%csmethodmodifiers ios_mir_gen(glp_tree *tree, void *gen) "
/**
 */
public";

%csmethodmodifiers ios_mir_term(void *gen) "
/**
 * ios_mir_term - terminate MIR cut generator .
 * <p>SYNOPSIS</p>
 * <p>#include \"glpios.h\" void ios_mir_term(void *gen);</p>
 * <p>DESCRIPTION</p>
 * <p>The routine ios_mir_term deletes the MIR cut generator working area freeing all the memory allocated to it. </p>
 */
public";

%csmethodmodifiers gzclose(gzFile file) "
/**
 */
public";

%csmethodmodifiers error(struct csa *csa, const char *fmt,...) "
/**
 */
public";

%csmethodmodifiers warning(struct csa *csa, const char *fmt,...) "
/**
 */
public";

%csmethodmodifiers read_char(struct csa *csa) "
/**
 */
public";

%csmethodmodifiers read_designator(struct csa *csa) "
/**
 */
public";

%csmethodmodifiers read_field(struct csa *csa) "
/**
 */
public";

%csmethodmodifiers end_of_line(struct csa *csa) "
/**
 */
public";

%csmethodmodifiers check_int(struct csa *csa, double num) "
/**
 */
public";

%csmethodmodifiers glp_read_mincost(glp_graph *G, int v_rhs, int a_low, int a_cap, int a_cost, const char *fname) "
/**
 * glp_read_mincost - read min-cost flow problem data in DIMACS format .
 * <p>SYNOPSIS</p>
 * <p>int glp_read_mincost(glp_graph *G, int v_rhs, int a_low, int a_cap, int a_cost, const char *fname);</p>
 * <p>DESCRIPTION</p>
 * <p>The routine glp_read_mincost reads minimum cost flow problem data in DIMACS format from a text file.</p>
 * <p>RETURNS</p>
 * <p>If the operation was successful, the routine returns zero. Otherwise it prints an error message and returns non-zero. </p>
 */
public";

%csmethodmodifiers glp_write_mincost(glp_graph *G, int v_rhs, int a_low, int a_cap, int a_cost, const char *fname) "
/**
 * glp_write_mincost - write min-cost flow problem data in DIMACS format .
 * <p>SYNOPSIS</p>
 * <p>int glp_write_mincost(glp_graph *G, int v_rhs, int a_low, int a_cap, int a_cost, const char *fname);</p>
 * <p>DESCRIPTION</p>
 * <p>The routine glp_write_mincost writes minimum cost flow problem data in DIMACS format to a text file.</p>
 * <p>RETURNS</p>
 * <p>If the operation was successful, the routine returns zero. Otherwise it prints an error message and returns non-zero. </p>
 */
public";

%csmethodmodifiers glp_read_maxflow(glp_graph *G, int *_s, int *_t, int a_cap, const char *fname) "
/**
 * glp_read_maxflow - read maximum flow problem data in DIMACS format .
 * <p>SYNOPSIS</p>
 * <p>int glp_read_maxflow(glp_graph *G, int *s, int *t, int a_cap, const char *fname);</p>
 * <p>DESCRIPTION</p>
 * <p>The routine glp_read_maxflow reads maximum flow problem data in DIMACS format from a text file.</p>
 * <p>RETURNS</p>
 * <p>If the operation was successful, the routine returns zero. Otherwise it prints an error message and returns non-zero. </p>
 */
public";

%csmethodmodifiers glp_write_maxflow(glp_graph *G, int s, int t, int a_cap, const char *fname) "
/**
 * glp_write_maxflow - write maximum flow problem data in DIMACS format .
 * <p>SYNOPSIS</p>
 * <p>int glp_write_maxflow(glp_graph *G, int s, int t, int a_cap, const char *fname);</p>
 * <p>DESCRIPTION</p>
 * <p>The routine glp_write_maxflow writes maximum flow problem data in DIMACS format to a text file.</p>
 * <p>RETURNS</p>
 * <p>If the operation was successful, the routine returns zero. Otherwise it prints an error message and returns non-zero. </p>
 */
public";

%csmethodmodifiers glp_read_asnprob(glp_graph *G, int v_set, int a_cost, const char *fname) "
/**
 * glp_read_asnprob - read assignment problem data in DIMACS format .
 * <p>SYNOPSIS</p>
 * <p>int glp_read_asnprob(glp_graph *G, int v_set, int a_cost, const char *fname);</p>
 * <p>DESCRIPTION</p>
 * <p>The routine glp_read_asnprob reads assignment problem data in DIMACS format from a text file.</p>
 * <p>RETURNS</p>
 * <p>If the operation was successful, the routine returns zero. Otherwise it prints an error message and returns non-zero. </p>
 */
public";

%csmethodmodifiers glp_write_asnprob(glp_graph *G, int v_set, int a_cost, const char *fname) "
/**
 * glp_write_asnprob - write assignment problem data in DIMACS format .
 * <p>SYNOPSIS</p>
 * <p>int glp_write_asnprob(glp_graph *G, int v_set, int a_cost, const char *fname);</p>
 * <p>DESCRIPTION</p>
 * <p>The routine glp_write_asnprob writes assignment problem data in DIMACS format to a text file.</p>
 * <p>RETURNS</p>
 * <p>If the operation was successful, the routine returns zero. Otherwise it prints an error message and returns non-zero. </p>
 */
public";

%csmethodmodifiers glp_read_ccdata(glp_graph *G, int v_wgt, const char *fname) "
/**
 * glp_read_ccdata - read graph in DIMACS clique/coloring format .
 * <p>SYNOPSIS</p>
 * <p>int glp_read_ccdata(glp_graph *G, int v_wgt, const char *fname);</p>
 * <p>DESCRIPTION</p>
 * <p>The routine glp_read_ccdata reads an (undirected) graph in DIMACS clique/coloring format from a text file.</p>
 * <p>RETURNS</p>
 * <p>If the operation was successful, the routine returns zero. Otherwise it prints an error message and returns non-zero. </p>
 */
public";

%csmethodmodifiers glp_write_ccdata(glp_graph *G, int v_wgt, const char *fname) "
/**
 * glp_write_ccdata - write graph in DIMACS clique/coloring format .
 * <p>SYNOPSIS</p>
 * <p>int glp_write_ccdata(glp_graph *G, int v_wgt, const char *fname);</p>
 * <p>DESCRIPTION</p>
 * <p>The routine glp_write_ccdata writes the specified graph in DIMACS clique/coloring format to a text file.</p>
 * <p>RETURNS</p>
 * <p>If the operation was successful, the routine returns zero. Otherwise it prints an error message and returns non-zero. </p>
 */
public";

%csmethodmodifiers glp_read_prob(glp_prob *P, int flags, const char *fname) "
/**
 * glp_read_prob - read problem data in GLPK format .
 * <p>SYNOPSIS</p>
 * <p>int glp_read_prob(glp_prob *P, int flags, const char *fname);</p>
 * <p>The routine glp_read_prob reads problem data in GLPK LP/MIP format from a text file.</p>
 * <p>RETURNS</p>
 * <p>If the operation was successful, the routine returns zero. Otherwise it prints an error message and returns non-zero. </p>
 */
public";

%csmethodmodifiers glp_write_prob(glp_prob *P, int flags, const char *fname) "
/**
 * glp_write_prob - write problem data in GLPK format .
 * <p>SYNOPSIS</p>
 * <p>int glp_write_prob(glp_prob *P, int flags, const char *fname);</p>
 * <p>The routine glp_write_prob writes problem data in GLPK LP/MIP format to a text file.</p>
 * <p>RETURNS</p>
 * <p>If the operation was successful, the routine returns zero. Otherwise it prints an error message and returns non-zero. </p>
 */
public";

%csmethodmodifiers glp_read_cnfsat(glp_prob *P, const char *fname) "
/**
 */
public";

%csmethodmodifiers glp_check_cnfsat(glp_prob *P) "
/**
 */
public";

%csmethodmodifiers glp_write_cnfsat(glp_prob *P, const char *fname) "
/**
 */
public";

%csmethodmodifiers AMD_control(double Control[]) "
/**
 */
public";

%csmethodmodifiers spm_create_mat(int m, int n) "
/**
 * spm_create_mat - create general sparse matrix .
 * <p>SYNOPSIS</p>
 * <p>#include \"glpspm.h\" SPM *spm_create_mat(int m, int n);</p>
 * <p>DESCRIPTION</p>
 * <p>The routine spm_create_mat creates a general sparse matrix having m rows and n columns. Being created the matrix is zero (empty), i.e. has no elements.</p>
 * <p>RETURNS</p>
 * <p>The routine returns a pointer to the matrix created. </p>
 */
public";

%csmethodmodifiers spm_new_elem(SPM *A, int i, int j, double val) "
/**
 * spm_new_elem - add new element to sparse matrix .
 * <p>SYNOPSIS</p>
 * <p>#include \"glpspm.h\" SPME *spm_new_elem(SPM *A, int i, int j, double val);</p>
 * <p>DESCRIPTION</p>
 * <p>The routine spm_new_elem adds a new element to the specified sparse matrix. Parameters i, j, and val specify the row number, the column number, and a numerical value of the element, respectively.</p>
 * <p>RETURNS</p>
 * <p>The routine returns a pointer to the new element added. </p>
 */
public";

%csmethodmodifiers spm_delete_mat(SPM *A) "
/**
 * spm_delete_mat - delete general sparse matrix .
 * <p>SYNOPSIS</p>
 * <p>#include \"glpspm.h\" void spm_delete_mat(SPM *A);</p>
 * <p>DESCRIPTION</p>
 * <p>The routine deletes the specified general sparse matrix freeing all the memory allocated to this object. </p>
 */
public";

%csmethodmodifiers spm_test_mat_e(int n, int c) "
/**
 * spm_test_mat_e - create test sparse matrix of E(n,c) class .
 * <p>SYNOPSIS</p>
 * <p>#include \"glpspm.h\" SPM *spm_test_mat_e(int n, int c);</p>
 * <p>DESCRIPTION</p>
 * <p>The routine spm_test_mat_e creates a test sparse matrix of E(n,c) class as described in the book: Ole 0sterby, Zahari Zlatev. Direct Methods for Sparse Matrices. Springer-Verlag, 1983.</p>
 * <p>Matrix of E(n,c) class is a symmetric positive definite matrix of the order n. It has the number 4 on its main diagonal and the number -1 on its four co-diagonals, two of which are neighbour to the main diagonal and two others are shifted from the main diagonal on the distance c.</p>
 * <p>It is necessary that n &gt;= 3 and 2 &lt;= c &lt;= n-1.</p>
 * <p>RETURNS</p>
 * <p>The routine returns a pointer to the matrix created. </p>
 */
public";

%csmethodmodifiers spm_test_mat_d(int n, int c) "
/**
 * spm_test_mat_d - create test sparse matrix of D(n,c) class .
 * <p>SYNOPSIS</p>
 * <p>#include \"glpspm.h\" SPM *spm_test_mat_d(int n, int c);</p>
 * <p>DESCRIPTION</p>
 * <p>The routine spm_test_mat_d creates a test sparse matrix of D(n,c) class as described in the book: Ole 0sterby, Zahari Zlatev. Direct Methods for Sparse Matrices. Springer-Verlag, 1983.</p>
 * <p>Matrix of D(n,c) class is a non-singular matrix of the order n. It has unity main diagonal, three co-diagonals above the main diagonal on the distance c, which are cyclically continued below the main diagonal, and a triangle block of the size 10x10 in the upper right corner.</p>
 * <p>It is necessary that n &gt;= 14 and 1 &lt;= c &lt;= n-13.</p>
 * <p>RETURNS</p>
 * <p>The routine returns a pointer to the matrix created. </p>
 */
public";

%csmethodmodifiers spm_show_mat(const SPM *A, const char *fname) "
/**
 * spm_show_mat - write sparse matrix pattern in BMP file format .
 * <p>SYNOPSIS</p>
 * <p>#include \"glpspm.h\" int spm_show_mat(const SPM *A, const char *fname);</p>
 * <p>DESCRIPTION</p>
 * <p>The routine spm_show_mat writes pattern of the specified sparse matrix in uncompressed BMP file format (Windows bitmap) to a binary file whose name is specified by the character string fname.</p>
 * <p>Each pixel corresponds to one matrix element. The pixel colors have the following meaning:</p>
 * <p>Black structurally zero element White positive element Cyan negative element Green zero element Red duplicate element</p>
 * <p>RETURNS</p>
 * <p>If no error occured, the routine returns zero. Otherwise, it prints an appropriate error message and returns non-zero. </p>
 */
public";

%csmethodmodifiers spm_read_hbm(const char *fname) "
/**
 * spm_read_hbm - read sparse matrix in Harwell-Boeing format .
 * <p>SYNOPSIS</p>
 * <p>#include \"glpspm.h\" SPM *spm_read_hbm(const char *fname);</p>
 * <p>DESCRIPTION</p>
 * <p>The routine spm_read_hbm reads a sparse matrix in the Harwell-Boeing format from a text file whose name is the character string fname.</p>
 * <p>Detailed description of the Harwell-Boeing format recognised by this routine can be found in the following report:</p>
 * <p>I.S.Duff, R.G.Grimes, J.G.Lewis. User's Guide for the Harwell-Boeing Sparse Matrix Collection (Release I), TR/PA/92/86, October 1992.</p>
 * <p>NOTE</p>
 * <p>The routine spm_read_hbm reads the matrix \"as is\", due to which zero and/or duplicate elements can appear in the matrix.</p>
 * <p>RETURNS</p>
 * <p>If no error occured, the routine returns a pointer to the matrix created. Otherwise, the routine prints an appropriate error message and returns NULL. </p>
 */
public";

%csmethodmodifiers spm_count_nnz(const SPM *A) "
/**
 * spm_count_nnz - determine number of non-zeros in sparse matrix .
 * <p>SYNOPSIS</p>
 * <p>#include \"glpspm.h\" int spm_count_nnz(const SPM *A);</p>
 * <p>RETURNS</p>
 * <p>The routine spm_count_nnz returns the number of structural non-zero elements in the specified sparse matrix. </p>
 */
public";

%csmethodmodifiers spm_drop_zeros(SPM *A, double eps) "
/**
 * spm_drop_zeros - remove zero elements from sparse matrix .
 * <p>SYNOPSIS</p>
 * <p>#include \"glpspm.h\" int spm_drop_zeros(SPM *A, double eps);</p>
 * <p>DESCRIPTION</p>
 * <p>The routine spm_drop_zeros removes all elements from the specified sparse matrix, whose absolute value is less than eps.</p>
 * <p>If the parameter eps is 0, only zero elements are removed from the matrix.</p>
 * <p>RETURNS</p>
 * <p>The routine returns the number of elements removed. </p>
 */
public";

%csmethodmodifiers spm_read_mat(const char *fname) "
/**
 * spm_read_mat - read sparse matrix from text file .
 * <p>SYNOPSIS</p>
 * <p>#include \"glpspm.h\" SPM *spm_read_mat(const char *fname);</p>
 * <p>DESCRIPTION</p>
 * <p>The routine reads a sparse matrix from a text file whose name is specified by the parameter fname.</p>
 * <p>For the file format see description of the routine spm_write_mat.</p>
 * <p>RETURNS</p>
 * <p>On success the routine returns a pointer to the matrix created, otherwise NULL. </p>
 */
public";

%csmethodmodifiers spm_write_mat(const SPM *A, const char *fname) "
/**
 * spm_write_mat - write sparse matrix to text file .
 * <p>SYNOPSIS</p>
 * <p>#include \"glpspm.h\" int spm_write_mat(const SPM *A, const char *fname);</p>
 * <p>DESCRIPTION</p>
 * <p>The routine spm_write_mat writes the specified sparse matrix to a text file whose name is specified by the parameter fname. This file can be read back with the routine spm_read_mat.</p>
 * <p>RETURNS</p>
 * <p>On success the routine returns zero, otherwise non-zero.</p>
 * <p>FILE FORMAT</p>
 * <p>The file created by the routine spm_write_mat is a plain text file, which contains the following information:</p>
 * <p>m n nnz row[1] col[1] val[1] row[2] col[2] val[2] . . . row[nnz] col[nnz] val[nnz]</p>
 * <p>where: m is the number of rows; n is the number of columns; nnz is the number of non-zeros; row[k], k = 1,...,nnz, are row indices; col[k], k = 1,...,nnz, are column indices; val[k], k = 1,...,nnz, are element values. </p>
 */
public";

%csmethodmodifiers spm_transpose(const SPM *A) "
/**
 * spm_transpose - transpose sparse matrix .
 * <p>SYNOPSIS</p>
 * <p>#include \"glpspm.h\" SPM *spm_transpose(const SPM *A);</p>
 * <p>RETURNS</p>
 * <p>The routine computes and returns sparse matrix B, which is a matrix transposed to sparse matrix A. </p>
 */
public";

%csmethodmodifiers spm_add_sym(const SPM *A, const SPM *B) "
/**
 */
public";

%csmethodmodifiers spm_add_num(SPM *C, double alfa, const SPM *A, double beta, const SPM *B) "
/**
 */
public";

%csmethodmodifiers spm_add_mat(double alfa, const SPM *A, double beta, const SPM *B) "
/**
 */
public";

%csmethodmodifiers spm_mul_sym(const SPM *A, const SPM *B) "
/**
 */
public";

%csmethodmodifiers spm_mul_num(SPM *C, const SPM *A, const SPM *B) "
/**
 */
public";

%csmethodmodifiers spm_mul_mat(const SPM *A, const SPM *B) "
/**
 */
public";

%csmethodmodifiers spm_create_per(int n) "
/**
 */
public";

%csmethodmodifiers spm_check_per(PER *P) "
/**
 */
public";

%csmethodmodifiers spm_delete_per(PER *P) "
/**
 */
public";

%csmethodmodifiers glp_check_kkt(glp_prob *P, int sol, int cond, double *_ae_max, int *_ae_ind, double *_re_max, int *_re_ind) "
/**
 */
public";

%csmethodmodifiers create_slice(MPL *mpl) "
/**
 */
public";

%csmethodmodifiers expand_slice(MPL *mpl, SLICE *slice, SYMBOL *sym) "
/**
 */
public";

%csmethodmodifiers slice_dimen(MPL *mpl, SLICE *slice) "
/**
 */
public";

%csmethodmodifiers slice_arity(MPL *mpl, SLICE *slice) "
/**
 */
public";

%csmethodmodifiers fake_slice(MPL *mpl, int dim) "
/**
 */
public";

%csmethodmodifiers delete_slice(MPL *mpl, SLICE *slice) "
/**
 */
public";

%csmethodmodifiers is_number(MPL *mpl) "
/**
 */
public";

%csmethodmodifiers is_symbol(MPL *mpl) "
/**
 */
public";

%csmethodmodifiers is_literal(MPL *mpl, char *literal) "
/**
 */
public";

%csmethodmodifiers read_number(MPL *mpl) "
/**
 */
public";

%csmethodmodifiers read_symbol(MPL *mpl) "
/**
 */
public";

%csmethodmodifiers read_slice(MPL *mpl, char *name, int dim) "
/**
 */
public";

%csmethodmodifiers select_set(MPL *mpl, char *name) "
/**
 */
public";

%csmethodmodifiers simple_format(MPL *mpl, SET *set, MEMBER *memb, SLICE *slice) "
/**
 */
public";

%csmethodmodifiers matrix_format(MPL *mpl, SET *set, MEMBER *memb, SLICE *slice, int tr) "
/**
 */
public";

%csmethodmodifiers set_data(MPL *mpl) "
/**
 */
public";

%csmethodmodifiers select_parameter(MPL *mpl, char *name) "
/**
 */
public";

%csmethodmodifiers set_default(MPL *mpl, PARAMETER *par, SYMBOL *altval) "
/**
 */
public";

%csmethodmodifiers read_value(MPL *mpl, PARAMETER *par, TUPLE *tuple) "
/**
 */
public";

%csmethodmodifiers plain_format(MPL *mpl, PARAMETER *par, SLICE *slice) "
/**
 */
public";

%csmethodmodifiers tabular_format(MPL *mpl, PARAMETER *par, SLICE *slice, int tr) "
/**
 */
public";

%csmethodmodifiers tabbing_format(MPL *mpl, SYMBOL *altval) "
/**
 */
public";

%csmethodmodifiers parameter_data(MPL *mpl) "
/**
 */
public";

%csmethodmodifiers data_section(MPL *mpl) "
/**
 */
public";

%csmethodmodifiers ios_create_vec(int n) "
/**
 * ios_create_vec - create sparse vector .
 * <p>SYNOPSIS</p>
 * <p>#include \"glpios.h\" IOSVEC *ios_create_vec(int n);</p>
 * <p>DESCRIPTION</p>
 * <p>The routine ios_create_vec creates a sparse vector of dimension n, which initially is a null vector.</p>
 * <p>RETURNS</p>
 * <p>The routine returns a pointer to the vector created. </p>
 */
public";

%csmethodmodifiers ios_check_vec(IOSVEC *v) "
/**
 * ios_check_vec - check that sparse vector has correct representation .
 * <p>SYNOPSIS</p>
 * <p>#include \"glpios.h\" void ios_check_vec(IOSVEC *v);</p>
 * <p>DESCRIPTION</p>
 * <p>The routine ios_check_vec checks that a sparse vector specified by the parameter v has correct representation.</p>
 * <p>NOTE</p>
 * <p>Complexity of this operation is O(n). </p>
 */
public";

%csmethodmodifiers ios_get_vj(IOSVEC *v, int j) "
/**
 * ios_get_vj - retrieve component of sparse vector .
 * <p>SYNOPSIS</p>
 * <p>#include \"glpios.h\" double ios_get_vj(IOSVEC *v, int j);</p>
 * <p>RETURNS</p>
 * <p>The routine ios_get_vj returns j-th component of a sparse vector specified by the parameter v. </p>
 */
public";

%csmethodmodifiers ios_set_vj(IOSVEC *v, int j, double val) "
/**
 * ios_set_vj - set/change component of sparse vector .
 * <p>SYNOPSIS</p>
 * <p>#include \"glpios.h\" void ios_set_vj(IOSVEC *v, int j, double val);</p>
 * <p>DESCRIPTION</p>
 * <p>The routine ios_set_vj assigns val to j-th component of a sparse vector specified by the parameter v. </p>
 */
public";

%csmethodmodifiers ios_clear_vec(IOSVEC *v) "
/**
 * ios_clear_vec - set all components of sparse vector to zero .
 * <p>SYNOPSIS</p>
 * <p>#include \"glpios.h\" void ios_clear_vec(IOSVEC *v);</p>
 * <p>DESCRIPTION</p>
 * <p>The routine ios_clear_vec sets all components of a sparse vector specified by the parameter v to zero. </p>
 */
public";

%csmethodmodifiers ios_clean_vec(IOSVEC *v, double eps) "
/**
 * ios_clean_vec - remove zero or small components from sparse vector .
 * <p>SYNOPSIS</p>
 * <p>#include \"glpios.h\" void ios_clean_vec(IOSVEC *v, double eps);</p>
 * <p>DESCRIPTION</p>
 * <p>The routine ios_clean_vec removes zero components and components whose magnitude is less than eps from a sparse vector specified by the parameter v. If eps is 0.0, only zero components are removed. </p>
 */
public";

%csmethodmodifiers ios_copy_vec(IOSVEC *x, IOSVEC *y) "
/**
 * ios_copy_vec - copy sparse vector (x := y) .
 * <p>SYNOPSIS</p>
 * <p>#include \"glpios.h\" void ios_copy_vec(IOSVEC *x, IOSVEC *y);</p>
 * <p>DESCRIPTION</p>
 * <p>The routine ios_copy_vec copies a sparse vector specified by the parameter y to a sparse vector specified by the parameter x. </p>
 */
public";

%csmethodmodifiers ios_linear_comb(IOSVEC *x, double a, IOSVEC *y) "
/**
 * ios_linear_comb - compute linear combination (x := x + a * y) .
 * <p>SYNOPSIS</p>
 * <p>#include \"glpios.h\" void ios_linear_comb(IOSVEC *x, double a, IOSVEC *y);</p>
 * <p>DESCRIPTION</p>
 * <p>The routine ios_linear_comb computes the linear combination</p>
 * <p>x := x + a * y,</p>
 * <p>where x and y are sparse vectors, a is a scalar. </p>
 */
public";

%csmethodmodifiers ios_delete_vec(IOSVEC *v) "
/**
 * ios_delete_vec - delete sparse vector .
 * <p>SYNOPSIS</p>
 * <p>#include \"glpios.h\" void ios_delete_vec(IOSVEC *v);</p>
 * <p>DESCRIPTION</p>
 * <p>The routine ios_delete_vec deletes a sparse vector specified by the parameter v freeing all the memory allocated to this object. </p>
 */
public";

%csmethodmodifiers bfd_create_it(void) "
/**
 */
public";

%csmethodmodifiers bfd_get_bfcp(BFD *bfd, void *parm) "
/**
 */
public";

%csmethodmodifiers bfd_set_bfcp(BFD *bfd, const void *parm) "
/**
 */
public";

%csmethodmodifiers bfd_col(void *info_, int j, int ind[], double val[]) "
/**
 */
public";

%csmethodmodifiers bfd_factorize(BFD *bfd, int m, int(*col1)(void *info, int j, int ind[], double val[]), void *info1) "
/**
 */
public";

%csmethodmodifiers bfd_condest(BFD *bfd) "
/**
 */
public";

%csmethodmodifiers bfd_ftran(BFD *bfd, double x[]) "
/**
 */
public";

%csmethodmodifiers bfd_btran(BFD *bfd, double x[]) "
/**
 */
public";

%csmethodmodifiers bfd_update(BFD *bfd, int j, int len, const int ind[], const double val[]) "
/**
 */
public";

%csmethodmodifiers bfd_get_count(BFD *bfd) "
/**
 */
public";

%csmethodmodifiers bfd_delete_it(BFD *bfd) "
/**
 */
public";

%csmethodmodifiers set_d_eps(mpq_t x, double val) "
/**
 * glp_exact - solve LP problem in exact arithmetic .
 * <p>SYNOPSIS</p>
 * <p>int glp_exact(glp_prob *lp, const glp_smcp *parm);</p>
 * <p>DESCRIPTION</p>
 * <p>The routine glp_exact is a tentative implementation of the primal two-phase simplex method based on exact (rational) arithmetic. It is similar to the routine glp_simplex, however, for all internal computations it uses arithmetic of rational numbers, which is exact in mathematical sense, i.e. free of round-off errors unlike floating point arithmetic.</p>
 * <p>Note that the routine glp_exact uses inly two control parameters passed in the structure glp_smcp, namely, it_lim and tm_lim.</p>
 * <p>RETURNS</p>
 * <p>0 The LP problem instance has been successfully solved. This code does not necessarily mean that the solver has found optimal solution. It only means that the solution process was successful.</p>
 * <p>GLP_EBADB Unable to start the search, because the initial basis specified in the problem object is invalidthe number of basic (auxiliary and structural) variables is not the same as the number of rows in the problem object.</p>
 * <p>GLP_ESING Unable to start the search, because the basis matrix correspodning to the initial basis is exactly singular.</p>
 * <p>GLP_EBOUND Unable to start the search, because some double-bounded variables have incorrect bounds.</p>
 * <p>GLP_EFAIL The problem has no rows/columns.</p>
 * <p>GLP_EITLIM The search was prematurely terminated, because the simplex iteration limit has been exceeded.</p>
 * <p>GLP_ETMLIM The search was prematurely terminated, because the time limit has been exceeded. </p>
 */
public";

%csmethodmodifiers load_data(SSX *ssx, glp_prob *lp) "
/**
 */
public";

%csmethodmodifiers load_basis(SSX *ssx, glp_prob *lp) "
/**
 */
public";

%csmethodmodifiers glp_exact(glp_prob *lp, const glp_smcp *parm) "
/**
 */
public";

%csmethodmodifiers rng_unif_01(RNG *rand) "
/**
 * rng_unif_01 - obtain pseudo-random number in the range [0, 1] .
 * <p>SYNOPSIS</p>
 * <p>#include \"rng.h\" double rng_unif_01(RNG *rand);</p>
 * <p>RETURNS</p>
 * <p>The routine rng_unif_01 returns a next pseudo-random number which is uniformly distributed in the range [0, 1]. </p>
 */
public";

%csmethodmodifiers rng_uniform(RNG *rand, double a, double b) "
/**
 * rng_uniform - obtain pseudo-random number in the range [a, b] .
 * <p>SYNOPSIS</p>
 * <p>#include \"rng.h\" double rng_uniform(RNG *rand, double a, double b);</p>
 * <p>RETURNS</p>
 * <p>The routine rng_uniform returns a next pseudo-random number which is uniformly distributed in the range [a, b]. </p>
 */
public";

%csmethodmodifiers round2n(double x) "
/**
 * round2n - round floating-point number to nearest power of two .
 * <p>SYNOPSIS</p>
 * <p>#include \"misc.h\" double round2n(double x);</p>
 * <p>RETURNS</p>
 * <p>Given a positive floating-point value x the routine round2n returns 2^n such that |x - 2^n| is minimal.</p>
 * <p>EXAMPLES</p>
 * <p>round2n(10.1) = 2^3 = 8 round2n(15.3) = 2^4 = 16 round2n(0.01) = 2^(-7) = 0.0078125</p>
 * <p>BACKGROUND</p>
 * <p>Let x = f * 2^e, where 0.5 &lt;= f &lt; 1 is a normalized fractional part, e is an integer exponent. Then, obviously, 0.5 * 2^e &lt;= x &lt; 2^e, so if x - 0.5 * 2^e &lt;= 2^e - x, we choose 0.5 * 2^e = 2^(e-1), and 2^e otherwise. The latter condition can be written as 2 * x &lt;= 1.5 * 2^e or 2 * f * 2^e &lt;= 1.5 * 2^e or, finally, f &lt;= 0.75. </p>
 */
public";

%csmethodmodifiers show_progress(glp_tree *T, int bingo) "
/**
 */
public";

%csmethodmodifiers is_branch_hopeful(glp_tree *T, int p) "
/**
 */
public";

%csmethodmodifiers check_integrality(glp_tree *T) "
/**
 */
public";

%csmethodmodifiers record_solution(glp_tree *T) "
/**
 */
public";

%csmethodmodifiers fix_by_red_cost(glp_tree *T) "
/**
 */
public";

%csmethodmodifiers branch_on(glp_tree *T, int j, int next) "
/**
 */
public";

%csmethodmodifiers cleanup_the_tree(glp_tree *T) "
/**
 */
public";

%csmethodmodifiers round_heur(glp_tree *T) "
/**
 */
public";

%csmethodmodifiers generate_cuts(glp_tree *T) "
/**
 */
public";

%csmethodmodifiers remove_cuts(glp_tree *T) "
/**
 */
public";

%csmethodmodifiers display_cut_info(glp_tree *T) "
/**
 */
public";

%csmethodmodifiers ios_driver(glp_tree *T) "
/**
 * ios_driver - branch-and-cut driver .
 * <p>SYNOPSIS</p>
 * <p>#include \"glpios.h\" int ios_driver(glp_tree *T);</p>
 * <p>DESCRIPTION</p>
 * <p>The routine ios_driver is a branch-and-cut driver. It controls the MIP solution process.</p>
 * <p>RETURNS</p>
 * <p>0 The MIP problem instance has been successfully solved. This code does not necessarily mean that the solver has found optimal solution. It only means that the solution process was successful.</p>
 * <p>GLP_EFAIL The search was prematurely terminated due to the solver failure.</p>
 * <p>GLP_EMIPGAP The search was prematurely terminated, because the relative mip gap tolerance has been reached.</p>
 * <p>GLP_ETMLIM The search was prematurely terminated, because the time limit has been exceeded.</p>
 * <p>GLP_ESTOP The search was prematurely terminated by application. </p>
 */
public";

%csmethodmodifiers print_help(const char *my_name) "
/**
 */
public";

%csmethodmodifiers print_version(int briefly) "
/**
 */
public";

%csmethodmodifiers parse_cmdline(struct csa *csa, int argc, const char *argv[]) "
/**
 */
public";

%csmethodmodifiers glp_main(int argc, const char *argv[]) "
/**
 */
public";

%csmethodmodifiers gz_reset(gz_statep state) "
/**
 */
public";

%csmethodmodifiers gz_open(char *path, int fd, const char *mode) const "
/**
 */
public";

%csmethodmodifiers gzopen(char *path, const char *mode) const "
/**
 */
public";

%csmethodmodifiers gzopen64(char *path, const char *mode) const "
/**
 */
public";

%csmethodmodifiers gzdopen(int fd, const char *mode) "
/**
 */
public";

%csmethodmodifiers gzbuffer(gzFile file, unsigned size) "
/**
 */
public";

%csmethodmodifiers gzrewind(gzFile file) "
/**
 */
public";

%csmethodmodifiers gzseek64(gzFile file, z_off64_t offset, int whence) "
/**
 */
public";

%csmethodmodifiers gzseek(gzFile file, z_off_t offset, int whence) "
/**
 */
public";

%csmethodmodifiers gztell64(gzFile file) "
/**
 */
public";

%csmethodmodifiers gztell(gzFile file) "
/**
 */
public";

%csmethodmodifiers gzoffset64(gzFile file) "
/**
 */
public";

%csmethodmodifiers gzoffset(gzFile file) "
/**
 */
public";

%csmethodmodifiers gzeof(gzFile file) "
/**
 */
public";

%csmethodmodifiers gzerror(gzFile file, int *errnum) "
/**
 */
public";

%csmethodmodifiers gzclearerr(gzFile file) "
/**
 */
public";

%csmethodmodifiers gz_error(gz_statep state, int err, const char *msg) "
/**
 */
public";

%csmethodmodifiers gz_intmax() "
/**
 */
public";

%csmethodmodifiers alloc_content(MPL *mpl) "
/**
 */
public";

%csmethodmodifiers generate_model(MPL *mpl) "
/**
 */
public";

%csmethodmodifiers build_problem(MPL *mpl) "
/**
 */
public";

%csmethodmodifiers postsolve_model(MPL *mpl) "
/**
 */
public";

%csmethodmodifiers clean_model(MPL *mpl) "
/**
 */
public";

%csmethodmodifiers open_input(MPL *mpl, char *file) "
/**
 */
public";

%csmethodmodifiers read_char(MPL *mpl) "
/**
 */
public";

%csmethodmodifiers close_input(MPL *mpl) "
/**
 */
public";

%csmethodmodifiers open_output(MPL *mpl, char *file) "
/**
 */
public";

%csmethodmodifiers write_char(MPL *mpl, int c) "
/**
 */
public";

%csmethodmodifiers write_text(MPL *mpl, char *fmt,...) "
/**
 */
public";

%csmethodmodifiers flush_output(MPL *mpl) "
/**
 */
public";

%csmethodmodifiers error(MPL *mpl, char *fmt,...) "
/**
 */
public";

%csmethodmodifiers warning(MPL *mpl, char *fmt,...) "
/**
 */
public";

%csmethodmodifiers mpl_initialize(void) "
/**
 */
public";

%csmethodmodifiers mpl_read_model(MPL *mpl, char *file, int skip_data) "
/**
 */
public";

%csmethodmodifiers mpl_read_data(MPL *mpl, char *file) "
/**
 */
public";

%csmethodmodifiers mpl_generate(MPL *mpl, char *file) "
/**
 */
public";

%csmethodmodifiers mpl_get_prob_name(MPL *mpl) "
/**
 */
public";

%csmethodmodifiers mpl_get_num_rows(MPL *mpl) "
/**
 */
public";

%csmethodmodifiers mpl_get_num_cols(MPL *mpl) "
/**
 */
public";

%csmethodmodifiers mpl_get_row_name(MPL *mpl, int i) "
/**
 */
public";

%csmethodmodifiers mpl_get_row_kind(MPL *mpl, int i) "
/**
 */
public";

%csmethodmodifiers mpl_get_row_bnds(MPL *mpl, int i, double *_lb, double *_ub) "
/**
 */
public";

%csmethodmodifiers mpl_get_mat_row(MPL *mpl, int i, int ndx[], double val[]) "
/**
 */
public";

%csmethodmodifiers mpl_get_row_c0(MPL *mpl, int i) "
/**
 */
public";

%csmethodmodifiers mpl_get_col_name(MPL *mpl, int j) "
/**
 */
public";

%csmethodmodifiers mpl_get_col_kind(MPL *mpl, int j) "
/**
 */
public";

%csmethodmodifiers mpl_get_col_bnds(MPL *mpl, int j, double *_lb, double *_ub) "
/**
 */
public";

%csmethodmodifiers mpl_has_solve_stmt(MPL *mpl) "
/**
 */
public";

%csmethodmodifiers mpl_put_row_soln(MPL *mpl, int i, int stat, double prim, double dual) "
/**
 */
public";

%csmethodmodifiers mpl_put_col_soln(MPL *mpl, int j, int stat, double prim, double dual) "
/**
 */
public";

%csmethodmodifiers mpl_postsolve(MPL *mpl) "
/**
 */
public";

%csmethodmodifiers mpl_terminate(MPL *mpl) "
/**
 */
public";

%csmethodmodifiers glp_init_cpxcp(glp_cpxcp *parm) "
/**
 * glp_init_cpxcp - initialize CPLEX LP format control parameters .
 * <p>SYNOPSIS</p>
 * <p>void glp_init_cpxcp(glp_cpxcp *parm):</p>
 * <p>The routine glp_init_cpxcp initializes control parameters used by the CPLEX LP input/output routines glp_read_lp and glp_write_lp with default values.</p>
 * <p>Default values of the control parameters are stored in the glp_cpxcp structure, which the parameter parm points to. </p>
 */
public";

%csmethodmodifiers check_parm(const char *func, const glp_cpxcp *parm) "
/**
 */
public";

%csmethodmodifiers error(struct csa *csa, const char *fmt,...) "
/**
 */
public";

%csmethodmodifiers warning(struct csa *csa, const char *fmt,...) "
/**
 */
public";

%csmethodmodifiers read_char(struct csa *csa) "
/**
 */
public";

%csmethodmodifiers add_char(struct csa *csa) "
/**
 */
public";

%csmethodmodifiers the_same(char *s1, char *s2) "
/**
 */
public";

%csmethodmodifiers scan_token(struct csa *csa) "
/**
 */
public";

%csmethodmodifiers find_col(struct csa *csa, char *name) "
/**
 */
public";

%csmethodmodifiers parse_linear_form(struct csa *csa) "
/**
 */
public";

%csmethodmodifiers parse_objective(struct csa *csa) "
/**
 */
public";

%csmethodmodifiers parse_constraints(struct csa *csa) "
/**
 */
public";

%csmethodmodifiers set_lower_bound(struct csa *csa, int j, double lb) "
/**
 */
public";

%csmethodmodifiers set_upper_bound(struct csa *csa, int j, double ub) "
/**
 */
public";

%csmethodmodifiers parse_bounds(struct csa *csa) "
/**
 */
public";

%csmethodmodifiers parse_integer(struct csa *csa) "
/**
 */
public";

%csmethodmodifiers glp_read_lp(glp_prob *P, const glp_cpxcp *parm, const char *fname) "
/**
 */
public";

%csmethodmodifiers check_name(char *name) "
/**
 */
public";

%csmethodmodifiers adjust_name(char *name) "
/**
 */
public";

%csmethodmodifiers row_name(struct csa *csa, int i, char rname[255+1]) "
/**
 */
public";

%csmethodmodifiers col_name(struct csa *csa, int j, char cname[255+1]) "
/**
 */
public";

%csmethodmodifiers glp_write_lp(glp_prob *P, const glp_cpxcp *parm, const char *fname) "
/**
 */
public";

%csmethodmodifiers glp_get_prob_name(glp_prob *lp) "
/**
 * glp_get_prob_name - retrieve problem name .
 * <p>SYNOPSIS</p>
 * <p>const char *glp_get_prob_name(glp_prob *lp);</p>
 * <p>RETURNS</p>
 * <p>The routine glp_get_prob_name returns a pointer to an internal buffer, which contains symbolic name of the problem. However, if the problem has no assigned name, the routine returns NULL. </p>
 */
public";

%csmethodmodifiers glp_get_obj_name(glp_prob *lp) "
/**
 * glp_get_obj_name - retrieve objective function name .
 * <p>SYNOPSIS</p>
 * <p>const char *glp_get_obj_name(glp_prob *lp);</p>
 * <p>RETURNS</p>
 * <p>The routine glp_get_obj_name returns a pointer to an internal buffer, which contains a symbolic name of the objective function. However, if the objective function has no assigned name, the routine returns NULL. </p>
 */
public";

%csmethodmodifiers glp_get_obj_dir(glp_prob *lp) "
/**
 * glp_get_obj_dir - retrieve optimization direction flag .
 * <p>SYNOPSIS</p>
 * <p>int glp_get_obj_dir(glp_prob *lp);</p>
 * <p>RETURNS</p>
 * <p>The routine glp_get_obj_dir returns the optimization direction flag (i.e. \"sense\" of the objective function):</p>
 * <p>GLP_MIN - minimization; GLP_MAX - maximization. </p>
 */
public";

%csmethodmodifiers glp_get_num_rows(glp_prob *lp) "
/**
 * glp_get_num_rows - retrieve number of rows .
 * <p>SYNOPSIS</p>
 * <p>int glp_get_num_rows(glp_prob *lp);</p>
 * <p>RETURNS</p>
 * <p>The routine glp_get_num_rows returns the current number of rows in the specified problem object. </p>
 */
public";

%csmethodmodifiers glp_get_num_cols(glp_prob *lp) "
/**
 * glp_get_num_cols - retrieve number of columns .
 * <p>SYNOPSIS</p>
 * <p>int glp_get_num_cols(glp_prob *lp);</p>
 * <p>RETURNS</p>
 * <p>The routine glp_get_num_cols returns the current number of columns in the specified problem object. </p>
 */
public";

%csmethodmodifiers glp_get_row_name(glp_prob *lp, int i) "
/**
 * glp_get_row_name - retrieve row name .
 * <p>SYNOPSIS</p>
 * <p>const char *glp_get_row_name(glp_prob *lp, int i);</p>
 * <p>RETURNS</p>
 * <p>The routine glp_get_row_name returns a pointer to an internal buffer, which contains symbolic name of i-th row. However, if i-th row has no assigned name, the routine returns NULL. </p>
 */
public";

%csmethodmodifiers glp_get_col_name(glp_prob *lp, int j) "
/**
 * glp_get_col_name - retrieve column name .
 * <p>SYNOPSIS</p>
 * <p>const char *glp_get_col_name(glp_prob *lp, int j);</p>
 * <p>RETURNS</p>
 * <p>The routine glp_get_col_name returns a pointer to an internal buffer, which contains symbolic name of j-th column. However, if j-th column has no assigned name, the routine returns NULL. </p>
 */
public";

%csmethodmodifiers glp_get_row_type(glp_prob *lp, int i) "
/**
 * glp_get_row_type - retrieve row type .
 * <p>SYNOPSIS</p>
 * <p>int glp_get_row_type(glp_prob *lp, int i);</p>
 * <p>RETURNS</p>
 * <p>The routine glp_get_row_type returns the type of i-th row, i.e. the type of corresponding auxiliary variable, as follows:</p>
 * <p>GLP_FR - free (unbounded) variable; GLP_LO - variable with lower bound; GLP_UP - variable with upper bound; GLP_DB - double-bounded variable; GLP_FX - fixed variable. </p>
 */
public";

%csmethodmodifiers glp_get_row_lb(glp_prob *lp, int i) "
/**
 * glp_get_row_lb - retrieve row lower bound .
 * <p>SYNOPSIS</p>
 * <p>double glp_get_row_lb(glp_prob *lp, int i);</p>
 * <p>RETURNS</p>
 * <p>The routine glp_get_row_lb returns the lower bound of i-th row, i.e. the lower bound of corresponding auxiliary variable. However, if the row has no lower bound, the routine returns -DBL_MAX. </p>
 */
public";

%csmethodmodifiers glp_get_row_ub(glp_prob *lp, int i) "
/**
 * glp_get_row_ub - retrieve row upper bound .
 * <p>SYNOPSIS</p>
 * <p>double glp_get_row_ub(glp_prob *lp, int i);</p>
 * <p>RETURNS</p>
 * <p>The routine glp_get_row_ub returns the upper bound of i-th row, i.e. the upper bound of corresponding auxiliary variable. However, if the row has no upper bound, the routine returns +DBL_MAX. </p>
 */
public";

%csmethodmodifiers glp_get_col_type(glp_prob *lp, int j) "
/**
 * glp_get_col_type - retrieve column type .
 * <p>SYNOPSIS</p>
 * <p>int glp_get_col_type(glp_prob *lp, int j);</p>
 * <p>RETURNS</p>
 * <p>The routine glp_get_col_type returns the type of j-th column, i.e. the type of corresponding structural variable, as follows:</p>
 * <p>GLP_FR - free (unbounded) variable; GLP_LO - variable with lower bound; GLP_UP - variable with upper bound; GLP_DB - double-bounded variable; GLP_FX - fixed variable. </p>
 */
public";

%csmethodmodifiers glp_get_col_lb(glp_prob *lp, int j) "
/**
 * glp_get_col_lb - retrieve column lower bound .
 * <p>SYNOPSIS</p>
 * <p>double glp_get_col_lb(glp_prob *lp, int j);</p>
 * <p>RETURNS</p>
 * <p>The routine glp_get_col_lb returns the lower bound of j-th column, i.e. the lower bound of corresponding structural variable. However, if the column has no lower bound, the routine returns -DBL_MAX. </p>
 */
public";

%csmethodmodifiers glp_get_col_ub(glp_prob *lp, int j) "
/**
 * glp_get_col_ub - retrieve column upper bound .
 * <p>SYNOPSIS</p>
 * <p>double glp_get_col_ub(glp_prob *lp, int j);</p>
 * <p>RETURNS</p>
 * <p>The routine glp_get_col_ub returns the upper bound of j-th column, i.e. the upper bound of corresponding structural variable. However, if the column has no upper bound, the routine returns +DBL_MAX. </p>
 */
public";

%csmethodmodifiers glp_get_obj_coef(glp_prob *lp, int j) "
/**
 * glp_get_obj_coef - retrieve obj. .
 * <p>coefficient or constant term</p>
 * <p>SYNOPSIS</p>
 * <p>double glp_get_obj_coef(glp_prob *lp, int j);</p>
 * <p>RETURNS</p>
 * <p>The routine glp_get_obj_coef returns the objective coefficient at j-th structural variable (column) of the specified problem object.</p>
 * <p>If the parameter j is zero, the routine returns the constant term (\"shift\") of the objective function. </p>
 */
public";

%csmethodmodifiers glp_get_num_nz(glp_prob *lp) "
/**
 * glp_get_num_nz - retrieve number of constraint coefficients .
 * <p>SYNOPSIS</p>
 * <p>int glp_get_num_nz(glp_prob *lp);</p>
 * <p>RETURNS</p>
 * <p>The routine glp_get_num_nz returns the number of (non-zero) elements in the constraint matrix of the specified problem object. </p>
 */
public";

%csmethodmodifiers glp_get_mat_row(glp_prob *lp, int i, int ind[], double val[]) "
/**
 * glp_get_mat_row - retrieve row of the constraint matrix .
 * <p>SYNOPSIS</p>
 * <p>int glp_get_mat_row(glp_prob *lp, int i, int ind[], double val[]);</p>
 * <p>DESCRIPTION</p>
 * <p>The routine glp_get_mat_row scans (non-zero) elements of i-th row of the constraint matrix of the specified problem object and stores their column indices and numeric values to locations ind[1], ..., ind[len] and val[1], ..., val[len], respectively, where 0 &lt;= len &lt;= n is the number of elements in i-th row, n is the number of columns.</p>
 * <p>The parameter ind and/or val can be specified as NULL, in which case corresponding information is not stored.</p>
 * <p>RETURNS</p>
 * <p>The routine glp_get_mat_row returns the length len, i.e. the number of (non-zero) elements in i-th row. </p>
 */
public";

%csmethodmodifiers glp_get_mat_col(glp_prob *lp, int j, int ind[], double val[]) "
/**
 * glp_get_mat_col - retrieve column of the constraint matrix .
 * <p>SYNOPSIS</p>
 * <p>int glp_get_mat_col(glp_prob *lp, int j, int ind[], double val[]);</p>
 * <p>DESCRIPTION</p>
 * <p>The routine glp_get_mat_col scans (non-zero) elements of j-th column of the constraint matrix of the specified problem object and stores their row indices and numeric values to locations ind[1], ..., ind[len] and val[1], ..., val[len], respectively, where 0 &lt;= len &lt;= m is the number of elements in j-th column, m is the number of rows.</p>
 * <p>The parameter ind or/and val can be specified as NULL, in which case corresponding information is not stored.</p>
 * <p>RETURNS</p>
 * <p>The routine glp_get_mat_col returns the length len, i.e. the number of (non-zero) elements in j-th column. </p>
 */
public";

%csmethodmodifiers ymalloc(int size) "
/**
 */
public";

%csmethodmodifiers yrealloc(void *ptr, int size) "
/**
 */
public";

%csmethodmodifiers yfree(void *ptr) "
/**
 */
public";

%csmethodmodifiers drand(double *seed) "
/**
 */
public";

%csmethodmodifiers irand(double *seed, int size) "
/**
 */
public";

%csmethodmodifiers sort(void **array, int size, int(*comp)(const void *, const void *)) "
/**
 */
public";

%csmethodmodifiers vecp_remove(vecp *v, void *e) "
/**
 */
public";

%csmethodmodifiers order_update(solver *s, int v) "
/**
 */
public";

%csmethodmodifiers order_unassigned(solver *s, int v) "
/**
 */
public";

%csmethodmodifiers order_select(solver *s, float random_var_freq) "
/**
 */
public";

%csmethodmodifiers act_var_rescale(solver *s) "
/**
 */
public";

%csmethodmodifiers act_var_bump(solver *s, int v) "
/**
 */
public";

%csmethodmodifiers act_var_decay(solver *s) "
/**
 */
public";

%csmethodmodifiers act_clause_rescale(solver *s) "
/**
 */
public";

%csmethodmodifiers act_clause_bump(solver *s, clause *c) "
/**
 */
public";

%csmethodmodifiers act_clause_decay(solver *s) "
/**
 */
public";

%csmethodmodifiers clause_new(solver *s, lit *begin, lit *end, int learnt) "
/**
 */
public";

%csmethodmodifiers clause_remove(solver *s, clause *c) "
/**
 */
public";

%csmethodmodifiers clause_simplify(solver *s, clause *c) "
/**
 */
public";

%csmethodmodifiers solver_setnvars(solver *s, int n) "
/**
 */
public";

%csmethodmodifiers enqueue(solver *s, lit l, clause *from) "
/**
 */
public";

%csmethodmodifiers assume(solver *s, lit l) "
/**
 */
public";

%csmethodmodifiers solver_canceluntil(solver *s, int level) "
/**
 */
public";

%csmethodmodifiers solver_record(solver *s, veci *cls) "
/**
 */
public";

%csmethodmodifiers solver_progress(solver *s) "
/**
 */
public";

%csmethodmodifiers solver_lit_removable(solver *s, lit l, int minl) "
/**
 */
public";

%csmethodmodifiers solver_analyze(solver *s, clause *c, veci *learnt) "
/**
 */
public";

%csmethodmodifiers solver_propagate(solver *s) "
/**
 */
public";

%csmethodmodifiers clause_cmp(const void *x, const void *y) "
/**
 */
public";

%csmethodmodifiers solver_reducedb(solver *s) "
/**
 */
public";

%csmethodmodifiers solver_search(solver *s, int nof_conflicts, int nof_learnts) "
/**
 */
public";

%csmethodmodifiers solver_new(void) "
/**
 */
public";

%csmethodmodifiers solver_delete(solver *s) "
/**
 */
public";

%csmethodmodifiers solver_addclause(solver *s, lit *begin, lit *end) "
/**
 */
public";

%csmethodmodifiers solver_simplify(solver *s) "
/**
 */
public";

%csmethodmodifiers solver_solve(solver *s, lit *begin, lit *end) "
/**
 */
public";

%csmethodmodifiers solver_nvars(solver *s) "
/**
 */
public";

%csmethodmodifiers solver_nclauses(solver *s) "
/**
 */
public";

%csmethodmodifiers solver_nconflicts(solver *s) "
/**
 */
public";

%csmethodmodifiers selectionsort(void **array, int size, int(*comp)(const void *, const void *)) "
/**
 */
public";

%csmethodmodifiers sortrnd(void **array, int size, int(*comp)(const void *, const void *), double *seed) "
/**
 */
public";

%csmethodmodifiers zlibVersion() "
/**
 */
public";

%csmethodmodifiers zlibCompileFlags() "
/**
 */
public";

%csmethodmodifiers zError(int err) "
/**
 */
public";

%csmethodmodifiers zcalloc(voidpf opaque, unsigned items, unsigned size) "
/**
 */
public";

%csmethodmodifiers zcfree(voidpf opaque, voidpf ptr) "
/**
 */
public";

%csmethodmodifiers spy_chuzc_std(SPXLP *lp, const double d[], double s, const double trow[], double tol_piv, double tol, double tol1) "
/**
 */
public";

%csmethodmodifiers spy_chuzc_harris(SPXLP *lp, const double d[], double s, const double trow[], double tol_piv, double tol, double tol1) "
/**
 */
public";

%csmethodmodifiers min_row_aij(glp_prob *lp, int i, int scaled) "
/**
 */
public";

%csmethodmodifiers max_row_aij(glp_prob *lp, int i, int scaled) "
/**
 */
public";

%csmethodmodifiers min_col_aij(glp_prob *lp, int j, int scaled) "
/**
 */
public";

%csmethodmodifiers max_col_aij(glp_prob *lp, int j, int scaled) "
/**
 */
public";

%csmethodmodifiers min_mat_aij(glp_prob *lp, int scaled) "
/**
 */
public";

%csmethodmodifiers max_mat_aij(glp_prob *lp, int scaled) "
/**
 */
public";

%csmethodmodifiers eq_scaling(glp_prob *lp, int flag) "
/**
 */
public";

%csmethodmodifiers gm_scaling(glp_prob *lp, int flag) "
/**
 */
public";

%csmethodmodifiers max_row_ratio(glp_prob *lp) "
/**
 */
public";

%csmethodmodifiers max_col_ratio(glp_prob *lp) "
/**
 */
public";

%csmethodmodifiers gm_iterate(glp_prob *lp, int it_max, double tau) "
/**
 */
public";

%csmethodmodifiers scale_prob(glp_prob *lp, int flags) "
/**
 * scale_prob - scale problem data .
 * <p>SYNOPSIS</p>
 * <p>#include \"glpscl.h\" void scale_prob(glp_prob *lp, int flags);</p>
 * <p>DESCRIPTION</p>
 * <p>The routine scale_prob performs automatic scaling of problem data for the specified problem object. </p>
 */
public";

%csmethodmodifiers glp_scale_prob(glp_prob *lp, int flags) "
/**
 * glp_scale_prob - scale problem data .
 * <p>SYNOPSIS</p>
 * <p>void glp_scale_prob(glp_prob *lp, int flags);</p>
 * <p>DESCRIPTION</p>
 * <p>The routine glp_scale_prob performs automatic scaling of problem data for the specified problem object.</p>
 * <p>The parameter flags specifies scaling options used by the routine. Options can be combined with the bitwise OR operator and may be the following:</p>
 * <p>GLP_SF_GM perform geometric mean scaling; GLP_SF_EQ perform equilibration scaling; GLP_SF_2N round scale factors to nearest power of two; GLP_SF_SKIP skip scaling, if the problem is well scaled.</p>
 * <p>The parameter flags may be specified as GLP_SF_AUTO, in which case the routine chooses scaling options automatically. </p>
 */
public";

%csmethodmodifiers show_progress(SSX *ssx, int phase) "
/**
 */
public";

%csmethodmodifiers ssx_phase_I(SSX *ssx) "
/**
 */
public";

%csmethodmodifiers ssx_phase_II(SSX *ssx) "
/**
 */
public";

%csmethodmodifiers ssx_driver(SSX *ssx) "
/**
 */
public";

%csmethodmodifiers jday(int d, int m, int y) "
/**
 * jday - convert calendar date to Julian day number .
 * <p>SYNOPSIS</p>
 * <p>#include \"jd.h\" int jday(int d, int m, int y);</p>
 * <p>DESCRIPTION</p>
 * <p>The routine jday converts a calendar date, Gregorian calendar, to corresponding Julian day number j.</p>
 * <p>From the given day d, month m, and year y, the Julian day number j is computed without using tables.</p>
 * <p>The routine is valid for 1 &lt;= y &lt;= 4000.</p>
 * <p>RETURNS</p>
 * <p>The routine jday returns the Julian day number, or negative value if the specified date is incorrect.</p>
 * <p>REFERENCES</p>
 * <p>R. G. Tantzen, Algorithm 199: conversions between calendar date and Julian day number, Communications of the ACM, vol. 6, no. 8, p. 444, Aug. 1963. </p>
 */
public";

%csmethodmodifiers jdate(int j, int *d_, int *m_, int *y_) "
/**
 * jdate - convert Julian day number to calendar date .
 * <p>SYNOPSIS</p>
 * <p>#include \"jd.h\" int jdate(int j, int *d, int *m, int *y);</p>
 * <p>DESCRIPTION</p>
 * <p>The routine jdate converts a Julian day number j to corresponding calendar date, Gregorian calendar.</p>
 * <p>The day d, month m, and year y are computed without using tables and stored in corresponding locations.</p>
 * <p>The routine is valid for 1721426 &lt;= j &lt;= 3182395.</p>
 * <p>RETURNS</p>
 * <p>If the conversion is successful, the routine returns zero, otherwise non-zero.</p>
 * <p>REFERENCES</p>
 * <p>R. G. Tantzen, Algorithm 199: conversions between calendar date and Julian day number, Communications of the ACM, vol. 6, no. 8, p. 444, Aug. 1963. </p>
 */
public";

%csmethodmodifiers glp_time(void) "
/**
 */
public";

%csmethodmodifiers glp_difftime(double t1, double t0) "
/**
 * glp_difftime - compute difference between two time values .
 * <p>SYNOPSIS</p>
 * <p>double glp_difftime(double t1, double t0);</p>
 * <p>RETURNS</p>
 * <p>The routine glp_difftime returns the difference between two time values t1 and t0, expressed in seconds. </p>
 */
public";

%csmethodmodifiers jth_col(void *info, int j, int ind[], double val[]) "
/**
 */
public";

%csmethodmodifiers spx_factorize(SPXLP *lp) "
/**
 */
public";

%csmethodmodifiers spx_eval_beta(SPXLP *lp, double beta[]) "
/**
 */
public";

%csmethodmodifiers spx_eval_obj(SPXLP *lp, const double beta[]) "
/**
 */
public";

%csmethodmodifiers spx_eval_pi(SPXLP *lp, double pi[]) "
/**
 */
public";

%csmethodmodifiers spx_eval_dj(SPXLP *lp, const double pi[], int j) "
/**
 */
public";

%csmethodmodifiers spx_eval_tcol(SPXLP *lp, int j, double tcol[]) "
/**
 */
public";

%csmethodmodifiers spx_eval_rho(SPXLP *lp, int i, double rho[]) "
/**
 */
public";

%csmethodmodifiers spx_eval_tij(SPXLP *lp, const double rho[], int j) "
/**
 */
public";

%csmethodmodifiers spx_eval_trow(SPXLP *lp, const double rho[], double trow[]) "
/**
 */
public";

%csmethodmodifiers spx_update_beta(SPXLP *lp, double beta[], int p, int p_flag, int q, const double tcol[]) "
/**
 */
public";

%csmethodmodifiers spx_update_d(SPXLP *lp, double d[], int p, int q, const double trow[], const double tcol[]) "
/**
 */
public";

%csmethodmodifiers spx_change_basis(SPXLP *lp, int p, int p_flag, int q) "
/**
 */
public";

%csmethodmodifiers spx_update_invb(SPXLP *lp, int i, int k) "
/**
 */
public";

%csmethodmodifiers glp_init_mpscp(glp_mpscp *parm) "
/**
 * glp_init_mpscp - initialize MPS format control parameters .
 * <p>SYNOPSIS</p>
 * <p>void glp_init_mpscp(glp_mpscp *parm);</p>
 * <p>DESCRIPTION</p>
 * <p>The routine glp_init_mpscp initializes control parameters, which are used by the MPS input/output routines glp_read_mps and glp_write_mps, with default values.</p>
 * <p>Default values of the control parameters are stored in the glp_mpscp structure, which the parameter parm points to. </p>
 */
public";

%csmethodmodifiers check_parm(const char *func, const glp_mpscp *parm) "
/**
 */
public";

%csmethodmodifiers error(struct csa *csa, const char *fmt,...) "
/**
 */
public";

%csmethodmodifiers warning(struct csa *csa, const char *fmt,...) "
/**
 */
public";

%csmethodmodifiers read_char(struct csa *csa) "
/**
 */
public";

%csmethodmodifiers indicator(struct csa *csa, int name) "
/**
 */
public";

%csmethodmodifiers read_field(struct csa *csa) "
/**
 */
public";

%csmethodmodifiers patch_name(struct csa *csa, char *name) "
/**
 */
public";

%csmethodmodifiers read_number(struct csa *csa) "
/**
 */
public";

%csmethodmodifiers skip_field(struct csa *csa) "
/**
 */
public";

%csmethodmodifiers read_name(struct csa *csa) "
/**
 */
public";

%csmethodmodifiers read_rows(struct csa *csa) "
/**
 */
public";

%csmethodmodifiers read_columns(struct csa *csa) "
/**
 */
public";

%csmethodmodifiers read_rhs(struct csa *csa) "
/**
 */
public";

%csmethodmodifiers read_ranges(struct csa *csa) "
/**
 */
public";

%csmethodmodifiers read_bounds(struct csa *csa) "
/**
 */
public";

%csmethodmodifiers glp_read_mps(glp_prob *P, int fmt, const glp_mpscp *parm, const char *fname) "
/**
 */
public";

%csmethodmodifiers mps_name(struct csa *csa) "
/**
 */
public";

%csmethodmodifiers row_name(struct csa *csa, int i) "
/**
 */
public";

%csmethodmodifiers col_name(struct csa *csa, int j) "
/**
 */
public";

%csmethodmodifiers mps_numb(struct csa *csa, double val) "
/**
 */
public";

%csmethodmodifiers glp_write_mps(glp_prob *P, int fmt, const glp_mpscp *parm, const char *fname) "
/**
 */
public";

%csmethodmodifiers dmp_create_pool(void) "
/**
 * dmp_create_pool - create dynamic memory pool .
 * <p>SYNOPSIS</p>
 * <p>#include \"dmp.h\" DMP *dmp_create_pool(void);</p>
 * <p>DESCRIPTION</p>
 * <p>The routine dmp_create_pool creates a dynamic memory pool.</p>
 * <p>RETURNS</p>
 * <p>The routine returns a pointer to the memory pool created. </p>
 */
public";

%csmethodmodifiers dmp_get_atom(DMP *pool, int size) "
/**
 * dmp_get_atom - get free atom from dynamic memory pool .
 * <p>SYNOPSIS</p>
 * <p>#include \"dmp.h\" void *dmp_get_atom(DMP *pool, int size);</p>
 * <p>DESCRIPTION</p>
 * <p>The routine dmp_get_atom obtains a free atom (memory space) from the specified memory pool.</p>
 * <p>The parameter size is the atom size, in bytes, 1 &lt;= size &lt;= 256.</p>
 * <p>Note that the free atom contains arbitrary data, not binary zeros.</p>
 * <p>RETURNS</p>
 * <p>The routine returns a pointer to the free atom obtained. </p>
 */
public";

%csmethodmodifiers dmp_free_atom(DMP *pool, void *atom, int size) "
/**
 * dmp_free_atom - return atom to dynamic memory pool .
 * <p>SYNOPSIS</p>
 * <p>#include \"dmp.h\" void dmp_free_atom(DMP *pool, void *atom, int size);</p>
 * <p>DESCRIPTION</p>
 * <p>The routine dmp_free_atom returns the specified atom (memory space) to the specified memory pool, making the atom free.</p>
 * <p>The parameter size is the atom size, in bytes, 1 &lt;= size &lt;= 256.</p>
 * <p>Note that the atom can be returned only to the pool, from which it was obtained, and its size must be exactly the same as on obtaining it from the pool. </p>
 */
public";

%csmethodmodifiers dmp_in_use(DMP *pool) "
/**
 * dmp_in_use - determine how many atoms are still in use .
 * <p>SYNOPSIS</p>
 * <p>#include \"dmp.h\" size_t dmp_in_use(DMP *pool);</p>
 * <p>RETURNS</p>
 * <p>The routine returns the number of atoms of the specified memory pool which are still in use. </p>
 */
public";

%csmethodmodifiers dmp_delete_pool(DMP *pool) "
/**
 * dmp_delete_pool - delete dynamic memory pool .
 * <p>SYNOPSIS</p>
 * <p>#include \"dmp.h\" void dmp_delete_pool(DMP *pool);</p>
 * <p>DESCRIPTION</p>
 * <p>The routine dmp_delete_pool deletes the specified dynamic memory pool freeing all the memory allocated to this object. </p>
 */
public";

%csmethodmodifiers mc21a(int n, const int icn[], const int ip[], const int lenr[], int iperm[], int pr[], int arp[], int cv[], int out[]) "
/**
 * mc21a - permutations for zero-free diagonal .
 * <p>SYNOPSIS</p>
 * <p>#include \"mc21a.h\" int mc21a(int n, const int icn[], const int ip[], const int lenr[], int iperm[], int pr[], int arp[], int cv[], int out[]);</p>
 * <p>DESCRIPTION</p>
 * <p>Given the pattern of nonzeros of a sparse matrix, the routine mc21a attempts to find a permutation of its rows that makes the matrix have no zeros on its diagonal.</p>
 * <p>INPUT PARAMETERS</p>
 * <p>n order of matrix.</p>
 * <p>icn array containing the column indices of the non-zeros. Those belonging to a single row must be contiguous but the ordering of column indices within each row is unimportant and wasted space between rows is permitted.</p>
 * <p>ip ip[i], i = 1,2,...,n, is the position in array icn of the first column index of a non-zero in row i.</p>
 * <p>lenr lenr[i], i = 1,2,...,n, is the number of non-zeros in row i.</p>
 * <p>OUTPUT PARAMETER</p>
 * <p>iperm contains permutation to make diagonal have the smallest number of zeros on it. Elements (iperm[i], i), i = 1,2,...,n, are non-zero at the end of the algorithm unless the matrix is structurally singular. In this case, (iperm[i], i) will be zero for n - numnz entries.</p>
 * <p>WORKING ARRAYS</p>
 * <p>pr working array of length [1+n], where pr[0] is not used. pr[i] is the previous row to i in the depth first search.</p>
 * <p>arp working array of length [1+n], where arp[0] is not used. arp[i] is one less than the number of non-zeros in row i which have not been scanned when looking for a cheap assignment.</p>
 * <p>cv working array of length [1+n], where cv[0] is not used. cv[i] is the most recent row extension at which column i was visited.</p>
 * <p>out working array of length [1+n], where out[0] is not used. out[i] is one less than the number of non-zeros in row i which have not been scanned during one pass through the main loop.</p>
 * <p>RETURNS</p>
 * <p>The routine mc21a returns numnz, the number of non-zeros on diagonal of permuted matrix. </p>
 */
public";

%csmethodmodifiers make_edge(struct csa *csa, int from, int to, int c1, int c2) "
/**
 */
public";

%csmethodmodifiers permute(struct csa *csa) "
/**
 */
public";

%csmethodmodifiers connect(struct csa *csa, int offset, int cv, int x1, int y1) "
/**
 */
public";

%csmethodmodifiers gen_rmf(struct csa *csa, int a, int b, int c1, int c2) "
/**
 */
public";

%csmethodmodifiers print_max_format(struct csa *csa, network *n, char *comm[], int dim) "
/**
 */
public";

%csmethodmodifiers gen_free_net(network *n) "
/**
 */
public";

%csmethodmodifiers glp_rmfgen(glp_graph *G_, int *_s, int *_t, int _a_cap, const int parm[1+5]) "
/**
 */
public";

%csmethodmodifiers fcmp(const void *ptr1, const void *ptr2) "
/**
 */
public";

%csmethodmodifiers get_column(glp_prob *lp, int j, int ind[], double val[]) "
/**
 */
public";

%csmethodmodifiers cpx_basis(glp_prob *lp) "
/**
 */
public";

%csmethodmodifiers glp_cpx_basis(glp_prob *lp) "
/**
 * glp_cpx_basis - construct Bixby's initial LP basis .
 * <p>SYNOPSIS</p>
 * <p>void glp_cpx_basis(glp_prob *lp);</p>
 * <p>DESCRIPTION</p>
 * <p>The routine glp_cpx_basis constructs an advanced initial basis for the specified problem object.</p>
 * <p>The routine is based on Bixby's algorithm described in the paper:</p>
 * <p>Robert E. Bixby. Implementing the Simplex Method: The Initial Basis. ORSA Journal on Computing, Vol. 4, No. 3, 1992, pp. 267-84. </p>
 */
public";

%csmethodmodifiers ios_clq_init(glp_tree *T) "
/**
 */
public";

%csmethodmodifiers ios_clq_gen(glp_tree *T, void *G_) "
/**
 */
public";

%csmethodmodifiers ios_clq_term(void *G_) "
/**
 */
public";

%csmethodmodifiers init_rows_cols(Int n_row, Int n_col, Colamd_Row Row[], Colamd_Col Col[], Int A[], Int p[], Int stats[COLAMD_STATS]) "
/**
 */
public";

%csmethodmodifiers init_scoring(Int n_row, Int n_col, Colamd_Row Row[], Colamd_Col Col[], Int A[], Int head[], double knobs[COLAMD_KNOBS], Int *p_n_row2, Int *p_n_col2, Int *p_max_deg) "
/**
 */
public";

%csmethodmodifiers find_ordering(Int n_row, Int n_col, Int Alen, Colamd_Row Row[], Colamd_Col Col[], Int A[], Int head[], Int n_col2, Int max_deg, Int pfree, Int aggressive) "
/**
 */
public";

%csmethodmodifiers order_children(Int n_col, Colamd_Col Col[], Int p[]) "
/**
 */
public";

%csmethodmodifiers detect_super_cols(Colamd_Col Col[], Int A[], Int head[], Int row_start, Int row_length) "
/**
 */
public";

%csmethodmodifiers garbage_collection(Int n_row, Int n_col, Colamd_Row Row[], Colamd_Col Col[], Int A[], Int *pfree) "
/**
 */
public";

%csmethodmodifiers clear_mark(Int tag_mark, Int max_mark, Int n_row, Colamd_Row Row[]) "
/**
 */
public";

%csmethodmodifiers print_report(char *method, Int stats[COLAMD_STATS]) "
/**
 */
public";

%csmethodmodifiers t_add(size_t a, size_t b, int *ok) "
/**
 */
public";

%csmethodmodifiers t_mult(size_t a, size_t k, int *ok) "
/**
 */
public";

%csmethodmodifiers COLAMD_recommended(Int nnz, Int n_row, Int n_col) "
/**
 */
public";

%csmethodmodifiers COLAMD_set_defaults(double knobs[COLAMD_KNOBS]) "
/**
 */
public";

%csmethodmodifiers SYMAMD_MAIN(Int n, Int A[], Int p[], Int perm[], double knobs[COLAMD_KNOBS], Int stats[COLAMD_STATS], void *(*allocate)(size_t, size_t), void(*release)(void *)) "
/**
 */
public";

%csmethodmodifiers COLAMD_MAIN(Int n_row, Int n_col, Int Alen, Int A[], Int p[], double knobs[COLAMD_KNOBS], Int stats[COLAMD_STATS]) "
/**
 */
public";

%csmethodmodifiers COLAMD_report(Int stats[COLAMD_STATS]) "
/**
 */
public";

%csmethodmodifiers SYMAMD_report(Int stats[COLAMD_STATS]) "
/**
 */
public";

%csmethodmodifiers check_flags(struct csa *csa) "
/**
 */
public";

%csmethodmodifiers set_art_bounds(struct csa *csa) "
/**
 */
public";

%csmethodmodifiers set_orig_bounds(struct csa *csa) "
/**
 */
public";

%csmethodmodifiers check_feas(struct csa *csa, double tol, double tol1, int recov) "
/**
 */
public";

%csmethodmodifiers choose_pivot(struct csa *csa) "
/**
 */
public";

%csmethodmodifiers display(struct csa *csa, int spec) "
/**
 */
public";

%csmethodmodifiers dual_simplex(struct csa *csa) "
/**
 */
public";

%csmethodmodifiers spy_dual(glp_prob *P, const glp_smcp *parm) "
/**
 */
public";

%csmethodmodifiers avl_create_tree(int(*fcmp)(void *info, const void *key1, const void *key2), void *info) "
/**
 */
public";

%csmethodmodifiers avl_strcmp(void *info, const void *key1, const void *key2) "
/**
 */
public";

%csmethodmodifiers rotate_subtree(AVL *tree, AVLNODE *node) "
/**
 */
public";

%csmethodmodifiers avl_insert_node(AVL *tree, const void *key) "
/**
 */
public";

%csmethodmodifiers avl_set_node_type(AVLNODE *node, int type) "
/**
 */
public";

%csmethodmodifiers avl_set_node_link(AVLNODE *node, void *link) "
/**
 */
public";

%csmethodmodifiers avl_find_node(AVL *tree, const void *key) "
/**
 */
public";

%csmethodmodifiers avl_get_node_type(AVLNODE *node) "
/**
 */
public";

%csmethodmodifiers avl_get_node_link(AVLNODE *node) "
/**
 */
public";

%csmethodmodifiers find_next_node(AVL *tree, AVLNODE *node) "
/**
 */
public";

%csmethodmodifiers avl_delete_node(AVL *tree, AVLNODE *node) "
/**
 */
public";

%csmethodmodifiers avl_delete_tree(AVL *tree) "
/**
 */
public";

%csmethodmodifiers triang(int m, int n, int(*mat)(void *info, int k, int ind[], double val[]), void *info, double tol, int rn[], int cn[]) "
/**
 */
public";
%csmethodmodifiers btfint_create(void) "
/**
 */
public";

%csmethodmodifiers factorize_triv(BTFINT *fi, int k, int(*col)(void *info, int j, int ind[], double val[]), void *info) "
/**
 */
public";

%csmethodmodifiers factorize_block(BTFINT *fi, int k, int(*col)(void *info, int j, int ind[], double val[]), void *info) "
/**
 */
public";

%csmethodmodifiers btfint_factorize(BTFINT *fi, int n, int(*col)(void *info, int j, int ind[], double val[]), void *info) "
/**
 */
public";

%csmethodmodifiers btfint_delete(BTFINT *fi) "
/**
 */
public";

%csmethodmodifiers gz_init(gz_statep state) "
/**
 */
public";

%csmethodmodifiers gz_comp(gz_statep state, int flush) "
/**
 */
public";

%csmethodmodifiers gz_zero(gz_statep state, z_off64_t len) "
/**
 */
public";

%csmethodmodifiers gzwrite(gzFile file, voidpc buf, unsigned len) "
/**
 */
public";

%csmethodmodifiers gzputc(gzFile file, int c) "
/**
 */
public";

%csmethodmodifiers gzputs(gzFile file, const char *str) "
/**
 */
public";

%csmethodmodifiers gzprintf(gzFile file, const char *format,...) "
/**
 */
public";

%csmethodmodifiers gzflush(gzFile file, int flush) "
/**
 */
public";

%csmethodmodifiers gzsetparams(gzFile file, int level, int strategy) "
/**
 */
public";

%csmethodmodifiers gzclose_w(gzFile file) "
/**
 */
public";

%csmethodmodifiers compress2(Bytef *dest, uLongf *destLen, const Bytef *source, uLong sourceLen, int level) "
/**
 */
public";

%csmethodmodifiers compress(Bytef *dest, uLongf *destLen, const Bytef *source, uLong sourceLen) "
/**
 */
public";

%csmethodmodifiers compressBound(uLong sourceLen) "
/**
 */
public";

%csmethodmodifiers read_card(struct dsa *dsa) "
/**
 */
public";

%csmethodmodifiers scan_int(struct dsa *dsa, char *fld, int pos, int width, int *val) "
/**
 */
public";

%csmethodmodifiers parse_fmt(struct dsa *dsa, char *fmt) "
/**
 */
public";

%csmethodmodifiers read_int_array(struct dsa *dsa, char *name, char *fmt, int n, int val[]) "
/**
 */
public";

%csmethodmodifiers read_real_array(struct dsa *dsa, char *name, char *fmt, int n, double val[]) "
/**
 */
public";

%csmethodmodifiers hbm_read_mat(const char *fname) "
/**
 */
public";

%csmethodmodifiers hbm_free_mat(HBM *hbm) "
/**
 * hbm_free_mat - free sparse matrix in Harwell-Boeing format .
 * <p>SYNOPSIS</p>
 * <p>#include \"glphbm.h\" void hbm_free_mat(HBM *hbm);</p>
 * <p>DESCRIPTION</p>
 * <p>The hbm_free_mat routine frees all the memory allocated to the data structure containing a sparse matrix in the Harwell-Boeing format. </p>
 */
public";

%csmethodmodifiers glp_set_row_stat(glp_prob *lp, int i, int stat) "
/**
 * glp_set_row_stat - set (change) row status .
 * <p>SYNOPSIS</p>
 * <p>void glp_set_row_stat(glp_prob *lp, int i, int stat);</p>
 * <p>DESCRIPTION</p>
 * <p>The routine glp_set_row_stat sets (changes) status of the auxiliary variable associated with i-th row.</p>
 * <p>The new status of the auxiliary variable should be specified by the parameter stat as follows:</p>
 * <p>GLP_BS - basic variable; GLP_NL - non-basic variable; GLP_NU - non-basic variable on its upper bound; if the variable is not double-bounded, this means the same as GLP_NL (only in case of this routine); GLP_NF - the same as GLP_NL (only in case of this routine); GLP_NS - the same as GLP_NL (only in case of this routine). </p>
 */
public";

%csmethodmodifiers glp_set_col_stat(glp_prob *lp, int j, int stat) "
/**
 * glp_set_col_stat - set (change) column status .
 * <p>SYNOPSIS</p>
 * <p>void glp_set_col_stat(glp_prob *lp, int j, int stat);</p>
 * <p>DESCRIPTION</p>
 * <p>The routine glp_set_col_stat sets (changes) status of the structural variable associated with j-th column.</p>
 * <p>The new status of the structural variable should be specified by the parameter stat as follows:</p>
 * <p>GLP_BS - basic variable; GLP_NL - non-basic variable; GLP_NU - non-basic variable on its upper bound; if the variable is not double-bounded, this means the same as GLP_NL (only in case of this routine); GLP_NF - the same as GLP_NL (only in case of this routine); GLP_NS - the same as GLP_NL (only in case of this routine). </p>
 */
public";

%csmethodmodifiers glp_std_basis(glp_prob *lp) "
/**
 * glp_std_basis - construct standard initial LP basis .
 * <p>SYNOPSIS</p>
 * <p>void glp_std_basis(glp_prob *lp);</p>
 * <p>DESCRIPTION</p>
 * <p>The routine glp_std_basis builds the \"standard\" (trivial) initial basis for the specified problem object.</p>
 * <p>In the \"standard\" basis all auxiliary variables are basic, and all structural variables are non-basic. </p>
 */
public";

%csmethodmodifiers glp_intfeas1(glp_prob *P, int use_bound, int obj_bound) "
/**
 */
public";

%csmethodmodifiers strspx(char *str) "
/**
 * strspx - remove all spaces from character string .
 * <p>SYNOPSIS</p>
 * <p>#include \"misc.h\" char *strspx(char *str);</p>
 * <p>DESCRIPTION</p>
 * <p>The routine strspx removes all spaces from the character string str.</p>
 * <p>RETURNS</p>
 * <p>The routine returns a pointer to the character string.</p>
 * <p>EXAMPLES</p>
 * <p>strspx(\"   Errare   humanum   est   \") => \"Errarehumanumest\"</p>
 * <p>strspx(\"      \") => \"\" </p>
 */
public";

%csmethodmodifiers kellerman(int n, int(*func)(void *info, int i, int ind[]), void *info, void *H_) "
/**
 */
public";

%csmethodmodifiers ifu_expand(IFU *ifu, double c[], double r[], double d) "
/**
 */
public";

%csmethodmodifiers ifu_bg_update(IFU *ifu, double c[], double r[], double d) "
/**
 */
public";

%csmethodmodifiers givens(double a, double b, double *c, double *s) "
/**
 */
public";

%csmethodmodifiers ifu_gr_update(IFU *ifu, double c[], double r[], double d) "
/**
 */
public";

%csmethodmodifiers ifu_a_solve(IFU *ifu, double x[], double w[]) "
/**
 */
public";

%csmethodmodifiers ifu_at_solve(IFU *ifu, double x[], double w[]) "
/**
 */
public";

%csmethodmodifiers cfg_create_graph(int n, int nv_max) "
/**
 */
public";

%csmethodmodifiers add_edge(CFG *G, int v, int w) "
/**
 */
public";

%csmethodmodifiers cfg_add_clique(CFG *G, int size, const int ind[]) "
/**
 */
public";

%csmethodmodifiers cfg_get_adjacent(CFG *G, int v, int ind[]) "
/**
 */
public";

%csmethodmodifiers intersection(int d_len, int d_ind[], int d_pos[], int len, const int ind[]) "
/**
 */
public";

%csmethodmodifiers cfg_expand_clique(CFG *G, int c_len, int c_ind[]) "
/**
 */
public";

%csmethodmodifiers cfg_check_clique(CFG *G, int c_len, const int c_ind[]) "
/**
 */
public";

%csmethodmodifiers cfg_delete_graph(CFG *G) "
/**
 */
public";

%csmethodmodifiers AMD_post_tree(Int root, Int k, Int Child[], const Int Sibling[], Int Order[], Int Stack[]) "
/**
 */
public";

%csmethodmodifiers db_iodbc_open_int(TABDCA *dca, int mode, const char **sqllines) "
/**
 */
public";

%csmethodmodifiers db_mysql_open_int(TABDCA *dca, int mode, const char **sqllines) "
/**
 */
public";

%csmethodmodifiers db_iodbc_open(TABDCA *dca, int mode) "
/**
 */
public";

%csmethodmodifiers db_iodbc_read(TABDCA *dca, void *link) "
/**
 */
public";

%csmethodmodifiers db_iodbc_write(TABDCA *dca, void *link) "
/**
 */
public";

%csmethodmodifiers db_iodbc_close(TABDCA *dca, void *link) "
/**
 */
public";

%csmethodmodifiers db_mysql_open(TABDCA *dca, int mode) "
/**
 */
public";

%csmethodmodifiers db_mysql_read(TABDCA *dca, void *link) "
/**
 */
public";

%csmethodmodifiers db_mysql_write(TABDCA *dca, void *link) "
/**
 */
public";

%csmethodmodifiers db_mysql_close(TABDCA *dca, void *link) "
/**
 */
public";

%csmethodmodifiers most_feas(glp_tree *T) "
/**
 * ios_choose_node - select subproblem to continue the search .
 * <p>SYNOPSIS</p>
 * <p>#include \"glpios.h\" int ios_choose_node(glp_tree *T);</p>
 * <p>DESCRIPTION</p>
 * <p>The routine ios_choose_node selects a subproblem from the active list to continue the search. The choice depends on the backtracking technique option.</p>
 * <p>RETURNS</p>
 * <p>The routine ios_choose_node return the reference number of the subproblem selected. </p>
 */
public";

%csmethodmodifiers best_proj(glp_tree *T) "
/**
 */
public";

%csmethodmodifiers best_node(glp_tree *T) "
/**
 */
public";

%csmethodmodifiers ios_choose_node(glp_tree *T) "
/**
 */
public";

%csmethodmodifiers npp_implied_bounds(NPP *npp, NPPROW *p) "
/**
 * npp_implied_bounds - determine implied column bounds .
 * <p>SYNOPSIS</p>
 * <p>#include \"glpnpp.h\" void npp_implied_bounds(NPP *npp, NPPROW *p);</p>
 * <p>DESCRIPTION</p>
 * <p>The routine npp_implied_bounds inspects general row (constraint) p:</p>
 * <p>L[p] &lt;= sum a[p,j] x[j] &lt;= U[p], (1)</p>
 * <p>l[j] &lt;= x[j] &lt;= u[j], (2)</p>
 * <p>where L[p] &lt;= U[p] and l[j] &lt;= u[j] for all a[p,j] != 0, to compute implied bounds of columns (variables x[j]) in this row.</p>
 * <p>The routine stores implied column bounds l'[j] and u'[j] in column descriptors (NPPCOL); it does not change current column bounds l[j] and u[j]. (Implied column bounds can be then used to strengthen the current column bounds; see the routines npp_implied_lower and npp_implied_upper).</p>
 * <p>ALGORITHM</p>
 * <p>Current column bounds (2) define implied lower and upper bounds of row (1) as follows:</p>
 * <p>L'[p] = inf sum a[p,j] x[j] = j (3) = sum a[p,j] l[j] + sum a[p,j] u[j], j in Jp j in Jn</p>
 * <p>U'[p] = sup sum a[p,j] x[j] = (4) = sum a[p,j] u[j] + sum a[p,j] l[j], j in Jp j in Jn</p>
 * <p>Jp = {j: a[p,j] &gt; 0}, Jn = {j: a[p,j] &lt; 0}. (5)</p>
 * <p>(Note that bounds of all columns in row p are assumed to be correct, so L'[p] &lt;= U'[p].)</p>
 * <p>If L[p] &gt; L'[p] and/or U[p] &lt; U'[p], the lower and/or upper bound of row (1) can be active, in which case such row defines implied bounds of its variables.</p>
 * <p>Let x[k] be some variable having in row (1) coefficient a[p,k] != 0. Consider a case when row lower bound can be active (L[p] &gt; L'[p]):</p>
 * <p>sum a[p,j] x[j] &gt;= L[p] ==> j</p>
 * <p>sum a[p,j] x[j] + a[p,k] x[k] &gt;= L[p] ==> j!=k (6) a[p,k] x[k] &gt;= L[p] - sum a[p,j] x[j] ==> j!=k</p>
 * <p>a[p,k] x[k] &gt;= L[p,k],</p>
 * <p>where</p>
 * <p>L[p,k] = inf(L[p] - sum a[p,j] x[j]) = j!=k</p>
 * <p>= L[p] - sup sum a[p,j] x[j] = (7) j!=k</p>
 * <p>= L[p] - sum a[p,j] u[j] - sum a[p,j] l[j]. j in Jpk} j in Jnk}</p>
 * <p>Thus:</p>
 * <p>x[k] &gt;= l'[k] = L[p,k] / a[p,k], if a[p,k] &gt; 0, (8)</p>
 * <p>x[k] &lt;= u'[k] = L[p,k] / a[p,k], if a[p,k] &lt; 0. (9)</p>
 * <p>where l'[k] and u'[k] are implied lower and upper bounds of variable x[k], resp.</p>
 * <p>Now consider a similar case when row upper bound can be active (U[p] &lt; U'[p]):</p>
 * <p>sum a[p,j] x[j] &lt;= U[p] ==> j</p>
 * <p>sum a[p,j] x[j] + a[p,k] x[k] &lt;= U[p] ==> j!=k (10) a[p,k] x[k] &lt;= U[p] - sum a[p,j] x[j] ==> j!=k</p>
 * <p>a[p,k] x[k] &lt;= U[p,k],</p>
 * <p>where:</p>
 * <p>U[p,k] = sup(U[p] - sum a[p,j] x[j]) = j!=k</p>
 * <p>= U[p] - inf sum a[p,j] x[j] = (11) j!=k</p>
 * <p>= U[p] - sum a[p,j] l[j] - sum a[p,j] u[j]. j in Jpk} j in Jnk}</p>
 * <p>Thus:</p>
 * <p>x[k] &lt;= u'[k] = U[p,k] / a[p,k], if a[p,k] &gt; 0, (12)</p>
 * <p>x[k] &gt;= l'[k] = U[p,k] / a[p,k], if a[p,k] &lt; 0. (13)</p>
 * <p>Note that in formulae (8), (9), (12), and (13) coefficient a[p,k] must not be too small in magnitude relatively to other non-zero coefficients in row (1), i.e. the following condition must hold:</p>
 * <p>|a[p,k]| &gt;= eps * max(1, |a[p,j]|), (14) j</p>
 * <p>where eps is a relative tolerance for constraint coefficients. Otherwise the implied column bounds can be numerical inreliable. For example, using formula (8) for the following inequality constraint:</p>
 * <p>1e-12 x1 - x2 - x3 &gt;= 0,</p>
 * <p>where x1 &gt;= -1, x2, x3, &gt;= 0, may lead to numerically unreliable conclusion that x1 &gt;= 0.</p>
 * <p>Using formulae (8), (9), (12), and (13) to compute implied bounds for one variable requires |J| operations, where J = {j: a[p,j] != 0}, because this needs computing L[p,k] and U[p,k]. Thus, computing implied bounds for all variables in row (1) would require |J|^2 operations, that is not a good technique. However, the total number of operations can be reduced to |J| as follows.</p>
 * <p>Let a[p,k] &gt; 0. Then from (7) and (11) we have:</p>
 * <p>L[p,k] = L[p] - (U'[p] - a[p,k] u[k]) =    = L[p] - U'[p] + a[p,k] u[k],
</p>
 * <p>U[p,k] = U[p] - (L'[p] - a[p,k] l[k]) =    = U[p] - L'[p] + a[p,k] l[k],
</p>
 * <p>where L'[p] and U'[p] are implied row lower and upper bounds defined by formulae (3) and (4). Substituting these expressions into (8) and (12) gives:</p>
 * <p>l'[k] = L[p,k] / a[p,k] = u[k] + (L[p] - U'[p]) / a[p,k], (15)</p>
 * <p>u'[k] = U[p,k] / a[p,k] = l[k] + (U[p] - L'[p]) / a[p,k]. (16)</p>
 * <p>Similarly, if a[p,k] &lt; 0, according to (7) and (11) we have:</p>
 * <p>L[p,k] = L[p] - (U'[p] - a[p,k] l[k]) =    = L[p] - U'[p] + a[p,k] l[k],
</p>
 * <p>U[p,k] = U[p] - (L'[p] - a[p,k] u[k]) =    = U[p] - L'[p] + a[p,k] u[k],
</p>
 * <p>and substituting these expressions into (8) and (12) gives:</p>
 * <p>l'[k] = U[p,k] / a[p,k] = u[k] + (U[p] - L'[p]) / a[p,k], (17)</p>
 * <p>u'[k] = L[p,k] / a[p,k] = l[k] + (L[p] - U'[p]) / a[p,k]. (18)</p>
 * <p>Note that formulae (15)-(18) can be used only if L'[p] and U'[p] exist. However, if for some variable x[j] it happens that l[j] = -oo and/or u[j] = +oo, values of L'[p] (if a[p,j] &gt; 0) and/or U'[p] (if a[p,j] &lt; 0) are undefined. Consider, therefore, the most general situation, when some column bounds (2) may not exist.</p>
 * <p>Let:</p>
 * <p>J' = {j : (a[p,j] &gt; 0 and l[j] = -oo) or (19) (a[p,j] &lt; 0 and u[j] = +oo)}.</p>
 * <p>Then (assuming that row upper bound U[p] can be active) the following three cases are possible:</p>
 * <p>1) |J'| = 0. In this case L'[p] exists, thus, for all variables x[j] in row (1) we can use formulae (16) and (17);</p>
 * <p>2) J' = {k}. In this case L'[p] = -oo, however, U[p,k] (11) exists, so for variable x[k] we can use formulae (12) and (13). Note that for all other variables x[j] (j != k) l'[j] = -oo (if a[p,j] &lt; 0) or u'[j] = +oo (if a[p,j] &gt; 0);</p>
 * <p>3) |J'| &gt; 1. In this case for all variables x[j] in row [1] we have l'[j] = -oo (if a[p,j] &lt; 0) or u'[j] = +oo (if a[p,j] &gt; 0).</p>
 * <p>Similarly, let:</p>
 * <p>J'' = {j : (a[p,j] &gt; 0 and u[j] = +oo) or (20) (a[p,j] &lt; 0 and l[j] = -oo)}.</p>
 * <p>Then (assuming that row lower bound L[p] can be active) the following three cases are possible:</p>
 * <p>1) |J''| = 0. In this case U'[p] exists, thus, for all variables x[j] in row (1) we can use formulae (15) and (18);</p>
 * <p>2) J'' = {k}. In this case U'[p] = +oo, however, L[p,k] (7) exists, so for variable x[k] we can use formulae (8) and (9). Note that for all other variables x[j] (j != k) l'[j] = -oo (if a[p,j] &gt; 0) or u'[j] = +oo (if a[p,j] &lt; 0);</p>
 * <p>3) |J''| &gt; 1. In this case for all variables x[j] in row (1) we have l'[j] = -oo (if a[p,j] &gt; 0) or u'[j] = +oo (if a[p,j] &lt; 0). </p>
 */
public";

%csmethodmodifiers npp_empty_row(NPP *npp, NPPROW *p) "
/**
 * npp_empty_row - process empty row .
 * <p>SYNOPSIS</p>
 * <p>#include \"glpnpp.h\" int npp_empty_row(NPP *npp, NPPROW *p);</p>
 * <p>DESCRIPTION</p>
 * <p>The routine npp_empty_row processes row p, which is empty, i.e. coefficients at all columns in this row are zero:</p>
 * <p>L[p] &lt;= sum 0 x[j] &lt;= U[p], (1)</p>
 * <p>where L[p] &lt;= U[p].</p>
 * <p>RETURNS</p>
 * <p>0 - success;</p>
 * <p>1 - problem has no primal feasible solution.</p>
 * <p>PROBLEM TRANSFORMATION</p>
 * <p>If the following conditions hold:</p>
 * <p>L[p] &lt;= +eps, U[p] &gt;= -eps, (2)</p>
 * <p>where eps is an absolute tolerance for row value, the row p is redundant. In this case it can be replaced by equivalent redundant row, which is free (unbounded), and then removed from the problem. Otherwise, the row p is infeasible and, thus, the problem has no primal feasible solution.</p>
 * <p>RECOVERING BASIC SOLUTION</p>
 * <p>See the routine npp_free_row.</p>
 * <p>RECOVERING INTERIOR-POINT SOLUTION</p>
 * <p>See the routine npp_free_row.</p>
 * <p>RECOVERING MIP SOLUTION</p>
 * <p>None needed. </p>
 */
public";

%csmethodmodifiers rcv_empty_col(NPP *npp, void *info) "
/**
 */
public";

%csmethodmodifiers npp_empty_col(NPP *npp, NPPCOL *q) "
/**
 */
public";

%csmethodmodifiers npp_implied_value(NPP *npp, NPPCOL *q, double s) "
/**
 * npp_implied_value - process implied column value .
 * <p>SYNOPSIS</p>
 * <p>#include \"glpnpp.h\" int npp_implied_value(NPP *npp, NPPCOL *q, double s);</p>
 * <p>DESCRIPTION</p>
 * <p>For column q:</p>
 * <p>l[q] &lt;= x[q] &lt;= u[q], (1)</p>
 * <p>where l[q] &lt; u[q], the routine npp_implied_value processes its implied value s[q]. If this implied value satisfies to the current column bounds and integrality condition, the routine fixes column q at the given point. Note that the column is kept in the problem in any case.</p>
 * <p>RETURNS</p>
 * <p>0 - column has been fixed;</p>
 * <p>1 - implied value violates to current column bounds;</p>
 * <p>2 - implied value violates integrality condition.</p>
 * <p>ALGORITHM</p>
 * <p>Implied column value s[q] satisfies to the current column bounds if the following condition holds:</p>
 * <p>l[q] - eps &lt;= s[q] &lt;= u[q] + eps, (2)</p>
 * <p>where eps is an absolute tolerance for column value. If the column is integral, the following condition also must hold:</p>
 * <p>|s[q] - floor(s[q]+0.5)| &lt;= eps, (3)</p>
 * <p>where floor(s[q]+0.5) is the nearest integer to s[q].</p>
 * <p>If both condition (2) and (3) are satisfied, the column can be fixed at the value s[q], or, if it is integral, at floor(s[q]+0.5). Otherwise, if s[q] violates (2) or (3), the problem has no feasible solution.</p>
 * <p>Note: If s[q] is close to l[q] or u[q], it seems to be reasonable to fix the column at its lower or upper bound, resp. rather than at the implied value. </p>
 */
public";

%csmethodmodifiers rcv_eq_singlet(NPP *npp, void *info) "
/**
 */
public";

%csmethodmodifiers npp_eq_singlet(NPP *npp, NPPROW *p) "
/**
 */
public";

%csmethodmodifiers npp_implied_lower(NPP *npp, NPPCOL *q, double l) "
/**
 * npp_implied_lower - process implied column lower bound .
 * <p>SYNOPSIS</p>
 * <p>#include \"glpnpp.h\" int npp_implied_lower(NPP *npp, NPPCOL *q, double l);</p>
 * <p>DESCRIPTION</p>
 * <p>For column q:</p>
 * <p>l[q] &lt;= x[q] &lt;= u[q], (1)</p>
 * <p>where l[q] &lt; u[q], the routine npp_implied_lower processes its implied lower bound l'[q]. As the result the current column lower bound may increase. Note that the column is kept in the problem in any case.</p>
 * <p>RETURNS</p>
 * <p>0 - current column lower bound has not changed;</p>
 * <p>1 - current column lower bound has changed, but not significantly;</p>
 * <p>2 - current column lower bound has significantly changed;</p>
 * <p>3 - column has been fixed on its upper bound;</p>
 * <p>4 - implied lower bound violates current column upper bound.</p>
 * <p>ALGORITHM</p>
 * <p>If column q is integral, before processing its implied lower bound should be rounded up:         ( floor(l'[q]+0.5), if |l'[q] - floor(l'[q]+0.5)| &lt;= eps
 l'[q] := &lt; (2) ( ceil(l'[q]), otherwise</p>
 * <p>where floor(l'[q]+0.5) is the nearest integer to l'[q], ceil(l'[q]) is smallest integer not less than l'[q], and eps is an absolute tolerance for column value.</p>
 * <p>Processing implied column lower bound l'[q] includes the following cases:</p>
 * <p>1) if l'[q] &lt; l[q] + eps, implied lower bound is redundant;</p>
 * <p>2) if l[q] + eps &lt;= l[q] &lt;= u[q] + eps, current column lower bound l[q] can be strengthened by replacing it with l'[q]. If in this case new column lower bound becomes close to current column upper bound u[q], the column can be fixed on its upper bound;</p>
 * <p>3) if l'[q] &gt; u[q] + eps, implied lower bound violates current column upper bound u[q], in which case the problem has no primal feasible solution. </p>
 */
public";

%csmethodmodifiers npp_implied_upper(NPP *npp, NPPCOL *q, double u) "
/**
 * npp_implied_upper - process implied column upper bound .
 * <p>SYNOPSIS</p>
 * <p>#include \"glpnpp.h\" int npp_implied_upper(NPP *npp, NPPCOL *q, double u);</p>
 * <p>DESCRIPTION</p>
 * <p>For column q:</p>
 * <p>l[q] &lt;= x[q] &lt;= u[q], (1)</p>
 * <p>where l[q] &lt; u[q], the routine npp_implied_upper processes its implied upper bound u'[q]. As the result the current column upper bound may decrease. Note that the column is kept in the problem in any case.</p>
 * <p>RETURNS</p>
 * <p>0 - current column upper bound has not changed;</p>
 * <p>1 - current column upper bound has changed, but not significantly;</p>
 * <p>2 - current column upper bound has significantly changed;</p>
 * <p>3 - column has been fixed on its lower bound;</p>
 * <p>4 - implied upper bound violates current column lower bound.</p>
 * <p>ALGORITHM</p>
 * <p>If column q is integral, before processing its implied upper bound should be rounded down:         ( floor(u'[q]+0.5), if |u'[q] - floor(l'[q]+0.5)| &lt;= eps
 u'[q] := &lt; (2) ( floor(l'[q]), otherwise</p>
 * <p>where floor(u'[q]+0.5) is the nearest integer to u'[q], floor(u'[q]) is largest integer not greater than u'[q], and eps is an absolute tolerance for column value.</p>
 * <p>Processing implied column upper bound u'[q] includes the following cases:</p>
 * <p>1) if u'[q] &gt; u[q] - eps, implied upper bound is redundant;</p>
 * <p>2) if l[q] - eps &lt;= u[q] &lt;= u[q] - eps, current column upper bound u[q] can be strengthened by replacing it with u'[q]. If in this case new column upper bound becomes close to current column lower bound, the column can be fixed on its lower bound;</p>
 * <p>3) if u'[q] &lt; l[q] - eps, implied upper bound violates current column lower bound l[q], in which case the problem has no primal feasible solution. </p>
 */
public";

%csmethodmodifiers rcv_ineq_singlet(NPP *npp, void *info) "
/**
 */
public";

%csmethodmodifiers npp_ineq_singlet(NPP *npp, NPPROW *p) "
/**
 */
public";

%csmethodmodifiers rcv_implied_slack(NPP *npp, void *info) "
/**
 */
public";

%csmethodmodifiers npp_implied_slack(NPP *npp, NPPCOL *q) "
/**
 */
public";

%csmethodmodifiers rcv_implied_free(NPP *npp, void *info) "
/**
 */
public";

%csmethodmodifiers npp_implied_free(NPP *npp, NPPCOL *q) "
/**
 */
public";

%csmethodmodifiers rcv_eq_doublet(NPP *npp, void *info) "
/**
 */
public";

%csmethodmodifiers npp_eq_doublet(NPP *npp, NPPROW *p) "
/**
 */
public";

%csmethodmodifiers rcv_forcing_row(NPP *npp, void *info) "
/**
 */
public";

%csmethodmodifiers npp_forcing_row(NPP *npp, NPPROW *p, int at) "
/**
 */
public";

%csmethodmodifiers npp_analyze_row(NPP *npp, NPPROW *p) "
/**
 * npp_analyze_row - perform general row analysis .
 * <p>SYNOPSIS</p>
 * <p>#include \"glpnpp.h\" int npp_analyze_row(NPP *npp, NPPROW *p);</p>
 * <p>DESCRIPTION</p>
 * <p>The routine npp_analyze_row performs analysis of row p of general format:</p>
 * <p>L[p] &lt;= sum a[p,j] x[j] &lt;= U[p], (1) j</p>
 * <p>l[j] &lt;= x[j] &lt;= u[j], (2)</p>
 * <p>where L[p] &lt;= U[p] and l[j] &lt;= u[j] for all a[p,j] != 0.</p>
 * <p>RETURNS</p>
 * <p>0x?0 - row lower bound does not exist or is redundant;</p>
 * <p>0x?1 - row lower bound can be active;</p>
 * <p>0x?2 - row lower bound is a forcing bound;</p>
 * <p>0x0? - row upper bound does not exist or is redundant;</p>
 * <p>0x1? - row upper bound can be active;</p>
 * <p>0x2? - row upper bound is a forcing bound;</p>
 * <p>0x33 - row bounds are inconsistent with column bounds.</p>
 * <p>ALGORITHM</p>
 * <p>Analysis of row (1) is based on analysis of its implied lower and upper bounds, which are determined by bounds of corresponding columns (variables) as follows:</p>
 * <p>L'[p] = inf sum a[p,j] x[j] = j (3) = sum a[p,j] l[j] + sum a[p,j] u[j], j in Jp j in Jn</p>
 * <p>U'[p] = sup sum a[p,j] x[j] = (4) = sum a[p,j] u[j] + sum a[p,j] l[j], j in Jp j in Jn</p>
 * <p>Jp = {j: a[p,j] &gt; 0}, Jn = {j: a[p,j] &lt; 0}. (5)</p>
 * <p>(Note that bounds of all columns in row p are assumed to be correct, so L'[p] &lt;= U'[p].)</p>
 * <p>Analysis of row lower bound L[p] includes the following cases:</p>
 * <p>1) if L[p] &gt; U'[p] + eps, where eps is an absolute tolerance for row value, row lower bound L[p] and implied row upper bound U'[p] are inconsistent, ergo, the problem has no primal feasible solution;</p>
 * <p>2) if U'[p] - eps &lt;= L[p] &lt;= U'[p] + eps, i.e. if L[p] =~ U'[p], the row is a forcing row on its lower bound (see description of the routine npp_forcing_row);</p>
 * <p>3) if L[p] &gt; L'[p] + eps, row lower bound L[p] can be active (this conclusion does not account other rows in the problem);</p>
 * <p>4) if L[p] &lt;= L'[p] + eps, row lower bound L[p] cannot be active, so it is redundant and can be removed (replaced by -oo).</p>
 * <p>Analysis of row upper bound U[p] is performed in a similar way and includes the following cases:</p>
 * <p>1) if U[p] &lt; L'[p] - eps, row upper bound U[p] and implied row lower bound L'[p] are inconsistent, ergo the problem has no primal feasible solution;</p>
 * <p>2) if L'[p] - eps &lt;= U[p] &lt;= L'[p] + eps, i.e. if U[p] =~ L'[p], the row is a forcing row on its upper bound (see description of the routine npp_forcing_row);</p>
 * <p>3) if U[p] &lt; U'[p] - eps, row upper bound U[p] can be active (this conclusion does not account other rows in the problem);</p>
 * <p>4) if U[p] &gt;= U'[p] - eps, row upper bound U[p] cannot be active, so it is redundant and can be removed (replaced by +oo). </p>
 */
public";

%csmethodmodifiers rcv_inactive_bound(NPP *npp, void *info) "
/**
 */
public";

%csmethodmodifiers npp_inactive_bound(NPP *npp, NPPROW *p, int which) "
/**
 */
public";
%csmethodmodifiers initialize(void) "
/**
 */
public";

%csmethodmodifiers open(const char *path, int oflag,...) "
/**
 */
public";

%csmethodmodifiers read(int fd, void *buf, unsigned long nbyte) "
/**
 */
public";

%csmethodmodifiers write(int fd, const void *buf, unsigned long nbyte) "
/**
 */
public";

%csmethodmodifiers lseek(int fd, long offset, int whence) "
/**
 */
public";

%csmethodmodifiers close(int fd) "
/**
 */
public";

%csmethodmodifiers main(int argc, char **argv) "
/**
 */
public";

%csmethodmodifiers spx_alloc_at(SPXLP *lp, SPXAT *at) "
/**
 */
public";

%csmethodmodifiers spx_build_at(SPXLP *lp, SPXAT *at) "
/**
 */
public";

%csmethodmodifiers spx_at_prod(SPXLP *lp, SPXAT *at, double y[], double s, const double x[]) "
/**
 */
public";

%csmethodmodifiers spx_nt_prod1(SPXLP *lp, SPXAT *at, double y[], int ign, double s, const double x[]) "
/**
 */
public";

%csmethodmodifiers spx_eval_trow1(SPXLP *lp, SPXAT *at, const double rho[], double trow[]) "
/**
 */
public";

%csmethodmodifiers spx_free_at(SPXLP *lp, SPXAT *at) "
/**
 */
public";

%csmethodmodifiers prepare_row_info(int n, const double a[], const double l[], const double u[], struct f_info *f) "
/**
 */
public";

%csmethodmodifiers row_implied_bounds(const struct f_info *f, double *LL, double *UU) "
/**
 */
public";

%csmethodmodifiers col_implied_bounds(const struct f_info *f, int n, const double a[], double L, double U, const double l[], const double u[], int k, double *ll, double *uu) "
/**
 */
public";

%csmethodmodifiers check_row_bounds(const struct f_info *f, double *L_, double *U_) "
/**
 */
public";

%csmethodmodifiers check_col_bounds(const struct f_info *f, int n, const double a[], double L, double U, const double l[], const double u[], int flag, int j, double *_lj, double *_uj) "
/**
 */
public";

%csmethodmodifiers check_efficiency(int flag, double l, double u, double ll, double uu) "
/**
 */
public";

%csmethodmodifiers basic_preprocessing(glp_prob *mip, double L[], double U[], double l[], double u[], int nrs, const int num[], int max_pass) "
/**
 */
public";

%csmethodmodifiers ios_preprocess_node(glp_tree *tree, int max_pass) "
/**
 * ios_preprocess_node - preprocess current subproblem .
 * <p>SYNOPSIS</p>
 * <p>#include \"glpios.h\" int ios_preprocess_node(glp_tree *tree, int max_pass);</p>
 * <p>DESCRIPTION</p>
 * <p>The routine ios_preprocess_node performs basic preprocessing of the current subproblem.</p>
 * <p>RETURNS</p>
 * <p>If no primal infeasibility is detected, the routine returns zero, otherwise non-zero. </p>
 */
public";

%csmethodmodifiers lpx_eval_tab_row(glp_prob *lp, int k, int ind[], double val[]) "
/**
 */
public";

%csmethodmodifiers lpx_dual_ratio_test(glp_prob *lp, int len, const int ind[], const double val[], int how, double tol) "
/**
 */
public";

%csmethodmodifiers new_node(glp_tree *tree, IOSNPD *parent) "
/**
 * ios_create_tree - create branch-and-bound tree .
 * <p>SYNOPSIS</p>
 * <p>#include \"glpios.h\" glp_tree *ios_create_tree(glp_prob *mip, const glp_iocp *parm);</p>
 * <p>DESCRIPTION</p>
 * <p>The routine ios_create_tree creates the branch-and-bound tree.</p>
 * <p>Being created the tree consists of the only root subproblem whose reference number is 1. Note that initially the root subproblem is in frozen state and therefore needs to be revived.</p>
 * <p>RETURNS</p>
 * <p>The routine returns a pointer to the tree created. </p>
 */
public";

%csmethodmodifiers ios_create_tree(glp_prob *mip, const glp_iocp *parm) "
/**
 */
public";

%csmethodmodifiers ios_revive_node(glp_tree *tree, int p) "
/**
 * ios_revive_node - revive specified subproblem .
 * <p>SYNOPSIS</p>
 * <p>#include \"glpios.h\" void ios_revive_node(glp_tree *tree, int p);</p>
 * <p>DESCRIPTION</p>
 * <p>The routine ios_revive_node revives the specified subproblem, whose reference number is p, and thereby makes it the current subproblem. Note that the specified subproblem must be active. Besides, if the current subproblem already exists, it must be frozen before reviving another subproblem. </p>
 */
public";

%csmethodmodifiers ios_freeze_node(glp_tree *tree) "
/**
 * ios_freeze_node - freeze current subproblem .
 * <p>SYNOPSIS</p>
 * <p>#include \"glpios.h\" void ios_freeze_node(glp_tree *tree);</p>
 * <p>DESCRIPTION</p>
 * <p>The routine ios_freeze_node freezes the current subproblem. </p>
 */
public";

%csmethodmodifiers get_slot(glp_tree *tree) "
/**
 * ios_clone_node - clone specified subproblem .
 * <p>SYNOPSIS</p>
 * <p>#include \"glpios.h\" void ios_clone_node(glp_tree *tree, int p, int nnn, int ref[]);</p>
 * <p>DESCRIPTION</p>
 * <p>The routine ios_clone_node clones the specified subproblem, whose reference number is p, creating its nnn exact copies. Note that the specified subproblem must be active and must be in the frozen state (i.e. it must not be the current subproblem).</p>
 * <p>Each clone, an exact copy of the specified subproblem, becomes a new active subproblem added to the end of the active list. After cloning the specified subproblem becomes inactive.</p>
 * <p>The reference numbers of clone subproblems are stored to locations ref[1], ..., ref[nnn]. </p>
 */
public";

%csmethodmodifiers ios_clone_node(glp_tree *tree, int p, int nnn, int ref[]) "
/**
 */
public";

%csmethodmodifiers ios_delete_node(glp_tree *tree, int p) "
/**
 * ios_delete_node - delete specified subproblem .
 * <p>SYNOPSIS</p>
 * <p>#include \"glpios.h\" void ios_delete_node(glp_tree *tree, int p);</p>
 * <p>DESCRIPTION</p>
 * <p>The routine ios_delete_node deletes the specified subproblem, whose reference number is p. The subproblem must be active and must be in the frozen state (i.e. it must not be the current subproblem).</p>
 * <p>Note that deletion is performed recursively, i.e. if a subproblem to be deleted is the only child of its parent, the parent subproblem is also deleted, etc. </p>
 */
public";

%csmethodmodifiers ios_delete_tree(glp_tree *tree) "
/**
 * ios_delete_tree - delete branch-and-bound tree .
 * <p>SYNOPSIS</p>
 * <p>#include \"glpios.h\" void ios_delete_tree(glp_tree *tree);</p>
 * <p>DESCRIPTION</p>
 * <p>The routine ios_delete_tree deletes the branch-and-bound tree, which the parameter tree points to, and frees all the memory allocated to this program object.</p>
 * <p>On exit components of the problem object are restored to correspond to the original MIP passed to the routine ios_create_tree. </p>
 */
public";

%csmethodmodifiers ios_eval_degrad(glp_tree *tree, int j, double *dn, double *up) "
/**
 * ios_eval_degrad - estimate obj. .
 * <p>degrad. for down- and up-branches</p>
 * <p>SYNOPSIS</p>
 * <p>#include \"glpios.h\" void ios_eval_degrad(glp_tree *tree, int j, double *dn, double *up);</p>
 * <p>DESCRIPTION</p>
 * <p>Given optimal basis to LP relaxation of the current subproblem the routine ios_eval_degrad performs the dual ratio test to compute the objective values in the adjacent basis for down- and up-branches, which are stored in locations *dn and *up, assuming that x[j] is a variable chosen to branch upon. </p>
 */
public";

%csmethodmodifiers ios_round_bound(glp_tree *tree, double bound) "
/**
 * ios_round_bound - improve local bound by rounding .
 * <p>SYNOPSIS</p>
 * <p>#include \"glpios.h\" double ios_round_bound(glp_tree *tree, double bound);</p>
 * <p>RETURNS</p>
 * <p>For the given local bound for any integer feasible solution to the current subproblem the routine ios_round_bound returns an improved local bound for the same integer feasible solution.</p>
 * <p>BACKGROUND</p>
 * <p>Let the current subproblem has the following objective function:</p>
 * <p>z = sum c[j] * x[j] + s &gt;= b, (1) j in J</p>
 * <p>where J = {j: c[j] is non-zero and integer, x[j] is integer}, s is the sum of terms corresponding to fixed variables, b is an initial local bound (minimization).</p>
 * <p>From (1) it follows that:</p>
 * <p>d * sum (c[j] / d) * x[j] + s &gt;= b, (2) j in J</p>
 * <p>or, equivalently,</p>
 * <p>sum (c[j] / d) * x[j] &gt;= (b - s) / d = h, (3) j in J</p>
 * <p>where d = gcd(c[j]). Since the left-hand side of (3) is integer, h = (b - s) / d can be rounded up to the nearest integer:</p>
 * <p>h' = ceil(h) = (b' - s) / d, (4)</p>
 * <p>that gives an rounded, improved local bound:</p>
 * <p>b' = d * h' + s. (5)</p>
 * <p>In case of maximization '>=' in (1) should be replaced by '&lt;=' that leads to the following formula:</p>
 * <p>h' = floor(h) = (b' - s) / d, (6)</p>
 * <p>which should used in the same way as (4).</p>
 * <p>NOTE: If b is a valid local bound for a child of the current subproblem, b' is also valid for that child subproblem. </p>
 */
public";

%csmethodmodifiers ios_is_hopeful(glp_tree *tree, double bound) "
/**
 * ios_is_hopeful - check if subproblem is hopeful .
 * <p>SYNOPSIS</p>
 * <p>#include \"glpios.h\" int ios_is_hopeful(glp_tree *tree, double bound);</p>
 * <p>DESCRIPTION</p>
 * <p>Given the local bound of a subproblem the routine ios_is_hopeful checks if the subproblem can have an integer optimal solution which is better than the best one currently known.</p>
 * <p>RETURNS</p>
 * <p>If the subproblem can have a better integer optimal solution, the routine returns non-zero; otherwise, if the corresponding branch can be pruned, the routine returns zero. </p>
 */
public";

%csmethodmodifiers ios_best_node(glp_tree *tree) "
/**
 * ios_best_node - find active node with best local bound .
 * <p>SYNOPSIS</p>
 * <p>#include \"glpios.h\" int ios_best_node(glp_tree *tree);</p>
 * <p>DESCRIPTION</p>
 * <p>The routine ios_best_node finds an active node whose local bound is best among other active nodes.</p>
 * <p>It is understood that the integer optimal solution of the original mip problem cannot be better than the best bound, so the best bound is an lower (minimization) or upper (maximization) global bound for the original problem.</p>
 * <p>RETURNS</p>
 * <p>The routine ios_best_node returns the subproblem reference number for the best node. However, if the tree is empty, it returns zero. </p>
 */
public";

%csmethodmodifiers ios_relative_gap(glp_tree *tree) "
/**
 * ios_relative_gap - compute relative mip gap .
 * <p>SYNOPSIS</p>
 * <p>#include \"glpios.h\" double ios_relative_gap(glp_tree *tree);</p>
 * <p>DESCRIPTION</p>
 * <p>The routine ios_relative_gap computes the relative mip gap using the formula:</p>
 * <p>gap = |best_mip - best_bnd| / (|best_mip| + DBL_EPSILON),</p>
 * <p>where best_mip is the best integer feasible solution found so far, best_bnd is the best (global) bound. If no integer feasible solution has been found yet, rel_gap is set to DBL_MAX.</p>
 * <p>RETURNS</p>
 * <p>The routine ios_relative_gap returns the relative mip gap. </p>
 */
public";

%csmethodmodifiers ios_solve_node(glp_tree *tree) "
/**
 * ios_solve_node - solve LP relaxation of current subproblem .
 * <p>SYNOPSIS</p>
 * <p>#include \"glpios.h\" int ios_solve_node(glp_tree *tree);</p>
 * <p>DESCRIPTION</p>
 * <p>The routine ios_solve_node re-optimizes LP relaxation of the current subproblem using the dual simplex method.</p>
 * <p>RETURNS</p>
 * <p>The routine returns the code which is reported by glp_simplex. </p>
 */
public";

%csmethodmodifiers ios_create_pool(glp_tree *tree) "
/**
 */
public";

%csmethodmodifiers ios_add_row(glp_tree *tree, IOSPOOL *pool, const char *name, int klass, int flags, int len, const int ind[], const double val[], int type, double rhs) "
/**
 */
public";

%csmethodmodifiers ios_find_row(IOSPOOL *pool, int i) "
/**
 */
public";

%csmethodmodifiers ios_del_row(glp_tree *tree, IOSPOOL *pool, int i) "
/**
 */
public";

%csmethodmodifiers ios_clear_pool(glp_tree *tree, IOSPOOL *pool) "
/**
 */
public";

%csmethodmodifiers ios_delete_pool(glp_tree *tree, IOSPOOL *pool) "
/**
 */
public";

%csmethodmodifiers ios_process_sol(glp_tree *T) "
/**
 */
public";

%csmethodmodifiers spx_chuzr_std(SPXLP *lp, int phase, const double beta[], int q, double s, const double tcol[], int *p_flag, double tol_piv, double tol, double tol1) "
/**
 */
public";

%csmethodmodifiers spx_chuzr_harris(SPXLP *lp, int phase, const double beta[], int q, double s, const double tcol[], int *p_flag, double tol_piv, double tol, double tol1) "
/**
 */
public";

%csmethodmodifiers read_char(struct csv *csv) "
/**
 */
public";

%csmethodmodifiers read_field(struct csv *csv) "
/**
 */
public";

%csmethodmodifiers csv_open_file(TABDCA *dca, int mode) "
/**
 */
public";

%csmethodmodifiers csv_read_record(TABDCA *dca, struct csv *csv) "
/**
 */
public";

%csmethodmodifiers csv_write_record(TABDCA *dca, struct csv *csv) "
/**
 */
public";

%csmethodmodifiers csv_close_file(TABDCA *dca, struct csv *csv) "
/**
 */
public";

%csmethodmodifiers read_byte(struct dbf *dbf) "
/**
 */
public";

%csmethodmodifiers read_header(TABDCA *dca, struct dbf *dbf) "
/**
 */
public";

%csmethodmodifiers parse_third_arg(TABDCA *dca, struct dbf *dbf) "
/**
 */
public";

%csmethodmodifiers write_byte(struct dbf *dbf, int b) "
/**
 */
public";

%csmethodmodifiers write_header(TABDCA *dca, struct dbf *dbf) "
/**
 */
public";

%csmethodmodifiers dbf_open_file(TABDCA *dca, int mode) "
/**
 */
public";

%csmethodmodifiers dbf_read_record(TABDCA *dca, struct dbf *dbf) "
/**
 */
public";

%csmethodmodifiers dbf_write_record(TABDCA *dca, struct dbf *dbf) "
/**
 */
public";

%csmethodmodifiers dbf_close_file(TABDCA *dca, struct dbf *dbf) "
/**
 */
public";

%csmethodmodifiers mpl_tab_drv_open(MPL *mpl, int mode) "
/**
 */
public";

%csmethodmodifiers mpl_tab_drv_read(MPL *mpl) "
/**
 */
public";

%csmethodmodifiers mpl_tab_drv_write(MPL *mpl) "
/**
 */
public";

%csmethodmodifiers mpl_tab_drv_close(MPL *mpl) "
/**
 */
public";
%csmethodmodifiers gmp_get_atom(int size) "
/**
 */
public";

%csmethodmodifiers gmp_free_atom(void *ptr, int size) "
/**
 */
public";

%csmethodmodifiers gmp_pool_count(void) "
/**
 */
public";

%csmethodmodifiers gmp_get_work(int size) "
/**
 */
public";

%csmethodmodifiers gmp_free_mem(void) "
/**
 */
public";

%csmethodmodifiers _mpz_init(void) "
/**
 */
public";

%csmethodmodifiers mpz_clear(mpz_t x) "
/**
 */
public";

%csmethodmodifiers mpz_set(mpz_t z, mpz_t x) "
/**
 */
public";

%csmethodmodifiers mpz_set_si(mpz_t x, int val) "
/**
 */
public";

%csmethodmodifiers mpz_get_d(mpz_t x) "
/**
 */
public";

%csmethodmodifiers mpz_get_d_2exp(int *exp, mpz_t x) "
/**
 */
public";

%csmethodmodifiers mpz_swap(mpz_t x, mpz_t y) "
/**
 */
public";

%csmethodmodifiers normalize(mpz_t x) "
/**
 */
public";

%csmethodmodifiers mpz_add(mpz_t z, mpz_t x, mpz_t y) "
/**
 */
public";

%csmethodmodifiers mpz_sub(mpz_t z, mpz_t x, mpz_t y) "
/**
 */
public";

%csmethodmodifiers mpz_mul(mpz_t z, mpz_t x, mpz_t y) "
/**
 */
public";

%csmethodmodifiers mpz_neg(mpz_t z, mpz_t x) "
/**
 */
public";

%csmethodmodifiers mpz_abs(mpz_t z, mpz_t x) "
/**
 */
public";

%csmethodmodifiers mpz_div(mpz_t q, mpz_t r, mpz_t x, mpz_t y) "
/**
 */
public";

%csmethodmodifiers mpz_gcd(mpz_t z, mpz_t x, mpz_t y) "
/**
 */
public";

%csmethodmodifiers mpz_cmp(mpz_t x, mpz_t y) "
/**
 */
public";

%csmethodmodifiers mpz_sgn(mpz_t x) "
/**
 */
public";

%csmethodmodifiers mpz_out_str(void *_fp, int base, mpz_t x) "
/**
 */
public";

%csmethodmodifiers _mpq_init(void) "
/**
 */
public";

%csmethodmodifiers mpq_clear(mpq_t x) "
/**
 */
public";

%csmethodmodifiers mpq_canonicalize(mpq_t x) "
/**
 */
public";

%csmethodmodifiers mpq_set(mpq_t z, mpq_t x) "
/**
 */
public";

%csmethodmodifiers mpq_set_si(mpq_t x, int p, unsigned int q) "
/**
 */
public";

%csmethodmodifiers mpq_get_d(mpq_t x) "
/**
 */
public";

%csmethodmodifiers mpq_set_d(mpq_t x, double val) "
/**
 */
public";

%csmethodmodifiers mpq_add(mpq_t z, mpq_t x, mpq_t y) "
/**
 */
public";

%csmethodmodifiers mpq_sub(mpq_t z, mpq_t x, mpq_t y) "
/**
 */
public";

%csmethodmodifiers mpq_mul(mpq_t z, mpq_t x, mpq_t y) "
/**
 */
public";

%csmethodmodifiers mpq_div(mpq_t z, mpq_t x, mpq_t y) "
/**
 */
public";

%csmethodmodifiers mpq_neg(mpq_t z, mpq_t x) "
/**
 */
public";

%csmethodmodifiers mpq_abs(mpq_t z, mpq_t x) "
/**
 */
public";

%csmethodmodifiers mpq_cmp(mpq_t x, mpq_t y) "
/**
 */
public";

%csmethodmodifiers mpq_sgn(mpq_t x) "
/**
 */
public";

%csmethodmodifiers mpq_out_str(void *_fp, int base, mpq_t x) "
/**
 */
public";

%csmethodmodifiers trivial_lp(glp_prob *P, const glp_smcp *parm) "
/**
 * glp_simplex - solve LP problem with the simplex method .
 * <p>SYNOPSIS</p>
 * <p>int glp_simplex(glp_prob *P, const glp_smcp *parm);</p>
 * <p>DESCRIPTION</p>
 * <p>The routine glp_simplex is a driver to the LP solver based on the simplex method. This routine retrieves problem data from the specified problem object, calls the solver to solve the problem instance, and stores results of computations back into the problem object.</p>
 * <p>The simplex solver has a set of control parameters. Values of the control parameters can be passed in a structure glp_smcp, which the parameter parm points to.</p>
 * <p>The parameter parm can be specified as NULL, in which case the LP solver uses default settings.</p>
 * <p>RETURNS</p>
 * <p>0 The LP problem instance has been successfully solved. This code does not necessarily mean that the solver has found optimal solution. It only means that the solution process was successful.</p>
 * <p>GLP_EBADB Unable to start the search, because the initial basis specified in the problem object is invalidthe number of basic (auxiliary and structural) variables is not the same as the number of rows in the problem object.</p>
 * <p>GLP_ESING Unable to start the search, because the basis matrix correspodning to the initial basis is singular within the working precision.</p>
 * <p>GLP_ECOND Unable to start the search, because the basis matrix correspodning to the initial basis is ill-conditioned, i.e. its condition number is too large.</p>
 * <p>GLP_EBOUND Unable to start the search, because some double-bounded variables have incorrect bounds.</p>
 * <p>GLP_EFAIL The search was prematurely terminated due to the solver failure.</p>
 * <p>GLP_EOBJLL The search was prematurely terminated, because the objective function being maximized has reached its lower limit and continues decreasing (dual simplex only).</p>
 * <p>GLP_EOBJUL The search was prematurely terminated, because the objective function being minimized has reached its upper limit and continues increasing (dual simplex only).</p>
 * <p>GLP_EITLIM The search was prematurely terminated, because the simplex iteration limit has been exceeded.</p>
 * <p>GLP_ETMLIM The search was prematurely terminated, because the time limit has been exceeded.</p>
 * <p>GLP_ENOPFS The LP problem instance has no primal feasible solution (only if the LP presolver is used).</p>
 * <p>GLP_ENODFS The LP problem instance has no dual feasible solution (only if the LP presolver is used). </p>
 */
public";

%csmethodmodifiers solve_lp(glp_prob *P, const glp_smcp *parm) "
/**
 */
public";

%csmethodmodifiers preprocess_and_solve_lp(glp_prob *P, const glp_smcp *parm) "
/**
 */
public";

%csmethodmodifiers glp_simplex(glp_prob *P, const glp_smcp *parm) "
/**
 */
public";

%csmethodmodifiers glp_init_smcp(glp_smcp *parm) "
/**
 * glp_init_smcp - initialize simplex method control parameters .
 * <p>SYNOPSIS</p>
 * <p>void glp_init_smcp(glp_smcp *parm);</p>
 * <p>DESCRIPTION</p>
 * <p>The routine glp_init_smcp initializes control parameters, which are used by the simplex solver, with default values.</p>
 * <p>Default values of the control parameters are stored in a glp_smcp structure, which the parameter parm points to. </p>
 */
public";

%csmethodmodifiers glp_get_status(glp_prob *lp) "
/**
 * glp_get_status - retrieve generic status of basic solution .
 * <p>SYNOPSIS</p>
 * <p>int glp_get_status(glp_prob *lp);</p>
 * <p>RETURNS</p>
 * <p>The routine glp_get_status reports the generic status of the basic solution for the specified problem object as follows:</p>
 * <p>GLP_OPT - solution is optimal; GLP_FEAS - solution is feasible; GLP_INFEAS - solution is infeasible; GLP_NOFEAS - problem has no feasible solution; GLP_UNBND - problem has unbounded solution; GLP_UNDEF - solution is undefined. </p>
 */
public";

%csmethodmodifiers glp_get_prim_stat(glp_prob *lp) "
/**
 * glp_get_prim_stat - retrieve status of primal basic solution .
 * <p>SYNOPSIS</p>
 * <p>int glp_get_prim_stat(glp_prob *lp);</p>
 * <p>RETURNS</p>
 * <p>The routine glp_get_prim_stat reports the status of the primal basic solution for the specified problem object as follows:</p>
 * <p>GLP_UNDEF - primal solution is undefined; GLP_FEAS - primal solution is feasible; GLP_INFEAS - primal solution is infeasible; GLP_NOFEAS - no primal feasible solution exists. </p>
 */
public";

%csmethodmodifiers glp_get_dual_stat(glp_prob *lp) "
/**
 * glp_get_dual_stat - retrieve status of dual basic solution .
 * <p>SYNOPSIS</p>
 * <p>int glp_get_dual_stat(glp_prob *lp);</p>
 * <p>RETURNS</p>
 * <p>The routine glp_get_dual_stat reports the status of the dual basic solution for the specified problem object as follows:</p>
 * <p>GLP_UNDEF - dual solution is undefined; GLP_FEAS - dual solution is feasible; GLP_INFEAS - dual solution is infeasible; GLP_NOFEAS - no dual feasible solution exists. </p>
 */
public";

%csmethodmodifiers glp_get_obj_val(glp_prob *lp) "
/**
 * glp_get_obj_val - retrieve objective value (basic solution) .
 * <p>SYNOPSIS</p>
 * <p>double glp_get_obj_val(glp_prob *lp);</p>
 * <p>RETURNS</p>
 * <p>The routine glp_get_obj_val returns value of the objective function for basic solution. </p>
 */
public";

%csmethodmodifiers glp_get_row_stat(glp_prob *lp, int i) "
/**
 * glp_get_row_stat - retrieve row status .
 * <p>SYNOPSIS</p>
 * <p>int glp_get_row_stat(glp_prob *lp, int i);</p>
 * <p>RETURNS</p>
 * <p>The routine glp_get_row_stat returns current status assigned to the auxiliary variable associated with i-th row as follows:</p>
 * <p>GLP_BS - basic variable; GLP_NL - non-basic variable on its lower bound; GLP_NU - non-basic variable on its upper bound; GLP_NF - non-basic free (unbounded) variable; GLP_NS - non-basic fixed variable. </p>
 */
public";

%csmethodmodifiers glp_get_row_prim(glp_prob *lp, int i) "
/**
 * glp_get_row_prim - retrieve row primal value (basic solution) .
 * <p>SYNOPSIS</p>
 * <p>double glp_get_row_prim(glp_prob *lp, int i);</p>
 * <p>RETURNS</p>
 * <p>The routine glp_get_row_prim returns primal value of the auxiliary variable associated with i-th row. </p>
 */
public";

%csmethodmodifiers glp_get_row_dual(glp_prob *lp, int i) "
/**
 * glp_get_row_dual - retrieve row dual value (basic solution) .
 * <p>SYNOPSIS</p>
 * <p>double glp_get_row_dual(glp_prob *lp, int i);</p>
 * <p>RETURNS</p>
 * <p>The routine glp_get_row_dual returns dual value (i.e. reduced cost) of the auxiliary variable associated with i-th row. </p>
 */
public";

%csmethodmodifiers glp_get_col_stat(glp_prob *lp, int j) "
/**
 * glp_get_col_stat - retrieve column status .
 * <p>SYNOPSIS</p>
 * <p>int glp_get_col_stat(glp_prob *lp, int j);</p>
 * <p>RETURNS</p>
 * <p>The routine glp_get_col_stat returns current status assigned to the structural variable associated with j-th column as follows:</p>
 * <p>GLP_BS - basic variable; GLP_NL - non-basic variable on its lower bound; GLP_NU - non-basic variable on its upper bound; GLP_NF - non-basic free (unbounded) variable; GLP_NS - non-basic fixed variable. </p>
 */
public";

%csmethodmodifiers glp_get_col_prim(glp_prob *lp, int j) "
/**
 * glp_get_col_prim - retrieve column primal value (basic solution) .
 * <p>SYNOPSIS</p>
 * <p>double glp_get_col_prim(glp_prob *lp, int j);</p>
 * <p>RETURNS</p>
 * <p>The routine glp_get_col_prim returns primal value of the structural variable associated with j-th column. </p>
 */
public";

%csmethodmodifiers glp_get_col_dual(glp_prob *lp, int j) "
/**
 * glp_get_col_dual - retrieve column dual value (basic solution) .
 * <p>SYNOPSIS</p>
 * <p>double glp_get_col_dual(glp_prob *lp, int j);</p>
 * <p>RETURNS</p>
 * <p>The routine glp_get_col_dual returns dual value (i.e. reduced cost) of the structural variable associated with j-th column. </p>
 */
public";

%csmethodmodifiers glp_get_unbnd_ray(glp_prob *lp) "
/**
 * glp_get_unbnd_ray - determine variable causing unboundedness .
 * <p>SYNOPSIS</p>
 * <p>int glp_get_unbnd_ray(glp_prob *lp);</p>
 * <p>RETURNS</p>
 * <p>The routine glp_get_unbnd_ray returns the number k of a variable, which causes primal or dual unboundedness. If 1 &lt;= k &lt;= m, it is k-th auxiliary variable, and if m+1 &lt;= k &lt;= m+n, it is (k-m)-th structural variable, where m is the number of rows, n is the number of columns in the problem object. If such variable is not defined, the routine returns 0.</p>
 * <p>COMMENTS</p>
 * <p>If it is not exactly known which version of the simplex solver detected unboundedness, i.e. whether the unboundedness is primal or dual, it is sufficient to check the status of the variable reported with the routine glp_get_row_stat or glp_get_col_stat. If the variable is non-basic, the unboundedness is primal, otherwise, if the variable is basic, the unboundedness is dual (the latter case means that the problem has no primal feasible dolution). </p>
 */
public";

%csmethodmodifiers glp_get_it_cnt(glp_prob *P) "
/**
 */
public";

%csmethodmodifiers glp_set_it_cnt(glp_prob *P, int it_cnt) "
/**
 */
public";

%csmethodmodifiers ssx_create(int m, int n, int nnz) "
/**
 */
public";

%csmethodmodifiers basis_col(void *info, int j, int ind[], mpq_t val[]) "
/**
 */
public";

%csmethodmodifiers ssx_factorize(SSX *ssx) "
/**
 */
public";

%csmethodmodifiers ssx_get_xNj(SSX *ssx, int j, mpq_t x) "
/**
 */
public";

%csmethodmodifiers ssx_eval_bbar(SSX *ssx) "
/**
 */
public";

%csmethodmodifiers ssx_eval_pi(SSX *ssx) "
/**
 */
public";

%csmethodmodifiers ssx_eval_dj(SSX *ssx, int j, mpq_t dj) "
/**
 */
public";

%csmethodmodifiers ssx_eval_cbar(SSX *ssx) "
/**
 */
public";

%csmethodmodifiers ssx_eval_rho(SSX *ssx) "
/**
 */
public";

%csmethodmodifiers ssx_eval_row(SSX *ssx) "
/**
 */
public";

%csmethodmodifiers ssx_eval_col(SSX *ssx) "
/**
 */
public";

%csmethodmodifiers ssx_chuzc(SSX *ssx) "
/**
 */
public";

%csmethodmodifiers ssx_chuzr(SSX *ssx) "
/**
 */
public";

%csmethodmodifiers ssx_update_bbar(SSX *ssx) "
/**
 */
public";

%csmethodmodifiers ssx_update_pi(SSX *ssx) "
/**
 */
public";

%csmethodmodifiers ssx_update_cbar(SSX *ssx) "
/**
 */
public";

%csmethodmodifiers ssx_change_basis(SSX *ssx) "
/**
 */
public";

%csmethodmodifiers ssx_delete(SSX *ssx) "
/**
 */
public";

%csmethodmodifiers transform(NPP *npp) "
/**
 * glp_interior - solve LP problem with the interior-point method .
 * <p>SYNOPSIS</p>
 * <p>int glp_interior(glp_prob *P, const glp_iptcp *parm);</p>
 * <p>The routine glp_interior is a driver to the LP solver based on the interior-point method.</p>
 * <p>The interior-point solver has a set of control parameters. Values of the control parameters can be passed in a structure glp_iptcp, which the parameter parm points to.</p>
 * <p>Currently this routine implements an easy variant of the primal-dual interior-point method based on Mehrotra's technique.</p>
 * <p>This routine transforms the original LP problem to an equivalent LP problem in the standard formulation (all constraints are equalities, all variables are non-negative), calls the routine ipm_main to solve the transformed problem, and then transforms an obtained solution to the solution of the original problem.</p>
 * <p>RETURNS</p>
 * <p>0 The LP problem instance has been successfully solved. This code does not necessarily mean that the solver has found optimal solution. It only means that the solution process was successful.</p>
 * <p>GLP_EFAIL The problem has no rows/columns.</p>
 * <p>GLP_ENOCVG Very slow convergence or divergence.</p>
 * <p>GLP_EITLIM Iteration limit exceeded.</p>
 * <p>GLP_EINSTAB Numerical instability on solving Newtonian system. </p>
 */
public";

%csmethodmodifiers glp_interior(glp_prob *P, const glp_iptcp *parm) "
/**
 */
public";

%csmethodmodifiers glp_init_iptcp(glp_iptcp *parm) "
/**
 * glp_init_iptcp - initialize interior-point solver control parameters .
 * <p>SYNOPSIS</p>
 * <p>void glp_init_iptcp(glp_iptcp *parm);</p>
 * <p>DESCRIPTION</p>
 * <p>The routine glp_init_iptcp initializes control parameters, which are used by the interior-point solver, with default values.</p>
 * <p>Default values of the control parameters are stored in the glp_iptcp structure, which the parameter parm points to. </p>
 */
public";

%csmethodmodifiers glp_ipt_status(glp_prob *lp) "
/**
 * glp_ipt_status - retrieve status of interior-point solution .
 * <p>SYNOPSIS</p>
 * <p>int glp_ipt_status(glp_prob *lp);</p>
 * <p>RETURNS</p>
 * <p>The routine glp_ipt_status reports the status of solution found by the interior-point solver as follows:</p>
 * <p>GLP_UNDEF - interior-point solution is undefined; GLP_OPT - interior-point solution is optimal; GLP_INFEAS - interior-point solution is infeasible; GLP_NOFEAS - no feasible solution exists. </p>
 */
public";

%csmethodmodifiers glp_ipt_obj_val(glp_prob *lp) "
/**
 * glp_ipt_obj_val - retrieve objective value (interior point) .
 * <p>SYNOPSIS</p>
 * <p>double glp_ipt_obj_val(glp_prob *lp);</p>
 * <p>RETURNS</p>
 * <p>The routine glp_ipt_obj_val returns value of the objective function for interior-point solution. </p>
 */
public";

%csmethodmodifiers glp_ipt_row_prim(glp_prob *lp, int i) "
/**
 * glp_ipt_row_prim - retrieve row primal value (interior point) .
 * <p>SYNOPSIS</p>
 * <p>double glp_ipt_row_prim(glp_prob *lp, int i);</p>
 * <p>RETURNS</p>
 * <p>The routine glp_ipt_row_prim returns primal value of the auxiliary variable associated with i-th row. </p>
 */
public";

%csmethodmodifiers glp_ipt_row_dual(glp_prob *lp, int i) "
/**
 * glp_ipt_row_dual - retrieve row dual value (interior point) .
 * <p>SYNOPSIS</p>
 * <p>double glp_ipt_row_dual(glp_prob *lp, int i);</p>
 * <p>RETURNS</p>
 * <p>The routine glp_ipt_row_dual returns dual value (i.e. reduced cost) of the auxiliary variable associated with i-th row. </p>
 */
public";

%csmethodmodifiers glp_ipt_col_prim(glp_prob *lp, int j) "
/**
 * glp_ipt_col_prim - retrieve column primal value (interior point) .
 * <p>SYNOPSIS</p>
 * <p>double glp_ipt_col_prim(glp_prob *lp, int j);</p>
 * <p>RETURNS</p>
 * <p>The routine glp_ipt_col_prim returns primal value of the structural variable associated with j-th column. </p>
 */
public";

%csmethodmodifiers glp_ipt_col_dual(glp_prob *lp, int j) "
/**
 * glp_ipt_col_dual - retrieve column dual value (interior point) .
 * <p>SYNOPSIS</p>
 * <p>double glp_ipt_col_dual(glp_prob *lp, int j);</p>
 * <p>RETURNS</p>
 * <p>The routine glp_ipt_col_dual returns dual value (i.e. reduced cost) of the structural variable associated with j-th column. </p>
 */
public";

%csmethodmodifiers fhv_ft_update(FHV *fhv, int q, int aq_len, const int aq_ind[], const double aq_val[], int ind[], double val[], double work[]) "
/**
 */
public";

%csmethodmodifiers fhv_h_solve(FHV *fhv, double x[]) "
/**
 */
public";

%csmethodmodifiers fhv_ht_solve(FHV *fhv, double x[]) "
/**
 */
public";

%csmethodmodifiers cresup(struct csa *csa) "
/**
 */
public";

%csmethodmodifiers chain(struct csa *csa, int lpick, int lsorc) "
/**
 */
public";

%csmethodmodifiers chnarc(struct csa *csa, int lsorc) "
/**
 */
public";

%csmethodmodifiers sort(struct csa *csa) "
/**
 */
public";

%csmethodmodifiers pickj(struct csa *csa, int it) "
/**
 */
public";

%csmethodmodifiers assign(struct csa *csa) "
/**
 */
public";

%csmethodmodifiers setran(struct csa *csa, int iseed) "
/**
 */
public";

%csmethodmodifiers iran(struct csa *csa, int ilow, int ihigh) "
/**
 */
public";

%csmethodmodifiers glp_netgen(glp_graph *G_, int _v_rhs, int _a_cap, int _a_cost, const int parm[1+15]) "
/**
 */
public";

%csmethodmodifiers glp_netgen_prob(int nprob, int parm[1+15]) "
/**
 */
public";

%csmethodmodifiers fp_add(MPL *mpl, double x, double y) "
/**
 */
public";

%csmethodmodifiers fp_sub(MPL *mpl, double x, double y) "
/**
 */
public";

%csmethodmodifiers fp_less(MPL *mpl, double x, double y) "
/**
 */
public";

%csmethodmodifiers fp_mul(MPL *mpl, double x, double y) "
/**
 */
public";

%csmethodmodifiers fp_div(MPL *mpl, double x, double y) "
/**
 */
public";

%csmethodmodifiers fp_idiv(MPL *mpl, double x, double y) "
/**
 */
public";

%csmethodmodifiers fp_mod(MPL *mpl, double x, double y) "
/**
 */
public";

%csmethodmodifiers fp_power(MPL *mpl, double x, double y) "
/**
 */
public";

%csmethodmodifiers fp_exp(MPL *mpl, double x) "
/**
 */
public";

%csmethodmodifiers fp_log(MPL *mpl, double x) "
/**
 */
public";

%csmethodmodifiers fp_log10(MPL *mpl, double x) "
/**
 */
public";

%csmethodmodifiers fp_sqrt(MPL *mpl, double x) "
/**
 */
public";

%csmethodmodifiers fp_sin(MPL *mpl, double x) "
/**
 */
public";

%csmethodmodifiers fp_cos(MPL *mpl, double x) "
/**
 */
public";

%csmethodmodifiers fp_atan(MPL *mpl, double x) "
/**
 */
public";

%csmethodmodifiers fp_atan2(MPL *mpl, double y, double x) "
/**
 */
public";

%csmethodmodifiers fp_round(MPL *mpl, double x, double n) "
/**
 */
public";

%csmethodmodifiers fp_trunc(MPL *mpl, double x, double n) "
/**
 */
public";

%csmethodmodifiers fp_irand224(MPL *mpl) "
/**
 */
public";

%csmethodmodifiers fp_uniform01(MPL *mpl) "
/**
 */
public";

%csmethodmodifiers fp_uniform(MPL *mpl, double a, double b) "
/**
 */
public";

%csmethodmodifiers fp_normal01(MPL *mpl) "
/**
 */
public";

%csmethodmodifiers fp_normal(MPL *mpl, double mu, double sigma) "
/**
 */
public";

%csmethodmodifiers create_string(MPL *mpl, char buf[MAX_LENGTH+1]) "
/**
 */
public";

%csmethodmodifiers copy_string(MPL *mpl, STRING *str) "
/**
 */
public";

%csmethodmodifiers compare_strings(MPL *mpl, STRING *str1, STRING *str2) "
/**
 */
public";

%csmethodmodifiers fetch_string(MPL *mpl, STRING *str, char buf[MAX_LENGTH+1]) "
/**
 */
public";

%csmethodmodifiers delete_string(MPL *mpl, STRING *str) "
/**
 */
public";

%csmethodmodifiers create_symbol_num(MPL *mpl, double num) "
/**
 */
public";

%csmethodmodifiers create_symbol_str(MPL *mpl, STRING *str) "
/**
 */
public";

%csmethodmodifiers copy_symbol(MPL *mpl, SYMBOL *sym) "
/**
 */
public";

%csmethodmodifiers compare_symbols(MPL *mpl, SYMBOL *sym1, SYMBOL *sym2) "
/**
 */
public";

%csmethodmodifiers delete_symbol(MPL *mpl, SYMBOL *sym) "
/**
 */
public";

%csmethodmodifiers format_symbol(MPL *mpl, SYMBOL *sym) "
/**
 */
public";

%csmethodmodifiers concat_symbols(MPL *mpl, SYMBOL *sym1, SYMBOL *sym2) "
/**
 */
public";

%csmethodmodifiers create_tuple(MPL *mpl) "
/**
 */
public";

%csmethodmodifiers expand_tuple(MPL *mpl, TUPLE *tuple, SYMBOL *sym) "
/**
 */
public";

%csmethodmodifiers tuple_dimen(MPL *mpl, TUPLE *tuple) "
/**
 */
public";

%csmethodmodifiers copy_tuple(MPL *mpl, TUPLE *tuple) "
/**
 */
public";

%csmethodmodifiers compare_tuples(MPL *mpl, TUPLE *tuple1, TUPLE *tuple2) "
/**
 */
public";

%csmethodmodifiers build_subtuple(MPL *mpl, TUPLE *tuple, int dim) "
/**
 */
public";

%csmethodmodifiers delete_tuple(MPL *mpl, TUPLE *tuple) "
/**
 */
public";

%csmethodmodifiers format_tuple(MPL *mpl, int c, TUPLE *tuple) "
/**
 */
public";

%csmethodmodifiers create_elemset(MPL *mpl, int dim) "
/**
 */
public";

%csmethodmodifiers find_tuple(MPL *mpl, ELEMSET *set, TUPLE *tuple) "
/**
 */
public";

%csmethodmodifiers add_tuple(MPL *mpl, ELEMSET *set, TUPLE *tuple) "
/**
 */
public";

%csmethodmodifiers check_then_add(MPL *mpl, ELEMSET *set, TUPLE *tuple) "
/**
 */
public";

%csmethodmodifiers copy_elemset(MPL *mpl, ELEMSET *set) "
/**
 */
public";

%csmethodmodifiers delete_elemset(MPL *mpl, ELEMSET *set) "
/**
 */
public";

%csmethodmodifiers arelset_size(MPL *mpl, double t0, double tf, double dt) "
/**
 */
public";

%csmethodmodifiers arelset_member(MPL *mpl, double t0, double tf, double dt, int j) "
/**
 */
public";

%csmethodmodifiers create_arelset(MPL *mpl, double t0, double tf, double dt) "
/**
 */
public";

%csmethodmodifiers set_union(MPL *mpl, ELEMSET *X, ELEMSET *Y) "
/**
 */
public";

%csmethodmodifiers set_diff(MPL *mpl, ELEMSET *X, ELEMSET *Y) "
/**
 */
public";

%csmethodmodifiers set_symdiff(MPL *mpl, ELEMSET *X, ELEMSET *Y) "
/**
 */
public";

%csmethodmodifiers set_inter(MPL *mpl, ELEMSET *X, ELEMSET *Y) "
/**
 */
public";

%csmethodmodifiers set_cross(MPL *mpl, ELEMSET *X, ELEMSET *Y) "
/**
 */
public";

%csmethodmodifiers constant_term(MPL *mpl, double coef) "
/**
 */
public";

%csmethodmodifiers single_variable(MPL *mpl, ELEMVAR *var) "
/**
 */
public";

%csmethodmodifiers copy_formula(MPL *mpl, FORMULA *form) "
/**
 */
public";

%csmethodmodifiers delete_formula(MPL *mpl, FORMULA *form) "
/**
 */
public";

%csmethodmodifiers linear_comb(MPL *mpl, double a, FORMULA *fx, double b, FORMULA *fy) "
/**
 */
public";

%csmethodmodifiers remove_constant(MPL *mpl, FORMULA *form, double *coef) "
/**
 */
public";

%csmethodmodifiers reduce_terms(MPL *mpl, FORMULA *form) "
/**
 */
public";

%csmethodmodifiers delete_value(MPL *mpl, int type, VALUE *value) "
/**
 */
public";

%csmethodmodifiers create_array(MPL *mpl, int type, int dim) "
/**
 */
public";

%csmethodmodifiers compare_member_tuples(void *info, const void *key1, const void *key2) "
/**
 */
public";

%csmethodmodifiers find_member(MPL *mpl, ARRAY *array, TUPLE *tuple) "
/**
 */
public";

%csmethodmodifiers add_member(MPL *mpl, ARRAY *array, TUPLE *tuple) "
/**
 */
public";

%csmethodmodifiers delete_array(MPL *mpl, ARRAY *array) "
/**
 */
public";

%csmethodmodifiers assign_dummy_index(MPL *mpl, DOMAIN_SLOT *slot, SYMBOL *value) "
/**
 */
public";

%csmethodmodifiers update_dummy_indices(MPL *mpl, DOMAIN_BLOCK *block) "
/**
 */
public";

%csmethodmodifiers enter_domain_block(MPL *mpl, DOMAIN_BLOCK *block, TUPLE *tuple, void *info, void(*func)(MPL *mpl, void *info)) "
/**
 */
public";

%csmethodmodifiers eval_domain_func(MPL *mpl, void *_my_info) "
/**
 */
public";

%csmethodmodifiers eval_within_domain(MPL *mpl, DOMAIN *domain, TUPLE *tuple, void *info, void(*func)(MPL *mpl, void *info)) "
/**
 */
public";

%csmethodmodifiers loop_domain_func(MPL *mpl, void *_my_info) "
/**
 */
public";

%csmethodmodifiers loop_within_domain(MPL *mpl, DOMAIN *domain, void *info, int(*func)(MPL *mpl, void *info)) "
/**
 */
public";

%csmethodmodifiers out_of_domain(MPL *mpl, char *name, TUPLE *tuple) "
/**
 */
public";

%csmethodmodifiers get_domain_tuple(MPL *mpl, DOMAIN *domain) "
/**
 */
public";

%csmethodmodifiers clean_domain(MPL *mpl, DOMAIN *domain) "
/**
 */
public";

%csmethodmodifiers check_elem_set(MPL *mpl, SET *set, TUPLE *tuple, ELEMSET *refer) "
/**
 */
public";

%csmethodmodifiers take_member_set(MPL *mpl, SET *set, TUPLE *tuple) "
/**
 */
public";

%csmethodmodifiers eval_set_func(MPL *mpl, void *_info) "
/**
 */
public";

%csmethodmodifiers saturate_set(MPL *mpl, SET *set) "
/**
 */
public";

%csmethodmodifiers eval_member_set(MPL *mpl, SET *set, TUPLE *tuple) "
/**
 */
public";

%csmethodmodifiers whole_set_func(MPL *mpl, void *info) "
/**
 */
public";

%csmethodmodifiers eval_whole_set(MPL *mpl, SET *set) "
/**
 */
public";

%csmethodmodifiers clean_set(MPL *mpl, SET *set) "
/**
 */
public";

%csmethodmodifiers check_value_num(MPL *mpl, PARAMETER *par, TUPLE *tuple, double value) "
/**
 */
public";

%csmethodmodifiers take_member_num(MPL *mpl, PARAMETER *par, TUPLE *tuple) "
/**
 */
public";

%csmethodmodifiers eval_num_func(MPL *mpl, void *_info) "
/**
 */
public";

%csmethodmodifiers eval_member_num(MPL *mpl, PARAMETER *par, TUPLE *tuple) "
/**
 */
public";

%csmethodmodifiers check_value_sym(MPL *mpl, PARAMETER *par, TUPLE *tuple, SYMBOL *value) "
/**
 */
public";

%csmethodmodifiers take_member_sym(MPL *mpl, PARAMETER *par, TUPLE *tuple) "
/**
 */
public";

%csmethodmodifiers eval_sym_func(MPL *mpl, void *_info) "
/**
 */
public";

%csmethodmodifiers eval_member_sym(MPL *mpl, PARAMETER *par, TUPLE *tuple) "
/**
 */
public";

%csmethodmodifiers whole_par_func(MPL *mpl, void *info) "
/**
 */
public";

%csmethodmodifiers eval_whole_par(MPL *mpl, PARAMETER *par) "
/**
 */
public";

%csmethodmodifiers clean_parameter(MPL *mpl, PARAMETER *par) "
/**
 */
public";

%csmethodmodifiers take_member_var(MPL *mpl, VARIABLE *var, TUPLE *tuple) "
/**
 */
public";

%csmethodmodifiers eval_var_func(MPL *mpl, void *_info) "
/**
 */
public";

%csmethodmodifiers eval_member_var(MPL *mpl, VARIABLE *var, TUPLE *tuple) "
/**
 */
public";

%csmethodmodifiers whole_var_func(MPL *mpl, void *info) "
/**
 */
public";

%csmethodmodifiers eval_whole_var(MPL *mpl, VARIABLE *var) "
/**
 */
public";

%csmethodmodifiers clean_variable(MPL *mpl, VARIABLE *var) "
/**
 */
public";

%csmethodmodifiers take_member_con(MPL *mpl, CONSTRAINT *con, TUPLE *tuple) "
/**
 */
public";

%csmethodmodifiers eval_con_func(MPL *mpl, void *_info) "
/**
 */
public";

%csmethodmodifiers eval_member_con(MPL *mpl, CONSTRAINT *con, TUPLE *tuple) "
/**
 */
public";

%csmethodmodifiers whole_con_func(MPL *mpl, void *info) "
/**
 */
public";

%csmethodmodifiers eval_whole_con(MPL *mpl, CONSTRAINT *con) "
/**
 */
public";

%csmethodmodifiers clean_constraint(MPL *mpl, CONSTRAINT *con) "
/**
 */
public";

%csmethodmodifiers iter_num_func(MPL *mpl, void *_info) "
/**
 */
public";

%csmethodmodifiers eval_numeric(MPL *mpl, CODE *code) "
/**
 */
public";

%csmethodmodifiers eval_symbolic(MPL *mpl, CODE *code) "
/**
 */
public";

%csmethodmodifiers iter_log_func(MPL *mpl, void *_info) "
/**
 */
public";

%csmethodmodifiers eval_logical(MPL *mpl, CODE *code) "
/**
 */
public";

%csmethodmodifiers eval_tuple(MPL *mpl, CODE *code) "
/**
 */
public";

%csmethodmodifiers iter_set_func(MPL *mpl, void *_info) "
/**
 */
public";

%csmethodmodifiers eval_elemset(MPL *mpl, CODE *code) "
/**
 */
public";

%csmethodmodifiers null_func(MPL *mpl, void *info) "
/**
 */
public";

%csmethodmodifiers is_member(MPL *mpl, CODE *code, TUPLE *tuple) "
/**
 */
public";

%csmethodmodifiers iter_form_func(MPL *mpl, void *_info) "
/**
 */
public";

%csmethodmodifiers eval_formula(MPL *mpl, CODE *code) "
/**
 */
public";

%csmethodmodifiers clean_code(MPL *mpl, CODE *code) "
/**
 */
public";

%csmethodmodifiers mpl_tab_num_args(TABDCA *dca) "
/**
 */
public";

%csmethodmodifiers mpl_tab_get_arg(TABDCA *dca, int k) "
/**
 */
public";

%csmethodmodifiers mpl_tab_num_flds(TABDCA *dca) "
/**
 */
public";

%csmethodmodifiers mpl_tab_get_name(TABDCA *dca, int k) "
/**
 */
public";

%csmethodmodifiers mpl_tab_get_type(TABDCA *dca, int k) "
/**
 */
public";

%csmethodmodifiers mpl_tab_get_num(TABDCA *dca, int k) "
/**
 */
public";

%csmethodmodifiers mpl_tab_get_str(TABDCA *dca, int k) "
/**
 */
public";

%csmethodmodifiers mpl_tab_set_num(TABDCA *dca, int k, double num) "
/**
 */
public";

%csmethodmodifiers mpl_tab_set_str(TABDCA *dca, int k, const char *str) "
/**
 */
public";

%csmethodmodifiers write_func(MPL *mpl, void *info) "
/**
 */
public";

%csmethodmodifiers execute_table(MPL *mpl, TABLE *tab) "
/**
 */
public";

%csmethodmodifiers free_dca(MPL *mpl) "
/**
 */
public";

%csmethodmodifiers clean_table(MPL *mpl, TABLE *tab) "
/**
 */
public";

%csmethodmodifiers check_func(MPL *mpl, void *info) "
/**
 */
public";

%csmethodmodifiers execute_check(MPL *mpl, CHECK *chk) "
/**
 */
public";

%csmethodmodifiers clean_check(MPL *mpl, CHECK *chk) "
/**
 */
public";

%csmethodmodifiers display_set(MPL *mpl, SET *set, MEMBER *memb) "
/**
 */
public";

%csmethodmodifiers display_par(MPL *mpl, PARAMETER *par, MEMBER *memb) "
/**
 */
public";

%csmethodmodifiers display_var(MPL *mpl, VARIABLE *var, MEMBER *memb, int suff) "
/**
 */
public";

%csmethodmodifiers display_con(MPL *mpl, CONSTRAINT *con, MEMBER *memb, int suff) "
/**
 */
public";

%csmethodmodifiers display_memb(MPL *mpl, CODE *code) "
/**
 */
public";

%csmethodmodifiers display_code(MPL *mpl, CODE *code) "
/**
 */
public";

%csmethodmodifiers display_func(MPL *mpl, void *info) "
/**
 */
public";

%csmethodmodifiers execute_display(MPL *mpl, DISPLAY *dpy) "
/**
 */
public";

%csmethodmodifiers clean_display(MPL *mpl, DISPLAY *dpy) "
/**
 */
public";

%csmethodmodifiers print_char(MPL *mpl, int c) "
/**
 */
public";

%csmethodmodifiers print_text(MPL *mpl, char *fmt,...) "
/**
 */
public";

%csmethodmodifiers printf_func(MPL *mpl, void *info) "
/**
 */
public";

%csmethodmodifiers execute_printf(MPL *mpl, PRINTF *prt) "
/**
 */
public";

%csmethodmodifiers clean_printf(MPL *mpl, PRINTF *prt) "
/**
 */
public";

%csmethodmodifiers for_func(MPL *mpl, void *info) "
/**
 */
public";

%csmethodmodifiers execute_for(MPL *mpl, FOR *fur) "
/**
 */
public";

%csmethodmodifiers clean_for(MPL *mpl, FOR *fur) "
/**
 */
public";

%csmethodmodifiers execute_statement(MPL *mpl, STATEMENT *stmt) "
/**
 */
public";

%csmethodmodifiers clean_statement(MPL *mpl, STATEMENT *stmt) "
/**
 */
public";

%csmethodmodifiers fcmp(const void *e1, const void *e2) "
/**
 */
public";

%csmethodmodifiers analyze_ineq(glp_prob *P, CFG *G, int len, int ind[], double val[], double rhs, struct term t[]) "
/**
 */
public";

%csmethodmodifiers cfg_build_graph(void *P_) "
/**
 */
public";

%csmethodmodifiers build_subgraph(struct csa *csa) "
/**
 */
public";

%csmethodmodifiers sub_adjacent(struct csa *csa, int i, int adj[]) "
/**
 */
public";

%csmethodmodifiers find_clique(struct csa *csa, int c_ind[]) "
/**
 */
public";

%csmethodmodifiers func(void *info, int i, int ind[]) "
/**
 */
public";

%csmethodmodifiers find_clique1(struct csa *csa, int c_ind[]) "
/**
 */
public";

%csmethodmodifiers cfg_find_clique(void *P, CFG *G, int ind[], double *sum_) "
/**
 */
public";

%csmethodmodifiers gcd(int x, int y) "
/**
 * gcd - find greatest common divisor of two integers .
 * <p>SYNOPSIS</p>
 * <p>#include \"misc.h\" int gcd(int x, int y);</p>
 * <p>RETURNS</p>
 * <p>The routine gcd returns gcd(x, y), the greatest common divisor of the two positive integers given.</p>
 * <p>ALGORITHM</p>
 * <p>The routine gcd is based on Euclid's algorithm.</p>
 * <p>REFERENCES</p>
 * <p>Don Knuth, The Art of Computer Programming, Vol.2: Seminumerical Algorithms, 3rd Edition, Addison-Wesley, 1997. Section 4.5.2: The Greatest Common Divisor, pp. 333-56. </p>
 */
public";

%csmethodmodifiers gcdn(int n, int x[]) "
/**
 * gcdn - find greatest common divisor of n integers .
 * <p>SYNOPSIS</p>
 * <p>#include \"misc.h\" int gcdn(int n, int x[]);</p>
 * <p>RETURNS</p>
 * <p>The routine gcdn returns gcd(x[1], x[2], ..., x[n]), the greatest common divisor of n positive integers given, n &gt; 0.</p>
 * <p>BACKGROUND</p>
 * <p>The routine gcdn is based on the following identity:</p>
 * <p>gcd(x, y, z) = gcd(gcd(x, y), z).</p>
 * <p>REFERENCES</p>
 * <p>Don Knuth, The Art of Computer Programming, Vol.2: Seminumerical Algorithms, 3rd Edition, Addison-Wesley, 1997. Section 4.5.2: The Greatest Common Divisor, pp. 333-56. </p>
 */
public";

%csmethodmodifiers enter_context(MPL *mpl) "
/**
 */
public";

%csmethodmodifiers print_context(MPL *mpl) "
/**
 */
public";

%csmethodmodifiers get_char(MPL *mpl) "
/**
 */
public";

%csmethodmodifiers append_char(MPL *mpl) "
/**
 */
public";

%csmethodmodifiers get_token(MPL *mpl) "
/**
 */
public";

%csmethodmodifiers unget_token(MPL *mpl) "
/**
 */
public";

%csmethodmodifiers is_keyword(MPL *mpl, char *keyword) "
/**
 */
public";

%csmethodmodifiers is_reserved(MPL *mpl) "
/**
 */
public";

%csmethodmodifiers make_code(MPL *mpl, int op, OPERANDS *arg, int type, int dim) "
/**
 */
public";

%csmethodmodifiers make_unary(MPL *mpl, int op, CODE *x, int type, int dim) "
/**
 */
public";

%csmethodmodifiers make_binary(MPL *mpl, int op, CODE *x, CODE *y, int type, int dim) "
/**
 */
public";

%csmethodmodifiers make_ternary(MPL *mpl, int op, CODE *x, CODE *y, CODE *z, int type, int dim) "
/**
 */
public";

%csmethodmodifiers numeric_literal(MPL *mpl) "
/**
 */
public";

%csmethodmodifiers string_literal(MPL *mpl) "
/**
 */
public";

%csmethodmodifiers create_arg_list(MPL *mpl) "
/**
 */
public";

%csmethodmodifiers expand_arg_list(MPL *mpl, ARG_LIST *list, CODE *x) "
/**
 */
public";

%csmethodmodifiers arg_list_len(MPL *mpl, ARG_LIST *list) "
/**
 */
public";

%csmethodmodifiers subscript_list(MPL *mpl) "
/**
 */
public";

%csmethodmodifiers object_reference(MPL *mpl) "
/**
 */
public";

%csmethodmodifiers numeric_argument(MPL *mpl, char *func) "
/**
 */
public";

%csmethodmodifiers symbolic_argument(MPL *mpl, char *func) "
/**
 */
public";

%csmethodmodifiers elemset_argument(MPL *mpl, char *func) "
/**
 */
public";

%csmethodmodifiers function_reference(MPL *mpl) "
/**
 */
public";

%csmethodmodifiers create_domain(MPL *mpl) "
/**
 */
public";

%csmethodmodifiers create_block(MPL *mpl) "
/**
 */
public";

%csmethodmodifiers append_block(MPL *mpl, DOMAIN *domain, DOMAIN_BLOCK *block) "
/**
 */
public";

%csmethodmodifiers append_slot(MPL *mpl, DOMAIN_BLOCK *block, char *name, CODE *code) "
/**
 */
public";

%csmethodmodifiers expression_list(MPL *mpl) "
/**
 */
public";

%csmethodmodifiers literal_set(MPL *mpl, CODE *code) "
/**
 */
public";

%csmethodmodifiers indexing_expression(MPL *mpl) "
/**
 */
public";

%csmethodmodifiers close_scope(MPL *mpl, DOMAIN *domain) "
/**
 */
public";

%csmethodmodifiers link_up(CODE *code) "
/**
 */
public";

%csmethodmodifiers iterated_expression(MPL *mpl) "
/**
 */
public";

%csmethodmodifiers domain_arity(MPL *mpl, DOMAIN *domain) "
/**
 */
public";

%csmethodmodifiers set_expression(MPL *mpl) "
/**
 */
public";

%csmethodmodifiers branched_expression(MPL *mpl) "
/**
 */
public";

%csmethodmodifiers primary_expression(MPL *mpl) "
/**
 */
public";

%csmethodmodifiers error_preceding(MPL *mpl, char *opstr) "
/**
 */
public";

%csmethodmodifiers error_following(MPL *mpl, char *opstr) "
/**
 */
public";

%csmethodmodifiers error_dimension(MPL *mpl, char *opstr, int dim1, int dim2) "
/**
 */
public";

%csmethodmodifiers expression_0(MPL *mpl) "
/**
 */
public";

%csmethodmodifiers expression_1(MPL *mpl) "
/**
 */
public";

%csmethodmodifiers expression_2(MPL *mpl) "
/**
 */
public";

%csmethodmodifiers expression_3(MPL *mpl) "
/**
 */
public";

%csmethodmodifiers expression_4(MPL *mpl) "
/**
 */
public";

%csmethodmodifiers expression_5(MPL *mpl) "
/**
 */
public";

%csmethodmodifiers expression_6(MPL *mpl) "
/**
 */
public";

%csmethodmodifiers expression_7(MPL *mpl) "
/**
 */
public";

%csmethodmodifiers expression_8(MPL *mpl) "
/**
 */
public";

%csmethodmodifiers expression_9(MPL *mpl) "
/**
 */
public";

%csmethodmodifiers expression_10(MPL *mpl) "
/**
 */
public";

%csmethodmodifiers expression_11(MPL *mpl) "
/**
 */
public";

%csmethodmodifiers expression_12(MPL *mpl) "
/**
 */
public";

%csmethodmodifiers expression_13(MPL *mpl) "
/**
 */
public";

%csmethodmodifiers set_statement(MPL *mpl) "
/**
 */
public";

%csmethodmodifiers parameter_statement(MPL *mpl) "
/**
 */
public";

%csmethodmodifiers variable_statement(MPL *mpl) "
/**
 */
public";

%csmethodmodifiers constraint_statement(MPL *mpl) "
/**
 */
public";

%csmethodmodifiers objective_statement(MPL *mpl) "
/**
 */
public";

%csmethodmodifiers table_statement(MPL *mpl) "
/**
 */
public";

%csmethodmodifiers solve_statement(MPL *mpl) "
/**
 */
public";

%csmethodmodifiers check_statement(MPL *mpl) "
/**
 */
public";

%csmethodmodifiers display_statement(MPL *mpl) "
/**
 */
public";

%csmethodmodifiers printf_statement(MPL *mpl) "
/**
 */
public";

%csmethodmodifiers for_statement(MPL *mpl) "
/**
 */
public";

%csmethodmodifiers end_statement(MPL *mpl) "
/**
 */
public";

%csmethodmodifiers simple_statement(MPL *mpl, int spec) "
/**
 */
public";

%csmethodmodifiers model_section(MPL *mpl) "
/**
 */
public";

%csmethodmodifiers ffalg(int nv, int na, const int tail[], const int head[], int s, int t, const int cap[], int x[], char cut[]) "
/**
 * ffalg - Ford-Fulkerson algorithm .
 * <p>SYNOPSIS</p>
 * <p>#include \"ffalg.h\" void ffalg(int nv, int na, const int tail[], const int head[], int s, int t, const int cap[], int x[], char cut[]);</p>
 * <p>DESCRIPTION</p>
 * <p>The routine ffalg implements the Ford-Fulkerson algorithm to find a maximal flow in the specified flow network.</p>
 * <p>INPUT PARAMETERS</p>
 * <p>nv is the number of nodes, nv &gt;= 2.</p>
 * <p>na is the number of arcs, na &gt;= 0.</p>
 * <p>tail[a], a = 1,...,na, is the index of tail node of arc a.</p>
 * <p>head[a], a = 1,...,na, is the index of head node of arc a.</p>
 * <p>s is the source node index, 1 &lt;= s &lt;= nv.</p>
 * <p>t is the sink node index, 1 &lt;= t &lt;= nv, t != s.</p>
 * <p>cap[a], a = 1,...,na, is the capacity of arc a, cap[a] &gt;= 0.</p>
 * <p>NOTE: Multiple arcs are allowed, but self-loops are not allowed.</p>
 * <p>OUTPUT PARAMETERS</p>
 * <p>x[a], a = 1,...,na, is optimal value of the flow through arc a.</p>
 * <p>cut[i], i = 1,...,nv, is 1 if node i is labelled, and 0 otherwise. The set of arcs, whose one endpoint is labelled and other is not, defines the minimal cut corresponding to the maximal flow found. If the parameter cut is NULL, the cut information are not stored.</p>
 * <p>REFERENCES</p>
 * <p>L.R.Ford, Jr., and D.R.Fulkerson, \"Flows in Networks,\" The RAND Corp., Report R-375-PR (August 1962), Chap. I \"Static Maximal Flow,\" pp.30-33. </p>
 */
public";

%csmethodmodifiers AMD_postorder(Int nn, Int Parent[], Int Nv[], Int Fsize[], Int Order[], Int Child[], Int Sibling[], Int Stack[]) "
/**
 */
public";

%csmethodmodifiers bfx_create_binv(void) "
/**
 */
public";

%csmethodmodifiers bfx_factorize(BFX *binv, int m, int(*col)(void *info, int j, int ind[], mpq_t val[]), void *info) "
/**
 */
public";

%csmethodmodifiers bfx_ftran(BFX *binv, mpq_t x[], int save) "
/**
 */
public";

%csmethodmodifiers bfx_btran(BFX *binv, mpq_t x[]) "
/**
 */
public";

%csmethodmodifiers bfx_update(BFX *binv, int j) "
/**
 */
public";

%csmethodmodifiers bfx_delete_binv(BFX *binv) "
/**
 */
public";

%csmethodmodifiers glp_weak_comp(glp_graph *G, int v_num) "
/**
 * glp_weak_comp - find all weakly connected components of graph .
 * <p>SYNOPSIS</p>
 * <p>int glp_weak_comp(glp_graph *G, int v_num);</p>
 * <p>DESCRIPTION</p>
 * <p>The routine glp_weak_comp finds all weakly connected components of the specified graph.</p>
 * <p>The parameter v_num specifies an offset of the field of type int in the vertex data block, to which the routine stores the number of a (weakly) connected component containing that vertex. If v_num &lt; 0, no component numbers are stored.</p>
 * <p>The components are numbered in arbitrary order from 1 to nc, where nc is the total number of components found, 0 &lt;= nc &lt;= |V|.</p>
 * <p>RETURNS</p>
 * <p>The routine returns nc, the total number of components found. </p>
 */
public";

%csmethodmodifiers glp_strong_comp(glp_graph *G, int v_num) "
/**
 * glp_strong_comp - find all strongly connected components of graph .
 * <p>SYNOPSIS</p>
 * <p>int glp_strong_comp(glp_graph *G, int v_num);</p>
 * <p>DESCRIPTION</p>
 * <p>The routine glp_strong_comp finds all strongly connected components of the specified graph.</p>
 * <p>The parameter v_num specifies an offset of the field of type int in the vertex data block, to which the routine stores the number of a strongly connected component containing that vertex. If v_num &lt; 0, no component numbers are stored.</p>
 * <p>The components are numbered in arbitrary order from 1 to nc, where nc is the total number of components found, 0 &lt;= nc &lt;= |V|. However, the component numbering has the property that for every arc (i-&gt;j) in the graph the condition num(i) &gt;= num(j) holds.</p>
 * <p>RETURNS</p>
 * <p>The routine returns nc, the total number of components found. </p>
 */
public";

%csmethodmodifiers top_sort(glp_graph *G, int num[]) "
/**
 * glp_top_sort - topological sorting of acyclic digraph .
 * <p>SYNOPSIS</p>
 * <p>int glp_top_sort(glp_graph *G, int v_num);</p>
 * <p>DESCRIPTION</p>
 * <p>The routine glp_top_sort performs topological sorting of vertices of the specified acyclic digraph.</p>
 * <p>The parameter v_num specifies an offset of the field of type int in the vertex data block, to which the routine stores the vertex number assigned. If v_num &lt; 0, vertex numbers are not stored.</p>
 * <p>The vertices are numbered from 1 to n, where n is the total number of vertices in the graph. The vertex numbering has the property that for every arc (i-&gt;j) in the graph the condition num(i) &lt; num(j) holds. Special case num(i) = 0 means that vertex i is not assigned a number, because the graph is not acyclic.</p>
 * <p>RETURNS</p>
 * <p>If the graph is acyclic and therefore all the vertices have been assigned numbers, the routine glp_top_sort returns zero. Otherwise, if the graph is not acyclic, the routine returns the number of vertices which have not been numbered, i.e. for which num(i) = 0. </p>
 */
public";

%csmethodmodifiers glp_top_sort(glp_graph *G, int v_num) "
/**
 */
public";

%csmethodmodifiers sgf_reduce_nuc(LUF *luf, int *k1_, int *k2_, int cnt[], int list[]) "
/**
 */
public";

%csmethodmodifiers sgf_singl_phase(LUF *luf, int k1, int k2, int updat, int ind[], double val[]) "
/**
 */
public";

%csmethodmodifiers sgf_choose_pivot(SGF *sgf, int *p_, int *q_) "
/**
 */
public";

%csmethodmodifiers sgf_eliminate(SGF *sgf, int p, int q) "
/**
 */
public";

%csmethodmodifiers sgf_dense_lu(int n, double a_[], int r[], int c[], double eps) "
/**
 */
public";

%csmethodmodifiers sgf_dense_phase(LUF *luf, int k, int updat) "
/**
 */
public";

%csmethodmodifiers sgf_factorize(SGF *sgf, int singl) "
/**
 */
public";

%csmethodmodifiers uncompress(Bytef *dest, uLongf *destLen, const Bytef *source, uLong sourceLen) "
/**
 */
public";

%csmethodmodifiers fcmp(const void *xx, const void *yy) "
/**
 */
public";

%csmethodmodifiers wclique1(int n, const double w[], int(*func)(void *info, int i, int ind[]), void *info, int c[]) "
/**
 */
public";

%csmethodmodifiers glp_set_rii(glp_prob *lp, int i, double rii) "
/**
 * glp_set_rii - set (change) row scale factor .
 * <p>SYNOPSIS</p>
 * <p>void glp_set_rii(glp_prob *lp, int i, double rii);</p>
 * <p>DESCRIPTION</p>
 * <p>The routine glp_set_rii sets (changes) the scale factor r[i,i] for i-th row of the specified problem object. </p>
 */
public";

%csmethodmodifiers glp_set_sjj(glp_prob *lp, int j, double sjj) "
/**
 * glp_set sjj - set (change) column scale factor .
 * <p>SYNOPSIS</p>
 * <p>void glp_set_sjj(glp_prob *lp, int j, double sjj);</p>
 * <p>DESCRIPTION</p>
 * <p>The routine glp_set_sjj sets (changes) the scale factor s[j,j] for j-th column of the specified problem object. </p>
 */
public";

%csmethodmodifiers glp_get_rii(glp_prob *lp, int i) "
/**
 * glp_get_rii - retrieve row scale factor .
 * <p>SYNOPSIS</p>
 * <p>double glp_get_rii(glp_prob *lp, int i);</p>
 * <p>RETURNS</p>
 * <p>The routine glp_get_rii returns current scale factor r[i,i] for i-th row of the specified problem object. </p>
 */
public";

%csmethodmodifiers glp_get_sjj(glp_prob *lp, int j) "
/**
 * glp_get_sjj - retrieve column scale factor .
 * <p>SYNOPSIS</p>
 * <p>double glp_get_sjj(glp_prob *lp, int j);</p>
 * <p>RETURNS</p>
 * <p>The routine glp_get_sjj returns current scale factor s[j,j] for j-th column of the specified problem object. </p>
 */
public";

%csmethodmodifiers glp_unscale_prob(glp_prob *lp) "
/**
 * glp_unscale_prob - unscale problem data .
 * <p>SYNOPSIS</p>
 * <p>void glp_unscale_prob(glp_prob *lp);</p>
 * <p>DESCRIPTION</p>
 * <p>The routine glp_unscale_prob performs unscaling of problem data for the specified problem object.</p>
 * <p>\"Unscaling\" means replacing the current scaling matrices R and S by unity matrices that cancels the scaling effect. </p>
 */
public";

%csmethodmodifiers cover2(int n, double a[], double b, double u, double x[], double y, int cov[], double *_alfa, double *_beta) "
/**
 */
public";

%csmethodmodifiers cover3(int n, double a[], double b, double u, double x[], double y, int cov[], double *_alfa, double *_beta) "
/**
 */
public";

%csmethodmodifiers cover4(int n, double a[], double b, double u, double x[], double y, int cov[], double *_alfa, double *_beta) "
/**
 */
public";

%csmethodmodifiers cover(int n, double a[], double b, double u, double x[], double y, int cov[], double *alfa, double *beta) "
/**
 */
public";

%csmethodmodifiers lpx_cover_cut(glp_prob *lp, int len, int ind[], double val[], double work[]) "
/**
 */
public";

%csmethodmodifiers lpx_eval_row(glp_prob *lp, int len, int ind[], double val[]) "
/**
 */
public";

%csmethodmodifiers ios_cov_gen(glp_tree *tree) "
/**
 * ios_cov_gen - generate mixed cover cuts .
 * <p>SYNOPSIS</p>
 * <p>#include \"glpios.h\" void ios_cov_gen(glp_tree *tree);</p>
 * <p>DESCRIPTION</p>
 * <p>The routine ios_cov_gen generates mixed cover cuts for the current point and adds them to the cut pool. </p>
 */
public";

%csmethodmodifiers AMD_preprocess(Int n, const Int Ap[], const Int Ai[], Int Rp[], Int Ri[], Int W[], Int Flag[]) "
/**
 */
public";

%csmethodmodifiers fcmp(const void *x, const void *y) "
/**
 */
public";

%csmethodmodifiers ios_feas_pump(glp_tree *T) "
/**
 */
public";

%csmethodmodifiers npp_create_wksp(void) "
/**
 */
public";

%csmethodmodifiers npp_insert_row(NPP *npp, NPPROW *row, int where) "
/**
 */
public";

%csmethodmodifiers npp_remove_row(NPP *npp, NPPROW *row) "
/**
 */
public";

%csmethodmodifiers npp_activate_row(NPP *npp, NPPROW *row) "
/**
 */
public";

%csmethodmodifiers npp_deactivate_row(NPP *npp, NPPROW *row) "
/**
 */
public";

%csmethodmodifiers npp_insert_col(NPP *npp, NPPCOL *col, int where) "
/**
 */
public";

%csmethodmodifiers npp_remove_col(NPP *npp, NPPCOL *col) "
/**
 */
public";

%csmethodmodifiers npp_activate_col(NPP *npp, NPPCOL *col) "
/**
 */
public";

%csmethodmodifiers npp_deactivate_col(NPP *npp, NPPCOL *col) "
/**
 */
public";

%csmethodmodifiers npp_add_row(NPP *npp) "
/**
 */
public";

%csmethodmodifiers npp_add_col(NPP *npp) "
/**
 */
public";

%csmethodmodifiers npp_add_aij(NPP *npp, NPPROW *row, NPPCOL *col, double val) "
/**
 */
public";

%csmethodmodifiers npp_row_nnz(NPP *npp, NPPROW *row) "
/**
 */
public";

%csmethodmodifiers npp_col_nnz(NPP *npp, NPPCOL *col) "
/**
 */
public";

%csmethodmodifiers npp_push_tse(NPP *npp, int(*func)(NPP *npp, void *info), int size) "
/**
 */
public";

%csmethodmodifiers npp_erase_row(NPP *npp, NPPROW *row) "
/**
 */
public";

%csmethodmodifiers npp_del_row(NPP *npp, NPPROW *row) "
/**
 */
public";

%csmethodmodifiers npp_del_col(NPP *npp, NPPCOL *col) "
/**
 */
public";

%csmethodmodifiers npp_del_aij(NPP *npp, NPPAIJ *aij) "
/**
 */
public";

%csmethodmodifiers npp_load_prob(NPP *npp, glp_prob *orig, int names, int sol, int scaling) "
/**
 */
public";

%csmethodmodifiers npp_build_prob(NPP *npp, glp_prob *prob) "
/**
 */
public";

%csmethodmodifiers npp_postprocess(NPP *npp, glp_prob *prob) "
/**
 */
public";

%csmethodmodifiers npp_unload_sol(NPP *npp, glp_prob *orig) "
/**
 */
public";

%csmethodmodifiers npp_delete_wksp(NPP *npp) "
/**
 */
public";

%csmethodmodifiers crc32_combine_(uLong crc1, uLong crc2, z_off64_t len2) "
/**
 */
public";

%csmethodmodifiers get_crc_table() "
/**
 */
public";

%csmethodmodifiers gf2_matrix_times(unsigned long *mat, unsigned long vec) "
/**
 */
public";

%csmethodmodifiers gf2_matrix_square(unsigned long *square, unsigned long *mat) "
/**
 */
public";

%csmethodmodifiers crc32_combine(uLong crc1, uLong crc2, z_off_t len2) "
/**
 */
public";

%csmethodmodifiers crc32_combine64(uLong crc1, uLong crc2, z_off64_t len2) "
/**
 */
public";

%csmethodmodifiers rcv_free_row(NPP *npp, void *info) "
/**
 */
public";

%csmethodmodifiers npp_free_row(NPP *npp, NPPROW *p) "
/**
 */
public";

%csmethodmodifiers rcv_geq_row(NPP *npp, void *info) "
/**
 */
public";

%csmethodmodifiers npp_geq_row(NPP *npp, NPPROW *p) "
/**
 */
public";

%csmethodmodifiers rcv_leq_row(NPP *npp, void *info) "
/**
 * npp_leq_row - process row of 'not greater than' type .
 * <p>SYNOPSIS</p>
 * <p>#include \"glpnpp.h\" void npp_leq_row(NPP *npp, NPPROW *p);</p>
 * <p>DESCRIPTION</p>
 * <p>The routine npp_leq_row processes row p, which is 'not greater than' inequality constraint:</p>
 * <p>(L[p] &lt;=) sum a[p,j] x[j] &lt;= U[p], (1) j</p>
 * <p>where L[p] &lt; U[p], and lower bound may not exist (L[p] = +oo).</p>
 * <p>PROBLEM TRANSFORMATION</p>
 * <p>Constraint (1) can be replaced by equality constraint:</p>
 * <p>sum a[p,j] x[j] + s = L[p], (2) j</p>
 * <p>where</p>
 * <p>0 &lt;= s (&lt;= U[p] - L[p]) (3)</p>
 * <p>is a non-negative slack variable.</p>
 * <p>Since in the primal system there appears column s having the only non-zero coefficient in row p, in the dual system there appears a new row:</p>
 * <p>(+1) pi[p] + lambda = 0, (4)</p>
 * <p>where (+1) is coefficient of column s in row p, pi[p] is multiplier of row p, lambda is multiplier of column q, 0 is coefficient of column s in the objective row.</p>
 * <p>RECOVERING BASIC SOLUTION</p>
 * <p>Status of row p in solution to the original problem is determined by its status and status of column q in solution to the transformed problem as follows:</p>
 * <p>+-----------------------------------+---------------+ | Transformed problem | Original problem | +--------------+-----------------+---------------+ | Status of row p | Status of column s | Status of row p | +--------------+-----------------+---------------+ | GLP_BS | GLP_BS | N/A | | GLP_BS | GLP_NL | GLP_BS | | GLP_BS | GLP_NU | GLP_BS | | GLP_NS | GLP_BS | GLP_BS | | GLP_NS | GLP_NL | GLP_NU | | GLP_NS | GLP_NU | GLP_NL | +--------------+-----------------+---------------+</p>
 * <p>Value of row multiplier pi[p] in solution to the original problem is the same as in solution to the transformed problem.</p>
 * <p>
In solution to the transformed problem row p and column q cannot be basic at the same time; otherwise the basis matrix would have two linear dependent columns: unity column of auxiliary variable of row p and unity column of variable s.Though in the transformed problem row p is equality constraint, it may be basic due to primal degeneracy.
</p>
 * <p>RECOVERING INTERIOR-POINT SOLUTION</p>
 * <p>Value of row multiplier pi[p] in solution to the original problem is the same as in solution to the transformed problem.</p>
 * <p>RECOVERING MIP SOLUTION</p>
 * <p>None needed. </p>
 */
public";

%csmethodmodifiers npp_leq_row(NPP *npp, NPPROW *p) "
/**
 */
public";

%csmethodmodifiers rcv_free_col(NPP *npp, void *info) "
/**
 */
public";

%csmethodmodifiers npp_free_col(NPP *npp, NPPCOL *q) "
/**
 */
public";

%csmethodmodifiers rcv_lbnd_col(NPP *npp, void *info) "
/**
 */
public";

%csmethodmodifiers npp_lbnd_col(NPP *npp, NPPCOL *q) "
/**
 */
public";

%csmethodmodifiers rcv_ubnd_col(NPP *npp, void *info) "
/**
 * npp_ubnd_col - process column with upper bound .
 * <p>SYNOPSIS</p>
 * <p>#include \"glpnpp.h\" void npp_ubnd_col(NPP *npp, NPPCOL *q);</p>
 * <p>DESCRIPTION</p>
 * <p>The routine npp_ubnd_col processes column q, which has upper bound:</p>
 * <p>(l[q] &lt;=) x[q] &lt;= u[q], (1)</p>
 * <p>where l[q] &lt; u[q], and lower bound may not exist (l[q] = -oo).</p>
 * <p>PROBLEM TRANSFORMATION</p>
 * <p>Column q can be replaced as follows:</p>
 * <p>x[q] = u[q] - s, (2)</p>
 * <p>where</p>
 * <p>0 &lt;= s (&lt;= u[q] - l[q]) (3)</p>
 * <p>is a non-negative variable.</p>
 * <p>Substituting x[q] from (2) into the objective row, we have:</p>
 * <p>z = sum c[j] x[j] + c0 = j</p>
 * <p>= sum c[j] x[j] + c[q] x[q] + c0 = j!=q</p>
 * <p>= sum c[j] x[j] + c[q] (u[q] - s) + c0 = j!=q</p>
 * <p>= sum c[j] x[j] - c[q] s + c~0,</p>
 * <p>where</p>
 * <p>c~0 = c0 + c[q] u[q] (4)</p>
 * <p>is the constant term of the objective in the transformed problem. Similarly, substituting x[q] into constraint row i, we have:</p>
 * <p>L[i] &lt;= sum a[i,j] x[j] &lt;= U[i] ==> j</p>
 * <p>L[i] &lt;= sum a[i,j] x[j] + a[i,q] x[q] &lt;= U[i] ==> j!=q</p>
 * <p>L[i] &lt;= sum a[i,j] x[j] + a[i,q] (u[q] - s) &lt;= U[i] ==> j!=q</p>
 * <p>L~[i] &lt;= sum a[i,j] x[j] - a[i,q] s &lt;= U~[i], j!=q</p>
 * <p>where</p>
 * <p>L~[i] = L[i] - a[i,q] u[q], U~[i] = U[i] - a[i,q] u[q] (5)</p>
 * <p>are lower and upper bounds of row i in the transformed problem, resp.</p>
 * <p>Note that in the transformed problem coefficients c[q] and a[i,q] change their sign. Thus, the row of the dual system corresponding to column q:</p>
 * <p>sum a[i,q] pi[i] + lambda[q] = c[q] (6) i</p>
 * <p>in the transformed problem becomes the following:</p>
 * <p>sum (-a[i,q]) pi[i] + lambda[s] = -c[q]. (7) i</p>
 * <p>Therefore:</p>
 * <p>lambda[q] = - lambda[s], (8)</p>
 * <p>where lambda[q] is multiplier for column q, lambda[s] is multiplier for column s.</p>
 * <p>RECOVERING BASIC SOLUTION</p>
 * <p>With respect to (8) status of column q in solution to the original problem is determined by status of column s in solution to the transformed problem as follows:</p>
 * <p>+--------------------+-----------------+ | Status of column s | Status of column q | | (transformed problem) | (original problem) | +--------------------+-----------------+ | GLP_BS | GLP_BS | | GLP_NL | GLP_NU | | GLP_NU | GLP_NL | +--------------------+-----------------+</p>
 * <p>Value of column q is computed with formula (2).</p>
 * <p>RECOVERING INTERIOR-POINT SOLUTION</p>
 * <p>Value of column q is computed with formula (2).</p>
 * <p>RECOVERING MIP SOLUTION</p>
 * <p>Value of column q is computed with formula (2). </p>
 */
public";

%csmethodmodifiers npp_ubnd_col(NPP *npp, NPPCOL *q) "
/**
 */
public";

%csmethodmodifiers rcv_dbnd_col(NPP *npp, void *info) "
/**
 */
public";

%csmethodmodifiers npp_dbnd_col(NPP *npp, NPPCOL *q) "
/**
 */
public";

%csmethodmodifiers rcv_fixed_col(NPP *npp, void *info) "
/**
 */
public";

%csmethodmodifiers npp_fixed_col(NPP *npp, NPPCOL *q) "
/**
 */
public";

%csmethodmodifiers rcv_make_equality(NPP *npp, void *info) "
/**
 */
public";

%csmethodmodifiers npp_make_equality(NPP *npp, NPPROW *p) "
/**
 */
public";

%csmethodmodifiers rcv_make_fixed(NPP *npp, void *info) "
/**
 */
public";

%csmethodmodifiers npp_make_fixed(NPP *npp, NPPCOL *q) "
/**
 */
public";

%csmethodmodifiers glp_set_col_kind(glp_prob *mip, int j, int kind) "
/**
 * glp_set_col_kind - set (change) column kind .
 * <p>SYNOPSIS</p>
 * <p>void glp_set_col_kind(glp_prob *mip, int j, int kind);</p>
 * <p>DESCRIPTION</p>
 * <p>The routine glp_set_col_kind sets (changes) the kind of j-th column (structural variable) as specified by the parameter kind:</p>
 * <p>GLP_CV - continuous variable; GLP_IV - integer variable; GLP_BV - binary variable. </p>
 */
public";

%csmethodmodifiers glp_get_col_kind(glp_prob *mip, int j) "
/**
 * glp_get_col_kind - retrieve column kind .
 * <p>SYNOPSIS</p>
 * <p>int glp_get_col_kind(glp_prob *mip, int j);</p>
 * <p>RETURNS</p>
 * <p>The routine glp_get_col_kind returns the kind of j-th column, i.e. the kind of corresponding structural variable, as follows:</p>
 * <p>GLP_CV - continuous variable; GLP_IV - integer variable; GLP_BV - binary variable </p>
 */
public";

%csmethodmodifiers glp_get_num_int(glp_prob *mip) "
/**
 * glp_get_num_int - retrieve number of integer columns .
 * <p>SYNOPSIS</p>
 * <p>int glp_get_num_int(glp_prob *mip);</p>
 * <p>RETURNS</p>
 * <p>The routine glp_get_num_int returns the current number of columns, which are marked as integer. </p>
 */
public";

%csmethodmodifiers glp_get_num_bin(glp_prob *mip) "
/**
 * glp_get_num_bin - retrieve number of binary columns .
 * <p>SYNOPSIS</p>
 * <p>int glp_get_num_bin(glp_prob *mip);</p>
 * <p>RETURNS</p>
 * <p>The routine glp_get_num_bin returns the current number of columns, which are marked as binary. </p>
 */
public";

%csmethodmodifiers solve_mip(glp_prob *P, const glp_iocp *parm, glp_prob *P0, NPP *npp) "
/**
 * glp_intopt - solve MIP problem with the branch-and-bound method .
 * <p>SYNOPSIS</p>
 * <p>int glp_intopt(glp_prob *P, const glp_iocp *parm);</p>
 * <p>DESCRIPTION</p>
 * <p>The routine glp_intopt is a driver to the MIP solver based on the branch-and-bound method.</p>
 * <p>On entry the problem object should contain optimal solution to LP relaxation (which can be obtained with the routine glp_simplex).</p>
 * <p>The MIP solver has a set of control parameters. Values of the control parameters can be passed in a structure glp_iocp, which the parameter parm points to.</p>
 * <p>The parameter parm can be specified as NULL, in which case the MIP solver uses default settings.</p>
 * <p>RETURNS</p>
 * <p>0 The MIP problem instance has been successfully solved. This code does not necessarily mean that the solver has found optimal solution. It only means that the solution process was successful.</p>
 * <p>GLP_EBOUND Unable to start the search, because some double-bounded variables have incorrect bounds or some integer variables have non-integer (fractional) bounds.</p>
 * <p>GLP_EROOT Unable to start the search, because optimal basis for initial LP relaxation is not provided.</p>
 * <p>GLP_EFAIL The search was prematurely terminated due to the solver failure.</p>
 * <p>GLP_EMIPGAP The search was prematurely terminated, because the relative mip gap tolerance has been reached.</p>
 * <p>GLP_ETMLIM The search was prematurely terminated, because the time limit has been exceeded.</p>
 * <p>GLP_ENOPFS The MIP problem instance has no primal feasible solution (only if the MIP presolver is used).</p>
 * <p>GLP_ENODFS LP relaxation of the MIP problem instance has no dual feasible solution (only if the MIP presolver is used).</p>
 * <p>GLP_ESTOP The search was prematurely terminated by application. </p>
 */
public";

%csmethodmodifiers preprocess_and_solve_mip(glp_prob *P, const glp_iocp *parm) "
/**
 */
public";

%csmethodmodifiers _glp_intopt1(glp_prob *P, const glp_iocp *parm) "
/**
 */
public";

%csmethodmodifiers glp_intopt(glp_prob *P, const glp_iocp *parm) "
/**
 */
public";

%csmethodmodifiers glp_init_iocp(glp_iocp *parm) "
/**
 * glp_init_iocp - initialize integer optimizer control parameters .
 * <p>SYNOPSIS</p>
 * <p>void glp_init_iocp(glp_iocp *parm);</p>
 * <p>DESCRIPTION</p>
 * <p>The routine glp_init_iocp initializes control parameters, which are used by the integer optimizer, with default values.</p>
 * <p>Default values of the control parameters are stored in a glp_iocp structure, which the parameter parm points to. </p>
 */
public";

%csmethodmodifiers glp_mip_status(glp_prob *mip) "
/**
 * glp_mip_status - retrieve status of MIP solution .
 * <p>SYNOPSIS</p>
 * <p>int glp_mip_status(glp_prob *mip);</p>
 * <p>RETURNS</p>
 * <p>The routine lpx_mip_status reports the status of MIP solution found by the branch-and-bound solver as follows:</p>
 * <p>GLP_UNDEF - MIP solution is undefined; GLP_OPT - MIP solution is integer optimal; GLP_FEAS - MIP solution is integer feasible but its optimality (or non-optimality) has not been proven, perhaps due to premature termination of the search; GLP_NOFEAS - problem has no integer feasible solution (proven by the solver). </p>
 */
public";

%csmethodmodifiers glp_mip_obj_val(glp_prob *mip) "
/**
 * glp_mip_obj_val - retrieve objective value (MIP solution) .
 * <p>SYNOPSIS</p>
 * <p>double glp_mip_obj_val(glp_prob *mip);</p>
 * <p>RETURNS</p>
 * <p>The routine glp_mip_obj_val returns value of the objective function for MIP solution. </p>
 */
public";

%csmethodmodifiers glp_mip_row_val(glp_prob *mip, int i) "
/**
 * glp_mip_row_val - retrieve row value (MIP solution) .
 * <p>SYNOPSIS</p>
 * <p>double glp_mip_row_val(glp_prob *mip, int i);</p>
 * <p>RETURNS</p>
 * <p>The routine glp_mip_row_val returns value of the auxiliary variable associated with i-th row. </p>
 */
public";

%csmethodmodifiers glp_mip_col_val(glp_prob *mip, int j) "
/**
 * glp_mip_col_val - retrieve column value (MIP solution) .
 * <p>SYNOPSIS</p>
 * <p>double glp_mip_col_val(glp_prob *mip, int j);</p>
 * <p>RETURNS</p>
 * <p>The routine glp_mip_col_val returns value of the structural variable associated with j-th column. </p>
 */
public";

%csmethodmodifiers glp_open(const char *name, const char *mode) "
/**
 * glp_open - open stream .
 * <p>SYNOPSIS</p>
 * <p>glp_file *glp_open(const char *name, const char *mode);</p>
 * <p>DESCRIPTION</p>
 * <p>The routine glp_open opens a file whose name is a string pointed to by name and associates a stream with it.</p>
 * <p>The following special filenames are recognized by the routine (this feature is platform independent):</p>
 * <p>\"/dev/null\" empty (null) file; \"/dev/stdin\" standard input stream; \"/dev/stdout\" standard output stream; \"/dev/stderr\" standard error stream.</p>
 * <p>If the specified filename is ended with \".gz\", it is assumed that the file is in gzipped format. In this case the file is compressed or decompressed by the I/O routines \"on the fly\".</p>
 * <p>The parameter mode points to a string, which indicates the open mode and should be one of the following:</p>
 * <p>\"r\" open text file for reading; \"w\" truncate to zero length or create text file for writing; \"a\" append, open or create text file for writing at end-of-file; \"rb\" open binary file for reading; \"wb\" truncate to zero length or create binary file for writing; \"ab\" append, open or create binary file for writing at end-of-file.</p>
 * <p>RETURNS</p>
 * <p>The routine glp_open returns a pointer to the object controlling the stream. If the operation fails, the routine returns NULL. </p>
 */
public";

%csmethodmodifiers glp_eof(glp_file *f) "
/**
 * glp_eof - test end-of-file indicator .
 * <p>SYNOPSIS</p>
 * <p>int glp_eof(glp_file *f);</p>
 * <p>DESCRIPTION</p>
 * <p>The routine glp_eof tests the end-of-file indicator for the stream pointed to by f.</p>
 * <p>RETURNS</p>
 * <p>The routine glp_eof returns non-zero if and only if the end-of-file indicator is set for the specified stream. </p>
 */
public";

%csmethodmodifiers glp_ioerr(glp_file *f) "
/**
 * glp_ioerr - test I/O error indicator .
 * <p>SYNOPSIS</p>
 * <p>int glp_ioerr(glp_file *f);</p>
 * <p>DESCRIPTION</p>
 * <p>The routine glp_ioerr tests the I/O error indicator for the stream pointed to by f.</p>
 * <p>RETURNS</p>
 * <p>The routine glp_ioerr returns non-zero if and only if the I/O error indicator is set for the specified stream. </p>
 */
public";

%csmethodmodifiers glp_read(glp_file *f, void *buf, int nnn) "
/**
 * glp_read - read data from stream .
 * <p>SYNOPSIS</p>
 * <p>int glp_read(glp_file *f, void *buf, int nnn);</p>
 * <p>DESCRIPTION</p>
 * <p>The routine glp_read reads, into the buffer pointed to by buf, up to nnn bytes, from the stream pointed to by f.</p>
 * <p>RETURNS</p>
 * <p>The routine glp_read returns the number of bytes successfully read (which may be less than nnn). If an end-of-file is encountered, the end-of-file indicator for the stream is set and glp_read returns zero. If a read error occurs, the error indicator for the stream is set and glp_read returns a negative value. </p>
 */
public";

%csmethodmodifiers glp_getc(glp_file *f) "
/**
 * glp_getc - read character from stream .
 * <p>SYNOPSIS</p>
 * <p>int glp_getc(glp_file *f);</p>
 * <p>DESCRIPTION</p>
 * <p>The routine glp_getc obtains a next character as an unsigned char converted to an int from the input stream pointed to by f.</p>
 * <p>RETURNS</p>
 * <p>The routine glp_getc returns the next character obtained. However, if an end-of-file is encountered or a read error occurs, the routine returns EOF. (An end-of-file and a read error can be distinguished by use of the routines glp_eof and glp_ioerr.) </p>
 */
public";

%csmethodmodifiers do_flush(glp_file *f) "
/**
 */
public";

%csmethodmodifiers glp_write(glp_file *f, const void *buf, int nnn) "
/**
 * glp_write - write data to stream .
 * <p>SYNOPSIS</p>
 * <p>int glp_write(glp_file *f, const void *buf, int nnn);</p>
 * <p>DESCRIPTION</p>
 * <p>The routine glp_write writes, from the buffer pointed to by buf, up to nnn bytes, to the stream pointed to by f.</p>
 * <p>RETURNS</p>
 * <p>The routine glp_write returns the number of bytes successfully written (which is equal to nnn). If a write error occurs, the error indicator for the stream is set and glp_write returns a negative value. </p>
 */
public";

%csmethodmodifiers glp_format(glp_file *f, const char *fmt,...) "
/**
 * glp_format - write formatted data to stream .
 * <p>SYNOPSIS</p>
 * <p>int glp_format(glp_file *f, const char *fmt, ...);</p>
 * <p>DESCRIPTION</p>
 * <p>The routine glp_format writes formatted data to the stream pointed to by f. The format control string pointed to by fmt specifies how subsequent arguments are converted for output.</p>
 * <p>RETURNS</p>
 * <p>The routine glp_format returns the number of characters written, or a negative value if an output error occurs. </p>
 */
public";

%csmethodmodifiers glp_close(glp_file *f) "
/**
 * glp_close - close stream .
 * <p>SYNOPSIS</p>
 * <p>int glp_close(glp_file *f);</p>
 * <p>DESCRIPTION</p>
 * <p>The routine glp_close closes the stream pointed to by f.</p>
 * <p>RETURNS</p>
 * <p>If the operation was successful, the routine returns zero, otherwise non-zero. </p>
 */
public";

%csmethodmodifiers dma(const char *func, void *ptr, size_t size) "
/**
 */
public";

%csmethodmodifiers glp_alloc(int n, int size) "
/**
 * glp_alloc - allocate memory block .
 * <p>SYNOPSIS</p>
 * <p>void *glp_alloc(int n, int size);</p>
 * <p>DESCRIPTION</p>
 * <p>The routine glp_alloc allocates a memory block of n * size bytes long.</p>
 * <p>Note that being allocated the memory block contains arbitrary data (not binary zeros!).</p>
 * <p>RETURNS</p>
 * <p>The routine glp_alloc returns a pointer to the block allocated. To free this block the routine glp_free (not free!) must be used. </p>
 */
public";

%csmethodmodifiers glp_realloc(void *ptr, int n, int size) "
/**
 */
public";

%csmethodmodifiers glp_free(void *ptr) "
/**
 * glp_free - free (deallocate) memory block .
 * <p>SYNOPSIS</p>
 * <p>void glp_free(void *ptr);</p>
 * <p>DESCRIPTION</p>
 * <p>The routine glp_free frees (deallocates) a memory block pointed to by ptr, which was previuosly allocated by the routine glp_alloc or reallocated by the routine glp_realloc. </p>
 */
public";

%csmethodmodifiers glp_mem_limit(int limit) "
/**
 * glp_mem_limit - set memory usage limit .
 * <p>SYNOPSIS</p>
 * <p>void glp_mem_limit(int limit);</p>
 * <p>DESCRIPTION</p>
 * <p>The routine glp_mem_limit limits the amount of memory available for dynamic allocation (in GLPK routines) to limit megabytes. </p>
 */
public";

%csmethodmodifiers glp_mem_usage(int *count, int *cpeak, size_t *total, size_t *tpeak) "
/**
 * glp_mem_usage - get memory usage information .
 * <p>SYNOPSIS</p>
 * <p>void glp_mem_usage(int *count, int *cpeak, size_t *total, size_t *tpeak);</p>
 * <p>DESCRIPTION</p>
 * <p>The routine glp_mem_usage reports some information about utilization of the memory by GLPK routines. Information is stored to locations specified by corresponding parameters (see below). Any parameter can be specified as NULL, in which case its value is not stored.</p>
 * <p>*count is the number of the memory blocks currently allocated by the routines glp_malloc and glp_calloc (one call to glp_malloc or glp_calloc results in allocating one memory block).</p>
 * <p>*cpeak is the peak value of *count reached since the initialization of the GLPK library environment.</p>
 * <p>*total is the total amount, in bytes, of the memory blocks currently allocated by the routines glp_malloc and glp_calloc.</p>
 * <p>*tpeak is the peak value of *total reached since the initialization of the GLPK library envirionment. </p>
 */
public";

%csmethodmodifiers str2int(const char *str, int *val_) "
/**
 * str2int - convert character string to value of int type .
 * <p>SYNOPSIS</p>
 * <p>#include \"misc.h\" int str2int(const char *str, int *val);</p>
 * <p>DESCRIPTION</p>
 * <p>The routine str2int converts the character string str to a value of integer type and stores the value into location, which the parameter val points to (in the case of error content of this location is not changed).</p>
 * <p>RETURNS</p>
 * <p>The routine returns one of the following error codes:</p>
 * <p>0 - no error; 1 - value out of range; 2 - character string is syntactically incorrect. </p>
 */
public";

%csmethodmodifiers glp_create_index(glp_prob *lp) "
/**
 * glp_create_index - create the name index .
 * <p>SYNOPSIS</p>
 * <p>void glp_create_index(glp_prob *lp);</p>
 * <p>DESCRIPTION</p>
 * <p>The routine glp_create_index creates the name index for the specified problem object. The name index is an auxiliary data structure, which is intended to quickly (i.e. for logarithmic time) find rows and columns by their names.</p>
 * <p>This routine can be called at any time. If the name index already exists, the routine does nothing. </p>
 */
public";

%csmethodmodifiers glp_find_row(glp_prob *lp, const char *name) "
/**
 * glp_find_row - find row by its name .
 * <p>SYNOPSIS</p>
 * <p>int glp_find_row(glp_prob *lp, const char *name);</p>
 * <p>RETURNS</p>
 * <p>The routine glp_find_row returns the ordinal number of a row, which is assigned (by the routine glp_set_row_name) the specified symbolic name. If no such row exists, the routine returns 0. </p>
 */
public";

%csmethodmodifiers glp_find_col(glp_prob *lp, const char *name) "
/**
 * glp_find_col - find column by its name .
 * <p>SYNOPSIS</p>
 * <p>int glp_find_col(glp_prob *lp, const char *name);</p>
 * <p>RETURNS</p>
 * <p>The routine glp_find_col returns the ordinal number of a column, which is assigned (by the routine glp_set_col_name) the specified symbolic name. If no such column exists, the routine returns 0. </p>
 */
public";

%csmethodmodifiers glp_delete_index(glp_prob *lp) "
/**
 * glp_delete_index - delete the name index .
 * <p>SYNOPSIS</p>
 * <p>void glp_delete_index(glp_prob *lp);</p>
 * <p>DESCRIPTION</p>
 * <p>The routine glp_delete_index deletes the name index previously created by the routine glp_create_index and frees the memory allocated to this auxiliary data structure.</p>
 * <p>This routine can be called at any time. If the name index does not exist, the routine does nothing. </p>
 */
public";

%csmethodmodifiers glp_minisat1(glp_prob *P) "
/**
 */
public";

%csmethodmodifiers sva_create_area(int n_max, int size) "
/**
 */
public";

%csmethodmodifiers sva_alloc_vecs(SVA *sva, int nnn) "
/**
 */
public";

%csmethodmodifiers sva_resize_area(SVA *sva, int delta) "
/**
 */
public";

%csmethodmodifiers sva_defrag_area(SVA *sva) "
/**
 */
public";

%csmethodmodifiers sva_more_space(SVA *sva, int m_size) "
/**
 */
public";

%csmethodmodifiers sva_enlarge_cap(SVA *sva, int k, int new_cap, int skip) "
/**
 */
public";

%csmethodmodifiers sva_reserve_cap(SVA *sva, int k, int new_cap) "
/**
 */
public";

%csmethodmodifiers sva_make_static(SVA *sva, int k) "
/**
 */
public";

%csmethodmodifiers sva_check_area(SVA *sva) "
/**
 */
public";

%csmethodmodifiers sva_delete_area(SVA *sva) "
/**
 */
public";

%csmethodmodifiers deflateInit_(z_streamp strm, int level, const char *version, int stream_size) "
/**
 */
public";

%csmethodmodifiers deflateInit2_(z_streamp strm, int level, int method, int windowBits, int memLevel, int strategy, const char *version, int stream_size) "
/**
 */
public";

%csmethodmodifiers deflateSetDictionary(z_streamp strm, const Bytef *dictionary, uInt dictLength) "
/**
 */
public";

%csmethodmodifiers deflateReset(z_streamp strm) "
/**
 */
public";

%csmethodmodifiers deflateSetHeader(z_streamp strm, gz_headerp head) "
/**
 */
public";

%csmethodmodifiers deflatePrime(z_streamp strm, int bits, int value) "
/**
 */
public";

%csmethodmodifiers deflateParams(z_streamp strm, int level, int strategy) "
/**
 */
public";

%csmethodmodifiers deflateTune(z_streamp strm, int good_length, int max_lazy, int nice_length, int max_chain) "
/**
 */
public";

%csmethodmodifiers deflateBound(z_streamp strm, uLong sourceLen) "
/**
 */
public";

%csmethodmodifiers putShortMSB(deflate_state *s, uInt b) "
/**
 */
public";

%csmethodmodifiers flush_pending(z_streamp strm) "
/**
 */
public";

%csmethodmodifiers deflate(z_streamp strm, int flush) "
/**
 */
public";

%csmethodmodifiers deflateEnd(z_streamp strm) "
/**
 */
public";

%csmethodmodifiers deflateCopy(z_streamp dest, z_streamp source) "
/**
 */
public";

%csmethodmodifiers read_buf(z_streamp strm, Bytef *buf, unsigned size) "
/**
 */
public";

%csmethodmodifiers lm_init(deflate_state *s) "
/**
 */
public";

%csmethodmodifiers longest_match(deflate_state *s, IPos cur_match) "
/**
 */
public";

%csmethodmodifiers fill_window(deflate_state *s) "
/**
 */
public";

%csmethodmodifiers deflate_stored(deflate_state *s, int flush) "
/**
 */
public";

%csmethodmodifiers deflate_fast(deflate_state *s, int flush) "
/**
 */
public";

%csmethodmodifiers deflate_slow(deflate_state *s, int flush) "
/**
 */
public";

%csmethodmodifiers deflate_rle(deflate_state *s, int flush) "
/**
 */
public";

%csmethodmodifiers deflate_huff(deflate_state *s, int flush) "
/**
 */
public";

%csmethodmodifiers adler32_combine_(uLong adler1, uLong adler2, z_off64_t len2) "
/**
 */
public";

%csmethodmodifiers adler32(uLong adler, const Bytef *buf, uInt len) "
/**
 */
public";

%csmethodmodifiers adler32_combine(uLong adler1, uLong adler2, z_off_t len2) "
/**
 */
public";

%csmethodmodifiers adler32_combine64(uLong adler1, uLong adler2, z_off64_t len2) "
/**
 */
public";

%csmethodmodifiers tr_static_init() "
/**
 */
public";

%csmethodmodifiers _tr_init(deflate_state *s) "
/**
 */
public";

%csmethodmodifiers init_block(deflate_state *s) "
/**
 */
public";

%csmethodmodifiers pqdownheap(deflate_state *s, ct_data *tree, int k) "
/**
 */
public";

%csmethodmodifiers gen_bitlen(deflate_state *s, tree_desc *desc) "
/**
 */
public";

%csmethodmodifiers gen_codes(ct_data *tree, int max_code, ushf *bl_count) "
/**
 */
public";

%csmethodmodifiers build_tree(deflate_state *s, tree_desc *desc) "
/**
 */
public";

%csmethodmodifiers scan_tree(deflate_state *s, ct_data *tree, int max_code) "
/**
 */
public";

%csmethodmodifiers send_tree(deflate_state *s, ct_data *tree, int max_code) "
/**
 */
public";

%csmethodmodifiers build_bl_tree(deflate_state *s) "
/**
 */
public";

%csmethodmodifiers send_all_trees(deflate_state *s, int lcodes, int dcodes, int blcodes) "
/**
 */
public";

%csmethodmodifiers _tr_stored_block(deflate_state *s, charf *buf, ulg stored_len, int last) "
/**
 */
public";

%csmethodmodifiers _tr_align(deflate_state *s) "
/**
 */
public";

%csmethodmodifiers _tr_flush_block(deflate_state *s, charf *buf, ulg stored_len, int last) "
/**
 */
public";

%csmethodmodifiers _tr_tally(deflate_state *s, unsigned dist, unsigned lc) "
/**
 */
public";

%csmethodmodifiers compress_block(deflate_state *s, ct_data *ltree, ct_data *dtree) "
/**
 */
public";

%csmethodmodifiers detect_data_type(deflate_state *s) "
/**
 */
public";

%csmethodmodifiers bi_reverse(unsigned code, int len) "
/**
 */
public";

%csmethodmodifiers bi_flush(deflate_state *s) "
/**
 */
public";

%csmethodmodifiers bi_windup(deflate_state *s) "
/**
 */
public";

%csmethodmodifiers copy_block(deflate_state *s, charf *buf, unsigned len, int header) "
/**
 */
public";

%csmethodmodifiers flip_cycle(RNG *rand) "
/**
 */
public";

%csmethodmodifiers rng_create_rand(void) "
/**
 * rng_create_rand - create pseudo-random number generator .
 * <p>SYNOPSIS</p>
 * <p>#include \"rng.h\" RNG *rng_create_rand(void);</p>
 * <p>DESCRIPTION</p>
 * <p>The routine rng_create_rand creates and initializes a pseudo-random number generator.</p>
 * <p>RETURNS</p>
 * <p>The routine returns a pointer to the generator created. </p>
 */
public";

%csmethodmodifiers rng_init_rand(RNG *rand, int seed) "
/**
 * rng_init_rand - initialize pseudo-random number generator .
 * <p>SYNOPSIS</p>
 * <p>#include \"rng.h\" void rng_init_rand(RNG *rand, int seed);</p>
 * <p>DESCRIPTION</p>
 * <p>The routine rng_init_rand initializes the pseudo-random number generator. The parameter seed may be any integer number. Note that on creating the generator this routine is called with the parameter seed equal to 1. </p>
 */
public";

%csmethodmodifiers rng_next_rand(RNG *rand) "
/**
 * rng_next_rand - obtain pseudo-random integer in the range [0, 2^31-1] .
 * <p>SYNOPSIS</p>
 * <p>#include \"rng.h\" int rng_next_rand(RNG *rand);</p>
 * <p>RETURNS</p>
 * <p>The routine rng_next_rand returns a next pseudo-random integer which is uniformly distributed between 0 and 2^31-1, inclusive. The period length of the generated numbers is 2^85 - 2^30. The low order bits of the generated numbers are just as random as the high-order bits. </p>
 */
public";

%csmethodmodifiers rng_unif_rand(RNG *rand, int m) "
/**
 */
public";

%csmethodmodifiers rng_delete_rand(RNG *rand) "
/**
 * rng_delete_rand - delete pseudo-random number generator .
 * <p>SYNOPSIS</p>
 * <p>#include \"rng.h\" void rng_delete_rand(RNG *rand);</p>
 * <p>DESCRIPTION</p>
 * <p>The routine rng_delete_rand frees all the memory allocated to the specified pseudo-random number generator. </p>
 */
public";

%csmethodmodifiers tls_set_ptr(void *ptr) "
/**
 * tls_set_ptr - store global pointer in TLS .
 * <p>SYNOPSIS</p>
 * <p>#include \"env.h\" void tls_set_ptr(void *ptr);</p>
 * <p>DESCRIPTION</p>
 * <p>The routine tls_set_ptr stores a pointer specified by the parameter ptr in the Thread Local Storage (TLS). </p>
 */
public";

%csmethodmodifiers tls_get_ptr(void) "
/**
 * tls_get_ptr - retrieve global pointer from TLS .
 * <p>SYNOPSIS</p>
 * <p>#include \"env.h\" void *tls_get_ptr(void);</p>
 * <p>RETURNS</p>
 * <p>The routine tls_get_ptr returns a pointer previously stored by the routine tls_set_ptr. If the latter has not been called yet, NULL is returned. </p>
 */
public";

%csmethodmodifiers npp_clean_prob(NPP *npp) "
/**
 * npp_clean_prob - perform initial LP/MIP processing .
 * <p>SYNOPSIS</p>
 * <p>#include \"glpnpp.h\" void npp_clean_prob(NPP *npp);</p>
 * <p>DESCRIPTION</p>
 * <p>The routine npp_clean_prob performs initial LP/MIP processing that currently includes:</p>
 * <p>1) removing free rows;</p>
 * <p>2) replacing double-sided constraint rows with almost identical bounds, by equality constraint rows;</p>
 * <p>3) removing fixed columns;</p>
 * <p>4) replacing double-bounded columns with almost identical bounds by fixed columns and removing those columns;</p>
 * <p>5) initial processing constraint coefficients (not implemented);</p>
 * <p>6) initial processing objective coefficients (not implemented). </p>
 */
public";

%csmethodmodifiers npp_process_row(NPP *npp, NPPROW *row, int hard) "
/**
 * npp_process_row - perform basic row processing .
 * <p>SYNOPSIS</p>
 * <p>#include \"glpnpp.h\" int npp_process_row(NPP *npp, NPPROW *row, int hard);</p>
 * <p>DESCRIPTION</p>
 * <p>The routine npp_process_row performs basic row processing that currently includes:</p>
 * <p>1) removing empty row;</p>
 * <p>2) removing equality constraint row singleton and corresponding column;</p>
 * <p>3) removing inequality constraint row singleton and corresponding column if it was fixed;</p>
 * <p>4) performing general row analysis;</p>
 * <p>5) removing redundant row bounds;</p>
 * <p>6) removing forcing row and corresponding columns;</p>
 * <p>7) removing row which becomes free due to redundant bounds;</p>
 * <p>8) computing implied bounds for all columns in the row and using them to strengthen current column bounds (MIP only, optional, performed if the flag hard is on).</p>
 * <p>Additionally the routine may activate affected rows and/or columns for further processing.</p>
 * <p>RETURNS</p>
 * <p>0 success;</p>
 * <p>GLP_ENOPFS primal/integer infeasibility detected;</p>
 * <p>GLP_ENODFS dual infeasibility detected. </p>
 */
public";

%csmethodmodifiers npp_improve_bounds(NPP *npp, NPPROW *row, int flag) "
/**
 * npp_improve_bounds - improve current column bounds .
 * <p>SYNOPSIS</p>
 * <p>#include \"glpnpp.h\" int npp_improve_bounds(NPP *npp, NPPROW *row, int flag);</p>
 * <p>DESCRIPTION</p>
 * <p>The routine npp_improve_bounds analyzes specified row (inequality or equality constraint) to determine implied column bounds and then uses these bounds to improve (strengthen) current column bounds.</p>
 * <p>If the flag is on and current column bounds changed significantly or the column was fixed, the routine activate rows affected by the column for further processing. (This feature is intended to be used in the main loop of the routine npp_process_row.)</p>
 * <p>NOTE: This operation can be used for MIP problem only.</p>
 * <p>RETURNS</p>
 * <p>The routine npp_improve_bounds returns the number of significantly changed bounds plus the number of column having been fixed due to bound improvements. However, if the routine detects primal/integer infeasibility, it returns a negative value. </p>
 */
public";

%csmethodmodifiers npp_process_col(NPP *npp, NPPCOL *col) "
/**
 * npp_process_col - perform basic column processing .
 * <p>SYNOPSIS</p>
 * <p>#include \"glpnpp.h\" int npp_process_col(NPP *npp, NPPCOL *col);</p>
 * <p>DESCRIPTION</p>
 * <p>The routine npp_process_col performs basic column processing that currently includes:</p>
 * <p>1) fixing and removing empty column;</p>
 * <p>2) removing column singleton, which is implied slack variable, and corresponding row if it becomes free;</p>
 * <p>3) removing bounds of column, which is implied free variable, and replacing corresponding row by equality constraint.</p>
 * <p>Additionally the routine may activate affected rows and/or columns for further processing.</p>
 * <p>RETURNS</p>
 * <p>0 success;</p>
 * <p>GLP_ENOPFS primal/integer infeasibility detected;</p>
 * <p>GLP_ENODFS dual infeasibility detected. </p>
 */
public";

%csmethodmodifiers npp_process_prob(NPP *npp, int hard) "
/**
 * npp_process_prob - perform basic LP/MIP processing .
 * <p>SYNOPSIS</p>
 * <p>#include \"glpnpp.h\" int npp_process_prob(NPP *npp, int hard);</p>
 * <p>DESCRIPTION</p>
 * <p>The routine npp_process_prob performs basic LP/MIP processing that currently includes:</p>
 * <p>1) initial LP/MIP processing (see the routine npp_clean_prob),</p>
 * <p>2) basic row processing (see the routine npp_process_row), and</p>
 * <p>3) basic column processing (see the routine npp_process_col).</p>
 * <p>If the flag hard is on, the routine attempts to improve current column bounds multiple times within the main processing loop, in which case this feature may take a time. Otherwise, if the flag hard is off, improving column bounds is performed only once at the end of the main loop. (Note that this feature is used for MIP only.)</p>
 * <p>The routine uses two sets: the set of active rows and the set of active columns. Rows/columns are marked by a flag (the field temp in NPPROW/NPPCOL). If the flag is non-zero, the row/column is active, in which case it is placed in the beginning of the row/column list; otherwise, if the flag is zero, the row/column is inactive, in which case it is placed in the end of the row/column list. If a row/column being currently processed may affect other rows/columns, the latters are activated for further processing.</p>
 * <p>RETURNS</p>
 * <p>0 success;</p>
 * <p>GLP_ENOPFS primal/integer infeasibility detected;</p>
 * <p>GLP_ENODFS dual infeasibility detected. </p>
 */
public";

%csmethodmodifiers npp_simplex(NPP *npp, const glp_smcp *parm) "
/**
 */
public";

%csmethodmodifiers npp_integer(NPP *npp, const glp_iocp *parm) "
/**
 */
public";

%csmethodmodifiers lux_create(int n) "
/**
 */
public";

%csmethodmodifiers initialize(LUX *lux, int(*col)(void *info, int j, int ind[], mpq_t val[]), void *info, LUXWKA *wka) "
/**
 */
public";

%csmethodmodifiers find_pivot(LUX *lux, LUXWKA *wka) "
/**
 */
public";

%csmethodmodifiers eliminate(LUX *lux, LUXWKA *wka, LUXELM *piv, int flag[], mpq_t work[]) "
/**
 */
public";

%csmethodmodifiers lux_decomp(LUX *lux, int(*col)(void *info, int j, int ind[], mpq_t val[]), void *info) "
/**
 */
public";

%csmethodmodifiers lux_f_solve(LUX *lux, int tr, mpq_t x[]) "
/**
 */
public";

%csmethodmodifiers lux_v_solve(LUX *lux, int tr, mpq_t x[]) "
/**
 */
public";

%csmethodmodifiers lux_solve(LUX *lux, int tr, mpq_t x[]) "
/**
 */
public";

%csmethodmodifiers lux_delete(LUX *lux) "
/**
 */
public";

%csmethodmodifiers glp_mpl_alloc_wksp(void) "
/**
 */
public";

%csmethodmodifiers _glp_mpl_init_rand(glp_tran *tran, int seed) "
/**
 */
public";

%csmethodmodifiers glp_mpl_read_model(glp_tran *tran, const char *fname, int skip) "
/**
 */
public";

%csmethodmodifiers glp_mpl_read_data(glp_tran *tran, const char *fname) "
/**
 */
public";

%csmethodmodifiers glp_mpl_generate(glp_tran *tran, const char *fname) "
/**
 */
public";

%csmethodmodifiers glp_mpl_build_prob(glp_tran *tran, glp_prob *prob) "
/**
 */
public";

%csmethodmodifiers glp_mpl_postsolve(glp_tran *tran, glp_prob *prob, int sol) "
/**
 */
public";

%csmethodmodifiers glp_mpl_free_wksp(glp_tran *tran) "
/**
 */
public";

%csmethodmodifiers glp_init_env(void) "
/**
 * glp_init_env - initialize GLPK environment .
 * <p>SYNOPSIS</p>
 * <p>int glp_init_env(void);</p>
 * <p>DESCRIPTION</p>
 * <p>The routine glp_init_env initializes the GLPK environment. Normally the application program does not need to call this routine, because it is called automatically on the first call to any API routine.</p>
 * <p>RETURNS</p>
 * <p>The routine glp_init_env returns one of the following codes:</p>
 * <p>0 - initialization successful; 1 - environment has been already initialized; 2 - initialization failed (insufficient memory); 3 - initialization failed (unsupported programming model). </p>
 */
public";

%csmethodmodifiers get_env_ptr(void) "
/**
 * get_env_ptr - retrieve pointer to environment block .
 * <p>SYNOPSIS</p>
 * <p>#include \"env.h\" ENV *get_env_ptr(void);</p>
 * <p>DESCRIPTION</p>
 * <p>The routine get_env_ptr retrieves and returns a pointer to the GLPK environment block.</p>
 * <p>If the GLPK environment has not been initialized yet, the routine performs initialization. If initialization fails, the routine prints an error message to stderr and terminates the program.</p>
 * <p>RETURNS</p>
 * <p>The routine returns a pointer to the environment block. </p>
 */
public";

%csmethodmodifiers glp_version(void) "
/**
 * glp_version - determine library version .
 * <p>SYNOPSIS</p>
 * <p>const char *glp_version(void);</p>
 * <p>RETURNS</p>
 * <p>The routine glp_version returns a pointer to a null-terminated character string, which specifies the version of the GLPK library in the form \"X.Y\", where X is the major version number, and Y is the minor version number, for example, \"4.16\". </p>
 */
public";

%csmethodmodifiers glp_free_env(void) "
/**
 * glp_free_env - free GLPK environment .
 * <p>SYNOPSIS</p>
 * <p>int glp_free_env(void);</p>
 * <p>DESCRIPTION</p>
 * <p>The routine glp_free_env frees all resources used by GLPK routines (memory blocks, etc.) which are currently still in use.</p>
 * <p>Normally the application program does not need to call this routine, because GLPK routines always free all unused resources. However, if the application program even has deleted all problem objects, there will be several memory blocks still allocated for the library needs. For some reasons the application program may want GLPK to free this memory, in which case it should call glp_free_env.</p>
 * <p>Note that a call to glp_free_env invalidates all problem objects as if no GLPK routine were called.</p>
 * <p>RETURNS</p>
 * <p>0 - termination successful; 1 - environment is inactive (was not initialized). </p>
 */
public";

%csmethodmodifiers ascnt1(struct relax4_csa *csa, int dm, int *delx, int *nlabel, int *feasbl, int *svitch, int nscan, int curnode, int *prevnode) "
/**
 * RELAX-IV (version of October 1994) .
 * <p>ascnt1 - multi-node price adjustment for positive deficit case</p>
 * <p>PURPOSE</p>
 * <p>This routine implements the relaxation method of Bertsekas and Tseng (see [1], [2]) for linear cost ordinary network flow problems.</p>
 * <p>[1] Bertsekas, D. P., \"A Unified Framework for Primal-Dual Methods\" Mathematical Programming, Vol. 32, 1985, pp. 125-145. [2] Bertsekas, D. P., and Tseng, P., \"Relaxation Methods for
    Minimum Cost\" Operations Research, Vol. 26, 1988, pp. 93-114.</p>
 * <p>The relaxation method is also described in the books:</p>
 * <p>[3] Bertsekas, D. P., \"Linear Network Optimization: Algorithms and
    Codes\" MIT Press, 1991. [4] Bertsekas, D. P. and Tsitsiklis, J. N., \"Parallel and Distributed
    Computation: Numerical Methods\", Prentice-Hall, 1989. [5] Bertsekas, D. P., \"Network Optimization: Continuous and Discrete
    Models\", Athena Scientific, 1998.</p>
 * <p>RELEASE NOTE</p>
 * <p>This version of relaxation code has option for a special crash procedure for the initial price-flow pair. This is recommended for difficult problems where the default initialization results in long running times. crash = 1 corresponds to an auction/shortest path method</p>
 * <p>These initializations are recommended in the absence of any prior information on a favorable initial flow-price vector pair that satisfies complementary slackness.</p>
 * <p>The relaxation portion of the code differs from the code RELAXT-III and other earlier relaxation codes in that it maintains the set of nodes with nonzero deficit in a fifo queue. Like its predecessor RELAXT-III, this code maintains a linked list of balanced (i.e., of zero reduced cost) arcs so to reduce the work in labeling and scanning. Unlike RELAXT-III, it does not use selectively shortest path iterations for initialization.</p>
 * <p>SOURCE</p>
 * <p>The original Fortran code was written by Dimitri P. Bertsekas and Paul Tseng, with a contribution by Jonathan Eckstein in the phase II initialization. The original Fortran routine AUCTION was written by Dimitri P. Bertsekas and is based on the method described in the paper:</p>
 * <p>[6] Bertsekas, D. P., \"An Auction/Sequential Shortest Path Algorithm
    for the Minimum Cost Flow Problem\", LIDS Report P-2146, MIT, Nov. 1992.</p>
 * <p>For inquiries about the original Fortran code, please contact:</p>
 * <p>Dimitri P. Bertsekas Laboratory for information and decision systems Massachusetts Institute of Technology Cambridge, MA 02139 (617) 253-7267, dimitrib@mit.edu</p>
 * <p>This code is the result of translation of the original Fortran code. The translation was made by Andrew Makhorin mao@gnu.org.</p>
 * <p>USER GUIDELINES</p>
 * <p>This routine is in the public domain to be used only for research purposes. It cannot be used as part of a commercial product, or to satisfy in any part commercial delivery requirements to government or industry, without prior agreement with the authors. Users are requested to acknowledge the authorship of the code, and the relaxation method.</p>
 * <p>No modification should be made to this code other than the minimal necessary to make it compatible with specific platforms.</p>
 * <p>INPUT PARAMETERS (see notes 1, 2, 4)</p>
 * <p>n = number of nodes na = number of arcs large = a very large integer to represent infinity (see note 3) repeat = true if initialization is to be skipped (false otherwise) crash = 0 if default initialization is used 1 if auction initialization is used startn[j] = starting node for arc j, j = 1,...,na endn[j] = ending node for arc j, j = 1,...,na fou[i] = first arc out of node i, i = 1,...,n nxtou[j] = next arc out of the starting node of arc j, j = 1,...,na fin[i] = first arc into node i, i = 1,...,n nxtin[j] = next arc into the ending node of arc j, j = 1,...,na</p>
 * <p>UPDATED PARAMETERS (see notes 1, 3, 4)</p>
 * <p>rc[j] = reduced cost of arc j, j = 1,...,na u[j] = capacity of arc j on input and (capacity of arc j) - x[j] on output, j = 1,...,na dfct[i] = demand at node i on input and zero on output, i = 1,...,n</p>
 * <p>OUTPUT PARAMETERS (see notes 1, 3, 4)</p>
 * <p>x[j] = flow on arc j, j = 1,...,na nmultinode = number of multinode relaxation iterations in RELAX4 iter = number of relaxation iterations in RELAX4 num_augm = number of flow augmentation steps in RELAX4 num_ascnt = number of multinode ascent steps in RELAX4 nsp = number of auction/shortest path iterations</p>
 * <p>WORKING PARAMETERS (see notes 1, 4, 5)</p>
 * <p>label[1+n], prdcsr[1+n], save[1+na], tfstou[1+n], tnxtou[1+na], tfstin[1+n], tnxtin[1+na], nxtqueue[1+n], scan[1+n], mark[1+n], extend_arc[1+n], sb_level[1+n], sb_arc[1+n]</p>
 * <p>RETURNS</p>
 * <p>0 = normal return 1,...,8 = problem is found to be infeasible</p>
 * <p>NOTE 1</p>
 * <p>To run in limited memory systems, declare the arrays startn, endn, nxtin, nxtou, fin, fou, label, prdcsr, save, tfstou, tnxtou, tfstin, tnxtin, ddpos, ddneg, nxtqueue as short instead.</p>
 * <p>NOTE 2</p>
 * <p>This routine makes no effort to initialize with a favorable x from amongst those flow vectors that satisfy complementary slackness with the initial reduced cost vector rc. If a favorable x is known, then it can be passed, together with the corresponding arrays u and dfct, to this routine directly. This, however, requires that the capacity tightening portion and the flow initialization portion of this routine (up to line labeled 90) be skipped.</p>
 * <p>NOTE 3</p>
 * <p>All problem data should be less than large in magnitude, and large should be less than, say, 1/4 the largest int of the machine used. This will guard primarily against overflow in uncapacitated problems where the arc capacities are taken finite but very large. Note, however, that as in all codes operating with integers, overflow may occur if some of the problem data takes very large values.</p>
 * <p>NOTE 4</p>
 * <p>[This note being specific to Fortran was removed.-A.M.]</p>
 * <p>NOTE 5</p>
 * <p>ddpos and ddneg are arrays that give the directional derivatives for all positive and negative single-node price changes. These are used only in phase II of the initialization procedure, before the linked list of balanced arcs comes to play. Therefore, to reduce storage, they are equivalence to tfstou and tfstin, which are of the same size (number of nodes) and are used only after the tree comes into use.</p>
 * <p>PURPOSE</p>
 * <p>This subroutine performs the multi-node price adjustment step for the case where the scanned nodes have positive deficit. It first checks if decreasing the price of the scanned nodes increases the dual cost. If yes, then it decreases the price of all scanned nodes. There are two possibilities for price decrease: if switch = true, then the set of scanned nodes corresponds to an elementary direction of maximal rate of ascent, in which case the price of all scanned nodes are decreased until the next breakpoint in the dual cost is encountered. At this point, some arc becomes balanced and more node(s) are added to the labeled set and the subroutine is exited. If switch = false, then the price of all scanned nodes are decreased until the rate of ascent becomes negative (this corresponds to the price adjustment step in which both the line search and the degenerate ascent iteration are implemented).</p>
 * <p>INPUT PARAMETERS</p>
 * <p>dm = total deficit of scanned nodes switch = true if labeling is to continue after price change nscan = number of scanned nodes curnode = most recently scanned node n = number of nodes na = number of arcs large = a very large integer to represent infinity (see note 3) startn[i] = starting node for the i-th arc, i = 1,...,na endn[i] = ending node for the i-th arc, i = 1,...,na fou[i] = first arc leaving i-th node, i = 1,...,n nxtou[i] = next arc leaving the starting node of j-th arc, i = 1,...,na fin[i] = first arc entering i-th node, i = 1,...,n nxtin[i] = next arc entering the ending node of j-th arc, i = 1,...,na</p>
 * <p>UPDATED PARAMETERS</p>
 * <p>delx = a lower estimate of the total flow on balanced arcs in the scanned-nodes cut nlabel = number of labeled nodes feasbl = false if problem is found to be infeasible prevnode = the node before curnode in queue rc[j] = reduced cost of arc j, j = 1,...,na u[j] = residual capacity of arc j, j = 1,...,na x[j] = flow on arc j, j = 1,...,na dfct[i] = deficit at node i, i = 1,...,n label[k] = k-th node labeled, k = 1,...,nlabel prdcsr[i] = predecessor of node i in tree of labeled nodes (0 if i is unlabeled), i = 1,...,n tfstou[i] = first balanced arc out of node i, i = 1,...,n tnxtou[j] = next balanced arc out of the starting node of arc j, j = 1,...,na tfstin[i] = first balanced arc into node i, i = 1,...,n tnxtin[j] = next balanced arc into the ending node of arc j, j = 1,...,na nxtqueue[i] = node following node i in the fifo queue (0 if node is not in the queue), i = 1,...,n scan[i] = true if node i is scanned, i = 1,...,n mark[i] = true if node i is labeled, i = 1,...,n</p>
 * <p>WORKING PARAMETERS</p>
 * <p>save[1+na] </p>
 */
public";

%csmethodmodifiers ascnt2(struct relax4_csa *csa, int dm, int *delx, int *nlabel, int *feasbl, int *svitch, int nscan, int curnode, int *prevnode) "
/**
 * ascnt2 - multi-node price adjustment for negative deficit case .
 * <p>PURPOSE</p>
 * <p>This routine is analogous to ascnt1 but for the case where the scanned nodes have negative deficit. </p>
 */
public";

%csmethodmodifiers auction(struct relax4_csa *csa) "
/**
 * auction - compute good initial flow and prices .
 * <p>PURPOSE</p>
 * <p>This subroutine uses a version of the auction algorithm for min cost network flow to compute a good initial flow and prices for the problem.</p>
 * <p>INPUT PARAMETERS</p>
 * <p>n = number of nodes na = number of arcs large = a very large integer to represent infinity (see note 3) startn[i] = starting node for the i-th arc, i = 1,...,na endn[i] = ending node for the i-th arc, i = 1,...,na fou[i] = first arc leaving i-th node, i = 1,...,n nxtou[i] = next arc leaving the starting node of j-th arc, i = 1,...,na fin[i] = first arc entering i-th node, i = 1,...,n nxtin[i] = next arc entering the ending node of j-th arc, i = 1,...,na</p>
 * <p>UPDATED PARAMETERS</p>
 * <p>rc[j] = reduced cost of arc j, j = 1,...,na u[j] = residual capacity of arc j, j = 1,...,na x[j] = flow on arc j, j = 1,...,na dfct[i] = deficit at node i, i = 1,...,n</p>
 * <p>OUTPUT PARAMETERS</p>
 * <p>nsp = number of auction/shortest path iterations</p>
 * <p>WORKING PARAMETERS</p>
 * <p>p[1+n], prdcsr[1+n], save[1+na], fpushf[1+n], nxtpushf[1+na], fpushb[1+n], nxtpushb[1+na], nxtqueue[1+n], extend_arc[1+n], sb_level[1+n], sb_arc[1+n], path_id[1+n]</p>
 * <p>RETURNS</p>
 * <p>0 = normal return 1 = problem is found to be infeasible </p>
 */
public";

%csmethodmodifiers relax4(struct relax4_csa *csa) "
/**
 */
public";

%csmethodmodifiers relax4_inidat(struct relax4_csa *csa) "
/**
 * relax4_inidat - construct linked lists for network topology .
 * <p>PURPOSE</p>
 * <p>This routine constructs two linked lists for the network topology: one list (given by fou, nxtou) for the outgoing arcs of nodes and one list (given by fin, nxtin) for the incoming arcs of nodes. These two lists are required by RELAX4.</p>
 * <p>INPUT PARAMETERS</p>
 * <p>n = number of nodes na = number of arcs startn[j] = starting node for arc j, j = 1,...,na endn[j] = ending node for arc j, j = 1,...,na</p>
 * <p>OUTPUT PARAMETERS</p>
 * <p>fou[i] = first arc out of node i, i = 1,...,n nxtou[j] = next arc out of the starting node of arc j, j = 1,...,na fin[i] = first arc into node i, i = 1,...,n nxtin[j] = next arc into the ending node of arc j, j = 1,...,na</p>
 * <p>WORKING PARAMETERS</p>
 * <p>tempin[1+n], tempou[1+n] </p>
 */
public";

%csmethodmodifiers inflateReset(z_streamp strm) "
/**
 */
public";

%csmethodmodifiers inflateReset2(z_streamp strm, int windowBits) "
/**
 */
public";

%csmethodmodifiers inflateInit2_(z_streamp strm, int windowBits, const char *version, int stream_size) "
/**
 */
public";

%csmethodmodifiers inflateInit_(z_streamp strm, const char *version, int stream_size) "
/**
 */
public";

%csmethodmodifiers inflatePrime(z_streamp strm, int bits, int value) "
/**
 */
public";

%csmethodmodifiers updatewindow(z_streamp strm, unsigned out) "
/**
 */
public";

%csmethodmodifiers inflate(z_streamp strm, int flush) "
/**
 */
public";

%csmethodmodifiers inflateEnd(z_streamp strm) "
/**
 */
public";

%csmethodmodifiers inflateSetDictionary(z_streamp strm, const Bytef *dictionary, uInt dictLength) "
/**
 */
public";

%csmethodmodifiers inflateGetHeader(z_streamp strm, gz_headerp head) "
/**
 */
public";

%csmethodmodifiers inflateSync(z_streamp strm) "
/**
 */
public";

%csmethodmodifiers inflateSyncPoint(z_streamp strm) "
/**
 */
public";

%csmethodmodifiers inflateCopy(z_streamp dest, z_streamp source) "
/**
 */
public";

%csmethodmodifiers inflateUndermine(z_streamp strm, int subvert) "
/**
 */
public";

%csmethodmodifiers inflateMark(z_streamp strm) "
/**
 */
public";

%csmethodmodifiers scf_r0_solve(SCF *scf, int tr, double x[]) "
/**
 */
public";

%csmethodmodifiers scf_s0_solve(SCF *scf, int tr, double x[], double w1[], double w2[], double w3[]) "
/**
 */
public";

%csmethodmodifiers scf_r_prod(SCF *scf, double y[], double a, const double x[]) "
/**
 */
public";

%csmethodmodifiers scf_rt_prod(SCF *scf, double y[], double a, const double x[]) "
/**
 */
public";

%csmethodmodifiers scf_s_prod(SCF *scf, double y[], double a, const double x[]) "
/**
 */
public";

%csmethodmodifiers scf_st_prod(SCF *scf, double y[], double a, const double x[]) "
/**
 */
public";

%csmethodmodifiers scf_a_solve(SCF *scf, double x[], double w[], double work1[], double work2[], double work3[]) "
/**
 */
public";

%csmethodmodifiers scf_at_solve(SCF *scf, double x[], double w[], double work1[], double work2[], double work3[]) "
/**
 */
public";

%csmethodmodifiers scf_add_r_row(SCF *scf, const double w[]) "
/**
 */
public";

%csmethodmodifiers scf_add_s_col(SCF *scf, const double v[]) "
/**
 */
public";

%csmethodmodifiers scf_update_aug(SCF *scf, double b[], double d[], double f[], double g[], double h, int upd, double w1[], double w2[], double w3[]) "
/**
 */
public";

%csmethodmodifiers inflate_fast(z_streamp strm, unsigned start) "
/**
 */
public";

%csmethodmodifiers put_byte(FILE *fp, int c) "
/**
 * rgr_write_bmp16 - write 16-color raster image in BMP file format .
 * <p>SYNOPSIS</p>
 * <p>#include \"glprgr.h\" int rgr_write_bmp16(const char *fname, int m, int n, const char map[]);</p>
 * <p>DESCRIPTION</p>
 * <p>The routine rgr_write_bmp16 writes 16-color raster image in uncompressed BMP file format (Windows bitmap) to a binary file whose name is specified by the character string fname.</p>
 * <p>The parameters m and n specify, respectively, the number of rows and the numbers of columns (i.e. height and width) of the raster image.</p>
 * <p>The character array map has m*n elements. Elements map[0, ..., n-1] correspond to the first (top) scanline, elements map[n, ..., 2*n-1] correspond to the second scanline, etc.</p>
 * <p>Each element of the array map specifies a color of the corresponding pixel as 8-bit binary number XXXXIRGB, where four high-order bits (X) are ignored, I is high intensity bit, R is red color bit, G is green color bit, and B is blue color bit. Thus, all 16 possible colors are coded as following hexadecimal numbers:</p>
 * <p>0x00 = black 0x08 = dark gray 0x01 = blue 0x09 = bright blue 0x02 = green 0x0A = bright green 0x03 = cyan 0x0B = bright cyan 0x04 = red 0x0C = bright red 0x05 = magenta 0x0D = bright magenta 0x06 = brown 0x0E = yellow 0x07 = light gray 0x0F = white</p>
 * <p>RETURNS</p>
 * <p>If no error occured, the routine returns zero; otherwise, it prints an appropriate error message and returns non-zero. </p>
 */
public";

%csmethodmodifiers put_word(FILE *fp, int w) "
/**
 */
public";

%csmethodmodifiers put_dword(FILE *fp, int d) "
/**
 */
public";

%csmethodmodifiers rgr_write_bmp16(const char *fname, int m, int n, const char map[]) "
/**
 */
public";

%csmethodmodifiers overflow(int u, int v) "
/**
 * okalg - out-of-kilter algorithm .
 * <p>SYNOPSIS</p>
 * <p>#include \"okalg.h\" int okalg(int nv, int na, const int tail[], const int head[], const int low[], const int cap[], const int cost[], int x[], int pi[]);</p>
 * <p>DESCRIPTION</p>
 * <p>The routine okalg implements the out-of-kilter algorithm to find a minimal-cost circulation in the specified flow network.</p>
 * <p>INPUT PARAMETERS</p>
 * <p>nv is the number of nodes, nv &gt;= 0.</p>
 * <p>na is the number of arcs, na &gt;= 0.</p>
 * <p>tail[a], a = 1,...,na, is the index of tail node of arc a.</p>
 * <p>head[a], a = 1,...,na, is the index of head node of arc a.</p>
 * <p>low[a], a = 1,...,na, is an lower bound to the flow through arc a.</p>
 * <p>cap[a], a = 1,...,na, is an upper bound to the flow through arc a, which is the capacity of the arc.</p>
 * <p>cost[a], a = 1,...,na, is a per-unit cost of the flow through arc a.</p>
 * <p>NOTES</p>
 * <p>
Multiple arcs are allowed, but self-loops are not allowed.It is required that 0 &lt;= low[a] &lt;= cap[a] for all arcs.Arc costs may have any sign.
</p>
 * <p>OUTPUT PARAMETERS</p>
 * <p>x[a], a = 1,...,na, is optimal value of the flow through arc a.</p>
 * <p>pi[i], i = 1,...,nv, is Lagrange multiplier for flow conservation equality constraint corresponding to node i (the node potential).</p>
 * <p>RETURNS</p>
 * <p>0 optimal circulation found;</p>
 * <p>1 there is no feasible circulation;</p>
 * <p>2 integer overflow occured;</p>
 * <p>3 optimality test failed (logic error).</p>
 * <p>REFERENCES</p>
 * <p>L.R.Ford, Jr., and D.R.Fulkerson, \"Flows in Networks,\" The RAND Corp., Report R-375-PR (August 1962), Chap. III \"Minimal Cost Flow
Problems,\" pp.113-26. </p>
 */
public";

%csmethodmodifiers okalg(int nv, int na, const int tail[], const int head[], const int low[], const int cap[], const int cost[], int x[], int pi[]) "
/**
 */
public";

%csmethodmodifiers spx_alloc_nt(SPXLP *lp, SPXNT *nt) "
/**
 */
public";

%csmethodmodifiers spx_init_nt(SPXLP *lp, SPXNT *nt) "
/**
 */
public";

%csmethodmodifiers spx_nt_add_col(SPXLP *lp, SPXNT *nt, int j, int k) "
/**
 */
public";

%csmethodmodifiers spx_build_nt(SPXLP *lp, SPXNT *nt) "
/**
 */
public";

%csmethodmodifiers spx_nt_del_col(SPXLP *lp, SPXNT *nt, int j, int k) "
/**
 */
public";

%csmethodmodifiers spx_update_nt(SPXLP *lp, SPXNT *nt, int p, int q) "
/**
 */
public";

%csmethodmodifiers spx_nt_prod(SPXLP *lp, SPXNT *nt, double y[], int ign, double s, const double x[]) "
/**
 */
public";

%csmethodmodifiers spx_free_nt(SPXLP *lp, SPXNT *nt) "
/**
 */
public";

%csmethodmodifiers btf_store_a_cols(BTF *btf, int(*col)(void *info, int j, int ind[], double val[]), void *info, int ind[], double val[]) "
/**
 */
public";

%csmethodmodifiers btf_make_blocks(BTF *btf) "
/**
 */
public";

%csmethodmodifiers btf_check_blocks(BTF *btf) "
/**
 */
public";

%csmethodmodifiers btf_build_a_rows(BTF *btf, int len[]) "
/**
 */
public";

%csmethodmodifiers btf_a_solve(BTF *btf, double b[], double x[], double w1[], double w2[]) "
/**
 */
public";

%csmethodmodifiers btf_at_solve(BTF *btf, double b[], double x[], double w1[], double w2[]) "
/**
 */
public";

%csmethodmodifiers btf_at_solve1(BTF *btf, double e[], double y[], double w1[], double w2[]) "
/**
 */
public";

%csmethodmodifiers btf_estimate_norm(BTF *btf, double w1[], double w2[], double w3[], double w4[]) "
/**
 */
public";

%csmethodmodifiers glp_bf_exists(glp_prob *lp) "
/**
 * glp_bf_exists - check if the basis factorization exists .
 * <p>SYNOPSIS</p>
 * <p>int glp_bf_exists(glp_prob *lp);</p>
 * <p>RETURNS</p>
 * <p>If the basis factorization for the current basis associated with the specified problem object exists and therefore is available for computations, the routine glp_bf_exists returns non-zero. Otherwise the routine returns zero. </p>
 */
public";

%csmethodmodifiers b_col(void *info, int j, int ind[], double val[]) "
/**
 * glp_factorize - compute the basis factorization .
 * <p>SYNOPSIS</p>
 * <p>int glp_factorize(glp_prob *lp);</p>
 * <p>DESCRIPTION</p>
 * <p>The routine glp_factorize computes the basis factorization for the current basis associated with the specified problem object.</p>
 * <p>RETURNS</p>
 * <p>0 The basis factorization has been successfully computed.</p>
 * <p>GLP_EBADB The basis matrix is invalid, i.e. the number of basic (auxiliary and structural) variables differs from the number of rows in the problem object.</p>
 * <p>GLP_ESING The basis matrix is singular within the working precision.</p>
 * <p>GLP_ECOND The basis matrix is ill-conditioned. </p>
 */
public";

%csmethodmodifiers glp_factorize(glp_prob *lp) "
/**
 */
public";

%csmethodmodifiers glp_bf_updated(glp_prob *lp) "
/**
 * glp_bf_updated - check if the basis factorization has been updated .
 * <p>SYNOPSIS</p>
 * <p>int glp_bf_updated(glp_prob *lp);</p>
 * <p>RETURNS</p>
 * <p>If the basis factorization has been just computed from scratch, the routine glp_bf_updated returns zero. Otherwise, if the factorization has been updated one or more times, the routine returns non-zero. </p>
 */
public";

%csmethodmodifiers glp_get_bfcp(glp_prob *P, glp_bfcp *parm) "
/**
 * glp_get_bfcp - retrieve basis factorization control parameters .
 * <p>SYNOPSIS</p>
 * <p>void glp_get_bfcp(glp_prob *lp, glp_bfcp *parm);</p>
 * <p>DESCRIPTION</p>
 * <p>The routine glp_get_bfcp retrieves control parameters, which are used on computing and updating the basis factorization associated with the specified problem object.</p>
 * <p>Current values of control parameters are stored by the routine in a glp_bfcp structure, which the parameter parm points to. </p>
 */
public";

%csmethodmodifiers glp_set_bfcp(glp_prob *P, const glp_bfcp *parm) "
/**
 * glp_set_bfcp - change basis factorization control parameters .
 * <p>SYNOPSIS</p>
 * <p>void glp_set_bfcp(glp_prob *lp, const glp_bfcp *parm);</p>
 * <p>DESCRIPTION</p>
 * <p>The routine glp_set_bfcp changes control parameters, which are used by internal GLPK routines in computing and updating the basis factorization associated with the specified problem object.</p>
 * <p>New values of the control parameters should be passed in a structure glp_bfcp, which the parameter parm points to.</p>
 * <p>The parameter parm can be specified as NULL, in which case all control parameters are reset to their default values. </p>
 */
public";

%csmethodmodifiers glp_get_bhead(glp_prob *lp, int k) "
/**
 * glp_get_bhead - retrieve the basis header information .
 * <p>SYNOPSIS</p>
 * <p>int glp_get_bhead(glp_prob *lp, int k);</p>
 * <p>DESCRIPTION</p>
 * <p>The routine glp_get_bhead returns the basis header information for the current basis associated with the specified problem object.</p>
 * <p>RETURNS</p>
 * <p>If xB[k], 1 &lt;= k &lt;= m, is i-th auxiliary variable (1 &lt;= i &lt;= m), the routine returns i. Otherwise, if xB[k] is j-th structural variable (1 &lt;= j &lt;= n), the routine returns m+j. Here m is the number of rows and n is the number of columns in the problem object. </p>
 */
public";

%csmethodmodifiers glp_get_row_bind(glp_prob *lp, int i) "
/**
 * glp_get_row_bind - retrieve row index in the basis header .
 * <p>SYNOPSIS</p>
 * <p>int glp_get_row_bind(glp_prob *lp, int i);</p>
 * <p>RETURNS</p>
 * <p>The routine glp_get_row_bind returns the index k of basic variable xB[k], 1 &lt;= k &lt;= m, which is i-th auxiliary variable, 1 &lt;= i &lt;= m, in the current basis associated with the specified problem object, where m is the number of rows. However, if i-th auxiliary variable is non-basic, the routine returns zero. </p>
 */
public";

%csmethodmodifiers glp_get_col_bind(glp_prob *lp, int j) "
/**
 * glp_get_col_bind - retrieve column index in the basis header .
 * <p>SYNOPSIS</p>
 * <p>int glp_get_col_bind(glp_prob *lp, int j);</p>
 * <p>RETURNS</p>
 * <p>The routine glp_get_col_bind returns the index k of basic variable xB[k], 1 &lt;= k &lt;= m, which is j-th structural variable, 1 &lt;= j &lt;= n, in the current basis associated with the specified problem object, where m is the number of rows, n is the number of columns. However, if j-th structural variable is non-basic, the routine returns zero. </p>
 */
public";

%csmethodmodifiers glp_ftran(glp_prob *lp, double x[]) "
/**
 * glp_ftran - perform forward transformation (solve system B*x = b) .
 * <p>SYNOPSIS</p>
 * <p>void glp_ftran(glp_prob *lp, double x[]);</p>
 * <p>DESCRIPTION</p>
 * <p>The routine glp_ftran performs forward transformation, i.e. solves the system B*x = b, where B is the basis matrix corresponding to the current basis for the specified problem object, x is the vector of unknowns to be computed, b is the vector of right-hand sides.</p>
 * <p>On entry elements of the vector b should be stored in dense format in locations x[1], ..., x[m], where m is the number of rows. On exit the routine stores elements of the vector x in the same locations.</p>
 * <p>SCALING/UNSCALING</p>
 * <p>Let A~ = (I | -A) is the augmented constraint matrix of the original (unscaled) problem. In the scaled LP problem instead the matrix A the scaled matrix A\" = R*A*S is actually used, so</p>
 * <p>A~\" = (I | A\") = (I | R*A*S) = (R*I*inv(R) | R*A*S) = (1) = R*(I | A)*S~ = R*A~*S~,</p>
 * <p>is the scaled augmented constraint matrix, where R and S are diagonal scaling matrices used to scale rows and columns of the matrix A, and</p>
 * <p>S~ = diag(inv(R) | S) (2)</p>
 * <p>is an augmented diagonal scaling matrix.</p>
 * <p>By definition:</p>
 * <p>A~ = (B | N), (3)</p>
 * <p>where B is the basic matrix, which consists of basic columns of the augmented constraint matrix A~, and N is a matrix, which consists of non-basic columns of A~. From (1) it follows that:</p>
 * <p>A~\" = (B\" | N\") = (R*B*SB | R*N*SN), (4)</p>
 * <p>where SB and SN are parts of the augmented scaling matrix S~, which correspond to basic and non-basic variables, respectively. Therefore</p>
 * <p>B\" = R*B*SB, (5)</p>
 * <p>which is the scaled basis matrix. </p>
 */
public";

%csmethodmodifiers glp_btran(glp_prob *lp, double x[]) "
/**
 * glp_btran - perform backward transformation (solve system B'*x = b) .
 * <p>SYNOPSIS</p>
 * <p>void glp_btran(glp_prob *lp, double x[]);</p>
 * <p>DESCRIPTION</p>
 * <p>The routine glp_btran performs backward transformation, i.e. solves the system B'*x = b, where B' is a matrix transposed to the basis matrix corresponding to the current basis for the specified problem problem object, x is the vector of unknowns to be computed, b is the vector of right-hand sides.</p>
 * <p>On entry elements of the vector b should be stored in dense format in locations x[1], ..., x[m], where m is the number of rows. On exit the routine stores elements of the vector x in the same locations.</p>
 * <p>SCALING/UNSCALING</p>
 * <p>See comments to the routine glp_ftran. </p>
 */
public";

%csmethodmodifiers glp_warm_up(glp_prob *P) "
/**
 * glp_warm_up - \"warm up\" LP basis .
 * <p>SYNOPSIS</p>
 * <p>int glp_warm_up(glp_prob *P);</p>
 * <p>DESCRIPTION</p>
 * <p>The routine glp_warm_up \"warms up\" the LP basis for the specified problem object using current statuses assigned to rows and columns (that is, to auxiliary and structural variables).</p>
 * <p>This operation includes computing factorization of the basis matrix (if it does not exist), computing primal and dual components of basic solution, and determining the solution status.</p>
 * <p>RETURNS</p>
 * <p>0 The operation has been successfully performed.</p>
 * <p>GLP_EBADB The basis matrix is invalid, i.e. the number of basic (auxiliary and structural) variables differs from the number of rows in the problem object.</p>
 * <p>GLP_ESING The basis matrix is singular within the working precision.</p>
 * <p>GLP_ECOND The basis matrix is ill-conditioned. </p>
 */
public";

%csmethodmodifiers glp_eval_tab_row(glp_prob *lp, int k, int ind[], double val[]) "
/**
 * glp_eval_tab_row - compute row of the simplex tableau .
 * <p>SYNOPSIS</p>
 * <p>int glp_eval_tab_row(glp_prob *lp, int k, int ind[], double val[]);</p>
 * <p>DESCRIPTION</p>
 * <p>The routine glp_eval_tab_row computes a row of the current simplex tableau for the basic variable, which is specified by the number k: if 1 &lt;= k &lt;= m, x[k] is k-th auxiliary variable; if m+1 &lt;= k &lt;= m+n, x[k] is (k-m)-th structural variable, where m is number of rows, and n is number of columns. The current basis must be available.</p>
 * <p>The routine stores column indices and numerical values of non-zero elements of the computed row using sparse format to the locations ind[1], ..., ind[len] and val[1], ..., val[len], respectively, where 0 &lt;= len &lt;= n is number of non-zeros returned on exit.</p>
 * <p>Element indices stored in the array ind have the same sense as the index k, i.e. indices 1 to m denote auxiliary variables and indices m+1 to m+n denote structural ones (all these variables are obviously non-basic by definition).</p>
 * <p>The computed row shows how the specified basic variable x[k] = xB[i] depends on non-basic variables:</p>
 * <p>xB[i] = alfa[i,1]*xN[1] + alfa[i,2]*xN[2] + ... + alfa[i,n]*xN[n],</p>
 * <p>where alfa[i,j] are elements of the simplex table row, xN[j] are non-basic (auxiliary and structural) variables.</p>
 * <p>RETURNS</p>
 * <p>The routine returns number of non-zero elements in the simplex table row stored in the arrays ind and val.</p>
 * <p>BACKGROUND</p>
 * <p>The system of equality constraints of the LP problem is:</p>
 * <p>xR = A * xS, (1)</p>
 * <p>where xR is the vector of auxliary variables, xS is the vector of structural variables, A is the matrix of constraint coefficients.</p>
 * <p>The system (1) can be written in homogenous form as follows:</p>
 * <p>A~ * x = 0, (2)</p>
 * <p>where A~ = (I | -A) is the augmented constraint matrix (has m rows and m+n columns), x = (xR | xS) is the vector of all (auxiliary and structural) variables.</p>
 * <p>By definition for the current basis we have:</p>
 * <p>A~ = (B | N), (3)</p>
 * <p>where B is the basis matrix. Thus, the system (2) can be written as:</p>
 * <p>B * xB + N * xN = 0. (4)</p>
 * <p>From (4) it follows that:</p>
 * <p>xB = A^ * xN, (5)</p>
 * <p>where the matrix</p>
 * <p>A^ = - inv(B) * N (6)</p>
 * <p>is called the simplex table.</p>
 * <p>It is understood that i-th row of the simplex table is:</p>
 * <p>e * A^ = - e * inv(B) * N, (7)</p>
 * <p>where e is a unity vector with e[i] = 1.</p>
 * <p>To compute i-th row of the simplex table the routine first computes i-th row of the inverse:</p>
 * <p>rho = inv(B') * e, (8)</p>
 * <p>where B' is a matrix transposed to B, and then computes elements of i-th row of the simplex table as scalar products:</p>
 * <p>alfa[i,j] = - rho * N[j] for all j, (9)</p>
 * <p>where N[j] is a column of the augmented constraint matrix A~, which corresponds to some non-basic auxiliary or structural variable. </p>
 */
public";

%csmethodmodifiers glp_eval_tab_col(glp_prob *lp, int k, int ind[], double val[]) "
/**
 * glp_eval_tab_col - compute column of the simplex tableau .
 * <p>SYNOPSIS</p>
 * <p>int glp_eval_tab_col(glp_prob *lp, int k, int ind[], double val[]);</p>
 * <p>DESCRIPTION</p>
 * <p>The routine glp_eval_tab_col computes a column of the current simplex table for the non-basic variable, which is specified by the number k: if 1 &lt;= k &lt;= m, x[k] is k-th auxiliary variable; if m+1 &lt;= k &lt;= m+n, x[k] is (k-m)-th structural variable, where m is number of rows, and n is number of columns. The current basis must be available.</p>
 * <p>The routine stores row indices and numerical values of non-zero elements of the computed column using sparse format to the locations ind[1], ..., ind[len] and val[1], ..., val[len] respectively, where 0 &lt;= len &lt;= m is number of non-zeros returned on exit.</p>
 * <p>Element indices stored in the array ind have the same sense as the index k, i.e. indices 1 to m denote auxiliary variables and indices m+1 to m+n denote structural ones (all these variables are obviously basic by the definition).</p>
 * <p>The computed column shows how basic variables depend on the specified non-basic variable x[k] = xN[j]:</p>
 * <p>xB[1] = ... + alfa[1,j]*xN[j] + ... xB[2] = ... + alfa[2,j]*xN[j] + ... . . . . . . xB[m] = ... + alfa[m,j]*xN[j] + ...</p>
 * <p>where alfa[i,j] are elements of the simplex table column, xB[i] are basic (auxiliary and structural) variables.</p>
 * <p>RETURNS</p>
 * <p>The routine returns number of non-zero elements in the simplex table column stored in the arrays ind and val.</p>
 * <p>BACKGROUND</p>
 * <p>As it was explained in comments to the routine glp_eval_tab_row (see above) the simplex table is the following matrix:</p>
 * <p>A^ = - inv(B) * N. (1)</p>
 * <p>Therefore j-th column of the simplex table is:</p>
 * <p>A^ * e = - inv(B) * N * e = - inv(B) * N[j], (2)</p>
 * <p>where e is a unity vector with e[j] = 1, B is the basis matrix, N[j] is a column of the augmented constraint matrix A~, which corresponds to the given non-basic auxiliary or structural variable. </p>
 */
public";

%csmethodmodifiers glp_transform_row(glp_prob *P, int len, int ind[], double val[]) "
/**
 * glp_transform_row - transform explicitly specified row .
 * <p>SYNOPSIS</p>
 * <p>int glp_transform_row(glp_prob *P, int len, int ind[], double val[]);</p>
 * <p>DESCRIPTION</p>
 * <p>The routine glp_transform_row performs the same operation as the routine glp_eval_tab_row with exception that the row to be transformed is specified explicitly as a sparse vector.</p>
 * <p>The explicitly specified row may be thought as a linear form:</p>
 * <p>x = a[1]*x[m+1] + a[2]*x[m+2] + ... + a[n]*x[m+n], (1)</p>
 * <p>where x is an auxiliary variable for this row, a[j] are coefficients of the linear form, x[m+j] are structural variables.</p>
 * <p>On entry column indices and numerical values of non-zero elements of the row should be stored in locations ind[1], ..., ind[len] and val[1], ..., val[len], where len is the number of non-zero elements.</p>
 * <p>This routine uses the system of equality constraints and the current basis in order to express the auxiliary variable x in (1) through the current non-basic variables (as if the transformed row were added to the problem object and its auxiliary variable were basic), i.e. the resultant row has the form:</p>
 * <p>x = alfa[1]*xN[1] + alfa[2]*xN[2] + ... + alfa[n]*xN[n], (2)</p>
 * <p>where xN[j] are non-basic (auxiliary or structural) variables, n is the number of columns in the LP problem object.</p>
 * <p>On exit the routine stores indices and numerical values of non-zero elements of the resultant row (2) in locations ind[1], ..., ind[len'] and val[1], ..., val[len'], where 0 &lt;= len' &lt;= n is the number of non-zero elements in the resultant row returned by the routine. Note that indices (numbers) of non-basic variables stored in the array ind correspond to original ordinal numbers of variables: indices 1 to m mean auxiliary variables and indices m+1 to m+n mean structural ones.</p>
 * <p>RETURNS</p>
 * <p>The routine returns len', which is the number of non-zero elements in the resultant row stored in the arrays ind and val.</p>
 * <p>BACKGROUND</p>
 * <p>The explicitly specified row (1) is transformed in the same way as it were the objective function row.</p>
 * <p>From (1) it follows that:</p>
 * <p>x = aB * xB + aN * xN, (3)</p>
 * <p>where xB is the vector of basic variables, xN is the vector of non-basic variables.</p>
 * <p>The simplex table, which corresponds to the current basis, is:</p>
 * <p>xB = [-inv(B) * N] * xN. (4)</p>
 * <p>Therefore substituting xB from (4) to (3) we have:</p>
 * <p>x = aB * [-inv(B) * N] * xN + aN * xN = (5) = rho * (-N) * xN + aN * xN = alfa * xN,</p>
 * <p>where:</p>
 * <p>rho = inv(B') * aB, (6)</p>
 * <p>and</p>
 * <p>alfa = aN + rho * (-N) (7)</p>
 * <p>is the resultant row computed by the routine. </p>
 */
public";

%csmethodmodifiers glp_transform_col(glp_prob *P, int len, int ind[], double val[]) "
/**
 * glp_transform_col - transform explicitly specified column .
 * <p>SYNOPSIS</p>
 * <p>int glp_transform_col(glp_prob *P, int len, int ind[], double val[]);</p>
 * <p>DESCRIPTION</p>
 * <p>The routine glp_transform_col performs the same operation as the routine glp_eval_tab_col with exception that the column to be transformed is specified explicitly as a sparse vector.</p>
 * <p>The explicitly specified column may be thought as if it were added to the original system of equality constraints:</p>
 * <p>x[1] = a[1,1]*x[m+1] + ... + a[1,n]*x[m+n] + a[1]*x x[2] = a[2,1]*x[m+1] + ... + a[2,n]*x[m+n] + a[2]*x (1) . . . . . . . . . . . . . . . x[m] = a[m,1]*x[m+1] + ... + a[m,n]*x[m+n] + a[m]*x</p>
 * <p>where x[i] are auxiliary variables, x[m+j] are structural variables, x is a structural variable for the explicitly specified column, a[i] are constraint coefficients for x.</p>
 * <p>On entry row indices and numerical values of non-zero elements of the column should be stored in locations ind[1], ..., ind[len] and val[1], ..., val[len], where len is the number of non-zero elements.</p>
 * <p>This routine uses the system of equality constraints and the current basis in order to express the current basic variables through the structural variable x in (1) (as if the transformed column were added to the problem object and the variable x were non-basic), i.e. the resultant column has the form:</p>
 * <p>xB[1] = ... + alfa[1]*x xB[2] = ... + alfa[2]*x (2) . . . . . . xB[m] = ... + alfa[m]*x</p>
 * <p>where xB are basic (auxiliary and structural) variables, m is the number of rows in the problem object.</p>
 * <p>On exit the routine stores indices and numerical values of non-zero elements of the resultant column (2) in locations ind[1], ..., ind[len'] and val[1], ..., val[len'], where 0 &lt;= len' &lt;= m is the number of non-zero element in the resultant column returned by the routine. Note that indices (numbers) of basic variables stored in the array ind correspond to original ordinal numbers of variables: indices 1 to m mean auxiliary variables and indices m+1 to m+n mean structural ones.</p>
 * <p>RETURNS</p>
 * <p>The routine returns len', which is the number of non-zero elements in the resultant column stored in the arrays ind and val.</p>
 * <p>BACKGROUND</p>
 * <p>The explicitly specified column (1) is transformed in the same way as any other column of the constraint matrix using the formula:</p>
 * <p>alfa = inv(B) * a, (3)</p>
 * <p>where alfa is the resultant column computed by the routine. </p>
 */
public";

%csmethodmodifiers glp_prim_rtest(glp_prob *P, int len, const int ind[], const double val[], int dir, double eps) "
/**
 * glp_prim_rtest - perform primal ratio test .
 * <p>SYNOPSIS</p>
 * <p>int glp_prim_rtest(glp_prob *P, int len, const int ind[], const double val[], int dir, double eps);</p>
 * <p>DESCRIPTION</p>
 * <p>The routine glp_prim_rtest performs the primal ratio test using an explicitly specified column of the simplex table.</p>
 * <p>The current basic solution associated with the LP problem object must be primal feasible.</p>
 * <p>The explicitly specified column of the simplex table shows how the basic variables xB depend on some non-basic variable x (which is not necessarily presented in the problem object):</p>
 * <p>xB[1] = ... + alfa[1] * x + ... xB[2] = ... + alfa[2] * x + ... (*) . . . . . . . . xB[m] = ... + alfa[m] * x + ...</p>
 * <p>The column (*) is specifed on entry to the routine using the sparse format. Ordinal numbers of basic variables xB[i] should be placed in locations ind[1], ..., ind[len], where ordinal number 1 to m denote auxiliary variables, and ordinal numbers m+1 to m+n denote structural variables. The corresponding non-zero coefficients alfa[i] should be placed in locations val[1], ..., val[len]. The arrays ind and val are not changed on exit.</p>
 * <p>The parameter dir specifies direction in which the variable x changes on entering the basis: +1 means increasing, -1 means decreasing.</p>
 * <p>The parameter eps is an absolute tolerance (small positive number) used by the routine to skip small alfa[j] of the row (*).</p>
 * <p>The routine determines which basic variable (among specified in ind[1], ..., ind[len]) should leave the basis in order to keep primal feasibility.</p>
 * <p>RETURNS</p>
 * <p>The routine glp_prim_rtest returns the index piv in the arrays ind and val corresponding to the pivot element chosen, 1 &lt;= piv &lt;= len. If the adjacent basic solution is primal unbounded and therefore the choice cannot be made, the routine returns zero.</p>
 * <p>COMMENTS</p>
 * <p>If the non-basic variable x is presented in the LP problem object, the column (*) can be computed with the routine glp_eval_tab_col; otherwise it can be computed with the routine glp_transform_col. </p>
 */
public";

%csmethodmodifiers glp_dual_rtest(glp_prob *P, int len, const int ind[], const double val[], int dir, double eps) "
/**
 * glp_dual_rtest - perform dual ratio test .
 * <p>SYNOPSIS</p>
 * <p>int glp_dual_rtest(glp_prob *P, int len, const int ind[], const double val[], int dir, double eps);</p>
 * <p>DESCRIPTION</p>
 * <p>The routine glp_dual_rtest performs the dual ratio test using an explicitly specified row of the simplex table.</p>
 * <p>The current basic solution associated with the LP problem object must be dual feasible.</p>
 * <p>The explicitly specified row of the simplex table is a linear form that shows how some basic variable x (which is not necessarily presented in the problem object) depends on non-basic variables xN:</p>
 * <p>x = alfa[1] * xN[1] + alfa[2] * xN[2] + ... + alfa[n] * xN[n]. (*)</p>
 * <p>The row (*) is specified on entry to the routine using the sparse format. Ordinal numbers of non-basic variables xN[j] should be placed in locations ind[1], ..., ind[len], where ordinal numbers 1 to m denote auxiliary variables, and ordinal numbers m+1 to m+n denote structural variables. The corresponding non-zero coefficients alfa[j] should be placed in locations val[1], ..., val[len]. The arrays ind and val are not changed on exit.</p>
 * <p>The parameter dir specifies direction in which the variable x changes on leaving the basis: +1 means that x goes to its lower bound, and -1 means that x goes to its upper bound.</p>
 * <p>The parameter eps is an absolute tolerance (small positive number) used by the routine to skip small alfa[j] of the row (*).</p>
 * <p>The routine determines which non-basic variable (among specified in ind[1], ..., ind[len]) should enter the basis in order to keep dual feasibility.</p>
 * <p>RETURNS</p>
 * <p>The routine glp_dual_rtest returns the index piv in the arrays ind and val corresponding to the pivot element chosen, 1 &lt;= piv &lt;= len. If the adjacent basic solution is dual unbounded and therefore the choice cannot be made, the routine returns zero.</p>
 * <p>COMMENTS</p>
 * <p>If the basic variable x is presented in the LP problem object, the row (*) can be computed with the routine glp_eval_tab_row; otherwise it can be computed with the routine glp_transform_row. </p>
 */
public";

%csmethodmodifiers _glp_analyze_row(glp_prob *P, int len, const int ind[], const double val[], int type, double rhs, double eps, int *_piv, double *_x, double *_dx, double *_y, double *_dy, double *_dz) "
/**
 * glp_analyze_row - simulate one iteration of dual simplex method .
 * <p>SYNOPSIS</p>
 * <p>int glp_analyze_row(glp_prob *P, int len, const int ind[], const double val[], int type, double rhs, double eps, int *piv, double *x, double *dx, double *y, double *dy, double *dz);</p>
 * <p>DESCRIPTION</p>
 * <p>Let the current basis be optimal or dual feasible, and there be specified a row (constraint), which is violated by the current basic solution. The routine glp_analyze_row simulates one iteration of the dual simplex method to determine some information on the adjacent basis (see below), where the specified row becomes active constraint (i.e. its auxiliary variable becomes non-basic).</p>
 * <p>The current basic solution associated with the problem object passed to the routine must be dual feasible, and its primal components must be defined.</p>
 * <p>The row to be analyzed must be previously transformed either with the routine glp_eval_tab_row (if the row is in the problem object) or with the routine glp_transform_row (if the row is external, i.e. not in the problem object). This is needed to express the row only through (auxiliary and structural) variables, which are non-basic in the current basis:</p>
 * <p>y = alfa[1] * xN[1] + alfa[2] * xN[2] + ... + alfa[n] * xN[n],</p>
 * <p>where y is an auxiliary variable of the row, alfa[j] is an influence coefficient, xN[j] is a non-basic variable.</p>
 * <p>The row is passed to the routine in sparse format. Ordinal numbers of non-basic variables are stored in locations ind[1], ..., ind[len], where numbers 1 to m denote auxiliary variables while numbers m+1 to m+n denote structural variables. Corresponding non-zero coefficients alfa[j] are stored in locations val[1], ..., val[len]. The arrays ind and val are ot changed on exit.</p>
 * <p>The parameters type and rhs specify the row type and its right-hand side as follows:</p>
 * <p>type = GLP_LO: y = sum alfa[j] * xN[j] &gt;= rhs</p>
 * <p>type = GLP_UP: y = sum alfa[j] * xN[j] &lt;= rhs</p>
 * <p>The parameter eps is an absolute tolerance (small positive number) used by the routine to skip small coefficients alfa[j] on performing the dual ratio test.</p>
 * <p>If the operation was successful, the routine stores the following information to corresponding location (if some parameter is NULL, its value is not stored):</p>
 * <p>piv index in the array ind and val, 1 &lt;= piv &lt;= len, determining the non-basic variable, which would enter the adjacent basis;</p>
 * <p>x value of the non-basic variable in the current basis;</p>
 * <p>dx difference between values of the non-basic variable in the adjacent and current bases, dx = x.new - x.old;</p>
 * <p>y value of the row (i.e. of its auxiliary variable) in the current basis;</p>
 * <p>dy difference between values of the row in the adjacent and current bases, dy = y.new - y.old;</p>
 * <p>dz difference between values of the objective function in the adjacent and current bases, dz = z.new - z.old. Note that in case of minimization dz &gt;= 0, and in case of maximization dz &lt;= 0, i.e. in the adjacent basis the objective function always gets worse (degrades). </p>
 */
public";

%csmethodmodifiers glp_analyze_bound(glp_prob *P, int k, double *value1, int *var1, double *value2, int *var2) "
/**
 * glp_analyze_bound - analyze active bound of non-basic variable .
 * <p>SYNOPSIS</p>
 * <p>void glp_analyze_bound(glp_prob *P, int k, double *limit1, int *var1, double *limit2, int *var2);</p>
 * <p>DESCRIPTION</p>
 * <p>The routine glp_analyze_bound analyzes the effect of varying the active bound of specified non-basic variable.</p>
 * <p>The non-basic variable is specified by the parameter k, where 1 &lt;= k &lt;= m means auxiliary variable of corresponding row while m+1 &lt;= k &lt;= m+n means structural variable (column).</p>
 * <p>Note that the current basic solution must be optimal, and the basis factorization must exist.</p>
 * <p>Results of the analysis have the following meaning.</p>
 * <p>value1 is the minimal value of the active bound, at which the basis still remains primal feasible and thus optimal. -DBL_MAX means that the active bound has no lower limit.</p>
 * <p>var1 is the ordinal number of an auxiliary (1 to m) or structural (m+1 to n) basic variable, which reaches its bound first and thereby limits further decreasing the active bound being analyzed. if value1 = -DBL_MAX, var1 is set to 0.</p>
 * <p>value2 is the maximal value of the active bound, at which the basis still remains primal feasible and thus optimal. +DBL_MAX means that the active bound has no upper limit.</p>
 * <p>var2 is the ordinal number of an auxiliary (1 to m) or structural (m+1 to n) basic variable, which reaches its bound first and thereby limits further increasing the active bound being analyzed. if value2 = +DBL_MAX, var2 is set to 0. </p>
 */
public";

%csmethodmodifiers glp_analyze_coef(glp_prob *P, int k, double *coef1, int *var1, double *value1, double *coef2, int *var2, double *value2) "
/**
 * glp_analyze_coef - analyze objective coefficient at basic variable .
 * <p>SYNOPSIS</p>
 * <p>void glp_analyze_coef(glp_prob *P, int k, double *coef1, int *var1, double *value1, double *coef2, int *var2, double *value2);</p>
 * <p>DESCRIPTION</p>
 * <p>The routine glp_analyze_coef analyzes the effect of varying the objective coefficient at specified basic variable.</p>
 * <p>The basic variable is specified by the parameter k, where 1 &lt;= k &lt;= m means auxiliary variable of corresponding row while m+1 &lt;= k &lt;= m+n means structural variable (column).</p>
 * <p>Note that the current basic solution must be optimal, and the basis factorization must exist.</p>
 * <p>Results of the analysis have the following meaning.</p>
 * <p>coef1 is the minimal value of the objective coefficient, at which the basis still remains dual feasible and thus optimal. -DBL_MAX means that the objective coefficient has no lower limit.</p>
 * <p>var1 is the ordinal number of an auxiliary (1 to m) or structural (m+1 to n) non-basic variable, whose reduced cost reaches its zero bound first and thereby limits further decreasing the objective coefficient being analyzed. If coef1 = -DBL_MAX, var1 is set to 0.</p>
 * <p>value1 is value of the basic variable being analyzed in an adjacent basis, which is defined as follows. Let the objective coefficient reaches its minimal value (coef1) and continues decreasing. Then the reduced cost of the limiting non-basic variable (var1) becomes dual infeasible and the current basis becomes non-optimal that forces the limiting non-basic variable to enter the basis replacing there some basic variable that leaves the basis to keep primal feasibility. Should note that on determining the adjacent basis current bounds of the basic variable being analyzed are ignored as if it were free (unbounded) variable, so it cannot leave the basis. It may happen that no dual feasible adjacent basis exists, in which case value1 is set to -DBL_MAX or +DBL_MAX.</p>
 * <p>coef2 is the maximal value of the objective coefficient, at which the basis still remains dual feasible and thus optimal. +DBL_MAX means that the objective coefficient has no upper limit.</p>
 * <p>var2 is the ordinal number of an auxiliary (1 to m) or structural (m+1 to n) non-basic variable, whose reduced cost reaches its zero bound first and thereby limits further increasing the objective coefficient being analyzed. If coef2 = +DBL_MAX, var2 is set to 0.</p>
 * <p>value2 is value of the basic variable being analyzed in an adjacent basis, which is defined exactly in the same way as value1 above with exception that now the objective coefficient is increasing. </p>
 */
public";

%csmethodmodifiers npp_sat_free_row(NPP *npp, NPPROW *p) "
/**
 */
public";

%csmethodmodifiers rcv_sat_fixed_col(NPP *, void *) "
/**
 */
public";

%csmethodmodifiers npp_sat_fixed_col(NPP *npp, NPPCOL *q) "
/**
 */
public";

%csmethodmodifiers npp_sat_is_bin_comb(NPP *npp, NPPROW *row) "
/**
 */
public";

%csmethodmodifiers npp_sat_num_pos_coef(NPP *npp, NPPROW *row) "
/**
 */
public";

%csmethodmodifiers npp_sat_num_neg_coef(NPP *npp, NPPROW *row) "
/**
 */
public";

%csmethodmodifiers npp_sat_is_cover_ineq(NPP *npp, NPPROW *row) "
/**
 */
public";

%csmethodmodifiers npp_sat_is_pack_ineq(NPP *npp, NPPROW *row) "
/**
 */
public";

%csmethodmodifiers npp_sat_is_partn_eq(NPP *npp, NPPROW *row) "
/**
 */
public";

%csmethodmodifiers npp_sat_reverse_row(NPP *npp, NPPROW *row) "
/**
 */
public";

%csmethodmodifiers npp_sat_split_pack(NPP *npp, NPPROW *row, int nlit) "
/**
 */
public";

%csmethodmodifiers npp_sat_encode_pack(NPP *npp, NPPROW *row) "
/**
 */
public";

%csmethodmodifiers npp_sat_encode_sum2(NPP *npp, NPPLSE *set, NPPSED *sed) "
/**
 */
public";

%csmethodmodifiers npp_sat_encode_sum3(NPP *npp, NPPLSE *set, NPPSED *sed) "
/**
 */
public";

%csmethodmodifiers remove_lse(NPP *npp, NPPLSE *set, NPPCOL *col) "
/**
 */
public";

%csmethodmodifiers npp_sat_encode_sum_ax(NPP *npp, NPPROW *row, NPPLIT y[]) "
/**
 */
public";

%csmethodmodifiers npp_sat_normalize_clause(NPP *npp, int size, NPPLIT lit[]) "
/**
 */
public";

%csmethodmodifiers npp_sat_encode_clause(NPP *npp, int size, NPPLIT lit[]) "
/**
 */
public";

%csmethodmodifiers npp_sat_encode_geq(NPP *npp, int n, NPPLIT y[], int rhs) "
/**
 */
public";

%csmethodmodifiers npp_sat_encode_leq(NPP *npp, int n, NPPLIT y[], int rhs) "
/**
 */
public";

%csmethodmodifiers npp_sat_encode_row(NPP *npp, NPPROW *row) "
/**
 */
public";

%csmethodmodifiers npp_sat_encode_prob(NPP *npp) "
/**
 */
public";

%csmethodmodifiers check_fvs(int n, int nnz, int ind[], double vec[]) "
/**
 */
public";

%csmethodmodifiers check_pattern(int m, int n, int A_ptr[], int A_ind[]) "
/**
 */
public";

%csmethodmodifiers transpose(int m, int n, int A_ptr[], int A_ind[], double A_val[], int AT_ptr[], int AT_ind[], double AT_val[]) "
/**
 */
public";

%csmethodmodifiers adat_symbolic(int m, int n, int P_per[], int A_ptr[], int A_ind[], int S_ptr[]) "
/**
 */
public";

%csmethodmodifiers adat_numeric(int m, int n, int P_per[], int A_ptr[], int A_ind[], double A_val[], double D_diag[], int S_ptr[], int S_ind[], double S_val[], double S_diag[]) "
/**
 */
public";

%csmethodmodifiers min_degree(int n, int A_ptr[], int A_ind[], int P_per[]) "
/**
 */
public";

%csmethodmodifiers amd_order1(int n, int A_ptr[], int A_ind[], int P_per[]) "
/**
 */
public";

%csmethodmodifiers allocate(size_t n, size_t size) "
/**
 */
public";

%csmethodmodifiers release(void *ptr) "
/**
 */
public";

%csmethodmodifiers symamd_ord(int n, int A_ptr[], int A_ind[], int P_per[]) "
/**
 */
public";

%csmethodmodifiers chol_symbolic(int n, int A_ptr[], int A_ind[], int U_ptr[]) "
/**
 */
public";

%csmethodmodifiers chol_numeric(int n, int A_ptr[], int A_ind[], double A_val[], double A_diag[], int U_ptr[], int U_ind[], double U_val[], double U_diag[]) "
/**
 */
public";

%csmethodmodifiers u_solve(int n, int U_ptr[], int U_ind[], double U_val[], double U_diag[], double x[]) "
/**
 */
public";

%csmethodmodifiers ut_solve(int n, int U_ptr[], int U_ind[], double U_val[], double U_diag[], double x[]) "
/**
 */
public";

%csmethodmodifiers next_char(glp_data *data) "
/**
 */
public";

%csmethodmodifiers glp_sdf_open_file(const char *fname) "
/**
 */
public";

%csmethodmodifiers glp_sdf_set_jump(glp_data *data, void *jump) "
/**
 */
public";

%csmethodmodifiers glp_sdf_error(glp_data *data, const char *fmt,...) "
/**
 */
public";

%csmethodmodifiers glp_sdf_warning(glp_data *data, const char *fmt,...) "
/**
 */
public";

%csmethodmodifiers skip_pad(glp_data *data) "
/**
 */
public";

%csmethodmodifiers next_item(glp_data *data) "
/**
 */
public";

%csmethodmodifiers glp_sdf_read_int(glp_data *data) "
/**
 */
public";

%csmethodmodifiers glp_sdf_read_num(glp_data *data) "
/**
 */
public";

%csmethodmodifiers glp_sdf_read_item(glp_data *data) "
/**
 */
public";

%csmethodmodifiers glp_sdf_read_text(glp_data *data) "
/**
 */
public";

%csmethodmodifiers glp_sdf_line(glp_data *data) "
/**
 */
public";

%csmethodmodifiers glp_sdf_close_file(glp_data *data) "
/**
 */
public";

%csmethodmodifiers callback(glp_tree *tree, void *info) "
/**
 */
public";

%csmethodmodifiers get_info(struct csa *csa, glp_prob *lp) "
/**
 */
public";

%csmethodmodifiers is_integer(struct csa *csa) "
/**
 */
public";

%csmethodmodifiers check_integrality(struct csa *csa) "
/**
 */
public";

%csmethodmodifiers check_ref(struct csa *csa, glp_prob *lp, double *xref) "
/**
 */
public";

%csmethodmodifiers second(void) "
/**
 */
public";

%csmethodmodifiers add_cutoff(struct csa *csa, glp_prob *lp) "
/**
 */
public";

%csmethodmodifiers get_sol(struct csa *csa, glp_prob *lp, double *xstar) "
/**
 */
public";

%csmethodmodifiers elapsed_time(struct csa *csa) "
/**
 */
public";

%csmethodmodifiers redefine_obj(glp_prob *lp, double *xtilde, int ncols, int *ckind, double *clb, double *cub) "
/**
 */
public";

%csmethodmodifiers update_cutoff(struct csa *csa, glp_prob *lp, double zstar, int index, double rel_impr) "
/**
 */
public";

%csmethodmodifiers compute_delta(struct csa *csa, double z, double rel_impr) "
/**
 */
public";

%csmethodmodifiers objval(int ncols, double *x, double *true_obj) "
/**
 */
public";

%csmethodmodifiers array_copy(int begin, int end, double *source, double *destination) "
/**
 */
public";

%csmethodmodifiers do_refine(struct csa *csa, glp_prob *lp_ref, int ncols, int *ckind, double *xref, int *tlim, int tref_lim, int verbose) "
/**
 */
public";

%csmethodmodifiers deallocate(struct csa *csa, int refine) "
/**
 */
public";

%csmethodmodifiers proxy(glp_prob *lp, double *zfinal, double *xfinal, const double initsol[], double rel_impr, int tlim, int verbose) "
/**
 */
public";

%csmethodmodifiers AMD_info(double Info[]) "
/**
 */
public";

%csmethodmodifiers reduce_ineq_coef(NPP *npp, struct elem *ptr, double *_b) "
/**
 * npp_reduce_ineq_coef - reduce inequality constraint coefficients .
 * <p>SYNOPSIS</p>
 * <p>#include \"glpnpp.h\" int npp_reduce_ineq_coef(NPP *npp, NPPROW *row);</p>
 * <p>DESCRIPTION</p>
 * <p>The routine npp_reduce_ineq_coef processes specified inequality constraint attempting to replace it by an equivalent constraint, where magnitude of coefficients at binary variables is smaller than in the original constraint. If the inequality is double-sided, it is replaced by a pair of single-sided inequalities, if necessary.</p>
 * <p>RETURNS</p>
 * <p>The routine npp_reduce_ineq_coef returns the number of coefficients reduced.</p>
 * <p>BACKGROUND</p>
 * <p>Consider an inequality constraint:</p>
 * <p>sum a[j] x[j] &gt;= b. (1) j in J</p>
 * <p>(In case of '&lt;=' inequality it can be transformed to '>=' format by multiplying both its sides by -1.) Let x[k] be a binary variable; other variables can be integer as well as continuous. We can write constraint (1) as follows:</p>
 * <p>a[k] x[k] + t[k] &gt;= b, (2)</p>
 * <p>where:</p>
 * <p>t[k] = sum a[j] x[j]. (3) j in Jk}</p>
 * <p>Since x[k] is binary, constraint (2) is equivalent to disjunction of the following two constraints:</p>
 * <p>x[k] = 0, t[k] &gt;= b (4)</p>
 * <p>OR</p>
 * <p>x[k] = 1, t[k] &gt;= b - a[k]. (5)</p>
 * <p>Let also that for the partial sum t[k] be known some its implied lower bound inf t[k].</p>
 * <p>Case a[k] &gt; 0. Let inf t[k] &lt; b, since otherwise both constraints (4) and (5) and therefore constraint (2) are redundant. If inf t[k] &gt; b - a[k], only constraint (5) is redundant, in which case it can be replaced with the following redundant and therefore equivalent constraint:</p>
 * <p>t[k] &gt;= b - a'[k] = inf t[k], (6)</p>
 * <p>where:</p>
 * <p>a'[k] = b - inf t[k]. (7)</p>
 * <p>Thus, the original constraint (2) is equivalent to the following constraint with coefficient at variable x[k] changed:</p>
 * <p>a'[k] x[k] + t[k] &gt;= b. (8)</p>
 * <p>From inf t[k] &lt; b it follows that a'[k] &gt; 0, i.e. the coefficient at x[k] keeps its sign. And from inf t[k] &gt; b - a[k] it follows that a'[k] &lt; a[k], i.e. the coefficient reduces in magnitude.</p>
 * <p>Case a[k] &lt; 0. Let inf t[k] &lt; b - a[k], since otherwise both constraints (4) and (5) and therefore constraint (2) are redundant. If inf t[k] &gt; b, only constraint (4) is redundant, in which case it can be replaced with the following redundant and therefore equivalent constraint:</p>
 * <p>t[k] &gt;= b' = inf t[k]. (9)</p>
 * <p>Rewriting constraint (5) as follows:</p>
 * <p>t[k] &gt;= b - a[k] = b' - a'[k], (10)</p>
 * <p>where:</p>
 * <p>a'[k] = a[k] + b' - b = a[k] + inf t[k] - b, (11)</p>
 * <p>we can see that disjunction of constraint (9) and (10) is equivalent to disjunction of constraint (4) and (5), from which it follows that the original constraint (2) is equivalent to the following constraint with both coefficient at variable x[k] and right-hand side changed:</p>
 * <p>a'[k] x[k] + t[k] &gt;= b'. (12)</p>
 * <p>From inf t[k] &lt; b - a[k] it follows that a'[k] &lt; 0, i.e. the coefficient at x[k] keeps its sign. And from inf t[k] &gt; b it follows that a'[k] &gt; a[k], i.e. the coefficient reduces in magnitude.</p>
 * <p>PROBLEM TRANSFORMATION</p>
 * <p>In the routine npp_reduce_ineq_coef the following implied lower bound of the partial sum (3) is used:</p>
 * <p>inf t[k] = sum a[j] l[j] + sum a[j] u[j], (13) j in Jpk} k in Jnk}</p>
 * <p>where Jp = {j : a[j] &gt; 0}, Jn = {j : a[j] &lt; 0}, l[j] and u[j] are lower and upper bounds, resp., of variable x[j].</p>
 * <p>In order to compute inf t[k] more efficiently, the following formula, which is equivalent to (13), is actually used:           ( h - a[k] l[k] = h,        if a[k] &gt; 0,
 inf t[k] = &lt; (14) ( h - a[k] u[k] = h - a[k], if a[k] &lt; 0,</p>
 * <p>where:</p>
 * <p>h = sum a[j] l[j] + sum a[j] u[j] (15) j in Jp j in Jn</p>
 * <p>is the implied lower bound of row (1).</p>
 * <p>Reduction of positive coefficient (a[k] &gt; 0) does not change value of h, since l[k] = 0. In case of reduction of negative coefficient (a[k] &lt; 0) from (11) it follows that:</p>
 * <p>delta a[k] = a'[k] - a[k] = inf t[k] - b (> 0), (16)</p>
 * <p>so new value of h (accounting that u[k] = 1) can be computed as follows:</p>
 * <p>h := h + delta a[k] = h + (inf t[k] - b). (17)</p>
 * <p>RECOVERING SOLUTION</p>
 * <p>None needed. </p>
 */
public";

%csmethodmodifiers npp_reduce_ineq_coef(NPP *npp, NPPROW *row) "
/**
 */
public";

%csmethodmodifiers rcv_binarize_prob(NPP *npp, void *info) "
/**
 */
public";

%csmethodmodifiers npp_binarize_prob(NPP *npp) "
/**
 */
public";

%csmethodmodifiers copy_form(NPP *npp, NPPROW *row, double s) "
/**
 */
public";

%csmethodmodifiers drop_form(NPP *npp, struct elem *ptr) "
/**
 */
public";

%csmethodmodifiers npp_is_packing(NPP *npp, NPPROW *row) "
/**
 * npp_is_packing - test if constraint is packing inequality .
 * <p>SYNOPSIS</p>
 * <p>#include \"glpnpp.h\" int npp_is_packing(NPP *npp, NPPROW *row);</p>
 * <p>RETURNS</p>
 * <p>If the specified row (constraint) is packing inequality (see below), the routine npp_is_packing returns non-zero. Otherwise, it returns zero.</p>
 * <p>PACKING INEQUALITIES</p>
 * <p>In canonical format the packing inequality is the following:</p>
 * <p>sum x[j] &lt;= 1, (1) j in J</p>
 * <p>where all variables x[j] are binary. This inequality expresses the condition that in any integer feasible solution at most one variable from set J can take non-zero (unity) value while other variables must be equal to zero. W.l.o.g. it is assumed that |J| &gt;= 2, because if J is empty or |J| = 1, the inequality (1) is redundant.</p>
 * <p>In general case the packing inequality may include original variables x[j] as well as their complements x~[j]:</p>
 * <p>sum x[j] + sum x~[j] &lt;= 1, (2) j in Jp j in Jn</p>
 * <p>where Jp and Jn are not intersected. Therefore, using substitution x~[j] = 1 - x[j] gives the packing inequality in generalized format:</p>
 * <p>sum x[j] - sum x[j] &lt;= 1 - |Jn|. (3) j in Jp j in Jn </p>
 */
public";

%csmethodmodifiers hidden_packing(NPP *npp, struct elem *ptr, double *_b) "
/**
 * npp_hidden_packing - identify hidden packing inequality .
 * <p>SYNOPSIS</p>
 * <p>#include \"glpnpp.h\" int npp_hidden_packing(NPP *npp, NPPROW *row);</p>
 * <p>DESCRIPTION</p>
 * <p>The routine npp_hidden_packing processes specified inequality constraint, which includes only binary variables, and the number of the variables is not less than two. If the original inequality is equivalent to a packing inequality, the routine replaces it by this equivalent inequality. If the original constraint is double-sided inequality, it is replaced by a pair of single-sided inequalities, if necessary.</p>
 * <p>RETURNS</p>
 * <p>If the original inequality constraint was replaced by equivalent packing inequality, the routine npp_hidden_packing returns non-zero. Otherwise, it returns zero.</p>
 * <p>PROBLEM TRANSFORMATION</p>
 * <p>Consider an inequality constraint:</p>
 * <p>sum a[j] x[j] &lt;= b, (1) j in J</p>
 * <p>where all variables x[j] are binary, and |J| &gt;= 2. (In case of '>=' inequality it can be transformed to '&lt;=' format by multiplying both its sides by -1.)</p>
 * <p>Let Jp = {j: a[j] &gt; 0}, Jn = {j: a[j] &lt; 0}. Performing substitution x[j] = 1 - x~[j] for all j in Jn, we have:</p>
 * <p>sum a[j] x[j] &lt;= b ==> j in J</p>
 * <p>sum a[j] x[j] + sum a[j] x[j] &lt;= b ==> j in Jp j in Jn</p>
 * <p>sum a[j] x[j] + sum a[j] (1 - x~[j]) &lt;= b ==> j in Jp j in Jn</p>
 * <p>sum a[j] x[j] - sum a[j] x~[j] &lt;= b - sum a[j]. j in Jp j in Jn j in Jn</p>
 * <p>Thus, meaning the transformation above, we can assume that in inequality (1) all coefficients a[j] are positive. Moreover, we can assume that a[j] &lt;= b. In fact, let a[j] &gt; b; then the following three cases are possible:</p>
 * <p>1) b &lt; 0. In this case inequality (1) is infeasible, so the problem has no feasible solution (see the routine npp_analyze_row);</p>
 * <p>2) b = 0. In this case inequality (1) is a forcing inequality on its upper bound (see the routine npp_forcing row), from which it follows that all variables x[j] should be fixed at zero;</p>
 * <p>3) b &gt; 0. In this case inequality (1) defines an implied zero upper bound for variable x[j] (see the routine npp_implied_bounds), from which it follows that x[j] should be fixed at zero.</p>
 * <p>It is assumed that all three cases listed above have been recognized by the routine npp_process_prob, which performs basic MIP processing prior to a call the routine npp_hidden_packing. So, if one of these cases occurs, we should just skip processing such constraint.</p>
 * <p>Thus, let 0 &lt; a[j] &lt;= b. Then it is obvious that constraint (1) is equivalent to packing inquality only if:</p>
 * <p>a[j] + a[k] &gt; b + eps (2)</p>
 * <p>for all j, k in J, j != k, where eps is an absolute tolerance for row (linear form) value. Checking the condition (2) for all j and k, j != k, requires time O(|J|^2). However, this time can be reduced to O(|J|), if use minimal a[j] and a[k], in which case it is sufficient to check the condition (2) only once.</p>
 * <p>Once the original inequality (1) is replaced by equivalent packing inequality, we need to perform back substitution x~[j] = 1 - x[j] for all j in Jn (see above).</p>
 * <p>RECOVERING SOLUTION</p>
 * <p>None needed. </p>
 */
public";

%csmethodmodifiers npp_hidden_packing(NPP *npp, NPPROW *row) "
/**
 */
public";

%csmethodmodifiers npp_implied_packing(NPP *npp, NPPROW *row, int which, NPPCOL *var[], char set[]) "
/**
 * npp_implied_packing - identify implied packing inequality .
 * <p>SYNOPSIS</p>
 * <p>#include \"glpnpp.h\" int npp_implied_packing(NPP *npp, NPPROW *row, int which, NPPCOL *var[], char set[]);</p>
 * <p>DESCRIPTION</p>
 * <p>The routine npp_implied_packing processes specified row (constraint) of general format:</p>
 * <p>L &lt;= sum a[j] x[j] &lt;= U. (1) j</p>
 * <p>If which = 0, only lower bound L, which must exist, is considered, while upper bound U is ignored. Similarly, if which = 1, only upper bound U, which must exist, is considered, while lower bound L is ignored. Thus, if the specified row is a double-sided inequality or equality constraint, this routine should be called twice for both lower and upper bounds.</p>
 * <p>The routine npp_implied_packing attempts to find a non-trivial (i.e. having not less than two binary variables) packing inequality:</p>
 * <p>sum x[j] - sum x[j] &lt;= 1 - |Jn|, (2) j in Jp j in Jn</p>
 * <p>which is relaxation of the constraint (1) in the sense that any solution satisfying to that constraint also satisfies to the packing inequality (2). If such relaxation exists, the routine stores pointers to descriptors of corresponding binary variables and their flags, resp., to locations var[1], var[2], ..., var[len] and set[1], set[2], ..., set[len], where set[j] = 0 means that j in Jp and set[j] = 1 means that j in Jn.</p>
 * <p>RETURNS</p>
 * <p>The routine npp_implied_packing returns len, which is the total number of binary variables in the packing inequality found, len &gt;= 2. However, if the relaxation does not exist, the routine returns zero.</p>
 * <p>ALGORITHM</p>
 * <p>If which = 0, the constraint coefficients (1) are multiplied by -1 and b is assigned -L; if which = 1, the constraint coefficients (1) are not changed and b is assigned +U. In both cases the specified constraint gets the following format:</p>
 * <p>sum a[j] x[j] &lt;= b. (3) j</p>
 * <p>(Note that (3) is a relaxation of (1), because one of bounds L or U is ignored.)</p>
 * <p>Let J be set of binary variables, Kp be set of non-binary (integer or continuous) variables with a[j] &gt; 0, and Kn be set of non-binary variables with a[j] &lt; 0. Then the inequality (3) can be written as follows:</p>
 * <p>sum a[j] x[j] &lt;= b - sum a[j] x[j] - sum a[j] x[j]. (4) j in J j in Kp j in Kn</p>
 * <p>To get rid of non-binary variables we can replace the inequality (4) by the following relaxed inequality:</p>
 * <p>sum a[j] x[j] &lt;= b~, (5) j in J</p>
 * <p>where:</p>
 * <p>b~ = sup(b - sum a[j] x[j] - sum a[j] x[j]) = j in Kp j in Kn</p>
 * <p>= b - inf sum a[j] x[j] - inf sum a[j] x[j] = (6) j in Kp j in Kn</p>
 * <p>= b - sum a[j] l[j] - sum a[j] u[j]. j in Kp j in Kn</p>
 * <p>Note that if lower bound l[j] (if j in Kp) or upper bound u[j] (if j in Kn) of some non-binary variable x[j] does not exist, then formally b = +oo, in which case further analysis is not performed.</p>
 * <p>Let Bp = {j in J: a[j] &gt; 0}, Bn = {j in J: a[j] &lt; 0}. To make all the inequality coefficients in (5) positive, we replace all x[j] in Bn by their complementaries, substituting x[j] = 1 - x~[j] for all j in Bn, that gives:</p>
 * <p>sum a[j] x[j] - sum a[j] x~[j] &lt;= b~ - sum a[j]. (7) j in Bp j in Bn j in Bn</p>
 * <p>This inequality is a relaxation of the original constraint (1), and it is a binary knapsack inequality. Writing it in the standard format we have:</p>
 * <p>sum alfa[j] z[j] &lt;= beta, (8) j in J</p>
 * <p>where: ( + a[j], if j in Bp, alfa[j] = &lt; (9) ( - a[j], if j in Bn,</p>
 * <p>( x[j], if j in Bp, z[j] = &lt; (10) ( 1 - x[j], if j in Bn,</p>
 * <p>beta = b~ - sum a[j]. (11) j in Bn</p>
 * <p>In the inequality (8) all coefficients are positive, therefore, the packing relaxation to be found for this inequality is the following:</p>
 * <p>sum z[j] &lt;= 1. (12) j in P</p>
 * <p>It is obvious that set P within J, which we would like to find, must satisfy to the following condition:</p>
 * <p>alfa[j] + alfa[k] &gt; beta + eps for all j, k in P, j != k, (13)</p>
 * <p>where eps is an absolute tolerance for value of the linear form. Thus, it is natural to take P = {j: alpha[j] &gt; (beta + eps) / 2}. Moreover, if in the equality (8) there exist coefficients alfa[k], for which alfa[k] &lt;= (beta + eps) / 2, but which, nevertheless, satisfies to the condition (13) for all j in P, one corresponding variable z[k] (having, for example, maximal coefficient alfa[k]) can be included in set P, that allows increasing the number of binary variables in (12) by one.</p>
 * <p>Once the set P has been built, for the inequality (12) we need to perform back substitution according to (10) in order to express it through the original binary variables. As the result of such back substitution the relaxed packing inequality get its final format (2), where Jp = J intersect Bp, and Jn = J intersect Bn. </p>
 */
public";

%csmethodmodifiers npp_is_covering(NPP *npp, NPPROW *row) "
/**
 * npp_is_covering - test if constraint is covering inequality .
 * <p>SYNOPSIS</p>
 * <p>#include \"glpnpp.h\" int npp_is_covering(NPP *npp, NPPROW *row);</p>
 * <p>RETURNS</p>
 * <p>If the specified row (constraint) is covering inequality (see below), the routine npp_is_covering returns non-zero. Otherwise, it returns zero.</p>
 * <p>COVERING INEQUALITIES</p>
 * <p>In canonical format the covering inequality is the following:</p>
 * <p>sum x[j] &gt;= 1, (1) j in J</p>
 * <p>where all variables x[j] are binary. This inequality expresses the condition that in any integer feasible solution variables in set J cannot be all equal to zero at the same time, i.e. at least one variable must take non-zero (unity) value. W.l.o.g. it is assumed that |J| &gt;= 2, because if J is empty, the inequality (1) is infeasible, and if |J| = 1, the inequality (1) is a forcing row.</p>
 * <p>In general case the covering inequality may include original variables x[j] as well as their complements x~[j]:</p>
 * <p>sum x[j] + sum x~[j] &gt;= 1, (2) j in Jp j in Jn</p>
 * <p>where Jp and Jn are not intersected. Therefore, using substitution x~[j] = 1 - x[j] gives the packing inequality in generalized format:</p>
 * <p>sum x[j] - sum x[j] &gt;= 1 - |Jn|. (3) j in Jp j in Jn</p>
 * <p>(May note that the inequality (3) cuts off infeasible solutions, where x[j] = 0 for all j in Jp and x[j] = 1 for all j in Jn.)</p>
 * <p>NOTE: If |J| = 2, the inequality (3) is equivalent to packing inequality (see the routine npp_is_packing). </p>
 */
public";

%csmethodmodifiers hidden_covering(NPP *npp, struct elem *ptr, double *_b) "
/**
 * npp_hidden_covering - identify hidden covering inequality .
 * <p>SYNOPSIS</p>
 * <p>#include \"glpnpp.h\" int npp_hidden_covering(NPP *npp, NPPROW *row);</p>
 * <p>DESCRIPTION</p>
 * <p>The routine npp_hidden_covering processes specified inequality constraint, which includes only binary variables, and the number of the variables is not less than three. If the original inequality is equivalent to a covering inequality (see below), the routine replaces it by the equivalent inequality. If the original constraint is double-sided inequality, it is replaced by a pair of single-sided inequalities, if necessary.</p>
 * <p>RETURNS</p>
 * <p>If the original inequality constraint was replaced by equivalent covering inequality, the routine npp_hidden_covering returns non-zero. Otherwise, it returns zero.</p>
 * <p>PROBLEM TRANSFORMATION</p>
 * <p>Consider an inequality constraint:</p>
 * <p>sum a[j] x[j] &gt;= b, (1) j in J</p>
 * <p>where all variables x[j] are binary, and |J| &gt;= 3. (In case of '&lt;=' inequality it can be transformed to '>=' format by multiplying both its sides by -1.)</p>
 * <p>Let Jp = {j: a[j] &gt; 0}, Jn = {j: a[j] &lt; 0}. Performing substitution x[j] = 1 - x~[j] for all j in Jn, we have:</p>
 * <p>sum a[j] x[j] &gt;= b ==> j in J</p>
 * <p>sum a[j] x[j] + sum a[j] x[j] &gt;= b ==> j in Jp j in Jn</p>
 * <p>sum a[j] x[j] + sum a[j] (1 - x~[j]) &gt;= b ==> j in Jp j in Jn</p>
 * <p>sum m a[j] x[j] - sum a[j] x~[j] &gt;= b - sum a[j]. j in Jp j in Jn j in Jn</p>
 * <p>Thus, meaning the transformation above, we can assume that in inequality (1) all coefficients a[j] are positive. Moreover, we can assume that b &gt; 0, because otherwise the inequality (1) would be redundant (see the routine npp_analyze_row). It is then obvious that constraint (1) is equivalent to covering inequality only if:</p>
 * <p>a[j] &gt;= b, (2)</p>
 * <p>for all j in J.</p>
 * <p>Once the original inequality (1) is replaced by equivalent covering inequality, we need to perform back substitution x~[j] = 1 - x[j] for all j in Jn (see above).</p>
 * <p>RECOVERING SOLUTION</p>
 * <p>None needed. </p>
 */
public";

%csmethodmodifiers npp_hidden_covering(NPP *npp, NPPROW *row) "
/**
 */
public";

%csmethodmodifiers npp_is_partitioning(NPP *npp, NPPROW *row) "
/**
 * npp_is_partitioning - test if constraint is partitioning equality .
 * <p>SYNOPSIS</p>
 * <p>#include \"glpnpp.h\" int npp_is_partitioning(NPP *npp, NPPROW *row);</p>
 * <p>RETURNS</p>
 * <p>If the specified row (constraint) is partitioning equality (see below), the routine npp_is_partitioning returns non-zero. Otherwise, it returns zero.</p>
 * <p>PARTITIONING EQUALITIES</p>
 * <p>In canonical format the partitioning equality is the following:</p>
 * <p>sum x[j] = 1, (1) j in J</p>
 * <p>where all variables x[j] are binary. This equality expresses the condition that in any integer feasible solution exactly one variable in set J must take non-zero (unity) value while other variables must be equal to zero. W.l.o.g. it is assumed that |J| &gt;= 2, because if J is empty, the inequality (1) is infeasible, and if |J| = 1, the inequality (1) is a fixing row.</p>
 * <p>In general case the partitioning equality may include original variables x[j] as well as their complements x~[j]:</p>
 * <p>sum x[j] + sum x~[j] = 1, (2) j in Jp j in Jn</p>
 * <p>where Jp and Jn are not intersected. Therefore, using substitution x~[j] = 1 - x[j] leads to the partitioning equality in generalized format:</p>
 * <p>sum x[j] - sum x[j] = 1 - |Jn|. (3) j in Jp j in Jn </p>
 */
public";

%csmethodmodifiers gz_load(gz_statep state, unsigned char *buf, unsigned len, unsigned *have) "
/**
 */
public";

%csmethodmodifiers gz_avail(gz_statep state) "
/**
 */
public";

%csmethodmodifiers gz_next4(gz_statep state, unsigned long *ret) "
/**
 */
public";

%csmethodmodifiers gz_head(gz_statep state) "
/**
 */
public";

%csmethodmodifiers gz_decomp(gz_statep state) "
/**
 */
public";

%csmethodmodifiers gz_make(gz_statep state) "
/**
 */
public";

%csmethodmodifiers gz_skip(gz_statep state, z_off64_t len) "
/**
 */
public";

%csmethodmodifiers gzread(gzFile file, voidp buf, unsigned len) "
/**
 */
public";

%csmethodmodifiers gzgetc(gzFile file) "
/**
 */
public";

%csmethodmodifiers gzungetc(int c, gzFile file) "
/**
 */
public";

%csmethodmodifiers gzgets(gzFile file, char *buf, int len) "
/**
 */
public";

%csmethodmodifiers gzdirect(gzFile file) "
/**
 */
public";

%csmethodmodifiers gzclose_r(gzFile file) "
/**
 */
public";

%csmethodmodifiers set_edge(int nv, unsigned char a[], int i, int j) "
/**
 */
public";

%csmethodmodifiers glp_wclique_exact(glp_graph *G, int v_wgt, double *sol, int v_set) "
/**
 */
public";

%csmethodmodifiers initialize(struct csa *csa) "
/**
 */
public";

%csmethodmodifiers A_by_vec(struct csa *csa, double x[], double y[]) "
/**
 */
public";

%csmethodmodifiers AT_by_vec(struct csa *csa, double x[], double y[]) "
/**
 */
public";

%csmethodmodifiers decomp_NE(struct csa *csa) "
/**
 */
public";

%csmethodmodifiers solve_NE(struct csa *csa, double y[]) "
/**
 */
public";

%csmethodmodifiers solve_NS(struct csa *csa, double p[], double q[], double r[], double dx[], double dy[], double dz[]) "
/**
 */
public";

%csmethodmodifiers initial_point(struct csa *csa) "
/**
 */
public";

%csmethodmodifiers basic_info(struct csa *csa) "
/**
 */
public";

%csmethodmodifiers make_step(struct csa *csa) "
/**
 */
public";

%csmethodmodifiers terminate(struct csa *csa) "
/**
 */
public";

%csmethodmodifiers ipm_main(struct csa *csa) "
/**
 */
public";

%csmethodmodifiers ipm_solve(glp_prob *P, const glp_iptcp *parm) "
/**
 * ipm_solve - core LP solver based on the interior-point method .
 * <p>SYNOPSIS</p>
 * <p>#include \"glpipm.h\" int ipm_solve(glp_prob *P, const glp_iptcp *parm);</p>
 * <p>DESCRIPTION</p>
 * <p>The routine ipm_solve is a core LP solver based on the primal-dual interior-point method.</p>
 * <p>The routine assumes the following standard formulation of LP problem to be solved:</p>
 * <p>minimize</p>
 * <p>F = c[0] + c[1]*x[1] + c[2]*x[2] + ... + c[n]*x[n]</p>
 * <p>subject to linear constraints</p>
 * <p>a[1,1]*x[1] + a[1,2]*x[2] + ... + a[1,n]*x[n] = b[1]</p>
 * <p>a[2,1]*x[1] + a[2,2]*x[2] + ... + a[2,n]*x[n] = b[2]   . . . . . .
</p>
 * <p>a[m,1]*x[1] + a[m,2]*x[2] + ... + a[m,n]*x[n] = b[m]</p>
 * <p>and non-negative variables</p>
 * <p>x[1] &gt;= 0, x[2] &gt;= 0, ..., x[n] &gt;= 0</p>
 * <p>where: F is the objective function; x[1], ..., x[n] are (structural) variables; c[0] is a constant term of the objective function; c[1], ..., c[n] are objective coefficients; a[1,1], ..., a[m,n] are constraint coefficients; b[1], ..., b[n] are right-hand sides.</p>
 * <p>The solution is three vectors x, y, and z, which are stored by the routine in the arrays x, y, and z, respectively. These vectors correspond to the best primal-dual point found during optimization. They are approximate solution of the following system (which is the Karush-Kuhn-Tucker optimality conditions):</p>
 * <p>A*x = b (primal feasibility condition)</p>
 * <p>A'*y + z = c (dual feasibility condition)</p>
 * <p>x'*z = 0 (primal-dual complementarity condition)</p>
 * <p>x &gt;= 0, z &gt;= 0 (non-negativity condition)</p>
 * <p>where: x[1], ..., x[n] are primal (structural) variables; y[1], ..., y[m] are dual variables (Lagrange multipliers) for equality constraints; z[1], ..., z[n] are dual variables (Lagrange multipliers) for non-negativity constraints.</p>
 * <p>RETURNS</p>
 * <p>0 LP has been successfully solved.</p>
 * <p>GLP_ENOCVG No convergence.</p>
 * <p>GLP_EITLIM Iteration limit exceeded.</p>
 * <p>GLP_EINSTAB Numeric instability on solving Newtonian system.</p>
 * <p>In case of non-zero return code the routine returns the best point, which has been reached during optimization. </p>
 */
public";

%csmethodmodifiers fcmp(const void *arg1, const void *arg2) "
/**
 */
public";

%csmethodmodifiers parallel(IOSCUT *a, IOSCUT *b, double work[]) "
/**
 */
public";

%csmethodmodifiers ios_process_cuts(glp_tree *T) "
/**
 */
public";

%csmethodmodifiers fhvint_create(void) "
/**
 */
public";

%csmethodmodifiers fhvint_factorize(FHVINT *fi, int n, int(*col)(void *info, int j, int ind[], double val[]), void *info) "
/**
 */
public";

%csmethodmodifiers fhvint_update(FHVINT *fi, int j, int len, const int ind[], const double val[]) "
/**
 */
public";

%csmethodmodifiers fhvint_ftran(FHVINT *fi, double x[]) "
/**
 */
public";

%csmethodmodifiers fhvint_btran(FHVINT *fi, double x[]) "
/**
 */
public";

%csmethodmodifiers fhvint_estimate(FHVINT *fi) "
/**
 */
public";

%csmethodmodifiers fhvint_delete(FHVINT *fi) "
/**
 */
public";

%csmethodmodifiers mat(void *info, int k, int ind[], double val[]) "
/**
 * glp_adv_basis - construct advanced initial LP basis .
 * <p>SYNOPSIS</p>
 * <p>void glp_adv_basis(glp_prob *P, int flags);</p>
 * <p>DESCRIPTION</p>
 * <p>The routine glp_adv_basis constructs an advanced initial LP basis for the specified problem object.</p>
 * <p>The parameter flag is reserved for use in the future and should be specified as zero.</p>
 * <p>NOTE</p>
 * <p>The routine glp_adv_basis should be called after the constraint matrix has been scaled (if scaling is used). </p>
 */
public";

%csmethodmodifiers glp_adv_basis(glp_prob *P, int flags) "
/**
 */
public";

%csmethodmodifiers genqmd(int *_neqns, int xadj[], int adjncy[], int perm[], int invp[], int deg[], int marker[], int rchset[], int nbrhd[], int qsize[], int qlink[], int *_nofsub) "
/**
 * genqmd - GENeral Quotient Minimum Degree algorithm .
 * <p>SYNOPSIS</p>
 * <p>#include \"qmd.h\" void genqmd(int *neqns, int xadj[], int adjncy[], int perm[], int invp[], int deg[], int marker[], int rchset[], int nbrhd[], int qsize[], int qlink[], int *nofsub);</p>
 * <p>PURPOSE</p>
 * <p>This routine implements the minimum degree algorithm. It makes use of the implicit representation of the elimination graph by quotient graphs, and the notion of indistinguishable nodes.</p>
 * <p>CAUTION</p>
 * <p>The adjancy vector adjncy will be destroyed.</p>
 * <p>INPUT PARAMETERS</p>
 * <p>neqns - number of equations; (xadj, adjncy) - the adjancy structure.</p>
 * <p>OUTPUT PARAMETERS</p>
 * <p>perm - the minimum degree ordering; invp - the inverse of perm.</p>
 * <p>WORKING PARAMETERS</p>
 * <p>deg - the degree vector. deg[i] is negative means node i has been numbered; marker - a marker vector, where marker[i] is negative means node i has been merged with another nodeand thus can be ignored; rchset - vector used for the reachable set; nbrhd - vector used for neighborhood set; qsize - vector used to store the size of indistinguishable supernodes; qlink - vector used to store indistinguishable nodes, i, qlink[i], qlink[qlink[i]], ... are the members of the supernode represented by i.</p>
 * <p>PROGRAM SUBROUTINES</p>
 * <p>qmdrch, qmdqt, qmdupd. </p>
 */
public";

%csmethodmodifiers qmdrch(int *_root, int xadj[], int adjncy[], int deg[], int marker[], int *_rchsze, int rchset[], int *_nhdsze, int nbrhd[]) "
/**
 * qmdrch - Quotient MD ReaCHable set .
 * <p>SYNOPSIS</p>
 * <p>#include \"qmd.h\" void qmdrch(int *root, int xadj[], int adjncy[], int deg[], int marker[], int *rchsze, int rchset[], int *nhdsze, int nbrhd[]);</p>
 * <p>PURPOSE</p>
 * <p>This subroutine determines the reachable set of a node through a given subset. The adjancy structure is assumed to be stored in a quotient graph format.</p>
 * <p>INPUT PARAMETERS</p>
 * <p>root - the given node not in the subset; (xadj, adjncy) - the adjancy structure pair; deg - the degree vector. deg[i] &lt; 0 means the node belongs to the given subset.</p>
 * <p>OUTPUT PARAMETERS</p>
 * <p>(rchsze, rchset) - the reachable set; (nhdsze, nbrhd) - the neighborhood set.</p>
 * <p>UPDATED PARAMETERS</p>
 * <p>marker - the marker vector for reach and nbrhd sets. &gt; 0 means the node is in reach set. &lt; 0 means the node has been merged with others in the quotient or it is in nbrhd set. </p>
 */
public";

%csmethodmodifiers qmdqt(int *_root, int xadj[], int adjncy[], int marker[], int *_rchsze, int rchset[], int nbrhd[]) "
/**
 * qmdqt - Quotient MD Quotient graph Transformation .
 * <p>SYNOPSIS</p>
 * <p>#include \"qmd.h\" void qmdqt(int *root, int xadj[], int adjncy[], int marker[], int *rchsze, int rchset[], int nbrhd[]);</p>
 * <p>PURPOSE</p>
 * <p>This subroutine performs the quotient graph transformation after a node has been eliminated.</p>
 * <p>INPUT PARAMETERS</p>
 * <p>root - the node just eliminated. It becomes the representative of the new supernode; (xadj, adjncy) - the adjancy structure; (rchsze, rchset) - the reachable set of root in the old quotient graph; nbrhd - the neighborhood set which will be merged with root to form the new supernode; marker - the marker vector.</p>
 * <p>UPDATED PARAMETERS</p>
 * <p>adjncy - becomes the adjncy of the quotient graph. </p>
 */
public";

%csmethodmodifiers qmdupd(int xadj[], int adjncy[], int *_nlist, int list[], int deg[], int qsize[], int qlink[], int marker[], int rchset[], int nbrhd[]) "
/**
 * qmdupd - Quotient MD UPDate .
 * <p>SYNOPSIS</p>
 * <p>#include \"qmd.h\" void qmdupd(int xadj[], int adjncy[], int *nlist, int list[], int deg[], int qsize[], int qlink[], int marker[], int rchset[], int nbrhd[]);</p>
 * <p>PURPOSE</p>
 * <p>This routine performs degree update for a set of nodes in the minimum degree algorithm.</p>
 * <p>INPUT PARAMETERS</p>
 * <p>(xadj, adjncy) - the adjancy structure; (nlist, list) - the list of nodes whose degree has to be updated.</p>
 * <p>UPDATED PARAMETERS</p>
 * <p>deg - the degree vector; qsize - size of indistinguishable supernodes; qlink - linked list for indistinguishable nodes; marker - used to mark those nodes in reach/nbrhd sets.</p>
 * <p>WORKING PARAMETERS</p>
 * <p>rchset - the reachable set; nbrhd - the neighborhood set.</p>
 * <p>PROGRAM SUBROUTINES</p>
 * <p>qmdmrg. </p>
 */
public";

%csmethodmodifiers qmdmrg(int xadj[], int adjncy[], int deg[], int qsize[], int qlink[], int marker[], int *_deg0, int *_nhdsze, int nbrhd[], int rchset[], int ovrlp[]) "
/**
 * qmdmrg - Quotient MD MeRGe .
 * <p>SYNOPSIS</p>
 * <p>#include \"qmd.h\" void qmdmrg(int xadj[], int adjncy[], int deg[], int qsize[], int qlink[], int marker[], int *deg0, int *nhdsze, int nbrhd[], int rchset[], int ovrlp[]);</p>
 * <p>PURPOSE</p>
 * <p>This routine merges indistinguishable nodes in the minimum degree ordering algorithm. It also computes the new degrees of these new supernodes.</p>
 * <p>INPUT PARAMETERS</p>
 * <p>(xadj, adjncy) - the adjancy structure; deg0 - the number of nodes in the given set; (nhdsze, nbrhd) - the set of eliminated supernodes adjacent to some nodes in the set.</p>
 * <p>UPDATED PARAMETERS</p>
 * <p>deg - the degree vector; qsize - size of indistinguishable nodes; qlink - linked list for indistinguishable nodes; marker - the given set is given by those nodes with marker value set to 1. Those nodes with degree updated will have marker value set to 2.</p>
 * <p>WORKING PARAMETERS</p>
 * <p>rchset - the reachable set; ovrlp - temp vector to store the intersection of two reachable sets. </p>
 */
public";

%csmethodmodifiers AMD_valid(Int n_row, Int n_col, const Int Ap[], const Int Ai[]) "
/**
 */
public";

%csmethodmodifiers luf_store_v_cols(LUF *luf, int(*col)(void *info, int j, int ind[], double val[]), void *info, int ind[], double val[]) "
/**
 */
public";

%csmethodmodifiers luf_check_all(LUF *luf, int k) "
/**
 */
public";

%csmethodmodifiers luf_build_v_rows(LUF *luf, int len[]) "
/**
 */
public";

%csmethodmodifiers luf_build_f_rows(LUF *luf, int len[]) "
/**
 */
public";

%csmethodmodifiers luf_build_v_cols(LUF *luf, int updat, int len[]) "
/**
 */
public";

%csmethodmodifiers luf_check_f_rc(LUF *luf) "
/**
 */
public";

%csmethodmodifiers luf_check_v_rc(LUF *luf) "
/**
 */
public";

%csmethodmodifiers luf_f_solve(LUF *luf, double x[]) "
/**
 */
public";

%csmethodmodifiers luf_ft_solve(LUF *luf, double x[]) "
/**
 */
public";

%csmethodmodifiers luf_v_solve(LUF *luf, double b[], double x[]) "
/**
 */
public";

%csmethodmodifiers luf_vt_solve(LUF *luf, double b[], double x[]) "
/**
 */
public";

%csmethodmodifiers luf_vt_solve1(LUF *luf, double e[], double y[]) "
/**
 */
public";

%csmethodmodifiers luf_estimate_norm(LUF *luf, double w1[], double w2[]) "
/**
 */
public";

%csmethodmodifiers glp_print_sol(glp_prob *P, const char *fname) "
/**
 */
public";

%csmethodmodifiers glp_read_sol(glp_prob *lp, const char *fname) "
/**
 * glp_read_sol - read basic solution from text file .
 * <p>SYNOPSIS</p>
 * <p>int glp_read_sol(glp_prob *lp, const char *fname);</p>
 * <p>DESCRIPTION</p>
 * <p>The routine glp_read_sol reads basic solution from a text file whose name is specified by the parameter fname into the problem object.</p>
 * <p>For the file format see description of the routine glp_write_sol.</p>
 * <p>RETURNS</p>
 * <p>On success the routine returns zero, otherwise non-zero. </p>
 */
public";

%csmethodmodifiers glp_write_sol(glp_prob *lp, const char *fname) "
/**
 * glp_write_sol - write basic solution to text file .
 * <p>SYNOPSIS</p>
 * <p>int glp_write_sol(glp_prob *lp, const char *fname);</p>
 * <p>DESCRIPTION</p>
 * <p>The routine glp_write_sol writes the current basic solution to a text file whose name is specified by the parameter fname. This file can be read back with the routine glp_read_sol.</p>
 * <p>RETURNS</p>
 * <p>On success the routine returns zero, otherwise non-zero.</p>
 * <p>FILE FORMAT</p>
 * <p>The file created by the routine glp_write_sol is a plain text file, which contains the following information:</p>
 * <p>m n p_stat d_stat obj_val r_stat[1] r_prim[1] r_dual[1] . . . r_stat[m] r_prim[m] r_dual[m] c_stat[1] c_prim[1] c_dual[1] . . . c_stat[n] c_prim[n] c_dual[n]</p>
 * <p>where: m is the number of rows (auxiliary variables); n is the number of columns (structural variables); p_stat is the primal status of the basic solution (GLP_UNDEF = 1, GLP_FEAS = 2, GLP_INFEAS = 3, or GLP_NOFEAS = 4); d_stat is the dual status of the basic solution (GLP_UNDEF = 1, GLP_FEAS = 2, GLP_INFEAS = 3, or GLP_NOFEAS = 4); obj_val is the objective value; r_stat[i], i = 1,...,m, is the status of i-th row (GLP_BS = 1, GLP_NL = 2, GLP_NU = 3, GLP_NF = 4, or GLP_NS = 5); r_prim[i], i = 1,...,m, is the primal value of i-th row; r_dual[i], i = 1,...,m, is the dual value of i-th row; c_stat[j], j = 1,...,n, is the status of j-th column (GLP_BS = 1, GLP_NL = 2, GLP_NU = 3, GLP_NF = 4, or GLP_NS = 5); c_prim[j], j = 1,...,n, is the primal value of j-th column; c_dual[j], j = 1,...,n, is the dual value of j-th column. </p>
 */
public";

%csmethodmodifiers format(char buf[13+1], double x) "
/**
 */
public";

%csmethodmodifiers glp_print_ranges(glp_prob *P, int len, const int list[], int flags, const char *fname) "
/**
 */
public";

%csmethodmodifiers glp_print_ipt(glp_prob *P, const char *fname) "
/**
 */
public";

%csmethodmodifiers glp_read_ipt(glp_prob *lp, const char *fname) "
/**
 * glp_read_ipt - read interior-point solution from text file .
 * <p>SYNOPSIS</p>
 * <p>int glp_read_ipt(glp_prob *lp, const char *fname);</p>
 * <p>DESCRIPTION</p>
 * <p>The routine glp_read_ipt reads interior-point solution from a text file whose name is specified by the parameter fname into the problem object.</p>
 * <p>For the file format see description of the routine glp_write_ipt.</p>
 * <p>RETURNS</p>
 * <p>On success the routine returns zero, otherwise non-zero. </p>
 */
public";

%csmethodmodifiers glp_write_ipt(glp_prob *lp, const char *fname) "
/**
 * glp_write_ipt - write interior-point solution to text file .
 * <p>SYNOPSIS</p>
 * <p>int glp_write_ipt(glp_prob *lp, const char *fname);</p>
 * <p>DESCRIPTION</p>
 * <p>The routine glp_write_ipt writes the current interior-point solution to a text file whose name is specified by the parameter fname. This file can be read back with the routine glp_read_ipt.</p>
 * <p>RETURNS</p>
 * <p>On success the routine returns zero, otherwise non-zero.</p>
 * <p>FILE FORMAT</p>
 * <p>The file created by the routine glp_write_ipt is a plain text file, which contains the following information:</p>
 * <p>m n stat obj_val r_prim[1] r_dual[1] . . . r_prim[m] r_dual[m] c_prim[1] c_dual[1] . . . c_prim[n] c_dual[n]</p>
 * <p>where: m is the number of rows (auxiliary variables); n is the number of columns (structural variables); stat is the solution status (GLP_UNDEF = 1 or GLP_OPT = 5); obj_val is the objective value; r_prim[i], i = 1,...,m, is the primal value of i-th row; r_dual[i], i = 1,...,m, is the dual value of i-th row; c_prim[j], j = 1,...,n, is the primal value of j-th column; c_dual[j], j = 1,...,n, is the dual value of j-th column. </p>
 */
public";

%csmethodmodifiers glp_print_mip(glp_prob *P, const char *fname) "
/**
 */
public";

%csmethodmodifiers glp_read_mip(glp_prob *mip, const char *fname) "
/**
 * glp_read_mip - read MIP solution from text file .
 * <p>SYNOPSIS</p>
 * <p>int glp_read_mip(glp_prob *mip, const char *fname);</p>
 * <p>DESCRIPTION</p>
 * <p>The routine glp_read_mip reads MIP solution from a text file whose name is specified by the parameter fname into the problem object.</p>
 * <p>For the file format see description of the routine glp_write_mip.</p>
 * <p>RETURNS</p>
 * <p>On success the routine returns zero, otherwise non-zero. </p>
 */
public";

%csmethodmodifiers glp_write_mip(glp_prob *mip, const char *fname) "
/**
 * glp_write_mip - write MIP solution to text file .
 * <p>SYNOPSIS</p>
 * <p>int glp_write_mip(glp_prob *mip, const char *fname);</p>
 * <p>DESCRIPTION</p>
 * <p>The routine glp_write_mip writes the current MIP solution to a text file whose name is specified by the parameter fname. This file can be read back with the routine glp_read_mip.</p>
 * <p>RETURNS</p>
 * <p>On success the routine returns zero, otherwise non-zero.</p>
 * <p>FILE FORMAT</p>
 * <p>The file created by the routine glp_write_sol is a plain text file, which contains the following information:</p>
 * <p>m n stat obj_val r_val[1] . . . r_val[m] c_val[1] . . . c_val[n]</p>
 * <p>where: m is the number of rows (auxiliary variables); n is the number of columns (structural variables); stat is the solution status (GLP_UNDEF = 1, GLP_FEAS = 2, GLP_NOFEAS = 4, or GLP_OPT = 5); obj_val is the objective value; r_val[i], i = 1,...,m, is the value of i-th row; c_val[j], j = 1,...,n, is the value of j-th column. </p>
 */
public";

%csmethodmodifiers mc13d(int n, const int icn[], const int ip[], const int lenr[], int ior[], int ib[], int lowl[], int numb[], int prev[]) "
/**
 * mc13d - permutations to block triangular form .
 * <p>SYNOPSIS</p>
 * <p>#include \"mc13d.h\" int mc13d(int n, const int icn[], const int ip[], const int lenr[], int ior[], int ib[], int lowl[], int numb[], int prev[]);</p>
 * <p>DESCRIPTION</p>
 * <p>Given the column numbers of the nonzeros in each row of the sparse matrix, the routine mc13d finds a symmetric permutation that makes the matrix block lower triangular.</p>
 * <p>INPUT PARAMETERS</p>
 * <p>n order of the matrix.</p>
 * <p>icn array containing the column indices of the non-zeros. Those belonging to a single row must be contiguous but the ordering of column indices within each row is unimportant and wasted space between rows is permitted.</p>
 * <p>ip ip[i], i = 1,2,...,n, is the position in array icn of the first column index of a non-zero in row i.</p>
 * <p>lenr lenr[i], i = 1,2,...,n, is the number of non-zeros in row i.</p>
 * <p>OUTPUT PARAMETERS</p>
 * <p>ior ior[i], i = 1,2,...,n, gives the position on the original ordering of the row or column which is in position i in the permuted form.</p>
 * <p>ib ib[i], i = 1,2,...,num, is the row number in the permuted matrix of the beginning of block i, 1 &lt;= num &lt;= n.</p>
 * <p>WORKING ARRAYS</p>
 * <p>arp working array of length [1+n], where arp[0] is not used. arp[i] is one less than the number of unsearched edges leaving node i. At the end of the algorithm it is set to a permutation which puts the matrix in block lower triangular form.</p>
 * <p>ib working array of length [1+n], where ib[0] is not used. ib[i] is the position in the ordering of the start of the ith block. ib[n+1-i] holds the node number of the ith node on the stack.</p>
 * <p>lowl working array of length [1+n], where lowl[0] is not used. lowl[i] is the smallest stack position of any node to which a path from node i has been found. It is set to n+1 when node i is removed from the stack.</p>
 * <p>numb working array of length [1+n], where numb[0] is not used. numb[i] is the position of node i in the stack if it is on it, is the permuted order of node i for those nodes whose final position has been found and is otherwise zero.</p>
 * <p>prev working array of length [1+n], where prev[0] is not used. prev[i] is the node at the end of the path when node i was placed on the stack.</p>
 * <p>RETURNS</p>
 * <p>The routine mc13d returns num, the number of blocks found. </p>
 */
public";

%csmethodmodifiers glp_mincost_lp(glp_prob *lp, glp_graph *G, int names, int v_rhs, int a_low, int a_cap, int a_cost) "
/**
 * glp_mincost_lp - convert minimum cost flow problem to LP .
 * <p>SYNOPSIS</p>
 * <p>void glp_mincost_lp(glp_prob *lp, glp_graph *G, int names, int v_rhs, int a_low, int a_cap, int a_cost);</p>
 * <p>DESCRIPTION</p>
 * <p>The routine glp_mincost_lp builds an LP problem, which corresponds to the minimum cost flow problem on the specified network G. </p>
 */
public";

%csmethodmodifiers glp_mincost_okalg(glp_graph *G, int v_rhs, int a_low, int a_cap, int a_cost, double *sol, int a_x, int v_pi) "
/**
 */
public";

%csmethodmodifiers overflow(int u, int v) "
/**
 */
public";

%csmethodmodifiers glp_mincost_relax4(glp_graph *G, int v_rhs, int a_low, int a_cap, int a_cost, int crash, double *sol, int a_x, int a_rc) "
/**
 */
public";

%csmethodmodifiers glp_maxflow_lp(glp_prob *lp, glp_graph *G, int names, int s, int t, int a_cap) "
/**
 * glp_maxflow_lp - convert maximum flow problem to LP .
 * <p>SYNOPSIS</p>
 * <p>void glp_maxflow_lp(glp_prob *lp, glp_graph *G, int names, int s, int t, int a_cap);</p>
 * <p>DESCRIPTION</p>
 * <p>The routine glp_maxflow_lp builds an LP problem, which corresponds to the maximum flow problem on the specified network G. </p>
 */
public";

%csmethodmodifiers glp_maxflow_ffalg(glp_graph *G, int s, int t, int a_cap, double *sol, int a_x, int v_cut) "
/**
 */
public";

%csmethodmodifiers glp_check_asnprob(glp_graph *G, int v_set) "
/**
 * glp_check_asnprob - check correctness of assignment problem data .
 * <p>SYNOPSIS</p>
 * <p>int glp_check_asnprob(glp_graph *G, int v_set);</p>
 * <p>RETURNS</p>
 * <p>If the specified assignment problem data are correct, the routine glp_check_asnprob returns zero, otherwise, non-zero. </p>
 */
public";

%csmethodmodifiers glp_asnprob_lp(glp_prob *P, int form, glp_graph *G, int names, int v_set, int a_cost) "
/**
 * glp_asnprob_lp - convert assignment problem to LP .
 * <p>SYNOPSIS</p>
 * <p>int glp_asnprob_lp(glp_prob *P, int form, glp_graph *G, int names, int v_set, int a_cost);</p>
 * <p>DESCRIPTION</p>
 * <p>The routine glp_asnprob_lp builds an LP problem, which corresponds to the assignment problem on the specified graph G.</p>
 * <p>RETURNS</p>
 * <p>If the LP problem has been successfully built, the routine returns zero, otherwise, non-zero. </p>
 */
public";

%csmethodmodifiers glp_asnprob_okalg(int form, glp_graph *G, int v_set, int a_cost, double *sol, int a_x) "
/**
 */
public";

%csmethodmodifiers glp_asnprob_hall(glp_graph *G, int v_set, int a_x) "
/**
 * glp_asnprob_hall - find bipartite matching of maximum cardinality .
 * <p>SYNOPSIS</p>
 * <p>int glp_asnprob_hall(glp_graph *G, int v_set, int a_x);</p>
 * <p>DESCRIPTION</p>
 * <p>The routine glp_asnprob_hall finds a matching of maximal cardinality in the specified bipartite graph G. It uses a version of the Fortran routine MC21A developed by I.S.Duff [1], which implements Hall's algorithm [2].</p>
 * <p>RETURNS</p>
 * <p>The routine glp_asnprob_hall returns the cardinality of the matching found. However, if the specified graph is incorrect (as detected by the routine glp_check_asnprob), the routine returns negative value.</p>
 * <p>REFERENCES</p>
 * <p>
I.S.Duff, Algorithm 575: Permutations for zero-free diagonal, ACM Trans. on Math. Softw. 7 (1981), 387-390.M.Hall, \"An Algorithm for distinct representatives,\" Amer. Math. Monthly 63 (1956), 716-717. 
</p>
 */
public";

%csmethodmodifiers sorting(glp_graph *G, int list[]) "
/**
 * glp_cpp - solve critical path problem .
 * <p>SYNOPSIS</p>
 * <p>double glp_cpp(glp_graph *G, int v_t, int v_es, int v_ls);</p>
 * <p>DESCRIPTION</p>
 * <p>The routine glp_cpp solves the critical path problem represented in the form of the project network.</p>
 * <p>The parameter G is a pointer to the graph object, which specifies the project network. This graph must be acyclic. Multiple arcs are allowed being considered as single arcs.</p>
 * <p>The parameter v_t specifies an offset of the field of type double in the vertex data block, which contains time t[i] &gt;= 0 needed to perform corresponding job j. If v_t &lt; 0, it is assumed that t[i] = 1 for all jobs.</p>
 * <p>The parameter v_es specifies an offset of the field of type double in the vertex data block, to which the routine stores earliest start time for corresponding job. If v_es &lt; 0, this time is not stored.</p>
 * <p>The parameter v_ls specifies an offset of the field of type double in the vertex data block, to which the routine stores latest start time for corresponding job. If v_ls &lt; 0, this time is not stored.</p>
 * <p>RETURNS</p>
 * <p>The routine glp_cpp returns the minimal project duration, that is, minimal time needed to perform all jobs in the project. </p>
 */
public";

%csmethodmodifiers glp_cpp(glp_graph *G, int v_t, int v_es, int v_ls) "
/**
 */
public";

%csmethodmodifiers AMD_order(Int n, const Int Ap[], const Int Ai[], Int P[], double Control[], double Info[]) "
/**
 */
public";

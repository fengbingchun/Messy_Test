/*Find the minimum value which satisfies the linear inequality:
    a*x + b*y >= 1 {a,b,x,y Integers} {a,b > 0} {a,b entered on command line}

  Nigel_Galloway@operamail.com
  February 2008
*/
using System;
using System.Runtime.InteropServices;

unsafe class GLPK{
  double *lp;
  public int a;
  public int b;

  const string glpkLibrary = "libglpk.so";
  readonly int GLP_FR = 1;
  readonly int GLP_IV = 2;
  readonly int GLP_DB = 4;
  struct ConstraintMatrix{
    public fixed int ia[3];
    public fixed int ja[3];
    public fixed double ar[3];
  }
  [DllImport(glpkLibrary, SetLastError=true)]
  static extern double* glp_create_prob();
  [DllImport(glpkLibrary, SetLastError=true)]
  static extern void glp_add_rows(double* lp, int rows);
  [DllImport(glpkLibrary, SetLastError=true)]
  static extern void glp_add_cols(double* lp, int cols);
  [DllImport(glpkLibrary, SetLastError=true)]
  static extern void glp_set_col_bnds(double* lp, int col, int bound_type, double lower_bound, double upper_bound);
  [DllImport(glpkLibrary, SetLastError=true)]
  static extern void glp_set_col_kind(double* lp, int col, int kind);
  [DllImport(glpkLibrary, SetLastError=true)]
  static extern void glp_load_matrix(double* lp, int elements, int* ia, int* ja, double* ar);
  public GLPK(int a, int b){
    this.a = a;
    this.b = b;
    lp = glp_create_prob();
    //Col 1 is x, Col 2 is y
    glp_add_rows(lp, 1);
    glp_add_cols(lp, 2);
    glp_set_col_bnds(lp, 1, GLP_FR, 0.0, 0.0);
    glp_set_col_bnds(lp, 2, GLP_FR, 0.0, 0.0);
    glp_set_col_kind(lp, 1, GLP_IV);
    glp_set_col_kind(lp, 2, GLP_IV);
    //Row 1 is a*x + b*y
    ConstraintMatrix CM = new ConstraintMatrix();
    CM.ia[1]=1; CM.ja[1]=1; CM.ar[1]=a;
    CM.ia[2]=1; CM.ja[2]=2; CM.ar[2]=b;
    glp_load_matrix(lp, 2, CM.ia, CM.ja, CM.ar);
    Console.WriteLine("Hello Nigel");
  }

  [DllImport(glpkLibrary, SetLastError=true)]
  static extern void glp_set_row_bnds(double* lp, int row, int bound_type, double lower_bound, double upper_bound);
  [DllImport(glpkLibrary, SetLastError=true)]
  static extern void glp_simplex(double* lp, void* options);
  [DllImport(glpkLibrary, SetLastError=true)]
  static extern void glp_intopt(double* lp, void* options);
  [DllImport(glpkLibrary, SetLastError=true)]
  static extern double glp_mip_col_val(double* lp, int col);
  public int betterGuess(int upper_bound){
    //Find a new guess less than the old guess: 1 <= (a*x + b*y) <= (old guess - 1)
    glp_set_row_bnds(lp, 1, GLP_DB, 1.0, ((double)upper_bound)-0.5);
    glp_simplex(lp, null);
    glp_intopt(lp, null);
    int x = (int)glp_mip_col_val(lp, 1);
    int y = (int)glp_mip_col_val(lp, 2);
    int nextGuess = a*x + b*y;
    Console.WriteLine("x = {0}, y = {1}, a*x + b*y = {2}",x,y,nextGuess);
    return nextGuess;
  }

  [DllImport(glpkLibrary, SetLastError=true)]
  static extern void glp_delete_prob(double* lp);
  ~GLPK(){
    glp_delete_prob(lp);
    Console.WriteLine("Goodbye Nigel");
  }

}

class test{
  static bool isMinimum(int a, int b, int guess){
    Console.WriteLine("Trying {0}",guess);
    if (a%guess > 0) return false;
    if (b%guess > 0) return false;
    Console.WriteLine("Solution is {0}",guess);
    return true;
  }

  public static void Main(string[] args){
    Console.WriteLine("a = {0}, b = {1}",args[0], args[1]);
    GLPK lp = new GLPK(Int32.Parse(args[0]),Int32.Parse(args[1]));
    int guess = (lp.a > lp.b) ? lp.b : lp.a;
    while (!isMinimum(lp.a,lp.b,guess)) guess = lp.betterGuess(guess);
  }
}

using System;
using org.gnu.glpk;

class Program
{  
	static void Main (string[] args)
	{
		Console.WriteLine ("GLPK " + GLPK.glp_version ());
	}
}
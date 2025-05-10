import org.gnu.glpk.GLPK;
import org.gnu.glpk.GLPKConstants;
import org.gnu.glpk.SWIGTYPE_p_double;
import org.gnu.glpk.SWIGTYPE_p_int;

/**
 * This example file demonstrates that OutOfMemoryErrors are
 * thrown if calloc fails.
 */
public class OutOfMemory {

    /**
     * This is the main function.
     */
    public static void main(String[] args) {
        SWIGTYPE_p_int ind;

        System.out.println("Testing allocation of integer array.");
        System.out.println("1: No error should occur");
        ind = GLPK.new_intArray(3);
	GLPK.delete_intArray(ind);
	System.out.println("1: Success");
	try {
	    System.out.println("2: Error should occur");
	    ind = GLPK.new_intArray(-1);
	} catch (OutOfMemoryError ex) {
	    ex.printStackTrace(System.out);
	    System.out.println("2: Success");
            System.exit(0);
	}
        System.out.println("2: Failure");
        System.exit(1);
    }
}

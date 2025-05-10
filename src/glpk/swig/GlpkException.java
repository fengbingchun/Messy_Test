package org.gnu.glpk; 

/**
 * Exception thrown, when the GLPK native library call fails.
 * <p>If an error occurs GLPK will release all internal memory. Hence all
 * object references to the library will be invalid.
 * <p>To reenable listening to terminal output call
 * <pre>
 * GLPK.glp_term_hook(null, null);
 * </pre>
 */
public class GlpkException extends RuntimeException {

    /**
     * Constructs a new GLPK exception.
     */
    public GlpkException() {
        super();
    }

    /**
     * Constructs a new GLPK exception.
     * @param message detail message
     */
    public GlpkException(final String message) {
        super(message);
    }
}


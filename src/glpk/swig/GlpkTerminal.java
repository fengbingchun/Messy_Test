package org.gnu.glpk;

import java.util.LinkedList;

/**
 * This class manages terminal output.
 * <p>GLPK will call method {@link #callback(String) callback} before producing
 * terminal output. A listener can inhibit the terminal output by returning
 * <code>false</code> in the {@link GlpkTerminalListener#output(String) output}
 * routine.
 * <p>The list of listeners is thread local. Each thread has to register its
 * own listener.
 * <p>If a {@link GlpkException GlpkExeption} has occured it is necessary to
 * call <pre>
 * GLPK.glp_term_hook(null, null);</pre>
 * to reenable listening to terminal output.
 * @see GlpkTerminalListener
 * @see GlpkException
 * @see GLPK#glp_term_hook(SWIGTYPE_p_f_p_void_p_q_const__char__int,
 * SWIGTYPE_p_void)
 */
public final class GlpkTerminal {
    /**
     * List of listeners.
     */
    private static ThreadLocal<LinkedList<GlpkTerminalListener>> listeners
            = new ThreadLocal<LinkedList<GlpkTerminalListener>>() {
                @Override
                protected LinkedList<GlpkTerminalListener> initialValue() {
                    return new LinkedList<GlpkTerminalListener>(); 
                }
            };

    static {
        GLPK.glp_term_hook(null, null);
    }

    /**
     * Constructor.
     */
    private GlpkTerminal() {
    }

    /**
     * Callback function called by native library.
     * Output to the console is created if any of the listeners.get() requests it.
     * @param str string to be written to console
     * @return 0 if output is requested
     */
    public static int callback(final String str) {
        boolean output = false;

        if (listeners.get().size() > 0) {
            for (GlpkTerminalListener listener : listeners.get()) {
                output |= listener.output(str);
            }
            if (output) {
                return 0;
            } else {
                return 1;
            }
        }
        return 0;
    }

    /**
     * Add listener.
     * @param listener listener for terminal output
     */
    public static void addListener(final GlpkTerminalListener listener) {
        listeners.get().add(listener);
    }

    /**
     * Removes first occurance of listener.
     * @param listener listener for terminal output
     * @return true if listener was found
     */
    public static boolean removeListener(final GlpkTerminalListener listener) {
        return listeners.get().remove(listener);
    }

    /**
     * Remove all listeners.get().
     */
    public static void removeAllListeners() {
        while (listeners.get().size() > 0) {
            listeners.get().removeLast();
        }
    }
}

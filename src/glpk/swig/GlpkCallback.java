package org.gnu.glpk;

import java.util.LinkedList;

/**
 * This class manages callbacks from the MIP solver.
 * <p>The GLPK MIP solver calls method {@link #callback(long) callback} in
 * the branch-and-cut algorithm. A listener to the callback can be used to
 * influence the sequence in which nodes of the search tree are evaluated, or
 * to supply a heuristic solution. To find out why the callback is issued
 * use method {@link GLPK#glp_ios_reason(glp_tree) GLPK.glp_ios_reason}.
 * <p>The list of listeners is thread local. Each thread has to register its
 * own listener.
 */
public final class GlpkCallback {
    /**
     * List of callback listeners.
     */
    private static ThreadLocal<LinkedList<GlpkCallbackListener>> listeners
            = new ThreadLocal<LinkedList<GlpkCallbackListener>>() {
                @Override
                protected LinkedList<GlpkCallbackListener> initialValue() {
                   return new LinkedList<GlpkCallbackListener>();
                }
            };

    /**
     * Constructor.
     */
    private GlpkCallback() {
    }

    /**
     * Callback method called by native library.
     * @param cPtr pointer to search tree
     */
    public static void callback(final long cPtr) {
        glp_tree tree;
        tree = new glp_tree(cPtr, false);
        for (GlpkCallbackListener listener : listeners.get()) {
            listener.callback(tree);
        }
    }

    /**
     * Adds a listener for callbacks.
     * @param listener listener for callbacks
     */
    public static void addListener(final GlpkCallbackListener listener) {
        listeners.get().add(listener);
    }

    /**
     * Removes first occurance of a listener for callbacks.
     * @param listener listener for callbacks
     * @return true if the listener was found
     */
    public static boolean removeListener(final GlpkCallbackListener listener) {
        return listeners.get().remove(listener);
    }

}

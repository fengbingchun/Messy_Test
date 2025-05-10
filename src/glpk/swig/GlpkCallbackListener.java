package org.gnu.glpk;

/**
 * Callback Listener.
 * <p>The GLPK MIP solver calls method {@link GlpkCallback#callback(long)
 * GLPK.callback} in the branch-and-cut algorithm. A listener to the callback
 * can be used to influence the sequence in which nodes of the search tree are
 * evaluated, or to supply a heuristic solution.
 * @see GlpkCallback
 */
public interface GlpkCallbackListener {
    /**
     * Method call by the GLPK MIP solver in the branch-and-cut algorithm.
     * @param tree search tree
     */
    void callback(glp_tree tree);
}

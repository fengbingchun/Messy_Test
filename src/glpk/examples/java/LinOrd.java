/*
 * @author Heinrich Schuchardt <xypron.glpk@gmx.de>
 * 
 * Adapted from an example in C written by
 * Andrew Makhorin <mao@gnu.org>, October 2009
 *
 *  LINEAR ORDERING PROBLEM
 *
 *  Let G = (V,E) denote the complete digraph, where V is the set of
 *  nodes and E is the set of arcs. A tournament T in E consists of a
 *  subset of arcs containing for every pair of nodes i and j either arc
 *  (i->j) or arc (j->i), but not both. T is an acyclic tournament if it
 *  contains no directed cycles. Obviously, an acyclic tournament induces
 *  an ordering <i1, i2, ..., in> of the nodes (and vice versa), where
 *  n = |V|. Node i1 is the one with no entering arcs, i2 has exactly one
 *  entering arc, etc., and in is the node with no outgoing arc. Given
 *  arc weights w[i,j] for every pair i, j in V, the Linear Ordering
 *  Problem (LOP) consists of finding an acyclic tournament T in E such
 *  that the sum of arcs in T is maximal, or in other words, of finding
 *  an ordering of the nodes such that the sum of the weights of the arcs
 *  compatible with this ordering is maximal.
 *
 *  Given a nxn-matrix C = (c[i,j]) the triangulation problem is to
 *  determine a symmetric permutation of the rows and columns of C such
 *  that the sum of subdiagonal entries is as small as possible. Note
 *  that it does not matter if diagonal entries are taken into account or
 *  not. Obviously, by setting arc weights w[i,j] = c[i,j] for the
 *  complete digraph G, the triangulation problem for C can be solved as
 *  linear ordering problem for G. Conversely, a linear ordering problem
 *  for G can be transformed to a triangulation problem for an nxn-matrix
 *  C by setting c[i,j] = w[i,j] and the diagonal entries c[i,i] = 0 (or
 *  to arbitrary values).
 *
 *  The LOP can be formulated as binary integer programming problem.
 *  We use binary variables x[i,j] for (i,j) in A, stating whether arc
 *  (i->j) is present in the tournament or not. Taking into account that
 *  a tournament is acyclic iff it contains no dicycles of length 3, it
 *  is easy to see that the LOP can be formulated as follows:
 *
 *     Maximize
 *
 *        sum    w[i,j] x[i,j]                                        (1)
 *     (i,j) in A
 *
 *     Subject to
 *
 *        x[i,j] + x[j,i] = 1, for all i,j in V, i < j,               (2)
 *
 *        x[i,j] + x[j,k] + x[k,i] <= 2,                              (3)
 *
 *              for all i,j,k in V, i < j, i < k, j != k,
 *
 *        x[i,j] in {0, 1}, for all i,j in V.                         (4)
 *
 *  (From <http://www.optsicom.es/lolib/#problem-description>.)
 */

import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.util.Scanner;
import org.gnu.glpk.GLPK;
import org.gnu.glpk.GLPKConstants;
import org.gnu.glpk.GlpkCallback;
import org.gnu.glpk.GlpkCallbackListener;
import org.gnu.glpk.GlpkException;
import org.gnu.glpk.SWIGTYPE_p_double;
import org.gnu.glpk.SWIGTYPE_p_int;
import org.gnu.glpk.glp_attr;
import org.gnu.glpk.glp_iocp;
import org.gnu.glpk.glp_prob;
import org.gnu.glpk.glp_tree;

/**
 * Solves linear ordering problems.
 */
public class LinOrd implements GlpkCallbackListener {

    /**
     * maximum number of nodes
     */
    public final static int N_MAX = 1000;
    /**
     * number of nodes in the digraph given
     */
    int n;
    /**
     * w[i,j] is weight of arc (i->j), 1 <= i,j <= n
     */
    int w[][];
    /**
     * x[i][j] is the number of binary variable x[i,j], 1 <= i,j <= n, i != j,
     * in the problem object, where x[i,j] = 1 means that node i precedes node
     * j, i.e. arc (i->j) is included in the tournament
     */
    int x[][];
    /**
     * problem object
     */
    glp_prob prob;

    /**
     * Reads data from file.
     *
     * @param fname file name
     */
    private void read_data(String fname) {
        FileReader fr = null;
        Scanner sc;
        String comment;
        int i, j;

        try {
            fr = new FileReader(fname);
        } catch (FileNotFoundException ex) {
            System.out.println(ex.getMessage());
            System.exit(1);
        }

        System.out.println("Reading LOP instance data from '"
                + fname
                + "'...");

        sc = new Scanner(fr);

        comment = sc.nextLine().trim();
        System.out.println(comment);

        n = sc.nextInt();
        if (n < 1) {
            System.out.println("invalid number of nodes");
            System.exit(1);
        }
        if (n > N_MAX) {
            System.out.println("too many nodes");
            System.exit(1);
        }
        System.out.println("Digraph has " + n + " nodes");
        w = new int[1 + n][];
        for (i = 1; i <= n; i++) {
            w[i] = new int[1 + n];
            for (j = 1; j <= n; j++) {
                w[i][j] = sc.nextInt();
            }
        }
        try {
            fr.close();
        } catch (IOException ex) {
            System.out.println(ex.getMessage());
            System.exit(1);
        }
    }

    /**
     * Creates mixed integer problem.
     */
    private void build_mip() {
        int i, j, row;
        SWIGTYPE_p_int ind = GLPK.new_intArray(1 + 2);
        SWIGTYPE_p_double val = GLPK.new_doubleArray(1 + 2);
        String name;
        prob = GLPK.glp_create_prob();
        GLPK.glp_set_obj_dir(prob, GLPKConstants.GLP_MAX);
        /* create binary variables */
        x = new int[1 + n][];
        for (i = 1; i <= n; i++) {
            x[i] = new int[1 + n];
            for (j = 1; j <= n; j++) {
                if (i == j) {
                    x[i][j] = 0;
                } else {
                    x[i][j] = GLPK.glp_add_cols(prob, 1);
                    name = "x[" + i + "," + j + "]";
                    GLPK.glp_set_col_name(prob, x[i][j], name);
                    GLPK.glp_set_col_kind(prob, x[i][j], GLPKConstants.GLP_BV);
                    /* objective coefficient */
                    GLPK.glp_set_obj_coef(prob, x[i][j], w[i][j]);
                }
            }
        }
        /* create irreflexivity constraints (2) */
        for (i = 1; i <= n; i++) {
            for (j = i + 1; j <= n; j++) {
                row = GLPK.glp_add_rows(prob, 1);
                GLPK.glp_set_row_bnds(prob, row, GLPKConstants.GLP_FX, 1, 1);
                GLPK.intArray_setitem(ind, 1, x[i][j]);
                GLPK.doubleArray_setitem(val, 1, 1.);
                GLPK.intArray_setitem(ind, 2, x[j][i]);
                GLPK.doubleArray_setitem(val, 2, 1.);
                GLPK.glp_set_mat_row(prob, row, 2, ind, val);
            }
        }

        GLPK.delete_intArray(ind);
        GLPK.delete_doubleArray(val);
    }

    /**
     * Identifies inactive constraints.
     *
     * @param tree branch and bound tree
     * @param list indices of inactive constraints
     * @return number of inactive constraints
     */
    private int inactive(glp_tree tree, SWIGTYPE_p_int list) {
        glp_attr attr = new glp_attr();
        int p = GLPK.glp_ios_curr_node(tree);
        int lev = GLPK.glp_ios_node_level(tree, p);
        int i, cnt = 0;
        for (i = GLPK.glp_get_num_rows(prob); i >= 1; i--) {
            GLPK.glp_ios_row_attr(tree, i, attr);
            if (attr.getLevel() < lev) {
                break;
            }
            if (attr.getOrigin() != GLPKConstants.GLP_RF_REG) {
                if (GLPK.glp_get_row_stat(prob, i) == GLPKConstants.GLP_BS) {
                    cnt++;
                    if (list != null) {
                        GLPK.intArray_setitem(list, cnt, i);
                    }
                }
            }
        }
        System.out.println(cnt + " inactive constraints removed");
        return cnt;
    }

    private void remove_inactive(glp_tree tree) {
        /* remove inactive transitivity constraints */
        int cnt;
        SWIGTYPE_p_int clist;
        cnt = inactive(tree, null);
        if (cnt > 0) {
            clist = GLPK.new_intArray(cnt + 1);
            inactive(tree, clist);
            GLPK.glp_del_rows(prob, cnt, clist);
        }
    }

    /**
     * Generates violated transitivity constraints and adds them to the current
     * subproblem. As suggested by Juenger et al., only only arc-disjoint
     * violated constraints are considered.
     *
     * @return number of generated constraints
     */
    private int generate_rows() {
        int i, j, k, cnt, row;
        int[][] u;
        SWIGTYPE_p_int ind = GLPK.new_intArray(1 + 3);
        SWIGTYPE_p_double val = GLPK.new_doubleArray(1 + 3);
        double r;
        /* u[i,j] = 1, if arc (i->j) is covered by some constraint */
        u = new int[1 + n][];
        for (i = 1; i <= n; i++) {
            u[i] = new int[1 + n];
            for (j = 1; j <= n; j++) {
                u[i][j] = 0;
            }
        }
        cnt = 0;
        for (i = 1; i <= n; i++) {
            for (j = 1; j <= n; j++) {
                for (k = 1; k <= n; k++) {
                    if (i == j) {
                    } else if (i == k) {
                    } else if (j == k) {
                    } else if (u[i][j] != 0 || u[j][i] != 0) {
                    } else if (u[i][k] != 0 || u[k][i] != 0) {
                    } else if (u[j][k] != 0 || u[k][j] != 0) {
                    } else {
                        /* check if x[i,j] + x[j,k] + x[k,i] <= 2 */
                        r = GLPK.glp_get_col_prim(prob, x[i][j])
                                + GLPK.glp_get_col_prim(prob, x[j][k])
                                + GLPK.glp_get_col_prim(prob, x[k][i]);
                        /* should note that it is not necessary to add to the
                         current subproblem every violated constraint (3), for
                         which r > 2; if r < 3, we can stop adding violated
                         constraints, because for integer feasible solution
                         the value of r is integer, so r < 3 is equivalent to
                         r <= 2; on the other hand, adding violated
                         constraints leads to tightening the feasible region
                         of LP relaxation and, thus, may reduce the size of
                         the search tree */
                        if (r > 2.15) {
                            /* generate violated transitivity constraint */
                            row = GLPK.glp_add_rows(prob, 1);
                            GLPK.glp_set_row_bnds(prob, row,
                                    GLPKConstants.GLP_UP, 0, 2);
                            GLPK.intArray_setitem(ind, 1, x[i][j]);
                            GLPK.doubleArray_setitem(val, 1, 1);
                            GLPK.intArray_setitem(ind, 2, x[j][k]);
                            GLPK.doubleArray_setitem(val, 2, 1);
                            GLPK.intArray_setitem(ind, 3, x[k][i]);
                            GLPK.doubleArray_setitem(val, 3, 1);
                            GLPK.glp_set_mat_row(prob, row, 3, ind, val);
                            u[i][j] = u[j][i] = 1;
                            u[i][k] = u[k][i] = 1;
                            u[j][k] = u[k][j] = 1;
                            cnt++;
                        }
                    }
                }
            }
        }
        GLPK.delete_intArray(ind);
        GLPK.delete_doubleArray(val);
        System.out.println(cnt + " violated constraints were generated");
        return cnt;
    }

    /**
     * Solves a linear ordering problem.
     *
     * @param inFile input file
     * @param outFile output file
     */
    private void solve(String inFile, String outFile) {
        glp_iocp iocp;

        GlpkCallback.addListener(this);
        read_data(inFile);
        build_mip();
        GLPK.glp_adv_basis(prob, 0);
        GLPK.glp_simplex(prob, null);
        iocp = new glp_iocp();
        GLPK.glp_init_iocp(iocp);
        GLPK.glp_intopt(prob, iocp);
        GLPK.glp_print_mip(prob, outFile);
        GlpkCallback.removeListener(this);
        GLPK.glp_delete_prob(prob);
    }

    /**
     * Main routine.
     *
     * @param args command line parameters (input file, output file)
     */
    public static void main(String[] args) {
        LinOrd l = new LinOrd();
        if (args.length != 2) {
            System.out.println("Usage: "
                    + LinOrd.class.getName()
                    + " infile outfile\n\n"
                    + "e.g. "
                    + LinOrd.class.getName()
                    + " tiw56r72.mat solution.txt");
            return;
        }
        try {
            l.solve(args[0], args[1]);
        } catch (GlpkException ex) {
            System.out.println("Program terminated due to an error");
        }
    }

    /**
     * Method call by the GLPK MIP solver in the branch-and-cut algorithm.
     *
     * @param tree search tree
     */
    public void callback(glp_tree tree) {
        if (GLPK.glp_ios_reason(tree) == GLPKConstants.GLP_IROWGEN) {
            remove_inactive(tree);
            generate_rows();
        }
    }
}

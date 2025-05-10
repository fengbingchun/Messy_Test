
/**
 * *********************************************************************
 * This code is part of GLPK for Java.
 *
 * Copyright 2012, Heinrich Schuchardt <xypron.glpk@gmx.de>
 *
 * GLPK for Java is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation, either version 3 of the License, or (at your option) any
 * later version.
 *
 * GLPK for Java is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE. See the GNU General Public License for more
 * details.
 *
 * You should have received a copy of the GNU General Public License along with
 * GLPK. If not, see <http://www.gnu.org/licenses/>.
 * 
**********************************************************************
 */
import org.gnu.glpk.*;

/**
 * This class demonstrates the GlpkCallbackListener interface.
 *
 * The callback method is used to branch down either <ul> <li>on the most
 * fractional integer variable or</li> <li>on a variable chosen by the Driebek
 * Tomlin heuristic</li> </ul>
 *
 * The implementation of the Driebeck Tomlin heuristic is derived from the
 * coding copyrighted by Andrew Makhorin.
 */
public class BranchDown implements GlpkCallbackListener {

    public final static String DRTOM = "--drtom";
    public final static String MOSTFDOWN = "--mfdn";
    private String heuristic = "";

    /**
     * Main method.
     *
     * @param arg command line arguments
     */
    public static void main(String[] arg) {
        if (2 != arg.length) {
            help();
            return;
        }
        if (arg[0].compareTo(DRTOM) != 0 && 
                arg[0].compareTo(MOSTFDOWN) != 0
                ) {
            help();
            return;
        }
        new BranchDown().solve(arg);
    }

    /**
     * Outputs help page.
     */
    private static void help() {
        System.out.println("Usage: java BranchDown option model.mod\n");
        System.out.println("Options:");
        System.out.println(
                " --drtom   branch down Driebeck Tomlin heuristic");
        System.out.println(
                " --mfdn    branch down on most fractional variable ");
    }

    /**
     * Solves a problem given in an GMPL file.
     *
     * @param arg command line arguments (option, filename)
     */
    public void solve(String[] arg) {
        String method = "";
        glp_prob lp = null;
        glp_tran tran;
        glp_iocp iocp;

        String fname;
        int skip = 0;
        int ret;

        heuristic = arg[0];

        // listen to callbacks
        GlpkCallback.addListener(this);

        fname = arg[1];

        lp = GLPK.glp_create_prob();
        System.out.println("Problem created");

        tran = GLPK.glp_mpl_alloc_wksp();
        ret = GLPK.glp_mpl_read_model(tran, fname, skip);
        if (ret != 0) {
            GLPK.glp_mpl_free_wksp(tran);
            GLPK.glp_delete_prob(lp);
            throw new RuntimeException("Model file not found: " + fname);
        }

        // generate model
        GLPK.glp_mpl_generate(tran, null);
        // build model
        GLPK.glp_mpl_build_prob(tran, lp);
        // set solver parameters
        iocp = new glp_iocp();
        GLPK.glp_init_iocp(iocp);
        iocp.setPresolve(GLPKConstants.GLP_ON);
        // solve model
        ret = GLPK.glp_intopt(lp, iocp);
        // postsolve model
        if (ret == 0) {
            GLPK.glp_mpl_postsolve(tran, lp, GLPKConstants.GLP_MIP);
        }
        // free memory
        GLPK.glp_mpl_free_wksp(tran);
        GLPK.glp_delete_prob(lp);

        // do not listen for callbacks anymore
        GlpkCallback.removeListener(this);

    }

    @Override
    public void callback(glp_tree tree) {
        int reason = GLPK.glp_ios_reason(tree);
        if (reason == GLPKConstants.GLP_IBRANCH) {
            if (heuristic.compareTo(DRTOM) == 0) {
                driebeckTomlinDown(tree);
            } else if (heuristic.compareTo(MOSTFDOWN) == 0) {
                mostFractionalDown(tree);
            };
        }
    }

    /**
     * Finds a column to branch down on using the Driebeck Tomlin heuristic.
     * 
     * <ul>
     * <li>Driebeek NJ (1966) An algorithm for the solution of mixed
     * integer programming problems. Managem Sci 21:576–587</li>
     * <li>Tomlin JA (1971) An improved branch and bound method for integer
     * programming. Oper Res 19:1070–1075</li>
     * </ul>
     *
     * The implementation of the Driebeck Tomlin heuristic is based on coding
     * written by Andrew Makhorin and marked
     *
     * Copyright (C) 2000, 2001, 2002, 2003, 2004, 2005, 2006, 2007, 2008, 2009,
     * 2010, 2011 Andrew Makhorin, Department for Applied Informatics, Moscow
     * Aviation Institute, Moscow, Russia. All rights reserved. E-mail:
     * <mao@gnu.org>.
     *
     * @param tree branch and bound tree
     */
    public void driebeckTomlinDown(glp_tree tree) {
        glp_prob mip = GLPK.glp_ios_get_prob(tree);
        int n = GLPK.glp_get_num_cols(mip);
        int m = GLPK.glp_get_num_rows(mip);
        double delta_z;
        double degrad = -1;
        int jj = 0;
        int dir = GLPK.glp_get_obj_dir(mip);
        SWIGTYPE_p_int ind = GLPK.new_intArray(n + 1);
        SWIGTYPE_p_double val = GLPK.new_doubleArray(n + 1);
        for (int j = 1; j <= n; j++) {
            if (0 == GLPK.glp_ios_can_branch(tree, j)) {
                continue;
            }
            double x = GLPK.glp_get_col_prim(mip, j);
            int len = GLPK.glp_eval_tab_row(mip, m + j, ind, val);
            int k = GLPK.glp_dual_rtest(mip, len, ind, val, -1, 1e-9);
            if (k != 0) {
                k = GLPK.intArray_getitem(ind, k);
            }
            if (k == 0) {
                if (dir == GLPKConstants.GLP_MIN) {
                    delta_z = Double.MAX_VALUE;
                } else {
                    delta_z = -Double.MAX_VALUE;
                }
            } else {
                double dk;
                int stat;
                int t;
                for (t = 1; t <= len; t++) {
                    if (GLPK.intArray_getitem(ind, t) == k) {
                        break;
                    }
                }
                double alfa = GLPK.doubleArray_getitem(val, t);
                double delta_j = Math.floor(x);
                double delta_k = delta_j / alfa;
                if (k > m && GLPK.glp_get_col_kind(mip, k - m)
                        != GLPKConstants.GLP_CV) {
                    if (Math.abs(delta_k - Math.floor(delta_k + 0.5)) > 1e-3) {
                        if (delta_k > 0.0) {
                            delta_k = Math.ceil(delta_k);
                        } else {
                            delta_k = Math.floor(delta_k);
                        }
                    }
                }
                if (k <= m) {
                    stat = GLPK.glp_get_row_stat(mip, k);
                    dk = GLPK.glp_get_row_dual(mip, k);
                } else {
                    stat = GLPK.glp_get_col_stat(mip, k - m);
                    dk = GLPK.glp_get_col_dual(mip, k - m);
                }
                if (dir == GLPKConstants.GLP_MIN) {
                    if (stat == GLPKConstants.GLP_NL && dk < 0.0
                            || stat == GLPKConstants.GLP_NU && dk > 0.0
                            || stat == GLPKConstants.GLP_NF) {
                        dk = 0.0;
                    }
                } else {
                    if (stat == GLPKConstants.GLP_NL && dk > 0.0
                            || stat == GLPKConstants.GLP_NU && dk < 0.0
                            || stat == GLPKConstants.GLP_NF) {
                        dk = 0.0;
                    }
                }
                delta_z = dk * delta_k;
            }
            if (degrad < Math.abs(delta_z)) {
                jj = j;
                degrad = Math.abs(delta_z);
            }
        }
        GLPK.glp_ios_branch_upon(tree, jj, GLPKConstants.GLP_DN_BRNCH);
        GLPK.delete_doubleArray(val);
        GLPK.delete_intArray(ind);
    }

    /**
     * Finds the most fractional integer variable and marks it for branching
     * down.
     *
     * @param tree branch and bound tree
     */
    public void mostFractionalDown(glp_tree tree) {
        glp_prob lp = GLPK.glp_ios_get_prob(tree);
        int n = GLPK.glp_get_num_cols(lp);
        double frac = -1;
        int ifrac = 0;
        for (int i = 1; i <= n; i++) {
            if (0 != GLPK.glp_ios_can_branch(tree, i)) {
                double value = GLPK.glp_mip_col_val(lp, i);
                if (frac <= value - Math.floor(value)) {
                    ifrac = i;
                    frac = value - Math.floor(value);
                }
                if (frac <= Math.ceil(value) - value) {
                    ifrac = i;
                    frac = Math.ceil(value) - value;
                }
            }
        }
        GLPK.glp_ios_branch_upon(tree, ifrac, GLPKConstants.GLP_DN_BRNCH);
    }

}

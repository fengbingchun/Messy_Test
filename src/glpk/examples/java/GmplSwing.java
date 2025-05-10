/*
 *  Copyright (C) 2010 Heinrich Schuchardt
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Component;
import java.awt.Dimension;
import java.awt.Font;
import java.awt.Graphics;
import java.awt.Insets;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.WindowEvent;
import java.awt.event.WindowListener;
import java.io.BufferedReader;
import java.io.File;
import javax.swing.filechooser.FileFilter;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.net.URL;
import java.util.TreeSet;
import javax.swing.AbstractAction;
import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JEditorPane;
import javax.swing.JFileChooser;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JMenu;
import javax.swing.JMenuBar;
import javax.swing.JMenuItem;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JSplitPane;
import javax.swing.JTextArea;
import javax.swing.JToolBar;
import javax.swing.SwingUtilities;
import javax.swing.UIManager;
import javax.swing.UIManager.LookAndFeelInfo;
import javax.swing.UnsupportedLookAndFeelException;
import javax.swing.border.EtchedBorder;
import org.gnu.glpk.GLPK;
import org.gnu.glpk.GLPKConstants;
import org.gnu.glpk.GlpkCallback;
import org.gnu.glpk.GlpkCallbackListener;
import org.gnu.glpk.GlpkException;
import org.gnu.glpk.GlpkTerminal;
import org.gnu.glpk.GlpkTerminalListener;
import org.gnu.glpk.SWIGTYPE_p_int;
import org.gnu.glpk.glp_iocp;
import org.gnu.glpk.glp_prob;
import org.gnu.glpk.glp_tran;
import org.gnu.glpk.glp_tree;

/**
 *
 * @author Heinrich Schuchardt
 */
public class GmplSwing implements Runnable, GlpkTerminalListener,
        GlpkCallbackListener, ActionListener {

    public enum Status {

        RUN,
        TERMINATE,
        ABORT,
	ABORTING
    }
    private final static String TERMINATE = "TERMINATE";
    private final static String ABORT = "ABORT";
    String[] args;
    private Status terminate = Status.RUN;
    private String lookAndFeel = "Nimbus";
    private JEditorPane jEditorPane = null;
    private JFrame jFrame = null;
    private JMenuBar jMenuBar = null;
    private JMenu jMenuFile = null;
    private JMenuItem jMenuItemEvaluate = null;
    private JMenuItem jMenuItemExit = null;
    private JMenuItem jMenuItemNew = null;
    private JMenuItem jMenuItemOpen = null;
    private JMenuItem jMenuItemSave = null;
    private JMenuItem jMenuItemSaveAs = null;
    private JSplitPane verticalSplitPane = null;
    private JSplitPane horizontalSplitPane = null;
    private JLabel statusLabel = null;
    private JTextArea jTextArea = null;
    private JPanel outputPane = null;
    private String filename = null;
    private File path = null;
    private boolean running = false;
    private final Object plock = new Object();
    private final Object lock = new Object();
    private JButton terminateButton;
    private JButton abortButton;
    private TreeSet<Progress> progressTree = null;
    private Diagram diagram = null;

    /**
     * Constructor
     *
     * @param args command line parameters
     */
    private GmplSwing(String[] args) {
        this.args = args;
        GLPK.glp_java_set_numeric_locale("C");
    }

    @Override
    public void actionPerformed(ActionEvent e) {
        String cmd;
        cmd = e.getActionCommand();
        if (cmd.equals(TERMINATE)) {
            terminate = Status.TERMINATE;
        } else if (cmd.equals(ABORT)) {
            terminate = Status.ABORT;
        }
    }

    private void evaluate() {
        File tmpFile;
        FileWriter fw;
        glp_prob lp = null;
        glp_tran tran;
        glp_iocp iocp;

        String fname;
        int skip = 0;
        int ret;

        synchronized (lock) {
            if (running) {
                return;
            }
            running = true;
        }

        synchronized (plock) {
            progressTree = new TreeSet<Progress>();
        }
        diagram.paint();

        // set the terminal hook to call GlpkTerminal
        GLPK.glp_term_hook(null, null);
        try {
            tmpFile = File.createTempFile("glp", ".mod");

            fw = new FileWriter(tmpFile);
            fw.write(jEditorPane.getText());
            fw.close();
            fname = tmpFile.getCanonicalPath();
        } catch (IOException ex) {
            statusLabel.setForeground(Color.red);
            statusLabel.setText(ex.getMessage());
            return;
        }

        statusLabel.setForeground(Color.black);
        statusLabel.setText("Running");
        jTextArea.setText(null);
        jTextArea.setLineWrap(true);
        terminate = Status.RUN;

        // listen to callbacks
        GlpkCallback.addListener(this);
        // listen to terminal output
        try {
            GlpkTerminal.addListener(this);
        } catch (Exception ex) {
        }

        lp = GLPK.glp_create_prob();

        try {
            tran = GLPK.glp_mpl_alloc_wksp();
            ret = GLPK.glp_mpl_read_model(tran, fname, skip);
            if (ret != 0) {
                GLPK.glp_mpl_free_wksp(tran);
                GLPK.glp_delete_prob(lp);
                throw new RuntimeException("Model file not valid: " + fname);
            }

            // generate model
            ret = GLPK.glp_mpl_generate(tran, null);
            if (ret != 0) {
                GLPK.glp_mpl_free_wksp(tran);
                GLPK.glp_delete_prob(lp);
                throw new RuntimeException("Cannot generate model: " + fname);
            }
            // build model
            GLPK.glp_mpl_build_prob(tran, lp);
            // set solver parameters
            iocp = new glp_iocp();
            GLPK.glp_init_iocp(iocp);
            iocp.setPresolve(GLPKConstants.GLP_ON);
            // solve model
            ret = GLPK.glp_intopt(lp, iocp);
            // postsolve model
            GLPK.glp_mpl_postsolve(tran, lp, GLPKConstants.GLP_MIP);
            // free memory
            GLPK.glp_mpl_free_wksp(tran);
            GLPK.glp_delete_prob(lp);

            statusLabel.setText("Model has been processed successfully.");
            statusLabel.setForeground(Color.black);
        } catch (RuntimeException ex) {
            statusLabel.setText(ex.getMessage());
            statusLabel.setForeground(Color.red);
        } finally {
            // do not listen for callbacks anymore
            GlpkCallback.removeListener(this);
            // do not listen to output anymore
            GlpkTerminal.removeListener(this);
        }
        // free the environment as evaluate will be called again by
        // a different thread
        GLPK.glp_free_env();
        synchronized (lock) {
            running = false;
        }
    }

    /**
     * Exit application
     */
    public void exit() {
        // If an optimization is running, we want to abort it now.
        terminate = Status.ABORT;
        while (running) {
            try {
                Thread.sleep(500);
            } catch (InterruptedException ex) {
            }
        }
        // Leave application
        jFrame.setVisible(false);
        jFrame.dispose();
        System.exit(0);
    }

    private Diagram getDiagram() {
        if (diagram == null) {
            diagram = new Diagram();
        }
        return diagram;
    }

    /**
     * Create horizontal splitter
     *
     * @return horizontal splitter
     */
    private JSplitPane getHorizontalSplitPane() {
        if (horizontalSplitPane == null) {
            horizontalSplitPane = new JSplitPane(JSplitPane.HORIZONTAL_SPLIT);
            horizontalSplitPane.setTopComponent(
                    new JScrollPane(getJEditorPane()));
            horizontalSplitPane.setBottomComponent(
                    getOutputPane());
        }
        return horizontalSplitPane;
    }

    private JEditorPane getJEditorPane() {
        if (jEditorPane == null) {
            jEditorPane = new JEditorPane();
            jEditorPane.setFont(new Font(Font.MONOSPACED, Font.PLAIN, 12));
        }
        return jEditorPane;
    }

    /**
     * This method initializes the frame
     *
     * @return frame
     */
    private JFrame getJFrame() {
        ClassLoader loader;
        JPanel jPanel;
        if (jFrame == null) {
            URL url;
            url = GmplSwing.class.getClassLoader().getResource(
                    "application.png");
            jFrame = new JFrame(getClass().getName());
            if (url != null) {
                jFrame.setIconImage(new ImageIcon(url).getImage());
            }
            jFrame.setSize(new Dimension(2560, 2048));
            jFrame.setExtendedState(JFrame.MAXIMIZED_BOTH);
            jFrame.setJMenuBar(getJMenuBar());
            setTitle();
            jPanel = new JPanel();
            jPanel.setLayout(new BorderLayout());
            jPanel.add(getVerticalSplitPane(), BorderLayout.CENTER);
            jPanel.add(getStatusLabel(), BorderLayout.SOUTH);
            jFrame.setContentPane(jPanel);
        }
        return jFrame;
    }

    /**
     * This method initializes the menu bar
     *
     * @return menu bar
     */
    private JMenuBar getJMenuBar() {
        if (jMenuBar == null) {
            jMenuBar = new JMenuBar();
            jMenuBar.add(getJMenuFile());
        }
        return jMenuBar;
    }

    /**
     * This method initializes jMenuFile
     *
     * @return javax.swing.JMenu
     */
    private JMenu getJMenuFile() {
        if (jMenuFile == null) {
            jMenuFile = new JMenu("File");
            jMenuFile.add(getJMenuItemNew());
            jMenuFile.add(getJMenuItemOpen());
            jMenuFile.add(getJMenuItemEvaluate());
            jMenuFile.add(getJMenuItemSave());
            jMenuFile.add(getJMenuItemSaveAs());
            jMenuFile.addSeparator();
            jMenuFile.add(getJMenuItemExit());
        }
        return jMenuFile;
    }

    /**
     * This method initializes jMenuItemEvaluate
     *
     * @return javax.swing.JMenuItem
     */
    private JMenuItem getJMenuItemEvaluate() {
        if (jMenuItemEvaluate == null) {
            jMenuItemEvaluate = new JMenuItem("Evaluate");
            jMenuItemEvaluate.addActionListener(new EvaluateAction());
        }
        return jMenuItemEvaluate;
    }

    /**
     * This method initializes jMenuItemExit
     *
     * @return javax.swing.JMenuItem
     */
    private JMenuItem getJMenuItemExit() {
        if (jMenuItemExit == null) {
            jMenuItemExit = new JMenuItem("Exit");
            jMenuItemExit.addActionListener(new ExitAction());
        }
        return jMenuItemExit;
    }

    /**
     * This method initializes jMenuItemNew
     *
     * @return javax.swing.JMenuItem
     */
    private JMenuItem getJMenuItemNew() {
        if (jMenuItemNew == null) {
            jMenuItemNew = new JMenuItem("New");
            jMenuItemNew.addActionListener(new NewAction());
        }
        return jMenuItemNew;
    }

    /**
     * This method initializes jMenuItemOpen
     *
     * @return javax.swing.JMenuItem
     */
    private JMenuItem getJMenuItemOpen() {
        if (jMenuItemOpen == null) {
            jMenuItemOpen = new JMenuItem("Open");
            jMenuItemOpen.addActionListener(new OpenAction());
        }
        return jMenuItemOpen;
    }

    /**
     * This method initializes jMenuItemSave
     *
     * @return javax.swing.JMenuItem
     */
    private JMenuItem getJMenuItemSave() {
        if (jMenuItemSave == null) {
            jMenuItemSave = new JMenuItem("Save");
            jMenuItemSave.addActionListener(new SaveAction());
        }
        return jMenuItemSave;
    }

    /**
     * This method initializes jMenuItemSaveAs
     *
     * @return javax.swing.JMenuItem
     */
    private JMenuItem getJMenuItemSaveAs() {
        if (jMenuItemSaveAs == null) {
            jMenuItemSaveAs = new JMenuItem("SaveAs");
            jMenuItemSaveAs.addActionListener(new SaveAsAction());
        }
        return jMenuItemSaveAs;
    }

    private JPanel getOutputPane() {
        if (outputPane == null) {
            JToolBar toolbar = new JToolBar();
            terminateButton = new JButton("Terminate");
            terminateButton.setActionCommand(TERMINATE);
            terminateButton.addActionListener(this);
            abortButton = new JButton("Abort");
            abortButton.setActionCommand(ABORT);
            abortButton.addActionListener(this);
            toolbar.setFloatable(false);
            toolbar.add(terminateButton);
            toolbar.add(abortButton);
            outputPane = new JPanel();
            outputPane.setLayout(new BorderLayout());
            outputPane.add(toolbar, BorderLayout.NORTH);
            outputPane.add(new JScrollPane(getJTextArea()), BorderLayout.CENTER);

        }
        return outputPane;
    }

    private JLabel getStatusLabel() {
        if (statusLabel == null) {
            statusLabel = new JLabel();
            statusLabel.setBorder(new TopEtchedBorder());
            statusLabel.setPreferredSize(new Dimension(0, 24));
        }
        return statusLabel;
    }

    private JTextArea getJTextArea() {
        if (jTextArea == null) {
            jTextArea = new JTextArea();
            jTextArea.setEditable(false);
        }
        return jTextArea;
    }

    /**
     * This method initializes the vertical splitter
     *
     * @return
     */
    private JSplitPane getVerticalSplitPane() {
        if (verticalSplitPane == null) {
            verticalSplitPane = new JSplitPane(JSplitPane.VERTICAL_SPLIT);
            verticalSplitPane.setTopComponent(getHorizontalSplitPane());
            verticalSplitPane.setBottomComponent(getDiagram());
        }
        return verticalSplitPane;
    }

    private void newFile() {
        filename = null;
        setTitle();
        jEditorPane.setText("");
    }

    private void open() {

        File file;
        JFileChooser jFileChooser;

        jFileChooser = new JFileChooser();
        jFileChooser.addChoosableFileFilter(new ModelFileFilter());
        jFileChooser.setCurrentDirectory(path);

        if (jFileChooser.showOpenDialog(getJFrame())
                != JFileChooser.APPROVE_OPTION) {
            return;
        }

        file = jFileChooser.getSelectedFile();
        if (!file.exists()
                && jFileChooser.getFileFilter() instanceof ModelFileFilter
                && !file.getName().contains(".")) {
            file = new File(file.getAbsolutePath() + ".mod");
        }

        readFile(file);
    }

    /**
     * Read model file
     *
     * @param file file
     * @return model
     */
    private void readFile(File file) {
        String text = "";
        String str;
        BufferedReader bufferedReader = null;
        try {
            bufferedReader = new BufferedReader(new FileReader(file));
            while ((str = bufferedReader.readLine()) != null) {
                text += str + "\n";
            }
            filename = file.getCanonicalPath();
            path = file.getParentFile();
            setTitle();
            statusLabel.setForeground(Color.black);
            statusLabel.setText("File read");
        } catch (IOException ex) {
            statusLabel.setText(ex.getMessage());
            statusLabel.setForeground(Color.red);
        } finally {
            if (bufferedReader != null) {
                try {
                    bufferedReader.close();
                    jEditorPane.setText(text);
                } catch (IOException ex) {
                }
            }
        }

    }

    @Override
    public void run() {
        setLookAndFeel();
        getJFrame().addWindowListener(new WindowClosingListener());
        getJFrame().setDefaultCloseOperation(JFrame.DO_NOTHING_ON_CLOSE);
        getJFrame().setVisible(true);
        verticalSplitPane.setDividerLocation(.75);
        horizontalSplitPane.setDividerLocation(.5);
        if (args.length == 1) {
            readFile(new File(args[0]));
        }
    }

    private void save() {
        writeFile(new File(filename));
    }

    private void saveAs() {
        File file;
        JFileChooser jFileChooser;

        jFileChooser = new JFileChooser();
        jFileChooser.addChoosableFileFilter(new ModelFileFilter());
        jFileChooser.setCurrentDirectory(path);

        for (;;) {
            if (jFileChooser.showSaveDialog(getJFrame())
                    != JFileChooser.APPROVE_OPTION) {
                statusLabel.setForeground(Color.black);
                statusLabel.setText("File save aborted by user");
                return;
            }
            try {
                file = new File(
                        jFileChooser.getSelectedFile().getCanonicalPath());
                if (!file.exists()
                        && jFileChooser.getFileFilter() instanceof ModelFileFilter
                        && !file.getName().contains(".")) {
                    file = new File(file.getAbsolutePath() + ".mod");
                }
                if (file.exists()) {
                    // File exists already
                    switch (JOptionPane.showConfirmDialog(
                            jFrame, "Replace existing file?")) {
                        case JOptionPane.NO_OPTION:
                            // User does not want to overwrite
                            continue;
                        case JOptionPane.CANCEL_OPTION:
                            statusLabel.setForeground(Color.black);
                            statusLabel.setText("File save aborted by user");
                            return;
                    }
                }
                writeFile(file);
                return;
            } catch (IOException ex) {
                statusLabel.setForeground(Color.red);
                statusLabel.setText(ex.getMessage());
            }
        }
    }

    /**
     * Set look and feel
     */
    private void setLookAndFeel() {
        try {
            for (LookAndFeelInfo info : UIManager.getInstalledLookAndFeels()) {
                if (lookAndFeel.equals(info.getName())) {
                    UIManager.setLookAndFeel(info.getClassName());
                    break;
                }
            }
        } catch (UnsupportedLookAndFeelException e) {
            // handle exception
        } catch (ClassNotFoundException e) {
            // handle exception
        } catch (InstantiationException e) {
            // handle exception
        } catch (IllegalAccessException e) {
            // handle exception
        }
    }

    private void setTitle() {
        String str = "untitled";
        if (filename != null) {
            str = filename;
        }
        jFrame.setTitle(this.getClass().getSimpleName()
                + " - " + str);
    }

    private void writeFile(File file) {
        FileWriter fw = null;
        try {
            fw = new FileWriter(file);
            fw.write(getJEditorPane().getText());
            filename = file.getCanonicalPath();
            path = file.getParentFile();
            setTitle();
            statusLabel.setText("File saved.");
        } catch (IOException ex) {
            statusLabel.setForeground(Color.red);
            statusLabel.setText(ex.getMessage());
        } finally {
            if (fw != null) {
                try {
                    fw.close();
                } catch (IOException ex) {
                }
            }
        }
    }

    /**
     * Starts the Application
     *
     * @param args command line parameters
     */
    public static void main(String[] args) {
        SwingUtilities.invokeLater(new GmplSwing(args));
    }

    @Override
    public boolean output(final String str) {

        if (terminate == Status.ABORT) {
            // remove terminal listeners
            GlpkTerminal.removeAllListeners();

            try {
	        terminate = Status.ABORTING;
                GLPK.glp_java_error("Aborting due to user request");
            } catch (GlpkException ex) {
            } finally {
                return false;
            }
        }

        SwingUtilities.invokeLater(
                new Runnable() {

                    @Override
                    public void run() {
                        jTextArea.append(str);
                    }
                });
        return false;
    }

    @Override
    public void callback(glp_tree tree) {

        glp_prob prob;
        prob = GLPK.glp_ios_get_prob(tree);
        int a_cnt;
        int n_cnt;
        int t_cnt;
        int reason;
        int status;
        SWIGTYPE_p_int p_a = GLPK.new_intArray(1);
        SWIGTYPE_p_int p_n = GLPK.new_intArray(1);
        SWIGTYPE_p_int p_t = GLPK.new_intArray(1);
        if (terminate != Status.RUN) {
            GLPK.glp_ios_terminate(tree);
            return;
        }

        reason = GLPK.glp_ios_reason(tree);
        status = GLPK.glp_mip_status(GLPK.glp_ios_get_prob(tree));

        if (reason == GLPKConstants.GLP_ISELECT
                || reason == GLPKConstants.GLP_IBINGO) {

            int bestNode;
            double bestBound;
            double bestValue;
            int lastCount;
            bestNode = GLPK.glp_ios_best_node(tree);
            bestBound = GLPK.glp_ios_node_bound(tree, bestNode);
            bestValue = GLPK.glp_mip_obj_val(GLPK.glp_ios_get_prob(tree));
            GLPK.glp_ios_tree_size(tree, p_a, p_n, p_t);
            a_cnt = GLPK.intArray_getitem(p_a, 0);
            n_cnt = GLPK.intArray_getitem(p_n, 0);
            t_cnt = GLPK.intArray_getitem(p_t, 0);

            if (progressTree.isEmpty()) {
                lastCount = 0;
            } else {
                lastCount = progressTree.last().evaluatedNodes;
            }
            Progress p = new Progress();
            p.evaluatedNodes = t_cnt - a_cnt;
            if (p.evaluatedNodes == 0) {
                return;
            }
            p.bestSolution = bestValue;
            p.lowerBound = bestBound;
            p.status = status;
            synchronized (plock) {
                progressTree.add(p);
            }
            if (lastCount < p.evaluatedNodes) {
                diagram.paint();
            }
        }
    }

    /**
     * Listener for menu item "Open".
     */
    private class OpenAction extends AbstractAction {

        private static final long serialVersionUID = 7326124121439143329L;

        @Override
        public void actionPerformed(ActionEvent arg0) {
            open();
        }
    }

    /**
     * Listener for menu item "Save".
     */
    private class SaveAction extends AbstractAction {

        private static final long serialVersionUID = 7326124121439143329L;

        @Override
        public void actionPerformed(ActionEvent arg0) {
            if (filename == null) {
                saveAs();
            } else {
                save();
            }
        }
    }

    /**
     * Listener for menu item "SaveAs".
     */
    private class SaveAsAction extends AbstractAction {

        private static final long serialVersionUID = 7326124121439143329L;

        @Override
        public void actionPerformed(ActionEvent arg0) {
            saveAs();
        }
    }

    /**
     * Listener for menu item "Evaluate".
     */
    private class EvaluateAction extends AbstractAction {

        private static final long serialVersionUID = 7326124121439143329L;

        @Override
        public void actionPerformed(ActionEvent arg0) {
            new EvaluateThread().start();
        }
    }

    private class EvaluateThread extends Thread {

        @Override
        public void run() {
            evaluate();
        }
    }

    /**
     * Listener for menu item "Exit".
     */
    private class ExitAction extends AbstractAction {

        private static final long serialVersionUID = 3256140765884925290L;

        @Override
        public void actionPerformed(ActionEvent arg0) {
            exit();
        }
    }

    /**
     * Listener for menu item "Exit".
     */
    private class NewAction extends AbstractAction {

        private static final long serialVersionUID = -5867871767895097849L;

        @Override
        public void actionPerformed(ActionEvent arg0) {
            newFile();
        }
    }

    /**
     * File filter for simulation model files, implements singleton pattern.
     */
    private class ModelFileFilter
            extends FileFilter {

        @Override
        public boolean accept(File f) {
            return f.getName().toLowerCase().endsWith(".mod")
                    || f.isDirectory();
        }

        @Override
        public String getDescription() {
            return "Model File (*.mod)";
        }
    }

    /**
     * WindowListener to react upon closing of the JFrame
     */
    private class WindowClosingListener implements WindowListener {

        @Override
        public void windowActivated(WindowEvent e) {
        }

        @Override
        public void windowClosed(WindowEvent e) {
        }

        @Override
        public void windowClosing(WindowEvent e) {
            exit();
        }

        @Override
        public void windowDeactivated(WindowEvent e) {
        }

        @Override
        public void windowDeiconified(WindowEvent e) {
        }

        @Override
        public void windowIconified(WindowEvent e) {
        }

        @Override
        public void windowOpened(WindowEvent e) {
        }
    }

    /**
     * Border style which is etched only on the top, to be used for the status
     * bar.
     */
    private class TopEtchedBorder extends EtchedBorder {

        @Override
        public Insets getBorderInsets(Component c) {
            return new Insets(2, 0, 0, 0);
        }

        @Override
        public void paintBorder(Component c, Graphics g, int x, int y,
                int width, int height) {
            int w = width;

            g.translate(x, y);

            g.setColor(etchType == LOWERED ? getShadowColor(c)
                    : getHighlightColor(c));
            g.drawLine(0, 0, w - 1, 0);

            g.setColor(etchType == LOWERED ? getHighlightColor(c)
                    : getShadowColor(c));
            g.drawLine(0, 1, w - 1, 1);

            g.translate(-x, -y);
        }
    }

    /**
     * One point in the progress chart
     */
    private class Progress implements Comparable<Progress> {

        public Integer evaluatedNodes;
        public double lowerBound;
        public double bestSolution;
        public int status;

        @Override
        public int compareTo(Progress o) {
            return evaluatedNodes.compareTo(o.evaluatedNodes);
        }
    }

    /*
     * Diagram showing the progress of the MIP solution process.
     * The x-axis is used for the number of evaluated nodes.
     * A green line shows the development of the best MIP solution.
     * A red line shows the development of the best bound.
     */
    private class Diagram extends JPanel {

        /**
         * Repaint using the AWT event dispatching thread.
         */
        public void paint() {
            final Diagram diagram = this;
            SwingUtilities.invokeLater(
                    new Runnable() {

                        @Override
                        public void run() {
                            diagram.repaint();
                        }
                    });
        }

        @Override
        public void paintComponent(Graphics g) {
            Dimension size = getSize();
            int height = size.height - 1;
            int width = size.width - 1;
            double xmax;
            double ymin;
            double ymax;
            Progress last = null;

            // paint packground in black
            g.setColor(Color.BLACK);
            g.fillRect(0, 0, size.width, size.height);

            if (height < 2) {
                return;
            }
            if (width < 2) {
                return;
            }

            synchronized (plock) {
                if (progressTree == null) {
                    return;
                }
                if (progressTree.isEmpty()) {
                    return;
                }

                // Determine the enclosing rectable of the graph
                xmax = progressTree.last().evaluatedNodes;
                if (xmax == 0) {
                    return;
                }
                ymax = -Double.MAX_VALUE;
                ymin = Double.MAX_VALUE;
                for (Progress p : progressTree) {
                    if (p.status == GLPKConstants.GLP_FEAS
                            || p.status == GLPKConstants.GLP_OPT) {
                        if (p.bestSolution < ymin) {
                            ymin = p.bestSolution;
                        }
                        if (p.bestSolution > ymax) {
                            ymax = p.bestSolution;
                        }
                    }
                    if (p.lowerBound > -1e300 && p.lowerBound < 1e300) {
                        if (p.lowerBound < ymin) {
                            ymin = p.lowerBound;
                        }
                        if (p.lowerBound > ymax) {
                            ymax = p.lowerBound;
                        }
                    }
                }
                if (ymax <= ymin) {
                    return;
                }
                for (Progress p : progressTree) {
                    if (last != null) {
                        g.setColor(Color.red);
                        g.drawLine(
                                (int) (last.evaluatedNodes / xmax * width),
                                (int) ((ymax - last.lowerBound) / (ymax - ymin) * height),
                                (int) (p.evaluatedNodes / xmax * width),
                                (int) ((ymax - p.lowerBound) / (ymax - ymin) * height));

                        if (last.status == GLPKConstants.GLP_FEAS
                                || last.status == GLPKConstants.GLP_OPT) {
                            g.setColor(Color.green);
                            g.drawLine(
                                    (int) (last.evaluatedNodes / xmax * width),
                                    (int) ((ymax - last.bestSolution) / (ymax - ymin) * height),
                                    (int) (p.evaluatedNodes / xmax * width),
                                    (int) ((ymax - p.bestSolution) / (ymax - ymin) * height));
                        }
                    }
                    last = p;
                }
            }
        }
    }
}

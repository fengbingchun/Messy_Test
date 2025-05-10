%module GLPK

%include "keyword.i"

%pragma(csharp) imclassclassmodifiers="
[global::System.CLSCompliant(false)]
public class "

/* As there is no good transformation for va_list
 * we will just do nothing.
 * cf. http://swig.org/Doc3.0/SWIGDocumentation.html#Varargs_nn8
 */
%typemap(in) (va_list arg) {
}

/* The function glp_term_hook is modified to preset
 * the callback function.
 */
%exception glp_term_hook  {
  arg1 = glp_cli_term_hook;
  arg2 = NULL;
  $action
}

/* The function glp_init_iocp is modified to preset
 * the callback function.
 */
%typemap(out) void glp_init_iocp {
  arg1->cb_func = glp_cli_cb;
  arg1->cb_info = NULL;
}

%{
#include "glpk.h"
#include "glpk_cli.h"
#include <locale.h>
#include <setjmp.h>
#include "config.h"

typedef void (SWIGSTDCALL* CSharpGlpkCallback_t)(void*);
typedef int (SWIGSTDCALL* CSharpGlpkTerminal_t)(const char*);

/*
 * Callback functions.
 */
CSharpGlpkCallback_t glpkCallback = NULL;
CSharpGlpkTerminal_t glpkTerminal = NULL;

/*
 * Function declarations
 */
int glp_cli_term_hook(void *info, const char *s);
void glp_cli_error_hook(void *in);

/*
 * Static variables to handle errors inside callbacks
 */
#define GLP_CLI_MAX_CALLBACK_LEVEL 4
TLS int glp_cli_callback_level = 0;
TLS int glp_cli_error_occured = 0;
TLS jmp_buf *glp_cli_callback_env[GLP_CLI_MAX_CALLBACK_LEVEL];

/*
 * Message level.
 */
TLS int glp_cli_msg_level = GLP_CLI_MSG_LVL_OFF;

/**
 * Abort with error message.
 */
void glp_cli_error(char *message) {
    glp_error("%s\n", message);
}

/**
 * Set message level.
 */
void glp_cli_set_msg_lvl(int msg_lvl) {
    glp_cli_msg_level = msg_lvl;
}

/**
 * Set locale for number formatting.
 */
void glp_cli_set_numeric_locale(const char *locale) {
    setlocale(LC_NUMERIC, locale);
}

/**
 * Registers delegate for terminal hook method.
 */
extern SWIGEXPORT void SWIGSTDCALL
    registerGlpkTerminal(CSharpGlpkTerminal_t value) {
        glpkTerminal = value;
}

/**
 * Terminal hook function.
 */
int glp_cli_term_hook(void *info, const char *s) {
    int ret = 0;

    glp_cli_callback_level++;
    if (glp_cli_callback_level >= GLP_CLI_MAX_CALLBACK_LEVEL) {
        glp_cli_error_occured = 1;
    } else {
        glp_cli_error_occured = 0;
        if (glpkTerminal) {
            ret = glpkTerminal(s);
        }
    }
    glp_cli_callback_level--;
    if (glp_cli_error_occured) {
       longjmp(*glp_cli_callback_env[glp_cli_callback_level], 1);
    }
    return ret;
}

/**
 * Registers delegate for MIP callback method.
 */
extern SWIGEXPORT
    void SWIGSTDCALL registerGlpkCallback(CSharpGlpkCallback_t value) {
        glpkCallback = value;
}

/**
 * Call back function for MIP solver
 */
void glp_cli_cb(glp_tree *tree, void *info) {

    glp_cli_callback_level++;
    if (glp_cli_callback_level >= GLP_CLI_MAX_CALLBACK_LEVEL) {
        glp_cli_error_occured = 1;
    } else {
        glp_cli_error_occured = 0;
        if (glpkCallback) {
            glpkCallback(tree);
        }
    }
    glp_cli_callback_level--;
    if (glp_cli_error_occured) {
       longjmp(*glp_cli_callback_env[glp_cli_callback_level], 1);
    }
}

/**
 * This hook function will be processed if an error occured
 * calling the glpk library
 * @param in pointer to long jump environment
 */
void glp_cli_error_hook(void *in) {
    glp_cli_error_occured = 1;
    /* free GLPK memory */
    glp_free_env();
    /* safely return */
    longjmp(*((jmp_buf*)in), 1);
}

/**
 * Get arc data.
 *
 * @param arc arc
 * @return data
 */
glp_cli_arc_data *glp_cli_arc_get_data(const glp_arc *arc) {
    return (glp_cli_arc_data *) arc->data;
}

/**
 * Get vertex
 *
 * @param G graph
 * @param i index
 * @return vertex
 */
glp_vertex *glp_cli_vertex_get(
      const glp_graph *G, const int i) {

    if (i < 1 || i > G->nv) {
        glp_error( "Index %d is out of range.\n", i);
    }
    return G->v[i];
}

/**
 * Get vertex data.
 *
 * @param G graph
 * @param i index to vertex
 * @return data
 */
glp_cli_vertex_data *glp_cli_vertex_data_get(
        const glp_graph *G, const int i) {

    if (i < 1 || i > G->nv) {
        glp_error( "Index %d is out of range.\n", i);
    }
    return (glp_cli_vertex_data *) G->v[i]->data;
}

/**
 * Get vertex data.
 *
 * @param v vertex
 * @return data
 */
glp_cli_vertex_data *glp_cli_vertex_get_data(
        const glp_vertex *v) {

    return v->data;
}

%}

// Add handling for structures
%include "glpk_cli_structures.i"
%glp_structure(glp_arc)
%glp_structure(glp_graph)
%glp_structure(glp_vertex)

%pragma(csharp) imclasscode=%{
    class GlpkTerminalHelper {
        public delegate int GlpkTerminalDelegate(System.IntPtr msg);
        static GlpkTerminalDelegate glpkTerminalDelegate =
            new GlpkTerminalDelegate(callback);

        static int callback(System.IntPtr msg) {
            return org.gnu.glpk.GlpkTerminal.callback(
                System.Runtime.InteropServices.Marshal.PtrToStringAnsi(msg));
        }

        [global::System.Runtime.InteropServices.DllImport(
                "$dllimport", EntryPoint="registerGlpkTerminal")]
        public static extern
                void registerGlpkTerminal(
                        GlpkTerminalDelegate value);

        static GlpkTerminalHelper() {
            registerGlpkTerminal(glpkTerminalDelegate);
        }
    }
    static GlpkTerminalHelper glpkTerminalHelper = new GlpkTerminalHelper();
    // This method is only introduced to avoid a warning.
    private static GlpkTerminalHelper getGlpkTerminalHelper() {
        return glpkTerminalHelper;
    }
%}

%pragma(csharp) imclasscode=%{
    class GlpkCallbackHelper {
        public delegate void GlpkCallbackDelegate(System.IntPtr tree);
        static GlpkCallbackDelegate glpkCallbackDelegate =
            new GlpkCallbackDelegate(callback);

        static void callback(System.IntPtr tree) {
            org.gnu.glpk.GlpkCallback.callback(tree);
        }

        [global::System.Runtime.InteropServices.DllImport(
                "$dllimport", EntryPoint="registerGlpkCallback")]
        public static extern
                void registerGlpkCallback(
                        GlpkCallbackDelegate value);

        static GlpkCallbackHelper() {
            registerGlpkCallback(glpkCallbackDelegate);
        }
    }
    static GlpkCallbackHelper glpkCallbackHelper = new GlpkCallbackHelper();
    // This method is only introduced to avoid a warning.
    private static GlpkCallbackHelper getGlpkCallbackHelper() {
        return glpkCallbackHelper;
    }
%}

// Exception handling
%insert(runtime) %{
    // Code to handle throwing of C# CustomApplicationException from
    // C/C++ code. The equivalent delegate to the callback,
    // CSharpExceptionCallback_t, is CustomExceptionDelegate
    // and the equivalent customExceptionCallback instance is customDelegate.
    typedef void (SWIGSTDCALL* CSharpExceptionCallback_t)(const char *);
    CSharpExceptionCallback_t customExceptionCallback = NULL;

    extern SWIGEXPORT
    void SWIGSTDCALL CustomExceptionRegisterCallback(CSharpExceptionCallback_t customCallback) {
      customExceptionCallback = customCallback;
    }

    // Note that SWIG detects any method calls named starting with
    // SWIG_CSharpSetPendingException
    static void SWIG_CSharpSetPendingExceptionCustom(const char *msg) {
      customExceptionCallback(msg);
    }
%}

%pragma(csharp) imclasscode=%{
    class CustomExceptionHelper {
        // C# delegate for the C/C++ customExceptionCallback
        public delegate void CustomExceptionDelegate(string message);
        static CustomExceptionDelegate customDelegate =
                new CustomExceptionDelegate(SetPendingCustomException);

        [global::System.Runtime.InteropServices.DllImport(
                "$dllimport", EntryPoint="CustomExceptionRegisterCallback")]
        public static extern
                void CustomExceptionRegisterCallback(
                        CustomExceptionDelegate customCallback);

        static void SetPendingCustomException(string message) {
                SWIGPendingException.Set(new GlpkException(message));
        }

        static CustomExceptionHelper() {
                CustomExceptionRegisterCallback(customDelegate);
        }
    }
    static CustomExceptionHelper exceptionHelper = new CustomExceptionHelper();
    // This method is only introduced to avoid a warning.
    private static CustomExceptionHelper getExceptionHelper() {
        return exceptionHelper;
    }
%}


%exception {
    jmp_buf glp_cli_env;

    if (glp_cli_msg_level != GLP_CLI_MSG_LVL_OFF) {
        glp_printf("entering function $name.\n");
    }
    glp_cli_callback_env[glp_cli_callback_level] = &glp_cli_env;
    if (setjmp(glp_cli_env)) {
        SWIG_CSharpSetPendingExceptionCustom("function $name failed");
    } else {
        glp_error_hook(glp_cli_error_hook, &glp_cli_env);
        $action;
    }
    glp_cli_callback_env[glp_cli_callback_level] = NULL;
    glp_error_hook(NULL, NULL);
    if (glp_cli_msg_level != GLP_CLI_MSG_LVL_OFF) {
        glp_printf("leaving function $name.\n");
    }
}

%include "glpk_cli_arrays.i"
%glp_array_functions(double, doubleArray);
%glp_array_functions(int, intArray);

%include "glpk_cli.i"
%include "glpk_doc.i"
%include "glpk.h"

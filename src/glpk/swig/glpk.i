%module GLPK

%pragma(java) jniclassclassmodifiers="
  /**
   * The intermediary JNI class.
   * Loads the native library.
   */
   public class"

%pragma(java) jniclasscode=%{
  static {
    try {
      if (System.getProperty("os.name").toLowerCase().contains("windows")) {
        // try to load Windows libraries
%}
#ifdef GLPKPRELOAD
%pragma(java) jniclasscode=%{
        try {
          System.loadLibrary("glpk_4_65");
        } catch (UnsatisfiedLinkError en) {
          // The dependent library might be in the OS library search path.
        }
%}
#endif
%pragma(java) jniclasscode=%{
        System.loadLibrary("glpk_4_65_java");
      } else {
        // try to load Linux library
%}
#ifdef GLPKPRELOAD
%pragma(java) jniclasscode=%{
        try {
          System.loadLibrary("glpk");
        } catch (UnsatisfiedLinkError e) {
          // The dependent library might be in the OS library search path.
        }
%}
#endif
%pragma(java) jniclasscode=%{
        System.loadLibrary("glpk_java");
      }
    } catch (UnsatisfiedLinkError e) {
      /**
       * Information string.
       */
      String info = "\n"
        + "The dynamic link library for GLPK for Java could not be "
        + "loaded.\nConsider using\njava -Djava.library.path=\n"
        + "The current value of system property java.library.path is:\n"
        + System.getProperty("java.library.path") + "\n\n";

      try {
          /**
           * Number of bits.
           */
          String bits = null;

          bits = System.getProperty("com.ibm.vm.bitmode");
          if (bits == null) {
              bits = System.getProperty("sun.arch.data.model");
          }

          info +=
            "java.vendor: " + System.getProperty("java.vendor")
            + "\njava.version: "
            + System.getProperty("java.version")
            + "\njava.vm.name: "
            + System.getProperty("java.vm.name")
            + "\njava.vm.version: "
            + System.getProperty("java.vm.version")
            + "\njava.runtime.version: "
            + System.getProperty("java.runtime.version");
          if (bits != null) {
              info += "\ndata model: " + bits + " bit";
          }
      } catch (SecurityException ex) {
          info += "\n\n";
          info += ex.getMessage();
      }
      info += "\n";
      System.err.println(info);
      throw e;  
    }
  }
%}

/* As there is no good transformation for va_list
 * we will just do nothing.
 * cf. http://swig.org/Doc1.3/SWIGDocumentation.html#Varargs_nn8
 * This typemap is necessary to compile on amd64
 * Linux. 
 */
%typemap(in) (va_list arg) {
}

/* The function glp_term_hook is modified to preset
 * the callback function.
 */
%exception glp_term_hook  { 
  arg1 = glp_java_term_hook;
  arg2 = (void *) jenv;
  $action
}

/* The function glp_init_iocp is modified to preset
 * the callback function.
 */
%typemap(out) void glp_init_iocp {
  arg1->cb_func = glp_java_cb;
  arg1->cb_info = (void *) jenv;
}

%{
#include "glpk.h"
#include "glpk_java.h"
#include <locale.h>
#include <setjmp.h>
#include <jni.h>
#include <config.h>

/*
 * Function declarations
 */
int glp_java_term_hook(void *info, const char *s);
void glp_java_error_hook(void *in);

/*
 * Static variables to handle errors inside callbacks
 */
#define GLP_JAVA_MAX_CALLBACK_LEVEL 4
TLS int glp_java_callback_level = 0;
TLS int glp_java_error_occured = 0;
TLS jmp_buf *glp_java_callback_env[GLP_JAVA_MAX_CALLBACK_LEVEL];

/*
 * Message level.
 */
TLS int glp_java_msg_level = GLP_JAVA_MSG_LVL_OFF;

/**
 * Aborts with error message.
 */
void glp_java_error(char *message) {
    glp_error("%s\n", message);
}

/**
 * Sets message level.
 */
void glp_java_set_msg_lvl(int msg_lvl) {
    glp_java_msg_level = msg_lvl;
}

/**
 * Sets locale for number formatting.
 */
void glp_java_set_numeric_locale(const char *locale) {
    setlocale(LC_NUMERIC, locale);
    }

/**
 * Terminal hook function.
 */
int glp_java_term_hook(void *info, const char *s) {
    jclass cls;
    jmethodID mid = NULL;
    JNIEnv *env = (JNIEnv *) info;
    jstring str = NULL;
    jint ret = 0;

    glp_java_callback_level++;
    if (glp_java_callback_level >= GLP_JAVA_MAX_CALLBACK_LEVEL) {
        glp_java_error_occured = 1;
    } else {
        glp_java_error_occured = 0;
        cls = (*env)->FindClass(env, "org/gnu/glpk/GlpkTerminal");
        if (cls != NULL) {
            mid = (*env)->GetStaticMethodID(
                env, cls, "callback", "(Ljava/lang/String;)I");
            if (mid != NULL) {
                str = (*env)->NewStringUTF(env, s);
                ret = (*env)->CallStaticIntMethod(env, cls, mid, str);
                if (str != NULL) {
                    (*env)->DeleteLocalRef( env, str );
                }
            }
            (*env)->DeleteLocalRef( env, cls );
        }
    }
    glp_java_callback_level--;
    if (glp_java_error_occured) {
       longjmp(*glp_java_callback_env[glp_java_callback_level], 1);
    }
    return ret;
}

/**
 * Call back function for MIP solver.
 */
void glp_java_cb(glp_tree *tree, void *info) {
    jclass cls;
    jmethodID mid = NULL;
    JNIEnv *env = (JNIEnv *) info;
    jlong ltree;

    glp_java_callback_level++;
    if (glp_java_callback_level >= GLP_JAVA_MAX_CALLBACK_LEVEL) {
        glp_java_error_occured = 1;
    } else {
        glp_java_error_occured = 0;
        cls = (*env)->FindClass(env, "org/gnu/glpk/GlpkCallback");
        if (cls != NULL) {
            mid = (*env)->GetStaticMethodID(
                env, cls, "callback", "(J)V");
        }
        if (mid != NULL) {
            *(glp_tree **)&ltree = tree;
            (*env)->CallStaticVoidMethod(env, cls, mid, ltree);
        }
        if (cls != NULL) {
            (*env)->DeleteLocalRef( env, cls );
        }
    }
    glp_java_callback_level--;
    if (glp_java_error_occured) {
       longjmp(*glp_java_callback_env[glp_java_callback_level], 1);
    }
}

/**
 * This hook function will be processed if an error occured
 * calling the glpk library.
 *
 * @param in pointer to long jump environment
 */
void glp_java_error_hook(void *in) {
    glp_java_error_occured = 1;
    /* free GLPK memory */
    glp_free_env();
    /* safely return */
    longjmp(*((jmp_buf*)in), 1);
}

/**
 * This function is used to throw a Java exception.
 *
 * @param env Java environment
 * @param message detail message
 */
void glp_java_throw(JNIEnv *env, char *message) {
    jclass newExcCls;
    newExcCls = (*env)->FindClass(env, "org/gnu/glpk/GlpkException");
    if (newExcCls == NULL) {
        newExcCls = (*env)->FindClass(env, "java/lang/IllegalArgumentException");
    }
    if (newExcCls != NULL) {
        (*env)->ThrowNew(env, newExcCls, message);
    }
}

/**
 * This function is used to throw a java.lang.OutOfMemoryError.
 *
 * @param env Java environment
 * @param message detail message
 */
void glp_java_throw_outofmemory(JNIEnv *env, char *message) {
    jclass newExcCls;
    newExcCls = (*env)->FindClass(env, "java/lang/OutOfMemoryError");
    if (newExcCls != NULL) {
        (*env)->ThrowNew(env, newExcCls, message);
    }
}

/**
 * Gets arc data.
 *
 * @param arc arc
 * @return data
 */
glp_java_arc_data *glp_java_arc_get_data(const glp_arc *arc) {
   return (glp_java_arc_data *) arc->data;
}

/**
 * Gets vertex.
 *
 * @param G graph
 * @param i index
 * @return vertex
 */
glp_vertex *glp_java_vertex_get(
      const glp_graph *G, const int i) {
   if (i < 1 || i > G->nv) {
      glp_error( "Index %d is out of range.\n", i);
   }
   return G->v[i];
}

/**
 * Gets vertex data.
 *
 * @param G graph
 * @param i index to vertex
 * @return data
 */
glp_java_vertex_data *glp_java_vertex_data_get(
      const glp_graph *G, const int i) {
   if (i < 1 || i > G->nv) {
      glp_error( "Index %d is out of range.\n", i);
   }
   return (glp_java_vertex_data *) G->v[i]->data;
}

/**
 * Gets vertex data.
 *
 * @param v vertex
 * @return data
 */
glp_java_vertex_data *glp_java_vertex_get_data(
      const glp_vertex *v) {
   return v->data;
}

%}

// Add handling for structures
%include "glpk_java_structures.i"
%glp_structure(glp_arc)
%glp_structure(glp_graph)
%glp_structure(glp_vertex)

// Add handling for arrays
%include "glpk_java_arrays.i"
%glp_array_functions(int, intArray)
%glp_array_functions(double, doubleArray)

// Add handling for String arrays in glp_main
%include "various.i"
%apply char **STRING_ARRAY { const char *argv[] };

// Exception handling
%exception {
    jmp_buf glp_java_env;

    if (glp_java_msg_level != GLP_JAVA_MSG_LVL_OFF) {
        glp_printf("entering function $name.\n");
    }
    glp_java_callback_env[glp_java_callback_level] = &glp_java_env;
    if (setjmp(glp_java_env)) {
        glp_java_throw(jenv, "function $name failed");
    } else {
        glp_error_hook(glp_java_error_hook, &glp_java_env);
        $action;
    }
    glp_java_callback_env[glp_java_callback_level] = NULL;
    glp_error_hook(NULL, NULL);
    if (glp_java_msg_level != GLP_JAVA_MSG_LVL_OFF) {
        glp_printf("leaving function $name.\n");
    }
}

%typemap(javaclassmodifiers) SWIGTYPE, SWIGTYPE *, SWIGTYPE &, SWIGTYPE [],
  SWIGTYPE (CLASS::*) "
/**
 * Wrapper class for pointer generated by SWIG.
 * <p>Please, refer to doc/glpk-java.pdf of the GLPK for Java distribution
 * and to doc/glpk.pdf of the GLPK source distribution
 * for details. You can download the GLPK source distribution from
 * <a href=\"ftp://ftp.gnu.org/gnu/glpk\">ftp://ftp.gnu.org/gnu/glpk</a>.
 */
public class";

%pragma(java) moduleclassmodifiers = "
/**
 * Wrapper class generated by SWIG.
 * <p>Please, refer to doc/glpk-java.pdf of the GLPK for Java distribution
 * and to doc/glpk.pdf of the GLPK source distribution
 * for details. You can download the source distribution from
 * <a href=\"ftp://ftp.gnu.org/gnu/glpk\">ftp://ftp.gnu.org/gnu/glpk</a>.
 *
 * <p>For handling arrays of int and double the following methods are
 * provided:
 * @see #new_doubleArray(int)
 * @see #delete_doubleArray(SWIGTYPE_p_double)
 * @see #doubleArray_getitem(SWIGTYPE_p_double, int)
 * @see #doubleArray_setitem(SWIGTYPE_p_double, int, double)
 * @see #new_intArray(int)
 * @see #delete_intArray(SWIGTYPE_p_int)
 * @see #intArray_getitem(SWIGTYPE_p_int, int)
 * @see #intArray_setitem(SWIGTYPE_p_int, int, int)
 */
public class";
// Add the library to be wrapped
%include "glpk_java.i"
%include "glpk_javadoc.i"
%include "glpk.h"

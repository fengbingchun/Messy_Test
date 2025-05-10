/* File glpk_java_structures.i
 *
 * Handling of structures.
 *
 * If typedefs like
 *   typedef struct TYPE TYPE
 * are used in the C coding. SWIG maps pointers of type TYPE* to
 * SWIGTYPE_p_TYPE and not to Java class TYPE. This can be overcome by using
 * the macro %glp_structure(TYPE) in the Swig control file.
 */

%define %glp_structure(TYPE)
%typemap(jni) TYPE * "jlong"
%typemap(jtype) TYPE * "long"
%typemap(jstype) TYPE * "TYPE"
%typemap(in) TYPE %{ $1 = *($&1_ltype)&$input; %}
%typemap(out) TYPE *
%{ *($&1_ltype)&$result = $1; %}
%typemap(javain) TYPE * "TYPE.getCPtr($javainput)"
%typemap(javaout) TYPE * {
    long cPtr = $jnicall;
    return (cPtr == 0) ? null : new TYPE(cPtr, $owner);
  }
%enddef

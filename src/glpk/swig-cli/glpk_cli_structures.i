/* File glpk_cli_structures.i
 *
 * Handling of structures.
 *
 * If typedefs like
 *   typedef struct TYPE TYPE
 * are used in the C coding. SWIG maps pointers of type TYPE* to
 * SWIGTYPE_p_TYPE and not to C# class TYPE. This can be overcome by using
 * the macro %glp_structure(TYPE) in the Swig control file.
 */

%define %glp_structure(TYPE)
%typemap(ctype) TYPE * "void *"
%typemap(imtype) TYPE * "global::System.IntPtr"
%typemap(cstype) TYPE * "TYPE"
%typemap(in) TYPE * %{ $1 = ($1_ltype)$input; %}
%typemap(out) TYPE * %{ $result = (void *)$1; %} 
%typemap(csin) TYPE * "global::System.Runtime.InteropServices.HandleRef.ToIntPtr(TYPE.getCPtr($csinput))"
%typemap(csout, excode=SWIGEXCODE) TYPE * {
    global::System.IntPtr cPtr = $imcall;$excode
    return (cPtr == global::System.IntPtr.Zero) ? null : new TYPE(cPtr, $owner);
  }
%typemap(csvarout, excode=SWIGEXCODE) TYPE * %{
    get {
      global::System.IntPtr cPtr = $imcall;$excode
      return (cPtr == global::System.IntPtr.Zero) ? null : new TYPE(cPtr, $owner);
    }
  %}
%enddef

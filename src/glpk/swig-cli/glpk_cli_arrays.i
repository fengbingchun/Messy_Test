/* File glpk_cli_arrays.i
 *
 * Handling of arrays.
 */

%define %glp_array_functions(TYPE,NAME)
%typemap (out) TYPE* new_##NAME {
    if ($1 == NULL) {
        SWIG_CSharpSetPendingException(SWIG_CSharpOutOfMemoryException,
            "$name: calloc failed, C-runtime heap is full.");
        return $null;
    }
    *(TYPE **)&$result = $1;
}
%{
static TYPE *new_##NAME(int nelements) {
  return (TYPE *) calloc(nelements,sizeof(TYPE));
}

static void delete_##NAME(TYPE *ary) { 
  if (ary != NULL) {
    free(ary);
  }
}

static TYPE NAME##_getitem(TYPE *ary, int index) {
  if (ary != NULL) {
    return ary[index];
  } else {
    return (TYPE) 0;
  }
}
static void NAME##_setitem(TYPE *ary, int index, TYPE value) {
  if (ary != NULL) {
    ary[index] = value;
  }
}
%}

%csmethodmodifiers new_##NAME(int nelements) "
/**
 * Creates a new array of TYPE.
 * <p>The memory is allocated with calloc(). To free the memory you will have
 * to call delete&#95;NAME.
 *
 * An OutOfMemoryError error indicates that the C-runtime heap of the process
 * (not the Java object heap) is full.
 *
 * @param nelements number of elements
 * @return array
 */
public";
TYPE *new_##NAME(int nelements);

%csmethodmodifiers delete_##NAME(TYPE *ary) "
/**
 * Deletes an array of TYPE.
 * <p>The memory is deallocated with free().
 *
 * @param ary array
 */
public";
void delete_##NAME(TYPE *ary);

%csmethodmodifiers NAME##_getitem(TYPE *ary, int index) "
/**
 * Retrieves an element of an array of TYPE.
 * <p>BEWARE: The validity of the index is not checked.
 *
 * @param ary array
 * @param index index of the element
 * @return array element
 */
public";
TYPE NAME##_getitem(TYPE *ary, int index);

%csmethodmodifiers NAME##_setitem(TYPE* ary, int index, TYPE value) "
/**
 * Sets the value of an element of an array of TYPE.
 * <p>BEWARE: The validity of the index is not checked.
 *
 * @param ary array
 * @param index index of the element
 * @param value new value
 */
public";
void NAME##_setitem(TYPE *ary, int index, TYPE value);

%enddef
/* Old Swig versions require a LF after enddef */


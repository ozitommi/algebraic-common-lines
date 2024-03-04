/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * runADMM_types.h
 *
 * Code generation for function 'runADMM'
 *
 */

#ifndef RUNADMM_TYPES_H
#define RUNADMM_TYPES_H

/* Include files */
#include "rtwtypes.h"

/* Type Definitions */
#ifndef struct_emxArray_real_T
#define struct_emxArray_real_T
struct emxArray_real_T {
  double *data;
  int *size;
  int allocatedSize;
  int numDimensions;
  boolean_T canFreeData;
};
#endif /* struct_emxArray_real_T */
#ifndef typedef_emxArray_real_T
#define typedef_emxArray_real_T
typedef struct emxArray_real_T emxArray_real_T;
#endif /* typedef_emxArray_real_T */

#ifndef struct_emxArray_boolean_T
#define struct_emxArray_boolean_T
struct emxArray_boolean_T {
  boolean_T *data;
  int *size;
  int allocatedSize;
  int numDimensions;
  boolean_T canFreeData;
};
#endif /* struct_emxArray_boolean_T */
#ifndef typedef_emxArray_boolean_T
#define typedef_emxArray_boolean_T
typedef struct emxArray_boolean_T emxArray_boolean_T;
#endif /* typedef_emxArray_boolean_T */

#ifndef typedef_struct0_T
#define typedef_struct0_T
typedef struct {
  double n;
  emxArray_boolean_T *keep;
  double IR_iter;
  double objlp_tol;
  double conv_tol;
  emxArray_real_T *E_est;
  double vld;
  emxArray_real_T *A;
  emxArray_real_T *X;
  emxArray_real_T *E;
  emxArray_real_T *Y;
  emxArray_real_T *gamma;
  emxArray_real_T *W;
  double tau;
  emxArray_real_T *lam;
  double objl2;
  double objlp;
} struct0_T;
#endif /* typedef_struct0_T */

#ifndef struct_emxArray_int8_T
#define struct_emxArray_int8_T
struct emxArray_int8_T {
  signed char *data;
  int *size;
  int allocatedSize;
  int numDimensions;
  boolean_T canFreeData;
};
#endif /* struct_emxArray_int8_T */
#ifndef typedef_emxArray_int8_T
#define typedef_emxArray_int8_T
typedef struct emxArray_int8_T emxArray_int8_T;
#endif /* typedef_emxArray_int8_T */

#endif
/* End of code generation (runADMM_types.h) */

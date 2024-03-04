/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * _coder_runADMM_api.h
 *
 * Code generation for function 'runADMM'
 *
 */

#ifndef _CODER_RUNADMM_API_H
#define _CODER_RUNADMM_API_H

/* Include files */
#include "emlrt.h"
#include "tmwtypes.h"
#include <string.h>

/* Type Definitions */
#ifndef struct_emxArray_boolean_T
#define struct_emxArray_boolean_T
struct emxArray_boolean_T {
  boolean_T *data;
  int32_T *size;
  int32_T allocatedSize;
  int32_T numDimensions;
  boolean_T canFreeData;
};
#endif /* struct_emxArray_boolean_T */
#ifndef typedef_emxArray_boolean_T
#define typedef_emxArray_boolean_T
typedef struct emxArray_boolean_T emxArray_boolean_T;
#endif /* typedef_emxArray_boolean_T */

#ifndef struct_emxArray_real_T
#define struct_emxArray_real_T
struct emxArray_real_T {
  real_T *data;
  int32_T *size;
  int32_T allocatedSize;
  int32_T numDimensions;
  boolean_T canFreeData;
};
#endif /* struct_emxArray_real_T */
#ifndef typedef_emxArray_real_T
#define typedef_emxArray_real_T
typedef struct emxArray_real_T emxArray_real_T;
#endif /* typedef_emxArray_real_T */

#ifndef typedef_struct0_T
#define typedef_struct0_T
typedef struct {
  real_T n;
  emxArray_boolean_T *keep;
  real_T IR_iter;
  real_T objlp_tol;
  real_T conv_tol;
  emxArray_real_T *E_est;
  real_T vld;
  emxArray_real_T *A;
  emxArray_real_T *X;
  emxArray_real_T *E;
  emxArray_real_T *Y;
  emxArray_real_T *gamma;
  emxArray_real_T *W;
  real_T tau;
  emxArray_real_T *lam;
  real_T objl2;
  real_T objlp;
} struct0_T;
#endif /* typedef_struct0_T */

/* Variable Declarations */
extern emlrtCTX emlrtRootTLSGlobal;
extern emlrtContext emlrtContextGlobal;

#ifdef __cplusplus
extern "C" {
#endif

/* Function Declarations */
void runADMM(struct0_T *var, emxArray_real_T *A_out, emxArray_real_T *lam_out);

void runADMM_api(const mxArray *prhs, int32_T nlhs, const mxArray *plhs[3]);

void runADMM_atexit(void);

void runADMM_initialize(void);

void runADMM_terminate(void);

void runADMM_xil_shutdown(void);

void runADMM_xil_terminate(void);

#ifdef __cplusplus
}
#endif

#endif
/* End of code generation (_coder_runADMM_api.h) */

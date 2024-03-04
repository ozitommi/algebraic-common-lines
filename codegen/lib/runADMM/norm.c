/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * norm.c
 *
 * Code generation for function 'norm'
 *
 */

/* Include files */
#include "norm.h"
#include "rt_nonfinite.h"
#include "runADMM_types.h"
#include "xnrm2.h"
#include <math.h>

/* Function Definitions */
double b_norm(const emxArray_real_T *x)
{
  const double *x_data;
  double y;
  int k;
  int p;
  boolean_T MATRIX_INPUT_AND_P_IS_FRO;
  boolean_T VECTOR_INPUT_AND_P_IS_NUMERIC;
  x_data = x->data;
  VECTOR_INPUT_AND_P_IS_NUMERIC = false;
  MATRIX_INPUT_AND_P_IS_FRO = false;
  p = 0;
  if ((x->size[0] == 1) || (x->size[1] == 1)) {
    p = 2;
    VECTOR_INPUT_AND_P_IS_NUMERIC = true;
  } else {
    MATRIX_INPUT_AND_P_IS_FRO = true;
  }
  if ((x->size[0] == 0) || (x->size[1] == 0)) {
    y = 0.0;
  } else if (MATRIX_INPUT_AND_P_IS_FRO) {
    y = xnrm2(x->size[0] * x->size[1], x);
  } else if (VECTOR_INPUT_AND_P_IS_NUMERIC) {
    if (p == 2) {
      y = xnrm2(x->size[0] * x->size[1], x);
    } else if (p == 1) {
      y = 0.0;
      p = x->size[0] * x->size[1];
      for (k = 0; k < p; k++) {
        y += fabs(x_data[k]);
      }
    } else {
      y = rtNaN;
    }
  } else {
    y = rtNaN;
  }
  return y;
}

/* End of code generation (norm.c) */

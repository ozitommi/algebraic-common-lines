/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * prod.c
 *
 * Code generation for function 'prod'
 *
 */

/* Include files */
#include "prod.h"
#include "rt_nonfinite.h"
#include "runADMM_emxutil.h"
#include "runADMM_types.h"

/* Function Definitions */
void prod(const emxArray_real_T *x, emxArray_real_T *y)
{
  const double *x_data;
  double *y_data;
  int j;
  x_data = x->data;
  if (x->size[0] == 0) {
    y->size[0] = 0;
  } else {
    int vstride;
    vstride = x->size[0];
    j = y->size[0];
    y->size[0] = x->size[0];
    emxEnsureCapacity_real_T(y, j);
    y_data = y->data;
    for (j = 0; j < vstride; j++) {
      y_data[j] = x_data[j] * x_data[vstride + j];
    }
  }
}

/* End of code generation (prod.c) */

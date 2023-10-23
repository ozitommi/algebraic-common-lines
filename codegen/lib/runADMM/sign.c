/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * sign.c
 *
 * Code generation for function 'sign'
 *
 */

/* Include files */
#include "sign.h"
#include "rt_nonfinite.h"
#include "runADMM_types.h"
#include "rt_nonfinite.h"

/* Function Definitions */
void b_sign(emxArray_real_T *x)
{
  double *x_data;
  int k;
  int nx_tmp;
  x_data = x->data;
  nx_tmp = x->size[0] * x->size[1];
  for (k = 0; k < nx_tmp; k++) {
    if (rtIsNaN(x_data[k])) {
      x_data[k] = rtNaN;
    } else if (x_data[k] < 0.0) {
      x_data[k] = -1.0;
    } else {
      x_data[k] = (x_data[k] > 0.0);
    }
  }
}

/* End of code generation (sign.c) */

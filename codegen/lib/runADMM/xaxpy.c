/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * xaxpy.c
 *
 * Code generation for function 'xaxpy'
 *
 */

/* Include files */
#include "xaxpy.h"
#include "rt_nonfinite.h"
#include "runADMM_types.h"

/* Function Definitions */
void b_xaxpy(int n, double a, const emxArray_real_T *x, int ix0,
             emxArray_real_T *y, int iy0)
{
  const double *x_data;
  double *y_data;
  int k;
  y_data = y->data;
  x_data = x->data;
  if ((n >= 1) && (!(a == 0.0))) {
    int i;
    i = n - 1;
    for (k = 0; k <= i; k++) {
      int i1;
      i1 = (iy0 + k) - 1;
      y_data[i1] += a * x_data[(ix0 + k) - 1];
    }
  }
}

void xaxpy(int n, double a, int ix0, emxArray_real_T *y, int iy0)
{
  double *y_data;
  int k;
  y_data = y->data;
  if ((n >= 1) && (!(a == 0.0))) {
    int i;
    i = n - 1;
    for (k = 0; k <= i; k++) {
      int i1;
      i1 = (iy0 + k) - 1;
      y_data[i1] += a * y_data[(ix0 + k) - 1];
    }
  }
}

/* End of code generation (xaxpy.c) */

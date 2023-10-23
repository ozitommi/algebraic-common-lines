/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * repelem.c
 *
 * Code generation for function 'repelem'
 *
 */

/* Include files */
#include "repelem.h"
#include "rt_nonfinite.h"
#include "runADMM_emxutil.h"
#include "runADMM_types.h"

/* Function Definitions */
void repelem(const emxArray_real_T *x, double varargin_1, emxArray_real_T *y)
{
  const double *x_data;
  double *y_data;
  int i;
  int k;
  int mrows;
  int sz_idx_0;
  x_data = x->data;
  sz_idx_0 = x->size[0] * (int)varargin_1;
  mrows = y->size[0] * y->size[1];
  y->size[0] = sz_idx_0;
  y->size[1] = 2;
  emxEnsureCapacity_real_T(y, mrows);
  y_data = y->data;
  if (sz_idx_0 != 0) {
    int rowIdx;
    mrows = x->size[0];
    rowIdx = -1;
    for (i = 0; i < mrows; i++) {
      int rowreps;
      rowreps = (int)varargin_1;
      for (k = 0; k < rowreps; k++) {
        y_data[(rowIdx + k) + 1] = x_data[i];
      }
      rowIdx += (int)varargin_1;
    }
    for (i = 0; i < sz_idx_0; i++) {
      y_data[i + y->size[0]] = y_data[i];
    }
  }
}

/* End of code generation (repelem.c) */

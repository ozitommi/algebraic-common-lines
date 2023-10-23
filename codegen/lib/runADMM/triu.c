/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * triu.c
 *
 * Code generation for function 'triu'
 *
 */

/* Include files */
#include "triu.h"
#include "rt_nonfinite.h"
#include "runADMM_types.h"

/* Function Definitions */
void b_triu(emxArray_real_T *x)
{
  double *x_data;
  int i;
  int j;
  int m;
  x_data = x->data;
  m = x->size[0];
  if ((x->size[0] != 0) && (x->size[1] != 0) && (x->size[0] > 1)) {
    int istart;
    int jend;
    istart = 2;
    if (x->size[0] - 2 < x->size[1] - 1) {
      jend = x->size[0] - 1;
    } else {
      jend = x->size[1];
    }
    for (j = 0; j < jend; j++) {
      for (i = istart; i <= m; i++) {
        x_data[(i + x->size[0] * j) - 1] = 0.0;
      }
      istart++;
    }
  }
}

void triu(emxArray_real_T *x)
{
  double *x_data;
  int i;
  int m;
  int ncolsm1;
  x_data = x->data;
  m = x->size[0];
  if ((x->size[0] != 0) && (x->size[1] != 0) && (x->size[0] > 0)) {
    int istart;
    int jstart;
    istart = 1;
    if (x->size[1] > 1) {
      jstart = 1;
    } else {
      jstart = x->size[1];
    }
    ncolsm1 = x->size[1] - jstart;
    if (x->size[0] - 1 < ncolsm1) {
      jstart = (jstart + x->size[0]) - 1;
    } else {
      jstart += ncolsm1;
    }
    for (ncolsm1 = 0; ncolsm1 < jstart; ncolsm1++) {
      for (i = istart; i <= m; i++) {
        x_data[(i + x->size[0] * ncolsm1) - 1] = 0.0;
      }
      istart++;
    }
  }
}

/* End of code generation (triu.c) */

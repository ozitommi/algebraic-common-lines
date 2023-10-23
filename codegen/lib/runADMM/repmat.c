/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * repmat.c
 *
 * Code generation for function 'repmat'
 *
 */

/* Include files */
#include "repmat.h"
#include "rt_nonfinite.h"
#include "runADMM_emxutil.h"
#include "runADMM_types.h"

/* Function Definitions */
void b_repmat(const emxArray_real_T *a, double varargin_1, emxArray_real_T *b)
{
  const double *a_data;
  double *b_data;
  int itilerow;
  int k;
  int nrows;
  int ntilerows;
  a_data = a->data;
  nrows = b->size[0];
  b->size[0] = a->size[0] * (int)varargin_1;
  emxEnsureCapacity_real_T(b, nrows);
  b_data = b->data;
  nrows = a->size[0];
  ntilerows = (int)varargin_1;
  for (itilerow = 0; itilerow < ntilerows; itilerow++) {
    int ibcol;
    ibcol = itilerow * nrows;
    for (k = 0; k < nrows; k++) {
      b_data[ibcol + k] = a_data[k];
    }
  }
}

void repmat(const emxArray_real_T *a, double varargin_1, emxArray_real_T *b)
{
  const double *a_data;
  double *b_data;
  int i;
  int itilerow;
  int jcol;
  int k;
  int nrows;
  int ntilerows;
  a_data = a->data;
  i = a->size[0] * (int)varargin_1;
  nrows = b->size[0] * b->size[1];
  b->size[0] = i;
  b->size[1] = 2;
  emxEnsureCapacity_real_T(b, nrows);
  b_data = b->data;
  nrows = a->size[0];
  ntilerows = (int)varargin_1;
  for (jcol = 0; jcol < 2; jcol++) {
    int iacol;
    int ibmat;
    iacol = jcol * nrows;
    ibmat = jcol * i - 1;
    for (itilerow = 0; itilerow < ntilerows; itilerow++) {
      int ibcol;
      ibcol = ibmat + itilerow * nrows;
      for (k = 0; k < nrows; k++) {
        b_data[(ibcol + k) + 1] = a_data[iacol + k];
      }
    }
  }
}

/* End of code generation (repmat.c) */

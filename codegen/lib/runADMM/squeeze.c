/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * squeeze.c
 *
 * Code generation for function 'squeeze'
 *
 */

/* Include files */
#include "squeeze.h"
#include "rt_nonfinite.h"
#include "runADMM_emxutil.h"
#include "runADMM_types.h"

/* Function Definitions */
void squeeze(const emxArray_real_T *a, emxArray_real_T *b)
{
  const double *a_data;
  double *b_data;
  int i;
  int szb_idx_0;
  a_data = a->data;
  szb_idx_0 = 1;
  if (a->size[2] != 1) {
    szb_idx_0 = a->size[2];
  }
  i = b->size[0] * b->size[1];
  b->size[0] = szb_idx_0;
  b->size[1] = 1;
  emxEnsureCapacity_real_T(b, i);
  b_data = b->data;
  for (i = 0; i < szb_idx_0; i++) {
    b_data[i] = a_data[i];
  }
}

/* End of code generation (squeeze.c) */

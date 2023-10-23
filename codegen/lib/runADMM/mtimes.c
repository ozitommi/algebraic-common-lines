/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * mtimes.c
 *
 * Code generation for function 'mtimes'
 *
 */

/* Include files */
#include "mtimes.h"
#include "rt_nonfinite.h"
#include "runADMM_emxutil.h"
#include "runADMM_types.h"

/* Function Definitions */
void mtimes(const emxArray_real_T *A, const emxArray_real_T *B,
            emxArray_real_T *C)
{
  const double *A_data;
  const double *B_data;
  double *C_data;
  int b_i;
  int i;
  int inner;
  int j;
  int k;
  int mc;
  int nc;
  B_data = B->data;
  A_data = A->data;
  mc = A->size[0];
  inner = A->size[1];
  nc = B->size[1];
  i = C->size[0] * C->size[1];
  C->size[0] = A->size[0];
  C->size[1] = B->size[1];
  emxEnsureCapacity_real_T(C, i);
  C_data = C->data;
  for (j = 0; j < nc; j++) {
    int boffset;
    int coffset;
    coffset = j * mc;
    boffset = j * B->size[0];
    for (b_i = 0; b_i < mc; b_i++) {
      C_data[coffset + b_i] = 0.0;
    }
    for (k = 0; k < inner; k++) {
      double bkj;
      int aoffset;
      aoffset = k * A->size[0];
      bkj = B_data[boffset + k];
      for (b_i = 0; b_i < mc; b_i++) {
        i = coffset + b_i;
        C_data[i] += A_data[aoffset + b_i] * bkj;
      }
    }
  }
}

/* End of code generation (mtimes.c) */

/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * kron.c
 *
 * Code generation for function 'kron'
 *
 */

/* Include files */
#include "kron.h"
#include "rt_nonfinite.h"
#include "runADMM_emxutil.h"
#include "runADMM_types.h"

/* Function Definitions */
void kron(const emxArray_real_T *A, emxArray_real_T *K)
{
  const double *A_data;
  double *K_data;
  int b_j1;
  int i1;
  int kidx;
  int ma;
  int na;
  A_data = A->data;
  ma = A->size[0];
  na = A->size[1];
  kidx = K->size[0] * K->size[1];
  K->size[0] = A->size[0] << 1;
  K->size[1] = A->size[1];
  emxEnsureCapacity_real_T(K, kidx);
  K_data = K->data;
  kidx = -1;
  for (b_j1 = 0; b_j1 < na; b_j1++) {
    for (i1 = 0; i1 < ma; i1++) {
      K_data[kidx + 1] = A_data[i1 + A->size[0] * b_j1];
      K_data[kidx + 2] = A_data[i1 + A->size[0] * b_j1];
      kidx += 2;
    }
  }
}

/* End of code generation (kron.c) */

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
void kron(const emxArray_real_T *A, const double B_data[], const int B_size[2],
          emxArray_real_T *K)
{
  const double *A_data;
  double *K_data;
  int i1;
  int i2;
  int j2;
  int kidx;
  int ma;
  int mb;
  int nb;
  A_data = A->data;
  ma = A->size[0];
  mb = B_size[0];
  nb = B_size[1];
  kidx = K->size[0] * K->size[1];
  K->size[0] = A->size[0] * B_size[0];
  K->size[1] = B_size[1];
  emxEnsureCapacity_real_T(K, kidx);
  K_data = K->data;
  kidx = -1;
  for (j2 = 0; j2 < nb; j2++) {
    for (i1 = 0; i1 < ma; i1++) {
      for (i2 = 0; i2 < mb; i2++) {
        K_data[(kidx + i2) + 1] = A_data[i1] * B_data[i2 + B_size[0] * j2];
      }
      kidx += mb;
    }
  }
}

/* End of code generation (kron.c) */

/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * svd.c
 *
 * Code generation for function 'svd'
 *
 */

/* Include files */
#include "svd.h"
#include "rt_nonfinite.h"
#include "runADMM_emxutil.h"
#include "runADMM_types.h"
#include "xzsvdc.h"

/* Function Definitions */
void svd(const emxArray_real_T *A, emxArray_real_T *U, emxArray_real_T *s,
         emxArray_real_T *V)
{
  emxArray_real_T *b_A;
  const double *A_data;
  double *U_data;
  int i;
  int loop_ub;
  A_data = A->data;
  if ((A->size[0] == 0) || (A->size[1] == 0)) {
    int m;
    m = A->size[1];
    i = U->size[0] * U->size[1];
    U->size[0] = A->size[0];
    U->size[1] = A->size[0];
    emxEnsureCapacity_real_T(U, i);
    U_data = U->data;
    loop_ub = A->size[0] * A->size[0];
    for (i = 0; i < loop_ub; i++) {
      U_data[i] = 0.0;
    }
    i = A->size[0];
    for (loop_ub = 0; loop_ub < i; loop_ub++) {
      U_data[loop_ub + U->size[0] * loop_ub] = 1.0;
    }
    i = V->size[0] * V->size[1];
    V->size[0] = A->size[1];
    V->size[1] = A->size[1];
    emxEnsureCapacity_real_T(V, i);
    U_data = V->data;
    loop_ub = A->size[1] * A->size[1];
    for (i = 0; i < loop_ub; i++) {
      U_data[i] = 0.0;
    }
    if (A->size[1] > 0) {
      for (loop_ub = 0; loop_ub < m; loop_ub++) {
        U_data[loop_ub + V->size[0] * loop_ub] = 1.0;
      }
    }
    s->size[0] = 0;
  } else {
    emxInit_real_T(&b_A, 2);
    i = b_A->size[0] * b_A->size[1];
    b_A->size[0] = A->size[0];
    b_A->size[1] = A->size[1];
    emxEnsureCapacity_real_T(b_A, i);
    U_data = b_A->data;
    loop_ub = A->size[0] * A->size[1] - 1;
    for (i = 0; i <= loop_ub; i++) {
      U_data[i] = A_data[i];
    }
    xzsvdc(b_A, U, s, V);
    emxFree_real_T(&b_A);
  }
}

/* End of code generation (svd.c) */

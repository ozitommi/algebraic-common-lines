/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * conv2AXPY.c
 *
 * Code generation for function 'conv2AXPY'
 *
 */

/* Include files */
#include "conv2AXPY.h"
#include "conv2AXPYValidCMP.h"
#include "rt_nonfinite.h"
#include "runADMM_emxutil.h"
#include "runADMM_types.h"

/* Function Definitions */
void f_binary_expand_op(emxArray_real_T *in1, const struct0_T *in2)
{
  emxArray_real_T *b_in2;
  double *in2_data;
  int aux_0_1;
  int aux_1_1;
  int b_loop_ub;
  int i;
  int i1;
  int loop_ub;
  int stride_0_0;
  int stride_0_1;
  int stride_1_0;
  int stride_1_1;
  emxInit_real_T(&b_in2, 2);
  if (in2->X->size[0] == 1) {
    loop_ub = in2->E_est->size[0];
  } else {
    loop_ub = in2->X->size[0];
  }
  i = b_in2->size[0] * b_in2->size[1];
  b_in2->size[0] = loop_ub;
  if (in2->X->size[1] == 1) {
    b_loop_ub = in2->E_est->size[1];
  } else {
    b_loop_ub = in2->X->size[1];
  }
  b_in2->size[1] = b_loop_ub;
  emxEnsureCapacity_real_T(b_in2, i);
  in2_data = b_in2->data;
  stride_0_0 = (in2->E_est->size[0] != 1);
  stride_0_1 = (in2->E_est->size[1] != 1);
  stride_1_0 = (in2->X->size[0] != 1);
  stride_1_1 = (in2->X->size[1] != 1);
  aux_0_1 = 0;
  aux_1_1 = 0;
  for (i = 0; i < b_loop_ub; i++) {
    for (i1 = 0; i1 < loop_ub; i1++) {
      in2_data[i1 + b_in2->size[0] * i] =
          in2->E_est->data[i1 * stride_0_0 + in2->E_est->size[0] * aux_0_1] *
          in2->X->data[i1 * stride_1_0 + in2->X->size[0] * aux_1_1];
    }
    aux_1_1 += stride_1_1;
    aux_0_1 += stride_0_1;
  }
  conv2AXPYValidCMP(b_in2, in1);
  emxFree_real_T(&b_in2);
}

/* End of code generation (conv2AXPY.c) */

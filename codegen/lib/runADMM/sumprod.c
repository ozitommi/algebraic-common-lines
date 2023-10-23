/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * sumprod.c
 *
 * Code generation for function 'sumprod'
 *
 */

/* Include files */
#include "sumprod.h"
#include "combineVectorElements.h"
#include "rt_nonfinite.h"
#include "runADMM_emxutil.h"
#include "runADMM_types.h"

/* Function Definitions */
void d_binary_expand_op(emxArray_real_T *in1, const emxArray_real_T *in2,
                        const struct0_T *in4, const emxArray_real_T *in5)
{
  emxArray_real_T *b_in2;
  emxArray_real_T *b_in4;
  const double *in2_data;
  const double *in5_data;
  double *b_in2_data;
  double *in4_data;
  int aux_0_1;
  int aux_1_1;
  int aux_2_1;
  int b_loop_ub;
  int i;
  int i1;
  int loop_ub;
  int stride_0_0;
  int stride_0_1;
  int stride_1_0;
  int stride_1_1;
  int stride_2_0;
  int stride_2_1;
  in5_data = in5->data;
  in2_data = in2->data;
  emxInit_real_T(&b_in4, 2);
  if (in5->size[0] == 1) {
    i = in4->X->size[0];
  } else {
    i = in5->size[0];
  }
  if (i == 1) {
    loop_ub = in4->E_est->size[0];
  } else {
    loop_ub = i;
  }
  i = b_in4->size[0] * b_in4->size[1];
  b_in4->size[0] = loop_ub;
  if (in5->size[1] == 1) {
    i1 = in4->X->size[1];
  } else {
    i1 = in5->size[1];
  }
  if (i1 == 1) {
    b_loop_ub = in4->E_est->size[1];
  } else {
    b_loop_ub = i1;
  }
  b_in4->size[1] = b_loop_ub;
  emxEnsureCapacity_real_T(b_in4, i);
  in4_data = b_in4->data;
  stride_0_0 = (in4->E_est->size[0] != 1);
  stride_0_1 = (in4->E_est->size[1] != 1);
  stride_1_0 = (in4->X->size[0] != 1);
  stride_1_1 = (in4->X->size[1] != 1);
  stride_2_0 = (in5->size[0] != 1);
  stride_2_1 = (in5->size[1] != 1);
  aux_0_1 = 0;
  aux_1_1 = 0;
  aux_2_1 = 0;
  for (i = 0; i < b_loop_ub; i++) {
    for (i1 = 0; i1 < loop_ub; i1++) {
      in4_data[i1 + b_in4->size[0] * i] =
          in4->E_est->data[i1 * stride_0_0 + in4->E_est->size[0] * aux_0_1] -
          in4->X->data[i1 * stride_1_0 + in4->X->size[0] * aux_1_1] *
              in5_data[i1 * stride_2_0 + in5->size[0] * aux_2_1];
    }
    aux_2_1 += stride_2_1;
    aux_1_1 += stride_1_1;
    aux_0_1 += stride_0_1;
  }
  emxInit_real_T(&b_in2, 2);
  if (b_in4->size[0] == 1) {
    loop_ub = in2->size[0];
  } else {
    loop_ub = b_in4->size[0];
  }
  i = b_in2->size[0] * b_in2->size[1];
  b_in2->size[0] = loop_ub;
  if (b_in4->size[1] == 1) {
    b_loop_ub = in2->size[1];
  } else {
    b_loop_ub = b_in4->size[1];
  }
  b_in2->size[1] = b_loop_ub;
  emxEnsureCapacity_real_T(b_in2, i);
  b_in2_data = b_in2->data;
  stride_0_0 = (in2->size[0] != 1);
  stride_0_1 = (in2->size[1] != 1);
  stride_1_0 = (b_in4->size[0] != 1);
  stride_1_1 = (b_in4->size[1] != 1);
  aux_0_1 = 0;
  aux_1_1 = 0;
  for (i = 0; i < b_loop_ub; i++) {
    for (i1 = 0; i1 < loop_ub; i1++) {
      double varargin_1;
      varargin_1 = in4_data[i1 * stride_1_0 + b_in4->size[0] * aux_1_1];
      b_in2_data[i1 + b_in2->size[0] * i] =
          in2_data[i1 * stride_0_0 + in2->size[0] * aux_0_1] *
          (varargin_1 * varargin_1);
    }
    aux_1_1 += stride_1_1;
    aux_0_1 += stride_0_1;
  }
  i = b_in4->size[0] * b_in4->size[1];
  b_in4->size[0] = b_in2->size[0];
  b_in4->size[1] = b_in2->size[1];
  emxEnsureCapacity_real_T(b_in4, i);
  in4_data = b_in4->data;
  loop_ub = b_in2->size[1];
  for (i = 0; i < loop_ub; i++) {
    b_loop_ub = b_in2->size[0];
    for (i1 = 0; i1 < b_loop_ub; i1++) {
      in4_data[i1 + b_in4->size[0] * i] = b_in2_data[i1 + b_in2->size[0] * i];
    }
  }
  emxFree_real_T(&b_in2);
  combineVectorElements(b_in4, in1);
  emxFree_real_T(&b_in4);
}

void j_binary_expand_op(emxArray_real_T *in1, const emxArray_real_T *in2,
                        const struct0_T *in4, const emxArray_real_T *in5)
{
  emxArray_real_T *b_in2;
  emxArray_real_T *b_in4;
  const double *in2_data;
  const double *in5_data;
  double *b_in2_data;
  double *in4_data;
  int aux_0_1;
  int aux_1_1;
  int aux_2_1;
  int b_loop_ub;
  int i;
  int i1;
  int loop_ub;
  int stride_0_0;
  int stride_0_1;
  int stride_1_0;
  int stride_1_1;
  int stride_2_0;
  int stride_2_1;
  in5_data = in5->data;
  in2_data = in2->data;
  emxInit_real_T(&b_in4, 2);
  if (in5->size[0] == 1) {
    i = in4->E->size[0];
  } else {
    i = in5->size[0];
  }
  if (i == 1) {
    loop_ub = in4->E_est->size[0];
  } else {
    loop_ub = i;
  }
  i = b_in4->size[0] * b_in4->size[1];
  b_in4->size[0] = loop_ub;
  if (in5->size[1] == 1) {
    i1 = in4->E->size[1];
  } else {
    i1 = in5->size[1];
  }
  if (i1 == 1) {
    b_loop_ub = in4->E_est->size[1];
  } else {
    b_loop_ub = i1;
  }
  b_in4->size[1] = b_loop_ub;
  emxEnsureCapacity_real_T(b_in4, i);
  in4_data = b_in4->data;
  stride_0_0 = (in4->E_est->size[0] != 1);
  stride_0_1 = (in4->E_est->size[1] != 1);
  stride_1_0 = (in4->E->size[0] != 1);
  stride_1_1 = (in4->E->size[1] != 1);
  stride_2_0 = (in5->size[0] != 1);
  stride_2_1 = (in5->size[1] != 1);
  aux_0_1 = 0;
  aux_1_1 = 0;
  aux_2_1 = 0;
  for (i = 0; i < b_loop_ub; i++) {
    for (i1 = 0; i1 < loop_ub; i1++) {
      in4_data[i1 + b_in4->size[0] * i] =
          in4->E_est->data[i1 * stride_0_0 + in4->E_est->size[0] * aux_0_1] -
          in4->E->data[i1 * stride_1_0 + in4->E->size[0] * aux_1_1] *
              in5_data[i1 * stride_2_0 + in5->size[0] * aux_2_1];
    }
    aux_2_1 += stride_2_1;
    aux_1_1 += stride_1_1;
    aux_0_1 += stride_0_1;
  }
  emxInit_real_T(&b_in2, 2);
  if (b_in4->size[0] == 1) {
    loop_ub = in2->size[0];
  } else {
    loop_ub = b_in4->size[0];
  }
  i = b_in2->size[0] * b_in2->size[1];
  b_in2->size[0] = loop_ub;
  if (b_in4->size[1] == 1) {
    b_loop_ub = in2->size[1];
  } else {
    b_loop_ub = b_in4->size[1];
  }
  b_in2->size[1] = b_loop_ub;
  emxEnsureCapacity_real_T(b_in2, i);
  b_in2_data = b_in2->data;
  stride_0_0 = (in2->size[0] != 1);
  stride_0_1 = (in2->size[1] != 1);
  stride_1_0 = (b_in4->size[0] != 1);
  stride_1_1 = (b_in4->size[1] != 1);
  aux_0_1 = 0;
  aux_1_1 = 0;
  for (i = 0; i < b_loop_ub; i++) {
    for (i1 = 0; i1 < loop_ub; i1++) {
      double varargin_1;
      varargin_1 = in4_data[i1 * stride_1_0 + b_in4->size[0] * aux_1_1];
      b_in2_data[i1 + b_in2->size[0] * i] =
          in2_data[i1 * stride_0_0 + in2->size[0] * aux_0_1] *
          (varargin_1 * varargin_1);
    }
    aux_1_1 += stride_1_1;
    aux_0_1 += stride_0_1;
  }
  i = b_in4->size[0] * b_in4->size[1];
  b_in4->size[0] = b_in2->size[0];
  b_in4->size[1] = b_in2->size[1];
  emxEnsureCapacity_real_T(b_in4, i);
  in4_data = b_in4->data;
  loop_ub = b_in2->size[1];
  for (i = 0; i < loop_ub; i++) {
    b_loop_ub = b_in2->size[0];
    for (i1 = 0; i1 < b_loop_ub; i1++) {
      in4_data[i1 + b_in4->size[0] * i] = b_in2_data[i1 + b_in2->size[0] * i];
    }
  }
  emxFree_real_T(&b_in2);
  combineVectorElements(b_in4, in1);
  emxFree_real_T(&b_in4);
}

void q_binary_expand_op(emxArray_real_T *in1, const emxArray_real_T *in2,
                        const emxArray_real_T *in4)
{
  emxArray_real_T *b_in2;
  const double *in2_data;
  const double *in4_data;
  double *b_in2_data;
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
  in4_data = in4->data;
  in2_data = in2->data;
  emxInit_real_T(&b_in2, 2);
  if (in4->size[0] == 1) {
    loop_ub = in2->size[0];
  } else {
    loop_ub = in4->size[0];
  }
  i = b_in2->size[0] * b_in2->size[1];
  b_in2->size[0] = loop_ub;
  if (in4->size[1] == 1) {
    b_loop_ub = in2->size[1];
  } else {
    b_loop_ub = in4->size[1];
  }
  b_in2->size[1] = b_loop_ub;
  emxEnsureCapacity_real_T(b_in2, i);
  b_in2_data = b_in2->data;
  stride_0_0 = (in2->size[0] != 1);
  stride_0_1 = (in2->size[1] != 1);
  stride_1_0 = (in4->size[0] != 1);
  stride_1_1 = (in4->size[1] != 1);
  aux_0_1 = 0;
  aux_1_1 = 0;
  for (i = 0; i < b_loop_ub; i++) {
    for (i1 = 0; i1 < loop_ub; i1++) {
      double varargin_1;
      varargin_1 = in4_data[i1 * stride_1_0 + in4->size[0] * aux_1_1];
      b_in2_data[i1 + b_in2->size[0] * i] =
          in2_data[i1 * stride_0_0 + in2->size[0] * aux_0_1] *
          (varargin_1 * varargin_1);
    }
    aux_1_1 += stride_1_1;
    aux_0_1 += stride_0_1;
  }
  combineVectorElements(b_in2, in1);
  emxFree_real_T(&b_in2);
}

/* End of code generation (sumprod.c) */

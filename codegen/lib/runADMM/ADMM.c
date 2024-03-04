/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * ADMM.c
 *
 * Code generation for function 'ADMM'
 *
 */

/* Include files */
#include "ADMM.h"
#include "div.h"
#include "kron.h"
#include "norm.h"
#include "rt_nonfinite.h"
#include "runADMM_emxutil.h"
#include "runADMM_internal_types.h"
#include "runADMM_types.h"
#include "sum.h"
#include "svd.h"
#include "rt_nonfinite.h"
#include <math.h>
#include <string.h>

/* Function Declarations */
static void b_binary_expand_op(struct0_T *in1, const emxArray_real_T *in2);

static void binary_expand_op(emxArray_real_T *in1, const emxArray_real_T *in2,
                             const struct0_T *in4, const emxArray_real_T *in5);

static void c_binary_expand_op(emxArray_boolean_T *in1,
                               const emxArray_real_T *in2,
                               const emxArray_real_T *in3);

static void e_binary_expand_op(emxArray_real_T *in1, const struct0_T *in2,
                               const emxArray_real_T *in3, double in4);

static void f_binary_expand_op(emxArray_real_T *in1, const struct0_T *in2,
                               double in3);

static void h_binary_expand_op(emxArray_real_T *in1, const struct0_T *in2);

static void i_binary_expand_op(struct0_T *in1);

static void j_binary_expand_op(emxArray_real_T *in1, const emxArray_real_T *in2,
                               const struct0_T *in4,
                               const emxArray_real_T *in5);

static double k_binary_expand_op(const struct0_T *in1);

static void l_binary_expand_op(struct0_T *in1);

static void m_binary_expand_op(emxArray_real_T *in1, const struct0_T *in2);

static void n_binary_expand_op(emxArray_real_T *in1, const struct0_T *in2);

/* Function Definitions */
static void b_binary_expand_op(struct0_T *in1, const emxArray_real_T *in2)
{
  const double *in2_data;
  int aux_0_1;
  int aux_1_1;
  int b_loop_ub;
  int i;
  int i1;
  int loop_ub;
  int stride_0_0_tmp;
  int stride_0_1_tmp;
  in2_data = in2->data;
  if (in2->size[1] == 1) {
    loop_ub = in2->size[0];
  } else {
    loop_ub = in2->size[1];
  }
  i = in1->lam->size[0] * in1->lam->size[1];
  in1->lam->size[0] = loop_ub;
  emxEnsureCapacity_real_T(in1->lam, i);
  if (in2->size[0] == 1) {
    b_loop_ub = in2->size[1];
  } else {
    b_loop_ub = in2->size[0];
  }
  i = in1->lam->size[0] * in1->lam->size[1];
  in1->lam->size[1] = b_loop_ub;
  emxEnsureCapacity_real_T(in1->lam, i);
  stride_0_0_tmp = (in2->size[0] != 1);
  stride_0_1_tmp = (in2->size[1] != 1);
  aux_0_1 = 0;
  aux_1_1 = 0;
  for (i = 0; i < b_loop_ub; i++) {
    for (i1 = 0; i1 < loop_ub; i1++) {
      in1->lam->data[i1 + in1->lam->size[0] * i] =
          in2_data[i1 * stride_0_0_tmp + in2->size[0] * aux_0_1] +
          in2_data[aux_1_1 + in2->size[0] * (i1 * stride_0_1_tmp)];
    }
    aux_1_1 += stride_0_0_tmp;
    aux_0_1 += stride_0_1_tmp;
  }
}

static void binary_expand_op(emxArray_real_T *in1, const emxArray_real_T *in2,
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
  b_sum(b_in4, in1);
  emxFree_real_T(&b_in4);
}

static void c_binary_expand_op(emxArray_boolean_T *in1,
                               const emxArray_real_T *in2,
                               const emxArray_real_T *in3)
{
  const double *in2_data;
  const double *in3_data;
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
  boolean_T *in1_data;
  in3_data = in3->data;
  in2_data = in2->data;
  if (in3->size[0] == 1) {
    loop_ub = in2->size[0];
  } else {
    loop_ub = in3->size[0];
  }
  i = in1->size[0] * in1->size[1];
  in1->size[0] = loop_ub;
  emxEnsureCapacity_boolean_T(in1, i);
  if (in3->size[1] == 1) {
    b_loop_ub = in2->size[1];
  } else {
    b_loop_ub = in3->size[1];
  }
  i = in1->size[0] * in1->size[1];
  in1->size[1] = b_loop_ub;
  emxEnsureCapacity_boolean_T(in1, i);
  in1_data = in1->data;
  stride_0_0 = (in2->size[0] != 1);
  stride_0_1 = (in2->size[1] != 1);
  stride_1_0 = (in3->size[0] != 1);
  stride_1_1 = (in3->size[1] != 1);
  aux_0_1 = 0;
  aux_1_1 = 0;
  for (i = 0; i < b_loop_ub; i++) {
    for (i1 = 0; i1 < loop_ub; i1++) {
      in1_data[i1 + in1->size[0] * i] =
          (in2_data[i1 * stride_0_0 + in2->size[0] * aux_0_1] -
               in3_data[i1 * stride_1_0 + in3->size[0] * aux_1_1] ==
           0.0);
    }
    aux_1_1 += stride_1_1;
    aux_0_1 += stride_0_1;
  }
}

static void e_binary_expand_op(emxArray_real_T *in1, const struct0_T *in2,
                               const emxArray_real_T *in3, double in4)
{
  const double *in3_data;
  double *in1_data;
  int aux_0_1;
  int aux_1_1;
  int b_loop_ub;
  int i;
  int i1;
  int loop_ub;
  int stride_0_0;
  int stride_0_1;
  int stride_1_0_tmp;
  in3_data = in3->data;
  if ((int)in4 == 1) {
    loop_ub = in2->W->size[0];
  } else {
    loop_ub = (int)in4;
  }
  i = in1->size[0] * in1->size[1];
  in1->size[0] = loop_ub;
  emxEnsureCapacity_real_T(in1, i);
  if ((int)in4 == 1) {
    b_loop_ub = in2->W->size[1];
  } else {
    b_loop_ub = (int)in4;
  }
  i = in1->size[0] * in1->size[1];
  in1->size[1] = b_loop_ub;
  emxEnsureCapacity_real_T(in1, i);
  in1_data = in1->data;
  stride_0_0 = (in2->W->size[0] != 1);
  stride_0_1 = (in2->W->size[1] != 1);
  stride_1_0_tmp = ((int)in4 != 1);
  aux_0_1 = 0;
  aux_1_1 = 0;
  for (i = 0; i < b_loop_ub; i++) {
    for (i1 = 0; i1 < loop_ub; i1++) {
      in1_data[i1 + in1->size[0] * i] =
          in2->W->data[i1 * stride_0_0 + in2->W->size[0] * aux_0_1] *
          in3_data[i1 * stride_1_0_tmp + (int)in4 * aux_1_1];
    }
    aux_1_1 += stride_1_0_tmp;
    aux_0_1 += stride_0_1;
  }
}

static void f_binary_expand_op(emxArray_real_T *in1, const struct0_T *in2,
                               double in3)
{
  emxArray_real_T *b_in2;
  double *in1_data;
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
  loop_ub = (int)(in3 * in3);
  i = in1->size[0] * in1->size[1];
  in1->size[0] = 2;
  in1->size[1] = loop_ub;
  emxEnsureCapacity_real_T(in1, i);
  in1_data = in1->data;
  for (i = 0; i < loop_ub; i++) {
    in1_data[2 * i] = in2_data[2 * i];
    i1 = 2 * i + 1;
    in1_data[i1] = in2_data[i1];
  }
  emxFree_real_T(&b_in2);
}

static void h_binary_expand_op(emxArray_real_T *in1, const struct0_T *in2)
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
  if (in2->lam->size[0] == 1) {
    loop_ub = in2->W->size[0];
  } else {
    loop_ub = in2->lam->size[0];
  }
  i = b_in2->size[0] * b_in2->size[1];
  b_in2->size[0] = loop_ub;
  if (in2->lam->size[1] == 1) {
    b_loop_ub = in2->W->size[1];
  } else {
    b_loop_ub = in2->lam->size[1];
  }
  b_in2->size[1] = b_loop_ub;
  emxEnsureCapacity_real_T(b_in2, i);
  in2_data = b_in2->data;
  stride_0_0 = (in2->W->size[0] != 1);
  stride_0_1 = (in2->W->size[1] != 1);
  stride_1_0 = (in2->lam->size[0] != 1);
  stride_1_1 = (in2->lam->size[1] != 1);
  aux_0_1 = 0;
  aux_1_1 = 0;
  for (i = 0; i < b_loop_ub; i++) {
    for (i1 = 0; i1 < loop_ub; i1++) {
      double varargin_1;
      varargin_1 =
          in2->lam->data[i1 * stride_1_0 + in2->lam->size[0] * aux_1_1];
      in2_data[i1 + b_in2->size[0] * i] =
          in2->W->data[i1 * stride_0_0 + in2->W->size[0] * aux_0_1] *
          (varargin_1 * varargin_1);
    }
    aux_1_1 += stride_1_1;
    aux_0_1 += stride_0_1;
  }
  kron(b_in2, in1);
  emxFree_real_T(&b_in2);
}

static void i_binary_expand_op(struct0_T *in1)
{
  emxArray_real_T *b_in1;
  double *in1_data;
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
  emxInit_real_T(&b_in1, 2);
  if (in1->lam->size[0] == 1) {
    loop_ub = in1->W->size[0];
  } else {
    loop_ub = in1->lam->size[0];
  }
  i = b_in1->size[0] * b_in1->size[1];
  b_in1->size[0] = loop_ub;
  if (in1->lam->size[1] == 1) {
    b_loop_ub = in1->W->size[1];
  } else {
    b_loop_ub = in1->lam->size[1];
  }
  b_in1->size[1] = b_loop_ub;
  emxEnsureCapacity_real_T(b_in1, i);
  in1_data = b_in1->data;
  stride_0_0 = (in1->W->size[0] != 1);
  stride_0_1 = (in1->W->size[1] != 1);
  stride_1_0 = (in1->lam->size[0] != 1);
  stride_1_1 = (in1->lam->size[1] != 1);
  aux_0_1 = 0;
  aux_1_1 = 0;
  for (i = 0; i < b_loop_ub; i++) {
    for (i1 = 0; i1 < loop_ub; i1++) {
      in1_data[i1 + b_in1->size[0] * i] =
          in1->W->data[i1 * stride_0_0 + in1->W->size[0] * aux_0_1] *
          in1->lam->data[i1 * stride_1_0 + in1->lam->size[0] * aux_1_1];
    }
    aux_1_1 += stride_1_1;
    aux_0_1 += stride_0_1;
  }
  kron(b_in1, in1->X);
  emxFree_real_T(&b_in1);
}

static void j_binary_expand_op(emxArray_real_T *in1, const emxArray_real_T *in2,
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
  b_sum(b_in4, in1);
  emxFree_real_T(&b_in4);
}

static double k_binary_expand_op(const struct0_T *in1)
{
  emxArray_real_T *b_in1;
  double out1;
  double *in1_data;
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
  emxInit_real_T(&b_in1, 2);
  if (in1->gamma->size[0] == 1) {
    if (in1->X->size[0] == 1) {
      loop_ub = in1->Y->size[0];
    } else {
      loop_ub = in1->X->size[0];
    }
  } else {
    loop_ub = in1->gamma->size[0];
  }
  i = b_in1->size[0] * b_in1->size[1];
  b_in1->size[0] = loop_ub;
  if (in1->gamma->size[1] == 1) {
    if (in1->X->size[1] == 1) {
      b_loop_ub = in1->Y->size[1];
    } else {
      b_loop_ub = in1->X->size[1];
    }
  } else {
    b_loop_ub = in1->gamma->size[1];
  }
  b_in1->size[1] = b_loop_ub;
  emxEnsureCapacity_real_T(b_in1, i);
  in1_data = b_in1->data;
  stride_0_0 = (in1->Y->size[0] != 1);
  stride_0_1 = (in1->Y->size[1] != 1);
  stride_1_0 = (in1->X->size[0] != 1);
  stride_1_1 = (in1->X->size[1] != 1);
  stride_2_0 = (in1->gamma->size[0] != 1);
  stride_2_1 = (in1->gamma->size[1] != 1);
  aux_0_1 = 0;
  aux_1_1 = 0;
  aux_2_1 = 0;
  for (i = 0; i < b_loop_ub; i++) {
    for (i1 = 0; i1 < loop_ub; i1++) {
      in1_data[i1 + b_in1->size[0] * i] =
          (in1->Y->data[i1 * stride_0_0 + in1->Y->size[0] * aux_0_1] -
           in1->X->data[i1 * stride_1_0 + in1->X->size[0] * aux_1_1]) +
          in1->gamma->data[i1 * stride_2_0 + in1->gamma->size[0] * aux_2_1];
    }
    aux_2_1 += stride_2_1;
    aux_1_1 += stride_1_1;
    aux_0_1 += stride_0_1;
  }
  out1 = b_norm(b_in1);
  emxFree_real_T(&b_in1);
  return out1;
}

static void l_binary_expand_op(struct0_T *in1)
{
  emxArray_real_T *b_in1;
  double *in1_data;
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
  emxInit_real_T(&b_in1, 2);
  if (in1->X->size[0] == 1) {
    i = in1->Y->size[0];
  } else {
    i = in1->X->size[0];
  }
  if (i == 1) {
    loop_ub = in1->gamma->size[0];
  } else {
    loop_ub = i;
  }
  i = b_in1->size[0] * b_in1->size[1];
  b_in1->size[0] = loop_ub;
  if (in1->X->size[1] == 1) {
    i1 = in1->Y->size[1];
  } else {
    i1 = in1->X->size[1];
  }
  if (i1 == 1) {
    b_loop_ub = in1->gamma->size[1];
  } else {
    b_loop_ub = i1;
  }
  b_in1->size[1] = b_loop_ub;
  emxEnsureCapacity_real_T(b_in1, i);
  in1_data = b_in1->data;
  stride_0_0 = (in1->gamma->size[0] != 1);
  stride_0_1 = (in1->gamma->size[1] != 1);
  stride_1_0 = (in1->Y->size[0] != 1);
  stride_1_1 = (in1->Y->size[1] != 1);
  stride_2_0 = (in1->X->size[0] != 1);
  stride_2_1 = (in1->X->size[1] != 1);
  aux_0_1 = 0;
  aux_1_1 = 0;
  aux_2_1 = 0;
  for (i = 0; i < b_loop_ub; i++) {
    for (i1 = 0; i1 < loop_ub; i1++) {
      in1_data[i1 + b_in1->size[0] * i] =
          in1->gamma->data[i1 * stride_0_0 + in1->gamma->size[0] * aux_0_1] +
          (in1->Y->data[i1 * stride_1_0 + in1->Y->size[0] * aux_1_1] -
           in1->X->data[i1 * stride_2_0 + in1->X->size[0] * aux_2_1]);
    }
    aux_2_1 += stride_2_1;
    aux_1_1 += stride_1_1;
    aux_0_1 += stride_0_1;
  }
  i = in1->gamma->size[0] * in1->gamma->size[1];
  in1->gamma->size[0] = b_in1->size[0];
  in1->gamma->size[1] = b_in1->size[1];
  emxEnsureCapacity_real_T(in1->gamma, i);
  loop_ub = b_in1->size[0] * b_in1->size[1];
  for (i = 0; i < loop_ub; i++) {
    in1->gamma->data[i] = in1_data[i];
  }
  emxFree_real_T(&b_in1);
}

static void m_binary_expand_op(emxArray_real_T *in1, const struct0_T *in2)
{
  double *in1_data;
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
  if (in2->gamma->size[0] == 1) {
    loop_ub = in2->X->size[0];
  } else {
    loop_ub = in2->gamma->size[0];
  }
  i = in1->size[0] * in1->size[1];
  in1->size[0] = loop_ub;
  emxEnsureCapacity_real_T(in1, i);
  if (in2->gamma->size[1] == 1) {
    b_loop_ub = in2->X->size[1];
  } else {
    b_loop_ub = in2->gamma->size[1];
  }
  i = in1->size[0] * in1->size[1];
  in1->size[1] = b_loop_ub;
  emxEnsureCapacity_real_T(in1, i);
  in1_data = in1->data;
  stride_0_0 = (in2->X->size[0] != 1);
  stride_0_1 = (in2->X->size[1] != 1);
  stride_1_0 = (in2->gamma->size[0] != 1);
  stride_1_1 = (in2->gamma->size[1] != 1);
  aux_0_1 = 0;
  aux_1_1 = 0;
  for (i = 0; i < b_loop_ub; i++) {
    for (i1 = 0; i1 < loop_ub; i1++) {
      in1_data[i1 + in1->size[0] * i] =
          in2->X->data[i1 * stride_0_0 + in2->X->size[0] * aux_0_1] -
          in2->gamma->data[i1 * stride_1_0 + in2->gamma->size[0] * aux_1_1];
    }
    aux_1_1 += stride_1_1;
    aux_0_1 += stride_0_1;
  }
}

static void n_binary_expand_op(emxArray_real_T *in1, const struct0_T *in2)
{
  double *in1_data;
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
  if (in2->gamma->size[0] == 1) {
    loop_ub = in2->Y->size[0];
  } else {
    loop_ub = in2->gamma->size[0];
  }
  i = in1->size[0] * in1->size[1];
  in1->size[0] = loop_ub;
  emxEnsureCapacity_real_T(in1, i);
  if (in2->gamma->size[1] == 1) {
    b_loop_ub = in2->Y->size[1];
  } else {
    b_loop_ub = in2->gamma->size[1];
  }
  i = in1->size[0] * in1->size[1];
  in1->size[1] = b_loop_ub;
  emxEnsureCapacity_real_T(in1, i);
  in1_data = in1->data;
  stride_0_0 = (in2->Y->size[0] != 1);
  stride_0_1 = (in2->Y->size[1] != 1);
  stride_1_0 = (in2->gamma->size[0] != 1);
  stride_1_1 = (in2->gamma->size[1] != 1);
  aux_0_1 = 0;
  aux_1_1 = 0;
  for (i = 0; i < b_loop_ub; i++) {
    for (i1 = 0; i1 < loop_ub; i1++) {
      in1_data[i1 + in1->size[0] * i] =
          in2->Y->data[i1 * stride_0_0 + in2->Y->size[0] * aux_0_1] +
          in2->gamma->data[i1 * stride_1_0 + in2->gamma->size[0] * aux_1_1];
    }
    aux_1_1 += stride_1_1;
    aux_0_1 += stride_0_1;
  }
}

void ADMM(struct0_T *var, struct0_T *result_var, struct_T *result_out)
{
  emxArray_boolean_T *r1;
  emxArray_real_T *D;
  emxArray_real_T *G;
  emxArray_real_T *U;
  emxArray_real_T *a;
  emxArray_real_T *b_var;
  emxArray_real_T *b_y;
  emxArray_real_T *r;
  emxArray_real_T *s;
  emxArray_real_T *tmpY;
  emxArray_real_T *x;
  emxArray_real_T *y;
  double diff;
  double obj;
  double t;
  double varargin_1;
  double *D_data;
  double *G_data;
  double *U_data;
  double *a_data;
  double *r3;
  double *tmpY_data;
  double *y_data;
  int actv;
  int count;
  int i;
  int j;
  int loop_ub_tmp;
  int npages;
  boolean_T *r2;
  count = 1;
  diff = rtInf;
  /*  full objective */
  emxInit_real_T(&b_var, 2);
  if (var->Y->size[0] == 1) {
    npages = var->X->size[0];
  } else {
    npages = var->Y->size[0];
  }
  if (var->Y->size[1] == 1) {
    i = var->X->size[1];
  } else {
    i = var->Y->size[1];
  }
  if ((var->Y->size[0] == var->X->size[0]) &&
      (var->Y->size[1] == var->X->size[1]) && (npages == var->gamma->size[0]) &&
      (i == var->gamma->size[1])) {
    j = b_var->size[0] * b_var->size[1];
    b_var->size[0] = var->Y->size[0];
    b_var->size[1] = var->Y->size[1];
    emxEnsureCapacity_real_T(b_var, j);
    D_data = b_var->data;
    npages = var->Y->size[0] * var->Y->size[1];
    for (j = 0; j < npages; j++) {
      D_data[j] = (var->Y->data[j] - var->X->data[j]) + var->gamma->data[j];
    }
    t = b_norm(b_var);
  } else {
    t = k_binary_expand_op(var);
  }
  /*  objective for A and Lambda */
  emxInit_real_T(&U, 2);
  kron(var->W, U);
  U_data = U->data;
  emxInit_real_T(&tmpY, 2);
  kron(var->lam, tmpY);
  tmpY_data = tmpY->data;
  if (var->E->size[0] == 1) {
    j = tmpY->size[0];
  } else {
    j = var->E->size[0];
  }
  if (var->E->size[1] == 1) {
    loop_ub_tmp = tmpY->size[1];
  } else {
    loop_ub_tmp = var->E->size[1];
  }
  emxInit_real_T(&y, 2);
  if (var->E_est->size[0] == 1) {
    npages = j;
  } else {
    npages = var->E_est->size[0];
  }
  if (var->E_est->size[1] == 1) {
    i = loop_ub_tmp;
  } else {
    i = var->E_est->size[1];
  }
  if ((var->E->size[0] == tmpY->size[0]) &&
      (var->E->size[1] == tmpY->size[1]) && (var->E_est->size[0] == j) &&
      (var->E_est->size[1] == loop_ub_tmp) && (U->size[0] == npages) &&
      (U->size[1] == i)) {
    j = b_var->size[0] * b_var->size[1];
    b_var->size[0] = U->size[0];
    b_var->size[1] = U->size[1];
    emxEnsureCapacity_real_T(b_var, j);
    D_data = b_var->data;
    npages = U->size[0] * U->size[1];
    for (j = 0; j < npages; j++) {
      varargin_1 = var->E_est->data[j] - var->E->data[j] * tmpY_data[j];
      D_data[j] = U_data[j] * (varargin_1 * varargin_1);
    }
    b_sum(b_var, y);
    y_data = y->data;
  } else {
    j_binary_expand_op(y, U, var, tmpY);
    y_data = y->data;
  }
  obj = 0.5 * c_sum(y) + var->tau / 2.0 * (t * t);
  memset(&result_out->residual[0], 0, 500U * sizeof(double));
  memset(&result_out->obj[0], 0, 500U * sizeof(double));
  /*  profile on */
  actv = 1;
  emxInit_real_T(&r, 2);
  emxInit_real_T(&b_y, 2);
  emxInit_real_T(&a, 2);
  emxInit_real_T(&s, 1);
  emxInit_real_T(&G, 2);
  emxInit_real_T(&D, 2);
  emxInit_real_T(&x, 2);
  emxInit_boolean_T(&r1, 2);
  while ((count < 500) && (actv != 0) && (diff > 1.0E-8)) {
    int m_tmp;
    int xpageoffset;
    boolean_T p;
    /*  run alternating ADMM optimization */
    result_out->obj[count - 1] = obj;
    /*  update A and Lambda */
    if ((var->Y->size[0] == var->gamma->size[0]) &&
        (var->Y->size[1] == var->gamma->size[1])) {
      j = G->size[0] * G->size[1];
      G->size[0] = var->Y->size[0];
      G->size[1] = var->Y->size[1];
      emxEnsureCapacity_real_T(G, j);
      G_data = G->data;
      npages = var->Y->size[0] * var->Y->size[1];
      for (j = 0; j < npages; j++) {
        G_data[j] = var->Y->data[j] + var->gamma->data[j];
      }
    } else {
      n_binary_expand_op(G, var);
      G_data = G->data;
    }
    /*  changed */
    /*  update A */
    if ((var->W->size[0] == var->lam->size[0]) &&
        (var->W->size[1] == var->lam->size[1])) {
      j = b_var->size[0] * b_var->size[1];
      b_var->size[0] = var->W->size[0];
      b_var->size[1] = var->W->size[1];
      emxEnsureCapacity_real_T(b_var, j);
      D_data = b_var->data;
      npages = var->W->size[0] * var->W->size[1];
      for (j = 0; j < npages; j++) {
        D_data[j] = var->W->data[j] * var->lam->data[j];
      }
      kron(b_var, var->X);
    } else {
      i_binary_expand_op(var);
    }
    if ((var->W->size[0] == var->lam->size[0]) &&
        (var->W->size[1] == var->lam->size[1])) {
      j = b_var->size[0] * b_var->size[1];
      b_var->size[0] = var->W->size[0];
      b_var->size[1] = var->W->size[1];
      emxEnsureCapacity_real_T(b_var, j);
      D_data = b_var->data;
      npages = var->W->size[0] * var->W->size[1];
      for (j = 0; j < npages; j++) {
        varargin_1 = var->lam->data[j];
        D_data[j] = var->W->data[j] * (varargin_1 * varargin_1);
      }
      kron(b_var, U);
      U_data = U->data;
    } else {
      h_binary_expand_op(U, var);
      U_data = U->data;
    }
    if (var->X->size[0] == 1) {
      j = var->E_est->size[0];
    } else {
      j = var->X->size[0];
    }
    if (var->X->size[1] == 1) {
      loop_ub_tmp = var->E_est->size[1];
    } else {
      loop_ub_tmp = var->X->size[1];
    }
    if (j == 1) {
      npages = G->size[0];
    } else {
      npages = j;
    }
    if (loop_ub_tmp == 1) {
      i = G->size[1];
    } else {
      i = loop_ub_tmp;
    }
    if ((var->X->size[0] == var->E_est->size[0]) &&
        (var->X->size[1] == var->E_est->size[1]) && (j == G->size[0]) &&
        (loop_ub_tmp == G->size[1]) && (npages == U->size[0]) &&
        (i == U->size[1])) {
      npages = var->X->size[0] * var->X->size[1];
      for (j = 0; j < npages; j++) {
        var->X->data[j] =
            (var->X->data[j] * var->E_est->data[j] + var->tau * G_data[j]) /
            (U_data[j] + var->tau);
      }
    } else {
      g_binary_expand_op(var, G, U);
    }
    if (var->n < 0.0) {
      t = 0.0;
    } else {
      t = var->n;
    }
    if (var->n < 0.0) {
      xpageoffset = 0;
    } else {
      xpageoffset = (int)var->n;
    }
    j = tmpY->size[0] * tmpY->size[1];
    tmpY->size[0] = (int)t;
    tmpY->size[1] = (int)t;
    emxEnsureCapacity_real_T(tmpY, j);
    tmpY_data = tmpY->data;
    npages = (int)t * (int)t;
    for (j = 0; j < npages; j++) {
      tmpY_data[j] = 0.0;
    }
    if ((int)t > 0) {
      for (npages = 0; npages < xpageoffset; npages++) {
        tmpY_data[npages + tmpY->size[0] * npages] = 1.0;
      }
    }
    kron(tmpY, U);
    U_data = U->data;
    xpageoffset = U->size[0] * U->size[1] - 1;
    for (i = 0; i <= xpageoffset; i++) {
      if (U_data[i] != 0.0) {
        var->X->data[i] = 0.0;
      }
    }
    /*  make 2x1 block diagonals 0 */
    j = var->E->size[0] * var->E->size[1];
    var->E->size[0] = var->X->size[0];
    var->E->size[1] = var->X->size[1];
    emxEnsureCapacity_real_T(var->E, j);
    npages = var->X->size[0] * var->X->size[1];
    for (j = 0; j < npages; j++) {
      var->E->data[j] = var->X->data[j];
    }
    /*     %% symmetric version */
    if ((var->E_est->size[0] == var->X->size[0]) &&
        (var->E_est->size[1] == var->X->size[1])) {
      j = b_var->size[0] * b_var->size[1];
      b_var->size[0] = var->E_est->size[0];
      b_var->size[1] = var->E_est->size[1];
      emxEnsureCapacity_real_T(b_var, j);
      D_data = b_var->data;
      npages = var->E_est->size[0] * var->E_est->size[1];
      for (j = 0; j < npages; j++) {
        D_data[j] = var->E_est->data[j] * var->X->data[j];
      }
      xpageoffset = (int)(var->n * var->n);
      j = x->size[0] * x->size[1];
      x->size[0] = 2;
      x->size[1] = xpageoffset;
      emxEnsureCapacity_real_T(x, j);
      G_data = x->data;
      loop_ub_tmp = xpageoffset << 1;
      for (j = 0; j < loop_ub_tmp; j++) {
        G_data[j] = D_data[j];
      }
    } else {
      f_binary_expand_op(x, var, var->n);
      G_data = x->data;
    }
    if (x->size[1] == 0) {
      y->size[0] = 1;
      y->size[1] = 0;
    } else {
      npages = x->size[1];
      j = y->size[0] * y->size[1];
      y->size[0] = 1;
      y->size[1] = x->size[1];
      emxEnsureCapacity_real_T(y, j);
      y_data = y->data;
      for (loop_ub_tmp = 0; loop_ub_tmp < npages; loop_ub_tmp++) {
        xpageoffset = loop_ub_tmp << 1;
        y_data[loop_ub_tmp] = G_data[xpageoffset] + G_data[xpageoffset + 1];
      }
    }
    if ((var->W->size[0] == (int)var->n) && (var->W->size[1] == (int)var->n)) {
      j = U->size[0] * U->size[1];
      U->size[0] = var->W->size[0];
      U->size[1] = var->W->size[1];
      emxEnsureCapacity_real_T(U, j);
      U_data = U->data;
      npages = var->W->size[0] * var->W->size[1];
      for (j = 0; j < npages; j++) {
        U_data[j] = var->W->data[j] * y_data[j];
      }
    } else {
      e_binary_expand_op(U, var, y, var->n);
      U_data = U->data;
    }
    j = x->size[0] * x->size[1];
    x->size[0] = 2;
    loop_ub_tmp = (int)(var->n * var->n);
    x->size[1] = loop_ub_tmp;
    emxEnsureCapacity_real_T(x, j);
    G_data = x->data;
    loop_ub_tmp <<= 1;
    for (j = 0; j < loop_ub_tmp; j++) {
      G_data[j] = var->X->data[j] * var->X->data[j];
    }
    if (x->size[1] == 0) {
      y->size[0] = 1;
      y->size[1] = 0;
    } else {
      npages = x->size[1];
      j = y->size[0] * y->size[1];
      y->size[0] = 1;
      y->size[1] = x->size[1];
      emxEnsureCapacity_real_T(y, j);
      y_data = y->data;
      for (loop_ub_tmp = 0; loop_ub_tmp < npages; loop_ub_tmp++) {
        xpageoffset = loop_ub_tmp << 1;
        y_data[loop_ub_tmp] = G_data[xpageoffset] + G_data[xpageoffset + 1];
      }
    }
    if ((var->W->size[0] == (int)var->n) && (var->W->size[1] == (int)var->n)) {
      j = tmpY->size[0] * tmpY->size[1];
      tmpY->size[0] = var->W->size[0];
      tmpY->size[1] = var->W->size[1];
      emxEnsureCapacity_real_T(tmpY, j);
      tmpY_data = tmpY->data;
      npages = var->W->size[0] * var->W->size[1];
      for (j = 0; j < npages; j++) {
        tmpY_data[j] = var->W->data[j] * y_data[j];
      }
    } else {
      e_binary_expand_op(tmpY, var, y, var->n);
      tmpY_data = tmpY->data;
    }
    if (U->size[0] == 1) {
      npages = U->size[1];
    } else {
      npages = U->size[0];
    }
    if (tmpY->size[0] == 1) {
      i = tmpY->size[1];
    } else {
      i = tmpY->size[0];
    }
    if (U->size[1] == 1) {
      m_tmp = U->size[0];
    } else {
      m_tmp = U->size[1];
    }
    if (tmpY->size[1] == 1) {
      xpageoffset = tmpY->size[0];
    } else {
      xpageoffset = tmpY->size[1];
    }
    if ((U->size[0] == U->size[1]) && (tmpY->size[0] == tmpY->size[1]) &&
        (tmpY->size[0] == tmpY->size[1]) && (npages == i) &&
        (m_tmp == xpageoffset)) {
      j = D->size[0] * D->size[1];
      D->size[0] = U->size[0];
      D->size[1] = U->size[1];
      emxEnsureCapacity_real_T(D, j);
      D_data = D->data;
      npages = U->size[1];
      for (j = 0; j < npages; j++) {
        xpageoffset = U->size[0];
        for (loop_ub_tmp = 0; loop_ub_tmp < xpageoffset; loop_ub_tmp++) {
          D_data[loop_ub_tmp + D->size[0] * j] =
              (U_data[loop_ub_tmp + U->size[0] * j] +
               U_data[j + U->size[0] * loop_ub_tmp]) /
              (tmpY_data[loop_ub_tmp + tmpY->size[0] * j] +
               tmpY_data[j + tmpY->size[0] * loop_ub_tmp]);
        }
      }
    } else {
      d_binary_expand_op(D, U, tmpY);
      D_data = D->data;
    }
    m_tmp = (int)var->n;
    j = U->size[0] * U->size[1];
    U->size[0] = (int)var->n;
    U->size[1] = (int)var->n;
    emxEnsureCapacity_real_T(U, j);
    U_data = U->data;
    loop_ub_tmp = (int)var->n * (int)var->n;
    for (j = 0; j < loop_ub_tmp; j++) {
      U_data[j] = 0.0;
    }
    if ((int)var->n > 0) {
      for (npages = 0; npages < m_tmp; npages++) {
        U_data[npages + U->size[0] * npages] = 1.0;
      }
    }
    j = tmpY->size[0] * tmpY->size[1];
    tmpY->size[0] = (int)var->n;
    tmpY->size[1] = (int)var->n;
    emxEnsureCapacity_real_T(tmpY, j);
    tmpY_data = tmpY->data;
    for (j = 0; j < loop_ub_tmp; j++) {
      tmpY_data[j] = 1.0;
    }
    if ((int)var->n > 1) {
      xpageoffset = 2;
      if ((int)var->n - 2 < (int)var->n - 1) {
        npages = (int)var->n - 1;
      } else {
        npages = (int)var->n;
      }
      for (j = 0; j < npages; j++) {
        for (i = xpageoffset; i <= m_tmp; i++) {
          tmpY_data[(i + tmpY->size[0] * j) - 1] = 0.0;
        }
        xpageoffset++;
      }
    }
    if ((tmpY->size[0] == U->size[0]) && (tmpY->size[1] == U->size[1])) {
      j = r1->size[0] * r1->size[1];
      r1->size[0] = tmpY->size[0];
      r1->size[1] = tmpY->size[1];
      emxEnsureCapacity_boolean_T(r1, j);
      r2 = r1->data;
      for (j = 0; j < loop_ub_tmp; j++) {
        r2[j] = (tmpY_data[j] - U_data[j] == 0.0);
      }
    } else {
      c_binary_expand_op(r1, tmpY, U);
      r2 = r1->data;
    }
    xpageoffset = r1->size[0] * r1->size[1] - 1;
    for (i = 0; i <= xpageoffset; i++) {
      if (r2[i]) {
        D_data[i] = 0.0;
      }
    }
    if (D->size[0] == D->size[1]) {
      j = var->lam->size[0] * var->lam->size[1];
      var->lam->size[0] = D->size[0];
      var->lam->size[1] = D->size[1];
      emxEnsureCapacity_real_T(var->lam, j);
      npages = D->size[1];
      for (j = 0; j < npages; j++) {
        xpageoffset = D->size[0];
        for (loop_ub_tmp = 0; loop_ub_tmp < xpageoffset; loop_ub_tmp++) {
          var->lam->data[loop_ub_tmp + var->lam->size[0] * j] =
              D_data[loop_ub_tmp + D->size[0] * j] +
              D_data[j + D->size[0] * loop_ub_tmp];
        }
      }
    } else {
      b_binary_expand_op(var, D);
    }
    /*  bound scales inside box */
    npages = var->lam->size[0] * var->lam->size[1];
    for (j = 0; j < npages; j++) {
      varargin_1 = var->lam->data[j];
      var->lam->data[j] = fmin(varargin_1, var->conv_tol);
    }
    npages = var->lam->size[0] * var->lam->size[1];
    for (j = 0; j < npages; j++) {
      varargin_1 = var->lam->data[j];
      var->lam->data[j] = fmax(varargin_1, -var->conv_tol);
    }
    /*  objective for A and Lambda */
    kron(var->W, U);
    U_data = U->data;
    kron(var->lam, tmpY);
    tmpY_data = tmpY->data;
    if (var->X->size[0] == 1) {
      j = tmpY->size[0];
    } else {
      j = var->X->size[0];
    }
    if (var->X->size[1] == 1) {
      loop_ub_tmp = tmpY->size[1];
    } else {
      loop_ub_tmp = var->X->size[1];
    }
    if (var->E_est->size[0] == 1) {
      npages = j;
    } else {
      npages = var->E_est->size[0];
    }
    if (var->E_est->size[1] == 1) {
      i = loop_ub_tmp;
    } else {
      i = var->E_est->size[1];
    }
    if ((var->X->size[0] == tmpY->size[0]) &&
        (var->X->size[1] == tmpY->size[1]) && (var->E_est->size[0] == j) &&
        (var->E_est->size[1] == loop_ub_tmp) && (U->size[0] == npages) &&
        (U->size[1] == i)) {
      j = b_var->size[0] * b_var->size[1];
      b_var->size[0] = U->size[0];
      b_var->size[1] = U->size[1];
      emxEnsureCapacity_real_T(b_var, j);
      D_data = b_var->data;
      npages = U->size[0] * U->size[1];
      for (j = 0; j < npages; j++) {
        varargin_1 = var->E_est->data[j] - var->X->data[j] * tmpY_data[j];
        D_data[j] = U_data[j] * (varargin_1 * varargin_1);
      }
      b_sum(b_var, y);
      y_data = y->data;
    } else {
      binary_expand_op(y, U, var, tmpY);
      y_data = y->data;
    }
    /*  update B */
    if ((var->X->size[0] == var->gamma->size[0]) &&
        (var->X->size[1] == var->gamma->size[1])) {
      j = tmpY->size[0] * tmpY->size[1];
      tmpY->size[0] = var->X->size[0];
      tmpY->size[1] = var->X->size[1];
      emxEnsureCapacity_real_T(tmpY, j);
      tmpY_data = tmpY->data;
      npages = var->X->size[0] * var->X->size[1];
      for (j = 0; j < npages; j++) {
        tmpY_data[j] = var->X->data[j] - var->gamma->data[j];
      }
    } else {
      m_binary_expand_op(tmpY, var);
      tmpY_data = tmpY->data;
    }
    xpageoffset = tmpY->size[0] * tmpY->size[1];
    p = true;
    for (npages = 0; npages < xpageoffset; npages++) {
      if ((!p) || (rtIsInf(tmpY_data[npages]) || rtIsNaN(tmpY_data[npages]))) {
        p = false;
      }
    }
    if (p) {
      svd(tmpY, U, s, D);
      D_data = D->data;
      G_data = s->data;
      U_data = U->data;
    } else {
      j = b_var->size[0] * b_var->size[1];
      b_var->size[0] = tmpY->size[0];
      b_var->size[1] = tmpY->size[1];
      emxEnsureCapacity_real_T(b_var, j);
      D_data = b_var->data;
      npages = tmpY->size[0] * tmpY->size[1];
      for (j = 0; j < npages; j++) {
        D_data[j] = 0.0;
      }
      svd(b_var, tmpY, s, D);
      j = U->size[0] * U->size[1];
      U->size[0] = tmpY->size[0];
      U->size[1] = tmpY->size[1];
      emxEnsureCapacity_real_T(U, j);
      U_data = U->data;
      npages = tmpY->size[0] * tmpY->size[1];
      for (j = 0; j < npages; j++) {
        U_data[j] = rtNaN;
      }
      xpageoffset = s->size[0];
      j = s->size[0];
      s->size[0] = xpageoffset;
      emxEnsureCapacity_real_T(s, j);
      G_data = s->data;
      for (j = 0; j < xpageoffset; j++) {
        G_data[j] = rtNaN;
      }
      xpageoffset = D->size[0];
      npages = D->size[1];
      j = D->size[0] * D->size[1];
      D->size[0] = xpageoffset;
      D->size[1] = npages;
      emxEnsureCapacity_real_T(D, j);
      D_data = D->data;
      npages *= xpageoffset;
      for (j = 0; j < npages; j++) {
        D_data[j] = rtNaN;
      }
    }
    j = tmpY->size[0] * tmpY->size[1];
    tmpY->size[0] = U->size[1];
    tmpY->size[1] = D->size[1];
    emxEnsureCapacity_real_T(tmpY, j);
    tmpY_data = tmpY->data;
    npages = U->size[1] * D->size[1];
    for (j = 0; j < npages; j++) {
      tmpY_data[j] = 0.0;
    }
    j = s->size[0] - 1;
    for (npages = 0; npages <= j; npages++) {
      tmpY_data[npages + tmpY->size[0] * npages] = G_data[npages];
    }
    j = r->size[0] * r->size[1];
    r->size[0] = D->size[0];
    r->size[1] = 3;
    emxEnsureCapacity_real_T(r, j);
    r3 = r->data;
    j = a->size[0] * a->size[1];
    a->size[0] = U->size[0];
    a->size[1] = 3;
    emxEnsureCapacity_real_T(a, j);
    a_data = a->data;
    npages = D->size[0];
    xpageoffset = U->size[0];
    for (j = 0; j < 3; j++) {
      for (loop_ub_tmp = 0; loop_ub_tmp < npages; loop_ub_tmp++) {
        r3[loop_ub_tmp + r->size[0] * j] = D_data[loop_ub_tmp + D->size[0] * j];
      }
      for (loop_ub_tmp = 0; loop_ub_tmp < xpageoffset; loop_ub_tmp++) {
        a_data[loop_ub_tmp + a->size[0] * j] =
            U_data[loop_ub_tmp + U->size[0] * j];
      }
    }
    loop_ub_tmp = U->size[0];
    j = b_y->size[0] * b_y->size[1];
    b_y->size[0] = U->size[0];
    b_y->size[1] = 3;
    emxEnsureCapacity_real_T(b_y, j);
    G_data = b_y->data;
    for (j = 0; j < 3; j++) {
      npages = j * loop_ub_tmp;
      xpageoffset = j * 3;
      for (i = 0; i < loop_ub_tmp; i++) {
        G_data[npages + i] =
            (a_data[i] * tmpY_data[xpageoffset % 3 +
                                   tmpY->size[0] * (xpageoffset / 3)] +
             a_data[U->size[0] + i] *
                 tmpY_data[(xpageoffset + 1) % 3 +
                           tmpY->size[0] * ((xpageoffset + 1) / 3)]) +
            a_data[(U->size[0] << 1) + i] *
                tmpY_data[(xpageoffset + 2) % 3 +
                          tmpY->size[0] * ((xpageoffset + 2) / 3)];
      }
    }
    loop_ub_tmp = b_y->size[0];
    xpageoffset = D->size[0];
    j = var->Y->size[0] * var->Y->size[1];
    var->Y->size[0] = b_y->size[0];
    var->Y->size[1] = D->size[0];
    emxEnsureCapacity_real_T(var->Y, j);
    for (j = 0; j < xpageoffset; j++) {
      npages = j * loop_ub_tmp;
      for (i = 0; i < loop_ub_tmp; i++) {
        var->Y->data[npages + i] =
            (G_data[i] * r3[j] +
             G_data[b_y->size[0] + i] * r3[D->size[0] + j]) +
            G_data[(b_y->size[0] << 1) + i] * r3[(D->size[0] << 1) + j];
      }
    }
    /*  [U, S, V] = svds(tmpY, 3); */
    /*  var.Y = U*S*V'; */
    /*  update Gamma */
    if (var->Y->size[0] == 1) {
      npages = var->X->size[0];
    } else {
      npages = var->Y->size[0];
    }
    if (var->Y->size[1] == 1) {
      i = var->X->size[1];
    } else {
      i = var->Y->size[1];
    }
    if ((var->Y->size[0] == var->X->size[0]) &&
        (var->Y->size[1] == var->X->size[1]) &&
        (var->gamma->size[0] == npages) && (var->gamma->size[1] == i)) {
      npages = var->gamma->size[0] * var->gamma->size[1];
      for (j = 0; j < npages; j++) {
        var->gamma->data[j] += var->Y->data[j] - var->X->data[j];
      }
    } else {
      l_binary_expand_op(var);
    }
    count++;
    j = (int)fmod(count, 20.0);
    if (j == 1) {
      /*  full objective */
      if (var->Y->size[0] == 1) {
        npages = var->X->size[0];
      } else {
        npages = var->Y->size[0];
      }
      if (var->Y->size[1] == 1) {
        i = var->X->size[1];
      } else {
        i = var->Y->size[1];
      }
      if ((var->Y->size[0] == var->X->size[0]) &&
          (var->Y->size[1] == var->X->size[1]) &&
          (npages == var->gamma->size[0]) && (i == var->gamma->size[1])) {
        loop_ub_tmp = b_var->size[0] * b_var->size[1];
        b_var->size[0] = var->Y->size[0];
        b_var->size[1] = var->Y->size[1];
        emxEnsureCapacity_real_T(b_var, loop_ub_tmp);
        D_data = b_var->data;
        npages = var->Y->size[0] * var->Y->size[1];
        for (loop_ub_tmp = 0; loop_ub_tmp < npages; loop_ub_tmp++) {
          D_data[loop_ub_tmp] =
              (var->Y->data[loop_ub_tmp] - var->X->data[loop_ub_tmp]) +
              var->gamma->data[loop_ub_tmp];
        }
        t = b_norm(b_var);
      } else {
        t = k_binary_expand_op(var);
      }
      /*  objective for A and Lambda */
      kron(var->W, U);
      U_data = U->data;
      kron(var->lam, tmpY);
      tmpY_data = tmpY->data;
      if (var->E->size[0] == 1) {
        loop_ub_tmp = tmpY->size[0];
      } else {
        loop_ub_tmp = var->E->size[0];
      }
      if (var->E->size[1] == 1) {
        xpageoffset = tmpY->size[1];
      } else {
        xpageoffset = var->E->size[1];
      }
      if (var->E_est->size[0] == 1) {
        npages = loop_ub_tmp;
      } else {
        npages = var->E_est->size[0];
      }
      if (var->E_est->size[1] == 1) {
        i = xpageoffset;
      } else {
        i = var->E_est->size[1];
      }
      if ((var->E->size[0] == tmpY->size[0]) &&
          (var->E->size[1] == tmpY->size[1]) &&
          (var->E_est->size[0] == loop_ub_tmp) &&
          (var->E_est->size[1] == xpageoffset) && (U->size[0] == npages) &&
          (U->size[1] == i)) {
        loop_ub_tmp = b_var->size[0] * b_var->size[1];
        b_var->size[0] = U->size[0];
        b_var->size[1] = U->size[1];
        emxEnsureCapacity_real_T(b_var, loop_ub_tmp);
        D_data = b_var->data;
        npages = U->size[0] * U->size[1];
        for (loop_ub_tmp = 0; loop_ub_tmp < npages; loop_ub_tmp++) {
          varargin_1 = var->E_est->data[loop_ub_tmp] -
                       var->E->data[loop_ub_tmp] * tmpY_data[loop_ub_tmp];
          D_data[loop_ub_tmp] = U_data[loop_ub_tmp] * (varargin_1 * varargin_1);
        }
        b_sum(b_var, y);
        y_data = y->data;
      } else {
        j_binary_expand_op(y, U, var, tmpY);
        y_data = y->data;
      }
      obj = 0.5 * c_sum(y) + var->tau / 2.0 * (t * t);
    }
    if (j == 10) {
      /*  full objective */
      if (var->Y->size[0] == 1) {
        npages = var->X->size[0];
      } else {
        npages = var->Y->size[0];
      }
      if (var->Y->size[1] == 1) {
        i = var->X->size[1];
      } else {
        i = var->Y->size[1];
      }
      if ((var->Y->size[0] == var->X->size[0]) &&
          (var->Y->size[1] == var->X->size[1]) &&
          (npages == var->gamma->size[0]) && (i == var->gamma->size[1])) {
        j = b_var->size[0] * b_var->size[1];
        b_var->size[0] = var->Y->size[0];
        b_var->size[1] = var->Y->size[1];
        emxEnsureCapacity_real_T(b_var, j);
        D_data = b_var->data;
        npages = var->Y->size[0] * var->Y->size[1];
        for (j = 0; j < npages; j++) {
          D_data[j] = (var->Y->data[j] - var->X->data[j]) + var->gamma->data[j];
        }
        t = b_norm(b_var);
      } else {
        t = k_binary_expand_op(var);
      }
      /*  objective for A and Lambda */
      kron(var->W, U);
      U_data = U->data;
      kron(var->lam, tmpY);
      tmpY_data = tmpY->data;
      if (var->E->size[0] == 1) {
        j = tmpY->size[0];
      } else {
        j = var->E->size[0];
      }
      if (var->E->size[1] == 1) {
        loop_ub_tmp = tmpY->size[1];
      } else {
        loop_ub_tmp = var->E->size[1];
      }
      if (var->E_est->size[0] == 1) {
        npages = j;
      } else {
        npages = var->E_est->size[0];
      }
      if (var->E_est->size[1] == 1) {
        i = loop_ub_tmp;
      } else {
        i = var->E_est->size[1];
      }
      if ((var->E->size[0] == tmpY->size[0]) &&
          (var->E->size[1] == tmpY->size[1]) && (var->E_est->size[0] == j) &&
          (var->E_est->size[1] == loop_ub_tmp) && (U->size[0] == npages) &&
          (U->size[1] == i)) {
        j = b_var->size[0] * b_var->size[1];
        b_var->size[0] = U->size[0];
        b_var->size[1] = U->size[1];
        emxEnsureCapacity_real_T(b_var, j);
        D_data = b_var->data;
        npages = U->size[0] * U->size[1];
        for (j = 0; j < npages; j++) {
          varargin_1 = var->E_est->data[j] - var->E->data[j] * tmpY_data[j];
          D_data[j] = U_data[j] * (varargin_1 * varargin_1);
        }
        b_sum(b_var, y);
        y_data = y->data;
      } else {
        j_binary_expand_op(y, U, var, tmpY);
        y_data = y->data;
      }
      t = 0.5 * c_sum(y) + var->tau / 2.0 * (t * t);
      diff = fabs(obj - t) / fmax(fabs(obj), fabs(t));
      if (diff < 1.0E-8) {
        actv = 0;
      }
    }
  }
  emxFree_real_T(&b_var);
  emxFree_boolean_T(&r1);
  emxFree_real_T(&x);
  emxFree_real_T(&y);
  emxFree_real_T(&D);
  emxFree_real_T(&G);
  emxFree_real_T(&U);
  emxFree_real_T(&s);
  emxFree_real_T(&a);
  emxFree_real_T(&b_y);
  emxFree_real_T(&r);
  emxFree_real_T(&tmpY);
  emxCopyStruct_struct0_T(result_var, var);
}

/* End of code generation (ADMM.c) */

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
#include "combineVectorElements.h"
#include "conv2AXPY.h"
#include "conv2AXPYValidCMP.h"
#include "div.h"
#include "norm.h"
#include "rt_nonfinite.h"
#include "runADMM_emxutil.h"
#include "runADMM_internal_types.h"
#include "runADMM_rtwutil.h"
#include "runADMM_types.h"
#include "sum.h"
#include "sumprod.h"
#include "svd.h"
#include <math.h>
#include <string.h>

/* Function Declarations */
static void h_binary_expand_op(emxArray_real_T *in1, const struct0_T *in2);

static void i_binary_expand_op(emxArray_real_T *in1, const struct0_T *in2);

static double k_binary_expand_op(const emxArray_real_T *in1,
                                 const struct0_T *in2);

static void l_binary_expand_op(struct0_T *in1, const emxArray_real_T *in2);

static void m_binary_expand_op(emxArray_real_T *in1, const struct0_T *in2);

static void n_binary_expand_op(const struct0_T *in1, emxArray_real_T *in2,
                               emxArray_real_T *in3, emxArray_real_T *in4);

static void o_binary_expand_op(emxArray_real_T *in1, const struct0_T *in2);

static double p_binary_expand_op(const struct0_T *in1);

/* Function Definitions */
static void h_binary_expand_op(emxArray_real_T *in1, const struct0_T *in2)
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
  if (in2->lam->size[0] == 1) {
    loop_ub = in2->W->size[0];
  } else {
    loop_ub = in2->lam->size[0];
  }
  i = in1->size[0] * in1->size[1];
  in1->size[0] = loop_ub;
  emxEnsureCapacity_real_T(in1, i);
  if (in2->lam->size[1] == 1) {
    b_loop_ub = in2->W->size[1];
  } else {
    b_loop_ub = in2->lam->size[1];
  }
  i = in1->size[0] * in1->size[1];
  in1->size[1] = b_loop_ub;
  emxEnsureCapacity_real_T(in1, i);
  in1_data = in1->data;
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
      in1_data[i1 + in1->size[0] * i] =
          in2->W->data[i1 * stride_0_0 + in2->W->size[0] * aux_0_1] *
          (varargin_1 * varargin_1);
    }
    aux_1_1 += stride_1_1;
    aux_0_1 += stride_0_1;
  }
}

static void i_binary_expand_op(emxArray_real_T *in1, const struct0_T *in2)
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
  if (in2->lam->size[0] == 1) {
    loop_ub = in2->W->size[0];
  } else {
    loop_ub = in2->lam->size[0];
  }
  i = in1->size[0] * in1->size[1];
  in1->size[0] = loop_ub;
  emxEnsureCapacity_real_T(in1, i);
  if (in2->lam->size[1] == 1) {
    b_loop_ub = in2->W->size[1];
  } else {
    b_loop_ub = in2->lam->size[1];
  }
  i = in1->size[0] * in1->size[1];
  in1->size[1] = b_loop_ub;
  emxEnsureCapacity_real_T(in1, i);
  in1_data = in1->data;
  stride_0_0 = (in2->W->size[0] != 1);
  stride_0_1 = (in2->W->size[1] != 1);
  stride_1_0 = (in2->lam->size[0] != 1);
  stride_1_1 = (in2->lam->size[1] != 1);
  aux_0_1 = 0;
  aux_1_1 = 0;
  for (i = 0; i < b_loop_ub; i++) {
    for (i1 = 0; i1 < loop_ub; i1++) {
      in1_data[i1 + in1->size[0] * i] =
          in2->W->data[i1 * stride_0_0 + in2->W->size[0] * aux_0_1] *
          in2->lam->data[i1 * stride_1_0 + in2->lam->size[0] * aux_1_1];
    }
    aux_1_1 += stride_1_1;
    aux_0_1 += stride_0_1;
  }
}

static double k_binary_expand_op(const emxArray_real_T *in1,
                                 const struct0_T *in2)
{
  emxArray_real_T *b_in1;
  const double *in1_data;
  double out1;
  double *b_in1_data;
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
  in1_data = in1->data;
  emxInit_real_T(&b_in1, 2);
  if (in2->gamma->size[0] == 1) {
    loop_ub = in1->size[0];
  } else {
    loop_ub = in2->gamma->size[0];
  }
  i = b_in1->size[0] * b_in1->size[1];
  b_in1->size[0] = loop_ub;
  if (in2->gamma->size[1] == 1) {
    b_loop_ub = in1->size[1];
  } else {
    b_loop_ub = in2->gamma->size[1];
  }
  b_in1->size[1] = b_loop_ub;
  emxEnsureCapacity_real_T(b_in1, i);
  b_in1_data = b_in1->data;
  stride_0_0 = (in1->size[0] != 1);
  stride_0_1 = (in1->size[1] != 1);
  stride_1_0 = (in2->gamma->size[0] != 1);
  stride_1_1 = (in2->gamma->size[1] != 1);
  aux_0_1 = 0;
  aux_1_1 = 0;
  for (i = 0; i < b_loop_ub; i++) {
    for (i1 = 0; i1 < loop_ub; i1++) {
      b_in1_data[i1 + b_in1->size[0] * i] =
          in1_data[i1 * stride_0_0 + in1->size[0] * aux_0_1] +
          in2->gamma->data[i1 * stride_1_0 + in2->gamma->size[0] * aux_1_1];
    }
    aux_1_1 += stride_1_1;
    aux_0_1 += stride_0_1;
  }
  out1 = b_norm(b_in1);
  emxFree_real_T(&b_in1);
  return out1;
}

static void l_binary_expand_op(struct0_T *in1, const emxArray_real_T *in2)
{
  emxArray_real_T *b_in1;
  const double *in2_data;
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
  in2_data = in2->data;
  emxInit_real_T(&b_in1, 2);
  if (in2->size[0] == 1) {
    loop_ub = in1->gamma->size[0];
  } else {
    loop_ub = in2->size[0];
  }
  i = b_in1->size[0] * b_in1->size[1];
  b_in1->size[0] = loop_ub;
  if (in2->size[1] == 1) {
    b_loop_ub = in1->gamma->size[1];
  } else {
    b_loop_ub = in2->size[1];
  }
  b_in1->size[1] = b_loop_ub;
  emxEnsureCapacity_real_T(b_in1, i);
  in1_data = b_in1->data;
  stride_0_0 = (in1->gamma->size[0] != 1);
  stride_0_1 = (in1->gamma->size[1] != 1);
  stride_1_0 = (in2->size[0] != 1);
  stride_1_1 = (in2->size[1] != 1);
  aux_0_1 = 0;
  aux_1_1 = 0;
  for (i = 0; i < b_loop_ub; i++) {
    for (i1 = 0; i1 < loop_ub; i1++) {
      in1_data[i1 + b_in1->size[0] * i] =
          in1->gamma->data[i1 * stride_0_0 + in1->gamma->size[0] * aux_0_1] +
          in2_data[i1 * stride_1_0 + in2->size[0] * aux_1_1];
    }
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
  if (in2->X->size[0] == 1) {
    loop_ub = in2->Y->size[0];
  } else {
    loop_ub = in2->X->size[0];
  }
  i = in1->size[0] * in1->size[1];
  in1->size[0] = loop_ub;
  emxEnsureCapacity_real_T(in1, i);
  if (in2->X->size[1] == 1) {
    b_loop_ub = in2->Y->size[1];
  } else {
    b_loop_ub = in2->X->size[1];
  }
  i = in1->size[0] * in1->size[1];
  in1->size[1] = b_loop_ub;
  emxEnsureCapacity_real_T(in1, i);
  in1_data = in1->data;
  stride_0_0 = (in2->Y->size[0] != 1);
  stride_0_1 = (in2->Y->size[1] != 1);
  stride_1_0 = (in2->X->size[0] != 1);
  stride_1_1 = (in2->X->size[1] != 1);
  aux_0_1 = 0;
  aux_1_1 = 0;
  for (i = 0; i < b_loop_ub; i++) {
    for (i1 = 0; i1 < loop_ub; i1++) {
      in1_data[i1 + in1->size[0] * i] =
          in2->Y->data[i1 * stride_0_0 + in2->Y->size[0] * aux_0_1] -
          in2->X->data[i1 * stride_1_0 + in2->X->size[0] * aux_1_1];
    }
    aux_1_1 += stride_1_1;
    aux_0_1 += stride_0_1;
  }
}

static void n_binary_expand_op(const struct0_T *in1, emxArray_real_T *in2,
                               emxArray_real_T *in3, emxArray_real_T *in4)
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
  if (in1->gamma->size[0] == 1) {
    loop_ub = in1->X->size[0];
  } else {
    loop_ub = in1->gamma->size[0];
  }
  i = b_in1->size[0] * b_in1->size[1];
  b_in1->size[0] = loop_ub;
  if (in1->gamma->size[1] == 1) {
    b_loop_ub = in1->X->size[1];
  } else {
    b_loop_ub = in1->gamma->size[1];
  }
  b_in1->size[1] = b_loop_ub;
  emxEnsureCapacity_real_T(b_in1, i);
  in1_data = b_in1->data;
  stride_0_0 = (in1->X->size[0] != 1);
  stride_0_1 = (in1->X->size[1] != 1);
  stride_1_0 = (in1->gamma->size[0] != 1);
  stride_1_1 = (in1->gamma->size[1] != 1);
  aux_0_1 = 0;
  aux_1_1 = 0;
  for (i = 0; i < b_loop_ub; i++) {
    for (i1 = 0; i1 < loop_ub; i1++) {
      in1_data[i1 + b_in1->size[0] * i] =
          in1->X->data[i1 * stride_0_0 + in1->X->size[0] * aux_0_1] -
          in1->gamma->data[i1 * stride_1_0 + in1->gamma->size[0] * aux_1_1];
    }
    aux_1_1 += stride_1_1;
    aux_0_1 += stride_0_1;
  }
  svd(b_in1, in2, in3, in4);
  emxFree_real_T(&b_in1);
}

static void o_binary_expand_op(emxArray_real_T *in1, const struct0_T *in2)
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

static double p_binary_expand_op(const struct0_T *in1)
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

void ADMM(struct0_T *var, struct0_T *result_var, struct_T *result_out)
{
  emxArray_real_T *G;
  emxArray_real_T *K;
  emxArray_real_T *S;
  emxArray_real_T *a;
  emxArray_real_T *b_K;
  emxArray_real_T *b_bl2;
  emxArray_real_T *b_var;
  emxArray_real_T *bl1;
  emxArray_real_T *bl2;
  emxArray_real_T *r;
  emxArray_real_T *y;
  double diff;
  double diff1;
  double f2;
  double obj;
  double *G_data;
  double *K_data;
  double *S_data;
  double *a_data;
  double *bl1_data;
  double *bl2_data;
  int actv;
  int b_j1;
  int count;
  int i;
  int i1;
  int iter;
  int kidx;
  int ma;
  int na;
  count = 1;
  diff = rtInf;
  /*  full objective */
  emxInit_real_T(&b_var, 2);
  if (var->Y->size[0] == 1) {
    i = var->X->size[0];
  } else {
    i = var->Y->size[0];
  }
  if (var->Y->size[1] == 1) {
    ma = var->X->size[1];
  } else {
    ma = var->Y->size[1];
  }
  if ((var->Y->size[0] == var->X->size[0]) &&
      (var->Y->size[1] == var->X->size[1]) && (i == var->gamma->size[0]) &&
      (ma == var->gamma->size[1])) {
    i = b_var->size[0] * b_var->size[1];
    b_var->size[0] = var->Y->size[0];
    b_var->size[1] = var->Y->size[1];
    emxEnsureCapacity_real_T(b_var, i);
    bl2_data = b_var->data;
    kidx = var->Y->size[0] * var->Y->size[1];
    for (i = 0; i < kidx; i++) {
      bl2_data[i] = (var->Y->data[i] - var->X->data[i]) + var->gamma->data[i];
    }
    diff1 = b_norm(b_var);
  } else {
    diff1 = p_binary_expand_op(var);
  }
  /*  objective for A and Lambda */
  ma = var->W->size[0];
  na = var->W->size[1];
  emxInit_real_T(&K, 2);
  i = K->size[0] * K->size[1];
  K->size[0] = var->W->size[0] << 1;
  K->size[1] = var->W->size[1];
  emxEnsureCapacity_real_T(K, i);
  K_data = K->data;
  kidx = -1;
  for (b_j1 = 0; b_j1 < na; b_j1++) {
    for (i1 = 0; i1 < ma; i1++) {
      K_data[kidx + 1] = var->W->data[i1 + var->W->size[0] * b_j1];
      K_data[kidx + 2] = var->W->data[i1 + var->W->size[0] * b_j1];
      kidx += 2;
    }
  }
  ma = var->lam->size[0];
  na = var->lam->size[1];
  emxInit_real_T(&b_K, 2);
  i = b_K->size[0] * b_K->size[1];
  b_K->size[0] = var->lam->size[0] << 1;
  b_K->size[1] = var->lam->size[1];
  emxEnsureCapacity_real_T(b_K, i);
  bl1_data = b_K->data;
  kidx = -1;
  for (b_j1 = 0; b_j1 < na; b_j1++) {
    for (i1 = 0; i1 < ma; i1++) {
      bl1_data[kidx + 1] = var->lam->data[i1 + var->lam->size[0] * b_j1];
      bl1_data[kidx + 2] = var->lam->data[i1 + var->lam->size[0] * b_j1];
      kidx += 2;
    }
  }
  if (var->E->size[0] == 1) {
    i = b_K->size[0];
  } else {
    i = var->E->size[0];
  }
  if (var->E->size[1] == 1) {
    i1 = b_K->size[1];
  } else {
    i1 = var->E->size[1];
  }
  emxInit_real_T(&r, 2);
  if (var->E_est->size[0] == 1) {
    ma = i;
  } else {
    ma = var->E_est->size[0];
  }
  if (var->E_est->size[1] == 1) {
    na = i1;
  } else {
    na = var->E_est->size[1];
  }
  if ((var->E->size[0] == b_K->size[0]) && (var->E->size[1] == b_K->size[1]) &&
      (var->E_est->size[0] == i) && (var->E_est->size[1] == i1) &&
      (K->size[0] == ma) && (K->size[1] == na)) {
    i = b_var->size[0] * b_var->size[1];
    b_var->size[0] = K->size[0];
    b_var->size[1] = K->size[1];
    emxEnsureCapacity_real_T(b_var, i);
    bl2_data = b_var->data;
    kidx = K->size[0] * K->size[1];
    for (i = 0; i < kidx; i++) {
      f2 = var->E_est->data[i] - var->E->data[i] * bl1_data[i];
      bl2_data[i] = K_data[i] * (f2 * f2);
    }
    combineVectorElements(b_var, r);
  } else {
    j_binary_expand_op(r, K, var, b_K);
  }
  obj = 0.5 * b_sum(r) + var->tau / 2.0 * (diff1 * diff1);
  memset(&result_out->residual[0], 0, 500U * sizeof(double));
  memset(&result_out->obj[0], 0, 500U * sizeof(double));
  /*  profile on */
  actv = 1;
  emxInit_real_T(&G, 2);
  emxInit_real_T(&bl1, 2);
  emxInit_real_T(&bl2, 2);
  emxInit_real_T(&S, 2);
  emxInit_real_T(&y, 2);
  emxInit_real_T(&a, 2);
  emxInit_real_T(&b_bl2, 2);
  while ((count < 500) && (actv != 0) && (diff > 1.0E-8)) {
    double f2_old;
    double n;
    /*  run alternating ADMM optimization */
    result_out->obj[count - 1] = obj;
    /*  update A and Lambda */
    n = var->n;
    if ((var->Y->size[0] == var->gamma->size[0]) &&
        (var->Y->size[1] == var->gamma->size[1])) {
      i = G->size[0] * G->size[1];
      G->size[0] = var->Y->size[0];
      G->size[1] = var->Y->size[1];
      emxEnsureCapacity_real_T(G, i);
      G_data = G->data;
      kidx = var->Y->size[0] * var->Y->size[1];
      for (i = 0; i < kidx; i++) {
        G_data[i] = var->Y->data[i] + var->gamma->data[i];
      }
    } else {
      o_binary_expand_op(G, var);
      G_data = G->data;
    }
    iter = 0;
    f2_old = 0.0;
    diff1 = rtInf;
    while ((iter < 10) && (diff1 > 1.0E-6)) {
      int loop_ub_tmp;
      int m_tmp_tmp_tmp;
      iter++;
      /*  update A */
      if ((var->W->size[0] == var->lam->size[0]) &&
          (var->W->size[1] == var->lam->size[1])) {
        i = b_K->size[0] * b_K->size[1];
        b_K->size[0] = var->W->size[0];
        b_K->size[1] = var->W->size[1];
        emxEnsureCapacity_real_T(b_K, i);
        bl1_data = b_K->data;
        kidx = var->W->size[0] * var->W->size[1];
        for (i = 0; i < kidx; i++) {
          bl1_data[i] = var->W->data[i] * var->lam->data[i];
        }
      } else {
        i_binary_expand_op(b_K, var);
        bl1_data = b_K->data;
      }
      ma = b_K->size[0];
      na = b_K->size[1];
      i = var->X->size[0] * var->X->size[1];
      var->X->size[0] = b_K->size[0] << 1;
      var->X->size[1] = b_K->size[1];
      emxEnsureCapacity_real_T(var->X, i);
      kidx = -1;
      for (b_j1 = 0; b_j1 < na; b_j1++) {
        for (i1 = 0; i1 < ma; i1++) {
          var->X->data[kidx + 1] = bl1_data[i1 + b_K->size[0] * b_j1];
          var->X->data[kidx + 2] = bl1_data[i1 + b_K->size[0] * b_j1];
          kidx += 2;
        }
      }
      if ((var->W->size[0] == var->lam->size[0]) &&
          (var->W->size[1] == var->lam->size[1])) {
        i = b_K->size[0] * b_K->size[1];
        b_K->size[0] = var->W->size[0];
        b_K->size[1] = var->W->size[1];
        emxEnsureCapacity_real_T(b_K, i);
        bl1_data = b_K->data;
        kidx = var->W->size[0] * var->W->size[1];
        for (i = 0; i < kidx; i++) {
          f2 = var->lam->data[i];
          bl1_data[i] = var->W->data[i] * (f2 * f2);
        }
      } else {
        h_binary_expand_op(b_K, var);
        bl1_data = b_K->data;
      }
      ma = b_K->size[0];
      na = b_K->size[1];
      i = K->size[0] * K->size[1];
      K->size[0] = b_K->size[0] << 1;
      K->size[1] = b_K->size[1];
      emxEnsureCapacity_real_T(K, i);
      K_data = K->data;
      kidx = -1;
      for (b_j1 = 0; b_j1 < na; b_j1++) {
        for (i1 = 0; i1 < ma; i1++) {
          K_data[kidx + 1] = bl1_data[i1 + b_K->size[0] * b_j1];
          K_data[kidx + 2] = bl1_data[i1 + b_K->size[0] * b_j1];
          kidx += 2;
        }
      }
      if (var->X->size[0] == 1) {
        i = var->E_est->size[0];
      } else {
        i = var->X->size[0];
      }
      if (var->X->size[1] == 1) {
        i1 = var->E_est->size[1];
      } else {
        i1 = var->X->size[1];
      }
      if (i == 1) {
        ma = G->size[0];
      } else {
        ma = i;
      }
      if (i1 == 1) {
        na = G->size[1];
      } else {
        na = i1;
      }
      if ((var->X->size[0] == var->E_est->size[0]) &&
          (var->X->size[1] == var->E_est->size[1]) && (i == G->size[0]) &&
          (i1 == G->size[1]) && (ma == K->size[0]) && (na == K->size[1])) {
        kidx = var->X->size[0] * var->X->size[1];
        for (i = 0; i < kidx; i++) {
          var->X->data[i] =
              (var->X->data[i] * var->E_est->data[i] + var->tau * G_data[i]) /
              (K_data[i] + var->tau);
        }
      } else {
        g_binary_expand_op(var, G, K);
      }
      if (n < 0.0) {
        diff1 = 0.0;
        m_tmp_tmp_tmp = 0;
      } else {
        diff1 = n;
        m_tmp_tmp_tmp = (int)n;
      }
      i = b_K->size[0] * b_K->size[1];
      b_K->size[0] = (int)diff1;
      b_K->size[1] = (int)diff1;
      emxEnsureCapacity_real_T(b_K, i);
      bl1_data = b_K->data;
      loop_ub_tmp = (int)diff1 * (int)diff1;
      for (i = 0; i < loop_ub_tmp; i++) {
        bl1_data[i] = 0.0;
      }
      if ((int)diff1 > 0) {
        for (kidx = 0; kidx < m_tmp_tmp_tmp; kidx++) {
          bl1_data[kidx + b_K->size[0] * kidx] = 1.0;
        }
      }
      ma = b_K->size[0];
      na = b_K->size[1];
      i = K->size[0] * K->size[1];
      K->size[0] = b_K->size[0] << 1;
      K->size[1] = b_K->size[1];
      emxEnsureCapacity_real_T(K, i);
      K_data = K->data;
      kidx = -1;
      for (b_j1 = 0; b_j1 < na; b_j1++) {
        for (i1 = 0; i1 < ma; i1++) {
          K_data[kidx + 1] = bl1_data[i1 + b_K->size[0] * b_j1];
          K_data[kidx + 2] = bl1_data[i1 + b_K->size[0] * b_j1];
          kidx += 2;
        }
      }
      kidx = K->size[0] * K->size[1] - 1;
      for (b_j1 = 0; b_j1 <= kidx; b_j1++) {
        if (K_data[b_j1] != 0.0) {
          var->X->data[b_j1] = 0.0;
        }
      }
      /*  make 2x1 block diagonals 0 */
      i = var->E->size[0] * var->E->size[1];
      var->E->size[0] = var->X->size[0];
      var->E->size[1] = var->X->size[1];
      emxEnsureCapacity_real_T(var->E, i);
      kidx = var->X->size[0] * var->X->size[1];
      for (i = 0; i < kidx; i++) {
        var->E->data[i] = var->X->data[i];
      }
      /*  update lambda */
      if ((var->E_est->size[0] == var->X->size[0]) &&
          (var->E_est->size[1] == var->X->size[1])) {
        i = b_var->size[0] * b_var->size[1];
        b_var->size[0] = var->E_est->size[0];
        b_var->size[1] = var->E_est->size[1];
        emxEnsureCapacity_real_T(b_var, i);
        bl2_data = b_var->data;
        kidx = var->E_est->size[0] * var->E_est->size[1];
        for (i = 0; i < kidx; i++) {
          bl2_data[i] = var->E_est->data[i] * var->X->data[i];
        }
        conv2AXPYValidCMP(b_var, bl1);
        bl1_data = bl1->data;
      } else {
        f_binary_expand_op(bl1, var);
        bl1_data = bl1->data;
      }
      /*  adds elements of each 2x1 submatrix */
      /*  formula: sum of entries of Hadarmard product of A and B is the trace
       * of A'*B */
      if (bl1->size[0] < 1) {
        i = 1;
        i1 = -1;
      } else {
        i = 2;
        i1 = bl1->size[0] - 1;
      }
      if (bl1->size[1] < 1) {
        kidx = 0;
      } else {
        kidx = bl1->size[1];
      }
      ma = div_s32(i1, i);
      i1 = bl2->size[0] * bl2->size[1];
      bl2->size[0] = ma + 1;
      bl2->size[1] = kidx;
      emxEnsureCapacity_real_T(bl2, i1);
      bl2_data = bl2->data;
      for (i1 = 0; i1 < kidx; i1++) {
        for (b_j1 = 0; b_j1 <= ma; b_j1++) {
          bl2_data[b_j1 + bl2->size[0] * i1] =
              bl1_data[i * b_j1 + bl1->size[0] * i1];
        }
      }
      i = bl1->size[0] * bl1->size[1];
      bl1->size[0] = bl2->size[0];
      bl1->size[1] = bl2->size[1];
      emxEnsureCapacity_real_T(bl1, i);
      bl1_data = bl1->data;
      na = bl2->size[0] * bl2->size[1];
      for (i = 0; i < na; i++) {
        bl1_data[i] = bl2_data[i];
      }
      /*  keeps only the properly aligned sums */
      i = b_var->size[0] * b_var->size[1];
      b_var->size[0] = var->X->size[0];
      b_var->size[1] = var->X->size[1];
      emxEnsureCapacity_real_T(b_var, i);
      bl2_data = b_var->data;
      kidx = var->X->size[0] * var->X->size[1];
      for (i = 0; i < kidx; i++) {
        bl2_data[i] = var->X->data[i] * var->X->data[i];
      }
      conv2AXPYValidCMP(b_var, bl2);
      bl2_data = bl2->data;
      if (bl2->size[0] < 1) {
        i = 1;
        i1 = -1;
      } else {
        i = 2;
        i1 = bl2->size[0] - 1;
      }
      if (bl2->size[1] < 1) {
        kidx = 0;
      } else {
        kidx = bl2->size[1];
      }
      ma = div_s32(i1, i);
      i1 = b_bl2->size[0] * b_bl2->size[1];
      b_bl2->size[0] = ma + 1;
      b_bl2->size[1] = kidx;
      emxEnsureCapacity_real_T(b_bl2, i1);
      a_data = b_bl2->data;
      for (i1 = 0; i1 < kidx; i1++) {
        for (b_j1 = 0; b_j1 <= ma; b_j1++) {
          a_data[b_j1 + b_bl2->size[0] * i1] =
              bl2_data[i * b_j1 + bl2->size[0] * i1];
        }
      }
      i = bl2->size[0] * bl2->size[1];
      bl2->size[0] = b_bl2->size[0];
      bl2->size[1] = b_bl2->size[1];
      emxEnsureCapacity_real_T(bl2, i);
      bl2_data = bl2->data;
      kidx = b_bl2->size[0] * b_bl2->size[1];
      for (i = 0; i < kidx; i++) {
        bl2_data[i] = a_data[i];
      }
      if ((bl1->size[0] == bl2->size[0]) && (bl1->size[1] == bl2->size[1])) {
        i = var->lam->size[0] * var->lam->size[1];
        var->lam->size[0] = bl1->size[0];
        var->lam->size[1] = bl1->size[1];
        emxEnsureCapacity_real_T(var->lam, i);
        for (i = 0; i < na; i++) {
          var->lam->data[i] = bl1_data[i] / bl2_data[i];
        }
      } else {
        e_binary_expand_op(var, bl1, bl2);
      }
      /*  diagonals are NaN from 0/0 */
      i = S->size[0] * S->size[1];
      S->size[0] = (int)diff1;
      S->size[1] = (int)diff1;
      emxEnsureCapacity_real_T(S, i);
      S_data = S->data;
      for (i = 0; i < loop_ub_tmp; i++) {
        S_data[i] = 0.0;
      }
      if ((int)diff1 > 0) {
        for (kidx = 0; kidx < m_tmp_tmp_tmp; kidx++) {
          S_data[kidx + S->size[0] * kidx] = 1.0;
        }
      }
      kidx = loop_ub_tmp - 1;
      for (b_j1 = 0; b_j1 <= kidx; b_j1++) {
        if (S_data[b_j1] != 0.0) {
          var->lam->data[b_j1] = 0.0;
        }
      }
      /*  set the NaN values to 0 */
      /*  objective for A and Lambda */
      ma = var->W->size[0];
      na = var->W->size[1];
      i = K->size[0] * K->size[1];
      K->size[0] = var->W->size[0] << 1;
      K->size[1] = var->W->size[1];
      emxEnsureCapacity_real_T(K, i);
      K_data = K->data;
      kidx = -1;
      for (b_j1 = 0; b_j1 < na; b_j1++) {
        for (i1 = 0; i1 < ma; i1++) {
          K_data[kidx + 1] = var->W->data[i1 + var->W->size[0] * b_j1];
          K_data[kidx + 2] = var->W->data[i1 + var->W->size[0] * b_j1];
          kidx += 2;
        }
      }
      ma = var->lam->size[0];
      na = var->lam->size[1];
      i = b_K->size[0] * b_K->size[1];
      b_K->size[0] = var->lam->size[0] << 1;
      b_K->size[1] = var->lam->size[1];
      emxEnsureCapacity_real_T(b_K, i);
      bl1_data = b_K->data;
      kidx = -1;
      for (b_j1 = 0; b_j1 < na; b_j1++) {
        for (i1 = 0; i1 < ma; i1++) {
          bl1_data[kidx + 1] = var->lam->data[i1 + var->lam->size[0] * b_j1];
          bl1_data[kidx + 2] = var->lam->data[i1 + var->lam->size[0] * b_j1];
          kidx += 2;
        }
      }
      if (var->X->size[0] == 1) {
        i = b_K->size[0];
      } else {
        i = var->X->size[0];
      }
      if (var->X->size[1] == 1) {
        i1 = b_K->size[1];
      } else {
        i1 = var->X->size[1];
      }
      if (var->E_est->size[0] == 1) {
        ma = i;
      } else {
        ma = var->E_est->size[0];
      }
      if (var->E_est->size[1] == 1) {
        na = i1;
      } else {
        na = var->E_est->size[1];
      }
      if ((var->X->size[0] == b_K->size[0]) &&
          (var->X->size[1] == b_K->size[1]) && (var->E_est->size[0] == i) &&
          (var->E_est->size[1] == i1) && (K->size[0] == ma) &&
          (K->size[1] == na)) {
        i = b_var->size[0] * b_var->size[1];
        b_var->size[0] = K->size[0];
        b_var->size[1] = K->size[1];
        emxEnsureCapacity_real_T(b_var, i);
        bl2_data = b_var->data;
        kidx = K->size[0] * K->size[1];
        for (i = 0; i < kidx; i++) {
          f2 = var->E_est->data[i] - var->X->data[i] * bl1_data[i];
          bl2_data[i] = K_data[i] * (f2 * f2);
        }
        combineVectorElements(b_var, r);
      } else {
        d_binary_expand_op(r, K, var, b_K);
      }
      f2 = 0.5 * b_sum(r);
      diff1 = fabs(f2 - f2_old);
      f2_old = f2;
    }
    /*  update B */
    if ((var->X->size[0] == var->gamma->size[0]) &&
        (var->X->size[1] == var->gamma->size[1])) {
      i = b_var->size[0] * b_var->size[1];
      b_var->size[0] = var->X->size[0];
      b_var->size[1] = var->X->size[1];
      emxEnsureCapacity_real_T(b_var, i);
      bl2_data = b_var->data;
      kidx = var->X->size[0] * var->X->size[1];
      for (i = 0; i < kidx; i++) {
        bl2_data[i] = var->X->data[i] - var->gamma->data[i];
      }
      svd(b_var, b_K, S, K);
      K_data = K->data;
      S_data = S->data;
      bl1_data = b_K->data;
    } else {
      n_binary_expand_op(var, b_K, S, K);
      K_data = K->data;
      S_data = S->data;
      bl1_data = b_K->data;
    }
    /*  [U, S, V] = svds(tmpY, 3); */
    i = a->size[0] * a->size[1];
    a->size[0] = b_K->size[0];
    a->size[1] = 3;
    emxEnsureCapacity_real_T(a, i);
    a_data = a->data;
    kidx = b_K->size[0];
    for (i = 0; i < 3; i++) {
      for (i1 = 0; i1 < kidx; i1++) {
        a_data[i1 + a->size[0] * i] = bl1_data[i1 + b_K->size[0] * i];
      }
    }
    na = b_K->size[0];
    i = y->size[0] * y->size[1];
    y->size[0] = b_K->size[0];
    y->size[1] = 3;
    emxEnsureCapacity_real_T(y, i);
    bl2_data = y->data;
    for (iter = 0; iter < 3; iter++) {
      ma = iter * na;
      kidx = iter * 3;
      for (b_j1 = 0; b_j1 < na; b_j1++) {
        bl2_data[ma + b_j1] =
            (a_data[b_j1] * S_data[kidx % 3 + S->size[0] * (kidx / 3)] +
             a_data[b_K->size[0] + b_j1] *
                 S_data[(kidx + 1) % 3 + S->size[0] * ((kidx + 1) / 3)]) +
            a_data[(b_K->size[0] << 1) + b_j1] *
                S_data[(kidx + 2) % 3 + S->size[0] * ((kidx + 2) / 3)];
      }
    }
    i = a->size[0] * a->size[1];
    a->size[0] = K->size[0];
    a->size[1] = 3;
    emxEnsureCapacity_real_T(a, i);
    a_data = a->data;
    kidx = K->size[0];
    for (i = 0; i < 3; i++) {
      for (i1 = 0; i1 < kidx; i1++) {
        a_data[i1 + a->size[0] * i] = K_data[i1 + K->size[0] * i];
      }
    }
    na = y->size[0];
    kidx = K->size[0];
    i = var->Y->size[0] * var->Y->size[1];
    var->Y->size[0] = y->size[0];
    var->Y->size[1] = K->size[0];
    emxEnsureCapacity_real_T(var->Y, i);
    for (iter = 0; iter < kidx; iter++) {
      ma = iter * na;
      for (b_j1 = 0; b_j1 < na; b_j1++) {
        var->Y->data[ma + b_j1] =
            (bl2_data[b_j1] * a_data[iter] +
             bl2_data[y->size[0] + b_j1] * a_data[K->size[0] + iter]) +
            bl2_data[(y->size[0] << 1) + b_j1] *
                a_data[(K->size[0] << 1) + iter];
      }
    }
    /*  var.Y = U*S*V'; */
    /*  update Gamma */
    if ((var->Y->size[0] == var->X->size[0]) &&
        (var->Y->size[1] == var->X->size[1])) {
      i = S->size[0] * S->size[1];
      S->size[0] = var->Y->size[0];
      S->size[1] = var->Y->size[1];
      emxEnsureCapacity_real_T(S, i);
      S_data = S->data;
      kidx = var->Y->size[0] * var->Y->size[1];
      for (i = 0; i < kidx; i++) {
        S_data[i] = var->Y->data[i] - var->X->data[i];
      }
    } else {
      m_binary_expand_op(S, var);
      S_data = S->data;
    }
    if ((var->gamma->size[0] == S->size[0]) &&
        (var->gamma->size[1] == S->size[1])) {
      kidx = var->gamma->size[0] * var->gamma->size[1];
      for (i = 0; i < kidx; i++) {
        var->gamma->data[i] += S_data[i];
      }
    } else {
      l_binary_expand_op(var, S);
    }
    count++;
    i = (int)fmod(count, 20.0);
    if (i == 1) {
      /*  full objective */
      if ((S->size[0] == var->gamma->size[0]) &&
          (S->size[1] == var->gamma->size[1])) {
        i1 = b_var->size[0] * b_var->size[1];
        b_var->size[0] = S->size[0];
        b_var->size[1] = S->size[1];
        emxEnsureCapacity_real_T(b_var, i1);
        bl2_data = b_var->data;
        kidx = S->size[0] * S->size[1];
        for (i1 = 0; i1 < kidx; i1++) {
          bl2_data[i1] = S_data[i1] + var->gamma->data[i1];
        }
        diff1 = b_norm(b_var);
      } else {
        diff1 = k_binary_expand_op(S, var);
      }
      /*  objective for A and Lambda */
      ma = var->W->size[0];
      na = var->W->size[1];
      i1 = K->size[0] * K->size[1];
      K->size[0] = var->W->size[0] << 1;
      K->size[1] = var->W->size[1];
      emxEnsureCapacity_real_T(K, i1);
      K_data = K->data;
      kidx = -1;
      for (b_j1 = 0; b_j1 < na; b_j1++) {
        for (i1 = 0; i1 < ma; i1++) {
          K_data[kidx + 1] = var->W->data[i1 + var->W->size[0] * b_j1];
          K_data[kidx + 2] = var->W->data[i1 + var->W->size[0] * b_j1];
          kidx += 2;
        }
      }
      ma = var->lam->size[0];
      na = var->lam->size[1];
      i1 = b_K->size[0] * b_K->size[1];
      b_K->size[0] = var->lam->size[0] << 1;
      b_K->size[1] = var->lam->size[1];
      emxEnsureCapacity_real_T(b_K, i1);
      bl1_data = b_K->data;
      kidx = -1;
      for (b_j1 = 0; b_j1 < na; b_j1++) {
        for (i1 = 0; i1 < ma; i1++) {
          bl1_data[kidx + 1] = var->lam->data[i1 + var->lam->size[0] * b_j1];
          bl1_data[kidx + 2] = var->lam->data[i1 + var->lam->size[0] * b_j1];
          kidx += 2;
        }
      }
      if (var->E->size[0] == 1) {
        i1 = b_K->size[0];
      } else {
        i1 = var->E->size[0];
      }
      if (var->E->size[1] == 1) {
        b_j1 = b_K->size[1];
      } else {
        b_j1 = var->E->size[1];
      }
      if (var->E_est->size[0] == 1) {
        ma = i1;
      } else {
        ma = var->E_est->size[0];
      }
      if (var->E_est->size[1] == 1) {
        na = b_j1;
      } else {
        na = var->E_est->size[1];
      }
      if ((var->E->size[0] == b_K->size[0]) &&
          (var->E->size[1] == b_K->size[1]) && (var->E_est->size[0] == i1) &&
          (var->E_est->size[1] == b_j1) && (K->size[0] == ma) &&
          (K->size[1] == na)) {
        i1 = b_var->size[0] * b_var->size[1];
        b_var->size[0] = K->size[0];
        b_var->size[1] = K->size[1];
        emxEnsureCapacity_real_T(b_var, i1);
        bl2_data = b_var->data;
        kidx = K->size[0] * K->size[1];
        for (i1 = 0; i1 < kidx; i1++) {
          f2 = var->E_est->data[i1] - var->E->data[i1] * bl1_data[i1];
          bl2_data[i1] = K_data[i1] * (f2 * f2);
        }
        combineVectorElements(b_var, r);
      } else {
        j_binary_expand_op(r, K, var, b_K);
      }
      obj = 0.5 * b_sum(r) + var->tau / 2.0 * (diff1 * diff1);
    }
    if (i == 10) {
      /*  full objective */
      if ((S->size[0] == var->gamma->size[0]) &&
          (S->size[1] == var->gamma->size[1])) {
        i = b_var->size[0] * b_var->size[1];
        b_var->size[0] = S->size[0];
        b_var->size[1] = S->size[1];
        emxEnsureCapacity_real_T(b_var, i);
        bl2_data = b_var->data;
        kidx = S->size[0] * S->size[1];
        for (i = 0; i < kidx; i++) {
          bl2_data[i] = S_data[i] + var->gamma->data[i];
        }
        diff1 = b_norm(b_var);
      } else {
        diff1 = k_binary_expand_op(S, var);
      }
      /*  objective for A and Lambda */
      ma = var->W->size[0];
      na = var->W->size[1];
      i = K->size[0] * K->size[1];
      K->size[0] = var->W->size[0] << 1;
      K->size[1] = var->W->size[1];
      emxEnsureCapacity_real_T(K, i);
      K_data = K->data;
      kidx = -1;
      for (b_j1 = 0; b_j1 < na; b_j1++) {
        for (i1 = 0; i1 < ma; i1++) {
          K_data[kidx + 1] = var->W->data[i1 + var->W->size[0] * b_j1];
          K_data[kidx + 2] = var->W->data[i1 + var->W->size[0] * b_j1];
          kidx += 2;
        }
      }
      ma = var->lam->size[0];
      na = var->lam->size[1];
      i = b_K->size[0] * b_K->size[1];
      b_K->size[0] = var->lam->size[0] << 1;
      b_K->size[1] = var->lam->size[1];
      emxEnsureCapacity_real_T(b_K, i);
      bl1_data = b_K->data;
      kidx = -1;
      for (b_j1 = 0; b_j1 < na; b_j1++) {
        for (i1 = 0; i1 < ma; i1++) {
          bl1_data[kidx + 1] = var->lam->data[i1 + var->lam->size[0] * b_j1];
          bl1_data[kidx + 2] = var->lam->data[i1 + var->lam->size[0] * b_j1];
          kidx += 2;
        }
      }
      if (var->E->size[0] == 1) {
        i = b_K->size[0];
      } else {
        i = var->E->size[0];
      }
      if (var->E->size[1] == 1) {
        i1 = b_K->size[1];
      } else {
        i1 = var->E->size[1];
      }
      if (var->E_est->size[0] == 1) {
        ma = i;
      } else {
        ma = var->E_est->size[0];
      }
      if (var->E_est->size[1] == 1) {
        na = i1;
      } else {
        na = var->E_est->size[1];
      }
      if ((var->E->size[0] == b_K->size[0]) &&
          (var->E->size[1] == b_K->size[1]) && (var->E_est->size[0] == i) &&
          (var->E_est->size[1] == i1) && (K->size[0] == ma) &&
          (K->size[1] == na)) {
        i = b_var->size[0] * b_var->size[1];
        b_var->size[0] = K->size[0];
        b_var->size[1] = K->size[1];
        emxEnsureCapacity_real_T(b_var, i);
        bl2_data = b_var->data;
        kidx = K->size[0] * K->size[1];
        for (i = 0; i < kidx; i++) {
          f2 = var->E_est->data[i] - var->E->data[i] * bl1_data[i];
          bl2_data[i] = K_data[i] * (f2 * f2);
        }
        combineVectorElements(b_var, r);
      } else {
        j_binary_expand_op(r, K, var, b_K);
      }
      diff1 = 0.5 * b_sum(r) + var->tau / 2.0 * (diff1 * diff1);
      diff = fabs(obj - diff1) / fmax(fabs(obj), fabs(diff1));
      if (diff < 1.0E-8) {
        actv = 0;
      }
    }
  }
  emxFree_real_T(&b_bl2);
  emxFree_real_T(&b_var);
  emxFree_real_T(&r);
  emxFree_real_T(&b_K);
  emxFree_real_T(&K);
  emxFree_real_T(&a);
  emxFree_real_T(&y);
  emxFree_real_T(&S);
  emxFree_real_T(&bl2);
  emxFree_real_T(&bl1);
  emxFree_real_T(&G);
  emxCopyStruct_struct0_T(result_var, var);
}

/* End of code generation (ADMM.c) */

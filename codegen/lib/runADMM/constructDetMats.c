/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * constructDetMats.c
 *
 * Code generation for function 'constructDetMats'
 *
 */

/* Include files */
#include "constructDetMats.h"
#include "combineVectorElements.h"
#include "find.h"
#include "prod.h"
#include "repelem.h"
#include "repmat.h"
#include "rt_nonfinite.h"
#include "runADMM_emxutil.h"
#include "runADMM_rtwutil.h"
#include "runADMM_types.h"
#include "sign.h"
#include "sum.h"
#include "triu.h"
#include "rt_nonfinite.h"
#include <math.h>

/* Function Declarations */
static void plus(emxArray_real_T *in1, const emxArray_real_T *in2);

static void u_binary_expand_op(emxArray_real_T *in1);

static void v_binary_expand_op(emxArray_real_T *in1, const emxArray_real_T *in2,
                               const emxArray_real_T *in3);

static void w_binary_expand_op(emxArray_boolean_T *in1,
                               const emxArray_real_T *in2,
                               const emxArray_real_T *in3);

static void x_binary_expand_op(emxArray_real_T *in1,
                               const emxArray_real_T *in2);

/* Function Definitions */
static void plus(emxArray_real_T *in1, const emxArray_real_T *in2)
{
  emxArray_real_T *b_in1;
  const double *in2_data;
  double *b_in1_data;
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
  in1_data = in1->data;
  emxInit_real_T(&b_in1, 2);
  if (in2->size[0] == 1) {
    loop_ub = in1->size[0];
  } else {
    loop_ub = in2->size[0];
  }
  i = b_in1->size[0] * b_in1->size[1];
  b_in1->size[0] = loop_ub;
  if (in2->size[1] == 1) {
    b_loop_ub = in1->size[1];
  } else {
    b_loop_ub = in2->size[1];
  }
  b_in1->size[1] = b_loop_ub;
  emxEnsureCapacity_real_T(b_in1, i);
  b_in1_data = b_in1->data;
  stride_0_0 = (in1->size[0] != 1);
  stride_0_1 = (in1->size[1] != 1);
  stride_1_0 = (in2->size[0] != 1);
  stride_1_1 = (in2->size[1] != 1);
  aux_0_1 = 0;
  aux_1_1 = 0;
  for (i = 0; i < b_loop_ub; i++) {
    for (i1 = 0; i1 < loop_ub; i1++) {
      b_in1_data[i1 + b_in1->size[0] * i] =
          in1_data[i1 * stride_0_0 + in1->size[0] * aux_0_1] +
          in2_data[i1 * stride_1_0 + in2->size[0] * aux_1_1];
    }
    aux_1_1 += stride_1_1;
    aux_0_1 += stride_0_1;
  }
  i = in1->size[0] * in1->size[1];
  in1->size[0] = b_in1->size[0];
  in1->size[1] = b_in1->size[1];
  emxEnsureCapacity_real_T(in1, i);
  in1_data = in1->data;
  loop_ub = b_in1->size[1];
  for (i = 0; i < loop_ub; i++) {
    b_loop_ub = b_in1->size[0];
    for (i1 = 0; i1 < b_loop_ub; i1++) {
      in1_data[i1 + in1->size[0] * i] = b_in1_data[i1 + b_in1->size[0] * i];
    }
  }
  emxFree_real_T(&b_in1);
}

static void u_binary_expand_op(emxArray_real_T *in1)
{
  emxArray_real_T *b_in1;
  double *b_in1_data;
  double *in1_data;
  int aux_0_1;
  int aux_1_1;
  int b_loop_ub;
  int i;
  int i1;
  int loop_ub;
  int stride_0_0_tmp;
  int stride_0_1_tmp;
  in1_data = in1->data;
  emxInit_real_T(&b_in1, 2);
  if (in1->size[1] == 1) {
    loop_ub = in1->size[0];
  } else {
    loop_ub = in1->size[1];
  }
  i = b_in1->size[0] * b_in1->size[1];
  b_in1->size[0] = loop_ub;
  if (in1->size[0] == 1) {
    b_loop_ub = in1->size[1];
  } else {
    b_loop_ub = in1->size[0];
  }
  b_in1->size[1] = b_loop_ub;
  emxEnsureCapacity_real_T(b_in1, i);
  b_in1_data = b_in1->data;
  stride_0_0_tmp = (in1->size[0] != 1);
  stride_0_1_tmp = (in1->size[1] != 1);
  aux_0_1 = 0;
  aux_1_1 = 0;
  for (i = 0; i < b_loop_ub; i++) {
    for (i1 = 0; i1 < loop_ub; i1++) {
      b_in1_data[i1 + b_in1->size[0] * i] =
          in1_data[i1 * stride_0_0_tmp + in1->size[0] * aux_0_1] +
          in1_data[aux_1_1 + in1->size[0] * (i1 * stride_0_1_tmp)];
    }
    aux_1_1 += stride_0_0_tmp;
    aux_0_1 += stride_0_1_tmp;
  }
  i = in1->size[0] * in1->size[1];
  in1->size[0] = b_in1->size[0];
  in1->size[1] = b_in1->size[1];
  emxEnsureCapacity_real_T(in1, i);
  in1_data = in1->data;
  loop_ub = b_in1->size[1];
  for (i = 0; i < loop_ub; i++) {
    b_loop_ub = b_in1->size[0];
    for (i1 = 0; i1 < b_loop_ub; i1++) {
      in1_data[i1 + in1->size[0] * i] = b_in1_data[i1 + b_in1->size[0] * i];
    }
  }
  emxFree_real_T(&b_in1);
}

static void v_binary_expand_op(emxArray_real_T *in1, const emxArray_real_T *in2,
                               const emxArray_real_T *in3)
{
  const double *in2_data;
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
  int stride_1_0;
  int stride_1_1;
  in3_data = in3->data;
  in2_data = in2->data;
  if (in3->size[0] == 1) {
    loop_ub = in2->size[1];
  } else {
    loop_ub = in3->size[0];
  }
  i = in1->size[0] * in1->size[1];
  in1->size[0] = loop_ub;
  emxEnsureCapacity_real_T(in1, i);
  if (in3->size[1] == 1) {
    b_loop_ub = in2->size[0];
  } else {
    b_loop_ub = in3->size[1];
  }
  i = in1->size[0] * in1->size[1];
  in1->size[1] = b_loop_ub;
  emxEnsureCapacity_real_T(in1, i);
  in1_data = in1->data;
  stride_0_0 = (in2->size[1] != 1);
  stride_0_1 = (in2->size[0] != 1);
  stride_1_0 = (in3->size[0] != 1);
  stride_1_1 = (in3->size[1] != 1);
  aux_0_1 = 0;
  aux_1_1 = 0;
  for (i = 0; i < b_loop_ub; i++) {
    for (i1 = 0; i1 < loop_ub; i1++) {
      in1_data[i1 + in1->size[0] * i] =
          in2_data[aux_0_1 + in2->size[0] * (i1 * stride_0_0)] -
          in3_data[i1 * stride_1_0 + in3->size[0] * aux_1_1];
    }
    aux_1_1 += stride_1_1;
    aux_0_1 += stride_0_1;
  }
}

static void w_binary_expand_op(emxArray_boolean_T *in1,
                               const emxArray_real_T *in2,
                               const emxArray_real_T *in3)
{
  const double *in2_data;
  const double *in3_data;
  int i;
  int i1;
  int loop_ub;
  int stride_0_0;
  int stride_1_0;
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
  in1->size[1] = 2;
  emxEnsureCapacity_boolean_T(in1, i);
  in1_data = in1->data;
  stride_0_0 = (in2->size[0] != 1);
  stride_1_0 = (in3->size[0] != 1);
  for (i = 0; i < 2; i++) {
    for (i1 = 0; i1 < loop_ub; i1++) {
      in1_data[i1 + in1->size[0] * i] =
          !(in2_data[i1 * stride_0_0 + in2->size[0] * i] ==
            in3_data[i1 * stride_1_0 + in3->size[0] * i]);
    }
  }
}

static void x_binary_expand_op(emxArray_real_T *in1, const emxArray_real_T *in2)
{
  emxArray_real_T *b_in1;
  const double *in2_data;
  double *b_in1_data;
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
  in1_data = in1->data;
  emxInit_real_T(&b_in1, 2);
  if (in2->size[0] == 1) {
    loop_ub = in1->size[0];
  } else {
    loop_ub = in2->size[0];
  }
  i = b_in1->size[0] * b_in1->size[1];
  b_in1->size[0] = loop_ub;
  if (in2->size[1] == 1) {
    b_loop_ub = in1->size[1];
  } else {
    b_loop_ub = in2->size[1];
  }
  b_in1->size[1] = b_loop_ub;
  emxEnsureCapacity_real_T(b_in1, i);
  b_in1_data = b_in1->data;
  stride_0_0 = (in1->size[0] != 1);
  stride_0_1 = (in1->size[1] != 1);
  stride_1_0 = (in2->size[0] != 1);
  stride_1_1 = (in2->size[1] != 1);
  aux_0_1 = 0;
  aux_1_1 = 0;
  for (i = 0; i < b_loop_ub; i++) {
    for (i1 = 0; i1 < loop_ub; i1++) {
      b_in1_data[i1 + b_in1->size[0] * i] =
          in1_data[i1 * stride_0_0 + in1->size[0] * aux_0_1] *
          in2_data[i1 * stride_1_0 + in2->size[0] * aux_1_1];
    }
    aux_1_1 += stride_1_1;
    aux_0_1 += stride_0_1;
  }
  i = in1->size[0] * in1->size[1];
  in1->size[0] = b_in1->size[0];
  in1->size[1] = b_in1->size[1];
  emxEnsureCapacity_real_T(in1, i);
  in1_data = in1->data;
  loop_ub = b_in1->size[1];
  for (i = 0; i < loop_ub; i++) {
    b_loop_ub = b_in1->size[0];
    for (i1 = 0; i1 < b_loop_ub; i1++) {
      in1_data[i1 + in1->size[0] * i] = b_in1_data[i1 + b_in1->size[0] * i];
    }
  }
  emxFree_real_T(&b_in1);
}

void constructDetMats(double var_n, const emxArray_real_T *var_missing_mu,
                      const emxArray_real_T *var_missing_tau1,
                      const emxArray_real_T *var_missing_tau2,
                      const emxArray_real_T *var_quad, emxArray_real_T *D1_mu,
                      emxArray_real_T *D2_mu, emxArray_real_T *D1_tau,
                      emxArray_real_T *D2_tau)
{
  emxArray_boolean_T *r;
  emxArray_boolean_T *r6;
  emxArray_boolean_T *r7;
  emxArray_boolean_T *r8;
  emxArray_boolean_T *varargin_1_tmp;
  emxArray_int32_T *c_y;
  emxArray_int32_T *v1;
  emxArray_int32_T *vk;
  emxArray_real_T c_col;
  emxArray_real_T *B;
  emxArray_real_T *M;
  emxArray_real_T *a;
  emxArray_real_T *b_M;
  emxArray_real_T *b_col;
  emxArray_real_T *b_var_missing_mu;
  emxArray_real_T *b_y;
  emxArray_real_T *col;
  emxArray_real_T *quad2_sqrt;
  emxArray_real_T *r2;
  emxArray_real_T *r4;
  emxArray_real_T *r5;
  emxArray_real_T *y;
  const double *var_missing_mu_data;
  const double *var_missing_tau1_data;
  const double *var_missing_tau2_data;
  const double *var_quad_data;
  double d;
  double d1;
  double d2;
  double varargin_1;
  double *B_data;
  double *D1_mu_data;
  double *M_data;
  double *a_data;
  double *col_data;
  double *quad2_sqrt_data;
  double *r3;
  double *y_data;
  int b_var_quad[2];
  int c_var_quad[2];
  int d_var_quad[2];
  int e_var_quad[2];
  int b_loop_ub_tmp;
  int i;
  int i1;
  int idx;
  int j;
  int k;
  int loop_ub_tmp;
  int na;
  int ni;
  unsigned int siz_idx_0;
  int *b_y_data;
  int *v1_data;
  int *vk_data;
  boolean_T *r1;
  boolean_T *varargin_1_tmp_data;
  var_quad_data = var_quad->data;
  var_missing_tau2_data = var_missing_tau2->data;
  var_missing_tau1_data = var_missing_tau1->data;
  var_missing_mu_data = var_missing_mu->data;
  idx = var_quad->size[0] * var_quad->size[1];
  emxInit_real_T(&B, 2);
  i = B->size[0] * B->size[1];
  B->size[0] = var_quad->size[0];
  B->size[1] = var_quad->size[1];
  emxEnsureCapacity_real_T(B, i);
  B_data = B->data;
  for (k = 0; k < idx; k++) {
    B_data[k] = fabs(var_quad_data[k]);
  }
  na = B->size[0] * B->size[1];
  for (k = 0; k < na; k++) {
    B_data[k] = sqrt(B_data[k]);
  }
  emxInit_real_T(&quad2_sqrt, 2);
  i = quad2_sqrt->size[0] * quad2_sqrt->size[1];
  quad2_sqrt->size[0] = var_quad->size[0];
  quad2_sqrt->size[1] = var_quad->size[1];
  emxEnsureCapacity_real_T(quad2_sqrt, i);
  quad2_sqrt_data = quad2_sqrt->data;
  for (i = 0; i < idx; i++) {
    quad2_sqrt_data[i] = var_quad_data[i];
  }
  b_sign(quad2_sqrt);
  quad2_sqrt_data = quad2_sqrt->data;
  if ((quad2_sqrt->size[0] == B->size[0]) &&
      (quad2_sqrt->size[1] == B->size[1])) {
    idx = quad2_sqrt->size[0] * quad2_sqrt->size[1];
    for (i = 0; i < idx; i++) {
      quad2_sqrt_data[i] *= B_data[i];
    }
  } else {
    x_binary_expand_op(quad2_sqrt, B);
    quad2_sqrt_data = quad2_sqrt->data;
  }
  /*  Construct the Jacobian matrices for the two sets of determinant equations
   */
  /*  jac1 mu */
  /*  diagonal elements */
  emxInit_real_T(&y, 2);
  y_data = y->data;
  if (rtIsNaN(var_n)) {
    i = y->size[0] * y->size[1];
    y->size[0] = 1;
    y->size[1] = 1;
    emxEnsureCapacity_real_T(y, i);
    y_data = y->data;
    y_data[0] = rtNaN;
  } else if (var_n < 1.0) {
    y->size[0] = 1;
    y->size[1] = 0;
  } else {
    i = y->size[0] * y->size[1];
    y->size[0] = 1;
    y->size[1] = (int)(var_n - 1.0) + 1;
    emxEnsureCapacity_real_T(y, i);
    y_data = y->data;
    idx = (int)(var_n - 1.0);
    for (i = 0; i <= idx; i++) {
      y_data[i] = (double)i + 1.0;
    }
  }
  emxInit_real_T(&b_var_missing_mu, 2);
  i = b_var_missing_mu->size[0] * b_var_missing_mu->size[1];
  b_var_missing_mu->size[0] = var_missing_mu->size[0];
  b_var_missing_mu->size[1] = 2;
  emxEnsureCapacity_real_T(b_var_missing_mu, i);
  D1_mu_data = b_var_missing_mu->data;
  idx = var_missing_mu->size[0];
  for (i = 0; i < 2; i++) {
    for (i1 = 0; i1 < idx; i1++) {
      D1_mu_data[i1 + b_var_missing_mu->size[0] * i] =
          var_missing_mu_data[i1 + var_missing_mu->size[0] * i];
    }
  }
  emxInit_real_T(&M, 2);
  repmat(b_var_missing_mu, var_n, M);
  M_data = M->data;
  i = b_var_missing_mu->size[0] * b_var_missing_mu->size[1];
  b_var_missing_mu->size[0] = quad2_sqrt->size[0];
  b_var_missing_mu->size[1] = 2;
  emxEnsureCapacity_real_T(b_var_missing_mu, i);
  D1_mu_data = b_var_missing_mu->data;
  idx = quad2_sqrt->size[0];
  for (i = 0; i < 2; i++) {
    for (i1 = 0; i1 < idx; i1++) {
      D1_mu_data[i1 + b_var_missing_mu->size[0] * i] =
          quad2_sqrt_data[i1 + quad2_sqrt->size[0] * i];
    }
  }
  emxInit_real_T(&col, 2);
  repmat(b_var_missing_mu, var_n, col);
  col_data = col->data;
  emxInit_real_T(&b_y, 1);
  i = b_y->size[0];
  b_y->size[0] = y->size[1];
  emxEnsureCapacity_real_T(b_y, i);
  D1_mu_data = b_y->data;
  idx = y->size[1];
  for (i = 0; i < idx; i++) {
    D1_mu_data[i] = y_data[i];
  }
  repelem(b_y, var_quad->size[0], b_var_missing_mu);
  D1_mu_data = b_var_missing_mu->data;
  emxInit_boolean_T(&r, 2);
  if (M->size[0] == b_var_missing_mu->size[0]) {
    i = r->size[0] * r->size[1];
    r->size[0] = M->size[0];
    r->size[1] = 2;
    emxEnsureCapacity_boolean_T(r, i);
    r1 = r->data;
    idx = M->size[0] << 1;
    for (i = 0; i < idx; i++) {
      r1[i] = !(M_data[i] == D1_mu_data[i]);
    }
  } else {
    w_binary_expand_op(r, M, b_var_missing_mu);
    r1 = r->data;
  }
  idx = (r->size[0] << 1) - 1;
  for (k = 0; k <= idx; k++) {
    if (r1[k]) {
      col_data[k] = 0.0;
    }
  }
  emxInit_real_T(&b_col, 1);
  c_sum(col, b_col);
  B_data = b_col->data;
  emxInit_real_T(&a, 2);
  i = a->size[0] * a->size[1];
  a->size[0] = var_quad->size[0];
  i1 = (int)var_n;
  a->size[1] = (int)var_n;
  emxEnsureCapacity_real_T(a, i);
  a_data = a->data;
  loop_ub_tmp = var_quad->size[0] * (int)var_n;
  for (i = 0; i < loop_ub_tmp; i++) {
    a_data[i] = B_data[i];
  }
  /*  off-diagonal elements */
  emxInit_real_T(&r2, 2);
  i = r2->size[0] * r2->size[1];
  r2->size[0] = (int)var_n;
  r2->size[1] = (int)var_n;
  emxEnsureCapacity_real_T(r2, i);
  r3 = r2->data;
  b_loop_ub_tmp = (int)var_n * (int)var_n;
  for (i = 0; i < b_loop_ub_tmp; i++) {
    r3[i] = 1.0;
  }
  triu(r2);
  r3 = r2->data;
  i = B->size[0] * B->size[1];
  B->size[0] = r2->size[1];
  B->size[1] = r2->size[0];
  emxEnsureCapacity_real_T(B, i);
  B_data = B->data;
  idx = r2->size[0];
  for (i = 0; i < idx; i++) {
    na = r2->size[1];
    for (k = 0; k < na; k++) {
      B_data[k + B->size[0] * i] = r3[i + r2->size[0] * k];
    }
  }
  siz_idx_0 = (unsigned int)B->size[0];
  emxInit_int32_T(&v1);
  eml_find(B, v1);
  v1_data = v1->data;
  idx = v1->size[0];
  for (i = 0; i < idx; i++) {
    v1_data[i]--;
  }
  emxInit_int32_T(&vk);
  i = vk->size[0];
  vk->size[0] = v1->size[0];
  emxEnsureCapacity_int32_T(vk, i);
  vk_data = vk->data;
  idx = v1->size[0];
  for (i = 0; i < idx; i++) {
    k = div_s32(v1_data[i], (int)siz_idx_0);
    vk_data[i] = k;
    v1_data[i] -= k * (int)siz_idx_0;
  }
  idx = v1->size[0];
  for (i = 0; i < idx; i++) {
    v1_data[i]++;
  }
  i = b_var_missing_mu->size[0] * b_var_missing_mu->size[1];
  b_var_missing_mu->size[0] = quad2_sqrt->size[0];
  b_var_missing_mu->size[1] = 2;
  emxEnsureCapacity_real_T(b_var_missing_mu, i);
  D1_mu_data = b_var_missing_mu->data;
  idx = quad2_sqrt->size[0];
  for (i = 0; i < 2; i++) {
    for (k = 0; k < idx; k++) {
      D1_mu_data[k + b_var_missing_mu->size[0] * i] =
          quad2_sqrt_data[k + quad2_sqrt->size[0] * i];
    }
  }
  repmat(b_var_missing_mu, v1->size[0], col);
  col_data = col->data;
  na = v1->size[0];
  emxInit_int32_T(&c_y);
  i = v1->size[0] * var_quad->size[0];
  k = c_y->size[0];
  c_y->size[0] = i;
  emxEnsureCapacity_int32_T(c_y, k);
  b_y_data = c_y->data;
  idx = -1;
  ni = var_quad->size[0];
  k = b_col->size[0];
  b_col->size[0] = vk->size[0];
  emxEnsureCapacity_real_T(b_col, k);
  B_data = b_col->data;
  for (k = 0; k < na; k++) {
    for (j = 0; j < ni; j++) {
      b_y_data[(idx + j) + 1] = v1_data[k];
    }
    idx += ni;
    B_data[k] = vk_data[k] + 1;
  }
  na = b_col->size[0];
  k = vk->size[0];
  vk->size[0] = i;
  emxEnsureCapacity_int32_T(vk, k);
  vk_data = vk->data;
  idx = -1;
  ni = var_quad->size[0];
  for (k = 0; k < na; k++) {
    for (j = 0; j < ni; j++) {
      vk_data[(idx + j) + 1] = (int)B_data[k];
    }
    idx += ni;
  }
  i = b_y->size[0];
  b_y->size[0] = var_missing_mu->size[0];
  emxEnsureCapacity_real_T(b_y, i);
  D1_mu_data = b_y->data;
  idx = var_missing_mu->size[0];
  for (i = 0; i < idx; i++) {
    D1_mu_data[i] = var_missing_mu_data[i];
  }
  b_repmat(b_y, v1->size[0], b_col);
  B_data = b_col->data;
  i = b_y->size[0];
  b_y->size[0] = var_missing_mu->size[0];
  emxEnsureCapacity_real_T(b_y, i);
  D1_mu_data = b_y->data;
  idx = var_missing_mu->size[0];
  for (i = 0; i < idx; i++) {
    D1_mu_data[i] = var_missing_mu_data[i + var_missing_mu->size[0]];
  }
  emxInit_real_T(&r4, 1);
  b_repmat(b_y, v1->size[0], r4);
  y_data = r4->data;
  emxInit_real_T(&b_M, 2);
  i = b_M->size[0] * b_M->size[1];
  b_M->size[0] = b_col->size[0];
  b_M->size[1] = 4;
  emxEnsureCapacity_real_T(b_M, i);
  M_data = b_M->data;
  idx = b_col->size[0];
  for (i = 0; i < idx; i++) {
    M_data[i] = B_data[i];
  }
  idx = r4->size[0];
  for (i = 0; i < idx; i++) {
    M_data[i + b_M->size[0]] = y_data[i];
  }
  idx = c_y->size[0];
  for (i = 0; i < idx; i++) {
    M_data[i + b_M->size[0] * 2] = b_y_data[i];
  }
  idx = vk->size[0];
  for (i = 0; i < idx; i++) {
    M_data[i + b_M->size[0] * 3] = vk_data[i];
  }
  emxInit_boolean_T(&varargin_1_tmp, 1);
  i = varargin_1_tmp->size[0];
  varargin_1_tmp->size[0] = b_M->size[0];
  emxEnsureCapacity_boolean_T(varargin_1_tmp, i);
  varargin_1_tmp_data = varargin_1_tmp->data;
  idx = b_M->size[0];
  for (i = 0; i < idx; i++) {
    varargin_1 = M_data[i];
    d = M_data[i + b_M->size[0] * 2];
    d1 = M_data[i + b_M->size[0]];
    d2 = M_data[i + b_M->size[0] * 3];
    varargin_1_tmp_data[i] = (((!(varargin_1 == d)) && (!(d1 == d))) ||
                              ((!(varargin_1 == d2)) && (!(d1 == d2))));
  }
  i = r->size[0] * r->size[1];
  r->size[0] = varargin_1_tmp->size[0];
  r->size[1] = 2;
  emxEnsureCapacity_boolean_T(r, i);
  r1 = r->data;
  idx = varargin_1_tmp->size[0];
  for (i = 0; i < idx; i++) {
    r1[i] = varargin_1_tmp_data[i];
    r1[i + r->size[0]] = varargin_1_tmp_data[i];
  }
  idx = (r->size[0] << 1) - 1;
  for (k = 0; k <= idx; k++) {
    if (r1[k]) {
      col_data[k] = 0.0;
    }
  }
  prod(col, b_col);
  B_data = b_col->data;
  idx = b_col->size[0];
  for (i = 0; i < idx; i++) {
    B_data[i] = -B_data[i];
  }
  i = r2->size[0] * r2->size[1];
  r2->size[0] = (int)var_n;
  r2->size[1] = (int)var_n;
  emxEnsureCapacity_real_T(r2, i);
  r3 = r2->data;
  for (i = 0; i < b_loop_ub_tmp; i++) {
    r3[i] = 0.0;
  }
  if ((int)var_n > 0) {
    for (k = 0; k < i1; k++) {
      r3[k + r2->size[0] * k] = 1.0;
    }
  }
  emxInit_real_T(&r5, 2);
  i = r5->size[0] * r5->size[1];
  r5->size[0] = (int)var_n;
  r5->size[1] = (int)var_n;
  emxEnsureCapacity_real_T(r5, i);
  y_data = r5->data;
  for (i = 0; i < b_loop_ub_tmp; i++) {
    y_data[i] = 1.0;
  }
  b_triu(r5);
  y_data = r5->data;
  if ((r2->size[0] == r5->size[1]) && (r5->size[0] == r2->size[1])) {
    i = D1_mu->size[0] * D1_mu->size[1];
    D1_mu->size[0] = r5->size[1];
    D1_mu->size[1] = r5->size[0];
    emxEnsureCapacity_real_T(D1_mu, i);
    D1_mu_data = D1_mu->data;
    idx = r5->size[0];
    for (i = 0; i < idx; i++) {
      na = r5->size[1];
      for (i1 = 0; i1 < na; i1++) {
        D1_mu_data[i1 + D1_mu->size[0] * i] =
            y_data[i + r5->size[0] * i1] - r3[i1 + r2->size[0] * i];
      }
    }
  } else {
    v_binary_expand_op(D1_mu, r5, r2);
    D1_mu_data = D1_mu->data;
  }
  na = var_quad->size[0];
  idx = (int)((double)b_col->size[0] / (double)var_quad->size[0]);
  c_col = *b_col;
  b_var_quad[0] = na;
  b_var_quad[1] = idx;
  c_col.size = &b_var_quad[0];
  c_col.numDimensions = 2;
  combineVectorElements(&c_col, y);
  y_data = y->data;
  ni = D1_mu->size[0] * D1_mu->size[1];
  idx = ni - 1;
  na = 0;
  for (k = 0; k <= idx; k++) {
    if (D1_mu_data[k] == 1.0) {
      D1_mu_data[k] = y_data[na];
      na++;
    }
  }
  i = r5->size[0] * r5->size[1];
  r5->size[0] = a->size[0];
  r5->size[1] = a->size[1];
  emxEnsureCapacity_real_T(r5, i);
  y_data = r5->data;
  for (i = 0; i < loop_ub_tmp; i++) {
    varargin_1 = a_data[i];
    y_data[i] = varargin_1 * varargin_1;
  }
  combineVectorElements(r5, y);
  i = y->size[0] * y->size[1];
  y->size[0] = 1;
  emxEnsureCapacity_real_T(y, i);
  y_data = y->data;
  idx = y->size[1] - 1;
  for (i = 0; i <= idx; i++) {
    y_data[i] *= 0.5;
  }
  idx = y->size[1];
  i = B->size[0] * B->size[1];
  B->size[0] = y->size[1];
  B->size[1] = y->size[1];
  emxEnsureCapacity_real_T(B, i);
  B_data = B->data;
  na = y->size[1] * y->size[1];
  for (i = 0; i < na; i++) {
    B_data[i] = 0.0;
  }
  for (j = 0; j < idx; j++) {
    B_data[j + B->size[0] * j] = y_data[j];
  }
  if ((D1_mu->size[0] == B->size[0]) && (D1_mu->size[1] == B->size[1])) {
    for (i = 0; i < ni; i++) {
      D1_mu_data[i] += B_data[i];
    }
  } else {
    plus(D1_mu, B);
    D1_mu_data = D1_mu->data;
  }
  if (D1_mu->size[0] == D1_mu->size[1]) {
    i = B->size[0] * B->size[1];
    B->size[0] = D1_mu->size[0];
    B->size[1] = D1_mu->size[1];
    emxEnsureCapacity_real_T(B, i);
    B_data = B->data;
    idx = D1_mu->size[1];
    for (i = 0; i < idx; i++) {
      na = D1_mu->size[0];
      for (i1 = 0; i1 < na; i1++) {
        B_data[i1 + B->size[0] * i] = D1_mu_data[i1 + D1_mu->size[0] * i] +
                                      D1_mu_data[i + D1_mu->size[0] * i1];
      }
    }
    i = D1_mu->size[0] * D1_mu->size[1];
    D1_mu->size[0] = B->size[0];
    D1_mu->size[1] = B->size[1];
    emxEnsureCapacity_real_T(D1_mu, i);
    D1_mu_data = D1_mu->data;
    idx = B->size[0] * B->size[1];
    for (i = 0; i < idx; i++) {
      D1_mu_data[i] = B_data[i];
    }
  } else {
    u_binary_expand_op(D1_mu);
  }
  /*  jac2 mu */
  /*  diagonal elements */
  if (var_n < 1.0) {
    y->size[0] = 1;
    y->size[1] = 0;
  } else {
    i = y->size[0] * y->size[1];
    y->size[0] = 1;
    y->size[1] = (int)(var_n - 1.0) + 1;
    emxEnsureCapacity_real_T(y, i);
    y_data = y->data;
    idx = (int)(var_n - 1.0);
    for (i = 0; i <= idx; i++) {
      y_data[i] = (double)i + 1.0;
    }
  }
  i = b_var_missing_mu->size[0] * b_var_missing_mu->size[1];
  b_var_missing_mu->size[0] = var_missing_mu->size[0];
  b_var_missing_mu->size[1] = 2;
  emxEnsureCapacity_real_T(b_var_missing_mu, i);
  D1_mu_data = b_var_missing_mu->data;
  idx = var_missing_mu->size[0];
  for (i = 0; i < 2; i++) {
    for (i1 = 0; i1 < idx; i1++) {
      D1_mu_data[i1 + b_var_missing_mu->size[0] * i] =
          var_missing_mu_data[i1 + var_missing_mu->size[0] * (i + 1)];
    }
  }
  repmat(b_var_missing_mu, var_n, M);
  M_data = M->data;
  i = b_var_missing_mu->size[0] * b_var_missing_mu->size[1];
  b_var_missing_mu->size[0] = quad2_sqrt->size[0];
  b_var_missing_mu->size[1] = 2;
  emxEnsureCapacity_real_T(b_var_missing_mu, i);
  D1_mu_data = b_var_missing_mu->data;
  idx = quad2_sqrt->size[0];
  for (i = 0; i < 2; i++) {
    for (i1 = 0; i1 < idx; i1++) {
      D1_mu_data[i1 + b_var_missing_mu->size[0] * i] =
          quad2_sqrt_data[i1 + quad2_sqrt->size[0] * (i + 1)];
    }
  }
  repmat(b_var_missing_mu, var_n, col);
  col_data = col->data;
  i = b_y->size[0];
  b_y->size[0] = y->size[1];
  emxEnsureCapacity_real_T(b_y, i);
  D1_mu_data = b_y->data;
  idx = y->size[1];
  for (i = 0; i < idx; i++) {
    D1_mu_data[i] = y_data[i];
  }
  repelem(b_y, var_quad->size[0], b_var_missing_mu);
  D1_mu_data = b_var_missing_mu->data;
  emxInit_boolean_T(&r6, 2);
  if (M->size[0] == b_var_missing_mu->size[0]) {
    i = r6->size[0] * r6->size[1];
    r6->size[0] = M->size[0];
    r6->size[1] = 2;
    emxEnsureCapacity_boolean_T(r6, i);
    r1 = r6->data;
    idx = M->size[0] << 1;
    for (i = 0; i < idx; i++) {
      r1[i] = !(M_data[i] == D1_mu_data[i]);
    }
  } else {
    w_binary_expand_op(r6, M, b_var_missing_mu);
    r1 = r6->data;
  }
  idx = (r6->size[0] << 1) - 1;
  for (k = 0; k <= idx; k++) {
    if (r1[k]) {
      col_data[k] = 0.0;
    }
  }
  emxFree_boolean_T(&r6);
  c_sum(col, b_col);
  B_data = b_col->data;
  i = a->size[0] * a->size[1];
  a->size[0] = var_quad->size[0];
  a->size[1] = (int)var_n;
  emxEnsureCapacity_real_T(a, i);
  a_data = a->data;
  for (i = 0; i < loop_ub_tmp; i++) {
    a_data[i] = B_data[i];
  }
  /*  off-diagonal elements */
  i = r5->size[0] * r5->size[1];
  r5->size[0] = (int)var_n;
  r5->size[1] = (int)var_n;
  emxEnsureCapacity_real_T(r5, i);
  y_data = r5->data;
  for (i = 0; i < b_loop_ub_tmp; i++) {
    y_data[i] = 1.0;
  }
  triu(r5);
  y_data = r5->data;
  i = B->size[0] * B->size[1];
  B->size[0] = r5->size[1];
  B->size[1] = r5->size[0];
  emxEnsureCapacity_real_T(B, i);
  B_data = B->data;
  idx = r5->size[0];
  for (i = 0; i < idx; i++) {
    na = r5->size[1];
    for (i1 = 0; i1 < na; i1++) {
      B_data[i1 + B->size[0] * i] = y_data[i + r5->size[0] * i1];
    }
  }
  siz_idx_0 = (unsigned int)B->size[0];
  eml_find(B, v1);
  v1_data = v1->data;
  idx = v1->size[0];
  for (i = 0; i < idx; i++) {
    v1_data[i]--;
  }
  i = vk->size[0];
  vk->size[0] = v1->size[0];
  emxEnsureCapacity_int32_T(vk, i);
  vk_data = vk->data;
  idx = v1->size[0];
  for (i = 0; i < idx; i++) {
    i1 = div_s32(v1_data[i], (int)siz_idx_0);
    vk_data[i] = i1;
    v1_data[i] -= i1 * (int)siz_idx_0;
  }
  idx = v1->size[0];
  for (i = 0; i < idx; i++) {
    v1_data[i]++;
  }
  i = b_var_missing_mu->size[0] * b_var_missing_mu->size[1];
  b_var_missing_mu->size[0] = quad2_sqrt->size[0];
  b_var_missing_mu->size[1] = 2;
  emxEnsureCapacity_real_T(b_var_missing_mu, i);
  D1_mu_data = b_var_missing_mu->data;
  idx = quad2_sqrt->size[0];
  for (i = 0; i < 2; i++) {
    for (i1 = 0; i1 < idx; i1++) {
      D1_mu_data[i1 + b_var_missing_mu->size[0] * i] =
          quad2_sqrt_data[i1 + quad2_sqrt->size[0] * (i + 1)];
    }
  }
  emxFree_real_T(&quad2_sqrt);
  repmat(b_var_missing_mu, v1->size[0], col);
  col_data = col->data;
  na = v1->size[0];
  i = v1->size[0] * var_quad->size[0];
  i1 = c_y->size[0];
  c_y->size[0] = i;
  emxEnsureCapacity_int32_T(c_y, i1);
  b_y_data = c_y->data;
  idx = -1;
  ni = var_quad->size[0];
  i1 = b_col->size[0];
  b_col->size[0] = vk->size[0];
  emxEnsureCapacity_real_T(b_col, i1);
  B_data = b_col->data;
  for (k = 0; k < na; k++) {
    for (j = 0; j < ni; j++) {
      b_y_data[(idx + j) + 1] = v1_data[k];
    }
    idx += ni;
    B_data[k] = vk_data[k] + 1;
  }
  na = b_col->size[0];
  i1 = vk->size[0];
  vk->size[0] = i;
  emxEnsureCapacity_int32_T(vk, i1);
  vk_data = vk->data;
  idx = -1;
  ni = var_quad->size[0];
  for (k = 0; k < na; k++) {
    for (j = 0; j < ni; j++) {
      vk_data[(idx + j) + 1] = (int)B_data[k];
    }
    idx += ni;
  }
  i = b_y->size[0];
  b_y->size[0] = var_missing_mu->size[0];
  emxEnsureCapacity_real_T(b_y, i);
  D1_mu_data = b_y->data;
  idx = var_missing_mu->size[0];
  for (i = 0; i < idx; i++) {
    D1_mu_data[i] = var_missing_mu_data[i + var_missing_mu->size[0]];
  }
  b_repmat(b_y, v1->size[0], b_col);
  B_data = b_col->data;
  i = b_y->size[0];
  b_y->size[0] = var_missing_mu->size[0];
  emxEnsureCapacity_real_T(b_y, i);
  D1_mu_data = b_y->data;
  idx = var_missing_mu->size[0];
  for (i = 0; i < idx; i++) {
    D1_mu_data[i] = var_missing_mu_data[i + var_missing_mu->size[0] * 2];
  }
  b_repmat(b_y, v1->size[0], r4);
  y_data = r4->data;
  i = b_M->size[0] * b_M->size[1];
  b_M->size[0] = b_col->size[0];
  b_M->size[1] = 4;
  emxEnsureCapacity_real_T(b_M, i);
  M_data = b_M->data;
  idx = b_col->size[0];
  for (i = 0; i < idx; i++) {
    M_data[i] = B_data[i];
  }
  idx = r4->size[0];
  for (i = 0; i < idx; i++) {
    M_data[i + b_M->size[0]] = y_data[i];
  }
  idx = c_y->size[0];
  for (i = 0; i < idx; i++) {
    M_data[i + b_M->size[0] * 2] = b_y_data[i];
  }
  idx = vk->size[0];
  for (i = 0; i < idx; i++) {
    M_data[i + b_M->size[0] * 3] = vk_data[i];
  }
  i = varargin_1_tmp->size[0];
  varargin_1_tmp->size[0] = b_M->size[0];
  emxEnsureCapacity_boolean_T(varargin_1_tmp, i);
  varargin_1_tmp_data = varargin_1_tmp->data;
  idx = b_M->size[0];
  for (i = 0; i < idx; i++) {
    varargin_1 = M_data[i];
    d = M_data[i + b_M->size[0] * 2];
    d1 = M_data[i + b_M->size[0]];
    d2 = M_data[i + b_M->size[0] * 3];
    varargin_1_tmp_data[i] = (((!(varargin_1 == d)) && (!(d1 == d))) ||
                              ((!(varargin_1 == d2)) && (!(d1 == d2))));
  }
  i = r->size[0] * r->size[1];
  r->size[0] = varargin_1_tmp->size[0];
  r->size[1] = 2;
  emxEnsureCapacity_boolean_T(r, i);
  r1 = r->data;
  idx = varargin_1_tmp->size[0];
  for (i = 0; i < idx; i++) {
    r1[i] = varargin_1_tmp_data[i];
    r1[i + r->size[0]] = varargin_1_tmp_data[i];
  }
  idx = (r->size[0] << 1) - 1;
  for (k = 0; k <= idx; k++) {
    if (r1[k]) {
      col_data[k] = 0.0;
    }
  }
  prod(col, b_col);
  B_data = b_col->data;
  idx = b_col->size[0];
  for (i = 0; i < idx; i++) {
    B_data[i] = -B_data[i];
  }
  i = r5->size[0] * r5->size[1];
  r5->size[0] = (int)var_n;
  r5->size[1] = (int)var_n;
  emxEnsureCapacity_real_T(r5, i);
  y_data = r5->data;
  for (i = 0; i < b_loop_ub_tmp; i++) {
    y_data[i] = 1.0;
  }
  b_triu(r5);
  y_data = r5->data;
  if ((r2->size[0] == r5->size[1]) && (r5->size[0] == r2->size[1])) {
    i = D2_mu->size[0] * D2_mu->size[1];
    D2_mu->size[0] = r5->size[1];
    D2_mu->size[1] = r5->size[0];
    emxEnsureCapacity_real_T(D2_mu, i);
    D1_mu_data = D2_mu->data;
    idx = r5->size[0];
    for (i = 0; i < idx; i++) {
      na = r5->size[1];
      for (i1 = 0; i1 < na; i1++) {
        D1_mu_data[i1 + D2_mu->size[0] * i] =
            y_data[i + r5->size[0] * i1] - r3[i1 + r2->size[0] * i];
      }
    }
  } else {
    v_binary_expand_op(D2_mu, r5, r2);
    D1_mu_data = D2_mu->data;
  }
  na = var_quad->size[0];
  idx = (int)((double)b_col->size[0] / (double)var_quad->size[0]);
  c_col = *b_col;
  c_var_quad[0] = na;
  c_var_quad[1] = idx;
  c_col.size = &c_var_quad[0];
  c_col.numDimensions = 2;
  combineVectorElements(&c_col, y);
  y_data = y->data;
  ni = D2_mu->size[0] * D2_mu->size[1];
  idx = ni - 1;
  na = 0;
  for (k = 0; k <= idx; k++) {
    if (D1_mu_data[k] == 1.0) {
      D1_mu_data[k] = y_data[na];
      na++;
    }
  }
  i = r5->size[0] * r5->size[1];
  r5->size[0] = a->size[0];
  r5->size[1] = a->size[1];
  emxEnsureCapacity_real_T(r5, i);
  y_data = r5->data;
  for (i = 0; i < loop_ub_tmp; i++) {
    varargin_1 = a_data[i];
    y_data[i] = varargin_1 * varargin_1;
  }
  combineVectorElements(r5, y);
  i = y->size[0] * y->size[1];
  y->size[0] = 1;
  emxEnsureCapacity_real_T(y, i);
  y_data = y->data;
  idx = y->size[1] - 1;
  for (i = 0; i <= idx; i++) {
    y_data[i] *= 0.5;
  }
  idx = y->size[1];
  i = B->size[0] * B->size[1];
  B->size[0] = y->size[1];
  B->size[1] = y->size[1];
  emxEnsureCapacity_real_T(B, i);
  B_data = B->data;
  na = y->size[1] * y->size[1];
  for (i = 0; i < na; i++) {
    B_data[i] = 0.0;
  }
  for (j = 0; j < idx; j++) {
    B_data[j + B->size[0] * j] = y_data[j];
  }
  if ((D2_mu->size[0] == B->size[0]) && (D2_mu->size[1] == B->size[1])) {
    for (i = 0; i < ni; i++) {
      D1_mu_data[i] += B_data[i];
    }
  } else {
    plus(D2_mu, B);
    D1_mu_data = D2_mu->data;
  }
  if (D2_mu->size[0] == D2_mu->size[1]) {
    i = B->size[0] * B->size[1];
    B->size[0] = D2_mu->size[0];
    B->size[1] = D2_mu->size[1];
    emxEnsureCapacity_real_T(B, i);
    B_data = B->data;
    idx = D2_mu->size[1];
    for (i = 0; i < idx; i++) {
      na = D2_mu->size[0];
      for (i1 = 0; i1 < na; i1++) {
        B_data[i1 + B->size[0] * i] = D1_mu_data[i1 + D2_mu->size[0] * i] +
                                      D1_mu_data[i + D2_mu->size[0] * i1];
      }
    }
    i = D2_mu->size[0] * D2_mu->size[1];
    D2_mu->size[0] = B->size[0];
    D2_mu->size[1] = B->size[1];
    emxEnsureCapacity_real_T(D2_mu, i);
    D1_mu_data = D2_mu->data;
    idx = B->size[0] * B->size[1];
    for (i = 0; i < idx; i++) {
      D1_mu_data[i] = B_data[i];
    }
  } else {
    u_binary_expand_op(D2_mu);
  }
  /*  jac1 tau */
  /*  diagonal elements */
  if (var_n < 1.0) {
    y->size[0] = 1;
    y->size[1] = 0;
  } else {
    i = y->size[0] * y->size[1];
    y->size[0] = 1;
    y->size[1] = (int)(var_n - 1.0) + 1;
    emxEnsureCapacity_real_T(y, i);
    y_data = y->data;
    idx = (int)(var_n - 1.0);
    for (i = 0; i <= idx; i++) {
      y_data[i] = (double)i + 1.0;
    }
  }
  i = b_var_missing_mu->size[0] * b_var_missing_mu->size[1];
  b_var_missing_mu->size[0] = var_missing_tau1->size[0];
  b_var_missing_mu->size[1] = 2;
  emxEnsureCapacity_real_T(b_var_missing_mu, i);
  D1_mu_data = b_var_missing_mu->data;
  idx = var_missing_tau1->size[0];
  for (i = 0; i < 2; i++) {
    for (i1 = 0; i1 < idx; i1++) {
      D1_mu_data[i1 + b_var_missing_mu->size[0] * i] =
          var_missing_tau1_data[i1 + var_missing_tau1->size[0] * i];
    }
  }
  repmat(b_var_missing_mu, var_n, M);
  M_data = M->data;
  i = b_var_missing_mu->size[0] * b_var_missing_mu->size[1];
  b_var_missing_mu->size[0] = var_quad->size[0];
  b_var_missing_mu->size[1] = 2;
  emxEnsureCapacity_real_T(b_var_missing_mu, i);
  D1_mu_data = b_var_missing_mu->data;
  idx = var_quad->size[0];
  for (i = 0; i < 2; i++) {
    for (i1 = 0; i1 < idx; i1++) {
      D1_mu_data[i1 + b_var_missing_mu->size[0] * i] =
          var_quad_data[i1 + var_quad->size[0] * i];
    }
  }
  repmat(b_var_missing_mu, var_n, col);
  col_data = col->data;
  i = b_y->size[0];
  b_y->size[0] = y->size[1];
  emxEnsureCapacity_real_T(b_y, i);
  D1_mu_data = b_y->data;
  idx = y->size[1];
  for (i = 0; i < idx; i++) {
    D1_mu_data[i] = y_data[i];
  }
  repelem(b_y, var_quad->size[0], b_var_missing_mu);
  D1_mu_data = b_var_missing_mu->data;
  emxInit_boolean_T(&r7, 2);
  if (M->size[0] == b_var_missing_mu->size[0]) {
    i = r7->size[0] * r7->size[1];
    r7->size[0] = M->size[0];
    r7->size[1] = 2;
    emxEnsureCapacity_boolean_T(r7, i);
    r1 = r7->data;
    idx = M->size[0] << 1;
    for (i = 0; i < idx; i++) {
      r1[i] = !(M_data[i] == D1_mu_data[i]);
    }
  } else {
    w_binary_expand_op(r7, M, b_var_missing_mu);
    r1 = r7->data;
  }
  idx = (r7->size[0] << 1) - 1;
  for (k = 0; k <= idx; k++) {
    if (r1[k]) {
      col_data[k] = 0.0;
    }
  }
  emxFree_boolean_T(&r7);
  c_sum(col, b_col);
  B_data = b_col->data;
  i = a->size[0] * a->size[1];
  a->size[0] = var_quad->size[0];
  a->size[1] = (int)var_n;
  emxEnsureCapacity_real_T(a, i);
  a_data = a->data;
  for (i = 0; i < loop_ub_tmp; i++) {
    a_data[i] = B_data[i];
  }
  /*  off-diagonal elements */
  i = r5->size[0] * r5->size[1];
  r5->size[0] = (int)var_n;
  r5->size[1] = (int)var_n;
  emxEnsureCapacity_real_T(r5, i);
  y_data = r5->data;
  for (i = 0; i < b_loop_ub_tmp; i++) {
    y_data[i] = 1.0;
  }
  triu(r5);
  y_data = r5->data;
  i = B->size[0] * B->size[1];
  B->size[0] = r5->size[1];
  B->size[1] = r5->size[0];
  emxEnsureCapacity_real_T(B, i);
  B_data = B->data;
  idx = r5->size[0];
  for (i = 0; i < idx; i++) {
    na = r5->size[1];
    for (i1 = 0; i1 < na; i1++) {
      B_data[i1 + B->size[0] * i] = y_data[i + r5->size[0] * i1];
    }
  }
  siz_idx_0 = (unsigned int)B->size[0];
  eml_find(B, v1);
  v1_data = v1->data;
  idx = v1->size[0];
  for (i = 0; i < idx; i++) {
    v1_data[i]--;
  }
  i = vk->size[0];
  vk->size[0] = v1->size[0];
  emxEnsureCapacity_int32_T(vk, i);
  vk_data = vk->data;
  idx = v1->size[0];
  for (i = 0; i < idx; i++) {
    i1 = div_s32(v1_data[i], (int)siz_idx_0);
    vk_data[i] = i1;
    v1_data[i] -= i1 * (int)siz_idx_0;
  }
  idx = v1->size[0];
  for (i = 0; i < idx; i++) {
    v1_data[i]++;
  }
  i = b_var_missing_mu->size[0] * b_var_missing_mu->size[1];
  b_var_missing_mu->size[0] = var_quad->size[0];
  b_var_missing_mu->size[1] = 2;
  emxEnsureCapacity_real_T(b_var_missing_mu, i);
  D1_mu_data = b_var_missing_mu->data;
  idx = var_quad->size[0];
  for (i = 0; i < 2; i++) {
    for (i1 = 0; i1 < idx; i1++) {
      D1_mu_data[i1 + b_var_missing_mu->size[0] * i] =
          var_quad_data[i1 + var_quad->size[0] * i];
    }
  }
  repmat(b_var_missing_mu, v1->size[0], col);
  col_data = col->data;
  na = v1->size[0];
  i = v1->size[0] * var_quad->size[0];
  i1 = c_y->size[0];
  c_y->size[0] = i;
  emxEnsureCapacity_int32_T(c_y, i1);
  b_y_data = c_y->data;
  idx = -1;
  ni = var_quad->size[0];
  i1 = b_col->size[0];
  b_col->size[0] = vk->size[0];
  emxEnsureCapacity_real_T(b_col, i1);
  B_data = b_col->data;
  for (k = 0; k < na; k++) {
    for (j = 0; j < ni; j++) {
      b_y_data[(idx + j) + 1] = v1_data[k];
    }
    idx += ni;
    B_data[k] = vk_data[k] + 1;
  }
  na = b_col->size[0];
  i1 = vk->size[0];
  vk->size[0] = i;
  emxEnsureCapacity_int32_T(vk, i1);
  vk_data = vk->data;
  idx = -1;
  ni = var_quad->size[0];
  for (k = 0; k < na; k++) {
    for (j = 0; j < ni; j++) {
      vk_data[(idx + j) + 1] = (int)B_data[k];
    }
    idx += ni;
  }
  i = b_y->size[0];
  b_y->size[0] = var_missing_tau1->size[0];
  emxEnsureCapacity_real_T(b_y, i);
  D1_mu_data = b_y->data;
  idx = var_missing_tau1->size[0];
  for (i = 0; i < idx; i++) {
    D1_mu_data[i] = var_missing_tau1_data[i];
  }
  b_repmat(b_y, v1->size[0], b_col);
  B_data = b_col->data;
  i = b_y->size[0];
  b_y->size[0] = var_missing_tau1->size[0];
  emxEnsureCapacity_real_T(b_y, i);
  D1_mu_data = b_y->data;
  idx = var_missing_tau1->size[0];
  for (i = 0; i < idx; i++) {
    D1_mu_data[i] = var_missing_tau1_data[i + var_missing_tau1->size[0]];
  }
  b_repmat(b_y, v1->size[0], r4);
  y_data = r4->data;
  i = b_M->size[0] * b_M->size[1];
  b_M->size[0] = b_col->size[0];
  b_M->size[1] = 4;
  emxEnsureCapacity_real_T(b_M, i);
  M_data = b_M->data;
  idx = b_col->size[0];
  for (i = 0; i < idx; i++) {
    M_data[i] = B_data[i];
  }
  idx = r4->size[0];
  for (i = 0; i < idx; i++) {
    M_data[i + b_M->size[0]] = y_data[i];
  }
  idx = c_y->size[0];
  for (i = 0; i < idx; i++) {
    M_data[i + b_M->size[0] * 2] = b_y_data[i];
  }
  idx = vk->size[0];
  for (i = 0; i < idx; i++) {
    M_data[i + b_M->size[0] * 3] = vk_data[i];
  }
  i = varargin_1_tmp->size[0];
  varargin_1_tmp->size[0] = b_M->size[0];
  emxEnsureCapacity_boolean_T(varargin_1_tmp, i);
  varargin_1_tmp_data = varargin_1_tmp->data;
  idx = b_M->size[0];
  for (i = 0; i < idx; i++) {
    varargin_1 = M_data[i];
    d = M_data[i + b_M->size[0] * 2];
    d1 = M_data[i + b_M->size[0]];
    d2 = M_data[i + b_M->size[0] * 3];
    varargin_1_tmp_data[i] = (((!(varargin_1 == d)) && (!(d1 == d))) ||
                              ((!(varargin_1 == d2)) && (!(d1 == d2))));
  }
  i = r->size[0] * r->size[1];
  r->size[0] = varargin_1_tmp->size[0];
  r->size[1] = 2;
  emxEnsureCapacity_boolean_T(r, i);
  r1 = r->data;
  idx = varargin_1_tmp->size[0];
  for (i = 0; i < idx; i++) {
    r1[i] = varargin_1_tmp_data[i];
    r1[i + r->size[0]] = varargin_1_tmp_data[i];
  }
  idx = (r->size[0] << 1) - 1;
  for (k = 0; k <= idx; k++) {
    if (r1[k]) {
      col_data[k] = 0.0;
    }
  }
  prod(col, b_col);
  B_data = b_col->data;
  idx = b_col->size[0];
  for (i = 0; i < idx; i++) {
    B_data[i] = -B_data[i];
  }
  i = r5->size[0] * r5->size[1];
  r5->size[0] = (int)var_n;
  r5->size[1] = (int)var_n;
  emxEnsureCapacity_real_T(r5, i);
  y_data = r5->data;
  for (i = 0; i < b_loop_ub_tmp; i++) {
    y_data[i] = 1.0;
  }
  b_triu(r5);
  y_data = r5->data;
  if ((r2->size[0] == r5->size[1]) && (r5->size[0] == r2->size[1])) {
    i = D1_tau->size[0] * D1_tau->size[1];
    D1_tau->size[0] = r5->size[1];
    D1_tau->size[1] = r5->size[0];
    emxEnsureCapacity_real_T(D1_tau, i);
    D1_mu_data = D1_tau->data;
    idx = r5->size[0];
    for (i = 0; i < idx; i++) {
      na = r5->size[1];
      for (i1 = 0; i1 < na; i1++) {
        D1_mu_data[i1 + D1_tau->size[0] * i] =
            y_data[i + r5->size[0] * i1] - r3[i1 + r2->size[0] * i];
      }
    }
  } else {
    v_binary_expand_op(D1_tau, r5, r2);
    D1_mu_data = D1_tau->data;
  }
  na = var_quad->size[0];
  idx = (int)((double)b_col->size[0] / (double)var_quad->size[0]);
  c_col = *b_col;
  d_var_quad[0] = na;
  d_var_quad[1] = idx;
  c_col.size = &d_var_quad[0];
  c_col.numDimensions = 2;
  combineVectorElements(&c_col, y);
  y_data = y->data;
  ni = D1_tau->size[0] * D1_tau->size[1];
  idx = ni - 1;
  na = 0;
  for (k = 0; k <= idx; k++) {
    if (D1_mu_data[k] == 1.0) {
      D1_mu_data[k] = y_data[na];
      na++;
    }
  }
  i = r5->size[0] * r5->size[1];
  r5->size[0] = a->size[0];
  r5->size[1] = a->size[1];
  emxEnsureCapacity_real_T(r5, i);
  y_data = r5->data;
  for (i = 0; i < loop_ub_tmp; i++) {
    varargin_1 = a_data[i];
    y_data[i] = varargin_1 * varargin_1;
  }
  combineVectorElements(r5, y);
  i = y->size[0] * y->size[1];
  y->size[0] = 1;
  emxEnsureCapacity_real_T(y, i);
  y_data = y->data;
  idx = y->size[1] - 1;
  for (i = 0; i <= idx; i++) {
    y_data[i] *= 0.5;
  }
  idx = y->size[1];
  i = B->size[0] * B->size[1];
  B->size[0] = y->size[1];
  B->size[1] = y->size[1];
  emxEnsureCapacity_real_T(B, i);
  B_data = B->data;
  na = y->size[1] * y->size[1];
  for (i = 0; i < na; i++) {
    B_data[i] = 0.0;
  }
  for (j = 0; j < idx; j++) {
    B_data[j + B->size[0] * j] = y_data[j];
  }
  if ((D1_tau->size[0] == B->size[0]) && (D1_tau->size[1] == B->size[1])) {
    for (i = 0; i < ni; i++) {
      D1_mu_data[i] += B_data[i];
    }
  } else {
    plus(D1_tau, B);
    D1_mu_data = D1_tau->data;
  }
  if (D1_tau->size[0] == D1_tau->size[1]) {
    i = B->size[0] * B->size[1];
    B->size[0] = D1_tau->size[0];
    B->size[1] = D1_tau->size[1];
    emxEnsureCapacity_real_T(B, i);
    B_data = B->data;
    idx = D1_tau->size[1];
    for (i = 0; i < idx; i++) {
      na = D1_tau->size[0];
      for (i1 = 0; i1 < na; i1++) {
        B_data[i1 + B->size[0] * i] = D1_mu_data[i1 + D1_tau->size[0] * i] +
                                      D1_mu_data[i + D1_tau->size[0] * i1];
      }
    }
    i = D1_tau->size[0] * D1_tau->size[1];
    D1_tau->size[0] = B->size[0];
    D1_tau->size[1] = B->size[1];
    emxEnsureCapacity_real_T(D1_tau, i);
    D1_mu_data = D1_tau->data;
    idx = B->size[0] * B->size[1];
    for (i = 0; i < idx; i++) {
      D1_mu_data[i] = B_data[i];
    }
  } else {
    u_binary_expand_op(D1_tau);
  }
  /*  jac2 tau */
  /*  diagonal elements */
  if (var_n < 1.0) {
    y->size[0] = 1;
    y->size[1] = 0;
  } else {
    i = y->size[0] * y->size[1];
    y->size[0] = 1;
    y->size[1] = (int)(var_n - 1.0) + 1;
    emxEnsureCapacity_real_T(y, i);
    y_data = y->data;
    idx = (int)(var_n - 1.0);
    for (i = 0; i <= idx; i++) {
      y_data[i] = (double)i + 1.0;
    }
  }
  i = b_var_missing_mu->size[0] * b_var_missing_mu->size[1];
  b_var_missing_mu->size[0] = var_missing_tau2->size[0];
  b_var_missing_mu->size[1] = 2;
  emxEnsureCapacity_real_T(b_var_missing_mu, i);
  D1_mu_data = b_var_missing_mu->data;
  idx = var_missing_tau2->size[0];
  for (i = 0; i < 2; i++) {
    for (i1 = 0; i1 < idx; i1++) {
      D1_mu_data[i1 + b_var_missing_mu->size[0] * i] =
          var_missing_tau2_data[i1 + var_missing_tau2->size[0] * i];
    }
  }
  repmat(b_var_missing_mu, var_n, M);
  M_data = M->data;
  i = b_var_missing_mu->size[0] * b_var_missing_mu->size[1];
  b_var_missing_mu->size[0] = var_quad->size[0];
  b_var_missing_mu->size[1] = 2;
  emxEnsureCapacity_real_T(b_var_missing_mu, i);
  D1_mu_data = b_var_missing_mu->data;
  idx = var_quad->size[0];
  for (i = 0; i < 2; i++) {
    for (i1 = 0; i1 < idx; i1++) {
      D1_mu_data[i1 + b_var_missing_mu->size[0] * i] =
          var_quad_data[i1 + var_quad->size[0] * (i + 1)];
    }
  }
  repmat(b_var_missing_mu, var_n, col);
  col_data = col->data;
  i = b_y->size[0];
  b_y->size[0] = y->size[1];
  emxEnsureCapacity_real_T(b_y, i);
  D1_mu_data = b_y->data;
  idx = y->size[1];
  for (i = 0; i < idx; i++) {
    D1_mu_data[i] = y_data[i];
  }
  repelem(b_y, var_quad->size[0], b_var_missing_mu);
  D1_mu_data = b_var_missing_mu->data;
  emxInit_boolean_T(&r8, 2);
  if (M->size[0] == b_var_missing_mu->size[0]) {
    i = r8->size[0] * r8->size[1];
    r8->size[0] = M->size[0];
    r8->size[1] = 2;
    emxEnsureCapacity_boolean_T(r8, i);
    r1 = r8->data;
    idx = M->size[0] << 1;
    for (i = 0; i < idx; i++) {
      r1[i] = !(M_data[i] == D1_mu_data[i]);
    }
  } else {
    w_binary_expand_op(r8, M, b_var_missing_mu);
    r1 = r8->data;
  }
  emxFree_real_T(&M);
  idx = (r8->size[0] << 1) - 1;
  for (k = 0; k <= idx; k++) {
    if (r1[k]) {
      col_data[k] = 0.0;
    }
  }
  emxFree_boolean_T(&r8);
  c_sum(col, b_col);
  B_data = b_col->data;
  i = a->size[0] * a->size[1];
  a->size[0] = var_quad->size[0];
  a->size[1] = (int)var_n;
  emxEnsureCapacity_real_T(a, i);
  a_data = a->data;
  for (i = 0; i < loop_ub_tmp; i++) {
    a_data[i] = B_data[i];
  }
  /*  off-diagonal elements */
  i = r5->size[0] * r5->size[1];
  r5->size[0] = (int)var_n;
  r5->size[1] = (int)var_n;
  emxEnsureCapacity_real_T(r5, i);
  y_data = r5->data;
  for (i = 0; i < b_loop_ub_tmp; i++) {
    y_data[i] = 1.0;
  }
  triu(r5);
  y_data = r5->data;
  i = B->size[0] * B->size[1];
  B->size[0] = r5->size[1];
  B->size[1] = r5->size[0];
  emxEnsureCapacity_real_T(B, i);
  B_data = B->data;
  idx = r5->size[0];
  for (i = 0; i < idx; i++) {
    na = r5->size[1];
    for (i1 = 0; i1 < na; i1++) {
      B_data[i1 + B->size[0] * i] = y_data[i + r5->size[0] * i1];
    }
  }
  siz_idx_0 = (unsigned int)B->size[0];
  eml_find(B, v1);
  v1_data = v1->data;
  idx = v1->size[0];
  for (i = 0; i < idx; i++) {
    v1_data[i]--;
  }
  i = vk->size[0];
  vk->size[0] = v1->size[0];
  emxEnsureCapacity_int32_T(vk, i);
  vk_data = vk->data;
  idx = v1->size[0];
  for (i = 0; i < idx; i++) {
    i1 = div_s32(v1_data[i], (int)siz_idx_0);
    vk_data[i] = i1;
    v1_data[i] -= i1 * (int)siz_idx_0;
  }
  idx = v1->size[0];
  for (i = 0; i < idx; i++) {
    v1_data[i]++;
  }
  i = b_var_missing_mu->size[0] * b_var_missing_mu->size[1];
  b_var_missing_mu->size[0] = var_quad->size[0];
  b_var_missing_mu->size[1] = 2;
  emxEnsureCapacity_real_T(b_var_missing_mu, i);
  D1_mu_data = b_var_missing_mu->data;
  idx = var_quad->size[0];
  for (i = 0; i < 2; i++) {
    for (i1 = 0; i1 < idx; i1++) {
      D1_mu_data[i1 + b_var_missing_mu->size[0] * i] =
          var_quad_data[i1 + var_quad->size[0] * (i + 1)];
    }
  }
  repmat(b_var_missing_mu, v1->size[0], col);
  col_data = col->data;
  emxFree_real_T(&b_var_missing_mu);
  na = v1->size[0];
  i = v1->size[0] * var_quad->size[0];
  i1 = c_y->size[0];
  c_y->size[0] = i;
  emxEnsureCapacity_int32_T(c_y, i1);
  b_y_data = c_y->data;
  idx = -1;
  ni = var_quad->size[0];
  i1 = b_col->size[0];
  b_col->size[0] = vk->size[0];
  emxEnsureCapacity_real_T(b_col, i1);
  B_data = b_col->data;
  for (k = 0; k < na; k++) {
    for (j = 0; j < ni; j++) {
      b_y_data[(idx + j) + 1] = v1_data[k];
    }
    idx += ni;
    B_data[k] = vk_data[k] + 1;
  }
  na = b_col->size[0];
  i1 = vk->size[0];
  vk->size[0] = i;
  emxEnsureCapacity_int32_T(vk, i1);
  vk_data = vk->data;
  idx = -1;
  ni = var_quad->size[0];
  for (k = 0; k < na; k++) {
    for (j = 0; j < ni; j++) {
      vk_data[(idx + j) + 1] = (int)B_data[k];
    }
    idx += ni;
  }
  i = b_y->size[0];
  b_y->size[0] = var_missing_tau2->size[0];
  emxEnsureCapacity_real_T(b_y, i);
  D1_mu_data = b_y->data;
  idx = var_missing_tau2->size[0];
  for (i = 0; i < idx; i++) {
    D1_mu_data[i] = var_missing_tau2_data[i];
  }
  b_repmat(b_y, v1->size[0], b_col);
  B_data = b_col->data;
  i = b_y->size[0];
  b_y->size[0] = var_missing_tau2->size[0];
  emxEnsureCapacity_real_T(b_y, i);
  D1_mu_data = b_y->data;
  idx = var_missing_tau2->size[0];
  for (i = 0; i < idx; i++) {
    D1_mu_data[i] = var_missing_tau2_data[i + var_missing_tau2->size[0]];
  }
  b_repmat(b_y, v1->size[0], r4);
  y_data = r4->data;
  emxFree_real_T(&b_y);
  emxFree_int32_T(&v1);
  i = b_M->size[0] * b_M->size[1];
  b_M->size[0] = b_col->size[0];
  b_M->size[1] = 4;
  emxEnsureCapacity_real_T(b_M, i);
  M_data = b_M->data;
  idx = b_col->size[0];
  for (i = 0; i < idx; i++) {
    M_data[i] = B_data[i];
  }
  idx = r4->size[0];
  for (i = 0; i < idx; i++) {
    M_data[i + b_M->size[0]] = y_data[i];
  }
  emxFree_real_T(&r4);
  idx = c_y->size[0];
  for (i = 0; i < idx; i++) {
    M_data[i + b_M->size[0] * 2] = b_y_data[i];
  }
  emxFree_int32_T(&c_y);
  idx = vk->size[0];
  for (i = 0; i < idx; i++) {
    M_data[i + b_M->size[0] * 3] = vk_data[i];
  }
  emxFree_int32_T(&vk);
  i = varargin_1_tmp->size[0];
  varargin_1_tmp->size[0] = b_M->size[0];
  emxEnsureCapacity_boolean_T(varargin_1_tmp, i);
  varargin_1_tmp_data = varargin_1_tmp->data;
  idx = b_M->size[0];
  for (i = 0; i < idx; i++) {
    varargin_1 = M_data[i];
    d = M_data[i + b_M->size[0] * 2];
    d1 = M_data[i + b_M->size[0]];
    d2 = M_data[i + b_M->size[0] * 3];
    varargin_1_tmp_data[i] = (((!(varargin_1 == d)) && (!(d1 == d))) ||
                              ((!(varargin_1 == d2)) && (!(d1 == d2))));
  }
  emxFree_real_T(&b_M);
  i = r->size[0] * r->size[1];
  r->size[0] = varargin_1_tmp->size[0];
  r->size[1] = 2;
  emxEnsureCapacity_boolean_T(r, i);
  r1 = r->data;
  idx = varargin_1_tmp->size[0];
  for (i = 0; i < idx; i++) {
    r1[i] = varargin_1_tmp_data[i];
    r1[i + r->size[0]] = varargin_1_tmp_data[i];
  }
  emxFree_boolean_T(&varargin_1_tmp);
  idx = (r->size[0] << 1) - 1;
  for (k = 0; k <= idx; k++) {
    if (r1[k]) {
      col_data[k] = 0.0;
    }
  }
  emxFree_boolean_T(&r);
  prod(col, b_col);
  B_data = b_col->data;
  emxFree_real_T(&col);
  idx = b_col->size[0];
  for (i = 0; i < idx; i++) {
    B_data[i] = -B_data[i];
  }
  i = r5->size[0] * r5->size[1];
  r5->size[0] = (int)var_n;
  r5->size[1] = (int)var_n;
  emxEnsureCapacity_real_T(r5, i);
  y_data = r5->data;
  for (i = 0; i < b_loop_ub_tmp; i++) {
    y_data[i] = 1.0;
  }
  b_triu(r5);
  y_data = r5->data;
  if ((r2->size[0] == r5->size[1]) && (r5->size[0] == r2->size[1])) {
    i = D2_tau->size[0] * D2_tau->size[1];
    D2_tau->size[0] = r5->size[1];
    D2_tau->size[1] = r5->size[0];
    emxEnsureCapacity_real_T(D2_tau, i);
    D1_mu_data = D2_tau->data;
    idx = r5->size[0];
    for (i = 0; i < idx; i++) {
      na = r5->size[1];
      for (i1 = 0; i1 < na; i1++) {
        D1_mu_data[i1 + D2_tau->size[0] * i] =
            y_data[i + r5->size[0] * i1] - r3[i1 + r2->size[0] * i];
      }
    }
  } else {
    v_binary_expand_op(D2_tau, r5, r2);
    D1_mu_data = D2_tau->data;
  }
  emxFree_real_T(&r5);
  na = var_quad->size[0];
  idx = (int)((double)b_col->size[0] / (double)var_quad->size[0]);
  c_col = *b_col;
  e_var_quad[0] = na;
  e_var_quad[1] = idx;
  c_col.size = &e_var_quad[0];
  c_col.numDimensions = 2;
  combineVectorElements(&c_col, y);
  y_data = y->data;
  emxFree_real_T(&b_col);
  ni = D2_tau->size[0] * D2_tau->size[1];
  idx = ni - 1;
  na = 0;
  for (k = 0; k <= idx; k++) {
    if (D1_mu_data[k] == 1.0) {
      D1_mu_data[k] = y_data[na];
      na++;
    }
  }
  i = r2->size[0] * r2->size[1];
  r2->size[0] = a->size[0];
  r2->size[1] = a->size[1];
  emxEnsureCapacity_real_T(r2, i);
  r3 = r2->data;
  for (i = 0; i < loop_ub_tmp; i++) {
    varargin_1 = a_data[i];
    r3[i] = varargin_1 * varargin_1;
  }
  emxFree_real_T(&a);
  combineVectorElements(r2, y);
  emxFree_real_T(&r2);
  i = y->size[0] * y->size[1];
  y->size[0] = 1;
  emxEnsureCapacity_real_T(y, i);
  y_data = y->data;
  idx = y->size[1] - 1;
  for (i = 0; i <= idx; i++) {
    y_data[i] *= 0.5;
  }
  idx = y->size[1];
  i = B->size[0] * B->size[1];
  B->size[0] = y->size[1];
  B->size[1] = y->size[1];
  emxEnsureCapacity_real_T(B, i);
  B_data = B->data;
  loop_ub_tmp = y->size[1] * y->size[1];
  for (i = 0; i < loop_ub_tmp; i++) {
    B_data[i] = 0.0;
  }
  for (j = 0; j < idx; j++) {
    B_data[j + B->size[0] * j] = y_data[j];
  }
  emxFree_real_T(&y);
  if ((D2_tau->size[0] == B->size[0]) && (D2_tau->size[1] == B->size[1])) {
    for (i = 0; i < ni; i++) {
      D1_mu_data[i] += B_data[i];
    }
  } else {
    plus(D2_tau, B);
    D1_mu_data = D2_tau->data;
  }
  if (D2_tau->size[0] == D2_tau->size[1]) {
    i = B->size[0] * B->size[1];
    B->size[0] = D2_tau->size[0];
    B->size[1] = D2_tau->size[1];
    emxEnsureCapacity_real_T(B, i);
    B_data = B->data;
    idx = D2_tau->size[1];
    for (i = 0; i < idx; i++) {
      na = D2_tau->size[0];
      for (i1 = 0; i1 < na; i1++) {
        B_data[i1 + B->size[0] * i] = D1_mu_data[i1 + D2_tau->size[0] * i] +
                                      D1_mu_data[i + D2_tau->size[0] * i1];
      }
    }
    i = D2_tau->size[0] * D2_tau->size[1];
    D2_tau->size[0] = B->size[0];
    D2_tau->size[1] = B->size[1];
    emxEnsureCapacity_real_T(D2_tau, i);
    D1_mu_data = D2_tau->data;
    idx = B->size[0] * B->size[1];
    for (i = 0; i < idx; i++) {
      D1_mu_data[i] = B_data[i];
    }
  } else {
    u_binary_expand_op(D2_tau);
  }
  emxFree_real_T(&B);
}

/* End of code generation (constructDetMats.c) */

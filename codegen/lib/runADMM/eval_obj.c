/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * eval_obj.c
 *
 * Code generation for function 'eval_obj'
 *
 */

/* Include files */
#include "eval_obj.h"
#include "rt_nonfinite.h"
#include "runADMM_emxutil.h"
#include "runADMM_types.h"
#include "sum.h"
#include <math.h>

/* Function Declarations */
static void o_binary_expand_op(emxArray_real_T *in1, const emxArray_real_T *in2,
                               const emxArray_real_T *in4);

static void p_binary_expand_op(emxArray_real_T *in1, const emxArray_real_T *in2,
                               const emxArray_real_T *in3);

/* Function Definitions */
static void o_binary_expand_op(emxArray_real_T *in1, const emxArray_real_T *in2,
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
  b_sum(b_in2, in1);
  emxFree_real_T(&b_in2);
}

static void p_binary_expand_op(emxArray_real_T *in1, const emxArray_real_T *in2,
                               const emxArray_real_T *in3)
{
  emxArray_real_T *b_in2;
  const double *in2_data;
  const double *in3_data;
  double *b_in2_data;
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
  in3_data = in3->data;
  in2_data = in2->data;
  in1_data = in1->data;
  emxInit_real_T(&b_in2, 2);
  if (in1->size[0] == 1) {
    i = in3->size[0];
  } else {
    i = in1->size[0];
  }
  if (i == 1) {
    loop_ub = in2->size[0];
  } else {
    loop_ub = i;
  }
  i = b_in2->size[0] * b_in2->size[1];
  b_in2->size[0] = loop_ub;
  if (in1->size[1] == 1) {
    i1 = in3->size[1];
  } else {
    i1 = in1->size[1];
  }
  if (i1 == 1) {
    b_loop_ub = in2->size[1];
  } else {
    b_loop_ub = i1;
  }
  b_in2->size[1] = b_loop_ub;
  emxEnsureCapacity_real_T(b_in2, i);
  b_in2_data = b_in2->data;
  stride_0_0 = (in2->size[0] != 1);
  stride_0_1 = (in2->size[1] != 1);
  stride_1_0 = (in3->size[0] != 1);
  stride_1_1 = (in3->size[1] != 1);
  stride_2_0 = (in1->size[0] != 1);
  stride_2_1 = (in1->size[1] != 1);
  aux_0_1 = 0;
  aux_1_1 = 0;
  aux_2_1 = 0;
  for (i = 0; i < b_loop_ub; i++) {
    for (i1 = 0; i1 < loop_ub; i1++) {
      b_in2_data[i1 + b_in2->size[0] * i] =
          in2_data[i1 * stride_0_0 + in2->size[0] * aux_0_1] -
          in3_data[i1 * stride_1_0 + in3->size[0] * aux_1_1] *
              in1_data[i1 * stride_2_0 + in1->size[0] * aux_2_1];
    }
    aux_2_1 += stride_2_1;
    aux_1_1 += stride_1_1;
    aux_0_1 += stride_0_1;
  }
  i = in1->size[0] * in1->size[1];
  in1->size[0] = b_in2->size[0];
  in1->size[1] = b_in2->size[1];
  emxEnsureCapacity_real_T(in1, i);
  in1_data = in1->data;
  loop_ub = b_in2->size[1];
  for (i = 0; i < loop_ub; i++) {
    b_loop_ub = b_in2->size[0];
    for (i1 = 0; i1 < b_loop_ub; i1++) {
      in1_data[i1 + in1->size[0] * i] = b_in2_data[i1 + b_in2->size[0] * i];
    }
  }
  emxFree_real_T(&b_in2);
}

double eval_obj(double var_n, const emxArray_boolean_T *var_keep,
                const emxArray_real_T *var_E_est, const emxArray_real_T *var_E,
                const emxArray_real_T *var_W, const emxArray_real_T *var_lam,
                double *objLp)
{
  emxArray_real_T *b_residual;
  emxArray_real_T *e;
  emxArray_real_T *r;
  emxArray_real_T *r1;
  emxArray_real_T *residual;
  const double *var_E_data;
  const double *var_E_est_data;
  const double *var_W_data;
  const double *var_lam_data;
  double objL2;
  double scale;
  double *b_residual_data;
  double *e_data;
  double *residual_data;
  int b_j1;
  int i1;
  int kidx;
  int ma;
  int na;
  const boolean_T *var_keep_data;
  var_lam_data = var_lam->data;
  var_W_data = var_W->data;
  var_E_data = var_E->data;
  var_E_est_data = var_E_est->data;
  var_keep_data = var_keep->data;
  /*  Evaluates the objective function in terms of the weighted Frobenius L2 */
  /*  norm and the L1 norm */
  ma = var_lam->size[0];
  na = var_lam->size[1];
  emxInit_real_T(&e, 2);
  b_j1 = e->size[0] * e->size[1];
  e->size[0] = var_lam->size[0] << 1;
  e->size[1] = var_lam->size[1];
  emxEnsureCapacity_real_T(e, b_j1);
  e_data = e->data;
  kidx = -1;
  for (b_j1 = 0; b_j1 < na; b_j1++) {
    for (i1 = 0; i1 < ma; i1++) {
      e_data[kidx + 1] = var_lam_data[i1 + var_lam->size[0] * b_j1];
      e_data[kidx + 2] = var_lam_data[i1 + var_lam->size[0] * b_j1];
      kidx += 2;
    }
  }
  if (var_E->size[0] == 1) {
    kidx = e->size[0];
  } else {
    kidx = var_E->size[0];
  }
  if (var_E->size[1] == 1) {
    ma = e->size[1];
  } else {
    ma = var_E->size[1];
  }
  if ((var_E->size[0] == e->size[0]) && (var_E->size[1] == e->size[1]) &&
      (var_E_est->size[0] == kidx) && (var_E_est->size[1] == ma)) {
    kidx = var_E_est->size[0] * var_E_est->size[1];
    b_j1 = e->size[0] * e->size[1];
    e->size[0] = var_E_est->size[0];
    e->size[1] = var_E_est->size[1];
    emxEnsureCapacity_real_T(e, b_j1);
    e_data = e->data;
    for (b_j1 = 0; b_j1 < kidx; b_j1++) {
      e_data[b_j1] = var_E_est_data[b_j1] - var_E_data[b_j1] * e_data[b_j1];
    }
  } else {
    p_binary_expand_op(e, var_E_est, var_E);
    e_data = e->data;
  }
  ma = var_W->size[0];
  na = var_W->size[1];
  emxInit_real_T(&residual, 2);
  b_j1 = residual->size[0] * residual->size[1];
  residual->size[0] = var_W->size[0] << 1;
  residual->size[1] = var_W->size[1];
  emxEnsureCapacity_real_T(residual, b_j1);
  residual_data = residual->data;
  kidx = -1;
  for (b_j1 = 0; b_j1 < na; b_j1++) {
    for (i1 = 0; i1 < ma; i1++) {
      residual_data[kidx + 1] = var_W_data[i1 + var_W->size[0] * b_j1];
      residual_data[kidx + 2] = var_W_data[i1 + var_W->size[0] * b_j1];
      kidx += 2;
    }
  }
  emxInit_real_T(&r, 2);
  if ((residual->size[0] == e->size[0]) && (residual->size[1] == e->size[1])) {
    emxInit_real_T(&b_residual, 2);
    b_j1 = b_residual->size[0] * b_residual->size[1];
    b_residual->size[0] = residual->size[0];
    b_residual->size[1] = residual->size[1];
    emxEnsureCapacity_real_T(b_residual, b_j1);
    b_residual_data = b_residual->data;
    kidx = residual->size[0] * residual->size[1];
    for (b_j1 = 0; b_j1 < kidx; b_j1++) {
      scale = e_data[b_j1];
      b_residual_data[b_j1] = residual_data[b_j1] * (scale * scale);
    }
    b_sum(b_residual, r);
    emxFree_real_T(&b_residual);
  } else {
    o_binary_expand_op(r, residual, e);
  }
  objL2 = 0.5 * c_sum(r);
  emxFree_real_T(&r);
  b_j1 = (int)var_n;
  ma = residual->size[0] * residual->size[1];
  residual->size[0] = (int)var_n;
  residual->size[1] = (int)var_n;
  emxEnsureCapacity_real_T(residual, ma);
  residual_data = residual->data;
  kidx = (int)var_n * (int)var_n;
  for (ma = 0; ma < kidx; ma++) {
    residual_data[ma] = 0.0;
  }
  for (ma = 0; ma < b_j1; ma++) {
    for (na = 0; na < b_j1; na++) {
      if (var_keep_data[ma + var_keep->size[0] * na]) {
        double absxk;
        double t;
        double y;
        unsigned int absxk_tmp;
        /* function inds = s3(i) */
        /* function out  = s3(R,i) */
        /* function out  = s3(A,i,j) */
        /*  */
        /*  This function, when given an index i vector, converts it to the node
         */
        /*  indices (3*i-2,3*i-1,3*i) for each value of i. It is meant for
         * accessing */
        /*  subblocks of block matrices. */
        /*  */
        /*  Uses: */
        /*  A(s3(1),s3(2)) retrieves the subblock A(1,2). */
        /*  A(s3([1 7]),s3(2:3)) retrieves the corresponding subblocks */
        /*          stampConst = [3 3 3]; */
        /*  CHANGED */
        scale = 3.3121686421112381E-170;
        absxk_tmp = (unsigned int)ma << 1;
        absxk = fabs(
            e_data[((int)((double)absxk_tmp + 1.0) + e->size[0] * na) - 1]);
        if (absxk > 3.3121686421112381E-170) {
          y = 1.0;
          scale = absxk;
        } else {
          t = absxk / 3.3121686421112381E-170;
          y = t * t;
        }
        absxk = fabs(
            e_data[((int)((double)absxk_tmp + 2.0) + e->size[0] * na) - 1]);
        if (absxk > scale) {
          t = scale / absxk;
          y = y * t * t + 1.0;
          scale = absxk;
        } else {
          t = absxk / scale;
          y += t * t;
        }
        residual_data[ma + residual->size[0] * na] = scale * sqrt(y);
      }
    }
  }
  emxFree_real_T(&e);
  emxInit_real_T(&r1, 1);
  b_j1 = r1->size[0];
  r1->size[0] = kidx;
  emxEnsureCapacity_real_T(r1, b_j1);
  b_residual_data = r1->data;
  for (b_j1 = 0; b_j1 < kidx; b_j1++) {
    scale = residual_data[b_j1];
    b_residual_data[b_j1] = scale;
  }
  emxFree_real_T(&residual);
  *objLp = sum(r1);
  emxFree_real_T(&r1);
  return objL2;
}

/* End of code generation (eval_obj.c) */

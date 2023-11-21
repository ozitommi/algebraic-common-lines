/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * runADMM.c
 *
 * Code generation for function 'runADMM'
 *
 */

/* Include files */
#include "runADMM.h"
#include "ADMM.h"
#include "checkQuadrics.h"
#include "constructDetMats.h"
#include "constructScaleMats.h"
#include "estimate_W.h"
#include "eval_obj.h"
#include "mtimes.h"
#include "norm.h"
#include "rt_nonfinite.h"
#include "runADMM_data.h"
#include "runADMM_emxutil.h"
#include "runADMM_initialize.h"
#include "runADMM_internal_types.h"
#include "runADMM_types.h"
#include "sum.h"
#include "svd.h"
#include <math.h>

/* Function Declarations */
static void b_binary_expand_op(const emxArray_real_T *in1,
                               const emxArray_real_T *in2,
                               const emxArray_real_T *in3, emxArray_real_T *in4,
                               emxArray_real_T *in5, emxArray_real_T *in6);

static double binary_expand_op(const emxArray_real_T *in1);

static double c_binary_expand_op(const emxArray_real_T *in1,
                                 const struct0_T *in2);

/* Function Definitions */
static void b_binary_expand_op(const emxArray_real_T *in1,
                               const emxArray_real_T *in2,
                               const emxArray_real_T *in3, emxArray_real_T *in4,
                               emxArray_real_T *in5, emxArray_real_T *in6)
{
  emxArray_real_T *b_in1;
  const double *in1_data;
  const double *in2_data;
  const double *in3_data;
  double *b_in1_data;
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
  emxInit_real_T(&b_in1, 2);
  if (in3->size[0] == 1) {
    if (in2->size[0] == 1) {
      loop_ub = in1->size[0];
    } else {
      loop_ub = in2->size[0];
    }
  } else {
    loop_ub = in3->size[0];
  }
  i = b_in1->size[0] * b_in1->size[1];
  b_in1->size[0] = loop_ub;
  if (in3->size[1] == 1) {
    if (in2->size[1] == 1) {
      b_loop_ub = in1->size[1];
    } else {
      b_loop_ub = in2->size[1];
    }
  } else {
    b_loop_ub = in3->size[1];
  }
  b_in1->size[1] = b_loop_ub;
  emxEnsureCapacity_real_T(b_in1, i);
  b_in1_data = b_in1->data;
  stride_0_0 = (in1->size[0] != 1);
  stride_0_1 = (in1->size[1] != 1);
  stride_1_0 = (in2->size[0] != 1);
  stride_1_1 = (in2->size[1] != 1);
  stride_2_0 = (in3->size[0] != 1);
  stride_2_1 = (in3->size[1] != 1);
  aux_0_1 = 0;
  aux_1_1 = 0;
  aux_2_1 = 0;
  for (i = 0; i < b_loop_ub; i++) {
    for (i1 = 0; i1 < loop_ub; i1++) {
      b_in1_data[i1 + b_in1->size[0] * i] =
          (in1_data[i1 * stride_0_0 + in1->size[0] * aux_0_1] +
           in2_data[i1 * stride_1_0 + in2->size[0] * aux_1_1]) +
          in3_data[i1 * stride_2_0 + in3->size[0] * aux_2_1];
    }
    aux_2_1 += stride_2_1;
    aux_1_1 += stride_1_1;
    aux_0_1 += stride_0_1;
  }
  svd(b_in1, in4, in5, in6);
  emxFree_real_T(&b_in1);
}

static double binary_expand_op(const emxArray_real_T *in1)
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
          in1_data[i1 * stride_0_0_tmp + in1->size[0] * aux_0_1] -
          in1_data[aux_1_1 + in1->size[0] * (i1 * stride_0_1_tmp)];
    }
    aux_1_1 += stride_0_0_tmp;
    aux_0_1 += stride_0_1_tmp;
  }
  out1 = b_norm(b_in1);
  emxFree_real_T(&b_in1);
  return out1;
}

static double c_binary_expand_op(const emxArray_real_T *in1,
                                 const struct0_T *in2)
{
  emxArray_real_T *b_in1;
  emxArray_real_T *b_in2;
  emxArray_real_T *c_in2;
  const double *in1_data;
  double out1;
  double *b_in1_data;
  double *in2_data;
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
          in1_data[i1 * stride_0_0_tmp + in1->size[0] * aux_0_1] -
          in1_data[aux_1_1 + in1->size[0] * (i1 * stride_0_1_tmp)];
    }
    aux_1_1 += stride_0_0_tmp;
    aux_0_1 += stride_0_1_tmp;
  }
  loop_ub = in2->quad->size[0];
  emxInit_real_T(&b_in2, 1);
  i = b_in2->size[0];
  b_in2->size[0] = in2->quad->size[0];
  emxEnsureCapacity_real_T(b_in2, i);
  b_in1_data = b_in2->data;
  emxInit_real_T(&c_in2, 1);
  i = c_in2->size[0];
  c_in2->size[0] = in2->quad->size[0];
  emxEnsureCapacity_real_T(c_in2, i);
  in2_data = c_in2->data;
  for (i = 0; i < loop_ub; i++) {
    double d;
    d = in2->quad->data[i + in2->quad->size[0]];
    b_in1_data[i] = in2->quad->data[i] - d;
    in2_data[i] = d - in2->quad->data[i + in2->quad->size[0] * 2];
  }
  out1 = b_norm(b_in1) + (c_norm(b_in2) + c_norm(c_in2));
  emxFree_real_T(&c_in2);
  emxFree_real_T(&b_in2);
  emxFree_real_T(&b_in1);
  return out1;
}

void runADMM(struct0_T *var, emxArray_real_T *A_out, double *fval, double *vld,
             double *conv)
{
  emxArray_boolean_T *c_x;
  emxArray_boolean_T *x;
  emxArray_boolean_T *y;
  emxArray_real_T b_var;
  emxArray_real_T *D2_mu;
  emxArray_real_T *L;
  emxArray_real_T *M;
  emxArray_real_T *V;
  emxArray_real_T *b_M;
  emxArray_real_T *b_x;
  emxArray_real_T *g_var;
  emxArray_real_T *h_var;
  emxArray_real_T *i_var;
  emxArray_real_T *quad1;
  struct0_T d_var;
  struct0_T e_var;
  struct_T expl_temp;
  double IR_iter;
  double diffF;
  double iter_irls;
  double n;
  double objlp;
  double objlp_tol;
  double *M_data;
  double *b_M_data;
  double *b_x_data;
  double *var_data;
  int a;
  int b_i;
  int c_var;
  int f_var;
  int i;
  int i2;
  int k;
  int nx;
  boolean_T c_y[2];
  boolean_T b_y;
  boolean_T exitg1;
  boolean_T *x_data;
  boolean_T *y_data;
  if (!isInitialized_runADMM) {
    runADMM_initialize();
  }
  n = var->n;
  *vld = var->vld;
  /*  Run IRLS and ADMM */
  /*  Performs IRLS and ADMM/alternating descent */
  /*  L1 cost function */
  IR_iter = var->IR_iter;
  objlp_tol = var->objlp_tol;
  /*  Run ADMM once */
  nx = var->W->size[0] * var->W->size[1];
  b_var = *var->W;
  c_var = nx;
  b_var.size = &c_var;
  b_var.numDimensions = 1;
  var->tau = 0.5 * sum(&b_var);
  emxInitStruct_struct0_T(&d_var);
  emxCopyStruct_struct0_T(&d_var, var);
  e_var = d_var;
  ADMM(&e_var, var, &expl_temp);
  /*  run ADMM */
  var->objl2 =
      eval_obj(var->n, var->keep, var->E_est, var->E, var->lam, var->W, &objlp);
  /*  evaluate cost function */
  diffF = fabs(objlp - var->objlp) / fmax(objlp, var->objlp);
  var->objlp = objlp;
  estimate_W(var->n, var->keep, var->E_est, var->E, var->lam, var->W);
  /*  estimate weights for IRLS */
  /*  fprintf('IRLS iter %d IRLS obj L2 %.3e obj Lp(p=1)
   * %.3e\n',iter_irls,objl2,objlp); */
  iter_irls = 2.0;
  /*  Repeat */
  while ((iter_irls < IR_iter + 1.0) && (diffF > 1.0E-6) &&
         (objlp > objlp_tol)) {
    nx = var->W->size[0] * var->W->size[1];
    b_var = *var->W;
    f_var = nx;
    b_var.size = &f_var;
    b_var.numDimensions = 1;
    var->tau = 0.5 * sum(&b_var);
    emxCopyStruct_struct0_T(&d_var, var);
    e_var = d_var;
    ADMM(&e_var, var, &expl_temp);
    /*  run ADMM */
    var->objl2 = eval_obj(var->n, var->keep, var->E_est, var->E, var->lam,
                          var->W, &objlp);
    /*  evaluate cost function */
    diffF = fabs(objlp - var->objlp) / fmax(objlp, var->objlp);
    var->objlp = objlp;
    estimate_W(var->n, var->keep, var->E_est, var->E, var->lam, var->W);
    /*  estimate weights for IRLS */
    /*  fprintf('IRLS iter %d IRLS obj L2 %.3e obj Lp(p=1)
     * %.3e\n',iter_irls,objl2,objlp); */
    iter_irls++;
  }
  emxFreeStruct_struct0_T(&d_var);
  /*  Output */
  /*  Check if ADMM converged */
  nx = var->lam->size[0] * var->lam->size[1];
  emxInit_real_T(&M, 2);
  i = M->size[0] * M->size[1];
  M->size[0] = var->lam->size[0];
  M->size[1] = var->lam->size[1];
  emxEnsureCapacity_real_T(M, i);
  M_data = M->data;
  for (k = 0; k < nx; k++) {
    M_data[k] = fabs(var->lam->data[k]);
  }
  emxInit_boolean_T(&x, 2);
  i = x->size[0] * x->size[1];
  x->size[0] = M->size[0];
  x->size[1] = M->size[1];
  emxEnsureCapacity_boolean_T(x, i);
  x_data = x->data;
  i2 = M->size[0] * M->size[1];
  for (i = 0; i < i2; i++) {
    x_data[i] = (M_data[i] > var->conv_tol);
  }
  emxInit_boolean_T(&y, 2);
  i = y->size[0] * y->size[1];
  y->size[0] = 1;
  y->size[1] = x->size[1];
  emxEnsureCapacity_boolean_T(y, i);
  y_data = y->data;
  i2 = x->size[1];
  for (i = 0; i < i2; i++) {
    y_data[i] = false;
  }
  nx = x->size[1];
  i2 = 0;
  for (b_i = 0; b_i < nx; b_i++) {
    a = i2 + x->size[0];
    k = i2;
    i2 += x->size[0];
    exitg1 = false;
    while ((!exitg1) && (k + 1 <= a)) {
      if (x_data[k]) {
        y_data[b_i] = true;
        exitg1 = true;
      } else {
        k++;
      }
    }
  }
  emxFree_boolean_T(&x);
  b_y = false;
  k = 1;
  exitg1 = false;
  while ((!exitg1) && (k <= y->size[1])) {
    if (y_data[k - 1]) {
      b_y = true;
      exitg1 = true;
    } else {
      k++;
    }
  }
  emxFree_boolean_T(&y);
  b_i = !b_y;
  /*  Fix norm equations with Sinkhorn */
  diffF = rtInf;
  objlp = rtInf;
  iter_irls = 1.0;
  emxInit_real_T(&quad1, 2);
  emxInit_real_T(&D2_mu, 2);
  emxInit_real_T(&V, 2);
  emxInit_real_T(&b_x, 2);
  emxInit_real_T(&L, 2);
  emxInit_real_T(&b_M, 2);
  emxInit_real_T(&g_var, 1);
  emxInit_real_T(&h_var, 1);
  emxInit_real_T(&i_var, 2);
  while ((iter_irls < var->MAX_SH) && (diffF > 1.0E-8)) {
    i = M->size[0] * M->size[1];
    M->size[0] = var->E->size[0];
    M->size[1] = var->E->size[1];
    emxEnsureCapacity_real_T(M, i);
    M_data = M->data;
    i2 = var->E->size[0] * var->E->size[1];
    for (i = 0; i < i2; i++) {
      IR_iter = var->E->data[i];
      M_data[i] = IR_iter * IR_iter;
    }
    i = (int)(n * n);
    if (i == 0) {
      k = b_x->size[0] * b_x->size[1];
      b_x->size[0] = 1;
      b_x->size[1] = 0;
      emxEnsureCapacity_real_T(b_x, k);
    } else {
      k = b_x->size[0] * b_x->size[1];
      b_x->size[0] = 1;
      b_x->size[1] = i;
      emxEnsureCapacity_real_T(b_x, k);
      b_x_data = b_x->data;
      for (i2 = 0; i2 < i; i2++) {
        nx = i2 << 1;
        b_x_data[i2] = M_data[nx];
        b_x_data[i2] += M_data[nx + 1];
      }
    }
    k = b_x->size[0] * b_x->size[1];
    b_x->size[0] = (int)n;
    b_x->size[1] = (int)n;
    emxEnsureCapacity_real_T(b_x, k);
    b_x_data = b_x->data;
    a = (int)n * (int)n;
    for (k = 0; k < a; k++) {
      b_x_data[k] = sqrt(b_x_data[k]);
    }
    constructScaleMats(b_x, b_M, M);
    b_M_data = b_M->data;
    k = i_var->size[0] * i_var->size[1];
    i_var->size[0] = var->E->size[0];
    i_var->size[1] = var->E->size[1];
    emxEnsureCapacity_real_T(i_var, k);
    var_data = i_var->data;
    i2 = var->E->size[0] * var->E->size[1] - 1;
    for (k = 0; k <= i2; k++) {
      var_data[k] = var->E->data[k];
    }
    checkQuadrics(i_var, quad1, var->quad);
    constructDetMats(var->n, var->missing_mu, var->missing_tau1,
                     var->missing_tau2, var->quad, i_var, D2_mu, M, b_x);
    M_data = D2_mu->data;
    var_data = i_var->data;
    if (b_M->size[0] == 1) {
      nx = i_var->size[0];
    } else {
      nx = b_M->size[0];
    }
    if (b_M->size[1] == 1) {
      k = i_var->size[1];
    } else {
      k = b_M->size[1];
    }
    if ((b_M->size[0] == i_var->size[0]) && (b_M->size[1] == i_var->size[1]) &&
        (nx == D2_mu->size[0]) && (k == D2_mu->size[1])) {
      k = L->size[0] * L->size[1];
      L->size[0] = b_M->size[0];
      L->size[1] = b_M->size[1];
      emxEnsureCapacity_real_T(L, k);
      b_x_data = L->data;
      i2 = b_M->size[0] * b_M->size[1];
      for (k = 0; k < i2; k++) {
        b_x_data[k] = (b_M_data[k] + var_data[k]) + M_data[k];
      }
      svd(L, M, b_x, V);
      M_data = V->data;
    } else {
      b_binary_expand_op(b_M, i_var, D2_mu, M, b_x, V);
      M_data = V->data;
    }
    i2 = V->size[0];
    k = g_var->size[0];
    g_var->size[0] = V->size[0] << 1;
    emxEnsureCapacity_real_T(g_var, k);
    var_data = g_var->data;
    nx = -1;
    for (k = 0; k < i2; k++) {
      IR_iter = M_data[k + V->size[0] * (V->size[1] - 1)];
      var_data[nx + 1] = IR_iter;
      var_data[nx + 2] = IR_iter;
      nx += 2;
    }
    nx = g_var->size[0];
    k = b_x->size[0] * b_x->size[1];
    b_x->size[0] = g_var->size[0];
    b_x->size[1] = g_var->size[0];
    emxEnsureCapacity_real_T(b_x, k);
    b_x_data = b_x->data;
    i2 = g_var->size[0] * g_var->size[0];
    for (k = 0; k < i2; k++) {
      b_x_data[k] = 0.0;
    }
    for (i2 = 0; i2 < nx; i2++) {
      b_x_data[i2 + b_x->size[0] * i2] = var_data[i2];
    }
    mtimes(b_x, var->E, M);
    M_data = M->data;
    IR_iter = b_norm(var->E);
    k = var->E->size[0] * var->E->size[1];
    var->E->size[0] = M->size[0];
    var->E->size[1] = M->size[1];
    emxEnsureCapacity_real_T(var->E, k);
    objlp_tol = b_norm(M);
    i2 = M->size[0] * M->size[1];
    for (k = 0; k < i2; k++) {
      var->E->data[k] = IR_iter * (M_data[k] / objlp_tol);
    }
    k = M->size[0] * M->size[1];
    M->size[0] = var->E->size[0];
    M->size[1] = var->E->size[1];
    emxEnsureCapacity_real_T(M, k);
    M_data = M->data;
    i2 = var->E->size[0] * var->E->size[1];
    for (k = 0; k < i2; k++) {
      IR_iter = var->E->data[k];
      M_data[k] = IR_iter * IR_iter;
    }
    if (i == 0) {
      k = b_x->size[0] * b_x->size[1];
      b_x->size[0] = 1;
      b_x->size[1] = 0;
      emxEnsureCapacity_real_T(b_x, k);
    } else {
      k = b_x->size[0] * b_x->size[1];
      b_x->size[0] = 1;
      b_x->size[1] = i;
      emxEnsureCapacity_real_T(b_x, k);
      b_x_data = b_x->data;
      for (i2 = 0; i2 < i; i2++) {
        nx = i2 << 1;
        b_x_data[i2] = M_data[nx];
        b_x_data[i2] += M_data[nx + 1];
      }
    }
    k = b_x->size[0] * b_x->size[1];
    b_x->size[0] = (int)n;
    b_x->size[1] = (int)n;
    emxEnsureCapacity_real_T(b_x, k);
    b_x_data = b_x->data;
    for (k = 0; k < a; k++) {
      b_x_data[k] = sqrt(b_x_data[k]);
    }
    constructScaleMats(b_x, M, b_M);
    b_M_data = b_M->data;
    k = i_var->size[0] * i_var->size[1];
    i_var->size[0] = var->E->size[0];
    i_var->size[1] = var->E->size[1];
    emxEnsureCapacity_real_T(i_var, k);
    var_data = i_var->data;
    i2 = var->E->size[0] * var->E->size[1] - 1;
    for (k = 0; k <= i2; k++) {
      var_data[k] = var->E->data[k];
    }
    checkQuadrics(i_var, quad1, var->quad);
    constructDetMats(var->n, var->missing_mu, var->missing_tau1,
                     var->missing_tau2, var->quad, M, b_x, i_var, D2_mu);
    M_data = D2_mu->data;
    var_data = i_var->data;
    if (b_M->size[0] == 1) {
      nx = i_var->size[0];
    } else {
      nx = b_M->size[0];
    }
    if (b_M->size[1] == 1) {
      k = i_var->size[1];
    } else {
      k = b_M->size[1];
    }
    if ((b_M->size[0] == i_var->size[0]) && (b_M->size[1] == i_var->size[1]) &&
        (nx == D2_mu->size[0]) && (k == D2_mu->size[1])) {
      k = L->size[0] * L->size[1];
      L->size[0] = b_M->size[0];
      L->size[1] = b_M->size[1];
      emxEnsureCapacity_real_T(L, k);
      b_x_data = L->data;
      i2 = b_M->size[0] * b_M->size[1];
      for (k = 0; k < i2; k++) {
        b_x_data[k] = (b_M_data[k] + var_data[k]) + M_data[k];
      }
      svd(L, M, b_x, V);
      M_data = V->data;
    } else {
      b_binary_expand_op(b_M, i_var, D2_mu, M, b_x, V);
      M_data = V->data;
    }
    nx = V->size[0];
    k = b_x->size[0] * b_x->size[1];
    b_x->size[0] = V->size[0];
    b_x->size[1] = V->size[0];
    emxEnsureCapacity_real_T(b_x, k);
    b_x_data = b_x->data;
    i2 = V->size[0] * V->size[0];
    for (k = 0; k < i2; k++) {
      b_x_data[k] = 0.0;
    }
    for (i2 = 0; i2 < nx; i2++) {
      b_x_data[i2 + b_x->size[0] * i2] =
          M_data[i2 + V->size[0] * (V->size[1] - 1)];
    }
    mtimes(var->E, b_x, M);
    M_data = M->data;
    IR_iter = b_norm(var->E);
    k = var->E->size[0] * var->E->size[1];
    var->E->size[0] = M->size[0];
    var->E->size[1] = M->size[1];
    emxEnsureCapacity_real_T(var->E, k);
    objlp_tol = b_norm(M);
    i2 = M->size[0] * M->size[1];
    for (k = 0; k < i2; k++) {
      var->E->data[k] = IR_iter * (M_data[k] / objlp_tol);
    }
    k = M->size[0] * M->size[1];
    M->size[0] = var->E->size[0];
    M->size[1] = var->E->size[1];
    emxEnsureCapacity_real_T(M, k);
    M_data = M->data;
    i2 = var->E->size[0] * var->E->size[1];
    for (k = 0; k < i2; k++) {
      IR_iter = var->E->data[k];
      M_data[k] = IR_iter * IR_iter;
    }
    if (i == 0) {
      i = b_x->size[0] * b_x->size[1];
      b_x->size[0] = 1;
      b_x->size[1] = 0;
      emxEnsureCapacity_real_T(b_x, i);
      b_x_data = b_x->data;
    } else {
      k = b_x->size[0] * b_x->size[1];
      b_x->size[0] = 1;
      b_x->size[1] = i;
      emxEnsureCapacity_real_T(b_x, k);
      b_x_data = b_x->data;
      for (i2 = 0; i2 < i; i2++) {
        nx = i2 << 1;
        b_x_data[i2] = M_data[nx];
        b_x_data[i2] += M_data[nx + 1];
      }
    }
    i = M->size[0] * M->size[1];
    M->size[0] = (int)n;
    M->size[1] = (int)n;
    emxEnsureCapacity_real_T(M, i);
    M_data = M->data;
    for (i = 0; i < a; i++) {
      M_data[i] = b_x_data[i];
    }
    for (k = 0; k < a; k++) {
      M_data[k] = sqrt(M_data[k]);
    }
    if (M->size[0] == M->size[1]) {
      i = b_M->size[0] * b_M->size[1];
      b_M->size[0] = M->size[0];
      b_M->size[1] = M->size[1];
      emxEnsureCapacity_real_T(b_M, i);
      b_M_data = b_M->data;
      i2 = M->size[1];
      for (i = 0; i < i2; i++) {
        nx = M->size[0];
        for (k = 0; k < nx; k++) {
          b_M_data[k + b_M->size[0] * i] =
              M_data[k + M->size[0] * i] - M_data[i + M->size[0] * k];
        }
      }
      IR_iter = b_norm(b_M);
    } else {
      IR_iter = binary_expand_op(M);
    }
    i = i_var->size[0] * i_var->size[1];
    i_var->size[0] = var->E->size[0];
    i_var->size[1] = var->E->size[1];
    emxEnsureCapacity_real_T(i_var, i);
    var_data = i_var->data;
    i2 = var->E->size[0] * var->E->size[1] - 1;
    for (i = 0; i <= i2; i++) {
      var_data[i] = var->E->data[i];
    }
    checkQuadrics(i_var, quad1, var->quad);
    i2 = var->quad->size[0];
    i = g_var->size[0];
    g_var->size[0] = var->quad->size[0];
    emxEnsureCapacity_real_T(g_var, i);
    var_data = g_var->data;
    i = h_var->size[0];
    h_var->size[0] = var->quad->size[0];
    emxEnsureCapacity_real_T(h_var, i);
    M_data = h_var->data;
    for (i = 0; i < i2; i++) {
      objlp_tol = var->quad->data[i + var->quad->size[0]];
      var_data[i] = var->quad->data[i] - objlp_tol;
      M_data[i] = objlp_tol - var->quad->data[i + var->quad->size[0] * 2];
    }
    /*  fprintf('error after rows %.9e\n',norm_err + det_err); */
    IR_iter += c_norm(g_var) + c_norm(h_var);
    diffF = fabs(objlp - IR_iter);
    objlp = IR_iter;
    iter_irls++;
  }
  emxFree_real_T(&L);
  emxFree_real_T(&V);
  emxFree_real_T(&D2_mu);
  /*  Output */
  i = A_out->size[0] * A_out->size[1];
  A_out->size[0] = var->E->size[0];
  A_out->size[1] = var->E->size[1];
  emxEnsureCapacity_real_T(A_out, i);
  M_data = A_out->data;
  nx = var->E->size[0] * var->E->size[1];
  for (i = 0; i < nx; i++) {
    M_data[i] = var->E->data[i];
  }
  i = M->size[0] * M->size[1];
  M->size[0] = var->E->size[0];
  M->size[1] = var->E->size[1];
  emxEnsureCapacity_real_T(M, i);
  M_data = M->data;
  for (i = 0; i < nx; i++) {
    IR_iter = var->E->data[i];
    M_data[i] = IR_iter * IR_iter;
  }
  i = (int)(n * n);
  if (i == 0) {
    i = b_x->size[0] * b_x->size[1];
    b_x->size[0] = 1;
    b_x->size[1] = 0;
    emxEnsureCapacity_real_T(b_x, i);
    b_x_data = b_x->data;
  } else {
    k = b_x->size[0] * b_x->size[1];
    b_x->size[0] = 1;
    b_x->size[1] = i;
    emxEnsureCapacity_real_T(b_x, k);
    b_x_data = b_x->data;
    for (i2 = 0; i2 < i; i2++) {
      nx = i2 << 1;
      b_x_data[i2] = M_data[nx];
      b_x_data[i2] += M_data[nx + 1];
    }
  }
  i = M->size[0] * M->size[1];
  M->size[0] = (int)n;
  M->size[1] = (int)n;
  emxEnsureCapacity_real_T(M, i);
  M_data = M->data;
  nx = (int)n * (int)n;
  for (i = 0; i < nx; i++) {
    M_data[i] = b_x_data[i];
  }
  emxFree_real_T(&b_x);
  for (k = 0; k < nx; k++) {
    M_data[k] = sqrt(M_data[k]);
  }
  i = i_var->size[0] * i_var->size[1];
  i_var->size[0] = var->E->size[0];
  i_var->size[1] = var->E->size[1];
  emxEnsureCapacity_real_T(i_var, i);
  var_data = i_var->data;
  i2 = var->E->size[0] * var->E->size[1] - 1;
  for (i = 0; i <= i2; i++) {
    var_data[i] = var->E->data[i];
  }
  checkQuadrics(i_var, quad1, var->quad);
  b_x_data = quad1->data;
  emxFree_real_T(&i_var);
  if (M->size[0] == M->size[1]) {
    i = b_M->size[0] * b_M->size[1];
    b_M->size[0] = M->size[0];
    b_M->size[1] = M->size[1];
    emxEnsureCapacity_real_T(b_M, i);
    b_M_data = b_M->data;
    i2 = M->size[1];
    for (i = 0; i < i2; i++) {
      nx = M->size[0];
      for (k = 0; k < nx; k++) {
        b_M_data[k + b_M->size[0] * i] =
            M_data[k + M->size[0] * i] - M_data[i + M->size[0] * k];
      }
    }
    i2 = var->quad->size[0];
    i = g_var->size[0];
    g_var->size[0] = var->quad->size[0];
    emxEnsureCapacity_real_T(g_var, i);
    var_data = g_var->data;
    i = h_var->size[0];
    h_var->size[0] = var->quad->size[0];
    emxEnsureCapacity_real_T(h_var, i);
    M_data = h_var->data;
    for (i = 0; i < i2; i++) {
      objlp_tol = var->quad->data[i + var->quad->size[0]];
      var_data[i] = var->quad->data[i] - objlp_tol;
      M_data[i] = objlp_tol - var->quad->data[i + var->quad->size[0] * 2];
    }
    *fval = b_norm(b_M) + (c_norm(g_var) + c_norm(h_var));
  } else {
    *fval = c_binary_expand_op(M, var);
  }
  emxFree_real_T(&h_var);
  emxFree_real_T(&g_var);
  emxFree_real_T(&b_M);
  emxFree_real_T(&M);
  emxInit_boolean_T(&c_x, 2);
  i = c_x->size[0] * c_x->size[1];
  c_x->size[0] = quad1->size[0];
  c_x->size[1] = 2;
  emxEnsureCapacity_boolean_T(c_x, i);
  x_data = c_x->data;
  i2 = quad1->size[0] << 1;
  for (i = 0; i < i2; i++) {
    x_data[i] = (b_x_data[i] < var->norm_tol);
  }
  emxFree_real_T(&quad1);
  c_y[0] = false;
  c_y[1] = false;
  a = c_x->size[0];
  k = 0;
  exitg1 = false;
  while ((!exitg1) && (k + 1 <= a)) {
    if (x_data[k]) {
      c_y[0] = true;
      exitg1 = true;
    } else {
      k++;
    }
  }
  a = c_x->size[0] + c_x->size[0];
  k = c_x->size[0];
  exitg1 = false;
  while ((!exitg1) && (k + 1 <= a)) {
    if (x_data[k]) {
      c_y[1] = true;
      exitg1 = true;
    } else {
      k++;
    }
  }
  emxFree_boolean_T(&c_x);
  b_y = false;
  k = 0;
  exitg1 = false;
  while ((!exitg1) && (k < 2)) {
    if (c_y[k]) {
      b_y = true;
      exitg1 = true;
    } else {
      k++;
    }
  }
  if (b_y) {
    b_i = 0;
  }
  *conv = b_i;
}

/* End of code generation (runADMM.c) */

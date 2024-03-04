/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * estimate_W.c
 *
 * Code generation for function 'estimate_W'
 *
 */

/* Include files */
#include "estimate_W.h"
#include "norm.h"
#include "rt_nonfinite.h"
#include "runADMM_emxutil.h"
#include "runADMM_types.h"
#include <math.h>

/* Function Definitions */
void estimate_W(double var_n, const emxArray_boolean_T *var_keep,
                const emxArray_real_T *var_E_est, const emxArray_real_T *var_E,
                const emxArray_real_T *var_lam, emxArray_real_T *W)
{
  emxArray_int8_T *r;
  const double *var_E_data;
  const double *var_E_est_data;
  const double *var_lam_data;
  double b;
  double *W_data;
  int b_i;
  int i;
  int loop_ub_tmp;
  int m;
  signed char *r1;
  const boolean_T *var_keep_data;
  var_lam_data = var_lam->data;
  var_E_data = var_E->data;
  var_E_est_data = var_E_est->data;
  var_keep_data = var_keep->data;
  /*  Updates the weights of the IRLS method */
  i = (int)var_n;
  m = W->size[0] * W->size[1];
  W->size[0] = (int)var_n;
  W->size[1] = (int)var_n;
  emxEnsureCapacity_real_T(W, m);
  W_data = W->data;
  loop_ub_tmp = (int)var_n * (int)var_n;
  for (m = 0; m < loop_ub_tmp; m++) {
    W_data[m] = 0.0;
  }
  for (b_i = 0; b_i < i; b_i++) {
    for (m = 0; m < i; m++) {
      if (var_keep_data[b_i + var_keep->size[0] * m]) {
        double absxk;
        double scale;
        double t;
        double y;
        unsigned int absxk_tmp_tmp;
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
        b = var_lam_data[b_i + var_lam->size[0] * m];
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
        absxk_tmp_tmp = (unsigned int)b_i << 1;
        absxk = fabs(var_E_est_data[((int)((double)absxk_tmp_tmp + 1.0) +
                                     var_E_est->size[0] * m) -
                                    1] -
                     var_E_data[((int)((double)absxk_tmp_tmp + 1.0) +
                                 var_E->size[0] * m) -
                                1] *
                         b);
        if (absxk > 3.3121686421112381E-170) {
          y = 1.0;
          scale = absxk;
        } else {
          t = absxk / 3.3121686421112381E-170;
          y = t * t;
        }
        absxk = fabs(var_E_est_data[((int)((double)absxk_tmp_tmp + 2.0) +
                                     var_E_est->size[0] * m) -
                                    1] -
                     var_E_data[((int)((double)absxk_tmp_tmp + 2.0) +
                                 var_E->size[0] * m) -
                                1] *
                         b);
        if (absxk > scale) {
          t = scale / absxk;
          y = y * t * t + 1.0;
          scale = absxk;
        } else {
          t = absxk / scale;
          y += t * t;
        }
        y = scale * sqrt(y);
        W_data[b_i + W->size[0] * m] = 1.0 / fmax(0.001, y);
      }
    }
  }
  m = var_keep->size[0] * var_keep->size[1] - 1;
  for (b_i = 0; b_i <= m; b_i++) {
    if (!var_keep_data[b_i]) {
      W_data[b_i] = 0.0;
    }
  }
  m = W->size[0];
  emxInit_int8_T(&r);
  i = r->size[0] * r->size[1];
  r->size[0] = W->size[0];
  r->size[1] = W->size[0];
  emxEnsureCapacity_int8_T(r, i);
  r1 = r->data;
  for (i = 0; i < loop_ub_tmp; i++) {
    r1[i] = 0;
  }
  if (W->size[0] > 0) {
    for (b_i = 0; b_i < m; b_i++) {
      r1[b_i + r->size[0] * b_i] = 1;
    }
  }
  m = loop_ub_tmp - 1;
  for (b_i = 0; b_i <= m; b_i++) {
    if (r1[b_i] != 0) {
      W_data[b_i] = 0.0;
    }
  }
  emxFree_int8_T(&r);
  b = b_norm(W);
  for (i = 0; i < loop_ub_tmp; i++) {
    W_data[i] /= b;
  }
}

/* End of code generation (estimate_W.c) */

/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * div.c
 *
 * Code generation for function 'div'
 *
 */

/* Include files */
#include "div.h"
#include "rt_nonfinite.h"
#include "runADMM_emxutil.h"
#include "runADMM_types.h"

/* Function Definitions */
void e_binary_expand_op(struct0_T *in1, const emxArray_real_T *in2,
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
  in3_data = in3->data;
  in2_data = in2->data;
  if (in3->size[0] == 1) {
    loop_ub = in2->size[0];
  } else {
    loop_ub = in3->size[0];
  }
  i = in1->lam->size[0] * in1->lam->size[1];
  in1->lam->size[0] = loop_ub;
  emxEnsureCapacity_real_T(in1->lam, i);
  if (in3->size[1] == 1) {
    b_loop_ub = in2->size[1];
  } else {
    b_loop_ub = in3->size[1];
  }
  i = in1->lam->size[0] * in1->lam->size[1];
  in1->lam->size[1] = b_loop_ub;
  emxEnsureCapacity_real_T(in1->lam, i);
  stride_0_0 = (in2->size[0] != 1);
  stride_0_1 = (in2->size[1] != 1);
  stride_1_0 = (in3->size[0] != 1);
  stride_1_1 = (in3->size[1] != 1);
  aux_0_1 = 0;
  aux_1_1 = 0;
  for (i = 0; i < b_loop_ub; i++) {
    for (i1 = 0; i1 < loop_ub; i1++) {
      in1->lam->data[i1 + in1->lam->size[0] * i] =
          in2_data[i1 * stride_0_0 + in2->size[0] * aux_0_1] /
          in3_data[i1 * stride_1_0 + in3->size[0] * aux_1_1];
    }
    aux_1_1 += stride_1_1;
    aux_0_1 += stride_0_1;
  }
}

void g_binary_expand_op(struct0_T *in1, const emxArray_real_T *in2,
                        const emxArray_real_T *in3)
{
  emxArray_real_T *b_in1;
  const double *in2_data;
  const double *in3_data;
  double *in1_data;
  int aux_0_1;
  int aux_1_1;
  int aux_2_1;
  int aux_3_1;
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
  int stride_3_0;
  int stride_3_1;
  in3_data = in3->data;
  in2_data = in2->data;
  emxInit_real_T(&b_in1, 2);
  if (in3->size[0] == 1) {
    if (in2->size[0] == 1) {
      if (in1->E_est->size[0] == 1) {
        loop_ub = in1->X->size[0];
      } else {
        loop_ub = in1->E_est->size[0];
      }
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
      if (in1->E_est->size[1] == 1) {
        b_loop_ub = in1->X->size[1];
      } else {
        b_loop_ub = in1->E_est->size[1];
      }
    } else {
      b_loop_ub = in2->size[1];
    }
  } else {
    b_loop_ub = in3->size[1];
  }
  b_in1->size[1] = b_loop_ub;
  emxEnsureCapacity_real_T(b_in1, i);
  in1_data = b_in1->data;
  stride_0_0 = (in1->X->size[0] != 1);
  stride_0_1 = (in1->X->size[1] != 1);
  stride_1_0 = (in1->E_est->size[0] != 1);
  stride_1_1 = (in1->E_est->size[1] != 1);
  stride_2_0 = (in2->size[0] != 1);
  stride_2_1 = (in2->size[1] != 1);
  stride_3_0 = (in3->size[0] != 1);
  stride_3_1 = (in3->size[1] != 1);
  aux_0_1 = 0;
  aux_1_1 = 0;
  aux_2_1 = 0;
  aux_3_1 = 0;
  for (i = 0; i < b_loop_ub; i++) {
    for (i1 = 0; i1 < loop_ub; i1++) {
      in1_data[i1 + b_in1->size[0] * i] =
          (in1->X->data[i1 * stride_0_0 + in1->X->size[0] * aux_0_1] *
               in1->E_est
                   ->data[i1 * stride_1_0 + in1->E_est->size[0] * aux_1_1] +
           in1->tau * in2_data[i1 * stride_2_0 + in2->size[0] * aux_2_1]) /
          (in3_data[i1 * stride_3_0 + in3->size[0] * aux_3_1] + in1->tau);
    }
    aux_3_1 += stride_3_1;
    aux_2_1 += stride_2_1;
    aux_1_1 += stride_1_1;
    aux_0_1 += stride_0_1;
  }
  i = in1->X->size[0] * in1->X->size[1];
  in1->X->size[0] = b_in1->size[0];
  in1->X->size[1] = b_in1->size[1];
  emxEnsureCapacity_real_T(in1->X, i);
  loop_ub = b_in1->size[0] * b_in1->size[1];
  for (i = 0; i < loop_ub; i++) {
    in1->X->data[i] = in1_data[i];
  }
  emxFree_real_T(&b_in1);
}

/* End of code generation (div.c) */

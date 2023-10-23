/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * conv2AXPYValidCMP.c
 *
 * Code generation for function 'conv2AXPYValidCMP'
 *
 */

/* Include files */
#include "conv2AXPYValidCMP.h"
#include "rt_nonfinite.h"
#include "runADMM_emxutil.h"
#include "runADMM_types.h"
#include "omp.h"

/* Function Definitions */
void conv2AXPYValidCMP(const emxArray_real_T *a, emxArray_real_T *c)
{
  emxArray_real_T *cj;
  const double *a_data;
  double *c_data;
  double *cj_data;
  int b_i;
  int i;
  int ib;
  int j;
  int mc;
  int ub_loop;
  a_data = a->data;
  if (a->size[0] < 1) {
    mc = 0;
  } else {
    mc = a->size[0] - 1;
  }
  if ((a->size[0] == 0) || (a->size[1] == 0) || (mc == 0)) {
    i = c->size[0] * c->size[1];
    c->size[0] = mc;
    c->size[1] = a->size[1];
    emxEnsureCapacity_real_T(c, i);
    c_data = c->data;
    ub_loop = mc * a->size[1];
    for (i = 0; i < ub_loop; i++) {
      c_data[i] = 0.0;
    }
  } else {
    i = c->size[0] * c->size[1];
    c->size[0] = mc;
    c->size[1] = a->size[1];
    emxEnsureCapacity_real_T(c, i);
    c_data = c->data;
    ub_loop = a->size[1] - 1;
#pragma omp parallel num_threads(omp_get_max_threads()) private(cj_data, cj,   \
                                                                b_i, ib)
    {
      emxInit_real_T(&cj, 1);
#pragma omp for nowait
      for (j = 0; j <= ub_loop; j++) {
        b_i = cj->size[0];
        cj->size[0] = mc;
        emxEnsureCapacity_real_T(cj, b_i);
        cj_data = cj->data;
        for (b_i = 0; b_i < mc; b_i++) {
          cj_data[b_i] = 0.0;
        }
        for (ib = 0; ib < 2; ib++) {
          for (b_i = 0; b_i < mc; b_i++) {
            cj_data[b_i] += a_data[(b_i + ib) + a->size[0] * j];
          }
        }
        ib = cj->size[0];
        for (b_i = 0; b_i < ib; b_i++) {
          c_data[b_i + c->size[0] * j] = cj_data[b_i];
        }
      }
      emxFree_real_T(&cj);
    }
  }
}

/* End of code generation (conv2AXPYValidCMP.c) */

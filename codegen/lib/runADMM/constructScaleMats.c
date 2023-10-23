/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * constructScaleMats.c
 *
 * Code generation for function 'constructScaleMats'
 *
 */

/* Include files */
#include "constructScaleMats.h"
#include "combineVectorElements.h"
#include "rt_nonfinite.h"
#include "runADMM_emxutil.h"
#include "runADMM_types.h"
#include "triu.h"

/* Function Declarations */
static void s_binary_expand_op(emxArray_real_T *in1,
                               const emxArray_real_T *in2);

/* Function Definitions */
static void s_binary_expand_op(emxArray_real_T *in1, const emxArray_real_T *in2)
{
  emxArray_real_T *b_in1;
  const double *in2_data;
  double *b_in1_data;
  double *in1_data;
  int aux_0_1;
  int aux_1_1;
  int aux_2_1;
  int b_loop_ub;
  int i;
  int i1;
  int loop_ub;
  int stride_0_0_tmp;
  int stride_0_1_tmp;
  int stride_2_0;
  int stride_2_1;
  in2_data = in2->data;
  in1_data = in1->data;
  emxInit_real_T(&b_in1, 2);
  if (in2->size[0] == 1) {
    if (in1->size[1] == 1) {
      loop_ub = in1->size[0];
    } else {
      loop_ub = in1->size[1];
    }
  } else {
    loop_ub = in2->size[0];
  }
  i = b_in1->size[0] * b_in1->size[1];
  b_in1->size[0] = loop_ub;
  if (in2->size[1] == 1) {
    if (in1->size[0] == 1) {
      b_loop_ub = in1->size[1];
    } else {
      b_loop_ub = in1->size[0];
    }
  } else {
    b_loop_ub = in2->size[1];
  }
  b_in1->size[1] = b_loop_ub;
  emxEnsureCapacity_real_T(b_in1, i);
  b_in1_data = b_in1->data;
  stride_0_0_tmp = (in1->size[0] != 1);
  stride_0_1_tmp = (in1->size[1] != 1);
  stride_2_0 = (in2->size[0] != 1);
  stride_2_1 = (in2->size[1] != 1);
  aux_0_1 = 0;
  aux_1_1 = 0;
  aux_2_1 = 0;
  for (i = 0; i < b_loop_ub; i++) {
    for (i1 = 0; i1 < loop_ub; i1++) {
      b_in1_data[i1 + b_in1->size[0] * i] =
          (in1_data[i1 * stride_0_0_tmp + in1->size[0] * aux_0_1] +
           in1_data[aux_1_1 + in1->size[0] * (i1 * stride_0_1_tmp)]) +
          in2_data[i1 * stride_2_0 + in2->size[0] * aux_2_1];
    }
    aux_2_1 += stride_2_1;
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

void constructScaleMats(const emxArray_real_T *M, emxArray_real_T *L,
                        emxArray_real_T *R)
{
  emxArray_real_T *M_trans;
  emxArray_real_T *bsum;
  emxArray_real_T *diagonalL;
  emxArray_real_T *diagonalR;
  emxArray_real_T *r;
  const double *M_data;
  double *L_data;
  double *M_trans_data;
  double *bsum_data;
  double *diagonalL_data;
  double *diagonalR_data;
  double *r1;
  int firstBlockLength;
  int hi;
  int ib;
  int k;
  int lastBlockLength;
  int nblocks;
  int vstride;
  int xj;
  int xoffset;
  M_data = M->data;
  /*  Construct the Jacobian matrices for the set of norm equations */
  emxInit_real_T(&M_trans, 2);
  ib = M_trans->size[0] * M_trans->size[1];
  M_trans->size[0] = M->size[0];
  M_trans->size[1] = M->size[1];
  emxEnsureCapacity_real_T(M_trans, ib);
  M_trans_data = M_trans->data;
  nblocks = M->size[0] * M->size[1];
  for (ib = 0; ib < nblocks; ib++) {
    double varargin_1;
    varargin_1 = M_data[ib];
    M_trans_data[ib] = varargin_1 * varargin_1;
  }
  emxInit_real_T(&diagonalL, 1);
  if ((M_trans->size[0] == 0) || (M_trans->size[1] == 0)) {
    ib = diagonalL->size[0];
    diagonalL->size[0] = M_trans->size[0];
    emxEnsureCapacity_real_T(diagonalL, ib);
    diagonalL_data = diagonalL->data;
    hi = M_trans->size[0];
    for (ib = 0; ib < hi; ib++) {
      diagonalL_data[ib] = 0.0;
    }
  } else {
    int bvstride;
    vstride = M_trans->size[0] - 1;
    bvstride = M_trans->size[0] << 10;
    ib = diagonalL->size[0];
    diagonalL->size[0] = M_trans->size[0];
    emxEnsureCapacity_real_T(diagonalL, ib);
    diagonalL_data = diagonalL->data;
    emxInit_real_T(&bsum, 1);
    ib = bsum->size[0];
    bsum->size[0] = M_trans->size[0];
    emxEnsureCapacity_real_T(bsum, ib);
    bsum_data = bsum->data;
    if (M_trans->size[1] <= 1024) {
      firstBlockLength = M_trans->size[1];
      lastBlockLength = 0;
      nblocks = 1;
    } else {
      firstBlockLength = 1024;
      nblocks = (int)((unsigned int)M_trans->size[1] >> 10);
      lastBlockLength = M_trans->size[1] - (nblocks << 10);
      if (lastBlockLength > 0) {
        nblocks++;
      } else {
        lastBlockLength = 1024;
      }
    }
    for (xj = 0; xj <= vstride; xj++) {
      diagonalL_data[xj] = M_trans_data[xj];
      bsum_data[xj] = 0.0;
    }
    for (k = 2; k <= firstBlockLength; k++) {
      xoffset = (k - 1) * (vstride + 1);
      for (xj = 0; xj <= vstride; xj++) {
        diagonalL_data[xj] += M_trans_data[xoffset + xj];
      }
    }
    for (ib = 2; ib <= nblocks; ib++) {
      firstBlockLength = (ib - 1) * bvstride;
      for (xj = 0; xj <= vstride; xj++) {
        bsum_data[xj] = M_trans_data[firstBlockLength + xj];
      }
      if (ib == nblocks) {
        hi = lastBlockLength;
      } else {
        hi = 1024;
      }
      for (k = 2; k <= hi; k++) {
        xoffset = firstBlockLength + (k - 1) * (vstride + 1);
        for (xj = 0; xj <= vstride; xj++) {
          bsum_data[xj] += M_trans_data[xoffset + xj];
        }
      }
      for (xj = 0; xj <= vstride; xj++) {
        diagonalL_data[xj] += bsum_data[xj];
      }
    }
    emxFree_real_T(&bsum);
  }
  emxInit_real_T(&diagonalR, 2);
  combineVectorElements(M_trans, diagonalR);
  diagonalR_data = diagonalR->data;
  ib = M_trans->size[0] * M_trans->size[1];
  M_trans->size[0] = M->size[1];
  M_trans->size[1] = M->size[0];
  emxEnsureCapacity_real_T(M_trans, ib);
  M_trans_data = M_trans->data;
  hi = M->size[0];
  for (ib = 0; ib < hi; ib++) {
    firstBlockLength = M->size[1];
    for (vstride = 0; vstride < firstBlockLength; vstride++) {
      M_trans_data[vstride + M_trans->size[0] * ib] =
          M_data[ib + M->size[0] * vstride];
    }
  }
  emxInit_real_T(&r, 2);
  ib = r->size[0] * r->size[1];
  r->size[0] = M->size[0];
  r->size[1] = M->size[0];
  emxEnsureCapacity_real_T(r, ib);
  r1 = r->data;
  nblocks = M->size[0] * M->size[0];
  for (ib = 0; ib < nblocks; ib++) {
    r1[ib] = 1.0;
  }
  triu(r);
  r1 = r->data;
  ib = L->size[0] * L->size[1];
  L->size[0] = M->size[0];
  L->size[1] = M->size[0];
  emxEnsureCapacity_real_T(L, ib);
  L_data = L->data;
  for (ib = 0; ib < nblocks; ib++) {
    L_data[ib] = 1.0;
  }
  triu(L);
  L_data = L->data;
  firstBlockLength = r->size[0] * r->size[1] - 1;
  for (hi = 0; hi <= firstBlockLength; hi++) {
    if (r1[hi] != 0.0) {
      L_data[hi] = -M_data[hi] * M_trans_data[hi];
    }
  }
  ib = R->size[0] * R->size[1];
  R->size[0] = L->size[0];
  R->size[1] = L->size[1];
  emxEnsureCapacity_real_T(R, ib);
  bsum_data = R->data;
  nblocks = L->size[0] * L->size[1];
  for (ib = 0; ib < nblocks; ib++) {
    bsum_data[ib] = L_data[ib];
  }
  firstBlockLength = diagonalL->size[0];
  ib = r->size[0] * r->size[1];
  r->size[0] = diagonalL->size[0];
  r->size[1] = diagonalL->size[0];
  emxEnsureCapacity_real_T(r, ib);
  r1 = r->data;
  hi = diagonalL->size[0] * diagonalL->size[0];
  for (ib = 0; ib < hi; ib++) {
    r1[ib] = 0.0;
  }
  for (hi = 0; hi < firstBlockLength; hi++) {
    r1[hi + r->size[0] * hi] = diagonalL_data[hi];
  }
  emxFree_real_T(&diagonalL);
  if (L->size[0] == 1) {
    ib = L->size[1];
  } else {
    ib = L->size[0];
  }
  if (L->size[1] == 1) {
    vstride = L->size[0];
  } else {
    vstride = L->size[1];
  }
  if ((L->size[0] == L->size[1]) && (ib == r->size[0]) &&
      (vstride == r->size[1])) {
    xoffset = M_trans->size[0] * M_trans->size[1];
    M_trans->size[0] = L->size[0];
    M_trans->size[1] = L->size[1];
    emxEnsureCapacity_real_T(M_trans, xoffset);
    M_trans_data = M_trans->data;
    hi = L->size[1];
    for (xoffset = 0; xoffset < hi; xoffset++) {
      firstBlockLength = L->size[0];
      for (lastBlockLength = 0; lastBlockLength < firstBlockLength;
           lastBlockLength++) {
        M_trans_data[lastBlockLength + M_trans->size[0] * xoffset] =
            (L_data[lastBlockLength + L->size[0] * xoffset] +
             L_data[xoffset + L->size[0] * lastBlockLength]) +
            r1[lastBlockLength + r->size[0] * xoffset];
      }
    }
    xoffset = L->size[0] * L->size[1];
    L->size[0] = M_trans->size[0];
    L->size[1] = M_trans->size[1];
    emxEnsureCapacity_real_T(L, xoffset);
    L_data = L->data;
    for (xoffset = 0; xoffset < nblocks; xoffset++) {
      L_data[xoffset] = M_trans_data[xoffset];
    }
  } else {
    s_binary_expand_op(L, r);
  }
  firstBlockLength = diagonalR->size[1];
  xoffset = r->size[0] * r->size[1];
  r->size[0] = diagonalR->size[1];
  r->size[1] = diagonalR->size[1];
  emxEnsureCapacity_real_T(r, xoffset);
  r1 = r->data;
  hi = diagonalR->size[1] * diagonalR->size[1];
  for (xoffset = 0; xoffset < hi; xoffset++) {
    r1[xoffset] = 0.0;
  }
  for (hi = 0; hi < firstBlockLength; hi++) {
    r1[hi + r->size[0] * hi] = diagonalR_data[hi];
  }
  emxFree_real_T(&diagonalR);
  if ((R->size[0] == R->size[1]) && (ib == r->size[0]) &&
      (vstride == r->size[1])) {
    ib = M_trans->size[0] * M_trans->size[1];
    M_trans->size[0] = R->size[0];
    M_trans->size[1] = R->size[1];
    emxEnsureCapacity_real_T(M_trans, ib);
    M_trans_data = M_trans->data;
    hi = R->size[1];
    for (ib = 0; ib < hi; ib++) {
      firstBlockLength = R->size[0];
      for (vstride = 0; vstride < firstBlockLength; vstride++) {
        M_trans_data[vstride + M_trans->size[0] * ib] =
            (bsum_data[vstride + R->size[0] * ib] +
             bsum_data[ib + R->size[0] * vstride]) +
            r1[vstride + r->size[0] * ib];
      }
    }
    ib = R->size[0] * R->size[1];
    R->size[0] = M_trans->size[0];
    R->size[1] = M_trans->size[1];
    emxEnsureCapacity_real_T(R, ib);
    bsum_data = R->data;
    for (ib = 0; ib < nblocks; ib++) {
      bsum_data[ib] = M_trans_data[ib];
    }
  } else {
    s_binary_expand_op(R, r);
  }
  emxFree_real_T(&r);
  emxFree_real_T(&M_trans);
}

/* End of code generation (constructScaleMats.c) */

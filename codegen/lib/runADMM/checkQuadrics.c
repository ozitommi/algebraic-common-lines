/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * checkQuadrics.c
 *
 * Code generation for function 'checkQuadrics'
 *
 */

/* Include files */
#include "checkQuadrics.h"
#include "kron.h"
#include "nchoosek.h"
#include "rt_nonfinite.h"
#include "runADMM_emxutil.h"
#include "runADMM_types.h"
#include "s3.h"
#include "squeeze.h"
#include <math.h>

/* Function Definitions */
void checkQuadrics(emxArray_real_T *A, emxArray_real_T *quad1,
                   emxArray_real_T *quad2)
{
  emxArray_int32_T *r6;
  emxArray_int8_T *K;
  emxArray_real_T *M;
  emxArray_real_T *X;
  emxArray_real_T *b_block1;
  emxArray_real_T *b_det3;
  emxArray_real_T *b_varargin_1;
  emxArray_real_T *block1;
  emxArray_real_T *det1;
  emxArray_real_T *det2;
  emxArray_real_T *det3;
  emxArray_real_T *ind_ij;
  emxArray_real_T *ind_ji;
  emxArray_real_T *r;
  emxArray_real_T *r1;
  emxArray_real_T *r3;
  emxArray_real_T *r5;
  emxArray_real_T *varargin_2;
  emxArray_real_T *y;
  double stampConst_data[4];
  double stampVar_data[4];
  double varargin_1;
  double *A_data;
  double *M_data;
  double *X_data;
  double *det1_data;
  double *det2_data;
  double *ind_ij_data;
  double *ind_ji_data;
  double *quad1_data;
  double *r2;
  double *r4;
  double *varargin_1_data;
  double *varargin_2_data;
  int stampConst_size[2];
  int stampVar_size[2];
  int b_j1;
  int i1;
  int loop_ub;
  int loop_ub_tmp;
  int ma;
  int na;
  int t;
  int *r7;
  signed char b_input_sizes_idx_1;
  signed char input_sizes_idx_1;
  signed char *K_data;
  boolean_T empty_non_axis_sizes;
  A_data = A->data;
  /*  Produces the values of the norms of the entries of A (quad1) and the */
  /*  determinants of the submatrices of A (quad2). */
  /*  The norm equations are satisfied if the two columns of quad1 are equal. */
  /*  The determinant equations are satisfied if the three columns of quad2  */
  /*  are equal. These columns correspond to the three columns of equalities  */
  /*  on the Overleaf document. */
  t = A->size[1];
  emxInit_real_T(&M, 2);
  i1 = M->size[0] * M->size[1];
  M->size[0] = A->size[1];
  M->size[1] = A->size[1];
  emxEnsureCapacity_real_T(M, i1);
  M_data = M->data;
  loop_ub_tmp = A->size[1] * A->size[1];
  for (i1 = 0; i1 < loop_ub_tmp; i1++) {
    M_data[i1] = 0.0;
  }
  if (A->size[1] > 0) {
    for (ma = 0; ma < t; ma++) {
      M_data[ma + M->size[0] * ma] = 1.0;
    }
  }
  ma = M->size[0];
  na = M->size[1];
  emxInit_int8_T(&K);
  i1 = K->size[0] * K->size[1];
  K->size[0] = M->size[0] << 1;
  K->size[1] = M->size[1];
  emxEnsureCapacity_int8_T(K, i1);
  K_data = K->data;
  t = -1;
  for (b_j1 = 0; b_j1 < na; b_j1++) {
    for (i1 = 0; i1 < ma; i1++) {
      input_sizes_idx_1 = (signed char)M_data[i1 + M->size[0] * b_j1];
      K_data[t + 1] = input_sizes_idx_1;
      K_data[t + 2] = input_sizes_idx_1;
      t += 2;
    }
  }
  ma = K->size[0] * K->size[1] - 1;
  for (na = 0; na <= ma; na++) {
    if (K_data[na] != 0) {
      A_data[na] = 0.0;
    }
  }
  /*  check the norm equations */
  i1 = M->size[0] * M->size[1];
  M->size[0] = A->size[0];
  M->size[1] = A->size[1];
  emxEnsureCapacity_real_T(M, i1);
  M_data = M->data;
  loop_ub = A->size[0] * A->size[1];
  for (i1 = 0; i1 < loop_ub; i1++) {
    varargin_1 = A_data[i1];
    M_data[i1] = varargin_1 * varargin_1;
  }
  i1 = (int)((double)A->size[1] * (double)A->size[1]);
  emxInit_real_T(&y, 2);
  if (i1 == 0) {
    i1 = y->size[0] * y->size[1];
    y->size[0] = 1;
    y->size[1] = 0;
    emxEnsureCapacity_real_T(y, i1);
    quad1_data = y->data;
  } else {
    b_j1 = y->size[0] * y->size[1];
    y->size[0] = 1;
    y->size[1] = i1;
    emxEnsureCapacity_real_T(y, b_j1);
    quad1_data = y->data;
    for (ma = 0; ma < i1; ma++) {
      t = ma << 1;
      quad1_data[ma] = M_data[t] + M_data[t + 1];
    }
  }
  i1 = M->size[0] * M->size[1];
  M->size[0] = A->size[1];
  M->size[1] = A->size[1];
  emxEnsureCapacity_real_T(M, i1);
  M_data = M->data;
  for (i1 = 0; i1 < loop_ub_tmp; i1++) {
    M_data[i1] = quad1_data[i1];
  }
  for (ma = 0; ma < loop_ub_tmp; ma++) {
    M_data[ma] = sqrt(M_data[ma]);
  }
  if (A->size[1] < 1) {
    y->size[0] = 1;
    y->size[1] = 0;
  } else {
    i1 = y->size[0] * y->size[1];
    y->size[0] = 1;
    y->size[1] = A->size[1];
    emxEnsureCapacity_real_T(y, i1);
    quad1_data = y->data;
    loop_ub = A->size[1] - 1;
    for (i1 = 0; i1 <= loop_ub; i1++) {
      quad1_data[i1] = (double)i1 + 1.0;
    }
  }
  emxInit_real_T(&ind_ij, 2);
  nchoosek(y, ind_ij);
  ind_ij_data = ind_ij->data;
  emxInit_real_T(&ind_ji, 2);
  i1 = ind_ji->size[0] * ind_ji->size[1];
  ind_ji->size[0] = ind_ij->size[0];
  ind_ji->size[1] = 2;
  emxEnsureCapacity_real_T(ind_ji, i1);
  ind_ji_data = ind_ji->data;
  loop_ub = ind_ij->size[0];
  for (i1 = 0; i1 < loop_ub; i1++) {
    ind_ji_data[i1] = ind_ij_data[i1 + ind_ij->size[0]];
    ind_ji_data[i1 + ind_ji->size[0]] = ind_ij_data[i1];
  }
  t = M->size[0];
  emxInit_real_T(&b_varargin_1, 1);
  i1 = b_varargin_1->size[0];
  b_varargin_1->size[0] = ind_ij->size[0];
  emxEnsureCapacity_real_T(b_varargin_1, i1);
  varargin_1_data = b_varargin_1->data;
  loop_ub = ind_ij->size[0];
  for (i1 = 0; i1 < loop_ub; i1++) {
    varargin_1_data[i1] =
        M_data[((int)ind_ij_data[i1] +
                t * ((int)ind_ij_data[i1 + ind_ij->size[0]] - 1)) -
               1];
  }
  t = M->size[0];
  emxInit_real_T(&varargin_2, 1);
  i1 = varargin_2->size[0];
  varargin_2->size[0] = ind_ji->size[0];
  emxEnsureCapacity_real_T(varargin_2, i1);
  varargin_2_data = varargin_2->data;
  loop_ub = ind_ji->size[0];
  i1 = quad1->size[0] * quad1->size[1];
  quad1->size[0] = b_varargin_1->size[0];
  quad1->size[1] = 2;
  emxEnsureCapacity_real_T(quad1, i1);
  quad1_data = quad1->data;
  for (i1 = 0; i1 < loop_ub; i1++) {
    varargin_2_data[i1] =
        M_data[((int)ind_ji_data[i1] +
                t * ((int)ind_ji_data[i1 + ind_ji->size[0]] - 1)) -
               1];
    quad1_data[i1] = varargin_1_data[i1];
  }
  emxFree_real_T(&ind_ji);
  loop_ub = varargin_2->size[0];
  for (i1 = 0; i1 < loop_ub; i1++) {
    quad1_data[i1 + quad1->size[0]] = varargin_2_data[i1];
  }
  /*  check the determinant equations */
  if (A->size[1] < 1) {
    y->size[0] = 1;
    y->size[1] = 0;
  } else {
    i1 = y->size[0] * y->size[1];
    y->size[0] = 1;
    y->size[1] = A->size[1];
    emxEnsureCapacity_real_T(y, i1);
    quad1_data = y->data;
    loop_ub = A->size[1] - 1;
    for (i1 = 0; i1 <= loop_ub; i1++) {
      quad1_data[i1] = (double)i1 + 1.0;
    }
  }
  emxInit_real_T(&X, 2);
  b_nchoosek(y, X);
  X_data = X->data;
  emxFree_real_T(&y);
  /*  I_rep = repmat(ones(2,1), 1, m); */
  /*  I_cell = mat2cell(I_rep, 2, ones(1,m)); */
  /*  ind = logical(blkdiag(I_cell{:})); */
  emxInit_real_T(&r, 2);
  i1 = r->size[0] * r->size[1];
  r->size[0] = 2;
  r->size[1] = X->size[0];
  emxEnsureCapacity_real_T(r, i1);
  varargin_2_data = r->data;
  loop_ub = X->size[0];
  emxInit_real_T(&r1, 2);
  i1 = r1->size[0] * r1->size[1];
  r1->size[0] = 2;
  r1->size[1] = X->size[0];
  emxEnsureCapacity_real_T(r1, i1);
  r2 = r1->data;
  emxInit_real_T(&block1, 3);
  i1 = block1->size[0] * block1->size[1] * block1->size[2];
  block1->size[0] = 1;
  block1->size[1] = 1;
  block1->size[2] = X->size[0];
  emxEnsureCapacity_real_T(block1, i1);
  ind_ji_data = block1->data;
  for (i1 = 0; i1 < loop_ub; i1++) {
    varargin_1 = X_data[i1];
    varargin_2_data[2 * i1] = varargin_1;
    b_j1 = 2 * i1 + 1;
    varargin_2_data[b_j1] = X_data[i1 + X->size[0]];
    r2[2 * i1] = varargin_1;
    r2[b_j1] = X_data[i1 + X->size[0] * 2];
    ind_ji_data[i1] = varargin_1;
  }
  emxInit_real_T(&det3, 2);
  squeeze(block1, det3);
  ind_ji_data = det3->data;
  /* function inds = s3(i) */
  /* function out  = s3(R,i) */
  /* function out  = s3(A,i,j) */
  /*  */
  /*  This function, when given an index i vector, converts it to the node */
  /*  indices (3*i-2,3*i-1,3*i) for each value of i. It is meant for accessing
   */
  /*  subblocks of block matrices. */
  /*  */
  /*  Uses: */
  /*  A(s3(1),s3(2)) retrieves the subblock A(1,2). */
  /*  A(s3([1 7]),s3(2:3)) retrieves the corresponding subblocks */
  if (det3->size[0] == 1) {
    /*          stampConst = [3 3 3]; */
    stampConst_size[0] = 1;
    stampConst_size[1] = 2;
    /*  CHANGED */
    stampVar_size[0] = 1;
    stampVar_size[1] = 2;
    stampConst_data[0] = 2.0;
    stampVar_data[0] = 0.0;
    stampConst_data[1] = 2.0;
    stampVar_data[1] = 1.0;
  } else {
    /*          stampConst = [3 3 3]'; */
    stampConst_size[0] = 2;
    stampConst_size[1] = 1;
    /*  CHANGED */
    stampVar_size[0] = 2;
    stampVar_size[1] = 1;
    stampConst_data[0] = 2.0;
    stampVar_data[0] = 0.0;
    stampConst_data[1] = 2.0;
    stampVar_data[1] = 1.0;
  }
  emxInit_real_T(&b_det3, 2);
  i1 = b_det3->size[0] * b_det3->size[1];
  b_det3->size[0] = det3->size[0];
  b_det3->size[1] = 1;
  emxEnsureCapacity_real_T(b_det3, i1);
  quad1_data = b_det3->data;
  loop_ub = det3->size[0];
  for (i1 = 0; i1 < loop_ub; i1++) {
    quad1_data[i1] = 1.0;
  }
  kron(b_det3, stampVar_data, stampVar_size, ind_ij);
  ind_ij_data = ind_ij->data;
  i1 = b_det3->size[0] * b_det3->size[1];
  b_det3->size[0] = det3->size[0];
  b_det3->size[1] = 1;
  emxEnsureCapacity_real_T(b_det3, i1);
  quad1_data = b_det3->data;
  loop_ub = det3->size[0];
  for (i1 = 0; i1 < loop_ub; i1++) {
    quad1_data[i1] = ind_ji_data[i1] - 1.0;
  }
  emxInit_real_T(&r3, 2);
  kron(b_det3, stampConst_data, stampConst_size, r3);
  r4 = r3->data;
  if ((ind_ij->size[0] == r3->size[0]) && (ind_ij->size[1] == r3->size[1])) {
    loop_ub = ind_ij->size[0] * ind_ij->size[1];
    for (i1 = 0; i1 < loop_ub; i1++) {
      ind_ij_data[i1] = (ind_ij_data[i1] + 1.0) + r4[i1];
    }
  } else {
    t_binary_expand_op(ind_ij, r3);
    ind_ij_data = ind_ij->data;
  }
  i1 = block1->size[0] * block1->size[1] * block1->size[2];
  block1->size[0] = 1;
  block1->size[1] = 1;
  block1->size[2] = X->size[0];
  emxEnsureCapacity_real_T(block1, i1);
  ind_ji_data = block1->data;
  loop_ub = X->size[0];
  for (i1 = 0; i1 < loop_ub; i1++) {
    ind_ji_data[i1] = r2[2 * i1];
  }
  squeeze(block1, det3);
  ind_ji_data = det3->data;
  /* function inds = s3(i) */
  /* function out  = s3(R,i) */
  /* function out  = s3(A,i,j) */
  /*  */
  /*  This function, when given an index i vector, converts it to the node */
  /*  indices (3*i-2,3*i-1,3*i) for each value of i. It is meant for accessing
   */
  /*  subblocks of block matrices. */
  /*  */
  /*  Uses: */
  /*  A(s3(1),s3(2)) retrieves the subblock A(1,2). */
  /*  A(s3([1 7]),s3(2:3)) retrieves the corresponding subblocks */
  if (det3->size[0] == 1) {
    /*          stampConst = [3 3 3]; */
    stampConst_size[0] = 1;
    stampConst_size[1] = 2;
    /*  CHANGED */
    stampVar_size[0] = 1;
    stampVar_size[1] = 2;
    stampConst_data[0] = 2.0;
    stampVar_data[0] = 0.0;
    stampConst_data[1] = 2.0;
    stampVar_data[1] = 1.0;
  } else {
    /*          stampConst = [3 3 3]'; */
    stampConst_size[0] = 2;
    stampConst_size[1] = 1;
    /*  CHANGED */
    stampVar_size[0] = 2;
    stampVar_size[1] = 1;
    stampConst_data[0] = 2.0;
    stampVar_data[0] = 0.0;
    stampConst_data[1] = 2.0;
    stampVar_data[1] = 1.0;
  }
  i1 = b_det3->size[0] * b_det3->size[1];
  b_det3->size[0] = det3->size[0];
  b_det3->size[1] = 1;
  emxEnsureCapacity_real_T(b_det3, i1);
  quad1_data = b_det3->data;
  loop_ub = det3->size[0];
  for (i1 = 0; i1 < loop_ub; i1++) {
    quad1_data[i1] = 1.0;
  }
  kron(b_det3, stampVar_data, stampVar_size, r3);
  r4 = r3->data;
  i1 = b_det3->size[0] * b_det3->size[1];
  b_det3->size[0] = det3->size[0];
  b_det3->size[1] = 1;
  emxEnsureCapacity_real_T(b_det3, i1);
  quad1_data = b_det3->data;
  loop_ub = det3->size[0];
  for (i1 = 0; i1 < loop_ub; i1++) {
    quad1_data[i1] = ind_ji_data[i1] - 1.0;
  }
  emxInit_real_T(&r5, 2);
  kron(b_det3, stampConst_data, stampConst_size, r5);
  quad1_data = r5->data;
  if ((r3->size[0] == r5->size[0]) && (r3->size[1] == r5->size[1])) {
    loop_ub = r3->size[0] * r3->size[1];
    for (i1 = 0; i1 < loop_ub; i1++) {
      r4[i1] = (r4[i1] + 1.0) + quad1_data[i1];
    }
  } else {
    t_binary_expand_op(r3, r5);
    r4 = r3->data;
  }
  t = X->size[0];
  i1 = M->size[0] * M->size[1];
  M->size[0] = X->size[0];
  M->size[1] = X->size[0];
  emxEnsureCapacity_real_T(M, i1);
  M_data = M->data;
  loop_ub = X->size[0] * X->size[0];
  for (i1 = 0; i1 < loop_ub; i1++) {
    M_data[i1] = 0.0;
  }
  if (X->size[0] > 0) {
    for (ma = 0; ma < t; ma++) {
      M_data[ma + M->size[0] * ma] = 1.0;
    }
  }
  ma = M->size[0];
  na = M->size[1];
  loop_ub = M->size[0] << 1;
  i1 = K->size[0] * K->size[1];
  K->size[0] = loop_ub;
  K->size[1] = M->size[1];
  emxEnsureCapacity_int8_T(K, i1);
  K_data = K->data;
  t = -1;
  for (b_j1 = 0; b_j1 < na; b_j1++) {
    for (i1 = 0; i1 < ma; i1++) {
      input_sizes_idx_1 = (signed char)M_data[i1 + M->size[0] * b_j1];
      K_data[t + 1] = input_sizes_idx_1;
      K_data[t + 2] = input_sizes_idx_1;
      t += 2;
    }
  }
  t = K->size[0] * K->size[1];
  ma = t - 1;
  t = 0;
  for (na = 0; na <= ma; na++) {
    if (K_data[na] != 0) {
      t++;
    }
  }
  emxInit_int32_T(&r6);
  i1 = r6->size[0];
  r6->size[0] = t;
  emxEnsureCapacity_int32_T(r6, i1);
  r7 = r6->data;
  t = 0;
  for (na = 0; na <= ma; na++) {
    if (K_data[na] != 0) {
      r7[t] = na;
      t++;
    }
  }
  emxFree_int8_T(&K);
  i1 = M->size[0] * M->size[1];
  M->size[0] = loop_ub;
  M->size[1] = X->size[0];
  emxEnsureCapacity_real_T(M, i1);
  M_data = M->data;
  t = X->size[0];
  for (i1 = 0; i1 < t; i1++) {
    for (b_j1 = 0; b_j1 < loop_ub; b_j1++) {
      M_data[b_j1 + M->size[0] * i1] =
          A_data[((int)ind_ij_data[b_j1] +
                  A->size[0] * ((int)varargin_2_data[2 * i1 + 1] - 1)) -
                 1];
    }
  }
  i1 = b_varargin_1->size[0];
  b_varargin_1->size[0] = r6->size[0];
  emxEnsureCapacity_real_T(b_varargin_1, i1);
  varargin_1_data = b_varargin_1->data;
  t = r6->size[0];
  for (i1 = 0; i1 < t; i1++) {
    varargin_1_data[i1] = M_data[r7[i1]];
  }
  i1 = M->size[0] * M->size[1];
  M->size[0] = loop_ub;
  M->size[1] = X->size[0];
  emxEnsureCapacity_real_T(M, i1);
  M_data = M->data;
  t = X->size[0];
  for (i1 = 0; i1 < t; i1++) {
    for (b_j1 = 0; b_j1 < loop_ub; b_j1++) {
      M_data[b_j1 + M->size[0] * i1] =
          A_data[((int)r4[b_j1] + A->size[0] * ((int)r2[2 * i1 + 1] - 1)) - 1];
    }
  }
  i1 = varargin_2->size[0];
  varargin_2->size[0] = r6->size[0];
  emxEnsureCapacity_real_T(varargin_2, i1);
  varargin_2_data = varargin_2->data;
  t = r6->size[0];
  for (i1 = 0; i1 < t; i1++) {
    varargin_2_data[i1] = M_data[r7[i1]];
  }
  emxInit_real_T(&b_block1, 3);
  i1 = b_block1->size[0] * b_block1->size[1] * b_block1->size[2];
  b_block1->size[0] = 2;
  b_block1->size[1] = 2;
  b_block1->size[2] = X->size[0];
  emxEnsureCapacity_real_T(b_block1, i1);
  quad1_data = b_block1->data;
  t = X->size[0];
  for (i1 = 0; i1 < t; i1++) {
    quad1_data[4 * i1] = varargin_1_data[2 * i1];
    quad1_data[4 * i1 + 2] = varargin_2_data[2 * i1];
    b_j1 = 2 * i1 + 1;
    quad1_data[4 * i1 + 1] = varargin_1_data[b_j1];
    quad1_data[4 * i1 + 3] = varargin_2_data[b_j1];
  }
  i1 = block1->size[0] * block1->size[1] * block1->size[2];
  block1->size[0] = 1;
  block1->size[1] = 1;
  block1->size[2] = b_block1->size[2];
  emxEnsureCapacity_real_T(block1, i1);
  ind_ji_data = block1->data;
  t = b_block1->size[2];
  for (i1 = 0; i1 < t; i1++) {
    ind_ji_data[i1] = quad1_data[4 * i1] * quad1_data[4 * i1 + 3] -
                      quad1_data[4 * i1 + 2] * quad1_data[4 * i1 + 1];
  }
  emxInit_real_T(&det1, 2);
  squeeze(block1, det1);
  det1_data = det1->data;
  i1 = r->size[0] * r->size[1];
  r->size[0] = 2;
  r->size[1] = X->size[0];
  emxEnsureCapacity_real_T(r, i1);
  varargin_2_data = r->data;
  t = X->size[0];
  i1 = r1->size[0] * r1->size[1];
  r1->size[0] = 2;
  r1->size[1] = X->size[0];
  emxEnsureCapacity_real_T(r1, i1);
  r2 = r1->data;
  i1 = block1->size[0] * block1->size[1] * block1->size[2];
  block1->size[0] = 1;
  block1->size[1] = 1;
  block1->size[2] = X->size[0];
  emxEnsureCapacity_real_T(block1, i1);
  ind_ji_data = block1->data;
  for (i1 = 0; i1 < t; i1++) {
    varargin_1 = X_data[i1 + X->size[0]];
    varargin_2_data[2 * i1] = varargin_1;
    b_j1 = 2 * i1 + 1;
    varargin_2_data[b_j1] = X_data[i1];
    r2[2 * i1] = varargin_1;
    r2[b_j1] = X_data[i1 + X->size[0] * 2];
    ind_ji_data[i1] = varargin_1;
  }
  squeeze(block1, det3);
  ind_ji_data = det3->data;
  /* function inds = s3(i) */
  /* function out  = s3(R,i) */
  /* function out  = s3(A,i,j) */
  /*  */
  /*  This function, when given an index i vector, converts it to the node */
  /*  indices (3*i-2,3*i-1,3*i) for each value of i. It is meant for accessing
   */
  /*  subblocks of block matrices. */
  /*  */
  /*  Uses: */
  /*  A(s3(1),s3(2)) retrieves the subblock A(1,2). */
  /*  A(s3([1 7]),s3(2:3)) retrieves the corresponding subblocks */
  if (det3->size[0] == 1) {
    /*          stampConst = [3 3 3]; */
    stampConst_size[0] = 1;
    stampConst_size[1] = 2;
    /*  CHANGED */
    stampVar_size[0] = 1;
    stampVar_size[1] = 2;
    stampConst_data[0] = 2.0;
    stampVar_data[0] = 0.0;
    stampConst_data[1] = 2.0;
    stampVar_data[1] = 1.0;
  } else {
    /*          stampConst = [3 3 3]'; */
    stampConst_size[0] = 2;
    stampConst_size[1] = 1;
    /*  CHANGED */
    stampVar_size[0] = 2;
    stampVar_size[1] = 1;
    stampConst_data[0] = 2.0;
    stampVar_data[0] = 0.0;
    stampConst_data[1] = 2.0;
    stampVar_data[1] = 1.0;
  }
  i1 = b_det3->size[0] * b_det3->size[1];
  b_det3->size[0] = det3->size[0];
  b_det3->size[1] = 1;
  emxEnsureCapacity_real_T(b_det3, i1);
  quad1_data = b_det3->data;
  t = det3->size[0];
  for (i1 = 0; i1 < t; i1++) {
    quad1_data[i1] = 1.0;
  }
  kron(b_det3, stampVar_data, stampVar_size, ind_ij);
  ind_ij_data = ind_ij->data;
  i1 = b_det3->size[0] * b_det3->size[1];
  b_det3->size[0] = det3->size[0];
  b_det3->size[1] = 1;
  emxEnsureCapacity_real_T(b_det3, i1);
  quad1_data = b_det3->data;
  t = det3->size[0];
  for (i1 = 0; i1 < t; i1++) {
    quad1_data[i1] = ind_ji_data[i1] - 1.0;
  }
  kron(b_det3, stampConst_data, stampConst_size, r3);
  r4 = r3->data;
  if ((ind_ij->size[0] == r3->size[0]) && (ind_ij->size[1] == r3->size[1])) {
    t = ind_ij->size[0] * ind_ij->size[1];
    for (i1 = 0; i1 < t; i1++) {
      ind_ij_data[i1] = (ind_ij_data[i1] + 1.0) + r4[i1];
    }
  } else {
    t_binary_expand_op(ind_ij, r3);
    ind_ij_data = ind_ij->data;
  }
  i1 = block1->size[0] * block1->size[1] * block1->size[2];
  block1->size[0] = 1;
  block1->size[1] = 1;
  block1->size[2] = X->size[0];
  emxEnsureCapacity_real_T(block1, i1);
  ind_ji_data = block1->data;
  t = X->size[0];
  for (i1 = 0; i1 < t; i1++) {
    ind_ji_data[i1] = r2[2 * i1];
  }
  squeeze(block1, det3);
  ind_ji_data = det3->data;
  /* function inds = s3(i) */
  /* function out  = s3(R,i) */
  /* function out  = s3(A,i,j) */
  /*  */
  /*  This function, when given an index i vector, converts it to the node */
  /*  indices (3*i-2,3*i-1,3*i) for each value of i. It is meant for accessing
   */
  /*  subblocks of block matrices. */
  /*  */
  /*  Uses: */
  /*  A(s3(1),s3(2)) retrieves the subblock A(1,2). */
  /*  A(s3([1 7]),s3(2:3)) retrieves the corresponding subblocks */
  if (det3->size[0] == 1) {
    /*          stampConst = [3 3 3]; */
    stampConst_size[0] = 1;
    stampConst_size[1] = 2;
    /*  CHANGED */
    stampVar_size[0] = 1;
    stampVar_size[1] = 2;
    stampConst_data[0] = 2.0;
    stampVar_data[0] = 0.0;
    stampConst_data[1] = 2.0;
    stampVar_data[1] = 1.0;
  } else {
    /*          stampConst = [3 3 3]'; */
    stampConst_size[0] = 2;
    stampConst_size[1] = 1;
    /*  CHANGED */
    stampVar_size[0] = 2;
    stampVar_size[1] = 1;
    stampConst_data[0] = 2.0;
    stampVar_data[0] = 0.0;
    stampConst_data[1] = 2.0;
    stampVar_data[1] = 1.0;
  }
  i1 = b_det3->size[0] * b_det3->size[1];
  b_det3->size[0] = det3->size[0];
  b_det3->size[1] = 1;
  emxEnsureCapacity_real_T(b_det3, i1);
  quad1_data = b_det3->data;
  t = det3->size[0];
  for (i1 = 0; i1 < t; i1++) {
    quad1_data[i1] = 1.0;
  }
  kron(b_det3, stampVar_data, stampVar_size, r3);
  r4 = r3->data;
  i1 = b_det3->size[0] * b_det3->size[1];
  b_det3->size[0] = det3->size[0];
  b_det3->size[1] = 1;
  emxEnsureCapacity_real_T(b_det3, i1);
  quad1_data = b_det3->data;
  t = det3->size[0];
  for (i1 = 0; i1 < t; i1++) {
    quad1_data[i1] = ind_ji_data[i1] - 1.0;
  }
  kron(b_det3, stampConst_data, stampConst_size, r5);
  quad1_data = r5->data;
  if ((r3->size[0] == r5->size[0]) && (r3->size[1] == r5->size[1])) {
    t = r3->size[0] * r3->size[1];
    for (i1 = 0; i1 < t; i1++) {
      r4[i1] = (r4[i1] + 1.0) + quad1_data[i1];
    }
  } else {
    t_binary_expand_op(r3, r5);
    r4 = r3->data;
  }
  i1 = M->size[0] * M->size[1];
  M->size[0] = loop_ub;
  M->size[1] = X->size[0];
  emxEnsureCapacity_real_T(M, i1);
  M_data = M->data;
  t = X->size[0];
  for (i1 = 0; i1 < t; i1++) {
    for (b_j1 = 0; b_j1 < loop_ub; b_j1++) {
      M_data[b_j1 + M->size[0] * i1] =
          A_data[((int)ind_ij_data[b_j1] +
                  A->size[0] * ((int)varargin_2_data[2 * i1 + 1] - 1)) -
                 1];
    }
  }
  i1 = b_varargin_1->size[0];
  b_varargin_1->size[0] = r6->size[0];
  emxEnsureCapacity_real_T(b_varargin_1, i1);
  varargin_1_data = b_varargin_1->data;
  t = r6->size[0];
  for (i1 = 0; i1 < t; i1++) {
    varargin_1_data[i1] = M_data[r7[i1]];
  }
  i1 = M->size[0] * M->size[1];
  M->size[0] = loop_ub;
  M->size[1] = X->size[0];
  emxEnsureCapacity_real_T(M, i1);
  M_data = M->data;
  t = X->size[0];
  for (i1 = 0; i1 < t; i1++) {
    for (b_j1 = 0; b_j1 < loop_ub; b_j1++) {
      M_data[b_j1 + M->size[0] * i1] =
          A_data[((int)r4[b_j1] + A->size[0] * ((int)r2[2 * i1 + 1] - 1)) - 1];
    }
  }
  i1 = varargin_2->size[0];
  varargin_2->size[0] = r6->size[0];
  emxEnsureCapacity_real_T(varargin_2, i1);
  varargin_2_data = varargin_2->data;
  t = r6->size[0];
  for (i1 = 0; i1 < t; i1++) {
    varargin_2_data[i1] = M_data[r7[i1]];
  }
  i1 = b_block1->size[0] * b_block1->size[1] * b_block1->size[2];
  b_block1->size[0] = 2;
  b_block1->size[1] = 2;
  b_block1->size[2] = X->size[0];
  emxEnsureCapacity_real_T(b_block1, i1);
  quad1_data = b_block1->data;
  t = X->size[0];
  for (i1 = 0; i1 < t; i1++) {
    quad1_data[4 * i1] = varargin_1_data[2 * i1];
    quad1_data[4 * i1 + 2] = varargin_2_data[2 * i1];
    b_j1 = 2 * i1 + 1;
    quad1_data[4 * i1 + 1] = varargin_1_data[b_j1];
    quad1_data[4 * i1 + 3] = varargin_2_data[b_j1];
  }
  i1 = block1->size[0] * block1->size[1] * block1->size[2];
  block1->size[0] = 1;
  block1->size[1] = 1;
  block1->size[2] = b_block1->size[2];
  emxEnsureCapacity_real_T(block1, i1);
  ind_ji_data = block1->data;
  t = b_block1->size[2];
  for (i1 = 0; i1 < t; i1++) {
    ind_ji_data[i1] = quad1_data[4 * i1] * quad1_data[4 * i1 + 3] -
                      quad1_data[4 * i1 + 2] * quad1_data[4 * i1 + 1];
  }
  emxInit_real_T(&det2, 2);
  squeeze(block1, det2);
  i1 = det2->size[0] * det2->size[1];
  det2->size[1] = 1;
  emxEnsureCapacity_real_T(det2, i1);
  det2_data = det2->data;
  t = det2->size[0] - 1;
  for (i1 = 0; i1 <= t; i1++) {
    det2_data[i1] = -det2_data[i1];
  }
  i1 = r->size[0] * r->size[1];
  r->size[0] = 2;
  r->size[1] = X->size[0];
  emxEnsureCapacity_real_T(r, i1);
  varargin_2_data = r->data;
  t = X->size[0];
  i1 = r1->size[0] * r1->size[1];
  r1->size[0] = 2;
  r1->size[1] = X->size[0];
  emxEnsureCapacity_real_T(r1, i1);
  r2 = r1->data;
  i1 = block1->size[0] * block1->size[1] * block1->size[2];
  block1->size[0] = 1;
  block1->size[1] = 1;
  block1->size[2] = X->size[0];
  emxEnsureCapacity_real_T(block1, i1);
  ind_ji_data = block1->data;
  for (i1 = 0; i1 < t; i1++) {
    varargin_1 = X_data[i1 + X->size[0] * 2];
    varargin_2_data[2 * i1] = varargin_1;
    b_j1 = 2 * i1 + 1;
    varargin_2_data[b_j1] = X_data[i1];
    r2[2 * i1] = varargin_1;
    r2[b_j1] = X_data[i1 + X->size[0]];
    ind_ji_data[i1] = varargin_1;
  }
  squeeze(block1, det3);
  ind_ji_data = det3->data;
  /* function inds = s3(i) */
  /* function out  = s3(R,i) */
  /* function out  = s3(A,i,j) */
  /*  */
  /*  This function, when given an index i vector, converts it to the node */
  /*  indices (3*i-2,3*i-1,3*i) for each value of i. It is meant for accessing
   */
  /*  subblocks of block matrices. */
  /*  */
  /*  Uses: */
  /*  A(s3(1),s3(2)) retrieves the subblock A(1,2). */
  /*  A(s3([1 7]),s3(2:3)) retrieves the corresponding subblocks */
  if (det3->size[0] == 1) {
    /*          stampConst = [3 3 3]; */
    stampConst_size[0] = 1;
    stampConst_size[1] = 2;
    /*  CHANGED */
    stampVar_size[0] = 1;
    stampVar_size[1] = 2;
    stampConst_data[0] = 2.0;
    stampVar_data[0] = 0.0;
    stampConst_data[1] = 2.0;
    stampVar_data[1] = 1.0;
  } else {
    /*          stampConst = [3 3 3]'; */
    stampConst_size[0] = 2;
    stampConst_size[1] = 1;
    /*  CHANGED */
    stampVar_size[0] = 2;
    stampVar_size[1] = 1;
    stampConst_data[0] = 2.0;
    stampVar_data[0] = 0.0;
    stampConst_data[1] = 2.0;
    stampVar_data[1] = 1.0;
  }
  i1 = b_det3->size[0] * b_det3->size[1];
  b_det3->size[0] = det3->size[0];
  b_det3->size[1] = 1;
  emxEnsureCapacity_real_T(b_det3, i1);
  quad1_data = b_det3->data;
  t = det3->size[0];
  for (i1 = 0; i1 < t; i1++) {
    quad1_data[i1] = 1.0;
  }
  kron(b_det3, stampVar_data, stampVar_size, ind_ij);
  ind_ij_data = ind_ij->data;
  i1 = b_det3->size[0] * b_det3->size[1];
  b_det3->size[0] = det3->size[0];
  b_det3->size[1] = 1;
  emxEnsureCapacity_real_T(b_det3, i1);
  quad1_data = b_det3->data;
  t = det3->size[0];
  for (i1 = 0; i1 < t; i1++) {
    quad1_data[i1] = ind_ji_data[i1] - 1.0;
  }
  kron(b_det3, stampConst_data, stampConst_size, r3);
  r4 = r3->data;
  if ((ind_ij->size[0] == r3->size[0]) && (ind_ij->size[1] == r3->size[1])) {
    t = ind_ij->size[0] * ind_ij->size[1];
    for (i1 = 0; i1 < t; i1++) {
      ind_ij_data[i1] = (ind_ij_data[i1] + 1.0) + r4[i1];
    }
  } else {
    t_binary_expand_op(ind_ij, r3);
    ind_ij_data = ind_ij->data;
  }
  i1 = block1->size[0] * block1->size[1] * block1->size[2];
  block1->size[0] = 1;
  block1->size[1] = 1;
  block1->size[2] = X->size[0];
  emxEnsureCapacity_real_T(block1, i1);
  ind_ji_data = block1->data;
  t = X->size[0];
  for (i1 = 0; i1 < t; i1++) {
    ind_ji_data[i1] = r2[2 * i1];
  }
  squeeze(block1, det3);
  ind_ji_data = det3->data;
  /* function inds = s3(i) */
  /* function out  = s3(R,i) */
  /* function out  = s3(A,i,j) */
  /*  */
  /*  This function, when given an index i vector, converts it to the node */
  /*  indices (3*i-2,3*i-1,3*i) for each value of i. It is meant for accessing
   */
  /*  subblocks of block matrices. */
  /*  */
  /*  Uses: */
  /*  A(s3(1),s3(2)) retrieves the subblock A(1,2). */
  /*  A(s3([1 7]),s3(2:3)) retrieves the corresponding subblocks */
  if (det3->size[0] == 1) {
    /*          stampConst = [3 3 3]; */
    stampConst_size[0] = 1;
    stampConst_size[1] = 2;
    /*  CHANGED */
    stampVar_size[0] = 1;
    stampVar_size[1] = 2;
    stampConst_data[0] = 2.0;
    stampVar_data[0] = 0.0;
    stampConst_data[1] = 2.0;
    stampVar_data[1] = 1.0;
  } else {
    /*          stampConst = [3 3 3]'; */
    stampConst_size[0] = 2;
    stampConst_size[1] = 1;
    /*  CHANGED */
    stampVar_size[0] = 2;
    stampVar_size[1] = 1;
    stampConst_data[0] = 2.0;
    stampVar_data[0] = 0.0;
    stampConst_data[1] = 2.0;
    stampVar_data[1] = 1.0;
  }
  i1 = b_det3->size[0] * b_det3->size[1];
  b_det3->size[0] = det3->size[0];
  b_det3->size[1] = 1;
  emxEnsureCapacity_real_T(b_det3, i1);
  quad1_data = b_det3->data;
  t = det3->size[0];
  for (i1 = 0; i1 < t; i1++) {
    quad1_data[i1] = 1.0;
  }
  kron(b_det3, stampVar_data, stampVar_size, r3);
  r4 = r3->data;
  i1 = b_det3->size[0] * b_det3->size[1];
  b_det3->size[0] = det3->size[0];
  b_det3->size[1] = 1;
  emxEnsureCapacity_real_T(b_det3, i1);
  quad1_data = b_det3->data;
  t = det3->size[0];
  for (i1 = 0; i1 < t; i1++) {
    quad1_data[i1] = ind_ji_data[i1] - 1.0;
  }
  kron(b_det3, stampConst_data, stampConst_size, r5);
  quad1_data = r5->data;
  emxFree_real_T(&b_det3);
  if ((r3->size[0] == r5->size[0]) && (r3->size[1] == r5->size[1])) {
    t = r3->size[0] * r3->size[1];
    for (i1 = 0; i1 < t; i1++) {
      r4[i1] = (r4[i1] + 1.0) + quad1_data[i1];
    }
  } else {
    t_binary_expand_op(r3, r5);
    r4 = r3->data;
  }
  emxFree_real_T(&r5);
  i1 = M->size[0] * M->size[1];
  M->size[0] = loop_ub;
  M->size[1] = X->size[0];
  emxEnsureCapacity_real_T(M, i1);
  M_data = M->data;
  t = X->size[0];
  for (i1 = 0; i1 < t; i1++) {
    for (b_j1 = 0; b_j1 < loop_ub; b_j1++) {
      M_data[b_j1 + M->size[0] * i1] =
          A_data[((int)ind_ij_data[b_j1] +
                  A->size[0] * ((int)varargin_2_data[2 * i1 + 1] - 1)) -
                 1];
    }
  }
  emxFree_real_T(&r);
  emxFree_real_T(&ind_ij);
  i1 = b_varargin_1->size[0];
  b_varargin_1->size[0] = r6->size[0];
  emxEnsureCapacity_real_T(b_varargin_1, i1);
  varargin_1_data = b_varargin_1->data;
  t = r6->size[0];
  for (i1 = 0; i1 < t; i1++) {
    varargin_1_data[i1] = M_data[r7[i1]];
  }
  i1 = M->size[0] * M->size[1];
  M->size[0] = loop_ub;
  M->size[1] = X->size[0];
  emxEnsureCapacity_real_T(M, i1);
  M_data = M->data;
  t = X->size[0];
  for (i1 = 0; i1 < t; i1++) {
    for (b_j1 = 0; b_j1 < loop_ub; b_j1++) {
      M_data[b_j1 + M->size[0] * i1] =
          A_data[((int)r4[b_j1] + A->size[0] * ((int)r2[2 * i1 + 1] - 1)) - 1];
    }
  }
  emxFree_real_T(&r3);
  emxFree_real_T(&r1);
  i1 = varargin_2->size[0];
  varargin_2->size[0] = r6->size[0];
  emxEnsureCapacity_real_T(varargin_2, i1);
  varargin_2_data = varargin_2->data;
  loop_ub = r6->size[0];
  for (i1 = 0; i1 < loop_ub; i1++) {
    varargin_2_data[i1] = M_data[r7[i1]];
  }
  emxFree_int32_T(&r6);
  emxFree_real_T(&M);
  i1 = b_block1->size[0] * b_block1->size[1] * b_block1->size[2];
  b_block1->size[0] = 2;
  b_block1->size[1] = 2;
  b_block1->size[2] = X->size[0];
  emxEnsureCapacity_real_T(b_block1, i1);
  quad1_data = b_block1->data;
  loop_ub = X->size[0];
  emxFree_real_T(&X);
  for (i1 = 0; i1 < loop_ub; i1++) {
    quad1_data[4 * i1] = varargin_1_data[2 * i1];
    quad1_data[4 * i1 + 2] = varargin_2_data[2 * i1];
    b_j1 = 2 * i1 + 1;
    quad1_data[4 * i1 + 1] = varargin_1_data[b_j1];
    quad1_data[4 * i1 + 3] = varargin_2_data[b_j1];
  }
  emxFree_real_T(&varargin_2);
  emxFree_real_T(&b_varargin_1);
  i1 = block1->size[0] * block1->size[1] * block1->size[2];
  block1->size[0] = 1;
  block1->size[1] = 1;
  block1->size[2] = b_block1->size[2];
  emxEnsureCapacity_real_T(block1, i1);
  ind_ji_data = block1->data;
  loop_ub = b_block1->size[2];
  for (i1 = 0; i1 < loop_ub; i1++) {
    ind_ji_data[i1] = quad1_data[4 * i1] * quad1_data[4 * i1 + 3] -
                      quad1_data[4 * i1 + 2] * quad1_data[4 * i1 + 1];
  }
  emxFree_real_T(&b_block1);
  squeeze(block1, det3);
  ind_ji_data = det3->data;
  emxFree_real_T(&block1);
  if (det1->size[0] != 0) {
    t = det1->size[0];
  } else if (det2->size[0] != 0) {
    t = det2->size[0];
  } else if (det3->size[0] != 0) {
    t = det3->size[0];
  } else {
    t = 0;
  }
  empty_non_axis_sizes = (t == 0);
  if (empty_non_axis_sizes || (det1->size[0] != 0)) {
    input_sizes_idx_1 = 1;
  } else {
    input_sizes_idx_1 = 0;
  }
  if (empty_non_axis_sizes || (det2->size[0] != 0)) {
    b_input_sizes_idx_1 = 1;
  } else {
    b_input_sizes_idx_1 = 0;
  }
  if (empty_non_axis_sizes || (det3->size[0] != 0)) {
    ma = 1;
  } else {
    ma = 0;
  }
  i1 = quad2->size[0] * quad2->size[1];
  quad2->size[0] = t;
  b_j1 = input_sizes_idx_1 + b_input_sizes_idx_1;
  quad2->size[1] = b_j1 + ma;
  emxEnsureCapacity_real_T(quad2, i1);
  quad1_data = quad2->data;
  loop_ub = input_sizes_idx_1;
  for (i1 = 0; i1 < loop_ub; i1++) {
    for (na = 0; na < t; na++) {
      quad1_data[na] = det1_data[na];
    }
  }
  emxFree_real_T(&det1);
  loop_ub = b_input_sizes_idx_1;
  for (i1 = 0; i1 < loop_ub; i1++) {
    for (na = 0; na < t; na++) {
      quad1_data[na + quad2->size[0] * input_sizes_idx_1] = det2_data[na];
    }
  }
  emxFree_real_T(&det2);
  for (i1 = 0; i1 < ma; i1++) {
    for (na = 0; na < t; na++) {
      quad1_data[na + quad2->size[0] * b_j1] = ind_ji_data[na];
    }
  }
  emxFree_real_T(&det3);
}

/* End of code generation (checkQuadrics.c) */

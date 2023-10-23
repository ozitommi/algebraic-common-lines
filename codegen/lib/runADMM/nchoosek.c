/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * nchoosek.c
 *
 * Code generation for function 'nchoosek'
 *
 */

/* Include files */
#include "nchoosek.h"
#include "rt_nonfinite.h"
#include "runADMM_emxutil.h"
#include "runADMM_types.h"
#include "rt_nonfinite.h"
#include <math.h>

/* Function Declarations */
static double nCk(double n, double k);

static double rt_roundd_snf(double u);

/* Function Definitions */
static double nCk(double n, double k)
{
  double y;
  int j;
  if (rtIsInf(n) || rtIsNaN(n) || (rtIsInf(k) || rtIsNaN(k))) {
    y = rtNaN;
  } else if (k > 1000.0) {
    y = rtInf;
  } else {
    double maxRelErr;
    int i;
    maxRelErr = 0.0;
    y = n;
    i = (int)(k - 1.0);
    for (j = 0; j < i; j++) {
      y *= ((n - ((double)j + 2.0)) + 1.0) / ((double)j + 2.0);
      if (!(y < 1.125899906842624E+15)) {
        maxRelErr += 4.4408920985006262E-16;
      }
      y = rt_roundd_snf(y);
    }
    if ((maxRelErr != 0.0) && (y <= 3.6893488147419103E+19)) {
      unsigned long b_i;
      unsigned long b_k;
      unsigned long b_n;
      unsigned long yint;
      boolean_T exitg1;
      maxRelErr = rt_roundd_snf(n);
      if (maxRelErr < 1.8446744073709552E+19) {
        if (maxRelErr >= 0.0) {
          b_n = (unsigned long)maxRelErr;
        } else {
          b_n = 0UL;
        }
      } else if (maxRelErr >= 1.8446744073709552E+19) {
        b_n = MAX_uint64_T;
      } else {
        b_n = 0UL;
      }
      maxRelErr = rt_roundd_snf(k);
      if (maxRelErr < 1.8446744073709552E+19) {
        if (maxRelErr >= 0.0) {
          b_k = (unsigned long)maxRelErr;
        } else {
          b_k = 0UL;
        }
      } else {
        b_k = 0UL;
      }
      yint = 1UL;
      b_i = 1UL;
      exitg1 = false;
      while ((!exitg1) && (b_i <= b_k)) {
        unsigned long u;
        unsigned long u1;
        if (b_i == 0UL) {
          u = MAX_uint64_T;
        } else {
          u = yint / b_i;
        }
        if (b_n == 0UL) {
          u1 = MAX_uint64_T;
        } else {
          u1 = MAX_uint64_T / b_n;
        }
        if (u >= u1) {
          yint = MAX_uint64_T;
          exitg1 = true;
        } else {
          if (b_i == 0UL) {
            u1 = MAX_uint64_T;
          } else {
            if (b_i == 0UL) {
              u1 = MAX_uint64_T;
            } else {
              u1 = yint / b_i;
            }
            u1 = (yint - u1 * b_i) * b_n / b_i;
          }
          yint = u * b_n + u1;
          b_n--;
          b_i++;
        }
      }
      y = (double)yint;
    }
  }
  return y;
}

static double rt_roundd_snf(double u)
{
  double y;
  if (fabs(u) < 4.503599627370496E+15) {
    if (u >= 0.5) {
      y = floor(u + 0.5);
    } else if (u > -0.5) {
      y = u * 0.0;
    } else {
      y = ceil(u - 0.5);
    }
  } else {
    y = u;
  }
  return y;
}

void b_nchoosek(const emxArray_real_T *x, emxArray_real_T *y)
{
  const double *x_data;
  double *y_data;
  int nmkpi;
  int row;
  x_data = x->data;
  if (x->size[1] == 1) {
    double r;
    r = 3.0;
    if (x_data[0] - 3.0 < 3.0) {
      r = x_data[0] - 3.0;
    }
    if (r == 0.0) {
      int b_r;
      b_r = y->size[0] * y->size[1];
      y->size[0] = 1;
      y->size[1] = 1;
      emxEnsureCapacity_real_T(y, b_r);
      y_data = y->data;
      y_data[0] = 1.0;
    } else if (r == 1.0) {
      int b_r;
      b_r = y->size[0] * y->size[1];
      y->size[0] = 1;
      y->size[1] = 1;
      emxEnsureCapacity_real_T(y, b_r);
      y_data = y->data;
      y_data[0] = x_data[0];
    } else {
      int b_r;
      b_r = y->size[0] * y->size[1];
      y->size[0] = 1;
      y->size[1] = 1;
      emxEnsureCapacity_real_T(y, b_r);
      y_data = y->data;
      y_data[0] = nCk(x_data[0], r);
    }
  } else if (x->size[1] < 3) {
    y->size[0] = 0;
    y->size[1] = 3;
  } else {
    double r;
    int comb[3];
    int b_r;
    int nrows;
    b_r = 3;
    if (x->size[1] - 3 < 3) {
      b_r = x->size[1] - 3;
    }
    if (b_r == 0) {
      r = 1.0;
    } else if (b_r == 1) {
      r = x->size[1];
    } else {
      r = nCk(x->size[1], b_r);
    }
    nrows = (int)floor(r);
    b_r = y->size[0] * y->size[1];
    y->size[0] = nrows;
    y->size[1] = 3;
    emxEnsureCapacity_real_T(y, b_r);
    y_data = y->data;
    comb[0] = 1;
    comb[1] = 2;
    comb[2] = 3;
    b_r = 2;
    nmkpi = x->size[1];
    for (row = 0; row < nrows; row++) {
      y_data[row] = x_data[comb[0] - 1];
      y_data[row + y->size[0]] = x_data[comb[1] - 1];
      y_data[row + y->size[0] * 2] = x_data[comb[2] - 1];
      if (b_r + 1 > 0) {
        int a;
        int combj;
        a = comb[b_r];
        combj = comb[b_r] + 1;
        comb[b_r]++;
        if (a + 1 < nmkpi) {
          b_r += 2;
          for (nmkpi = b_r; nmkpi < 4; nmkpi++) {
            combj++;
            comb[nmkpi - 1] = combj;
          }
          b_r = 2;
          nmkpi = x->size[1];
        } else {
          b_r--;
          nmkpi--;
        }
      }
    }
  }
}

void nchoosek(const emxArray_real_T *x, emxArray_real_T *y)
{
  const double *x_data;
  double *y_data;
  int nmkpi;
  int row;
  x_data = x->data;
  if (x->size[1] == 1) {
    double r;
    r = 2.0;
    if (x_data[0] - 2.0 < 2.0) {
      r = x_data[0] - 2.0;
    }
    if (r == 0.0) {
      int b_r;
      b_r = y->size[0] * y->size[1];
      y->size[0] = 1;
      y->size[1] = 1;
      emxEnsureCapacity_real_T(y, b_r);
      y_data = y->data;
      y_data[0] = 1.0;
    } else if (r == 1.0) {
      int b_r;
      b_r = y->size[0] * y->size[1];
      y->size[0] = 1;
      y->size[1] = 1;
      emxEnsureCapacity_real_T(y, b_r);
      y_data = y->data;
      y_data[0] = x_data[0];
    } else {
      int b_r;
      b_r = y->size[0] * y->size[1];
      y->size[0] = 1;
      y->size[1] = 1;
      emxEnsureCapacity_real_T(y, b_r);
      y_data = y->data;
      y_data[0] = nCk(x_data[0], r);
    }
  } else if (x->size[1] < 2) {
    y->size[0] = 0;
    y->size[1] = 2;
  } else {
    double r;
    int comb[2];
    int b_r;
    int nrows;
    b_r = 2;
    if (x->size[1] - 2 < 2) {
      b_r = x->size[1] - 2;
    }
    if (b_r == 0) {
      r = 1.0;
    } else if (b_r == 1) {
      r = x->size[1];
    } else {
      r = nCk(x->size[1], b_r);
    }
    nrows = (int)floor(r);
    b_r = y->size[0] * y->size[1];
    y->size[0] = nrows;
    y->size[1] = 2;
    emxEnsureCapacity_real_T(y, b_r);
    y_data = y->data;
    comb[0] = 1;
    comb[1] = 2;
    b_r = 1;
    nmkpi = x->size[1];
    for (row = 0; row < nrows; row++) {
      y_data[row] = x_data[comb[0] - 1];
      y_data[row + y->size[0]] = x_data[comb[1] - 1];
      if (b_r + 1 > 0) {
        int a;
        int combj;
        a = comb[b_r];
        combj = comb[b_r] + 1;
        comb[b_r]++;
        if (a + 1 < nmkpi) {
          b_r += 2;
          for (nmkpi = b_r; nmkpi < 3; nmkpi++) {
            combj++;
            comb[1] = combj;
          }
          b_r = 1;
          nmkpi = x->size[1];
        } else {
          b_r--;
          nmkpi--;
        }
      }
    }
  }
}

/* End of code generation (nchoosek.c) */

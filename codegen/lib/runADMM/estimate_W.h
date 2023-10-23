/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * estimate_W.h
 *
 * Code generation for function 'estimate_W'
 *
 */

#ifndef ESTIMATE_W_H
#define ESTIMATE_W_H

/* Include files */
#include "rtwtypes.h"
#include "runADMM_types.h"
#include <stddef.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Function Declarations */
void estimate_W(double var_n, const emxArray_boolean_T *var_keep,
                const emxArray_real_T *var_E_est, const emxArray_real_T *var_E,
                const emxArray_real_T *var_lam, emxArray_real_T *W);

#ifdef __cplusplus
}
#endif

#endif
/* End of code generation (estimate_W.h) */

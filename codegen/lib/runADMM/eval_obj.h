/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * eval_obj.h
 *
 * Code generation for function 'eval_obj'
 *
 */

#ifndef EVAL_OBJ_H
#define EVAL_OBJ_H

/* Include files */
#include "rtwtypes.h"
#include "runADMM_types.h"
#include <stddef.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Function Declarations */
double eval_obj(double var_n, const emxArray_boolean_T *var_keep,
                const emxArray_real_T *var_E_est, const emxArray_real_T *var_E,
                const emxArray_real_T *var_W, const emxArray_real_T *var_lam,
                double *objLp);

#ifdef __cplusplus
}
#endif

#endif
/* End of code generation (eval_obj.h) */

/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * constructDetMats.h
 *
 * Code generation for function 'constructDetMats'
 *
 */

#ifndef CONSTRUCTDETMATS_H
#define CONSTRUCTDETMATS_H

/* Include files */
#include "rtwtypes.h"
#include "runADMM_types.h"
#include <stddef.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Function Declarations */
void constructDetMats(double var_n, const emxArray_real_T *var_missing_mu,
                      const emxArray_real_T *var_missing_tau1,
                      const emxArray_real_T *var_missing_tau2,
                      const emxArray_real_T *var_quad, emxArray_real_T *D1_mu,
                      emxArray_real_T *D2_mu, emxArray_real_T *D1_tau,
                      emxArray_real_T *D2_tau);

#ifdef __cplusplus
}
#endif

#endif
/* End of code generation (constructDetMats.h) */

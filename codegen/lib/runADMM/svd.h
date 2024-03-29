/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * svd.h
 *
 * Code generation for function 'svd'
 *
 */

#ifndef SVD_H
#define SVD_H

/* Include files */
#include "rtwtypes.h"
#include "runADMM_types.h"
#include <stddef.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Function Declarations */
void svd(const emxArray_real_T *A, emxArray_real_T *U, emxArray_real_T *s,
         emxArray_real_T *V);

#ifdef __cplusplus
}
#endif

#endif
/* End of code generation (svd.h) */

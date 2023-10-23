/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * sumprod.h
 *
 * Code generation for function 'sumprod'
 *
 */

#ifndef SUMPROD_H
#define SUMPROD_H

/* Include files */
#include "rtwtypes.h"
#include "runADMM_types.h"
#include <stddef.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Function Declarations */
void d_binary_expand_op(emxArray_real_T *in1, const emxArray_real_T *in2,
                        const struct0_T *in4, const emxArray_real_T *in5);

void j_binary_expand_op(emxArray_real_T *in1, const emxArray_real_T *in2,
                        const struct0_T *in4, const emxArray_real_T *in5);

void q_binary_expand_op(emxArray_real_T *in1, const emxArray_real_T *in2,
                        const emxArray_real_T *in4);

#ifdef __cplusplus
}
#endif

#endif
/* End of code generation (sumprod.h) */

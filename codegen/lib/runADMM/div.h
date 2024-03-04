/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * div.h
 *
 * Code generation for function 'div'
 *
 */

#ifndef DIV_H
#define DIV_H

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
                        const emxArray_real_T *in3);

void g_binary_expand_op(struct0_T *in1, const emxArray_real_T *in2,
                        const emxArray_real_T *in3);

#ifdef __cplusplus
}
#endif

#endif
/* End of code generation (div.h) */

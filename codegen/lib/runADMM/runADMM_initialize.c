/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * runADMM_initialize.c
 *
 * Code generation for function 'runADMM_initialize'
 *
 */

/* Include files */
#include "runADMM_initialize.h"
#include "rt_nonfinite.h"
#include "runADMM_data.h"
#include "omp.h"

/* Function Definitions */
void runADMM_initialize(void)
{
  omp_init_nest_lock(&runADMM_nestLockGlobal);
  isInitialized_runADMM = true;
}

/* End of code generation (runADMM_initialize.c) */

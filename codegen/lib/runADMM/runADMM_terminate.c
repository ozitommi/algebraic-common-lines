/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * runADMM_terminate.c
 *
 * Code generation for function 'runADMM_terminate'
 *
 */

/* Include files */
#include "runADMM_terminate.h"
#include "rt_nonfinite.h"
#include "runADMM_data.h"
#include "omp.h"

/* Function Definitions */
void runADMM_terminate(void)
{
  omp_destroy_nest_lock(&runADMM_nestLockGlobal);
  isInitialized_runADMM = false;
}

/* End of code generation (runADMM_terminate.c) */

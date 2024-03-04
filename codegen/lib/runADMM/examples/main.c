/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * main.c
 *
 * Code generation for function 'main'
 *
 */

/*************************************************************************/
/* This automatically generated example C main file shows how to call    */
/* entry-point functions that MATLAB Coder generated. You must customize */
/* this file for your application. Do not modify this file directly.     */
/* Instead, make a copy of this file, modify it, and integrate it into   */
/* your development environment.                                         */
/*                                                                       */
/* This file initializes entry-point function arguments to a default     */
/* size and value before calling the entry-point functions. It does      */
/* not store or use any values returned from the entry-point functions.  */
/* If necessary, it does pre-allocate memory for returned values.        */
/* You can use this file as a starting point for a main function that    */
/* you can deploy in your application.                                   */
/*                                                                       */
/* After you copy the file, and before you deploy it, you must make the  */
/* following changes:                                                    */
/* * For variable-size function arguments, change the example sizes to   */
/* the sizes that your application requires.                             */
/* * Change the example values of function arguments to the values that  */
/* your application requires.                                            */
/* * If the entry-point functions return values, store these values or   */
/* otherwise use them as required by your application.                   */
/*                                                                       */
/*************************************************************************/

/* Include files */
#include "main.h"
#include "rt_nonfinite.h"
#include "runADMM.h"
#include "runADMM_emxAPI.h"
#include "runADMM_terminate.h"
#include "runADMM_types.h"

/* Function Declarations */
static boolean_T argInit_boolean_T(void);

static double argInit_real_T(void);

static void argInit_struct0_T(struct0_T *result);

static emxArray_boolean_T *c_argInit_UnboundedxUnbounded_b(void);

static emxArray_real_T *c_argInit_UnboundedxUnbounded_r(void);

/* Function Definitions */
static boolean_T argInit_boolean_T(void)
{
  return false;
}

static double argInit_real_T(void)
{
  return 0.0;
}

static void argInit_struct0_T(struct0_T *result)
{
  double result_tmp;
  /* Set the value of each structure field.
Change this value to the value that the application requires. */
  result_tmp = argInit_real_T();
  result->IR_iter = result_tmp;
  result->objlp_tol = result_tmp;
  result->conv_tol = result_tmp;
  result->vld = result_tmp;
  result->tau = result_tmp;
  result->objl2 = result_tmp;
  result->objlp = result_tmp;
  result->n = result_tmp;
  result->keep = c_argInit_UnboundedxUnbounded_b();
  result->E_est = c_argInit_UnboundedxUnbounded_r();
  result->A = c_argInit_UnboundedxUnbounded_r();
  result->X = c_argInit_UnboundedxUnbounded_r();
  result->E = c_argInit_UnboundedxUnbounded_r();
  result->Y = c_argInit_UnboundedxUnbounded_r();
  result->gamma = c_argInit_UnboundedxUnbounded_r();
  result->W = c_argInit_UnboundedxUnbounded_r();
  result->lam = c_argInit_UnboundedxUnbounded_r();
}

static emxArray_boolean_T *c_argInit_UnboundedxUnbounded_b(void)
{
  emxArray_boolean_T *result;
  int idx0;
  int idx1;
  boolean_T *result_data;
  /* Set the size of the array.
Change this size to the value that the application requires. */
  result = emxCreate_boolean_T(2, 2);
  result_data = result->data;
  /* Loop over the array to initialize each element. */
  for (idx0 = 0; idx0 < result->size[0U]; idx0++) {
    for (idx1 = 0; idx1 < result->size[1U]; idx1++) {
      /* Set the value of the array element.
Change this value to the value that the application requires. */
      result_data[idx0 + result->size[0] * idx1] = argInit_boolean_T();
    }
  }
  return result;
}

static emxArray_real_T *c_argInit_UnboundedxUnbounded_r(void)
{
  emxArray_real_T *result;
  double *result_data;
  int idx0;
  int idx1;
  /* Set the size of the array.
Change this size to the value that the application requires. */
  result = emxCreate_real_T(2, 2);
  result_data = result->data;
  /* Loop over the array to initialize each element. */
  for (idx0 = 0; idx0 < result->size[0U]; idx0++) {
    for (idx1 = 0; idx1 < result->size[1U]; idx1++) {
      /* Set the value of the array element.
Change this value to the value that the application requires. */
      result_data[idx0 + result->size[0] * idx1] = argInit_real_T();
    }
  }
  return result;
}

int main(int argc, char **argv)
{
  (void)argc;
  (void)argv;
  /* The initialize function is being called automatically from your entry-point
   * function. So, a call to initialize is not included here. */
  /* Invoke the entry-point functions.
You can call entry-point functions multiple times. */
  main_runADMM();
  /* Terminate the application.
You do not need to do this more than one time. */
  runADMM_terminate();
  return 0;
}

void main_runADMM(void)
{
  emxArray_real_T *A_out;
  emxArray_real_T *lam_out;
  struct0_T var;
  /* Initialize function 'runADMM' input arguments. */
  /* Initialize function input argument 'var'. */
  argInit_struct0_T(&var);
  /* Call the entry-point 'runADMM'. */
  emxInitArray_real_T(&A_out, 2);
  emxInitArray_real_T(&lam_out, 2);
  runADMM(&var, A_out, lam_out);
  emxDestroyArray_real_T(A_out);
  emxDestroyArray_real_T(lam_out);
  emxDestroy_struct0_T(var);
}

/* End of code generation (main.c) */

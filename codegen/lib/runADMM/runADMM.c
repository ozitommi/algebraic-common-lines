/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * runADMM.c
 *
 * Code generation for function 'runADMM'
 *
 */

/* Include files */
#include "runADMM.h"
#include "ADMM.h"
#include "estimate_W.h"
#include "eval_obj.h"
#include "rt_nonfinite.h"
#include "runADMM_emxutil.h"
#include "runADMM_internal_types.h"
#include "runADMM_types.h"
#include "sum.h"
#include <math.h>

/* Function Definitions */
void runADMM(struct0_T *var, emxArray_real_T *A_out, emxArray_real_T *lam_out)
{
  emxArray_real_T c_var;
  struct0_T e_var;
  struct0_T f_var;
  struct_T expl_temp;
  double IR_iter;
  double diffF;
  double iter_irls;
  double objlp;
  double objlp_tol;
  double *A_out_data;
  int b_var;
  int d_var;
  int g_var;
  int i;
  /*  Run IRLS and ADMM */
  /*  Performs IRLS and ADMM/alternating descent */
  /*  L1 cost function */
  IR_iter = var->IR_iter;
  objlp_tol = var->objlp_tol;
  /*  Run ADMM once */
  b_var = var->W->size[0] * var->W->size[1];
  c_var = *var->W;
  d_var = b_var;
  c_var.size = &d_var;
  c_var.numDimensions = 1;
  var->tau = 0.5 * sum(&c_var);
  emxInitStruct_struct0_T(&e_var);
  emxCopyStruct_struct0_T(&e_var, var);
  f_var = e_var;
  ADMM(&f_var, var, &expl_temp);
  /*  run ADMM */
  var->objl2 =
      eval_obj(var->n, var->keep, var->E_est, var->E, var->W, var->lam, &objlp);
  /*  evaluate cost function */
  diffF = fabs(objlp - var->objlp) / fmax(objlp, var->objlp);
  var->objlp = objlp;
  estimate_W(var->n, var->keep, var->E_est, var->E, var->lam, var->W);
  /*  estimate weights for IRLS */
  /*  fprintf('IRLS iter %d IRLS obj L2 %.3e obj Lp(p=1)
   * %.3e\n',iter_irls,objl2,objlp); */
  iter_irls = 2.0;
  /*  Repeat */
  while ((iter_irls < IR_iter + 1.0) && (diffF > 1.0E-6) &&
         (objlp > objlp_tol)) {
    b_var = var->W->size[0] * var->W->size[1];
    c_var = *var->W;
    g_var = b_var;
    c_var.size = &g_var;
    c_var.numDimensions = 1;
    var->tau = 0.5 * sum(&c_var);
    emxCopyStruct_struct0_T(&e_var, var);
    f_var = e_var;
    ADMM(&f_var, var, &expl_temp);
    /*  run ADMM */
    var->objl2 = eval_obj(var->n, var->keep, var->E_est, var->E, var->W,
                          var->lam, &objlp);
    /*  evaluate cost function */
    diffF = fabs(objlp - var->objlp) / fmax(objlp, var->objlp);
    var->objlp = objlp;
    estimate_W(var->n, var->keep, var->E_est, var->E, var->lam, var->W);
    /*  estimate weights for IRLS */
    /*  fprintf('IRLS iter %d IRLS obj L2 %.3e obj Lp(p=1)
     * %.3e\n',iter_irls,objl2,objlp); */
    iter_irls++;
    /*  [~,Sigma,~] = svd(var.E,'vector') */
  }
  emxFreeStruct_struct0_T(&e_var);
  /*  Output */
  i = A_out->size[0] * A_out->size[1];
  A_out->size[0] = var->E->size[0];
  A_out->size[1] = var->E->size[1];
  emxEnsureCapacity_real_T(A_out, i);
  A_out_data = A_out->data;
  b_var = var->E->size[0] * var->E->size[1];
  for (i = 0; i < b_var; i++) {
    A_out_data[i] = var->E->data[i];
  }
  i = lam_out->size[0] * lam_out->size[1];
  lam_out->size[0] = var->lam->size[0];
  lam_out->size[1] = var->lam->size[1];
  emxEnsureCapacity_real_T(lam_out, i);
  A_out_data = lam_out->data;
  b_var = var->lam->size[0] * var->lam->size[1];
  for (i = 0; i < b_var; i++) {
    A_out_data[i] = var->lam->data[i];
  }
}

/* End of code generation (runADMM.c) */

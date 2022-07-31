/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: MRAC_for_coder.c
 *
 * Code generated for Simulink model 'MRAC_for_coder'.
 *
 * Model version                  : 8.2
 * Simulink Coder version         : 9.7 (R2022a) 13-Nov-2021
 * C/C++ source code generated on : Sun Jul 31 20:11:37 2022
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "MRAC_for_coder.h"
#include "rtwtypes.h"
#include "MRAC_for_coder_private.h"

/* Exported data definition */

/* Data with Exported storage */
real_T MRAC_for_code_controller_output;/* '<Root>/controller_output' */

/* Block signals (default storage) */
B_MRAC_for_coder_T MRAC_for_coder_B;

/* Continuous states */
X_MRAC_for_coder_T MRAC_for_coder_X;

/* Real-time model */
static RT_MODEL_MRAC_for_coder_T MRAC_for_coder_M_;
RT_MODEL_MRAC_for_coder_T *const MRAC_for_coder_M = &MRAC_for_coder_M_;

/*
 * This function updates continuous states using the ODE3 fixed-step
 * solver algorithm
 */
static void rt_ertODEUpdateContinuousStates(RTWSolverInfo *si )
{
  /* Solver Matrices */
  static const real_T rt_ODE3_A[3] = {
    1.0/2.0, 3.0/4.0, 1.0
  };

  static const real_T rt_ODE3_B[3][3] = {
    { 1.0/2.0, 0.0, 0.0 },

    { 0.0, 3.0/4.0, 0.0 },

    { 2.0/9.0, 1.0/3.0, 4.0/9.0 }
  };

  time_T t = rtsiGetT(si);
  time_T tnew = rtsiGetSolverStopTime(si);
  time_T h = rtsiGetStepSize(si);
  real_T *x = rtsiGetContStates(si);
  ODE3_IntgData *id = (ODE3_IntgData *)rtsiGetSolverData(si);
  real_T *y = id->y;
  real_T *f0 = id->f[0];
  real_T *f1 = id->f[1];
  real_T *f2 = id->f[2];
  real_T hB[3];
  int_T i;
  int_T nXc = 6;
  rtsiSetSimTimeStep(si,MINOR_TIME_STEP);

  /* Save the state values at time t in y, we'll use x as ynew. */
  (void) memcpy(y, x,
                (uint_T)nXc*sizeof(real_T));

  /* Assumes that rtsiSetT and ModelOutputs are up-to-date */
  /* f0 = f(t,y) */
  rtsiSetdX(si, f0);
  MRAC_for_coder_derivatives();

  /* f(:,2) = feval(odefile, t + hA(1), y + f*hB(:,1), args(:)(*)); */
  hB[0] = h * rt_ODE3_B[0][0];
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0]);
  }

  rtsiSetT(si, t + h*rt_ODE3_A[0]);
  rtsiSetdX(si, f1);
  MRAC_for_coder_step();
  MRAC_for_coder_derivatives();

  /* f(:,3) = feval(odefile, t + hA(2), y + f*hB(:,2), args(:)(*)); */
  for (i = 0; i <= 1; i++) {
    hB[i] = h * rt_ODE3_B[1][i];
  }

  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0] + f1[i]*hB[1]);
  }

  rtsiSetT(si, t + h*rt_ODE3_A[1]);
  rtsiSetdX(si, f2);
  MRAC_for_coder_step();
  MRAC_for_coder_derivatives();

  /* tnew = t + hA(3);
     ynew = y + f*hB(:,3); */
  for (i = 0; i <= 2; i++) {
    hB[i] = h * rt_ODE3_B[2][i];
  }

  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0] + f1[i]*hB[1] + f2[i]*hB[2]);
  }

  rtsiSetT(si, tnew);
  rtsiSetSimTimeStep(si,MAJOR_TIME_STEP);
}

/* Model step function */
void MRAC_for_coder_step(void)
{
  real_T rtb_e[2];
  real_T rtb_k1[2];
  real_T rtb_Sum2;
  real_T rtb_u;
  uint32_T ri;
  if (rtmIsMajorTimeStep(MRAC_for_coder_M)) {
    /* set solver stop time */
    rtsiSetSolverStopTime(&MRAC_for_coder_M->solverInfo,
                          ((MRAC_for_coder_M->Timing.clockTick0+1)*
      MRAC_for_coder_M->Timing.stepSize0));
  }                                    /* end MajorTimeStep */

  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep(MRAC_for_coder_M)) {
    MRAC_for_coder_M->Timing.t[0] = rtsiGetT(&MRAC_for_coder_M->solverInfo);
  }

  /* StateSpace: '<Root>/变量k1' */
  rtb_k1[0] = 0.0;
  rtb_k1[1] = 0.0;
  for (ri = MRAC_for_coder_P.k1_C_jc[0U]; ri < MRAC_for_coder_P.k1_C_jc[1U]; ri
       ++) {
    rtb_k1[MRAC_for_coder_P.k1_C_ir[ri]] += MRAC_for_coder_P.k1_C_pr[ri] *
      MRAC_for_coder_X.k1_CSTATE[0U];
  }

  for (ri = MRAC_for_coder_P.k1_C_jc[1U]; ri < MRAC_for_coder_P.k1_C_jc[2U]; ri
       ++) {
    rtb_k1[MRAC_for_coder_P.k1_C_ir[ri]] += MRAC_for_coder_P.k1_C_pr[ri] *
      MRAC_for_coder_X.k1_CSTATE[1U];
  }

  /* End of StateSpace: '<Root>/变量k1' */

  /* StateSpace: '<Root>/参考模型' */
  rtb_e[0] = 0.0;
  rtb_e[1] = 0.0;
  for (ri = MRAC_for_coder_P._C_jc[0U]; ri < MRAC_for_coder_P._C_jc[1U]; ri++) {
    rtb_e[MRAC_for_coder_P._C_ir[ri]] += MRAC_for_coder_P._C_pr[ri] *
      MRAC_for_coder_X._CSTATE[0U];
  }

  for (ri = MRAC_for_coder_P._C_jc[1U]; ri < MRAC_for_coder_P._C_jc[2U]; ri++) {
    rtb_e[MRAC_for_coder_P._C_ir[ri]] += MRAC_for_coder_P._C_pr[ri] *
      MRAC_for_coder_X._CSTATE[1U];
  }

  /* End of StateSpace: '<Root>/参考模型' */

  /* Sum: '<Root>/Sum' incorporates:
   *  Inport: '<Root>/theta'
   */
  rtb_u = rtb_e[0] - MRAC_for_coder_theta;

  /* DotProduct: '<Root>/Dot Product2' incorporates:
   *  Constant: '<Root>/Constant2'
   */
  rtb_Sum2 = MRAC_for_coder_P.Constant2_Value[0] * rtb_u;

  /* Sum: '<Root>/Sum' incorporates:
   *  Inport: '<Root>/omega'
   */
  rtb_e[0] = rtb_u;
  rtb_u = rtb_e[1] - MRAC_for_coder_omega;

  /* DotProduct: '<Root>/Dot Product2' incorporates:
   *  Constant: '<Root>/Constant2'
   */
  rtb_Sum2 += MRAC_for_coder_P.Constant2_Value[1] * rtb_u;

  /* Gain: '<Root>/Gain1' incorporates:
   *  DotProduct: '<Root>/Dot Product2'
   *  Inport: '<Root>/ref'
   *  Product: '<Root>/Product1'
   */
  MRAC_for_coder_B.Gain1 = rtb_Sum2 * MRAC_for_coder_ref *
    MRAC_for_coder_P.Gain1_Gain;

  /* Gain: '<Root>/Gain' incorporates:
   *  DotProduct: '<Root>/Dot Product2'
   *  Inport: '<Root>/omega'
   *  Inport: '<Root>/theta'
   *  Product: '<Root>/Product'
   */
  MRAC_for_coder_B.Gain[0] = rtb_Sum2 * MRAC_for_coder_theta *
    MRAC_for_coder_P.Gain_Gain;
  MRAC_for_coder_B.Gain[1] = rtb_Sum2 * MRAC_for_coder_omega *
    MRAC_for_coder_P.Gain_Gain;

  /* Gain: '<Root>/Gain2' incorporates:
   *  Constant: '<Root>/Constant3'
   *  DotProduct: '<Root>/Dot Product4'
   */
  MRAC_for_coder_B.Gain2 = (rtb_e[0] * MRAC_for_coder_P.Constant3_Value[0] +
    rtb_u * MRAC_for_coder_P.Constant3_Value[1]) * MRAC_for_coder_P.Gain2_Gain;

  /* StateSpace: '<Root>/变量k2' */
  rtb_u = 0.0;
  for (ri = MRAC_for_coder_P.k2_C_jc[0U]; ri < MRAC_for_coder_P.k2_C_jc[1U]; ri
       ++) {
    rtb_u += MRAC_for_coder_P.k2_C_pr * MRAC_for_coder_X.k2_CSTATE;
  }

  /* End of StateSpace: '<Root>/变量k2' */

  /* Sum: '<Root>/Sum2' incorporates:
   *  DotProduct: '<Root>/Dot Product3'
   *  Inport: '<Root>/omega'
   *  Inport: '<Root>/ref'
   *  Inport: '<Root>/theta'
   *  Product: '<Root>/Product2'
   */
  rtb_Sum2 = (rtb_k1[0] * MRAC_for_coder_theta + rtb_k1[1] *
              MRAC_for_coder_omega) + rtb_u * MRAC_for_coder_ref;

  /* StateSpace: '<Root>/扰动观测器' */
  rtb_u = 0.0;
  for (ri = MRAC_for_coder_P._C_jc_m[0U]; ri < MRAC_for_coder_P._C_jc_m[1U]; ri
       ++) {
    rtb_u += MRAC_for_coder_P._C_pr_c * MRAC_for_coder_X._CSTATE_j;
  }

  /* End of StateSpace: '<Root>/扰动观测器' */

  /* Outport: '<Root>/controller_output' incorporates:
   *  Sum: '<Root>/Sum1'
   */
  MRAC_for_code_controller_output = rtb_Sum2 + rtb_u;
  if (rtmIsMajorTimeStep(MRAC_for_coder_M)) {
    rt_ertODEUpdateContinuousStates(&MRAC_for_coder_M->solverInfo);

    /* Update absolute time for base rate */
    /* The "clockTick0" counts the number of times the code of this task has
     * been executed. The absolute time is the multiplication of "clockTick0"
     * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
     * overflow during the application lifespan selected.
     */
    ++MRAC_for_coder_M->Timing.clockTick0;
    MRAC_for_coder_M->Timing.t[0] = rtsiGetSolverStopTime
      (&MRAC_for_coder_M->solverInfo);

    {
      /* Update absolute timer for sample time: [0.02s, 0.0s] */
      /* The "clockTick1" counts the number of times the code of this task has
       * been executed. The resolution of this integer timer is 0.02, which is the step size
       * of the task. Size of "clockTick1" ensures timer will not overflow during the
       * application lifespan selected.
       */
      MRAC_for_coder_M->Timing.clockTick1++;
    }
  }                                    /* end MajorTimeStep */
}

/* Derivatives for root system: '<Root>' */
void MRAC_for_coder_derivatives(void)
{
  XDot_MRAC_for_coder_T *_rtXdot;
  uint32_T ri;
  _rtXdot = ((XDot_MRAC_for_coder_T *) MRAC_for_coder_M->derivs);

  /* Derivatives for StateSpace: '<Root>/变量k1' */
  _rtXdot->k1_CSTATE[0] = 0.0;
  _rtXdot->k1_CSTATE[1] = 0.0;
  for (ri = MRAC_for_coder_P.k1_B_jc[0U]; ri < MRAC_for_coder_P.k1_B_jc[1U]; ri
       ++) {
    _rtXdot->k1_CSTATE[MRAC_for_coder_P.k1_B_ir[ri]] +=
      MRAC_for_coder_P.k1_B_pr[ri] * MRAC_for_coder_B.Gain[0U];
  }

  for (ri = MRAC_for_coder_P.k1_B_jc[1U]; ri < MRAC_for_coder_P.k1_B_jc[2U]; ri
       ++) {
    _rtXdot->k1_CSTATE[MRAC_for_coder_P.k1_B_ir[ri]] +=
      MRAC_for_coder_P.k1_B_pr[ri] * MRAC_for_coder_B.Gain[1U];
  }

  /* End of Derivatives for StateSpace: '<Root>/变量k1' */

  /* Derivatives for StateSpace: '<Root>/参考模型' incorporates:
   *  Inport: '<Root>/ref'
   */
  _rtXdot->_CSTATE[0] = 0.0;
  _rtXdot->_CSTATE[1] = 0.0;
  for (ri = MRAC_for_coder_P._A_jc[0U]; ri < MRAC_for_coder_P._A_jc[1U]; ri++) {
    _rtXdot->_CSTATE[MRAC_for_coder_P._A_ir[ri]] += MRAC_for_coder_P._A_pr[ri] *
      MRAC_for_coder_X._CSTATE[0U];
  }

  for (ri = MRAC_for_coder_P._A_jc[1U]; ri < MRAC_for_coder_P._A_jc[2U]; ri++) {
    _rtXdot->_CSTATE[MRAC_for_coder_P._A_ir[ri]] += MRAC_for_coder_P._A_pr[ri] *
      MRAC_for_coder_X._CSTATE[1U];
  }

  for (ri = MRAC_for_coder_P._B_jc[0U]; ri < MRAC_for_coder_P._B_jc[1U]; ri++) {
    _rtXdot->_CSTATE[MRAC_for_coder_P._B_ir] += MRAC_for_coder_P._B_pr *
      MRAC_for_coder_ref;
  }

  /* End of Derivatives for StateSpace: '<Root>/参考模型' */

  /* Derivatives for StateSpace: '<Root>/变量k2' */
  _rtXdot->k2_CSTATE = 0.0;
  for (ri = MRAC_for_coder_P.k2_B_jc[0U]; ri < MRAC_for_coder_P.k2_B_jc[1U]; ri
       ++) {
    _rtXdot->k2_CSTATE += MRAC_for_coder_P.k2_B_pr * MRAC_for_coder_B.Gain1;
  }

  /* End of Derivatives for StateSpace: '<Root>/变量k2' */

  /* Derivatives for StateSpace: '<Root>/扰动观测器' */
  _rtXdot->_CSTATE_j = 0.0;
  for (ri = MRAC_for_coder_P._B_jc_n[0U]; ri < MRAC_for_coder_P._B_jc_n[1U]; ri
       ++) {
    _rtXdot->_CSTATE_j += MRAC_for_coder_P._B_pr_o * MRAC_for_coder_B.Gain2;
  }

  /* End of Derivatives for StateSpace: '<Root>/扰动观测器' */
}

/* Model initialize function */
void MRAC_for_coder_initialize(void)
{
  /* Registration code */
  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&MRAC_for_coder_M->solverInfo,
                          &MRAC_for_coder_M->Timing.simTimeStep);
    rtsiSetTPtr(&MRAC_for_coder_M->solverInfo, &rtmGetTPtr(MRAC_for_coder_M));
    rtsiSetStepSizePtr(&MRAC_for_coder_M->solverInfo,
                       &MRAC_for_coder_M->Timing.stepSize0);
    rtsiSetdXPtr(&MRAC_for_coder_M->solverInfo, &MRAC_for_coder_M->derivs);
    rtsiSetContStatesPtr(&MRAC_for_coder_M->solverInfo, (real_T **)
                         &MRAC_for_coder_M->contStates);
    rtsiSetNumContStatesPtr(&MRAC_for_coder_M->solverInfo,
      &MRAC_for_coder_M->Sizes.numContStates);
    rtsiSetNumPeriodicContStatesPtr(&MRAC_for_coder_M->solverInfo,
      &MRAC_for_coder_M->Sizes.numPeriodicContStates);
    rtsiSetPeriodicContStateIndicesPtr(&MRAC_for_coder_M->solverInfo,
      &MRAC_for_coder_M->periodicContStateIndices);
    rtsiSetPeriodicContStateRangesPtr(&MRAC_for_coder_M->solverInfo,
      &MRAC_for_coder_M->periodicContStateRanges);
    rtsiSetErrorStatusPtr(&MRAC_for_coder_M->solverInfo, (&rtmGetErrorStatus
      (MRAC_for_coder_M)));
    rtsiSetRTModelPtr(&MRAC_for_coder_M->solverInfo, MRAC_for_coder_M);
  }

  rtsiSetSimTimeStep(&MRAC_for_coder_M->solverInfo, MAJOR_TIME_STEP);
  MRAC_for_coder_M->intgData.y = MRAC_for_coder_M->odeY;
  MRAC_for_coder_M->intgData.f[0] = MRAC_for_coder_M->odeF[0];
  MRAC_for_coder_M->intgData.f[1] = MRAC_for_coder_M->odeF[1];
  MRAC_for_coder_M->intgData.f[2] = MRAC_for_coder_M->odeF[2];
  MRAC_for_coder_M->contStates = ((X_MRAC_for_coder_T *) &MRAC_for_coder_X);
  rtsiSetSolverData(&MRAC_for_coder_M->solverInfo, (void *)
                    &MRAC_for_coder_M->intgData);
  rtsiSetIsMinorTimeStepWithModeChange(&MRAC_for_coder_M->solverInfo, false);
  rtsiSetSolverName(&MRAC_for_coder_M->solverInfo,"ode3");
  rtmSetTPtr(MRAC_for_coder_M, &MRAC_for_coder_M->Timing.tArray[0]);
  MRAC_for_coder_M->Timing.stepSize0 = 0.02;

  /* InitializeConditions for StateSpace: '<Root>/变量k1' */
  MRAC_for_coder_X.k1_CSTATE[0] = MRAC_for_coder_P.k1_InitialCondition;

  /* InitializeConditions for StateSpace: '<Root>/参考模型' */
  MRAC_for_coder_X._CSTATE[0] = MRAC_for_coder_P._InitialCondition;

  /* InitializeConditions for StateSpace: '<Root>/变量k1' */
  MRAC_for_coder_X.k1_CSTATE[1] = MRAC_for_coder_P.k1_InitialCondition;

  /* InitializeConditions for StateSpace: '<Root>/参考模型' */
  MRAC_for_coder_X._CSTATE[1] = MRAC_for_coder_P._InitialCondition;

  /* InitializeConditions for StateSpace: '<Root>/变量k2' */
  MRAC_for_coder_X.k2_CSTATE = MRAC_for_coder_P.k2_InitialCondition;

  /* InitializeConditions for StateSpace: '<Root>/扰动观测器' */
  MRAC_for_coder_X._CSTATE_j = MRAC_for_coder_P._InitialCondition_a;
}

/* Model terminate function */
void MRAC_for_coder_terminate(void)
{
  /* (no terminate code required) */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */

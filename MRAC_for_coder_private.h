/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: MRAC_for_coder_private.h
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

#ifndef RTW_HEADER_MRAC_for_coder_private_h_
#define RTW_HEADER_MRAC_for_coder_private_h_
#include "rtwtypes.h"

/* Private macros used by the generated code to access rtModel */
#ifndef rtmIsMajorTimeStep
#define rtmIsMajorTimeStep(rtm)        (((rtm)->Timing.simTimeStep) == MAJOR_TIME_STEP)
#endif

#ifndef rtmIsMinorTimeStep
#define rtmIsMinorTimeStep(rtm)        (((rtm)->Timing.simTimeStep) == MINOR_TIME_STEP)
#endif

#ifndef rtmSetTPtr
#define rtmSetTPtr(rtm, val)           ((rtm)->Timing.t = (val))
#endif

/* private model entry point functions */
extern void MRAC_for_coder_derivatives(void);

/* Exported data declaration */

/* Data with Imported storage */
extern real_T MRAC_for_coder_omega;    /* '<Root>/omega' */
extern real_T MRAC_for_coder_ref;      /* '<Root>/ref' */
extern real_T MRAC_for_coder_theta;    /* '<Root>/theta' */

#endif                                /* RTW_HEADER_MRAC_for_coder_private_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */

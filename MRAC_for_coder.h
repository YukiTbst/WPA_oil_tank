/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: MRAC_for_coder.h
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

#ifndef RTW_HEADER_MRAC_for_coder_h_
#define RTW_HEADER_MRAC_for_coder_h_
#ifndef MRAC_for_coder_COMMON_INCLUDES_
#define MRAC_for_coder_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#endif                                 /* MRAC_for_coder_COMMON_INCLUDES_ */

#include "MRAC_for_coder_types.h"
#include <string.h>
#include <stddef.h>

/* Macros for accessing real-time model data structure */
#ifndef rtmGetContStateDisabled
#define rtmGetContStateDisabled(rtm)   ((rtm)->contStateDisabled)
#endif

#ifndef rtmSetContStateDisabled
#define rtmSetContStateDisabled(rtm, val) ((rtm)->contStateDisabled = (val))
#endif

#ifndef rtmGetContStates
#define rtmGetContStates(rtm)          ((rtm)->contStates)
#endif

#ifndef rtmSetContStates
#define rtmSetContStates(rtm, val)     ((rtm)->contStates = (val))
#endif

#ifndef rtmGetContTimeOutputInconsistentWithStateAtMajorStepFlag
#define rtmGetContTimeOutputInconsistentWithStateAtMajorStepFlag(rtm) ((rtm)->CTOutputIncnstWithState)
#endif

#ifndef rtmSetContTimeOutputInconsistentWithStateAtMajorStepFlag
#define rtmSetContTimeOutputInconsistentWithStateAtMajorStepFlag(rtm, val) ((rtm)->CTOutputIncnstWithState = (val))
#endif

#ifndef rtmGetDerivCacheNeedsReset
#define rtmGetDerivCacheNeedsReset(rtm) ((rtm)->derivCacheNeedsReset)
#endif

#ifndef rtmSetDerivCacheNeedsReset
#define rtmSetDerivCacheNeedsReset(rtm, val) ((rtm)->derivCacheNeedsReset = (val))
#endif

#ifndef rtmGetIntgData
#define rtmGetIntgData(rtm)            ((rtm)->intgData)
#endif

#ifndef rtmSetIntgData
#define rtmSetIntgData(rtm, val)       ((rtm)->intgData = (val))
#endif

#ifndef rtmGetOdeF
#define rtmGetOdeF(rtm)                ((rtm)->odeF)
#endif

#ifndef rtmSetOdeF
#define rtmSetOdeF(rtm, val)           ((rtm)->odeF = (val))
#endif

#ifndef rtmGetOdeY
#define rtmGetOdeY(rtm)                ((rtm)->odeY)
#endif

#ifndef rtmSetOdeY
#define rtmSetOdeY(rtm, val)           ((rtm)->odeY = (val))
#endif

#ifndef rtmGetPeriodicContStateIndices
#define rtmGetPeriodicContStateIndices(rtm) ((rtm)->periodicContStateIndices)
#endif

#ifndef rtmSetPeriodicContStateIndices
#define rtmSetPeriodicContStateIndices(rtm, val) ((rtm)->periodicContStateIndices = (val))
#endif

#ifndef rtmGetPeriodicContStateRanges
#define rtmGetPeriodicContStateRanges(rtm) ((rtm)->periodicContStateRanges)
#endif

#ifndef rtmSetPeriodicContStateRanges
#define rtmSetPeriodicContStateRanges(rtm, val) ((rtm)->periodicContStateRanges = (val))
#endif

#ifndef rtmGetZCCacheNeedsReset
#define rtmGetZCCacheNeedsReset(rtm)   ((rtm)->zCCacheNeedsReset)
#endif

#ifndef rtmSetZCCacheNeedsReset
#define rtmSetZCCacheNeedsReset(rtm, val) ((rtm)->zCCacheNeedsReset = (val))
#endif

#ifndef rtmGetdX
#define rtmGetdX(rtm)                  ((rtm)->derivs)
#endif

#ifndef rtmSetdX
#define rtmSetdX(rtm, val)             ((rtm)->derivs = (val))
#endif

#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    ((rtm)->errorStatus = (val))
#endif

#ifndef rtmGetStopRequested
#define rtmGetStopRequested(rtm)       ((rtm)->Timing.stopRequestedFlag)
#endif

#ifndef rtmSetStopRequested
#define rtmSetStopRequested(rtm, val)  ((rtm)->Timing.stopRequestedFlag = (val))
#endif

#ifndef rtmGetStopRequestedPtr
#define rtmGetStopRequestedPtr(rtm)    (&((rtm)->Timing.stopRequestedFlag))
#endif

#ifndef rtmGetT
#define rtmGetT(rtm)                   (rtmGetTPtr((rtm))[0])
#endif

#ifndef rtmGetTPtr
#define rtmGetTPtr(rtm)                ((rtm)->Timing.t)
#endif

/* Block signals (default storage) */
typedef struct {
  real_T Gain[2];                      /* '<Root>/Gain' */
  real_T Gain1;                        /* '<Root>/Gain1' */
  real_T Gain2;                        /* '<Root>/Gain2' */
} B_MRAC_for_coder_T;

/* Continuous states (default storage) */
typedef struct {
  real_T k1_CSTATE[2];                 /* '<Root>/变量k1' */
  real_T _CSTATE[2];                   /* '<Root>/参考模型' */
  real_T k2_CSTATE;                    /* '<Root>/变量k2' */
  real_T _CSTATE_j;                    /* '<Root>/扰动观测器' */
} X_MRAC_for_coder_T;

/* State derivatives (default storage) */
typedef struct {
  real_T k1_CSTATE[2];                 /* '<Root>/变量k1' */
  real_T _CSTATE[2];                   /* '<Root>/参考模型' */
  real_T k2_CSTATE;                    /* '<Root>/变量k2' */
  real_T _CSTATE_j;                    /* '<Root>/扰动观测器' */
} XDot_MRAC_for_coder_T;

/* State disabled  */
typedef struct {
  boolean_T k1_CSTATE[2];              /* '<Root>/变量k1' */
  boolean_T _CSTATE[2];                /* '<Root>/参考模型' */
  boolean_T k2_CSTATE;                 /* '<Root>/变量k2' */
  boolean_T _CSTATE_j;                 /* '<Root>/扰动观测器' */
} XDis_MRAC_for_coder_T;

#ifndef ODE3_INTG
#define ODE3_INTG

/* ODE3 Integration Data */
typedef struct {
  real_T *y;                           /* output */
  real_T *f[3];                        /* derivatives */
} ODE3_IntgData;

#endif

/* Parameters (default storage) */
struct P_MRAC_for_coder_T_ {
  real_T k1_B_pr[2];                   /* Computed Parameter: k1_B_pr
                                        * Referenced by: '<Root>/变量k1'
                                        */
  real_T k1_C_pr[2];                   /* Computed Parameter: k1_C_pr
                                        * Referenced by: '<Root>/变量k1'
                                        */
  real_T k1_InitialCondition;          /* Expression: 0
                                        * Referenced by: '<Root>/变量k1'
                                        */
  real_T Constant2_Value[2];           /* Expression: [25, 65]
                                        * Referenced by: '<Root>/Constant2'
                                        */
  real_T Constant3_Value[2];           /* Expression: [1, 2.6]
                                        * Referenced by: '<Root>/Constant3'
                                        */
  real_T _A_pr[3];                     /* Computed Parameter: _A_pr
                                        * Referenced by: '<Root>/参考模型'
                                        */
  real_T _B_pr;                        /* Computed Parameter: _B_pr
                                        * Referenced by: '<Root>/参考模型'
                                        */
  real_T _C_pr[2];                     /* Computed Parameter: _C_pr
                                        * Referenced by: '<Root>/参考模型'
                                        */
  real_T _InitialCondition;            /* Expression: 0
                                        * Referenced by: '<Root>/参考模型'
                                        */
  real_T Gain_Gain;                    /* Expression: 1
                                        * Referenced by: '<Root>/Gain'
                                        */
  real_T Gain1_Gain;                   /* Expression: 10
                                        * Referenced by: '<Root>/Gain1'
                                        */
  real_T Gain2_Gain;                   /* Expression: 10
                                        * Referenced by: '<Root>/Gain2'
                                        */
  real_T k2_B_pr;                      /* Computed Parameter: k2_B_pr
                                        * Referenced by: '<Root>/变量k2'
                                        */
  real_T k2_C_pr;                      /* Computed Parameter: k2_C_pr
                                        * Referenced by: '<Root>/变量k2'
                                        */
  real_T k2_InitialCondition;          /* Expression: 0
                                        * Referenced by: '<Root>/变量k2'
                                        */
  real_T _B_pr_o;                      /* Computed Parameter: _B_pr_o
                                        * Referenced by: '<Root>/扰动观测器'
                                        */
  real_T _C_pr_c;                      /* Computed Parameter: _C_pr_c
                                        * Referenced by: '<Root>/扰动观测器'
                                        */
  real_T _InitialCondition_a;          /* Expression: 0
                                        * Referenced by: '<Root>/扰动观测器'
                                        */
  uint32_T k1_B_ir[2];                 /* Computed Parameter: k1_B_ir
                                        * Referenced by: '<Root>/变量k1'
                                        */
  uint32_T k1_B_jc[3];                 /* Computed Parameter: k1_B_jc
                                        * Referenced by: '<Root>/变量k1'
                                        */
  uint32_T k1_C_ir[2];                 /* Computed Parameter: k1_C_ir
                                        * Referenced by: '<Root>/变量k1'
                                        */
  uint32_T k1_C_jc[3];                 /* Computed Parameter: k1_C_jc
                                        * Referenced by: '<Root>/变量k1'
                                        */
  uint32_T _A_ir[3];                   /* Computed Parameter: _A_ir
                                        * Referenced by: '<Root>/参考模型'
                                        */
  uint32_T _A_jc[3];                   /* Computed Parameter: _A_jc
                                        * Referenced by: '<Root>/参考模型'
                                        */
  uint32_T _B_ir;                      /* Computed Parameter: _B_ir
                                        * Referenced by: '<Root>/参考模型'
                                        */
  uint32_T _B_jc[2];                   /* Computed Parameter: _B_jc
                                        * Referenced by: '<Root>/参考模型'
                                        */
  uint32_T _C_ir[2];                   /* Computed Parameter: _C_ir
                                        * Referenced by: '<Root>/参考模型'
                                        */
  uint32_T _C_jc[3];                   /* Computed Parameter: _C_jc
                                        * Referenced by: '<Root>/参考模型'
                                        */
  uint32_T k2_B_ir;                    /* Computed Parameter: k2_B_ir
                                        * Referenced by: '<Root>/变量k2'
                                        */
  uint32_T k2_B_jc[2];                 /* Computed Parameter: k2_B_jc
                                        * Referenced by: '<Root>/变量k2'
                                        */
  uint32_T k2_C_ir;                    /* Computed Parameter: k2_C_ir
                                        * Referenced by: '<Root>/变量k2'
                                        */
  uint32_T k2_C_jc[2];                 /* Computed Parameter: k2_C_jc
                                        * Referenced by: '<Root>/变量k2'
                                        */
  uint32_T _B_ir_c;                    /* Computed Parameter: _B_ir_c
                                        * Referenced by: '<Root>/扰动观测器'
                                        */
  uint32_T _B_jc_n[2];                 /* Computed Parameter: _B_jc_n
                                        * Referenced by: '<Root>/扰动观测器'
                                        */
  uint32_T _C_ir_p;                    /* Computed Parameter: _C_ir_p
                                        * Referenced by: '<Root>/扰动观测器'
                                        */
  uint32_T _C_jc_m[2];                 /* Computed Parameter: _C_jc_m
                                        * Referenced by: '<Root>/扰动观测器'
                                        */
};

/* Real-time Model Data Structure */
struct tag_RTM_MRAC_for_coder_T {
  const char_T *errorStatus;
  RTWSolverInfo solverInfo;
  X_MRAC_for_coder_T *contStates;
  int_T *periodicContStateIndices;
  real_T *periodicContStateRanges;
  real_T *derivs;
  boolean_T *contStateDisabled;
  boolean_T zCCacheNeedsReset;
  boolean_T derivCacheNeedsReset;
  boolean_T CTOutputIncnstWithState;
  real_T odeY[6];
  real_T odeF[3][6];
  ODE3_IntgData intgData;

  /*
   * Sizes:
   * The following substructure contains sizes information
   * for many of the model attributes such as inputs, outputs,
   * dwork, sample times, etc.
   */
  struct {
    int_T numContStates;
    int_T numPeriodicContStates;
    int_T numSampTimes;
  } Sizes;

  /*
   * Timing:
   * The following substructure contains information regarding
   * the timing information for the model.
   */
  struct {
    uint32_T clockTick0;
    time_T stepSize0;
    uint32_T clockTick1;
    SimTimeStep simTimeStep;
    boolean_T stopRequestedFlag;
    time_T *t;
    time_T tArray[2];
  } Timing;
};

/* Block parameters (default storage) */
extern P_MRAC_for_coder_T MRAC_for_coder_P;

/* Block signals (default storage) */
extern B_MRAC_for_coder_T MRAC_for_coder_B;

/* Continuous states (default storage) */
extern X_MRAC_for_coder_T MRAC_for_coder_X;

/* Model entry point functions */
extern void MRAC_for_coder_initialize(void);
extern void MRAC_for_coder_step(void);
extern void MRAC_for_coder_terminate(void);

/* Exported data declaration */

/* Data with Exported storage */
extern real_T MRAC_for_code_controller_output;/* '<Root>/controller_output' */

/* Real-time Model object */
extern RT_MODEL_MRAC_for_coder_T *const MRAC_for_coder_M;

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Use the MATLAB hilite_system command to trace the generated code back
 * to the model.  For example,
 *
 * hilite_system('<S3>')    - opens system 3
 * hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'MRAC_for_coder'
 */
#endif                                 /* RTW_HEADER_MRAC_for_coder_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */

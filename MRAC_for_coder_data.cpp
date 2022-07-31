/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: MRAC_for_coder_data.c
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

/* Block parameters (default storage) */
P_MRAC_for_coder_T MRAC_for_coder_P = {
  /* Computed Parameter: k1_B_pr
   * Referenced by: '<Root>/变量k1'
   */
  { 1.0, 1.0 },

  /* Computed Parameter: k1_C_pr
   * Referenced by: '<Root>/变量k1'
   */
  { 1.0, 1.0 },

  /* Expression: 0
   * Referenced by: '<Root>/变量k1'
   */
  0.0,

  /* Expression: [25, 65]
   * Referenced by: '<Root>/Constant2'
   */
  { 25.0, 65.0 },

  /* Expression: [1, 2.6]
   * Referenced by: '<Root>/Constant3'
   */
  { 1.0, 2.6 },

  /* Computed Parameter: _A_pr
   * Referenced by: '<Root>/参考模型'
   */
  { -25.0, 1.0, -10.0 },

  /* Computed Parameter: _B_pr
   * Referenced by: '<Root>/参考模型'
   */
  25.0,

  /* Computed Parameter: _C_pr
   * Referenced by: '<Root>/参考模型'
   */
  { 1.0, 1.0 },

  /* Expression: 0
   * Referenced by: '<Root>/参考模型'
   */
  0.0,

  /* Expression: 1
   * Referenced by: '<Root>/Gain'
   */
  1.0,

  /* Expression: 10
   * Referenced by: '<Root>/Gain1'
   */
  10.0,

  /* Expression: 10
   * Referenced by: '<Root>/Gain2'
   */
  10.0,

  /* Computed Parameter: k2_B_pr
   * Referenced by: '<Root>/变量k2'
   */
  1.0,

  /* Computed Parameter: k2_C_pr
   * Referenced by: '<Root>/变量k2'
   */
  1.0,

  /* Expression: 0
   * Referenced by: '<Root>/变量k2'
   */
  0.0,

  /* Computed Parameter: _B_pr_o
   * Referenced by: '<Root>/扰动观测器'
   */
  1.0,

  /* Computed Parameter: _C_pr_c
   * Referenced by: '<Root>/扰动观测器'
   */
  1.0,

  /* Expression: 0
   * Referenced by: '<Root>/扰动观测器'
   */
  0.0,

  /* Computed Parameter: k1_B_ir
   * Referenced by: '<Root>/变量k1'
   */
  { 0U, 1U },

  /* Computed Parameter: k1_B_jc
   * Referenced by: '<Root>/变量k1'
   */
  { 0U, 1U, 2U },

  /* Computed Parameter: k1_C_ir
   * Referenced by: '<Root>/变量k1'
   */
  { 0U, 1U },

  /* Computed Parameter: k1_C_jc
   * Referenced by: '<Root>/变量k1'
   */
  { 0U, 1U, 2U },

  /* Computed Parameter: _A_ir
   * Referenced by: '<Root>/参考模型'
   */
  { 1U, 0U, 1U },

  /* Computed Parameter: _A_jc
   * Referenced by: '<Root>/参考模型'
   */
  { 0U, 1U, 3U },

  /* Computed Parameter: _B_ir
   * Referenced by: '<Root>/参考模型'
   */
  1U,

  /* Computed Parameter: _B_jc
   * Referenced by: '<Root>/参考模型'
   */
  { 0U, 1U },

  /* Computed Parameter: _C_ir
   * Referenced by: '<Root>/参考模型'
   */
  { 0U, 1U },

  /* Computed Parameter: _C_jc
   * Referenced by: '<Root>/参考模型'
   */
  { 0U, 1U, 2U },

  /* Computed Parameter: k2_B_ir
   * Referenced by: '<Root>/变量k2'
   */
  0U,

  /* Computed Parameter: k2_B_jc
   * Referenced by: '<Root>/变量k2'
   */
  { 0U, 1U },

  /* Computed Parameter: k2_C_ir
   * Referenced by: '<Root>/变量k2'
   */
  0U,

  /* Computed Parameter: k2_C_jc
   * Referenced by: '<Root>/变量k2'
   */
  { 0U, 1U },

  /* Computed Parameter: _B_ir_c
   * Referenced by: '<Root>/扰动观测器'
   */
  0U,

  /* Computed Parameter: _B_jc_n
   * Referenced by: '<Root>/扰动观测器'
   */
  { 0U, 1U },

  /* Computed Parameter: _C_ir_p
   * Referenced by: '<Root>/扰动观测器'
   */
  0U,

  /* Computed Parameter: _C_jc_m
   * Referenced by: '<Root>/扰动观测器'
   */
  { 0U, 1U }
};

/*
 * File trailer for generated code.
 *
 * [EOF]
 */

/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: DataAcquisition_RPM_data.c
 *
 * Code generated for Simulink model 'DataAcquisition_RPM'.
 *
 * Model version                  : 1.24
 * Simulink Coder version         : 9.8 (R2022b) 13-May-2022
 * C/C++ source code generated on : Sun Nov 19 18:24:30 2023
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Atmel->AVR
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "DataAcquisition_RPM.h"

/* Block parameters (default storage) */
P_DataAcquisition_RPM_T DataAcquisition_RPM_P = {
  /* Expression: int8(0)
   * Referenced by: '<Root>/S-Function Builder Left motor'
   */
  0,

  /* Expression: int8(18)
   * Referenced by: '<Root>/S-Function Builder Left motor'
   */
  18,

  /* Expression: int8(19)
   * Referenced by: '<Root>/S-Function Builder Left motor'
   */
  19,

  /* Start of '<S4>/If Action Subsystem1' */
  {
    /* Expression: 1
     * Referenced by: '<S8>/Constant'
     */
    1.0,

    /* Expression: -1
     * Referenced by: '<S8>/Gain'
     */
    -1.0
  }
  ,

  /* End of '<S4>/If Action Subsystem1' */

  /* Start of '<S4>/If Action Subsystem' */
  {
    /* Expression: 0
     * Referenced by: '<S7>/Constant'
     */
    0.0
  }
  ,

  /* End of '<S4>/If Action Subsystem' */

  /* Start of '<S3>/If Action Subsystem1' */
  {
    /* Expression: 1
     * Referenced by: '<S6>/Constant'
     */
    1.0,

    /* Expression: -1
     * Referenced by: '<S6>/Gain'
     */
    -1.0
  }
  ,

  /* End of '<S3>/If Action Subsystem1' */

  /* Start of '<S3>/If Action Subsystem' */
  {
    /* Expression: 0
     * Referenced by: '<S5>/Constant'
     */
    0.0
  }
  /* End of '<S3>/If Action Subsystem' */
};

/*
 * File trailer for generated code.
 *
 * [EOF]
 */

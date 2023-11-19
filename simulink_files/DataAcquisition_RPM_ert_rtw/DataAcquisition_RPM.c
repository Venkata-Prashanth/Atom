/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: DataAcquisition_RPM.c
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
#include "rtwtypes.h"
#include "DataAcquisition_RPM_private.h"
#include "DataAcquisition_RPM_types.h"
#include <math.h>

/* Block signals (default storage) */
B_DataAcquisition_RPM_T DataAcquisition_RPM_B;

/* Block states (default storage) */
DW_DataAcquisition_RPM_T DataAcquisition_RPM_DW;

/* Real-time model */
static RT_MODEL_DataAcquisition_RPM_T DataAcquisition_RPM_M_;
RT_MODEL_DataAcquisition_RPM_T *const DataAcquisition_RPM_M =
  &DataAcquisition_RPM_M_;

/*
 * Output and update for action system:
 *    '<S3>/If Action Subsystem'
 *    '<S4>/If Action Subsystem'
 */
void DataAcquisiti_IfActionSubsystem(real_T rtu_SignalIN, real_T *rty_Out1,
  real_T *rty_Out2, P_IfActionSubsystem_DataAcqui_T *localP)
{
  /* SignalConversion generated from: '<S5>/Out2' incorporates:
   *  Constant: '<S5>/Constant'
   */
  *rty_Out2 = localP->Constant_Value;

  /* SignalConversion generated from: '<S5>/Signal IN' */
  *rty_Out1 = rtu_SignalIN;
}

/*
 * Output and update for action system:
 *    '<S3>/If Action Subsystem1'
 *    '<S4>/If Action Subsystem1'
 */
void DataAcquisit_IfActionSubsystem1(real_T rtu_SignalIN, real_T *rty_Out1,
  real_T *rty_Out2, P_IfActionSubsystem1_DataAcqu_T *localP)
{
  /* SignalConversion generated from: '<S6>/Out2' incorporates:
   *  Constant: '<S6>/Constant'
   */
  *rty_Out2 = localP->Constant_Value;

  /* Gain: '<S6>/Gain' */
  *rty_Out1 = localP->Gain_Gain * rtu_SignalIN;
}

real_T rt_roundd_snf(real_T u)
{
  real_T y;
  if (fabs(u) < 4.503599627370496E+15) {
    if (u >= 0.5) {
      y = floor(u + 0.5);
    } else if (u > -0.5) {
      y = u * 0.0;
    } else {
      y = ceil(u - 0.5);
    }
  } else {
    y = u;
  }

  return y;
}

/* Model step function */
void DataAcquisition_RPM_step(void)
{
  /* local block i/o variables */
  real_T rtb_LM;
  real_T rtb_RM;
  codertarget_arduinobase_inter_T *obj;
  real_T rtb_Merge;
  real_T rtb_Merge1;
  uint8_T tmp;

  /* FromWorkspace: '<S1>/fromWS_Signal 1' */
  {
    real_T t = DataAcquisition_RPM_M->Timing.t[0];
    real_T *pTimeValues = (real_T *)
      DataAcquisition_RPM_DW.fromWS_Signal1_PWORK.TimePtr;
    real_T *pDataValues = (real_T *)
      DataAcquisition_RPM_DW.fromWS_Signal1_PWORK.DataPtr;
    if (t < pTimeValues[0]) {
      rtb_LM = 0.0;
    } else if (t == pTimeValues[9]) {
      rtb_LM = pDataValues[9];
    } else if (t > pTimeValues[9]) {
      rtb_LM = 0.0;
    } else {
      int_T currTimeIndex =
        DataAcquisition_RPM_DW.fromWS_Signal1_IWORK.PrevIndex;
      if (t < pTimeValues[currTimeIndex]) {
        while (t < pTimeValues[currTimeIndex]) {
          currTimeIndex--;
        }
      } else {
        while (t >= pTimeValues[currTimeIndex + 1]) {
          currTimeIndex++;
        }
      }

      rtb_LM = pDataValues[currTimeIndex];
      DataAcquisition_RPM_DW.fromWS_Signal1_IWORK.PrevIndex = currTimeIndex;
    }
  }

  /* If: '<S3>/If' */
  if (rtb_LM > 0.0) {
    /* Outputs for IfAction SubSystem: '<S3>/If Action Subsystem' incorporates:
     *  ActionPort: '<S5>/Action Port'
     */
    DataAcquisiti_IfActionSubsystem(rtb_LM, &rtb_Merge, &rtb_Merge1,
      &DataAcquisition_RPM_P.IfActionSubsystem);

    /* End of Outputs for SubSystem: '<S3>/If Action Subsystem' */
  } else {
    /* Outputs for IfAction SubSystem: '<S3>/If Action Subsystem1' incorporates:
     *  ActionPort: '<S6>/Action Port'
     */
    DataAcquisit_IfActionSubsystem1(rtb_LM, &rtb_Merge, &rtb_Merge1,
      &DataAcquisition_RPM_P.IfActionSubsystem1);

    /* End of Outputs for SubSystem: '<S3>/If Action Subsystem1' */
  }

  /* End of If: '<S3>/If' */

  /* MATLABSystem: '<Root>/Left Dir PIN' */
  rtb_Merge1 = rt_roundd_snf(rtb_Merge1);
  if (rtb_Merge1 < 256.0) {
    if (rtb_Merge1 >= 0.0) {
      tmp = (uint8_T)rtb_Merge1;
    } else {
      tmp = 0U;
    }
  } else {
    tmp = MAX_uint8_T;
  }

  writeDigitalPin(45, tmp);

  /* End of MATLABSystem: '<Root>/Left Dir PIN' */

  /* MATLABSystem: '<Root>/Left PWM' */
  obj = &DataAcquisition_RPM_DW.obj_h;
  obj->PWMDriverObj.MW_PWM_HANDLE = MW_PWM_GetHandle(46UL);
  if (!(rtb_Merge <= 255.0)) {
    rtb_Merge = 255.0;
  }

  if (!(rtb_Merge >= 0.0)) {
    rtb_Merge = 0.0;
  }

  MW_PWM_SetDutyCycle(DataAcquisition_RPM_DW.obj_h.PWMDriverObj.MW_PWM_HANDLE,
                      rtb_Merge);

  /* End of MATLABSystem: '<Root>/Left PWM' */

  /* FromWorkspace: '<S2>/fromWS_Signal 1' */
  {
    real_T t = DataAcquisition_RPM_M->Timing.t[0];
    real_T *pTimeValues = (real_T *)
      DataAcquisition_RPM_DW.fromWS_Signal1_PWORK_c.TimePtr;
    real_T *pDataValues = (real_T *)
      DataAcquisition_RPM_DW.fromWS_Signal1_PWORK_c.DataPtr;
    if (t < pTimeValues[0]) {
      rtb_RM = 0.0;
    } else if (t == pTimeValues[9]) {
      rtb_RM = pDataValues[9];
    } else if (t > pTimeValues[9]) {
      rtb_RM = 0.0;
    } else {
      int_T currTimeIndex =
        DataAcquisition_RPM_DW.fromWS_Signal1_IWORK_d.PrevIndex;
      if (t < pTimeValues[currTimeIndex]) {
        while (t < pTimeValues[currTimeIndex]) {
          currTimeIndex--;
        }
      } else {
        while (t >= pTimeValues[currTimeIndex + 1]) {
          currTimeIndex++;
        }
      }

      rtb_RM = pDataValues[currTimeIndex];
      DataAcquisition_RPM_DW.fromWS_Signal1_IWORK_d.PrevIndex = currTimeIndex;
    }
  }

  /* If: '<S4>/If' */
  if (rtb_RM > 0.0) {
    /* Outputs for IfAction SubSystem: '<S4>/If Action Subsystem' incorporates:
     *  ActionPort: '<S7>/Action Port'
     */
    DataAcquisiti_IfActionSubsystem(rtb_RM, &rtb_Merge, &rtb_Merge1,
      &DataAcquisition_RPM_P.IfActionSubsystem_f);

    /* End of Outputs for SubSystem: '<S4>/If Action Subsystem' */
  } else {
    /* Outputs for IfAction SubSystem: '<S4>/If Action Subsystem1' incorporates:
     *  ActionPort: '<S8>/Action Port'
     */
    DataAcquisit_IfActionSubsystem1(rtb_RM, &rtb_Merge, &rtb_Merge1,
      &DataAcquisition_RPM_P.IfActionSubsystem1_j);

    /* End of Outputs for SubSystem: '<S4>/If Action Subsystem1' */
  }

  /* End of If: '<S4>/If' */

  /* MATLABSystem: '<Root>/Right Dir PIN' */
  rtb_Merge1 = rt_roundd_snf(rtb_Merge1);
  if (rtb_Merge1 < 256.0) {
    if (rtb_Merge1 >= 0.0) {
      tmp = (uint8_T)rtb_Merge1;
    } else {
      tmp = 0U;
    }
  } else {
    tmp = MAX_uint8_T;
  }

  writeDigitalPin(43, tmp);

  /* End of MATLABSystem: '<Root>/Right Dir PIN' */

  /* MATLABSystem: '<Root>/Right PWM' */
  obj = &DataAcquisition_RPM_DW.obj_l;
  obj->PWMDriverObj.MW_PWM_HANDLE = MW_PWM_GetHandle(44UL);
  if (!(rtb_Merge <= 255.0)) {
    rtb_Merge = 255.0;
  }

  if (!(rtb_Merge >= 0.0)) {
    rtb_Merge = 0.0;
  }

  MW_PWM_SetDutyCycle(DataAcquisition_RPM_DW.obj_l.PWMDriverObj.MW_PWM_HANDLE,
                      rtb_Merge);

  /* End of MATLABSystem: '<Root>/Right PWM' */

  /* S-Function (encoder): '<Root>/S-Function Builder Left motor' */
  encoder_Outputs_wrapper(&DataAcquisition_RPM_B.SFunctionBuilderLeftmotor,
    &DataAcquisition_RPM_DW.SFunctionBuilderLeftmotor_DSTAT,
    &DataAcquisition_RPM_P.SFunctionBuilderLeftmotor_P1, 1,
    &DataAcquisition_RPM_P.SFunctionBuilderLeftmotor_P2, 1,
    &DataAcquisition_RPM_P.SFunctionBuilderLeftmotor_P3, 1);

  /* Update for S-Function (encoder): '<Root>/S-Function Builder Left motor' */

  /* S-Function "encoder_wrapper" Block: <Root>/S-Function Builder Left motor */
  encoder_Update_wrapper(&DataAcquisition_RPM_B.SFunctionBuilderLeftmotor,
    &DataAcquisition_RPM_DW.SFunctionBuilderLeftmotor_DSTAT,
    &DataAcquisition_RPM_P.SFunctionBuilderLeftmotor_P1, 1,
    &DataAcquisition_RPM_P.SFunctionBuilderLeftmotor_P2, 1,
    &DataAcquisition_RPM_P.SFunctionBuilderLeftmotor_P3, 1);

  /* Update absolute time for base rate */
  /* The "clockTick0" counts the number of times the code of this task has
   * been executed. The absolute time is the multiplication of "clockTick0"
   * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
   * overflow during the application lifespan selected.
   */
  DataAcquisition_RPM_M->Timing.t[0] =
    ((time_T)(++DataAcquisition_RPM_M->Timing.clockTick0)) *
    DataAcquisition_RPM_M->Timing.stepSize0;

  {
    /* Update absolute timer for sample time: [0.1s, 0.0s] */
    /* The "clockTick1" counts the number of times the code of this task has
     * been executed. The resolution of this integer timer is 0.1, which is the step size
     * of the task. Size of "clockTick1" ensures timer will not overflow during the
     * application lifespan selected.
     */
    DataAcquisition_RPM_M->Timing.clockTick1++;
  }
}

/* Model initialize function */
void DataAcquisition_RPM_initialize(void)
{
  /* Registration code */
  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&DataAcquisition_RPM_M->solverInfo,
                          &DataAcquisition_RPM_M->Timing.simTimeStep);
    rtsiSetTPtr(&DataAcquisition_RPM_M->solverInfo, &rtmGetTPtr
                (DataAcquisition_RPM_M));
    rtsiSetStepSizePtr(&DataAcquisition_RPM_M->solverInfo,
                       &DataAcquisition_RPM_M->Timing.stepSize0);
    rtsiSetErrorStatusPtr(&DataAcquisition_RPM_M->solverInfo,
                          (&rtmGetErrorStatus(DataAcquisition_RPM_M)));
    rtsiSetRTModelPtr(&DataAcquisition_RPM_M->solverInfo, DataAcquisition_RPM_M);
  }

  rtsiSetSimTimeStep(&DataAcquisition_RPM_M->solverInfo, MAJOR_TIME_STEP);
  rtsiSetSolverName(&DataAcquisition_RPM_M->solverInfo,"FixedStepDiscrete");
  rtmSetTPtr(DataAcquisition_RPM_M, &DataAcquisition_RPM_M->Timing.tArray[0]);
  DataAcquisition_RPM_M->Timing.stepSize0 = 0.1;

  {
    codertarget_arduinobase_inter_T *obj;

    /* Start for FromWorkspace: '<S1>/fromWS_Signal 1' */
    {
      static real_T pTimeValues0[] = { 0.0, 5.0, 5.0, 7.0, 7.0, 9.0, 9.0, 11.0,
        11.0, 13.0 } ;

      static real_T pDataValues0[] = { 0.0, 0.0, 75.0, 75.0, 0.0, 0.0, -75.0,
        -75.0, 0.0, 0.0 } ;

      DataAcquisition_RPM_DW.fromWS_Signal1_PWORK.TimePtr = (void *)
        pTimeValues0;
      DataAcquisition_RPM_DW.fromWS_Signal1_PWORK.DataPtr = (void *)
        pDataValues0;
      DataAcquisition_RPM_DW.fromWS_Signal1_IWORK.PrevIndex = 0;
    }

    /* Start for FromWorkspace: '<S2>/fromWS_Signal 1' */
    {
      static real_T pTimeValues0[] = { 0.0, 5.0, 5.0, 7.0, 7.0, 9.0, 9.0, 11.0,
        11.0, 13.0 } ;

      static real_T pDataValues0[] = { 0.0, 0.0, -75.0, -75.0, 0.0, 0.0, 75.0,
        75.0, 0.0, 0.0 } ;

      DataAcquisition_RPM_DW.fromWS_Signal1_PWORK_c.TimePtr = (void *)
        pTimeValues0;
      DataAcquisition_RPM_DW.fromWS_Signal1_PWORK_c.DataPtr = (void *)
        pDataValues0;
      DataAcquisition_RPM_DW.fromWS_Signal1_IWORK_d.PrevIndex = 0;
    }

    /* InitializeConditions for S-Function (encoder): '<Root>/S-Function Builder Left motor' */

    /* S-Function Block: <Root>/S-Function Builder Left motor */
    {
      real_T initVector[1] = { 0 };

      {
        int_T i1;
        for (i1=0; i1 < 1; i1++) {
          DataAcquisition_RPM_DW.SFunctionBuilderLeftmotor_DSTAT = initVector[0];
        }
      }
    }

    /* Start for MATLABSystem: '<Root>/Left Dir PIN' */
    DataAcquisition_RPM_DW.obj_j.matlabCodegenIsDeleted = false;
    DataAcquisition_RPM_DW.obj_j.isInitialized = 1L;
    digitalIOSetup(45, 1);
    DataAcquisition_RPM_DW.obj_j.isSetupComplete = true;

    /* Start for MATLABSystem: '<Root>/Left PWM' */
    DataAcquisition_RPM_DW.obj_h.matlabCodegenIsDeleted = false;
    obj = &DataAcquisition_RPM_DW.obj_h;
    DataAcquisition_RPM_DW.obj_h.isInitialized = 1L;
    obj->PWMDriverObj.MW_PWM_HANDLE = MW_PWM_Open(46UL, 0.0, 0.0);
    DataAcquisition_RPM_DW.obj_h.isSetupComplete = true;

    /* Start for MATLABSystem: '<Root>/Right Dir PIN' */
    DataAcquisition_RPM_DW.obj.matlabCodegenIsDeleted = false;
    DataAcquisition_RPM_DW.obj.isInitialized = 1L;
    digitalIOSetup(43, 1);
    DataAcquisition_RPM_DW.obj.isSetupComplete = true;

    /* Start for MATLABSystem: '<Root>/Right PWM' */
    DataAcquisition_RPM_DW.obj_l.matlabCodegenIsDeleted = false;
    obj = &DataAcquisition_RPM_DW.obj_l;
    DataAcquisition_RPM_DW.obj_l.isInitialized = 1L;
    obj->PWMDriverObj.MW_PWM_HANDLE = MW_PWM_Open(44UL, 0.0, 0.0);
    DataAcquisition_RPM_DW.obj_l.isSetupComplete = true;
  }
}

/* Model terminate function */
void DataAcquisition_RPM_terminate(void)
{
  codertarget_arduinobase_inter_T *obj;

  /* Terminate for MATLABSystem: '<Root>/Left Dir PIN' */
  if (!DataAcquisition_RPM_DW.obj_j.matlabCodegenIsDeleted) {
    DataAcquisition_RPM_DW.obj_j.matlabCodegenIsDeleted = true;
  }

  /* End of Terminate for MATLABSystem: '<Root>/Left Dir PIN' */

  /* Terminate for MATLABSystem: '<Root>/Left PWM' */
  obj = &DataAcquisition_RPM_DW.obj_h;
  if (!DataAcquisition_RPM_DW.obj_h.matlabCodegenIsDeleted) {
    DataAcquisition_RPM_DW.obj_h.matlabCodegenIsDeleted = true;
    if ((DataAcquisition_RPM_DW.obj_h.isInitialized == 1L) &&
        DataAcquisition_RPM_DW.obj_h.isSetupComplete) {
      obj->PWMDriverObj.MW_PWM_HANDLE = MW_PWM_GetHandle(46UL);
      MW_PWM_SetDutyCycle
        (DataAcquisition_RPM_DW.obj_h.PWMDriverObj.MW_PWM_HANDLE, 0.0);
      obj->PWMDriverObj.MW_PWM_HANDLE = MW_PWM_GetHandle(46UL);
      MW_PWM_Close(DataAcquisition_RPM_DW.obj_h.PWMDriverObj.MW_PWM_HANDLE);
    }
  }

  /* End of Terminate for MATLABSystem: '<Root>/Left PWM' */
  /* Terminate for MATLABSystem: '<Root>/Right Dir PIN' */
  if (!DataAcquisition_RPM_DW.obj.matlabCodegenIsDeleted) {
    DataAcquisition_RPM_DW.obj.matlabCodegenIsDeleted = true;
  }

  /* End of Terminate for MATLABSystem: '<Root>/Right Dir PIN' */

  /* Terminate for MATLABSystem: '<Root>/Right PWM' */
  obj = &DataAcquisition_RPM_DW.obj_l;
  if (!DataAcquisition_RPM_DW.obj_l.matlabCodegenIsDeleted) {
    DataAcquisition_RPM_DW.obj_l.matlabCodegenIsDeleted = true;
    if ((DataAcquisition_RPM_DW.obj_l.isInitialized == 1L) &&
        DataAcquisition_RPM_DW.obj_l.isSetupComplete) {
      obj->PWMDriverObj.MW_PWM_HANDLE = MW_PWM_GetHandle(44UL);
      MW_PWM_SetDutyCycle
        (DataAcquisition_RPM_DW.obj_l.PWMDriverObj.MW_PWM_HANDLE, 0.0);
      obj->PWMDriverObj.MW_PWM_HANDLE = MW_PWM_GetHandle(44UL);
      MW_PWM_Close(DataAcquisition_RPM_DW.obj_l.PWMDriverObj.MW_PWM_HANDLE);
    }
  }

  /* End of Terminate for MATLABSystem: '<Root>/Right PWM' */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */

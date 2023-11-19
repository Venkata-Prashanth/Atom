/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: DataAcquisition_RPM.h
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

#ifndef RTW_HEADER_DataAcquisition_RPM_h_
#define RTW_HEADER_DataAcquisition_RPM_h_
#ifndef DataAcquisition_RPM_COMMON_INCLUDES_
#define DataAcquisition_RPM_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#include "MW_arduino_digitalio.h"
#include "MW_PWM.h"
#endif                                /* DataAcquisition_RPM_COMMON_INCLUDES_ */

#include "DataAcquisition_RPM_types.h"
#include <math.h>
#include <stddef.h>
#include "MW_target_hardware_resources.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    ((rtm)->errorStatus = (val))
#endif

#ifndef rtmGetT
#define rtmGetT(rtm)                   (rtmGetTPtr((rtm))[0])
#endif

#ifndef rtmGetTPtr
#define rtmGetTPtr(rtm)                ((rtm)->Timing.t)
#endif

/* Block signals (default storage) */
typedef struct {
  int16_T SFunctionBuilderLeftmotor;/* '<Root>/S-Function Builder Left motor' */
} B_DataAcquisition_RPM_T;

/* Block states (default storage) for system '<Root>' */
typedef struct {
  codertarget_arduinobase_block_T obj; /* '<Root>/Right Dir PIN' */
  codertarget_arduinobase_block_T obj_j;/* '<Root>/Left Dir PIN' */
  codertarget_arduinobase_inter_T obj_l;/* '<Root>/Right PWM' */
  codertarget_arduinobase_inter_T obj_h;/* '<Root>/Left PWM' */
  real_T SFunctionBuilderLeftmotor_DSTAT;
                                    /* '<Root>/S-Function Builder Left motor' */
  struct {
    void *TimePtr;
    void *DataPtr;
    void *RSimInfoPtr;
  } fromWS_Signal1_PWORK;              /* '<S1>/fromWS_Signal 1' */

  struct {
    void *TimePtr;
    void *DataPtr;
    void *RSimInfoPtr;
  } fromWS_Signal1_PWORK_c;            /* '<S2>/fromWS_Signal 1' */

  struct {
    int_T PrevIndex;
  } fromWS_Signal1_IWORK;              /* '<S1>/fromWS_Signal 1' */

  struct {
    int_T PrevIndex;
  } fromWS_Signal1_IWORK_d;            /* '<S2>/fromWS_Signal 1' */
} DW_DataAcquisition_RPM_T;

/* Parameters for system: '<S3>/If Action Subsystem' */
struct P_IfActionSubsystem_DataAcqui_T_ {
  real_T Constant_Value;               /* Expression: 0
                                        * Referenced by: '<S5>/Constant'
                                        */
};

/* Parameters for system: '<S3>/If Action Subsystem1' */
struct P_IfActionSubsystem1_DataAcqu_T_ {
  real_T Constant_Value;               /* Expression: 1
                                        * Referenced by: '<S6>/Constant'
                                        */
  real_T Gain_Gain;                    /* Expression: -1
                                        * Referenced by: '<S6>/Gain'
                                        */
};

/* Parameters (default storage) */
struct P_DataAcquisition_RPM_T_ {
  int8_T SFunctionBuilderLeftmotor_P1; /* Expression: int8(0)
                                        * Referenced by: '<Root>/S-Function Builder Left motor'
                                        */
  int8_T SFunctionBuilderLeftmotor_P2; /* Expression: int8(18)
                                        * Referenced by: '<Root>/S-Function Builder Left motor'
                                        */
  int8_T SFunctionBuilderLeftmotor_P3; /* Expression: int8(19)
                                        * Referenced by: '<Root>/S-Function Builder Left motor'
                                        */
  P_IfActionSubsystem1_DataAcqu_T IfActionSubsystem1_j;/* '<S4>/If Action Subsystem1' */
  P_IfActionSubsystem_DataAcqui_T IfActionSubsystem_f;/* '<S4>/If Action Subsystem' */
  P_IfActionSubsystem1_DataAcqu_T IfActionSubsystem1;/* '<S3>/If Action Subsystem1' */
  P_IfActionSubsystem_DataAcqui_T IfActionSubsystem;/* '<S3>/If Action Subsystem' */
};

/* Real-time Model Data Structure */
struct tag_RTM_DataAcquisition_RPM_T {
  const char_T *errorStatus;
  RTWSolverInfo solverInfo;

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
    time_T *t;
    time_T tArray[2];
  } Timing;
};

/* Block parameters (default storage) */
extern P_DataAcquisition_RPM_T DataAcquisition_RPM_P;

/* Block signals (default storage) */
extern B_DataAcquisition_RPM_T DataAcquisition_RPM_B;

/* Block states (default storage) */
extern DW_DataAcquisition_RPM_T DataAcquisition_RPM_DW;

/* Model entry point functions */
extern void DataAcquisition_RPM_initialize(void);
extern void DataAcquisition_RPM_step(void);
extern void DataAcquisition_RPM_terminate(void);

/* Real-time Model object */
extern RT_MODEL_DataAcquisition_RPM_T *const DataAcquisition_RPM_M;
extern volatile boolean_T stopRequested;
extern volatile boolean_T runModel;

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<Root>/Constant2' : Unused code path elimination
 * Block '<Root>/Display5' : Unused code path elimination
 * Block '<Root>/Divide' : Unused code path elimination
 * Block '<Root>/Gain' : Unused code path elimination
 * Block '<Root>/Sum' : Unused code path elimination
 * Block '<Root>/Unit Delay4' : Unused code path elimination
 * Block '<Root>/Zero-Order Hold4' : Unused code path elimination
 */

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
 * '<Root>' : 'DataAcquisition_RPM'
 * '<S1>'   : 'DataAcquisition_RPM/Signal Editor Left motor'
 * '<S2>'   : 'DataAcquisition_RPM/Signal Editor Right motor'
 * '<S3>'   : 'DataAcquisition_RPM/Subsystem'
 * '<S4>'   : 'DataAcquisition_RPM/Subsystem1'
 * '<S5>'   : 'DataAcquisition_RPM/Subsystem/If Action Subsystem'
 * '<S6>'   : 'DataAcquisition_RPM/Subsystem/If Action Subsystem1'
 * '<S7>'   : 'DataAcquisition_RPM/Subsystem1/If Action Subsystem'
 * '<S8>'   : 'DataAcquisition_RPM/Subsystem1/If Action Subsystem1'
 */
#endif                                 /* RTW_HEADER_DataAcquisition_RPM_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */

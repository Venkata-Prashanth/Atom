/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: DataAcquisition_RPM_private.h
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

#ifndef RTW_HEADER_DataAcquisition_RPM_private_h_
#define RTW_HEADER_DataAcquisition_RPM_private_h_
#include "rtwtypes.h"
#include "DataAcquisition_RPM.h"
#include "DataAcquisition_RPM_types.h"

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

/* Used by FromWorkspace Block: '<S1>/fromWS_Signal 1' */
#ifndef rtInterpolate
# define rtInterpolate(v1,v2,f1,f2)    (((v1)==(v2))?((double)(v1)): (((f1)*((double)(v1)))+((f2)*((double)(v2)))))
#endif

#ifndef rtRound
# define rtRound(v)                    ( ((v) >= 0) ? floor((v) + 0.5) : ceil((v) - 0.5) )
#endif

#ifdef __cplusplus
#define SFB_EXTERN_C                   extern "C"
#else
#define SFB_EXTERN_C                   extern
#endif

SFB_EXTERN_C void encoder_Start_wrapper(real_T *xD,
  const int8_T *enc, const int_T p_width0,
  const int8_T *pinA, const int_T p_width1,
  const int8_T *pinB, const int_T p_width2);
SFB_EXTERN_C void encoder_Outputs_wrapper(int16_T *pos,
  const real_T *xD,
  const int8_T *enc, const int_T p_width0,
  const int8_T *pinA, const int_T p_width1,
  const int8_T *pinB, const int_T p_width2);
SFB_EXTERN_C void encoder_Update_wrapper(int16_T *pos,
  real_T *xD,
  const int8_T *enc, const int_T p_width0,
  const int8_T *pinA, const int_T p_width1,
  const int8_T *pinB, const int_T p_width2);
SFB_EXTERN_C void encoder_Terminate_wrapper(real_T *xD,
  const int8_T *enc, const int_T p_width0,
  const int8_T *pinA, const int_T p_width1,
  const int8_T *pinB, const int_T p_width2);

#undef SFB_EXTERN_C

extern real_T rt_roundd_snf(real_T u);
extern void DataAcquisiti_IfActionSubsystem(real_T rtu_SignalIN, real_T
  *rty_Out1, real_T *rty_Out2, P_IfActionSubsystem_DataAcqui_T *localP);
extern void DataAcquisit_IfActionSubsystem1(real_T rtu_SignalIN, real_T
  *rty_Out1, real_T *rty_Out2, P_IfActionSubsystem1_DataAcqu_T *localP);

#endif                           /* RTW_HEADER_DataAcquisition_RPM_private_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */

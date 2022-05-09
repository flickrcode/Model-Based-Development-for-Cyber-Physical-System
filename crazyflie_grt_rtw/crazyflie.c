/*
 * crazyflie.c
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "crazyflie".
 *
 * Model version              : 6.18
 * Simulink Coder version : 9.4 (R2020b) 29-Jul-2020
 * C source code generated on : Tue May 25 20:40:19 2021
 *
 * Target selection: grt.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: ARM Compatible->ARM Cortex
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "crazyflie.h"
#include "crazyflie_private.h"

/* Block states (default storage) */
DW_crazyflie_T crazyflie_DW;

/* External inputs (root inport signals with default storage) */
ExtU_crazyflie_T crazyflie_U;

/* External outputs (root outports fed by signals with default storage) */
ExtY_crazyflie_T crazyflie_Y;

/* Real-time model */
static RT_MODEL_crazyflie_T crazyflie_M_;
RT_MODEL_crazyflie_T *const crazyflie_M = &crazyflie_M_;
real_T rt_atan2d_snf(real_T u0, real_T u1)
{
  real_T y;
  int32_T u0_0;
  int32_T u1_0;
  if (rtIsNaN(u0) || rtIsNaN(u1)) {
    y = (rtNaN);
  } else if (rtIsInf(u0) && rtIsInf(u1)) {
    if (u0 > 0.0) {
      u0_0 = 1;
    } else {
      u0_0 = -1;
    }

    if (u1 > 0.0) {
      u1_0 = 1;
    } else {
      u1_0 = -1;
    }

    y = atan2(u0_0, u1_0);
  } else if (u1 == 0.0) {
    if (u0 > 0.0) {
      y = RT_PI / 2.0;
    } else if (u0 < 0.0) {
      y = -(RT_PI / 2.0);
    } else {
      y = 0.0;
    }
  } else {
    y = atan2(u0, u1);
  }

  return y;
}

/* Model step function */
void crazyflie_step(void)
{
  /* local block i/o variables */
  real_T rtb_filtx_a;
  real_T scale_0[5];
  real_T rtb_Saturation[4];
  real_T tmp[4];
  real_T absxk;
  real_T scale;
  real_T t;
  real_T y;
  int32_T i;
  int32_T i_0;

  /* MATLAB Function: '<Root>/MATLAB Function1' incorporates:
   *  Inport: '<Root>/Acc_y'
   *  Inport: '<Root>/Acc_z'
   */
  /* MATLAB Function 'MATLAB Function1': '<S1>:1' */
  /* '<S1>:1:3' phi = atan2d(Ay,Az); */
  /* '<S1>:1:4' theta = atan2d(-Ax,norm([Ay Az])); */
  scale = 3.3121686421112381E-170;
  absxk = fabs(crazyflie_U.Acc_y);
  if (absxk > 3.3121686421112381E-170) {
    y = 1.0;
    scale = absxk;
  } else {
    t = absxk / 3.3121686421112381E-170;
    y = t * t;
  }

  absxk = fabs(crazyflie_U.Acc_z);
  if (absxk > scale) {
    t = scale / absxk;
    y = y * t * t + 1.0;
    scale = absxk;
  } else {
    t = absxk / scale;
    y += t * t;
  }

  y = scale * sqrt(y);

  /* Sum: '<Root>/Sum3' incorporates:
   *  Delay: '<Root>/Delay1'
   *  Gain: '<Root>/Gain3'
   *  Gain: '<Root>/Gain5'
   *  Gain: '<Root>/Gain8'
   *  Inport: '<Root>/Acc_y'
   *  Inport: '<Root>/Acc_z'
   *  Inport: '<Root>/Gyro_x'
   *  MATLAB Function: '<Root>/MATLAB Function1'
   *  Sum: '<Root>/Sum'
   */
  scale = (0.0001 * crazyflie_U.Gyro_x + crazyflie_DW.Delay1_DSTATE) * 0.98 +
    57.295779513082323 * rt_atan2d_snf(crazyflie_U.Acc_y, crazyflie_U.Acc_z) *
    0.02;

  /* Sum: '<Root>/Sum2' incorporates:
   *  Delay: '<Root>/Delay2'
   *  Gain: '<Root>/Gain1'
   *  Gain: '<Root>/Gain2'
   *  Gain: '<Root>/Gain6'
   *  Inport: '<Root>/Acc_x'
   *  Inport: '<Root>/Gyro_y'
   *  MATLAB Function: '<Root>/MATLAB Function1'
   *  Sum: '<Root>/Sum1'
   */
  rtb_filtx_a = (0.0001 * crazyflie_U.Gyro_y + crazyflie_DW.Delay2_DSTATE) *
    0.98 + 57.295779513082323 * rt_atan2d_snf(-crazyflie_U.Acc_x, y) * 0.02;

  /* SignalConversion generated from: '<Root>/Gain4' incorporates:
   *  Inport: '<Root>/Gyro_x'
   *  Inport: '<Root>/Gyro_y'
   *  Inport: '<Root>/Gyro_z'
   *  Inport: '<Root>/Ref_Pitch'
   *  Inport: '<Root>/Ref_Roll'
   *  Sum: '<Root>/Sum5'
   */
  scale_0[0] = scale - crazyflie_U.Ref_Roll;
  scale_0[1] = rtb_filtx_a - crazyflie_U.Ref_Pitch;
  scale_0[2] = crazyflie_U.Gyro_x;
  scale_0[3] = crazyflie_U.Gyro_y;
  scale_0[4] = crazyflie_U.Gyro_z;
  for (i = 0; i < 4; i++) {
    /* Gain: '<Root>/Gain4' */
    tmp[i] = 0.0;
    for (i_0 = 0; i_0 < 5; i_0++) {
      tmp[i] += crazyflie_ConstP.Gain4_Gain[(i_0 << 2) + i] * scale_0[i_0];
    }

    /* End of Gain: '<Root>/Gain4' */

    /* Saturate: '<Root>/Saturation' incorporates:
     *  Gain: '<Root>/Thrust converter'
     *  Inport: '<Root>/Base_Thrust'
     *  Sum: '<Root>/Sum6'
     */
    absxk = 445368.67142371729 * tmp[i] + crazyflie_U.Base_Thrust;
    if (absxk > 65536.0) {
      rtb_Saturation[i] = 65536.0;
    } else if (absxk < 0.0) {
      rtb_Saturation[i] = 0.0;
    } else {
      rtb_Saturation[i] = absxk;
    }

    /* End of Saturate: '<Root>/Saturation' */
  }

  /* DataTypeConversion: '<Root>/ToUint16' */
  if (rtb_Saturation[0] < 65536.0) {
    /* Outport: '<Root>/Motor_1' */
    crazyflie_Y.Motor_1 = (uint16_T)rtb_Saturation[0];
  } else {
    /* Outport: '<Root>/Motor_1' */
    crazyflie_Y.Motor_1 = MAX_uint16_T;
  }

  /* End of DataTypeConversion: '<Root>/ToUint16' */

  /* DataTypeConversion: '<Root>/ToUint16_1' */
  if (rtb_Saturation[1] < 65536.0) {
    /* Outport: '<Root>/Motor_2' */
    crazyflie_Y.Motor_2 = (uint16_T)rtb_Saturation[1];
  } else {
    /* Outport: '<Root>/Motor_2' */
    crazyflie_Y.Motor_2 = MAX_uint16_T;
  }

  /* End of DataTypeConversion: '<Root>/ToUint16_1' */

  /* DataTypeConversion: '<Root>/ToUint16_2' */
  if (rtb_Saturation[2] < 65536.0) {
    /* Outport: '<Root>/Motor_3' */
    crazyflie_Y.Motor_3 = (uint16_T)rtb_Saturation[2];
  } else {
    /* Outport: '<Root>/Motor_3' */
    crazyflie_Y.Motor_3 = MAX_uint16_T;
  }

  /* End of DataTypeConversion: '<Root>/ToUint16_2' */

  /* DataTypeConversion: '<Root>/ToUint16_3' */
  if (rtb_Saturation[3] < 65536.0) {
    /* Outport: '<Root>/Motor_4' */
    crazyflie_Y.Motor_4 = (uint16_T)rtb_Saturation[3];
  } else {
    /* Outport: '<Root>/Motor_4' */
    crazyflie_Y.Motor_4 = MAX_uint16_T;
  }

  /* End of DataTypeConversion: '<Root>/ToUint16_3' */

  /* Outport: '<Root>/Log1' incorporates:
   *  Inport: '<Root>/Ref_Pitch'
   *  Inport: '<Root>/Ref_Roll'
   */
  crazyflie_Y.Log1[0] = crazyflie_U.Ref_Roll;
  crazyflie_Y.Log1[1] = crazyflie_U.Ref_Pitch;

  /* Update for Delay: '<Root>/Delay1' */
  crazyflie_DW.Delay1_DSTATE = scale;

  /* Update for Delay: '<Root>/Delay2' */
  crazyflie_DW.Delay2_DSTATE = rtb_filtx_a;

  /* Matfile logging */
  rt_UpdateTXYLogVars(crazyflie_M->rtwLogInfo, (&crazyflie_M->Timing.taskTime0));

  /* signal main to stop simulation */
  {                                    /* Sample time: [0.0001s, 0.0s] */
    if ((rtmGetTFinal(crazyflie_M)!=-1) &&
        !((rtmGetTFinal(crazyflie_M)-crazyflie_M->Timing.taskTime0) >
          crazyflie_M->Timing.taskTime0 * (DBL_EPSILON))) {
      rtmSetErrorStatus(crazyflie_M, "Simulation finished");
    }
  }

  /* Update absolute time for base rate */
  /* The "clockTick0" counts the number of times the code of this task has
   * been executed. The absolute time is the multiplication of "clockTick0"
   * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
   * overflow during the application lifespan selected.
   * Timer of this task consists of two 32 bit unsigned integers.
   * The two integers represent the low bits Timing.clockTick0 and the high bits
   * Timing.clockTickH0. When the low bit overflows to 0, the high bits increment.
   */
  if (!(++crazyflie_M->Timing.clockTick0)) {
    ++crazyflie_M->Timing.clockTickH0;
  }

  crazyflie_M->Timing.taskTime0 = crazyflie_M->Timing.clockTick0 *
    crazyflie_M->Timing.stepSize0 + crazyflie_M->Timing.clockTickH0 *
    crazyflie_M->Timing.stepSize0 * 4294967296.0;
}

/* Model initialize function */
void crazyflie_initialize(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* initialize real-time model */
  (void) memset((void *)crazyflie_M, 0,
                sizeof(RT_MODEL_crazyflie_T));
  rtmSetTFinal(crazyflie_M, 160.0);
  crazyflie_M->Timing.stepSize0 = 0.0001;

  /* Setup for data logging */
  {
    static RTWLogInfo rt_DataLoggingInfo;
    rt_DataLoggingInfo.loggingInterval = NULL;
    crazyflie_M->rtwLogInfo = &rt_DataLoggingInfo;
  }

  /* Setup for data logging */
  {
    rtliSetLogXSignalInfo(crazyflie_M->rtwLogInfo, (NULL));
    rtliSetLogXSignalPtrs(crazyflie_M->rtwLogInfo, (NULL));
    rtliSetLogT(crazyflie_M->rtwLogInfo, "tout");
    rtliSetLogX(crazyflie_M->rtwLogInfo, "");
    rtliSetLogXFinal(crazyflie_M->rtwLogInfo, "");
    rtliSetLogVarNameModifier(crazyflie_M->rtwLogInfo, "rt_");
    rtliSetLogFormat(crazyflie_M->rtwLogInfo, 4);
    rtliSetLogMaxRows(crazyflie_M->rtwLogInfo, 0);
    rtliSetLogDecimation(crazyflie_M->rtwLogInfo, 1);
    rtliSetLogY(crazyflie_M->rtwLogInfo, "");
    rtliSetLogYSignalInfo(crazyflie_M->rtwLogInfo, (NULL));
    rtliSetLogYSignalPtrs(crazyflie_M->rtwLogInfo, (NULL));
  }

  /* states (dwork) */
  (void) memset((void *)&crazyflie_DW, 0,
                sizeof(DW_crazyflie_T));

  /* external inputs */
  (void)memset(&crazyflie_U, 0, sizeof(ExtU_crazyflie_T));

  /* external outputs */
  (void) memset((void *)&crazyflie_Y, 0,
                sizeof(ExtY_crazyflie_T));

  /* Matfile logging */
  rt_StartDataLoggingWithStartTime(crazyflie_M->rtwLogInfo, 0.0, rtmGetTFinal
    (crazyflie_M), crazyflie_M->Timing.stepSize0, (&rtmGetErrorStatus
    (crazyflie_M)));

  /* InitializeConditions for Delay: '<Root>/Delay1' */
  crazyflie_DW.Delay1_DSTATE = 0.0;

  /* InitializeConditions for Delay: '<Root>/Delay2' */
  crazyflie_DW.Delay2_DSTATE = 0.0;

  /* ConstCode for Outport: '<Root>/Log2' */
  crazyflie_Y.Log2 = 0.0;

  /* ConstCode for Outport: '<Root>/Log3' */
  crazyflie_Y.Log3 = 0.0;

  /* ConstCode for Outport: '<Root>/Log4' */
  crazyflie_Y.Log4 = 0.0;

  /* ConstCode for Outport: '<Root>/Log5' */
  crazyflie_Y.Log5 = 0.0;

  /* ConstCode for Outport: '<Root>/Log6' */
  crazyflie_Y.Log6 = 0.0;
}

/* Model terminate function */
void crazyflie_terminate(void)
{
  /* (no terminate code required) */
}

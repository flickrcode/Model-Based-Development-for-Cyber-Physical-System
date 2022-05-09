/*
 * crazyflie.h
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

#ifndef RTW_HEADER_crazyflie_h_
#define RTW_HEADER_crazyflie_h_
#include <math.h>
#include <string.h>
#include <float.h>
#include <stddef.h>
#ifndef crazyflie_COMMON_INCLUDES_
#define crazyflie_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#include "rt_logging.h"
#endif                                 /* crazyflie_COMMON_INCLUDES_ */

#include "crazyflie_types.h"

/* Shared type includes */
#include "multiword_types.h"
#include "rt_defines.h"
#include "rt_nonfinite.h"
#include "rtGetInf.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetFinalTime
#define rtmGetFinalTime(rtm)           ((rtm)->Timing.tFinal)
#endif

#ifndef rtmGetRTWLogInfo
#define rtmGetRTWLogInfo(rtm)          ((rtm)->rtwLogInfo)
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
#define rtmGetT(rtm)                   ((rtm)->Timing.taskTime0)
#endif

#ifndef rtmGetTFinal
#define rtmGetTFinal(rtm)              ((rtm)->Timing.tFinal)
#endif

#ifndef rtmGetTPtr
#define rtmGetTPtr(rtm)                (&(rtm)->Timing.taskTime0)
#endif

/* Block states (default storage) for system '<Root>' */
typedef struct {
  real_T Delay1_DSTATE;                /* '<Root>/Delay1' */
  real_T Delay2_DSTATE;                /* '<Root>/Delay2' */
} DW_crazyflie_T;

/* Constant parameters (default storage) */
typedef struct {
  /* Expression: -K
   * Referenced by: '<Root>/Gain4'
   */
  real_T Gain4_Gain[20];
} ConstP_crazyflie_T;

/* External inputs (root inport signals with default storage) */
typedef struct {
  real_T Base_Thrust;                  /* '<Root>/Base_Thrust' */
  real_T Ref_Roll;                     /* '<Root>/Ref_Roll' */
  real_T Ref_Pitch;                    /* '<Root>/Ref_Pitch' */
  real_T Ref_YawRate;                  /* '<Root>/Ref_YawRate' */
  int16_T Flow_x;                      /* '<Root>/Flow_x' */
  int16_T Flow_y;                      /* '<Root>/Flow_y' */
  real_T Acc_x;                        /* '<Root>/Acc_x' */
  real_T Acc_y;                        /* '<Root>/Acc_y' */
  real_T Acc_z;                        /* '<Root>/Acc_z' */
  real_T Gyro_x;                       /* '<Root>/Gyro_x' */
  real_T Gyro_y;                       /* '<Root>/Gyro_y' */
  real_T Gyro_z;                       /* '<Root>/Gyro_z' */
} ExtU_crazyflie_T;

/* External outputs (root outports fed by signals with default storage) */
typedef struct {
  uint16_T Motor_1;                    /* '<Root>/Motor_1' */
  uint16_T Motor_2;                    /* '<Root>/Motor_2' */
  uint16_T Motor_3;                    /* '<Root>/Motor_3' */
  uint16_T Motor_4;                    /* '<Root>/Motor_4' */
  real_T Log1[2];                      /* '<Root>/Log1' */
  real_T Log2;                         /* '<Root>/Log2' */
  real_T Log3;                         /* '<Root>/Log3' */
  real_T Log4;                         /* '<Root>/Log4' */
  real_T Log5;                         /* '<Root>/Log5' */
  real_T Log6;                         /* '<Root>/Log6' */
} ExtY_crazyflie_T;

/* Real-time Model Data Structure */
struct tag_RTM_crazyflie_T {
  const char_T *errorStatus;
  RTWLogInfo *rtwLogInfo;

  /*
   * Timing:
   * The following substructure contains information regarding
   * the timing information for the model.
   */
  struct {
    time_T taskTime0;
    uint32_T clockTick0;
    uint32_T clockTickH0;
    time_T stepSize0;
    time_T tFinal;
    boolean_T stopRequestedFlag;
  } Timing;
};

/* Block states (default storage) */
extern DW_crazyflie_T crazyflie_DW;

/* External inputs (root inport signals with default storage) */
extern ExtU_crazyflie_T crazyflie_U;

/* External outputs (root outports fed by signals with default storage) */
extern ExtY_crazyflie_T crazyflie_Y;

/* Constant parameters (default storage) */
extern const ConstP_crazyflie_T crazyflie_ConstP;

/* Model entry point functions */
extern void crazyflie_initialize(void);
extern void crazyflie_step(void);
extern void crazyflie_terminate(void);

/* Real-time Model object */
extern RT_MODEL_crazyflie_T *const crazyflie_M;

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<Root>/ToDouble' : Eliminate redundant data type conversion
 * Block '<Root>/ToDouble1' : Eliminate redundant data type conversion
 * Block '<Root>/ToDouble2' : Eliminate redundant data type conversion
 * Block '<Root>/ToDouble3' : Eliminate redundant data type conversion
 * Block '<Root>/ToDouble4' : Eliminate redundant data type conversion
 * Block '<Root>/ToDouble5' : Eliminate redundant data type conversion
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
 * '<Root>' : 'crazyflie'
 * '<S1>'   : 'crazyflie/MATLAB Function1'
 */
#endif                                 /* RTW_HEADER_crazyflie_h_ */

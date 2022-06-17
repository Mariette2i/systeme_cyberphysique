

/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: Asserv.h
 *
 * Code generated for Simulink model 'Asserv'.
 *
 * Model version                  : 1.7
 * Simulink Coder version         : 9.4 (R2020b) 29-Jul-2020
 * C/C++ source code generated on : Wed Jun 15 15:09:40 2022
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Atmel->AVR (8-bit)
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. RAM efficiency
 * Validation result: Not run
 */

#ifndef RTW_HEADER_Asserv_h_
#define RTW_HEADER_Asserv_h_
#include "rtwtypes.h"
#ifndef Asserv_COMMON_INCLUDES_
#define Asserv_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#endif                                 /* Asserv_COMMON_INCLUDES_ */

/* Model Code Variants */

/* Macros for accessing real-time model data structure */
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

/* Forward declaration for rtModel */
typedef struct tag_RTM RT_MODEL;

/* Block signals and states (default storage) for system '<Root>' */
typedef struct {
  real_T Sum7;                         /* '<S3>/Sum7' */
  real_T Sum3;                         /* '<S2>/Sum3' */
} DW;

/* Continuous states (default storage) */
typedef struct {
  real_T Integrator_CSTATE;            /* '<S3>/Integrator' */
  real_T Integrator_CSTATE_n;          /* '<S2>/Integrator' */
} X;

/* State derivatives (default storage) */
typedef struct {
  real_T Integrator_CSTATE;            /* '<S3>/Integrator' */
  real_T Integrator_CSTATE_n;          /* '<S2>/Integrator' */
} XDot;

/* State disabled  */
typedef struct {
  boolean_T Integrator_CSTATE;         /* '<S3>/Integrator' */
  boolean_T Integrator_CSTATE_n;       /* '<S2>/Integrator' */
} XDis;

#ifndef ODE1_INTG
#define ODE1_INTG

/* ODE1 Integration Data */
typedef struct {
  real_T *f[1];                        /* derivatives */
} ODE1_IntgData;

#endif

/* External inputs (root inport signals with default storage) */
typedef struct {
  real_T vg;                           /* '<Root>/vg' */
  real_T vg_p;                         /* '<Root>/vg+' */
  real_T vd;                           /* '<Root>/vd+' */
  real_T vd_p;                         /* '<Root>/vd' */
} ExtU;

/* External outputs (root outports fed by signals with default storage) */
typedef struct {
  real_T Ug;                           /* '<Root>/Ug' */
  real_T Ud;                           /* '<Root>/Ud' */
} ExtY;

/* Parameters (default storage) */
struct P_ {
  real_T Integrator_IC;                /* Expression: 0
                                        * Referenced by: '<S3>/Integrator'
                                        */
  real_T Saturation1_UpperSat;         /* Expression: 9
                                        * Referenced by: '<S3>/Saturation1'
                                        */
  real_T Saturation1_LowerSat;         /* Expression: -9
                                        * Referenced by: '<S3>/Saturation1'
                                        */
  real_T Integrator_IC_p;              /* Expression: 0
                                        * Referenced by: '<S2>/Integrator'
                                        */
  real_T Saturation_UpperSat;          /* Expression: 9
                                        * Referenced by: '<S2>/Saturation'
                                        */
  real_T Saturation_LowerSat;          /* Expression: -9
                                        * Referenced by: '<S2>/Saturation'
                                        */
};

/* Parameters (default storage) */
typedef struct P_ P;

/* Real-time Model Data Structure */
struct tag_RTM {
  const char_T *errorStatus;
  RTWSolverInfo solverInfo;
  X *contStates;
  int_T *periodicContStateIndices;
  real_T *periodicContStateRanges;
  real_T *derivs;
  boolean_T *contStateDisabled;
  boolean_T zCCacheNeedsReset;
  boolean_T derivCacheNeedsReset;
  boolean_T CTOutputIncnstWithState;
  real_T odeF[1][2];
  ODE1_IntgData intgData;

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
extern P rtP;

/* Continuous states (default storage) */
extern X rtX;

/* Block signals and states (default storage) */
extern DW rtDW;

/* External inputs (root inport signals with default storage) */
extern ExtU rtU;

/* External outputs (root outports fed by signals with default storage) */
extern ExtY rtY;

/*
 * Exported Global Parameters
 *
 * Note: Exported global parameters are tunable parameters with an exported
 * global storage class designation.  Code generation will declare the memory for
 * these parameters and exports their symbols.
 *
 */
extern real_T Kb;                      /* Variable: Kb
                                        * Referenced by:
                                        *   '<S2>/Gain2'
                                        *   '<S3>/Gain2'
                                        */
extern real_T Ki;                      /* Variable: Ki
                                        * Referenced by:
                                        *   '<S2>/Gain1'
                                        *   '<S3>/Gain1'
                                        */
extern real_T Kx;                      /* Variable: Kx
                                        * Referenced by:
                                        *   '<S2>/Gain'
                                        *   '<S3>/Gain'
                                        */

/* Model entry point functions */
extern void Asserv_initialize(void);
extern void Asserv_step(void);

/* Real-time Model object */
extern RT_MODEL *const rtM;

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Note that this particular code originates from a subsystem build,
 * and has its own system numbers different from the parent model.
 * Refer to the system hierarchy for this subsystem below, and use the
 * MATLAB hilite_system command to trace the generated code back
 * to the parent model.  For example,
 *
 * hilite_system('bigModele/Asserv global')    - opens subsystem bigModele/Asserv global
 * hilite_system('bigModele/Asserv global/Kp') - opens and selects block Kp
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'bigModele'
 * '<S1>'   : 'bigModele/Asserv global'
 * '<S2>'   : 'bigModele/Asserv global/asserv vd'
 * '<S3>'   : 'bigModele/Asserv global/asserv vg'
 */
#endif                                 /* RTW_HEADER_Asserv_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */

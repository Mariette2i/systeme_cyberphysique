

/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: Asserv.c
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

#include "asserv.h"

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

/* Exported block parameters */
real_T Kb = 500.00000000000574;        /* Variable: Kb
                                        * Referenced by:
                                        *   '<S2>/Gain2'
                                        *   '<S3>/Gain2'
                                        */
real_T Ki = -0.39999999999999541;      /* Variable: Ki
                                        * Referenced by:
                                        *   '<S2>/Gain1'
                                        *   '<S3>/Gain1'
                                        */
real_T Kx = 0.00799999999999983;       /* Variable: Kx
                                        * Referenced by:
                                        *   '<S2>/Gain'
                                        *   '<S3>/Gain'
                                        */

/* Continuous states */
X rtX;

/* Block signals and states (default storage) */
DW rtDW;

/* External inputs (root inport signals with default storage) */
ExtU rtU;

/* External outputs (root outports fed by signals with default storage) */
ExtY rtY;

/* Real-time model */
static RT_MODEL rtM_;
RT_MODEL *const rtM = &rtM_;

/* private model entry point functions */
extern void Asserv_derivatives(void);

/*
 * This function updates continuous states using the ODE1 fixed-step
 * solver algorithm
 */
static void rt_ertODEUpdateContinuousStates(RTWSolverInfo *si )
{
  time_T tnew = rtsiGetSolverStopTime(si);
  time_T h = rtsiGetStepSize(si);
  real_T *x = rtsiGetContStates(si);
  ODE1_IntgData *id = (ODE1_IntgData *)rtsiGetSolverData(si);
  real_T *f0 = id->f[0];
  int_T i;
  int_T nXc = 2;
  rtsiSetSimTimeStep(si,MINOR_TIME_STEP);
  rtsiSetdX(si, f0);
  Asserv_derivatives();
  rtsiSetT(si, tnew);
  for (i = 0; i < nXc; ++i) {
    x[i] += h * f0[i];
  }

  rtsiSetSimTimeStep(si,MAJOR_TIME_STEP);
}

/* Model step function */
void Asserv_step(void)
{
  real_T rtb_Saturation;
  real_T rtb_Sum1;
  if (rtmIsMajorTimeStep(rtM)) {
    /* set solver stop time */
    rtsiSetSolverStopTime(&rtM->solverInfo,((rtM->Timing.clockTick0+1)*
      rtM->Timing.stepSize0));
  }                                    /* end MajorTimeStep */

  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep(rtM)) {
    rtM->Timing.t[0] = rtsiGetT(&rtM->solverInfo);
  }

  /* Sum: '<S3>/Sum1' incorporates:
   *  Gain: '<S3>/Gain'
   *  Gain: '<S3>/Gain1'
   *  Inport: '<Root>/vg'
   *  Integrator: '<S3>/Integrator'
   */
  rtb_Saturation = (0.0 - Ki * rtX.Integrator_CSTATE) - Kx * rtU.vg;

  /* Saturate: '<S3>/Saturation1' */
  if (rtb_Saturation > rtP.Saturation1_UpperSat) {
    rtb_Sum1 = rtP.Saturation1_UpperSat;
  } else if (rtb_Saturation < rtP.Saturation1_LowerSat) {
    rtb_Sum1 = rtP.Saturation1_LowerSat;
  } else {
    rtb_Sum1 = rtb_Saturation;
  }

  /* End of Saturate: '<S3>/Saturation1' */

  /* Sum: '<S3>/Sum7' incorporates:
   *  Gain: '<S3>/Gain2'
   *  Inport: '<Root>/vg'
   *  Inport: '<Root>/vg+'
   *  Sum: '<S3>/Sum'
   *  Sum: '<S3>/Sum2'
   */
  rtDW.Sum7 = (rtb_Sum1 - rtb_Saturation) * Kb + (rtU.vg_p - rtU.vg);

  /* Outport: '<Root>/Ug' */
  rtY.Ug = rtb_Sum1;

  /* Sum: '<S2>/Sum1' incorporates:
   *  Gain: '<S2>/Gain'
   *  Gain: '<S2>/Gain1'
   *  Inport: '<Root>/vd'
   *  Integrator: '<S2>/Integrator'
   */
  rtb_Sum1 = (0.0 - Ki * rtX.Integrator_CSTATE_n) - Kx * rtU.vd_p;

  /* Saturate: '<S2>/Saturation' */
  if (rtb_Sum1 > rtP.Saturation_UpperSat) {
    rtb_Saturation = rtP.Saturation_UpperSat;
  } else if (rtb_Sum1 < rtP.Saturation_LowerSat) {
    rtb_Saturation = rtP.Saturation_LowerSat;
  } else {
    rtb_Saturation = rtb_Sum1;
  }

  /* End of Saturate: '<S2>/Saturation' */

  /* Sum: '<S2>/Sum3' incorporates:
   *  Gain: '<S2>/Gain2'
   *  Inport: '<Root>/vd'
   *  Inport: '<Root>/vd+'
   *  Sum: '<S2>/Sum'
   *  Sum: '<S2>/Sum2'
   */
  rtDW.Sum3 = (rtb_Saturation - rtb_Sum1) * Kb + (rtU.vd - rtU.vd_p);

  /* Outport: '<Root>/Ud' */
  rtY.Ud = rtb_Saturation;
  if (rtmIsMajorTimeStep(rtM)) {
    rt_ertODEUpdateContinuousStates(&rtM->solverInfo);

    /* Update absolute time for base rate */
    /* The "clockTick0" counts the number of times the code of this task has
     * been executed. The absolute time is the multiplication of "clockTick0"
     * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
     * overflow during the application lifespan selected.
     */
    ++rtM->Timing.clockTick0;
    rtM->Timing.t[0] = rtsiGetSolverStopTime(&rtM->solverInfo);

    {
      /* Update absolute timer for sample time: [0.005s, 0.0s] */
      /* The "clockTick1" counts the number of times the code of this task has
       * been executed. The resolution of this integer timer is 0.005, which is the step size
       * of the task. Size of "clockTick1" ensures timer will not overflow during the
       * application lifespan selected.
       */
      rtM->Timing.clockTick1++;
    }
  }                                    /* end MajorTimeStep */
}

/* Derivatives for root system: '<Root>' */
void Asserv_derivatives(void)
{
  XDot *_rtXdot;
  _rtXdot = ((XDot *) rtM->derivs);

  /* Derivatives for Integrator: '<S3>/Integrator' */
  _rtXdot->Integrator_CSTATE = rtDW.Sum7;

  /* Derivatives for Integrator: '<S2>/Integrator' */
  _rtXdot->Integrator_CSTATE_n = rtDW.Sum3;
}

/* Model initialize function */
void Asserv_initialize(void)
{
  /* Registration code */
  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&rtM->solverInfo, &rtM->Timing.simTimeStep);
    rtsiSetTPtr(&rtM->solverInfo, &rtmGetTPtr(rtM));
    rtsiSetStepSizePtr(&rtM->solverInfo, &rtM->Timing.stepSize0);
    rtsiSetdXPtr(&rtM->solverInfo, &rtM->derivs);
    rtsiSetContStatesPtr(&rtM->solverInfo, (real_T **) &rtM->contStates);
    rtsiSetNumContStatesPtr(&rtM->solverInfo, &rtM->Sizes.numContStates);
    rtsiSetNumPeriodicContStatesPtr(&rtM->solverInfo,
      &rtM->Sizes.numPeriodicContStates);
    rtsiSetPeriodicContStateIndicesPtr(&rtM->solverInfo,
      &rtM->periodicContStateIndices);
    rtsiSetPeriodicContStateRangesPtr(&rtM->solverInfo,
      &rtM->periodicContStateRanges);
    rtsiSetErrorStatusPtr(&rtM->solverInfo, (&rtmGetErrorStatus(rtM)));
    rtsiSetRTModelPtr(&rtM->solverInfo, rtM);
  }

  rtsiSetSimTimeStep(&rtM->solverInfo, MAJOR_TIME_STEP);
  rtM->intgData.f[0] = rtM->odeF[0];
  rtM->contStates = ((X *) &rtX);
  rtsiSetSolverData(&rtM->solverInfo, (void *)&rtM->intgData);
  rtsiSetSolverName(&rtM->solverInfo,"ode1");
  rtmSetTPtr(rtM, &rtM->Timing.tArray[0]);
  rtM->Timing.stepSize0 = 0.005;

  /* InitializeConditions for Integrator: '<S3>/Integrator' */
  rtX.Integrator_CSTATE = rtP.Integrator_IC;

  /* InitializeConditions for Integrator: '<S2>/Integrator' */
  rtX.Integrator_CSTATE_n = rtP.Integrator_IC_p;
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */

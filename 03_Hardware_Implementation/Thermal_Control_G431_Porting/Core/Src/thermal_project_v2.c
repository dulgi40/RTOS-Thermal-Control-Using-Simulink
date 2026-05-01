/*
 * File: thermal_project_v2.c
 *
 * Code generated for Simulink model 'thermal_project_v2'.
 *
 * Model version                  : 1.5
 * Simulink Coder version         : 9.5 (R2021a) 14-Nov-2020
 * C/C++ source code generated on : Fri Mar 20 11:22:07 2026
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-M
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "thermal_project_v2.h"
#include "thermal_project_v2_private.h"

/* Block states (default storage) */
DW_thermal_project_v2_T thermal_project_v2_DW;

/* External inputs (root inport signals with default storage) */
ExtU_thermal_project_v2_T thermal_project_v2_U;

/* External outputs (root outports fed by signals with default storage) */
ExtY_thermal_project_v2_T thermal_project_v2_Y;

/* Real-time model */
static RT_MODEL_thermal_project_v2_T thermal_project_v2_M_;
RT_MODEL_thermal_project_v2_T *const thermal_project_v2_M =
  &thermal_project_v2_M_;

/* Model step function */
void thermal_project_v2_step(void)
{
  real_T rtb_error;
  boolean_T rtb_Compare_g;

  /* Sum: '<S1>/error' incorporates:
   *  Inport: '<Root>/set_temp'
   *  Inport: '<Root>/temp'
   */
  rtb_error = thermal_project_v2_U.set_temp - thermal_project_v2_U.temp;

  /* Sum: '<S1>/Sum3' incorporates:
   *  Gain: '<S1>/Kp'
   *  UnitDelay: '<S1>/I_z1'
   */
  thermal_project_v2_Y.pwm_out = -5.0 * rtb_error +
    thermal_project_v2_DW.I_z1_DSTATE;

  /* Switch: '<S1>/Switch' incorporates:
   *  Constant: '<S3>/Constant'
   *  Constant: '<S4>/Constant'
   *  Gain: '<S1>/KiTs'
   *  Logic: '<S1>/Logical Operator'
   *  RelationalOperator: '<S3>/Compare'
   *  RelationalOperator: '<S4>/Compare'
   *  Sum: '<S1>/Sum2'
   *  UnitDelay: '<S1>/I_z1'
   */
  if ((!(thermal_project_v2_Y.pwm_out > 100.0)) &&
      (!(thermal_project_v2_Y.pwm_out < 0.0))) {
    thermal_project_v2_DW.I_z1_DSTATE += -0.05 * rtb_error;
  }

  /* End of Switch: '<S1>/Switch' */

  /* RelationalOperator: '<S5>/Compare' incorporates:
   *  Constant: '<S5>/Constant'
   *  Inport: '<Root>/temp'
   */
  rtb_Compare_g = (thermal_project_v2_U.temp > 35.0);

  /* Switch: '<S2>/Switch' incorporates:
   *  DataTypeConversion: '<S2>/Data Type Conversion'
   *  Saturate: '<S1>/Saturation'
   */
  if ((real_T)rtb_Compare_g >= 0.5) {
    /* Sum: '<S1>/Sum3' incorporates:
     *  Constant: '<S2>/Constant'
     *  Outport: '<Root>/pwm_out'
     */
    thermal_project_v2_Y.pwm_out = 100.0;
  } else if (thermal_project_v2_Y.pwm_out > 100.0) {
    /* Sum: '<S1>/Sum3' incorporates:
     *  Outport: '<Root>/pwm_out'
     *  Saturate: '<S1>/Saturation'
     */
    thermal_project_v2_Y.pwm_out = 100.0;
  } else if (thermal_project_v2_Y.pwm_out < 0.0) {
    /* Sum: '<S1>/Sum3' incorporates:
     *  Outport: '<Root>/pwm_out'
     *  Saturate: '<S1>/Saturation'
     */
    thermal_project_v2_Y.pwm_out = 0.0;
  }

  /* End of Switch: '<S2>/Switch' */

  /* Outport: '<Root>/fault_flag' incorporates:
   *  DataTypeConversion: '<S2>/Data Type Conversion'
   */
  thermal_project_v2_Y.fault_flag = rtb_Compare_g;
}

/* Model initialize function */
void thermal_project_v2_initialize(void)
{
  /* (no initialization code required) */
}

/* Model terminate function */
void thermal_project_v2_terminate(void)
{
  /* (no terminate code required) */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */

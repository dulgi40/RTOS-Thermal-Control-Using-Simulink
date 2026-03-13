/*
 * File: thermal_project.c
 *
 * Code generated for Simulink model 'thermal_project'.
 *
 * Model version                  : 1.4
 * Simulink Coder version         : 9.5 (R2021a) 14-Nov-2020
 * C/C++ source code generated on : Sun Mar  8 20:33:41 2026
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-M
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "thermal_project.h"
#include "thermal_project_private.h"

/* Block states (default storage) */
DW_thermal_project_T thermal_project_DW;

/* External inputs (root inport signals with default storage) */
ExtU_thermal_project_T thermal_project_U;

/* External outputs (root outports fed by signals with default storage) */
ExtY_thermal_project_T thermal_project_Y;

/* Real-time model */
static RT_MODEL_thermal_project_T thermal_project_M_;
RT_MODEL_thermal_project_T *const thermal_project_M = &thermal_project_M_;

/* Model step function */
void thermal_project_step(void)
{
  real_T rtb_error;
  boolean_T rtb_Compare_g;

  /* Outport: '<Root>/temp' incorporates:
   *  UnitDelay: '<S2>/temp_z1'
   */
  thermal_project_Y.temp = thermal_project_DW.temp_z1_DSTATE;

  /* RelationalOperator: '<S6>/Compare' incorporates:
   *  Constant: '<S6>/Constant'
   *  UnitDelay: '<S2>/temp_z1'
   */
  rtb_Compare_g = (thermal_project_DW.temp_z1_DSTATE > 70.0);

  /* Outport: '<Root>/fault_flag' incorporates:
   *  DataTypeConversion: '<S3>/Data Type Conversion'
   */
  thermal_project_Y.fault_flag = rtb_Compare_g;

  /* Outport: '<Root>/u_raw' incorporates:
   *  UnitDelay: '<S1>/I_z1'
   */
  thermal_project_Y.u_raw = thermal_project_DW.I_z1_DSTATE;

  /* Sum: '<S1>/error' incorporates:
   *  Inport: '<Root>/set_temp'
   *  UnitDelay: '<S2>/temp_z1'
   */


  rtb_error = thermal_project_U.set_temp - thermal_project_DW.temp_z1_DSTATE;

  /* Sum: '<S1>/Sum3' incorporates:
   *  Gain: '<S1>/Kp'
   *  UnitDelay: '<S1>/I_z1'
   */
  thermal_project_Y.I_term = -5.0 * rtb_error + thermal_project_DW.I_z1_DSTATE;

  /* Switch: '<S3>/Switch' incorporates:
   *  DataTypeConversion: '<S3>/Data Type Conversion'
   *  Saturate: '<S1>/Saturation'
   */
  if ((real_T)rtb_Compare_g >= 0.5) {
    /* Switch: '<S3>/Switch' incorporates:
     *  Constant: '<S3>/Constant'
     */
    thermal_project_Y.pwm_out = 100.0;
  } else if (thermal_project_Y.I_term > 100.0) {
    /* Switch: '<S3>/Switch' incorporates:
     *  Saturate: '<S1>/Saturation'
     */
    thermal_project_Y.pwm_out = 100.0;
  } else if (thermal_project_Y.I_term < 0.0) {
    /* Switch: '<S3>/Switch' incorporates:
     *  Saturate: '<S1>/Saturation'
     */
    thermal_project_Y.pwm_out = 0.0;
  } else {
    /* Switch: '<S3>/Switch' incorporates:
     *  Saturate: '<S1>/Saturation'
     */
    thermal_project_Y.pwm_out = thermal_project_Y.I_term;
  }

  /* End of Switch: '<S3>/Switch' */

  /* Sum: '<S2>/temp_update' incorporates:
   *  Constant: '<S2>/ambient'
   *  Gain: '<S2>/Ts_gain'
   *  Gain: '<S2>/a_gain'
   *  Gain: '<S2>/b_gain'
   *  Gain: '<S2>/c_gain'
   *  Inport: '<Root>/heat_input'
   *  Sum: '<S2>/Sum'
   *  Sum: '<S2>/dtemp'
   *  UnitDelay: '<S2>/temp_z1'
   */
  thermal_project_DW.temp_z1_DSTATE += ((3.0 * thermal_project_U.heat_input -
    0.08 * thermal_project_Y.pwm_out) - (thermal_project_DW.temp_z1_DSTATE -
    25.0) * 0.02) * 0.1;

  /* Switch: '<S1>/Switch' incorporates:
   *  Constant: '<S4>/Constant'
   *  Constant: '<S5>/Constant'
   *  Gain: '<S1>/KiTs'
   *  Logic: '<S1>/Logical Operator'
   *  RelationalOperator: '<S4>/Compare'
   *  RelationalOperator: '<S5>/Compare'
   *  Sum: '<S1>/Sum2'
   *  UnitDelay: '<S1>/I_z1'
   */


  if ((!(thermal_project_Y.I_term > 100.0)) && (!(thermal_project_Y.I_term < 0.0)))
  {
    thermal_project_DW.I_z1_DSTATE += -0.05 * rtb_error;
  }
   // for AW ON

  //thermal_project_DW.I_z1_DSTATE += -0.05 * rtb_error; // for AW off

  /* End of Switch: '<S1>/Switch' */
}

/* Model initialize function */
void thermal_project_initialize(void)
{
  /* InitializeConditions for UnitDelay: '<S2>/temp_z1' */
  thermal_project_DW.temp_z1_DSTATE = 25.0;
}

/* Model terminate function */
void thermal_project_terminate(void)
{
  /* (no terminate code required) */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */

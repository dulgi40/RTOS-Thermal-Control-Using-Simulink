/*
 * File: thermal_project.h
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

#ifndef RTW_HEADER_thermal_project_h_
#define RTW_HEADER_thermal_project_h_
#ifndef thermal_project_COMMON_INCLUDES_
#define thermal_project_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                                 /* thermal_project_COMMON_INCLUDES_ */

#include "thermal_project_types.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    ((rtm)->errorStatus = (val))
#endif

/* Block states (default storage) for system '<Root>' */
typedef struct {
  real_T temp_z1_DSTATE;               /* '<S2>/temp_z1' */
  real_T I_z1_DSTATE;                  /* '<S1>/I_z1' */
} DW_thermal_project_T;

/* External inputs (root inport signals with default storage) */
typedef struct {
  real_T set_temp;                     /* '<Root>/set_temp' */
  real_T heat_input;                   /* '<Root>/heat_input' */
} ExtU_thermal_project_T;

/* External outputs (root outports fed by signals with default storage) */
typedef struct {
  real_T pwm_out;                      /* '<Root>/pwm_out' */
  real_T fault_flag;                   /* '<Root>/fault_flag' */
  real_T temp;                         /* '<Root>/temp' */
  real_T I_term;                       /* '<Root>/I_term' */
  real_T u_raw;                        /* '<Root>/u_raw' */
} ExtY_thermal_project_T;

/* Real-time Model Data Structure */
struct tag_RTM_thermal_project_T {
  const char_T * volatile errorStatus;
};

/* Block states (default storage) */
extern DW_thermal_project_T thermal_project_DW;

/* External inputs (root inport signals with default storage) */
extern ExtU_thermal_project_T thermal_project_U;

/* External outputs (root outports fed by signals with default storage) */
extern ExtY_thermal_project_T thermal_project_Y;

/* Model entry point functions */
extern void thermal_project_initialize(void);
extern void thermal_project_step(void);
extern void thermal_project_terminate(void);

/* Real-time Model object */
extern RT_MODEL_thermal_project_T *const thermal_project_M;

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<Root>/Constant' : Unused code path elimination
 * Block '<Root>/Constant1' : Unused code path elimination
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
 * '<Root>' : 'thermal_project'
 * '<S1>'   : 'thermal_project/Control System'
 * '<S2>'   : 'thermal_project/Plant Subsystem'
 * '<S3>'   : 'thermal_project/SafetyManager Subsystem'
 * '<S4>'   : 'thermal_project/Control System/Compare To Constant'
 * '<S5>'   : 'thermal_project/Control System/Compare To Constant1'
 * '<S6>'   : 'thermal_project/SafetyManager Subsystem/Compare To Constant'
 */
#endif                                 /* RTW_HEADER_thermal_project_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */

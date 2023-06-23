/***********************************************************************************************************************
 * This file was generated by the MCUXpresso Config Tools. Any manual edits made to this file
 * will be overwritten if the respective MCUXpresso Config Tools is used to update this file.
 **********************************************************************************************************************/

#ifndef _PERIPHERALS_H_
#define _PERIPHERALS_H_

/***********************************************************************************************************************
 * Included files
 **********************************************************************************************************************/
#include "fsl_common.h"
#include "fsl_snvs_lp.h"
#include "fsl_elcdif.h"
#include "fsl_lpadc.h"
#include "fsl_pwm.h"
#include "fsl_wdog.h"
#include "fsl_clock.h"

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/***********************************************************************************************************************
 * Definitions
 **********************************************************************************************************************/
/* Definitions for BOARD_InitPeripherals functional group */
/* Definition of peripheral ID */
#define SNVS_PERIPHERAL SNVS
/* Definition of peripheral ID */
#define LCDIF_PERIPHERAL LCDIF
/* Definition of the expected display clock frequency */
#define LCDIF_EXPECTED_DCLK_FREQ 6489600UL
/* Definition of the panel width */
#define LCDIF_PANEL_WIDTH 240
/* Definition of the panel height */
#define LCDIF_PANEL_HEIGHT 320
/* Definition of the RGB buffer alignment */
#define LCDIF_RGB_BUFFER_ALIGN 32
/* Definition of number of pixel at HSYNC pulse. */
#define LCDIF_HSW 16U
/* Definition of number of pixel at horizontal back porch. */
#define LCDIF_HBP 48U
/* Definition of number of pixel at horizontal front porch. */
#define LCDIF_HFP 16U
/* Definition of number of lines at VSYNC pulse. */
#define LCDIF_VSW 6U
/* Definition of number of lines at vertical back porch. */
#define LCDIF_VBP 6U
/* Definition of number of lines at vertical front porch. */
#define LCDIF_VFP 6U
/* LCDIF interrupt vector ID (number). */
#define LCDIF_LCDIF_IRQN eLCDIF_IRQn
/* LCDIF interrupt handler identifier. */
#define LCDIF_LCDIF_IRQHANDLER eLCDIF_IRQHandler
/* Alias for LPADC1 peripheral */
#define LPADC1_PERIPHERAL LPADC1
/* Definition of peripheral ID */
#define PWM1_PERIPHERAL PWM1
/* Definition of submodule 0 ID */
#define PWM1_SM0 kPWM_Module_0
/* Definition of clock source of submodule 0 frequency in Hertz */
#define PWM1_SM0_SM_CLK_SOURCE_FREQ_HZ 240000000U
/* Definition of submodule 0 counter clock source frequency in Hertz - PWM1_SM0_SM_CLK_SOURCE_FREQ_HZ divided by prescaler */
#define PWM1_SM0_COUNTER_CLK_SOURCE_FREQ_HZ 3750000U
/* Definition of submodule 0 counter (PWM) frequency in Hertz */
#define PWM1_SM0_COUNTER_FREQ_HZ 200U
/* Definition of submodule 0 channel A ID */
#define PWM1_SM0_A kPWM_PwmA
/* Definition of submodule 0 channel B ID */
#define PWM1_SM0_B kPWM_PwmB
/* Definition of submodule 0 channel X ID */
#define PWM1_SM0_X kPWM_PwmX
/* Definition of fault Fault0 ID */
#define PWM1_F0_FAULT0 kPWM_Fault_0
/* Definition of fault Fault1 ID */
#define PWM1_F0_FAULT1 kPWM_Fault_1
/* Definition of fault Fault2 ID */
#define PWM1_F0_FAULT2 kPWM_Fault_2
/* Definition of fault Fault3 ID */
#define PWM1_F0_FAULT3 kPWM_Fault_3
/* Definition of peripheral ID */
#define WDOG1_PERIPHERAL WDOG1

/***********************************************************************************************************************
 * Global variables
 **********************************************************************************************************************/
/* SNVS LP configuration */
extern const snvs_lp_srtc_config_t SNVS_config;
/* RGB mode configuration */
extern const elcdif_rgb_mode_config_t LCDIF_rgbConfig;
/* RGB buffer */
extern uint16_t LCDIF_Buffer[1][LCDIF_PANEL_HEIGHT][LCDIF_PANEL_WIDTH];
extern const lpadc_config_t LPADC1_config;
extern lpadc_conv_command_config_t LPADC1_commandsConfig[3];
extern pwm_config_t PWM1_SM0_config;

extern pwm_signal_param_t PWM1_SM0_pwm_function_config[1];
extern const pwm_fault_input_filter_param_t PWM1_faultInputFilter_config;
extern const pwm_fault_param_t PWM1_Fault0_fault_config;
extern const pwm_fault_param_t PWM1_Fault1_fault_config;
extern const pwm_fault_param_t PWM1_Fault2_fault_config;
extern const pwm_fault_param_t PWM1_Fault3_fault_config;
extern const wdog_config_t WDOG1_config;

/***********************************************************************************************************************
 * Initialization functions
 **********************************************************************************************************************/

void LCDIF_init(void);
void BOARD_InitPeripherals(void);

/***********************************************************************************************************************
 * BOARD_InitBootPeripherals function
 **********************************************************************************************************************/
void BOARD_InitBootPeripherals(void);

#if defined(__cplusplus)
}
#endif

#endif /* _PERIPHERALS_H_ */

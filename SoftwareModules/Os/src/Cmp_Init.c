
/* @file FILE NAME */
#ifndef CMP_INIT_C
#define CMP_INIT_C

/***********************************************************************************************************************
 *    DISCLAIMER
 *   Copyright (C) 2011, 2016 Niyata Infotech Pvt. Ltd. All rights reserved.
 ***********************************************************************************************************************/

/************************************************************************************************************************
 * @author              Author : Name (mail-id)
 ***********************************************************************************************************************/

/***********************************************************************************************************************
 *                                                F I L E  D E S C R I P T I O N
 **----------------------------------------------------------------------------------------------------------------------
 *  @brief
 *
 *  File name                       :Cmp_Init.c
 *  Version                         :V1.0.0
 *  Micros supported                :Micro Independent
 *  Compilers supported             :J link
 *  Platforms supported             :Platform Independent
 *  Description                     : This file consists of definitions of
 *  @bug
--------------------------------------------------------------------------------------------------------------------*/



/***********************************************************************************************************************
 *                                               I N C L U D E   F I L E S
 ***********************************************************************************************************************/
#include "Cmp_Init.h"
#include "clock_config.h"
#include "TTMgr.h"
#include "pin_mux.h"
#include "Cmp_Tasks.h"
#include "lvgl_app.h"
#include "Swc_System_Service.h"
#include "CanIF.h"
#include "Fuel_Guage.h"
#include "fsl_lpadc.h"
#include "Swc_Voltage_Battery_St.h"
#include "Dio_Handler.h"
#include "fsl_lpuart.h"
#include "fsl_pwm.h"
#include "HMI_Tacho_Rend.h"
#include "UART_DataManager.h"
#include "HMI_Gear.h"
#include "HMI_Clock.h"
#include "HMI_Setting_Screen.h"
#include "Ambient_light_sensor.h"
#include "HMI_Main_Screen.h"
#include "I2C_Handler.h"
#include "peripherals.h"
#include "OPT3001_driver.h"
#include "rtc.h"
#include "Swc_Trip_Timer.h"
#include "Swc_TT_Fog_Lamp.h"
#include "Swc_TT_Oil_Pressure.h"
#include "Swc_Service_Remainder.h"
#include "Swc_Averege_Speed.h"
#include "board.h"
#include "fuel03.h"
#include"UDS.h"
#include "CanTp.h"
#include "Crc.h"
#include "UdsApp.h"
//#include"fsl_romapi.h"
/***********************************************************************************************************************
*                                               I N C L U D E  LIBRARY F I L E S
***********************************************************************************************************************/



/***********************************************************************************************************************
 *                                          M A C R O   D E F I N I T I O N S
 ***********************************************************************************************************************/
#define DEMO_LPADC_VREF_SOURCE  kLPADC_ReferenceVoltageAlt2



/*
 * @brief: This macro is used to
 * @Unit:
 * @Resolution:
 * @Range:
 * @Applicability:
 */
#define EXAMPLE_VEHICLE_CAN_CLK_FREQ ((CLOCK_GetRootClockFreq(kCLOCK_Root_Can3) / 100000U) * 100000U)


#define EXAMPLE_DIAG_CAN_CLK_FREQ ((CLOCK_GetRootClockFreq(kCLOCK_Root_Can2) / 100000U) * 100000U)



#define BOARD_DEBUG_UART_BAUDRATE       (115200U)
#define DEMO_LPUART_CLK_FREQ            BOARD_DebugConsoleSrcFreq()
#define UART_IRQn                       LPUART10_IRQn



/***********************************************************************************************************************
 *                                          L O C A L  V A R I A B L E   D E F I N I T I O N S
 ***********************************************************************************************************************/
/*
 * @brief: This variable is used to
 * @Unit:
 * @Resolution:
 * @Range:
 * @Applicability:
 */
flexcan_config_t flexcanConfig;

flexcan_rx_mb_config_t mbConfig;

/***********************************************************************************************************************
 *                                  P R I V A T E   V A R I A B L E   D E F I N I T I O N S
 ***********************************************************************************************************************/
/*
 * @brief: This variable is used to
 * @Unit:
 * @Resolution:
 * @Range:
 * @Applicability:
 */
extern flexcan_handle_t Vehicle_flexcanHandle;


extern flexcan_handle_t Diag_flexcanHandle;

uint32_t txIdentifier;
uint32_t rxIdentifier;
/***********************************************************************************************************************
 *                                    P R I V A T E     F U N C T I O N S    D E C L A R A T I O N
 ***********************************************************************************************************************/

/*
 * @brief    This function processes the
 * @param
 * @return
 */

/***********************************************************************************************************************
 *                                          F U N C T I O N     D E F I N I T I O N S
 ***********************************************************************************************************************/

/*
 * @brief    This function processes the board Init 
 * @param     void 
 * @return    void 
 */
void HardWare_Init()
{

    /* Init board hardware. */
    BOARD_ConfigMPU();
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    SystemCoreClockUpdate();
    /*Clock setting for FLEXCAN*/
    clock_root_config_t rootCfg = {0};
    rootCfg.mux                 = FLEXCAN_CLOCK_SOURCE_SELECT;
    rootCfg.div                 = FLEXCAN_CLOCK_SOURCE_DIVIDER;
    CLOCK_SetRootClock(kCLOCK_Root_Can3, &rootCfg);
    CLOCK_SetRootClock(kCLOCK_Root_Can2, &rootCfg);

    BOARD_InitBootPeripherals();    

    FlexCan_Vechile_Init();

    FlexCan_Diag_Init();

    Adc_Init();

    UART_Init();
    
	Rtc_Init();

    OPT3001_Init();

    Board_PowerUP_Sequence();   

}


/*
 * @brief    This function processes the Application Init
 * @param
 * @return
 */
void Application_Init(void)
{

    PowerUp_Sequence_After_IGNITION();

    TFT_Display_Init();

    Dio_Handler_Init();

    TT_Mgr_init();

    TT_Mgr_Activate();

    TT_Mgr_Proveout();

    Abs_TT_init();

    CanMgr_Init();

    CanIf_Init();

    CanTp_Init();
    UdsApp_Init();
	 UDS_Init();

    Crc_Init();

    System_Service_Init();

    TT_Fog_Lamp_Init();

    TT_Mil_Tft_Init();

    I2C_Handler_Init();

    Speedometer_Init();

    Tachometer_Init();   

    NVM_Handler_Init();

    Trip_Timer_Init();

    fuel03_KSColdInit();

    Fuel_Guage_Init();

    TT_Service_Remainder_Init();

    TT_Oil_Pressure_Init();

	gear_position_Init();

    Button_Mgr_Init();

    ODO_Init();

    Voltage_Battery_Init();

    HMI_Main_Screen_Init();

    Average_Speed_Init();
    
    SS_TT_ADC_Config_Init();
    
    Side_Stand_TT_init();

    SWC_TFT_Illum_Init();

	I2C_Ambient_Sensor_Init();
    UART_DataManager_Init();
    Gui_Gear_Init();
	Gui_HMI_Clock_Init();
	 HMI_Tacho_Rend_Init();

}


/*
 * @brief   This function processes the application Cold Init 
 * @param   NONE
 * @return  NONE
 */
void Application_Cold_Init(void)
{
    RTC_Cold_Init();

    HMI_Setting_Screen_Cold_Init();

    TC_Cold_init();

}

/*
 * @brief   This function processes the application Warm Init 
 * @param   NONE
 * @return  NONE
 */
void Application_Warm_Init(void)
{
    HMI_Setting_Screen_Warm_Init();

    TC_Warm_init();
}

/*
 * @brief    This function processes the board Power Up Sequence 
 * @param     void 
 * @return    void 
 */
void Board_PowerUP_Sequence(void)
{

    /*firsrt Set in 5V_SW_EN */
    GPIO_PinWrite(BOARD_INITPINS_en_5v_GPIO, BOARD_INITPINS_en_5v_GPIO_PIN, 1);

    for (int i = 0; i < 10; i++);
    
    /*Third Set in CAN_DIAG_STB , CAN_VEH_STB */
    GPIO_PinWrite(GPIO9, BOARD_INITPINS_LPSPI1_PCS0_GPIO_PIN, 1U);
    GPIO_PinWrite(GPIO9, BOARD_INITPINS_CAN_STB_GPIO_PIN, 1U);

}

/*
 * @brief    This function processes the Power Up Sequence After IGN 
 * @param     void 
 * @return    void 
 */
void PowerUp_Sequence_After_IGNITION(void)
{
    /* Initialize buffers used to store display contents*/
	TFT_Buffers_Init();

	/*Set in TFT_3_3V_EN*/
    GPIO_PinWrite(BOARD_INITPINS_tft_3v3_GPIO, BOARD_INITPINS_tft_3v3_GPIO_PIN, 1);

	/*Second Clear in TFT_BKLT_EN*/
	TFT_Backlight_Disable();

	/*Second Clear in TFT_XRES_EN*/
    GPIO_PinWrite(BOARD_INITPINS_tft_xres_GPIO, BOARD_INITPINS_tft_xres_GPIO_PIN, 0);

    //set_ProfilePin();
    /* wati for 10ms */
    WaitTime(10);
    //Clr_ProfilerPin();
    
	/*Second Clear in TFT_XRES_EN*/
	GPIO_PinWrite(BOARD_INITPINS_tft_xres_GPIO, BOARD_INITPINS_tft_xres_GPIO_PIN, 1);

	/*Third Clear in TFT_CSB_EN*/
	GPIO_PinWrite(BOARD_INITPINS_tft_csb_GPIO, BOARD_INITPINS_tft_csb_GPIO_PIN, 0);

    /* wati for 10ms */
    WaitTime(2);

	/*Third Set in TFT_CSB_EN*/
	GPIO_PinWrite(BOARD_INITPINS_tft_csb_GPIO, BOARD_INITPINS_tft_csb_GPIO_PIN, 1);

	/* wati for 10ms */
    WaitTime(10);

    LCDIF_init();

	/* wati for 150ms */
    WaitTime(150);

    /*Set in TFT Illum Duty 10 percentage*/
    Illum_PWM_DutyCycle(0);    

    /*Set in TFT Backlight Enable*/
    TFT_Backlight_Enable();   

    for (int i = 0; i < 150; i++);

    /*Set in Sw BTLE Enable */
    SW_BTLE_Enable();

    for (int i = 0; i < 150; i++);
    
    /*Set in Batt Mon Enable*/
    Batt_Mon_Enable();

    for (int i = 0; i < 150; i++);

    /*Set Switched Batt Enable*/
    Switched_Batt_Enable();

    for (int i = 0; i < 150; i++);  

}
/*
 * @brief    This function processes the TFT RGB Enable , clocks
 * @param     void 
 * @return    void 
 */
void TFT_Enable_RGB(void)
{
    /* do nothing */
}

/*
 * @brief    This function used to create wait time during power on and power down sequence.
 * @param    uint16_t delay_ms 
 * @return    void 
 */
void WaitTime(uint16_t delay_ms)
{
    uint32_t Current_Tick_Cnt = 0;
    uint32_t Current_Stamp_Tick = 0;
    uint32_t Delta_Count = 0;
    uint32_t Delay_Loop = 0;
    uint32_t Basic_Delay_loop = 0;

    for(Delay_Loop = 0; Delay_Loop < delay_ms; Delay_Loop++)  // THIS SHALL EXECUTE FOR NUMBER OF MILLIS
    {
        for(Basic_Delay_loop = 0; Basic_Delay_loop < 0x1C900; Basic_Delay_loop++);  //1MS EXECUTION TIME MEASURED APPROX
    }

}

/*
 * @brief    This function processes the TFT Display backlight Disable 
 * @param     void 
 * @return    void 
 */

void TFT_Backlight_Disable(void)
{
	/*Clear in TFT_BKLT_EN*/
	GPIO_PinWrite(BOARD_INITPINS_bklt_GPIO, BOARD_INITPINS_bklt_GPIO_PIN, 0);

}

/*
 * @brief    This function processes the TFT Display backlight Enable 
 * @param     void 
 * @return    void 
 */
void TFT_Backlight_Enable(void)
{

    /*Set in TFT_BKLT_EN*/
	GPIO_PinWrite(BOARD_INITPINS_bklt_GPIO, BOARD_INITPINS_bklt_GPIO_PIN, 1);

}

/*
 * @brief    This function processes the Switched Battery Enable 
 * @param     void 
 * @return    void 
 */
void Switched_Batt_Enable(void)
{

    /*Set in SWITCHED_BATT_EN*/
	GPIO_PinWrite(BOARD_INITPINS_batt_en_GPIO, BOARD_INITPINS_batt_en_GPIO_PIN, 1);

}


/*
 * @brief    This function processes the Switched Battery Disable 
 * @param     void 
 * @return    void 
 */
void Switched_Batt_Disable(void)
{

    /*clear in SWITCHED_BATT_EN*/
	GPIO_PinWrite(BOARD_INITPINS_batt_en_GPIO, BOARD_INITPINS_batt_en_GPIO_PIN, 0);

}

 /* @brief    This function processes the Battery  Mon Enable
 * @param     void 
 * @return    void 
 */
void Batt_Mon_Enable(void)
{

    /*Set in BATT_MON_EN*/
    GPIO_PinWrite(BOARD_INITPINS_DO_BATT_MON_EN_PERIPHERAL, BOARD_INITPINS_DO_BATT_MON_EN_CHANNEL, 1U);

}

/*
 * @brief    This function processes the Battery Mon Disable 
 * @param     void 
 * @return    void 
 */
void Batt_Mon_Disable(void)
{

    /*Clear in BATT_MON_EN*/
    GPIO_PinWrite(BOARD_INITPINS_DO_BATT_MON_EN_PERIPHERAL, BOARD_INITPINS_DO_BATT_MON_EN_CHANNEL, 0U);

}


/*
 * @brief    This function processes the SW BTLE Enable 
 * @param     void 
 * @return    void 
 */
void SW_BTLE_Enable(void)
{

    /*Set in SW_BTLE_EN*/
    GPIO_PinWrite(BOARD_INITPINS_BLE_3P3V_EN_GPIO, BOARD_INITPINS_BLE_3P3V_EN_GPIO_PIN, 1U);

}

/*
 * @brief    This function processes the Set ILLUM PWM DUTY 
 * @param     void 
 * @return    void 
 */
void Illum_PWM_DutyCycle(uint8_t pwm_duty)
{
	/* update current duty cycle value in PWM Driver */
	PWM_UpdatePwmDutycycle(PWM1,kPWM_Module_0,kPWM_PwmA,kPWM_SignedCenterAligned,pwm_duty);

    /* Load PWM Register */
	PWM_SetPwmLdok(PWM1, (kPWM_Control_Module_0), true);

}
/*
 * @brief    This function processes the SW BTLE Disable 
 * @param     void 
 * @return    void 
 */
void SW_BTLE_Disable(void)
{

    /*Clear in SW_BTLE_EN*/
    GPIO_PinWrite(BOARD_INITPINS_BLE_3P3V_EN_GPIO, BOARD_INITPINS_BLE_3P3V_EN_GPIO_PIN, 0U);

}


/*
 * @brief    This function processes the Power Down Sequence 
 * @param     void 
 * @return    void 
 */
void PowerDown_Sequence(void)
{

    /*Set in TFT Illum Duty 50 percentage*/
    Illum_PWM_DutyCycle(0); 

    for (int i = 0; i < 150; i++);

    /*Second Clear in TFT_BKLT_EN*/
	TFT_Backlight_Disable();

    /*Set in TFT_3_3V_EN*/
    GPIO_PinWrite(BOARD_INITPINS_tft_3v3_GPIO, BOARD_INITPINS_tft_3v3_GPIO_PIN, 0);

    for (int i = 0; i < 150; i++);

    /*Set in Sw BTLE Disable */
    SW_BTLE_Disable();

    for (int i = 0; i < 150; i++);

    /*Third Set in CAN_DIAG_STB , CAN_VEH_STB */
    GPIO_PinWrite(GPIO9, BOARD_INITPINS_LPSPI1_PCS0_GPIO_PIN, 0U);
    GPIO_PinWrite(GPIO9, BOARD_INITPINS_CAN_STB_GPIO_PIN, 0U);

    for (int i = 0; i < 150; i++);

    /*firsrt Set in 5V_SW_EN */
    GPIO_PinWrite(BOARD_INITPINS_en_5v_GPIO, BOARD_INITPINS_en_5v_GPIO_PIN, 0);

    for (int i = 0; i < 150; i++);

    Switched_Batt_Disable();

    for (int i = 0; i < 150; i++);

    Batt_Mon_Disable();

}


/*
 * @brief    This function processes Adc2 Init
 * @param     void 
 * @return    void 
 */
void Adc_Init(void)
{
	lpadc_config_t mLpadcConfigStruct;

	LPADC_GetDefaultConfig(&mLpadcConfigStruct);
	mLpadcConfigStruct.enableAnalogPreliminary = true;

	mLpadcConfigStruct.referenceVoltageSource = DEMO_LPADC_VREF_SOURCE;

	LPADC_Init(DEMO_LPADC_BASE, &mLpadcConfigStruct);
    mLpadcConfigStruct.referenceVoltageSource = kLPADC_ReferenceVoltageAlt3;
    LPADC_Init(ADC_BASE2, &mLpadcConfigStruct);
}



/*
 * @brief    This function processes Uart Init
 * @param     void 
 * @return    void 
 */

void UART_Init(void)
{
    lpuart_config_t config;

    LPUART_GetDefaultConfig(&config);
    config.baudRate_Bps = BOARD_DEBUG_UART_BAUDRATE;
    config.enableTx     = true;
    config.enableRx     = true;

    LPUART_Init(UART_CHANNEL, &config, DEMO_LPUART_CLK_FREQ);

    LPUART_EnableInterrupts(UART_CHANNEL, kLPUART_RxDataRegFullInterruptEnable);
    EnableIRQ(UART_IRQn);
}

/*
 * @brief    This function processes Animation Display Init
 * @param     void 
 * @return    void 
 */
void TFT_Display_Init(void)
{

    lvgl_app_int(); 

}


/*
 * @brief    This function processes Vehicle CAN Init
 * @param     void 
 * @return    void 
 */

void FlexCan_Vechile_Init(void)
{
	flexcan_config_t vehicle_flexcanConfig;

	FLEXCAN_GetDefaultConfig(&vehicle_flexcanConfig);

	    
    /* Set Baud rate for 500kbs */
    vehicle_flexcanConfig.bitRate = 500000;

    flexcan_timing_config_t timing_config;

    memset(&timing_config, 0, sizeof(flexcan_timing_config_t));

    GPIO_PinWrite(GPIO9, BOARD_INITPINS_CAN_STB_GPIO_PIN, 1U);


    if (FLEXCAN_CalculateImprovedTimingValues(VECHILE_CAN, vehicle_flexcanConfig.baudRate, EXAMPLE_VEHICLE_CAN_CLK_FREQ,
                                                    &timing_config))
        {
            /* Update the improved timing configuration*/
            memcpy(&(vehicle_flexcanConfig.timingConfig), &timing_config, sizeof(flexcan_timing_config_t));
        }
        else
        {

    }

    FLEXCAN_Init(VECHILE_CAN, &vehicle_flexcanConfig, EXAMPLE_VEHICLE_CAN_CLK_FREQ);

     
	FLEXCAN_TransferCreateHandle(VECHILE_CAN, &Vehicle_flexcanHandle, Vehicle_flexcan_callback, NULL);      


}

/*
 * @brief    This function processes Diag CAN Init
 * @param     void 
 * @return    void 
 */

void FlexCan_Diag_Init(void)
{
	flexcan_config_t flexcanConfig;

	FLEXCAN_GetDefaultConfig(&flexcanConfig);

    flexcanConfig.maxMbNum = 28;

    /* Set Baud rate for 500kbs */
    flexcanConfig.bitRate = 500000;

    flexcan_timing_config_t timing_config;

    memset(&timing_config, 0, sizeof(flexcan_timing_config_t));

    GPIO_PinWrite(GPIO9, BOARD_INITPINS_LPSPI1_PCS0_GPIO_PIN, 1U);

    if (FLEXCAN_CalculateImprovedTimingValues(DIAG_CAN, flexcanConfig.baudRate, EXAMPLE_DIAG_CAN_CLK_FREQ,
                                                    &timing_config))
    {
        /* Update the improved timing configuration*/
        memcpy(&(flexcanConfig.timingConfig), &timing_config, sizeof(flexcan_timing_config_t));
    }
    else
    {

    }

    FLEXCAN_Init(DIAG_CAN, &flexcanConfig, EXAMPLE_DIAG_CAN_CLK_FREQ);

    FLEXCAN_TransferCreateHandle(DIAG_CAN, &Diag_flexcanHandle, flexcan_Diag_callback, NULL);

}



/* PWM1_0_IRQn interrupt handler */
void PWM1_0_IRQHandler(void) {
  /*  Place your code here */
  

  /* Add for ARM errata 838869, affects Cortex-M4, Cortex-M4F
     Store immediate overlapping exception return operation might vector to incorrect interrupt. */
  #if defined __CORTEX_M && (__CORTEX_M == 4U)
    __DSB();
  #endif
}


/***********************************************************************************************************************
                                              E N D   O F   S O F T W A R E
 **********************************************************************************************************************/


/***********************************************************************************************************************
 *                                              R E V I S I O N   H I S T O R Y
 ***********************************************************************************************************************
    REVISION NUMBER      : Major.Minor.Patch
    REVISION DATE        : MONTH/DATE/YEAR
    CREATED / REVISED BY : NAME (EMAIL-ID)
    DESCRIPTION          : Initial version
------------------------------------------------------------------------------------------------------------------------

 ***********************************************************************************************************************/
#endif /* ! CMP_INIT_C */

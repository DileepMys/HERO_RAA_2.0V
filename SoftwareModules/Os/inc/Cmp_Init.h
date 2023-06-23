/* @file FILE NAME */
#ifndef CMP_INIT_H
#define CMP_INIT_H

/***********************************************************************************************************************
*    DISCLAIMER
*   Copyright (C) 2020 Niyata Infotech Pvt. Ltd. All rights reserved.                                             
***********************************************************************************************************************/

/************************************************************************************************************************
* @author              Author : Name (mail-id)                                                                         
***********************************************************************************************************************/

/***********************************************************************************************************************
*                                                F I L E  D E S C R I P T I O N                                        
**----------------------------------------------------------------------------------------------------------------------
*  @brief
*
*  File name                       : Cmp_Init.h
*  Version                         : V1.0.0
*  Micros supported                : Micro Independent
*  Compilers supported             : J link
*  Platforms supported             : Platform Independent                
*  Description                     : This header file contains the declarations of CmP init tasks
*  @bug                            : N/A
--------------------------------------------------------------------------------------------------------------------*/


/***********************************************************************************************************************
*                                               I N C L U D E   CONFIGURATION F I L E S 
***********************************************************************************************************************/
#include"main_init.h"
#include "fsl_flexcan.h"
#include "fsl_debug_console.h"
/***********************************************************************************************************************
                                               I N C L U D E  CONDITION BASED F I L E S                             
***********************************************************************************************************************/
#if SYSTEM_1
# include "system_1.h"
#elif SYSTEM_2
# include "system_2.h"
#elif SYSTEM_3
#endif


/***********************************************************************************************************************
*                                      V E R S I O N   I N T E G R I T Y  C H E C K                                  
***********************************************************************************************************************/

/***********************************************************************************************************************
*                                            M A C R O   D E F I N I T I O N S                                         
***********************************************************************************************************************/
/**
* @brief This macro is used to define 
* @Unit:  
* @Resolution: 
* @Range: 
* @Applicability: 
* @Note:  
*/

#define VECHILE_CAN                   CAN3
#define VECHILE_FLEXCAN_RxWarningIRQn CAN3_IRQn
#define VECHILE_FLEXCAN_BusOffIRQn    CAN3_IRQn
#define VECHILE_FLEXCAN_ErrorIRQn     CAN3_IRQn
#define VECHILE_FLEXCAN_MBIRQn        CAN3_IRQn
#define VECHILE_FLEXCAN_IRQHandler    CAN3_IRQHandler


#define DIAG_CAN                      CAN2
#define DIAG_FLEXCAN_RxWarningIRQn CAN2_IRQn
#define DIAG_FLEXCAN_BusOffIRQn    CAN2_IRQn
#define DIAG_FLEXCAN_ErrorIRQn     CAN2_IRQn
#define DIAG_FLEXCAN_MBIRQn        CAN2_IRQn
#define DIAG_FLEXCAN_IRQHandler    CAN2_IRQHandler

#define TX_MB_ID 0x321UL

#define LOG_INFO (void)PRINTF

#define RX_MB_ID_MASK 0xFFUL
/* RX MB ID after mask. */
#define RX_MB_ID_AFTER_MASK (RX_MB_ID_MASK & TX_MB_ID)

#define BYTES_IN_MB                   kFLEXCAN_64BperMB

/* Select OSC24Mhz as master flexcan clock source */
#define FLEXCAN_CLOCK_SOURCE_SELECT (1U)
/* Clock divider for master flexcan clock source */
#define FLEXCAN_CLOCK_SOURCE_DIVIDER (1U)

#define UART_CHANNEL                    LPUART10
//#define UART_IRQHandler                 LPUART10_IRQHandler
/***********************************************************************************************************************
*                                          T Y P E   D E F I N I T I O N S                                           
***********************************************************************************************************************/

/*
 * @brief    This typedef is used to define 
 * @param    
 * @return
 **/
//extern typedef unsigned short uint16_t;
//extern typedef unsigned char uint8_t;


/*
 * @brief    This typedef enum is used to define 
 * @param    
 * @param
 **/


/*
 * @brief    This structure is used to define 
 * @param    
 * @param    
 **/


/***********************************************************************************************************************
*                                    P U B L I C     F U N C T I O N S    D E C L A R A T I O N                      
***********************************************************************************************************************/


/*
 * @brief    This function processes the board Init 
 * @param     void 
 * @return    void 
 */
void HardWare_Init(void);

/*
* @brief    This API is used to Application init
* @param
* @return
* @invocation
*/
void Application_Init(void);


/*
 * @brief   This function processes the application Warm Init 
 * @param   NONE
 * @return  NONE
 */
void Application_Warm_Init(void);

/*
 * @brief   This function processes the application Cold Init 
 * @param   NONE
 * @return  NONE
 */
void Application_Cold_Init(void);

/*
 * @brief    This function processes the board Power Up Sequence 
 * @param     void 
 * @return    void 
 */
void Board_PowerUP_Sequence(void);

/*
 * @brief    This function processes the Power Up Sequence After IGN
 * @param     void 
 * @return    void 
 */
void PowerUp_Sequence_After_IGNITION(void);

/*
 * @brief    This function processes the TFT Display backlight Enable 
 * @param     void 
 * @return    void 
 */
void TFT_Backlight_Enable(void);


/*
 * @brief    This function processes the TFT Display backlight Disable 
 * @param     void 
 * @return    void 
 */
void TFT_Backlight_Disable(void);

/*
 * @brief    This function processes the Switched Battery Enable 
 * @param     void 
 * @return    void 
 */
void Switched_Batt_Enable(void);

/*
 * @brief    This function processes the Switched Battery Disable 
 * @param     void 
 * @return    void 
 */
void Switched_Batt_Disable(void);

/*
 * @brief    This function processes the Battery  Mon Enable 
 * @param     void 
 * @return    void 
 */
void Batt_Mon_Enable(void);

/*
 * @brief    This function processes the Battery Mon Disable 
 * @param     void 
 * @return    void 
 */
void Batt_Mon_Disable(void);

/*
 * @brief    This function processes the SW BTLE Enable 
 * @param     void 
 * @return    void 
 */
void SW_BTLE_Enable(void);

/*
 * @brief    This function processes the SW BTLE Disable 
 * @param     void 
 * @return    void 
 */
void SW_BTLE_Disable(void);

/*
 * @brief    This function processes the Set ILLUM PWM DUTY 
 * @param     void 
 * @return    void 
 */
void Illum_PWM_DutyCycle(uint8_t pwm_duty);


/*
 * @brief    This function processes Adc2 Init
 * @param     void 
 * @return    void 
 */
void Adc_Init(void);

/*
 * @brief    This function processes Uart Init
 * @param     void 
 * @return    void 
 */

void UART_Init(void);

/*
 * @brief    This function processes Animation Display Init
 * @param     void 
 * @return    void 
 */
void TFT_Display_Init(void);

/*
 * @brief    This function processes Vehicle CAN Init
 * @param     void 
 * @return    void 
 */

void FlexCan_Vechile_Init(void);

/*
 * @brief    This function processes Diag CAN Init
 * @param     void 
 * @return    void 
 */

void FlexCan_Diag_Init(void);

/*
 * @brief    This function processes WaitTime   
 * @param     delay_ms
 * @return    void 
 */

void WaitTime(uint16_t delay_ms);
/*
 * @brief    This function processes the Battery  Mon Enable 
 * @param     void 
 * @return    void 
 */
void PowerDown_Sequence(void);


/***********************************************************************************************************************
                                              E N D   O F   S O F T W A R E                                         
*********************************************************************************************************************/


/***********************************************************************************************************************
*                                              R E V I S I O N   H I S T O R Y                                       
***********************************************************************************************************************
    REVISION NUMBER      : V1.0.0
    REVISION DATE        : MONTH/DATE/YEAR                              
    CREATED / REVISED BY : NAME (EMAIL-ID)   
    DESCRIPTION          : Initial version                                  
------------------------------------------------------------------------------------------------------------------------

***********************************************************************************************************************/
#endif /* ! CMP_INIT_H */

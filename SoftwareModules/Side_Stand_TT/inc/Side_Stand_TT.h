/* @file FILE NAME */
#ifndef SIDE_STAND_TT_H
#define SIDE_STAND_TT_H

/***********************************************************************************************************************
*    DISCLAIMER
*   Copyright (C) 2020 Niyata Infotech Pvt. Ltd. All rights reserved.                                             
***********************************************************************************************************************/

/************************************************************************************************************************
* @author              Author : balaji pandurangan (balaji.pandurangan@niyatainfotech.com)                                                                         
***********************************************************************************************************************/

/***********************************************************************************************************************
*                                                F I L E  D E S C R I P T I O N                                        
**----------------------------------------------------------------------------------------------------------------------
*  @brief
*
*  File name                       : Side_Stand_TT.h
*  Version                         : v1.0.0
*  Micros supported                : Micro Independent
*  Compilers supported             : J Link
*  Platforms supported             : Platform Independent               
*  Description                     : This file consists of declaration of side stand telltale
*  @bug                            : N/A
--------------------------------------------------------------------------------------------------------------------*/

/**********************************************************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif
/**********************************************************************************************************************/
/***********************************************************************************************************************
*                                               I N C L U D E   CONFIGURATION F I L E S 
***********************************************************************************************************************/
#include "stdbool.h"
#include "hal_stdtypes.h"

/***********************************************************************************************************************
                                               I N C L U D E  CONDITION BASED F I L E S                             
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
#define SIDESTAND_SAMPLE_INDEX                  6U



/**
* @brief This macro is used to define 
* @Unit:  
* @Resolution: 
* @Range: 
* @Applicability: 
* @Note:  
*/
#define ENABLE_SS_CRC                           0U
/***********************************************************************************************************************
*                                          T Y P E   D E F I N I T I O N S                                           
***********************************************************************************************************************/

/***********************************************************************************************************************
*                                    P U B L I C     F U N C T I O N S    D E C L A R A T I O N                      
***********************************************************************************************************************/

/*
* @brief            This function processes the intialization of Side stand Telltale
* @param            void
* @return           void
* @invocation       invoked by scheduler
*/
void Side_Stand_TT_init(void);

/*
* @brief            This function processes the De-intialization of Side stand Telltale
* @param            void
* @return           void
* @invocation       invoked by scheduler
*/
void Side_Stand_TT_Deinit(void);

/*
* @brief            This function processes the Side Stand Telltale and this the periodic function
* @param            void
* @return           void
* @invocation       invoked by scheduler
*/
void Side_Stand_TT_Main_Function(void);

/*
* @brief            This function processes the Can Message Side stand telltale Missing TimeOut callback 
                    which invokes when the message is missing
* @param            void       
* @return           void
* @invocation       invoked by scheduler
*/
void CanMgr_SideStand_Telltale_Timeout_Callback_0x131(void);

/*
* @brief            This function processes the Can Message Side stand telltale reception callback which invokes 
                    when the message is received
* @param            void
* @return           void
* @invocation       invoked by scheduler
*/
void CanMgr_SideStand_Telltale_reception_cbk(void);


/*
* @brief            This function processes the Can Message Side stand sensor reception callback which invokes 
                    when the message is received
* @param            void
* @return           void
* @invocation       invoked by scheduler
*/
void CanMgr_SideStand_Sensor_Fault_Timeout_Callback_0x131(void);

/*
* @brief            This function processes the Can Message  Side stand sensor reception callback which invokes 
                    when the message is received
* @param            void
* @return           void
* @invocation       invoked by scheduler
*/
void CanMgr_SideStand_Sensor_Fault_reception_cbk(void);

/*
 * @brief           This function processes the Intialization of Adc configuration
 * @param           void 
 * @return          void
 */
void SS_TT_ADC_Config_Init(void);
/*
* @brief            This function processes the  Checksum error recovery indication callback which invokes when the message is received
* @param            void       
* @return           void
* @invocation       invoked by scheduler
 */

void canMgr_SideStand_Sensor_CRC_recovery_indication_callback(uint8_t msgId,uint8_t UserId);


/*
* @brief            This function processes the  Checksum error recovery indication callback which invokes when the message is received
* @param            void       
* @return           void
* @invocation       invoked by scheduler
 */
void canMgr_SideStand_Sensor_CRC_ERROR_indication_callback(uint8_t msgId,uint8_t UserId);

/*
* @brief            This function processes the  Alive Counter recovery indication callback which invokes when the message is received
* @param            void
* @return           void  
* @invocation 
*/
void canMgr_SideStand_Sensor_Alive_Counter_recovery_indication_callback(uint8_t msgId,uint8_t UserId);


/*
* @brief            This function processes the CRC Error Message Missing TimeOut callback which invokes when the message is missing
* @param            void       
* @return           void
* @invocation 
*/
void canMgr_SideStand_Sensor_Alive_Counter_Error_recovery_indication_callback(uint8_t msgId,uint8_t UserId);




void CanMgr_SideStand_Sensor_Fault_Timeout_Cbk(void);
void CanMgr_SideStand_Telltale_Timeout_Cbk(void);
void Side_Stand_TT_Feedback(void);

/***********************************************************************************************************************
                                              E N D   O F   S O F T W A R E                                         
*********************************************************************************************************************/
#ifdef __cplusplus
}
#endif

/***********************************************************************************************************************
*                                              R E V I S I O N   H I S T O R Y                                       
/***********************************************************************************************************************
    REVISION NUMBER      : v1.0.0                          
    REVISION DATE        : July/02/2022        
    CREATED / REVISED BY : Balaji Pandurangan (balaji.pandurangan@niyatainfotech.com)      
    DESCRIPTION          : Updated Trigger value and software Trigger      
------------------------------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------------------------------

    REVISION NUMBER      : v1.0.0                          
    REVISION DATE        : Jan/17/2023       
    CREATED / REVISED BY : Yuvaraj (yuvaraj@niyatainfotech.com)      
    DESCRIPTION          : Updated CRC and Alive counter call back functions     
------------------------------------------------------------------------------------------------------------------------

***********************************************************************************************************************/
#endif /* ! SIDE_STAND_TT_H */

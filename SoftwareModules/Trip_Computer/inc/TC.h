
/* @file TC_H */
#ifndef TC_H
#define TC_H

/***********************************************************************************************************************
*   DISCLAIMER
*   Copyright © , 2021 Niyata Infotech Pvt. Ltd. All rights reserved.                                             
***********************************************************************************************************************/

/************************************************************************************************************************
* @author              Author : Maheswari R (maheswari@niyatainfotech.com)                                                                         
***********************************************************************************************************************/

/***********************************************************************************************************************
*                                                F I L E  D E S C R I P T I O N                                        
**----------------------------------------------------------------------------------------------------------------------
*  @brief
*
*  File name                       : TC.h
*  Version                         : V1.0.2
*  Micros supported                : Micro Independent
*  Compilers supported             : Compiler Independent
*  Platforms supported             : Platform Independent                
*  Description                     : This header file contains the declarations of Trip computer APIs
*  @bug                            : N/A
--------------------------------------------------------------------------------------------------------------------*/
/**********************************************************************************************************************/

/***********************************************************************************************************************
*                                               I N C L U D E   C O N F I G U R A T I O N   F I L E S 
***********************************************************************************************************************/
#include "TC_Cfg.h"

/***********************************************************************************************************************
                                             I N C L U D E  CONDITION BASED   F I L E S                             
***********************************************************************************************************************/

/***********************************************************************************************************************
*                                      V E R S I O N   I N T E G R I T Y  C H E C K                                  
***********************************************************************************************************************/

/***********************************************************************************************************************
*                                             M A C R O   D E F I N I T I O N S                                         
***********************************************************************************************************************/
#define TC_INVALID         0xFFFFFFFF
#define AFE_SAMPLES         10

/***********************************************************************************************************************
*                                          T Y P E   D E F I N I T I O N S                                           
***********************************************************************************************************************/

typedef struct
{
    float array[AFE_SAMPLES];
    uint8_t index;
}afe_sample_type_st;

/***********************************************************************************************************************
*                                    P U B L I C     F U N C T I O N S    D E C L A R A T I O N                      
***********************************************************************************************************************/
/*
* @brief     :This API is used to initialize the Trip computer
* @param     :NULL
* @return    :NULL
* @invocation:This function is invoked by OS
*/
void TC_init(void);

/*
* @brief     :This API is used to Active the IFE computer 
* @param     :NULL
* @return    :NULL
* @invocation:This function is invoked by OS
*/
void IFE_Active(void);

/*
* @brief     :This API is used to Active the AFE computer 
* @param     :NULL
* @return    :NULL
* @invocation:This function is invoked by OS
*/
void AFE_Active(void);

/*
* @brief     :This API is used to Active the AFE computer 
* @param     :NULL
* @return    :NULL
* @invocation:This function is invoked by OS
*/
void DTE_Active(void);

/*
* @brief     :This API is used to Activate the Trip computer 
* @param     :NULL
* @return    :NULL
* @invocation:This function is invoked by OS
*/
void TC_Activate(void);

/*
* @brief     :This API is used to Deactivate the Trip computer 
* @param     :NULL
* @return    :NULL
* @invocation:This function is invoked by OS
*/
void TC_Deactivate(void);

/*
* @brief     :This API is used to Deinit the Trip computer 
* @param     :NULL
* @return    :NULL
* @invocation:This function is invoked by OS
*/
void TC_Deinit(void);

/*
* @brief     :This API is used to display IFE Value
* @param     :void
* @return    :uint32_t
* @invocation:This function is invoked by OS
*/
uint32_t display_IFE(void);

/*
* @brief    This function is used to cold initialize the Trip computer
* @param    None 
* @return   None
*/
void TC_Cold_init(void);

uint32_t displayed_IFE(void);

void Swc_AFE_Writesync(void);

void Swc_AFE_Readsync(void);

void Swc_DTE_Readsync(void);

void Swc_DTE_Writesync(void);

void Swc_AFE_SW_Reset(uint8_t fl_Trip_Index_u8);

/*
* @brief     :This API is used to display AFE Value
* @param     :NULL
* @return    :NULL
* @invocation:This function is invoked by OS
*/
uint32_t display_AFE(uint8_t trip_id);

uint32_t display_DTE(void);

void CanMgr_TC_reception_cbk(void);

void ECM_ADDITION_INFO_Timeout_Callback_0x135(void);

void CanMgr_TC_Timeout_Flag(void);

void TC_Set_Unit(uint8_t  p_Unit_Sel_u8);

bool Swc_TC_Get_CAN_Bus_OFF_Status(void);

void Swc_AFE_FUEL_WriteSync(void);

void TC_Warm_init(void);

typedef enum
{
    TC_IFE_UNIT_KMPL = 2,
    TC_IFE_UNIT_LP100KM = 1
}Trip_IFE_Unit_Type;

/*
* @brief    This function is used to validate Current AFE value in L/100km unit 
* @param    uint32_t *p_AVF_Val -  pointer to data
* @return   NONE
* @note:    N/A
*/
void SWC_TC_Max_Limit_Check_For_AVF_In_LPer100KM(uint32_t *p_AVF_Val);

/*
* @brief    This function is used to validate Current RTMI value in L/100km unit 
* @param    uint32_t *p_AVF_Val -  pointer to data
* @return   NONE
* @note:    N/A
*/
void SWC_TC_Max_Limit_Check_For_RTMI_In_LPer100KM(uint32_t *p_AVF_Val);
/***********************************************************************************************************************
                                             E N D   O F   S O F T W A R E                                         
*********************************************************************************************************************/


/***********************************************************************************************************************
*                                              R E V I S I O N   H I S T O R Y                                       
***********************************************************************************************************************
REVISION NUMBER      : V1.0.0                                                
REVISION DATE        : 11-03-2021                             
CREATED / REVISED BY : maheswari@niyatainfotech.com   
DESCRIPTION          : Initial version 

REVISION NUMBER      : V1.0.1                                                
REVISION DATE        : 16-03-2021                             
CREATED / REVISED BY : maheswari@niyatainfotech.com   
DESCRIPTION          : Invocation added 

REVISION NUMBER      : V1.0.2                                                
REVISION DATE        : 24-01-2023                             
CREATED / REVISED BY : palanikumar@niyatainfotech.com   
DESCRIPTION          : API's for Max limit check for AFE , RTMI added. 
------------------------------------------------------------------------------------------------------------------------

***********************************************************************************************************************/
#endif /* ! TTMGR_H */

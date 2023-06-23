/* @file UDS_DTCAPP_H */
#ifndef UDS_DTCAPP_H
#define UDS_DTCAPP_H

/***********************************************************************************************************************
*    DISCLAIMER
*   Copyright (C) 2011, 2016 Niyata Infotech Pvt. Ltd. All rights reserved.                                             
***********************************************************************************************************************/

/************************************************************************************************************************
* @author              Author : Sharmili N (sharmili@niyatainfotech.com)                                                                        
***********************************************************************************************************************/

/***********************************************************************************************************************
*                                                F I L E  D E S C R I P T I O N                                        
**----------------------------------------------------------------------------------------------------------------------
 *  @brief
 *
 *  File name                       : Uds_DtcApp.h
 *  Version                         : V1.0.0
 *  Micros supported                : Micro Agnostic (Independent)
 *  Compilers supported             : XXXXX
 *  Platforms supported             : XXXXX 
 *  Description                     : This header file contains the declarations of Uds_DtcApp (Application) Layer
 *  @bug                            : N/A
--------------------------------------------------------------------------------------------------------------------*/

/**********************************************************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif
/**********************************************************************************************************************/
/***********************************************************************************************************************
*                                               I N C L U D E   F I L E S 
***********************************************************************************************************************/
#include "Uds_Types.h"
#include "hal_stdtypes.h"

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


/***********************************************************************************************************************
*                                          T Y P E   D E F I N I T I O N S                                           
***********************************************************************************************************************/

/*
 * @brief    This typedef is used to define 
 * @param    
 * @return
 **/


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
* @brief    This API is used to Initialize the Dtc Application Layer
* @param    NULL
* @return   NULL
*/
void Uds_DtcApp_Init(void);

/*
* @brief    This API is used to Deinitialize  the Dtc Appliation Layer
* @param    NULL
* @return   NULL
*/
void Uds_DtcApp_DeInit(void);

/*
* @brief    This API is used to execute the periodic task of Dtc Application  Layer
* @param    NULL
* @return   NULL
*/
void Uds_DtcApp_MainFunction(void);

/*
* @brief    This API is used to Control the DTC Setting upon 0x85 service request as ON (0x85 01)
* @param    NULL
* @return   NULL
*/
void Uds_DtcApp_Enable_DTC_Logging_0x85(void);

/*
* @brief    This API is used to Control the DTC Setting upon 0x85 service request as OFF (0x85 02)
* @param    NULL
* @return   NULL
*/
void Uds_DtcApp_Disable_DTC_Logging_0x85(void);

/*
* @brief    This API is used to get the status of DTC Setting
* @param    uint8_t - DTC setting status - DTC_SETTING_ON/DTC_SETTING_OFF
* @return   NULL
*/
uint8_t Uds_DtcApp_Get_MonitoringStatus(void);

/*
* @brief    This API is used to Get the Record information from Appllication when the 3rd bit confirmedDTC bit
* @param    fl_DtcIndex_u8 - Index of the DTC information table
* @param    fl_DataPtr_u8 - Data pointer with Error data ( Snapshot/ Stored/ Extended Data)
* @param    fl_DLC_u8 - Length of the Data record received through pointer
* @return   
*/
void Uds_DtcApp_Get_Record_Info(uint8_t fl_DtcIndex_u8, uint8_t* fl_DataPtr_u8, uint8_t* fl_DLC_u8);

/*
* @brief    This API is used to Read the Diagnostic information when requested by the Client through service 0x19 
            for subfunctions with Uer-Specific details
* @param    fl_pdiagdata_u8 - Data associated with the 0x19 request 
* @param    fl_DataPtr_u8 - Pointer to return with updated data read from DTC layer to UdsApp layer
* @param    fl_DLC_u8 - Length of the Data returned through pointer above
* @return   
*/
void Uds_DtcApp_ReadDtc_Info(const uint8_t *fl_pdiagdata_u8, uint8_t *fl_DataPtr_u8, uint8_t *fl_DLC_u8);

/*
* @brief    This API is used to get the Warning Indicator status whether conditions satisfied or not
* @param    fl_DtcIndex_u8 - Index of the DTC information table
* @return   Warning indicator THRESHOLD SATISFIED - E_OK, Warning indicator THRESHOLD NOT SATISFIED- E_NOT_OK/
*/
uint8_t  Uds_DtcApp_WarningIndicator_Status(uint8_t fl_dtcindex_u8);


/***********************************************************************************************************************
                                              E N D   O F   S O F T W A R E                                         
*********************************************************************************************************************/
#ifdef __cplusplus
}
#endif

/***********************************************************************************************************************
*                                              R E V I S I O N   H I S T O R Y                                       
***********************************************************************************************************************
    REVISION NUMBER      : V1.0.0                                                           
    REVISION DATE        : 26-June-2020                                  
    CREATED / REVISED BY : Sharmili N (sharmili@niyatainfotech.com)   
    DESCRIPTION          : Initial version                                  
------------------------------------------------------------------------------------------------------------------------

***********************************************************************************************************************/
#endif /* ! UDS_DTCAPP_H */

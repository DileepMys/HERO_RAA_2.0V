/* @file UDS_DTCAPP_C */
#ifndef UDS_DTCAPP_C
#define UDS_DTCAPP_C

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
 *  File name                       : Uds_DtcApp.c
 *  Version                         : V1.0.0
 *  Micros supported                : Micro Agnostic (Independent)
 *  Compilers supported             : XXXXX
 *  Platforms supported             : XXXXX 
 *  Description                     : This header file contains the definitions of Uds_DtcApp (Application) Layer
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
#include "Uds_DtcApp.h"
#include "Uds_Dtc_Types.h"
/***********************************************************************************************************************
 *                                          M A C R O   D E F I N I T I O N S
 ***********************************************************************************************************************/

/*  
 * @brief: This macro is used to 
 * @Unit:  
 * @Resolution: 
 * @Range: 
 * @Applicability: 
 */

/***********************************************************************************************************************
 *                                          L O C A L  V A R I A B L E   D E F I N I T I O N S
 ***********************************************************************************************************************/
/*
 * @brief: This variable is used to hold the DTC setting status
 * @Unit:  N/A
 * @Resolution: N/A  
 * @Range: DTC_SETTING_ON/ DTC_SETTING_OFF
 * @Applicability: Yes
 */
static uint8_t l_DTC_Setting_Status_u8;
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
* @brief    This API is used to Initialize the Dtc Application Layer
* @param    NULL
* @return   NULL
*/
void Uds_DtcApp_Init(void)
{
        /*User-Specific implementation*/
}

/*
* @brief    This API is used to Deinitialize  the Dtc Appliation Layer
* @param    NULL
* @return   NULL
*/
void Uds_DtcApp_DeInit(void)
{
        /*User-Specific implementation*/
}

/*
* @brief    This API is used to execute the periodic task of Dtc Application  Layer
* @param    NULL
* @return   NULL
*/
void Uds_DtcApp_MainFunction(void)
{
        /*User-Specific implementation*/
}

/*
* @brief    This API is used to Control the DTC Setting upon 0x85 service request as ON (0x85 01)
* @param    NULL
* @return   NULL
*/
void Uds_DtcApp_Enable_DTC_Logging_0x85(void)
{
    /*Enable the DTC setting mode as ON as per the request*/
    l_DTC_Setting_Status_u8 = DTC_SETTING_ON;
}

/*
* @brief    This API is used to Control the DTC Setting upon 0x85 service request as OFF (0x85 02)
* @param    NULL
* @return   NULL
*/
void Uds_DtcApp_Disable_DTC_Logging_0x85(void)
{
    /*Enable the DTC setting mode as ON as per the request*/
    l_DTC_Setting_Status_u8 = DTC_SETTING_OFF;
}

/*
* @brief    This API is used to get the status of DTC Setting
* @param    uint8_t - DTC setting status - DTC_SETTING_ON/DTC_SETTING_OFF
* @return   NULL
*/
uint8_t Uds_DtcApp_Get_MonitoringStatus(void)
{
    /*Expose the Control DTC setting status*/
    return l_DTC_Setting_Status_u8;
}

/*
* @brief    This API is used to Get the Record information from Appllication when the 3rd bit confirmedDTC bit
* @param    fl_DtcIndex_u8 - Index of the DTC information table
* @param    fl_DataPtr_u8 - Data pointer with Error data ( Snapshot/ Stored/ Extended Data)
* @param    fl_DLC_u8 - Length of the Data record received through pointer
* @return   
*/
void Uds_DtcApp_Get_Record_Info(uint8_t fl_DtcIndex_u8, uint8_t *fl_DataPtr_u8, uint8_t *fl_DLC_u8)
{
        /*User-Specific implementation to fetch data record from Application*/
}

/*
* @brief    This API is used to Read the Diagnostic information when requested by the Client through service 0x19 
            for subfunctions with Uer-Specific details
* @param    fl_pdiagdata_u8 - Data associated with the 0x19 request 
* @param    fl_DataPtr_u8 - Pointer to return with updated data read from DTC layer to UdsApp layer
* @param    fl_DLC_u8 - Length of the Data returned through pointer above
* @return   
*/
void Uds_DtcApp_ReadDtc_Info(const uint8_t *fl_pdiagdata_u8, uint8_t *fl_DataPtr_u8, uint8_t *fl_DLC_u8)
{
    uint8_t fl_subfunction_u8 = (fl_pdiagdata_u8[0] & ((uint8_t)0x7F));
    switch(fl_subfunction_u8)
    {
        case (uint8_t)0x03:
                /*User-Specific implementation*/
                break;

        case (uint8_t)0x04:
                /*User-Specific implementation*/
                break;

        case ((uint8_t)0x05):
                /*User-Specific implementation*/
                break;

        case (uint8_t)0x06:
                /*User-Specific implementation*/
                break;

        case (uint8_t)0x07:
                /*User-Specific implementation*/
                break;

        case (uint8_t)0x08:
               /*User-Specific implementation*/
                break;

        case (uint8_t)0x09:
                /*User-Specific implementation*/
                break;

        case (uint8_t)0x10:
                /*User-Specific implementation*/
                break;

        case (uint8_t)0x0B:
                /*User-Specific implementation*/
                break;

        case (uint8_t)0x0C:
                /*User-Specific implementation*/
                break;
        
        case (uint8_t)0x0D:
                /*User-Specific implementation*/
                break;

        case (uint8_t)0x0E:
                /*User-Specific implementation*/
                break;

        case (uint8_t)0x0F:
                /*User-Specific implementation*/
                break;

        case (uint8_t)0x11:
                /*User-Specific implementation*/
                break;

        case (uint8_t)0x12:
                /*User-Specific implementation*/
                break;

        case (uint8_t)0x13:
                /*User-Specific implementation*/
                break;

        case (uint8_t)0x14:
                /*User-Specific implementation*/
                break;

        case (uint8_t)0x15:
                /*User-Specific implementation*/
                break;

        case (uint8_t)0x16:
                /*User-Specific implementation*/
                break;

        case (uint8_t)0x17:
                /*User-Specific implementation*/
                break;

        case (uint8_t)0x18:
                /*User-Specific implementation*/
                break;

        case (uint8_t)0x19:
                /*User-Specific implementation*/
                break;

        case (uint8_t)0x42:
                /*User-Specific implementation*/
                break;

        case (uint8_t)0x55:
                /*User-Specific implementation*/
                break;

        default:
                /*Do nothing*/
                break;
    }    
}

/*
* @brief    This API is used to get the Warning Indicator status whether conditions satisfied or not
* @param    fl_DtcIndex_u8 - Index of the DTC information table
* @return   Warning indicator THRESHOLD SATISFIED - E_OK, Warning indicator THRESHOLD NOT SATISFIED- E_NOT_OK/
* @note     This API has to be implemented and utilized by Vehicle Manufacturer if the 7th bit of status byte is used
*/
uint8_t  Uds_DtcApp_WarningIndicator_Status(uint8_t fl_dtcindex_u8)
{
        /*User-Specific implementation*/
    return E_NOT_OK;
}

/***********************************************************************************************************************
                                              E N D   O F   S O F T W A R E                                         
 **********************************************************************************************************************/
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
#endif /* ! UDS_DTCAPP_C */

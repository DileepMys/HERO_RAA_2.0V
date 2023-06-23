/* @file UDSAPP_SUPPORT_CFG_C */
#ifndef UDSAPP_SUPPORT_CFG_C
#define UDSAPP_SUPPORT_CFG_C

/***********************************************************************************************************************
*   DISCLAIMER
*   Copyright © 2011, 2016 Niyata Infotech Pvt. Ltd. All rights reserved.                                             
***********************************************************************************************************************/

/***********************************************************************************************************************
*                                                F I L E  D E S C R I P T I O N                                        
**----------------------------------------------------------------------------------------------------------------------
*  @brief
*
*  File name                       : UdsApp_Support_Cfg.c
*  Generation Time                 : 18-10-2022 16:41:17
*  Tool Version                    : UDS_Configurator  2.2.1.0
*  Description                     : This file consists of Configurations of the Support file APIs
*  @bug                          
--------------------------------------------------------------------------------------------------------------------*/

/**********************************************************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif
/**********************************************************************************************************************/

/***********************************************************************************************************************
*                                               I N C L U D E   CONFIGURATION F I L E S 
***********************************************************************************************************************/
#include "UdsApp_Support_Cfg.h"
#include "UdsApp_Cfg.h"
/*********************************************************************************************************************
*                                          M A C R O   D E F I N I T I O N S                                          
*********************************************************************************************************************/

/***********************************************************************************************************************
*                                          C O N F I G U R A T I O N  V A R I A B L E   D E F I N I T I O N S                                           
***********************************************************************************************************************/

/**************************************** READ DATA BY IDENTIFIER - 0x22 *************************************************/
#if(UDS_READ_DID_SID_0x22_FEATURE == STD_ON)
/**
 *
 * @brief    This configurable variable is used to maintain the corresponding information required to handle
 *           Read DID service
 * @Unit  N/A
 * @Resolution N/A
 * @Range N/A
 * @Applicability YES if 0x22 service enabled
 * @param    1. DID         - Requested Data ID
 * @param    2. Block_Id    - Block ID in  NvM 
 **/
const UdsApp_Support_Nvm_st g_Read_NVM_Data_st[READ_NVM_MAX_DID] = { \

    {                              \
        PROGRAMING_DATE_DID,         \
        NVM_APPLICATION_SOFTWARE_PROGRAMMING_DATE
    },                             \
	{                              \
        FINGERPRINT_DATA_DID,         \
        NVM_FINGERPRINT_DATA_DID
    },                             \
   
    {                              \
        PROGRAMMING_ATTEMPT_COUNTER_DID,\
        NVM_PROGRAMMING_ATTEMPT_COUNTER
    },
    {                              \
        PROGRAMMING_SUCCESS_COUNTER_DID,\
        NVM_PROGRAMMING_SUCCESS_COUNTER
    },

       {   BOOTLOADER_VERSION_DID,         \
    	 NVM_BOOTLOADER_VERSION
       }
 

};

/**
 * @brief    This configurable variable is used to maintain the corresponding information required to handle
 *           Read DID service thorugh ROM
 * @Unit  N/A
 * @Resolution N/A
 * @Range N/A
 * @Applicability YES if 0x22 service enabled
 * @param    DID             - Requested Data ID
 * @param    StartAddress    - Start address of the sector
 **/
const UdsApp_Support_ROM_st g_Read_ROM_Data_st[READ_ROM_MAX_DID] = {
                            
 										
   
};
#endif
/**************************************************************************************************************************/

/**************************************** WRITE DATA BY IDENTIFIER - 0x2E *************************************************/
#if(UDS_WRITE_DID_SID_0x2E_FEATURE == STD_ON)
/**
 * @brief    This configurable variable is used to maintain the corresponding information required to handle
 *           Write DID servce
 * @Unit  N/A
 * @Resolution N/A
 * @Range N/A
 * @Applicability YES if 0x2E service enabled
 * @param    1. DID         - Requested Data ID
 * @param    2. Block_Id    - Block ID in  NvM 
 *  Example:
 * const UdsApp_Support_Nvm_st g_Write_NVM_Data_st[WRITE_NVM_MAX_DID] = { \
    {                              \
             BMS_HW_PART_NUMBER,         \
             1u
         },                             \
         {                              \
             DCDC_HW_PART_NUMBER,         \
             2u
         },                             \

};
 * */
const UdsApp_Support_Nvm_st g_Write_NVM_Data_st[WRITE_NVM_MAX_DID] = { \
    {                              \
        PROGRAMING_DATE_DID,       \
        NVM_APPLICATION_SOFTWARE_PROGRAMMING_DATE
    },                             \
    {                              \
        FINGERPRINT_DATA_DID,      \
        NVM_FINGERPRINT_DATA_DID
    },
   {                              \
		PROGRAMMING_ATTEMPT_COUNTER_DID,\
		NVM_PROGRAMMING_ATTEMPT_COUNTER
	},
	{                              \
		PROGRAMMING_SUCCESS_COUNTER_DID,\
		NVM_PROGRAMMING_SUCCESS_COUNTER
	},

    {   BOOTLOADER_VERSION_DID,         \
    	NVM_BOOTLOADER_VERSION
    }


};

/**
 * @brief    This configurable variable is used to maintain the corresponding information required to handle
 *           Write DID service thorugh ROM
 * @Unit  N/A
 * @Resolution N/A
 * @Range N/A
 * @Applicability YES if 0x2E service enabled
 * @param    DID             - Requested Data ID
 * @param    StartAddress    - Start address of the sector
 * Example:
 * const UdsApp_Support_ROM_st g_Write_ROM_Data_st[WRITE_ROM_MAX_DID] = {
    {
        BMS_SW_PART_NUMBER,
        (UDS_UINT8 *)0x00008000
    },
    {
        DCDC_SW_PART_NUMBER,
        (UDS_UINT8 *)0x00008020
    }
};

 * */
const UdsApp_Support_ROM_st g_Write_ROM_Data_st[WRITE_ROM_MAX_DID] = {

    {   BOOTLOADER_VERSION_DID,         \
    	(UDS_UINT8*)0X00004000
    }
};
#endif
/**************************************************************************************************************************/

/***********************************************************************************************************************
                                              E N D   O F   S O F T W A R E                                         
**********************************************************************************************************************/
#ifdef __cplusplus
}
#endif

#endif /* ! UDSAPP_SUPPORT_CFG_C */

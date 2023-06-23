/* @file UDSAPP_SUPPORT_CFG_H */
#ifndef UDSAPP_SUPPORT_CFG_H
#define UDSAPP_SUPPORT_CFG_H

/***********************************************************************************************************************
*   DISCLAIMER
*   Copyright © 2011, 2016 Niyata Infotech Pvt. Ltd. All rights reserved.                                             
***********************************************************************************************************************/

/***********************************************************************************************************************
*                                                F I L E  D E S C R I P T I O N                                        
**----------------------------------------------------------------------------------------------------------------------
*  @brief
*
*  File name                       : UdsApp_Support_Cfg.h
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
#include "Uds_Types.h"
#include "UDS_Cfg.h"
#include "UdsApp_Support.h"
/*********************************************************************************************************************
*                                          M A C R O   D E F I N I T I O N S                                          
*********************************************************************************************************************/
/**************************************** READ DATA BY IDENTIFIER - 0x22 *************************************************/
#if(UDS_READ_DID_SID_0x22_FEATURE == STD_ON)
/*
* @brief: This macro is used to configure the total number of DIDs are available that could be read from NvM
  @param: None
  @Unit:  N/A
  @Resolution: 1
  @Range: N/A
  @Applicability: YES if 0x22 service enabled
*/
#define READ_NVM_MAX_DID     5u

/*
* @brief: This macro is used to configure the total number of DIDs are available that could be read from ROM
  @param: None
  @Unit:  N/A
  @Resolution: 1
  @Range: N/A
  @Applicability: YES if 0x22 service enabled
*/
#define READ_ROM_MAX_DID     0u

#endif
/****************************************************************************************************************/

/**************************************** WRITE DATA BY IDENTIFIER - 0x2E *************************************************/
#if(UDS_WRITE_DID_SID_0x2E_FEATURE == STD_ON)
/*
* @brief: This macro is used to configure the total number of DIDs are available that could be written to NvM
  @param: None
  @Unit:  N/A
  @Resolution: 1
  @Range: N/A
  @Applicability: YES if 0x2E service enabled
*/
#define WRITE_NVM_MAX_DID     5u

/*
* @brief: This macro is used to configure the total number of DIDs are available that could be written to ROM
  @param: None
  @Unit:  N/A
  @Resolution: 1
  @Range: N/A
  @Applicability: YES if 0x2E service enabled
*/
#define WRITE_ROM_MAX_DID     1u

/*
* @brief: This macro is used to configure the Flash Handler Erase Request initialization to access Shared ROM
  @param: None
  @Unit:  N/A
  @Resolution: N/A
  @Range: N/A
  @Applicability: User specific
*/
#define SUPPORT_FLASH_HANDLER_ERASEREQ_INIT(a, b)                     0

/*
* @brief: This macro is used to configure the Flash Handler Writing API in Shared ROM region
  @param: None
  @Unit:  N/A
  @Resolution: N/A
  @Range: N/A
  @Applicability: User specific
*/
#define SUPPORT_FLASH_HANDLER_ISSUE_PRGRM_CMD(a, b, c)      FlashHandler_IssueProgramCmd(a, b, c)
#endif
/**********************************************************************************************************************/

/***********************************************************************************************************************
*                                          C O N F I G U R A T I O N  V A R I A B L E   D E F I N I T I O N S                                           
***********************************************************************************************************************/

/**************************************** READ DATA BY IDENTIFIER - 0x22 *************************************************/
#if(UDS_READ_DID_SID_0x22_FEATURE == STD_ON)
/*
 * @brief    This configurable variable is used to maintain the corresponding information required to handle DID 
 * @Unit  N/A
 * @Resolution N/A
 * @Range N/A
 * @Applicability YES if 0x22 service enabled
 * @param    1. DID         - Requested Data ID
 * @param    2. Block_Id    - Block ID in  NvM 
 **/
extern const UdsApp_Support_Nvm_st g_Read_NVM_Data_st[READ_NVM_MAX_DID];

/*
 * @brief    This configurable variable is used to maintain the corresponding information required to handle
 *           Read DID service thorugh ROM
 * @Unit  N/A
 * @Resolution N/A
 * @Range N/A
 * @Applicability YES if 0x22 service enabled
 * @param    DID             - Requested Data ID
 * @param    StartAddress    - Start address of the sector
 **/
extern const UdsApp_Support_ROM_st g_Read_ROM_Data_st[READ_ROM_MAX_DID];
#endif
/**************************************************************************************************************************/

/**************************************** WRITE DATA BY IDENTIFIER - 0x2E *************************************************/
#if(UDS_WRITE_DID_SID_0x2E_FEATURE == STD_ON)
/*
 * @brief    This configurable variable is used to maintain the corresponding information required to handle
 *           Write DID servce
 * @Unit  N/A
 * @Resolution N/A
 * @Range N/A
 * @Applicability YES if 0x2E service enabled
 * @param    1. DID         - Requested Data ID
 * @param    2. Block_Id    - Block ID in  NvM 
 **/
extern const UdsApp_Support_Nvm_st g_Write_NVM_Data_st[WRITE_NVM_MAX_DID];

/*
 * @brief    This configurable variable is used to maintain the corresponding information required to handle
 *           Write DID service thorugh ROM
 * @Unit  N/A
 * @Resolution N/A
 * @Range N/A
 * @Applicability YES if 0x2E service enabled
 * @param    DID             - Requested Data ID
 * @param    StartAddress    - Start address of the sector
 **/
extern const UdsApp_Support_ROM_st g_Write_ROM_Data_st[WRITE_ROM_MAX_DID];
#endif
/**********************************************************************************************************************/
/***********************************************************************************************************************
                                              E N D   O F   S O F T W A R E                                         
**********************************************************************************************************************/
#ifdef __cplusplus
}
#endif
#endif /* ! UDSAPP_SUPPORT_CFG_H */

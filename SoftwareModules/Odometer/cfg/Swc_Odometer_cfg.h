/* @file FILE NAME */
#ifndef ODO_CFG_H
#define ODO_CFG_H

/***********************************************************************************************************************
*   DISCLAIMER
*   Copyright © , 2021 Niyata Infotech Ptv. Ltd. All rights reserved.                                             
***********************************************************************************************************************/

/************************************************************************************************************************
* @author              Author : R.Maheswari (maheswari@niyatainfotech.com)                                                                         
***********************************************************************************************************************/

/***********************************************************************************************************************
*                                                F I L E  D E S C R I P T I O N                                        
**----------------------------------------------------------------------------------------------------------------------
*  @brief
*
*  File name                       : ODO_Cfg.h
*  Version                         : V1.0.2
*  Micros supported                : Micro Independent
*  Compilers supported             : Compiler Independent
*  Platforms supported             : Platform Independent
*  Description                     : This file contains the configuration declarations of Odometer
*  @bug                            : N/A
----------------------------------------------------------------------------------------------------------------------*/

/**********************************************************************************************************************/


/***********************************************************************************************************************
*                                               I N C L U D E   F I L E S 
***********************************************************************************************************************/
#include "Swc_Odometer.h"
#include "Swc_Odometer_cfg.h"
#include "Swc_Trip_Timer.h"
#include "Swc_NVM_Handler.h"
/***********************************************************************************************************************
*                                      V E R S I O N   I N T E G R I T Y  C H E C K                                  
***********************************************************************************************************************/

/***********************************************************************************************************************
*                                     C O N F I G U R A T I O N     M A C R O S                      
***********************************************************************************************************************/


/*
* @brief          : This macro is used to configure the function of Get Trip switch
* @Unit           : N/A
* @Resolution:    : 1
* @Range          : 0 to 8 bit
* @Applicability  : Selection of TRIP ID
* @Note           : Do not modify this macro value or name
*/
/*#define ODO_GET_TRIP_ID*/


/*
* @brief          : This macro is used to configure the NVM Write Life cycle
* @Unit           : N/A
* @Resolution:    : 1
* @Range          : 0 to 32 bit
* @Applicability  : NVM block size is computed using this configuration
* @Note           : Do not modify this macro value or name
*/
/*#define ODO_NVM_WRITE_CYCLE          (uint32_t)1000000U*/


/*
* @brief          : This macro is used to configure the maximum number of TRIP switches
* @Unit           : N/A
* @Resolution:    : 1
* @Range          : 0 to 32 bit
* @Applicability  : This value is used to compute the Trip distance for Trip switches
* @Note           : Do not modify this macro value or name
*/
#define ODO_TRIP_MAX                   2u







/***********************************************************************************************************************
*                             C O N F I G U R A T I O N    C O N S T A N T S    D E C L A R A T I O N                       
***********************************************************************************************************************/

/***********************************************************************************************************************
*                            C O N F I G U R A T I O N    V A R I A B L E S    D E C L A R A T I O N                  
***********************************************************************************************************************/

/*********************************************************************************************************************
*                         C O N F I G U R A T I O N     F U N C T I O N    D E C L A R A T I O N S                      
*********************************************************************************************************************/

/***********************************************************************************************************************
                                              E N D   O F   S O F T W A R E                                         
**********************************************************************************************************************/


/***********************************************************************************************************************
*                                              R E V I S I O N   H I S T O R Y                                       
************************************************************************************************************************
REVISION NUMBER      : V1.0.0
REVISION DATE        : 30-April-2021
CREATED / REVISED BY : Maheswari R(maheswari@niyatainfotech.com)
DESCRIPTION          : Initial Version


REVISION NUMBER      : V1.0.1
REVISION DATE        : 26-May-2021
CREATED / REVISED BY : Maheswari R(maheswari@niyatainfotech.com)
DESCRIPTION          : Peer Review comments fixed 

REVISION NUMBER      : V1.0.2
REVISION DATE        : 26-May-2021
CREATED / REVISED BY : Palani kumar R(palanikumar@niyatainfotech.com)
DESCRIPTION          : ODO_INIT_VALID_DATA_REQUIRED macro is added for CRC and Parity check to NVM Error
------------------------------------------------------------------------------------------------------------------------

***********************************************************************************************************************/
#endif /* !ODO_CFG_H */

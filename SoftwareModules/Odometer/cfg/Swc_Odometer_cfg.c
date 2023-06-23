
/* @file ODO_H */
#ifndef ODO_TYPES_H
#define ODO_TYPES_H

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
*  File name                       : ODO_Types.h
*  Version                         : V1.0.1
*  Micros supported                : Micro Independent
*  Compilers supported             : Compiler Independent
*  Platforms supported             : Platform Independent                
*  Description                     : This header file contains the declarations of Odometer
*  @bug                            : N/A
--------------------------------------------------------------------------------------------------------------------*/
/**********************************************************************************************************************/

/***********************************************************************************************************************
*                                               I N C L U D E   C O N F I G U R A T I O N   F I L E S 
***********************************************************************************************************************/
#include "Swc_Odometer_Cfg.h"

/***********************************************************************************************************************
                                             I N C L U D E  CONDITION BASED   F I L E S                             
***********************************************************************************************************************/

/***********************************************************************************************************************
*                                      V E R S I O N   I N T E G R I T Y  C H E C K                                  
***********************************************************************************************************************/

/***********************************************************************************************************************
*                                             M A C R O   D E F I N I T I O N S                                         
***********************************************************************************************************************/


/*
* @brief          : This macro is used to configure the Trip switches
* @Unit           : N/A
* @Resolution:    : 1
* @Range          : 0 to 8 bit
* @Applicability  : Selection of Trip switches for trip distance computation
* @Note           : Do not modify this macro value or name
*/
#if (ODO_TRIP_MAX > 0)
#define ODO_TRIP1  0u
#elif (ODO_TRIP_MAX >(uint8_t)1)
#define ODO_TRIP1  0u
#define ODO_TRIP2  1u
#elif (ODO_TRIP_MAX >(uint8_t)2)
#define ODO_TRIP1  0u
#define ODO_TRIP2  1u
#define ODO_TRIP3  2u
#elif (ODO_TRIP_MAX >(uint8_t)3)
#define ODO_TRIP1  0u
#define ODO_TRIP2  1u
#define ODO_TRIP3  2u
#define ODO_TRIP4  3u
#else
#define ODO_TRIP1  0u
#define ODO_TRIP2  1u
#define ODO_TRIP3  2u
#define ODO_TRIP4  3u
#define ODO_TRIP5  4u
#endif


/***********************************************************************************************************************
*                                          T Y P E   D E F I N I T I O N S                                           
***********************************************************************************************************************/

/***********************************************************************************************************************
*                                    P U B L I C     F U N C T I O N S    D E C L A R A T I O N                      
***********************************************************************************************************************/



/***********************************************************************************************************************
                                             E N D   O F   S O F T W A R E                                         
*********************************************************************************************************************/

/***********************************************************************************************************************
                                             E N D   O F   S O F T W A R E                                         
*********************************************************************************************************************/


/***********************************************************************************************************************
*                                              R E V I S I O N   H I S T O R Y                                       
***********************************************************************************************************************
REVISION NUMBER      : V1.0.0                                                
REVISION DATE        : 30-04-2021                             
CREATED / REVISED BY : maheswari@niyatainfotech.com   
DESCRIPTION          : Initial version 

REVISION NUMBER      : V1.0.1
REVISION DATE        : 26-May-2021
CREATED / REVISED BY : Maheswari R(maheswari@niyatainfotech.com)
DESCRIPTION          : Peer Review comments fixed 


------------------------------------------------------------------------------------------------------------------------

***********************************************************************************************************************/
#endif /* ! ODO_H */
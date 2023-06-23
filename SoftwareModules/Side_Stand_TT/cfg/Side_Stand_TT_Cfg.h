/* @file FILE NAME */
#ifndef Side_Stand_TT_CFG_H
#define Side_Stand_TT_CFG_H

/***********************************************************************************************************************
*    DISCLAIMER
*   Copyright (C) 2020 Niyata Infotech Pvt. Ltd. All rights reserved.                                             
***********************************************************************************************************************/

/************************************************************************************************************************
* @author              Author : Rubina Josphine B (rubinajosphine@niyatainfotech.com)                                                                         
***********************************************************************************************************************/

/***********************************************************************************************************************
*                                                F I L E  D E S C R I P T I O N                                        
**----------------------------------------------------------------------------------------------------------------------
*  @brief
*
*  File name                       : Side_Stand_TT_cfg.h
*  Version                         : v1.0.0
*  Micros supported                : Micro Independent
*  Compilers supported             : J Link
*  Platforms supported             : Platform Independent               
*  Description                     : This file consists of declaration of side stand telltale
*  @bug                            : N/A                            : 
*--------------------------------------------------------------------------------------------------------------------*/

/**********************************************************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif
/**********************************************************************************************************************/
/***********************************************************************************************************************
*                                               I N C L U D E   F I L E S 
***********************************************************************************************************************/
#include "Side_Stand_TT.h"
#include"pin_mux.h"
#include "stdbool.h"
#include "MIMXRT1172.h"
#include "fsl_flexcan.h"

/***********************************************************************************************************************
*                                      V E R S I O N   I N T E G R I T Y  C H E C K                                  
***********************************************************************************************************************/

/***********************************************************************************************************************
*                                    C O N F I G U R A T I O N     M A C R O S                      
***********************************************************************************************************************/
/*
* @brief: This macro is used to configure the IGN ON
* @Unit:  Nil
* @Resolution: Nil
* @Range: Nil
* @Applicability: N/A
* @Note: 
*/
#define IGNITION_ON  1

/*
* @brief: This macro is used to configure the IGN OFF
* @Unit:  Nil
* @Resolution: Nil
* @Range: Nil
* @Applicability: N/A
* @Note: 
*/
#define IGNITION_OFF 0

/*
* @brief: This macro is used to configure the side stand TT ON condition
* @Unit:  Nil
* @Resolution: Nil
* @Range: Nil
* @Applicability: N/A
* @Note: 
*/
#define Side_Stand_TT_ON    0x01

/*
* @brief: This macro is used to configure the side stand TT OFF condition
* @Unit:  Nil
* @Resolution: Nil
* @Range: Nil
* @Applicability: N/A
* @Note: 
*/
#define Side_Stand_TT_OFF   0x00

/*
* @brief: This macro is used to configure the Can bus off status
* @Unit:  Nil
* @Resolution: Nil
* @Range: Nil
* @Applicability: N/A
* @Note:: 
*/
#define CAN_BUS_OFF_ST  1

/*
* @brief: This macro is used to configure the side stand CRC 
* @Unit:  Nil
* @Resolution: Nil
* @Range: Nil
* @Applicability: N/A
* @Note: 
*/
#define CRC_INVALID     1

/*
* @brief: This macro is used to configure the Side stand ADC base
* @Unit:  Nil
* @Resolution: Nil
* @Range: Nil
* @Applicability: N/A
* @Note: 
*/
#define SIDESTAND_LPADC_BASE  LPADC2 

/*
* @brief: This macro is used to configure the Side stand Telltale OFF 
* @Unit:  Nil
* @Resolution: Nil
* @Range: Nil
* @Applicability: N/A
* @Note:
*/
#define IC_SS_TELL_TELL_OFF   0x00

/*
* @brief: This macro is used to configure the Side stand Telltale ON
* @Unit:  Nil
* @Resolution: Nil
* @Range: Nil
* @Applicability: N/A
* @Note: 
*/
#define IC_SS_TELL_TELL_ON   0x01

/*
* @brief: This macro is used to configure the No Error stauts
* @Unit:  Nil
* @Resolution: Nil
* @Range: Nil
* @Applicability: N/A
* @Note: 
*/
#define NO_ERROR  0x0

/*
* @brief: This macro is used to configure the Led short status
* @Unit:  Nil
* @Resolution: Nil
* @Range: Nil
* @Applicability: N/A
* @Note: 
*/
#define LED_SHORT 0x1

/*
* @brief: This macro is used to configure the Led open status
* @Unit:  Nil
* @Resolution: Nil
* @Range: Nil
* @Applicability: N/A
* @Note: 
*/
#define LED_OPEN  0x2

/*
* @brief: This macro is used to configure the common error status
* @Unit:  Nil
* @Resolution: Nil
* @Range: Nil
* @Applicability: N/A
* @Note:
*/
#define COMMON_ERROR  0x3



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
#ifdef __cplusplus
}
#endif

/***********************************************************************************************************************
*                                              R E V I S I O N   H I S T O R Y                                       
/***********************************************************************************************************************
  REVISION NUMBER      : V1.0.0
  REVISION DATE        : MONTH/DATE/YEAR                              
  CREATED / REVISED BY : NAME (EMAIL-ID)   
  DESCRIPTION          : Initial version                                  
------------------------------------------------------------------------------------------------------------------------

***********************************************************************************************************************/
#endif /* ! Side_Stand_TT_CFG_H */

/* @file FILE NAME */
#ifndef CANGATEWAY_CFG_C
#define CANGATEWAY_CFG_C

/***********************************************************************************************************************
 *    DISCLAIMER
 *   Copyright (C) 2020 Niyata Infotech Pvt. Ltd. All rights reserved.
 ***********************************************************************************************************************/

/************************************************************************************************************************
 * @author              Author : Balajipandurangan (Balaji.pandurangan@niyatainfotech.com)
 ***********************************************************************************************************************/

/***********************************************************************************************************************
 *                                                F I L E  D E S C R I P T I O N
 **----------------------------------------------------------------------------------------------------------------------
 *  @brief
 *
 *  File name                       : CanGateway_cfg.c
 *  Version                         : V1.0.0
 *  Micros supported                : Micro Independent
 *  Compilers supported             : MCU Xpresso IDE
 *  Platforms supported             : XXXXX
 *  Description                     : This file consists of the configuration definitions of CanGateway
 *  @bug
*--------------------------------------------------------------------------------------------------------------------*/

/**********************************************************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif
/**********************************************************************************************************************/

/***********************************************************************************************************************
*                                               I N C L U D E   F I L E S                                            
***********************************************************************************************************************/
#include "CanGateway_cfg.h"
#include "CanGateway.h"
/***********************************************************************************************************************
*                             C O N F I G U R A T I O N    C O N S T A N T S   D E F I N I T I O N                          
***********************************************************************************************************************/
/*
* @brief: This variable is used to configure the mapping of can2 to can1 frame ID's
* @Unit:  n/a
* @Resolution: n/a
* @Range: n/a
* @Applicability: YES
* @Note:
*/
const CanGateway_ReqRes_ID_st g_CanGateway_Diag_Mapping_Table[REQUEST_GATEWAY_TOTAL_MESSAGES] = {

{
    REQ_DIAG_ANSW_TCU_0X631,
    REQ_DIAGN_ANS_TCU_0X631
},

{
    REQ_DIAG_ANSW_IC_0X632,
    REQ_DIAGN_ANS_TCU_0X631
},

{
    REQ_DIAG_ANSW_ABS_0X6F0,
    REQ_DIAGN_ANS_ABS_0X6F0
},

{
    REQ_DIAG_ANSW_BCM_0X6F1,
    REQ_DIAGN_ANS_BCM_0X6F1
},

{
    REQ_DIAG_ANSW_ECM_0X7E0,
    REQ_DIAGN_ANS_ECM_0X7E0
}

};


/*
* @brief: This variable is used to configure the mapping of can1 to can2 frame ID's
* @Unit:  n/a
* @Resolution: n/a
* @Range: n/a
* @Applicability: YES
* @Note:
*/
const CanGateway_ReqRes_ID_st g_CanGateway_Vehicle_Mapping_Table[RESPONSE_GATEWAY_TOTAL_MESSAGES] = {

{
    DIAG_ANSW_TCU_0X641,
    DIA_ANSW_TCU_0X641
},

{
    REQ_DIAG_ANS_IC_0X632,
    DIAG_ANSW_IC_0X642
},

{
    DIAG_ANS_ABS_0X629,
    DIAG_ANSW_ABS_0X629
},

{
    DIAG_ANS_BCM_0X644,
    DIAG_ANSW_BCM_0X644
},

{
    DIAG_ANS_ECM_0X7E8,
    DIAG_ANSW_ECM_0X7E8
}

};
/***********************************************************************************************************************
*                           C O N F I G U R A T I O N    V A R I A B L E S    D E F I N I T I O N                                            
***********************************************************************************************************************/
/*
* @brief This variable is used to configure the 
* @Unit:  
* @Resolution: 
* @Range: 
* @Applicability: 
* @Note:  
*/

/*********************************************************************************************************************
*                         C O N F I G U R A T I O N     F U N C T I O N    D E F I N I T I O N S                      
*********************************************************************************************************************/
/*
* @brief    This function is used to 
* @param    
* @return 
* @note:  
*/

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
    REVISION DATE        : 07/24/2022                              
    CREATED / REVISED BY : Balaji Pandurangan (balaji.pandurangan@niyatainfotech.com) 
    DESCRIPTION          : Initial version          
------------------------------------------------------------------------------------------------------------------------

 ***********************************************************************************************************************/
#endif /* ! CANGATEWAY_CFG_C */

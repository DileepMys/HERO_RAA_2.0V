/* @file FILE NAME */
#ifndef RTC_H
#define RTC_H

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
*  File name                        : rtc.h
 *  Version                         : v1.0.0
 *  Micros supported                : Micro Independent
 *  Compilers supported             : J link
 *  Platforms supported             : Platform Independent
 *  Description                     : This file consists of declaration of variable and function  of rtc
 *  @bug                            : N/A
--------------------------------------------------------------------------------------------------------------------*/


/***********************************************************************************************************************
*                                               I N C L U D E   CONFIGURATION F I L E S 
***********************************************************************************************************************/
#include "rtc_Cfg.h"
#include "hal_stdtypes.h"
#include "MIMXRT1172.h"
#include "fsl_snvs_lp.h"
#include "fsl_common.h"
/***********************************************************************************************************************
                                               I N C L U D E  CONDITION BASED F I L E S                             
***********************************************************************************************************************/
#if SYSTEM_1
# include "system_1.h"
#elif SYSTEM_2
# include "system_2.h"
#elif SYSTEM_3
#endif


/***********************************************************************************************************************
*                                      V E R S I O N   I N T E G R I T Y  C H E C K                                  
***********************************************************************************************************************/
/* perform integrity check when it is necessary */
#if ( FILE_NAME_H_VERSION != 0x0001 )

#endif
/***********************************************************************************************************************
*                                            M A C R O   D E F I N I T I O N S                                         
***********************************************************************************************************************/

/***********************************************************************************************************************
*                                          T Y P E   D E F I N I T I O N S                                           
***********************************************************************************************************************/

/*
 * @brief    This structure is used to define the date and time elements of the system
 * @param    nil
 * @param    nil
 **/

typedef struct
{
    uint16_t year;  /*!<  from 1970 to 2099.*/
    uint8_t month;  /*!< Range from 1 to 12.*/
    uint8_t day;    /*!< Range from 1 to 31 (depending on month).*/
    uint8_t hour;   /*!< Range from 0 to 23.*/
    uint8_t minute; /*!< Range from 0 to 59.*/
    uint8_t second; /*!< Range from 0 to 59.*/
} RTC_TIME_STAMP_ST;

RTC_TIME_STAMP_ST RTC_Time_Display(void);

/***********************************************************************************************************************
*                                    P U B L I C     F U N C T I O N S    D E C L A R A T I O N                      
***********************************************************************************************************************/


/*
* @brief This API is used to initiate the RTC init variables with default values 
* @Unit: N/A 
* @Resolution: N/A
* @Range: N/A
* @Applicability: NIL 
* @Note:  
*/
void Rtc_Init(void);


/*
* @brief : This API is used to reset the RTC init variables with default values 
* @Unit: N/A 
* @Resolution: N/A
* @Range: N/A
* @Applicability: NIL 
* @Note: 
*/

void Rtc_DeInit(void);
/*
* @brief    This API is used to perform cold init of RTC
* @param    NONE
* @return   NONE
* @invocation 
*/
void RTC_Cold_Init(void);

/*
* @brief : This API is used to activate the RTC init variables with default values 
* @Unit: N/A 
* @Resolution: N/A
* @Range: N/A
* @Applicability: NIL 
* @Note:  
*/
 
void Rtc_Activate(void);


/*
* @brief : This API is used to reset the RTC init variables with default values 
* @Unit: N/A 
* @Resolution: N/A
* @Range: N/A
* @Applicability: NIL 
* @Note:  
*/
 
void Rtc_DeActivate(void);


/*
* @brief : This API is used to execute the RTC 
* @Unit: N/A 
* @Resolution: N/A
* @Range: N/A
* @Applicability: NIL 
* @Note:  
*/
void Rtc_MainFunction(void);


/*!
 * This functionnis to set the date and time according to the given time structure.
 *
 * param base     SNVS peripheral base address
 * param datetime Pointer to the structure where the date and time details are stored.
 *
 * return kStatus_Success: Success in setting the time and starting the SNVS SRTC
 *         kStatus_InvalidArgument: Error because the datetime format is incorrect
 */
status_t RTC_Set_Date_time(SNVS_Type *base_add,  RTC_TIME_STAMP_ST *datetime);


/***********************************************************************************************************************
                                              E N D   O F   S O F T W A R E                                         
*********************************************************************************************************************/
#ifdef __cplusplus
}
#endif

/***********************************************************************************************************************
*                                              R E V I S I O N   H I S T O R Y                                       
/***********************************************************************************************************************
    REVISION NUMBER      : V1.0.0                                               
    REVISION DATE        : 04/06/2022                             
    CREATED / REVISED BY : Rubina Josphine B (rubinajosphine@niyatainfotech.com)   
    DESCRIPTION          : Initial version                                  
------------------------------------------------------------------------------------------------------------------------

***********************************************************************************************************************/
#endif /* ! RTC_H */

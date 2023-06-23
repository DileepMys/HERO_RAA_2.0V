/* @file TTMGR_CFG_H */
#ifndef TTMGR_CFG_H
#define TTMGR_CFG_H

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
*  File name                       : TTMgr_Cfg.h
*  Version                         : V1.0.1
*  Micros supported                : Micro Independent
*  Compilers supported             : Compiler Independent
*  Platforms supported             : Platform Independent
*  Description                     : This file contains the configuration elements of Tell-Tale Manager
*  @bug                            : N/A
----------------------------------------------------------------------------------------------------------------------*/

/**********************************************************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif
/**********************************************************************************************************************/

/***********************************************************************************************************************
*                                               I N C L U D E   CONFIGURATION F I L E S 
***********************************************************************************************************************/


#include "MIMXRT1172.h"
/***********************************************************************************************************************
                                               I N C L U D E  CONDITION BASED F I L E S                             
***********************************************************************************************************************/


/***********************************************************************************************************************
*                                            V E R S I O N   I N T E G R I T Y  C H E C K                                  
***********************************************************************************************************************/


/***********************************************************************************************************************
*                                          M A C R O   D E F I N I T I O N S                                         
***********************************************************************************************************************/

/*
 * @brief: This macro is used to define  the self check count
 * @Unit:  N/A
 * @Resolution: 1
 * @Range: 0 to 255
 * @Applicability: YES
 */
#define TT_SELFCHECK_COUNT    0u

/*
 * @brief: This macro is used to define  the timetask
 * @Unit:  milliseconds
 * @Resolution: 1
 * @Range: 0 to 255
 * @Applicability: YES
 */
#define TT_TIMETASK 		   100u

/*
 * @brief: This macro is used to define  the TT_ON task
 * @Unit:  milliseconds
 * @Resolution: 1
 * @Range: 0 to 255
 * @Applicability: YES
 */
#define TT_ON				  0x01u

/*
 * @brief: This macro is used to define  the TT_OFF task
 * @Unit:  milliseconds
 * @Resolution: 1
 * @Range: 0 to 255
 * @Applicability: YES
 */
#define TT_OFF				  0x00u

/*
 * @brief: This macro is used to define  the TT_FLASH task
 * @Unit:  milliseconds
 * @Resolution: 1
 * @Range: 0 to 255
 * @Applicability: YES
 */
#define TT_FLASH		      0x04u

#define TT_NO_ACTION		0x08u

//#define TT_PORT_PIN		{{TT0}, {TT1}, {TT2}}

//#define TT_GPIO_WRITE(Port_index, Pin_index, value)				GPIO_WriteBit(Port_index, Pin_index, value)

/***********************************************************************************************************************
*                                          T Y P E   D E F I N I T I O N S                                           
***********************************************************************************************************************/

/*
 * @brief: This macros is used to define  the Tell-Tale datatype
 * @Unit:  N/A
 * @Resolution: N/A
 * @Range: N/A
 * @Applicability: YES
 */
typedef unsigned short uint16_t;
typedef unsigned char uint8_t;

/*
 * @brief: This configuration shall configure the Tell-Tale Index
 * @Unit:  milliseconds
 * @Resolution: N/A
 * @Range: 0 to 255
 * @Applicability: YES
 */
typedef enum
{
	Abs_Reminder 	= 0u,
	Side_Stand 	,
	Gear_Position  ,
	Service_Remainder   ,
	Fuel_Bar			,
	CLOCK_COLON			,
	TT_MAX 				
}TT_List_Type_en;


/*
 * @brief: This configuration shall configure the ECU state 
 * @Unit:  N/A
 * @Resolution: N/A
 * @Range: 0 to 255
 * @Applicability: YES
 */
 
typedef enum
{
	ECU_Normal 			=0u,
	ECU_Sleep			=1u,
	ECU_MAX_STATE		=2u
}TT_ECU_State_Type_En;


/*
 * @brief: This configuration shall configure the Tell-Tale Mode
 * @Unit:  N/A
 * @Resolution: N/A
 * @Range: 0 to 255
 * @Applicability: YES
 */
typedef enum
{
	GPIO 				=0u,
	TFT					=1u,
	TT_MAX_MODE			=2u
}TT_Mode_Type_En;

/*
 * @brief: This configuration shall configure the Tell-Tale Operation 
 * @Unit:  N/A
 * @Resolution: N/A
 * @Range: 0 to 255
 * @Applicability: YES
 */
typedef enum
{
	NORMAL 				=0u,
	SAFETY				=1u,
    TT_MAX_OPERATION	=2u
}TT_Operation_Type_En;


/*
 * @brief: This configuration shall configure the Tell-Tale Operation
 * @Unit:  N/A
 * @Resolution: N/A
 * @Range: 0 to 255
 * @Applicability: YES
 */
typedef enum
{
	LED_ON 				=0u,
	LED_OFF				=1u
}TT_Led_Status_Type_En;


/*
 * @brief: This configuration shall configure the Tell-Tale Flash Functionality  
 * @Unit:  N/A
 * @Resolution: N/A
 * @Range: 0 to 255
 * @Applicability: YES
 */
typedef struct
{
	uint16_t TT_Duty;
	uint16_t TT_Frequency;
}TellTale_Flash_Config_Type_St;

/*
 * @brief: This configuration shall configure the NVM Functionality  
 * @Unit:  N/A
 * @Resolution: N/A
 * @Range: 0 to 255
 * @Applicability: YES
 */
typedef enum
{
	VEHICLE_MODEL_LXI	 = 0u,
	VEHICLE_MODEL_VXI	 =1u,
	VEHICLE_MODEL_LXI_VXI=2u,
	VEHICLE_MODEL_MAX	 =3u
}TT_NVM_Config_Type_En;

typedef void (*HMI_TT_ONEvent_CBK_Type)(void);

typedef void (*HMI_TT_OFFEvent_CBK_Type)(void);

/*
 * @brief: This configuration shall configure the Tell-Tale details   
 * @Unit:  N/A
 * @Resolution: N/A
 * @Range: 0 to 255
 * @Applicability: YES
 */
typedef struct
{
	
	TellTale_Flash_Config_Type_St TellTale_Flash_Config_St;
	uint8_t TT_Index;
	uint8_t TT_ECU_State;
	uint8_t TT_Status;
	uint8_t TT_Mode;
	uint8_t TT_Operation;
	uint8_t TT_Vehicle_Model;
	GPIO_Type *Port_Name;
	uint32_t pin;
	HMI_TT_ONEvent_CBK_Type  HMI_TT_ON_CBK;
	HMI_TT_OFFEvent_CBK_Type  HMI_TT_OFF_CBK;
}TT_Const_Details_Type_St;

extern const TT_Const_Details_Type_St g_TT_Const_Details_St[TT_MAX];

/***********************************************************************************************************************
                                              E N D   O F   S O F T W A R E                                         
***********************************************************************************************************************/
#ifdef __cplusplus
}
#endif

/***********************************************************************************************************************
*                                              R E V I S I O N   H I S T O R Y                                       
************************************************************************************************************************
			REVISION NUMBER      : V1.0.0                                                
			REVISION DATE        : 28-12-2020                              
			CREATED / REVISED BY : R Maheswari (maheswari@niyatainfotech.com)   
			DESCRIPTION          : Initial version                                 
------------------------------------------------------------------------------------------------------------------------
			REVISION NUMBER      : V1.0.1                                                
			REVISION DATE        : 20-01-2021                              
			CREATED / REVISED BY : R Maheswari (maheswari@niyatainfotech.com)   
			DESCRIPTION          : Peer reveiew comments fixed 	
***********************************************************************************************************************/
#endif /* !TTMGR_CFG_H */

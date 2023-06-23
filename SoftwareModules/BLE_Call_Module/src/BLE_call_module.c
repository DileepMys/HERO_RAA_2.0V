/* @file FILE NAME */
#ifndef BLE_CALL_MODULE_C
#define BLE_CALL_MODULE_C

/***********************************************************************************************************************
 *    DISCLAIMER
 *   Copyright (C) 2011, 2016 Niyata Infotech Pvt. Ltd. All rights reserved.
 ***********************************************************************************************************************/

/************************************************************************************************************************
 * @author              Author : Jeevajothi (jeevajothi@niyatainfotech.com)
 ***********************************************************************************************************************/

/***********************************************************************************************************************
 *                                                F I L E  D E S C R I P T I O N
 **----------------------------------------------------------------------------------------------------------------------
 *  @brief
 *
 *  File name                       : BLE_call_module.c
 *  Version                         : V1.0.0
 *  Micros supported                : Micro Independent
 *  Compilers supported             : Compiler Independent
 *  Platforms supported             : Platform Independent
 *  Description                     : 
 *  @bug
--------------------------------------------------------------------------------------------------------------------*/



/***********************************************************************************************************************
 *                                               I N C L U D E   F I L E S
 ***********************************************************************************************************************/
#include "BLE_call_module.h"
#include "BLE_call_module_cfg.h"
#include "HMI_Setting_Screen.h"
#include "Swc_System_Service.h"
#include "UART_DataManager.h"
#include "BLE_music_module.h"


/***********************************************************************************************************************
*                                               I N C L U D E  LIBRARY F I L E S                                     
***********************************************************************************************************************/

#include "fsl_debug_console.h"



/***********************************************************************************************************************
 *                                          M A C R O   D E F I N I T I O N S
 ***********************************************************************************************************************/


 

/***********************************************************************************************************************
 *                                          G L O B A L  V A R I A B L E   D E F I N I T I O N S
 ***********************************************************************************************************************/
/*
 * @brief: This variable is used to get the BLE connectivity status whether its connected or not  
 * @Unit:  nil
 * @Resolution: NA
 * @Range: NA
 * @Applicability: BLE_checking
 */

#define USER_NAME_MAXLENGTH 18
uint8_t fl_BLE_call_connectivity_status;


 /*
 * @brief:check pre condition states such as ignition from the function if it false it goes off condition 
 * @Unit:  N/A
 * @Resolution: 
 * @Range: N/A
 * @Applicability: BLE_checking?
 */
uint8_t g_BLE_call_Ign_Position_u8;

/*
 * @brief:check previous condition states such as ignition from the function if it false it goes off condition 
 * @Unit:  N/A
 * @Resolution: 
 * @Range: N/A
 * @Applicability: 
 */
bool g_BLE_call_pre_condition_Status;


 /*
 * @brief:check previous condition states such as Low voltage shutdown from the function if it false it goes off condition 
 * @Unit:  N/A
 * @Resolution: 
 * @Range: N/A
 * @Applicability: 
 */
uint8_t g_BLE_call_LVSD_check_u8;


 /*
 * @brief:check pre condition states such as High voltage shutdown from the function if it false it goes off condition 
 * @Unit:  N/A
 * @Resolution: 
 * @Range: N/A
 * @Applicability: 
 */
uint8_t g_BLE_call_HVSD_check_u8;


 /*
 * @brief: This variable is used to store the music packet information which is received in structure form from UART
 * @Unit:  N/A
 * @Resolution: 
 * @Range: N/A
 * @Applicability: 
 */
UART_DATA_MGR_SMARTPHONE_PKT_TYPE_ST g_BLE_CALL_PKT_TYPE_ST;

UART_DATA_MGR_SMARTPHONE_PKT_TYPE_ST g_BLE_MISSED_CALL_PKT_TYPE_ST;

UART_DATA_MGR_SMARTPHONE_PKT_TYPE_ST g_BLE_UNREAD_SMS_PKT_TYPE_ST;

UART_DATA_MGR_SMARTPHONE_PKT_TYPE_ST g_BLE_ACTIVE_CALL_PKT_TYPE_ST;

UART_DATA_MGR_SMARTPHONE_PKT_TYPE_ST g_BLE_USER_NAME_PKT_TYPE_ST;


uint8_t g_Char_INDEX_U8 = 0;

/***********************************************************************************************************************
 *                                    P R I V A T E     F U N C T I O N S    D E C L A R A T I O N
 ***********************************************************************************************************************/


/***********************************************************************************************************************
 *                                          F U N C T I O N     D E F I N I T I O N S
 ***********************************************************************************************************************/

/* Initialize the values for the init variables */
void BLE_Call_module_init(void)
{

		//g_MUSIC_ACTIVE_STATUS_u8  = MUSIC_ACTIVE;
		fl_BLE_call_connectivity_status = 0x00;    //check ble macro
}

void BLE_Call_module_de_init(void)
{
        /* do nothing */
}

void BLE_call_activate(void)
{
	/* do nothing */
}

void BLE_call_deactivate(void)
{
	/* do nothing */
}

/* check Bluetooth precondition to find whether the system is on /off and it getting power or not */
uint8_t BLE_call_Pre_Condition_check(void)
{

	/* check previous condition states such as ign,LVSD/HVSD * from the function if it false it goes off condition */
	 g_BLE_call_pre_condition_Status = FALSE;

	g_BLE_call_Ign_Position_u8 = BLE_GET_IGN_POSITION();
	g_BLE_call_LVSD_check_u8 = BLE_GET_LOW_VOLTAGE_STATE();
	g_BLE_call_HVSD_check_u8 = BLE_GET_HIGH_VOLTAGE_STATE();

	/* check condition */
    if((g_BLE_call_Ign_Position_u8  == IGN_ON) && \
   	  (g_BLE_call_LVSD_check_u8 != SYSTEM_SERVICE_NORMAL_VOLTAGE) &&\
	  (g_BLE_call_HVSD_check_u8 != SYSTEM_SERVICE_NORMAL_VOLTAGE))

	{
	   /* If the pre condition is true then calculate the luminanca value else returned to off state */
    	g_BLE_call_pre_condition_Status = TRUE;
	}

   return g_BLE_call_pre_condition_Status;
}


	/*  function is used to get the bluetooth connectivity status whether its on off if its off it goes to BLE off state */
uint8_t Check_BLE_call_Connectivity_status(void)
{
	fl_BLE_call_connectivity_status = GUI_BLE_Enable_Status();
	return fl_BLE_call_connectivity_status;
}


void BLE_Call_Mainfunction(void)
{	

	/* This API is used to get the pre-condition check as LVSD/HVSD and ign on and ign Off state */
	g_BLE_call_pre_condition_Status = BLE_Pre_Condition_check();


	/* if the pre condition is true then check the BLE connectivity status else music will not connect*/
	if(g_BLE_call_pre_condition_Status == TRUE)
	{	 

	/* function is used to get the bluetooth connectivity status if BLE is ON it shows the music information */
	Check_BLE_call_Connectivity_status();

	if(fl_BLE_call_connectivity_status = BLUETOOTH_ON )
	{

	/* This API is used to get the current music information on the screen */
		HERO_SMARTPHONE_CALL_NUMBER_PKT_TYPE_ST BLE_contact_index_screen();
	
	}
	else
	{
		/* do nothing */
	}

	}
	else
	{
		/* do nothing */
	}

	}



void BLE_call_function_screen(Cluster_Joystick_Info_En CAll_Info)
{	
	UART_DataManager_Set_Connectivity_Info(CAll_Info);	
}


HERO_SMARTPHONE_CALL_NUMBER_PKT_TYPE_ST BLE_contact_index_screen(void)
{
g_BLE_CALL_PKT_TYPE_ST = UART_DataManager_Get_Connectivity_Info(CALL_NUM_PKT);

return (g_BLE_CALL_PKT_TYPE_ST.Hero_SmarPhone_Call_Number_Pkt_St);
}

HERO_SMARTPHONE_MISSED_CALL_PKT_TYPE_ST BLE_missedcall_screen(void)
{
g_BLE_MISSED_CALL_PKT_TYPE_ST = UART_DataManager_Get_Connectivity_Info(MISSED_CALL_PKT);

return (g_BLE_MISSED_CALL_PKT_TYPE_ST.Hero_SmartPhone_Missed_Call_Pkt_St);
}

HERO_SMARTPHONE_SMS_NUMBER_PKT_TYPE_ST BLE_UNREAD_SMS_screen(void)
{
g_BLE_UNREAD_SMS_PKT_TYPE_ST = UART_DataManager_Get_Connectivity_Info(SMS_NUM_PKT);

return (g_BLE_UNREAD_SMS_PKT_TYPE_ST.Hero_SmartPhone_Sms_Number_Pkt_St);
}

HERO_SMARTPHONE_CALL_STATUS_PKT_TYPE_ST BLE_active_call_info_screen(void)
{
g_BLE_ACTIVE_CALL_PKT_TYPE_ST = UART_DataManager_Get_Connectivity_Info(CALL_STS_PKT);

return (g_BLE_ACTIVE_CALL_PKT_TYPE_ST.Hero_SmartPhone_Call_Status_Pkt_St);
}

void HMI_contact_info_screen_info(HMI_contact_number_st *g_contact_info_st_ptr)
{
	if(g_contact_info_st_ptr != 0)
	{
	g_BLE_CALL_PKT_TYPE_ST = UART_DataManager_Get_Connectivity_Info(CALL_NUM_PKT);
	g_contact_info_st_ptr->Contact_number1[18] = g_BLE_CALL_PKT_TYPE_ST.Hero_SmarPhone_Call_Number_Pkt_St.CONTACT_1[18];
	g_contact_info_st_ptr->Contact_number2[18] = g_BLE_CALL_PKT_TYPE_ST.Hero_SmarPhone_Call_Number_Pkt_St.CONTACT_2[18];
	g_contact_info_st_ptr->Contact_number3[18] = g_BLE_CALL_PKT_TYPE_ST.Hero_SmarPhone_Call_Number_Pkt_St.CONTACT_3[18];
	g_contact_info_st_ptr->Contact_number4[18] = g_BLE_CALL_PKT_TYPE_ST.Hero_SmarPhone_Call_Number_Pkt_St.CONTACT_4[18];
	g_contact_info_st_ptr->Contact_number5[18] = g_BLE_CALL_PKT_TYPE_ST.Hero_SmarPhone_Call_Number_Pkt_St.CONTACT_5[18];
	}
}

void HMI_unread_SMS_screen_info(HMI_SMS_info_st *g_sms_info_ptr)
{
	if(g_sms_info_ptr!= 0)
	{	
		g_BLE_UNREAD_SMS_PKT_TYPE_ST = UART_DataManager_Get_Connectivity_Info(SMS_NUM_PKT);
	    g_sms_info_ptr->Number_of_SMS[0] = g_BLE_UNREAD_SMS_PKT_TYPE_ST.Hero_SmartPhone_Sms_Number_Pkt_St.NUMBER_SMS[0];	
		g_sms_info_ptr->Number_of_SMS[1] = g_BLE_UNREAD_SMS_PKT_TYPE_ST.Hero_SmartPhone_Sms_Number_Pkt_St.NUMBER_SMS[1];	
		
	}
}

void HMI_UserName_info(HMI_USERNAME_Info_st *g_username_info_ptr)
{
	if(g_username_info_ptr!= 0)
	{	
		g_BLE_USER_NAME_PKT_TYPE_ST = UART_DataManager_Get_Connectivity_Info(STS_PKT);
		for (g_Char_INDEX_U8 = 0 ; g_Char_INDEX_U8 < USER_NAME_MAXLENGTH; g_Char_INDEX_U8 ++)
		{
			g_username_info_ptr->USER_NAME[g_Char_INDEX_U8] =((char)g_BLE_USER_NAME_PKT_TYPE_ST.Hero_SmartPhone_Status_Pkt_St.USER_NAME[g_Char_INDEX_U8]);
		}
		
			
	}
}

void HMI_missed_call_screen_info(HMI_missed_call_INFO_st *g_missed_call_info_ptr)
{
	if( g_missed_call_info_ptr!= 0)
	{	
		g_BLE_MISSED_CALL_PKT_TYPE_ST = UART_DataManager_Get_Connectivity_Info(MISSED_CALL_PKT);
	    g_missed_call_info_ptr->NUmber_of_missed_call[0] = g_BLE_MISSED_CALL_PKT_TYPE_ST.Hero_SmartPhone_Missed_Call_Pkt_St.SMRTPH_MISSED_CALLS[0];
		 g_missed_call_info_ptr->NUmber_of_missed_call[1] = g_BLE_MISSED_CALL_PKT_TYPE_ST.Hero_SmartPhone_Missed_Call_Pkt_St.SMRTPH_MISSED_CALLS[1];
		
	}
}

void HMI_active_call_screen_info(HMI_Active_call_screen_st *g_active_call_screen_info_ptr)
{	
	if( g_active_call_screen_info_ptr!= 0)
	{	
		g_BLE_ACTIVE_CALL_PKT_TYPE_ST = UART_DataManager_Get_Connectivity_Info(CALL_STS_PKT);

		Memory_Copy(&g_active_call_screen_info_ptr->First_caller_name[0] , &g_BLE_ACTIVE_CALL_PKT_TYPE_ST.Hero_SmartPhone_Call_Status_Pkt_St.CALLER_NUM_NAME_1[0],18);
		Memory_Copy(&g_active_call_screen_info_ptr->Second_caller_name[0] , &g_BLE_ACTIVE_CALL_PKT_TYPE_ST.Hero_SmartPhone_Call_Status_Pkt_St.CALLER_NUM_NAME_2[0],18);
		Memory_Copy(&g_active_call_screen_info_ptr->call_duration[0] , &g_BLE_ACTIVE_CALL_PKT_TYPE_ST.Hero_SmartPhone_Call_Status_Pkt_St.CALL_DURATION[0],6);
		g_active_call_screen_info_ptr->First_call_status = g_BLE_ACTIVE_CALL_PKT_TYPE_ST.Hero_SmartPhone_Call_Status_Pkt_St.CALL_STATUS_1;
		g_active_call_screen_info_ptr->Second_call_status = g_BLE_ACTIVE_CALL_PKT_TYPE_ST.Hero_SmartPhone_Call_Status_Pkt_St.CALL_STATUS_2;
		g_active_call_screen_info_ptr->PH_volume_level = g_BLE_ACTIVE_CALL_PKT_TYPE_ST.Hero_SmartPhone_Call_Status_Pkt_St.PH_VOLUME;

	}
}











/***********************************************************************************************************************
                                              E N D   O F   S O F T W A R E                                         
 **********************************************************************************************************************/


/***********************************************************************************************************************
 *                                              R E V I S I O N   H I S T O R Y
 ***********************************************************************************************************************
    REVISION NUMBER      : V1.0.0
    REVISION DATE        : MONTH/DATE/YEAR        
    CREATED / REVISED BY : Jeevajothi (jeevajothi@niyatainfotech.com)
    DESCRIPTION          : BLE_call_module details
------------------------------------------------------------------------------------------------------------------------

 ***********************************************************************************************************************/
#endif /* ! BLE_CALL_MODULE_C */

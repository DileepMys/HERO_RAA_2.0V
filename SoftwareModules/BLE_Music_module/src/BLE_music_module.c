/* @file FILE NAME */
#ifndef BLE_MUSIC_MODULE_C
#define BLE_MUSIC_MODULE_C

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
 *  File name                       : BLE_music_module.c
 *  Version                         : V1.0.0
 *  Micros supported                : Micro Independent
 *  Compilers supported             : Compiler Independent
 *  Platforms supported             : Platform Independent
 *  Description                     : This file consistes of BLE call module implementation 
 *  @bug
--------------------------------------------------------------------------------------------------------------------*/



/***********************************************************************************************************************
 *                                               I N C L U D E   F I L E S
 ***********************************************************************************************************************/
#include "BLE_music_module.h"
#include "HMI_Setting_Screen.h"
#include "Swc_System_Service.h"
#include "UART_DataManager.h"
#include "BLE_call_module_cfg.h"


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
 * @brief: This variable is used to get the lux sample  
 * @Unit:  
 * @Resolution: 0.01
 * @Range: 0-10
 * @Applicability: Samples are taken from I2C sensor  
 */

uint8_t fl_BLE_connectivity_status;


 /*
 * @brief:check previous condition states such as ignition from the function if it false it goes off condition 
 * @Unit:  N/A
 * @Resolution: 
 * @Range: N/A
 * @Applicability: 
 */
uint8_t g_BLE_Ign_Position_u8;


 /*
 * @brief: This variable is used to get the BLE pre condition status
 * @Unit:  N/A
 * @Resolution: 
 * @Range: N/A
 * @Applicability: 
 */
bool g_BLE_pre_condition_Status;


 /*
 * @brief:check previous condition states such as Low voltage shutdown from the function if it false it goes off condition 
 * @Unit:  N/A
 * @Resolution: 
 * @Range: N/A
 * @Applicability: 
 */
uint8_t g_BLE_LVSD_check_u8;


 /*
 * @brief:check previous condition states such as High voltage shutdown from the function if it false it goes off condition 
 * @Unit:  N/A
 * @Resolution: 
 * @Range: N/A
 * @Applicability: 
 */
uint8_t g_BLE_HVSD_check_u8;


 /*
 * @brief: This variable is used to store the music packet information which is received in structure form from UART
 * @Unit:  N/A
 * @Resolution: 
 * @Range: N/A
 * @Applicability: 
 */
UART_DATA_MGR_SMARTPHONE_PKT_TYPE_ST g_BLE_MUSIC_PKT_TYPE_ST;

 /*
 * @brief: This variable is used to store the structure member from the music packet 
 * @Unit:  N/A
 * @Resolution: 
 * @Range: N/A
 * @Applicability: 
 */
uint8_t g_music_playback_state;


 /*
 * @brief: This variable is used to store music activate status
 * @Unit:  N/A
 * @Resolution: 
 * @Range: N/A
 * @Applicability: 
 */
uint8_t g_MUSIC_ACTIVE_STATUS_u8;


 /*
 * @brief: This variable is used to store music activate status
 * @Unit:  N/A
 * @Resolution: 
 * @Range: N/A
 * @Applicability: 
 */
UART_DATA_MGR_CLUSTER_PKT_TYPE_ST g_BLE_META_DATA2_cluster_info_st;


 /*
 * @brief: This variable is used to store music activate status
 * @Unit:  N/A
 * @Resolution: 
 * @Range: N/A
 * @Applicability: 
 */
UART_DATA_MGR_SMARTPHONE_PKT_TYPE_ST g_BLE_META_DATA2_cluster_ack_st;

uint8_t g_check_status;
uint8_t g_Pause_u8;
/***********************************************************************************************************************
 *                                    P R I V A T E     F U N C T I O N S    D E C L A R A T I O N
 ***********************************************************************************************************************/


/***********************************************************************************************************************
 *                                          F U N C T I O N     D E F I N I T I O N S
 ***********************************************************************************************************************/

/* Initialize the values for the init variables */
void BLE_Music_module_init(void)
{

		g_MUSIC_ACTIVE_STATUS_u8  = MUSIC_ON;
		fl_BLE_connectivity_status = 0x00;
}

void BLE_Music_module_de_init(void)
{
        /* do nothing */
}
void BLE_music_activate(void)
{

}
void BLE_music_deactivate(void)
{
	
}

/* check Bluetooth precondition to find whether the system is on /off and it getting power or not */
boolean BLE_Pre_Condition_check(void)
{

	/* check previous condition states such as ign,LVSD/HVSD * from the function if it false it goes off condition */
	 g_BLE_pre_condition_Status = FALSE;

	 g_BLE_Ign_Position_u8 = BLE_GET_IGN_POSITION();
	 g_BLE_LVSD_check_u8 = BLE_GET_LOW_VOLTAGE_STATE();
	 g_BLE_HVSD_check_u8 = BLE_GET_HIGH_VOLTAGE_STATE();

	/* check condition */
    if((g_BLE_Ign_Position_u8  == IGN_ON) && \
   	  (g_BLE_LVSD_check_u8 != SYSTEM_SERVICE_NORMAL_VOLTAGE) &&\
	  (g_BLE_HVSD_check_u8 != SYSTEM_SERVICE_NORMAL_VOLTAGE))

	{
	   /* If the pre condition is true then check the BLE connectivity */
    	g_BLE_pre_condition_Status = TRUE;
	}

   return g_BLE_pre_condition_Status;
}


	/*  function is used to get the bluetooth connectivity status whether its on off if its off it goes to BLE off state */
uint8_t Check_BLE_Connectivity_status(void)
{
	fl_BLE_connectivity_status = GUI_BLE_Enable_Status();
	return fl_BLE_connectivity_status;
}


void BLE_Music_Mainfunction(void)
{	

	/* This API is used to get the pre-condition check as LVSD/HVSD and ign on and ign Off state */
	g_BLE_pre_condition_Status = BLE_Pre_Condition_check();


	/* if the pre condition is true then check the BLE connectivity status else music will not connect*/
	if(g_BLE_pre_condition_Status == TRUE)
	{	 

	/* function is used to get the bluetooth connectivity status if BLE is ON it shows the music information */
	Check_BLE_Connectivity_status();

	if(fl_BLE_connectivity_status = BLUETOOTH_ON )  
	{

	/* This API is used to get the current music information on the screen */
	BLE_music_function_screen(); 
	
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

HERO_SMARTPHONE_MUSIC_PKT_TYPE_ST BLE_music_main_screen(void)
{
	if (g_MUSIC_ACTIVE_STATUS_u8 == MUSIC_ON)
	{
		BLE_music_function_screen();
	}
	else
	{
		g_MUSIC_ACTIVE_STATUS_u8 = MUSIC_OFF;		
	}

}

void HMI_music_main_screen_info(HMI_Music_Main_Screen_Type_St *g_music_main_screen_info_st_ptr)
{
	if(g_music_main_screen_info_st_ptr != 0)
	{
	g_BLE_MUSIC_PKT_TYPE_ST = UART_DataManager_Get_Connectivity_Info(MUSIC_PKT);
	
	Memory_Copy((uint8_t*)&g_music_main_screen_info_st_ptr->artist_name[0] ,(uint8_t*)&g_BLE_MUSIC_PKT_TYPE_ST.Hero_SmartPhone_Music_Pkt_St.MUSIC_META_DATA_1[0],20);

	Memory_Copy((uint8_t*)&g_music_main_screen_info_st_ptr->song_name[0] ,(uint8_t*) &g_BLE_MUSIC_PKT_TYPE_ST.Hero_SmartPhone_Music_Pkt_St.MUSIC_META_DATA_2[0],20);
	
	g_music_main_screen_info_st_ptr->elapsed_time = g_BLE_MUSIC_PKT_TYPE_ST.Hero_SmartPhone_Music_Pkt_St.ELAPSED_TIME;
	//g_music_main_screen_info_st_ptr->elapsed_time = g_check_status;
	 
	g_music_main_screen_info_st_ptr->playback_state = g_BLE_MUSIC_PKT_TYPE_ST.Hero_SmartPhone_Music_Pkt_St.PLYBCK_STATE;

	g_music_main_screen_info_st_ptr->Volume_Level = g_BLE_MUSIC_PKT_TYPE_ST.Hero_SmartPhone_Music_Pkt_St.MUSIC_VOLUME;
	
	//g_music_main_screen_info_st_ptr->Volume_Level = g_Pause_u8;
	//g_music_main_screen_info_st_ptr->playback_state = g_Pause_u8;
	//return();
	}	
}



void BLE_music_setting_screen(Cluster_Joystick_Info_En Music_Info)
{	
	UART_DataManager_Set_Connectivity_Info(Music_Info);	
}





void BLE_setting_MetaData_transmission_Check(Cluster_Joystick_Info_En Meta_Data_Info)
{
	UART_DataManager_Set_Connectivity_Info(Meta_Data_Info);	 //button event to HMI setting screen
}



/***********************************************************************************************************************
                                              E N D   O F   S O F T W A R E                                         
 **********************************************************************************************************************/


/***********************************************************************************************************************
 *                                              R E V I S I O N   H I S T O R Y
 ***********************************************************************************************************************
    REVISION NUMBER      : Major.Minor.Patch                          
    REVISION DATE        : MONTH/DATE/YEAR        
    CREATED / REVISED BY : NAME (EMAIL-ID)      
    DESCRIPTION          : ALS_initialization_send_statusial version            
------------------------------------------------------------------------------------------------------------------------

 ***********************************************************************************************************************/
#endif /* ! FILE NAME */

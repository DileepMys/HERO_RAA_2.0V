/* @file FILE NAME */
#ifndef HMI_NAVIGATION_H
#define HMI_NAVIGATION_H

/***********************************************************************************************************************
*    DISCLAIMER
*   Copyright (C) 2020 Niyata Infotech Pvt. Ltd. All rights reserved.                                             
***********************************************************************************************************************/

/************************************************************************************************************************
* @author              Author : Balasubramanina (balasubramanian@niyatainfotech.com)                                                                         
***********************************************************************************************************************/

/***********************************************************************************************************************
*                                                F I L E  D E S C R I P T I O N                                        
**----------------------------------------------------------------------------------------------------------------------
*  @brief
*
*  File name                       : HMI_Navigation.h
*  Version                         : 
*  Micros supported                : 
*  Compilers supported             : 
*  Platforms supported             :                 
*  Description                     : This header file contains the declarations of navigation design
*  @bug                            : N/A
--------------------------------------------------------------------------------------------------------------------*/

/**********************************************************************************************************************/

/**********************************************************************************************************************/
/***********************************************************************************************************************
*                                               I N C L U D E   CONFIGURATION F I L E S 
***********************************************************************************************************************/
#include "hal_stdtypes.h"
#include "lvgl_app.h"

/***********************************************************************************************************************
                                               I N C L U D E  CONDITION BASED F I L E S                             
***********************************************************************************************************************/



/***********************************************************************************************************************
*                                      V E R S I O N   I N T E G R I T Y  C H E C K                                  
***********************************************************************************************************************/

/***********************************************************************************************************************
*                                            M A C R O   D E F I N I T I O N S                                         
***********************************************************************************************************************/
/**
* @brief This macro is used to define 
* @Unit:  
* @Resolution: 
* @Range: 
* @Applicability: 
* @Note:  
*/


/***********************************************************************************************************************
*                                          T Y P E   D E F I N I T I O N S                                           
***********************************************************************************************************************/

/*
 * @brief    This typedef is used to define 
 * @param    
 * @return
 **/


/*
 * @brief    This typedef enum is used to define 
 * @param    
 * @param
 **/


/*
 * @brief    This structure is used to define 
 * @param    
 * @param    
 **/

typedef struct
{
	uint16_t g_Nav_img_num;
	const lv_img_dsc_t *g_Nav_Night_img;
	const lv_img_dsc_t *g_Nav_Day_img;
	uint8_t Nav_Img_X_Pos;
	uint8_t Nav_Img_Y_Pos;
	bool Nav_Blink_Status;
} g_Nav_image;

/***********************************************************************************************************************
*                                    P U B L I C     F U N C T I O N S    D E C L A R A T I O N                      
***********************************************************************************************************************/
/*
 * @brief    This function processes the navigation init
 * @param    
 * @return   
 */

#define NAVIGATION_IMAGE_TABLE {0x00, &nightnosignalicon_25x25, &nightnosignalicon_25x25, 78, 15		,FALSE},\
							   {0x42, &reroute_icon_day_img, &reroute_icon_night_img, 68, 20			,FALSE},\
							   {0x43, &nightturnslightleft_38x70, &img_day_turn_slight_left, 58, 15		,FALSE},\
							   {0x44, &nightturnslightright_38x70, &img_day_turn_slight_right, 85, 15	,FALSE},\
							   {0x45, &nightturnsharpleft_38x70, &img_day_turn_sharp_left, 58, 15		,FALSE},\
							   {0x46, &nightturnsharpright_38x70, &img_day_turn_sharp_right, 85, 15		,FALSE},\
							   {0x47, &nightstraight_32x68, &img_day_straight, 75, 18					,FALSE},\
							   {0x48, &destreached_36x48, &img_day_destination_reached, 75, 20			,FALSE},\
							   {0x49, &nightturnleft_40x70, &img_day_turn_left, 56, 15					,FALSE},\
							   {0x4A, &nightturnright_40x70, &img_day_turn_right, 85, 15				,FALSE},\
							   {0x4B, &nightrampleft_55x64, &img_day_ramp_left, 60, 21					,FALSE},\
							   {0x4C, &nightrampright_55x64, &img_day_ramp_right, 70, 21				,FALSE},\
							   {0x4E, &nightroundaboutright_55x59, &img_day_roundabout_right, 67, 27	,FALSE},\
							   {0x4F, &nightuturnleft_53x45, &img_day_U_turn_right, 60, 28				,FALSE},\
							   {0x50, &nightuturn_53x45, &img_day_U_turn_left, 65, 28					,FALSE},\
							   {0x51, &nightforkleft_61x65, &img_day_fork_left, 55, 21					,FALSE},\
							   {0x52, &nightkeepright_61x65, &img_day_fork_right, 64, 21				,FALSE},\
							   {0x54, &nightferrytrain_52x40, &img_day_ferry_train, 65, 30				,FALSE},\
							   {0x55, &nightroundaboutleft_55x59, &img_day_roundabout_left, 58, 27		,FALSE},\
							   {0x56, &nightmerge_39x66, &img_day_merge, 70, 21							,FALSE},\
							   {0x58, &nightkeepright_61x65, &day_keep_right, 63, 21					,FALSE},\
							   {0x59, &nightferry_54x47, &img_day_ferry, 65, 30							,FALSE},\
							   {0x5A, &nightkeepleft_61x65, &img_day_keep_left, 57, 21					,FALSE},\
							   {0x62, &reroute_icon_day_img, &reroute_icon_night_img, 68, 20			,TRUE },\
							   {0x63, &nightturnslightleft_38x70, &img_day_turn_slight_left, 58, 15		,TRUE },\
							   {0x64, &nightturnslightright_38x70, &img_day_turn_slight_right, 85, 15	,TRUE },\
							   {0x65, &nightturnsharpleft_38x70, &img_day_turn_sharp_left, 58, 15		,TRUE },\
							   {0x66, &nightturnsharpright_38x70, &img_day_turn_sharp_right, 85, 15		,TRUE },\
							   {0x67, &nightstraight_32x68, &img_day_straight, 75, 18					,TRUE },\
							   {0x68, &destreached_36x48, &img_day_destination_reached, 75, 18			,TRUE },\
							   {0x69, &nightturnleft_40x70, &img_day_turn_left, 56, 15					,TRUE },\
							   {0x6A, &nightturnright_40x70, &img_day_turn_right, 85, 15				,TRUE },\
							   {0x6B, &nightrampleft_55x64, &img_day_ramp_left, 60, 21					,TRUE },\
							   {0x6C, &nightrampright_55x64, &img_day_ramp_right, 70, 21				,TRUE },\
							   {0x6E, &nightroundaboutright_55x59, &img_day_roundabout_right, 67, 27	,TRUE },\
							   {0x6F, &nightuturnleft_53x45, &img_day_U_turn_right, 60, 28				,TRUE },\
							   {0x70, &nightuturn_53x45, &img_day_U_turn_left, 65, 28					,TRUE },\
							   {0x71, &nightforkleft_61x65, &img_day_fork_left, 55, 21					,TRUE },\
							   {0x72, &nightkeepright_61x65, &img_day_fork_right, 64, 21				,TRUE },\
							   {0x74, &nightferrytrain_52x40, &img_day_ferry_train, 65, 30				,TRUE },\
							   {0x75, &nightroundaboutleft_55x59, &img_day_roundabout_left, 58, 27		,TRUE },\
							   {0x76, &nightmerge_39x66, &img_day_merge, 70, 21							,TRUE },\
							   {0x78, &nightkeepright_61x65, &day_keep_right, 63, 21					,TRUE },\
							   {0x79, &nightferry_54x47, &img_day_ferry, 65, 30							,TRUE },\
							   {0x7A, &nightkeepleft_61x65, &img_day_keep_left, 57, 21					,TRUE },



void GUI_Navigation_Screen(uint8_t Screen_Main_Int_u8, uint8_t Day_Night_Mode_u8);



/*
* @brief    This API is used to define the position and size for navigation idle images during the screen transition
* @param    
* @return  
* @invocation 
*/

void GUI_Navigation_Night_Entry(void);
void GUI_Navigation_Night_During(void);
void GUI_Navigation_Night_Exit(void);


void GUI_Navigation_Day_Entry(void);
void GUI_Navigation_Day_During(void);
void GUI_Navigation_Day_Exit(void);

void GUI_Navigation_Entry_Screen_Main_Day_Mode(void);
void GUI_Navigation_During_Screen_Main_Day_Mode(void);
void GUI_Navigation_Exit_Screen_Main_Day_Mode(void);

/***********************************************************************************************************************
                                              E N D   O F   S O F T W A R E                                         
*********************************************************************************************************************/


/***********************************************************************************************************************
*                                              R E V I S I O N   H I S T O R Y                                       
/***********************************************************************************************************************
    REVISION NUMBER      : V1.0.1                                                
    REVISION DATE        : 8/22/2022                              
    CREATED / REVISED BY : Balasubramaninan (balasubramanian@niyatainfotech.com)   
    DESCRIPTION          : Initial version                                  
------------------------------------------------------------------------------------------------------------------------

***********************************************************************************************************************/
#endif /* ! HMI_NAVIGATION */





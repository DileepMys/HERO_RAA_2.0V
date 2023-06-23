/* @file FILE NAME */
#ifndef HMI_GEAR_C
#define HMI_GEAR_C

/***********************************************************************************************************************
 *    DISCLAIMER
 *   Copyright (C) 2011, 2016 Niyata Infotech Pvt. Ltd. All rights reserved.
 ***********************************************************************************************************************/

/************************************************************************************************************************
 * @author              Author : Name (mail-id)
 ***********************************************************************************************************************/

/***********************************************************************************************************************
 *                                                F I L E  D E S C R I P T I O N
 **----------------------------------------------------------------------------------------------------------------------
 *  @brief
 *
 *  File name                       : 
 *  Version                         : 
 *  Micros supported                : 
 *  Compilers supported             : 
 *  Platforms supported             : 
 *  Description                     : This file consists of definitions of 
 *  @bug
--------------------------------------------------------------------------------------------------------------------*/



/***********************************************************************************************************************
 *                                               I N C L U D E   F I L E S
 ***********************************************************************************************************************/
#include <gen/events_init.h>
#include <gen/gui_guider.h>
#include "peripherals.h"

#include "../lvgl/lvgl.h"

#include "lvgl_app.h"


#include "custom.h"
#include "fsl_gpio.h"
#include "SWC_Gear_position.h"
#include "TTMgr.h"
#include "HMI_Gear.h"
/***********************************************************************************************************************
*                                               I N C L U D E  LIBRARY F I L E S                                     
***********************************************************************************************************************/



/***********************************************************************************************************************
 *                                          M A C R O   D E F I N I T I O N S
 ***********************************************************************************************************************/

/*  
 * @brief: This macro is used to 
 * @Unit:  
 * @Resolution: 
 * @Range: 
 * @Applicability: 
 */

/***********************************************************************************************************************
 *                                          L O C A L  V A R I A B L E   D E F I N I T I O N S
 ***********************************************************************************************************************/
/*
 * @brief: This variable is used to 
 * @Unit:  
 * @Resolution: 
 * @Range: 
 * @Applicability: 
 */

/***********************************************************************************************************************
 *                                  P R I V A T E   V A R I A B L E   D E F I N I T I O N S
 ***********************************************************************************************************************/
/*
 * @brief: This variable is used to 
 * @Unit:  
 * @Resolution: 
 * @Range: 
 * @Applicability: 
 */
//uint8_t g_gear_position_number_u8;

 uint8_t g_previous_gear_position_number_u8;

//uint8_t g_gear_advisory_u8;
uint8_t g_previous_gear_advisory_u8;


uint8_t g_Gear_Indication_Flash_u8;

bool g_Gear_TT_Status;
/***********************************************************************************************************************
 *                                    P R I V A T E     F U N C T I O N S    D E C L A R A T I O N
 ***********************************************************************************************************************/

/*
 * @brief    This function processes the 
 * @param    
 * @return   
 */

/***********************************************************************************************************************
 *                                          F U N C T I O N     D E F I N I T I O N S
 ***********************************************************************************************************************/
void Gui_Gear_Init(void)
{
    g_previous_gear_position_number_u8= 0;

     g_previous_gear_advisory_u8= 0;

    g_Gear_Indication_Flash_u8 = 0;
}

void Gui_Gear_Deinit(void)
{
    g_previous_gear_position_number_u8 = 0;

    g_previous_gear_advisory_u8 = 0;

    g_Gear_Indication_Flash_u8 = 0;
}

/*Gear Position and advisory*/

void Gear_Day_Entry(void)
{
	g_previous_gear_position_number_u8 = 0xFF;
	g_previous_gear_advisory_u8 = 0xFF;
    lv_obj_set_pos(guider_ui.screen_Day_Gear_pos_Num,31,144);
    lv_obj_move_foreground(guider_ui.screen_Day_Gear_pos_Num);
}

void Gear_Night_Entry(void)
{
	g_previous_gear_position_number_u8 = 0xFF;
	g_previous_gear_advisory_u8 = 0xFF;
	lv_obj_set_pos(guider_ui.screen_Gear_Position_Number,31,144);	
}


void GUI_Gear_Poition_Handler_Day(void)
{
   	
   uint8_t fl_present_gear_position_number_u8 = Get_Gear_Position_Number_Indication();             
   uint8_t fl_present_gear_advisory_u8 = Get_Gear_Position_Shift_Advisory_Indication();           
                                                                                                  
  if((g_previous_gear_position_number_u8 !=fl_present_gear_position_number_u8))
    {
	
         g_previous_gear_position_number_u8 =fl_present_gear_position_number_u8;


	  if(g_previous_gear_position_number_u8 < GEAR_POS_INVALID)
	  {
		  if(g_previous_gear_position_number_u8 == 0)
		  {
			
			lv_label_set_text(guider_ui.screen_Day_Gear_pos_Num,"N");
			lv_obj_set_style_text_color(guider_ui.screen_Day_Gear_pos_Num, lv_color_Green(), 0);
			set_obj_opa_S(guider_ui.screen_Day_Gear_pos_Num,0);

			/* Disable & Enbale The Gear Number & Neutral Images*/
			lv_obj_clear_flag(guider_ui.screen_gear_N_img_Day,LV_OBJ_FLAG_HIDDEN);
			lv_obj_add_flag(guider_ui.screen_Day_Gear_pos_Num,LV_OBJ_FLAG_HIDDEN);
			 
		  }
		  else
		  {
		    
			 lv_label_set_text_fmt(guider_ui.screen_Day_Gear_pos_Num, "%d", g_previous_gear_position_number_u8);
			 lv_obj_set_style_text_color(guider_ui.screen_Day_Gear_pos_Num, lv_color_black(), 0);
			set_obj_opa_S(guider_ui.screen_Day_Gear_pos_Num,0);

			/* Disable & Enbale The Gear Number & Neutral Images*/
			lv_obj_add_flag(guider_ui.screen_gear_N_img_Day,LV_OBJ_FLAG_HIDDEN);
			lv_obj_clear_flag(guider_ui.screen_Day_Gear_pos_Num,LV_OBJ_FLAG_HIDDEN);
			
		  }
		   	lv_img_set_src(guider_ui.screen_day_gear_up,&new_day_gear_arrows_up_white);
  			lv_img_set_src(guider_ui.screen_day_gear_down,&new_day_gear_arrows_down_white);
  	   }
          
	}            
        
        if(( g_previous_gear_advisory_u8 !=fl_present_gear_advisory_u8))
        {
        	
	         g_previous_gear_advisory_u8 = fl_present_gear_advisory_u8;
        
         
		 if(  g_previous_gear_advisory_u8 == 1)
		 {
		 	  /*  Flush the White Icon, which is assigned for Button Pressed */		 	
			   lv_img_set_src(guider_ui.screen_day_gear_up,&new_day_gear_arrows_up_white);
			   lv_obj_clear_flag(guider_ui.screen_day_gear_up,LV_OBJ_FLAG_HIDDEN);
			   lv_img_set_src(guider_ui.screen_day_gear_down,&new_day_gear_arrows_down_white);
			   lv_obj_add_flag(guider_ui.screen_day_gear_down,LV_OBJ_FLAG_HIDDEN);

		 }
		 else if(g_previous_gear_advisory_u8  == 2)
		 {			 
			   lv_img_set_src(guider_ui.screen_day_gear_down,&new_day_gear_arrows_down_white);
			    lv_obj_clear_flag(guider_ui.screen_day_gear_down,LV_OBJ_FLAG_HIDDEN);
			    lv_img_set_src(guider_ui.screen_day_gear_up,&new_day_gear_arrows_up_white);
			   	lv_obj_add_flag(guider_ui.screen_day_gear_up,LV_OBJ_FLAG_HIDDEN);
		 }
		 else
		 {
			lv_img_set_src(guider_ui.screen_day_gear_down,&new_day_gear_arrows_down_white);
			lv_img_set_src(guider_ui.screen_day_gear_up,&new_day_gear_arrows_up_white);
			lv_obj_add_flag(guider_ui.screen_day_gear_down,LV_OBJ_FLAG_HIDDEN);
			lv_obj_add_flag(guider_ui.screen_day_gear_up,LV_OBJ_FLAG_HIDDEN);
		 }

	  }

	  if(g_previous_gear_position_number_u8 == GEAR_POS_INVALID)
	  {		 
		  lv_img_set_src(guider_ui.screen_day_gear_down,&new_day_gear_arrows_down_white);
		  lv_img_set_src(guider_ui.screen_day_gear_up,&new_day_gear_arrows_up_white);


		  if(g_Gear_TT_Status != FALSE)
		  {
			HMI_Gear_TT_ON_Day();
		  }
		  else
		  {
			HMI_Gear_TT_OFF_Day();
		  }	  	

	  }
}


/*Gear Position and advisory*/
void GUI_Gear_Poition_Handler(void)
{	

   uint8_t fl_present_gear_position_number_u8 = Get_Gear_Position_Number_Indication();             
   uint8_t fl_present_gear_advisory_u8 = Get_Gear_Position_Shift_Advisory_Indication();           
                                                                                                  
  if((g_previous_gear_position_number_u8 !=fl_present_gear_position_number_u8))
    {
	
         g_previous_gear_position_number_u8 =fl_present_gear_position_number_u8;


	  if(g_previous_gear_position_number_u8 < GEAR_POS_INVALID)
	  {
		  if(g_previous_gear_position_number_u8 == 0)
		  {
			 lv_label_set_text(guider_ui.screen_Gear_Position_Number,"N");
			 lv_obj_set_style_text_color(guider_ui.screen_Gear_Position_Number, lv_color_Green(), 0);
			set_obj_opa_S(guider_ui.screen_Gear_Position_Number,0);
			

			/* Disable & Enbale The Gear Number & Neutral Images*/
			lv_obj_clear_flag(guider_ui.screen_gear_N_img_night,LV_OBJ_FLAG_HIDDEN);
			lv_obj_add_flag(guider_ui.screen_Gear_Position_Number,LV_OBJ_FLAG_HIDDEN);
			 
		  }
		  else
		  {
		    lv_label_set_text_fmt(guider_ui.screen_Gear_Position_Number, "%d", g_previous_gear_position_number_u8);
			 lv_obj_set_style_text_color(guider_ui.screen_Gear_Position_Number, lv_color_white(), 0);
			set_obj_opa_S(guider_ui.screen_Gear_Position_Number,0);

			/* Disable & Enbale The Gear Number & Neutral Images*/
			lv_obj_add_flag(guider_ui.screen_gear_N_img_night,LV_OBJ_FLAG_HIDDEN);
			lv_obj_clear_flag(guider_ui.screen_Gear_Position_Number,LV_OBJ_FLAG_HIDDEN);
			
		  }
		
  	   }
    	
	}      
                
      
	if ((g_previous_gear_advisory_u8 != fl_present_gear_advisory_u8) || (g_previous_gear_position_number_u8 != fl_present_gear_position_number_u8))
	{

		g_previous_gear_advisory_u8 = fl_present_gear_advisory_u8;
		g_previous_gear_position_number_u8 = fl_present_gear_position_number_u8;

		if (g_previous_gear_advisory_u8 == 1 && g_previous_gear_position_number_u8 != 6 && g_previous_gear_position_number_u8 != 0)
		 {
		 	  /*  Flush the White Icon, which is assigned for Button Pressed */
		 	  lv_imgbtn_set_state(guider_ui.screen_Gear_UP_Advisory, 1);
		 	  lv_imgbtn_set_state(guider_ui.screen_Gear_Down_Advisory,0);

			  lv_obj_clear_flag(guider_ui.screen_Gear_UP_Advisory,LV_OBJ_FLAG_HIDDEN);
			  lv_obj_add_flag(guider_ui.screen_Gear_Down_Advisory,LV_OBJ_FLAG_HIDDEN);

			  lv_obj_set_style_bg_img_opa(guider_ui.screen_Gear_UP_Advisory, LV_OPA_0, 0);
			  lv_obj_set_style_bg_img_opa(guider_ui.screen_Gear_Down_Advisory, LV_OPA_0, 0);


		 }
		 else if(g_previous_gear_advisory_u8  == 2)
		 {
		 		lv_imgbtn_set_state(guider_ui.screen_Gear_Down_Advisory, 1);
		 		lv_imgbtn_set_state(guider_ui.screen_Gear_UP_Advisory, 0);

				  lv_obj_add_flag(guider_ui.screen_Gear_UP_Advisory,LV_OBJ_FLAG_HIDDEN);
			  	  lv_obj_clear_flag(guider_ui.screen_Gear_Down_Advisory,LV_OBJ_FLAG_HIDDEN);

				lv_obj_set_style_bg_img_opa(guider_ui.screen_Gear_Down_Advisory, LV_OPA_0, 0);
			  lv_obj_set_style_bg_img_opa(guider_ui.screen_Gear_UP_Advisory, LV_OPA_0, 0);

		 }
		 else
		 {
		 		  lv_imgbtn_set_state(guider_ui.screen_Gear_Down_Advisory, 0);
		 		  lv_imgbtn_set_state(guider_ui.screen_Gear_UP_Advisory, 0);
				  lv_obj_add_flag(guider_ui.screen_Gear_Down_Advisory,LV_OBJ_FLAG_HIDDEN);
				  lv_obj_add_flag(guider_ui.screen_Gear_UP_Advisory,LV_OBJ_FLAG_HIDDEN);

			lv_obj_set_style_bg_img_opa(guider_ui.screen_Gear_UP_Advisory, LV_OPA_0, 0);
			lv_obj_set_style_bg_img_opa(guider_ui.screen_Gear_Down_Advisory, LV_OPA_0, 0);

		 }

	  }

	  if(g_previous_gear_position_number_u8 == GEAR_POS_INVALID)
	  {
		  lv_imgbtn_set_state(guider_ui.screen_Gear_Down_Advisory, 0);
		  lv_imgbtn_set_state(guider_ui.screen_Gear_UP_Advisory, 0);



		  if(g_Gear_TT_Status != FALSE)
		  {
			HMI_Gear_TT_ON();
		  }
		  else
		  {
			HMI_Gear_TT_OFF();
		  }
		  	

	  }
}

void HMI_Gear_TT_OFF(void)
{
	
	lv_label_set_text_fmt(guider_ui.screen_Gear_Position_Number, "%c");
	lv_obj_set_style_text_color(guider_ui.screen_Gear_Position_Number, lv_color_white(), 0);
	set_obj_opa_S(guider_ui.screen_Gear_Position_Number,0);	

	// lv_label_set_text_fmt(guider_ui.screen_Day_Gear_pos_Num, "%c");
	// lv_obj_set_style_text_color(guider_ui.screen_Day_Gear_pos_Num, lv_color_black(), 0);
	// set_obj_opa_S(guider_ui.screen_Day_Gear_pos_Num,0);

	/* Disable & Enbale The Gear Number & Neutral Images*/
	lv_obj_add_flag(guider_ui.screen_gear_N_img_night,LV_OBJ_FLAG_HIDDEN);
	lv_obj_clear_flag(guider_ui.screen_Gear_Position_Number,LV_OBJ_FLAG_HIDDEN);

}

void HMI_Gear_TT_ON(void)
{
	lv_obj_set_pos(guider_ui.screen_Gear_Position_Number,31,142);
	lv_label_set_text_fmt(guider_ui.screen_Gear_Position_Number, "%c",'-');
	lv_obj_set_style_text_color(guider_ui.screen_Gear_Position_Number, lv_color_white(), 0);
	set_obj_opa_S(guider_ui.screen_Gear_Position_Number,0);

	/* Disable & Enbale The Gear Number & Neutral Images*/
	lv_obj_add_flag(guider_ui.screen_gear_N_img_night,LV_OBJ_FLAG_HIDDEN);
	lv_obj_clear_flag(guider_ui.screen_Gear_Position_Number,LV_OBJ_FLAG_HIDDEN);

}

void HMI_Set_Gear_TT_ON(void)
{
	g_Gear_TT_Status = TRUE;
}

void HMI_Set_Gear_TT_OFF(void)
{
	g_Gear_TT_Status = FALSE;

}

void HMI_Gear_TT_OFF_Day(void)
{	

	lv_label_set_text_fmt(guider_ui.screen_Day_Gear_pos_Num, "%c");
	lv_obj_set_style_text_color(guider_ui.screen_Day_Gear_pos_Num, lv_color_black(), 0);
	set_obj_opa_S(guider_ui.screen_Day_Gear_pos_Num,0);

	/* Disable & Enbale The Gear Number & Neutral Images*/
	lv_obj_add_flag(guider_ui.screen_gear_N_img_Day,LV_OBJ_FLAG_HIDDEN);
	lv_obj_clear_flag(guider_ui.screen_Day_Gear_pos_Num,LV_OBJ_FLAG_HIDDEN);

}

void HMI_Gear_TT_ON_Day(void)
{
		
	lv_obj_set_pos(guider_ui.screen_Day_Gear_pos_Num, 31, 142);
	lv_label_set_text_fmt(guider_ui.screen_Day_Gear_pos_Num, "%c",'-');
	lv_obj_set_style_text_color(guider_ui.screen_Day_Gear_pos_Num, lv_color_black(), 0);
	set_obj_opa_S(guider_ui.screen_Day_Gear_pos_Num,0);

	/* Disable & Enbale The Gear Number & Neutral Images*/
	lv_obj_add_flag(guider_ui.screen_gear_N_img_Day,LV_OBJ_FLAG_HIDDEN);
	lv_obj_clear_flag(guider_ui.screen_Day_Gear_pos_Num,LV_OBJ_FLAG_HIDDEN);

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
    DESCRIPTION          : Initial version            
------------------------------------------------------------------------------------------------------------------------

 ***********************************************************************************************************************/
#endif /* ! FILE NAME */
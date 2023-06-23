/* @file FILE NAME */
#ifndef HMI_SPEEDOMETER_C
#define HMI_SPEEDOMETER_C

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
#include "HMI_Speedometer.h"

#include "custom.h"
#include "fsl_gpio.h"

/* APPLCIATION - INCLUDE */
#include "Swc_Speedometer.h"

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

uint16 g_Speedo_Value_u16;
uint16 g_Previous_Speedo_Value_u16;
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
void GUI_Speedometer_Init(void)
{
	g_Speedo_Value_u16 = 0;
	g_Previous_Speedo_Value_u16 = 0;
}

void GUI_Speedometer_Deinit(void)
{
	/*Do nothing*/
}
void GUI_SpeedoMeter_Previous_Change(void)
{

	/* Screen Transation time Change Value to 0 */
	g_Previous_Speedo_Value_u16 = 0;
}
void GUI_Speedometer_Handler(void)
{

	lv_img_set_src(guider_ui.screen_imgKmph, &_txt_night_speed_unit_33x19);
	set_obj_opa(guider_ui.screen_imgKmph, 255);
	lv_img_set_src(guider_ui.screen_Sub_Con, &_Layer_0_9x9);

	uint8_t Digit_Value_1_u8 = 0;
	uint8_t Digit_Value_2_u8 = 0;
	uint8_t Digit_Value_3_u8 = 0;

	lv_img_set_src(guider_ui.screen_Sub_Button, &_Layer_0_9x9);

	g_Speedo_Value_u16 = Get_display_Speed();

	if (g_Previous_Speedo_Value_u16 != g_Speedo_Value_u16)
	{

		Digit_Value_1_u8 = (g_Speedo_Value_u16) % 10;
		Digit_Value_2_u8 = (((g_Speedo_Value_u16)-Digit_Value_1_u8) % 100) / 10;
		Digit_Value_3_u8 = (((g_Speedo_Value_u16) - (Digit_Value_2_u8 * 10)) % 1000) / 100;

		if (g_Speedo_Value_u16 >= SPEED_MAX)
		{
			lv_img_set_src(guider_ui.screen_SC_3, &txt_night_speed_line_2_white9);

			lv_img_set_src(guider_ui.screen_SC_2, &txt_night_speed_line_2_white9);

			lv_img_set_src(guider_ui.screen_SC_1, &txt_night_speed_line_3_white1);

			lv_img_set_src(guider_ui.screen_imgKmph, &_txt_night_speed_unit_33x19);
			set_obj_opa(guider_ui.screen_imgKmph, 255);
		}
		else
		{
			if ((g_Speedo_Value_u16 >= 0) && (g_Speedo_Value_u16 < 10))
			{

				lv_img_set_src(guider_ui.screen_SC_3, &txt_night_speed_line_2_white9);

				lv_img_set_src(guider_ui.screen_SC_2, &txt_night_speed_line_3_grey0);

				lv_img_set_src(guider_ui.screen_SC_1, &txt_night_speed_line_3_grey0);

				lv_img_set_src(guider_ui.screen_imgKmph, &_txt_night_speed_unit_33x19);
				set_obj_opa(guider_ui.screen_imgKmph, 255);
			}
			else if ((g_Speedo_Value_u16 >= 10) && (g_Speedo_Value_u16 < 100))
			{
				lv_img_set_src(guider_ui.screen_SC_1, &txt_night_speed_line_3_grey0);

				lv_img_set_src(guider_ui.screen_SC_2, &txt_night_speed_line_3_white0);

				lv_img_set_src(guider_ui.screen_SC_3, &txt_night_speed_line_3_white0);

				if ((Digit_Value_2_u8 >= 0) && (Digit_Value_2_u8 <= 9))
				{

					Speed_Digit(Digit_Value_2_u8, 1);
				}
				else
				{
					/* Do Nothing */
				}
			}
			else if ((g_Speedo_Value_u16 >= 100) && (g_Speedo_Value_u16 < 1000))
			{
				lv_img_set_src(guider_ui.screen_SC_1, &txt_night_speed_line_3_white0);

				lv_img_set_src(guider_ui.screen_SC_2, &txt_night_speed_line_3_white0);

				lv_img_set_src(guider_ui.screen_SC_3, &txt_night_speed_line_3_white0);

				if ((Digit_Value_3_u8 >= 0) && (Digit_Value_3_u8 <= 9))
				{

					Speed_Digit(Digit_Value_3_u8, 2);
				}
				if ((Digit_Value_2_u8 >= 0) && (Digit_Value_2_u8 <= 9))
				{

					Speed_Digit(Digit_Value_2_u8, 1);
				}
			}
			else
			{
			}

			if (Digit_Value_1_u8 == 0)
			{

				lv_img_set_src(guider_ui.screen_imgKmph, &_txt_night_speed_unit_33x19);
				/*to make whitezero*/
				lv_img_set_src(guider_ui.screen_SC_3, &txt_night_speed_line_3_white0);
			}
			else if (Digit_Value_1_u8 == 1)
			{
				lv_img_set_src(guider_ui.screen_SC_3, &txt_night_speed_line_3_white1);
			}
			else if (Digit_Value_1_u8 == 2)
			{
				lv_img_set_src(guider_ui.screen_SC_3, &txt_night_speed_line_3_white2);
			}
			else if (Digit_Value_1_u8 == 3)
			{
				lv_img_set_src(guider_ui.screen_SC_3, &txt_night_speed_line_3_white3);
			}
			else if (Digit_Value_1_u8 == 4)
			{
				lv_img_set_src(guider_ui.screen_SC_3, &txt_night_speed_line_3_white4);
			}
			else if (Digit_Value_1_u8 == 5)
			{
				lv_img_set_src(guider_ui.screen_SC_3, &txt_night_speed_line_3_white5);
			}
			else if (Digit_Value_1_u8 == 6)
			{
				lv_img_set_src(guider_ui.screen_SC_3, &txt_night_speed_line_3_white6);
			}
			else if (Digit_Value_1_u8 == 7)
			{
				lv_img_set_src(guider_ui.screen_SC_3, &txt_night_speed_line_3_white7);
			}
			else if (Digit_Value_1_u8 == 8)
			{
				lv_img_set_src(guider_ui.screen_SC_3, &txt_night_speed_line_3_white8);
			}
			else if (Digit_Value_1_u8 == 9)
			{
				lv_img_set_src(guider_ui.screen_SC_3, &txt_night_speed_line_2_white9);
			}
		}
		g_Previous_Speedo_Value_u16 = g_Speedo_Value_u16;
	}
	else
	{
		/* Do Nothing */
	}
}
void Speed_Digit(uint8_t fl_no_Digit_u8, uint8_t Digit_Selection)
{
	switch (fl_no_Digit_u8)
	{
	case 0:
		if (Digit_Selection == 1)
		{
			lv_img_set_src(guider_ui.screen_SC_2, &txt_night_speed_line_3_white0);
		}
		else if (Digit_Selection == 2)
		{
			lv_img_set_src(guider_ui.screen_SC_1, &txt_night_speed_line_3_white0);
		}
		else
		{
			/*do nothing*/
		}
		break;
	case 1:
		if (Digit_Selection == 1)
		{

			lv_img_set_src(guider_ui.screen_SC_2, &txt_night_speed_line_3_white1);
		}
		else if (Digit_Selection == 2)
		{

			lv_img_set_src(guider_ui.screen_SC_1, &txt_night_speed_line_3_white1);
		}
		else
		{
			/*do nothing*/
		}
		break;

	case 2:
		if (Digit_Selection == 1)
		{

			lv_img_set_src(guider_ui.screen_SC_2, &txt_night_speed_line_3_white2);
		}
		else if (Digit_Selection == 2)
		{

			lv_img_set_src(guider_ui.screen_SC_2, &txt_night_speed_line_3_white2);
		}
		else
		{
			/*do nothing*/
		}

		break;

	case 3:
		if (Digit_Selection == 1)
		{

			lv_img_set_src(guider_ui.screen_SC_2, &txt_night_speed_line_3_white3);
		}
		else if (Digit_Selection == 2)
		{

			lv_img_set_src(guider_ui.screen_SC_2, &txt_night_speed_line_3_white3);
		}
		else
		{
			/*do nothing*/
		}

		break;

	case 4:
		if (Digit_Selection == 1)
		{

			lv_img_set_src(guider_ui.screen_SC_2, &txt_night_speed_line_3_white4);
		}
		else if (Digit_Selection == 2)
		{

			lv_img_set_src(guider_ui.screen_SC_1, &txt_night_speed_line_3_white4);
		}
		else
		{
			/*do nothing*/
		}

		break;

	case 5:
		if (Digit_Selection == 1)
		{

			lv_img_set_src(guider_ui.screen_SC_2, &txt_night_speed_line_3_white5);
		}
		else if (Digit_Selection == 2)
		{

			lv_img_set_src(guider_ui.screen_SC_1, &txt_night_speed_line_3_white5);
		}
		else
		{
			/*do nothing*/
		}

		break;

	case 6:
		if (Digit_Selection == 1)
		{

			lv_img_set_src(guider_ui.screen_SC_2, &txt_night_speed_line_3_white6);
		}
		else if (Digit_Selection == 2)
		{

			lv_img_set_src(guider_ui.screen_SC_1, &txt_night_speed_line_3_white6);
		}
		else
		{
			/*do nothing*/
		}

		break;

	case 7:
		if (Digit_Selection == 1)
		{

			lv_img_set_src(guider_ui.screen_SC_2, &txt_night_speed_line_3_white7);
		}
		else if (Digit_Selection == 2)
		{

			lv_img_set_src(guider_ui.screen_SC_1, &txt_night_speed_line_3_white7);
		}
		else
		{
			/*do nothing*/
		}

		break;

	case 8:
		if (Digit_Selection == 1)
		{

			lv_img_set_src(guider_ui.screen_SC_2, &txt_night_speed_line_3_white8);
		}
		else if (Digit_Selection == 2)
		{

			lv_img_set_src(guider_ui.screen_SC_1, &txt_night_speed_line_3_white8);
		}
		else
		{
			/*do nothing*/
		}

		break;

	case 9:
		if (Digit_Selection == 1)
		{

			lv_img_set_src(guider_ui.screen_SC_2, &txt_night_speed_line_2_white9);
		}
		else if (Digit_Selection == 2)
		{

			lv_img_set_src(guider_ui.screen_SC_2, &txt_night_speed_line_2_white9);
		}
		else
		{
			/*do nothing*/
		}

		break;
	}
}

void GUI_Day_Speedometer_Handler(void)
{

	uint8_t Digit_Value_1_u8 = 0;
	uint8_t Digit_Value_2_u8 = 0;
	uint8_t Digit_Value_3_u8 = 0;

	g_Speedo_Value_u16 = Get_display_Speed();

	if (g_Previous_Speedo_Value_u16 != g_Speedo_Value_u16)
	{

		Digit_Value_1_u8 = (g_Speedo_Value_u16) % 10;
		Digit_Value_2_u8 = (((g_Speedo_Value_u16)-Digit_Value_1_u8) % 100) / 10;
		Digit_Value_3_u8 = (((g_Speedo_Value_u16) - (Digit_Value_2_u8 * 10)) % 1000) / 100;

		if (g_Speedo_Value_u16 >= SPEED_MAX)
		{
			lv_img_set_src(guider_ui.screen_main_sc_1, &txt_day_speed_line_3_white9);

			lv_img_set_src(guider_ui.screen_main_sc_2, &txt_day_speed_line_3_white9);

			lv_img_set_src(guider_ui.screen_main_sc_3, &txt_day_speed_line_3_white1);
		}
		else
		{
			if ((g_Speedo_Value_u16 >= 0) && (g_Speedo_Value_u16 < 10))
			{

				lv_img_set_src(guider_ui.screen_main_sc_1, &txt_day_speed_line_3_white0);

				lv_img_set_src(guider_ui.screen_main_sc_2, &txt_day_speed_line_3_grey0);

				lv_img_set_src(guider_ui.screen_main_sc_3, &txt_day_speed_line_3_grey0);
			}
			else if ((g_Speedo_Value_u16 >= 10) && (g_Speedo_Value_u16 < 100))
			{

				lv_img_set_src(guider_ui.screen_main_sc_3, &txt_day_speed_line_3_grey0);

				lv_img_set_src(guider_ui.screen_main_sc_2, &txt_day_speed_line_3_white0);

				lv_img_set_src(guider_ui.screen_main_sc_1, &txt_day_speed_line_3_white0);

				if ((Digit_Value_2_u8 >= 0) && (Digit_Value_2_u8 <= 9))
				{

					Speed_Digit_Day(Digit_Value_2_u8, 1);
				}
				else
				{
				}
			}
			else if ((g_Speedo_Value_u16 >= 100) && (g_Speedo_Value_u16 < 1000))
			{

				lv_img_set_src(guider_ui.screen_main_sc_3, &txt_day_speed_line_3_white0);

				lv_img_set_src(guider_ui.screen_main_sc_2, &txt_day_speed_line_3_white0);

				lv_img_set_src(guider_ui.screen_main_sc_1, &txt_day_speed_line_3_white0);

				if ((Digit_Value_3_u8 >= 0) && (Digit_Value_3_u8 <= 9))
				{

					Speed_Digit_Day(Digit_Value_3_u8, 2);
				}
				if ((Digit_Value_2_u8 >= 0) && (Digit_Value_2_u8 <= 9))
				{

					Speed_Digit_Day(Digit_Value_2_u8, 1);
				}
			}
			else
			{
			}

			if (Digit_Value_1_u8 == 0)
			{

				lv_img_set_src(guider_ui.screen_main_sc_1, &txt_day_speed_line_3_white0);
			}
			else if (Digit_Value_1_u8 == 1)
			{
				lv_img_set_src(guider_ui.screen_main_sc_1, &txt_day_speed_line_3_white1);
			}
			else if (Digit_Value_1_u8 == 2)
			{

				lv_img_set_src(guider_ui.screen_main_sc_1, &txt_day_speed_line_3_white2);
			}
			else if (Digit_Value_1_u8 == 3)
			{
				lv_img_set_src(guider_ui.screen_main_sc_1, &txt_day_speed_line_3_white3);
			}
			else if (Digit_Value_1_u8 == 4)
			{
				lv_img_set_src(guider_ui.screen_main_sc_1, &txt_day_speed_line_3_white4);
			}
			else if (Digit_Value_1_u8 == 5)
			{

				lv_img_set_src(guider_ui.screen_main_sc_1, &txt_day_speed_line_3_white5);
			}
			else if (Digit_Value_1_u8 == 6)
			{

				lv_img_set_src(guider_ui.screen_main_sc_1, &txt_day_speed_line_3_white6);
			}
			else if (Digit_Value_1_u8 == 7)
			{

				lv_img_set_src(guider_ui.screen_main_sc_1, &txt_day_speed_line_3_white7);
			}
			else if (Digit_Value_1_u8 == 8)
			{

				lv_img_set_src(guider_ui.screen_main_sc_1, &txt_day_speed_line_3_white8);
			}
			else if (Digit_Value_1_u8 == 9)
			{
				lv_img_set_src(guider_ui.screen_main_sc_1, &txt_day_speed_line_3_white9);
			}
		}
		g_Previous_Speedo_Value_u16 = g_Speedo_Value_u16;
	}
	else
	{
		/* Do Nothing */
	}
}

void Speed_Digit_Day(uint8_t fl_no_Digit_u8, uint8_t Digit_Selection)
{
	switch (fl_no_Digit_u8)
	{
	case 0:
		if (Digit_Selection == 1)
		{
			lv_img_set_src(guider_ui.screen_main_sc_2, &txt_day_speed_line_3_white0);
		}
		else if (Digit_Selection == 2)
		{
			lv_img_set_src(guider_ui.screen_main_sc_3, &txt_day_speed_line_3_white0);
		}
		else
		{
			/*do nothing*/
		}
		break;
	case 1:
		if (Digit_Selection == 1)
		{
			lv_img_set_src(guider_ui.screen_main_sc_2, &txt_day_speed_line_3_white1);
		}
		else if (Digit_Selection == 2)
		{
			lv_img_set_src(guider_ui.screen_main_sc_3, &txt_day_speed_line_3_white1);
		}
		else
		{
			/*do nothing*/
		}
		break;

	case 2:
		if (Digit_Selection == 1)
		{
			lv_img_set_src(guider_ui.screen_main_sc_2, &txt_day_speed_line_3_white2);
		}
		else if (Digit_Selection == 2)
		{

			lv_img_set_src(guider_ui.screen_main_sc_2, &txt_day_speed_line_3_white2);
		}
		else
		{
			/*do nothing*/
		}

		break;

	case 3:
		if (Digit_Selection == 1)
		{

			lv_img_set_src(guider_ui.screen_main_sc_2, &txt_day_speed_line_3_white3);
		}
		else if (Digit_Selection == 2)
		{

			lv_img_set_src(guider_ui.screen_main_sc_2, &txt_day_speed_line_3_white3);
		}
		else
		{
			/*do nothing*/
		}

		break;

	case 4:
		if (Digit_Selection == 1)
		{

			lv_img_set_src(guider_ui.screen_main_sc_2, &txt_day_speed_line_3_white4);
		}
		else if (Digit_Selection == 2)
		{

			lv_img_set_src(guider_ui.screen_main_sc_3, &txt_day_speed_line_3_white4);
		}
		else
		{
			/*do nothing*/
		}

		break;

	case 5:
		if (Digit_Selection == 1)
		{
			lv_img_set_src(guider_ui.screen_main_sc_2, &txt_day_speed_line_3_white5);
		}
		else if (Digit_Selection == 2)
		{

			lv_img_set_src(guider_ui.screen_main_sc_3, &txt_day_speed_line_3_white5);
		}
		else
		{
			/*do nothing*/
		}

		break;

	case 6:
		if (Digit_Selection == 1)
		{

			lv_img_set_src(guider_ui.screen_main_sc_2, &txt_day_speed_line_3_white6);
		}
		else if (Digit_Selection == 2)
		{

			lv_img_set_src(guider_ui.screen_main_sc_3, &txt_day_speed_line_3_white6);
		}
		else
		{
			/*do nothing*/
		}

		break;

	case 7:
		if (Digit_Selection == 1)
		{

			lv_img_set_src(guider_ui.screen_main_sc_2, &txt_day_speed_line_3_white7);
		}
		else if (Digit_Selection == 2)
		{

			lv_img_set_src(guider_ui.screen_main_sc_3, &txt_day_speed_line_3_white7);
		}
		else
		{
			/*do nothing*/
		}

		break;

	case 8:
		if (Digit_Selection == 1)
		{

			lv_img_set_src(guider_ui.screen_main_sc_2, &txt_day_speed_line_3_white8);
		}
		else if (Digit_Selection == 2)
		{

			lv_img_set_src(guider_ui.screen_main_sc_3, &txt_day_speed_line_3_white8);
			set_obj_opa(guider_ui.screen_main_sc_3, 255);
		}
		else
		{
			/*do nothing*/
		}

		break;

	case 9:
		if (Digit_Selection == 1)
		{

			lv_img_set_src(guider_ui.screen_main_sc_2, &txt_day_speed_line_3_white9);
		}
		else if (Digit_Selection == 2)
		{

			lv_img_set_src(guider_ui.screen_main_sc_3, &txt_day_speed_line_3_white9);
		}
		else
		{
			/*do nothing*/
		}

		break;
	}
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

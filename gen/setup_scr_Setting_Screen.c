/*
 * Copyright 2022 NXP
 * SPDX-License-Identifier: MIT
 */

#include "lvgl/lvgl.h"
#include <stdio.h>
#include "gui_guider.h"
#include "events_init.h"
#include "custom.h"


void setup_scr_Setting_Screen(lv_ui *ui){

	//Write codes Setting_Screen
	ui->Setting_Screen = lv_obj_create(NULL);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_main_main_default
	static lv_style_t style_setting_screen_main_main_default;
	lv_style_reset(&style_setting_screen_main_main_default);
	lv_style_set_bg_color(&style_setting_screen_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_opa(&style_setting_screen_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen, &style_setting_screen_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_skin
	ui->Setting_Screen_skin = lv_img_create(ui->Setting_Screen);
	lv_obj_set_pos(ui->Setting_Screen_skin, 0, 0);
	lv_obj_set_size(ui->Setting_Screen_skin, 240, 320);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_skin_main_main_default
	static lv_style_t style_setting_screen_skin_main_main_default;
	lv_style_reset(&style_setting_screen_skin_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_skin_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_skin_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_skin_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_skin, &style_setting_screen_skin_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_skin, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_skin,&_Hero_RAAA_Outer_Ring_240x320);
	lv_img_set_pivot(ui->Setting_Screen_skin, 0,0);
	lv_img_set_angle(ui->Setting_Screen_skin, 0);

	//Write codes Setting_Screen_D_Cir
	ui->Setting_Screen_D_Cir = lv_img_create(ui->Setting_Screen);
	lv_obj_set_pos(ui->Setting_Screen_D_Cir, 7, 47);
	lv_obj_set_size(ui->Setting_Screen_D_Cir, 226, 226);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_d_cir_main_main_default
	static lv_style_t style_setting_screen_d_cir_main_main_default;
	lv_style_reset(&style_setting_screen_d_cir_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_d_cir_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_d_cir_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_d_cir_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_D_Cir, &style_setting_screen_d_cir_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_D_Cir, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_D_Cir,&day_white_Grey_circle);
	lv_img_set_pivot(ui->Setting_Screen_D_Cir, 0,0);
	lv_img_set_angle(ui->Setting_Screen_D_Cir, 0);

	//Write codes Setting_Screen_FogLampTT
	ui->Setting_Screen_FogLampTT = lv_imgbtn_create(ui->Setting_Screen);
	lv_obj_set_pos(ui->Setting_Screen_FogLampTT, 10, 11);
	lv_obj_set_size(ui->Setting_Screen_FogLampTT, 24, 21);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_foglamptt_main_main_default
	static lv_style_t style_setting_screen_foglamptt_main_main_default;
	lv_style_reset(&style_setting_screen_foglamptt_main_main_default);
	lv_style_set_text_color(&style_setting_screen_foglamptt_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_img_recolor(&style_setting_screen_foglamptt_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_foglamptt_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_foglamptt_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_FogLampTT, &style_setting_screen_foglamptt_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style state: LV_STATE_PRESSED for style_setting_screen_foglamptt_main_main_pressed
	static lv_style_t style_setting_screen_foglamptt_main_main_pressed;
	lv_style_reset(&style_setting_screen_foglamptt_main_main_pressed);
	lv_style_set_text_color(&style_setting_screen_foglamptt_main_main_pressed, lv_color_make(0xFF, 0x33, 0xFF));
	lv_style_set_img_recolor(&style_setting_screen_foglamptt_main_main_pressed, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_img_recolor_opa(&style_setting_screen_foglamptt_main_main_pressed, 0);
	lv_obj_add_style(ui->Setting_Screen_FogLampTT, &style_setting_screen_foglamptt_main_main_pressed, LV_PART_MAIN|LV_STATE_PRESSED);

	//Write style state: LV_STATE_CHECKED for style_setting_screen_foglamptt_main_main_checked
	static lv_style_t style_setting_screen_foglamptt_main_main_checked;
	lv_style_reset(&style_setting_screen_foglamptt_main_main_checked);
	lv_style_set_text_color(&style_setting_screen_foglamptt_main_main_checked, lv_color_make(0xFF, 0x33, 0xFF));
	lv_style_set_img_recolor(&style_setting_screen_foglamptt_main_main_checked, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_img_recolor_opa(&style_setting_screen_foglamptt_main_main_checked, 0);
	lv_obj_add_style(ui->Setting_Screen_FogLampTT, &style_setting_screen_foglamptt_main_main_checked, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_imgbtn_set_src(ui->Setting_Screen_FogLampTT, LV_IMGBTN_STATE_RELEASED, NULL, &new_header_fog_telltale, NULL);
	lv_imgbtn_set_src(ui->Setting_Screen_FogLampTT, LV_IMGBTN_STATE_PRESSED, NULL, &_Layer_0_alpha_24x20, NULL);
	lv_obj_add_flag(ui->Setting_Screen_FogLampTT, LV_OBJ_FLAG_CHECKABLE);

	//Write codes Setting_Screen_imgEngineTT
	ui->Setting_Screen_imgEngineTT = lv_imgbtn_create(ui->Setting_Screen);
	lv_obj_set_pos(ui->Setting_Screen_imgEngineTT, 204, 12);
	lv_obj_set_size(ui->Setting_Screen_imgEngineTT, 26, 18);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_imgenginett_main_main_default
	static lv_style_t style_setting_screen_imgenginett_main_main_default;
	lv_style_reset(&style_setting_screen_imgenginett_main_main_default);
	lv_style_set_text_color(&style_setting_screen_imgenginett_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_img_recolor(&style_setting_screen_imgenginett_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_imgenginett_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_imgenginett_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_imgEngineTT, &style_setting_screen_imgenginett_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style state: LV_STATE_PRESSED for style_setting_screen_imgenginett_main_main_pressed
	static lv_style_t style_setting_screen_imgenginett_main_main_pressed;
	lv_style_reset(&style_setting_screen_imgenginett_main_main_pressed);
	lv_style_set_text_color(&style_setting_screen_imgenginett_main_main_pressed, lv_color_make(0xFF, 0x33, 0xFF));
	lv_style_set_img_recolor(&style_setting_screen_imgenginett_main_main_pressed, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_img_recolor_opa(&style_setting_screen_imgenginett_main_main_pressed, 0);
	lv_obj_add_style(ui->Setting_Screen_imgEngineTT, &style_setting_screen_imgenginett_main_main_pressed, LV_PART_MAIN|LV_STATE_PRESSED);

	//Write style state: LV_STATE_CHECKED for style_setting_screen_imgenginett_main_main_checked
	static lv_style_t style_setting_screen_imgenginett_main_main_checked;
	lv_style_reset(&style_setting_screen_imgenginett_main_main_checked);
	lv_style_set_text_color(&style_setting_screen_imgenginett_main_main_checked, lv_color_make(0xFF, 0x33, 0xFF));
	lv_style_set_img_recolor(&style_setting_screen_imgenginett_main_main_checked, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_img_recolor_opa(&style_setting_screen_imgenginett_main_main_checked, 0);
	lv_obj_add_style(ui->Setting_Screen_imgEngineTT, &style_setting_screen_imgenginett_main_main_checked, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_imgbtn_set_src(ui->Setting_Screen_imgEngineTT, LV_IMGBTN_STATE_RELEASED, NULL, &new_engine_telltale, NULL);
	lv_imgbtn_set_src(ui->Setting_Screen_imgEngineTT, LV_IMGBTN_STATE_PRESSED, NULL, &_Layer_0_alpha_25x17, NULL);
	lv_obj_add_flag(ui->Setting_Screen_imgEngineTT, LV_OBJ_FLAG_CHECKABLE);

	//Write codes Setting_Screen_imgOilTelltale
	ui->Setting_Screen_imgOilTelltale = lv_imgbtn_create(ui->Setting_Screen);
	lv_obj_set_pos(ui->Setting_Screen_imgOilTelltale, 4, 290);
	lv_obj_set_size(ui->Setting_Screen_imgOilTelltale, 34, 14);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_imgoiltelltale_main_main_default
	static lv_style_t style_setting_screen_imgoiltelltale_main_main_default;
	lv_style_reset(&style_setting_screen_imgoiltelltale_main_main_default);
	lv_style_set_text_color(&style_setting_screen_imgoiltelltale_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_img_recolor(&style_setting_screen_imgoiltelltale_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_imgoiltelltale_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_imgoiltelltale_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_imgOilTelltale, &style_setting_screen_imgoiltelltale_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style state: LV_STATE_PRESSED for style_setting_screen_imgoiltelltale_main_main_pressed
	static lv_style_t style_setting_screen_imgoiltelltale_main_main_pressed;
	lv_style_reset(&style_setting_screen_imgoiltelltale_main_main_pressed);
	lv_style_set_text_color(&style_setting_screen_imgoiltelltale_main_main_pressed, lv_color_make(0xFF, 0x33, 0xFF));
	lv_style_set_img_recolor(&style_setting_screen_imgoiltelltale_main_main_pressed, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_img_recolor_opa(&style_setting_screen_imgoiltelltale_main_main_pressed, 0);
	lv_obj_add_style(ui->Setting_Screen_imgOilTelltale, &style_setting_screen_imgoiltelltale_main_main_pressed, LV_PART_MAIN|LV_STATE_PRESSED);

	//Write style state: LV_STATE_CHECKED for style_setting_screen_imgoiltelltale_main_main_checked
	static lv_style_t style_setting_screen_imgoiltelltale_main_main_checked;
	lv_style_reset(&style_setting_screen_imgoiltelltale_main_main_checked);
	lv_style_set_text_color(&style_setting_screen_imgoiltelltale_main_main_checked, lv_color_make(0xFF, 0x33, 0xFF));
	lv_style_set_img_recolor(&style_setting_screen_imgoiltelltale_main_main_checked, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_img_recolor_opa(&style_setting_screen_imgoiltelltale_main_main_checked, 0);
	lv_obj_add_style(ui->Setting_Screen_imgOilTelltale, &style_setting_screen_imgoiltelltale_main_main_checked, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_imgbtn_set_src(ui->Setting_Screen_imgOilTelltale, LV_IMGBTN_STATE_RELEASED, NULL, &new_oil_telltale, NULL);
	lv_imgbtn_set_src(ui->Setting_Screen_imgOilTelltale, LV_IMGBTN_STATE_PRESSED, NULL, &_Layer_0_alpha_32x13, NULL);
	lv_obj_add_flag(ui->Setting_Screen_imgOilTelltale, LV_OBJ_FLAG_CHECKABLE);

	//Write codes Setting_Screen_Clock_hour
	ui->Setting_Screen_Clock_hour = lv_label_create(ui->Setting_Screen);
	lv_obj_set_pos(ui->Setting_Screen_Clock_hour, 75, 285);
	lv_obj_set_size(ui->Setting_Screen_Clock_hour, 21, 15);
	lv_label_set_text(ui->Setting_Screen_Clock_hour, "24");
	lv_label_set_long_mode(ui->Setting_Screen_Clock_hour, LV_LABEL_LONG_WRAP);
	lv_obj_set_style_text_align(ui->Setting_Screen_Clock_hour, LV_TEXT_ALIGN_RIGHT, 0);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_clock_hour_main_main_default
	static lv_style_t style_setting_screen_clock_hour_main_main_default;
	lv_style_reset(&style_setting_screen_clock_hour_main_main_default);
	lv_style_set_radius(&style_setting_screen_clock_hour_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_clock_hour_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_color(&style_setting_screen_clock_hour_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_dir(&style_setting_screen_clock_hour_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_clock_hour_main_main_default, 0);
	lv_style_set_text_color(&style_setting_screen_clock_hour_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_setting_screen_clock_hour_main_main_default, &lv_font_FjallaOne_Regular_14);
	lv_style_set_text_letter_space(&style_setting_screen_clock_hour_main_main_default, 0);
	lv_style_set_pad_left(&style_setting_screen_clock_hour_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_clock_hour_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_clock_hour_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_clock_hour_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_Clock_hour, &style_setting_screen_clock_hour_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_Clock_min
	ui->Setting_Screen_Clock_min = lv_label_create(ui->Setting_Screen);
	lv_obj_set_pos(ui->Setting_Screen_Clock_min, 107, 285);
	lv_obj_set_size(ui->Setting_Screen_Clock_min, 20, 15);
	lv_label_set_text(ui->Setting_Screen_Clock_min, "60");
	lv_label_set_long_mode(ui->Setting_Screen_Clock_min, LV_LABEL_LONG_WRAP);
	lv_obj_set_style_text_align(ui->Setting_Screen_Clock_min, LV_TEXT_ALIGN_LEFT, 0);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_clock_min_main_main_default
	static lv_style_t style_setting_screen_clock_min_main_main_default;
	lv_style_reset(&style_setting_screen_clock_min_main_main_default);
	lv_style_set_radius(&style_setting_screen_clock_min_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_clock_min_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_color(&style_setting_screen_clock_min_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_dir(&style_setting_screen_clock_min_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_clock_min_main_main_default, 0);
	lv_style_set_text_color(&style_setting_screen_clock_min_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_setting_screen_clock_min_main_main_default, &lv_font_FjallaOne_Regular_14);
	lv_style_set_text_letter_space(&style_setting_screen_clock_min_main_main_default, 0);
	lv_style_set_pad_left(&style_setting_screen_clock_min_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_clock_min_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_clock_min_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_clock_min_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_Clock_min, &style_setting_screen_clock_min_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_Clock_Colan
	ui->Setting_Screen_Clock_Colan = lv_label_create(ui->Setting_Screen);
	lv_obj_set_pos(ui->Setting_Screen_Clock_Colan, 94, 285);
	lv_obj_set_size(ui->Setting_Screen_Clock_Colan, 15, 15);
	lv_label_set_text(ui->Setting_Screen_Clock_Colan, ":");
	lv_label_set_long_mode(ui->Setting_Screen_Clock_Colan, LV_LABEL_LONG_WRAP);
	lv_obj_set_style_text_align(ui->Setting_Screen_Clock_Colan, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_clock_colan_main_main_default
	static lv_style_t style_setting_screen_clock_colan_main_main_default;
	lv_style_reset(&style_setting_screen_clock_colan_main_main_default);
	lv_style_set_radius(&style_setting_screen_clock_colan_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_clock_colan_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_color(&style_setting_screen_clock_colan_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_dir(&style_setting_screen_clock_colan_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_clock_colan_main_main_default, 0);
	lv_style_set_text_color(&style_setting_screen_clock_colan_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_setting_screen_clock_colan_main_main_default, &lv_font_FjallaOne_Regular_14);
	lv_style_set_text_letter_space(&style_setting_screen_clock_colan_main_main_default, 2);
	lv_style_set_pad_left(&style_setting_screen_clock_colan_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_clock_colan_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_clock_colan_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_clock_colan_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_Clock_Colan, &style_setting_screen_clock_colan_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_Clock_AM
	ui->Setting_Screen_Clock_AM = lv_label_create(ui->Setting_Screen);
	lv_obj_set_pos(ui->Setting_Screen_Clock_AM, 130, 285);
	lv_obj_set_size(ui->Setting_Screen_Clock_AM, 28, 13);
	lv_label_set_text(ui->Setting_Screen_Clock_AM, "AM");
	lv_label_set_long_mode(ui->Setting_Screen_Clock_AM, LV_LABEL_LONG_WRAP);
	lv_obj_set_style_text_align(ui->Setting_Screen_Clock_AM, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_clock_am_main_main_default
	static lv_style_t style_setting_screen_clock_am_main_main_default;
	lv_style_reset(&style_setting_screen_clock_am_main_main_default);
	lv_style_set_radius(&style_setting_screen_clock_am_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_clock_am_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_color(&style_setting_screen_clock_am_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_dir(&style_setting_screen_clock_am_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_clock_am_main_main_default, 0);
	lv_style_set_text_color(&style_setting_screen_clock_am_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_setting_screen_clock_am_main_main_default, &lv_font_FjallaOne_Regular_14);
	lv_style_set_text_letter_space(&style_setting_screen_clock_am_main_main_default, 0);
	lv_style_set_pad_left(&style_setting_screen_clock_am_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_clock_am_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_clock_am_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_clock_am_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_Clock_AM, &style_setting_screen_clock_am_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_display_label
	ui->Setting_Screen_display_label = lv_label_create(ui->Setting_Screen);
	lv_obj_set_pos(ui->Setting_Screen_display_label, 0, 22);
	lv_obj_set_size(ui->Setting_Screen_display_label, 240, 17);
	lv_label_set_text(ui->Setting_Screen_display_label, "DATE AND TIME");
	lv_label_set_long_mode(ui->Setting_Screen_display_label, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->Setting_Screen_display_label, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_display_label_main_main_default
	static lv_style_t style_setting_screen_display_label_main_main_default;
	lv_style_reset(&style_setting_screen_display_label_main_main_default);
	lv_style_set_radius(&style_setting_screen_display_label_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_display_label_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_color(&style_setting_screen_display_label_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_dir(&style_setting_screen_display_label_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_display_label_main_main_default, 0);
	lv_style_set_text_color(&style_setting_screen_display_label_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_setting_screen_display_label_main_main_default, &lv_font_FjallaOne_Regular_19);
	lv_style_set_text_letter_space(&style_setting_screen_display_label_main_main_default, 0);
	lv_style_set_pad_left(&style_setting_screen_display_label_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_display_label_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_display_label_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_display_label_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_display_label, &style_setting_screen_display_label_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	

	//Write codes Setting_Screen_setting_main_container
	ui->Setting_Screen_setting_main_container = lv_obj_create(ui->Setting_Screen);
	lv_obj_set_pos(ui->Setting_Screen_setting_main_container, 0, 0);
	lv_obj_set_size(ui->Setting_Screen_setting_main_container, 240, 320);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_setting_main_container_main_main_default
	static lv_style_t style_setting_screen_setting_main_container_main_main_default;
	lv_style_reset(&style_setting_screen_setting_main_container_main_main_default);
	lv_style_set_radius(&style_setting_screen_setting_main_container_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_setting_main_container_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_color(&style_setting_screen_setting_main_container_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_dir(&style_setting_screen_setting_main_container_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_setting_main_container_main_main_default, 0);
	lv_style_set_border_color(&style_setting_screen_setting_main_container_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_border_width(&style_setting_screen_setting_main_container_main_main_default, 0);
	lv_style_set_border_opa(&style_setting_screen_setting_main_container_main_main_default, 255);
	lv_style_set_pad_left(&style_setting_screen_setting_main_container_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_setting_main_container_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_setting_main_container_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_setting_main_container_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_setting_main_container, &style_setting_screen_setting_main_container_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_main_side_night_img
	ui->Setting_Screen_main_side_night_img = lv_img_create(ui->Setting_Screen_setting_main_container);
	lv_obj_set_pos(ui->Setting_Screen_main_side_night_img, 16, 142);
	lv_obj_set_size(ui->Setting_Screen_main_side_night_img, 40, 40);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_main_side_night_img_main_main_default
	static lv_style_t style_setting_screen_main_side_night_img_main_main_default;
	lv_style_reset(&style_setting_screen_main_side_night_img_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_main_side_night_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_main_side_night_img_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_main_side_night_img_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_main_side_night_img, &style_setting_screen_main_side_night_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_main_sub_button_night_img
	ui->Setting_Screen_main_sub_button_night_img = lv_img_create(ui->Setting_Screen_setting_main_container);
	lv_obj_set_pos(ui->Setting_Screen_main_sub_button_night_img, 196, 149);
	lv_obj_set_size(ui->Setting_Screen_main_sub_button_night_img, 24, 24);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_main_sub_button_night_img_main_main_default
	static lv_style_t style_setting_screen_main_sub_button_night_img_main_main_default;
	lv_style_reset(&style_setting_screen_main_sub_button_night_img_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_main_sub_button_night_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_main_sub_button_night_img_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_main_sub_button_night_img_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_main_sub_button_night_img, &style_setting_screen_main_sub_button_night_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_main_sub_button_night_img, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_main_sub_button_night_img,&subbtn_night_24x24);
	lv_img_set_pivot(ui->Setting_Screen_main_sub_button_night_img, 0,0);
	lv_img_set_angle(ui->Setting_Screen_main_sub_button_night_img, 0);

	//Write codes Setting_Screen_main_up_arrow_night_img
	ui->Setting_Screen_main_up_arrow_night_img = lv_img_create(ui->Setting_Screen_setting_main_container);
	lv_obj_set_pos(ui->Setting_Screen_main_up_arrow_night_img, 110, 65);
	lv_obj_set_size(ui->Setting_Screen_main_up_arrow_night_img, 20, 11);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_main_up_arrow_night_img_main_main_default
	static lv_style_t style_setting_screen_main_up_arrow_night_img_main_main_default;
	lv_style_reset(&style_setting_screen_main_up_arrow_night_img_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_main_up_arrow_night_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_main_up_arrow_night_img_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_main_up_arrow_night_img_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_main_up_arrow_night_img, &style_setting_screen_main_up_arrow_night_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_main_up_arrow_night_img, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_main_up_arrow_night_img,&_Setting_Up_Arrow_20x11);
	lv_img_set_pivot(ui->Setting_Screen_main_up_arrow_night_img, 0,0);
	lv_img_set_angle(ui->Setting_Screen_main_up_arrow_night_img, 0);

	//Write codes Setting_Screen_main_down_arr_night_img
	ui->Setting_Screen_main_down_arr_night_img = lv_img_create(ui->Setting_Screen_setting_main_container);
	lv_obj_set_pos(ui->Setting_Screen_main_down_arr_night_img, 110, 238);
	lv_obj_set_size(ui->Setting_Screen_main_down_arr_night_img, 20, 11);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_main_down_arr_night_img_main_main_default
	static lv_style_t style_setting_screen_main_down_arr_night_img_main_main_default;
	lv_style_reset(&style_setting_screen_main_down_arr_night_img_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_main_down_arr_night_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_main_down_arr_night_img_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_main_down_arr_night_img_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_main_down_arr_night_img, &style_setting_screen_main_down_arr_night_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_main_down_arr_night_img, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_main_down_arr_night_img,&_Setting_Drow_Arrow_20x11);
	lv_img_set_pivot(ui->Setting_Screen_main_down_arr_night_img, 0,0);
	lv_img_set_angle(ui->Setting_Screen_main_down_arr_night_img, 0);

	//Write codes Setting_Screen_main_night_L1
	ui->Setting_Screen_main_night_L1 = lv_label_create(ui->Setting_Screen_setting_main_container);
	lv_obj_set_pos(ui->Setting_Screen_main_night_L1, 0, 100);
	lv_obj_set_size(ui->Setting_Screen_main_night_L1, 240, 18);
	lv_label_set_text(ui->Setting_Screen_main_night_L1, "");
	lv_label_set_long_mode(ui->Setting_Screen_main_night_L1, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->Setting_Screen_main_night_L1, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_main_night_l1_main_main_default
	static lv_style_t style_setting_screen_main_night_l1_main_main_default;
	lv_style_reset(&style_setting_screen_main_night_l1_main_main_default);
	lv_style_set_radius(&style_setting_screen_main_night_l1_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_main_night_l1_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_setting_screen_main_night_l1_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_setting_screen_main_night_l1_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_main_night_l1_main_main_default, 0);
	lv_style_set_text_color(&style_setting_screen_main_night_l1_main_main_default, lv_color_make(0x50, 0x50, 0x50));
	lv_style_set_text_font(&style_setting_screen_main_night_l1_main_main_default, &lv_font_FjallaOne_Regular_22);
	lv_style_set_text_letter_space(&style_setting_screen_main_night_l1_main_main_default, 0);
	lv_style_set_pad_left(&style_setting_screen_main_night_l1_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_main_night_l1_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_main_night_l1_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_main_night_l1_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_main_night_L1, &style_setting_screen_main_night_l1_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_main_night_L2
	ui->Setting_Screen_main_night_L2 = lv_label_create(ui->Setting_Screen_setting_main_container);
	lv_obj_set_pos(ui->Setting_Screen_main_night_L2, 0, 148);
	lv_obj_set_size(ui->Setting_Screen_main_night_L2, 240, 18);
	lv_label_set_text(ui->Setting_Screen_main_night_L2, "");
	lv_label_set_long_mode(ui->Setting_Screen_main_night_L2, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->Setting_Screen_main_night_L2, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_main_night_l2_main_main_default
	static lv_style_t style_setting_screen_main_night_l2_main_main_default;
	lv_style_reset(&style_setting_screen_main_night_l2_main_main_default);
	lv_style_set_radius(&style_setting_screen_main_night_l2_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_main_night_l2_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_setting_screen_main_night_l2_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_setting_screen_main_night_l2_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_main_night_l2_main_main_default, 0);
	lv_style_set_text_color(&style_setting_screen_main_night_l2_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_setting_screen_main_night_l2_main_main_default, &lv_font_FjallaOne_Regular_22);
	lv_style_set_text_letter_space(&style_setting_screen_main_night_l2_main_main_default, 0);
	lv_style_set_pad_left(&style_setting_screen_main_night_l2_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_main_night_l2_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_main_night_l2_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_main_night_l2_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_main_night_L2, &style_setting_screen_main_night_l2_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_main_night_L3
	ui->Setting_Screen_main_night_L3 = lv_label_create(ui->Setting_Screen_setting_main_container);
	lv_obj_set_pos(ui->Setting_Screen_main_night_L3, 0, 196);
	lv_obj_set_size(ui->Setting_Screen_main_night_L3, 240, 18);
	lv_label_set_text(ui->Setting_Screen_main_night_L3, "");
	lv_label_set_long_mode(ui->Setting_Screen_main_night_L3, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->Setting_Screen_main_night_L3, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_main_night_l3_main_main_default
	static lv_style_t style_setting_screen_main_night_l3_main_main_default;
	lv_style_reset(&style_setting_screen_main_night_l3_main_main_default);
	lv_style_set_radius(&style_setting_screen_main_night_l3_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_main_night_l3_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_setting_screen_main_night_l3_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_setting_screen_main_night_l3_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_main_night_l3_main_main_default, 0);
	lv_style_set_text_color(&style_setting_screen_main_night_l3_main_main_default, lv_color_make(0x50, 0x50, 0x50));
	lv_style_set_text_font(&style_setting_screen_main_night_l3_main_main_default, &lv_font_FjallaOne_Regular_22);
	lv_style_set_text_letter_space(&style_setting_screen_main_night_l3_main_main_default, 0);
	lv_style_set_pad_left(&style_setting_screen_main_night_l3_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_main_night_l3_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_main_night_l3_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_main_night_l3_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_main_night_L3, &style_setting_screen_main_night_l3_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_setting_main_day_container
	ui->Setting_Screen_setting_main_day_container = lv_obj_create(ui->Setting_Screen);
	lv_obj_set_pos(ui->Setting_Screen_setting_main_day_container, 0, 0);
	lv_obj_set_size(ui->Setting_Screen_setting_main_day_container, 240, 320);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_setting_main_day_container_main_main_default
	static lv_style_t style_setting_screen_setting_main_day_container_main_main_default;
	lv_style_reset(&style_setting_screen_setting_main_day_container_main_main_default);
	lv_style_set_radius(&style_setting_screen_setting_main_day_container_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_setting_main_day_container_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_color(&style_setting_screen_setting_main_day_container_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_dir(&style_setting_screen_setting_main_day_container_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_setting_main_day_container_main_main_default, 0);
	lv_style_set_border_color(&style_setting_screen_setting_main_day_container_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_border_width(&style_setting_screen_setting_main_day_container_main_main_default, 0);
	lv_style_set_border_opa(&style_setting_screen_setting_main_day_container_main_main_default, 255);
	lv_style_set_pad_left(&style_setting_screen_setting_main_day_container_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_setting_main_day_container_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_setting_main_day_container_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_setting_main_day_container_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_setting_main_day_container, &style_setting_screen_setting_main_day_container_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_main_day_circle_img
	ui->Setting_Screen_main_day_circle_img = lv_img_create(ui->Setting_Screen_setting_main_day_container);
	lv_obj_set_pos(ui->Setting_Screen_main_day_circle_img, 7, 47);
	lv_obj_set_size(ui->Setting_Screen_main_day_circle_img, 226, 226);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_main_day_circle_img_main_main_default
	static lv_style_t style_setting_screen_main_day_circle_img_main_main_default;
	lv_style_reset(&style_setting_screen_main_day_circle_img_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_main_day_circle_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_main_day_circle_img_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_main_day_circle_img_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_main_day_circle_img, &style_setting_screen_main_day_circle_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_main_day_circle_img, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_main_day_circle_img,&day_white_Grey_circle);
	lv_img_set_pivot(ui->Setting_Screen_main_day_circle_img, 0,0);
	lv_img_set_angle(ui->Setting_Screen_main_day_circle_img, 0);

	//Write codes Setting_Screen_main_side_day_img
	ui->Setting_Screen_main_side_day_img = lv_img_create(ui->Setting_Screen_setting_main_day_container);
	lv_obj_set_pos(ui->Setting_Screen_main_side_day_img, 16, 142);
	lv_obj_set_size(ui->Setting_Screen_main_side_day_img, 40, 40);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_main_side_day_img_main_main_default
	static lv_style_t style_setting_screen_main_side_day_img_main_main_default;
	lv_style_reset(&style_setting_screen_main_side_day_img_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_main_side_day_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_main_side_day_img_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_main_side_day_img_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_main_side_day_img, &style_setting_screen_main_side_day_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_main_sub_button_day_img
	ui->Setting_Screen_main_sub_button_day_img = lv_img_create(ui->Setting_Screen_setting_main_day_container);
	lv_obj_set_pos(ui->Setting_Screen_main_sub_button_day_img, 196, 149);
	lv_obj_set_size(ui->Setting_Screen_main_sub_button_day_img, 24, 24);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_main_sub_button_day_img_main_main_default
	static lv_style_t style_setting_screen_main_sub_button_day_img_main_main_default;
	lv_style_reset(&style_setting_screen_main_sub_button_day_img_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_main_sub_button_day_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_main_sub_button_day_img_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_main_sub_button_day_img_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_main_sub_button_day_img, &style_setting_screen_main_sub_button_day_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_main_sub_button_day_img, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_main_sub_button_day_img,&subbtn_day_24x24);
	lv_img_set_pivot(ui->Setting_Screen_main_sub_button_day_img, 0,0);
	lv_img_set_angle(ui->Setting_Screen_main_sub_button_day_img, 0);

	//Write codes Setting_Screen_main_up_night_day_img
	ui->Setting_Screen_main_up_night_day_img = lv_img_create(ui->Setting_Screen_setting_main_day_container);
	lv_obj_set_pos(ui->Setting_Screen_main_up_night_day_img, 110, 65);
	lv_obj_set_size(ui->Setting_Screen_main_up_night_day_img, 20, 11);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_main_up_night_day_img_main_main_default
	static lv_style_t style_setting_screen_main_up_night_day_img_main_main_default;
	lv_style_reset(&style_setting_screen_main_up_night_day_img_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_main_up_night_day_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_main_up_night_day_img_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_main_up_night_day_img_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_main_up_night_day_img, &style_setting_screen_main_up_night_day_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_main_up_night_day_img, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_main_up_night_day_img,&_day_up_arrow_20x11);
	lv_img_set_pivot(ui->Setting_Screen_main_up_night_day_img, 0,0);
	lv_img_set_angle(ui->Setting_Screen_main_up_night_day_img, 0);

	//Write codes Setting_Screen_main_down_arr_day_img
	ui->Setting_Screen_main_down_arr_day_img = lv_img_create(ui->Setting_Screen_setting_main_day_container);
	lv_obj_set_pos(ui->Setting_Screen_main_down_arr_day_img, 110, 238);
	lv_obj_set_size(ui->Setting_Screen_main_down_arr_day_img, 20, 11);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_main_down_arr_day_img_main_main_default
	static lv_style_t style_setting_screen_main_down_arr_day_img_main_main_default;
	lv_style_reset(&style_setting_screen_main_down_arr_day_img_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_main_down_arr_day_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_main_down_arr_day_img_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_main_down_arr_day_img_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_main_down_arr_day_img, &style_setting_screen_main_down_arr_day_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_main_down_arr_day_img, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_main_down_arr_day_img,&_day_down_arrow_20x11);
	lv_img_set_pivot(ui->Setting_Screen_main_down_arr_day_img, 0,0);
	lv_img_set_angle(ui->Setting_Screen_main_down_arr_day_img, 0);

	//Write codes Setting_Screen_main_day_L1
	ui->Setting_Screen_main_day_L1 = lv_label_create(ui->Setting_Screen_setting_main_day_container);
	lv_obj_set_pos(ui->Setting_Screen_main_day_L1, 0, 100);
	lv_obj_set_size(ui->Setting_Screen_main_day_L1, 240, 18);
	lv_label_set_text(ui->Setting_Screen_main_day_L1, "");
	lv_label_set_long_mode(ui->Setting_Screen_main_day_L1, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->Setting_Screen_main_day_L1, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_main_day_l1_main_main_default
	static lv_style_t style_setting_screen_main_day_l1_main_main_default;
	lv_style_reset(&style_setting_screen_main_day_l1_main_main_default);
	lv_style_set_radius(&style_setting_screen_main_day_l1_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_main_day_l1_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_setting_screen_main_day_l1_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_setting_screen_main_day_l1_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_main_day_l1_main_main_default, 0);
	lv_style_set_text_color(&style_setting_screen_main_day_l1_main_main_default, lv_color_make(0xb8, 0xb8, 0xb8));
	lv_style_set_text_font(&style_setting_screen_main_day_l1_main_main_default, &lv_font_FjallaOne_Regular_22);
	lv_style_set_text_letter_space(&style_setting_screen_main_day_l1_main_main_default, 0);
	lv_style_set_pad_left(&style_setting_screen_main_day_l1_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_main_day_l1_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_main_day_l1_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_main_day_l1_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_main_day_L1, &style_setting_screen_main_day_l1_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_main_day_L2
	ui->Setting_Screen_main_day_L2 = lv_label_create(ui->Setting_Screen_setting_main_day_container);
	lv_obj_set_pos(ui->Setting_Screen_main_day_L2, 0, 148);
	lv_obj_set_size(ui->Setting_Screen_main_day_L2, 240, 18);
	lv_label_set_text(ui->Setting_Screen_main_day_L2, "");
	lv_label_set_long_mode(ui->Setting_Screen_main_day_L2, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->Setting_Screen_main_day_L2, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_main_day_l2_main_main_default
	static lv_style_t style_setting_screen_main_day_l2_main_main_default;
	lv_style_reset(&style_setting_screen_main_day_l2_main_main_default);
	lv_style_set_radius(&style_setting_screen_main_day_l2_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_main_day_l2_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_setting_screen_main_day_l2_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_setting_screen_main_day_l2_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_main_day_l2_main_main_default, 0);
	lv_style_set_text_color(&style_setting_screen_main_day_l2_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_setting_screen_main_day_l2_main_main_default, &lv_font_FjallaOne_Regular_22);
	lv_style_set_text_letter_space(&style_setting_screen_main_day_l2_main_main_default, 0);
	lv_style_set_pad_left(&style_setting_screen_main_day_l2_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_main_day_l2_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_main_day_l2_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_main_day_l2_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_main_day_L2, &style_setting_screen_main_day_l2_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_main_day_L3
	ui->Setting_Screen_main_day_L3 = lv_label_create(ui->Setting_Screen_setting_main_day_container);
	lv_obj_set_pos(ui->Setting_Screen_main_day_L3, 0, 196);
	lv_obj_set_size(ui->Setting_Screen_main_day_L3, 240, 18);
	lv_label_set_text(ui->Setting_Screen_main_day_L3, "");
	lv_label_set_long_mode(ui->Setting_Screen_main_day_L3, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->Setting_Screen_main_day_L3, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_main_day_l3_main_main_default
	static lv_style_t style_setting_screen_main_day_l3_main_main_default;
	lv_style_reset(&style_setting_screen_main_day_l3_main_main_default);
	lv_style_set_radius(&style_setting_screen_main_day_l3_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_main_day_l3_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_setting_screen_main_day_l3_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_setting_screen_main_day_l3_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_main_day_l3_main_main_default, 0);
	lv_style_set_text_color(&style_setting_screen_main_day_l3_main_main_default, lv_color_make(0xb8, 0xb8, 0xb8));
	lv_style_set_text_font(&style_setting_screen_main_day_l3_main_main_default, &lv_font_FjallaOne_Regular_22);
	lv_style_set_text_letter_space(&style_setting_screen_main_day_l3_main_main_default, 0);
	lv_style_set_pad_left(&style_setting_screen_main_day_l3_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_main_day_l3_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_main_day_l3_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_main_day_l3_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_main_day_L3, &style_setting_screen_main_day_l3_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_setting_bike_night_container
	ui->Setting_Screen_setting_bike_night_container = lv_obj_create(ui->Setting_Screen);
	lv_obj_set_pos(ui->Setting_Screen_setting_bike_night_container, 0, 0);
	lv_obj_set_size(ui->Setting_Screen_setting_bike_night_container, 240, 320);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_setting_bike_night_container_main_main_default
	static lv_style_t style_setting_screen_setting_bike_night_container_main_main_default;
	lv_style_reset(&style_setting_screen_setting_bike_night_container_main_main_default);
	lv_style_set_radius(&style_setting_screen_setting_bike_night_container_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_setting_bike_night_container_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_color(&style_setting_screen_setting_bike_night_container_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_dir(&style_setting_screen_setting_bike_night_container_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_setting_bike_night_container_main_main_default, 0);
	lv_style_set_border_color(&style_setting_screen_setting_bike_night_container_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_border_width(&style_setting_screen_setting_bike_night_container_main_main_default, 0);
	lv_style_set_border_opa(&style_setting_screen_setting_bike_night_container_main_main_default, 255);
	lv_style_set_pad_left(&style_setting_screen_setting_bike_night_container_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_setting_bike_night_container_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_setting_bike_night_container_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_setting_bike_night_container_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_setting_bike_night_container, &style_setting_screen_setting_bike_night_container_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_bike_side_night_img
	ui->Setting_Screen_bike_side_night_img = lv_img_create(ui->Setting_Screen_setting_bike_night_container);
	lv_obj_set_pos(ui->Setting_Screen_bike_side_night_img, 16, 142);
	lv_obj_set_size(ui->Setting_Screen_bike_side_night_img, 40, 40);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_bike_side_night_img_main_main_default
	static lv_style_t style_setting_screen_bike_side_night_img_main_main_default;
	lv_style_reset(&style_setting_screen_bike_side_night_img_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_bike_side_night_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_bike_side_night_img_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_bike_side_night_img_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_bike_side_night_img, &style_setting_screen_bike_side_night_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_bike_sub_button_night_img
	ui->Setting_Screen_bike_sub_button_night_img = lv_img_create(ui->Setting_Screen_setting_bike_night_container);
	lv_obj_set_pos(ui->Setting_Screen_bike_sub_button_night_img, 196, 149);
	lv_obj_set_size(ui->Setting_Screen_bike_sub_button_night_img, 24, 24);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_bike_sub_button_night_img_main_main_default
	static lv_style_t style_setting_screen_bike_sub_button_night_img_main_main_default;
	lv_style_reset(&style_setting_screen_bike_sub_button_night_img_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_bike_sub_button_night_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_bike_sub_button_night_img_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_bike_sub_button_night_img_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_bike_sub_button_night_img, &style_setting_screen_bike_sub_button_night_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_bike_sub_button_night_img, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_bike_sub_button_night_img,&subbtn_night_24x24);
	lv_img_set_pivot(ui->Setting_Screen_bike_sub_button_night_img, 0,0);
	lv_img_set_angle(ui->Setting_Screen_bike_sub_button_night_img, 0);

	//Write codes Setting_Screen_bike_up_arrow_night_img
	ui->Setting_Screen_bike_up_arrow_night_img = lv_img_create(ui->Setting_Screen_setting_bike_night_container);
	lv_obj_set_pos(ui->Setting_Screen_bike_up_arrow_night_img, 110, 65);
	lv_obj_set_size(ui->Setting_Screen_bike_up_arrow_night_img, 20, 11);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_bike_up_arrow_night_img_main_main_default
	static lv_style_t style_setting_screen_bike_up_arrow_night_img_main_main_default;
	lv_style_reset(&style_setting_screen_bike_up_arrow_night_img_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_bike_up_arrow_night_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_bike_up_arrow_night_img_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_bike_up_arrow_night_img_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_bike_up_arrow_night_img, &style_setting_screen_bike_up_arrow_night_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_bike_up_arrow_night_img, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_bike_up_arrow_night_img,&_Setting_Up_Arrow_20x11);
	lv_img_set_pivot(ui->Setting_Screen_bike_up_arrow_night_img, 0,0);
	lv_img_set_angle(ui->Setting_Screen_bike_up_arrow_night_img, 0);

	//Write codes Setting_Screen_bike_down_arrow_night_img
	ui->Setting_Screen_bike_down_arrow_night_img = lv_img_create(ui->Setting_Screen_setting_bike_night_container);
	lv_obj_set_pos(ui->Setting_Screen_bike_down_arrow_night_img, 110, 238);
	lv_obj_set_size(ui->Setting_Screen_bike_down_arrow_night_img, 20, 11);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_bike_down_arrow_night_img_main_main_default
	static lv_style_t style_setting_screen_bike_down_arrow_night_img_main_main_default;
	lv_style_reset(&style_setting_screen_bike_down_arrow_night_img_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_bike_down_arrow_night_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_bike_down_arrow_night_img_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_bike_down_arrow_night_img_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_bike_down_arrow_night_img, &style_setting_screen_bike_down_arrow_night_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_bike_down_arrow_night_img, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_bike_down_arrow_night_img,&_Setting_Drow_Arrow_20x11);
	lv_img_set_pivot(ui->Setting_Screen_bike_down_arrow_night_img, 0,0);
	lv_img_set_angle(ui->Setting_Screen_bike_down_arrow_night_img, 0);

	//Write codes Setting_Screen_bike_night_L1
	ui->Setting_Screen_bike_night_L1 = lv_label_create(ui->Setting_Screen_setting_bike_night_container);
	lv_obj_set_pos(ui->Setting_Screen_bike_night_L1, 0, 100);
	lv_obj_set_size(ui->Setting_Screen_bike_night_L1, 240, 26);
	lv_label_set_text(ui->Setting_Screen_bike_night_L1, "");
	lv_label_set_long_mode(ui->Setting_Screen_bike_night_L1, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->Setting_Screen_bike_night_L1, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_bike_night_l1_main_main_default
	static lv_style_t style_setting_screen_bike_night_l1_main_main_default;
	lv_style_reset(&style_setting_screen_bike_night_l1_main_main_default);
	lv_style_set_radius(&style_setting_screen_bike_night_l1_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_bike_night_l1_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_setting_screen_bike_night_l1_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_setting_screen_bike_night_l1_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_bike_night_l1_main_main_default, 0);
	lv_style_set_text_color(&style_setting_screen_bike_night_l1_main_main_default, lv_color_make(0x50, 0x50, 0x50));
	lv_style_set_text_font(&style_setting_screen_bike_night_l1_main_main_default, &lv_font_FjallaOne_Regular_22);
	lv_style_set_text_letter_space(&style_setting_screen_bike_night_l1_main_main_default, 0);
	lv_style_set_pad_left(&style_setting_screen_bike_night_l1_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_bike_night_l1_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_bike_night_l1_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_bike_night_l1_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_bike_night_L1, &style_setting_screen_bike_night_l1_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_bike_night_L2
	ui->Setting_Screen_bike_night_L2 = lv_label_create(ui->Setting_Screen_setting_bike_night_container);
	lv_obj_set_pos(ui->Setting_Screen_bike_night_L2, 0, 148);
	lv_obj_set_size(ui->Setting_Screen_bike_night_L2, 240, 26);
	lv_label_set_text(ui->Setting_Screen_bike_night_L2, "");
	lv_label_set_long_mode(ui->Setting_Screen_bike_night_L2, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->Setting_Screen_bike_night_L2, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_bike_night_l2_main_main_default
	static lv_style_t style_setting_screen_bike_night_l2_main_main_default;
	lv_style_reset(&style_setting_screen_bike_night_l2_main_main_default);
	lv_style_set_radius(&style_setting_screen_bike_night_l2_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_bike_night_l2_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_setting_screen_bike_night_l2_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_setting_screen_bike_night_l2_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_bike_night_l2_main_main_default, 0);
	lv_style_set_text_color(&style_setting_screen_bike_night_l2_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_setting_screen_bike_night_l2_main_main_default, &lv_font_FjallaOne_Regular_22);
	lv_style_set_text_letter_space(&style_setting_screen_bike_night_l2_main_main_default, 0);
	lv_style_set_pad_left(&style_setting_screen_bike_night_l2_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_bike_night_l2_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_bike_night_l2_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_bike_night_l2_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_bike_night_L2, &style_setting_screen_bike_night_l2_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_bike_night_L3
	ui->Setting_Screen_bike_night_L3 = lv_label_create(ui->Setting_Screen_setting_bike_night_container);
	lv_obj_set_pos(ui->Setting_Screen_bike_night_L3, 0, 196);
	lv_obj_set_size(ui->Setting_Screen_bike_night_L3, 240, 26);
	lv_label_set_text(ui->Setting_Screen_bike_night_L3, "");
	lv_label_set_long_mode(ui->Setting_Screen_bike_night_L3, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->Setting_Screen_bike_night_L3, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_bike_night_l3_main_main_default
	static lv_style_t style_setting_screen_bike_night_l3_main_main_default;
	lv_style_reset(&style_setting_screen_bike_night_l3_main_main_default);
	lv_style_set_radius(&style_setting_screen_bike_night_l3_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_bike_night_l3_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_setting_screen_bike_night_l3_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_setting_screen_bike_night_l3_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_bike_night_l3_main_main_default, 0);
	lv_style_set_text_color(&style_setting_screen_bike_night_l3_main_main_default, lv_color_make(0x50, 0x50, 0x50));
	lv_style_set_text_font(&style_setting_screen_bike_night_l3_main_main_default, &lv_font_FjallaOne_Regular_22);
	lv_style_set_text_letter_space(&style_setting_screen_bike_night_l3_main_main_default, 0);
	lv_style_set_pad_left(&style_setting_screen_bike_night_l3_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_bike_night_l3_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_bike_night_l3_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_bike_night_l3_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_bike_night_L3, &style_setting_screen_bike_night_l3_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_setting_bike_day_container
	ui->Setting_Screen_setting_bike_day_container = lv_obj_create(ui->Setting_Screen);
	lv_obj_set_pos(ui->Setting_Screen_setting_bike_day_container, 0, 0);
	lv_obj_set_size(ui->Setting_Screen_setting_bike_day_container, 240, 320);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_setting_bike_day_container_main_main_default
	static lv_style_t style_setting_screen_setting_bike_day_container_main_main_default;
	lv_style_reset(&style_setting_screen_setting_bike_day_container_main_main_default);
	lv_style_set_radius(&style_setting_screen_setting_bike_day_container_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_setting_bike_day_container_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_color(&style_setting_screen_setting_bike_day_container_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_dir(&style_setting_screen_setting_bike_day_container_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_setting_bike_day_container_main_main_default, 0);
	lv_style_set_border_color(&style_setting_screen_setting_bike_day_container_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_border_width(&style_setting_screen_setting_bike_day_container_main_main_default, 0);
	lv_style_set_border_opa(&style_setting_screen_setting_bike_day_container_main_main_default, 255);
	lv_style_set_pad_left(&style_setting_screen_setting_bike_day_container_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_setting_bike_day_container_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_setting_bike_day_container_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_setting_bike_day_container_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_setting_bike_day_container, &style_setting_screen_setting_bike_day_container_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_bike_day_circle_img
	ui->Setting_Screen_bike_day_circle_img = lv_img_create(ui->Setting_Screen_setting_bike_day_container);
	lv_obj_set_pos(ui->Setting_Screen_bike_day_circle_img, 7, 47);
	lv_obj_set_size(ui->Setting_Screen_bike_day_circle_img, 226, 226);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_bike_day_circle_img_main_main_default
	static lv_style_t style_setting_screen_bike_day_circle_img_main_main_default;
	lv_style_reset(&style_setting_screen_bike_day_circle_img_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_bike_day_circle_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_bike_day_circle_img_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_bike_day_circle_img_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_bike_day_circle_img, &style_setting_screen_bike_day_circle_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_bike_day_circle_img, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_bike_day_circle_img,&day_white_Grey_circle);
	lv_img_set_pivot(ui->Setting_Screen_bike_day_circle_img, 0,0);
	lv_img_set_angle(ui->Setting_Screen_bike_day_circle_img, 0);

	//Write codes Setting_Screen_bike_side_day_img
	ui->Setting_Screen_bike_side_day_img = lv_img_create(ui->Setting_Screen_setting_bike_day_container);
	lv_obj_set_pos(ui->Setting_Screen_bike_side_day_img, 16, 142);
	lv_obj_set_size(ui->Setting_Screen_bike_side_day_img, 40, 40);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_bike_side_day_img_main_main_default
	static lv_style_t style_setting_screen_bike_side_day_img_main_main_default;
	lv_style_reset(&style_setting_screen_bike_side_day_img_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_bike_side_day_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_bike_side_day_img_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_bike_side_day_img_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_bike_side_day_img, &style_setting_screen_bike_side_day_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_bike_sub_button_img
	ui->Setting_Screen_bike_sub_button_img = lv_img_create(ui->Setting_Screen_setting_bike_day_container);
	lv_obj_set_pos(ui->Setting_Screen_bike_sub_button_img, 196, 149);
	lv_obj_set_size(ui->Setting_Screen_bike_sub_button_img, 24, 24);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_bike_sub_button_img_main_main_default
	static lv_style_t style_setting_screen_bike_sub_button_img_main_main_default;
	lv_style_reset(&style_setting_screen_bike_sub_button_img_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_bike_sub_button_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_bike_sub_button_img_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_bike_sub_button_img_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_bike_sub_button_img, &style_setting_screen_bike_sub_button_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_bike_sub_button_img, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_bike_sub_button_img,&subbtn_day_24x24);
	lv_img_set_pivot(ui->Setting_Screen_bike_sub_button_img, 0,0);
	lv_img_set_angle(ui->Setting_Screen_bike_sub_button_img, 0);

	//Write codes Setting_Screen_bike_up_arr_day_img
	ui->Setting_Screen_bike_up_arr_day_img = lv_img_create(ui->Setting_Screen_setting_bike_day_container);
	lv_obj_set_pos(ui->Setting_Screen_bike_up_arr_day_img, 110, 65);
	lv_obj_set_size(ui->Setting_Screen_bike_up_arr_day_img, 20, 11);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_bike_up_arr_day_img_main_main_default
	static lv_style_t style_setting_screen_bike_up_arr_day_img_main_main_default;
	lv_style_reset(&style_setting_screen_bike_up_arr_day_img_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_bike_up_arr_day_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_bike_up_arr_day_img_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_bike_up_arr_day_img_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_bike_up_arr_day_img, &style_setting_screen_bike_up_arr_day_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_bike_up_arr_day_img, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_bike_up_arr_day_img,&_day_up_arrow_20x11);
	lv_img_set_pivot(ui->Setting_Screen_bike_up_arr_day_img, 0,0);
	lv_img_set_angle(ui->Setting_Screen_bike_up_arr_day_img, 0);

	//Write codes Setting_Screen_bike_down_arr_day_img
	ui->Setting_Screen_bike_down_arr_day_img = lv_img_create(ui->Setting_Screen_setting_bike_day_container);
	lv_obj_set_pos(ui->Setting_Screen_bike_down_arr_day_img, 110, 238);
	lv_obj_set_size(ui->Setting_Screen_bike_down_arr_day_img, 20, 11);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_bike_down_arr_day_img_main_main_default
	static lv_style_t style_setting_screen_bike_down_arr_day_img_main_main_default;
	lv_style_reset(&style_setting_screen_bike_down_arr_day_img_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_bike_down_arr_day_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_bike_down_arr_day_img_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_bike_down_arr_day_img_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_bike_down_arr_day_img, &style_setting_screen_bike_down_arr_day_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_bike_down_arr_day_img, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_bike_down_arr_day_img,&_day_down_arrow_20x11);
	lv_img_set_pivot(ui->Setting_Screen_bike_down_arr_day_img, 0,0);
	lv_img_set_angle(ui->Setting_Screen_bike_down_arr_day_img, 0);

	//Write codes Setting_Screen_bike_day_L1
	ui->Setting_Screen_bike_day_L1 = lv_label_create(ui->Setting_Screen_setting_bike_day_container);
	lv_obj_set_pos(ui->Setting_Screen_bike_day_L1, 0, 100);
	lv_obj_set_size(ui->Setting_Screen_bike_day_L1, 240, 26);
	lv_label_set_text(ui->Setting_Screen_bike_day_L1, "");
	lv_label_set_long_mode(ui->Setting_Screen_bike_day_L1, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->Setting_Screen_bike_day_L1, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_bike_day_l1_main_main_default
	static lv_style_t style_setting_screen_bike_day_l1_main_main_default;
	lv_style_reset(&style_setting_screen_bike_day_l1_main_main_default);
	lv_style_set_radius(&style_setting_screen_bike_day_l1_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_bike_day_l1_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_setting_screen_bike_day_l1_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_setting_screen_bike_day_l1_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_bike_day_l1_main_main_default, 0);
	lv_style_set_text_color(&style_setting_screen_bike_day_l1_main_main_default, lv_color_make(0xb8, 0xb8, 0xb8));
	lv_style_set_text_font(&style_setting_screen_bike_day_l1_main_main_default, &lv_font_FjallaOne_Regular_22);
	lv_style_set_text_letter_space(&style_setting_screen_bike_day_l1_main_main_default, 0);
	lv_style_set_pad_left(&style_setting_screen_bike_day_l1_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_bike_day_l1_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_bike_day_l1_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_bike_day_l1_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_bike_day_L1, &style_setting_screen_bike_day_l1_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_bike_day_L2
	ui->Setting_Screen_bike_day_L2 = lv_label_create(ui->Setting_Screen_setting_bike_day_container);
	lv_obj_set_pos(ui->Setting_Screen_bike_day_L2, 0, 148);
	lv_obj_set_size(ui->Setting_Screen_bike_day_L2, 240, 26);
	lv_label_set_text(ui->Setting_Screen_bike_day_L2, "");
	lv_label_set_long_mode(ui->Setting_Screen_bike_day_L2, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->Setting_Screen_bike_day_L2, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_bike_day_l2_main_main_default
	static lv_style_t style_setting_screen_bike_day_l2_main_main_default;
	lv_style_reset(&style_setting_screen_bike_day_l2_main_main_default);
	lv_style_set_radius(&style_setting_screen_bike_day_l2_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_bike_day_l2_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_setting_screen_bike_day_l2_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_setting_screen_bike_day_l2_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_bike_day_l2_main_main_default, 0);
	lv_style_set_text_color(&style_setting_screen_bike_day_l2_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_setting_screen_bike_day_l2_main_main_default, &lv_font_FjallaOne_Regular_22);
	lv_style_set_text_letter_space(&style_setting_screen_bike_day_l2_main_main_default, 0);
	lv_style_set_pad_left(&style_setting_screen_bike_day_l2_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_bike_day_l2_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_bike_day_l2_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_bike_day_l2_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_bike_day_L2, &style_setting_screen_bike_day_l2_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_bike_day_L3
	ui->Setting_Screen_bike_day_L3 = lv_label_create(ui->Setting_Screen_setting_bike_day_container);
	lv_obj_set_pos(ui->Setting_Screen_bike_day_L3, 0, 196);
	lv_obj_set_size(ui->Setting_Screen_bike_day_L3, 240, 26);
	lv_label_set_text(ui->Setting_Screen_bike_day_L3, "");
	lv_label_set_long_mode(ui->Setting_Screen_bike_day_L3, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->Setting_Screen_bike_day_L3, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_bike_day_l3_main_main_default
	static lv_style_t style_setting_screen_bike_day_l3_main_main_default;
	lv_style_reset(&style_setting_screen_bike_day_l3_main_main_default);
	lv_style_set_radius(&style_setting_screen_bike_day_l3_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_bike_day_l3_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_setting_screen_bike_day_l3_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_setting_screen_bike_day_l3_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_bike_day_l3_main_main_default, 0);
	lv_style_set_text_color(&style_setting_screen_bike_day_l3_main_main_default, lv_color_make(0xb8, 0xb8, 0xb8));
	lv_style_set_text_font(&style_setting_screen_bike_day_l3_main_main_default, &lv_font_FjallaOne_Regular_22);
	lv_style_set_text_letter_space(&style_setting_screen_bike_day_l3_main_main_default, 0);
	lv_style_set_pad_left(&style_setting_screen_bike_day_l3_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_bike_day_l3_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_bike_day_l3_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_bike_day_l3_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_bike_day_L3, &style_setting_screen_bike_day_l3_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_setting_about_night_container
	ui->Setting_Screen_setting_about_night_container = lv_obj_create(ui->Setting_Screen);
	lv_obj_set_pos(ui->Setting_Screen_setting_about_night_container, 0, 0);
	lv_obj_set_size(ui->Setting_Screen_setting_about_night_container, 240, 320);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_setting_about_night_container_main_main_default
	static lv_style_t style_setting_screen_setting_about_night_container_main_main_default;
	lv_style_reset(&style_setting_screen_setting_about_night_container_main_main_default);
	lv_style_set_radius(&style_setting_screen_setting_about_night_container_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_setting_about_night_container_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_color(&style_setting_screen_setting_about_night_container_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_dir(&style_setting_screen_setting_about_night_container_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_setting_about_night_container_main_main_default, 0);
	lv_style_set_border_color(&style_setting_screen_setting_about_night_container_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_border_width(&style_setting_screen_setting_about_night_container_main_main_default, 0);
	lv_style_set_border_opa(&style_setting_screen_setting_about_night_container_main_main_default, 255);
	lv_style_set_pad_left(&style_setting_screen_setting_about_night_container_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_setting_about_night_container_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_setting_about_night_container_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_setting_about_night_container_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_setting_about_night_container, &style_setting_screen_setting_about_night_container_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_about_side_night_img
	ui->Setting_Screen_about_side_night_img = lv_img_create(ui->Setting_Screen_setting_about_night_container);
	lv_obj_set_pos(ui->Setting_Screen_about_side_night_img, 16, 142);
	lv_obj_set_size(ui->Setting_Screen_about_side_night_img, 40, 40);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_about_side_night_img_main_main_default
	static lv_style_t style_setting_screen_about_side_night_img_main_main_default;
	lv_style_reset(&style_setting_screen_about_side_night_img_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_about_side_night_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_about_side_night_img_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_about_side_night_img_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_about_side_night_img, &style_setting_screen_about_side_night_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_about_sub_button_night_img
	ui->Setting_Screen_about_sub_button_night_img = lv_img_create(ui->Setting_Screen_setting_about_night_container);
	lv_obj_set_pos(ui->Setting_Screen_about_sub_button_night_img, 196, 149);
	lv_obj_set_size(ui->Setting_Screen_about_sub_button_night_img, 24, 24);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_about_sub_button_night_img_main_main_default
	static lv_style_t style_setting_screen_about_sub_button_night_img_main_main_default;
	lv_style_reset(&style_setting_screen_about_sub_button_night_img_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_about_sub_button_night_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_about_sub_button_night_img_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_about_sub_button_night_img_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_about_sub_button_night_img, &style_setting_screen_about_sub_button_night_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_about_sub_button_night_img, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_about_sub_button_night_img,&subbtn_night_24x24);
	lv_img_set_pivot(ui->Setting_Screen_about_sub_button_night_img, 0,0);
	lv_img_set_angle(ui->Setting_Screen_about_sub_button_night_img, 0);

	//Write codes Setting_Screen_about_up_arr_night_img
	ui->Setting_Screen_about_up_arr_night_img = lv_img_create(ui->Setting_Screen_setting_about_night_container);
	lv_obj_set_pos(ui->Setting_Screen_about_up_arr_night_img, 110, 65);
	lv_obj_set_size(ui->Setting_Screen_about_up_arr_night_img, 20, 11);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_about_up_arr_night_img_main_main_default
	static lv_style_t style_setting_screen_about_up_arr_night_img_main_main_default;
	lv_style_reset(&style_setting_screen_about_up_arr_night_img_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_about_up_arr_night_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_about_up_arr_night_img_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_about_up_arr_night_img_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_about_up_arr_night_img, &style_setting_screen_about_up_arr_night_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_about_up_arr_night_img, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_about_up_arr_night_img,&_Setting_Up_Arrow_20x11);
	lv_img_set_pivot(ui->Setting_Screen_about_up_arr_night_img, 0,0);
	lv_img_set_angle(ui->Setting_Screen_about_up_arr_night_img, 0);

	//Write codes Setting_Screen_about_down_arr_night_img
	ui->Setting_Screen_about_down_arr_night_img = lv_img_create(ui->Setting_Screen_setting_about_night_container);
	lv_obj_set_pos(ui->Setting_Screen_about_down_arr_night_img, 110, 238);
	lv_obj_set_size(ui->Setting_Screen_about_down_arr_night_img, 20, 11);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_about_down_arr_night_img_main_main_default
	static lv_style_t style_setting_screen_about_down_arr_night_img_main_main_default;
	lv_style_reset(&style_setting_screen_about_down_arr_night_img_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_about_down_arr_night_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_about_down_arr_night_img_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_about_down_arr_night_img_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_about_down_arr_night_img, &style_setting_screen_about_down_arr_night_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_about_down_arr_night_img, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_about_down_arr_night_img,&_Setting_Drow_Arrow_20x11);
	lv_img_set_pivot(ui->Setting_Screen_about_down_arr_night_img, 0,0);
	lv_img_set_angle(ui->Setting_Screen_about_down_arr_night_img, 0);

	//Write codes Setting_Screen_about_night_L1
	ui->Setting_Screen_about_night_L1 = lv_label_create(ui->Setting_Screen_setting_about_night_container);
	lv_obj_set_pos(ui->Setting_Screen_about_night_L1, 0, 100);
	lv_obj_set_size(ui->Setting_Screen_about_night_L1, 240, 18);
	lv_label_set_text(ui->Setting_Screen_about_night_L1, "");
	lv_label_set_long_mode(ui->Setting_Screen_about_night_L1, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->Setting_Screen_about_night_L1, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_about_night_l1_main_main_default
	static lv_style_t style_setting_screen_about_night_l1_main_main_default;
	lv_style_reset(&style_setting_screen_about_night_l1_main_main_default);
	lv_style_set_radius(&style_setting_screen_about_night_l1_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_about_night_l1_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_setting_screen_about_night_l1_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_setting_screen_about_night_l1_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_about_night_l1_main_main_default, 0);
	lv_style_set_text_color(&style_setting_screen_about_night_l1_main_main_default, lv_color_make(0x50, 0x50, 0x50));
	lv_style_set_text_font(&style_setting_screen_about_night_l1_main_main_default, &lv_font_FjallaOne_Regular_22);
	lv_style_set_text_letter_space(&style_setting_screen_about_night_l1_main_main_default, 0);
	lv_style_set_pad_left(&style_setting_screen_about_night_l1_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_about_night_l1_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_about_night_l1_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_about_night_l1_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_about_night_L1, &style_setting_screen_about_night_l1_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_about_night_L2
	ui->Setting_Screen_about_night_L2 = lv_label_create(ui->Setting_Screen_setting_about_night_container);
	lv_obj_set_pos(ui->Setting_Screen_about_night_L2, 0, 148);
	lv_obj_set_size(ui->Setting_Screen_about_night_L2, 240, 18);
	lv_label_set_text(ui->Setting_Screen_about_night_L2, "");
	lv_label_set_long_mode(ui->Setting_Screen_about_night_L2, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->Setting_Screen_about_night_L2, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_about_night_l2_main_main_default
	static lv_style_t style_setting_screen_about_night_l2_main_main_default;
	lv_style_reset(&style_setting_screen_about_night_l2_main_main_default);
	lv_style_set_radius(&style_setting_screen_about_night_l2_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_about_night_l2_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_setting_screen_about_night_l2_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_setting_screen_about_night_l2_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_about_night_l2_main_main_default, 0);
	lv_style_set_text_color(&style_setting_screen_about_night_l2_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_setting_screen_about_night_l2_main_main_default, &lv_font_FjallaOne_Regular_22);
	lv_style_set_text_letter_space(&style_setting_screen_about_night_l2_main_main_default, 0);
	lv_style_set_pad_left(&style_setting_screen_about_night_l2_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_about_night_l2_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_about_night_l2_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_about_night_l2_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_about_night_L2, &style_setting_screen_about_night_l2_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_about_night_L3
	ui->Setting_Screen_about_night_L3 = lv_label_create(ui->Setting_Screen_setting_about_night_container);
	lv_obj_set_pos(ui->Setting_Screen_about_night_L3, 0, 196);
	lv_obj_set_size(ui->Setting_Screen_about_night_L3, 240, 18);
	lv_label_set_text(ui->Setting_Screen_about_night_L3, "");
	lv_label_set_long_mode(ui->Setting_Screen_about_night_L3, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->Setting_Screen_about_night_L3, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_about_night_l3_main_main_default
	static lv_style_t style_setting_screen_about_night_l3_main_main_default;
	lv_style_reset(&style_setting_screen_about_night_l3_main_main_default);
	lv_style_set_radius(&style_setting_screen_about_night_l3_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_about_night_l3_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_setting_screen_about_night_l3_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_setting_screen_about_night_l3_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_about_night_l3_main_main_default, 0);
	lv_style_set_text_color(&style_setting_screen_about_night_l3_main_main_default, lv_color_make(0x50, 0x50, 0x50));
	lv_style_set_text_font(&style_setting_screen_about_night_l3_main_main_default, &lv_font_FjallaOne_Regular_22);
	lv_style_set_text_letter_space(&style_setting_screen_about_night_l3_main_main_default, 0);
	lv_style_set_pad_left(&style_setting_screen_about_night_l3_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_about_night_l3_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_about_night_l3_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_about_night_l3_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_about_night_L3, &style_setting_screen_about_night_l3_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_setting_about_day_container
	ui->Setting_Screen_setting_about_day_container = lv_obj_create(ui->Setting_Screen);
	lv_obj_set_pos(ui->Setting_Screen_setting_about_day_container, 0, 0);
	lv_obj_set_size(ui->Setting_Screen_setting_about_day_container, 240, 320);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_setting_about_day_container_main_main_default
	static lv_style_t style_setting_screen_setting_about_day_container_main_main_default;
	lv_style_reset(&style_setting_screen_setting_about_day_container_main_main_default);
	lv_style_set_radius(&style_setting_screen_setting_about_day_container_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_setting_about_day_container_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_color(&style_setting_screen_setting_about_day_container_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_dir(&style_setting_screen_setting_about_day_container_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_setting_about_day_container_main_main_default, 0);
	lv_style_set_border_color(&style_setting_screen_setting_about_day_container_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_border_width(&style_setting_screen_setting_about_day_container_main_main_default, 0);
	lv_style_set_border_opa(&style_setting_screen_setting_about_day_container_main_main_default, 255);
	lv_style_set_pad_left(&style_setting_screen_setting_about_day_container_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_setting_about_day_container_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_setting_about_day_container_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_setting_about_day_container_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_setting_about_day_container, &style_setting_screen_setting_about_day_container_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_about_day_circle_img
	ui->Setting_Screen_about_day_circle_img = lv_img_create(ui->Setting_Screen_setting_about_day_container);
	lv_obj_set_pos(ui->Setting_Screen_about_day_circle_img, 7, 47);
	lv_obj_set_size(ui->Setting_Screen_about_day_circle_img, 226, 226);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_about_day_circle_img_main_main_default
	static lv_style_t style_setting_screen_about_day_circle_img_main_main_default;
	lv_style_reset(&style_setting_screen_about_day_circle_img_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_about_day_circle_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_about_day_circle_img_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_about_day_circle_img_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_about_day_circle_img, &style_setting_screen_about_day_circle_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_about_day_circle_img, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_about_day_circle_img,&day_white_Grey_circle);
	lv_img_set_pivot(ui->Setting_Screen_about_day_circle_img, 0,0);
	lv_img_set_angle(ui->Setting_Screen_about_day_circle_img, 0);

	//Write codes Setting_Screen_about_side_day_img
	ui->Setting_Screen_about_side_day_img = lv_img_create(ui->Setting_Screen_setting_about_day_container);
	lv_obj_set_pos(ui->Setting_Screen_about_side_day_img, 16, 142);
	lv_obj_set_size(ui->Setting_Screen_about_side_day_img, 40, 40);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_about_side_day_img_main_main_default
	static lv_style_t style_setting_screen_about_side_day_img_main_main_default;
	lv_style_reset(&style_setting_screen_about_side_day_img_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_about_side_day_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_about_side_day_img_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_about_side_day_img_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_about_side_day_img, &style_setting_screen_about_side_day_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_about_sub_button_day_img
	ui->Setting_Screen_about_sub_button_day_img = lv_img_create(ui->Setting_Screen_setting_about_day_container);
	lv_obj_set_pos(ui->Setting_Screen_about_sub_button_day_img, 196, 149);
	lv_obj_set_size(ui->Setting_Screen_about_sub_button_day_img, 24, 24);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_about_sub_button_day_img_main_main_default
	static lv_style_t style_setting_screen_about_sub_button_day_img_main_main_default;
	lv_style_reset(&style_setting_screen_about_sub_button_day_img_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_about_sub_button_day_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_about_sub_button_day_img_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_about_sub_button_day_img_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_about_sub_button_day_img, &style_setting_screen_about_sub_button_day_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_about_sub_button_day_img, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_about_sub_button_day_img,&subbtn_day_24x24);
	lv_img_set_pivot(ui->Setting_Screen_about_sub_button_day_img, 0,0);
	lv_img_set_angle(ui->Setting_Screen_about_sub_button_day_img, 0);

	//Write codes Setting_Screen_about_up_arr_day_img
	ui->Setting_Screen_about_up_arr_day_img = lv_img_create(ui->Setting_Screen_setting_about_day_container);
	lv_obj_set_pos(ui->Setting_Screen_about_up_arr_day_img, 110, 65);
	lv_obj_set_size(ui->Setting_Screen_about_up_arr_day_img, 20, 11);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_about_up_arr_day_img_main_main_default
	static lv_style_t style_setting_screen_about_up_arr_day_img_main_main_default;
	lv_style_reset(&style_setting_screen_about_up_arr_day_img_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_about_up_arr_day_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_about_up_arr_day_img_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_about_up_arr_day_img_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_about_up_arr_day_img, &style_setting_screen_about_up_arr_day_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_about_up_arr_day_img, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_about_up_arr_day_img,&_day_up_arrow_20x11);
	lv_img_set_pivot(ui->Setting_Screen_about_up_arr_day_img, 0,0);
	lv_img_set_angle(ui->Setting_Screen_about_up_arr_day_img, 0);

	//Write codes Setting_Screen_about_down_arr_day_img
	ui->Setting_Screen_about_down_arr_day_img = lv_img_create(ui->Setting_Screen_setting_about_day_container);
	lv_obj_set_pos(ui->Setting_Screen_about_down_arr_day_img, 110, 238);
	lv_obj_set_size(ui->Setting_Screen_about_down_arr_day_img, 20, 11);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_about_down_arr_day_img_main_main_default
	static lv_style_t style_setting_screen_about_down_arr_day_img_main_main_default;
	lv_style_reset(&style_setting_screen_about_down_arr_day_img_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_about_down_arr_day_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_about_down_arr_day_img_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_about_down_arr_day_img_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_about_down_arr_day_img, &style_setting_screen_about_down_arr_day_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_about_down_arr_day_img, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_about_down_arr_day_img,&_day_down_arrow_20x11);
	lv_img_set_pivot(ui->Setting_Screen_about_down_arr_day_img, 0,0);
	lv_img_set_angle(ui->Setting_Screen_about_down_arr_day_img, 0);

	//Write codes Setting_Screen_about_day_L1
	ui->Setting_Screen_about_day_L1 = lv_label_create(ui->Setting_Screen_setting_about_day_container);
	lv_obj_set_pos(ui->Setting_Screen_about_day_L1, 0, 100);
	lv_obj_set_size(ui->Setting_Screen_about_day_L1, 240, 18);
	lv_label_set_text(ui->Setting_Screen_about_day_L1, "");
	lv_label_set_long_mode(ui->Setting_Screen_about_day_L1, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->Setting_Screen_about_day_L1, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_about_day_l1_main_main_default
	static lv_style_t style_setting_screen_about_day_l1_main_main_default;
	lv_style_reset(&style_setting_screen_about_day_l1_main_main_default);
	lv_style_set_radius(&style_setting_screen_about_day_l1_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_about_day_l1_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_setting_screen_about_day_l1_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_setting_screen_about_day_l1_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_about_day_l1_main_main_default, 0);
	lv_style_set_text_color(&style_setting_screen_about_day_l1_main_main_default, lv_color_make(0xb8, 0xb8, 0xb8));
	lv_style_set_text_font(&style_setting_screen_about_day_l1_main_main_default, &lv_font_FjallaOne_Regular_22);
	lv_style_set_text_letter_space(&style_setting_screen_about_day_l1_main_main_default, 0);
	lv_style_set_pad_left(&style_setting_screen_about_day_l1_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_about_day_l1_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_about_day_l1_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_about_day_l1_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_about_day_L1, &style_setting_screen_about_day_l1_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_about_day_L2
	ui->Setting_Screen_about_day_L2 = lv_label_create(ui->Setting_Screen_setting_about_day_container);
	lv_obj_set_pos(ui->Setting_Screen_about_day_L2, 0, 148);
	lv_obj_set_size(ui->Setting_Screen_about_day_L2, 240, 18);
	lv_label_set_text(ui->Setting_Screen_about_day_L2, "");
	lv_label_set_long_mode(ui->Setting_Screen_about_day_L2, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->Setting_Screen_about_day_L2, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_about_day_l2_main_main_default
	static lv_style_t style_setting_screen_about_day_l2_main_main_default;
	lv_style_reset(&style_setting_screen_about_day_l2_main_main_default);
	lv_style_set_radius(&style_setting_screen_about_day_l2_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_about_day_l2_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_setting_screen_about_day_l2_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_setting_screen_about_day_l2_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_about_day_l2_main_main_default, 0);
	lv_style_set_text_color(&style_setting_screen_about_day_l2_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_setting_screen_about_day_l2_main_main_default, &lv_font_FjallaOne_Regular_22);
	lv_style_set_text_letter_space(&style_setting_screen_about_day_l2_main_main_default, 0);
	lv_style_set_pad_left(&style_setting_screen_about_day_l2_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_about_day_l2_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_about_day_l2_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_about_day_l2_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_about_day_L2, &style_setting_screen_about_day_l2_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_about_day_L3
	ui->Setting_Screen_about_day_L3 = lv_label_create(ui->Setting_Screen_setting_about_day_container);
	lv_obj_set_pos(ui->Setting_Screen_about_day_L3, 0, 196);
	lv_obj_set_size(ui->Setting_Screen_about_day_L3, 240, 18);
	lv_label_set_text(ui->Setting_Screen_about_day_L3, "");
	lv_label_set_long_mode(ui->Setting_Screen_about_day_L3, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->Setting_Screen_about_day_L3, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_about_day_l3_main_main_default
	static lv_style_t style_setting_screen_about_day_l3_main_main_default;
	lv_style_reset(&style_setting_screen_about_day_l3_main_main_default);
	lv_style_set_radius(&style_setting_screen_about_day_l3_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_about_day_l3_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_setting_screen_about_day_l3_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_setting_screen_about_day_l3_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_about_day_l3_main_main_default, 0);
	lv_style_set_text_color(&style_setting_screen_about_day_l3_main_main_default, lv_color_make(0xb8, 0xb8, 0xb8));
	lv_style_set_text_font(&style_setting_screen_about_day_l3_main_main_default, &lv_font_FjallaOne_Regular_22);
	lv_style_set_text_letter_space(&style_setting_screen_about_day_l3_main_main_default, 0);
	lv_style_set_pad_left(&style_setting_screen_about_day_l3_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_about_day_l3_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_about_day_l3_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_about_day_l3_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_about_day_L3, &style_setting_screen_about_day_l3_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);


	//Write codes Setting_Screen_setting_display_night_container
	ui->Setting_Screen_setting_display_night_container = lv_obj_create(ui->Setting_Screen);
	lv_obj_set_pos(ui->Setting_Screen_setting_display_night_container, 0, 0);
	lv_obj_set_size(ui->Setting_Screen_setting_display_night_container, 240, 320);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_setting_display_night_container_main_main_default
	static lv_style_t style_setting_screen_setting_display_night_container_main_main_default;
	lv_style_reset(&style_setting_screen_setting_display_night_container_main_main_default);
	lv_style_set_radius(&style_setting_screen_setting_display_night_container_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_setting_display_night_container_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_color(&style_setting_screen_setting_display_night_container_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_dir(&style_setting_screen_setting_display_night_container_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_setting_display_night_container_main_main_default, 0);
	lv_style_set_border_color(&style_setting_screen_setting_display_night_container_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_border_width(&style_setting_screen_setting_display_night_container_main_main_default, 0);
	lv_style_set_border_opa(&style_setting_screen_setting_display_night_container_main_main_default, 255);
	lv_style_set_pad_left(&style_setting_screen_setting_display_night_container_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_setting_display_night_container_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_setting_display_night_container_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_setting_display_night_container_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_setting_display_night_container, &style_setting_screen_setting_display_night_container_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_display_side_night_img
	ui->Setting_Screen_display_side_night_img = lv_img_create(ui->Setting_Screen_setting_display_night_container);
	lv_obj_set_pos(ui->Setting_Screen_display_side_night_img, 16, 142);
	lv_obj_set_size(ui->Setting_Screen_display_side_night_img, 40, 40);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_display_side_night_img_main_main_default
	static lv_style_t style_setting_screen_display_side_night_img_main_main_default;
	lv_style_reset(&style_setting_screen_display_side_night_img_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_display_side_night_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_display_side_night_img_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_display_side_night_img_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_display_side_night_img, &style_setting_screen_display_side_night_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_display_sub_button_night_img
	ui->Setting_Screen_display_sub_button_night_img = lv_img_create(ui->Setting_Screen_setting_display_night_container);
	lv_obj_set_pos(ui->Setting_Screen_display_sub_button_night_img, 196, 149);
	lv_obj_set_size(ui->Setting_Screen_display_sub_button_night_img, 24, 24);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_display_sub_button_night_img_main_main_default
	static lv_style_t style_setting_screen_display_sub_button_night_img_main_main_default;
	lv_style_reset(&style_setting_screen_display_sub_button_night_img_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_display_sub_button_night_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_display_sub_button_night_img_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_display_sub_button_night_img_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_display_sub_button_night_img, &style_setting_screen_display_sub_button_night_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_display_sub_button_night_img, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_display_sub_button_night_img,&subbtn_night_24x24);
	lv_img_set_pivot(ui->Setting_Screen_display_sub_button_night_img, 0,0);
	lv_img_set_angle(ui->Setting_Screen_display_sub_button_night_img, 0);

	//Write codes Setting_Screen_display_up_arr_night_img
	ui->Setting_Screen_display_up_arr_night_img = lv_img_create(ui->Setting_Screen_setting_display_night_container);
	lv_obj_set_pos(ui->Setting_Screen_display_up_arr_night_img, 110, 65);
	lv_obj_set_size(ui->Setting_Screen_display_up_arr_night_img, 20, 11);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_display_up_arr_night_img_main_main_default
	static lv_style_t style_setting_screen_display_up_arr_night_img_main_main_default;
	lv_style_reset(&style_setting_screen_display_up_arr_night_img_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_display_up_arr_night_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_display_up_arr_night_img_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_display_up_arr_night_img_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_display_up_arr_night_img, &style_setting_screen_display_up_arr_night_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_display_up_arr_night_img, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_display_up_arr_night_img,&_Setting_Up_Arrow_20x11);
	lv_img_set_pivot(ui->Setting_Screen_display_up_arr_night_img, 0,0);
	lv_img_set_angle(ui->Setting_Screen_display_up_arr_night_img, 0);

	//Write codes Setting_Screen_display_down_arr_night_img
	ui->Setting_Screen_display_down_arr_night_img = lv_img_create(ui->Setting_Screen_setting_display_night_container);
	lv_obj_set_pos(ui->Setting_Screen_display_down_arr_night_img, 110, 238);
	lv_obj_set_size(ui->Setting_Screen_display_down_arr_night_img, 20, 11);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_display_down_arr_night_img_main_main_default
	static lv_style_t style_setting_screen_display_down_arr_night_img_main_main_default;
	lv_style_reset(&style_setting_screen_display_down_arr_night_img_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_display_down_arr_night_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_display_down_arr_night_img_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_display_down_arr_night_img_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_display_down_arr_night_img, &style_setting_screen_display_down_arr_night_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_display_down_arr_night_img, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_display_down_arr_night_img,&_Setting_Drow_Arrow_20x11);
	lv_img_set_pivot(ui->Setting_Screen_display_down_arr_night_img, 0,0);
	lv_img_set_angle(ui->Setting_Screen_display_down_arr_night_img, 0);

	//Write codes Setting_Screen_display_night_L1
	ui->Setting_Screen_display_night_L1 = lv_label_create(ui->Setting_Screen_setting_display_night_container);
	lv_obj_set_pos(ui->Setting_Screen_display_night_L1, 0, 100);
	lv_obj_set_size(ui->Setting_Screen_display_night_L1, 240, 18);
	lv_label_set_text(ui->Setting_Screen_display_night_L1, "");
	lv_label_set_long_mode(ui->Setting_Screen_display_night_L1, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->Setting_Screen_display_night_L1, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_display_night_l1_main_main_default
	static lv_style_t style_setting_screen_display_night_l1_main_main_default;
	lv_style_reset(&style_setting_screen_display_night_l1_main_main_default);
	lv_style_set_radius(&style_setting_screen_display_night_l1_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_display_night_l1_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_setting_screen_display_night_l1_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_setting_screen_display_night_l1_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_display_night_l1_main_main_default, 0);
	lv_style_set_text_color(&style_setting_screen_display_night_l1_main_main_default, lv_color_make(0x50, 0x50, 0x50));
	lv_style_set_text_font(&style_setting_screen_display_night_l1_main_main_default, &lv_font_FjallaOne_Regular_22);
	lv_style_set_text_letter_space(&style_setting_screen_display_night_l1_main_main_default, 0);
	lv_style_set_pad_left(&style_setting_screen_display_night_l1_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_display_night_l1_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_display_night_l1_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_display_night_l1_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_display_night_L1, &style_setting_screen_display_night_l1_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_display_night_L2
	ui->Setting_Screen_display_night_L2 = lv_label_create(ui->Setting_Screen_setting_display_night_container);
	lv_obj_set_pos(ui->Setting_Screen_display_night_L2, 0, 148);
	lv_obj_set_size(ui->Setting_Screen_display_night_L2, 240, 18);
	lv_label_set_text(ui->Setting_Screen_display_night_L2, "");
	lv_label_set_long_mode(ui->Setting_Screen_display_night_L2, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->Setting_Screen_display_night_L2, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_display_night_l2_main_main_default
	static lv_style_t style_setting_screen_display_night_l2_main_main_default;
	lv_style_reset(&style_setting_screen_display_night_l2_main_main_default);
	lv_style_set_radius(&style_setting_screen_display_night_l2_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_display_night_l2_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_setting_screen_display_night_l2_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_setting_screen_display_night_l2_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_display_night_l2_main_main_default, 0);
	lv_style_set_text_color(&style_setting_screen_display_night_l2_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_setting_screen_display_night_l2_main_main_default, &lv_font_FjallaOne_Regular_22);
	lv_style_set_text_letter_space(&style_setting_screen_display_night_l2_main_main_default, 0);
	lv_style_set_pad_left(&style_setting_screen_display_night_l2_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_display_night_l2_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_display_night_l2_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_display_night_l2_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_display_night_L2, &style_setting_screen_display_night_l2_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_display_night_L3
	ui->Setting_Screen_display_night_L3 = lv_label_create(ui->Setting_Screen_setting_display_night_container);
	lv_obj_set_pos(ui->Setting_Screen_display_night_L3, 0, 196);
	lv_obj_set_size(ui->Setting_Screen_display_night_L3, 240, 18);
	lv_label_set_text(ui->Setting_Screen_display_night_L3, "");
	lv_label_set_long_mode(ui->Setting_Screen_display_night_L3, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->Setting_Screen_display_night_L3, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_display_night_l3_main_main_default
	static lv_style_t style_setting_screen_display_night_l3_main_main_default;
	lv_style_reset(&style_setting_screen_display_night_l3_main_main_default);
	lv_style_set_radius(&style_setting_screen_display_night_l3_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_display_night_l3_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_setting_screen_display_night_l3_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_setting_screen_display_night_l3_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_display_night_l3_main_main_default, 0);
	lv_style_set_text_color(&style_setting_screen_display_night_l3_main_main_default, lv_color_make(0x50, 0x50, 0x50));
	lv_style_set_text_font(&style_setting_screen_display_night_l3_main_main_default, &lv_font_FjallaOne_Regular_22);
	lv_style_set_text_letter_space(&style_setting_screen_display_night_l3_main_main_default, 0);
	lv_style_set_pad_left(&style_setting_screen_display_night_l3_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_display_night_l3_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_display_night_l3_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_display_night_l3_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_display_night_L3, &style_setting_screen_display_night_l3_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_setting_display_day_container
	ui->Setting_Screen_setting_display_day_container = lv_obj_create(ui->Setting_Screen);
	lv_obj_set_pos(ui->Setting_Screen_setting_display_day_container, 0, 0);
	lv_obj_set_size(ui->Setting_Screen_setting_display_day_container, 240, 320);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_setting_display_day_container_main_main_default
	static lv_style_t style_setting_screen_setting_display_day_container_main_main_default;
	lv_style_reset(&style_setting_screen_setting_display_day_container_main_main_default);
	lv_style_set_radius(&style_setting_screen_setting_display_day_container_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_setting_display_day_container_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_color(&style_setting_screen_setting_display_day_container_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_dir(&style_setting_screen_setting_display_day_container_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_setting_display_day_container_main_main_default, 0);
	lv_style_set_border_color(&style_setting_screen_setting_display_day_container_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_border_width(&style_setting_screen_setting_display_day_container_main_main_default, 0);
	lv_style_set_border_opa(&style_setting_screen_setting_display_day_container_main_main_default, 255);
	lv_style_set_pad_left(&style_setting_screen_setting_display_day_container_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_setting_display_day_container_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_setting_display_day_container_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_setting_display_day_container_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_setting_display_day_container, &style_setting_screen_setting_display_day_container_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_display_day_circle_img
	ui->Setting_Screen_display_day_circle_img = lv_img_create(ui->Setting_Screen_setting_display_day_container);
	lv_obj_set_pos(ui->Setting_Screen_display_day_circle_img, 7, 47);
	lv_obj_set_size(ui->Setting_Screen_display_day_circle_img, 226, 226);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_display_day_circle_img_main_main_default
	static lv_style_t style_setting_screen_display_day_circle_img_main_main_default;
	lv_style_reset(&style_setting_screen_display_day_circle_img_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_display_day_circle_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_display_day_circle_img_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_display_day_circle_img_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_display_day_circle_img, &style_setting_screen_display_day_circle_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_display_day_circle_img, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_display_day_circle_img,&day_white_Grey_circle);
	lv_img_set_pivot(ui->Setting_Screen_display_day_circle_img, 0,0);
	lv_img_set_angle(ui->Setting_Screen_display_day_circle_img, 0);

	//Write codes Setting_Screen_display_side_day_img
	ui->Setting_Screen_display_side_day_img = lv_img_create(ui->Setting_Screen_setting_display_day_container);
	lv_obj_set_pos(ui->Setting_Screen_display_side_day_img, 16, 142);
	lv_obj_set_size(ui->Setting_Screen_display_side_day_img, 40, 40);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_display_side_day_img_main_main_default
	static lv_style_t style_setting_screen_display_side_day_img_main_main_default;
	lv_style_reset(&style_setting_screen_display_side_day_img_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_display_side_day_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_display_side_day_img_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_display_side_day_img_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_display_side_day_img, &style_setting_screen_display_side_day_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_display_sub_button_day_img
	ui->Setting_Screen_display_sub_button_day_img = lv_img_create(ui->Setting_Screen_setting_display_day_container);
	lv_obj_set_pos(ui->Setting_Screen_display_sub_button_day_img, 196, 149);
	lv_obj_set_size(ui->Setting_Screen_display_sub_button_day_img, 24, 24);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_display_sub_button_day_img_main_main_default
	static lv_style_t style_setting_screen_display_sub_button_day_img_main_main_default;
	lv_style_reset(&style_setting_screen_display_sub_button_day_img_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_display_sub_button_day_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_display_sub_button_day_img_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_display_sub_button_day_img_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_display_sub_button_day_img, &style_setting_screen_display_sub_button_day_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_display_sub_button_day_img, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_display_sub_button_day_img,&subbtn_day_24x24);
	lv_img_set_pivot(ui->Setting_Screen_display_sub_button_day_img, 0,0);
	lv_img_set_angle(ui->Setting_Screen_display_sub_button_day_img, 0);

	//Write codes Setting_Screen_display_up_arr_day_img
	ui->Setting_Screen_display_up_arr_day_img = lv_img_create(ui->Setting_Screen_setting_display_day_container);
	lv_obj_set_pos(ui->Setting_Screen_display_up_arr_day_img, 110, 65);
	lv_obj_set_size(ui->Setting_Screen_display_up_arr_day_img, 20, 11);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_display_up_arr_day_img_main_main_default
	static lv_style_t style_setting_screen_display_up_arr_day_img_main_main_default;
	lv_style_reset(&style_setting_screen_display_up_arr_day_img_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_display_up_arr_day_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_display_up_arr_day_img_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_display_up_arr_day_img_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_display_up_arr_day_img, &style_setting_screen_display_up_arr_day_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_display_up_arr_day_img, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_display_up_arr_day_img,&_day_up_arrow_20x11);
	lv_img_set_pivot(ui->Setting_Screen_display_up_arr_day_img, 0,0);
	lv_img_set_angle(ui->Setting_Screen_display_up_arr_day_img, 0);

	//Write codes Setting_Screen_display_down_arr_day_img
	ui->Setting_Screen_display_down_arr_day_img = lv_img_create(ui->Setting_Screen_setting_display_day_container);
	lv_obj_set_pos(ui->Setting_Screen_display_down_arr_day_img, 110, 238);
	lv_obj_set_size(ui->Setting_Screen_display_down_arr_day_img, 20, 11);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_display_down_arr_day_img_main_main_default
	static lv_style_t style_setting_screen_display_down_arr_day_img_main_main_default;
	lv_style_reset(&style_setting_screen_display_down_arr_day_img_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_display_down_arr_day_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_display_down_arr_day_img_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_display_down_arr_day_img_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_display_down_arr_day_img, &style_setting_screen_display_down_arr_day_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_display_down_arr_day_img, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_display_down_arr_day_img,&_day_down_arrow_20x11);
	lv_img_set_pivot(ui->Setting_Screen_display_down_arr_day_img, 0,0);
	lv_img_set_angle(ui->Setting_Screen_display_down_arr_day_img, 0);

	//Write codes Setting_Screen_display_day_L1
	ui->Setting_Screen_display_day_L1 = lv_label_create(ui->Setting_Screen_setting_display_day_container);
	lv_obj_set_pos(ui->Setting_Screen_display_day_L1, 0, 100);
	lv_obj_set_size(ui->Setting_Screen_display_day_L1, 240, 18);
	lv_label_set_text(ui->Setting_Screen_display_day_L1, "");
	lv_label_set_long_mode(ui->Setting_Screen_display_day_L1, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->Setting_Screen_display_day_L1, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_display_day_l1_main_main_default
	static lv_style_t style_setting_screen_display_day_l1_main_main_default;
	lv_style_reset(&style_setting_screen_display_day_l1_main_main_default);
	lv_style_set_radius(&style_setting_screen_display_day_l1_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_display_day_l1_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_setting_screen_display_day_l1_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_setting_screen_display_day_l1_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_display_day_l1_main_main_default, 0);
	lv_style_set_text_color(&style_setting_screen_display_day_l1_main_main_default, lv_color_make(0xb8, 0xb8, 0xb8));
	lv_style_set_text_font(&style_setting_screen_display_day_l1_main_main_default, &lv_font_FjallaOne_Regular_22);
	lv_style_set_text_letter_space(&style_setting_screen_display_day_l1_main_main_default, 0);
	lv_style_set_pad_left(&style_setting_screen_display_day_l1_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_display_day_l1_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_display_day_l1_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_display_day_l1_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_display_day_L1, &style_setting_screen_display_day_l1_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_display_day_L2
	ui->Setting_Screen_display_day_L2 = lv_label_create(ui->Setting_Screen_setting_display_day_container);
	lv_obj_set_pos(ui->Setting_Screen_display_day_L2, 0, 148);
	lv_obj_set_size(ui->Setting_Screen_display_day_L2, 240, 18);
	lv_label_set_text(ui->Setting_Screen_display_day_L2, "");
	lv_label_set_long_mode(ui->Setting_Screen_display_day_L2, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->Setting_Screen_display_day_L2, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_display_day_l2_main_main_default
	static lv_style_t style_setting_screen_display_day_l2_main_main_default;
	lv_style_reset(&style_setting_screen_display_day_l2_main_main_default);
	lv_style_set_radius(&style_setting_screen_display_day_l2_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_display_day_l2_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_setting_screen_display_day_l2_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_setting_screen_display_day_l2_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_display_day_l2_main_main_default, 0);
	lv_style_set_text_color(&style_setting_screen_display_day_l2_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_setting_screen_display_day_l2_main_main_default, &lv_font_FjallaOne_Regular_22);
	lv_style_set_text_letter_space(&style_setting_screen_display_day_l2_main_main_default, 0);
	lv_style_set_pad_left(&style_setting_screen_display_day_l2_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_display_day_l2_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_display_day_l2_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_display_day_l2_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_display_day_L2, &style_setting_screen_display_day_l2_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_display_day_L3
	ui->Setting_Screen_display_day_L3 = lv_label_create(ui->Setting_Screen_setting_display_day_container);
	lv_obj_set_pos(ui->Setting_Screen_display_day_L3, 0, 196);
	lv_obj_set_size(ui->Setting_Screen_display_day_L3, 240, 18);
	lv_label_set_text(ui->Setting_Screen_display_day_L3, "");
	lv_label_set_long_mode(ui->Setting_Screen_display_day_L3, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->Setting_Screen_display_day_L3, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_display_day_l3_main_main_default
	static lv_style_t style_setting_screen_display_day_l3_main_main_default;
	lv_style_reset(&style_setting_screen_display_day_l3_main_main_default);
	lv_style_set_radius(&style_setting_screen_display_day_l3_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_display_day_l3_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_setting_screen_display_day_l3_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_setting_screen_display_day_l3_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_display_day_l3_main_main_default, 0);
	lv_style_set_text_color(&style_setting_screen_display_day_l3_main_main_default, lv_color_make(0xb8, 0xb8, 0xb8));
	lv_style_set_text_font(&style_setting_screen_display_day_l3_main_main_default, &lv_font_FjallaOne_Regular_22);
	lv_style_set_text_letter_space(&style_setting_screen_display_day_l3_main_main_default, 0);
	lv_style_set_pad_left(&style_setting_screen_display_day_l3_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_display_day_l3_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_display_day_l3_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_display_day_l3_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_display_day_L3, &style_setting_screen_display_day_l3_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);


	//Write codes Setting_Screen_setting_connect_night_container
	ui->Setting_Screen_setting_connect_night_container = lv_obj_create(ui->Setting_Screen);
	lv_obj_set_pos(ui->Setting_Screen_setting_connect_night_container, 0, 0);
	lv_obj_set_size(ui->Setting_Screen_setting_connect_night_container, 240, 320);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_setting_connect_night_container_main_main_default
	static lv_style_t style_setting_screen_setting_connect_night_container_main_main_default;
	lv_style_reset(&style_setting_screen_setting_connect_night_container_main_main_default);
	lv_style_set_radius(&style_setting_screen_setting_connect_night_container_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_setting_connect_night_container_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_color(&style_setting_screen_setting_connect_night_container_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_dir(&style_setting_screen_setting_connect_night_container_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_setting_connect_night_container_main_main_default, 0);
	lv_style_set_border_color(&style_setting_screen_setting_connect_night_container_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_border_width(&style_setting_screen_setting_connect_night_container_main_main_default, 0);
	lv_style_set_border_opa(&style_setting_screen_setting_connect_night_container_main_main_default, 255);
	lv_style_set_pad_left(&style_setting_screen_setting_connect_night_container_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_setting_connect_night_container_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_setting_connect_night_container_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_setting_connect_night_container_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_setting_connect_night_container, &style_setting_screen_setting_connect_night_container_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_connnect_side_night_img
	ui->Setting_Screen_connnect_side_night_img = lv_img_create(ui->Setting_Screen_setting_connect_night_container);
	lv_obj_set_pos(ui->Setting_Screen_connnect_side_night_img, 16, 142);
	lv_obj_set_size(ui->Setting_Screen_connnect_side_night_img, 40, 40);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_connnect_side_night_img_main_main_default
	static lv_style_t style_setting_screen_connnect_side_night_img_main_main_default;
	lv_style_reset(&style_setting_screen_connnect_side_night_img_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_connnect_side_night_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_connnect_side_night_img_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_connnect_side_night_img_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_connnect_side_night_img, &style_setting_screen_connnect_side_night_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_connect_sub_button_night_img
	ui->Setting_Screen_connect_sub_button_night_img = lv_img_create(ui->Setting_Screen_setting_connect_night_container);
	lv_obj_set_pos(ui->Setting_Screen_connect_sub_button_night_img, 196, 149);
	lv_obj_set_size(ui->Setting_Screen_connect_sub_button_night_img, 24, 24);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_connect_sub_button_night_img_main_main_default
	static lv_style_t style_setting_screen_connect_sub_button_night_img_main_main_default;
	lv_style_reset(&style_setting_screen_connect_sub_button_night_img_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_connect_sub_button_night_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_connect_sub_button_night_img_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_connect_sub_button_night_img_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_connect_sub_button_night_img, &style_setting_screen_connect_sub_button_night_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_connect_sub_button_night_img, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_connect_sub_button_night_img,&subbtn_night_24x24);
	lv_img_set_pivot(ui->Setting_Screen_connect_sub_button_night_img, 0,0);
	lv_img_set_angle(ui->Setting_Screen_connect_sub_button_night_img, 0);

	//Write codes Setting_Screen_connect_switch_btn_night_img
	ui->Setting_Screen_connect_switch_btn_night_img = lv_img_create(ui->Setting_Screen_setting_connect_night_container);
	lv_obj_set_pos(ui->Setting_Screen_connect_switch_btn_night_img, 179, 147);
	lv_obj_set_size(ui->Setting_Screen_connect_switch_btn_night_img, 29, 20);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_connect_switch_btn_night_img_main_main_default
	static lv_style_t style_setting_screen_connect_switch_btn_night_img_main_main_default;
	lv_style_reset(&style_setting_screen_connect_switch_btn_night_img_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_connect_switch_btn_night_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_connect_switch_btn_night_img_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_connect_switch_btn_night_img_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_connect_switch_btn_night_img, &style_setting_screen_connect_switch_btn_night_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_connect_switch_btn_night_img, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_connect_switch_btn_night_img,&_btn_1_29x20);
	lv_img_set_pivot(ui->Setting_Screen_connect_switch_btn_night_img, 0,0);
	lv_img_set_angle(ui->Setting_Screen_connect_switch_btn_night_img, 0);

	//Write codes Setting_Screen_connect_up_arr_night_img
	ui->Setting_Screen_connect_up_arr_night_img = lv_img_create(ui->Setting_Screen_setting_connect_night_container);
	lv_obj_set_pos(ui->Setting_Screen_connect_up_arr_night_img, 110, 105);
	lv_obj_set_size(ui->Setting_Screen_connect_up_arr_night_img, 20, 11);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_connect_up_arr_night_img_main_main_default
	static lv_style_t style_setting_screen_connect_up_arr_night_img_main_main_default;
	lv_style_reset(&style_setting_screen_connect_up_arr_night_img_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_connect_up_arr_night_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_connect_up_arr_night_img_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_connect_up_arr_night_img_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_connect_up_arr_night_img, &style_setting_screen_connect_up_arr_night_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_connect_up_arr_night_img, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_connect_up_arr_night_img,&_Setting_Up_Arrow_20x11);
	lv_img_set_pivot(ui->Setting_Screen_connect_up_arr_night_img, 0,0);
	lv_img_set_angle(ui->Setting_Screen_connect_up_arr_night_img, 0);

	//Write codes Setting_Screen_connect_down_arr_night_img
	ui->Setting_Screen_connect_down_arr_night_img = lv_img_create(ui->Setting_Screen_setting_connect_night_container);
	lv_obj_set_pos(ui->Setting_Screen_connect_down_arr_night_img, 110, 198);
	lv_obj_set_size(ui->Setting_Screen_connect_down_arr_night_img, 20, 11);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_connect_down_arr_night_img_main_main_default
	static lv_style_t style_setting_screen_connect_down_arr_night_img_main_main_default;
	lv_style_reset(&style_setting_screen_connect_down_arr_night_img_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_connect_down_arr_night_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_connect_down_arr_night_img_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_connect_down_arr_night_img_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_connect_down_arr_night_img, &style_setting_screen_connect_down_arr_night_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_connect_down_arr_night_img, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_connect_down_arr_night_img,&_Setting_Drow_Arrow_20x11);
	lv_img_set_pivot(ui->Setting_Screen_connect_down_arr_night_img, 0,0);
	lv_img_set_angle(ui->Setting_Screen_connect_down_arr_night_img, 0);

	//Write codes Setting_Screen_connect_night_L1
	ui->Setting_Screen_connect_night_L1 = lv_label_create(ui->Setting_Screen_setting_connect_night_container);
	lv_obj_set_pos(ui->Setting_Screen_connect_night_L1, 0, 148);
	lv_obj_set_size(ui->Setting_Screen_connect_night_L1, 240, 18);
	lv_label_set_text(ui->Setting_Screen_connect_night_L1, "");
	lv_label_set_long_mode(ui->Setting_Screen_connect_night_L1, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->Setting_Screen_connect_night_L1, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_connect_night_l1_main_main_default
	static lv_style_t style_setting_screen_connect_night_l1_main_main_default;
	lv_style_reset(&style_setting_screen_connect_night_l1_main_main_default);
	lv_style_set_radius(&style_setting_screen_connect_night_l1_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_connect_night_l1_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_setting_screen_connect_night_l1_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_setting_screen_connect_night_l1_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_connect_night_l1_main_main_default, 0);
	lv_style_set_text_color(&style_setting_screen_connect_night_l1_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_setting_screen_connect_night_l1_main_main_default, &lv_font_FjallaOne_Regular_22);
	lv_style_set_text_letter_space(&style_setting_screen_connect_night_l1_main_main_default, 0);
	lv_style_set_pad_left(&style_setting_screen_connect_night_l1_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_connect_night_l1_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_connect_night_l1_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_connect_night_l1_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_connect_night_L1, &style_setting_screen_connect_night_l1_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_setting_connect_day_container
	ui->Setting_Screen_setting_connect_day_container = lv_obj_create(ui->Setting_Screen);
	lv_obj_set_pos(ui->Setting_Screen_setting_connect_day_container, 0, 0);
	lv_obj_set_size(ui->Setting_Screen_setting_connect_day_container, 240, 320);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_setting_connect_day_container_main_main_default
	static lv_style_t style_setting_screen_setting_connect_day_container_main_main_default;
	lv_style_reset(&style_setting_screen_setting_connect_day_container_main_main_default);
	lv_style_set_radius(&style_setting_screen_setting_connect_day_container_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_setting_connect_day_container_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_color(&style_setting_screen_setting_connect_day_container_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_dir(&style_setting_screen_setting_connect_day_container_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_setting_connect_day_container_main_main_default, 0);
	lv_style_set_border_color(&style_setting_screen_setting_connect_day_container_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_border_width(&style_setting_screen_setting_connect_day_container_main_main_default, 0);
	lv_style_set_border_opa(&style_setting_screen_setting_connect_day_container_main_main_default, 255);
	lv_style_set_pad_left(&style_setting_screen_setting_connect_day_container_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_setting_connect_day_container_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_setting_connect_day_container_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_setting_connect_day_container_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_setting_connect_day_container, &style_setting_screen_setting_connect_day_container_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_connect_day_circle_img
	ui->Setting_Screen_connect_day_circle_img = lv_img_create(ui->Setting_Screen_setting_connect_day_container);
	lv_obj_set_pos(ui->Setting_Screen_connect_day_circle_img, 7, 47);
	lv_obj_set_size(ui->Setting_Screen_connect_day_circle_img, 226, 226);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_connect_day_circle_img_main_main_default
	static lv_style_t style_setting_screen_connect_day_circle_img_main_main_default;
	lv_style_reset(&style_setting_screen_connect_day_circle_img_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_connect_day_circle_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_connect_day_circle_img_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_connect_day_circle_img_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_connect_day_circle_img, &style_setting_screen_connect_day_circle_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_connect_day_circle_img, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_connect_day_circle_img,&day_white_Grey_circle);
	lv_img_set_pivot(ui->Setting_Screen_connect_day_circle_img, 0,0);
	lv_img_set_angle(ui->Setting_Screen_connect_day_circle_img, 0);

	//Write codes Setting_Screen_connect_side_day_img
	ui->Setting_Screen_connect_side_day_img = lv_img_create(ui->Setting_Screen_setting_connect_day_container);
	lv_obj_set_pos(ui->Setting_Screen_connect_side_day_img, 16, 142);
	lv_obj_set_size(ui->Setting_Screen_connect_side_day_img, 40, 40);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_connect_side_day_img_main_main_default
	static lv_style_t style_setting_screen_connect_side_day_img_main_main_default;
	lv_style_reset(&style_setting_screen_connect_side_day_img_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_connect_side_day_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_connect_side_day_img_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_connect_side_day_img_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_connect_side_day_img, &style_setting_screen_connect_side_day_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_connect_sub_button_day_img
	ui->Setting_Screen_connect_sub_button_day_img = lv_img_create(ui->Setting_Screen_setting_connect_day_container);
	lv_obj_set_pos(ui->Setting_Screen_connect_sub_button_day_img, 196, 149);
	lv_obj_set_size(ui->Setting_Screen_connect_sub_button_day_img, 24, 24);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_connect_sub_button_day_img_main_main_default
	static lv_style_t style_setting_screen_connect_sub_button_day_img_main_main_default;
	lv_style_reset(&style_setting_screen_connect_sub_button_day_img_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_connect_sub_button_day_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_connect_sub_button_day_img_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_connect_sub_button_day_img_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_connect_sub_button_day_img, &style_setting_screen_connect_sub_button_day_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_connect_sub_button_day_img, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_connect_sub_button_day_img,&subbtn_day_24x24);
	lv_img_set_pivot(ui->Setting_Screen_connect_sub_button_day_img, 0,0);
	lv_img_set_angle(ui->Setting_Screen_connect_sub_button_day_img, 0);

	//Write codes Setting_Screen_connect_switch_btn_day_img
	ui->Setting_Screen_connect_switch_btn_day_img = lv_img_create(ui->Setting_Screen_setting_connect_day_container);
	lv_obj_set_pos(ui->Setting_Screen_connect_switch_btn_day_img, 179, 147);
	lv_obj_set_size(ui->Setting_Screen_connect_switch_btn_day_img, 29, 20);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_connect_switch_btn_day_img_main_main_default
	static lv_style_t style_setting_screen_connect_switch_btn_day_img_main_main_default;
	lv_style_reset(&style_setting_screen_connect_switch_btn_day_img_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_connect_switch_btn_day_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_connect_switch_btn_day_img_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_connect_switch_btn_day_img_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_connect_switch_btn_day_img, &style_setting_screen_connect_switch_btn_day_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_connect_switch_btn_day_img, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_connect_switch_btn_day_img,&_day_toogle_on_29x20);
	lv_img_set_pivot(ui->Setting_Screen_connect_switch_btn_day_img, 0,0);
	lv_img_set_angle(ui->Setting_Screen_connect_switch_btn_day_img, 0);

	//Write codes Setting_Screen_connect_up_arr_day_img
	ui->Setting_Screen_connect_up_arr_day_img = lv_img_create(ui->Setting_Screen_setting_connect_day_container);
	lv_obj_set_pos(ui->Setting_Screen_connect_up_arr_day_img, 110, 105);
	lv_obj_set_size(ui->Setting_Screen_connect_up_arr_day_img, 20, 11);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_connect_up_arr_day_img_main_main_default
	static lv_style_t style_setting_screen_connect_up_arr_day_img_main_main_default;
	lv_style_reset(&style_setting_screen_connect_up_arr_day_img_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_connect_up_arr_day_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_connect_up_arr_day_img_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_connect_up_arr_day_img_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_connect_up_arr_day_img, &style_setting_screen_connect_up_arr_day_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_connect_up_arr_day_img, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_connect_up_arr_day_img,&_day_up_arrow_20x11);
	lv_img_set_pivot(ui->Setting_Screen_connect_up_arr_day_img, 0,0);
	lv_img_set_angle(ui->Setting_Screen_connect_up_arr_day_img, 0);

	//Write codes Setting_Screen_connect_dow_arr_day_img
	ui->Setting_Screen_connect_dow_arr_day_img = lv_img_create(ui->Setting_Screen_setting_connect_day_container);
	lv_obj_set_pos(ui->Setting_Screen_connect_dow_arr_day_img, 110, 198);
	lv_obj_set_size(ui->Setting_Screen_connect_dow_arr_day_img, 20, 11);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_connect_dow_arr_day_img_main_main_default
	static lv_style_t style_setting_screen_connect_dow_arr_day_img_main_main_default;
	lv_style_reset(&style_setting_screen_connect_dow_arr_day_img_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_connect_dow_arr_day_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_connect_dow_arr_day_img_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_connect_dow_arr_day_img_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_connect_dow_arr_day_img, &style_setting_screen_connect_dow_arr_day_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_connect_dow_arr_day_img, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_connect_dow_arr_day_img,&_day_down_arrow_20x11);
	lv_img_set_pivot(ui->Setting_Screen_connect_dow_arr_day_img, 0,0);
	lv_img_set_angle(ui->Setting_Screen_connect_dow_arr_day_img, 0);

	//Write codes Setting_Screen_connect_day_L1
	ui->Setting_Screen_connect_day_L1 = lv_label_create(ui->Setting_Screen_setting_connect_day_container);
	lv_obj_set_pos(ui->Setting_Screen_connect_day_L1, 0, 148);
	lv_obj_set_size(ui->Setting_Screen_connect_day_L1, 240, 18);
	lv_label_set_text(ui->Setting_Screen_connect_day_L1, "");
	lv_label_set_long_mode(ui->Setting_Screen_connect_day_L1, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->Setting_Screen_connect_day_L1, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_connect_day_l1_main_main_default
	static lv_style_t style_setting_screen_connect_day_l1_main_main_default;
	lv_style_reset(&style_setting_screen_connect_day_l1_main_main_default);
	lv_style_set_radius(&style_setting_screen_connect_day_l1_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_connect_day_l1_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_setting_screen_connect_day_l1_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_setting_screen_connect_day_l1_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_connect_day_l1_main_main_default, 0);
	lv_style_set_text_color(&style_setting_screen_connect_day_l1_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_setting_screen_connect_day_l1_main_main_default, &lv_font_FjallaOne_Regular_22);
	lv_style_set_text_letter_space(&style_setting_screen_connect_day_l1_main_main_default, 0);
	lv_style_set_pad_left(&style_setting_screen_connect_day_l1_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_connect_day_l1_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_connect_day_l1_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_connect_day_l1_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_connect_day_L1, &style_setting_screen_connect_day_l1_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_setting_music_night_container
	ui->Setting_Screen_setting_music_night_container = lv_obj_create(ui->Setting_Screen);
	lv_obj_set_pos(ui->Setting_Screen_setting_music_night_container, 0, 0);
	lv_obj_set_size(ui->Setting_Screen_setting_music_night_container, 240, 320);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_setting_music_night_container_main_main_default
	static lv_style_t style_setting_screen_setting_music_night_container_main_main_default;
	lv_style_reset(&style_setting_screen_setting_music_night_container_main_main_default);
	lv_style_set_radius(&style_setting_screen_setting_music_night_container_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_setting_music_night_container_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_color(&style_setting_screen_setting_music_night_container_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_dir(&style_setting_screen_setting_music_night_container_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_setting_music_night_container_main_main_default, 0);
	lv_style_set_border_color(&style_setting_screen_setting_music_night_container_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_border_width(&style_setting_screen_setting_music_night_container_main_main_default, 0);
	lv_style_set_border_opa(&style_setting_screen_setting_music_night_container_main_main_default, 255);
	lv_style_set_pad_left(&style_setting_screen_setting_music_night_container_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_setting_music_night_container_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_setting_music_night_container_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_setting_music_night_container_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_setting_music_night_container, &style_setting_screen_setting_music_night_container_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_music_sel_btn1_img
	ui->Setting_Screen_music_sel_btn1_img = lv_img_create(ui->Setting_Screen_setting_music_night_container);
	lv_obj_set_pos(ui->Setting_Screen_music_sel_btn1_img, 176, 103);
	lv_obj_set_size(ui->Setting_Screen_music_sel_btn1_img, 20, 20);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_music_sel_btn1_img_main_main_default
	static lv_style_t style_setting_screen_music_sel_btn1_img_main_main_default;
	lv_style_reset(&style_setting_screen_music_sel_btn1_img_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_music_sel_btn1_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_music_sel_btn1_img_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_music_sel_btn1_img_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_music_sel_btn1_img, &style_setting_screen_music_sel_btn1_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_music_sel_btn1_img, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_music_sel_btn1_img,&_radiobtn_night_unchecked_20x20);
	lv_img_set_pivot(ui->Setting_Screen_music_sel_btn1_img, 0,0);
	lv_img_set_angle(ui->Setting_Screen_music_sel_btn1_img, 0);

	//Write codes Setting_Screen_music_sel_btn2_img
	ui->Setting_Screen_music_sel_btn2_img = lv_img_create(ui->Setting_Screen_setting_music_night_container);
	lv_obj_set_pos(ui->Setting_Screen_music_sel_btn2_img, 176, 150);
	lv_obj_set_size(ui->Setting_Screen_music_sel_btn2_img, 20, 20);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_music_sel_btn2_img_main_main_default
	static lv_style_t style_setting_screen_music_sel_btn2_img_main_main_default;
	lv_style_reset(&style_setting_screen_music_sel_btn2_img_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_music_sel_btn2_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_music_sel_btn2_img_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_music_sel_btn2_img_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_music_sel_btn2_img, &style_setting_screen_music_sel_btn2_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_music_sel_btn2_img, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_music_sel_btn2_img,&_radiobtn_night_Checked_20x20);
	lv_img_set_pivot(ui->Setting_Screen_music_sel_btn2_img, 0,0);
	lv_img_set_angle(ui->Setting_Screen_music_sel_btn2_img, 0);

	//Write codes Setting_Screen_music_sel_btn3_img
	ui->Setting_Screen_music_sel_btn3_img = lv_img_create(ui->Setting_Screen_setting_music_night_container);
	lv_obj_set_pos(ui->Setting_Screen_music_sel_btn3_img, 176, 198);
	lv_obj_set_size(ui->Setting_Screen_music_sel_btn3_img, 20, 20);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_music_sel_btn3_img_main_main_default
	static lv_style_t style_setting_screen_music_sel_btn3_img_main_main_default;
	lv_style_reset(&style_setting_screen_music_sel_btn3_img_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_music_sel_btn3_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_music_sel_btn3_img_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_music_sel_btn3_img_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_music_sel_btn3_img, &style_setting_screen_music_sel_btn3_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_music_sel_btn3_img, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_music_sel_btn3_img,&_radiobtn_night_unchecked_20x20);
	lv_img_set_pivot(ui->Setting_Screen_music_sel_btn3_img, 0,0);
	lv_img_set_angle(ui->Setting_Screen_music_sel_btn3_img, 0);

	//Write codes Setting_Screen_music_up_arr_night_img
	ui->Setting_Screen_music_up_arr_night_img = lv_img_create(ui->Setting_Screen_setting_music_night_container);
	lv_obj_set_pos(ui->Setting_Screen_music_up_arr_night_img, 110, 65);
	lv_obj_set_size(ui->Setting_Screen_music_up_arr_night_img, 20, 11);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_music_up_arr_night_img_main_main_default
	static lv_style_t style_setting_screen_music_up_arr_night_img_main_main_default;
	lv_style_reset(&style_setting_screen_music_up_arr_night_img_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_music_up_arr_night_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_music_up_arr_night_img_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_music_up_arr_night_img_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_music_up_arr_night_img, &style_setting_screen_music_up_arr_night_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_music_up_arr_night_img, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_music_up_arr_night_img,&_Setting_Up_Arrow_20x11);
	lv_img_set_pivot(ui->Setting_Screen_music_up_arr_night_img, 0,0);
	lv_img_set_angle(ui->Setting_Screen_music_up_arr_night_img, 0);

	//Write codes Setting_Screen_music_down_arr_night_img
	ui->Setting_Screen_music_down_arr_night_img = lv_img_create(ui->Setting_Screen_setting_music_night_container);
	lv_obj_set_pos(ui->Setting_Screen_music_down_arr_night_img, 110, 238);
	lv_obj_set_size(ui->Setting_Screen_music_down_arr_night_img, 20, 11);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_music_down_arr_night_img_main_main_default
	static lv_style_t style_setting_screen_music_down_arr_night_img_main_main_default;
	lv_style_reset(&style_setting_screen_music_down_arr_night_img_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_music_down_arr_night_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_music_down_arr_night_img_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_music_down_arr_night_img_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_music_down_arr_night_img, &style_setting_screen_music_down_arr_night_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_music_down_arr_night_img, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_music_down_arr_night_img,&_Setting_Drow_Arrow_20x11);
	lv_img_set_pivot(ui->Setting_Screen_music_down_arr_night_img, 0,0);
	lv_img_set_angle(ui->Setting_Screen_music_down_arr_night_img, 0);

	//Write codes Setting_Screen_music_night_L1
	ui->Setting_Screen_music_night_L1 = lv_label_create(ui->Setting_Screen_setting_music_night_container);
	lv_obj_set_pos(ui->Setting_Screen_music_night_L1, 49, 100);
	lv_obj_set_size(ui->Setting_Screen_music_night_L1, 130, 18);
	lv_label_set_text(ui->Setting_Screen_music_night_L1, "");
	lv_label_set_long_mode(ui->Setting_Screen_music_night_L1, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->Setting_Screen_music_night_L1, LV_TEXT_ALIGN_LEFT, 0);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_music_night_l1_main_main_default
	static lv_style_t style_setting_screen_music_night_l1_main_main_default;
	lv_style_reset(&style_setting_screen_music_night_l1_main_main_default);
	lv_style_set_radius(&style_setting_screen_music_night_l1_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_music_night_l1_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_setting_screen_music_night_l1_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_setting_screen_music_night_l1_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_music_night_l1_main_main_default, 0);
	lv_style_set_text_color(&style_setting_screen_music_night_l1_main_main_default, lv_color_make(0x50, 0x50, 0x50));
	lv_style_set_text_font(&style_setting_screen_music_night_l1_main_main_default, &lv_font_FjallaOne_Regular_22);
	lv_style_set_text_letter_space(&style_setting_screen_music_night_l1_main_main_default, 0);
	lv_style_set_pad_left(&style_setting_screen_music_night_l1_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_music_night_l1_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_music_night_l1_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_music_night_l1_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_music_night_L1, &style_setting_screen_music_night_l1_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_music_night_L2
	ui->Setting_Screen_music_night_L2 = lv_label_create(ui->Setting_Screen_setting_music_night_container);
	lv_obj_set_pos(ui->Setting_Screen_music_night_L2, 49, 148);
	lv_obj_set_size(ui->Setting_Screen_music_night_L2, 100, 18);
	lv_label_set_text(ui->Setting_Screen_music_night_L2, "");
	lv_label_set_long_mode(ui->Setting_Screen_music_night_L2, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->Setting_Screen_music_night_L2, LV_TEXT_ALIGN_LEFT, 0);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_music_night_l2_main_main_default
	static lv_style_t style_setting_screen_music_night_l2_main_main_default;
	lv_style_reset(&style_setting_screen_music_night_l2_main_main_default);
	lv_style_set_radius(&style_setting_screen_music_night_l2_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_music_night_l2_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_setting_screen_music_night_l2_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_setting_screen_music_night_l2_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_music_night_l2_main_main_default, 0);
	lv_style_set_text_color(&style_setting_screen_music_night_l2_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_setting_screen_music_night_l2_main_main_default, &lv_font_FjallaOne_Regular_22);
	lv_style_set_text_letter_space(&style_setting_screen_music_night_l2_main_main_default, 0);
	lv_style_set_pad_left(&style_setting_screen_music_night_l2_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_music_night_l2_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_music_night_l2_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_music_night_l2_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_music_night_L2, &style_setting_screen_music_night_l2_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_music_night_L3
	ui->Setting_Screen_music_night_L3 = lv_label_create(ui->Setting_Screen_setting_music_night_container);
	lv_obj_set_pos(ui->Setting_Screen_music_night_L3, 49, 196);
	lv_obj_set_size(ui->Setting_Screen_music_night_L3, 100, 18);
	lv_label_set_text(ui->Setting_Screen_music_night_L3, "");
	lv_label_set_long_mode(ui->Setting_Screen_music_night_L3, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->Setting_Screen_music_night_L3, LV_TEXT_ALIGN_LEFT, 0);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_music_night_l3_main_main_default
	static lv_style_t style_setting_screen_music_night_l3_main_main_default;
	lv_style_reset(&style_setting_screen_music_night_l3_main_main_default);
	lv_style_set_radius(&style_setting_screen_music_night_l3_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_music_night_l3_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_setting_screen_music_night_l3_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_setting_screen_music_night_l3_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_music_night_l3_main_main_default, 0);
	lv_style_set_text_color(&style_setting_screen_music_night_l3_main_main_default, lv_color_make(0x50, 0x50, 0x50));
	lv_style_set_text_font(&style_setting_screen_music_night_l3_main_main_default, &lv_font_FjallaOne_Regular_22);
	lv_style_set_text_letter_space(&style_setting_screen_music_night_l3_main_main_default, 0);
	lv_style_set_pad_left(&style_setting_screen_music_night_l3_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_music_night_l3_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_music_night_l3_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_music_night_l3_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_music_night_L3, &style_setting_screen_music_night_l3_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_setting_music_day_container
	ui->Setting_Screen_setting_music_day_container = lv_obj_create(ui->Setting_Screen);
	lv_obj_set_pos(ui->Setting_Screen_setting_music_day_container, 0, 0);
	lv_obj_set_size(ui->Setting_Screen_setting_music_day_container, 240, 320);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_setting_music_day_container_main_main_default
	static lv_style_t style_setting_screen_setting_music_day_container_main_main_default;
	lv_style_reset(&style_setting_screen_setting_music_day_container_main_main_default);
	lv_style_set_radius(&style_setting_screen_setting_music_day_container_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_setting_music_day_container_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_color(&style_setting_screen_setting_music_day_container_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_dir(&style_setting_screen_setting_music_day_container_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_setting_music_day_container_main_main_default, 0);
	lv_style_set_border_color(&style_setting_screen_setting_music_day_container_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_border_width(&style_setting_screen_setting_music_day_container_main_main_default, 0);
	lv_style_set_border_opa(&style_setting_screen_setting_music_day_container_main_main_default, 255);
	lv_style_set_pad_left(&style_setting_screen_setting_music_day_container_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_setting_music_day_container_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_setting_music_day_container_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_setting_music_day_container_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_setting_music_day_container, &style_setting_screen_setting_music_day_container_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_music_day_cicrcle_img
	ui->Setting_Screen_music_day_cicrcle_img = lv_img_create(ui->Setting_Screen_setting_music_day_container);
	lv_obj_set_pos(ui->Setting_Screen_music_day_cicrcle_img, 7, 47);
	lv_obj_set_size(ui->Setting_Screen_music_day_cicrcle_img, 226, 226);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_music_day_cicrcle_img_main_main_default
	static lv_style_t style_setting_screen_music_day_cicrcle_img_main_main_default;
	lv_style_reset(&style_setting_screen_music_day_cicrcle_img_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_music_day_cicrcle_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_music_day_cicrcle_img_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_music_day_cicrcle_img_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_music_day_cicrcle_img, &style_setting_screen_music_day_cicrcle_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_music_day_cicrcle_img, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_music_day_cicrcle_img,&day_white_Grey_circle);
	lv_img_set_pivot(ui->Setting_Screen_music_day_cicrcle_img, 0,0);
	lv_img_set_angle(ui->Setting_Screen_music_day_cicrcle_img, 0);

	//Write codes Setting_Screen_music_sel_day_btn1_img
	ui->Setting_Screen_music_sel_day_btn1_img = lv_img_create(ui->Setting_Screen_setting_music_day_container);
	lv_obj_set_pos(ui->Setting_Screen_music_sel_day_btn1_img, 176, 103);
	lv_obj_set_size(ui->Setting_Screen_music_sel_day_btn1_img, 20, 20);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_music_sel_day_btn1_img_main_main_default
	static lv_style_t style_setting_screen_music_sel_day_btn1_img_main_main_default;
	lv_style_reset(&style_setting_screen_music_sel_day_btn1_img_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_music_sel_day_btn1_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_music_sel_day_btn1_img_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_music_sel_day_btn1_img_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_music_sel_day_btn1_img, &style_setting_screen_music_sel_day_btn1_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_music_sel_day_btn1_img, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_music_sel_day_btn1_img,&_radiobtn_day_unchecked_20x20);
	lv_img_set_pivot(ui->Setting_Screen_music_sel_day_btn1_img, 0,0);
	lv_img_set_angle(ui->Setting_Screen_music_sel_day_btn1_img, 0);

	//Write codes Setting_Screen_music_sel_day_btn2_img
	ui->Setting_Screen_music_sel_day_btn2_img = lv_img_create(ui->Setting_Screen_setting_music_day_container);
	lv_obj_set_pos(ui->Setting_Screen_music_sel_day_btn2_img, 176, 150);
	lv_obj_set_size(ui->Setting_Screen_music_sel_day_btn2_img, 20, 20);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_music_sel_day_btn2_img_main_main_default
	static lv_style_t style_setting_screen_music_sel_day_btn2_img_main_main_default;
	lv_style_reset(&style_setting_screen_music_sel_day_btn2_img_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_music_sel_day_btn2_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_music_sel_day_btn2_img_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_music_sel_day_btn2_img_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_music_sel_day_btn2_img, &style_setting_screen_music_sel_day_btn2_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_music_sel_day_btn2_img, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_music_sel_day_btn2_img,&_radiobtn_day_checked_20x20);
	lv_img_set_pivot(ui->Setting_Screen_music_sel_day_btn2_img, 0,0);
	lv_img_set_angle(ui->Setting_Screen_music_sel_day_btn2_img, 0);

	//Write codes Setting_Screen_music_sel_day_btn3_img
	ui->Setting_Screen_music_sel_day_btn3_img = lv_img_create(ui->Setting_Screen_setting_music_day_container);
	lv_obj_set_pos(ui->Setting_Screen_music_sel_day_btn3_img, 176, 198);
	lv_obj_set_size(ui->Setting_Screen_music_sel_day_btn3_img, 20, 20);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_music_sel_day_btn3_img_main_main_default
	static lv_style_t style_setting_screen_music_sel_day_btn3_img_main_main_default;
	lv_style_reset(&style_setting_screen_music_sel_day_btn3_img_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_music_sel_day_btn3_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_music_sel_day_btn3_img_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_music_sel_day_btn3_img_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_music_sel_day_btn3_img, &style_setting_screen_music_sel_day_btn3_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_music_sel_day_btn3_img, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_music_sel_day_btn3_img,&_radiobtn_day_unchecked_20x20);
	lv_img_set_pivot(ui->Setting_Screen_music_sel_day_btn3_img, 0,0);
	lv_img_set_angle(ui->Setting_Screen_music_sel_day_btn3_img, 0);

	//Write codes Setting_Screen_music_up_arr_day_img
	ui->Setting_Screen_music_up_arr_day_img = lv_img_create(ui->Setting_Screen_setting_music_day_container);
	lv_obj_set_pos(ui->Setting_Screen_music_up_arr_day_img, 110, 65);
	lv_obj_set_size(ui->Setting_Screen_music_up_arr_day_img, 20, 11);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_music_up_arr_day_img_main_main_default
	static lv_style_t style_setting_screen_music_up_arr_day_img_main_main_default;
	lv_style_reset(&style_setting_screen_music_up_arr_day_img_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_music_up_arr_day_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_music_up_arr_day_img_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_music_up_arr_day_img_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_music_up_arr_day_img, &style_setting_screen_music_up_arr_day_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_music_up_arr_day_img, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_music_up_arr_day_img,&_day_up_arrow_20x11);
	lv_img_set_pivot(ui->Setting_Screen_music_up_arr_day_img, 0,0);
	lv_img_set_angle(ui->Setting_Screen_music_up_arr_day_img, 0);

	//Write codes Setting_Screen_music_night_arr_day_img
	ui->Setting_Screen_music_night_arr_day_img = lv_img_create(ui->Setting_Screen_setting_music_day_container);
	lv_obj_set_pos(ui->Setting_Screen_music_night_arr_day_img, 110, 238);
	lv_obj_set_size(ui->Setting_Screen_music_night_arr_day_img, 20, 11);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_music_night_arr_day_img_main_main_default
	static lv_style_t style_setting_screen_music_night_arr_day_img_main_main_default;
	lv_style_reset(&style_setting_screen_music_night_arr_day_img_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_music_night_arr_day_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_music_night_arr_day_img_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_music_night_arr_day_img_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_music_night_arr_day_img, &style_setting_screen_music_night_arr_day_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_music_night_arr_day_img, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_music_night_arr_day_img,&_day_down_arrow_20x11);
	lv_img_set_pivot(ui->Setting_Screen_music_night_arr_day_img, 0,0);
	lv_img_set_angle(ui->Setting_Screen_music_night_arr_day_img, 0);

	//Write codes Setting_Screen_music_day_L1
	ui->Setting_Screen_music_day_L1 = lv_label_create(ui->Setting_Screen_setting_music_day_container);
	lv_obj_set_pos(ui->Setting_Screen_music_day_L1, 49, 100);
	lv_obj_set_size(ui->Setting_Screen_music_day_L1, 100, 18);
	lv_label_set_text(ui->Setting_Screen_music_day_L1, "");
	lv_label_set_long_mode(ui->Setting_Screen_music_day_L1, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->Setting_Screen_music_day_L1, LV_TEXT_ALIGN_LEFT, 0);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_music_day_l1_main_main_default
	static lv_style_t style_setting_screen_music_day_l1_main_main_default;
	lv_style_reset(&style_setting_screen_music_day_l1_main_main_default);
	lv_style_set_radius(&style_setting_screen_music_day_l1_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_music_day_l1_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_setting_screen_music_day_l1_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_setting_screen_music_day_l1_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_music_day_l1_main_main_default, 0);
	lv_style_set_text_color(&style_setting_screen_music_day_l1_main_main_default, lv_color_make(0xb8, 0xb8, 0xb8));
	lv_style_set_text_font(&style_setting_screen_music_day_l1_main_main_default, &lv_font_FjallaOne_Regular_22);
	lv_style_set_text_letter_space(&style_setting_screen_music_day_l1_main_main_default, 0);
	lv_style_set_pad_left(&style_setting_screen_music_day_l1_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_music_day_l1_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_music_day_l1_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_music_day_l1_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_music_day_L1, &style_setting_screen_music_day_l1_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_music_day_L2
	ui->Setting_Screen_music_day_L2 = lv_label_create(ui->Setting_Screen_setting_music_day_container);
	lv_obj_set_pos(ui->Setting_Screen_music_day_L2, 49, 148);
	lv_obj_set_size(ui->Setting_Screen_music_day_L2, 100, 18);
	lv_label_set_text(ui->Setting_Screen_music_day_L2, "");
	lv_label_set_long_mode(ui->Setting_Screen_music_day_L2, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->Setting_Screen_music_day_L2, LV_TEXT_ALIGN_LEFT, 0);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_music_day_l2_main_main_default
	static lv_style_t style_setting_screen_music_day_l2_main_main_default;
	lv_style_reset(&style_setting_screen_music_day_l2_main_main_default);
	lv_style_set_radius(&style_setting_screen_music_day_l2_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_music_day_l2_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_setting_screen_music_day_l2_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_setting_screen_music_day_l2_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_music_day_l2_main_main_default, 0);
	lv_style_set_text_color(&style_setting_screen_music_day_l2_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_setting_screen_music_day_l2_main_main_default, &lv_font_FjallaOne_Regular_22);
	lv_style_set_text_letter_space(&style_setting_screen_music_day_l2_main_main_default, 0);
	lv_style_set_pad_left(&style_setting_screen_music_day_l2_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_music_day_l2_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_music_day_l2_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_music_day_l2_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_music_day_L2, &style_setting_screen_music_day_l2_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_music_day_L3
	ui->Setting_Screen_music_day_L3 = lv_label_create(ui->Setting_Screen_setting_music_day_container);
	lv_obj_set_pos(ui->Setting_Screen_music_day_L3, 49, 196);
	lv_obj_set_size(ui->Setting_Screen_music_day_L3, 100, 18);
	lv_label_set_text(ui->Setting_Screen_music_day_L3, "");
	lv_label_set_long_mode(ui->Setting_Screen_music_day_L3, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->Setting_Screen_music_day_L3, LV_TEXT_ALIGN_LEFT, 0);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_music_day_l3_main_main_default
	static lv_style_t style_setting_screen_music_day_l3_main_main_default;
	lv_style_reset(&style_setting_screen_music_day_l3_main_main_default);
	lv_style_set_radius(&style_setting_screen_music_day_l3_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_music_day_l3_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_setting_screen_music_day_l3_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_setting_screen_music_day_l3_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_music_day_l3_main_main_default, 0);
	lv_style_set_text_color(&style_setting_screen_music_day_l3_main_main_default, lv_color_make(0xb8, 0xb8, 0xb8));
	lv_style_set_text_font(&style_setting_screen_music_day_l3_main_main_default, &lv_font_FjallaOne_Regular_22);
	lv_style_set_text_letter_space(&style_setting_screen_music_day_l3_main_main_default, 0);
	lv_style_set_pad_left(&style_setting_screen_music_day_l3_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_music_day_l3_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_music_day_l3_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_music_day_l3_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_music_day_L3, &style_setting_screen_music_day_l3_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);


	//Write codes Setting_Screen_setting_brightness_night_contain
	ui->Setting_Screen_setting_brightness_night_contain = lv_obj_create(ui->Setting_Screen);
	lv_obj_set_pos(ui->Setting_Screen_setting_brightness_night_contain, 0, 0);
	lv_obj_set_size(ui->Setting_Screen_setting_brightness_night_contain, 240, 320);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_setting_brightness_night_contain_main_main_default
	static lv_style_t style_setting_screen_setting_brightness_night_contain_main_main_default;
	lv_style_reset(&style_setting_screen_setting_brightness_night_contain_main_main_default);
	lv_style_set_radius(&style_setting_screen_setting_brightness_night_contain_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_setting_brightness_night_contain_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_color(&style_setting_screen_setting_brightness_night_contain_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_dir(&style_setting_screen_setting_brightness_night_contain_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_setting_brightness_night_contain_main_main_default, 0);
	lv_style_set_border_color(&style_setting_screen_setting_brightness_night_contain_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_border_width(&style_setting_screen_setting_brightness_night_contain_main_main_default, 0);
	lv_style_set_border_opa(&style_setting_screen_setting_brightness_night_contain_main_main_default, 255);
	lv_style_set_pad_left(&style_setting_screen_setting_brightness_night_contain_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_setting_brightness_night_contain_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_setting_brightness_night_contain_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_setting_brightness_night_contain_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_setting_brightness_night_contain, &style_setting_screen_setting_brightness_night_contain_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_brightness_sel_btn1_img
	ui->Setting_Screen_brightness_sel_btn1_img = lv_img_create(ui->Setting_Screen_setting_brightness_night_contain);
	lv_obj_set_pos(ui->Setting_Screen_brightness_sel_btn1_img, 176, 103);
	lv_obj_set_size(ui->Setting_Screen_brightness_sel_btn1_img, 20, 20);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_brightness_sel_btn1_img_main_main_default
	static lv_style_t style_setting_screen_brightness_sel_btn1_img_main_main_default;
	lv_style_reset(&style_setting_screen_brightness_sel_btn1_img_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_brightness_sel_btn1_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_brightness_sel_btn1_img_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_brightness_sel_btn1_img_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_brightness_sel_btn1_img, &style_setting_screen_brightness_sel_btn1_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_brightness_sel_btn1_img, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_brightness_sel_btn1_img,&_radiobtn_night_unchecked_20x20);
	lv_img_set_pivot(ui->Setting_Screen_brightness_sel_btn1_img, 0,0);
	lv_img_set_angle(ui->Setting_Screen_brightness_sel_btn1_img, 0);

	//Write codes Setting_Screen_brightness_sel_btn2_img
	ui->Setting_Screen_brightness_sel_btn2_img = lv_img_create(ui->Setting_Screen_setting_brightness_night_contain);
	lv_obj_set_pos(ui->Setting_Screen_brightness_sel_btn2_img, 176, 150);
	lv_obj_set_size(ui->Setting_Screen_brightness_sel_btn2_img, 20, 20);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_brightness_sel_btn2_img_main_main_default
	static lv_style_t style_setting_screen_brightness_sel_btn2_img_main_main_default;
	lv_style_reset(&style_setting_screen_brightness_sel_btn2_img_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_brightness_sel_btn2_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_brightness_sel_btn2_img_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_brightness_sel_btn2_img_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_brightness_sel_btn2_img, &style_setting_screen_brightness_sel_btn2_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_brightness_sel_btn2_img, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_brightness_sel_btn2_img,&_radiobtn_night_Checked_20x20);
	lv_img_set_pivot(ui->Setting_Screen_brightness_sel_btn2_img, 0,0);
	lv_img_set_angle(ui->Setting_Screen_brightness_sel_btn2_img, 0);

	//Write codes Setting_Screen_brightness_sel_btn3_img
	ui->Setting_Screen_brightness_sel_btn3_img = lv_img_create(ui->Setting_Screen_setting_brightness_night_contain);
	lv_obj_set_pos(ui->Setting_Screen_brightness_sel_btn3_img, 176, 198);
	lv_obj_set_size(ui->Setting_Screen_brightness_sel_btn3_img, 20, 20);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_brightness_sel_btn3_img_main_main_default
	static lv_style_t style_setting_screen_brightness_sel_btn3_img_main_main_default;
	lv_style_reset(&style_setting_screen_brightness_sel_btn3_img_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_brightness_sel_btn3_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_brightness_sel_btn3_img_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_brightness_sel_btn3_img_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_brightness_sel_btn3_img, &style_setting_screen_brightness_sel_btn3_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_brightness_sel_btn3_img, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_brightness_sel_btn3_img,&_radiobtn_night_unchecked_20x20);
	lv_img_set_pivot(ui->Setting_Screen_brightness_sel_btn3_img, 0,0);
	lv_img_set_angle(ui->Setting_Screen_brightness_sel_btn3_img, 0);

	//Write codes Setting_Screen_brightness_up_arr_night_img
	ui->Setting_Screen_brightness_up_arr_night_img = lv_img_create(ui->Setting_Screen_setting_brightness_night_contain);
	lv_obj_set_pos(ui->Setting_Screen_brightness_up_arr_night_img, 110, 65);
	lv_obj_set_size(ui->Setting_Screen_brightness_up_arr_night_img, 20, 11);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_brightness_up_arr_night_img_main_main_default
	static lv_style_t style_setting_screen_brightness_up_arr_night_img_main_main_default;
	lv_style_reset(&style_setting_screen_brightness_up_arr_night_img_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_brightness_up_arr_night_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_brightness_up_arr_night_img_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_brightness_up_arr_night_img_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_brightness_up_arr_night_img, &style_setting_screen_brightness_up_arr_night_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_brightness_up_arr_night_img, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_brightness_up_arr_night_img,&_Setting_Up_Arrow_20x11);
	lv_img_set_pivot(ui->Setting_Screen_brightness_up_arr_night_img, 0,0);
	lv_img_set_angle(ui->Setting_Screen_brightness_up_arr_night_img, 0);

	//Write codes Setting_Screen_brightness_down_arr_night_img
	ui->Setting_Screen_brightness_down_arr_night_img = lv_img_create(ui->Setting_Screen_setting_brightness_night_contain);
	lv_obj_set_pos(ui->Setting_Screen_brightness_down_arr_night_img, 110, 238);
	lv_obj_set_size(ui->Setting_Screen_brightness_down_arr_night_img, 20, 11);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_brightness_down_arr_night_img_main_main_default
	static lv_style_t style_setting_screen_brightness_down_arr_night_img_main_main_default;
	lv_style_reset(&style_setting_screen_brightness_down_arr_night_img_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_brightness_down_arr_night_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_brightness_down_arr_night_img_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_brightness_down_arr_night_img_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_brightness_down_arr_night_img, &style_setting_screen_brightness_down_arr_night_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_brightness_down_arr_night_img, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_brightness_down_arr_night_img,&_Setting_Drow_Arrow_20x11);
	lv_img_set_pivot(ui->Setting_Screen_brightness_down_arr_night_img, 0,0);
	lv_img_set_angle(ui->Setting_Screen_brightness_down_arr_night_img, 0);

	//Write codes Setting_Screen_brightness_night_L1
	ui->Setting_Screen_brightness_night_L1 = lv_label_create(ui->Setting_Screen_setting_brightness_night_contain);
	lv_obj_set_pos(ui->Setting_Screen_brightness_night_L1, 49, 100);
	lv_obj_set_size(ui->Setting_Screen_brightness_night_L1, 100, 18);
	lv_label_set_text(ui->Setting_Screen_brightness_night_L1, "");
	lv_label_set_long_mode(ui->Setting_Screen_brightness_night_L1, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->Setting_Screen_brightness_night_L1, LV_TEXT_ALIGN_LEFT, 0);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_brightness_night_l1_main_main_default
	static lv_style_t style_setting_screen_brightness_night_l1_main_main_default;
	lv_style_reset(&style_setting_screen_brightness_night_l1_main_main_default);
	lv_style_set_radius(&style_setting_screen_brightness_night_l1_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_brightness_night_l1_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_setting_screen_brightness_night_l1_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_setting_screen_brightness_night_l1_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_brightness_night_l1_main_main_default, 0);
	lv_style_set_text_color(&style_setting_screen_brightness_night_l1_main_main_default, lv_color_make(0x50, 0x50, 0x50));
	lv_style_set_text_font(&style_setting_screen_brightness_night_l1_main_main_default, &lv_font_FjallaOne_Regular_22);
	lv_style_set_text_letter_space(&style_setting_screen_brightness_night_l1_main_main_default, 0);
	lv_style_set_pad_left(&style_setting_screen_brightness_night_l1_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_brightness_night_l1_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_brightness_night_l1_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_brightness_night_l1_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_brightness_night_L1, &style_setting_screen_brightness_night_l1_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_brightness_night_L2
	ui->Setting_Screen_brightness_night_L2 = lv_label_create(ui->Setting_Screen_setting_brightness_night_contain);
	lv_obj_set_pos(ui->Setting_Screen_brightness_night_L2, 49, 148);
	lv_obj_set_size(ui->Setting_Screen_brightness_night_L2, 100, 18);
	lv_label_set_text(ui->Setting_Screen_brightness_night_L2, "");
	lv_label_set_long_mode(ui->Setting_Screen_brightness_night_L2, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->Setting_Screen_brightness_night_L2, LV_TEXT_ALIGN_LEFT, 0);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_brightness_night_l2_main_main_default
	static lv_style_t style_setting_screen_brightness_night_l2_main_main_default;
	lv_style_reset(&style_setting_screen_brightness_night_l2_main_main_default);
	lv_style_set_radius(&style_setting_screen_brightness_night_l2_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_brightness_night_l2_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_setting_screen_brightness_night_l2_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_setting_screen_brightness_night_l2_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_brightness_night_l2_main_main_default, 0);
	lv_style_set_text_color(&style_setting_screen_brightness_night_l2_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_setting_screen_brightness_night_l2_main_main_default, &lv_font_FjallaOne_Regular_22);
	lv_style_set_text_letter_space(&style_setting_screen_brightness_night_l2_main_main_default, 0);
	lv_style_set_pad_left(&style_setting_screen_brightness_night_l2_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_brightness_night_l2_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_brightness_night_l2_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_brightness_night_l2_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_brightness_night_L2, &style_setting_screen_brightness_night_l2_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_brightness_night_L3
	ui->Setting_Screen_brightness_night_L3 = lv_label_create(ui->Setting_Screen_setting_brightness_night_contain);
	lv_obj_set_pos(ui->Setting_Screen_brightness_night_L3, 49, 196);
	lv_obj_set_size(ui->Setting_Screen_brightness_night_L3, 100, 18);
	lv_label_set_text(ui->Setting_Screen_brightness_night_L3, "");
	lv_label_set_long_mode(ui->Setting_Screen_brightness_night_L3, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->Setting_Screen_brightness_night_L3, LV_TEXT_ALIGN_LEFT, 0);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_brightness_night_l3_main_main_default
	static lv_style_t style_setting_screen_brightness_night_l3_main_main_default;
	lv_style_reset(&style_setting_screen_brightness_night_l3_main_main_default);
	lv_style_set_radius(&style_setting_screen_brightness_night_l3_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_brightness_night_l3_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_setting_screen_brightness_night_l3_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_setting_screen_brightness_night_l3_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_brightness_night_l3_main_main_default, 0);
	lv_style_set_text_color(&style_setting_screen_brightness_night_l3_main_main_default, lv_color_make(0x50, 0x50, 0x50));
	lv_style_set_text_font(&style_setting_screen_brightness_night_l3_main_main_default, &lv_font_FjallaOne_Regular_22);
	lv_style_set_text_letter_space(&style_setting_screen_brightness_night_l3_main_main_default, 0);
	lv_style_set_pad_left(&style_setting_screen_brightness_night_l3_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_brightness_night_l3_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_brightness_night_l3_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_brightness_night_l3_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_brightness_night_L3, &style_setting_screen_brightness_night_l3_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_setting_brightness_day_contain
	ui->Setting_Screen_setting_brightness_day_contain = lv_obj_create(ui->Setting_Screen);
	lv_obj_set_pos(ui->Setting_Screen_setting_brightness_day_contain, 0, 0);
	lv_obj_set_size(ui->Setting_Screen_setting_brightness_day_contain, 240, 320);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_setting_brightness_day_contain_main_main_default
	static lv_style_t style_setting_screen_setting_brightness_day_contain_main_main_default;
	lv_style_reset(&style_setting_screen_setting_brightness_day_contain_main_main_default);
	lv_style_set_radius(&style_setting_screen_setting_brightness_day_contain_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_setting_brightness_day_contain_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_color(&style_setting_screen_setting_brightness_day_contain_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_dir(&style_setting_screen_setting_brightness_day_contain_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_setting_brightness_day_contain_main_main_default, 0);
	lv_style_set_border_color(&style_setting_screen_setting_brightness_day_contain_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_border_width(&style_setting_screen_setting_brightness_day_contain_main_main_default, 0);
	lv_style_set_border_opa(&style_setting_screen_setting_brightness_day_contain_main_main_default, 255);
	lv_style_set_pad_left(&style_setting_screen_setting_brightness_day_contain_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_setting_brightness_day_contain_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_setting_brightness_day_contain_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_setting_brightness_day_contain_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_setting_brightness_day_contain, &style_setting_screen_setting_brightness_day_contain_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_setting_day_circle_img
	ui->Setting_Screen_setting_day_circle_img = lv_img_create(ui->Setting_Screen_setting_brightness_day_contain);
	lv_obj_set_pos(ui->Setting_Screen_setting_day_circle_img, 7, 47);
	lv_obj_set_size(ui->Setting_Screen_setting_day_circle_img, 226, 226);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_setting_day_circle_img_main_main_default
	static lv_style_t style_setting_screen_setting_day_circle_img_main_main_default;
	lv_style_reset(&style_setting_screen_setting_day_circle_img_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_setting_day_circle_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_setting_day_circle_img_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_setting_day_circle_img_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_setting_day_circle_img, &style_setting_screen_setting_day_circle_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_setting_day_circle_img, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_setting_day_circle_img,&day_white_Grey_circle);
	lv_img_set_pivot(ui->Setting_Screen_setting_day_circle_img, 0,0);
	lv_img_set_angle(ui->Setting_Screen_setting_day_circle_img, 0);

	//Write codes Setting_Screen_brightness_sel_day_btn1_img
	ui->Setting_Screen_brightness_sel_day_btn1_img = lv_img_create(ui->Setting_Screen_setting_brightness_day_contain);
	lv_obj_set_pos(ui->Setting_Screen_brightness_sel_day_btn1_img, 176, 103);
	lv_obj_set_size(ui->Setting_Screen_brightness_sel_day_btn1_img, 20, 20);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_brightness_sel_day_btn1_img_main_main_default
	static lv_style_t style_setting_screen_brightness_sel_day_btn1_img_main_main_default;
	lv_style_reset(&style_setting_screen_brightness_sel_day_btn1_img_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_brightness_sel_day_btn1_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_brightness_sel_day_btn1_img_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_brightness_sel_day_btn1_img_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_brightness_sel_day_btn1_img, &style_setting_screen_brightness_sel_day_btn1_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_brightness_sel_day_btn1_img, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_brightness_sel_day_btn1_img,&_radiobtn_day_unchecked_20x20);
	lv_img_set_pivot(ui->Setting_Screen_brightness_sel_day_btn1_img, 0,0);
	lv_img_set_angle(ui->Setting_Screen_brightness_sel_day_btn1_img, 0);

	//Write codes Setting_Screen_brightness_sel_day_btn2_img
	ui->Setting_Screen_brightness_sel_day_btn2_img = lv_img_create(ui->Setting_Screen_setting_brightness_day_contain);
	lv_obj_set_pos(ui->Setting_Screen_brightness_sel_day_btn2_img, 176, 150);
	lv_obj_set_size(ui->Setting_Screen_brightness_sel_day_btn2_img, 20, 20);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_brightness_sel_day_btn2_img_main_main_default
	static lv_style_t style_setting_screen_brightness_sel_day_btn2_img_main_main_default;
	lv_style_reset(&style_setting_screen_brightness_sel_day_btn2_img_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_brightness_sel_day_btn2_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_brightness_sel_day_btn2_img_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_brightness_sel_day_btn2_img_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_brightness_sel_day_btn2_img, &style_setting_screen_brightness_sel_day_btn2_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_brightness_sel_day_btn2_img, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_brightness_sel_day_btn2_img,&_radiobtn_day_checked_20x20);
	lv_img_set_pivot(ui->Setting_Screen_brightness_sel_day_btn2_img, 0,0);
	lv_img_set_angle(ui->Setting_Screen_brightness_sel_day_btn2_img, 0);

	//Write codes Setting_Screen_brightness_sel_day_btn3_img
	ui->Setting_Screen_brightness_sel_day_btn3_img = lv_img_create(ui->Setting_Screen_setting_brightness_day_contain);
	lv_obj_set_pos(ui->Setting_Screen_brightness_sel_day_btn3_img, 176, 198);
	lv_obj_set_size(ui->Setting_Screen_brightness_sel_day_btn3_img, 20, 20);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_brightness_sel_day_btn3_img_main_main_default
	static lv_style_t style_setting_screen_brightness_sel_day_btn3_img_main_main_default;
	lv_style_reset(&style_setting_screen_brightness_sel_day_btn3_img_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_brightness_sel_day_btn3_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_brightness_sel_day_btn3_img_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_brightness_sel_day_btn3_img_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_brightness_sel_day_btn3_img, &style_setting_screen_brightness_sel_day_btn3_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_brightness_sel_day_btn3_img, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_brightness_sel_day_btn3_img,&_radiobtn_day_unchecked_20x20);
	lv_img_set_pivot(ui->Setting_Screen_brightness_sel_day_btn3_img, 0,0);
	lv_img_set_angle(ui->Setting_Screen_brightness_sel_day_btn3_img, 0);

	//Write codes Setting_Screen_brightness_up_arr_day_img
	ui->Setting_Screen_brightness_up_arr_day_img = lv_img_create(ui->Setting_Screen_setting_brightness_day_contain);
	lv_obj_set_pos(ui->Setting_Screen_brightness_up_arr_day_img, 110, 65);
	lv_obj_set_size(ui->Setting_Screen_brightness_up_arr_day_img, 20, 11);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_brightness_up_arr_day_img_main_main_default
	static lv_style_t style_setting_screen_brightness_up_arr_day_img_main_main_default;
	lv_style_reset(&style_setting_screen_brightness_up_arr_day_img_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_brightness_up_arr_day_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_brightness_up_arr_day_img_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_brightness_up_arr_day_img_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_brightness_up_arr_day_img, &style_setting_screen_brightness_up_arr_day_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_brightness_up_arr_day_img, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_brightness_up_arr_day_img,&_day_up_arrow_20x11);
	lv_img_set_pivot(ui->Setting_Screen_brightness_up_arr_day_img, 0,0);
	lv_img_set_angle(ui->Setting_Screen_brightness_up_arr_day_img, 0);

	//Write codes Setting_Screen_brightness_down_arr_day_img
	ui->Setting_Screen_brightness_down_arr_day_img = lv_img_create(ui->Setting_Screen_setting_brightness_day_contain);
	lv_obj_set_pos(ui->Setting_Screen_brightness_down_arr_day_img, 110, 238);
	lv_obj_set_size(ui->Setting_Screen_brightness_down_arr_day_img, 20, 11);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_brightness_down_arr_day_img_main_main_default
	static lv_style_t style_setting_screen_brightness_down_arr_day_img_main_main_default;
	lv_style_reset(&style_setting_screen_brightness_down_arr_day_img_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_brightness_down_arr_day_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_brightness_down_arr_day_img_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_brightness_down_arr_day_img_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_brightness_down_arr_day_img, &style_setting_screen_brightness_down_arr_day_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_brightness_down_arr_day_img, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_brightness_down_arr_day_img,&_day_down_arrow_20x11);
	lv_img_set_pivot(ui->Setting_Screen_brightness_down_arr_day_img, 0,0);
	lv_img_set_angle(ui->Setting_Screen_brightness_down_arr_day_img, 0);

	//Write codes Setting_Screen_brightness_day_L1
	ui->Setting_Screen_brightness_day_L1 = lv_label_create(ui->Setting_Screen_setting_brightness_day_contain);
	lv_obj_set_pos(ui->Setting_Screen_brightness_day_L1, 49, 100);
	lv_obj_set_size(ui->Setting_Screen_brightness_day_L1, 100, 18);
	lv_label_set_text(ui->Setting_Screen_brightness_day_L1, "");
	lv_label_set_long_mode(ui->Setting_Screen_brightness_day_L1, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->Setting_Screen_brightness_day_L1, LV_TEXT_ALIGN_LEFT, 0);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_brightness_day_l1_main_main_default
	static lv_style_t style_setting_screen_brightness_day_l1_main_main_default;
	lv_style_reset(&style_setting_screen_brightness_day_l1_main_main_default);
	lv_style_set_radius(&style_setting_screen_brightness_day_l1_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_brightness_day_l1_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_setting_screen_brightness_day_l1_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_setting_screen_brightness_day_l1_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_brightness_day_l1_main_main_default, 0);
	lv_style_set_text_color(&style_setting_screen_brightness_day_l1_main_main_default, lv_color_make(0xb8, 0xb8, 0xb8));
	lv_style_set_text_font(&style_setting_screen_brightness_day_l1_main_main_default, &lv_font_FjallaOne_Regular_22);
	lv_style_set_text_letter_space(&style_setting_screen_brightness_day_l1_main_main_default, 0);
	lv_style_set_pad_left(&style_setting_screen_brightness_day_l1_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_brightness_day_l1_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_brightness_day_l1_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_brightness_day_l1_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_brightness_day_L1, &style_setting_screen_brightness_day_l1_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_brightness_day_L2
	ui->Setting_Screen_brightness_day_L2 = lv_label_create(ui->Setting_Screen_setting_brightness_day_contain);
	lv_obj_set_pos(ui->Setting_Screen_brightness_day_L2, 49, 148);
	lv_obj_set_size(ui->Setting_Screen_brightness_day_L2, 100, 18);
	lv_label_set_text(ui->Setting_Screen_brightness_day_L2, "");
	lv_label_set_long_mode(ui->Setting_Screen_brightness_day_L2, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->Setting_Screen_brightness_day_L2, LV_TEXT_ALIGN_LEFT, 0);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_brightness_day_l2_main_main_default
	static lv_style_t style_setting_screen_brightness_day_l2_main_main_default;
	lv_style_reset(&style_setting_screen_brightness_day_l2_main_main_default);
	lv_style_set_radius(&style_setting_screen_brightness_day_l2_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_brightness_day_l2_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_setting_screen_brightness_day_l2_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_setting_screen_brightness_day_l2_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_brightness_day_l2_main_main_default, 0);
	lv_style_set_text_color(&style_setting_screen_brightness_day_l2_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_setting_screen_brightness_day_l2_main_main_default, &lv_font_FjallaOne_Regular_22);
	lv_style_set_text_letter_space(&style_setting_screen_brightness_day_l2_main_main_default, 0);
	lv_style_set_pad_left(&style_setting_screen_brightness_day_l2_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_brightness_day_l2_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_brightness_day_l2_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_brightness_day_l2_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_brightness_day_L2, &style_setting_screen_brightness_day_l2_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_brightness_day_L3
	ui->Setting_Screen_brightness_day_L3 = lv_label_create(ui->Setting_Screen_setting_brightness_day_contain);
	lv_obj_set_pos(ui->Setting_Screen_brightness_day_L3, 49, 196);
	lv_obj_set_size(ui->Setting_Screen_brightness_day_L3, 100, 18);
	lv_label_set_text(ui->Setting_Screen_brightness_day_L3, "");
	lv_label_set_long_mode(ui->Setting_Screen_brightness_day_L3, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->Setting_Screen_brightness_day_L3, LV_TEXT_ALIGN_LEFT, 0);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_brightness_day_l3_main_main_default
	static lv_style_t style_setting_screen_brightness_day_l3_main_main_default;
	lv_style_reset(&style_setting_screen_brightness_day_l3_main_main_default);
	lv_style_set_radius(&style_setting_screen_brightness_day_l3_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_brightness_day_l3_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_setting_screen_brightness_day_l3_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_setting_screen_brightness_day_l3_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_brightness_day_l3_main_main_default, 0);
	lv_style_set_text_color(&style_setting_screen_brightness_day_l3_main_main_default, lv_color_make(0xb8, 0xb8, 0xb8));
	lv_style_set_text_font(&style_setting_screen_brightness_day_l3_main_main_default, &lv_font_FjallaOne_Regular_22);
	lv_style_set_text_letter_space(&style_setting_screen_brightness_day_l3_main_main_default, 0);
	lv_style_set_pad_left(&style_setting_screen_brightness_day_l3_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_brightness_day_l3_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_brightness_day_l3_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_brightness_day_l3_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_brightness_day_L3, &style_setting_screen_brightness_day_l3_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_setting_menu_night_contain
	ui->Setting_Screen_setting_menu_night_contain = lv_obj_create(ui->Setting_Screen);
	lv_obj_set_pos(ui->Setting_Screen_setting_menu_night_contain, 0, 0);
	lv_obj_set_size(ui->Setting_Screen_setting_menu_night_contain, 240, 320);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_setting_menu_night_contain_main_main_default
	static lv_style_t style_setting_screen_setting_menu_night_contain_main_main_default;
	lv_style_reset(&style_setting_screen_setting_menu_night_contain_main_main_default);
	lv_style_set_radius(&style_setting_screen_setting_menu_night_contain_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_setting_menu_night_contain_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_color(&style_setting_screen_setting_menu_night_contain_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_dir(&style_setting_screen_setting_menu_night_contain_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_setting_menu_night_contain_main_main_default, 0);
	lv_style_set_border_color(&style_setting_screen_setting_menu_night_contain_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_border_width(&style_setting_screen_setting_menu_night_contain_main_main_default, 0);
	lv_style_set_border_opa(&style_setting_screen_setting_menu_night_contain_main_main_default, 255);
	lv_style_set_pad_left(&style_setting_screen_setting_menu_night_contain_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_setting_menu_night_contain_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_setting_menu_night_contain_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_setting_menu_night_contain_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_setting_menu_night_contain, &style_setting_screen_setting_menu_night_contain_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_menu_sel_btn1_img
	ui->Setting_Screen_menu_sel_btn1_img = lv_img_create(ui->Setting_Screen_setting_menu_night_contain);
	lv_obj_set_pos(ui->Setting_Screen_menu_sel_btn1_img, 178, 101);
	lv_obj_set_size(ui->Setting_Screen_menu_sel_btn1_img, 29, 20);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_menu_sel_btn1_img_main_main_default
	static lv_style_t style_setting_screen_menu_sel_btn1_img_main_main_default;
	lv_style_reset(&style_setting_screen_menu_sel_btn1_img_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_menu_sel_btn1_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_menu_sel_btn1_img_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_menu_sel_btn1_img_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_menu_sel_btn1_img, &style_setting_screen_menu_sel_btn1_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_menu_sel_btn1_img, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_menu_sel_btn1_img,&_radiobtn_night_unchecked_20x20);
	lv_img_set_pivot(ui->Setting_Screen_menu_sel_btn1_img, 0,0);
	lv_img_set_angle(ui->Setting_Screen_menu_sel_btn1_img, 0);

	//Write codes Setting_Screen_menu_sel_btn2_img
	ui->Setting_Screen_menu_sel_btn2_img = lv_img_create(ui->Setting_Screen_setting_menu_night_contain);
	lv_obj_set_pos(ui->Setting_Screen_menu_sel_btn2_img, 178, 149);
	lv_obj_set_size(ui->Setting_Screen_menu_sel_btn2_img, 29, 20);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_menu_sel_btn2_img_main_main_default
	static lv_style_t style_setting_screen_menu_sel_btn2_img_main_main_default;
	lv_style_reset(&style_setting_screen_menu_sel_btn2_img_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_menu_sel_btn2_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_menu_sel_btn2_img_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_menu_sel_btn2_img_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_menu_sel_btn2_img, &style_setting_screen_menu_sel_btn2_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_menu_sel_btn2_img, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_menu_sel_btn2_img,&_radiobtn_night_Checked_20x20);
	lv_img_set_pivot(ui->Setting_Screen_menu_sel_btn2_img, 0,0);
	lv_img_set_angle(ui->Setting_Screen_menu_sel_btn2_img, 0);

	//Write codes Setting_Screen_menu_sel_btn3_img
	ui->Setting_Screen_menu_sel_btn3_img = lv_img_create(ui->Setting_Screen_setting_menu_night_contain);
	lv_obj_set_pos(ui->Setting_Screen_menu_sel_btn3_img, 178, 198);
	lv_obj_set_size(ui->Setting_Screen_menu_sel_btn3_img, 29, 20);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_menu_sel_btn3_img_main_main_default
	static lv_style_t style_setting_screen_menu_sel_btn3_img_main_main_default;
	lv_style_reset(&style_setting_screen_menu_sel_btn3_img_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_menu_sel_btn3_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_menu_sel_btn3_img_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_menu_sel_btn3_img_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_menu_sel_btn3_img, &style_setting_screen_menu_sel_btn3_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_menu_sel_btn3_img, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_menu_sel_btn3_img,&_radiobtn_night_unchecked_20x20);
	lv_img_set_pivot(ui->Setting_Screen_menu_sel_btn3_img, 0,0);
	lv_img_set_angle(ui->Setting_Screen_menu_sel_btn3_img, 0);

	//Write codes Setting_Screen_menu_up_arr_day_img
	ui->Setting_Screen_menu_up_arr_day_img = lv_img_create(ui->Setting_Screen_setting_menu_night_contain);
	lv_obj_set_pos(ui->Setting_Screen_menu_up_arr_day_img, 110, 65);
	lv_obj_set_size(ui->Setting_Screen_menu_up_arr_day_img, 20, 11);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_menu_up_arr_day_img_main_main_default
	static lv_style_t style_setting_screen_menu_up_arr_day_img_main_main_default;
	lv_style_reset(&style_setting_screen_menu_up_arr_day_img_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_menu_up_arr_day_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_menu_up_arr_day_img_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_menu_up_arr_day_img_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_menu_up_arr_day_img, &style_setting_screen_menu_up_arr_day_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_menu_up_arr_day_img, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_menu_up_arr_day_img,&_Setting_Up_Arrow_20x11);
	lv_img_set_pivot(ui->Setting_Screen_menu_up_arr_day_img, 0,0);
	lv_img_set_angle(ui->Setting_Screen_menu_up_arr_day_img, 0);

	//Write codes Setting_Screen_menu_down_arr_day_img
	ui->Setting_Screen_menu_down_arr_day_img = lv_img_create(ui->Setting_Screen_setting_menu_night_contain);
	lv_obj_set_pos(ui->Setting_Screen_menu_down_arr_day_img, 110, 258);
	lv_obj_set_size(ui->Setting_Screen_menu_down_arr_day_img, 20, 11);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_menu_down_arr_day_img_main_main_default
	static lv_style_t style_setting_screen_menu_down_arr_day_img_main_main_default;
	lv_style_reset(&style_setting_screen_menu_down_arr_day_img_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_menu_down_arr_day_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_menu_down_arr_day_img_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_menu_down_arr_day_img_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_menu_down_arr_day_img, &style_setting_screen_menu_down_arr_day_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_menu_down_arr_day_img, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_menu_down_arr_day_img,&_Setting_Drow_Arrow_20x11);
	lv_img_set_pivot(ui->Setting_Screen_menu_down_arr_day_img, 0,0);
	lv_img_set_angle(ui->Setting_Screen_menu_down_arr_day_img, 0);

	//Write codes Setting_Screen_menu_night_L1
	ui->Setting_Screen_menu_night_L1 = lv_label_create(ui->Setting_Screen_setting_menu_night_contain);
	lv_obj_set_pos(ui->Setting_Screen_menu_night_L1, 49, 100);
	lv_obj_set_size(ui->Setting_Screen_menu_night_L1, 130, 18);
	lv_label_set_text(ui->Setting_Screen_menu_night_L1, "");
	lv_label_set_long_mode(ui->Setting_Screen_menu_night_L1, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->Setting_Screen_menu_night_L1, LV_TEXT_ALIGN_LEFT, 0);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_menu_night_l1_main_main_default
	static lv_style_t style_setting_screen_menu_night_l1_main_main_default;
	lv_style_reset(&style_setting_screen_menu_night_l1_main_main_default);
	lv_style_set_radius(&style_setting_screen_menu_night_l1_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_menu_night_l1_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_setting_screen_menu_night_l1_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_setting_screen_menu_night_l1_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_menu_night_l1_main_main_default, 0);
	lv_style_set_text_color(&style_setting_screen_menu_night_l1_main_main_default, lv_color_make(0x50, 0x50, 0x50));
	lv_style_set_text_font(&style_setting_screen_menu_night_l1_main_main_default, &lv_font_FjallaOne_Regular_22);
	lv_style_set_text_letter_space(&style_setting_screen_menu_night_l1_main_main_default, 0);
	lv_style_set_pad_left(&style_setting_screen_menu_night_l1_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_menu_night_l1_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_menu_night_l1_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_menu_night_l1_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_menu_night_L1, &style_setting_screen_menu_night_l1_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_menu_night_L2
	ui->Setting_Screen_menu_night_L2 = lv_label_create(ui->Setting_Screen_setting_menu_night_contain);
	lv_obj_set_pos(ui->Setting_Screen_menu_night_L2, 49, 148);
	lv_obj_set_size(ui->Setting_Screen_menu_night_L2, 130, 18);
	lv_label_set_text(ui->Setting_Screen_menu_night_L2, "");
	lv_label_set_long_mode(ui->Setting_Screen_menu_night_L2, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->Setting_Screen_menu_night_L2, LV_TEXT_ALIGN_LEFT, 0);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_menu_night_l2_main_main_default
	static lv_style_t style_setting_screen_menu_night_l2_main_main_default;
	lv_style_reset(&style_setting_screen_menu_night_l2_main_main_default);
	lv_style_set_radius(&style_setting_screen_menu_night_l2_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_menu_night_l2_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_setting_screen_menu_night_l2_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_setting_screen_menu_night_l2_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_menu_night_l2_main_main_default, 0);
	lv_style_set_text_color(&style_setting_screen_menu_night_l2_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_setting_screen_menu_night_l2_main_main_default, &lv_font_FjallaOne_Regular_22);
	lv_style_set_text_letter_space(&style_setting_screen_menu_night_l2_main_main_default, 0);
	lv_style_set_pad_left(&style_setting_screen_menu_night_l2_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_menu_night_l2_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_menu_night_l2_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_menu_night_l2_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_menu_night_L2, &style_setting_screen_menu_night_l2_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_menu_night_L3
	ui->Setting_Screen_menu_night_L3 = lv_label_create(ui->Setting_Screen_setting_menu_night_contain);
	lv_obj_set_pos(ui->Setting_Screen_menu_night_L3, 49, 196);
	lv_obj_set_size(ui->Setting_Screen_menu_night_L3, 130, 18);
	lv_label_set_text(ui->Setting_Screen_menu_night_L3, "");
	lv_label_set_long_mode(ui->Setting_Screen_menu_night_L3, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->Setting_Screen_menu_night_L3, LV_TEXT_ALIGN_LEFT, 0);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_menu_night_l3_main_main_default
	static lv_style_t style_setting_screen_menu_night_l3_main_main_default;
	lv_style_reset(&style_setting_screen_menu_night_l3_main_main_default);
	lv_style_set_radius(&style_setting_screen_menu_night_l3_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_menu_night_l3_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_setting_screen_menu_night_l3_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_setting_screen_menu_night_l3_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_menu_night_l3_main_main_default, 0);
	lv_style_set_text_color(&style_setting_screen_menu_night_l3_main_main_default, lv_color_make(0x50, 0x50, 0x50));
	lv_style_set_text_font(&style_setting_screen_menu_night_l3_main_main_default, &lv_font_FjallaOne_Regular_22);
	lv_style_set_text_letter_space(&style_setting_screen_menu_night_l3_main_main_default, 0);
	lv_style_set_pad_left(&style_setting_screen_menu_night_l3_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_menu_night_l3_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_menu_night_l3_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_menu_night_l3_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_menu_night_L3, &style_setting_screen_menu_night_l3_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_setting_menu_day_contain
	ui->Setting_Screen_setting_menu_day_contain = lv_obj_create(ui->Setting_Screen);
	lv_obj_set_pos(ui->Setting_Screen_setting_menu_day_contain, 0, 0);
	lv_obj_set_size(ui->Setting_Screen_setting_menu_day_contain, 240, 320);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_setting_menu_day_contain_main_main_default
	static lv_style_t style_setting_screen_setting_menu_day_contain_main_main_default;
	lv_style_reset(&style_setting_screen_setting_menu_day_contain_main_main_default);
	lv_style_set_radius(&style_setting_screen_setting_menu_day_contain_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_setting_menu_day_contain_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_color(&style_setting_screen_setting_menu_day_contain_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_dir(&style_setting_screen_setting_menu_day_contain_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_setting_menu_day_contain_main_main_default, 0);
	lv_style_set_border_color(&style_setting_screen_setting_menu_day_contain_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_border_width(&style_setting_screen_setting_menu_day_contain_main_main_default, 0);
	lv_style_set_border_opa(&style_setting_screen_setting_menu_day_contain_main_main_default, 255);
	lv_style_set_pad_left(&style_setting_screen_setting_menu_day_contain_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_setting_menu_day_contain_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_setting_menu_day_contain_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_setting_menu_day_contain_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_setting_menu_day_contain, &style_setting_screen_setting_menu_day_contain_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_menu_day_circle_img
	ui->Setting_Screen_menu_day_circle_img = lv_img_create(ui->Setting_Screen_setting_menu_day_contain);
	lv_obj_set_pos(ui->Setting_Screen_menu_day_circle_img, 7, 47);
	lv_obj_set_size(ui->Setting_Screen_menu_day_circle_img, 226, 226);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_menu_day_circle_img_main_main_default
	static lv_style_t style_setting_screen_menu_day_circle_img_main_main_default;
	lv_style_reset(&style_setting_screen_menu_day_circle_img_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_menu_day_circle_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_menu_day_circle_img_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_menu_day_circle_img_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_menu_day_circle_img, &style_setting_screen_menu_day_circle_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_menu_day_circle_img, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_menu_day_circle_img,&day_white_Grey_circle);
	lv_img_set_pivot(ui->Setting_Screen_menu_day_circle_img, 0,0);
	lv_img_set_angle(ui->Setting_Screen_menu_day_circle_img, 0);

	//Write codes Setting_Screen_menu_sel_day_btn1_img
	ui->Setting_Screen_menu_sel_day_btn1_img = lv_img_create(ui->Setting_Screen_setting_menu_day_contain);
	lv_obj_set_pos(ui->Setting_Screen_menu_sel_day_btn1_img, 176, 101);
	lv_obj_set_size(ui->Setting_Screen_menu_sel_day_btn1_img, 29, 20);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_menu_sel_day_btn1_img_main_main_default
	static lv_style_t style_setting_screen_menu_sel_day_btn1_img_main_main_default;
	lv_style_reset(&style_setting_screen_menu_sel_day_btn1_img_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_menu_sel_day_btn1_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_menu_sel_day_btn1_img_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_menu_sel_day_btn1_img_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_menu_sel_day_btn1_img, &style_setting_screen_menu_sel_day_btn1_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_menu_sel_day_btn1_img, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_menu_sel_day_btn1_img,&_radiobtn_day_unchecked_20x20);
	lv_img_set_pivot(ui->Setting_Screen_menu_sel_day_btn1_img, 0,0);
	lv_img_set_angle(ui->Setting_Screen_menu_sel_day_btn1_img, 0);

	//Write codes Setting_Screen_menu_sel_day_btn2_img
	ui->Setting_Screen_menu_sel_day_btn2_img = lv_img_create(ui->Setting_Screen_setting_menu_day_contain);
	lv_obj_set_pos(ui->Setting_Screen_menu_sel_day_btn2_img, 176, 150);
	lv_obj_set_size(ui->Setting_Screen_menu_sel_day_btn2_img, 29, 20);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_menu_sel_day_btn2_img_main_main_default
	static lv_style_t style_setting_screen_menu_sel_day_btn2_img_main_main_default;
	lv_style_reset(&style_setting_screen_menu_sel_day_btn2_img_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_menu_sel_day_btn2_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_menu_sel_day_btn2_img_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_menu_sel_day_btn2_img_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_menu_sel_day_btn2_img, &style_setting_screen_menu_sel_day_btn2_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_menu_sel_day_btn2_img, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_menu_sel_day_btn2_img,&_radiobtn_day_checked_20x20);
	lv_img_set_pivot(ui->Setting_Screen_menu_sel_day_btn2_img, 0,0);
	lv_img_set_angle(ui->Setting_Screen_menu_sel_day_btn2_img, 0);

	//Write codes Setting_Screen_menu_sel_day_btn3_img
	ui->Setting_Screen_menu_sel_day_btn3_img = lv_img_create(ui->Setting_Screen_setting_menu_day_contain);
	lv_obj_set_pos(ui->Setting_Screen_menu_sel_day_btn3_img, 176, 198);
	lv_obj_set_size(ui->Setting_Screen_menu_sel_day_btn3_img, 29, 20);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_menu_sel_day_btn3_img_main_main_default
	static lv_style_t style_setting_screen_menu_sel_day_btn3_img_main_main_default;
	lv_style_reset(&style_setting_screen_menu_sel_day_btn3_img_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_menu_sel_day_btn3_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_menu_sel_day_btn3_img_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_menu_sel_day_btn3_img_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_menu_sel_day_btn3_img, &style_setting_screen_menu_sel_day_btn3_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_menu_sel_day_btn3_img, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_menu_sel_day_btn3_img,&_radiobtn_day_unchecked_20x20);
	lv_img_set_pivot(ui->Setting_Screen_menu_sel_day_btn3_img, 0,0);
	lv_img_set_angle(ui->Setting_Screen_menu_sel_day_btn3_img, 0);

	//Write codes Setting_Screen_menu_up_darr_day_img
	ui->Setting_Screen_menu_up_darr_day_img = lv_img_create(ui->Setting_Screen_setting_menu_day_contain);
	lv_obj_set_pos(ui->Setting_Screen_menu_up_darr_day_img, 110, 65);
	lv_obj_set_size(ui->Setting_Screen_menu_up_darr_day_img, 20, 11);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_menu_up_darr_day_img_main_main_default
	static lv_style_t style_setting_screen_menu_up_darr_day_img_main_main_default;
	lv_style_reset(&style_setting_screen_menu_up_darr_day_img_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_menu_up_darr_day_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_menu_up_darr_day_img_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_menu_up_darr_day_img_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_menu_up_darr_day_img, &style_setting_screen_menu_up_darr_day_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_menu_up_darr_day_img, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_menu_up_darr_day_img,&_day_up_arrow_20x11);
	lv_img_set_pivot(ui->Setting_Screen_menu_up_darr_day_img, 0,0);
	lv_img_set_angle(ui->Setting_Screen_menu_up_darr_day_img, 0);

	//Write codes Setting_Screen_menu_down_darr_day_img
	ui->Setting_Screen_menu_down_darr_day_img = lv_img_create(ui->Setting_Screen_setting_menu_day_contain);
	lv_obj_set_pos(ui->Setting_Screen_menu_down_darr_day_img, 110, 245);
	lv_obj_set_size(ui->Setting_Screen_menu_down_darr_day_img, 20, 11);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_menu_down_darr_day_img_main_main_default
	static lv_style_t style_setting_screen_menu_down_darr_day_img_main_main_default;
	lv_style_reset(&style_setting_screen_menu_down_darr_day_img_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_menu_down_darr_day_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_menu_down_darr_day_img_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_menu_down_darr_day_img_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_menu_down_darr_day_img, &style_setting_screen_menu_down_darr_day_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_menu_down_darr_day_img, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_menu_down_darr_day_img,&_day_down_arrow_20x11);
	lv_img_set_pivot(ui->Setting_Screen_menu_down_darr_day_img, 0,0);
	lv_img_set_angle(ui->Setting_Screen_menu_down_darr_day_img, 0);

	//Write codes Setting_Screen_menu_day_L1
	ui->Setting_Screen_menu_day_L1 = lv_label_create(ui->Setting_Screen_setting_menu_day_contain);
	lv_obj_set_pos(ui->Setting_Screen_menu_day_L1, 49, 100);
	lv_obj_set_size(ui->Setting_Screen_menu_day_L1, 130, 18);
	lv_label_set_text(ui->Setting_Screen_menu_day_L1, "");
	lv_label_set_long_mode(ui->Setting_Screen_menu_day_L1, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->Setting_Screen_menu_day_L1, LV_TEXT_ALIGN_LEFT, 0);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_menu_day_l1_main_main_default
	static lv_style_t style_setting_screen_menu_day_l1_main_main_default;
	lv_style_reset(&style_setting_screen_menu_day_l1_main_main_default);
	lv_style_set_radius(&style_setting_screen_menu_day_l1_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_menu_day_l1_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_setting_screen_menu_day_l1_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_setting_screen_menu_day_l1_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_menu_day_l1_main_main_default, 0);
	lv_style_set_text_color(&style_setting_screen_menu_day_l1_main_main_default, lv_color_make(0xb8, 0xb8, 0xb8));
	lv_style_set_text_font(&style_setting_screen_menu_day_l1_main_main_default, &lv_font_FjallaOne_Regular_22);
	lv_style_set_text_letter_space(&style_setting_screen_menu_day_l1_main_main_default, 0);
	lv_style_set_pad_left(&style_setting_screen_menu_day_l1_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_menu_day_l1_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_menu_day_l1_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_menu_day_l1_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_menu_day_L1, &style_setting_screen_menu_day_l1_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_menu_day_L2
	ui->Setting_Screen_menu_day_L2 = lv_label_create(ui->Setting_Screen_setting_menu_day_contain);
	lv_obj_set_pos(ui->Setting_Screen_menu_day_L2, 49, 148);
	lv_obj_set_size(ui->Setting_Screen_menu_day_L2, 130, 18);
	lv_label_set_text(ui->Setting_Screen_menu_day_L2, "");
	lv_label_set_long_mode(ui->Setting_Screen_menu_day_L2, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->Setting_Screen_menu_day_L2, LV_TEXT_ALIGN_LEFT, 0);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_menu_day_l2_main_main_default
	static lv_style_t style_setting_screen_menu_day_l2_main_main_default;
	lv_style_reset(&style_setting_screen_menu_day_l2_main_main_default);
	lv_style_set_radius(&style_setting_screen_menu_day_l2_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_menu_day_l2_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_setting_screen_menu_day_l2_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_setting_screen_menu_day_l2_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_menu_day_l2_main_main_default, 0);
	lv_style_set_text_color(&style_setting_screen_menu_day_l2_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_setting_screen_menu_day_l2_main_main_default, &lv_font_FjallaOne_Regular_22);
	lv_style_set_text_letter_space(&style_setting_screen_menu_day_l2_main_main_default, 0);
	lv_style_set_pad_left(&style_setting_screen_menu_day_l2_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_menu_day_l2_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_menu_day_l2_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_menu_day_l2_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_menu_day_L2, &style_setting_screen_menu_day_l2_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_menu_day_L3
	ui->Setting_Screen_menu_day_L3 = lv_label_create(ui->Setting_Screen_setting_menu_day_contain);
	lv_obj_set_pos(ui->Setting_Screen_menu_day_L3, 49, 196);
	lv_obj_set_size(ui->Setting_Screen_menu_day_L3, 130, 18);
	lv_label_set_text(ui->Setting_Screen_menu_day_L3, "");
	lv_label_set_long_mode(ui->Setting_Screen_menu_day_L3, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->Setting_Screen_menu_day_L3, LV_TEXT_ALIGN_LEFT, 0);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_menu_day_l3_main_main_default
	static lv_style_t style_setting_screen_menu_day_l3_main_main_default;
	lv_style_reset(&style_setting_screen_menu_day_l3_main_main_default);
	lv_style_set_radius(&style_setting_screen_menu_day_l3_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_menu_day_l3_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_setting_screen_menu_day_l3_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_setting_screen_menu_day_l3_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_menu_day_l3_main_main_default, 0);
	lv_style_set_text_color(&style_setting_screen_menu_day_l3_main_main_default, lv_color_make(0xb8, 0xb8, 0xb8));
	lv_style_set_text_font(&style_setting_screen_menu_day_l3_main_main_default, &lv_font_FjallaOne_Regular_22);
	lv_style_set_text_letter_space(&style_setting_screen_menu_day_l3_main_main_default, 0);
	lv_style_set_pad_left(&style_setting_screen_menu_day_l3_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_menu_day_l3_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_menu_day_l3_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_menu_day_l3_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_menu_day_L3, &style_setting_screen_menu_day_l3_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);


	//Write codes Setting_Screen_seting_date_time_container
	ui->Setting_Screen_seting_date_time_container = lv_obj_create(ui->Setting_Screen);
	lv_obj_set_pos(ui->Setting_Screen_seting_date_time_container, 0, 0);
	lv_obj_set_size(ui->Setting_Screen_seting_date_time_container, 240, 320);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_seting_date_time_container_main_main_default
	static lv_style_t style_setting_screen_seting_date_time_container_main_main_default;
	lv_style_reset(&style_setting_screen_seting_date_time_container_main_main_default);
	lv_style_set_radius(&style_setting_screen_seting_date_time_container_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_seting_date_time_container_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_color(&style_setting_screen_seting_date_time_container_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_dir(&style_setting_screen_seting_date_time_container_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_seting_date_time_container_main_main_default, 0);
	lv_style_set_border_color(&style_setting_screen_seting_date_time_container_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_border_width(&style_setting_screen_seting_date_time_container_main_main_default, 0);
	lv_style_set_border_opa(&style_setting_screen_seting_date_time_container_main_main_default, 255);
	lv_style_set_pad_left(&style_setting_screen_seting_date_time_container_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_seting_date_time_container_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_seting_date_time_container_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_seting_date_time_container_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_seting_date_time_container, &style_setting_screen_seting_date_time_container_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_data_time_night_icon_img
	ui->Setting_Screen_data_time_night_icon_img = lv_img_create(ui->Setting_Screen_seting_date_time_container);
	lv_obj_set_pos(ui->Setting_Screen_data_time_night_icon_img, 16, 142);
	lv_obj_set_size(ui->Setting_Screen_data_time_night_icon_img, 40, 40);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_data_time_night_icon_img_main_main_default
	static lv_style_t style_setting_screen_data_time_night_icon_img_main_main_default;
	lv_style_reset(&style_setting_screen_data_time_night_icon_img_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_data_time_night_icon_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_data_time_night_icon_img_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_data_time_night_icon_img_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_data_time_night_icon_img, &style_setting_screen_data_time_night_icon_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_data_time_night_sub_button_img
	ui->Setting_Screen_data_time_night_sub_button_img = lv_img_create(ui->Setting_Screen_seting_date_time_container);
	lv_obj_set_pos(ui->Setting_Screen_data_time_night_sub_button_img, 196, 149);
	lv_obj_set_size(ui->Setting_Screen_data_time_night_sub_button_img, 24, 24);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_data_time_night_sub_button_img_main_main_default
	static lv_style_t style_setting_screen_data_time_night_sub_button_img_main_main_default;
	lv_style_reset(&style_setting_screen_data_time_night_sub_button_img_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_data_time_night_sub_button_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_data_time_night_sub_button_img_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_data_time_night_sub_button_img_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_data_time_night_sub_button_img, &style_setting_screen_data_time_night_sub_button_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_data_time_night_sub_button_img, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_data_time_night_sub_button_img,&subbtn_night_24x24);
	lv_img_set_pivot(ui->Setting_Screen_data_time_night_sub_button_img, 0,0);
	lv_img_set_angle(ui->Setting_Screen_data_time_night_sub_button_img, 0);

	//Write codes Setting_Screen_data_time_night_toggl_btn
	ui->Setting_Screen_data_time_night_toggl_btn = lv_img_create(ui->Setting_Screen_seting_date_time_container);
	lv_obj_set_pos(ui->Setting_Screen_data_time_night_toggl_btn, 179, 230);
	lv_obj_set_size(ui->Setting_Screen_data_time_night_toggl_btn, 29, 20);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_data_time_night_toggl_btn_main_main_default
	static lv_style_t style_setting_screen_data_time_night_toggl_btn_main_main_default;
	lv_style_reset(&style_setting_screen_data_time_night_toggl_btn_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_data_time_night_toggl_btn_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_data_time_night_toggl_btn_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_data_time_night_toggl_btn_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_data_time_night_toggl_btn, &style_setting_screen_data_time_night_toggl_btn_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_data_time_night_toggl_btn, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_data_time_night_toggl_btn,&_day_toogle_on_29x20);
	lv_img_set_pivot(ui->Setting_Screen_data_time_night_toggl_btn, 0,0);
	lv_img_set_angle(ui->Setting_Screen_data_time_night_toggl_btn, 0);

	//Write codes Setting_Screen_data_time_up_arr_nigh_button_img
	ui->Setting_Screen_data_time_up_arr_nigh_button_img = lv_img_create(ui->Setting_Screen_seting_date_time_container);
	lv_obj_set_pos(ui->Setting_Screen_data_time_up_arr_nigh_button_img, 110, 65);
	lv_obj_set_size(ui->Setting_Screen_data_time_up_arr_nigh_button_img, 20, 11);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_data_time_up_arr_nigh_button_img_main_main_default
	static lv_style_t style_setting_screen_data_time_up_arr_nigh_button_img_main_main_default;
	lv_style_reset(&style_setting_screen_data_time_up_arr_nigh_button_img_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_data_time_up_arr_nigh_button_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_data_time_up_arr_nigh_button_img_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_data_time_up_arr_nigh_button_img_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_data_time_up_arr_nigh_button_img, &style_setting_screen_data_time_up_arr_nigh_button_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_data_time_up_arr_nigh_button_img, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_data_time_up_arr_nigh_button_img,&_Setting_Up_Arrow_20x11);
	lv_img_set_pivot(ui->Setting_Screen_data_time_up_arr_nigh_button_img, 0,0);
	lv_img_set_angle(ui->Setting_Screen_data_time_up_arr_nigh_button_img, 0);

	//Write codes Setting_Screen_data_time_do_arr_nigh_button_img
	ui->Setting_Screen_data_time_do_arr_nigh_button_img = lv_img_create(ui->Setting_Screen_seting_date_time_container);
	lv_obj_set_pos(ui->Setting_Screen_data_time_do_arr_nigh_button_img, 110, 238);
	lv_obj_set_size(ui->Setting_Screen_data_time_do_arr_nigh_button_img, 20, 11);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_data_time_do_arr_nigh_button_img_main_main_default
	static lv_style_t style_setting_screen_data_time_do_arr_nigh_button_img_main_main_default;
	lv_style_reset(&style_setting_screen_data_time_do_arr_nigh_button_img_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_data_time_do_arr_nigh_button_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_data_time_do_arr_nigh_button_img_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_data_time_do_arr_nigh_button_img_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_data_time_do_arr_nigh_button_img, &style_setting_screen_data_time_do_arr_nigh_button_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_data_time_do_arr_nigh_button_img, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_data_time_do_arr_nigh_button_img,&_Setting_Drow_Arrow_20x11);
	lv_img_set_pivot(ui->Setting_Screen_data_time_do_arr_nigh_button_img, 0,0);
	lv_img_set_angle(ui->Setting_Screen_data_time_do_arr_nigh_button_img, 0);

	//Write codes Setting_Screen_data_time_do_arr_nigh_LB1
	ui->Setting_Screen_data_time_do_arr_nigh_LB1 = lv_label_create(ui->Setting_Screen_seting_date_time_container);
	lv_obj_set_pos(ui->Setting_Screen_data_time_do_arr_nigh_LB1, 49, 100);
	lv_obj_set_size(ui->Setting_Screen_data_time_do_arr_nigh_LB1, 126, 18);
	lv_label_set_text(ui->Setting_Screen_data_time_do_arr_nigh_LB1, "");
	lv_label_set_long_mode(ui->Setting_Screen_data_time_do_arr_nigh_LB1, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->Setting_Screen_data_time_do_arr_nigh_LB1, LV_TEXT_ALIGN_LEFT, 0);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_data_time_do_arr_nigh_lb1_main_main_default
	static lv_style_t style_setting_screen_data_time_do_arr_nigh_lb1_main_main_default;
	lv_style_reset(&style_setting_screen_data_time_do_arr_nigh_lb1_main_main_default);
	lv_style_set_radius(&style_setting_screen_data_time_do_arr_nigh_lb1_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_data_time_do_arr_nigh_lb1_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_setting_screen_data_time_do_arr_nigh_lb1_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_setting_screen_data_time_do_arr_nigh_lb1_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_data_time_do_arr_nigh_lb1_main_main_default, 0);
	lv_style_set_text_color(&style_setting_screen_data_time_do_arr_nigh_lb1_main_main_default, lv_color_make(0x50, 0x50, 0x50));
	lv_style_set_text_font(&style_setting_screen_data_time_do_arr_nigh_lb1_main_main_default, &lv_font_FjallaOne_Regular_22);
	lv_style_set_text_letter_space(&style_setting_screen_data_time_do_arr_nigh_lb1_main_main_default, 0);
	lv_style_set_pad_left(&style_setting_screen_data_time_do_arr_nigh_lb1_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_data_time_do_arr_nigh_lb1_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_data_time_do_arr_nigh_lb1_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_data_time_do_arr_nigh_lb1_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_data_time_do_arr_nigh_LB1, &style_setting_screen_data_time_do_arr_nigh_lb1_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_data_time_do_arr_nigh_LB2
	ui->Setting_Screen_data_time_do_arr_nigh_LB2 = lv_label_create(ui->Setting_Screen_seting_date_time_container);
	lv_obj_set_pos(ui->Setting_Screen_data_time_do_arr_nigh_LB2, 49, 148);
	lv_obj_set_size(ui->Setting_Screen_data_time_do_arr_nigh_LB2, 126, 18);
	lv_label_set_text(ui->Setting_Screen_data_time_do_arr_nigh_LB2, "");
	lv_label_set_long_mode(ui->Setting_Screen_data_time_do_arr_nigh_LB2, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->Setting_Screen_data_time_do_arr_nigh_LB2, LV_TEXT_ALIGN_LEFT, 0);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_data_time_do_arr_nigh_lb2_main_main_default
	static lv_style_t style_setting_screen_data_time_do_arr_nigh_lb2_main_main_default;
	lv_style_reset(&style_setting_screen_data_time_do_arr_nigh_lb2_main_main_default);
	lv_style_set_radius(&style_setting_screen_data_time_do_arr_nigh_lb2_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_data_time_do_arr_nigh_lb2_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_setting_screen_data_time_do_arr_nigh_lb2_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_setting_screen_data_time_do_arr_nigh_lb2_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_data_time_do_arr_nigh_lb2_main_main_default, 0);
	lv_style_set_text_color(&style_setting_screen_data_time_do_arr_nigh_lb2_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_setting_screen_data_time_do_arr_nigh_lb2_main_main_default, &lv_font_FjallaOne_Regular_22);
	lv_style_set_text_letter_space(&style_setting_screen_data_time_do_arr_nigh_lb2_main_main_default, 0);
	lv_style_set_pad_left(&style_setting_screen_data_time_do_arr_nigh_lb2_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_data_time_do_arr_nigh_lb2_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_data_time_do_arr_nigh_lb2_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_data_time_do_arr_nigh_lb2_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_data_time_do_arr_nigh_LB2, &style_setting_screen_data_time_do_arr_nigh_lb2_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_data_time_do_arr_nigh_LB3
	ui->Setting_Screen_data_time_do_arr_nigh_LB3 = lv_label_create(ui->Setting_Screen_seting_date_time_container);
	lv_obj_set_pos(ui->Setting_Screen_data_time_do_arr_nigh_LB3, 49, 196);
	lv_obj_set_size(ui->Setting_Screen_data_time_do_arr_nigh_LB3, 126, 18);
	lv_label_set_text(ui->Setting_Screen_data_time_do_arr_nigh_LB3, "");
	lv_label_set_long_mode(ui->Setting_Screen_data_time_do_arr_nigh_LB3, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->Setting_Screen_data_time_do_arr_nigh_LB3, LV_TEXT_ALIGN_LEFT, 0);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_data_time_do_arr_nigh_lb3_main_main_default
	static lv_style_t style_setting_screen_data_time_do_arr_nigh_lb3_main_main_default;
	lv_style_reset(&style_setting_screen_data_time_do_arr_nigh_lb3_main_main_default);
	lv_style_set_radius(&style_setting_screen_data_time_do_arr_nigh_lb3_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_data_time_do_arr_nigh_lb3_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_setting_screen_data_time_do_arr_nigh_lb3_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_setting_screen_data_time_do_arr_nigh_lb3_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_data_time_do_arr_nigh_lb3_main_main_default, 0);
	lv_style_set_text_color(&style_setting_screen_data_time_do_arr_nigh_lb3_main_main_default, lv_color_make(0x50, 0x50, 0x50));
	lv_style_set_text_font(&style_setting_screen_data_time_do_arr_nigh_lb3_main_main_default, &lv_font_FjallaOne_Regular_22);
	lv_style_set_text_letter_space(&style_setting_screen_data_time_do_arr_nigh_lb3_main_main_default, 0);
	lv_style_set_pad_left(&style_setting_screen_data_time_do_arr_nigh_lb3_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_data_time_do_arr_nigh_lb3_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_data_time_do_arr_nigh_lb3_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_data_time_do_arr_nigh_lb3_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_data_time_do_arr_nigh_LB3, &style_setting_screen_data_time_do_arr_nigh_lb3_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_seting_date_time_day_container
	ui->Setting_Screen_seting_date_time_day_container = lv_obj_create(ui->Setting_Screen);
	lv_obj_set_pos(ui->Setting_Screen_seting_date_time_day_container, 0, 0);
	lv_obj_set_size(ui->Setting_Screen_seting_date_time_day_container, 240, 320);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_seting_date_time_day_container_main_main_default
	static lv_style_t style_setting_screen_seting_date_time_day_container_main_main_default;
	lv_style_reset(&style_setting_screen_seting_date_time_day_container_main_main_default);
	lv_style_set_radius(&style_setting_screen_seting_date_time_day_container_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_seting_date_time_day_container_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_color(&style_setting_screen_seting_date_time_day_container_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_dir(&style_setting_screen_seting_date_time_day_container_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_seting_date_time_day_container_main_main_default, 0);
	lv_style_set_border_color(&style_setting_screen_seting_date_time_day_container_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_border_width(&style_setting_screen_seting_date_time_day_container_main_main_default, 0);
	lv_style_set_border_opa(&style_setting_screen_seting_date_time_day_container_main_main_default, 255);
	lv_style_set_pad_left(&style_setting_screen_seting_date_time_day_container_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_seting_date_time_day_container_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_seting_date_time_day_container_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_seting_date_time_day_container_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_seting_date_time_day_container, &style_setting_screen_seting_date_time_day_container_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_date_day_circle_img
	ui->Setting_Screen_date_day_circle_img = lv_img_create(ui->Setting_Screen_seting_date_time_day_container);
	lv_obj_set_pos(ui->Setting_Screen_date_day_circle_img, 7, 47);
	lv_obj_set_size(ui->Setting_Screen_date_day_circle_img, 226, 226);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_date_day_circle_img_main_main_default
	static lv_style_t style_setting_screen_date_day_circle_img_main_main_default;
	lv_style_reset(&style_setting_screen_date_day_circle_img_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_date_day_circle_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_date_day_circle_img_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_date_day_circle_img_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_date_day_circle_img, &style_setting_screen_date_day_circle_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_date_day_circle_img, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_date_day_circle_img,&day_white_Grey_circle);
	lv_img_set_pivot(ui->Setting_Screen_date_day_circle_img, 0,0);
	lv_img_set_angle(ui->Setting_Screen_date_day_circle_img, 0);

	//Write codes Setting_Screen_date_side_day_img
	ui->Setting_Screen_date_side_day_img = lv_img_create(ui->Setting_Screen_seting_date_time_day_container);
	lv_obj_set_pos(ui->Setting_Screen_date_side_day_img, 16, 142);
	lv_obj_set_size(ui->Setting_Screen_date_side_day_img, 40, 40);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_date_side_day_img_main_main_default
	static lv_style_t style_setting_screen_date_side_day_img_main_main_default;
	lv_style_reset(&style_setting_screen_date_side_day_img_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_date_side_day_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_date_side_day_img_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_date_side_day_img_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_date_side_day_img, &style_setting_screen_date_side_day_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_date_sub_btn_day_img
	ui->Setting_Screen_date_sub_btn_day_img = lv_img_create(ui->Setting_Screen_seting_date_time_day_container);
	lv_obj_set_pos(ui->Setting_Screen_date_sub_btn_day_img, 196, 149);
	lv_obj_set_size(ui->Setting_Screen_date_sub_btn_day_img, 24, 24);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_date_sub_btn_day_img_main_main_default
	static lv_style_t style_setting_screen_date_sub_btn_day_img_main_main_default;
	lv_style_reset(&style_setting_screen_date_sub_btn_day_img_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_date_sub_btn_day_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_date_sub_btn_day_img_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_date_sub_btn_day_img_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_date_sub_btn_day_img, &style_setting_screen_date_sub_btn_day_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_date_sub_btn_day_img, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_date_sub_btn_day_img,&subbtn_day_24x24);
	lv_img_set_pivot(ui->Setting_Screen_date_sub_btn_day_img, 0,0);
	lv_img_set_angle(ui->Setting_Screen_date_sub_btn_day_img, 0);

	//Write codes Setting_Screen_data_time_day_toggl_btn
	ui->Setting_Screen_data_time_day_toggl_btn = lv_img_create(ui->Setting_Screen_seting_date_time_day_container);
	lv_obj_set_pos(ui->Setting_Screen_data_time_day_toggl_btn, 149, 170);
	lv_obj_set_size(ui->Setting_Screen_data_time_day_toggl_btn, 29, 20);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_data_time_day_toggl_btn_main_main_default
	static lv_style_t style_setting_screen_data_time_day_toggl_btn_main_main_default;
	lv_style_reset(&style_setting_screen_data_time_day_toggl_btn_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_data_time_day_toggl_btn_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_data_time_day_toggl_btn_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_data_time_day_toggl_btn_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_data_time_day_toggl_btn, &style_setting_screen_data_time_day_toggl_btn_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_data_time_day_toggl_btn, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_data_time_day_toggl_btn,&_day_toogle_on_29x20);
	lv_img_set_pivot(ui->Setting_Screen_data_time_day_toggl_btn, 0,0);
	lv_img_set_angle(ui->Setting_Screen_data_time_day_toggl_btn, 0);

	//Write codes Setting_Screen_data_time_up_arr_day_button_img
	ui->Setting_Screen_data_time_up_arr_day_button_img = lv_img_create(ui->Setting_Screen_seting_date_time_day_container);
	lv_obj_set_pos(ui->Setting_Screen_data_time_up_arr_day_button_img, 110, 65);
	lv_obj_set_size(ui->Setting_Screen_data_time_up_arr_day_button_img, 20, 11);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_data_time_up_arr_day_button_img_main_main_default
	static lv_style_t style_setting_screen_data_time_up_arr_day_button_img_main_main_default;
	lv_style_reset(&style_setting_screen_data_time_up_arr_day_button_img_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_data_time_up_arr_day_button_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_data_time_up_arr_day_button_img_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_data_time_up_arr_day_button_img_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_data_time_up_arr_day_button_img, &style_setting_screen_data_time_up_arr_day_button_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_data_time_up_arr_day_button_img, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_data_time_up_arr_day_button_img,&_day_up_arrow_20x11);
	lv_img_set_pivot(ui->Setting_Screen_data_time_up_arr_day_button_img, 0,0);
	lv_img_set_angle(ui->Setting_Screen_data_time_up_arr_day_button_img, 0);

	//Write codes Setting_Screen_data_time_dow_arr_day_button_img
	ui->Setting_Screen_data_time_dow_arr_day_button_img = lv_img_create(ui->Setting_Screen_seting_date_time_day_container);
	lv_obj_set_pos(ui->Setting_Screen_data_time_dow_arr_day_button_img, 110, 238);
	lv_obj_set_size(ui->Setting_Screen_data_time_dow_arr_day_button_img, 20, 11);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_data_time_dow_arr_day_button_img_main_main_default
	static lv_style_t style_setting_screen_data_time_dow_arr_day_button_img_main_main_default;
	lv_style_reset(&style_setting_screen_data_time_dow_arr_day_button_img_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_data_time_dow_arr_day_button_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_data_time_dow_arr_day_button_img_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_data_time_dow_arr_day_button_img_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_data_time_dow_arr_day_button_img, &style_setting_screen_data_time_dow_arr_day_button_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_data_time_dow_arr_day_button_img, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_data_time_dow_arr_day_button_img,&_day_down_arrow_20x11);
	lv_img_set_pivot(ui->Setting_Screen_data_time_dow_arr_day_button_img, 0,0);
	lv_img_set_angle(ui->Setting_Screen_data_time_dow_arr_day_button_img, 0);

	//Write codes Setting_Screen_data_time_do_arr_day_LB1
	ui->Setting_Screen_data_time_do_arr_day_LB1 = lv_label_create(ui->Setting_Screen_seting_date_time_day_container);
	lv_obj_set_pos(ui->Setting_Screen_data_time_do_arr_day_LB1, 49, 100);
	lv_obj_set_size(ui->Setting_Screen_data_time_do_arr_day_LB1, 126, 18);
	lv_label_set_text(ui->Setting_Screen_data_time_do_arr_day_LB1, "");
	lv_label_set_long_mode(ui->Setting_Screen_data_time_do_arr_day_LB1, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->Setting_Screen_data_time_do_arr_day_LB1, LV_TEXT_ALIGN_LEFT, 0);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_data_time_do_arr_day_lb1_main_main_default
	static lv_style_t style_setting_screen_data_time_do_arr_day_lb1_main_main_default;
	lv_style_reset(&style_setting_screen_data_time_do_arr_day_lb1_main_main_default);
	lv_style_set_radius(&style_setting_screen_data_time_do_arr_day_lb1_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_data_time_do_arr_day_lb1_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_setting_screen_data_time_do_arr_day_lb1_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_setting_screen_data_time_do_arr_day_lb1_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_data_time_do_arr_day_lb1_main_main_default, 0);
	lv_style_set_text_color(&style_setting_screen_data_time_do_arr_day_lb1_main_main_default, lv_color_make(0xb8, 0xb8, 0xb8));
	lv_style_set_text_font(&style_setting_screen_data_time_do_arr_day_lb1_main_main_default, &lv_font_FjallaOne_Regular_22);
	lv_style_set_text_letter_space(&style_setting_screen_data_time_do_arr_day_lb1_main_main_default, 0);
	lv_style_set_pad_left(&style_setting_screen_data_time_do_arr_day_lb1_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_data_time_do_arr_day_lb1_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_data_time_do_arr_day_lb1_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_data_time_do_arr_day_lb1_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_data_time_do_arr_day_LB1, &style_setting_screen_data_time_do_arr_day_lb1_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_data_time_do_arr_day_LB2
	ui->Setting_Screen_data_time_do_arr_day_LB2 = lv_label_create(ui->Setting_Screen_seting_date_time_day_container);
	lv_obj_set_pos(ui->Setting_Screen_data_time_do_arr_day_LB2, 49, 148);
	lv_obj_set_size(ui->Setting_Screen_data_time_do_arr_day_LB2, 126, 18);
	lv_label_set_text(ui->Setting_Screen_data_time_do_arr_day_LB2, "");
	lv_label_set_long_mode(ui->Setting_Screen_data_time_do_arr_day_LB2, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->Setting_Screen_data_time_do_arr_day_LB2, LV_TEXT_ALIGN_LEFT, 0);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_data_time_do_arr_day_lb2_main_main_default
	static lv_style_t style_setting_screen_data_time_do_arr_day_lb2_main_main_default;
	lv_style_reset(&style_setting_screen_data_time_do_arr_day_lb2_main_main_default);
	lv_style_set_radius(&style_setting_screen_data_time_do_arr_day_lb2_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_data_time_do_arr_day_lb2_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_setting_screen_data_time_do_arr_day_lb2_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_setting_screen_data_time_do_arr_day_lb2_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_data_time_do_arr_day_lb2_main_main_default, 0);
	lv_style_set_text_color(&style_setting_screen_data_time_do_arr_day_lb2_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_setting_screen_data_time_do_arr_day_lb2_main_main_default, &lv_font_FjallaOne_Regular_22);
	lv_style_set_text_letter_space(&style_setting_screen_data_time_do_arr_day_lb2_main_main_default, 0);
	lv_style_set_pad_left(&style_setting_screen_data_time_do_arr_day_lb2_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_data_time_do_arr_day_lb2_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_data_time_do_arr_day_lb2_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_data_time_do_arr_day_lb2_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_data_time_do_arr_day_LB2, &style_setting_screen_data_time_do_arr_day_lb2_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_data_time_do_arr_day_LB3
	ui->Setting_Screen_data_time_do_arr_day_LB3 = lv_label_create(ui->Setting_Screen_seting_date_time_day_container);
	lv_obj_set_pos(ui->Setting_Screen_data_time_do_arr_day_LB3, 49, 196);
	lv_obj_set_size(ui->Setting_Screen_data_time_do_arr_day_LB3, 126, 18);
	lv_label_set_text(ui->Setting_Screen_data_time_do_arr_day_LB3, "");
	lv_label_set_long_mode(ui->Setting_Screen_data_time_do_arr_day_LB3, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->Setting_Screen_data_time_do_arr_day_LB3, LV_TEXT_ALIGN_LEFT, 0);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_data_time_do_arr_day_lb3_main_main_default
	static lv_style_t style_setting_screen_data_time_do_arr_day_lb3_main_main_default;
	lv_style_reset(&style_setting_screen_data_time_do_arr_day_lb3_main_main_default);
	lv_style_set_radius(&style_setting_screen_data_time_do_arr_day_lb3_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_data_time_do_arr_day_lb3_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_setting_screen_data_time_do_arr_day_lb3_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_setting_screen_data_time_do_arr_day_lb3_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_data_time_do_arr_day_lb3_main_main_default, 0);
	lv_style_set_text_color(&style_setting_screen_data_time_do_arr_day_lb3_main_main_default, lv_color_make(0xb8, 0xb8, 0xb8));
	lv_style_set_text_font(&style_setting_screen_data_time_do_arr_day_lb3_main_main_default, &lv_font_FjallaOne_Regular_22);
	lv_style_set_text_letter_space(&style_setting_screen_data_time_do_arr_day_lb3_main_main_default, 0);
	lv_style_set_pad_left(&style_setting_screen_data_time_do_arr_day_lb3_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_data_time_do_arr_day_lb3_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_data_time_do_arr_day_lb3_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_data_time_do_arr_day_lb3_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_data_time_do_arr_day_LB3, &style_setting_screen_data_time_do_arr_day_lb3_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_setting_unit_night_container
	ui->Setting_Screen_setting_unit_night_container = lv_obj_create(ui->Setting_Screen);
	lv_obj_set_pos(ui->Setting_Screen_setting_unit_night_container, 0, 0);
	lv_obj_set_size(ui->Setting_Screen_setting_unit_night_container, 240, 320);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_setting_unit_night_container_main_main_default
	static lv_style_t style_setting_screen_setting_unit_night_container_main_main_default;
	lv_style_reset(&style_setting_screen_setting_unit_night_container_main_main_default);
	lv_style_set_radius(&style_setting_screen_setting_unit_night_container_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_setting_unit_night_container_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_color(&style_setting_screen_setting_unit_night_container_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_dir(&style_setting_screen_setting_unit_night_container_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_setting_unit_night_container_main_main_default, 0);
	lv_style_set_border_color(&style_setting_screen_setting_unit_night_container_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_border_width(&style_setting_screen_setting_unit_night_container_main_main_default, 0);
	lv_style_set_border_opa(&style_setting_screen_setting_unit_night_container_main_main_default, 255);
	lv_style_set_pad_left(&style_setting_screen_setting_unit_night_container_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_setting_unit_night_container_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_setting_unit_night_container_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_setting_unit_night_container_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_setting_unit_night_container, &style_setting_screen_setting_unit_night_container_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_unit_night_icon_img
	ui->Setting_Screen_unit_night_icon_img = lv_img_create(ui->Setting_Screen_setting_unit_night_container);
	lv_obj_set_pos(ui->Setting_Screen_unit_night_icon_img, 16, 142);
	lv_obj_set_size(ui->Setting_Screen_unit_night_icon_img, 40, 40);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_unit_night_icon_img_main_main_default
	static lv_style_t style_setting_screen_unit_night_icon_img_main_main_default;
	lv_style_reset(&style_setting_screen_unit_night_icon_img_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_unit_night_icon_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_unit_night_icon_img_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_unit_night_icon_img_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_unit_night_icon_img, &style_setting_screen_unit_night_icon_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_unit_night_sub_btn_img
	ui->Setting_Screen_unit_night_sub_btn_img = lv_img_create(ui->Setting_Screen_setting_unit_night_container);
	lv_obj_set_pos(ui->Setting_Screen_unit_night_sub_btn_img, 196, 149);
	lv_obj_set_size(ui->Setting_Screen_unit_night_sub_btn_img, 24, 24);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_unit_night_sub_btn_img_main_main_default
	static lv_style_t style_setting_screen_unit_night_sub_btn_img_main_main_default;
	lv_style_reset(&style_setting_screen_unit_night_sub_btn_img_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_unit_night_sub_btn_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_unit_night_sub_btn_img_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_unit_night_sub_btn_img_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_unit_night_sub_btn_img, &style_setting_screen_unit_night_sub_btn_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_unit_night_sub_btn_img, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_unit_night_sub_btn_img,&subbtn_night_24x24);
	lv_img_set_pivot(ui->Setting_Screen_unit_night_sub_btn_img, 0,0);
	lv_img_set_angle(ui->Setting_Screen_unit_night_sub_btn_img, 0);

	//Write codes Setting_Screen_unit_night_up_arr_img
	ui->Setting_Screen_unit_night_up_arr_img = lv_img_create(ui->Setting_Screen_setting_unit_night_container);
	lv_obj_set_pos(ui->Setting_Screen_unit_night_up_arr_img, 110, 105);
	lv_obj_set_size(ui->Setting_Screen_unit_night_up_arr_img, 20, 11);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_unit_night_up_arr_img_main_main_default
	static lv_style_t style_setting_screen_unit_night_up_arr_img_main_main_default;
	lv_style_reset(&style_setting_screen_unit_night_up_arr_img_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_unit_night_up_arr_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_unit_night_up_arr_img_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_unit_night_up_arr_img_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_unit_night_up_arr_img, &style_setting_screen_unit_night_up_arr_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_unit_night_up_arr_img, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_unit_night_up_arr_img,&_Setting_Up_Arrow_20x11);
	lv_img_set_pivot(ui->Setting_Screen_unit_night_up_arr_img, 0,0);
	lv_img_set_angle(ui->Setting_Screen_unit_night_up_arr_img, 0);

	//Write codes Setting_Screen_unit_night_down_arr_img
	ui->Setting_Screen_unit_night_down_arr_img = lv_img_create(ui->Setting_Screen_setting_unit_night_container);
	lv_obj_set_pos(ui->Setting_Screen_unit_night_down_arr_img, 110, 198);
	lv_obj_set_size(ui->Setting_Screen_unit_night_down_arr_img, 20, 11);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_unit_night_down_arr_img_main_main_default
	static lv_style_t style_setting_screen_unit_night_down_arr_img_main_main_default;
	lv_style_reset(&style_setting_screen_unit_night_down_arr_img_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_unit_night_down_arr_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_unit_night_down_arr_img_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_unit_night_down_arr_img_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_unit_night_down_arr_img, &style_setting_screen_unit_night_down_arr_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_unit_night_down_arr_img, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_unit_night_down_arr_img,&_Setting_Drow_Arrow_20x11);
	lv_img_set_pivot(ui->Setting_Screen_unit_night_down_arr_img, 0,0);
	lv_img_set_angle(ui->Setting_Screen_unit_night_down_arr_img, 0);

	//Write codes Setting_Screen_unit_night_Lb1
	ui->Setting_Screen_unit_night_Lb1 = lv_label_create(ui->Setting_Screen_setting_unit_night_container);
	lv_obj_set_pos(ui->Setting_Screen_unit_night_Lb1, 0, 148);
	lv_obj_set_size(ui->Setting_Screen_unit_night_Lb1, 240, 18);
	lv_label_set_text(ui->Setting_Screen_unit_night_Lb1, "");
	lv_label_set_long_mode(ui->Setting_Screen_unit_night_Lb1, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->Setting_Screen_unit_night_Lb1, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_unit_night_lb1_main_main_default
	static lv_style_t style_setting_screen_unit_night_lb1_main_main_default;
	lv_style_reset(&style_setting_screen_unit_night_lb1_main_main_default);
	lv_style_set_radius(&style_setting_screen_unit_night_lb1_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_unit_night_lb1_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_setting_screen_unit_night_lb1_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_setting_screen_unit_night_lb1_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_unit_night_lb1_main_main_default, 0);
	lv_style_set_text_color(&style_setting_screen_unit_night_lb1_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_setting_screen_unit_night_lb1_main_main_default, &lv_font_FjallaOne_Regular_22);
	lv_style_set_text_letter_space(&style_setting_screen_unit_night_lb1_main_main_default, 0);
	lv_style_set_pad_left(&style_setting_screen_unit_night_lb1_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_unit_night_lb1_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_unit_night_lb1_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_unit_night_lb1_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_unit_night_Lb1, &style_setting_screen_unit_night_lb1_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_setting_unit_day_container
	ui->Setting_Screen_setting_unit_day_container = lv_obj_create(ui->Setting_Screen);
	lv_obj_set_pos(ui->Setting_Screen_setting_unit_day_container, 0, 0);
	lv_obj_set_size(ui->Setting_Screen_setting_unit_day_container, 240, 320);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_setting_unit_day_container_main_main_default
	static lv_style_t style_setting_screen_setting_unit_day_container_main_main_default;
	lv_style_reset(&style_setting_screen_setting_unit_day_container_main_main_default);
	lv_style_set_radius(&style_setting_screen_setting_unit_day_container_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_setting_unit_day_container_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_color(&style_setting_screen_setting_unit_day_container_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_dir(&style_setting_screen_setting_unit_day_container_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_setting_unit_day_container_main_main_default, 0);
	lv_style_set_border_color(&style_setting_screen_setting_unit_day_container_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_border_width(&style_setting_screen_setting_unit_day_container_main_main_default, 0);
	lv_style_set_border_opa(&style_setting_screen_setting_unit_day_container_main_main_default, 255);
	lv_style_set_pad_left(&style_setting_screen_setting_unit_day_container_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_setting_unit_day_container_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_setting_unit_day_container_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_setting_unit_day_container_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_setting_unit_day_container, &style_setting_screen_setting_unit_day_container_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_unit_day_circle_img
	ui->Setting_Screen_unit_day_circle_img = lv_img_create(ui->Setting_Screen_setting_unit_day_container);
	lv_obj_set_pos(ui->Setting_Screen_unit_day_circle_img, 7, 47);
	lv_obj_set_size(ui->Setting_Screen_unit_day_circle_img, 226, 226);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_unit_day_circle_img_main_main_default
	static lv_style_t style_setting_screen_unit_day_circle_img_main_main_default;
	lv_style_reset(&style_setting_screen_unit_day_circle_img_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_unit_day_circle_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_unit_day_circle_img_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_unit_day_circle_img_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_unit_day_circle_img, &style_setting_screen_unit_day_circle_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_unit_day_circle_img, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_unit_day_circle_img,&day_white_Grey_circle);
	lv_img_set_pivot(ui->Setting_Screen_unit_day_circle_img, 0,0);
	lv_img_set_angle(ui->Setting_Screen_unit_day_circle_img, 0);

	//Write codes Setting_Screen_unit_day_icon_img
	ui->Setting_Screen_unit_day_icon_img = lv_img_create(ui->Setting_Screen_setting_unit_day_container);
	lv_obj_set_pos(ui->Setting_Screen_unit_day_icon_img, 16, 142);
	lv_obj_set_size(ui->Setting_Screen_unit_day_icon_img, 40, 40);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_unit_day_icon_img_main_main_default
	static lv_style_t style_setting_screen_unit_day_icon_img_main_main_default;
	lv_style_reset(&style_setting_screen_unit_day_icon_img_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_unit_day_icon_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_unit_day_icon_img_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_unit_day_icon_img_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_unit_day_icon_img, &style_setting_screen_unit_day_icon_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_unit_day_sub_btn_img
	ui->Setting_Screen_unit_day_sub_btn_img = lv_img_create(ui->Setting_Screen_setting_unit_day_container);
	lv_obj_set_pos(ui->Setting_Screen_unit_day_sub_btn_img, 196, 149);
	lv_obj_set_size(ui->Setting_Screen_unit_day_sub_btn_img, 24, 24);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_unit_day_sub_btn_img_main_main_default
	static lv_style_t style_setting_screen_unit_day_sub_btn_img_main_main_default;
	lv_style_reset(&style_setting_screen_unit_day_sub_btn_img_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_unit_day_sub_btn_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_unit_day_sub_btn_img_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_unit_day_sub_btn_img_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_unit_day_sub_btn_img, &style_setting_screen_unit_day_sub_btn_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_unit_day_sub_btn_img, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_unit_day_sub_btn_img,&subbtn_day_24x24);
	lv_img_set_pivot(ui->Setting_Screen_unit_day_sub_btn_img, 0,0);
	lv_img_set_angle(ui->Setting_Screen_unit_day_sub_btn_img, 0);

	//Write codes Setting_Screen_unit_day_up_arr_img
	ui->Setting_Screen_unit_day_up_arr_img = lv_img_create(ui->Setting_Screen_setting_unit_day_container);
	lv_obj_set_pos(ui->Setting_Screen_unit_day_up_arr_img, 110, 105);
	lv_obj_set_size(ui->Setting_Screen_unit_day_up_arr_img, 20, 11);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_unit_day_up_arr_img_main_main_default
	static lv_style_t style_setting_screen_unit_day_up_arr_img_main_main_default;
	lv_style_reset(&style_setting_screen_unit_day_up_arr_img_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_unit_day_up_arr_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_unit_day_up_arr_img_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_unit_day_up_arr_img_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_unit_day_up_arr_img, &style_setting_screen_unit_day_up_arr_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_unit_day_up_arr_img, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_unit_day_up_arr_img,&_day_up_arrow_20x11);
	lv_img_set_pivot(ui->Setting_Screen_unit_day_up_arr_img, 0,0);
	lv_img_set_angle(ui->Setting_Screen_unit_day_up_arr_img, 0);

	//Write codes Setting_Screen_unit_day_night_arr_img
	ui->Setting_Screen_unit_day_night_arr_img = lv_img_create(ui->Setting_Screen_setting_unit_day_container);
	lv_obj_set_pos(ui->Setting_Screen_unit_day_night_arr_img, 110, 198);
	lv_obj_set_size(ui->Setting_Screen_unit_day_night_arr_img, 20, 11);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_unit_day_night_arr_img_main_main_default
	static lv_style_t style_setting_screen_unit_day_night_arr_img_main_main_default;
	lv_style_reset(&style_setting_screen_unit_day_night_arr_img_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_unit_day_night_arr_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_unit_day_night_arr_img_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_unit_day_night_arr_img_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_unit_day_night_arr_img, &style_setting_screen_unit_day_night_arr_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_unit_day_night_arr_img, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_unit_day_night_arr_img,&_day_down_arrow_20x11);
	lv_img_set_pivot(ui->Setting_Screen_unit_day_night_arr_img, 0,0);
	lv_img_set_angle(ui->Setting_Screen_unit_day_night_arr_img, 0);

	//Write codes Setting_Screen_unit_day_lb1
	ui->Setting_Screen_unit_day_lb1 = lv_label_create(ui->Setting_Screen_setting_unit_day_container);
	lv_obj_set_pos(ui->Setting_Screen_unit_day_lb1, 0, 148);
	lv_obj_set_size(ui->Setting_Screen_unit_day_lb1, 240, 18);
	lv_label_set_text(ui->Setting_Screen_unit_day_lb1, "");
	lv_label_set_long_mode(ui->Setting_Screen_unit_day_lb1, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->Setting_Screen_unit_day_lb1, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_unit_day_lb1_main_main_default
	static lv_style_t style_setting_screen_unit_day_lb1_main_main_default;
	lv_style_reset(&style_setting_screen_unit_day_lb1_main_main_default);
	lv_style_set_radius(&style_setting_screen_unit_day_lb1_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_unit_day_lb1_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_setting_screen_unit_day_lb1_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_setting_screen_unit_day_lb1_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_unit_day_lb1_main_main_default, 0);
	lv_style_set_text_color(&style_setting_screen_unit_day_lb1_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_setting_screen_unit_day_lb1_main_main_default, &lv_font_FjallaOne_Regular_22);
	lv_style_set_text_letter_space(&style_setting_screen_unit_day_lb1_main_main_default, 0);
	lv_style_set_pad_left(&style_setting_screen_unit_day_lb1_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_unit_day_lb1_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_unit_day_lb1_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_unit_day_lb1_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_unit_day_lb1, &style_setting_screen_unit_day_lb1_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_setting_units_sub_container
	ui->Setting_Screen_setting_units_sub_container = lv_obj_create(ui->Setting_Screen);
	lv_obj_set_pos(ui->Setting_Screen_setting_units_sub_container, 0, 0);
	lv_obj_set_size(ui->Setting_Screen_setting_units_sub_container, 240, 320);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_setting_units_sub_container_main_main_default
	static lv_style_t style_setting_screen_setting_units_sub_container_main_main_default;
	lv_style_reset(&style_setting_screen_setting_units_sub_container_main_main_default);
	lv_style_set_radius(&style_setting_screen_setting_units_sub_container_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_setting_units_sub_container_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_color(&style_setting_screen_setting_units_sub_container_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_dir(&style_setting_screen_setting_units_sub_container_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_setting_units_sub_container_main_main_default, 0);
	lv_style_set_border_color(&style_setting_screen_setting_units_sub_container_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_border_width(&style_setting_screen_setting_units_sub_container_main_main_default, 0);
	lv_style_set_border_opa(&style_setting_screen_setting_units_sub_container_main_main_default, 255);
	lv_style_set_pad_left(&style_setting_screen_setting_units_sub_container_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_setting_units_sub_container_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_setting_units_sub_container_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_setting_units_sub_container_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_setting_units_sub_container, &style_setting_screen_setting_units_sub_container_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_units_check_btn_img
	ui->Setting_Screen_units_check_btn_img = lv_img_create(ui->Setting_Screen_setting_units_sub_container);
	lv_obj_set_pos(ui->Setting_Screen_units_check_btn_img, 168, 117);
	lv_obj_set_size(ui->Setting_Screen_units_check_btn_img, 20, 20);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_units_check_btn_img_main_main_default
	static lv_style_t style_setting_screen_units_check_btn_img_main_main_default;
	lv_style_reset(&style_setting_screen_units_check_btn_img_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_units_check_btn_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_units_check_btn_img_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_units_check_btn_img_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_units_check_btn_img, &style_setting_screen_units_check_btn_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_units_check_btn_img, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_units_check_btn_img,&_radiobtn_night_Checked_20x20);
	lv_img_set_pivot(ui->Setting_Screen_units_check_btn_img, 0,0);
	lv_img_set_angle(ui->Setting_Screen_units_check_btn_img, 0);

	//Write codes Setting_Screen_units_sub_up_arr_img
	ui->Setting_Screen_units_sub_up_arr_img = lv_img_create(ui->Setting_Screen_setting_units_sub_container);
	lv_obj_set_pos(ui->Setting_Screen_units_sub_up_arr_img, 110, 115);
	lv_obj_set_size(ui->Setting_Screen_units_sub_up_arr_img, 20, 11);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_units_sub_up_arr_img_main_main_default
	static lv_style_t style_setting_screen_units_sub_up_arr_img_main_main_default;
	lv_style_reset(&style_setting_screen_units_sub_up_arr_img_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_units_sub_up_arr_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_units_sub_up_arr_img_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_units_sub_up_arr_img_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_units_sub_up_arr_img, &style_setting_screen_units_sub_up_arr_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_units_sub_up_arr_img, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_units_sub_up_arr_img,&_Setting_Up_Arrow_20x11);
	lv_img_set_pivot(ui->Setting_Screen_units_sub_up_arr_img, 0,0);
	lv_img_set_angle(ui->Setting_Screen_units_sub_up_arr_img, 0);

	//Write codes Setting_Screen_units_sub_down_arr_img
	ui->Setting_Screen_units_sub_down_arr_img = lv_img_create(ui->Setting_Screen_setting_units_sub_container);
	lv_obj_set_pos(ui->Setting_Screen_units_sub_down_arr_img, 110, 198);
	lv_obj_set_size(ui->Setting_Screen_units_sub_down_arr_img, 20, 11);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_units_sub_down_arr_img_main_main_default
	static lv_style_t style_setting_screen_units_sub_down_arr_img_main_main_default;
	lv_style_reset(&style_setting_screen_units_sub_down_arr_img_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_units_sub_down_arr_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_units_sub_down_arr_img_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_units_sub_down_arr_img_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_units_sub_down_arr_img, &style_setting_screen_units_sub_down_arr_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_units_sub_down_arr_img, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_units_sub_down_arr_img,&_Setting_Drow_Arrow_20x11);
	lv_img_set_pivot(ui->Setting_Screen_units_sub_down_arr_img, 0,0);
	lv_img_set_angle(ui->Setting_Screen_units_sub_down_arr_img, 0);

	//Write codes Setting_Screen_units_sub_lbl
	ui->Setting_Screen_units_sub_lbl = lv_label_create(ui->Setting_Screen_setting_units_sub_container);
	lv_obj_set_pos(ui->Setting_Screen_units_sub_lbl, 51, 148);
	lv_obj_set_size(ui->Setting_Screen_units_sub_lbl, 126, 18);
	lv_label_set_text(ui->Setting_Screen_units_sub_lbl, "L/100 km");
	lv_label_set_long_mode(ui->Setting_Screen_units_sub_lbl, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->Setting_Screen_units_sub_lbl, LV_TEXT_ALIGN_LEFT, 0);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_units_sub_lbl_main_main_default
	static lv_style_t style_setting_screen_units_sub_lbl_main_main_default;
	lv_style_reset(&style_setting_screen_units_sub_lbl_main_main_default);
	lv_style_set_radius(&style_setting_screen_units_sub_lbl_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_units_sub_lbl_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_setting_screen_units_sub_lbl_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_setting_screen_units_sub_lbl_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_units_sub_lbl_main_main_default, 0);
	lv_style_set_text_color(&style_setting_screen_units_sub_lbl_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_setting_screen_units_sub_lbl_main_main_default, &lv_font_FjallaOne_Regular_22);
	lv_style_set_text_letter_space(&style_setting_screen_units_sub_lbl_main_main_default, 0);
	lv_style_set_pad_left(&style_setting_screen_units_sub_lbl_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_units_sub_lbl_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_units_sub_lbl_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_units_sub_lbl_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_units_sub_lbl, &style_setting_screen_units_sub_lbl_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_setting_units_day_sub_container
	ui->Setting_Screen_setting_units_day_sub_container = lv_obj_create(ui->Setting_Screen);
	lv_obj_set_pos(ui->Setting_Screen_setting_units_day_sub_container, 0, 0);
	lv_obj_set_size(ui->Setting_Screen_setting_units_day_sub_container, 240, 320);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_setting_units_day_sub_container_main_main_default
	static lv_style_t style_setting_screen_setting_units_day_sub_container_main_main_default;
	lv_style_reset(&style_setting_screen_setting_units_day_sub_container_main_main_default);
	lv_style_set_radius(&style_setting_screen_setting_units_day_sub_container_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_setting_units_day_sub_container_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_color(&style_setting_screen_setting_units_day_sub_container_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_dir(&style_setting_screen_setting_units_day_sub_container_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_setting_units_day_sub_container_main_main_default, 0);
	lv_style_set_border_color(&style_setting_screen_setting_units_day_sub_container_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_border_width(&style_setting_screen_setting_units_day_sub_container_main_main_default, 0);
	lv_style_set_border_opa(&style_setting_screen_setting_units_day_sub_container_main_main_default, 255);
	lv_style_set_pad_left(&style_setting_screen_setting_units_day_sub_container_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_setting_units_day_sub_container_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_setting_units_day_sub_container_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_setting_units_day_sub_container_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_setting_units_day_sub_container, &style_setting_screen_setting_units_day_sub_container_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_units_day_circle_img
	ui->Setting_Screen_units_day_circle_img = lv_img_create(ui->Setting_Screen_setting_units_day_sub_container);
	lv_obj_set_pos(ui->Setting_Screen_units_day_circle_img, 7, 47);
	lv_obj_set_size(ui->Setting_Screen_units_day_circle_img, 226, 226);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_units_day_circle_img_main_main_default
	static lv_style_t style_setting_screen_units_day_circle_img_main_main_default;
	lv_style_reset(&style_setting_screen_units_day_circle_img_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_units_day_circle_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_units_day_circle_img_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_units_day_circle_img_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_units_day_circle_img, &style_setting_screen_units_day_circle_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_units_day_circle_img, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_units_day_circle_img,&day_white_Grey_circle);
	lv_img_set_pivot(ui->Setting_Screen_units_day_circle_img, 0,0);
	lv_img_set_angle(ui->Setting_Screen_units_day_circle_img, 0);

	//Write codes Setting_Screen_units_check_day_btn_img
	ui->Setting_Screen_units_check_day_btn_img = lv_img_create(ui->Setting_Screen_setting_units_day_sub_container);
	lv_obj_set_pos(ui->Setting_Screen_units_check_day_btn_img, 196, 145);
	lv_obj_set_size(ui->Setting_Screen_units_check_day_btn_img, 20, 20);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_units_check_day_btn_img_main_main_default
	static lv_style_t style_setting_screen_units_check_day_btn_img_main_main_default;
	lv_style_reset(&style_setting_screen_units_check_day_btn_img_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_units_check_day_btn_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_units_check_day_btn_img_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_units_check_day_btn_img_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_units_check_day_btn_img, &style_setting_screen_units_check_day_btn_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_units_check_day_btn_img, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_units_check_day_btn_img,&_radiobtn_day_checked_20x20);
	lv_img_set_pivot(ui->Setting_Screen_units_check_day_btn_img, 0,0);
	lv_img_set_angle(ui->Setting_Screen_units_check_day_btn_img, 0);

	//Write codes Setting_Screen_units_up_arr_day_img
	ui->Setting_Screen_units_up_arr_day_img = lv_img_create(ui->Setting_Screen_setting_units_day_sub_container);
	lv_obj_set_pos(ui->Setting_Screen_units_up_arr_day_img, 110, 115);
	lv_obj_set_size(ui->Setting_Screen_units_up_arr_day_img, 20, 11);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_units_up_arr_day_img_main_main_default
	static lv_style_t style_setting_screen_units_up_arr_day_img_main_main_default;
	lv_style_reset(&style_setting_screen_units_up_arr_day_img_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_units_up_arr_day_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_units_up_arr_day_img_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_units_up_arr_day_img_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_units_up_arr_day_img, &style_setting_screen_units_up_arr_day_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_units_up_arr_day_img, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_units_up_arr_day_img,&_day_up_arrow_20x11);
	lv_img_set_pivot(ui->Setting_Screen_units_up_arr_day_img, 0,0);
	lv_img_set_angle(ui->Setting_Screen_units_up_arr_day_img, 0);

	//Write codes Setting_Screen_units_up_arr_night_img
	ui->Setting_Screen_units_up_arr_night_img = lv_img_create(ui->Setting_Screen_setting_units_day_sub_container);
	lv_obj_set_pos(ui->Setting_Screen_units_up_arr_night_img, 110, 198);
	lv_obj_set_size(ui->Setting_Screen_units_up_arr_night_img, 20, 11);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_units_up_arr_night_img_main_main_default
	static lv_style_t style_setting_screen_units_up_arr_night_img_main_main_default;
	lv_style_reset(&style_setting_screen_units_up_arr_night_img_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_units_up_arr_night_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_units_up_arr_night_img_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_units_up_arr_night_img_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_units_up_arr_night_img, &style_setting_screen_units_up_arr_night_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_units_up_arr_night_img, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_units_up_arr_night_img,&_day_down_arrow_20x11);
	lv_img_set_pivot(ui->Setting_Screen_units_up_arr_night_img, 0,0);
	lv_img_set_angle(ui->Setting_Screen_units_up_arr_night_img, 0);

	//Write codes Setting_Screen_units_day_lbl1
	ui->Setting_Screen_units_day_lbl1 = lv_label_create(ui->Setting_Screen_setting_units_day_sub_container);
	lv_obj_set_pos(ui->Setting_Screen_units_day_lbl1, 51, 148);
	lv_obj_set_size(ui->Setting_Screen_units_day_lbl1, 126, 18);
	lv_label_set_text(ui->Setting_Screen_units_day_lbl1, "L/100 km");
	lv_label_set_long_mode(ui->Setting_Screen_units_day_lbl1, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->Setting_Screen_units_day_lbl1, LV_TEXT_ALIGN_LEFT, 0);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_units_day_lbl1_main_main_default
	static lv_style_t style_setting_screen_units_day_lbl1_main_main_default;
	lv_style_reset(&style_setting_screen_units_day_lbl1_main_main_default);
	lv_style_set_radius(&style_setting_screen_units_day_lbl1_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_units_day_lbl1_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_setting_screen_units_day_lbl1_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_setting_screen_units_day_lbl1_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_units_day_lbl1_main_main_default, 0);
	lv_style_set_text_color(&style_setting_screen_units_day_lbl1_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_setting_screen_units_day_lbl1_main_main_default, &lv_font_FjallaOne_Regular_22);
	lv_style_set_text_letter_space(&style_setting_screen_units_day_lbl1_main_main_default, 0);
	lv_style_set_pad_left(&style_setting_screen_units_day_lbl1_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_units_day_lbl1_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_units_day_lbl1_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_units_day_lbl1_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_units_day_lbl1, &style_setting_screen_units_day_lbl1_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);


	//Write codes Setting_Screen_setting_about_inf_container
	ui->Setting_Screen_setting_about_inf_container = lv_obj_create(ui->Setting_Screen);
	lv_obj_set_pos(ui->Setting_Screen_setting_about_inf_container, 0, 0);
	lv_obj_set_size(ui->Setting_Screen_setting_about_inf_container, 240, 320);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_setting_about_inf_container_main_main_default
	static lv_style_t style_setting_screen_setting_about_inf_container_main_main_default;
	lv_style_reset(&style_setting_screen_setting_about_inf_container_main_main_default);
	lv_style_set_radius(&style_setting_screen_setting_about_inf_container_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_setting_about_inf_container_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_color(&style_setting_screen_setting_about_inf_container_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_dir(&style_setting_screen_setting_about_inf_container_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_setting_about_inf_container_main_main_default, 0);
	lv_style_set_border_color(&style_setting_screen_setting_about_inf_container_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_border_width(&style_setting_screen_setting_about_inf_container_main_main_default, 0);
	lv_style_set_border_opa(&style_setting_screen_setting_about_inf_container_main_main_default, 255);
	lv_style_set_pad_left(&style_setting_screen_setting_about_inf_container_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_setting_about_inf_container_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_setting_about_inf_container_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_setting_about_inf_container_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_setting_about_inf_container, &style_setting_screen_setting_about_inf_container_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_aboutinf_lb1
	ui->Setting_Screen_aboutinf_lb1 = lv_label_create(ui->Setting_Screen_setting_about_inf_container);
	lv_obj_set_pos(ui->Setting_Screen_aboutinf_lb1, 62, 148);
	lv_obj_set_size(ui->Setting_Screen_aboutinf_lb1, 126, 18);
	lv_label_set_text(ui->Setting_Screen_aboutinf_lb1, "");
	lv_label_set_long_mode(ui->Setting_Screen_aboutinf_lb1, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->Setting_Screen_aboutinf_lb1, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_aboutinf_lb1_main_main_default
	static lv_style_t style_setting_screen_aboutinf_lb1_main_main_default;
	lv_style_reset(&style_setting_screen_aboutinf_lb1_main_main_default);
	lv_style_set_radius(&style_setting_screen_aboutinf_lb1_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_aboutinf_lb1_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_setting_screen_aboutinf_lb1_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_setting_screen_aboutinf_lb1_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_aboutinf_lb1_main_main_default, 0);
	lv_style_set_text_color(&style_setting_screen_aboutinf_lb1_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_setting_screen_aboutinf_lb1_main_main_default, &lv_font_FjallaOne_Regular_22);
	lv_style_set_text_letter_space(&style_setting_screen_aboutinf_lb1_main_main_default, 0);
	lv_style_set_pad_left(&style_setting_screen_aboutinf_lb1_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_aboutinf_lb1_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_aboutinf_lb1_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_aboutinf_lb1_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_aboutinf_lb1, &style_setting_screen_aboutinf_lb1_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_setting_about_inf_nigh_container
	ui->Setting_Screen_setting_about_inf_nigh_container = lv_obj_create(ui->Setting_Screen);
	lv_obj_set_pos(ui->Setting_Screen_setting_about_inf_nigh_container, 0, 0);
	lv_obj_set_size(ui->Setting_Screen_setting_about_inf_nigh_container, 240, 320);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_setting_about_inf_nigh_container_main_main_default
	static lv_style_t style_setting_screen_setting_about_inf_nigh_container_main_main_default;
	lv_style_reset(&style_setting_screen_setting_about_inf_nigh_container_main_main_default);
	lv_style_set_radius(&style_setting_screen_setting_about_inf_nigh_container_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_setting_about_inf_nigh_container_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_color(&style_setting_screen_setting_about_inf_nigh_container_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_dir(&style_setting_screen_setting_about_inf_nigh_container_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_setting_about_inf_nigh_container_main_main_default, 0);
	lv_style_set_border_color(&style_setting_screen_setting_about_inf_nigh_container_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_border_width(&style_setting_screen_setting_about_inf_nigh_container_main_main_default, 0);
	lv_style_set_border_opa(&style_setting_screen_setting_about_inf_nigh_container_main_main_default, 255);
	lv_style_set_pad_left(&style_setting_screen_setting_about_inf_nigh_container_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_setting_about_inf_nigh_container_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_setting_about_inf_nigh_container_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_setting_about_inf_nigh_container_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_setting_about_inf_nigh_container, &style_setting_screen_setting_about_inf_nigh_container_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_aboout_day_cir_img
	ui->Setting_Screen_aboout_day_cir_img = lv_img_create(ui->Setting_Screen_setting_about_inf_nigh_container);
	lv_obj_set_pos(ui->Setting_Screen_aboout_day_cir_img, 7, 47);
	lv_obj_set_size(ui->Setting_Screen_aboout_day_cir_img, 226, 226);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_aboout_day_cir_img_main_main_default
	static lv_style_t style_setting_screen_aboout_day_cir_img_main_main_default;
	lv_style_reset(&style_setting_screen_aboout_day_cir_img_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_aboout_day_cir_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_aboout_day_cir_img_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_aboout_day_cir_img_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_aboout_day_cir_img, &style_setting_screen_aboout_day_cir_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_aboout_day_cir_img, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_aboout_day_cir_img,&day_white_Grey_circle);
	lv_img_set_pivot(ui->Setting_Screen_aboout_day_cir_img, 0,0);
	lv_img_set_angle(ui->Setting_Screen_aboout_day_cir_img, 0);

	//Write codes Setting_Screen_aboutinf_nnight_lbl1
	ui->Setting_Screen_aboutinf_nnight_lbl1 = lv_label_create(ui->Setting_Screen_setting_about_inf_nigh_container);
	lv_obj_set_pos(ui->Setting_Screen_aboutinf_nnight_lbl1, 62, 148);
	lv_obj_set_size(ui->Setting_Screen_aboutinf_nnight_lbl1, 126, 18);
	lv_label_set_text(ui->Setting_Screen_aboutinf_nnight_lbl1, "");
	lv_label_set_long_mode(ui->Setting_Screen_aboutinf_nnight_lbl1, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->Setting_Screen_aboutinf_nnight_lbl1, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_aboutinf_nnight_lbl1_main_main_default
	static lv_style_t style_setting_screen_aboutinf_nnight_lbl1_main_main_default;
	lv_style_reset(&style_setting_screen_aboutinf_nnight_lbl1_main_main_default);
	lv_style_set_radius(&style_setting_screen_aboutinf_nnight_lbl1_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_aboutinf_nnight_lbl1_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_setting_screen_aboutinf_nnight_lbl1_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_setting_screen_aboutinf_nnight_lbl1_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_aboutinf_nnight_lbl1_main_main_default, 0);
	lv_style_set_text_color(&style_setting_screen_aboutinf_nnight_lbl1_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_setting_screen_aboutinf_nnight_lbl1_main_main_default, &lv_font_FjallaOne_Regular_22);
	lv_style_set_text_letter_space(&style_setting_screen_aboutinf_nnight_lbl1_main_main_default, 0);
	lv_style_set_pad_left(&style_setting_screen_aboutinf_nnight_lbl1_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_aboutinf_nnight_lbl1_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_aboutinf_nnight_lbl1_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_aboutinf_nnight_lbl1_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_aboutinf_nnight_lbl1, &style_setting_screen_aboutinf_nnight_lbl1_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_setting_date_set_container
	ui->Setting_Screen_setting_date_set_container = lv_obj_create(ui->Setting_Screen);
	lv_obj_set_pos(ui->Setting_Screen_setting_date_set_container, 0, 0);
	lv_obj_set_size(ui->Setting_Screen_setting_date_set_container, 240, 320);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_setting_date_set_container_main_main_default
	static lv_style_t style_setting_screen_setting_date_set_container_main_main_default;
	lv_style_reset(&style_setting_screen_setting_date_set_container_main_main_default);
	lv_style_set_radius(&style_setting_screen_setting_date_set_container_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_setting_date_set_container_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_color(&style_setting_screen_setting_date_set_container_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_dir(&style_setting_screen_setting_date_set_container_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_setting_date_set_container_main_main_default, 0);
	lv_style_set_border_color(&style_setting_screen_setting_date_set_container_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_border_width(&style_setting_screen_setting_date_set_container_main_main_default, 0);
	lv_style_set_border_opa(&style_setting_screen_setting_date_set_container_main_main_default, 255);
	lv_style_set_pad_left(&style_setting_screen_setting_date_set_container_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_setting_date_set_container_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_setting_date_set_container_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_setting_date_set_container_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_setting_date_set_container, &style_setting_screen_setting_date_set_container_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_date_night_up_arr_1
	ui->Setting_Screen_date_night_up_arr_1 = lv_img_create(ui->Setting_Screen_setting_date_set_container);
	lv_obj_set_pos(ui->Setting_Screen_date_night_up_arr_1, 60, 133);
	lv_obj_set_size(ui->Setting_Screen_date_night_up_arr_1, 20, 11);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_date_night_up_arr_1_main_main_default
	static lv_style_t style_setting_screen_date_night_up_arr_1_main_main_default;
	lv_style_reset(&style_setting_screen_date_night_up_arr_1_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_date_night_up_arr_1_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_date_night_up_arr_1_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_date_night_up_arr_1_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_date_night_up_arr_1, &style_setting_screen_date_night_up_arr_1_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_date_night_up_arr_1, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_date_night_up_arr_1,&_Setting_Up_Arrow_20x11);
	lv_img_set_pivot(ui->Setting_Screen_date_night_up_arr_1, 0,0);
	lv_img_set_angle(ui->Setting_Screen_date_night_up_arr_1, 0);

	//Write codes Setting_Screen_date_night_up_arr_2
	ui->Setting_Screen_date_night_up_arr_2 = lv_img_create(ui->Setting_Screen_setting_date_set_container);
	lv_obj_set_pos(ui->Setting_Screen_date_night_up_arr_2, 109, 133);
	lv_obj_set_size(ui->Setting_Screen_date_night_up_arr_2, 20, 11);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_date_night_up_arr_2_main_main_default
	static lv_style_t style_setting_screen_date_night_up_arr_2_main_main_default;
	lv_style_reset(&style_setting_screen_date_night_up_arr_2_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_date_night_up_arr_2_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_date_night_up_arr_2_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_date_night_up_arr_2_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_date_night_up_arr_2, &style_setting_screen_date_night_up_arr_2_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_date_night_up_arr_2, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_date_night_up_arr_2,&_Setting_Up_Arrow_20x11);
	lv_img_set_pivot(ui->Setting_Screen_date_night_up_arr_2, 0,0);
	lv_img_set_angle(ui->Setting_Screen_date_night_up_arr_2, 0);

	//Write codes Setting_Screen_date_night_up_arr_3
	ui->Setting_Screen_date_night_up_arr_3 = lv_img_create(ui->Setting_Screen_setting_date_set_container);
	lv_obj_set_pos(ui->Setting_Screen_date_night_up_arr_3, 159, 133);
	lv_obj_set_size(ui->Setting_Screen_date_night_up_arr_3, 20, 11);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_date_night_up_arr_3_main_main_default
	static lv_style_t style_setting_screen_date_night_up_arr_3_main_main_default;
	lv_style_reset(&style_setting_screen_date_night_up_arr_3_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_date_night_up_arr_3_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_date_night_up_arr_3_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_date_night_up_arr_3_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_date_night_up_arr_3, &style_setting_screen_date_night_up_arr_3_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_date_night_up_arr_3, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_date_night_up_arr_3,&_Setting_Up_Arrow_20x11);
	lv_img_set_pivot(ui->Setting_Screen_date_night_up_arr_3, 0,0);
	lv_img_set_angle(ui->Setting_Screen_date_night_up_arr_3, 0);

	//Write codes Setting_Screen_date_night_down_arr_1
	ui->Setting_Screen_date_night_down_arr_1 = lv_img_create(ui->Setting_Screen_setting_date_set_container);
	lv_obj_set_pos(ui->Setting_Screen_date_night_down_arr_1, 60, 177);
	lv_obj_set_size(ui->Setting_Screen_date_night_down_arr_1, 20, 11);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_date_night_down_arr_1_main_main_default
	static lv_style_t style_setting_screen_date_night_down_arr_1_main_main_default;
	lv_style_reset(&style_setting_screen_date_night_down_arr_1_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_date_night_down_arr_1_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_date_night_down_arr_1_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_date_night_down_arr_1_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_date_night_down_arr_1, &style_setting_screen_date_night_down_arr_1_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_date_night_down_arr_1, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_date_night_down_arr_1,&_Setting_Drow_Arrow_20x11);
	lv_img_set_pivot(ui->Setting_Screen_date_night_down_arr_1, 0,0);
	lv_img_set_angle(ui->Setting_Screen_date_night_down_arr_1, 0);

	//Write codes Setting_Screen_date_night_down_arr_2
	ui->Setting_Screen_date_night_down_arr_2 = lv_img_create(ui->Setting_Screen_setting_date_set_container);
	lv_obj_set_pos(ui->Setting_Screen_date_night_down_arr_2, 109, 177);
	lv_obj_set_size(ui->Setting_Screen_date_night_down_arr_2, 20, 11);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_date_night_down_arr_2_main_main_default
	static lv_style_t style_setting_screen_date_night_down_arr_2_main_main_default;
	lv_style_reset(&style_setting_screen_date_night_down_arr_2_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_date_night_down_arr_2_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_date_night_down_arr_2_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_date_night_down_arr_2_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_date_night_down_arr_2, &style_setting_screen_date_night_down_arr_2_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_date_night_down_arr_2, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_date_night_down_arr_2,&_Setting_Drow_Arrow_20x11);
	lv_img_set_pivot(ui->Setting_Screen_date_night_down_arr_2, 0,0);
	lv_img_set_angle(ui->Setting_Screen_date_night_down_arr_2, 0);

	//Write codes Setting_Screen_date_night_down_arr_3
	ui->Setting_Screen_date_night_down_arr_3 = lv_img_create(ui->Setting_Screen_setting_date_set_container);
	lv_obj_set_pos(ui->Setting_Screen_date_night_down_arr_3, 159, 177);
	lv_obj_set_size(ui->Setting_Screen_date_night_down_arr_3, 20, 11);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_date_night_down_arr_3_main_main_default
	static lv_style_t style_setting_screen_date_night_down_arr_3_main_main_default;
	lv_style_reset(&style_setting_screen_date_night_down_arr_3_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_date_night_down_arr_3_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_date_night_down_arr_3_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_date_night_down_arr_3_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_date_night_down_arr_3, &style_setting_screen_date_night_down_arr_3_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_date_night_down_arr_3, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_date_night_down_arr_3,&_Setting_Drow_Arrow_20x11);
	lv_img_set_pivot(ui->Setting_Screen_date_night_down_arr_3, 0,0);
	lv_img_set_angle(ui->Setting_Screen_date_night_down_arr_3, 0);

	//Write codes Setting_Screen_date_night_lbl1
	ui->Setting_Screen_date_night_lbl1 = lv_label_create(ui->Setting_Screen_setting_date_set_container);
	lv_obj_set_pos(ui->Setting_Screen_date_night_lbl1, 59, 148);
	lv_obj_set_size(ui->Setting_Screen_date_night_lbl1, 21, 18);
	lv_label_set_text(ui->Setting_Screen_date_night_lbl1, "99");
	lv_label_set_long_mode(ui->Setting_Screen_date_night_lbl1, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->Setting_Screen_date_night_lbl1, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_date_night_lbl1_main_main_default
	static lv_style_t style_setting_screen_date_night_lbl1_main_main_default;
	lv_style_reset(&style_setting_screen_date_night_lbl1_main_main_default);
	lv_style_set_radius(&style_setting_screen_date_night_lbl1_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_date_night_lbl1_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_setting_screen_date_night_lbl1_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_setting_screen_date_night_lbl1_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_date_night_lbl1_main_main_default, 0);
	lv_style_set_text_color(&style_setting_screen_date_night_lbl1_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_setting_screen_date_night_lbl1_main_main_default, &lv_font_FjallaOne_Regular_22);
	lv_style_set_text_letter_space(&style_setting_screen_date_night_lbl1_main_main_default, 0);
	lv_style_set_pad_left(&style_setting_screen_date_night_lbl1_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_date_night_lbl1_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_date_night_lbl1_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_date_night_lbl1_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_date_night_lbl1, &style_setting_screen_date_night_lbl1_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_date_night_lbl2
	ui->Setting_Screen_date_night_lbl2 = lv_label_create(ui->Setting_Screen_setting_date_set_container);
	lv_obj_set_pos(ui->Setting_Screen_date_night_lbl2, 109, 148);
	lv_obj_set_size(ui->Setting_Screen_date_night_lbl2, 21, 18);
	lv_label_set_text(ui->Setting_Screen_date_night_lbl2, "99");
	lv_label_set_long_mode(ui->Setting_Screen_date_night_lbl2, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->Setting_Screen_date_night_lbl2, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_date_night_lbl2_main_main_default
	static lv_style_t style_setting_screen_date_night_lbl2_main_main_default;
	lv_style_reset(&style_setting_screen_date_night_lbl2_main_main_default);
	lv_style_set_radius(&style_setting_screen_date_night_lbl2_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_date_night_lbl2_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_setting_screen_date_night_lbl2_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_setting_screen_date_night_lbl2_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_date_night_lbl2_main_main_default, 0);
	lv_style_set_text_color(&style_setting_screen_date_night_lbl2_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_setting_screen_date_night_lbl2_main_main_default, &lv_font_FjallaOne_Regular_22);
	lv_style_set_text_letter_space(&style_setting_screen_date_night_lbl2_main_main_default, 0);
	lv_style_set_pad_left(&style_setting_screen_date_night_lbl2_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_date_night_lbl2_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_date_night_lbl2_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_date_night_lbl2_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_date_night_lbl2, &style_setting_screen_date_night_lbl2_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_date_night_lbl3
	ui->Setting_Screen_date_night_lbl3 = lv_label_create(ui->Setting_Screen_setting_date_set_container);
	lv_obj_set_pos(ui->Setting_Screen_date_night_lbl3, 148, 148);
	lv_obj_set_size(ui->Setting_Screen_date_night_lbl3, 43, 18);
	lv_label_set_text(ui->Setting_Screen_date_night_lbl3, "9999");
	lv_label_set_long_mode(ui->Setting_Screen_date_night_lbl3, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->Setting_Screen_date_night_lbl3, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_date_night_lbl3_main_main_default
	static lv_style_t style_setting_screen_date_night_lbl3_main_main_default;
	lv_style_reset(&style_setting_screen_date_night_lbl3_main_main_default);
	lv_style_set_radius(&style_setting_screen_date_night_lbl3_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_date_night_lbl3_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_setting_screen_date_night_lbl3_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_setting_screen_date_night_lbl3_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_date_night_lbl3_main_main_default, 0);
	lv_style_set_text_color(&style_setting_screen_date_night_lbl3_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_setting_screen_date_night_lbl3_main_main_default, &lv_font_FjallaOne_Regular_22);
	lv_style_set_text_letter_space(&style_setting_screen_date_night_lbl3_main_main_default, 0);
	lv_style_set_pad_left(&style_setting_screen_date_night_lbl3_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_date_night_lbl3_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_date_night_lbl3_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_date_night_lbl3_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_date_night_lbl3, &style_setting_screen_date_night_lbl3_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_date_hold_lbl
	ui->Setting_Screen_date_hold_lbl = lv_label_create(ui->Setting_Screen_setting_date_set_container);
	lv_obj_set_pos(ui->Setting_Screen_date_hold_lbl, 68, 231);
	lv_obj_set_size(ui->Setting_Screen_date_hold_lbl, 27, 13);
	lv_label_set_text(ui->Setting_Screen_date_hold_lbl, "");
	lv_label_set_long_mode(ui->Setting_Screen_date_hold_lbl, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->Setting_Screen_date_hold_lbl, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_date_hold_lbl_main_main_default
	static lv_style_t style_setting_screen_date_hold_lbl_main_main_default;
	lv_style_reset(&style_setting_screen_date_hold_lbl_main_main_default);
	lv_style_set_radius(&style_setting_screen_date_hold_lbl_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_date_hold_lbl_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_setting_screen_date_hold_lbl_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_setting_screen_date_hold_lbl_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_date_hold_lbl_main_main_default, 0);
	lv_style_set_text_color(&style_setting_screen_date_hold_lbl_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_setting_screen_date_hold_lbl_main_main_default, &lv_font_FjallaOne_Regular_14);
	lv_style_set_text_letter_space(&style_setting_screen_date_hold_lbl_main_main_default, 0);
	lv_style_set_pad_left(&style_setting_screen_date_hold_lbl_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_date_hold_lbl_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_date_hold_lbl_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_date_hold_lbl_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_date_hold_lbl, &style_setting_screen_date_hold_lbl_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_date_toset_lbl
	ui->Setting_Screen_date_toset_lbl = lv_label_create(ui->Setting_Screen_setting_date_set_container);
	lv_obj_set_pos(ui->Setting_Screen_date_toset_lbl, 127, 231);
	lv_obj_set_size(ui->Setting_Screen_date_toset_lbl, 37, 14);
	lv_label_set_text(ui->Setting_Screen_date_toset_lbl, "");
	lv_label_set_long_mode(ui->Setting_Screen_date_toset_lbl, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->Setting_Screen_date_toset_lbl, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_date_toset_lbl_main_main_default
	static lv_style_t style_setting_screen_date_toset_lbl_main_main_default;
	lv_style_reset(&style_setting_screen_date_toset_lbl_main_main_default);
	lv_style_set_radius(&style_setting_screen_date_toset_lbl_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_date_toset_lbl_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_setting_screen_date_toset_lbl_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_setting_screen_date_toset_lbl_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_date_toset_lbl_main_main_default, 0);
	lv_style_set_text_color(&style_setting_screen_date_toset_lbl_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_setting_screen_date_toset_lbl_main_main_default, &lv_font_FjallaOne_Regular_14);
	lv_style_set_text_letter_space(&style_setting_screen_date_toset_lbl_main_main_default, 0);
	lv_style_set_pad_left(&style_setting_screen_date_toset_lbl_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_date_toset_lbl_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_date_toset_lbl_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_date_toset_lbl_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_date_toset_lbl, &style_setting_screen_date_toset_lbl_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_date_sub_btn_img
	ui->Setting_Screen_date_sub_btn_img = lv_img_create(ui->Setting_Screen_setting_date_set_container);
	lv_obj_set_pos(ui->Setting_Screen_date_sub_btn_img, 73, 228);
	lv_obj_set_size(ui->Setting_Screen_date_sub_btn_img, 95, 20);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_date_sub_btn_img_main_main_default
	static lv_style_t style_setting_screen_date_sub_btn_img_main_main_default;
	lv_style_reset(&style_setting_screen_date_sub_btn_img_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_date_sub_btn_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_date_sub_btn_img_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_date_sub_btn_img_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_date_sub_btn_img, &style_setting_screen_date_sub_btn_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_date_sub_btn_img, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_date_sub_btn_img,&hold_to_set_night);
	lv_img_set_pivot(ui->Setting_Screen_date_sub_btn_img, 0,0);
	lv_img_set_angle(ui->Setting_Screen_date_sub_btn_img, 0);

	//Write codes Setting_Screen_setting_date_set_night_container
	ui->Setting_Screen_setting_date_set_night_container = lv_obj_create(ui->Setting_Screen);
	lv_obj_set_pos(ui->Setting_Screen_setting_date_set_night_container, 0, 0);
	lv_obj_set_size(ui->Setting_Screen_setting_date_set_night_container, 240, 320);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_setting_date_set_night_container_main_main_default
	static lv_style_t style_setting_screen_setting_date_set_night_container_main_main_default;
	lv_style_reset(&style_setting_screen_setting_date_set_night_container_main_main_default);
	lv_style_set_radius(&style_setting_screen_setting_date_set_night_container_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_setting_date_set_night_container_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_color(&style_setting_screen_setting_date_set_night_container_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_dir(&style_setting_screen_setting_date_set_night_container_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_setting_date_set_night_container_main_main_default, 0);
	lv_style_set_border_color(&style_setting_screen_setting_date_set_night_container_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_border_width(&style_setting_screen_setting_date_set_night_container_main_main_default, 0);
	lv_style_set_border_opa(&style_setting_screen_setting_date_set_night_container_main_main_default, 255);
	lv_style_set_pad_left(&style_setting_screen_setting_date_set_night_container_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_setting_date_set_night_container_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_setting_date_set_night_container_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_setting_date_set_night_container_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_setting_date_set_night_container, &style_setting_screen_setting_date_set_night_container_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_date_day_cir_img
	ui->Setting_Screen_date_day_cir_img = lv_img_create(ui->Setting_Screen_setting_date_set_night_container);
	lv_obj_set_pos(ui->Setting_Screen_date_day_cir_img, 7, 47);
	lv_obj_set_size(ui->Setting_Screen_date_day_cir_img, 226, 226);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_date_day_cir_img_main_main_default
	static lv_style_t style_setting_screen_date_day_cir_img_main_main_default;
	lv_style_reset(&style_setting_screen_date_day_cir_img_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_date_day_cir_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_date_day_cir_img_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_date_day_cir_img_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_date_day_cir_img, &style_setting_screen_date_day_cir_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_date_day_cir_img, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_date_day_cir_img,&day_white_Grey_circle);
	lv_img_set_pivot(ui->Setting_Screen_date_day_cir_img, 0,0);
	lv_img_set_angle(ui->Setting_Screen_date_day_cir_img, 0);

	//Write codes Setting_Screen_date_day_up_arr_1
	ui->Setting_Screen_date_day_up_arr_1 = lv_img_create(ui->Setting_Screen_setting_date_set_night_container);
	lv_obj_set_pos(ui->Setting_Screen_date_day_up_arr_1, 60, 133);
	lv_obj_set_size(ui->Setting_Screen_date_day_up_arr_1, 20, 11);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_date_day_up_arr_1_main_main_default
	static lv_style_t style_setting_screen_date_day_up_arr_1_main_main_default;
	lv_style_reset(&style_setting_screen_date_day_up_arr_1_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_date_day_up_arr_1_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_date_day_up_arr_1_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_date_day_up_arr_1_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_date_day_up_arr_1, &style_setting_screen_date_day_up_arr_1_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_date_day_up_arr_1, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_date_day_up_arr_1,&_day_up_arrow_20x11);
	lv_img_set_pivot(ui->Setting_Screen_date_day_up_arr_1, 0,0);
	lv_img_set_angle(ui->Setting_Screen_date_day_up_arr_1, 0);

	//Write codes Setting_Screen_date_day_up_arr_2
	ui->Setting_Screen_date_day_up_arr_2 = lv_img_create(ui->Setting_Screen_setting_date_set_night_container);
	lv_obj_set_pos(ui->Setting_Screen_date_day_up_arr_2, 109, 133);
	lv_obj_set_size(ui->Setting_Screen_date_day_up_arr_2, 20, 11);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_date_day_up_arr_2_main_main_default
	static lv_style_t style_setting_screen_date_day_up_arr_2_main_main_default;
	lv_style_reset(&style_setting_screen_date_day_up_arr_2_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_date_day_up_arr_2_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_date_day_up_arr_2_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_date_day_up_arr_2_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_date_day_up_arr_2, &style_setting_screen_date_day_up_arr_2_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_date_day_up_arr_2, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_date_day_up_arr_2,&_day_up_arrow_20x11);
	lv_img_set_pivot(ui->Setting_Screen_date_day_up_arr_2, 0,0);
	lv_img_set_angle(ui->Setting_Screen_date_day_up_arr_2, 0);

	//Write codes Setting_Screen_date_day_up_arr_3
	ui->Setting_Screen_date_day_up_arr_3 = lv_img_create(ui->Setting_Screen_setting_date_set_night_container);
	lv_obj_set_pos(ui->Setting_Screen_date_day_up_arr_3, 159, 133);
	lv_obj_set_size(ui->Setting_Screen_date_day_up_arr_3, 20, 11);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_date_day_up_arr_3_main_main_default
	static lv_style_t style_setting_screen_date_day_up_arr_3_main_main_default;
	lv_style_reset(&style_setting_screen_date_day_up_arr_3_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_date_day_up_arr_3_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_date_day_up_arr_3_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_date_day_up_arr_3_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_date_day_up_arr_3, &style_setting_screen_date_day_up_arr_3_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_date_day_up_arr_3, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_date_day_up_arr_3,&_day_up_arrow_20x11);
	lv_img_set_pivot(ui->Setting_Screen_date_day_up_arr_3, 0,0);
	lv_img_set_angle(ui->Setting_Screen_date_day_up_arr_3, 0);

	//Write codes Setting_Screen_date_day_down_arr_1
	ui->Setting_Screen_date_day_down_arr_1 = lv_img_create(ui->Setting_Screen_setting_date_set_night_container);
	lv_obj_set_pos(ui->Setting_Screen_date_day_down_arr_1, 60, 177);
	lv_obj_set_size(ui->Setting_Screen_date_day_down_arr_1, 20, 11);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_date_day_down_arr_1_main_main_default
	static lv_style_t style_setting_screen_date_day_down_arr_1_main_main_default;
	lv_style_reset(&style_setting_screen_date_day_down_arr_1_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_date_day_down_arr_1_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_date_day_down_arr_1_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_date_day_down_arr_1_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_date_day_down_arr_1, &style_setting_screen_date_day_down_arr_1_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_date_day_down_arr_1, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_date_day_down_arr_1,&_day_down_arrow_20x11);
	lv_img_set_pivot(ui->Setting_Screen_date_day_down_arr_1, 0,0);
	lv_img_set_angle(ui->Setting_Screen_date_day_down_arr_1, 0);

	//Write codes Setting_Screen_date_day_down_arr_2
	ui->Setting_Screen_date_day_down_arr_2 = lv_img_create(ui->Setting_Screen_setting_date_set_night_container);
	lv_obj_set_pos(ui->Setting_Screen_date_day_down_arr_2, 109, 179);
	lv_obj_set_size(ui->Setting_Screen_date_day_down_arr_2, 20, 11);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_date_day_down_arr_2_main_main_default
	static lv_style_t style_setting_screen_date_day_down_arr_2_main_main_default;
	lv_style_reset(&style_setting_screen_date_day_down_arr_2_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_date_day_down_arr_2_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_date_day_down_arr_2_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_date_day_down_arr_2_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_date_day_down_arr_2, &style_setting_screen_date_day_down_arr_2_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_date_day_down_arr_2, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_date_day_down_arr_2,&_day_down_arrow_20x11);
	lv_img_set_pivot(ui->Setting_Screen_date_day_down_arr_2, 0,0);
	lv_img_set_angle(ui->Setting_Screen_date_day_down_arr_2, 0);

	//Write codes Setting_Screen_date_day_down_arr_3
	ui->Setting_Screen_date_day_down_arr_3 = lv_img_create(ui->Setting_Screen_setting_date_set_night_container);
	lv_obj_set_pos(ui->Setting_Screen_date_day_down_arr_3, 159, 177);
	lv_obj_set_size(ui->Setting_Screen_date_day_down_arr_3, 20, 11);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_date_day_down_arr_3_main_main_default
	static lv_style_t style_setting_screen_date_day_down_arr_3_main_main_default;
	lv_style_reset(&style_setting_screen_date_day_down_arr_3_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_date_day_down_arr_3_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_date_day_down_arr_3_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_date_day_down_arr_3_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_date_day_down_arr_3, &style_setting_screen_date_day_down_arr_3_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_date_day_down_arr_3, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_date_day_down_arr_3,&_day_down_arrow_20x11);
	lv_img_set_pivot(ui->Setting_Screen_date_day_down_arr_3, 0,0);
	lv_img_set_angle(ui->Setting_Screen_date_day_down_arr_3, 0);

	//Write codes Setting_Screen_date_day_lbl1
	ui->Setting_Screen_date_day_lbl1 = lv_label_create(ui->Setting_Screen_setting_date_set_night_container);
	lv_obj_set_pos(ui->Setting_Screen_date_day_lbl1, 59, 148);
	lv_obj_set_size(ui->Setting_Screen_date_day_lbl1, 21, 18);
	lv_label_set_text(ui->Setting_Screen_date_day_lbl1, "99");
	lv_label_set_long_mode(ui->Setting_Screen_date_day_lbl1, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->Setting_Screen_date_day_lbl1, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_date_day_lbl1_main_main_default
	static lv_style_t style_setting_screen_date_day_lbl1_main_main_default;
	lv_style_reset(&style_setting_screen_date_day_lbl1_main_main_default);
	lv_style_set_radius(&style_setting_screen_date_day_lbl1_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_date_day_lbl1_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_setting_screen_date_day_lbl1_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_setting_screen_date_day_lbl1_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_date_day_lbl1_main_main_default, 0);
	lv_style_set_text_color(&style_setting_screen_date_day_lbl1_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_setting_screen_date_day_lbl1_main_main_default, &lv_font_FjallaOne_Regular_22);
	lv_style_set_text_letter_space(&style_setting_screen_date_day_lbl1_main_main_default, 0);
	lv_style_set_pad_left(&style_setting_screen_date_day_lbl1_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_date_day_lbl1_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_date_day_lbl1_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_date_day_lbl1_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_date_day_lbl1, &style_setting_screen_date_day_lbl1_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_date_day_lbl2
	ui->Setting_Screen_date_day_lbl2 = lv_label_create(ui->Setting_Screen_setting_date_set_night_container);
	lv_obj_set_pos(ui->Setting_Screen_date_day_lbl2, 109, 148);
	lv_obj_set_size(ui->Setting_Screen_date_day_lbl2, 21, 18);
	lv_label_set_text(ui->Setting_Screen_date_day_lbl2, "99");
	lv_label_set_long_mode(ui->Setting_Screen_date_day_lbl2, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->Setting_Screen_date_day_lbl2, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_date_day_lbl2_main_main_default
	static lv_style_t style_setting_screen_date_day_lbl2_main_main_default;
	lv_style_reset(&style_setting_screen_date_day_lbl2_main_main_default);
	lv_style_set_radius(&style_setting_screen_date_day_lbl2_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_date_day_lbl2_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_setting_screen_date_day_lbl2_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_setting_screen_date_day_lbl2_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_date_day_lbl2_main_main_default, 0);
	lv_style_set_text_color(&style_setting_screen_date_day_lbl2_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_setting_screen_date_day_lbl2_main_main_default, &lv_font_FjallaOne_Regular_22);
	lv_style_set_text_letter_space(&style_setting_screen_date_day_lbl2_main_main_default, 0);
	lv_style_set_pad_left(&style_setting_screen_date_day_lbl2_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_date_day_lbl2_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_date_day_lbl2_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_date_day_lbl2_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_date_day_lbl2, &style_setting_screen_date_day_lbl2_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_date_day_lbl3
	ui->Setting_Screen_date_day_lbl3 = lv_label_create(ui->Setting_Screen_setting_date_set_night_container);
	lv_obj_set_pos(ui->Setting_Screen_date_day_lbl3, 148, 148);
	lv_obj_set_size(ui->Setting_Screen_date_day_lbl3, 43, 18);
	lv_label_set_text(ui->Setting_Screen_date_day_lbl3, "9999");
	lv_label_set_long_mode(ui->Setting_Screen_date_day_lbl3, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->Setting_Screen_date_day_lbl3, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_date_day_lbl3_main_main_default
	static lv_style_t style_setting_screen_date_day_lbl3_main_main_default;
	lv_style_reset(&style_setting_screen_date_day_lbl3_main_main_default);
	lv_style_set_radius(&style_setting_screen_date_day_lbl3_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_date_day_lbl3_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_setting_screen_date_day_lbl3_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_setting_screen_date_day_lbl3_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_date_day_lbl3_main_main_default, 0);
	lv_style_set_text_color(&style_setting_screen_date_day_lbl3_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_setting_screen_date_day_lbl3_main_main_default, &lv_font_FjallaOne_Regular_22);
	lv_style_set_text_letter_space(&style_setting_screen_date_day_lbl3_main_main_default, 0);
	lv_style_set_pad_left(&style_setting_screen_date_day_lbl3_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_date_day_lbl3_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_date_day_lbl3_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_date_day_lbl3_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_date_day_lbl3, &style_setting_screen_date_day_lbl3_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_date_day_hold_lbl
	ui->Setting_Screen_date_day_hold_lbl = lv_label_create(ui->Setting_Screen_setting_date_set_night_container);
	lv_obj_set_pos(ui->Setting_Screen_date_day_hold_lbl, 68, 230);
	lv_obj_set_size(ui->Setting_Screen_date_day_hold_lbl, 27, 13);
	lv_label_set_text(ui->Setting_Screen_date_day_hold_lbl, "");
	lv_label_set_long_mode(ui->Setting_Screen_date_day_hold_lbl, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->Setting_Screen_date_day_hold_lbl, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_date_day_hold_lbl_main_main_default
	static lv_style_t style_setting_screen_date_day_hold_lbl_main_main_default;
	lv_style_reset(&style_setting_screen_date_day_hold_lbl_main_main_default);
	lv_style_set_radius(&style_setting_screen_date_day_hold_lbl_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_date_day_hold_lbl_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_setting_screen_date_day_hold_lbl_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_setting_screen_date_day_hold_lbl_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_date_day_hold_lbl_main_main_default, 0);
	lv_style_set_text_color(&style_setting_screen_date_day_hold_lbl_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_setting_screen_date_day_hold_lbl_main_main_default, &lv_font_FjallaOne_Regular_14);
	lv_style_set_text_letter_space(&style_setting_screen_date_day_hold_lbl_main_main_default, 0);
	lv_style_set_pad_left(&style_setting_screen_date_day_hold_lbl_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_date_day_hold_lbl_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_date_day_hold_lbl_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_date_day_hold_lbl_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_date_day_hold_lbl, &style_setting_screen_date_day_hold_lbl_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_date_day_toset_lbl
	ui->Setting_Screen_date_day_toset_lbl = lv_label_create(ui->Setting_Screen_setting_date_set_night_container);
	lv_obj_set_pos(ui->Setting_Screen_date_day_toset_lbl, 127, 230);
	lv_obj_set_size(ui->Setting_Screen_date_day_toset_lbl, 37, 14);
	lv_label_set_text(ui->Setting_Screen_date_day_toset_lbl, "");
	lv_label_set_long_mode(ui->Setting_Screen_date_day_toset_lbl, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->Setting_Screen_date_day_toset_lbl, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_date_day_toset_lbl_main_main_default
	static lv_style_t style_setting_screen_date_day_toset_lbl_main_main_default;
	lv_style_reset(&style_setting_screen_date_day_toset_lbl_main_main_default);
	lv_style_set_radius(&style_setting_screen_date_day_toset_lbl_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_date_day_toset_lbl_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_setting_screen_date_day_toset_lbl_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_setting_screen_date_day_toset_lbl_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_date_day_toset_lbl_main_main_default, 0);
	lv_style_set_text_color(&style_setting_screen_date_day_toset_lbl_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_setting_screen_date_day_toset_lbl_main_main_default, &lv_font_FjallaOne_Regular_14);
	lv_style_set_text_letter_space(&style_setting_screen_date_day_toset_lbl_main_main_default, 0);
	lv_style_set_pad_left(&style_setting_screen_date_day_toset_lbl_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_date_day_toset_lbl_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_date_day_toset_lbl_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_date_day_toset_lbl_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_date_day_toset_lbl, &style_setting_screen_date_day_toset_lbl_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_date_day_subbutn_img
	ui->Setting_Screen_date_day_subbutn_img = lv_img_create(ui->Setting_Screen_setting_date_set_night_container);
	lv_obj_set_pos(ui->Setting_Screen_date_day_subbutn_img, 72, 228);
	lv_obj_set_size(ui->Setting_Screen_date_day_subbutn_img, 96, 20);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_date_day_subbutn_img_main_main_default
	static lv_style_t style_setting_screen_date_day_subbutn_img_main_main_default;
	lv_style_reset(&style_setting_screen_date_day_subbutn_img_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_date_day_subbutn_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_date_day_subbutn_img_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_date_day_subbutn_img_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_date_day_subbutn_img, &style_setting_screen_date_day_subbutn_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_date_day_subbutn_img, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_date_day_subbutn_img,&hold_set_day);
	lv_img_set_pivot(ui->Setting_Screen_date_day_subbutn_img, 0,0);
	lv_img_set_angle(ui->Setting_Screen_date_day_subbutn_img, 0);

	//Write codes Setting_Screen_setting_time_set_container
	ui->Setting_Screen_setting_time_set_container = lv_obj_create(ui->Setting_Screen);
	lv_obj_set_pos(ui->Setting_Screen_setting_time_set_container, 0, 0);
	lv_obj_set_size(ui->Setting_Screen_setting_time_set_container, 240, 320);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_setting_time_set_container_main_main_default
	static lv_style_t style_setting_screen_setting_time_set_container_main_main_default;
	lv_style_reset(&style_setting_screen_setting_time_set_container_main_main_default);
	lv_style_set_radius(&style_setting_screen_setting_time_set_container_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_setting_time_set_container_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_color(&style_setting_screen_setting_time_set_container_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_dir(&style_setting_screen_setting_time_set_container_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_setting_time_set_container_main_main_default, 0);
	lv_style_set_border_color(&style_setting_screen_setting_time_set_container_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_border_width(&style_setting_screen_setting_time_set_container_main_main_default, 0);
	lv_style_set_border_opa(&style_setting_screen_setting_time_set_container_main_main_default, 255);
	lv_style_set_pad_left(&style_setting_screen_setting_time_set_container_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_setting_time_set_container_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_setting_time_set_container_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_setting_time_set_container_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_setting_time_set_container, &style_setting_screen_setting_time_set_container_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_time_night_up_arr_1
	ui->Setting_Screen_time_night_up_arr_1 = lv_img_create(ui->Setting_Screen_setting_time_set_container);
	lv_obj_set_pos(ui->Setting_Screen_time_night_up_arr_1, 60, 133);
	lv_obj_set_size(ui->Setting_Screen_time_night_up_arr_1, 20, 11);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_time_night_up_arr_1_main_main_default
	static lv_style_t style_setting_screen_time_night_up_arr_1_main_main_default;
	lv_style_reset(&style_setting_screen_time_night_up_arr_1_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_time_night_up_arr_1_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_time_night_up_arr_1_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_time_night_up_arr_1_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_time_night_up_arr_1, &style_setting_screen_time_night_up_arr_1_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_time_night_up_arr_1, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_time_night_up_arr_1,&_Setting_Up_Arrow_20x11);
	lv_img_set_pivot(ui->Setting_Screen_time_night_up_arr_1, 0,0);
	lv_img_set_angle(ui->Setting_Screen_time_night_up_arr_1, 0);

	//Write codes Setting_Screen_time_night_up_arr_2
	ui->Setting_Screen_time_night_up_arr_2 = lv_img_create(ui->Setting_Screen_setting_time_set_container);
	lv_obj_set_pos(ui->Setting_Screen_time_night_up_arr_2, 109, 133);
	lv_obj_set_size(ui->Setting_Screen_time_night_up_arr_2, 20, 11);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_time_night_up_arr_2_main_main_default
	static lv_style_t style_setting_screen_time_night_up_arr_2_main_main_default;
	lv_style_reset(&style_setting_screen_time_night_up_arr_2_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_time_night_up_arr_2_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_time_night_up_arr_2_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_time_night_up_arr_2_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_time_night_up_arr_2, &style_setting_screen_time_night_up_arr_2_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_time_night_up_arr_2, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_time_night_up_arr_2,&_Setting_Up_Arrow_20x11);
	lv_img_set_pivot(ui->Setting_Screen_time_night_up_arr_2, 0,0);
	lv_img_set_angle(ui->Setting_Screen_time_night_up_arr_2, 0);

	//Write codes Setting_Screen_time_night_up_arr_3
	ui->Setting_Screen_time_night_up_arr_3 = lv_img_create(ui->Setting_Screen_setting_time_set_container);
	lv_obj_set_pos(ui->Setting_Screen_time_night_up_arr_3, 159, 133);
	lv_obj_set_size(ui->Setting_Screen_time_night_up_arr_3, 20, 11);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_time_night_up_arr_3_main_main_default
	static lv_style_t style_setting_screen_time_night_up_arr_3_main_main_default;
	lv_style_reset(&style_setting_screen_time_night_up_arr_3_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_time_night_up_arr_3_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_time_night_up_arr_3_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_time_night_up_arr_3_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_time_night_up_arr_3, &style_setting_screen_time_night_up_arr_3_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_time_night_up_arr_3, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_time_night_up_arr_3,&_Setting_Up_Arrow_20x11);
	lv_img_set_pivot(ui->Setting_Screen_time_night_up_arr_3, 0,0);
	lv_img_set_angle(ui->Setting_Screen_time_night_up_arr_3, 0);

	//Write codes Setting_Screen_time_night_down_arr_1
	ui->Setting_Screen_time_night_down_arr_1 = lv_img_create(ui->Setting_Screen_setting_time_set_container);
	lv_obj_set_pos(ui->Setting_Screen_time_night_down_arr_1, 60, 177);
	lv_obj_set_size(ui->Setting_Screen_time_night_down_arr_1, 20, 11);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_time_night_down_arr_1_main_main_default
	static lv_style_t style_setting_screen_time_night_down_arr_1_main_main_default;
	lv_style_reset(&style_setting_screen_time_night_down_arr_1_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_time_night_down_arr_1_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_time_night_down_arr_1_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_time_night_down_arr_1_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_time_night_down_arr_1, &style_setting_screen_time_night_down_arr_1_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_time_night_down_arr_1, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_time_night_down_arr_1,&_Setting_Drow_Arrow_20x11);
	lv_img_set_pivot(ui->Setting_Screen_time_night_down_arr_1, 0,0);
	lv_img_set_angle(ui->Setting_Screen_time_night_down_arr_1, 0);

	//Write codes Setting_Screen_time_night_down_arr_2
	ui->Setting_Screen_time_night_down_arr_2 = lv_img_create(ui->Setting_Screen_setting_time_set_container);
	lv_obj_set_pos(ui->Setting_Screen_time_night_down_arr_2, 109, 177);
	lv_obj_set_size(ui->Setting_Screen_time_night_down_arr_2, 20, 11);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_time_night_down_arr_2_main_main_default
	static lv_style_t style_setting_screen_time_night_down_arr_2_main_main_default;
	lv_style_reset(&style_setting_screen_time_night_down_arr_2_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_time_night_down_arr_2_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_time_night_down_arr_2_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_time_night_down_arr_2_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_time_night_down_arr_2, &style_setting_screen_time_night_down_arr_2_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_time_night_down_arr_2, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_time_night_down_arr_2,&_Setting_Drow_Arrow_20x11);
	lv_img_set_pivot(ui->Setting_Screen_time_night_down_arr_2, 0,0);
	lv_img_set_angle(ui->Setting_Screen_time_night_down_arr_2, 0);

	//Write codes Setting_Screen_time_night_down_arr_3
	ui->Setting_Screen_time_night_down_arr_3 = lv_img_create(ui->Setting_Screen_setting_time_set_container);
	lv_obj_set_pos(ui->Setting_Screen_time_night_down_arr_3, 159, 177);
	lv_obj_set_size(ui->Setting_Screen_time_night_down_arr_3, 20, 11);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_time_night_down_arr_3_main_main_default
	static lv_style_t style_setting_screen_time_night_down_arr_3_main_main_default;
	lv_style_reset(&style_setting_screen_time_night_down_arr_3_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_time_night_down_arr_3_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_time_night_down_arr_3_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_time_night_down_arr_3_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_time_night_down_arr_3, &style_setting_screen_time_night_down_arr_3_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_time_night_down_arr_3, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_time_night_down_arr_3,&_Setting_Drow_Arrow_20x11);
	lv_img_set_pivot(ui->Setting_Screen_time_night_down_arr_3, 0,0);
	lv_img_set_angle(ui->Setting_Screen_time_night_down_arr_3, 0);

	//Write codes Setting_Screen_time_night_lbl1
	ui->Setting_Screen_time_night_lbl1 = lv_label_create(ui->Setting_Screen_setting_time_set_container);
	lv_obj_set_pos(ui->Setting_Screen_time_night_lbl1, 59, 148);
	lv_obj_set_size(ui->Setting_Screen_time_night_lbl1, 21, 18);
	lv_label_set_text(ui->Setting_Screen_time_night_lbl1, "12");
	lv_label_set_long_mode(ui->Setting_Screen_time_night_lbl1, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->Setting_Screen_time_night_lbl1, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_time_night_lbl1_main_main_default
	static lv_style_t style_setting_screen_time_night_lbl1_main_main_default;
	lv_style_reset(&style_setting_screen_time_night_lbl1_main_main_default);
	lv_style_set_radius(&style_setting_screen_time_night_lbl1_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_time_night_lbl1_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_setting_screen_time_night_lbl1_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_setting_screen_time_night_lbl1_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_time_night_lbl1_main_main_default, 0);
	lv_style_set_text_color(&style_setting_screen_time_night_lbl1_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_setting_screen_time_night_lbl1_main_main_default, &lv_font_FjallaOne_Regular_22);
	lv_style_set_text_letter_space(&style_setting_screen_time_night_lbl1_main_main_default, 0);
	lv_style_set_pad_left(&style_setting_screen_time_night_lbl1_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_time_night_lbl1_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_time_night_lbl1_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_time_night_lbl1_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_time_night_lbl1, &style_setting_screen_time_night_lbl1_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_time_night_lbl2
	ui->Setting_Screen_time_night_lbl2 = lv_label_create(ui->Setting_Screen_setting_time_set_container);
	lv_obj_set_pos(ui->Setting_Screen_time_night_lbl2, 109, 148);
	lv_obj_set_size(ui->Setting_Screen_time_night_lbl2, 21, 18);
	lv_label_set_text(ui->Setting_Screen_time_night_lbl2, "00");
	lv_label_set_long_mode(ui->Setting_Screen_time_night_lbl2, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->Setting_Screen_time_night_lbl2, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_time_night_lbl2_main_main_default
	static lv_style_t style_setting_screen_time_night_lbl2_main_main_default;
	lv_style_reset(&style_setting_screen_time_night_lbl2_main_main_default);
	lv_style_set_radius(&style_setting_screen_time_night_lbl2_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_time_night_lbl2_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_setting_screen_time_night_lbl2_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_setting_screen_time_night_lbl2_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_time_night_lbl2_main_main_default, 0);
	lv_style_set_text_color(&style_setting_screen_time_night_lbl2_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_setting_screen_time_night_lbl2_main_main_default, &lv_font_FjallaOne_Regular_22);
	lv_style_set_text_letter_space(&style_setting_screen_time_night_lbl2_main_main_default, 0);
	lv_style_set_pad_left(&style_setting_screen_time_night_lbl2_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_time_night_lbl2_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_time_night_lbl2_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_time_night_lbl2_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_time_night_lbl2, &style_setting_screen_time_night_lbl2_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_time_night_lbl3
	ui->Setting_Screen_time_night_lbl3 = lv_label_create(ui->Setting_Screen_setting_time_set_container);
	lv_obj_set_pos(ui->Setting_Screen_time_night_lbl3, 148, 148);
	lv_obj_set_size(ui->Setting_Screen_time_night_lbl3, 43, 18);
	lv_label_set_text(ui->Setting_Screen_time_night_lbl3, "AM");
	lv_label_set_long_mode(ui->Setting_Screen_time_night_lbl3, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->Setting_Screen_time_night_lbl3, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_time_night_lbl3_main_main_default
	static lv_style_t style_setting_screen_time_night_lbl3_main_main_default;
	lv_style_reset(&style_setting_screen_time_night_lbl3_main_main_default);
	lv_style_set_radius(&style_setting_screen_time_night_lbl3_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_time_night_lbl3_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_setting_screen_time_night_lbl3_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_setting_screen_time_night_lbl3_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_time_night_lbl3_main_main_default, 0);
	lv_style_set_text_color(&style_setting_screen_time_night_lbl3_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_setting_screen_time_night_lbl3_main_main_default, &lv_font_FjallaOne_Regular_22);
	lv_style_set_text_letter_space(&style_setting_screen_time_night_lbl3_main_main_default, 0);
	lv_style_set_pad_left(&style_setting_screen_time_night_lbl3_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_time_night_lbl3_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_time_night_lbl3_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_time_night_lbl3_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_time_night_lbl3, &style_setting_screen_time_night_lbl3_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_time_night_hold_lbl
	ui->Setting_Screen_time_night_hold_lbl = lv_label_create(ui->Setting_Screen_setting_time_set_container);
	lv_obj_set_pos(ui->Setting_Screen_time_night_hold_lbl, 68, 231);
	lv_obj_set_size(ui->Setting_Screen_time_night_hold_lbl, 27, 13);
	lv_label_set_text(ui->Setting_Screen_time_night_hold_lbl, "");
	lv_label_set_long_mode(ui->Setting_Screen_time_night_hold_lbl, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->Setting_Screen_time_night_hold_lbl, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_time_night_hold_lbl_main_main_default
	static lv_style_t style_setting_screen_time_night_hold_lbl_main_main_default;
	lv_style_reset(&style_setting_screen_time_night_hold_lbl_main_main_default);
	lv_style_set_radius(&style_setting_screen_time_night_hold_lbl_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_time_night_hold_lbl_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_setting_screen_time_night_hold_lbl_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_setting_screen_time_night_hold_lbl_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_time_night_hold_lbl_main_main_default, 0);
	lv_style_set_text_color(&style_setting_screen_time_night_hold_lbl_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_setting_screen_time_night_hold_lbl_main_main_default, &lv_font_FjallaOne_Regular_14);
	lv_style_set_text_letter_space(&style_setting_screen_time_night_hold_lbl_main_main_default, 0);
	lv_style_set_pad_left(&style_setting_screen_time_night_hold_lbl_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_time_night_hold_lbl_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_time_night_hold_lbl_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_time_night_hold_lbl_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_time_night_hold_lbl, &style_setting_screen_time_night_hold_lbl_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_time_night_toset_lbl
	ui->Setting_Screen_time_night_toset_lbl = lv_label_create(ui->Setting_Screen_setting_time_set_container);
	lv_obj_set_pos(ui->Setting_Screen_time_night_toset_lbl, 127, 230);
	lv_obj_set_size(ui->Setting_Screen_time_night_toset_lbl, 37, 14);
	lv_label_set_text(ui->Setting_Screen_time_night_toset_lbl, "");
	lv_label_set_long_mode(ui->Setting_Screen_time_night_toset_lbl, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->Setting_Screen_time_night_toset_lbl, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_time_night_toset_lbl_main_main_default
	static lv_style_t style_setting_screen_time_night_toset_lbl_main_main_default;
	lv_style_reset(&style_setting_screen_time_night_toset_lbl_main_main_default);
	lv_style_set_radius(&style_setting_screen_time_night_toset_lbl_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_time_night_toset_lbl_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_setting_screen_time_night_toset_lbl_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_setting_screen_time_night_toset_lbl_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_time_night_toset_lbl_main_main_default, 0);
	lv_style_set_text_color(&style_setting_screen_time_night_toset_lbl_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_setting_screen_time_night_toset_lbl_main_main_default, &lv_font_FjallaOne_Regular_14);
	lv_style_set_text_letter_space(&style_setting_screen_time_night_toset_lbl_main_main_default, 0);
	lv_style_set_pad_left(&style_setting_screen_time_night_toset_lbl_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_time_night_toset_lbl_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_time_night_toset_lbl_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_time_night_toset_lbl_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_time_night_toset_lbl, &style_setting_screen_time_night_toset_lbl_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_time_night_sub_btn
	ui->Setting_Screen_time_night_sub_btn = lv_img_create(ui->Setting_Screen_setting_time_set_container);
	lv_obj_set_pos(ui->Setting_Screen_time_night_sub_btn, 73, 228);
	lv_obj_set_size(ui->Setting_Screen_time_night_sub_btn, 95, 20);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_time_night_sub_btn_main_main_default
	static lv_style_t style_setting_screen_time_night_sub_btn_main_main_default;
	lv_style_reset(&style_setting_screen_time_night_sub_btn_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_time_night_sub_btn_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_time_night_sub_btn_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_time_night_sub_btn_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_time_night_sub_btn, &style_setting_screen_time_night_sub_btn_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_time_night_sub_btn, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_time_night_sub_btn,&hold_to_set_night);
	lv_img_set_pivot(ui->Setting_Screen_time_night_sub_btn, 0,0);
	lv_img_set_angle(ui->Setting_Screen_time_night_sub_btn, 0);

	//Write codes Setting_Screen_setting_time_set_night_container
	ui->Setting_Screen_setting_time_set_night_container = lv_obj_create(ui->Setting_Screen);
	lv_obj_set_pos(ui->Setting_Screen_setting_time_set_night_container, 0, 0);
	lv_obj_set_size(ui->Setting_Screen_setting_time_set_night_container, 240, 320);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_setting_time_set_night_container_main_main_default
	static lv_style_t style_setting_screen_setting_time_set_night_container_main_main_default;
	lv_style_reset(&style_setting_screen_setting_time_set_night_container_main_main_default);
	lv_style_set_radius(&style_setting_screen_setting_time_set_night_container_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_setting_time_set_night_container_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_color(&style_setting_screen_setting_time_set_night_container_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_dir(&style_setting_screen_setting_time_set_night_container_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_setting_time_set_night_container_main_main_default, 0);
	lv_style_set_border_color(&style_setting_screen_setting_time_set_night_container_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_border_width(&style_setting_screen_setting_time_set_night_container_main_main_default, 0);
	lv_style_set_border_opa(&style_setting_screen_setting_time_set_night_container_main_main_default, 255);
	lv_style_set_pad_left(&style_setting_screen_setting_time_set_night_container_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_setting_time_set_night_container_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_setting_time_set_night_container_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_setting_time_set_night_container_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_setting_time_set_night_container, &style_setting_screen_setting_time_set_night_container_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_time_day_cir_img
	ui->Setting_Screen_time_day_cir_img = lv_img_create(ui->Setting_Screen_setting_time_set_night_container);
	lv_obj_set_pos(ui->Setting_Screen_time_day_cir_img, 7, 47);
	lv_obj_set_size(ui->Setting_Screen_time_day_cir_img, 226, 226);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_time_day_cir_img_main_main_default
	static lv_style_t style_setting_screen_time_day_cir_img_main_main_default;
	lv_style_reset(&style_setting_screen_time_day_cir_img_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_time_day_cir_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_time_day_cir_img_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_time_day_cir_img_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_time_day_cir_img, &style_setting_screen_time_day_cir_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_time_day_cir_img, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_time_day_cir_img,&day_white_Grey_circle);
	lv_img_set_pivot(ui->Setting_Screen_time_day_cir_img, 0,0);
	lv_img_set_angle(ui->Setting_Screen_time_day_cir_img, 0);

	//Write codes Setting_Screen_time_day_up_arr_1
	ui->Setting_Screen_time_day_up_arr_1 = lv_img_create(ui->Setting_Screen_setting_time_set_night_container);
	lv_obj_set_pos(ui->Setting_Screen_time_day_up_arr_1, 60, 133);
	lv_obj_set_size(ui->Setting_Screen_time_day_up_arr_1, 20, 11);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_time_day_up_arr_1_main_main_default
	static lv_style_t style_setting_screen_time_day_up_arr_1_main_main_default;
	lv_style_reset(&style_setting_screen_time_day_up_arr_1_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_time_day_up_arr_1_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_time_day_up_arr_1_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_time_day_up_arr_1_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_time_day_up_arr_1, &style_setting_screen_time_day_up_arr_1_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_time_day_up_arr_1, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_time_day_up_arr_1,&_day_up_arrow_20x11);
	lv_img_set_pivot(ui->Setting_Screen_time_day_up_arr_1, 0,0);
	lv_img_set_angle(ui->Setting_Screen_time_day_up_arr_1, 0);

	//Write codes Setting_Screen_time_day_up_arr_2
	ui->Setting_Screen_time_day_up_arr_2 = lv_img_create(ui->Setting_Screen_setting_time_set_night_container);
	lv_obj_set_pos(ui->Setting_Screen_time_day_up_arr_2, 109, 133);
	lv_obj_set_size(ui->Setting_Screen_time_day_up_arr_2, 20, 11);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_time_day_up_arr_2_main_main_default
	static lv_style_t style_setting_screen_time_day_up_arr_2_main_main_default;
	lv_style_reset(&style_setting_screen_time_day_up_arr_2_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_time_day_up_arr_2_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_time_day_up_arr_2_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_time_day_up_arr_2_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_time_day_up_arr_2, &style_setting_screen_time_day_up_arr_2_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_time_day_up_arr_2, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_time_day_up_arr_2,&_day_up_arrow_20x11);
	lv_img_set_pivot(ui->Setting_Screen_time_day_up_arr_2, 0,0);
	lv_img_set_angle(ui->Setting_Screen_time_day_up_arr_2, 0);

	//Write codes Setting_Screen_time_day_up_arr_3
	ui->Setting_Screen_time_day_up_arr_3 = lv_img_create(ui->Setting_Screen_setting_time_set_night_container);
	lv_obj_set_pos(ui->Setting_Screen_time_day_up_arr_3, 159, 133);
	lv_obj_set_size(ui->Setting_Screen_time_day_up_arr_3, 20, 11);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_time_day_up_arr_3_main_main_default
	static lv_style_t style_setting_screen_time_day_up_arr_3_main_main_default;
	lv_style_reset(&style_setting_screen_time_day_up_arr_3_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_time_day_up_arr_3_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_time_day_up_arr_3_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_time_day_up_arr_3_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_time_day_up_arr_3, &style_setting_screen_time_day_up_arr_3_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_time_day_up_arr_3, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_time_day_up_arr_3,&_day_up_arrow_20x11);
	lv_img_set_pivot(ui->Setting_Screen_time_day_up_arr_3, 0,0);
	lv_img_set_angle(ui->Setting_Screen_time_day_up_arr_3, 0);

	//Write codes Setting_Screen_time_day_down_arr_1
	ui->Setting_Screen_time_day_down_arr_1 = lv_img_create(ui->Setting_Screen_setting_time_set_night_container);
	lv_obj_set_pos(ui->Setting_Screen_time_day_down_arr_1, 60, 177);
	lv_obj_set_size(ui->Setting_Screen_time_day_down_arr_1, 20, 11);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_time_day_down_arr_1_main_main_default
	static lv_style_t style_setting_screen_time_day_down_arr_1_main_main_default;
	lv_style_reset(&style_setting_screen_time_day_down_arr_1_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_time_day_down_arr_1_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_time_day_down_arr_1_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_time_day_down_arr_1_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_time_day_down_arr_1, &style_setting_screen_time_day_down_arr_1_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_time_day_down_arr_1, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_time_day_down_arr_1,&_day_down_arrow_20x11);
	lv_img_set_pivot(ui->Setting_Screen_time_day_down_arr_1, 0,0);
	lv_img_set_angle(ui->Setting_Screen_time_day_down_arr_1, 0);

	//Write codes Setting_Screen_time_day_down_arr_2
	ui->Setting_Screen_time_day_down_arr_2 = lv_img_create(ui->Setting_Screen_setting_time_set_night_container);
	lv_obj_set_pos(ui->Setting_Screen_time_day_down_arr_2, 109, 177);
	lv_obj_set_size(ui->Setting_Screen_time_day_down_arr_2, 20, 11);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_time_day_down_arr_2_main_main_default
	static lv_style_t style_setting_screen_time_day_down_arr_2_main_main_default;
	lv_style_reset(&style_setting_screen_time_day_down_arr_2_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_time_day_down_arr_2_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_time_day_down_arr_2_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_time_day_down_arr_2_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_time_day_down_arr_2, &style_setting_screen_time_day_down_arr_2_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_time_day_down_arr_2, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_time_day_down_arr_2,&_day_down_arrow_20x11);
	lv_img_set_pivot(ui->Setting_Screen_time_day_down_arr_2, 0,0);
	lv_img_set_angle(ui->Setting_Screen_time_day_down_arr_2, 0);

	//Write codes Setting_Screen_time_day_down_arr_3
	ui->Setting_Screen_time_day_down_arr_3 = lv_img_create(ui->Setting_Screen_setting_time_set_night_container);
	lv_obj_set_pos(ui->Setting_Screen_time_day_down_arr_3, 159, 177);
	lv_obj_set_size(ui->Setting_Screen_time_day_down_arr_3, 20, 11);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_time_day_down_arr_3_main_main_default
	static lv_style_t style_setting_screen_time_day_down_arr_3_main_main_default;
	lv_style_reset(&style_setting_screen_time_day_down_arr_3_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_time_day_down_arr_3_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_time_day_down_arr_3_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_time_day_down_arr_3_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_time_day_down_arr_3, &style_setting_screen_time_day_down_arr_3_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_time_day_down_arr_3, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_time_day_down_arr_3,&_day_down_arrow_20x11);
	lv_img_set_pivot(ui->Setting_Screen_time_day_down_arr_3, 0,0);
	lv_img_set_angle(ui->Setting_Screen_time_day_down_arr_3, 0);

	//Write codes Setting_Screen_time_day_lbl1
	ui->Setting_Screen_time_day_lbl1 = lv_label_create(ui->Setting_Screen_setting_time_set_night_container);
	lv_obj_set_pos(ui->Setting_Screen_time_day_lbl1, 59, 148);
	lv_obj_set_size(ui->Setting_Screen_time_day_lbl1, 21, 18);
	lv_label_set_text(ui->Setting_Screen_time_day_lbl1, "99");
	lv_label_set_long_mode(ui->Setting_Screen_time_day_lbl1, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->Setting_Screen_time_day_lbl1, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_time_day_lbl1_main_main_default
	static lv_style_t style_setting_screen_time_day_lbl1_main_main_default;
	lv_style_reset(&style_setting_screen_time_day_lbl1_main_main_default);
	lv_style_set_radius(&style_setting_screen_time_day_lbl1_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_time_day_lbl1_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_setting_screen_time_day_lbl1_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_setting_screen_time_day_lbl1_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_time_day_lbl1_main_main_default, 0);
	lv_style_set_text_color(&style_setting_screen_time_day_lbl1_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_setting_screen_time_day_lbl1_main_main_default, &lv_font_FjallaOne_Regular_22);
	lv_style_set_text_letter_space(&style_setting_screen_time_day_lbl1_main_main_default, 0);
	lv_style_set_pad_left(&style_setting_screen_time_day_lbl1_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_time_day_lbl1_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_time_day_lbl1_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_time_day_lbl1_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_time_day_lbl1, &style_setting_screen_time_day_lbl1_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_time_day_lbl2
	ui->Setting_Screen_time_day_lbl2 = lv_label_create(ui->Setting_Screen_setting_time_set_night_container);
	lv_obj_set_pos(ui->Setting_Screen_time_day_lbl2, 109, 148);
	lv_obj_set_size(ui->Setting_Screen_time_day_lbl2, 21, 18);
	lv_label_set_text(ui->Setting_Screen_time_day_lbl2, "99");
	lv_label_set_long_mode(ui->Setting_Screen_time_day_lbl2, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->Setting_Screen_time_day_lbl2, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_time_day_lbl2_main_main_default
	static lv_style_t style_setting_screen_time_day_lbl2_main_main_default;
	lv_style_reset(&style_setting_screen_time_day_lbl2_main_main_default);
	lv_style_set_radius(&style_setting_screen_time_day_lbl2_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_time_day_lbl2_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_setting_screen_time_day_lbl2_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_setting_screen_time_day_lbl2_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_time_day_lbl2_main_main_default, 0);
	lv_style_set_text_color(&style_setting_screen_time_day_lbl2_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_setting_screen_time_day_lbl2_main_main_default, &lv_font_FjallaOne_Regular_22);
	lv_style_set_text_letter_space(&style_setting_screen_time_day_lbl2_main_main_default, 0);
	lv_style_set_pad_left(&style_setting_screen_time_day_lbl2_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_time_day_lbl2_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_time_day_lbl2_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_time_day_lbl2_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_time_day_lbl2, &style_setting_screen_time_day_lbl2_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_time_day_lbl3
	ui->Setting_Screen_time_day_lbl3 = lv_label_create(ui->Setting_Screen_setting_time_set_night_container);
	lv_obj_set_pos(ui->Setting_Screen_time_day_lbl3, 148, 148);
	lv_obj_set_size(ui->Setting_Screen_time_day_lbl3, 43, 18);
	lv_label_set_text(ui->Setting_Screen_time_day_lbl3, "AM");
	lv_label_set_long_mode(ui->Setting_Screen_time_day_lbl3, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->Setting_Screen_time_day_lbl3, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_time_day_lbl3_main_main_default
	static lv_style_t style_setting_screen_time_day_lbl3_main_main_default;
	lv_style_reset(&style_setting_screen_time_day_lbl3_main_main_default);
	lv_style_set_radius(&style_setting_screen_time_day_lbl3_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_time_day_lbl3_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_setting_screen_time_day_lbl3_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_setting_screen_time_day_lbl3_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_time_day_lbl3_main_main_default, 0);
	lv_style_set_text_color(&style_setting_screen_time_day_lbl3_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_setting_screen_time_day_lbl3_main_main_default, &lv_font_FjallaOne_Regular_22);
	lv_style_set_text_letter_space(&style_setting_screen_time_day_lbl3_main_main_default, 0);
	lv_style_set_pad_left(&style_setting_screen_time_day_lbl3_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_time_day_lbl3_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_time_day_lbl3_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_time_day_lbl3_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_time_day_lbl3, &style_setting_screen_time_day_lbl3_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_time_day_Hold_lbl1
	ui->Setting_Screen_time_day_Hold_lbl1 = lv_label_create(ui->Setting_Screen_setting_time_set_night_container);
	lv_obj_set_pos(ui->Setting_Screen_time_day_Hold_lbl1, 68, 231);
	lv_obj_set_size(ui->Setting_Screen_time_day_Hold_lbl1, 27, 13);
	lv_label_set_text(ui->Setting_Screen_time_day_Hold_lbl1, "");
	lv_label_set_long_mode(ui->Setting_Screen_time_day_Hold_lbl1, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->Setting_Screen_time_day_Hold_lbl1, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_time_day_hold_lbl1_main_main_default
	static lv_style_t style_setting_screen_time_day_hold_lbl1_main_main_default;
	lv_style_reset(&style_setting_screen_time_day_hold_lbl1_main_main_default);
	lv_style_set_radius(&style_setting_screen_time_day_hold_lbl1_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_time_day_hold_lbl1_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_setting_screen_time_day_hold_lbl1_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_setting_screen_time_day_hold_lbl1_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_time_day_hold_lbl1_main_main_default, 0);
	lv_style_set_text_color(&style_setting_screen_time_day_hold_lbl1_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_setting_screen_time_day_hold_lbl1_main_main_default, &lv_font_FjallaOne_Regular_14);
	lv_style_set_text_letter_space(&style_setting_screen_time_day_hold_lbl1_main_main_default, 0);
	lv_style_set_pad_left(&style_setting_screen_time_day_hold_lbl1_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_time_day_hold_lbl1_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_time_day_hold_lbl1_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_time_day_hold_lbl1_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_time_day_Hold_lbl1, &style_setting_screen_time_day_hold_lbl1_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_time_day_Hold_lbl2
	ui->Setting_Screen_time_day_Hold_lbl2 = lv_label_create(ui->Setting_Screen_setting_time_set_night_container);
	lv_obj_set_pos(ui->Setting_Screen_time_day_Hold_lbl2, 127, 231);
	lv_obj_set_size(ui->Setting_Screen_time_day_Hold_lbl2, 37, 14);
	lv_label_set_text(ui->Setting_Screen_time_day_Hold_lbl2, "");
	lv_label_set_long_mode(ui->Setting_Screen_time_day_Hold_lbl2, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->Setting_Screen_time_day_Hold_lbl2, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_time_day_hold_lbl2_main_main_default
	static lv_style_t style_setting_screen_time_day_hold_lbl2_main_main_default;
	lv_style_reset(&style_setting_screen_time_day_hold_lbl2_main_main_default);
	lv_style_set_radius(&style_setting_screen_time_day_hold_lbl2_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_time_day_hold_lbl2_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_setting_screen_time_day_hold_lbl2_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_setting_screen_time_day_hold_lbl2_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_time_day_hold_lbl2_main_main_default, 0);
	lv_style_set_text_color(&style_setting_screen_time_day_hold_lbl2_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_setting_screen_time_day_hold_lbl2_main_main_default, &lv_font_FjallaOne_Regular_14);
	lv_style_set_text_letter_space(&style_setting_screen_time_day_hold_lbl2_main_main_default, 0);
	lv_style_set_pad_left(&style_setting_screen_time_day_hold_lbl2_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_time_day_hold_lbl2_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_time_day_hold_lbl2_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_time_day_hold_lbl2_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_time_day_Hold_lbl2, &style_setting_screen_time_day_hold_lbl2_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_time_day_sub_btn
	ui->Setting_Screen_time_day_sub_btn = lv_img_create(ui->Setting_Screen_setting_time_set_night_container);
	lv_obj_set_pos(ui->Setting_Screen_time_day_sub_btn, 72, 228);
	lv_obj_set_size(ui->Setting_Screen_time_day_sub_btn, 96, 20);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_time_day_sub_btn_main_main_default
	static lv_style_t style_setting_screen_time_day_sub_btn_main_main_default;
	lv_style_reset(&style_setting_screen_time_day_sub_btn_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_time_day_sub_btn_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_time_day_sub_btn_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_time_day_sub_btn_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_time_day_sub_btn, &style_setting_screen_time_day_sub_btn_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_time_day_sub_btn, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_time_day_sub_btn,&hold_set_day);
	lv_img_set_pivot(ui->Setting_Screen_time_day_sub_btn, 0,0);
	lv_img_set_angle(ui->Setting_Screen_time_day_sub_btn, 0);

	//Write codes Setting_Screen_setting_time_12_container
	ui->Setting_Screen_setting_time_12_container = lv_obj_create(ui->Setting_Screen);
	lv_obj_set_pos(ui->Setting_Screen_setting_time_12_container, 0, 0);
	lv_obj_set_size(ui->Setting_Screen_setting_time_12_container, 240, 320);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_setting_time_12_container_main_main_default
	static lv_style_t style_setting_screen_setting_time_12_container_main_main_default;
	lv_style_reset(&style_setting_screen_setting_time_12_container_main_main_default);
	lv_style_set_radius(&style_setting_screen_setting_time_12_container_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_setting_time_12_container_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_color(&style_setting_screen_setting_time_12_container_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_dir(&style_setting_screen_setting_time_12_container_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_setting_time_12_container_main_main_default, 0);
	lv_style_set_border_color(&style_setting_screen_setting_time_12_container_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_border_width(&style_setting_screen_setting_time_12_container_main_main_default, 0);
	lv_style_set_border_opa(&style_setting_screen_setting_time_12_container_main_main_default, 255);
	lv_style_set_pad_left(&style_setting_screen_setting_time_12_container_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_setting_time_12_container_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_setting_time_12_container_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_setting_time_12_container_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_setting_time_12_container, &style_setting_screen_setting_time_12_container_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_time_12_up_arr_1
	ui->Setting_Screen_time_12_up_arr_1 = lv_img_create(ui->Setting_Screen_setting_time_12_container);
	lv_obj_set_pos(ui->Setting_Screen_time_12_up_arr_1, 86, 120);
	lv_obj_set_size(ui->Setting_Screen_time_12_up_arr_1, 20, 11);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_time_12_up_arr_1_main_main_default
	static lv_style_t style_setting_screen_time_12_up_arr_1_main_main_default;
	lv_style_reset(&style_setting_screen_time_12_up_arr_1_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_time_12_up_arr_1_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_time_12_up_arr_1_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_time_12_up_arr_1_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_time_12_up_arr_1, &style_setting_screen_time_12_up_arr_1_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_time_12_up_arr_1, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_time_12_up_arr_1,&_Setting_Up_Arrow_20x11);
	lv_img_set_pivot(ui->Setting_Screen_time_12_up_arr_1, 0,0);
	lv_img_set_angle(ui->Setting_Screen_time_12_up_arr_1, 0);

	//Write codes Setting_Screen_time_12_up_arr_2
	ui->Setting_Screen_time_12_up_arr_2 = lv_img_create(ui->Setting_Screen_setting_time_12_container);
	lv_obj_set_pos(ui->Setting_Screen_time_12_up_arr_2, 134, 120);
	lv_obj_set_size(ui->Setting_Screen_time_12_up_arr_2, 20, 11);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_time_12_up_arr_2_main_main_default
	static lv_style_t style_setting_screen_time_12_up_arr_2_main_main_default;
	lv_style_reset(&style_setting_screen_time_12_up_arr_2_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_time_12_up_arr_2_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_time_12_up_arr_2_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_time_12_up_arr_2_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_time_12_up_arr_2, &style_setting_screen_time_12_up_arr_2_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_time_12_up_arr_2, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_time_12_up_arr_2,&_Setting_Up_Arrow_20x11);
	lv_img_set_pivot(ui->Setting_Screen_time_12_up_arr_2, 0,0);
	lv_img_set_angle(ui->Setting_Screen_time_12_up_arr_2, 0);

	//Write codes Setting_Screen_time_12_down_arr_1
	ui->Setting_Screen_time_12_down_arr_1 = lv_img_create(ui->Setting_Screen_setting_time_12_container);
	lv_obj_set_pos(ui->Setting_Screen_time_12_down_arr_1, 86, 190);
	lv_obj_set_size(ui->Setting_Screen_time_12_down_arr_1, 20, 11);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_time_12_down_arr_1_main_main_default
	static lv_style_t style_setting_screen_time_12_down_arr_1_main_main_default;
	lv_style_reset(&style_setting_screen_time_12_down_arr_1_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_time_12_down_arr_1_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_time_12_down_arr_1_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_time_12_down_arr_1_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_time_12_down_arr_1, &style_setting_screen_time_12_down_arr_1_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_time_12_down_arr_1, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_time_12_down_arr_1,&_Setting_Drow_Arrow_20x11);
	lv_img_set_pivot(ui->Setting_Screen_time_12_down_arr_1, 0,0);
	lv_img_set_angle(ui->Setting_Screen_time_12_down_arr_1, 0);

	//Write codes Setting_Screen_time_12_down_arr_2
	ui->Setting_Screen_time_12_down_arr_2 = lv_img_create(ui->Setting_Screen_setting_time_12_container);
	lv_obj_set_pos(ui->Setting_Screen_time_12_down_arr_2, 134, 190);
	lv_obj_set_size(ui->Setting_Screen_time_12_down_arr_2, 20, 11);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_time_12_down_arr_2_main_main_default
	static lv_style_t style_setting_screen_time_12_down_arr_2_main_main_default;
	lv_style_reset(&style_setting_screen_time_12_down_arr_2_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_time_12_down_arr_2_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_time_12_down_arr_2_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_time_12_down_arr_2_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_time_12_down_arr_2, &style_setting_screen_time_12_down_arr_2_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_time_12_down_arr_2, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_time_12_down_arr_2,&_Setting_Drow_Arrow_20x11);
	lv_img_set_pivot(ui->Setting_Screen_time_12_down_arr_2, 0,0);
	lv_img_set_angle(ui->Setting_Screen_time_12_down_arr_2, 0);

	//Write codes Setting_Screen_time_12_lbl_1
	ui->Setting_Screen_time_12_lbl_1 = lv_label_create(ui->Setting_Screen_setting_time_12_container);
	lv_obj_set_pos(ui->Setting_Screen_time_12_lbl_1, 85, 148);
	lv_obj_set_size(ui->Setting_Screen_time_12_lbl_1, 21, 18);
	lv_label_set_text(ui->Setting_Screen_time_12_lbl_1, "99");
	lv_label_set_long_mode(ui->Setting_Screen_time_12_lbl_1, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->Setting_Screen_time_12_lbl_1, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_time_12_lbl_1_main_main_default
	static lv_style_t style_setting_screen_time_12_lbl_1_main_main_default;
	lv_style_reset(&style_setting_screen_time_12_lbl_1_main_main_default);
	lv_style_set_radius(&style_setting_screen_time_12_lbl_1_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_time_12_lbl_1_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_setting_screen_time_12_lbl_1_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_setting_screen_time_12_lbl_1_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_time_12_lbl_1_main_main_default, 0);
	lv_style_set_text_color(&style_setting_screen_time_12_lbl_1_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_setting_screen_time_12_lbl_1_main_main_default, &lv_font_FjallaOne_Regular_22);
	lv_style_set_text_letter_space(&style_setting_screen_time_12_lbl_1_main_main_default, 0);
	lv_style_set_pad_left(&style_setting_screen_time_12_lbl_1_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_time_12_lbl_1_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_time_12_lbl_1_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_time_12_lbl_1_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_time_12_lbl_1, &style_setting_screen_time_12_lbl_1_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_time_12_lbl_2
	ui->Setting_Screen_time_12_lbl_2 = lv_label_create(ui->Setting_Screen_setting_time_12_container);
	lv_obj_set_pos(ui->Setting_Screen_time_12_lbl_2, 134, 148);
	lv_obj_set_size(ui->Setting_Screen_time_12_lbl_2, 21, 18);
	lv_label_set_text(ui->Setting_Screen_time_12_lbl_2, "99");
	lv_label_set_long_mode(ui->Setting_Screen_time_12_lbl_2, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->Setting_Screen_time_12_lbl_2, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_time_12_lbl_2_main_main_default
	static lv_style_t style_setting_screen_time_12_lbl_2_main_main_default;
	lv_style_reset(&style_setting_screen_time_12_lbl_2_main_main_default);
	lv_style_set_radius(&style_setting_screen_time_12_lbl_2_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_time_12_lbl_2_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_setting_screen_time_12_lbl_2_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_setting_screen_time_12_lbl_2_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_time_12_lbl_2_main_main_default, 0);
	lv_style_set_text_color(&style_setting_screen_time_12_lbl_2_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_setting_screen_time_12_lbl_2_main_main_default, &lv_font_FjallaOne_Regular_22);
	lv_style_set_text_letter_space(&style_setting_screen_time_12_lbl_2_main_main_default, 0);
	lv_style_set_pad_left(&style_setting_screen_time_12_lbl_2_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_time_12_lbl_2_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_time_12_lbl_2_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_time_12_lbl_2_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_time_12_lbl_2, &style_setting_screen_time_12_lbl_2_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_time_12_hold_lbl
	ui->Setting_Screen_time_12_hold_lbl = lv_label_create(ui->Setting_Screen_setting_time_12_container);
	lv_obj_set_pos(ui->Setting_Screen_time_12_hold_lbl, 68, 231);
	lv_obj_set_size(ui->Setting_Screen_time_12_hold_lbl, 27, 13);
	lv_label_set_text(ui->Setting_Screen_time_12_hold_lbl, "Hold");
	lv_label_set_long_mode(ui->Setting_Screen_time_12_hold_lbl, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->Setting_Screen_time_12_hold_lbl, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_time_12_hold_lbl_main_main_default
	static lv_style_t style_setting_screen_time_12_hold_lbl_main_main_default;
	lv_style_reset(&style_setting_screen_time_12_hold_lbl_main_main_default);
	lv_style_set_radius(&style_setting_screen_time_12_hold_lbl_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_time_12_hold_lbl_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_setting_screen_time_12_hold_lbl_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_setting_screen_time_12_hold_lbl_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_time_12_hold_lbl_main_main_default, 0);
	lv_style_set_text_color(&style_setting_screen_time_12_hold_lbl_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_setting_screen_time_12_hold_lbl_main_main_default, &lv_font_FjallaOne_Regular_14);
	lv_style_set_text_letter_space(&style_setting_screen_time_12_hold_lbl_main_main_default, 0);
	lv_style_set_pad_left(&style_setting_screen_time_12_hold_lbl_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_time_12_hold_lbl_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_time_12_hold_lbl_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_time_12_hold_lbl_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_time_12_hold_lbl, &style_setting_screen_time_12_hold_lbl_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_time_12_toset_lbl
	ui->Setting_Screen_time_12_toset_lbl = lv_label_create(ui->Setting_Screen_setting_time_12_container);
	lv_obj_set_pos(ui->Setting_Screen_time_12_toset_lbl, 127, 231);
	lv_obj_set_size(ui->Setting_Screen_time_12_toset_lbl, 37, 14);
	lv_label_set_text(ui->Setting_Screen_time_12_toset_lbl, "toSET");
	lv_label_set_long_mode(ui->Setting_Screen_time_12_toset_lbl, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->Setting_Screen_time_12_toset_lbl, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_time_12_toset_lbl_main_main_default
	static lv_style_t style_setting_screen_time_12_toset_lbl_main_main_default;
	lv_style_reset(&style_setting_screen_time_12_toset_lbl_main_main_default);
	lv_style_set_radius(&style_setting_screen_time_12_toset_lbl_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_time_12_toset_lbl_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_setting_screen_time_12_toset_lbl_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_setting_screen_time_12_toset_lbl_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_time_12_toset_lbl_main_main_default, 0);
	lv_style_set_text_color(&style_setting_screen_time_12_toset_lbl_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_setting_screen_time_12_toset_lbl_main_main_default, &lv_font_FjallaOne_Regular_14);
	lv_style_set_text_letter_space(&style_setting_screen_time_12_toset_lbl_main_main_default, 0);
	lv_style_set_pad_left(&style_setting_screen_time_12_toset_lbl_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_time_12_toset_lbl_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_time_12_toset_lbl_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_time_12_toset_lbl_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_time_12_toset_lbl, &style_setting_screen_time_12_toset_lbl_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_time_12_sub_btn_lbl
	ui->Setting_Screen_time_12_sub_btn_lbl = lv_img_create(ui->Setting_Screen_setting_time_12_container);
	lv_obj_set_pos(ui->Setting_Screen_time_12_sub_btn_lbl, 101, 225);
	lv_obj_set_size(ui->Setting_Screen_time_12_sub_btn_lbl, 20, 20);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_time_12_sub_btn_lbl_main_main_default
	static lv_style_t style_setting_screen_time_12_sub_btn_lbl_main_main_default;
	lv_style_reset(&style_setting_screen_time_12_sub_btn_lbl_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_time_12_sub_btn_lbl_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_time_12_sub_btn_lbl_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_time_12_sub_btn_lbl_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_time_12_sub_btn_lbl, &style_setting_screen_time_12_sub_btn_lbl_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_time_12_sub_btn_lbl, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_time_12_sub_btn_lbl,&_img_night_menu_btn_20x20);
	lv_img_set_pivot(ui->Setting_Screen_time_12_sub_btn_lbl, 0,0);
	lv_img_set_angle(ui->Setting_Screen_time_12_sub_btn_lbl, 0);

	//Write codes Setting_Screen_setting_time_12_day_container
	ui->Setting_Screen_setting_time_12_day_container = lv_obj_create(ui->Setting_Screen);
	lv_obj_set_pos(ui->Setting_Screen_setting_time_12_day_container, 0, 0);
	lv_obj_set_size(ui->Setting_Screen_setting_time_12_day_container, 240, 320);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_setting_time_12_day_container_main_main_default
	static lv_style_t style_setting_screen_setting_time_12_day_container_main_main_default;
	lv_style_reset(&style_setting_screen_setting_time_12_day_container_main_main_default);
	lv_style_set_radius(&style_setting_screen_setting_time_12_day_container_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_setting_time_12_day_container_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_color(&style_setting_screen_setting_time_12_day_container_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_dir(&style_setting_screen_setting_time_12_day_container_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_setting_time_12_day_container_main_main_default, 0);
	lv_style_set_border_color(&style_setting_screen_setting_time_12_day_container_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_border_width(&style_setting_screen_setting_time_12_day_container_main_main_default, 0);
	lv_style_set_border_opa(&style_setting_screen_setting_time_12_day_container_main_main_default, 255);
	lv_style_set_pad_left(&style_setting_screen_setting_time_12_day_container_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_setting_time_12_day_container_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_setting_time_12_day_container_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_setting_time_12_day_container_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_setting_time_12_day_container, &style_setting_screen_setting_time_12_day_container_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_time_12_day_circle
	ui->Setting_Screen_time_12_day_circle = lv_img_create(ui->Setting_Screen_setting_time_12_day_container);
	lv_obj_set_pos(ui->Setting_Screen_time_12_day_circle, 7, 47);
	lv_obj_set_size(ui->Setting_Screen_time_12_day_circle, 226, 226);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_time_12_day_circle_main_main_default
	static lv_style_t style_setting_screen_time_12_day_circle_main_main_default;
	lv_style_reset(&style_setting_screen_time_12_day_circle_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_time_12_day_circle_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_time_12_day_circle_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_time_12_day_circle_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_time_12_day_circle, &style_setting_screen_time_12_day_circle_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_time_12_day_circle, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_time_12_day_circle,&day_white_Grey_circle);
	lv_img_set_pivot(ui->Setting_Screen_time_12_day_circle, 0,0);
	lv_img_set_angle(ui->Setting_Screen_time_12_day_circle, 0);

	//Write codes Setting_Screen_time_12_up_arr_day_1
	ui->Setting_Screen_time_12_up_arr_day_1 = lv_img_create(ui->Setting_Screen_setting_time_12_day_container);
	lv_obj_set_pos(ui->Setting_Screen_time_12_up_arr_day_1, 86, 120);
	lv_obj_set_size(ui->Setting_Screen_time_12_up_arr_day_1, 20, 11);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_time_12_up_arr_day_1_main_main_default
	static lv_style_t style_setting_screen_time_12_up_arr_day_1_main_main_default;
	lv_style_reset(&style_setting_screen_time_12_up_arr_day_1_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_time_12_up_arr_day_1_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_time_12_up_arr_day_1_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_time_12_up_arr_day_1_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_time_12_up_arr_day_1, &style_setting_screen_time_12_up_arr_day_1_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_time_12_up_arr_day_1, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_time_12_up_arr_day_1,&_day_up_arrow_20x11);
	lv_img_set_pivot(ui->Setting_Screen_time_12_up_arr_day_1, 0,0);
	lv_img_set_angle(ui->Setting_Screen_time_12_up_arr_day_1, 0);

	//Write codes Setting_Screen_time_12_up_arr_day_2
	ui->Setting_Screen_time_12_up_arr_day_2 = lv_img_create(ui->Setting_Screen_setting_time_12_day_container);
	lv_obj_set_pos(ui->Setting_Screen_time_12_up_arr_day_2, 134, 120);
	lv_obj_set_size(ui->Setting_Screen_time_12_up_arr_day_2, 20, 11);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_time_12_up_arr_day_2_main_main_default
	static lv_style_t style_setting_screen_time_12_up_arr_day_2_main_main_default;
	lv_style_reset(&style_setting_screen_time_12_up_arr_day_2_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_time_12_up_arr_day_2_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_time_12_up_arr_day_2_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_time_12_up_arr_day_2_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_time_12_up_arr_day_2, &style_setting_screen_time_12_up_arr_day_2_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_time_12_up_arr_day_2, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_time_12_up_arr_day_2,&_day_up_arrow_20x11);
	lv_img_set_pivot(ui->Setting_Screen_time_12_up_arr_day_2, 0,0);
	lv_img_set_angle(ui->Setting_Screen_time_12_up_arr_day_2, 0);

	//Write codes Setting_Screen_time_12_down_arr_day_1
	ui->Setting_Screen_time_12_down_arr_day_1 = lv_img_create(ui->Setting_Screen_setting_time_12_day_container);
	lv_obj_set_pos(ui->Setting_Screen_time_12_down_arr_day_1, 86, 190);
	lv_obj_set_size(ui->Setting_Screen_time_12_down_arr_day_1, 20, 11);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_time_12_down_arr_day_1_main_main_default
	static lv_style_t style_setting_screen_time_12_down_arr_day_1_main_main_default;
	lv_style_reset(&style_setting_screen_time_12_down_arr_day_1_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_time_12_down_arr_day_1_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_time_12_down_arr_day_1_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_time_12_down_arr_day_1_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_time_12_down_arr_day_1, &style_setting_screen_time_12_down_arr_day_1_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_time_12_down_arr_day_1, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_time_12_down_arr_day_1,&_day_down_arrow_20x11);
	lv_img_set_pivot(ui->Setting_Screen_time_12_down_arr_day_1, 0,0);
	lv_img_set_angle(ui->Setting_Screen_time_12_down_arr_day_1, 0);

	//Write codes Setting_Screen_time_12_down_arr_day_2
	ui->Setting_Screen_time_12_down_arr_day_2 = lv_img_create(ui->Setting_Screen_setting_time_12_day_container);
	lv_obj_set_pos(ui->Setting_Screen_time_12_down_arr_day_2, 134, 190);
	lv_obj_set_size(ui->Setting_Screen_time_12_down_arr_day_2, 20, 11);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_time_12_down_arr_day_2_main_main_default
	static lv_style_t style_setting_screen_time_12_down_arr_day_2_main_main_default;
	lv_style_reset(&style_setting_screen_time_12_down_arr_day_2_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_time_12_down_arr_day_2_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_time_12_down_arr_day_2_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_time_12_down_arr_day_2_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_time_12_down_arr_day_2, &style_setting_screen_time_12_down_arr_day_2_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_time_12_down_arr_day_2, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_time_12_down_arr_day_2,&_day_down_arrow_20x11);
	lv_img_set_pivot(ui->Setting_Screen_time_12_down_arr_day_2, 0,0);
	lv_img_set_angle(ui->Setting_Screen_time_12_down_arr_day_2, 0);

	//Write codes Setting_Screen_time_12_day_lbl1
	ui->Setting_Screen_time_12_day_lbl1 = lv_label_create(ui->Setting_Screen_setting_time_12_day_container);
	lv_obj_set_pos(ui->Setting_Screen_time_12_day_lbl1, 85, 148);
	lv_obj_set_size(ui->Setting_Screen_time_12_day_lbl1, 21, 18);
	lv_label_set_text(ui->Setting_Screen_time_12_day_lbl1, "99");
	lv_label_set_long_mode(ui->Setting_Screen_time_12_day_lbl1, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->Setting_Screen_time_12_day_lbl1, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_time_12_day_lbl1_main_main_default
	static lv_style_t style_setting_screen_time_12_day_lbl1_main_main_default;
	lv_style_reset(&style_setting_screen_time_12_day_lbl1_main_main_default);
	lv_style_set_radius(&style_setting_screen_time_12_day_lbl1_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_time_12_day_lbl1_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_setting_screen_time_12_day_lbl1_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_setting_screen_time_12_day_lbl1_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_time_12_day_lbl1_main_main_default, 0);
	lv_style_set_text_color(&style_setting_screen_time_12_day_lbl1_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_setting_screen_time_12_day_lbl1_main_main_default, &lv_font_FjallaOne_Regular_22);
	lv_style_set_text_letter_space(&style_setting_screen_time_12_day_lbl1_main_main_default, 0);
	lv_style_set_pad_left(&style_setting_screen_time_12_day_lbl1_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_time_12_day_lbl1_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_time_12_day_lbl1_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_time_12_day_lbl1_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_time_12_day_lbl1, &style_setting_screen_time_12_day_lbl1_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_time_12_day_lbl2
	ui->Setting_Screen_time_12_day_lbl2 = lv_label_create(ui->Setting_Screen_setting_time_12_day_container);
	lv_obj_set_pos(ui->Setting_Screen_time_12_day_lbl2, 139, 148);
	lv_obj_set_size(ui->Setting_Screen_time_12_day_lbl2, 21, 18);
	lv_label_set_text(ui->Setting_Screen_time_12_day_lbl2, "99");
	lv_label_set_long_mode(ui->Setting_Screen_time_12_day_lbl2, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->Setting_Screen_time_12_day_lbl2, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_time_12_day_lbl2_main_main_default
	static lv_style_t style_setting_screen_time_12_day_lbl2_main_main_default;
	lv_style_reset(&style_setting_screen_time_12_day_lbl2_main_main_default);
	lv_style_set_radius(&style_setting_screen_time_12_day_lbl2_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_time_12_day_lbl2_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_setting_screen_time_12_day_lbl2_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_setting_screen_time_12_day_lbl2_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_time_12_day_lbl2_main_main_default, 0);
	lv_style_set_text_color(&style_setting_screen_time_12_day_lbl2_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_setting_screen_time_12_day_lbl2_main_main_default, &lv_font_FjallaOne_Regular_22);
	lv_style_set_text_letter_space(&style_setting_screen_time_12_day_lbl2_main_main_default, 0);
	lv_style_set_pad_left(&style_setting_screen_time_12_day_lbl2_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_time_12_day_lbl2_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_time_12_day_lbl2_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_time_12_day_lbl2_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_time_12_day_lbl2, &style_setting_screen_time_12_day_lbl2_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_time_12_day_hold_lbl
	ui->Setting_Screen_time_12_day_hold_lbl = lv_label_create(ui->Setting_Screen_setting_time_12_day_container);
	lv_obj_set_pos(ui->Setting_Screen_time_12_day_hold_lbl, 62, 231);
	lv_obj_set_size(ui->Setting_Screen_time_12_day_hold_lbl, 27, 13);
	lv_label_set_text(ui->Setting_Screen_time_12_day_hold_lbl, "Hold");
	lv_label_set_long_mode(ui->Setting_Screen_time_12_day_hold_lbl, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->Setting_Screen_time_12_day_hold_lbl, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_time_12_day_hold_lbl_main_main_default
	static lv_style_t style_setting_screen_time_12_day_hold_lbl_main_main_default;
	lv_style_reset(&style_setting_screen_time_12_day_hold_lbl_main_main_default);
	lv_style_set_radius(&style_setting_screen_time_12_day_hold_lbl_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_time_12_day_hold_lbl_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_setting_screen_time_12_day_hold_lbl_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_setting_screen_time_12_day_hold_lbl_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_time_12_day_hold_lbl_main_main_default, 0);
	lv_style_set_text_color(&style_setting_screen_time_12_day_hold_lbl_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_setting_screen_time_12_day_hold_lbl_main_main_default, &lv_font_FjallaOne_Regular_14);
	lv_style_set_text_letter_space(&style_setting_screen_time_12_day_hold_lbl_main_main_default, 0);
	lv_style_set_pad_left(&style_setting_screen_time_12_day_hold_lbl_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_time_12_day_hold_lbl_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_time_12_day_hold_lbl_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_time_12_day_hold_lbl_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_time_12_day_hold_lbl, &style_setting_screen_time_12_day_hold_lbl_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_time_12_day_sub_btn
	ui->Setting_Screen_time_12_day_sub_btn = lv_label_create(ui->Setting_Screen_setting_time_12_day_container);
	lv_obj_set_pos(ui->Setting_Screen_time_12_day_sub_btn, 127, 232);
	lv_obj_set_size(ui->Setting_Screen_time_12_day_sub_btn, 37, 14);
	lv_label_set_text(ui->Setting_Screen_time_12_day_sub_btn, "toSET");
	lv_label_set_long_mode(ui->Setting_Screen_time_12_day_sub_btn, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->Setting_Screen_time_12_day_sub_btn, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_time_12_day_sub_btn_main_main_default
	static lv_style_t style_setting_screen_time_12_day_sub_btn_main_main_default;
	lv_style_reset(&style_setting_screen_time_12_day_sub_btn_main_main_default);
	lv_style_set_radius(&style_setting_screen_time_12_day_sub_btn_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_time_12_day_sub_btn_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_setting_screen_time_12_day_sub_btn_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_setting_screen_time_12_day_sub_btn_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_time_12_day_sub_btn_main_main_default, 0);
	lv_style_set_text_color(&style_setting_screen_time_12_day_sub_btn_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_setting_screen_time_12_day_sub_btn_main_main_default, &lv_font_FjallaOne_Regular_14);
	lv_style_set_text_letter_space(&style_setting_screen_time_12_day_sub_btn_main_main_default, 0);
	lv_style_set_pad_left(&style_setting_screen_time_12_day_sub_btn_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_time_12_day_sub_btn_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_time_12_day_sub_btn_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_time_12_day_sub_btn_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_time_12_day_sub_btn, &style_setting_screen_time_12_day_sub_btn_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_time_12_day_toset_lbl
	ui->Setting_Screen_time_12_day_toset_lbl = lv_img_create(ui->Setting_Screen_setting_time_12_day_container);
	lv_obj_set_pos(ui->Setting_Screen_time_12_day_toset_lbl, 101, 225);
	lv_obj_set_size(ui->Setting_Screen_time_12_day_toset_lbl, 20, 20);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_time_12_day_toset_lbl_main_main_default
	static lv_style_t style_setting_screen_time_12_day_toset_lbl_main_main_default;
	lv_style_reset(&style_setting_screen_time_12_day_toset_lbl_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_time_12_day_toset_lbl_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_time_12_day_toset_lbl_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_time_12_day_toset_lbl_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_time_12_day_toset_lbl, &style_setting_screen_time_12_day_toset_lbl_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_time_12_day_toset_lbl, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_time_12_day_toset_lbl,&_day_sub_btn_20x20);
	lv_img_set_pivot(ui->Setting_Screen_time_12_day_toset_lbl, 0,0);
	lv_img_set_angle(ui->Setting_Screen_time_12_day_toset_lbl, 0);

	//Write codes Setting_Screen_setting_battery_container
	ui->Setting_Screen_setting_battery_container = lv_obj_create(ui->Setting_Screen);
	lv_obj_set_pos(ui->Setting_Screen_setting_battery_container, 0, 0);
	lv_obj_set_size(ui->Setting_Screen_setting_battery_container, 240, 320);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_setting_battery_container_main_main_default
	static lv_style_t style_setting_screen_setting_battery_container_main_main_default;
	lv_style_reset(&style_setting_screen_setting_battery_container_main_main_default);
	lv_style_set_radius(&style_setting_screen_setting_battery_container_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_setting_battery_container_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_color(&style_setting_screen_setting_battery_container_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_dir(&style_setting_screen_setting_battery_container_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_setting_battery_container_main_main_default, 0);
	lv_style_set_border_color(&style_setting_screen_setting_battery_container_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_border_width(&style_setting_screen_setting_battery_container_main_main_default, 0);
	lv_style_set_border_opa(&style_setting_screen_setting_battery_container_main_main_default, 255);
	lv_style_set_pad_left(&style_setting_screen_setting_battery_container_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_setting_battery_container_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_setting_battery_container_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_setting_battery_container_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_setting_battery_container, &style_setting_screen_setting_battery_container_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_battery_img
	ui->Setting_Screen_battery_img = lv_img_create(ui->Setting_Screen_setting_battery_container);
	lv_obj_set_pos(ui->Setting_Screen_battery_img, 16, 142);
	lv_obj_set_size(ui->Setting_Screen_battery_img, 40, 40);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_battery_img_main_main_default
	static lv_style_t style_setting_screen_battery_img_main_main_default;
	lv_style_reset(&style_setting_screen_battery_img_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_battery_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_battery_img_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_battery_img_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_battery_img, &style_setting_screen_battery_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_battery_lbl1
	ui->Setting_Screen_battery_lbl1 = lv_label_create(ui->Setting_Screen_setting_battery_container);
	lv_obj_set_pos(ui->Setting_Screen_battery_lbl1, 0, 148);
	lv_obj_set_size(ui->Setting_Screen_battery_lbl1, 240, 18);
	lv_label_set_text(ui->Setting_Screen_battery_lbl1, "");
	lv_label_set_long_mode(ui->Setting_Screen_battery_lbl1, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->Setting_Screen_battery_lbl1, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_battery_lbl1_main_main_default
	static lv_style_t style_setting_screen_battery_lbl1_main_main_default;
	lv_style_reset(&style_setting_screen_battery_lbl1_main_main_default);
	lv_style_set_radius(&style_setting_screen_battery_lbl1_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_battery_lbl1_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_setting_screen_battery_lbl1_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_setting_screen_battery_lbl1_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_battery_lbl1_main_main_default, 0);
	lv_style_set_text_color(&style_setting_screen_battery_lbl1_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_setting_screen_battery_lbl1_main_main_default, &lv_font_FjallaOne_Regular_22);
	lv_style_set_text_letter_space(&style_setting_screen_battery_lbl1_main_main_default, 0);
	lv_style_set_pad_left(&style_setting_screen_battery_lbl1_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_battery_lbl1_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_battery_lbl1_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_battery_lbl1_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_battery_lbl1, &style_setting_screen_battery_lbl1_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_setting_battery_day_container
	ui->Setting_Screen_setting_battery_day_container = lv_obj_create(ui->Setting_Screen);
	lv_obj_set_pos(ui->Setting_Screen_setting_battery_day_container, 0, 0);
	lv_obj_set_size(ui->Setting_Screen_setting_battery_day_container, 240, 320);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_setting_battery_day_container_main_main_default
	static lv_style_t style_setting_screen_setting_battery_day_container_main_main_default;
	lv_style_reset(&style_setting_screen_setting_battery_day_container_main_main_default);
	lv_style_set_radius(&style_setting_screen_setting_battery_day_container_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_setting_battery_day_container_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_color(&style_setting_screen_setting_battery_day_container_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_dir(&style_setting_screen_setting_battery_day_container_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_setting_battery_day_container_main_main_default, 0);
	lv_style_set_border_color(&style_setting_screen_setting_battery_day_container_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_border_width(&style_setting_screen_setting_battery_day_container_main_main_default, 0);
	lv_style_set_border_opa(&style_setting_screen_setting_battery_day_container_main_main_default, 255);
	lv_style_set_pad_left(&style_setting_screen_setting_battery_day_container_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_setting_battery_day_container_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_setting_battery_day_container_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_setting_battery_day_container_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_setting_battery_day_container, &style_setting_screen_setting_battery_day_container_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_battery_day_im
	ui->Setting_Screen_battery_day_im = lv_img_create(ui->Setting_Screen_setting_battery_day_container);
	lv_obj_set_pos(ui->Setting_Screen_battery_day_im, 7, 47);
	lv_obj_set_size(ui->Setting_Screen_battery_day_im, 226, 226);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_battery_day_im_main_main_default
	static lv_style_t style_setting_screen_battery_day_im_main_main_default;
	lv_style_reset(&style_setting_screen_battery_day_im_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_battery_day_im_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_battery_day_im_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_battery_day_im_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_battery_day_im, &style_setting_screen_battery_day_im_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_battery_day_im, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_battery_day_im,&day_white_Grey_circle);
	lv_img_set_pivot(ui->Setting_Screen_battery_day_im, 0,0);
	lv_img_set_angle(ui->Setting_Screen_battery_day_im, 0);

	//Write codes Setting_Screen_battery_day_img
	ui->Setting_Screen_battery_day_img = lv_img_create(ui->Setting_Screen_setting_battery_day_container);
	lv_obj_set_pos(ui->Setting_Screen_battery_day_img, 16, 142);
	lv_obj_set_size(ui->Setting_Screen_battery_day_img, 40, 40);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_battery_day_img_main_main_default
	static lv_style_t style_setting_screen_battery_day_img_main_main_default;
	lv_style_reset(&style_setting_screen_battery_day_img_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_battery_day_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_battery_day_img_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_battery_day_img_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_battery_day_img, &style_setting_screen_battery_day_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_battery_day_lbl1
	ui->Setting_Screen_battery_day_lbl1 = lv_label_create(ui->Setting_Screen_setting_battery_day_container);
	lv_obj_set_pos(ui->Setting_Screen_battery_day_lbl1, 0, 148);
	lv_obj_set_size(ui->Setting_Screen_battery_day_lbl1, 240, 18);
	lv_label_set_text(ui->Setting_Screen_battery_day_lbl1, "");
	lv_label_set_long_mode(ui->Setting_Screen_battery_day_lbl1, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->Setting_Screen_battery_day_lbl1, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_battery_day_lbl1_main_main_default
	static lv_style_t style_setting_screen_battery_day_lbl1_main_main_default;
	lv_style_reset(&style_setting_screen_battery_day_lbl1_main_main_default);
	lv_style_set_radius(&style_setting_screen_battery_day_lbl1_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_battery_day_lbl1_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_setting_screen_battery_day_lbl1_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_setting_screen_battery_day_lbl1_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_battery_day_lbl1_main_main_default, 0);
	lv_style_set_text_color(&style_setting_screen_battery_day_lbl1_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_setting_screen_battery_day_lbl1_main_main_default, &lv_font_FjallaOne_Regular_22);
	lv_style_set_text_letter_space(&style_setting_screen_battery_day_lbl1_main_main_default, 0);
	lv_style_set_pad_left(&style_setting_screen_battery_day_lbl1_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_battery_day_lbl1_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_battery_day_lbl1_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_battery_day_lbl1_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_battery_day_lbl1, &style_setting_screen_battery_day_lbl1_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_setting_trip_container
	ui->Setting_Screen_setting_trip_container = lv_obj_create(ui->Setting_Screen);
	lv_obj_set_pos(ui->Setting_Screen_setting_trip_container, 0, 0);
	lv_obj_set_size(ui->Setting_Screen_setting_trip_container, 240, 320);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_setting_trip_container_main_main_default
	static lv_style_t style_setting_screen_setting_trip_container_main_main_default;
	lv_style_reset(&style_setting_screen_setting_trip_container_main_main_default);
	lv_style_set_radius(&style_setting_screen_setting_trip_container_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_setting_trip_container_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_color(&style_setting_screen_setting_trip_container_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_dir(&style_setting_screen_setting_trip_container_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_setting_trip_container_main_main_default, 0);
	lv_style_set_border_color(&style_setting_screen_setting_trip_container_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_border_width(&style_setting_screen_setting_trip_container_main_main_default, 0);
	lv_style_set_border_opa(&style_setting_screen_setting_trip_container_main_main_default, 255);
	lv_style_set_pad_left(&style_setting_screen_setting_trip_container_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_setting_trip_container_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_setting_trip_container_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_setting_trip_container_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_setting_trip_container, &style_setting_screen_setting_trip_container_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_trip_up_arr_img
	ui->Setting_Screen_trip_up_arr_img = lv_img_create(ui->Setting_Screen_setting_trip_container);
	lv_obj_set_pos(ui->Setting_Screen_trip_up_arr_img, 110, 65);
	lv_obj_set_size(ui->Setting_Screen_trip_up_arr_img, 20, 11);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_trip_up_arr_img_main_main_default
	static lv_style_t style_setting_screen_trip_up_arr_img_main_main_default;
	lv_style_reset(&style_setting_screen_trip_up_arr_img_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_trip_up_arr_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_trip_up_arr_img_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_trip_up_arr_img_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_trip_up_arr_img, &style_setting_screen_trip_up_arr_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_trip_up_arr_img, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_trip_up_arr_img,&_Setting_Up_Arrow_20x11);
	lv_img_set_pivot(ui->Setting_Screen_trip_up_arr_img, 0,0);
	lv_img_set_angle(ui->Setting_Screen_trip_up_arr_img, 0);

	//Write codes Setting_Screen_trip_down_arr_img
	ui->Setting_Screen_trip_down_arr_img = lv_img_create(ui->Setting_Screen_setting_trip_container);
	lv_obj_set_pos(ui->Setting_Screen_trip_down_arr_img, 110, 238);
	lv_obj_set_size(ui->Setting_Screen_trip_down_arr_img, 20, 11);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_trip_down_arr_img_main_main_default
	static lv_style_t style_setting_screen_trip_down_arr_img_main_main_default;
	lv_style_reset(&style_setting_screen_trip_down_arr_img_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_trip_down_arr_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_trip_down_arr_img_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_trip_down_arr_img_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_trip_down_arr_img, &style_setting_screen_trip_down_arr_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_trip_down_arr_img, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_trip_down_arr_img,&_Setting_Drow_Arrow_20x11);
	lv_img_set_pivot(ui->Setting_Screen_trip_down_arr_img, 0,0);
	lv_img_set_angle(ui->Setting_Screen_trip_down_arr_img, 0);

	//Write codes Setting_Screen_trip_lbl1
	ui->Setting_Screen_trip_lbl1 = lv_label_create(ui->Setting_Screen_setting_trip_container);
	lv_obj_set_pos(ui->Setting_Screen_trip_lbl1, 20, 97);
	lv_obj_set_size(ui->Setting_Screen_trip_lbl1, 200, 26);
	lv_label_set_text(ui->Setting_Screen_trip_lbl1, "Av Speed 999 L/100km");
	lv_label_set_long_mode(ui->Setting_Screen_trip_lbl1, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->Setting_Screen_trip_lbl1, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_trip_lbl1_main_main_default
	static lv_style_t style_setting_screen_trip_lbl1_main_main_default;
	lv_style_reset(&style_setting_screen_trip_lbl1_main_main_default);
	lv_style_set_radius(&style_setting_screen_trip_lbl1_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_trip_lbl1_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_setting_screen_trip_lbl1_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_setting_screen_trip_lbl1_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_trip_lbl1_main_main_default, 0);
	lv_style_set_text_color(&style_setting_screen_trip_lbl1_main_main_default, lv_color_make(0x50, 0x50, 0x50));
	lv_style_set_text_font(&style_setting_screen_trip_lbl1_main_main_default, &lv_font_FjallaOne_Regular_22);
	lv_style_set_text_letter_space(&style_setting_screen_trip_lbl1_main_main_default, 0);
	lv_style_set_pad_left(&style_setting_screen_trip_lbl1_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_trip_lbl1_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_trip_lbl1_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_trip_lbl1_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_trip_lbl1, &style_setting_screen_trip_lbl1_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_trip_lbl2
	ui->Setting_Screen_trip_lbl2 = lv_label_create(ui->Setting_Screen_setting_trip_container);
	lv_obj_set_pos(ui->Setting_Screen_trip_lbl2, 20, 145);
	lv_obj_set_size(ui->Setting_Screen_trip_lbl2, 200, 26);
	lv_label_set_text(ui->Setting_Screen_trip_lbl2, "Av Speed 999 L/100km");
	lv_label_set_long_mode(ui->Setting_Screen_trip_lbl2, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->Setting_Screen_trip_lbl2, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_trip_lbl2_main_main_default
	static lv_style_t style_setting_screen_trip_lbl2_main_main_default;
	lv_style_reset(&style_setting_screen_trip_lbl2_main_main_default);
	lv_style_set_radius(&style_setting_screen_trip_lbl2_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_trip_lbl2_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_setting_screen_trip_lbl2_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_setting_screen_trip_lbl2_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_trip_lbl2_main_main_default, 0);
	lv_style_set_text_color(&style_setting_screen_trip_lbl2_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_setting_screen_trip_lbl2_main_main_default, &lv_font_FjallaOne_Regular_22);
	lv_style_set_text_letter_space(&style_setting_screen_trip_lbl2_main_main_default, 0);
	lv_style_set_pad_left(&style_setting_screen_trip_lbl2_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_trip_lbl2_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_trip_lbl2_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_trip_lbl2_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_trip_lbl2, &style_setting_screen_trip_lbl2_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_trip_lbl3
	ui->Setting_Screen_trip_lbl3 = lv_label_create(ui->Setting_Screen_setting_trip_container);
	lv_obj_set_pos(ui->Setting_Screen_trip_lbl3, 20, 193);
	lv_obj_set_size(ui->Setting_Screen_trip_lbl3, 200, 26);
	lv_label_set_text(ui->Setting_Screen_trip_lbl3, "Hold           to   Set");
	lv_label_set_long_mode(ui->Setting_Screen_trip_lbl3, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->Setting_Screen_trip_lbl3, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_trip_lbl3_main_main_default
	static lv_style_t style_setting_screen_trip_lbl3_main_main_default;
	lv_style_reset(&style_setting_screen_trip_lbl3_main_main_default);
	lv_style_set_radius(&style_setting_screen_trip_lbl3_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_trip_lbl3_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_setting_screen_trip_lbl3_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_setting_screen_trip_lbl3_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_trip_lbl3_main_main_default, 0);
	lv_style_set_text_color(&style_setting_screen_trip_lbl3_main_main_default, lv_color_make(0x50, 0x50, 0x50));
	lv_style_set_text_font(&style_setting_screen_trip_lbl3_main_main_default, &lv_font_FjallaOne_Regular_22);
	lv_style_set_text_letter_space(&style_setting_screen_trip_lbl3_main_main_default, 0);
	lv_style_set_pad_left(&style_setting_screen_trip_lbl3_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_trip_lbl3_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_trip_lbl3_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_trip_lbl3_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_trip_lbl3, &style_setting_screen_trip_lbl3_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_trip_hold_btn
	ui->Setting_Screen_trip_hold_btn = lv_img_create(ui->Setting_Screen_setting_trip_container);
	lv_obj_set_pos(ui->Setting_Screen_trip_hold_btn, 90, 118);
	lv_obj_set_size(ui->Setting_Screen_trip_hold_btn, 20, 20);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_trip_hold_btn_main_main_default
	static lv_style_t style_setting_screen_trip_hold_btn_main_main_default;
	lv_style_reset(&style_setting_screen_trip_hold_btn_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_trip_hold_btn_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_trip_hold_btn_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_trip_hold_btn_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_trip_hold_btn, &style_setting_screen_trip_hold_btn_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_trip_hold_btn, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_trip_hold_btn,&_img_night_menu_btn_20x20);
	lv_img_set_pivot(ui->Setting_Screen_trip_hold_btn, 0,0);
	lv_img_set_angle(ui->Setting_Screen_trip_hold_btn, 0);

	//Write codes Setting_Screen_setting_trip_day_container
	ui->Setting_Screen_setting_trip_day_container = lv_obj_create(ui->Setting_Screen);
	lv_obj_set_pos(ui->Setting_Screen_setting_trip_day_container, 0, 0);
	lv_obj_set_size(ui->Setting_Screen_setting_trip_day_container, 240, 320);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_setting_trip_day_container_main_main_default
	static lv_style_t style_setting_screen_setting_trip_day_container_main_main_default;
	lv_style_reset(&style_setting_screen_setting_trip_day_container_main_main_default);
	lv_style_set_radius(&style_setting_screen_setting_trip_day_container_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_setting_trip_day_container_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_color(&style_setting_screen_setting_trip_day_container_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_dir(&style_setting_screen_setting_trip_day_container_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_setting_trip_day_container_main_main_default, 0);
	lv_style_set_border_color(&style_setting_screen_setting_trip_day_container_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_border_width(&style_setting_screen_setting_trip_day_container_main_main_default, 0);
	lv_style_set_border_opa(&style_setting_screen_setting_trip_day_container_main_main_default, 255);
	lv_style_set_pad_left(&style_setting_screen_setting_trip_day_container_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_setting_trip_day_container_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_setting_trip_day_container_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_setting_trip_day_container_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_setting_trip_day_container, &style_setting_screen_setting_trip_day_container_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_trip_day_circle
	ui->Setting_Screen_trip_day_circle = lv_img_create(ui->Setting_Screen_setting_trip_day_container);
	lv_obj_set_pos(ui->Setting_Screen_trip_day_circle, 7, 47);
	lv_obj_set_size(ui->Setting_Screen_trip_day_circle, 226, 226);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_trip_day_circle_main_main_default
	static lv_style_t style_setting_screen_trip_day_circle_main_main_default;
	lv_style_reset(&style_setting_screen_trip_day_circle_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_trip_day_circle_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_trip_day_circle_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_trip_day_circle_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_trip_day_circle, &style_setting_screen_trip_day_circle_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_trip_day_circle, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_trip_day_circle,&day_white_Grey_circle);
	lv_img_set_pivot(ui->Setting_Screen_trip_day_circle, 0,0);
	lv_img_set_angle(ui->Setting_Screen_trip_day_circle, 0);

	//Write codes Setting_Screen_trip_day_up_arr
	ui->Setting_Screen_trip_day_up_arr = lv_img_create(ui->Setting_Screen_setting_trip_day_container);
	lv_obj_set_pos(ui->Setting_Screen_trip_day_up_arr, 110, 65);
	lv_obj_set_size(ui->Setting_Screen_trip_day_up_arr, 20, 11);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_trip_day_up_arr_main_main_default
	static lv_style_t style_setting_screen_trip_day_up_arr_main_main_default;
	lv_style_reset(&style_setting_screen_trip_day_up_arr_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_trip_day_up_arr_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_trip_day_up_arr_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_trip_day_up_arr_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_trip_day_up_arr, &style_setting_screen_trip_day_up_arr_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_trip_day_up_arr, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_trip_day_up_arr,&_day_up_arrow_20x11);
	lv_img_set_pivot(ui->Setting_Screen_trip_day_up_arr, 0,0);
	lv_img_set_angle(ui->Setting_Screen_trip_day_up_arr, 0);

	//Write codes Setting_Screen_trip_day_down_arr
	ui->Setting_Screen_trip_day_down_arr = lv_img_create(ui->Setting_Screen_setting_trip_day_container);
	lv_obj_set_pos(ui->Setting_Screen_trip_day_down_arr, 110, 238);
	lv_obj_set_size(ui->Setting_Screen_trip_day_down_arr, 20, 11);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_trip_day_down_arr_main_main_default
	static lv_style_t style_setting_screen_trip_day_down_arr_main_main_default;
	lv_style_reset(&style_setting_screen_trip_day_down_arr_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_trip_day_down_arr_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_trip_day_down_arr_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_trip_day_down_arr_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_trip_day_down_arr, &style_setting_screen_trip_day_down_arr_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_trip_day_down_arr, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_trip_day_down_arr,&_day_down_arrow_20x11);
	lv_img_set_pivot(ui->Setting_Screen_trip_day_down_arr, 0,0);
	lv_img_set_angle(ui->Setting_Screen_trip_day_down_arr, 0);

	//Write codes Setting_Screen_trip_day_lbl1
	ui->Setting_Screen_trip_day_lbl1 = lv_label_create(ui->Setting_Screen_setting_trip_day_container);
	lv_obj_set_pos(ui->Setting_Screen_trip_day_lbl1, 20, 97);
	lv_obj_set_size(ui->Setting_Screen_trip_day_lbl1, 200, 26);
	lv_label_set_text(ui->Setting_Screen_trip_day_lbl1, "Av Speed 999 L/100km");
	lv_label_set_long_mode(ui->Setting_Screen_trip_day_lbl1, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->Setting_Screen_trip_day_lbl1, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_trip_day_lbl1_main_main_default
	static lv_style_t style_setting_screen_trip_day_lbl1_main_main_default;
	lv_style_reset(&style_setting_screen_trip_day_lbl1_main_main_default);
	lv_style_set_radius(&style_setting_screen_trip_day_lbl1_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_trip_day_lbl1_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_setting_screen_trip_day_lbl1_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_setting_screen_trip_day_lbl1_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_trip_day_lbl1_main_main_default, 0);
	lv_style_set_text_color(&style_setting_screen_trip_day_lbl1_main_main_default, lv_color_make(0xb8, 0xb8, 0xb8));
	lv_style_set_text_font(&style_setting_screen_trip_day_lbl1_main_main_default, &lv_font_FjallaOne_Regular_22);
	lv_style_set_text_letter_space(&style_setting_screen_trip_day_lbl1_main_main_default, 0);
	lv_style_set_pad_left(&style_setting_screen_trip_day_lbl1_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_trip_day_lbl1_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_trip_day_lbl1_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_trip_day_lbl1_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_trip_day_lbl1, &style_setting_screen_trip_day_lbl1_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_trip_day_lbl2
	ui->Setting_Screen_trip_day_lbl2 = lv_label_create(ui->Setting_Screen_setting_trip_day_container);
	lv_obj_set_pos(ui->Setting_Screen_trip_day_lbl2, 20, 145);
	lv_obj_set_size(ui->Setting_Screen_trip_day_lbl2, 200, 26);
	lv_label_set_text(ui->Setting_Screen_trip_day_lbl2, "Av Speed 999 L/100km");
	lv_label_set_long_mode(ui->Setting_Screen_trip_day_lbl2, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->Setting_Screen_trip_day_lbl2, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_trip_day_lbl2_main_main_default
	static lv_style_t style_setting_screen_trip_day_lbl2_main_main_default;
	lv_style_reset(&style_setting_screen_trip_day_lbl2_main_main_default);
	lv_style_set_radius(&style_setting_screen_trip_day_lbl2_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_trip_day_lbl2_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_setting_screen_trip_day_lbl2_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_setting_screen_trip_day_lbl2_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_trip_day_lbl2_main_main_default, 0);
	lv_style_set_text_color(&style_setting_screen_trip_day_lbl2_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_setting_screen_trip_day_lbl2_main_main_default, &lv_font_FjallaOne_Regular_22);
	lv_style_set_text_letter_space(&style_setting_screen_trip_day_lbl2_main_main_default, 0);
	lv_style_set_pad_left(&style_setting_screen_trip_day_lbl2_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_trip_day_lbl2_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_trip_day_lbl2_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_trip_day_lbl2_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_trip_day_lbl2, &style_setting_screen_trip_day_lbl2_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_trip_day_lbl3
	ui->Setting_Screen_trip_day_lbl3 = lv_label_create(ui->Setting_Screen_setting_trip_day_container);
	lv_obj_set_pos(ui->Setting_Screen_trip_day_lbl3, 20, 193);
	lv_obj_set_size(ui->Setting_Screen_trip_day_lbl3, 200, 26);
	lv_label_set_text(ui->Setting_Screen_trip_day_lbl3, "Hold           to   Set");
	lv_label_set_long_mode(ui->Setting_Screen_trip_day_lbl3, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->Setting_Screen_trip_day_lbl3, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_trip_day_lbl3_main_main_default
	static lv_style_t style_setting_screen_trip_day_lbl3_main_main_default;
	lv_style_reset(&style_setting_screen_trip_day_lbl3_main_main_default);
	lv_style_set_radius(&style_setting_screen_trip_day_lbl3_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_trip_day_lbl3_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_setting_screen_trip_day_lbl3_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_setting_screen_trip_day_lbl3_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_trip_day_lbl3_main_main_default, 0);
	lv_style_set_text_color(&style_setting_screen_trip_day_lbl3_main_main_default, lv_color_make(0xb8, 0xb8, 0xb8));
	lv_style_set_text_font(&style_setting_screen_trip_day_lbl3_main_main_default, &lv_font_FjallaOne_Regular_22);
	lv_style_set_text_letter_space(&style_setting_screen_trip_day_lbl3_main_main_default, 0);
	lv_style_set_pad_left(&style_setting_screen_trip_day_lbl3_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_trip_day_lbl3_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_trip_day_lbl3_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_trip_day_lbl3_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_trip_day_lbl3, &style_setting_screen_trip_day_lbl3_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_trip_day_hold
	ui->Setting_Screen_trip_day_hold = lv_img_create(ui->Setting_Screen_setting_trip_day_container);
	lv_obj_set_pos(ui->Setting_Screen_trip_day_hold, 90, 118);
	lv_obj_set_size(ui->Setting_Screen_trip_day_hold, 20, 20);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_trip_day_hold_main_main_default
	static lv_style_t style_setting_screen_trip_day_hold_main_main_default;
	lv_style_reset(&style_setting_screen_trip_day_hold_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_trip_day_hold_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_trip_day_hold_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_trip_day_hold_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_trip_day_hold, &style_setting_screen_trip_day_hold_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_trip_day_hold, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_trip_day_hold,&_day_sub_btn_20x20);
	lv_img_set_pivot(ui->Setting_Screen_trip_day_hold, 0,0);
	lv_img_set_angle(ui->Setting_Screen_trip_day_hold, 0);


	//Write codes Setting_Screen_setting_disc_night_container
	ui->Setting_Screen_setting_disc_night_container = lv_obj_create(ui->Setting_Screen);
	lv_obj_set_pos(ui->Setting_Screen_setting_disc_night_container, 0, 0);
	lv_obj_set_size(ui->Setting_Screen_setting_disc_night_container, 240, 320);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_setting_disc_night_container_main_main_default
	static lv_style_t style_setting_screen_setting_disc_night_container_main_main_default;
	lv_style_reset(&style_setting_screen_setting_disc_night_container_main_main_default);
	lv_style_set_radius(&style_setting_screen_setting_disc_night_container_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_setting_disc_night_container_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_color(&style_setting_screen_setting_disc_night_container_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_dir(&style_setting_screen_setting_disc_night_container_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_setting_disc_night_container_main_main_default, 0);
	lv_style_set_border_color(&style_setting_screen_setting_disc_night_container_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_border_width(&style_setting_screen_setting_disc_night_container_main_main_default, 0);
	lv_style_set_border_opa(&style_setting_screen_setting_disc_night_container_main_main_default, 255);
	lv_style_set_pad_left(&style_setting_screen_setting_disc_night_container_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_setting_disc_night_container_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_setting_disc_night_container_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_setting_disc_night_container_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_setting_disc_night_container, &style_setting_screen_setting_disc_night_container_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_disc_up_arr_img
	ui->Setting_Screen_disc_up_arr_img = lv_img_create(ui->Setting_Screen_setting_disc_night_container);
	lv_obj_set_pos(ui->Setting_Screen_disc_up_arr_img, 110, 65);
	lv_obj_set_size(ui->Setting_Screen_disc_up_arr_img, 20, 11);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_disc_up_arr_img_main_main_default
	static lv_style_t style_setting_screen_disc_up_arr_img_main_main_default;
	lv_style_reset(&style_setting_screen_disc_up_arr_img_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_disc_up_arr_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_disc_up_arr_img_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_disc_up_arr_img_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_disc_up_arr_img, &style_setting_screen_disc_up_arr_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_disc_up_arr_img, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_disc_up_arr_img,&_Setting_Up_Arrow_20x11);
	lv_img_set_pivot(ui->Setting_Screen_disc_up_arr_img, 0,0);
	lv_img_set_angle(ui->Setting_Screen_disc_up_arr_img, 0);

	//Write codes Setting_Screen_disc_up_down_img
	ui->Setting_Screen_disc_up_down_img = lv_img_create(ui->Setting_Screen_setting_disc_night_container);
	lv_obj_set_pos(ui->Setting_Screen_disc_up_down_img, 110, 238);
	lv_obj_set_size(ui->Setting_Screen_disc_up_down_img, 20, 11);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_disc_up_down_img_main_main_default
	static lv_style_t style_setting_screen_disc_up_down_img_main_main_default;
	lv_style_reset(&style_setting_screen_disc_up_down_img_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_disc_up_down_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_disc_up_down_img_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_disc_up_down_img_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_disc_up_down_img, &style_setting_screen_disc_up_down_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_disc_up_down_img, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_disc_up_down_img,&_Setting_Drow_Arrow_20x11);
	lv_img_set_pivot(ui->Setting_Screen_disc_up_down_img, 0,0);
	lv_img_set_angle(ui->Setting_Screen_disc_up_down_img, 0);

	//Write codes Setting_Screen_dis_night_lb1
	ui->Setting_Screen_dis_night_lb1 = lv_label_create(ui->Setting_Screen_setting_disc_night_container);
	lv_obj_set_pos(ui->Setting_Screen_dis_night_lb1, 25, 98);
	lv_obj_set_size(ui->Setting_Screen_dis_night_lb1, 190, 20);
	lv_label_set_text(ui->Setting_Screen_dis_night_lb1, "");
	lv_label_set_long_mode(ui->Setting_Screen_dis_night_lb1, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->Setting_Screen_dis_night_lb1, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_dis_night_lb1_main_main_default
	static lv_style_t style_setting_screen_dis_night_lb1_main_main_default;
	lv_style_reset(&style_setting_screen_dis_night_lb1_main_main_default);
	lv_style_set_radius(&style_setting_screen_dis_night_lb1_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_dis_night_lb1_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_setting_screen_dis_night_lb1_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_setting_screen_dis_night_lb1_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_dis_night_lb1_main_main_default, 0);
	lv_style_set_text_color(&style_setting_screen_dis_night_lb1_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_setting_screen_dis_night_lb1_main_main_default, &lv_font_FjallaOne_Regular_22);
	lv_style_set_text_letter_space(&style_setting_screen_dis_night_lb1_main_main_default, 0);
	lv_style_set_pad_left(&style_setting_screen_dis_night_lb1_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_dis_night_lb1_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_dis_night_lb1_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_dis_night_lb1_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_dis_night_lb1, &style_setting_screen_dis_night_lb1_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_dis_night_lb2
	ui->Setting_Screen_dis_night_lb2 = lv_label_create(ui->Setting_Screen_setting_disc_night_container);
	lv_obj_set_pos(ui->Setting_Screen_dis_night_lb2, 25, 146);
	lv_obj_set_size(ui->Setting_Screen_dis_night_lb2, 190, 20);
	lv_label_set_text(ui->Setting_Screen_dis_night_lb2, "");
	lv_label_set_long_mode(ui->Setting_Screen_dis_night_lb2, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->Setting_Screen_dis_night_lb2, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_dis_night_lb2_main_main_default
	static lv_style_t style_setting_screen_dis_night_lb2_main_main_default;
	lv_style_reset(&style_setting_screen_dis_night_lb2_main_main_default);
	lv_style_set_radius(&style_setting_screen_dis_night_lb2_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_dis_night_lb2_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_setting_screen_dis_night_lb2_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_setting_screen_dis_night_lb2_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_dis_night_lb2_main_main_default, 0);
	lv_style_set_text_color(&style_setting_screen_dis_night_lb2_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_setting_screen_dis_night_lb2_main_main_default, &lv_font_FjallaOne_Regular_22);
	lv_style_set_text_letter_space(&style_setting_screen_dis_night_lb2_main_main_default, 0);
	lv_style_set_pad_left(&style_setting_screen_dis_night_lb2_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_dis_night_lb2_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_dis_night_lb2_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_dis_night_lb2_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_dis_night_lb2, &style_setting_screen_dis_night_lb2_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_dis_night_lb3
	ui->Setting_Screen_dis_night_lb3 = lv_label_create(ui->Setting_Screen_setting_disc_night_container);
	lv_obj_set_pos(ui->Setting_Screen_dis_night_lb3, 25, 194);
	lv_obj_set_size(ui->Setting_Screen_dis_night_lb3, 190, 20);
	lv_label_set_text(ui->Setting_Screen_dis_night_lb3, "");
	lv_label_set_long_mode(ui->Setting_Screen_dis_night_lb3, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->Setting_Screen_dis_night_lb3, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_dis_night_lb3_main_main_default
	static lv_style_t style_setting_screen_dis_night_lb3_main_main_default;
	lv_style_reset(&style_setting_screen_dis_night_lb3_main_main_default);
	lv_style_set_radius(&style_setting_screen_dis_night_lb3_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_dis_night_lb3_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_setting_screen_dis_night_lb3_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_setting_screen_dis_night_lb3_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_dis_night_lb3_main_main_default, 0);
	lv_style_set_text_color(&style_setting_screen_dis_night_lb3_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_setting_screen_dis_night_lb3_main_main_default, &lv_font_FjallaOne_Regular_22);
	lv_style_set_text_letter_space(&style_setting_screen_dis_night_lb3_main_main_default, 0);
	lv_style_set_pad_left(&style_setting_screen_dis_night_lb3_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_dis_night_lb3_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_dis_night_lb3_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_dis_night_lb3_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_dis_night_lb3, &style_setting_screen_dis_night_lb3_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_setting_disc_day_container
	ui->Setting_Screen_setting_disc_day_container = lv_obj_create(ui->Setting_Screen);
	lv_obj_set_pos(ui->Setting_Screen_setting_disc_day_container, 0, 0);
	lv_obj_set_size(ui->Setting_Screen_setting_disc_day_container, 240, 320);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_setting_disc_day_container_main_main_default
	static lv_style_t style_setting_screen_setting_disc_day_container_main_main_default;
	lv_style_reset(&style_setting_screen_setting_disc_day_container_main_main_default);
	lv_style_set_radius(&style_setting_screen_setting_disc_day_container_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_setting_disc_day_container_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_color(&style_setting_screen_setting_disc_day_container_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_dir(&style_setting_screen_setting_disc_day_container_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_setting_disc_day_container_main_main_default, 0);
	lv_style_set_border_color(&style_setting_screen_setting_disc_day_container_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_border_width(&style_setting_screen_setting_disc_day_container_main_main_default, 0);
	lv_style_set_border_opa(&style_setting_screen_setting_disc_day_container_main_main_default, 255);
	lv_style_set_pad_left(&style_setting_screen_setting_disc_day_container_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_setting_disc_day_container_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_setting_disc_day_container_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_setting_disc_day_container_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_setting_disc_day_container, &style_setting_screen_setting_disc_day_container_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_disc_day_base_img
	ui->Setting_Screen_disc_day_base_img = lv_img_create(ui->Setting_Screen_setting_disc_day_container);
	lv_obj_set_pos(ui->Setting_Screen_disc_day_base_img, 7, 47);
	lv_obj_set_size(ui->Setting_Screen_disc_day_base_img, 226, 226);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_disc_day_base_img_main_main_default
	static lv_style_t style_setting_screen_disc_day_base_img_main_main_default;
	lv_style_reset(&style_setting_screen_disc_day_base_img_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_disc_day_base_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_disc_day_base_img_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_disc_day_base_img_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_disc_day_base_img, &style_setting_screen_disc_day_base_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_disc_day_base_img, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_disc_day_base_img,&day_white_Grey_circle);
	lv_img_set_pivot(ui->Setting_Screen_disc_day_base_img, 0,0);
	lv_img_set_angle(ui->Setting_Screen_disc_day_base_img, 0);

	//Write codes Setting_Screen_dis_day_up_arr_img
	ui->Setting_Screen_dis_day_up_arr_img = lv_img_create(ui->Setting_Screen_setting_disc_day_container);
	lv_obj_set_pos(ui->Setting_Screen_dis_day_up_arr_img, 110, 65);
	lv_obj_set_size(ui->Setting_Screen_dis_day_up_arr_img, 20, 11);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_dis_day_up_arr_img_main_main_default
	static lv_style_t style_setting_screen_dis_day_up_arr_img_main_main_default;
	lv_style_reset(&style_setting_screen_dis_day_up_arr_img_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_dis_day_up_arr_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_dis_day_up_arr_img_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_dis_day_up_arr_img_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_dis_day_up_arr_img, &style_setting_screen_dis_day_up_arr_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_dis_day_up_arr_img, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_dis_day_up_arr_img,&_day_up_arrow_20x11);
	lv_img_set_pivot(ui->Setting_Screen_dis_day_up_arr_img, 0,0);
	lv_img_set_angle(ui->Setting_Screen_dis_day_up_arr_img, 0);

	//Write codes Setting_Screen_dis_day_down_arr_img
	ui->Setting_Screen_dis_day_down_arr_img = lv_img_create(ui->Setting_Screen_setting_disc_day_container);
	lv_obj_set_pos(ui->Setting_Screen_dis_day_down_arr_img, 110, 238);
	lv_obj_set_size(ui->Setting_Screen_dis_day_down_arr_img, 20, 11);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_dis_day_down_arr_img_main_main_default
	static lv_style_t style_setting_screen_dis_day_down_arr_img_main_main_default;
	lv_style_reset(&style_setting_screen_dis_day_down_arr_img_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_dis_day_down_arr_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_dis_day_down_arr_img_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_dis_day_down_arr_img_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_dis_day_down_arr_img, &style_setting_screen_dis_day_down_arr_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_dis_day_down_arr_img, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_dis_day_down_arr_img,&_day_down_arrow_20x11);
	lv_img_set_pivot(ui->Setting_Screen_dis_day_down_arr_img, 0,0);
	lv_img_set_angle(ui->Setting_Screen_dis_day_down_arr_img, 0);

	//Write codes Setting_Screen_dis_day_lb1
	ui->Setting_Screen_dis_day_lb1 = lv_label_create(ui->Setting_Screen_setting_disc_day_container);
	lv_obj_set_pos(ui->Setting_Screen_dis_day_lb1, 25, 98);
	lv_obj_set_size(ui->Setting_Screen_dis_day_lb1, 190, 20);
	lv_label_set_text(ui->Setting_Screen_dis_day_lb1, "");
	lv_label_set_long_mode(ui->Setting_Screen_dis_day_lb1, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->Setting_Screen_dis_day_lb1, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_dis_day_lb1_main_main_default
	static lv_style_t style_setting_screen_dis_day_lb1_main_main_default;
	lv_style_reset(&style_setting_screen_dis_day_lb1_main_main_default);
	lv_style_set_radius(&style_setting_screen_dis_day_lb1_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_dis_day_lb1_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_setting_screen_dis_day_lb1_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_setting_screen_dis_day_lb1_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_dis_day_lb1_main_main_default, 0);
	lv_style_set_text_color(&style_setting_screen_dis_day_lb1_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_setting_screen_dis_day_lb1_main_main_default, &lv_font_FjallaOne_Regular_22);
	lv_style_set_text_letter_space(&style_setting_screen_dis_day_lb1_main_main_default, 0);
	lv_style_set_pad_left(&style_setting_screen_dis_day_lb1_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_dis_day_lb1_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_dis_day_lb1_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_dis_day_lb1_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_dis_day_lb1, &style_setting_screen_dis_day_lb1_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_dis_day_lb2
	ui->Setting_Screen_dis_day_lb2 = lv_label_create(ui->Setting_Screen_setting_disc_day_container);
	lv_obj_set_pos(ui->Setting_Screen_dis_day_lb2, 25, 146);
	lv_obj_set_size(ui->Setting_Screen_dis_day_lb2, 190, 20);
	lv_label_set_text(ui->Setting_Screen_dis_day_lb2, "");
	lv_label_set_long_mode(ui->Setting_Screen_dis_day_lb2, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->Setting_Screen_dis_day_lb2, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_dis_day_lb2_main_main_default
	static lv_style_t style_setting_screen_dis_day_lb2_main_main_default;
	lv_style_reset(&style_setting_screen_dis_day_lb2_main_main_default);
	lv_style_set_radius(&style_setting_screen_dis_day_lb2_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_dis_day_lb2_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_setting_screen_dis_day_lb2_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_setting_screen_dis_day_lb2_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_dis_day_lb2_main_main_default, 0);
	lv_style_set_text_color(&style_setting_screen_dis_day_lb2_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_setting_screen_dis_day_lb2_main_main_default, &lv_font_FjallaOne_Regular_22);
	lv_style_set_text_letter_space(&style_setting_screen_dis_day_lb2_main_main_default, 0);
	lv_style_set_pad_left(&style_setting_screen_dis_day_lb2_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_dis_day_lb2_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_dis_day_lb2_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_dis_day_lb2_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_dis_day_lb2, &style_setting_screen_dis_day_lb2_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_dis_day_lb3
	ui->Setting_Screen_dis_day_lb3 = lv_label_create(ui->Setting_Screen_setting_disc_day_container);
	lv_obj_set_pos(ui->Setting_Screen_dis_day_lb3, 25, 194);
	lv_obj_set_size(ui->Setting_Screen_dis_day_lb3, 190, 20);
	lv_label_set_text(ui->Setting_Screen_dis_day_lb3, "");
	lv_label_set_long_mode(ui->Setting_Screen_dis_day_lb3, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->Setting_Screen_dis_day_lb3, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_dis_day_lb3_main_main_default
	static lv_style_t style_setting_screen_dis_day_lb3_main_main_default;
	lv_style_reset(&style_setting_screen_dis_day_lb3_main_main_default);
	lv_style_set_radius(&style_setting_screen_dis_day_lb3_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_dis_day_lb3_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_setting_screen_dis_day_lb3_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_setting_screen_dis_day_lb3_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_dis_day_lb3_main_main_default, 0);
	lv_style_set_text_color(&style_setting_screen_dis_day_lb3_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_setting_screen_dis_day_lb3_main_main_default, &lv_font_FjallaOne_Regular_22);
	lv_style_set_text_letter_space(&style_setting_screen_dis_day_lb3_main_main_default, 0);
	lv_style_set_pad_left(&style_setting_screen_dis_day_lb3_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_dis_day_lb3_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_dis_day_lb3_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_dis_day_lb3_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_dis_day_lb3, &style_setting_screen_dis_day_lb3_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_Setting_disclaimer_night_new
	ui->Setting_Screen_Setting_disclaimer_night_new = lv_obj_create(ui->Setting_Screen);
	lv_obj_set_pos(ui->Setting_Screen_Setting_disclaimer_night_new, 0, 0);
	lv_obj_set_size(ui->Setting_Screen_Setting_disclaimer_night_new, 240, 320);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_setting_disclaimer_night_new_main_main_default
	static lv_style_t style_setting_screen_setting_disclaimer_night_new_main_main_default;
	lv_style_reset(&style_setting_screen_setting_disclaimer_night_new_main_main_default);
	lv_style_set_radius(&style_setting_screen_setting_disclaimer_night_new_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_setting_disclaimer_night_new_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_color(&style_setting_screen_setting_disclaimer_night_new_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_dir(&style_setting_screen_setting_disclaimer_night_new_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_setting_disclaimer_night_new_main_main_default, 0);
	lv_style_set_border_color(&style_setting_screen_setting_disclaimer_night_new_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_border_width(&style_setting_screen_setting_disclaimer_night_new_main_main_default, 0);
	lv_style_set_border_opa(&style_setting_screen_setting_disclaimer_night_new_main_main_default, 255);
	lv_style_set_pad_left(&style_setting_screen_setting_disclaimer_night_new_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_setting_disclaimer_night_new_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_setting_disclaimer_night_new_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_setting_disclaimer_night_new_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_Setting_disclaimer_night_new, &style_setting_screen_setting_disclaimer_night_new_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_dis_msg_night_img
	ui->Setting_Screen_dis_msg_night_img = lv_img_create(ui->Setting_Screen_Setting_disclaimer_night_new);
	lv_obj_set_pos(ui->Setting_Screen_dis_msg_night_img, 24, 89);
	lv_obj_set_size(ui->Setting_Screen_dis_msg_night_img, 192, 134);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_dis_msg_night_img_main_main_default
	static lv_style_t style_setting_screen_dis_msg_night_img_main_main_default;
	lv_style_reset(&style_setting_screen_dis_msg_night_img_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_dis_msg_night_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_dis_msg_night_img_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_dis_msg_night_img_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_dis_msg_night_img, &style_setting_screen_dis_msg_night_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_img_set_src(ui->Setting_Screen_dis_msg_night_img,&dis_night);

	//Write codes Setting_Screen_Setting_disclaimer_day_new
	ui->Setting_Screen_Setting_disclaimer_day_new = lv_obj_create(ui->Setting_Screen);
	lv_obj_set_pos(ui->Setting_Screen_Setting_disclaimer_day_new, 0, 0);
	lv_obj_set_size(ui->Setting_Screen_Setting_disclaimer_day_new, 240, 320);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_setting_disclaimer_day_new_main_main_default
	static lv_style_t style_setting_screen_setting_disclaimer_day_new_main_main_default;
	lv_style_reset(&style_setting_screen_setting_disclaimer_day_new_main_main_default);
	lv_style_set_radius(&style_setting_screen_setting_disclaimer_day_new_main_main_default, 0);
	lv_style_set_bg_color(&style_setting_screen_setting_disclaimer_day_new_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_color(&style_setting_screen_setting_disclaimer_day_new_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_dir(&style_setting_screen_setting_disclaimer_day_new_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_setting_screen_setting_disclaimer_day_new_main_main_default, 0);
	lv_style_set_border_color(&style_setting_screen_setting_disclaimer_day_new_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_border_width(&style_setting_screen_setting_disclaimer_day_new_main_main_default, 0);
	lv_style_set_border_opa(&style_setting_screen_setting_disclaimer_day_new_main_main_default, 255);
	lv_style_set_pad_left(&style_setting_screen_setting_disclaimer_day_new_main_main_default, 0);
	lv_style_set_pad_right(&style_setting_screen_setting_disclaimer_day_new_main_main_default, 0);
	lv_style_set_pad_top(&style_setting_screen_setting_disclaimer_day_new_main_main_default, 0);
	lv_style_set_pad_bottom(&style_setting_screen_setting_disclaimer_day_new_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_Setting_disclaimer_day_new, &style_setting_screen_setting_disclaimer_day_new_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Setting_Screen_dis_day_whitebaseimg
	ui->Setting_Screen_dis_day_whitebaseimg = lv_img_create(ui->Setting_Screen_Setting_disclaimer_day_new);
	lv_obj_set_pos(ui->Setting_Screen_dis_day_whitebaseimg, 7, 47);
	lv_obj_set_size(ui->Setting_Screen_dis_day_whitebaseimg, 226, 226);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_dis_day_whitebaseimg_main_main_default
	static lv_style_t style_setting_screen_dis_day_whitebaseimg_main_main_default;
	lv_style_reset(&style_setting_screen_dis_day_whitebaseimg_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_dis_day_whitebaseimg_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_dis_day_whitebaseimg_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_dis_day_whitebaseimg_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_dis_day_whitebaseimg, &style_setting_screen_dis_day_whitebaseimg_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_dis_day_whitebaseimg, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_dis_day_whitebaseimg,&day_white_Grey_circle);
	lv_img_set_pivot(ui->Setting_Screen_dis_day_whitebaseimg, 0,0);
	lv_img_set_angle(ui->Setting_Screen_dis_day_whitebaseimg, 0);

	//Write codes Setting_Screen_dis_msg_day_img
	ui->Setting_Screen_dis_msg_day_img = lv_img_create(ui->Setting_Screen_Setting_disclaimer_day_new);
	lv_obj_set_pos(ui->Setting_Screen_dis_msg_day_img, 24, 89);
	lv_obj_set_size(ui->Setting_Screen_dis_msg_day_img, 192, 134);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_dis_msg_day_img_main_main_default
	static lv_style_t style_setting_screen_dis_msg_day_img_main_main_default;
	lv_style_reset(&style_setting_screen_dis_msg_day_img_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_dis_msg_day_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_dis_msg_day_img_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_dis_msg_day_img_main_main_default, 255);
	lv_obj_add_style(ui->Setting_Screen_dis_msg_day_img, &style_setting_screen_dis_msg_day_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_dis_msg_day_img, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_dis_msg_day_img,&dis_day);
	lv_img_set_pivot(ui->Setting_Screen_dis_msg_day_img, 0,0);
	lv_img_set_angle(ui->Setting_Screen_dis_msg_day_img, 0);

	


	//Write codes Setting_Screen_setting_ghost_images
	ui->Setting_Screen_setting_ghost_images = lv_img_create(ui->Setting_Screen);
	lv_obj_set_pos(ui->Setting_Screen_setting_ghost_images, 0, 0);
	lv_obj_set_size(ui->Setting_Screen_setting_ghost_images, 240, 320);

	//Write style state: LV_STATE_DEFAULT for style_setting_screen_setting_ghost_images_main_main_default
	static lv_style_t style_setting_screen_setting_ghost_images_main_main_default;
	lv_style_reset(&style_setting_screen_setting_ghost_images_main_main_default);
	lv_style_set_img_recolor(&style_setting_screen_setting_ghost_images_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_setting_screen_setting_ghost_images_main_main_default, 0);
	lv_style_set_img_opa(&style_setting_screen_setting_ghost_images_main_main_default, 0);
	lv_obj_add_style(ui->Setting_Screen_setting_ghost_images, &style_setting_screen_setting_ghost_images_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Setting_Screen_setting_ghost_images, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Setting_Screen_setting_ghost_images,&_1_240x320);
	lv_img_set_pivot(ui->Setting_Screen_setting_ghost_images, 0,0);
	lv_img_set_angle(ui->Setting_Screen_setting_ghost_images, 0);
}

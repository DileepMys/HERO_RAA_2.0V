/*
 * Copyright 2022 NXP
 * SPDX-License-Identifier: MIT
 */

#include "lvgl/lvgl.h"
#include <stdio.h>
#include "gui_guider.h"
#include "events_init.h"
#include "custom.h"
#include "lvgl_app.h"


void setup_scr_screen(lv_ui *ui){

	//Write codes screen
	ui->screen = lv_obj_create(NULL);

	

	//Write style state: LV_STATE_DEFAULT for style_screen_main_main_default
	static lv_style_t style_screen_main_main_default;
	lv_style_reset(&style_screen_main_main_default);
	lv_style_set_bg_color(&style_screen_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_opa(&style_screen_main_main_default, 255);
	lv_obj_add_style(ui->screen, &style_screen_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_skin
	ui->screen_skin = lv_img_create(ui->screen);
	lv_obj_set_pos(ui->screen_skin, 0, 0);
	lv_obj_set_size(ui->screen_skin, 240, 320);

	//Write style state: LV_STATE_DEFAULT for style_screen_skin_main_main_default
	static lv_style_t style_screen_skin_main_main_default;
	lv_style_reset(&style_screen_skin_main_main_default);
	lv_style_set_img_recolor(&style_screen_skin_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_skin_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_skin_main_main_default, 255);
	lv_obj_add_style(ui->screen_skin, &style_screen_skin_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->screen_skin, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_skin,&_Skin_BG_240x320);
	lv_img_set_pivot(ui->screen_skin, 0,0);
	lv_img_set_angle(ui->screen_skin, 0);

	//Write codes screen_Circ
	ui->screen_Circ = lv_img_create(ui->screen);
	lv_obj_set_pos(ui->screen_Circ, 7, 47);
	lv_obj_set_size(ui->screen_Circ, 226, 226);

	//Write style state: LV_STATE_DEFAULT for style_screen_circ_main_main_default
	static lv_style_t style_screen_circ_main_main_default;
	lv_style_reset(&style_screen_circ_main_main_default);
	lv_style_set_img_recolor(&style_screen_circ_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_circ_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_circ_main_main_default, 0);
	lv_obj_add_style(ui->screen_Circ, &style_screen_circ_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->screen_Circ, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_Circ,&_circle_226x226);
	lv_img_set_pivot(ui->screen_Circ, 0,0);
	lv_img_set_angle(ui->screen_Circ, 0);

	//Write codes screen_TripA
	ui->screen_TripA = lv_img_create(ui->screen);
	lv_obj_set_pos(ui->screen_TripA, 105, 252);
	lv_obj_set_size(ui->screen_TripA, 30, 30);

	//Write style state: LV_STATE_DEFAULT for style_screen_tripa_main_main_default
	static lv_style_t style_screen_tripa_main_main_default;
	lv_style_reset(&style_screen_tripa_main_main_default);
	lv_style_set_img_recolor(&style_screen_tripa_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_tripa_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_tripa_main_main_default, 255);
	lv_obj_add_style(ui->screen_TripA, &style_screen_tripa_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->screen_TripA, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_TripA,&_img_trip_A_icon_30x30);
	lv_img_set_pivot(ui->screen_TripA, 0,0);
	lv_img_set_angle(ui->screen_TripA, 0);

	//Write codes screen_FogLampTT
	ui->screen_FogLampTT = lv_imgbtn_create(ui->screen);
	lv_obj_set_pos(ui->screen_FogLampTT, 10, 11);
	lv_obj_set_size(ui->screen_FogLampTT, 24, 21);

	//Write style state: LV_STATE_DEFAULT for style_screen_foglamptt_main_main_default
	static lv_style_t style_screen_foglamptt_main_main_default;
	lv_style_reset(&style_screen_foglamptt_main_main_default);
	lv_style_set_text_color(&style_screen_foglamptt_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_img_recolor(&style_screen_foglamptt_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_foglamptt_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_foglamptt_main_main_default, 255);
	lv_obj_add_style(ui->screen_FogLampTT, &style_screen_foglamptt_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style state: LV_STATE_PRESSED for style_screen_foglamptt_main_main_pressed
	static lv_style_t style_screen_foglamptt_main_main_pressed;
	lv_style_reset(&style_screen_foglamptt_main_main_pressed);
	lv_style_set_text_color(&style_screen_foglamptt_main_main_pressed, lv_color_make(0xFF, 0x33, 0xFF));
	lv_style_set_img_recolor(&style_screen_foglamptt_main_main_pressed, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_img_recolor_opa(&style_screen_foglamptt_main_main_pressed, 0);
	lv_obj_add_style(ui->screen_FogLampTT, &style_screen_foglamptt_main_main_pressed, LV_PART_MAIN|LV_STATE_PRESSED);

	//Write style state: LV_STATE_CHECKED for style_screen_foglamptt_main_main_checked
	static lv_style_t style_screen_foglamptt_main_main_checked;
	lv_style_reset(&style_screen_foglamptt_main_main_checked);
	lv_style_set_text_color(&style_screen_foglamptt_main_main_checked, lv_color_make(0xFF, 0x33, 0xFF));
	lv_style_set_img_recolor(&style_screen_foglamptt_main_main_checked, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_img_recolor_opa(&style_screen_foglamptt_main_main_checked, 0);
	lv_obj_add_style(ui->screen_FogLampTT, &style_screen_foglamptt_main_main_checked, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_imgbtn_set_src(ui->screen_FogLampTT, LV_IMGBTN_STATE_RELEASED, NULL, &new_header_fog_telltale, NULL);
	lv_imgbtn_set_src(ui->screen_FogLampTT, LV_IMGBTN_STATE_PRESSED, NULL, &_Layer_0_alpha_24x20, NULL);
	lv_obj_add_flag(ui->screen_FogLampTT, LV_OBJ_FLAG_CHECKABLE);

	//Write codes screen_imgEngineTT
	ui->screen_imgEngineTT = lv_imgbtn_create(ui->screen);
	lv_obj_set_pos(ui->screen_imgEngineTT, 204, 12);
	lv_obj_set_size(ui->screen_imgEngineTT, 26, 18);

	//Write style state: LV_STATE_DEFAULT for style_screen_imgenginett_main_main_default
	static lv_style_t style_screen_imgenginett_main_main_default;
	lv_style_reset(&style_screen_imgenginett_main_main_default);
	lv_style_set_text_color(&style_screen_imgenginett_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_img_recolor(&style_screen_imgenginett_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_imgenginett_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_imgenginett_main_main_default, 255);
	lv_obj_add_style(ui->screen_imgEngineTT, &style_screen_imgenginett_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style state: LV_STATE_PRESSED for style_screen_imgenginett_main_main_pressed
	static lv_style_t style_screen_imgenginett_main_main_pressed;
	lv_style_reset(&style_screen_imgenginett_main_main_pressed);
	lv_style_set_text_color(&style_screen_imgenginett_main_main_pressed, lv_color_make(0xFF, 0x33, 0xFF));
	lv_style_set_img_recolor(&style_screen_imgenginett_main_main_pressed, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_img_recolor_opa(&style_screen_imgenginett_main_main_pressed, 0);
	lv_obj_add_style(ui->screen_imgEngineTT, &style_screen_imgenginett_main_main_pressed, LV_PART_MAIN|LV_STATE_PRESSED);

	//Write style state: LV_STATE_CHECKED for style_screen_imgenginett_main_main_checked
	static lv_style_t style_screen_imgenginett_main_main_checked;
	lv_style_reset(&style_screen_imgenginett_main_main_checked);
	lv_style_set_text_color(&style_screen_imgenginett_main_main_checked, lv_color_make(0xFF, 0x33, 0xFF));
	lv_style_set_img_recolor(&style_screen_imgenginett_main_main_checked, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_img_recolor_opa(&style_screen_imgenginett_main_main_checked, 0);
	lv_obj_add_style(ui->screen_imgEngineTT, &style_screen_imgenginett_main_main_checked, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_imgbtn_set_src(ui->screen_imgEngineTT, LV_IMGBTN_STATE_RELEASED, NULL, &new_engine_telltale, NULL);
	lv_imgbtn_set_src(ui->screen_imgEngineTT, LV_IMGBTN_STATE_PRESSED, NULL, &_Layer_0_alpha_25x17, NULL);
	lv_obj_add_flag(ui->screen_imgEngineTT, LV_OBJ_FLAG_CHECKABLE);

	//Write codes screen_Trip_blank
	ui->screen_Trip_blank = lv_img_create(ui->screen);
	lv_obj_set_pos(ui->screen_Trip_blank, 105, 255);
	lv_obj_set_size(ui->screen_Trip_blank, 30, 30);

	//Write style state: LV_STATE_DEFAULT for style_screen_trip_blank_main_main_default
	static lv_style_t style_screen_trip_blank_main_main_default;
	lv_style_reset(&style_screen_trip_blank_main_main_default);
	lv_style_set_img_recolor(&style_screen_trip_blank_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_trip_blank_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_trip_blank_main_main_default, 255);
	lv_obj_add_style(ui->screen_Trip_blank, &style_screen_trip_blank_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->screen_Trip_blank, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_Trip_blank,&_BlankTrip_30x30);
	lv_img_set_pivot(ui->screen_Trip_blank, 0,0);
	lv_img_set_angle(ui->screen_Trip_blank, 0);

	//Write codes screen_imgKmph
	ui->screen_imgKmph = lv_img_create(ui->screen);
	lv_obj_set_pos(ui->screen_imgKmph, 195, 155);
	lv_obj_set_size(ui->screen_imgKmph, 33, 19);

	//Write style state: LV_STATE_DEFAULT for style_screen_imgkmph_main_main_default
	static lv_style_t style_screen_imgkmph_main_main_default;
	lv_style_reset(&style_screen_imgkmph_main_main_default);
	lv_style_set_img_recolor(&style_screen_imgkmph_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_imgkmph_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_imgkmph_main_main_default, 255);
	lv_obj_add_style(ui->screen_imgKmph, &style_screen_imgkmph_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->screen_imgKmph, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_imgKmph,&_txt_night_speed_unit_33x19);
	lv_img_set_pivot(ui->screen_imgKmph, 0,0);
	lv_img_set_angle(ui->screen_imgKmph, 0);

	//Write codes screen_E_F_Img
	ui->screen_E_F_Img = lv_img_create(ui->screen);
	lv_obj_set_pos(ui->screen_E_F_Img, 35, 254);
	lv_obj_set_size(ui->screen_E_F_Img, 13, 15);

	//Write style state: LV_STATE_DEFAULT for style_screen_e_f_img_main_main_default
	static lv_style_t style_screen_e_f_img_main_main_default;
	lv_style_reset(&style_screen_e_f_img_main_main_default);
	lv_style_set_img_recolor(&style_screen_e_f_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_e_f_img_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_e_f_img_main_main_default, 255);
	lv_obj_add_style(ui->screen_E_F_Img, &style_screen_e_f_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->screen_E_F_Img, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_E_F_Img,&_img_night_fuel_E_13x15);
	lv_img_set_pivot(ui->screen_E_F_Img, 0,0);
	lv_img_set_angle(ui->screen_E_F_Img, 0);

	//Write codes screen_F_Img
	ui->screen_F_Img = lv_img_create(ui->screen);
	lv_obj_set_pos(ui->screen_F_Img, 190, 252);
	lv_obj_set_size(ui->screen_F_Img, 10, 16);

	//Write style state: LV_STATE_DEFAULT for style_screen_f_img_main_main_default
	static lv_style_t style_screen_f_img_main_main_default;
	lv_style_reset(&style_screen_f_img_main_main_default);
	lv_style_set_img_recolor(&style_screen_f_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_f_img_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_f_img_main_main_default, 255);
	lv_obj_add_style(ui->screen_F_Img, &style_screen_f_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->screen_F_Img, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_F_Img,&_img_night_fuel_F_10x16);
	lv_img_set_pivot(ui->screen_F_Img, 0,0);
	lv_img_set_angle(ui->screen_F_Img, 0);

	//Write codes screen_Fuelbar0
	ui->screen_Fuelbar0 = lv_img_create(ui->screen);
	lv_obj_set_pos(ui->screen_Fuelbar0, 38, 266);
	lv_obj_set_size(ui->screen_Fuelbar0, 158, 43);

	//Write style state: LV_STATE_DEFAULT for style_screen_fuelbar0_main_main_default
	static lv_style_t style_screen_fuelbar0_main_main_default;
	lv_style_reset(&style_screen_fuelbar0_main_main_default);
	lv_style_set_img_recolor(&style_screen_fuelbar0_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_fuelbar0_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_fuelbar0_main_main_default, 255);
	lv_obj_add_style(ui->screen_Fuelbar0, &style_screen_fuelbar0_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->screen_Fuelbar0, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_Fuelbar0,&img_fuel_grey_bg_white_icon);
	lv_img_set_pivot(ui->screen_Fuelbar0, 0,0);
	lv_img_set_angle(ui->screen_Fuelbar0, 0);

	//Write codes screen_Gear_Symbol
	ui->screen_Gear_Symbol = lv_img_create(ui->screen);
	lv_obj_set_pos(ui->screen_Gear_Symbol, 17, 148);
	lv_obj_set_size(ui->screen_Gear_Symbol, 10, 24);

	//Write style state: LV_STATE_DEFAULT for style_screen_gear_symbol_main_main_default
	static lv_style_t style_screen_gear_symbol_main_main_default;
	lv_style_reset(&style_screen_gear_symbol_main_main_default);
	lv_style_set_img_recolor(&style_screen_gear_symbol_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_gear_symbol_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_gear_symbol_main_main_default, 255);
	lv_obj_add_style(ui->screen_Gear_Symbol, &style_screen_gear_symbol_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->screen_Gear_Symbol, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_Gear_Symbol,&_Ge_i_10x24);
	lv_img_set_pivot(ui->screen_Gear_Symbol, 0,0);
	lv_img_set_angle(ui->screen_Gear_Symbol, 0);

	//Write codes screen_Gear_Position_Number
	ui->screen_Gear_Position_Number = lv_label_create(ui->screen);
	lv_obj_set_pos(ui->screen_Gear_Position_Number, 31, 148);
	lv_obj_set_size(ui->screen_Gear_Position_Number, 14, 26);
	lv_label_set_text(ui->screen_Gear_Position_Number, "2");
	lv_label_set_long_mode(ui->screen_Gear_Position_Number, LV_LABEL_LONG_WRAP);
	lv_obj_set_style_text_align(ui->screen_Gear_Position_Number, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_screen_gear_position_number_main_main_default
	static lv_style_t style_screen_gear_position_number_main_main_default;
	lv_style_reset(&style_screen_gear_position_number_main_main_default);
	lv_style_set_radius(&style_screen_gear_position_number_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_gear_position_number_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_color(&style_screen_gear_position_number_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_dir(&style_screen_gear_position_number_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_gear_position_number_main_main_default, 0);
	lv_style_set_text_color(&style_screen_gear_position_number_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_screen_gear_position_number_main_main_default, &lv_font_FjallaOne_Regular_30);
	lv_style_set_text_letter_space(&style_screen_gear_position_number_main_main_default, 0);
	lv_style_set_pad_left(&style_screen_gear_position_number_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_gear_position_number_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_gear_position_number_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_gear_position_number_main_main_default, 0);
	lv_obj_add_style(ui->screen_Gear_Position_Number, &style_screen_gear_position_number_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	

	//Write codes screen_gear_N_img_night
	ui->screen_gear_N_img_night = lv_img_create(ui->screen);
	lv_obj_set_pos(ui->screen_gear_N_img_night, 30, 150);
	lv_obj_set_size(ui->screen_gear_N_img_night, 15, 23);

	//Write style state: LV_STATE_DEFAULT for style_screen_gear_n_img_night_main_main_default
	static lv_style_t style_screen_gear_n_img_night_main_main_default;
	lv_style_reset(&style_screen_gear_n_img_night_main_main_default);
	lv_style_set_img_recolor(&style_screen_gear_n_img_night_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_gear_n_img_night_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_gear_n_img_night_main_main_default, 255);
	lv_obj_add_style(ui->screen_gear_N_img_night, &style_screen_gear_n_img_night_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_img_set_src(ui->screen_gear_N_img_night,&img_night_gear_neutral);

	//Write codes screen_Clock_hour
	ui->screen_Clock_hour = lv_label_create(ui->screen);
	lv_obj_set_pos(ui->screen_Clock_hour, 86, 69);
	lv_obj_set_size(ui->screen_Clock_hour, 13, 12);
	lv_label_set_text(ui->screen_Clock_hour, "24");
	lv_label_set_long_mode(ui->screen_Clock_hour, LV_LABEL_LONG_WRAP);
	lv_obj_set_style_text_align(ui->screen_Clock_hour, LV_TEXT_ALIGN_RIGHT, 0);

	//Write style state: LV_STATE_DEFAULT for style_screen_clock_hour_main_main_default
	static lv_style_t style_screen_clock_hour_main_main_default;
	lv_style_reset(&style_screen_clock_hour_main_main_default);
	lv_style_set_radius(&style_screen_clock_hour_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_clock_hour_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_clock_hour_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_clock_hour_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_clock_hour_main_main_default, 0);
	lv_style_set_text_color(&style_screen_clock_hour_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_screen_clock_hour_main_main_default, &lv_font_FjallaOne_Regular_19);
	lv_style_set_text_letter_space(&style_screen_clock_hour_main_main_default, 2);
	lv_style_set_pad_left(&style_screen_clock_hour_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_clock_hour_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_clock_hour_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_clock_hour_main_main_default, 0);
	lv_obj_add_style(ui->screen_Clock_hour, &style_screen_clock_hour_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_Clock_min
	ui->screen_Clock_min = lv_label_create(ui->screen);
	lv_obj_set_pos(ui->screen_Clock_min, 113, 69);
	lv_obj_set_size(ui->screen_Clock_min, 15, 12);
	lv_label_set_text(ui->screen_Clock_min, "60");
	lv_label_set_long_mode(ui->screen_Clock_min, LV_LABEL_LONG_WRAP);
	lv_obj_set_style_text_align(ui->screen_Clock_min, LV_TEXT_ALIGN_LEFT, 0);

	//Write style state: LV_STATE_DEFAULT for style_screen_clock_min_main_main_default
	static lv_style_t style_screen_clock_min_main_main_default;
	lv_style_reset(&style_screen_clock_min_main_main_default);
	lv_style_set_radius(&style_screen_clock_min_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_clock_min_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_clock_min_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_clock_min_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_clock_min_main_main_default, 0);
	lv_style_set_text_color(&style_screen_clock_min_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_screen_clock_min_main_main_default, &lv_font_FjallaOne_Regular_19);
	lv_style_set_text_letter_space(&style_screen_clock_min_main_main_default, 2);
	lv_style_set_pad_left(&style_screen_clock_min_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_clock_min_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_clock_min_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_clock_min_main_main_default, 0);
	lv_obj_add_style(ui->screen_Clock_min, &style_screen_clock_min_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_Clock_Colan
	ui->screen_Clock_Colan = lv_label_create(ui->screen);
	lv_obj_set_pos(ui->screen_Clock_Colan, 109, 69);
	lv_obj_set_size(ui->screen_Clock_Colan, 3, 10);
	lv_label_set_text(ui->screen_Clock_Colan, ":");
	lv_label_set_long_mode(ui->screen_Clock_Colan, LV_LABEL_LONG_WRAP);
	lv_obj_set_style_text_align(ui->screen_Clock_Colan, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_screen_clock_colan_main_main_default
	static lv_style_t style_screen_clock_colan_main_main_default;
	lv_style_reset(&style_screen_clock_colan_main_main_default);
	lv_style_set_radius(&style_screen_clock_colan_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_clock_colan_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_clock_colan_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_clock_colan_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_clock_colan_main_main_default, 0);
	lv_style_set_text_color(&style_screen_clock_colan_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_screen_clock_colan_main_main_default, &lv_font_FjallaOne_Regular_19);
	lv_style_set_text_letter_space(&style_screen_clock_colan_main_main_default, 2);
	lv_style_set_pad_left(&style_screen_clock_colan_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_clock_colan_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_clock_colan_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_clock_colan_main_main_default, 0);
	lv_obj_add_style(ui->screen_Clock_Colan, &style_screen_clock_colan_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_TachoBarBlank
	ui->screen_TachoBarBlank = lv_img_create(ui->screen);
	lv_obj_set_pos(ui->screen_TachoBarBlank, 3, 8);
	lv_obj_set_size(ui->screen_TachoBarBlank, 231, 78);

	//Write style state: LV_STATE_DEFAULT for style_screen_tachobarblank_main_main_default
	static lv_style_t style_screen_tachobarblank_main_main_default;
	lv_style_reset(&style_screen_tachobarblank_main_main_default);
	lv_style_set_img_recolor(&style_screen_tachobarblank_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_tachobarblank_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_tachobarblank_main_main_default, 0);
	lv_obj_add_style(ui->screen_TachoBarBlank, &style_screen_tachobarblank_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->screen_TachoBarBlank, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_TachoBarBlank,&_Layer_0_231x78);
	lv_img_set_pivot(ui->screen_TachoBarBlank, 0,0);
	lv_img_set_angle(ui->screen_TachoBarBlank, 0);

	//Write codes screen_TripB
	ui->screen_TripB = lv_img_create(ui->screen);
	lv_obj_set_pos(ui->screen_TripB, 105, 252);
	lv_obj_set_size(ui->screen_TripB, 30, 30);

	//Write style state: LV_STATE_DEFAULT for style_screen_tripb_main_main_default
	static lv_style_t style_screen_tripb_main_main_default;
	lv_style_reset(&style_screen_tripb_main_main_default);
	lv_style_set_img_recolor(&style_screen_tripb_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_tripb_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_tripb_main_main_default, 0);
	lv_obj_add_style(ui->screen_TripB, &style_screen_tripb_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->screen_TripB, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_TripB,&_img_trip_B_icon_30x30);
	lv_img_set_pivot(ui->screen_TripB, 0,0);
	lv_img_set_angle(ui->screen_TripB, 0);

	//Write codes screen_Service_Icon
	ui->screen_Service_Icon = lv_img_create(ui->screen);
	lv_obj_set_pos(ui->screen_Service_Icon, 98, 252);
	lv_obj_set_size(ui->screen_Service_Icon, 30, 30);

	//Write style state: LV_STATE_DEFAULT for style_screen_service_icon_main_main_default
	static lv_style_t style_screen_service_icon_main_main_default;
	lv_style_reset(&style_screen_service_icon_main_main_default);
	lv_style_set_img_recolor(&style_screen_service_icon_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_service_icon_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_service_icon_main_main_default, 0);
	lv_obj_add_style(ui->screen_Service_Icon, &style_screen_service_icon_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->screen_Service_Icon, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_Service_Icon,&_img_night_service_icon_30x30);
	lv_img_set_pivot(ui->screen_Service_Icon, 0,0);
	lv_img_set_angle(ui->screen_Service_Icon, 0);

	//Write codes screen_Gear_UP_Advisory
	ui->screen_Gear_UP_Advisory = lv_imgbtn_create(ui->screen);
	lv_obj_set_pos(ui->screen_Gear_UP_Advisory, 30, 174);
	lv_obj_set_size(ui->screen_Gear_UP_Advisory, 15, 11);

	//Write style state: LV_STATE_DEFAULT for style_screen_gear_up_advisory_main_main_default
	static lv_style_t style_screen_gear_up_advisory_main_main_default;
	lv_style_reset(&style_screen_gear_up_advisory_main_main_default);
	lv_style_set_text_color(&style_screen_gear_up_advisory_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_img_recolor(&style_screen_gear_up_advisory_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_gear_up_advisory_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_gear_up_advisory_main_main_default, 254);
	lv_obj_add_style(ui->screen_Gear_UP_Advisory, &style_screen_gear_up_advisory_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style state: LV_STATE_PRESSED for style_screen_gear_up_advisory_main_main_pressed
	static lv_style_t style_screen_gear_up_advisory_main_main_pressed;
	lv_style_reset(&style_screen_gear_up_advisory_main_main_pressed);
	lv_style_set_text_color(&style_screen_gear_up_advisory_main_main_pressed, lv_color_make(0xFF, 0x33, 0xFF));
	lv_style_set_img_recolor(&style_screen_gear_up_advisory_main_main_pressed, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_img_recolor_opa(&style_screen_gear_up_advisory_main_main_pressed, 0);
	lv_obj_add_style(ui->screen_Gear_UP_Advisory, &style_screen_gear_up_advisory_main_main_pressed, LV_PART_MAIN|LV_STATE_PRESSED);

	//Write style state: LV_STATE_CHECKED for style_screen_gear_up_advisory_main_main_checked
	static lv_style_t style_screen_gear_up_advisory_main_main_checked;
	lv_style_reset(&style_screen_gear_up_advisory_main_main_checked);
	lv_style_set_text_color(&style_screen_gear_up_advisory_main_main_checked, lv_color_make(0xFF, 0x33, 0xFF));
	lv_style_set_img_recolor(&style_screen_gear_up_advisory_main_main_checked, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_img_recolor_opa(&style_screen_gear_up_advisory_main_main_checked, 0);
	lv_obj_add_style(ui->screen_Gear_UP_Advisory, &style_screen_gear_up_advisory_main_main_checked, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_imgbtn_set_src(ui->screen_Gear_UP_Advisory, LV_IMGBTN_STATE_RELEASED, NULL, &new_night_gear_arrows_up_white, NULL);
	lv_imgbtn_set_src(ui->screen_Gear_UP_Advisory, LV_IMGBTN_STATE_PRESSED, NULL, &_img_night_gear_arrows_up_white_13x9, NULL);
	lv_obj_add_flag(ui->screen_Gear_UP_Advisory, LV_OBJ_FLAG_CHECKABLE);

	//Write codes screen_Gear_Down_Advisory
	ui->screen_Gear_Down_Advisory = lv_imgbtn_create(ui->screen);
	lv_obj_set_pos(ui->screen_Gear_Down_Advisory, 30, 174);
	lv_obj_set_size(ui->screen_Gear_Down_Advisory, 15, 11);

	//Write style state: LV_STATE_DEFAULT for style_screen_gear_down_advisory_main_main_default
	static lv_style_t style_screen_gear_down_advisory_main_main_default;
	lv_style_reset(&style_screen_gear_down_advisory_main_main_default);
	lv_style_set_text_color(&style_screen_gear_down_advisory_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_img_recolor(&style_screen_gear_down_advisory_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_gear_down_advisory_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_gear_down_advisory_main_main_default, 253);
	lv_obj_add_style(ui->screen_Gear_Down_Advisory, &style_screen_gear_down_advisory_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style state: LV_STATE_PRESSED for style_screen_gear_down_advisory_main_main_pressed
	static lv_style_t style_screen_gear_down_advisory_main_main_pressed;
	lv_style_reset(&style_screen_gear_down_advisory_main_main_pressed);
	lv_style_set_text_color(&style_screen_gear_down_advisory_main_main_pressed, lv_color_make(0xFF, 0x33, 0xFF));
	lv_style_set_img_recolor(&style_screen_gear_down_advisory_main_main_pressed, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_img_recolor_opa(&style_screen_gear_down_advisory_main_main_pressed, 0);
	lv_obj_add_style(ui->screen_Gear_Down_Advisory, &style_screen_gear_down_advisory_main_main_pressed, LV_PART_MAIN|LV_STATE_PRESSED);

	//Write style state: LV_STATE_CHECKED for style_screen_gear_down_advisory_main_main_checked
	static lv_style_t style_screen_gear_down_advisory_main_main_checked;
	lv_style_reset(&style_screen_gear_down_advisory_main_main_checked);
	lv_style_set_text_color(&style_screen_gear_down_advisory_main_main_checked, lv_color_make(0xFF, 0x33, 0xFF));
	lv_style_set_img_recolor(&style_screen_gear_down_advisory_main_main_checked, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_img_recolor_opa(&style_screen_gear_down_advisory_main_main_checked, 0);
	lv_obj_add_style(ui->screen_Gear_Down_Advisory, &style_screen_gear_down_advisory_main_main_checked, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_imgbtn_set_src(ui->screen_Gear_Down_Advisory, LV_IMGBTN_STATE_RELEASED, NULL, &new_night_gear_arrows_down_white, NULL);
	lv_imgbtn_set_src(ui->screen_Gear_Down_Advisory, LV_IMGBTN_STATE_PRESSED, NULL, &_img_night_gear_arrows_down_white_13x9, NULL);
	lv_obj_add_flag(ui->screen_Gear_Down_Advisory, LV_OBJ_FLAG_CHECKABLE);

	//Write codes screen_Service_Due
	ui->screen_Service_Due = lv_imgbtn_create(ui->screen);
	lv_obj_set_pos(ui->screen_Service_Due, 207, 234);
	lv_obj_set_size(ui->screen_Service_Due, 25, 25);

	//Write style state: LV_STATE_DEFAULT for style_screen_service_due_main_main_default
	static lv_style_t style_screen_service_due_main_main_default;
	lv_style_reset(&style_screen_service_due_main_main_default);
	lv_style_set_text_color(&style_screen_service_due_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_img_recolor(&style_screen_service_due_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_img_recolor_opa(&style_screen_service_due_main_main_default, 3);
	lv_style_set_img_opa(&style_screen_service_due_main_main_default, 255);
	lv_obj_add_style(ui->screen_Service_Due, &style_screen_service_due_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_move_foreground(ui->screen_Service_Due);

	//Write style state: LV_STATE_PRESSED for style_screen_service_due_main_main_pressed
	static lv_style_t style_screen_service_due_main_main_pressed;
	lv_style_reset(&style_screen_service_due_main_main_pressed);
	lv_style_set_text_color(&style_screen_service_due_main_main_pressed, lv_color_make(0xFF, 0x33, 0xFF));
	lv_style_set_img_recolor(&style_screen_service_due_main_main_pressed, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_img_recolor_opa(&style_screen_service_due_main_main_pressed, 0);
	lv_obj_add_style(ui->screen_Service_Due, &style_screen_service_due_main_main_pressed, LV_PART_MAIN|LV_STATE_PRESSED);

	//Write style state: LV_STATE_CHECKED for style_screen_service_due_main_main_checked
	static lv_style_t style_screen_service_due_main_main_checked;
	lv_style_reset(&style_screen_service_due_main_main_checked);
	lv_style_set_text_color(&style_screen_service_due_main_main_checked, lv_color_make(0xFF, 0x33, 0xFF));
	lv_style_set_img_recolor(&style_screen_service_due_main_main_checked, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_img_recolor_opa(&style_screen_service_due_main_main_checked, 0);
	lv_obj_add_style(ui->screen_Service_Due, &style_screen_service_due_main_main_checked, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_imgbtn_set_src(ui->screen_Service_Due, LV_IMGBTN_STATE_RELEASED, NULL, &img_Service_Remainder_25x25, NULL);
	lv_imgbtn_set_src(ui->screen_Service_Due, LV_IMGBTN_STATE_PRESSED, NULL, &_Layer_0_22x25, NULL);
	lv_obj_add_flag(ui->screen_Service_Due, LV_OBJ_FLAG_CHECKABLE);

	//Write codes screen_Black
	ui->screen_Black = lv_img_create(ui->screen);
	lv_obj_set_pos(ui->screen_Black, 48, 99);
	lv_obj_set_size(ui->screen_Black, 9, 9);

	//Write style state: LV_STATE_DEFAULT for style_screen_black_main_main_default
	static lv_style_t style_screen_black_main_main_default;
	lv_style_reset(&style_screen_black_main_main_default);
	lv_style_set_img_recolor(&style_screen_black_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_black_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_black_main_main_default, 255);
	lv_obj_add_style(ui->screen_Black, &style_screen_black_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->screen_Black, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_Black,&_Layer_0_9x9);
	lv_img_set_pivot(ui->screen_Black, 0,0);
	lv_img_set_angle(ui->screen_Black, 0);

	//Write codes screen_TachoBar0
	ui->screen_TachoBar0 = lv_img_create(ui->screen);
	lv_obj_set_pos(ui->screen_TachoBar0, 7, 6);
	lv_obj_set_size(ui->screen_TachoBar0, 227, 75);

	//Write style state: LV_STATE_DEFAULT for style_screen_tachobar0_main_main_default
	static lv_style_t style_screen_tachobar0_main_main_default;
	lv_style_reset(&style_screen_tachobar0_main_main_default);
	lv_style_set_img_recolor(&style_screen_tachobar0_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_tachobar0_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_tachobar0_main_main_default, 255);
	lv_obj_add_style(ui->screen_TachoBar0, &style_screen_tachobar0_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->screen_TachoBar0, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_TachoBar0,&img_tacho_chaplets);
	lv_img_set_pivot(ui->screen_TachoBar0, 0,0);
	lv_img_set_angle(ui->screen_TachoBar0, 0);

	//Write codes screen_TachoBar0_1
	ui->screen_TachoBar0_1 = lv_img_create(ui->screen);
	lv_obj_set_pos(ui->screen_TachoBar0_1, 3, 8);
	lv_obj_set_size(ui->screen_TachoBar0_1, 231, 78);

	//Write style state: LV_STATE_DEFAULT for style_screen_tachobar0_1_main_main_default
	static lv_style_t style_screen_tachobar0_1_main_main_default;
	lv_style_reset(&style_screen_tachobar0_1_main_main_default);
	lv_style_set_img_recolor(&style_screen_tachobar0_1_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_tachobar0_1_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_tachobar0_1_main_main_default, 255);
	lv_obj_add_style(ui->screen_TachoBar0_1, &style_screen_tachobar0_1_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->screen_TachoBar0_1, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_TachoBar0_1,&_img_night_tacho_fill_001_231x78);
	lv_img_set_pivot(ui->screen_TachoBar0_1, 0,0);
	lv_img_set_angle(ui->screen_TachoBar0_1, 0);
	//set_obj_opa(ui->screen_TachoBar0_1, 255);

	//Write codes screen_Fuel_Img_Icon
	ui->screen_Fuel_Img_Icon = lv_img_create(ui->screen);
	lv_obj_set_pos(ui->screen_Fuel_Img_Icon, 105, 253);
	lv_obj_set_size(ui->screen_Fuel_Img_Icon, 30, 30);

	//Write style state: LV_STATE_DEFAULT for style_screen_fuel_img_icon_main_main_default
	static lv_style_t style_screen_fuel_img_icon_main_main_default;
	lv_style_reset(&style_screen_fuel_img_icon_main_main_default);
	lv_style_set_img_recolor(&style_screen_fuel_img_icon_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_fuel_img_icon_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_fuel_img_icon_main_main_default, 0);
	lv_obj_add_style(ui->screen_Fuel_Img_Icon, &style_screen_fuel_img_icon_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->screen_Fuel_Img_Icon, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_Fuel_Img_Icon,&_img_night_display_units_fuel_icon_30x30);
	lv_img_set_pivot(ui->screen_Fuel_Img_Icon, 0,0);
	lv_img_set_angle(ui->screen_Fuel_Img_Icon, 0);

	//Write codes screen_imgOilTelltale
	ui->screen_imgOilTelltale = lv_imgbtn_create(ui->screen);
	lv_obj_set_pos(ui->screen_imgOilTelltale, 4, 290);
	lv_obj_set_size(ui->screen_imgOilTelltale, 34, 14);

	//Write style state: LV_STATE_DEFAULT for style_screen_imgoiltelltale_main_main_default
	static lv_style_t style_screen_imgoiltelltale_main_main_default;
	lv_style_reset(&style_screen_imgoiltelltale_main_main_default);
	lv_style_set_text_color(&style_screen_imgoiltelltale_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_img_recolor(&style_screen_imgoiltelltale_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_imgoiltelltale_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_imgoiltelltale_main_main_default, 254);
	lv_obj_add_style(ui->screen_imgOilTelltale, &style_screen_imgoiltelltale_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style state: LV_STATE_PRESSED for style_screen_imgoiltelltale_main_main_pressed
	static lv_style_t style_screen_imgoiltelltale_main_main_pressed;
	lv_style_reset(&style_screen_imgoiltelltale_main_main_pressed);
	lv_style_set_text_color(&style_screen_imgoiltelltale_main_main_pressed, lv_color_make(0xFF, 0x33, 0xFF));
	lv_style_set_img_recolor(&style_screen_imgoiltelltale_main_main_pressed, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_img_recolor_opa(&style_screen_imgoiltelltale_main_main_pressed, 0);
	lv_obj_add_style(ui->screen_imgOilTelltale, &style_screen_imgoiltelltale_main_main_pressed, LV_PART_MAIN|LV_STATE_PRESSED);

	//Write style state: LV_STATE_CHECKED for style_screen_imgoiltelltale_main_main_checked
	static lv_style_t style_screen_imgoiltelltale_main_main_checked;
	lv_style_reset(&style_screen_imgoiltelltale_main_main_checked);
	lv_style_set_text_color(&style_screen_imgoiltelltale_main_main_checked, lv_color_make(0xFF, 0x33, 0xFF));
	lv_style_set_img_recolor(&style_screen_imgoiltelltale_main_main_checked, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_img_recolor_opa(&style_screen_imgoiltelltale_main_main_checked, 0);
	lv_obj_add_style(ui->screen_imgOilTelltale, &style_screen_imgoiltelltale_main_main_checked, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_imgbtn_set_src(ui->screen_imgOilTelltale, LV_IMGBTN_STATE_RELEASED, NULL, &new_oil_telltale, NULL);
	lv_imgbtn_set_src(ui->screen_imgOilTelltale, LV_IMGBTN_STATE_PRESSED, NULL, &_Layer_0_alpha_32x13, NULL);
	lv_obj_add_flag(ui->screen_imgOilTelltale, LV_OBJ_FLAG_CHECKABLE);

	//Write codes screen_Sub_Button
	ui->screen_Sub_Button = lv_imgbtn_create(ui->screen);
	lv_obj_set_pos(ui->screen_Sub_Button, 200, 150);
	lv_obj_set_size(ui->screen_Sub_Button, 20, 20);

	//Write style state: LV_STATE_DEFAULT for style_screen_sub_button_main_main_default
	static lv_style_t style_screen_sub_button_main_main_default;
	lv_style_reset(&style_screen_sub_button_main_main_default);
	lv_style_set_text_color(&style_screen_sub_button_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_img_recolor(&style_screen_sub_button_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_sub_button_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_sub_button_main_main_default, 255);
	lv_obj_add_style(ui->screen_Sub_Button, &style_screen_sub_button_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style state: LV_STATE_PRESSED for style_screen_sub_button_main_main_pressed
	static lv_style_t style_screen_sub_button_main_main_pressed;
	lv_style_reset(&style_screen_sub_button_main_main_pressed);
	lv_style_set_text_color(&style_screen_sub_button_main_main_pressed, lv_color_make(0xFF, 0x33, 0xFF));
	lv_style_set_img_recolor(&style_screen_sub_button_main_main_pressed, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_img_recolor_opa(&style_screen_sub_button_main_main_pressed, 0);
	lv_obj_add_style(ui->screen_Sub_Button, &style_screen_sub_button_main_main_pressed, LV_PART_MAIN|LV_STATE_PRESSED);

	//Write style state: LV_STATE_CHECKED for style_screen_sub_button_main_main_checked
	static lv_style_t style_screen_sub_button_main_main_checked;
	lv_style_reset(&style_screen_sub_button_main_main_checked);
	lv_style_set_text_color(&style_screen_sub_button_main_main_checked, lv_color_make(0xFF, 0x33, 0xFF));
	lv_style_set_img_recolor(&style_screen_sub_button_main_main_checked, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_img_recolor_opa(&style_screen_sub_button_main_main_checked, 0);
	lv_obj_add_style(ui->screen_Sub_Button, &style_screen_sub_button_main_main_checked, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_imgbtn_set_src(ui->screen_Sub_Button, LV_IMGBTN_STATE_RELEASED, NULL, &_Button_alpha_20x20, NULL);
	lv_imgbtn_set_src(ui->screen_Sub_Button, LV_IMGBTN_STATE_PRESSED, NULL, &_Layer_0_alpha_20x20, NULL);
	lv_obj_add_flag(ui->screen_Sub_Button, LV_OBJ_FLAG_CHECKABLE);

	//Write codes screen_Sub_Button_Intermediatae
	ui->screen_Sub_Button_Intermediatae = lv_img_create(ui->screen);
	lv_obj_set_pos(ui->screen_Sub_Button_Intermediatae, 204, 151);
	lv_obj_set_size(ui->screen_Sub_Button_Intermediatae, 20, 20);

	//Write style state: LV_STATE_DEFAULT for style_screen_sub_button_intermediatae_main_main_default
	static lv_style_t style_screen_sub_button_intermediatae_main_main_default;
	lv_style_reset(&style_screen_sub_button_intermediatae_main_main_default);
	lv_style_set_img_recolor(&style_screen_sub_button_intermediatae_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_sub_button_intermediatae_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_sub_button_intermediatae_main_main_default, 255);
	lv_obj_add_style(ui->screen_Sub_Button_Intermediatae, &style_screen_sub_button_intermediatae_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->screen_Sub_Button_Intermediatae, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_Sub_Button_Intermediatae,&_Button_20x20);
	lv_img_set_pivot(ui->screen_Sub_Button_Intermediatae, 0,0);
	lv_img_set_angle(ui->screen_Sub_Button_Intermediatae, 0);

	//Write codes screen_Clock_Am
	ui->screen_Clock_Am = lv_label_create(ui->screen);
	lv_obj_set_pos(ui->screen_Clock_Am, 118, 69);
	lv_obj_set_size(ui->screen_Clock_Am, 16, 12);
	lv_label_set_text(ui->screen_Clock_Am, "AM");
	lv_label_set_long_mode(ui->screen_Clock_Am, LV_LABEL_LONG_WRAP);
	lv_obj_set_style_text_align(ui->screen_Clock_Am, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_screen_clock_am_main_main_default
	static lv_style_t style_screen_clock_am_main_main_default;
	lv_style_reset(&style_screen_clock_am_main_main_default);
	lv_style_set_radius(&style_screen_clock_am_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_clock_am_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_clock_am_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_clock_am_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_clock_am_main_main_default, 0);
	lv_style_set_text_color(&style_screen_clock_am_main_main_default, lv_color_make(0xfa, 0xfa, 0xfa));
	lv_style_set_text_font(&style_screen_clock_am_main_main_default, &lv_font_FjallaOne_Regular_17);
	lv_style_set_text_letter_space(&style_screen_clock_am_main_main_default, 2);
	lv_style_set_pad_left(&style_screen_clock_am_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_clock_am_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_clock_am_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_clock_am_main_main_default, 0);
	lv_obj_add_style(ui->screen_Clock_Am, &style_screen_clock_am_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_Music_Icon
	ui->screen_Music_Icon = lv_img_create(ui->screen);
	lv_obj_set_pos(ui->screen_Music_Icon, 105, 252);
	lv_obj_set_size(ui->screen_Music_Icon, 30, 30);

	//Write style state: LV_STATE_DEFAULT for style_screen_music_icon_main_main_default
	static lv_style_t style_screen_music_icon_main_main_default;
	lv_style_reset(&style_screen_music_icon_main_main_default);
	lv_style_set_img_recolor(&style_screen_music_icon_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_music_icon_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_music_icon_main_main_default, 0);
	lv_obj_add_style(ui->screen_Music_Icon, &style_screen_music_icon_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->screen_Music_Icon, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_Music_Icon,&_grp_night_common_30x30);
	lv_img_set_pivot(ui->screen_Music_Icon, 0,0);
	lv_img_set_angle(ui->screen_Music_Icon, 0);

	//Write codes screen_Slider
	ui->screen_Slider = lv_slider_create(ui->screen);
	lv_obj_set_pos(ui->screen_Slider, 55, 240);
	lv_obj_set_size(ui->screen_Slider, 137, 2);

	//Write style state: LV_STATE_DEFAULT for style_screen_slider_main_main_default
	static lv_style_t style_screen_slider_main_main_default;
	lv_style_reset(&style_screen_slider_main_main_default);
	lv_style_set_radius(&style_screen_slider_main_main_default, 50);
	lv_style_set_bg_color(&style_screen_slider_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_screen_slider_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_screen_slider_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_slider_main_main_default, 255);
	lv_style_set_outline_color(&style_screen_slider_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_outline_width(&style_screen_slider_main_main_default, 0);
	lv_style_set_outline_opa(&style_screen_slider_main_main_default, 0);
	lv_style_set_pad_left(&style_screen_slider_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_slider_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_slider_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_slider_main_main_default, 0);
	lv_obj_add_style(ui->screen_Slider, &style_screen_slider_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style state: LV_STATE_DEFAULT for style_screen_slider_main_indicator_default
	static lv_style_t style_screen_slider_main_indicator_default;
	lv_style_reset(&style_screen_slider_main_indicator_default);
	lv_style_set_radius(&style_screen_slider_main_indicator_default, 50);
	lv_style_set_bg_color(&style_screen_slider_main_indicator_default, lv_color_make(0xf6, 0x93, 0x23));
	lv_style_set_bg_grad_color(&style_screen_slider_main_indicator_default, lv_color_make(0xf6, 0x57, 0x23));
	lv_style_set_bg_grad_dir(&style_screen_slider_main_indicator_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_slider_main_indicator_default, 255);
	lv_obj_add_style(ui->screen_Slider, &style_screen_slider_main_indicator_default, LV_PART_INDICATOR|LV_STATE_DEFAULT);

	//Write style state: LV_STATE_DEFAULT for style_screen_slider_main_knob_default
	static lv_style_t style_screen_slider_main_knob_default;
	lv_style_reset(&style_screen_slider_main_knob_default);
	lv_style_set_radius(&style_screen_slider_main_knob_default, 50);
	lv_style_set_bg_color(&style_screen_slider_main_knob_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_screen_slider_main_knob_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_screen_slider_main_knob_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_slider_main_knob_default, 255);
	lv_obj_add_style(ui->screen_Slider, &style_screen_slider_main_knob_default, LV_PART_KNOB|LV_STATE_DEFAULT);
	lv_slider_set_range(ui->screen_Slider,0, 100);
	lv_slider_set_value(ui->screen_Slider,50,false);

	//Write codes screen_x1000RPM_Img
	ui->screen_x1000RPM_Img = lv_img_create(ui->screen);
	lv_obj_set_pos(ui->screen_x1000RPM_Img, 94, 53);
	lv_obj_set_size(ui->screen_x1000RPM_Img, 51, 13);

	//Write style state: LV_STATE_DEFAULT for style_screen_x1000rpm_img_main_main_default
	static lv_style_t style_screen_x1000rpm_img_main_main_default;
	lv_style_reset(&style_screen_x1000rpm_img_main_main_default);
	lv_style_set_img_recolor(&style_screen_x1000rpm_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_x1000rpm_img_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_x1000rpm_img_main_main_default, 255);
	lv_obj_add_style(ui->screen_x1000RPM_Img, &style_screen_x1000rpm_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->screen_x1000RPM_Img, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_x1000RPM_Img,&_1000_RPM_49x13);
	lv_img_set_pivot(ui->screen_x1000RPM_Img, 0,0);
	lv_img_set_angle(ui->screen_x1000RPM_Img, 0);
	

	//Write codes screen_Fuel_low_mMarker
	ui->screen_Fuel_low_mMarker = lv_img_create(ui->screen);
	lv_obj_set_pos(ui->screen_Fuel_low_mMarker, 35, 276);
	lv_obj_set_size(ui->screen_Fuel_low_mMarker, 11, 13);

	//Write style state: LV_STATE_DEFAULT for style_screen_fuel_low_mmarker_main_main_default
	static lv_style_t style_screen_fuel_low_mmarker_main_main_default;
	lv_style_reset(&style_screen_fuel_low_mmarker_main_main_default);
	lv_style_set_img_recolor(&style_screen_fuel_low_mmarker_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_fuel_low_mmarker_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_fuel_low_mmarker_main_main_default, 255);
	lv_obj_add_style(ui->screen_Fuel_low_mMarker, &style_screen_fuel_low_mmarker_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->screen_Fuel_low_mMarker, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_Fuel_low_mMarker,&_img_night_fuel_low_marker_11x13);
	lv_img_set_pivot(ui->screen_Fuel_low_mMarker, 0,0);
	lv_img_set_angle(ui->screen_Fuel_low_mMarker, 0);

	//Write codes screen_Batt_Outline
	ui->screen_Batt_Outline = lv_img_create(ui->screen);
	lv_obj_set_pos(ui->screen_Batt_Outline, 26, 111);
	lv_obj_set_size(ui->screen_Batt_Outline, 20, 12);

	//Write style state: LV_STATE_DEFAULT for style_screen_batt_outline_main_main_default
	static lv_style_t style_screen_batt_outline_main_main_default;
	lv_style_reset(&style_screen_batt_outline_main_main_default);
	lv_style_set_img_recolor(&style_screen_batt_outline_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_batt_outline_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_batt_outline_main_main_default, 255);
	lv_obj_add_style(ui->screen_Batt_Outline, &style_screen_batt_outline_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->screen_Batt_Outline, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_Batt_Outline,&_Layer_0_9x9);
	lv_img_set_pivot(ui->screen_Batt_Outline, 0,0);
	lv_img_set_angle(ui->screen_Batt_Outline, 0);
	

	//Write codes screen_Signal_1
	ui->screen_Signal_1 = lv_img_create(ui->screen);
	lv_obj_set_pos(ui->screen_Signal_1, 200, 119);
	lv_obj_set_size(ui->screen_Signal_1, 2, 4);

	//Write style state: LV_STATE_DEFAULT for style_screen_signal_1_main_main_default
	static lv_style_t style_screen_signal_1_main_main_default;
	lv_style_reset(&style_screen_signal_1_main_main_default);
	lv_style_set_img_recolor(&style_screen_signal_1_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_signal_1_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_signal_1_main_main_default, 255);
	lv_obj_add_style(ui->screen_Signal_1, &style_screen_signal_1_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->screen_Signal_1, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_Signal_1,&_Layer_0_9x9);
	lv_img_set_pivot(ui->screen_Signal_1, 0,0);
	lv_img_set_angle(ui->screen_Signal_1, 0);

	
	//Write codes screen_Whit_Img
	ui->screen_Whit_Img = lv_img_create(ui->screen);
	lv_obj_set_pos(ui->screen_Whit_Img, 48, 99);
	lv_obj_set_size(ui->screen_Whit_Img, 9, 9);

	//Write style state: LV_STATE_DEFAULT for style_screen_whit_img_main_main_default
	static lv_style_t style_screen_whit_img_main_main_default;
	lv_style_reset(&style_screen_whit_img_main_main_default);
	lv_style_set_img_recolor(&style_screen_whit_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_whit_img_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_whit_img_main_main_default, 255);
	lv_obj_add_style(ui->screen_Whit_Img, &style_screen_whit_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->screen_Whit_Img, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_Whit_Img,&_Batt_2_9x9);
	lv_img_set_pivot(ui->screen_Whit_Img, 0,0);
	lv_img_set_angle(ui->screen_Whit_Img, 0);

	//Write codes screen_img_An_1
	ui->screen_img_An_1 = lv_img_create(ui->screen);
	lv_obj_set_pos(ui->screen_img_An_1, 0, 0);
	lv_obj_set_size(ui->screen_img_An_1, 240, 320);

	//Write style state: LV_STATE_DEFAULT for style_screen_img_an_1_main_main_default
	static lv_style_t style_screen_img_an_1_main_main_default;
	lv_style_reset(&style_screen_img_an_1_main_main_default);
	lv_style_set_img_recolor(&style_screen_img_an_1_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_img_an_1_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_img_an_1_main_main_default, 0);
	lv_obj_add_style(ui->screen_img_An_1, &style_screen_img_an_1_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->screen_img_An_1, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_img_An_1,&_1_240x320);
	lv_img_set_pivot(ui->screen_img_An_1, 0,0);
	lv_img_set_angle(ui->screen_img_An_1, 0);

	//Write codes screen_D_A_Icon
	ui->screen_D_A_Icon = lv_img_create(ui->screen);
	lv_obj_set_pos(ui->screen_D_A_Icon, 105, 252);
	lv_obj_set_size(ui->screen_D_A_Icon, 30, 30);

	//Write style state: LV_STATE_DEFAULT for style_screen_d_a_icon_main_main_default
	static lv_style_t style_screen_d_a_icon_main_main_default;
	lv_style_reset(&style_screen_d_a_icon_main_main_default);
	lv_style_set_img_recolor(&style_screen_d_a_icon_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_d_a_icon_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_d_a_icon_main_main_default, 0);
	lv_obj_add_style(ui->screen_D_A_Icon, &style_screen_d_a_icon_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->screen_D_A_Icon, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_D_A_Icon,&_D_A_I_30x30);
	lv_img_set_pivot(ui->screen_D_A_Icon, 0,0);
	lv_img_set_angle(ui->screen_D_A_Icon, 0);

	//Write codes screen_D_B_Icon
	ui->screen_D_B_Icon = lv_img_create(ui->screen);
	lv_obj_set_pos(ui->screen_D_B_Icon, 105, 252);
	lv_obj_set_size(ui->screen_D_B_Icon, 30, 30);

	//Write style state: LV_STATE_DEFAULT for style_screen_d_b_icon_main_main_default
	static lv_style_t style_screen_d_b_icon_main_main_default;
	lv_style_reset(&style_screen_d_b_icon_main_main_default);
	lv_style_set_img_recolor(&style_screen_d_b_icon_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_d_b_icon_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_d_b_icon_main_main_default, 0);
	lv_obj_add_style(ui->screen_D_B_Icon, &style_screen_d_b_icon_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->screen_D_B_Icon, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_D_B_Icon,&_D_B_I_30x30);
	lv_img_set_pivot(ui->screen_D_B_Icon, 0,0);
	lv_img_set_angle(ui->screen_D_B_Icon, 0);

	//Write codes screen_D_Up_A
	ui->screen_D_Up_A = lv_img_create(ui->screen);
	lv_obj_set_pos(ui->screen_D_Up_A, 31, 135);
	lv_obj_set_size(ui->screen_D_Up_A, 13, 9);

	//Write style state: LV_STATE_DEFAULT for style_screen_d_up_a_main_main_default
	static lv_style_t style_screen_d_up_a_main_main_default;
	lv_style_reset(&style_screen_d_up_a_main_main_default);
	lv_style_set_img_recolor(&style_screen_d_up_a_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_d_up_a_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_d_up_a_main_main_default, 255);
	lv_obj_add_style(ui->screen_D_Up_A, &style_screen_d_up_a_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->screen_D_Up_A, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_D_Up_A,&_img_night_gear_arrows_up_grey_13x9);
	lv_img_set_pivot(ui->screen_D_Up_A, 0,0);
	lv_img_set_angle(ui->screen_D_Up_A, 0);

	//Write codes screen_D_Down_A
	ui->screen_D_Down_A = lv_img_create(ui->screen);
	lv_obj_set_pos(ui->screen_D_Down_A, 31, 178);
	lv_obj_set_size(ui->screen_D_Down_A, 13, 9);

	//Write style state: LV_STATE_DEFAULT for style_screen_d_down_a_main_main_default
	static lv_style_t style_screen_d_down_a_main_main_default;
	lv_style_reset(&style_screen_d_down_a_main_main_default);
	lv_style_set_img_recolor(&style_screen_d_down_a_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_d_down_a_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_d_down_a_main_main_default, 255);
	lv_obj_add_style(ui->screen_D_Down_A, &style_screen_d_down_a_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->screen_D_Down_A, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_D_Down_A,&_img_night_gear_arrows_down_grey_13x9);
	lv_img_set_pivot(ui->screen_D_Down_A, 0,0);
	lv_img_set_angle(ui->screen_D_Down_A, 0);

	//Write codes screen_Whi_gear
	ui->screen_Whi_gear = lv_img_create(ui->screen);
	lv_obj_set_pos(ui->screen_Whi_gear, 17, 148);
	lv_obj_set_size(ui->screen_Whi_gear, 10, 24);

	//Write style state: LV_STATE_DEFAULT for style_screen_whi_gear_main_main_default
	static lv_style_t style_screen_whi_gear_main_main_default;
	lv_style_reset(&style_screen_whi_gear_main_main_default);
	lv_style_set_img_recolor(&style_screen_whi_gear_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_whi_gear_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_whi_gear_main_main_default, 255);
	lv_obj_add_style(ui->screen_Whi_gear, &style_screen_whi_gear_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->screen_Whi_gear, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_Whi_gear,&_White_gear_10x24);
	lv_img_set_pivot(ui->screen_Whi_gear, 0,0);
	lv_img_set_angle(ui->screen_Whi_gear, 0);

	//Write codes screen_contscr_1
	ui->screen_contscr_1 = lv_obj_create(ui->screen);
	lv_obj_set_pos(ui->screen_contscr_1, 30, 167);
	lv_obj_set_size(ui->screen_contscr_1, 210, 78);

	//Write style state: LV_STATE_DEFAULT for style_screen_contscr_1_main_main_default
	static lv_style_t style_screen_contscr_1_main_main_default;
	lv_style_reset(&style_screen_contscr_1_main_main_default);
	lv_style_set_radius(&style_screen_contscr_1_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_contscr_1_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_color(&style_screen_contscr_1_main_main_default, lv_color_make(0x08, 0x08, 0x08));
	lv_style_set_bg_grad_dir(&style_screen_contscr_1_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_contscr_1_main_main_default, 0);
	lv_style_set_border_color(&style_screen_contscr_1_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_border_width(&style_screen_contscr_1_main_main_default, 0);
	lv_style_set_border_opa(&style_screen_contscr_1_main_main_default, 0);
	lv_style_set_pad_left(&style_screen_contscr_1_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_contscr_1_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_contscr_1_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_contscr_1_main_main_default, 0);
	lv_obj_add_style(ui->screen_contscr_1, &style_screen_contscr_1_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_L1_lbl
	ui->screen_L1_lbl = lv_label_create(ui->screen_contscr_1);
	lv_obj_set_pos(ui->screen_L1_lbl, 0, 21);
	lv_obj_set_size(ui->screen_L1_lbl, 79, 17);
	lv_label_set_text(ui->screen_L1_lbl, "Av Speed");
	lv_label_set_long_mode(ui->screen_L1_lbl, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->screen_L1_lbl, LV_TEXT_ALIGN_RIGHT, 0);

	//Write style state: LV_STATE_DEFAULT for style_screen_l1_lbl_main_main_default
	static lv_style_t style_screen_l1_lbl_main_main_default;
	lv_style_reset(&style_screen_l1_lbl_main_main_default);
	lv_style_set_radius(&style_screen_l1_lbl_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_l1_lbl_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_l1_lbl_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_l1_lbl_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_l1_lbl_main_main_default, 0);
	lv_style_set_text_color(&style_screen_l1_lbl_main_main_default, lv_color_make(0xff, 0x78, 0x00));
	lv_style_set_text_font(&style_screen_l1_lbl_main_main_default, &lv_font_FjallaOne_Regular_17);
	lv_style_set_text_letter_space(&style_screen_l1_lbl_main_main_default, 0);
	lv_style_set_pad_left(&style_screen_l1_lbl_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_l1_lbl_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_l1_lbl_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_l1_lbl_main_main_default, 0);
	lv_obj_add_style(ui->screen_L1_lbl, &style_screen_l1_lbl_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_L1_val
	ui->screen_L1_val = lv_label_create(ui->screen_contscr_1);
	lv_obj_set_pos(ui->screen_L1_val, 81, 18);
	lv_obj_set_size(ui->screen_L1_val, 48, 18);
	lv_label_set_text(ui->screen_L1_val, "123.9");
	lv_label_set_long_mode(ui->screen_L1_val, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->screen_L1_val, LV_TEXT_ALIGN_RIGHT, 0);

	//Write style state: LV_STATE_DEFAULT for style_screen_l1_val_main_main_default
	static lv_style_t style_screen_l1_val_main_main_default;
	lv_style_reset(&style_screen_l1_val_main_main_default);
	lv_style_set_radius(&style_screen_l1_val_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_l1_val_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_l1_val_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_l1_val_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_l1_val_main_main_default, 0);
	lv_style_set_text_color(&style_screen_l1_val_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_screen_l1_val_main_main_default, &lv_font_FjallaOne_Regular_22);
	lv_style_set_text_letter_space(&style_screen_l1_val_main_main_default, 0);
	lv_style_set_pad_left(&style_screen_l1_val_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_l1_val_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_l1_val_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_l1_val_main_main_default, 0);
	lv_obj_add_style(ui->screen_L1_val, &style_screen_l1_val_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_L1_unit
	ui->screen_L1_unit = lv_label_create(ui->screen_contscr_1);
	lv_obj_set_pos(ui->screen_L1_unit, 131, 21);
	lv_obj_set_size(ui->screen_L1_unit, 56, 19);
	lv_label_set_text(ui->screen_L1_unit, "L/100km");
	lv_label_set_long_mode(ui->screen_L1_unit, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->screen_L1_unit, LV_TEXT_ALIGN_LEFT, 0);

	//Write style state: LV_STATE_DEFAULT for style_screen_l1_unit_main_main_default
	static lv_style_t style_screen_l1_unit_main_main_default;
	lv_style_reset(&style_screen_l1_unit_main_main_default);
	lv_style_set_radius(&style_screen_l1_unit_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_l1_unit_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_l1_unit_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_l1_unit_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_l1_unit_main_main_default, 0);
	lv_style_set_text_color(&style_screen_l1_unit_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_screen_l1_unit_main_main_default, &lv_font_FjallaOne_Regular_17);
	lv_style_set_text_letter_space(&style_screen_l1_unit_main_main_default, 0);
	lv_style_set_pad_left(&style_screen_l1_unit_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_l1_unit_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_l1_unit_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_l1_unit_main_main_default, 0);
	lv_obj_add_style(ui->screen_L1_unit, &style_screen_l1_unit_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_L2_lbl
	ui->screen_L2_lbl = lv_label_create(ui->screen_contscr_1);
	lv_obj_set_pos(ui->screen_L2_lbl, 0, 47);
	lv_obj_set_size(ui->screen_L2_lbl, 79, 17);
	lv_label_set_text(ui->screen_L2_lbl, "Service Due");
	lv_label_set_long_mode(ui->screen_L2_lbl, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->screen_L2_lbl, LV_TEXT_ALIGN_RIGHT, 0);

	//Write style state: LV_STATE_DEFAULT for style_screen_l2_lbl_main_main_default
	static lv_style_t style_screen_l2_lbl_main_main_default;
	lv_style_reset(&style_screen_l2_lbl_main_main_default);
	lv_style_set_radius(&style_screen_l2_lbl_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_l2_lbl_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_l2_lbl_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_l2_lbl_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_l2_lbl_main_main_default, 0);
	lv_style_set_text_color(&style_screen_l2_lbl_main_main_default, lv_color_make(0xff, 0x78, 0x00));
	lv_style_set_text_font(&style_screen_l2_lbl_main_main_default, &lv_font_FjallaOne_Regular_17);
	lv_style_set_text_letter_space(&style_screen_l2_lbl_main_main_default, 0);
	lv_style_set_pad_left(&style_screen_l2_lbl_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_l2_lbl_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_l2_lbl_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_l2_lbl_main_main_default, 0);
	lv_obj_add_style(ui->screen_L2_lbl, &style_screen_l2_lbl_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_L2_val
	ui->screen_L2_val = lv_label_create(ui->screen_contscr_1);
	lv_obj_set_pos(ui->screen_L2_val, 81, 45);
	lv_obj_set_size(ui->screen_L2_val, 104, 18);
	lv_label_set_text(ui->screen_L2_val, "00 h 00m");
	lv_label_set_long_mode(ui->screen_L2_val, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->screen_L2_val, LV_TEXT_ALIGN_RIGHT, 0);

	//Write style state: LV_STATE_DEFAULT for style_screen_l2_val_main_main_default
	static lv_style_t style_screen_l2_val_main_main_default;
	lv_style_reset(&style_screen_l2_val_main_main_default);
	lv_style_set_radius(&style_screen_l2_val_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_l2_val_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_l2_val_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_l2_val_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_l2_val_main_main_default, 0);
	lv_style_set_text_color(&style_screen_l2_val_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_screen_l2_val_main_main_default, &lv_font_FjallaOne_Regular_22);
	lv_style_set_text_letter_space(&style_screen_l2_val_main_main_default, 0);
	lv_style_set_pad_left(&style_screen_l2_val_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_l2_val_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_l2_val_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_l2_val_main_main_default, 0);
	lv_obj_add_style(ui->screen_L2_val, &style_screen_l2_val_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_L2_unit
	ui->screen_L2_unit = lv_label_create(ui->screen_contscr_1);
	lv_obj_set_pos(ui->screen_L2_unit, 131, 46);
	lv_obj_set_size(ui->screen_L2_unit, 56, 19);
	lv_label_set_text(ui->screen_L2_unit, "L/100km");
	lv_label_set_long_mode(ui->screen_L2_unit, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->screen_L2_unit, LV_TEXT_ALIGN_LEFT, 0);

	//Write style state: LV_STATE_DEFAULT for style_screen_l2_unit_main_main_default
	static lv_style_t style_screen_l2_unit_main_main_default;
	lv_style_reset(&style_screen_l2_unit_main_main_default);
	lv_style_set_radius(&style_screen_l2_unit_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_l2_unit_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_l2_unit_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_l2_unit_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_l2_unit_main_main_default, 0);
	lv_style_set_text_color(&style_screen_l2_unit_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_screen_l2_unit_main_main_default, &lv_font_FjallaOne_Regular_17);
	lv_style_set_text_letter_space(&style_screen_l2_unit_main_main_default, 0);
	lv_style_set_pad_left(&style_screen_l2_unit_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_l2_unit_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_l2_unit_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_l2_unit_main_main_default, 0);
	lv_obj_add_style(ui->screen_L2_unit, &style_screen_l2_unit_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_up_arr
	ui->screen_up_arr = lv_img_create(ui->screen_contscr_1);
	lv_obj_set_pos(ui->screen_up_arr, 80, 4);
	lv_obj_set_size(ui->screen_up_arr, 14, 9);

	//Write style state: LV_STATE_DEFAULT for style_screen_up_arr_main_main_default
	static lv_style_t style_screen_up_arr_main_main_default;
	lv_style_reset(&style_screen_up_arr_main_main_default);
	lv_style_set_img_recolor(&style_screen_up_arr_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_up_arr_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_up_arr_main_main_default, 255);
	lv_obj_add_style(ui->screen_up_arr, &style_screen_up_arr_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->screen_up_arr, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_up_arr,&_white_12x7);
	lv_img_set_src(ui->screen_up_arr,&new_trip_up_arrow);
	lv_img_set_pivot(ui->screen_up_arr, 0,0);
	lv_img_set_angle(ui->screen_up_arr, 0);

	//Write codes screen_dw_arr
	ui->screen_dw_arr = lv_img_create(ui->screen_contscr_1);
	lv_obj_set_pos(ui->screen_dw_arr, 80, 68);
	lv_obj_set_size(ui->screen_dw_arr, 14, 9);

	//Write style state: LV_STATE_DEFAULT for style_screen_dw_arr_main_main_default
	static lv_style_t style_screen_dw_arr_main_main_default;
	lv_style_reset(&style_screen_dw_arr_main_main_default);
	lv_style_set_img_recolor(&style_screen_dw_arr_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_dw_arr_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_dw_arr_main_main_default, 255);
	lv_obj_add_style(ui->screen_dw_arr, &style_screen_dw_arr_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->screen_dw_arr, LV_OBJ_FLAG_CLICKABLE);
	//lv_img_set_src(ui->screen_dw_arr,&_DowAre_12x7);
	lv_img_set_src(ui->screen_trip_down_arrow,&new_trip_down_arrow);
	lv_img_set_pivot(ui->screen_dw_arr, 0,0);
	lv_img_set_angle(ui->screen_dw_arr, 0);

	//Write codes screen_contSp_Main_2
	ui->screen_contSp_Main_2 = lv_obj_create(ui->screen);
	lv_obj_set_pos(ui->screen_contSp_Main_2, 56, 120);
	lv_obj_set_size(ui->screen_contSp_Main_2, 136, 123);

	//Write style state: LV_STATE_DEFAULT for style_screen_contsp_main_2_main_main_default
	static lv_style_t style_screen_contsp_main_2_main_main_default;
	lv_style_reset(&style_screen_contsp_main_2_main_main_default);
	lv_style_set_radius(&style_screen_contsp_main_2_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_contsp_main_2_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_color(&style_screen_contsp_main_2_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_dir(&style_screen_contsp_main_2_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_contsp_main_2_main_main_default, 255);
	lv_style_set_border_color(&style_screen_contsp_main_2_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_border_width(&style_screen_contsp_main_2_main_main_default, 0);
	lv_style_set_border_opa(&style_screen_contsp_main_2_main_main_default, 0);
	lv_style_set_pad_left(&style_screen_contsp_main_2_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_contsp_main_2_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_contsp_main_2_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_contsp_main_2_main_main_default, 0);
	lv_obj_add_style(ui->screen_contSp_Main_2, &style_screen_contsp_main_2_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_con_odo_val
	ui->screen_con_odo_val = lv_label_create(ui->screen_contSp_Main_2);
	lv_obj_set_pos(ui->screen_con_odo_val, 38, 99);
	lv_obj_set_size(ui->screen_con_odo_val, 69, 19);
	lv_label_set_text(ui->screen_con_odo_val, "0");
	lv_label_set_long_mode(ui->screen_con_odo_val, LV_LABEL_LONG_WRAP);
	lv_obj_set_style_text_align(ui->screen_con_odo_val, LV_TEXT_ALIGN_RIGHT, 0);

	//Write style state: LV_STATE_DEFAULT for style_screen_con_odo_val_main_main_default
	static lv_style_t style_screen_con_odo_val_main_main_default;
	lv_style_reset(&style_screen_con_odo_val_main_main_default);
	lv_style_set_radius(&style_screen_con_odo_val_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_con_odo_val_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_color(&style_screen_con_odo_val_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_dir(&style_screen_con_odo_val_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_con_odo_val_main_main_default, 255);
	lv_style_set_text_color(&style_screen_con_odo_val_main_main_default, lv_color_make(0xff, 0x78, 0x00));
	lv_style_set_text_font(&style_screen_con_odo_val_main_main_default, &lv_font_FjallaOne_Regular_22);
	lv_style_set_text_letter_space(&style_screen_con_odo_val_main_main_default, 0);
	lv_style_set_pad_left(&style_screen_con_odo_val_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_con_odo_val_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_con_odo_val_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_con_odo_val_main_main_default, 0);
	lv_obj_add_style(ui->screen_con_odo_val, &style_screen_con_odo_val_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_Codo
	ui->screen_Codo = lv_img_create(ui->screen_contSp_Main_2);
	lv_obj_set_pos(ui->screen_Codo, 2, 103);
	lv_obj_set_size(ui->screen_Codo, 27, 14);

	//Write style state: LV_STATE_DEFAULT for style_screen_codo_main_main_default
	static lv_style_t style_screen_codo_main_main_default;
	lv_style_reset(&style_screen_codo_main_main_default);
	lv_style_set_img_recolor(&style_screen_codo_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_codo_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_codo_main_main_default, 255);
	lv_obj_add_style(ui->screen_Codo, &style_screen_codo_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->screen_Codo, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_Codo,&_txt_night_odo_27x14);
	lv_img_set_pivot(ui->screen_Codo, 0,0);
	lv_img_set_angle(ui->screen_Codo, 0);

	//Write codes screen_conkm
	ui->screen_conkm = lv_img_create(ui->screen_contSp_Main_2);
	lv_obj_set_pos(ui->screen_conkm, 110, 102);
	lv_obj_set_size(ui->screen_conkm, 20, 15);

	//Write style state: LV_STATE_DEFAULT for style_screen_conkm_main_main_default
	static lv_style_t style_screen_conkm_main_main_default;
	lv_style_reset(&style_screen_conkm_main_main_default);
	lv_style_set_img_recolor(&style_screen_conkm_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_conkm_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_conkm_main_main_default, 255);
	lv_obj_add_style(ui->screen_conkm, &style_screen_conkm_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->screen_conkm, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_conkm,&txt_night_odo_unit);
	lv_img_set_pivot(ui->screen_conkm, 0,0);
	lv_img_set_angle(ui->screen_conkm, 0);

	//Write codes screen_SC_1
	ui->screen_SC_1 = lv_img_create(ui->screen_contSp_Main_2);
	lv_obj_set_pos(ui->screen_SC_1, 3, 5);
	lv_obj_set_size(ui->screen_SC_1, 41, 73);

	//Write style state: LV_STATE_DEFAULT for style_screen_sc_1_main_main_default
	static lv_style_t style_screen_sc_1_main_main_default;
	lv_style_reset(&style_screen_sc_1_main_main_default);
	lv_style_set_img_recolor(&style_screen_sc_1_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_sc_1_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_sc_1_main_main_default, 0);
	lv_obj_add_style(ui->screen_SC_1, &style_screen_sc_1_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->screen_SC_1, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_SC_1,&txt_night_speed_line_3_grey0);
	lv_img_set_pivot(ui->screen_SC_1, 0,0);
	lv_img_set_angle(ui->screen_SC_1, 0);

	//Write codes screen_SC_2
	ui->screen_SC_2 = lv_img_create(ui->screen_contSp_Main_2);
	lv_obj_set_pos(ui->screen_SC_2, 44, 5);
	lv_obj_set_size(ui->screen_SC_2, 41, 73);

	//Write style state: LV_STATE_DEFAULT for style_screen_sc_2_main_main_default
	static lv_style_t style_screen_sc_2_main_main_default;
	lv_style_reset(&style_screen_sc_2_main_main_default);
	lv_style_set_img_recolor(&style_screen_sc_2_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_sc_2_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_sc_2_main_main_default, 0);
	lv_obj_add_style(ui->screen_SC_2, &style_screen_sc_2_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->screen_SC_2, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_SC_2,&txt_night_speed_line_3_grey0);
	lv_img_set_pivot(ui->screen_SC_2, 0,0);
	lv_img_set_angle(ui->screen_SC_2, 0);

	//Write codes screen_SC_3
	ui->screen_SC_3 = lv_img_create(ui->screen_contSp_Main_2);
	lv_obj_set_pos(ui->screen_SC_3, 86, 5);
	lv_obj_set_size(ui->screen_SC_3, 41, 73);

	//Write style state: LV_STATE_DEFAULT for style_screen_sc_3_main_main_default
	static lv_style_t style_screen_sc_3_main_main_default;
	lv_style_reset(&style_screen_sc_3_main_main_default);
	lv_style_set_img_recolor(&style_screen_sc_3_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_sc_3_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_sc_3_main_main_default, 0);
	lv_obj_add_style(ui->screen_SC_3, &style_screen_sc_3_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->screen_SC_3, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_SC_3,&txt_night_speed_line_3_white0);
	lv_img_set_pivot(ui->screen_SC_3, 0,0);
	lv_img_set_angle(ui->screen_SC_3, 0);

	//Write codes screen_trip_spedo_cont
	ui->screen_trip_spedo_cont = lv_obj_create(ui->screen);
	lv_obj_set_pos(ui->screen_trip_spedo_cont, 57, 97);
	lv_obj_set_size(ui->screen_trip_spedo_cont, 160, 67);

	//Write style state: LV_STATE_DEFAULT for style_screen_trip_spedo_cont_main_main_default
	static lv_style_t style_screen_trip_spedo_cont_main_main_default;
	lv_style_reset(&style_screen_trip_spedo_cont_main_main_default);
	lv_style_set_radius(&style_screen_trip_spedo_cont_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_trip_spedo_cont_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_color(&style_screen_trip_spedo_cont_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_dir(&style_screen_trip_spedo_cont_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_trip_spedo_cont_main_main_default, 255);
	lv_style_set_border_color(&style_screen_trip_spedo_cont_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_border_width(&style_screen_trip_spedo_cont_main_main_default, 0);
	lv_style_set_border_opa(&style_screen_trip_spedo_cont_main_main_default, 255);
	lv_style_set_pad_left(&style_screen_trip_spedo_cont_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_trip_spedo_cont_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_trip_spedo_cont_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_trip_spedo_cont_main_main_default, 0);
	lv_obj_add_style(ui->screen_trip_spedo_cont, &style_screen_trip_spedo_cont_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_trip_km_unit_Img
	ui->screen_trip_km_unit_Img = lv_img_create(ui->screen_trip_spedo_cont);
	lv_obj_set_pos(ui->screen_trip_km_unit_Img, 108, 33);
	lv_obj_set_size(ui->screen_trip_km_unit_Img, 27, 16);

	//Write style state: LV_STATE_DEFAULT for style_screen_trip_km_unit_img_main_main_default
	static lv_style_t style_screen_trip_km_unit_img_main_main_default;
	lv_style_reset(&style_screen_trip_km_unit_img_main_main_default);
	lv_style_set_img_recolor(&style_screen_trip_km_unit_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_trip_km_unit_img_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_trip_km_unit_img_main_main_default, 255);
	lv_obj_add_style(ui->screen_trip_km_unit_Img, &style_screen_trip_km_unit_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_img_set_src(ui->screen_trip_km_unit_Img,&km_text_unit_night_Img);

	//Write codes screen_SPD_Int_3
	ui->screen_SPD_Int_3 = lv_img_create(ui->screen_trip_spedo_cont);
	lv_obj_set_pos(ui->screen_SPD_Int_3, 76, -1);
	lv_obj_set_size(ui->screen_SPD_Int_3, 24, 47);

	//Write style state: LV_STATE_DEFAULT for style_screen_spd_int_3_main_main_default
	static lv_style_t style_screen_spd_int_3_main_main_default;
	lv_style_reset(&style_screen_spd_int_3_main_main_default);
	lv_style_set_img_recolor(&style_screen_spd_int_3_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_spd_int_3_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_spd_int_3_main_main_default, 0);
	lv_obj_add_style(ui->screen_SPD_Int_3, &style_screen_spd_int_3_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->screen_SPD_Int_3, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_SPD_Int_3,&_ISP3_24x47);
	lv_img_set_pivot(ui->screen_SPD_Int_3, 0,0);
	lv_img_set_angle(ui->screen_SPD_Int_3, 0);

	//Write codes screen_SPD_Int_2
	ui->screen_SPD_Int_2 = lv_img_create(ui->screen_trip_spedo_cont);
	lv_obj_set_pos(ui->screen_SPD_Int_2, 76, -1);
	lv_obj_set_size(ui->screen_SPD_Int_2, 24, 47);

	//Write style state: LV_STATE_DEFAULT for style_screen_spd_int_2_main_main_default
	static lv_style_t style_screen_spd_int_2_main_main_default;
	lv_style_reset(&style_screen_spd_int_2_main_main_default);
	lv_style_set_img_recolor(&style_screen_spd_int_2_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_spd_int_2_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_spd_int_2_main_main_default, 0);
	lv_obj_add_style(ui->screen_SPD_Int_2, &style_screen_spd_int_2_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->screen_SPD_Int_2, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_SPD_Int_2,&_ISP2_24x47);
	lv_img_set_pivot(ui->screen_SPD_Int_2, 0,0);
	lv_img_set_angle(ui->screen_SPD_Int_2, 0);

	//Write codes screen_SPD_Int_1
	ui->screen_SPD_Int_1 = lv_img_create(ui->screen_trip_spedo_cont);
	lv_obj_set_pos(ui->screen_SPD_Int_1, 76, -1);
	lv_obj_set_size(ui->screen_SPD_Int_1, 24, 47);

	//Write style state: LV_STATE_DEFAULT for style_screen_spd_int_1_main_main_default
	static lv_style_t style_screen_spd_int_1_main_main_default;
	lv_style_reset(&style_screen_spd_int_1_main_main_default);
	lv_style_set_img_recolor(&style_screen_spd_int_1_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_spd_int_1_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_spd_int_1_main_main_default, 0);
	lv_obj_add_style(ui->screen_SPD_Int_1, &style_screen_spd_int_1_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->screen_SPD_Int_1, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_SPD_Int_1,&_ISP1_24x47);
	lv_img_set_pivot(ui->screen_SPD_Int_1, 0,0);
	lv_img_set_angle(ui->screen_SPD_Int_1, 0);

	//Write codes screen_SPD_Int_0
	ui->screen_SPD_Int_0 = lv_img_create(ui->screen_trip_spedo_cont);
	lv_obj_set_pos(ui->screen_SPD_Int_0, 76, -1);
	lv_obj_set_size(ui->screen_SPD_Int_0, 24, 47);

	//Write style state: LV_STATE_DEFAULT for style_screen_spd_int_0_main_main_default
	static lv_style_t style_screen_spd_int_0_main_main_default;
	lv_style_reset(&style_screen_spd_int_0_main_main_default);
	lv_style_set_img_recolor(&style_screen_spd_int_0_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_spd_int_0_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_spd_int_0_main_main_default, 0);
	lv_obj_add_style(ui->screen_SPD_Int_0, &style_screen_spd_int_0_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->screen_SPD_Int_0, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_SPD_Int_0,&_ISP0_24x47);
	lv_img_set_pivot(ui->screen_SPD_Int_0, 0,0);
	lv_img_set_angle(ui->screen_SPD_Int_0, 0);

	//Write codes screen_trip_spedo_unit
	ui->screen_trip_spedo_unit = lv_label_create(ui->screen_trip_spedo_cont);
	lv_obj_set_pos(ui->screen_trip_spedo_unit, 104, 34);
	lv_obj_set_size(ui->screen_trip_spedo_unit, 28, 10);
	lv_label_set_text(ui->screen_trip_spedo_unit, "km/h");
	lv_label_set_long_mode(ui->screen_trip_spedo_unit, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->screen_trip_spedo_unit, LV_TEXT_ALIGN_LEFT, 0);

	//Write style state: LV_STATE_DEFAULT for style_screen_trip_spedo_unit_main_main_default
	static lv_style_t style_screen_trip_spedo_unit_main_main_default;
	lv_style_reset(&style_screen_trip_spedo_unit_main_main_default);
	lv_style_set_radius(&style_screen_trip_spedo_unit_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_trip_spedo_unit_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_trip_spedo_unit_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_trip_spedo_unit_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_trip_spedo_unit_main_main_default, 0);
	lv_style_set_text_color(&style_screen_trip_spedo_unit_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_screen_trip_spedo_unit_main_main_default, &lv_font_FjallaOne_Regular_11);
	lv_style_set_text_letter_space(&style_screen_trip_spedo_unit_main_main_default, 0);
	lv_style_set_pad_left(&style_screen_trip_spedo_unit_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_trip_spedo_unit_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_trip_spedo_unit_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_trip_spedo_unit_main_main_default, 0);
	lv_obj_add_style(ui->screen_trip_spedo_unit, &style_screen_trip_spedo_unit_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->screen_trip_spedo_unit,LV_OBJ_FLAG_HIDDEN);

	//Write codes screen_trip_spedo_line
	ui->screen_trip_spedo_line = lv_img_create(ui->screen_trip_spedo_cont);
	lv_obj_set_pos(ui->screen_trip_spedo_line, 0, 63);
	lv_obj_set_size(ui->screen_trip_spedo_line, 134, 2);

	//Write style state: LV_STATE_DEFAULT for style_screen_trip_spedo_line_main_main_default
	static lv_style_t style_screen_trip_spedo_line_main_main_default;
	lv_style_reset(&style_screen_trip_spedo_line_main_main_default);
	lv_style_set_img_recolor(&style_screen_trip_spedo_line_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_trip_spedo_line_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_trip_spedo_line_main_main_default, 255);
	lv_obj_add_style(ui->screen_trip_spedo_line, &style_screen_trip_spedo_line_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->screen_trip_spedo_line, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_trip_spedo_line,&_img_center_divider_line_134x2);
	lv_img_set_pivot(ui->screen_trip_spedo_line, 0,0);
	lv_img_set_angle(ui->screen_trip_spedo_line, 0);

	//Write codes screen_trip_spedo_s1
	ui->screen_trip_spedo_s1 = lv_img_create(ui->screen_trip_spedo_cont);
	lv_obj_set_pos(ui->screen_trip_spedo_s1, 76, 2);
	lv_obj_set_size(ui->screen_trip_spedo_s1, 24, 47);

	//Write style state: LV_STATE_DEFAULT for style_screen_trip_spedo_s1_main_main_default
	static lv_style_t style_screen_trip_spedo_s1_main_main_default;
	lv_style_reset(&style_screen_trip_spedo_s1_main_main_default);
	lv_style_set_img_recolor(&style_screen_trip_spedo_s1_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_trip_spedo_s1_main_main_default, 176);
	lv_style_set_img_opa(&style_screen_trip_spedo_s1_main_main_default, 255);
	lv_obj_add_style(ui->screen_trip_spedo_s1, &style_screen_trip_spedo_s1_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->screen_trip_spedo_s1, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_trip_spedo_s1,&_ISP0_24x47);
	lv_img_set_pivot(ui->screen_trip_spedo_s1, 0,0);
	lv_img_set_angle(ui->screen_trip_spedo_s1, 0);
	lv_obj_set_style_img_opa(ui->screen_trip_spedo_s1,255, 0);
	lv_obj_set_style_img_recolor(ui->screen_trip_spedo_s1, lv_color_white(), 0);

	//Write codes screen_trip_spedo_s2
	ui->screen_trip_spedo_s2 = lv_img_create(ui->screen_trip_spedo_cont);
	lv_obj_set_pos(ui->screen_trip_spedo_s2, 46, 2);
	lv_obj_set_size(ui->screen_trip_spedo_s2, 24, 47);

	//Write style state: LV_STATE_DEFAULT for style_screen_trip_spedo_s2_main_main_default
	static lv_style_t style_screen_trip_spedo_s2_main_main_default;
	lv_style_reset(&style_screen_trip_spedo_s2_main_main_default);
	lv_style_set_img_recolor(&style_screen_trip_spedo_s2_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_trip_spedo_s2_main_main_default, 176);
	lv_style_set_img_opa(&style_screen_trip_spedo_s2_main_main_default, 255);
	lv_obj_add_style(ui->screen_trip_spedo_s2, &style_screen_trip_spedo_s2_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->screen_trip_spedo_s2, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_trip_spedo_s2,&_ISP0_24x47);
	lv_img_set_pivot(ui->screen_trip_spedo_s2, 0,0);
	lv_img_set_angle(ui->screen_trip_spedo_s2, 0);
	lv_obj_set_style_img_opa(ui->screen_trip_spedo_s2,255, 0);
	lv_obj_set_style_img_recolor(ui->screen_trip_spedo_s2, lv_color_Intermediate_Grey(), 0);
	set_obj_opa(ui->screen_trip_spedo_s2,50);

	//Write codes screen_trip_spedo_s3
	ui->screen_trip_spedo_s3 = lv_img_create(ui->screen_trip_spedo_cont);
	lv_obj_set_pos(ui->screen_trip_spedo_s3, 17, 2);
	lv_obj_set_size(ui->screen_trip_spedo_s3, 24, 47);

	//Write style state: LV_STATE_DEFAULT for style_screen_trip_spedo_s3_main_main_default
	static lv_style_t style_screen_trip_spedo_s3_main_main_default;
	lv_style_reset(&style_screen_trip_spedo_s3_main_main_default);
	lv_style_set_img_recolor(&style_screen_trip_spedo_s3_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_trip_spedo_s3_main_main_default, 176);
	lv_style_set_img_opa(&style_screen_trip_spedo_s3_main_main_default, 255);
	lv_obj_add_style(ui->screen_trip_spedo_s3, &style_screen_trip_spedo_s3_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->screen_trip_spedo_s3, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_trip_spedo_s3,&_ISP0_24x47);
	lv_img_set_pivot(ui->screen_trip_spedo_s3, 0,0);
	lv_img_set_angle(ui->screen_trip_spedo_s3, 0);
	lv_obj_set_style_img_opa(ui->screen_trip_spedo_s3,255, 0);
	lv_obj_set_style_img_recolor(ui->screen_trip_spedo_s3, lv_color_Intermediate_Grey(), 0);
	set_obj_opa(ui->screen_trip_spedo_s3,50);

	//Write codes screen_navi_container
	ui->screen_navi_container = lv_obj_create(ui->screen);
	lv_obj_set_pos(ui->screen_navi_container, 30, 167);
	lv_obj_set_size(ui->screen_navi_container, 195, 95);

	//Write style state: LV_STATE_DEFAULT for style_screen_navi_container_main_main_default
	static lv_style_t style_screen_navi_container_main_main_default;
	lv_style_reset(&style_screen_navi_container_main_main_default);
	lv_style_set_radius(&style_screen_navi_container_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_navi_container_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_color(&style_screen_navi_container_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_dir(&style_screen_navi_container_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_navi_container_main_main_default, 0);
	lv_style_set_border_color(&style_screen_navi_container_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_border_width(&style_screen_navi_container_main_main_default, 0);
	lv_style_set_border_opa(&style_screen_navi_container_main_main_default, 255);
	lv_style_set_pad_left(&style_screen_navi_container_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_navi_container_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_navi_container_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_navi_container_main_main_default, 0);
	lv_obj_add_style(ui->screen_navi_container, &style_screen_navi_container_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_No_Sig_Nyt
	ui->screen_No_Sig_Nyt = lv_img_create(ui->screen_navi_container);
	lv_obj_set_pos(ui->screen_No_Sig_Nyt, 67, 54);
	lv_obj_set_size(ui->screen_No_Sig_Nyt, 46, 16);

	//Write style state: LV_STATE_DEFAULT for style_screen_no_sig_nyt_main_main_default
	static lv_style_t style_screen_no_sig_nyt_main_main_default;
	lv_style_reset(&style_screen_no_sig_nyt_main_main_default);
	lv_style_set_img_recolor(&style_screen_no_sig_nyt_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_no_sig_nyt_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_no_sig_nyt_main_main_default, 255);
	lv_obj_add_style(ui->screen_No_Sig_Nyt, &style_screen_no_sig_nyt_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_navi_val
	ui->screen_navi_val = lv_label_create(ui->screen_navi_container);
	lv_obj_set_pos(ui->screen_navi_val, 20, 8);
	lv_obj_set_size(ui->screen_navi_val, 30, 17);
	lv_label_set_text(ui->screen_navi_val, "9999");
	lv_label_set_long_mode(ui->screen_navi_val, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->screen_navi_val, LV_TEXT_ALIGN_RIGHT, 0);

	//Write style state: LV_STATE_DEFAULT for style_screen_navi_val_main_main_default
	static lv_style_t style_screen_navi_val_main_main_default;
	lv_style_reset(&style_screen_navi_val_main_main_default);
	lv_style_set_radius(&style_screen_navi_val_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_navi_val_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_navi_val_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_navi_val_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_navi_val_main_main_default, 0);
	lv_style_set_text_color(&style_screen_navi_val_main_main_default, lv_color_make(0xff, 0x78, 0x00));
	lv_style_set_text_font(&style_screen_navi_val_main_main_default, &lv_font_FjallaOne_Regular_22);
	lv_style_set_text_letter_space(&style_screen_navi_val_main_main_default, 0);
	lv_style_set_pad_left(&style_screen_navi_val_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_navi_val_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_navi_val_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_navi_val_main_main_default, 0);
	lv_obj_add_style(ui->screen_navi_val, &style_screen_navi_val_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_navi_unit
	ui->screen_navi_unit = lv_label_create(ui->screen_navi_container);
	lv_obj_set_pos(ui->screen_navi_unit, 30, 35);
	lv_obj_set_size(ui->screen_navi_unit, 26, 11);
	lv_label_set_text(ui->screen_navi_unit, "km");
	lv_label_set_long_mode(ui->screen_navi_unit, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->screen_navi_unit, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_screen_navi_unit_main_main_default
	static lv_style_t style_screen_navi_unit_main_main_default;
	lv_style_reset(&style_screen_navi_unit_main_main_default);
	lv_style_set_radius(&style_screen_navi_unit_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_navi_unit_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_navi_unit_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_navi_unit_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_navi_unit_main_main_default, 0);
	lv_style_set_text_color(&style_screen_navi_unit_main_main_default, lv_color_make(0xff, 0x78, 0x00));
	lv_style_set_text_font(&style_screen_navi_unit_main_main_default, &lv_font_FjallaOne_Regular_14);
	lv_style_set_text_letter_space(&style_screen_navi_unit_main_main_default, 0);
	lv_style_set_pad_left(&style_screen_navi_unit_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_navi_unit_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_navi_unit_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_navi_unit_main_main_default, 0);
	lv_obj_add_style(ui->screen_navi_unit, &style_screen_navi_unit_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_nav_est
	ui->screen_nav_est = lv_label_create(ui->screen_navi_container);
	lv_obj_set_pos(ui->screen_nav_est, 143, 35);
	lv_obj_set_size(ui->screen_nav_est, 26, 14);
	lv_label_set_text(ui->screen_nav_est, "ETA");
	lv_label_set_long_mode(ui->screen_nav_est, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->screen_nav_est, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_screen_nav_est_main_main_default
	static lv_style_t style_screen_nav_est_main_main_default;
	lv_style_reset(&style_screen_nav_est_main_main_default);
	lv_style_set_radius(&style_screen_nav_est_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_nav_est_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_nav_est_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_nav_est_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_nav_est_main_main_default, 0);
	lv_style_set_text_color(&style_screen_nav_est_main_main_default, lv_color_make(0x98, 0x98, 0x98));
	lv_style_set_text_font(&style_screen_nav_est_main_main_default, &lv_font_FjallaOne_Regular_17);
	lv_style_set_text_letter_space(&style_screen_nav_est_main_main_default, 0);
	lv_style_set_pad_left(&style_screen_nav_est_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_nav_est_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_nav_est_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_nav_est_main_main_default, 0);
	lv_obj_add_style(ui->screen_nav_est, &style_screen_nav_est_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_nav_clo_hr
	ui->screen_nav_clo_hr = lv_label_create(ui->screen_navi_container);
	lv_obj_set_pos(ui->screen_nav_clo_hr, 130, 8);
	lv_obj_set_size(ui->screen_nav_clo_hr, 18, 15);
	lv_label_set_text(ui->screen_nav_clo_hr, "99");
	lv_label_set_long_mode(ui->screen_nav_clo_hr, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->screen_nav_clo_hr, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_screen_nav_clo_hr_main_main_default
	static lv_style_t style_screen_nav_clo_hr_main_main_default;
	lv_style_reset(&style_screen_nav_clo_hr_main_main_default);
	lv_style_set_radius(&style_screen_nav_clo_hr_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_nav_clo_hr_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_nav_clo_hr_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_nav_clo_hr_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_nav_clo_hr_main_main_default, 0);
	lv_style_set_text_color(&style_screen_nav_clo_hr_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_screen_nav_clo_hr_main_main_default, &lv_font_FjallaOne_Regular_17);
	lv_style_set_text_letter_space(&style_screen_nav_clo_hr_main_main_default, 0);
	lv_style_set_pad_left(&style_screen_nav_clo_hr_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_nav_clo_hr_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_nav_clo_hr_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_nav_clo_hr_main_main_default, 0);
	lv_obj_add_style(ui->screen_nav_clo_hr, &style_screen_nav_clo_hr_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_nav_clo_colon
	ui->screen_nav_clo_colon = lv_label_create(ui->screen_navi_container);
	lv_obj_set_pos(ui->screen_nav_clo_colon, 148, 8);
	lv_obj_set_size(ui->screen_nav_clo_colon, 4, 13);
	lv_label_set_text(ui->screen_nav_clo_colon, ":");
	lv_label_set_long_mode(ui->screen_nav_clo_colon, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->screen_nav_clo_colon, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_screen_nav_clo_colon_main_main_default
	static lv_style_t style_screen_nav_clo_colon_main_main_default;
	lv_style_reset(&style_screen_nav_clo_colon_main_main_default);
	lv_style_set_radius(&style_screen_nav_clo_colon_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_nav_clo_colon_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_nav_clo_colon_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_nav_clo_colon_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_nav_clo_colon_main_main_default, 0);
	lv_style_set_text_color(&style_screen_nav_clo_colon_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_screen_nav_clo_colon_main_main_default, &lv_font_FjallaOne_Regular_17);
	lv_style_set_text_letter_space(&style_screen_nav_clo_colon_main_main_default, 0);
	lv_style_set_pad_left(&style_screen_nav_clo_colon_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_nav_clo_colon_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_nav_clo_colon_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_nav_clo_colon_main_main_default, 0);
	lv_obj_add_style(ui->screen_nav_clo_colon, &style_screen_nav_clo_colon_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_nav_clo_min
	ui->screen_nav_clo_min = lv_label_create(ui->screen_navi_container);
	lv_obj_set_pos(ui->screen_nav_clo_min, 153, 8);
	lv_obj_set_size(ui->screen_nav_clo_min, 17, 15);
	lv_label_set_text(ui->screen_nav_clo_min, "99");
	lv_label_set_long_mode(ui->screen_nav_clo_min, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->screen_nav_clo_min, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_screen_nav_clo_min_main_main_default
	static lv_style_t style_screen_nav_clo_min_main_main_default;
	lv_style_reset(&style_screen_nav_clo_min_main_main_default);
	lv_style_set_radius(&style_screen_nav_clo_min_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_nav_clo_min_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_nav_clo_min_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_nav_clo_min_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_nav_clo_min_main_main_default, 0);
	lv_style_set_text_color(&style_screen_nav_clo_min_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_screen_nav_clo_min_main_main_default, &lv_font_FjallaOne_Regular_17);
	lv_style_set_text_letter_space(&style_screen_nav_clo_min_main_main_default, 0);
	lv_style_set_pad_left(&style_screen_nav_clo_min_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_nav_clo_min_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_nav_clo_min_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_nav_clo_min_main_main_default, 0);
	lv_obj_add_style(ui->screen_nav_clo_min, &style_screen_nav_clo_min_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_nav_clo_am
	ui->screen_nav_clo_am = lv_label_create(ui->screen_navi_container);
	lv_obj_set_pos(ui->screen_nav_clo_am, 174, 8);
	lv_obj_set_size(ui->screen_nav_clo_am, 19, 15);
	lv_label_set_text(ui->screen_nav_clo_am, "AM");
	lv_label_set_long_mode(ui->screen_nav_clo_am, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->screen_nav_clo_am, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_screen_nav_clo_am_main_main_default
	static lv_style_t style_screen_nav_clo_am_main_main_default;
	lv_style_reset(&style_screen_nav_clo_am_main_main_default);
	lv_style_set_radius(&style_screen_nav_clo_am_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_nav_clo_am_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_nav_clo_am_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_nav_clo_am_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_nav_clo_am_main_main_default, 0);
	lv_style_set_text_color(&style_screen_nav_clo_am_main_main_default, lv_color_make(0x98, 0x98, 0x98));
	lv_style_set_text_font(&style_screen_nav_clo_am_main_main_default, &lv_font_FjallaOne_Regular_17);
	lv_style_set_text_letter_space(&style_screen_nav_clo_am_main_main_default, 0);
	lv_style_set_pad_left(&style_screen_nav_clo_am_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_nav_clo_am_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_nav_clo_am_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_nav_clo_am_main_main_default, 0);
	lv_obj_add_style(ui->screen_nav_clo_am, &style_screen_nav_clo_am_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_nav_img
	ui->screen_nav_img = lv_img_create(ui->screen_navi_container);
	lv_obj_set_pos(ui->screen_nav_img, 55, 5);
	lv_obj_set_size(ui->screen_nav_img, 70, 70);

	//Write style state: LV_STATE_DEFAULT for style_screen_nav_img_main_main_default
	static lv_style_t style_screen_nav_img_main_main_default;
	lv_style_reset(&style_screen_nav_img_main_main_default);
	lv_style_set_img_recolor(&style_screen_nav_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_nav_img_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_nav_img_main_main_default, 255);
	lv_obj_add_style(ui->screen_nav_img, &style_screen_nav_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_navi_lbl
	ui->screen_navi_lbl = lv_label_create(ui->screen_navi_container);
	lv_obj_set_pos(ui->screen_navi_lbl, 5, 6);
	lv_obj_set_size(ui->screen_navi_lbl, 100, 10);
	lv_label_set_text(ui->screen_navi_lbl, "No SIGNAL");
	lv_label_set_long_mode(ui->screen_navi_lbl, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->screen_navi_lbl, LV_TEXT_ALIGN_CENTER, 0);

	//Write codes screen_Hidden_White
	ui->screen_Hidden_White = lv_img_create(ui->screen);
	lv_obj_set_pos(ui->screen_Hidden_White, 143, 122);
	lv_obj_set_size(ui->screen_Hidden_White, 34, 69);

	//Write style state: LV_STATE_DEFAULT for style_screen_hidden_white_main_main_default
	static lv_style_t style_screen_hidden_white_main_main_default;
	lv_style_reset(&style_screen_hidden_white_main_main_default);
	lv_style_set_img_recolor(&style_screen_hidden_white_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_hidden_white_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_hidden_white_main_main_default, 0);
	lv_obj_add_style(ui->screen_Hidden_White, &style_screen_hidden_white_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->screen_Hidden_White, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_Hidden_White,&_txt_night_speed_line_3_white_34x69);
	lv_img_set_pivot(ui->screen_Hidden_White, 0,0);
	lv_img_set_angle(ui->screen_Hidden_White, 0);

	//Write codes screen_Sub_Con
	ui->screen_Sub_Con = lv_img_create(ui->screen);
	lv_obj_set_pos(ui->screen_Sub_Con, 198, 147);
	lv_obj_set_size(ui->screen_Sub_Con, 24, 24);

	//Write style state: LV_STATE_DEFAULT for style_screen_sub_con_main_main_default
	static lv_style_t style_screen_sub_con_main_main_default;
	lv_style_reset(&style_screen_sub_con_main_main_default);
	lv_style_set_img_recolor(&style_screen_sub_con_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_sub_con_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_sub_con_main_main_default, 255);
	lv_obj_add_style(ui->screen_Sub_Con, &style_screen_sub_con_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->screen_Sub_Con, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_Sub_Con,&subbtn_night_24x24);
	lv_img_set_pivot(ui->screen_Sub_Con, 0,0);
	lv_img_set_angle(ui->screen_Sub_Con, 0);

		//Write codes screen_bl_pass_container
	ui->screen_bl_pass_container = lv_obj_create(ui->screen);
	lv_obj_set_pos(ui->screen_bl_pass_container, 30, 167);
	lv_obj_set_size(ui->screen_bl_pass_container, 195, 78);

	//Write style state: LV_STATE_DEFAULT for style_screen_bl_pass_container_main_main_default
	static lv_style_t style_screen_bl_pass_container_main_main_default;
	lv_style_reset(&style_screen_bl_pass_container_main_main_default);
	lv_style_set_radius(&style_screen_bl_pass_container_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_bl_pass_container_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_color(&style_screen_bl_pass_container_main_main_default, lv_color_make(0x08, 0x08, 0x08));
	lv_style_set_bg_grad_dir(&style_screen_bl_pass_container_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_bl_pass_container_main_main_default, 0);
	lv_style_set_border_color(&style_screen_bl_pass_container_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_border_width(&style_screen_bl_pass_container_main_main_default, 0);
	lv_style_set_border_opa(&style_screen_bl_pass_container_main_main_default, 0);
	lv_style_set_pad_left(&style_screen_bl_pass_container_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_bl_pass_container_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_bl_pass_container_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_bl_pass_container_main_main_default, 0);
	lv_obj_add_style(ui->screen_bl_pass_container, &style_screen_bl_pass_container_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_pass_label
	ui->screen_pass_label = lv_label_create(ui->screen_bl_pass_container);
	lv_obj_set_pos(ui->screen_pass_label, 46, 9);
	lv_obj_set_size(ui->screen_pass_label, 98, 18);
	lv_label_set_text(ui->screen_pass_label, "Passcode");
	lv_label_set_long_mode(ui->screen_pass_label, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->screen_pass_label, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_screen_pass_label_main_main_default
	static lv_style_t style_screen_pass_label_main_main_default;
	lv_style_reset(&style_screen_pass_label_main_main_default);
	lv_style_set_radius(&style_screen_pass_label_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_pass_label_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_pass_label_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_pass_label_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_pass_label_main_main_default, 0);
	lv_style_set_text_color(&style_screen_pass_label_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_screen_pass_label_main_main_default, &lv_font_FjallaOne_Regular_22);
	lv_style_set_text_letter_space(&style_screen_pass_label_main_main_default, 0);
	lv_style_set_pad_left(&style_screen_pass_label_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_pass_label_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_pass_label_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_pass_label_main_main_default, 0);
	lv_obj_add_style(ui->screen_pass_label, &style_screen_pass_label_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_pass_unit
	ui->screen_pass_unit = lv_label_create(ui->screen_bl_pass_container);
	lv_obj_set_pos(ui->screen_pass_unit, 68, 35);
	lv_obj_set_size(ui->screen_pass_unit, 51, 16);
	lv_label_set_text(ui->screen_pass_unit, "123456");
	lv_label_set_long_mode(ui->screen_pass_unit, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->screen_pass_unit, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_screen_pass_unit_main_main_default
	static lv_style_t style_screen_pass_unit_main_main_default;
	lv_style_reset(&style_screen_pass_unit_main_main_default);
	lv_style_set_radius(&style_screen_pass_unit_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_pass_unit_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_pass_unit_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_pass_unit_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_pass_unit_main_main_default, 0);
	lv_style_set_text_color(&style_screen_pass_unit_main_main_default, lv_color_make(0x98, 0x98, 0x98));
	lv_style_set_text_font(&style_screen_pass_unit_main_main_default, &lv_font_FjallaOne_Regular_16);
	lv_style_set_text_letter_space(&style_screen_pass_unit_main_main_default, 0);
	lv_style_set_pad_left(&style_screen_pass_unit_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_pass_unit_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_pass_unit_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_pass_unit_main_main_default, 0);
	lv_obj_add_style(ui->screen_pass_unit, &style_screen_pass_unit_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_pass_larrow
	ui->screen_pass_larrow = lv_label_create(ui->screen_bl_pass_container);
	lv_obj_set_pos(ui->screen_pass_larrow, 60, 38);
	lv_obj_set_size(ui->screen_pass_larrow, 7, 9);
	lv_label_set_text(ui->screen_pass_larrow, "<");
	lv_label_set_long_mode(ui->screen_pass_larrow, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->screen_pass_larrow, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_screen_pass_larrow_main_main_default
	static lv_style_t style_screen_pass_larrow_main_main_default;
	lv_style_reset(&style_screen_pass_larrow_main_main_default);
	lv_style_set_radius(&style_screen_pass_larrow_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_pass_larrow_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_pass_larrow_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_pass_larrow_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_pass_larrow_main_main_default, 0);
	lv_style_set_text_color(&style_screen_pass_larrow_main_main_default, lv_color_make(0x98, 0x98, 0x98));
	lv_style_set_text_font(&style_screen_pass_larrow_main_main_default, &lv_font_FjallaOne_Regular_10);
	lv_style_set_text_letter_space(&style_screen_pass_larrow_main_main_default, 0);
	lv_style_set_pad_left(&style_screen_pass_larrow_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_pass_larrow_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_pass_larrow_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_pass_larrow_main_main_default, 0);
	lv_obj_add_style(ui->screen_pass_larrow, &style_screen_pass_larrow_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_pass_rarrow
	ui->screen_pass_rarrow = lv_label_create(ui->screen_bl_pass_container);
	lv_obj_set_pos(ui->screen_pass_rarrow, 121, 38);
	lv_obj_set_size(ui->screen_pass_rarrow, 7, 9);
	lv_label_set_text(ui->screen_pass_rarrow, ">");
	lv_label_set_long_mode(ui->screen_pass_rarrow, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->screen_pass_rarrow, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_screen_pass_rarrow_main_main_default
	static lv_style_t style_screen_pass_rarrow_main_main_default;
	lv_style_reset(&style_screen_pass_rarrow_main_main_default);
	lv_style_set_radius(&style_screen_pass_rarrow_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_pass_rarrow_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_pass_rarrow_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_pass_rarrow_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_pass_rarrow_main_main_default, 0);
	lv_style_set_text_color(&style_screen_pass_rarrow_main_main_default, lv_color_make(0x98, 0x98, 0x98));
	lv_style_set_text_font(&style_screen_pass_rarrow_main_main_default, &lv_font_FjallaOne_Regular_10);
	lv_style_set_text_letter_space(&style_screen_pass_rarrow_main_main_default, 0);
	lv_style_set_pad_left(&style_screen_pass_rarrow_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_pass_rarrow_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_pass_rarrow_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_pass_rarrow_main_main_default, 0);
	lv_obj_add_style(ui->screen_pass_rarrow, &style_screen_pass_rarrow_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_phone_container
	ui->screen_phone_container = lv_obj_create(ui->screen);
	lv_obj_set_pos(ui->screen_phone_container, 30, 167);
	lv_obj_set_size(ui->screen_phone_container, 197, 84);

	//Write style state: LV_STATE_DEFAULT for style_screen_phone_container_main_main_default
	static lv_style_t style_screen_phone_container_main_main_default;
	lv_style_reset(&style_screen_phone_container_main_main_default);
	lv_style_set_radius(&style_screen_phone_container_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_phone_container_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_color(&style_screen_phone_container_main_main_default, lv_color_make(0x08, 0x08, 0x08));
	lv_style_set_bg_grad_dir(&style_screen_phone_container_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_phone_container_main_main_default, 0);
	lv_style_set_border_color(&style_screen_phone_container_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_border_width(&style_screen_phone_container_main_main_default, 0);
	lv_style_set_border_opa(&style_screen_phone_container_main_main_default, 0);
	lv_style_set_pad_left(&style_screen_phone_container_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_phone_container_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_phone_container_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_phone_container_main_main_default, 0);
	lv_obj_add_style(ui->screen_phone_container, &style_screen_phone_container_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_phone_up_arrow
	ui->screen_phone_up_arrow = lv_img_create(ui->screen_phone_container);
	lv_obj_set_pos(ui->screen_phone_up_arrow, 84, 4);
	lv_obj_set_size(ui->screen_phone_up_arrow, 12, 7);

	//Write style state: LV_STATE_DEFAULT for style_screen_phone_up_arrow_main_main_default
	static lv_style_t style_screen_phone_up_arrow_main_main_default;
	lv_style_reset(&style_screen_phone_up_arrow_main_main_default);
	lv_style_set_img_recolor(&style_screen_phone_up_arrow_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_phone_up_arrow_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_phone_up_arrow_main_main_default, 255);
	lv_obj_add_style(ui->screen_phone_up_arrow, &style_screen_phone_up_arrow_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->screen_phone_up_arrow, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_phone_up_arrow,&_Setting_Up_Arrow_12x7);
	lv_img_set_pivot(ui->screen_phone_up_arrow, 0,0);
	lv_img_set_angle(ui->screen_phone_up_arrow, 0);

	//Write codes screen_phone_down_arrow
	ui->screen_phone_down_arrow = lv_img_create(ui->screen_phone_container);
	lv_obj_set_pos(ui->screen_phone_down_arrow, 84, 62);
	lv_obj_set_size(ui->screen_phone_down_arrow, 12, 7);

	//Write style state: LV_STATE_DEFAULT for style_screen_phone_down_arrow_main_main_default
	static lv_style_t style_screen_phone_down_arrow_main_main_default;
	lv_style_reset(&style_screen_phone_down_arrow_main_main_default);
	lv_style_set_img_recolor(&style_screen_phone_down_arrow_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_phone_down_arrow_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_phone_down_arrow_main_main_default, 255);
	lv_obj_add_style(ui->screen_phone_down_arrow, &style_screen_phone_down_arrow_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->screen_phone_down_arrow, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_phone_down_arrow,&_Setting_Drow_Arrow_12x7);
	lv_img_set_pivot(ui->screen_phone_down_arrow, 0,0);
	lv_img_set_angle(ui->screen_phone_down_arrow, 0);

	//Write codes screen_phone_lbl_1
	ui->screen_phone_lbl_1 = lv_label_create(ui->screen_phone_container);
	lv_obj_set_pos(ui->screen_phone_lbl_1, 8, 7);
	lv_obj_set_size(ui->screen_phone_lbl_1, 183, 20);
	lv_label_set_text(ui->screen_phone_lbl_1, "+91 XXXXXXXXXXX");
	lv_label_set_long_mode(ui->screen_phone_lbl_1, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->screen_phone_lbl_1, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_screen_phone_lbl_1_main_main_default
	static lv_style_t style_screen_phone_lbl_1_main_main_default;
	lv_style_reset(&style_screen_phone_lbl_1_main_main_default);
	lv_style_set_radius(&style_screen_phone_lbl_1_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_phone_lbl_1_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_phone_lbl_1_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_phone_lbl_1_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_phone_lbl_1_main_main_default, 0);
	lv_style_set_text_color(&style_screen_phone_lbl_1_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_screen_phone_lbl_1_main_main_default, &lv_font_FjallaOne_Regular_22);
	lv_style_set_text_letter_space(&style_screen_phone_lbl_1_main_main_default, 0);
	lv_style_set_pad_left(&style_screen_phone_lbl_1_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_phone_lbl_1_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_phone_lbl_1_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_phone_lbl_1_main_main_default, 0);
	lv_obj_add_style(ui->screen_phone_lbl_1, &style_screen_phone_lbl_1_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_phone_lbl_2
	ui->screen_phone_lbl_2 = lv_label_create(ui->screen_phone_container);
	lv_obj_set_pos(ui->screen_phone_lbl_2, 42, 20);
	lv_obj_set_size(ui->screen_phone_lbl_2, 100, 16);
	lv_label_set_text(ui->screen_phone_lbl_2, "");
	lv_label_set_long_mode(ui->screen_phone_lbl_2, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->screen_phone_lbl_2, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_screen_phone_lbl_2_main_main_default
	static lv_style_t style_screen_phone_lbl_2_main_main_default;
	lv_style_reset(&style_screen_phone_lbl_2_main_main_default);
	lv_style_set_radius(&style_screen_phone_lbl_2_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_phone_lbl_2_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_phone_lbl_2_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_phone_lbl_2_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_phone_lbl_2_main_main_default, 0);
	lv_style_set_text_color(&style_screen_phone_lbl_2_main_main_default, lv_color_make(0x41, 0x41, 0x41));
	lv_style_set_text_font(&style_screen_phone_lbl_2_main_main_default, &lv_font_FjallaOne_Regular_14);
	lv_style_set_text_letter_space(&style_screen_phone_lbl_2_main_main_default, 0);
	lv_style_set_pad_left(&style_screen_phone_lbl_2_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_phone_lbl_2_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_phone_lbl_2_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_phone_lbl_2_main_main_default, 0);
	lv_obj_add_style(ui->screen_phone_lbl_2, &style_screen_phone_lbl_2_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_phone_btn1
	ui->screen_phone_btn1 = lv_img_create(ui->screen_phone_container);
	lv_obj_set_pos(ui->screen_phone_btn1, 28, 49);
	lv_obj_set_size(ui->screen_phone_btn1, 30, 30);

	//Write style state: LV_STATE_DEFAULT for style_screen_phone_btn1_main_main_default
	static lv_style_t style_screen_phone_btn1_main_main_default;
	lv_style_reset(&style_screen_phone_btn1_main_main_default);
	lv_style_set_img_recolor(&style_screen_phone_btn1_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_phone_btn1_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_phone_btn1_main_main_default, 255);
	lv_obj_add_style(ui->screen_phone_btn1, &style_screen_phone_btn1_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->screen_phone_btn1, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_phone_btn1,&_img_night_call_declined_decline_30x30);
	lv_img_set_pivot(ui->screen_phone_btn1, 0,0);
	lv_img_set_angle(ui->screen_phone_btn1, 0);

	//Write codes screen_phone_btn2
	ui->screen_phone_btn2 = lv_img_create(ui->screen_phone_container);
	lv_obj_set_pos(ui->screen_phone_btn2, 75, 49);
	lv_obj_set_size(ui->screen_phone_btn2, 30, 30);

	//Write style state: LV_STATE_DEFAULT for style_screen_phone_btn2_main_main_default
	static lv_style_t style_screen_phone_btn2_main_main_default;
	lv_style_reset(&style_screen_phone_btn2_main_main_default);
	lv_style_set_img_recolor(&style_screen_phone_btn2_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_phone_btn2_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_phone_btn2_main_main_default, 255);
	lv_obj_add_style(ui->screen_phone_btn2, &style_screen_phone_btn2_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->screen_phone_btn2, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_phone_btn2,&_img_night_call_declined_decline_30x30);
	lv_img_set_pivot(ui->screen_phone_btn2, 0,0);
	lv_img_set_angle(ui->screen_phone_btn2, 0);

	//Write codes screen_phone_btn3
	ui->screen_phone_btn3 = lv_img_create(ui->screen_phone_container);
	lv_obj_set_pos(ui->screen_phone_btn3, 122, 49);
	lv_obj_set_size(ui->screen_phone_btn3, 30, 30);

	//Write style state: LV_STATE_DEFAULT for style_screen_phone_btn3_main_main_default
	static lv_style_t style_screen_phone_btn3_main_main_default;
	lv_style_reset(&style_screen_phone_btn3_main_main_default);
	lv_style_set_img_recolor(&style_screen_phone_btn3_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_phone_btn3_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_phone_btn3_main_main_default, 255);
	lv_obj_add_style(ui->screen_phone_btn3, &style_screen_phone_btn3_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->screen_phone_btn3, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_phone_btn3,&_img_night_incoming_call_accept_30x30);
	lv_img_set_pivot(ui->screen_phone_btn3, 0,0);
	lv_img_set_angle(ui->screen_phone_btn3, 0);

	//Write codes screen_phone_call_btn
	ui->screen_phone_call_btn = lv_img_create(ui->screen_phone_container);
	lv_obj_set_pos(ui->screen_phone_call_btn, 146, 19);
	lv_obj_set_size(ui->screen_phone_call_btn, 30, 30);

	//Write style state: LV_STATE_DEFAULT for style_screen_phone_call_btn_main_main_default
	static lv_style_t style_screen_phone_call_btn_main_main_default;
	lv_style_reset(&style_screen_phone_call_btn_main_main_default);
	lv_style_set_img_recolor(&style_screen_phone_call_btn_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_phone_call_btn_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_phone_call_btn_main_main_default, 255);
	lv_obj_add_style(ui->screen_phone_call_btn, &style_screen_phone_call_btn_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->screen_phone_call_btn, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_phone_call_btn,&_img_night_contacts_l1_call_icon_30x30);
	lv_img_set_pivot(ui->screen_phone_call_btn, 0,0);
	lv_img_set_angle(ui->screen_phone_call_btn, 0);

	//Write codes screen_music_container
	ui->screen_music_container = lv_obj_create(ui->screen);
	lv_obj_set_pos(ui->screen_music_container, 30, 167);
	lv_obj_set_size(ui->screen_music_container, 197, 84);

	//Write style state: LV_STATE_DEFAULT for style_screen_music_container_main_main_default
	static lv_style_t style_screen_music_container_main_main_default;
	lv_style_reset(&style_screen_music_container_main_main_default);
	lv_style_set_radius(&style_screen_music_container_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_music_container_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_color(&style_screen_music_container_main_main_default, lv_color_make(0x08, 0x08, 0x08));
	lv_style_set_bg_grad_dir(&style_screen_music_container_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_music_container_main_main_default, 0);
	lv_style_set_border_color(&style_screen_music_container_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_border_width(&style_screen_music_container_main_main_default, 0);
	lv_style_set_border_opa(&style_screen_music_container_main_main_default, 0);
	lv_style_set_pad_left(&style_screen_music_container_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_music_container_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_music_container_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_music_container_main_main_default, 0);
	lv_obj_add_style(ui->screen_music_container, &style_screen_music_container_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_music_slider_whitebase_img
	ui->screen_music_slider_whitebase_img = lv_img_create(ui->screen_music_container);
	lv_obj_set_pos(ui->screen_music_slider_whitebase_img, 25, 62);
	lv_obj_set_size(ui->screen_music_slider_whitebase_img, 130, 2);

	//Write style state: LV_STATE_DEFAULT for style_screen_music_slider_whitebase_img_main_main_default
	static lv_style_t style_screen_music_slider_whitebase_img_main_main_default;
	lv_style_reset(&style_screen_music_slider_whitebase_img_main_main_default);
	lv_style_set_img_recolor(&style_screen_music_slider_whitebase_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_music_slider_whitebase_img_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_music_slider_whitebase_img_main_main_default, 255);
	lv_obj_add_style(ui->screen_music_slider_whitebase_img, &style_screen_music_slider_whitebase_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->screen_music_slider_whitebase_img, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_music_slider_whitebase_img,&_night_slider_white_100x2);
	lv_img_set_pivot(ui->screen_music_slider_whitebase_img, 0,0);
	lv_img_set_angle(ui->screen_music_slider_whitebase_img, 0);

	//Write codes screen_music_slider_orange_img
	ui->screen_music_slider_orange_img = lv_img_create(ui->screen_music_container);
	lv_obj_set_pos(ui->screen_music_slider_orange_img, 25, 62);
	lv_obj_set_size(ui->screen_music_slider_orange_img, 40, 2);

	//Write style state: LV_STATE_DEFAULT for style_screen_music_slider_orange_img_main_main_default
	static lv_style_t style_screen_music_slider_orange_img_main_main_default;
	lv_style_reset(&style_screen_music_slider_orange_img_main_main_default);
	lv_style_set_img_recolor(&style_screen_music_slider_orange_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_music_slider_orange_img_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_music_slider_orange_img_main_main_default, 255);
	lv_obj_add_style(ui->screen_music_slider_orange_img, &style_screen_music_slider_orange_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->screen_music_slider_orange_img, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_music_slider_orange_img,&_night_slider_orange_40x2);
	lv_img_set_pivot(ui->screen_music_slider_orange_img, 0,0);
	lv_img_set_angle(ui->screen_music_slider_orange_img, 0);

	//Write codes screen_music_slide_dot
	ui->screen_music_slide_dot = lv_img_create(ui->screen_music_container);
	lv_obj_set_pos(ui->screen_music_slide_dot, 81, 56);
	lv_obj_set_size(ui->screen_music_slide_dot, 14, 14);

	//Write style state: LV_STATE_DEFAULT for style_screen_music_slide_dot_main_main_default
	static lv_style_t style_screen_music_slide_dot_main_main_default;
	lv_style_reset(&style_screen_music_slide_dot_main_main_default);
	lv_style_set_img_recolor(&style_screen_music_slide_dot_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_music_slide_dot_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_music_slide_dot_main_main_default, 255);
	lv_obj_add_style(ui->screen_music_slide_dot, &style_screen_music_slide_dot_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->screen_music_slide_dot, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_music_slide_dot,&_night_slider_dot_14x14);
	lv_img_set_pivot(ui->screen_music_slide_dot, 0,0);
	lv_img_set_angle(ui->screen_music_slide_dot, 0);

	//Write codes screen_music_lbl_1
	ui->screen_music_lbl_1 = lv_label_create(ui->screen_music_container);
	lv_obj_set_pos(ui->screen_music_lbl_1, 24, 9);
	lv_obj_set_size(ui->screen_music_lbl_1, 153, 20);
	lv_label_set_text(ui->screen_music_lbl_1, "XX XXXXXX");
	lv_label_set_long_mode(ui->screen_music_lbl_1, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->screen_music_lbl_1, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_screen_music_lbl_1_main_main_default
	static lv_style_t style_screen_music_lbl_1_main_main_default;
	lv_style_reset(&style_screen_music_lbl_1_main_main_default);
	lv_style_set_radius(&style_screen_music_lbl_1_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_music_lbl_1_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_music_lbl_1_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_music_lbl_1_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_music_lbl_1_main_main_default, 0);
	lv_style_set_text_color(&style_screen_music_lbl_1_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_screen_music_lbl_1_main_main_default, &lv_font_FjallaOne_Regular_22);
	lv_style_set_text_letter_space(&style_screen_music_lbl_1_main_main_default, 0);
	lv_style_set_pad_left(&style_screen_music_lbl_1_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_music_lbl_1_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_music_lbl_1_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_music_lbl_1_main_main_default, 0);
	lv_obj_add_style(ui->screen_music_lbl_1, &style_screen_music_lbl_1_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_music_lbl_2
	ui->screen_music_lbl_2 = lv_label_create(ui->screen_music_container);
	lv_obj_set_pos(ui->screen_music_lbl_2, 21, 29);
	lv_obj_set_size(ui->screen_music_lbl_2, 153, 15);
	lv_label_set_text(ui->screen_music_lbl_2, "XX XXXXXX");
	lv_label_set_long_mode(ui->screen_music_lbl_2, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->screen_music_lbl_2, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_screen_music_lbl_2_main_main_default
	static lv_style_t style_screen_music_lbl_2_main_main_default;
	lv_style_reset(&style_screen_music_lbl_2_main_main_default);
	lv_style_set_radius(&style_screen_music_lbl_2_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_music_lbl_2_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_music_lbl_2_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_music_lbl_2_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_music_lbl_2_main_main_default, 0);
	lv_style_set_text_color(&style_screen_music_lbl_2_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_screen_music_lbl_2_main_main_default, &lv_font_FjallaOne_Regular_17);
	lv_style_set_text_letter_space(&style_screen_music_lbl_2_main_main_default, 0);
	lv_style_set_pad_left(&style_screen_music_lbl_2_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_music_lbl_2_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_music_lbl_2_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_music_lbl_2_main_main_default, 0);
	lv_obj_add_style(ui->screen_music_lbl_2, &style_screen_music_lbl_2_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_music_lbl_3
	ui->screen_music_lbl_3 = lv_label_create(ui->screen_music_container);
	lv_obj_set_pos(ui->screen_music_lbl_3, 15, 34);
	lv_obj_set_size(ui->screen_music_lbl_3, 153, 15);
	lv_label_set_text(ui->screen_music_lbl_3, "XX XXXXXX");
	lv_label_set_long_mode(ui->screen_music_lbl_3, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->screen_music_lbl_3, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_screen_music_lbl_3_main_main_default
	static lv_style_t style_screen_music_lbl_3_main_main_default;
	lv_style_reset(&style_screen_music_lbl_3_main_main_default);
	lv_style_set_radius(&style_screen_music_lbl_3_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_music_lbl_3_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_music_lbl_3_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_music_lbl_3_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_music_lbl_3_main_main_default, 0);
	lv_style_set_text_color(&style_screen_music_lbl_3_main_main_default, lv_color_make(0x70, 0x6f, 0x6f));
	lv_style_set_text_font(&style_screen_music_lbl_3_main_main_default, &lv_font_FjallaOne_Regular_17);
	lv_style_set_text_letter_space(&style_screen_music_lbl_3_main_main_default, 0);
	lv_style_set_pad_left(&style_screen_music_lbl_3_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_music_lbl_3_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_music_lbl_3_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_music_lbl_3_main_main_default, 0);
	lv_obj_add_style(ui->screen_music_lbl_3, &style_screen_music_lbl_3_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_music_up_img
	ui->screen_music_up_img = lv_img_create(ui->screen_music_container);
	lv_obj_set_pos(ui->screen_music_up_img, 85, 6);
	lv_obj_set_size(ui->screen_music_up_img, 10, 13);

	//Write style state: LV_STATE_DEFAULT for style_screen_music_up_img_main_main_default
	static lv_style_t style_screen_music_up_img_main_main_default;
	lv_style_reset(&style_screen_music_up_img_main_main_default);
	lv_style_set_img_recolor(&style_screen_music_up_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_music_up_img_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_music_up_img_main_main_default, 255);
	lv_obj_add_style(ui->screen_music_up_img, &style_screen_music_up_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_music_down_img
	ui->screen_music_down_img = lv_img_create(ui->screen_music_container);
	lv_obj_set_pos(ui->screen_music_down_img, 85, 61);
	lv_obj_set_size(ui->screen_music_down_img, 9, 12);

	//Write style state: LV_STATE_DEFAULT for style_screen_music_down_img_main_main_default
	static lv_style_t style_screen_music_down_img_main_main_default;
	lv_style_reset(&style_screen_music_down_img_main_main_default);
	lv_style_set_img_recolor(&style_screen_music_down_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_music_down_img_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_music_down_img_main_main_default, 255);
	lv_obj_add_style(ui->screen_music_down_img, &style_screen_music_down_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_music_sub_button
	ui->screen_music_sub_button = lv_img_create(ui->screen_music_container);
	lv_obj_set_pos(ui->screen_music_sub_button, 150, 22);
	lv_obj_set_size(ui->screen_music_sub_button, 30, 30);

	//Write style state: LV_STATE_DEFAULT for style_screen_music_sub_button_main_main_default
	static lv_style_t style_screen_music_sub_button_main_main_default;
	lv_style_reset(&style_screen_music_sub_button_main_main_default);
	lv_style_set_img_recolor(&style_screen_music_sub_button_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_music_sub_button_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_music_sub_button_main_main_default, 255);
	lv_obj_add_style(ui->screen_music_sub_button, &style_screen_music_sub_button_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);



	//Write codes screen_volume_container
	ui->screen_volume_container = lv_obj_create(ui->screen);
	lv_obj_set_pos(ui->screen_volume_container, 30, 167);
	lv_obj_set_size(ui->screen_volume_container, 197, 84);

	//Write style state: LV_STATE_DEFAULT for style_screen_volume_container_main_main_default
	static lv_style_t style_screen_volume_container_main_main_default;
	lv_style_reset(&style_screen_volume_container_main_main_default);
	lv_style_set_radius(&style_screen_volume_container_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_volume_container_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_color(&style_screen_volume_container_main_main_default, lv_color_make(0x08, 0x08, 0x08));
	lv_style_set_bg_grad_dir(&style_screen_volume_container_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_volume_container_main_main_default, 0);
	lv_style_set_border_color(&style_screen_volume_container_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_border_width(&style_screen_volume_container_main_main_default, 0);
	lv_style_set_border_opa(&style_screen_volume_container_main_main_default, 0);
	lv_style_set_pad_left(&style_screen_volume_container_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_volume_container_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_volume_container_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_volume_container_main_main_default, 0);
	lv_obj_add_style(ui->screen_volume_container, &style_screen_volume_container_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_volume_plus
	ui->screen_volume_plus = lv_img_create(ui->screen_volume_container);
	lv_obj_set_pos(ui->screen_volume_plus, 85, 5);
	lv_obj_set_size(ui->screen_volume_plus, 11, 11);

	//Write style state: LV_STATE_DEFAULT for style_screen_volume_plus_main_main_default
	static lv_style_t style_screen_volume_plus_main_main_default;
	lv_style_reset(&style_screen_volume_plus_main_main_default);
	lv_style_set_img_recolor(&style_screen_volume_plus_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_volume_plus_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_volume_plus_main_main_default, 255);
	lv_obj_add_style(ui->screen_volume_plus, &style_screen_volume_plus_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_volume_minus
	ui->screen_volume_minus = lv_img_create(ui->screen_volume_container);
	lv_obj_set_pos(ui->screen_volume_minus, 85, 75);
	lv_obj_set_size(ui->screen_volume_minus, 11, 3);

	//Write style state: LV_STATE_DEFAULT for style_screen_volume_minus_main_main_default
	static lv_style_t style_screen_volume_minus_main_main_default;
	lv_style_reset(&style_screen_volume_minus_main_main_default);
	lv_style_set_img_recolor(&style_screen_volume_minus_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_volume_minus_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_volume_minus_main_main_default, 255);
	lv_obj_add_style(ui->screen_volume_minus, &style_screen_volume_minus_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_volume_signbtn
	ui->screen_volume_signbtn = lv_img_create(ui->screen_volume_container);
	lv_obj_set_pos(ui->screen_volume_signbtn, 150, 22);
	lv_obj_set_size(ui->screen_volume_signbtn, 30, 30);

	//Write style state: LV_STATE_DEFAULT for style_screen_volume_signbtn_main_main_default
	static lv_style_t style_screen_volume_signbtn_main_main_default;
	lv_style_reset(&style_screen_volume_signbtn_main_main_default);
	lv_style_set_img_recolor(&style_screen_volume_signbtn_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_volume_signbtn_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_volume_signbtn_main_main_default, 255);
	lv_obj_add_style(ui->screen_volume_signbtn, &style_screen_volume_signbtn_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_volume_base
	ui->screen_volume_base = lv_img_create(ui->screen_volume_container);
	lv_obj_set_pos(ui->screen_volume_base, 40, 40);
	lv_obj_set_size(ui->screen_volume_base, 110, 27);

	//Write style state: LV_STATE_DEFAULT for style_screen_volume_base_main_main_default
	static lv_style_t style_screen_volume_base_main_main_default;
	lv_style_reset(&style_screen_volume_base_main_main_default);
	lv_style_set_img_recolor(&style_screen_volume_base_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_volume_base_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_volume_base_main_main_default, 255);
	lv_obj_add_style(ui->screen_volume_base, &style_screen_volume_base_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_volume_label
	ui->screen_volume_label = lv_label_create(ui->screen_volume_container);
	lv_obj_set_pos(ui->screen_volume_label, 59, 16);
	lv_obj_set_size(ui->screen_volume_label, 70, 20);
	lv_label_set_text(ui->screen_volume_label, "Volume");
	lv_label_set_long_mode(ui->screen_volume_label, LV_LABEL_LONG_WRAP);
	lv_obj_set_style_text_align(ui->screen_volume_label, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_screen_volume_label_main_main_default
	static lv_style_t style_screen_volume_label_main_main_default;
	lv_style_reset(&style_screen_volume_label_main_main_default);
	lv_style_set_radius(&style_screen_volume_label_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_volume_label_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_volume_label_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_volume_label_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_volume_label_main_main_default, 0);
	lv_style_set_text_color(&style_screen_volume_label_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_screen_volume_label_main_main_default, &lv_font_FjallaOne_Regular_22);
	lv_style_set_text_letter_space(&style_screen_volume_label_main_main_default, 0);
	lv_style_set_pad_left(&style_screen_volume_label_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_volume_label_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_volume_label_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_volume_label_main_main_default, 0);
	lv_obj_add_style(ui->screen_volume_label, &style_screen_volume_label_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	

	//Write codes screen_Fuel_low_mMarker
	ui->screen_Fuel_low_mMarker = lv_img_create(ui->screen);
	lv_obj_set_pos(ui->screen_Fuel_low_mMarker, 35, 276);
	lv_obj_set_size(ui->screen_Fuel_low_mMarker, 11, 13);

	//Write style state: LV_STATE_DEFAULT for style_screen_fuel_low_mmarker_main_main_default
	//static lv_style_t style_screen_fuel_low_mmarker_main_main_default;
	lv_style_reset(&style_screen_fuel_low_mmarker_main_main_default);
	lv_style_set_img_recolor(&style_screen_fuel_low_mmarker_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_fuel_low_mmarker_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_fuel_low_mmarker_main_main_default, 255);
	lv_obj_add_style(ui->screen_Fuel_low_mMarker, &style_screen_fuel_low_mmarker_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->screen_Fuel_low_mMarker, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_Fuel_low_mMarker,&_img_night_fuel_low_marker_11x13);
	lv_img_set_pivot(ui->screen_Fuel_low_mMarker, 0,0);
	lv_img_set_angle(ui->screen_Fuel_low_mMarker, 0);

	//Write codes screen_trip_container
	ui->screen_trip_container = lv_obj_create(ui->screen);
	lv_obj_set_pos(ui->screen_trip_container, 30, 167);
	lv_obj_set_size(ui->screen_trip_container, 195, 78);

	//Write style state: LV_STATE_DEFAULT for style_screen_trip_container_main_main_default
	static lv_style_t style_screen_trip_container_main_main_default;
	lv_style_reset(&style_screen_trip_container_main_main_default);
	lv_style_set_radius(&style_screen_trip_container_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_trip_container_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_color(&style_screen_trip_container_main_main_default, lv_color_make(0x08, 0x08, 0x08));
	lv_style_set_bg_grad_dir(&style_screen_trip_container_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_trip_container_main_main_default, 0);
	lv_style_set_border_color(&style_screen_trip_container_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_border_width(&style_screen_trip_container_main_main_default, 0);
	lv_style_set_border_opa(&style_screen_trip_container_main_main_default, 0);
	lv_style_set_pad_left(&style_screen_trip_container_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_trip_container_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_trip_container_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_trip_container_main_main_default, 0);
	lv_obj_add_style(ui->screen_trip_container, &style_screen_trip_container_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_trip_lbl1
	ui->screen_trip_lbl1 = lv_label_create(ui->screen_trip_container);
	lv_obj_set_pos(ui->screen_trip_lbl1, 37, 15);
	lv_obj_set_size(ui->screen_trip_lbl1, 26, 21);
	lv_label_set_text(ui->screen_trip_lbl1, "Trip");
	lv_label_set_long_mode(ui->screen_trip_lbl1, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->screen_trip_lbl1, LV_TEXT_ALIGN_LEFT, 0);

	//Write style state: LV_STATE_DEFAULT for style_screen_trip_lbl1_main_main_default
	static lv_style_t style_screen_trip_lbl1_main_main_default;
	lv_style_reset(&style_screen_trip_lbl1_main_main_default);
	lv_style_set_radius(&style_screen_trip_lbl1_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_trip_lbl1_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_trip_lbl1_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_trip_lbl1_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_trip_lbl1_main_main_default, 0);
	lv_style_set_text_color(&style_screen_trip_lbl1_main_main_default, lv_color_make(0xff, 0x78, 0x00));
	lv_style_set_text_font(&style_screen_trip_lbl1_main_main_default, &lv_font_FjallaOne_Regular_17);
	lv_style_set_text_letter_space(&style_screen_trip_lbl1_main_main_default, 0);
	lv_style_set_pad_left(&style_screen_trip_lbl1_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_trip_lbl1_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_trip_lbl1_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_trip_lbl1_main_main_default, 0);
	lv_obj_add_style(ui->screen_trip_lbl1, &style_screen_trip_lbl1_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_trip_val_1
	ui->screen_trip_val_1 = lv_label_create(ui->screen_trip_container);
	lv_obj_set_pos(ui->screen_trip_val_1, 71, 14);
	lv_obj_set_size(ui->screen_trip_val_1, 49, 18);
	lv_label_set_text(ui->screen_trip_val_1, "999.9");
	lv_label_set_long_mode(ui->screen_trip_val_1, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->screen_trip_val_1, LV_TEXT_ALIGN_RIGHT, 0);

	//Write style state: LV_STATE_DEFAULT for style_screen_trip_val_1_main_main_default
	static lv_style_t style_screen_trip_val_1_main_main_default;
	lv_style_reset(&style_screen_trip_val_1_main_main_default);
	lv_style_set_radius(&style_screen_trip_val_1_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_trip_val_1_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_trip_val_1_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_trip_val_1_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_trip_val_1_main_main_default, 0);
	lv_style_set_text_color(&style_screen_trip_val_1_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_screen_trip_val_1_main_main_default, &lv_font_FjallaOne_Regular_22);
	lv_style_set_text_letter_space(&style_screen_trip_val_1_main_main_default, 0);
	lv_style_set_pad_left(&style_screen_trip_val_1_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_trip_val_1_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_trip_val_1_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_trip_val_1_main_main_default, 0);
	lv_obj_add_style(ui->screen_trip_val_1, &style_screen_trip_val_1_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_trip_unit_1
	ui->screen_trip_unit_1 = lv_label_create(ui->screen_trip_container);
	lv_obj_set_pos(ui->screen_trip_unit_1, 124, 16);
	lv_obj_set_size(ui->screen_trip_unit_1, 56, 19);
	lv_label_set_text(ui->screen_trip_unit_1, "L/100km");
	lv_label_set_long_mode(ui->screen_trip_unit_1, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->screen_trip_unit_1, LV_TEXT_ALIGN_LEFT, 0);

	//Write style state: LV_STATE_DEFAULT for style_screen_trip_unit_1_main_main_default
	static lv_style_t style_screen_trip_unit_1_main_main_default;
	lv_style_reset(&style_screen_trip_unit_1_main_main_default);
	lv_style_set_radius(&style_screen_trip_unit_1_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_trip_unit_1_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_trip_unit_1_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_trip_unit_1_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_trip_unit_1_main_main_default, 0);
	lv_style_set_text_color(&style_screen_trip_unit_1_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_screen_trip_unit_1_main_main_default, &lv_font_FjallaOne_Regular_17);
	lv_style_set_text_letter_space(&style_screen_trip_unit_1_main_main_default, 0);
	lv_style_set_pad_left(&style_screen_trip_unit_1_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_trip_unit_1_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_trip_unit_1_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_trip_unit_1_main_main_default, 0);
	lv_obj_add_style(ui->screen_trip_unit_1, &style_screen_trip_unit_1_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_trip_lbl_2
	ui->screen_trip_lbl_2 = lv_label_create(ui->screen_trip_container);
	lv_obj_set_pos(ui->screen_trip_lbl_2, 34, 43);
	lv_obj_set_size(ui->screen_trip_lbl_2, 33, 21);
	lv_label_set_text(ui->screen_trip_lbl_2, "Time");
	lv_label_set_long_mode(ui->screen_trip_lbl_2, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->screen_trip_lbl_2, LV_TEXT_ALIGN_RIGHT, 0);

	//Write style state: LV_STATE_DEFAULT for style_screen_trip_lbl_2_main_main_default
	static lv_style_t style_screen_trip_lbl_2_main_main_default;
	lv_style_reset(&style_screen_trip_lbl_2_main_main_default);
	lv_style_set_radius(&style_screen_trip_lbl_2_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_trip_lbl_2_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_trip_lbl_2_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_trip_lbl_2_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_trip_lbl_2_main_main_default, 0);
	lv_style_set_text_color(&style_screen_trip_lbl_2_main_main_default, lv_color_make(0xff, 0x78, 0x00));
	lv_style_set_text_font(&style_screen_trip_lbl_2_main_main_default, &lv_font_FjallaOne_Regular_17);
	lv_style_set_text_letter_space(&style_screen_trip_lbl_2_main_main_default, 0);
	lv_style_set_pad_left(&style_screen_trip_lbl_2_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_trip_lbl_2_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_trip_lbl_2_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_trip_lbl_2_main_main_default, 0);
	lv_obj_add_style(ui->screen_trip_lbl_2, &style_screen_trip_lbl_2_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_trip_hr_lbl
	ui->screen_trip_hr_lbl = lv_label_create(ui->screen_trip_container);
	lv_obj_set_pos(ui->screen_trip_hr_lbl, 71, 42);
	lv_obj_set_size(ui->screen_trip_hr_lbl, 21, 18);
	lv_label_set_text(ui->screen_trip_hr_lbl, "99");
	lv_label_set_long_mode(ui->screen_trip_hr_lbl, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->screen_trip_hr_lbl, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_screen_trip_hr_lbl_main_main_default
	static lv_style_t style_screen_trip_hr_lbl_main_main_default;
	lv_style_reset(&style_screen_trip_hr_lbl_main_main_default);
	lv_style_set_radius(&style_screen_trip_hr_lbl_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_trip_hr_lbl_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_trip_hr_lbl_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_trip_hr_lbl_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_trip_hr_lbl_main_main_default, 0);
	lv_style_set_text_color(&style_screen_trip_hr_lbl_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_screen_trip_hr_lbl_main_main_default, &lv_font_FjallaOne_Regular_22);
	lv_style_set_text_letter_space(&style_screen_trip_hr_lbl_main_main_default, 0);
	lv_style_set_pad_left(&style_screen_trip_hr_lbl_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_trip_hr_lbl_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_trip_hr_lbl_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_trip_hr_lbl_main_main_default, 0);
	lv_obj_add_style(ui->screen_trip_hr_lbl, &style_screen_trip_hr_lbl_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_trip_hh_lbl
	ui->screen_trip_hh_lbl = lv_label_create(ui->screen_trip_container);
	lv_obj_set_pos(ui->screen_trip_hh_lbl, 98, 44);
	lv_obj_set_size(ui->screen_trip_hh_lbl, 11, 12);
	lv_label_set_text(ui->screen_trip_hh_lbl, "h");
	lv_label_set_long_mode(ui->screen_trip_hh_lbl, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->screen_trip_hh_lbl, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_screen_trip_hh_lbl_main_main_default
	static lv_style_t style_screen_trip_hh_lbl_main_main_default;
	lv_style_reset(&style_screen_trip_hh_lbl_main_main_default);
	lv_style_set_radius(&style_screen_trip_hh_lbl_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_trip_hh_lbl_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_trip_hh_lbl_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_trip_hh_lbl_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_trip_hh_lbl_main_main_default, 0);
	lv_style_set_text_color(&style_screen_trip_hh_lbl_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_screen_trip_hh_lbl_main_main_default, &lv_font_FjallaOne_Regular_17);
	lv_style_set_text_letter_space(&style_screen_trip_hh_lbl_main_main_default, 0);
	lv_style_set_pad_left(&style_screen_trip_hh_lbl_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_trip_hh_lbl_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_trip_hh_lbl_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_trip_hh_lbl_main_main_default, 0);
	lv_obj_add_style(ui->screen_trip_hh_lbl, &style_screen_trip_hh_lbl_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_trip_mi_lbl
	ui->screen_trip_mi_lbl = lv_label_create(ui->screen_trip_container);
	lv_obj_set_pos(ui->screen_trip_mi_lbl, 109, 42);
	lv_obj_set_size(ui->screen_trip_mi_lbl, 21, 18);
	lv_label_set_text(ui->screen_trip_mi_lbl, "99");
	lv_label_set_long_mode(ui->screen_trip_mi_lbl, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->screen_trip_mi_lbl, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_screen_trip_mi_lbl_main_main_default
	static lv_style_t style_screen_trip_mi_lbl_main_main_default;
	lv_style_reset(&style_screen_trip_mi_lbl_main_main_default);
	lv_style_set_radius(&style_screen_trip_mi_lbl_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_trip_mi_lbl_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_trip_mi_lbl_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_trip_mi_lbl_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_trip_mi_lbl_main_main_default, 0);
	lv_style_set_text_color(&style_screen_trip_mi_lbl_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_screen_trip_mi_lbl_main_main_default, &lv_font_FjallaOne_Regular_22);
	lv_style_set_text_letter_space(&style_screen_trip_mi_lbl_main_main_default, 0);
	lv_style_set_pad_left(&style_screen_trip_mi_lbl_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_trip_mi_lbl_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_trip_mi_lbl_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_trip_mi_lbl_main_main_default, 0);
	lv_obj_add_style(ui->screen_trip_mi_lbl, &style_screen_trip_mi_lbl_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_trip_mm_lbl
	ui->screen_trip_mm_lbl = lv_label_create(ui->screen_trip_container);
	lv_obj_set_pos(ui->screen_trip_mm_lbl, 135, 44);
	lv_obj_set_size(ui->screen_trip_mm_lbl, 12, 12);
	lv_label_set_text(ui->screen_trip_mm_lbl, "m");
	lv_label_set_long_mode(ui->screen_trip_mm_lbl, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->screen_trip_mm_lbl, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_screen_trip_mm_lbl_main_main_default
	static lv_style_t style_screen_trip_mm_lbl_main_main_default;
	lv_style_reset(&style_screen_trip_mm_lbl_main_main_default);
	lv_style_set_radius(&style_screen_trip_mm_lbl_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_trip_mm_lbl_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_trip_mm_lbl_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_trip_mm_lbl_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_trip_mm_lbl_main_main_default, 0);
	lv_style_set_text_color(&style_screen_trip_mm_lbl_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_screen_trip_mm_lbl_main_main_default, &lv_font_FjallaOne_Regular_17);
	lv_style_set_text_letter_space(&style_screen_trip_mm_lbl_main_main_default, 0);
	lv_style_set_pad_left(&style_screen_trip_mm_lbl_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_trip_mm_lbl_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_trip_mm_lbl_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_trip_mm_lbl_main_main_default, 0);
	lv_obj_add_style(ui->screen_trip_mm_lbl, &style_screen_trip_mm_lbl_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_trip_up_arrow
	ui->screen_trip_up_arrow = lv_img_create(ui->screen_trip_container);
	lv_obj_set_pos(ui->screen_trip_up_arrow, 85, 4);
	lv_obj_set_size(ui->screen_trip_up_arrow, 12, 7);

	//Write style state: LV_STATE_DEFAULT for style_screen_trip_up_arrow_main_main_default
	static lv_style_t style_screen_trip_up_arrow_main_main_default;
	lv_style_reset(&style_screen_trip_up_arrow_main_main_default);
	lv_style_set_img_recolor(&style_screen_trip_up_arrow_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_trip_up_arrow_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_trip_up_arrow_main_main_default, 255);
	lv_obj_add_style(ui->screen_trip_up_arrow, &style_screen_trip_up_arrow_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->screen_trip_up_arrow, LV_OBJ_FLAG_CLICKABLE);
	//lv_img_set_src(ui->screen_trip_up_arrow,&_white_12x7);
	lv_img_set_src(ui->screen_trip_up_arrow,&new_trip_up_arrow);
	
	lv_img_set_pivot(ui->screen_trip_up_arrow, 0,0);
	lv_img_set_angle(ui->screen_trip_up_arrow, 0);

	//Write codes screen_trip_down_arrow
	ui->screen_trip_down_arrow = lv_img_create(ui->screen_trip_container);
	lv_obj_set_pos(ui->screen_trip_down_arrow, 84, 68);
	lv_obj_set_size(ui->screen_trip_down_arrow, 12, 7);

	//Write style state: LV_STATE_DEFAULT for style_screen_trip_down_arrow_main_main_default
	static lv_style_t style_screen_trip_down_arrow_main_main_default;
	lv_style_reset(&style_screen_trip_down_arrow_main_main_default);
	lv_style_set_img_recolor(&style_screen_trip_down_arrow_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_trip_down_arrow_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_trip_down_arrow_main_main_default, 255);
	lv_obj_add_style(ui->screen_trip_down_arrow, &style_screen_trip_down_arrow_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->screen_trip_down_arrow, LV_OBJ_FLAG_CLICKABLE);
	//lv_img_set_src(ui->screen_trip_down_arrow,&_DowAre_12x7);
	lv_img_set_src(ui->screen_trip_down_arrow,&new_trip_down_arrow);
	lv_img_set_pivot(ui->screen_trip_down_arrow, 0,0);
	lv_img_set_angle(ui->screen_trip_down_arrow, 0);

	//Write codes screen_blu_msg_icon
	ui->screen_blu_msg_icon = lv_img_create(ui->screen);
	lv_obj_set_pos(ui->screen_blu_msg_icon, 42, 87);
	lv_obj_set_size(ui->screen_blu_msg_icon, 20, 12);

	//Write style state: LV_STATE_DEFAULT for style_screen_blu_msg_icon_main_main_default
	static lv_style_t style_screen_blu_msg_icon_main_main_default;
	lv_style_reset(&style_screen_blu_msg_icon_main_main_default);
	lv_style_set_img_recolor(&style_screen_blu_msg_icon_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_blu_msg_icon_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_blu_msg_icon_main_main_default, 255);
	lv_obj_add_style(ui->screen_blu_msg_icon, &style_screen_blu_msg_icon_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->screen_blu_msg_icon, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_blu_msg_icon,&_night_Message_black_20x12);
	lv_img_set_pivot(ui->screen_blu_msg_icon, 0,0);
	lv_img_set_angle(ui->screen_blu_msg_icon, 0);

	//Write codes screen_blu_mis_call_icon
	ui->screen_blu_mis_call_icon = lv_img_create(ui->screen);
	lv_obj_set_pos(ui->screen_blu_mis_call_icon, 183, 87);
	lv_obj_set_size(ui->screen_blu_mis_call_icon, 15, 12);

	//Write style state: LV_STATE_DEFAULT for style_screen_blu_mis_call_icon_main_main_default
	static lv_style_t style_screen_blu_mis_call_icon_main_main_default;
	lv_style_reset(&style_screen_blu_mis_call_icon_main_main_default);
	lv_style_set_img_recolor(&style_screen_blu_mis_call_icon_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_blu_mis_call_icon_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_blu_mis_call_icon_main_main_default, 255);
	lv_obj_add_style(ui->screen_blu_mis_call_icon, &style_screen_blu_mis_call_icon_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->screen_blu_mis_call_icon, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_blu_mis_call_icon,&_night_Missed_Call_15x12);
	lv_img_set_pivot(ui->screen_blu_mis_call_icon, 0,0);
	lv_img_set_angle(ui->screen_blu_mis_call_icon, 0);

	//Write codes screen_day_base_container
	ui->screen_day_base_container = lv_obj_create(ui->screen);
	lv_obj_set_pos(ui->screen_day_base_container, 0, 0);
	lv_obj_set_size(ui->screen_day_base_container, 240, 320);

	//Write style state: LV_STATE_DEFAULT for style_screen_day_base_container_main_main_default
	static lv_style_t style_screen_day_base_container_main_main_default;
	lv_style_reset(&style_screen_day_base_container_main_main_default);
	lv_style_set_radius(&style_screen_day_base_container_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_day_base_container_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_color(&style_screen_day_base_container_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_dir(&style_screen_day_base_container_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_day_base_container_main_main_default, 0);
	lv_style_set_border_color(&style_screen_day_base_container_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_border_width(&style_screen_day_base_container_main_main_default, 0);
	lv_style_set_border_opa(&style_screen_day_base_container_main_main_default, 255);
	lv_style_set_pad_left(&style_screen_day_base_container_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_day_base_container_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_day_base_container_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_day_base_container_main_main_default, 0);
	lv_obj_add_style(ui->screen_day_base_container, &style_screen_day_base_container_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_white_img
	ui->screen_white_img = lv_img_create(ui->screen_day_base_container);
	lv_obj_set_pos(ui->screen_white_img, 7, 47);
	lv_obj_set_size(ui->screen_white_img, 226, 226);

	//Write style state: LV_STATE_DEFAULT for style_screen_white_img_main_main_default
	static lv_style_t style_screen_white_img_main_main_default;
	lv_style_reset(&style_screen_white_img_main_main_default);
	lv_style_set_img_recolor(&style_screen_white_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_white_img_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_white_img_main_main_default, 255);
	lv_obj_add_style(ui->screen_white_img, &style_screen_white_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->screen_white_img, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_white_img,&day_white_Grey_circle);
	lv_img_set_pivot(ui->screen_white_img, 0,0);
	lv_img_set_angle(ui->screen_white_img, 0);

	//Write codes screen_day_msg_img
	ui->screen_day_msg_img = lv_img_create(ui->screen_day_base_container);
	lv_obj_set_pos(ui->screen_day_msg_img, 42, 87);
	lv_obj_set_size(ui->screen_day_msg_img, 20, 12);

	//Write style state: LV_STATE_DEFAULT for style_screen_day_msg_img_main_main_default
	static lv_style_t style_screen_day_msg_img_main_main_default;
	lv_style_reset(&style_screen_day_msg_img_main_main_default);
	lv_style_set_img_recolor(&style_screen_day_msg_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_day_msg_img_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_day_msg_img_main_main_default, 255);
	lv_obj_add_style(ui->screen_day_msg_img, &style_screen_day_msg_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_img_set_src(ui->screen_day_msg_img,&day_msg_icon);

	//Write codes screen_day_mis_call_img
	ui->screen_day_mis_call_img = lv_img_create(ui->screen_day_base_container);
	lv_obj_set_pos(ui->screen_day_mis_call_img, 183, 87);
	lv_obj_set_size(ui->screen_day_mis_call_img, 15, 12);

	//Write style state: LV_STATE_DEFAULT for style_screen_day_mis_call_img_main_main_default
	static lv_style_t style_screen_day_mis_call_img_main_main_default;
	lv_style_reset(&style_screen_day_mis_call_img_main_main_default);
	lv_style_set_img_recolor(&style_screen_day_mis_call_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_day_mis_call_img_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_day_mis_call_img_main_main_default, 255);
	lv_obj_add_style(ui->screen_day_mis_call_img, &style_screen_day_mis_call_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_img_set_src(ui->screen_day_mis_call_img,&day_mis_call_icon);

	//Write codes screen_day_battery_img
	ui->screen_day_battery_img = lv_img_create(ui->screen_day_base_container);
	lv_obj_set_pos(ui->screen_day_battery_img, 26, 111);
	lv_obj_set_size(ui->screen_day_battery_img, 20, 12);

	//Write style state: LV_STATE_DEFAULT for style_screen_day_battery_img_main_main_default
	static lv_style_t style_screen_day_battery_img_main_main_default;
	lv_style_reset(&style_screen_day_battery_img_main_main_default);
	lv_style_set_img_recolor(&style_screen_day_battery_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_day_battery_img_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_day_battery_img_main_main_default, 255);
	lv_obj_add_style(ui->screen_day_battery_img, &style_screen_day_battery_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_day_signal_img
	ui->screen_day_signal_img = lv_img_create(ui->screen_day_base_container);
	lv_obj_set_pos(ui->screen_day_signal_img, 200, 111);
	lv_obj_set_size(ui->screen_day_signal_img, 14, 12);

	//Write style state: LV_STATE_DEFAULT for style_screen_day_signal_img_main_main_default
	static lv_style_t style_screen_day_signal_img_main_main_default;
	lv_style_reset(&style_screen_day_signal_img_main_main_default);
	lv_style_set_img_recolor(&style_screen_day_signal_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_day_signal_img_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_day_signal_img_main_main_default, 255);
	lv_obj_add_style(ui->screen_day_signal_img, &style_screen_day_signal_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_day_sub_btn
	ui->screen_day_sub_btn = lv_img_create(ui->screen_day_base_container);
	lv_obj_set_pos(ui->screen_day_sub_btn, 198, 147);
	lv_obj_set_size(ui->screen_day_sub_btn, 24, 24);

	//Write style state: LV_STATE_DEFAULT for style_screen_day_sub_btn_main_main_default
	static lv_style_t style_screen_day_sub_btn_main_main_default;
	lv_style_reset(&style_screen_day_sub_btn_main_main_default);
	lv_style_set_img_recolor(&style_screen_day_sub_btn_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_day_sub_btn_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_day_sub_btn_main_main_default, 255);
	lv_obj_add_style(ui->screen_day_sub_btn, &style_screen_day_sub_btn_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->screen_day_sub_btn, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_day_sub_btn,&subbtn_day_24x24);
	lv_img_set_pivot(ui->screen_day_sub_btn, 0,0);
	lv_img_set_angle(ui->screen_day_sub_btn, 0);

	//Write codes screen_Day_colon
	ui->screen_Day_colon = lv_label_create(ui->screen_day_base_container);
	lv_obj_set_pos(ui->screen_Day_colon, 105, 85);
	lv_obj_set_size(ui->screen_Day_colon, 4, 11);
	lv_label_set_text(ui->screen_Day_colon, ":");
	lv_label_set_long_mode(ui->screen_Day_colon, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->screen_Day_colon, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_screen_day_colon_main_main_default
	static lv_style_t style_screen_day_colon_main_main_default;
	lv_style_reset(&style_screen_day_colon_main_main_default);
	lv_style_set_radius(&style_screen_day_colon_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_day_colon_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_day_colon_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_day_colon_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_day_colon_main_main_default, 0);
	lv_style_set_text_color(&style_screen_day_colon_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_screen_day_colon_main_main_default, &lv_font_FjallaOne_Regular_19);
	lv_style_set_text_letter_space(&style_screen_day_colon_main_main_default, 0);
	lv_style_set_pad_left(&style_screen_day_colon_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_day_colon_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_day_colon_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_day_colon_main_main_default, 0);
	lv_obj_add_style(ui->screen_Day_colon, &style_screen_day_colon_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_Day_min
	ui->screen_Day_min = lv_label_create(ui->screen_day_base_container);
	lv_obj_set_pos(ui->screen_Day_min, 110, 81);
	lv_obj_set_size(ui->screen_Day_min, 17, 15);
	lv_label_set_text(ui->screen_Day_min, "24");
	lv_label_set_long_mode(ui->screen_Day_min, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->screen_Day_min, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_screen_day_min_main_main_default
	static lv_style_t style_screen_day_min_main_main_default;
	lv_style_reset(&style_screen_day_min_main_main_default);
	lv_style_set_radius(&style_screen_day_min_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_day_min_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_day_min_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_day_min_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_day_min_main_main_default, 0);
	lv_style_set_text_color(&style_screen_day_min_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_screen_day_min_main_main_default, &lv_font_FjallaOne_Regular_19);
	lv_style_set_text_letter_space(&style_screen_day_min_main_main_default, 0);
	lv_style_set_pad_left(&style_screen_day_min_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_day_min_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_day_min_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_day_min_main_main_default, 0);
	lv_obj_add_style(ui->screen_Day_min, &style_screen_day_min_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_Day_Am_pm
	ui->screen_Day_Am_pm = lv_label_create(ui->screen_day_base_container);
	lv_obj_set_pos(ui->screen_Day_Am_pm, 131, 81);
	lv_obj_set_size(ui->screen_Day_Am_pm, 20, 15);
	lv_label_set_text(ui->screen_Day_Am_pm, "Pm");
	lv_label_set_long_mode(ui->screen_Day_Am_pm, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->screen_Day_Am_pm, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_screen_day_am_pm_main_main_default
	static lv_style_t style_screen_day_am_pm_main_main_default;
	lv_style_reset(&style_screen_day_am_pm_main_main_default);
	lv_style_set_radius(&style_screen_day_am_pm_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_day_am_pm_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_day_am_pm_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_day_am_pm_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_day_am_pm_main_main_default, 0);
	lv_style_set_text_color(&style_screen_day_am_pm_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_screen_day_am_pm_main_main_default, &lv_font_FjallaOne_Regular_19);
	lv_style_set_text_letter_space(&style_screen_day_am_pm_main_main_default, 0);
	lv_style_set_pad_left(&style_screen_day_am_pm_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_day_am_pm_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_day_am_pm_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_day_am_pm_main_main_default, 0);
	lv_obj_add_style(ui->screen_Day_Am_pm, &style_screen_day_am_pm_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_Day_hour
	ui->screen_Day_hour = lv_label_create(ui->screen_day_base_container);
	lv_obj_set_pos(ui->screen_Day_hour, 88, 81);
	lv_obj_set_size(ui->screen_Day_hour, 16, 15);
	lv_label_set_text(ui->screen_Day_hour, "24");
	lv_label_set_long_mode(ui->screen_Day_hour, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->screen_Day_hour, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_screen_day_hour_main_main_default
	static lv_style_t style_screen_day_hour_main_main_default;
	lv_style_reset(&style_screen_day_hour_main_main_default);
	lv_style_set_radius(&style_screen_day_hour_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_day_hour_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_day_hour_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_day_hour_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_day_hour_main_main_default, 0);
	lv_style_set_text_color(&style_screen_day_hour_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_screen_day_hour_main_main_default, &lv_font_FjallaOne_Regular_19);
	lv_style_set_text_letter_space(&style_screen_day_hour_main_main_default, 0);
	lv_style_set_pad_left(&style_screen_day_hour_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_day_hour_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_day_hour_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_day_hour_main_main_default, 0);
	lv_obj_add_style(ui->screen_Day_hour, &style_screen_day_hour_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_Day_1000_rpm
	ui->screen_Day_1000_rpm = lv_img_create(ui->screen_day_base_container);
	lv_obj_set_pos(ui->screen_Day_1000_rpm, 94, 53);
	lv_obj_set_size(ui->screen_Day_1000_rpm, 51, 13);

	//Write style state: LV_STATE_DEFAULT for style_screen_day_1000_rpm_main_main_default
	static lv_style_t style_screen_day_1000_rpm_main_main_default;
	lv_style_reset(&style_screen_day_1000_rpm_main_main_default);
	lv_style_set_img_recolor(&style_screen_day_1000_rpm_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_day_1000_rpm_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_day_1000_rpm_main_main_default, 255);
	lv_obj_add_style(ui->screen_Day_1000_rpm, &style_screen_day_1000_rpm_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->screen_Day_1000_rpm, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_Day_1000_rpm,&img_day_x1000_RPM_new);
	lv_img_set_pivot(ui->screen_Day_1000_rpm, 0,0);
	lv_img_set_angle(ui->screen_Day_1000_rpm, 0);

	//Write codes screen_gear_N_img_Day
	ui->screen_gear_N_img_Day = lv_img_create(ui->screen_day_base_container);
	lv_obj_set_pos(ui->screen_gear_N_img_Day, 30, 150);
	lv_obj_set_size(ui->screen_gear_N_img_Day, 15, 23);

	//Write style state: LV_STATE_DEFAULT for style_screen_gear_n_img_day_main_main_default
	static lv_style_t style_screen_gear_n_img_day_main_main_default;
	lv_style_reset(&style_screen_gear_n_img_day_main_main_default);
	lv_style_set_img_recolor(&style_screen_gear_n_img_day_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_gear_n_img_day_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_gear_n_img_day_main_main_default, 255);
	lv_obj_add_style(ui->screen_gear_N_img_Day, &style_screen_gear_n_img_day_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_img_set_src(ui->screen_gear_N_img_Day,&img_day_gear_neutral);

	//Write codes screen_Day_Gear_pos_Num
	ui->screen_Day_Gear_pos_Num = lv_label_create(ui->screen_day_base_container);
	lv_obj_set_pos(ui->screen_Day_Gear_pos_Num, 31, 142);
	lv_obj_set_size(ui->screen_Day_Gear_pos_Num, 12, 28);
	lv_label_set_text(ui->screen_Day_Gear_pos_Num, "2");
	lv_label_set_long_mode(ui->screen_Day_Gear_pos_Num, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->screen_Day_Gear_pos_Num, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_screen_day_gear_pos_num_main_main_default
	static lv_style_t style_screen_day_gear_pos_num_main_main_default;
	lv_style_reset(&style_screen_day_gear_pos_num_main_main_default);
	lv_style_set_radius(&style_screen_day_gear_pos_num_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_day_gear_pos_num_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_day_gear_pos_num_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_day_gear_pos_num_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_day_gear_pos_num_main_main_default, 0);
	lv_style_set_text_color(&style_screen_day_gear_pos_num_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_screen_day_gear_pos_num_main_main_default, &lv_font_FjallaOne_Regular_30);
	lv_style_set_text_letter_space(&style_screen_day_gear_pos_num_main_main_default, 0);
	lv_style_set_pad_left(&style_screen_day_gear_pos_num_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_day_gear_pos_num_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_day_gear_pos_num_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_day_gear_pos_num_main_main_default, 0);
	lv_obj_add_style(ui->screen_Day_Gear_pos_Num, &style_screen_day_gear_pos_num_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_kmimage
	ui->screen_kmimage = lv_img_create(ui->screen_day_base_container);
	lv_obj_set_pos(ui->screen_kmimage, 189, 150);
	lv_obj_set_size(ui->screen_kmimage, 33, 19);

	//Write style state: LV_STATE_DEFAULT for style_screen_kmimage_main_main_default
	static lv_style_t style_screen_kmimage_main_main_default;
	lv_style_reset(&style_screen_kmimage_main_main_default);
	lv_style_set_img_recolor(&style_screen_kmimage_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_kmimage_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_kmimage_main_main_default, 255);
	lv_obj_add_style(ui->screen_kmimage, &style_screen_kmimage_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->screen_kmimage, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_kmimage,&kmimage_day);
	lv_img_set_pivot(ui->screen_kmimage, 0,0);
	lv_img_set_angle(ui->screen_kmimage, 0);

	//Write codes screen_day_gear
	ui->screen_day_gear = lv_img_create(ui->screen_day_base_container);
	lv_obj_set_pos(ui->screen_day_gear, 17, 148);
	lv_obj_set_size(ui->screen_day_gear, 10, 24);

	//Write style state: LV_STATE_DEFAULT for style_screen_day_gear_main_main_default
	static lv_style_t style_screen_day_gear_main_main_default;
	lv_style_reset(&style_screen_day_gear_main_main_default);
	lv_style_set_img_recolor(&style_screen_day_gear_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_day_gear_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_day_gear_main_main_default, 255);
	lv_obj_add_style(ui->screen_day_gear, &style_screen_day_gear_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->screen_day_gear, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_day_gear,&_White_gear_10x24);
	lv_img_set_pivot(ui->screen_day_gear, 0,0);
	lv_img_set_angle(ui->screen_day_gear, 0);

	//Write codes screen_day_gear_up
	ui->screen_day_gear_up = lv_img_create(ui->screen_day_base_container);
	lv_obj_set_pos(ui->screen_day_gear_up, 30, 134);
	lv_obj_set_size(ui->screen_day_gear_up, 15, 11);

	//Write style state: LV_STATE_DEFAULT for style_screen_day_gear_up_main_main_default
	static lv_style_t style_screen_day_gear_up_main_main_default;
	lv_style_reset(&style_screen_day_gear_up_main_main_default);
	lv_style_set_img_recolor(&style_screen_day_gear_up_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_day_gear_up_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_day_gear_up_main_main_default, 255);
	lv_obj_add_style(ui->screen_day_gear_up, &style_screen_day_gear_up_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->screen_day_gear_up, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_day_gear_up,&new_day_gear_arrows_up_white);
	lv_img_set_pivot(ui->screen_day_gear_up, 0,0);
	lv_img_set_angle(ui->screen_day_gear_up, 0);

	//Write codes screen_day_gear_down
	ui->screen_day_gear_down = lv_img_create(ui->screen_day_base_container);
	lv_obj_set_pos(ui->screen_day_gear_down, 30, 177);
	lv_obj_set_size(ui->screen_day_gear_down, 15, 11);

	//Write style state: LV_STATE_DEFAULT for style_screen_day_gear_down_main_main_default
	static lv_style_t style_screen_day_gear_down_main_main_default;
	lv_style_reset(&style_screen_day_gear_down_main_main_default);
	lv_style_set_img_recolor(&style_screen_day_gear_down_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_day_gear_down_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_day_gear_down_main_main_default, 255);
	lv_obj_add_style(ui->screen_day_gear_down, &style_screen_day_gear_down_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->screen_day_gear_down, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_day_gear_down,&new_day_gear_arrows_down_white);
	lv_img_set_pivot(ui->screen_day_gear_down, 0,0);
	lv_img_set_angle(ui->screen_day_gear_down, 0);

	//Write codes screen_main_white_container
	ui->screen_main_white_container = lv_obj_create(ui->screen);
	lv_obj_set_pos(ui->screen_main_white_container, 56, 120);
	lv_obj_set_size(ui->screen_main_white_container, 136, 123);

	//Write style state: LV_STATE_DEFAULT for style_screen_main_white_container_main_main_default
	static lv_style_t style_screen_main_white_container_main_main_default;
	lv_style_reset(&style_screen_main_white_container_main_main_default);
	lv_style_set_radius(&style_screen_main_white_container_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_main_white_container_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_screen_main_white_container_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_screen_main_white_container_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_main_white_container_main_main_default, 0);
	lv_style_set_border_color(&style_screen_main_white_container_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_border_width(&style_screen_main_white_container_main_main_default, 0);
	lv_style_set_border_opa(&style_screen_main_white_container_main_main_default, 0);
	lv_style_set_pad_left(&style_screen_main_white_container_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_main_white_container_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_main_white_container_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_main_white_container_main_main_default, 0);
	lv_obj_add_style(ui->screen_main_white_container, &style_screen_main_white_container_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_main_odo_lbl
	ui->screen_main_odo_lbl = lv_label_create(ui->screen_main_white_container);
	lv_obj_set_pos(ui->screen_main_odo_lbl, 38, 99);
	lv_obj_set_size(ui->screen_main_odo_lbl, 69, 19);
	lv_label_set_text(ui->screen_main_odo_lbl, "0");
	lv_label_set_long_mode(ui->screen_main_odo_lbl, LV_LABEL_LONG_WRAP);
	lv_obj_set_style_text_align(ui->screen_main_odo_lbl, LV_TEXT_ALIGN_RIGHT, 0);

	//Write style state: LV_STATE_DEFAULT for style_screen_main_odo_lbl_main_main_default
	static lv_style_t style_screen_main_odo_lbl_main_main_default;
	lv_style_reset(&style_screen_main_odo_lbl_main_main_default);
	lv_style_set_radius(&style_screen_main_odo_lbl_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_main_odo_lbl_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_color(&style_screen_main_odo_lbl_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_dir(&style_screen_main_odo_lbl_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_main_odo_lbl_main_main_default, 0);
	lv_style_set_text_color(&style_screen_main_odo_lbl_main_main_default, lv_color_make(0xff, 0x78, 0x00));
	lv_style_set_text_font(&style_screen_main_odo_lbl_main_main_default, &lv_font_FjallaOne_Regular_22);
	lv_style_set_text_letter_space(&style_screen_main_odo_lbl_main_main_default, 0);
	lv_style_set_pad_left(&style_screen_main_odo_lbl_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_main_odo_lbl_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_main_odo_lbl_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_main_odo_lbl_main_main_default, 0);
	lv_obj_add_style(ui->screen_main_odo_lbl, &style_screen_main_odo_lbl_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_main_odo_img
	ui->screen_main_odo_img = lv_img_create(ui->screen_main_white_container);
	lv_obj_set_pos(ui->screen_main_odo_img, 2, 103);
	lv_obj_set_size(ui->screen_main_odo_img, 27, 14);

	//Write style state: LV_STATE_DEFAULT for style_screen_main_odo_img_main_main_default
	static lv_style_t style_screen_main_odo_img_main_main_default;
	lv_style_reset(&style_screen_main_odo_img_main_main_default);
	lv_style_set_img_recolor(&style_screen_main_odo_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_main_odo_img_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_main_odo_img_main_main_default, 255);
	lv_obj_add_style(ui->screen_main_odo_img, &style_screen_main_odo_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->screen_main_odo_img, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_main_odo_img,&txt_day_odo);
	lv_img_set_pivot(ui->screen_main_odo_img, 0,0);
	lv_img_set_angle(ui->screen_main_odo_img, 0);

	//Write codes screen_main_odo_km
	ui->screen_main_odo_km = lv_img_create(ui->screen_main_white_container);
	lv_obj_set_pos(ui->screen_main_odo_km, 110, 102);
	lv_obj_set_size(ui->screen_main_odo_km, 20, 15);

	//Write style state: LV_STATE_DEFAULT for style_screen_main_odo_km_main_main_default
	static lv_style_t style_screen_main_odo_km_main_main_default;
	lv_style_reset(&style_screen_main_odo_km_main_main_default);
	lv_style_set_img_recolor(&style_screen_main_odo_km_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_main_odo_km_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_main_odo_km_main_main_default, 255);
	lv_obj_add_style(ui->screen_main_odo_km, &style_screen_main_odo_km_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->screen_main_odo_km, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_main_odo_km,&txt_day_odo_unit);
	lv_img_set_pivot(ui->screen_main_odo_km, 0,0);
	lv_img_set_angle(ui->screen_main_odo_km, 0);

	//Write codes screen_main_sc_3
	ui->screen_main_sc_3 = lv_img_create(ui->screen_main_white_container);
	lv_obj_set_pos(ui->screen_main_sc_3, 2, 3);
	lv_obj_set_size(ui->screen_main_sc_3, 41, 73);

	//Write style state: LV_STATE_DEFAULT for style_screen_main_sc_3_main_main_default
	static lv_style_t style_screen_main_sc_3_main_main_default;
	lv_style_reset(&style_screen_main_sc_3_main_main_default);
	lv_style_set_img_recolor(&style_screen_main_sc_3_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_main_sc_3_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_main_sc_3_main_main_default, 255);
	lv_obj_add_style(ui->screen_main_sc_3, &style_screen_main_sc_3_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->screen_main_sc_3, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_main_sc_3,&txt_day_speed_line_3_grey0);
	lv_img_set_pivot(ui->screen_main_sc_3, 0,0);
	lv_img_set_angle(ui->screen_main_sc_3, 0);

	//Write codes screen_main_sc_2
	ui->screen_main_sc_2 = lv_img_create(ui->screen_main_white_container);
	lv_obj_set_pos(ui->screen_main_sc_2, 43, 3);
	lv_obj_set_size(ui->screen_main_sc_2, 41, 73);

	//Write style state: LV_STATE_DEFAULT for style_screen_main_sc_2_main_main_default
	static lv_style_t style_screen_main_sc_2_main_main_default;
	lv_style_reset(&style_screen_main_sc_2_main_main_default);
	lv_style_set_img_recolor(&style_screen_main_sc_2_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_main_sc_2_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_main_sc_2_main_main_default, 255);
	lv_obj_add_style(ui->screen_main_sc_2, &style_screen_main_sc_2_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->screen_main_sc_2, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_main_sc_2,&txt_day_speed_line_3_grey0);
	lv_img_set_pivot(ui->screen_main_sc_2, 0,0);
	lv_img_set_angle(ui->screen_main_sc_2, 0);

	//Write codes screen_main_sc_1
	ui->screen_main_sc_1 = lv_img_create(ui->screen_main_white_container);
	lv_obj_set_pos(ui->screen_main_sc_1, 85, 3);
	lv_obj_set_size(ui->screen_main_sc_1, 41, 73);

	//Write style state: LV_STATE_DEFAULT for style_screen_main_sc_1_main_main_default
	static lv_style_t style_screen_main_sc_1_main_main_default;
	lv_style_reset(&style_screen_main_sc_1_main_main_default);
	lv_style_set_img_recolor(&style_screen_main_sc_1_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_main_sc_1_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_main_sc_1_main_main_default, 255);
	lv_obj_add_style(ui->screen_main_sc_1, &style_screen_main_sc_1_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->screen_main_sc_1, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_main_sc_1,&txt_day_speed_line_3_white0);
	lv_img_set_pivot(ui->screen_main_sc_1, 0,0);
	lv_img_set_angle(ui->screen_main_sc_1, 0);

	//Write codes screen_day_trip_con
	ui->screen_day_trip_con = lv_obj_create(ui->screen);
	lv_obj_set_pos(ui->screen_day_trip_con, 30, 167);
	lv_obj_set_size(ui->screen_day_trip_con, 195, 78);

	//Write style state: LV_STATE_DEFAULT for style_screen_day_trip_con_main_main_default
	static lv_style_t style_screen_day_trip_con_main_main_default;
	lv_style_reset(&style_screen_day_trip_con_main_main_default);
	lv_style_set_radius(&style_screen_day_trip_con_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_day_trip_con_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_color(&style_screen_day_trip_con_main_main_default, lv_color_make(0x08, 0x08, 0x08));
	lv_style_set_bg_grad_dir(&style_screen_day_trip_con_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_day_trip_con_main_main_default, 0);
	lv_style_set_border_color(&style_screen_day_trip_con_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_border_width(&style_screen_day_trip_con_main_main_default, 0);
	lv_style_set_border_opa(&style_screen_day_trip_con_main_main_default, 0);
	lv_style_set_pad_left(&style_screen_day_trip_con_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_day_trip_con_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_day_trip_con_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_day_trip_con_main_main_default, 0);
	lv_obj_add_style(ui->screen_day_trip_con, &style_screen_day_trip_con_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);


	//Write codes screen_day_Trip_up_arr
	ui->screen_day_Trip_up_arr = lv_img_create(ui->screen_day_trip_con);
	lv_obj_set_pos(ui->screen_day_Trip_up_arr, 80, 4);
	lv_obj_set_size(ui->screen_day_Trip_up_arr, 14, 9);

	//Write style state: LV_STATE_DEFAULT for style_screen_day_trip_up_arr_main_main_default
	static lv_style_t style_screen_day_trip_up_arr_main_main_default;
	lv_style_reset(&style_screen_day_trip_up_arr_main_main_default);
	lv_style_set_img_recolor(&style_screen_day_trip_up_arr_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_day_trip_up_arr_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_day_trip_up_arr_main_main_default, 255);
	lv_obj_add_style(ui->screen_day_Trip_up_arr, &style_screen_day_trip_up_arr_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_day_Trip_down_arr
	ui->screen_day_Trip_down_arr = lv_img_create(ui->screen_day_trip_con);
	lv_obj_set_pos(ui->screen_day_Trip_down_arr, 80, 68);
	lv_obj_set_size(ui->screen_day_Trip_down_arr, 14, 9);

	//Write style state: LV_STATE_DEFAULT for style_screen_day_trip_down_arr_main_main_default
	static lv_style_t style_screen_day_trip_down_arr_main_main_default;
	lv_style_reset(&style_screen_day_trip_down_arr_main_main_default);
	lv_style_set_img_recolor(&style_screen_day_trip_down_arr_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_day_trip_down_arr_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_day_trip_down_arr_main_main_default, 255);
	lv_obj_add_style(ui->screen_day_Trip_down_arr, &style_screen_day_trip_down_arr_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_day_lbl1
	ui->screen_day_lbl1 = lv_label_create(ui->screen_day_trip_con);
	lv_obj_set_pos(ui->screen_day_lbl1, 37, 15);
	lv_obj_set_size(ui->screen_day_lbl1, 26, 21);
	lv_label_set_text(ui->screen_day_lbl1, "Trip");
	lv_label_set_long_mode(ui->screen_day_lbl1, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->screen_day_lbl1, LV_TEXT_ALIGN_LEFT, 0);

	//Write style state: LV_STATE_DEFAULT for style_screen_day_lbl1_main_main_default
	static lv_style_t style_screen_day_lbl1_main_main_default;
	lv_style_reset(&style_screen_day_lbl1_main_main_default);
	lv_style_set_radius(&style_screen_day_lbl1_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_day_lbl1_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_day_lbl1_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_day_lbl1_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_day_lbl1_main_main_default, 0);
	lv_style_set_text_color(&style_screen_day_lbl1_main_main_default, lv_color_make(0xff, 0x78, 0x00));
	lv_style_set_text_font(&style_screen_day_lbl1_main_main_default, &lv_font_FjallaOne_Regular_17);
	lv_style_set_text_letter_space(&style_screen_day_lbl1_main_main_default, 0);
	lv_style_set_pad_left(&style_screen_day_lbl1_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_day_lbl1_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_day_lbl1_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_day_lbl1_main_main_default, 0);
	lv_obj_add_style(ui->screen_day_lbl1, &style_screen_day_lbl1_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_day_lbl2
	ui->screen_day_lbl2 = lv_label_create(ui->screen_day_trip_con);
	lv_obj_set_pos(ui->screen_day_lbl2, 71, 14);
	lv_obj_set_size(ui->screen_day_lbl2, 49, 18);
	lv_label_set_text(ui->screen_day_lbl2, "999.9");
	lv_label_set_long_mode(ui->screen_day_lbl2, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->screen_day_lbl2, LV_TEXT_ALIGN_LEFT, 0);

	//Write style state: LV_STATE_DEFAULT for style_screen_day_lbl2_main_main_default
	static lv_style_t style_screen_day_lbl2_main_main_default;
	lv_style_reset(&style_screen_day_lbl2_main_main_default);
	lv_style_set_radius(&style_screen_day_lbl2_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_day_lbl2_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_day_lbl2_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_day_lbl2_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_day_lbl2_main_main_default, 0);
	lv_style_set_text_color(&style_screen_day_lbl2_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_screen_day_lbl2_main_main_default, &lv_font_FjallaOne_Regular_22);
	lv_style_set_text_letter_space(&style_screen_day_lbl2_main_main_default, 0);
	lv_style_set_pad_left(&style_screen_day_lbl2_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_day_lbl2_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_day_lbl2_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_day_lbl2_main_main_default, 0);
	lv_obj_add_style(ui->screen_day_lbl2, &style_screen_day_lbl2_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_day_lbl3
	ui->screen_day_lbl3 = lv_label_create(ui->screen_day_trip_con);
	lv_obj_set_pos(ui->screen_day_lbl3, 124, 16);
	lv_obj_set_size(ui->screen_day_lbl3, 56, 19);
	lv_label_set_text(ui->screen_day_lbl3, "L/100km");
	lv_label_set_long_mode(ui->screen_day_lbl3, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->screen_day_lbl3, LV_TEXT_ALIGN_LEFT, 0);

	//Write style state: LV_STATE_DEFAULT for style_screen_day_lbl3_main_main_default
	static lv_style_t style_screen_day_lbl3_main_main_default;
	lv_style_reset(&style_screen_day_lbl3_main_main_default);
	lv_style_set_radius(&style_screen_day_lbl3_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_day_lbl3_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_day_lbl3_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_day_lbl3_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_day_lbl3_main_main_default, 0);
	lv_style_set_text_color(&style_screen_day_lbl3_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_screen_day_lbl3_main_main_default, &lv_font_FjallaOne_Regular_17);
	lv_style_set_text_letter_space(&style_screen_day_lbl3_main_main_default, 0);
	lv_style_set_pad_left(&style_screen_day_lbl3_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_day_lbl3_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_day_lbl3_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_day_lbl3_main_main_default, 0);
	lv_obj_add_style(ui->screen_day_lbl3, &style_screen_day_lbl3_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_day_lbl4
	ui->screen_day_lbl4 = lv_label_create(ui->screen_day_trip_con);
	lv_obj_set_pos(ui->screen_day_lbl4, 34, 43);
	lv_obj_set_size(ui->screen_day_lbl4, 33, 21);
	lv_label_set_text(ui->screen_day_lbl4, "Time");
	lv_label_set_long_mode(ui->screen_day_lbl4, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->screen_day_lbl4, LV_TEXT_ALIGN_RIGHT, 0);

	//Write style state: LV_STATE_DEFAULT for style_screen_day_lbl4_main_main_default
	static lv_style_t style_screen_day_lbl4_main_main_default;
	lv_style_reset(&style_screen_day_lbl4_main_main_default);
	lv_style_set_radius(&style_screen_day_lbl4_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_day_lbl4_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_day_lbl4_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_day_lbl4_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_day_lbl4_main_main_default, 0);
	lv_style_set_text_color(&style_screen_day_lbl4_main_main_default, lv_color_make(0xff, 0x78, 0x00));
	lv_style_set_text_font(&style_screen_day_lbl4_main_main_default, &lv_font_FjallaOne_Regular_17);
	lv_style_set_text_letter_space(&style_screen_day_lbl4_main_main_default, 0);
	lv_style_set_pad_left(&style_screen_day_lbl4_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_day_lbl4_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_day_lbl4_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_day_lbl4_main_main_default, 0);
	lv_obj_add_style(ui->screen_day_lbl4, &style_screen_day_lbl4_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_day_lbl5
	ui->screen_day_lbl5 = lv_label_create(ui->screen_day_trip_con);
	lv_obj_set_pos(ui->screen_day_lbl5, 71, 42);
	lv_obj_set_size(ui->screen_day_lbl5, 21, 18);
	lv_label_set_text(ui->screen_day_lbl5, "99");
	lv_label_set_long_mode(ui->screen_day_lbl5, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->screen_day_lbl5, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_screen_day_lbl5_main_main_default
	static lv_style_t style_screen_day_lbl5_main_main_default;
	lv_style_reset(&style_screen_day_lbl5_main_main_default);
	lv_style_set_radius(&style_screen_day_lbl5_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_day_lbl5_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_day_lbl5_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_day_lbl5_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_day_lbl5_main_main_default, 0);
	lv_style_set_text_color(&style_screen_day_lbl5_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_screen_day_lbl5_main_main_default, &lv_font_FjallaOne_Regular_22);
	lv_style_set_text_letter_space(&style_screen_day_lbl5_main_main_default, 0);
	lv_style_set_pad_left(&style_screen_day_lbl5_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_day_lbl5_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_day_lbl5_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_day_lbl5_main_main_default, 0);
	lv_obj_add_style(ui->screen_day_lbl5, &style_screen_day_lbl5_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_day_lbl_6
	ui->screen_day_lbl_6 = lv_label_create(ui->screen_day_trip_con);
	lv_obj_set_pos(ui->screen_day_lbl_6, 98, 44);
	lv_obj_set_size(ui->screen_day_lbl_6, 11, 12);
	lv_label_set_text(ui->screen_day_lbl_6, "h");
	lv_label_set_long_mode(ui->screen_day_lbl_6, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->screen_day_lbl_6, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_screen_day_lbl_6_main_main_default
	static lv_style_t style_screen_day_lbl_6_main_main_default;
	lv_style_reset(&style_screen_day_lbl_6_main_main_default);
	lv_style_set_radius(&style_screen_day_lbl_6_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_day_lbl_6_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_day_lbl_6_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_day_lbl_6_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_day_lbl_6_main_main_default, 0);
	lv_style_set_text_color(&style_screen_day_lbl_6_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_screen_day_lbl_6_main_main_default, &lv_font_FjallaOne_Regular_17);
	lv_style_set_text_letter_space(&style_screen_day_lbl_6_main_main_default, 0);
	lv_style_set_pad_left(&style_screen_day_lbl_6_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_day_lbl_6_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_day_lbl_6_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_day_lbl_6_main_main_default, 0);
	lv_obj_add_style(ui->screen_day_lbl_6, &style_screen_day_lbl_6_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_day_lbl_7
	ui->screen_day_lbl_7 = lv_label_create(ui->screen_day_trip_con);
	lv_obj_set_pos(ui->screen_day_lbl_7, 109, 42);
	lv_obj_set_size(ui->screen_day_lbl_7, 21, 18);
	lv_label_set_text(ui->screen_day_lbl_7, "99");
	lv_label_set_long_mode(ui->screen_day_lbl_7, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->screen_day_lbl_7, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_screen_day_lbl_7_main_main_default
	static lv_style_t style_screen_day_lbl_7_main_main_default;
	lv_style_reset(&style_screen_day_lbl_7_main_main_default);
	lv_style_set_radius(&style_screen_day_lbl_7_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_day_lbl_7_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_day_lbl_7_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_day_lbl_7_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_day_lbl_7_main_main_default, 0);
	lv_style_set_text_color(&style_screen_day_lbl_7_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_screen_day_lbl_7_main_main_default, &lv_font_FjallaOne_Regular_22);
	lv_style_set_text_letter_space(&style_screen_day_lbl_7_main_main_default, 0);
	lv_style_set_pad_left(&style_screen_day_lbl_7_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_day_lbl_7_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_day_lbl_7_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_day_lbl_7_main_main_default, 0);
	lv_obj_add_style(ui->screen_day_lbl_7, &style_screen_day_lbl_7_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_day_lbl_8
	ui->screen_day_lbl_8 = lv_label_create(ui->screen_day_trip_con);
	lv_obj_set_pos(ui->screen_day_lbl_8, 135, 44);
	lv_obj_set_size(ui->screen_day_lbl_8, 12, 12);
	lv_label_set_text(ui->screen_day_lbl_8, "m");
	lv_label_set_long_mode(ui->screen_day_lbl_8, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->screen_day_lbl_8, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_screen_day_lbl_8_main_main_default
	static lv_style_t style_screen_day_lbl_8_main_main_default;
	lv_style_reset(&style_screen_day_lbl_8_main_main_default);
	lv_style_set_radius(&style_screen_day_lbl_8_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_day_lbl_8_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_day_lbl_8_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_day_lbl_8_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_day_lbl_8_main_main_default, 0);
	lv_style_set_text_color(&style_screen_day_lbl_8_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_screen_day_lbl_8_main_main_default, &lv_font_FjallaOne_Regular_17);
	lv_style_set_text_letter_space(&style_screen_day_lbl_8_main_main_default, 0);
	lv_style_set_pad_left(&style_screen_day_lbl_8_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_day_lbl_8_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_day_lbl_8_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_day_lbl_8_main_main_default, 0);
	lv_obj_add_style(ui->screen_day_lbl_8, &style_screen_day_lbl_8_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_dat_inter_con
	ui->screen_dat_inter_con = lv_obj_create(ui->screen);
	lv_obj_set_pos(ui->screen_dat_inter_con, 57, 97);
	lv_obj_set_size(ui->screen_dat_inter_con, 160, 67);

	//Write style state: LV_STATE_DEFAULT for style_screen_dat_inter_con_main_main_default
	static lv_style_t style_screen_dat_inter_con_main_main_default;
	lv_style_reset(&style_screen_dat_inter_con_main_main_default);
	lv_style_set_radius(&style_screen_dat_inter_con_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_dat_inter_con_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_screen_dat_inter_con_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_screen_dat_inter_con_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_dat_inter_con_main_main_default, 0);
	lv_style_set_border_color(&style_screen_dat_inter_con_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_border_width(&style_screen_dat_inter_con_main_main_default, 0);
	lv_style_set_border_opa(&style_screen_dat_inter_con_main_main_default, 0);
	lv_style_set_pad_left(&style_screen_dat_inter_con_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_dat_inter_con_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_dat_inter_con_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_dat_inter_con_main_main_default, 0);
	lv_obj_add_style(ui->screen_dat_inter_con, &style_screen_dat_inter_con_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_day_in_unit
	ui->screen_day_in_unit = lv_label_create(ui->screen_dat_inter_con);
	lv_obj_set_pos(ui->screen_day_in_unit, 104, 35);
	lv_obj_set_size(ui->screen_day_in_unit, 28, 15);
	lv_label_set_text(ui->screen_day_in_unit, "km/h");
	lv_label_set_long_mode(ui->screen_day_in_unit, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->screen_day_in_unit, LV_TEXT_ALIGN_LEFT, 0);

	//Write style state: LV_STATE_DEFAULT for style_screen_day_in_unit_main_main_default
	static lv_style_t style_screen_day_in_unit_main_main_default;
	lv_style_reset(&style_screen_day_in_unit_main_main_default);
	lv_style_set_radius(&style_screen_day_in_unit_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_day_in_unit_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_day_in_unit_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_day_in_unit_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_day_in_unit_main_main_default, 0);
	lv_style_set_text_color(&style_screen_day_in_unit_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_screen_day_in_unit_main_main_default, &lv_font_FjallaOne_Regular_11);
	lv_style_set_text_letter_space(&style_screen_day_in_unit_main_main_default, 0);
	lv_style_set_pad_left(&style_screen_day_in_unit_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_day_in_unit_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_day_in_unit_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_day_in_unit_main_main_default, 0);
	lv_obj_add_style(ui->screen_day_in_unit, &style_screen_day_in_unit_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->screen_day_in_unit,LV_OBJ_FLAG_HIDDEN);

	//Write codes screen_day_km_unit_Img
	ui->screen_day_km_unit_Img = lv_img_create(ui->screen_dat_inter_con);
	lv_obj_set_pos(ui->screen_day_km_unit_Img, 108, 33);
	lv_obj_set_size(ui->screen_day_km_unit_Img, 27, 16);

	//Write style state: LV_STATE_DEFAULT for style_screen_day_km_unit_img_main_main_default
	static lv_style_t style_screen_day_km_unit_img_main_main_default;
	lv_style_reset(&style_screen_day_km_unit_img_main_main_default);
	lv_style_set_img_recolor(&style_screen_day_km_unit_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_day_km_unit_img_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_day_km_unit_img_main_main_default, 255);
	lv_obj_add_style(ui->screen_day_km_unit_Img, &style_screen_day_km_unit_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_img_set_src(ui->screen_day_km_unit_Img,&km_text_unit_day_Img);

	//Write codes screen_day_line_img
	ui->screen_day_line_img = lv_img_create(ui->screen_dat_inter_con);
	lv_obj_set_pos(ui->screen_day_line_img, 0, 61);
	lv_obj_set_size(ui->screen_day_line_img, 134, 2);

	//Write style state: LV_STATE_DEFAULT for style_screen_day_line_img_main_main_default
	static lv_style_t style_screen_day_line_img_main_main_default;
	lv_style_reset(&style_screen_day_line_img_main_main_default);
	lv_style_set_img_recolor(&style_screen_day_line_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_day_line_img_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_day_line_img_main_main_default, 255);
	lv_obj_add_style(ui->screen_day_line_img, &style_screen_day_line_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->screen_day_line_img, LV_OBJ_FLAG_CLICKABLE);
	//lv_img_set_src(ui->screen_day_line_img,&_night_slider_orange_134x2);
	lv_img_set_pivot(ui->screen_day_line_img, 0,0);
	lv_img_set_angle(ui->screen_day_line_img, 0);

	//Write codes screen_day_in_sc1
	ui->screen_day_in_sc1 = lv_img_create(ui->screen_dat_inter_con);
	lv_obj_set_pos(ui->screen_day_in_sc1, 76, 2);
	lv_obj_set_size(ui->screen_day_in_sc1, 27, 47);

	//Write style state: LV_STATE_DEFAULT for style_screen_day_in_sc1_main_main_default
	static lv_style_t style_screen_day_in_sc1_main_main_default;
	lv_style_reset(&style_screen_day_in_sc1_main_main_default);
	lv_style_set_img_recolor(&style_screen_day_in_sc1_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_day_in_sc1_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_day_in_sc1_main_main_default, 255);
	lv_obj_add_style(ui->screen_day_in_sc1, &style_screen_day_in_sc1_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->screen_day_in_sc1, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_day_in_sc1,&black0_24x47);
	lv_img_set_pivot(ui->screen_day_in_sc1, 0,0);
	lv_img_set_angle(ui->screen_day_in_sc1, 0);
	lv_obj_set_style_img_opa(ui->screen_day_in_sc1, 255, 0);
	lv_obj_set_style_img_recolor(ui->screen_day_in_sc1, lv_color_black(), 0);

	//Write codes screen_day_in_sc2
	ui->screen_day_in_sc2 = lv_img_create(ui->screen_dat_inter_con);
	lv_obj_set_pos(ui->screen_day_in_sc2, 46, 2);
	lv_obj_set_size(ui->screen_day_in_sc2, 27, 47);

	//Write style state: LV_STATE_DEFAULT for style_screen_day_in_sc2_main_main_default
	static lv_style_t style_screen_day_in_sc2_main_main_default;
	lv_style_reset(&style_screen_day_in_sc2_main_main_default);
	lv_style_set_img_recolor(&style_screen_day_in_sc2_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_day_in_sc2_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_day_in_sc2_main_main_default, 255);
	lv_obj_add_style(ui->screen_day_in_sc2, &style_screen_day_in_sc2_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->screen_day_in_sc2, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_day_in_sc2,&black0_24x47);
	lv_img_set_pivot(ui->screen_day_in_sc2, 0,0);
	lv_img_set_angle(ui->screen_day_in_sc2, 0);
	lv_obj_set_style_img_opa(ui->screen_day_in_sc2, 255, 0);
	lv_obj_set_style_img_recolor(ui->screen_day_in_sc2, lv_color_Day_Grey(), 0);
	set_obj_opa(ui->screen_day_in_sc2, 50);

	//Write codes screen_day_in_sc3
	ui->screen_day_in_sc3 = lv_img_create(ui->screen_dat_inter_con);
	lv_obj_set_pos(ui->screen_day_in_sc3, 17, 2);
	lv_obj_set_size(ui->screen_day_in_sc3, 27, 47);

	//Write style state: LV_STATE_DEFAULT for style_screen_day_in_sc3_main_main_default
	static lv_style_t style_screen_day_in_sc3_main_main_default;
	lv_style_reset(&style_screen_day_in_sc3_main_main_default);
	lv_style_set_img_recolor(&style_screen_day_in_sc3_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_day_in_sc3_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_day_in_sc3_main_main_default, 255);
	lv_obj_add_style(ui->screen_day_in_sc3, &style_screen_day_in_sc3_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->screen_day_in_sc3, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_day_in_sc3,&black0_24x47);
	lv_img_set_pivot(ui->screen_day_in_sc3, 0,0);
	lv_img_set_angle(ui->screen_day_in_sc3, 0);
	lv_obj_set_style_img_opa(ui->screen_day_in_sc3, 255, 0);
	lv_obj_set_style_img_recolor(ui->screen_day_in_sc3, lv_color_Day_Grey(), 0);
	set_obj_opa(ui->screen_day_in_sc3, 50);

	//Write codes screen_day_inter_con2
	ui->screen_day_inter_con2 = lv_obj_create(ui->screen);
	lv_obj_set_pos(ui->screen_day_inter_con2, 30, 167);
	lv_obj_set_size(ui->screen_day_inter_con2, 210, 78);

	//Write style state: LV_STATE_DEFAULT for style_screen_day_inter_con2_main_main_default
	static lv_style_t style_screen_day_inter_con2_main_main_default;
	lv_style_reset(&style_screen_day_inter_con2_main_main_default);
	lv_style_set_radius(&style_screen_day_inter_con2_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_day_inter_con2_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_color(&style_screen_day_inter_con2_main_main_default, lv_color_make(0x08, 0x08, 0x08));
	lv_style_set_bg_grad_dir(&style_screen_day_inter_con2_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_day_inter_con2_main_main_default, 0);
	lv_style_set_border_color(&style_screen_day_inter_con2_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_border_width(&style_screen_day_inter_con2_main_main_default, 0);
	lv_style_set_border_opa(&style_screen_day_inter_con2_main_main_default, 0);
	lv_style_set_pad_left(&style_screen_day_inter_con2_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_day_inter_con2_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_day_inter_con2_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_day_inter_con2_main_main_default, 0);
	lv_obj_add_style(ui->screen_day_inter_con2, &style_screen_day_inter_con2_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_day_in_lb1
	ui->screen_day_in_lb1 = lv_label_create(ui->screen_day_inter_con2);
	lv_obj_set_pos(ui->screen_day_in_lb1, 0, 21);
	lv_obj_set_size(ui->screen_day_in_lb1, 79, 17);
	lv_label_set_text(ui->screen_day_in_lb1, "Av Speed");
	lv_label_set_long_mode(ui->screen_day_in_lb1, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->screen_day_in_lb1, LV_TEXT_ALIGN_RIGHT, 0);

	//Write style state: LV_STATE_DEFAULT for style_screen_day_in_lb1_main_main_default
	static lv_style_t style_screen_day_in_lb1_main_main_default;
	lv_style_reset(&style_screen_day_in_lb1_main_main_default);
	lv_style_set_radius(&style_screen_day_in_lb1_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_day_in_lb1_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_day_in_lb1_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_day_in_lb1_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_day_in_lb1_main_main_default, 0);
	lv_style_set_text_color(&style_screen_day_in_lb1_main_main_default, lv_color_make(0xff, 0x78, 0x00));
	lv_style_set_text_font(&style_screen_day_in_lb1_main_main_default, &lv_font_FjallaOne_Regular_17);
	lv_style_set_text_letter_space(&style_screen_day_in_lb1_main_main_default, 0);
	lv_style_set_pad_left(&style_screen_day_in_lb1_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_day_in_lb1_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_day_in_lb1_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_day_in_lb1_main_main_default, 0);
	lv_obj_add_style(ui->screen_day_in_lb1, &style_screen_day_in_lb1_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_day_in_lb2
	ui->screen_day_in_lb2 = lv_label_create(ui->screen_day_inter_con2);
	lv_obj_set_pos(ui->screen_day_in_lb2, 81, 18);
	lv_obj_set_size(ui->screen_day_in_lb2, 48, 18);
	lv_label_set_text(ui->screen_day_in_lb2, "123.9");
	lv_label_set_long_mode(ui->screen_day_in_lb2, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->screen_day_in_lb2, LV_TEXT_ALIGN_RIGHT, 0);

	//Write style state: LV_STATE_DEFAULT for style_screen_day_in_lb2_main_main_default
	static lv_style_t style_screen_day_in_lb2_main_main_default;
	lv_style_reset(&style_screen_day_in_lb2_main_main_default);
	lv_style_set_radius(&style_screen_day_in_lb2_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_day_in_lb2_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_day_in_lb2_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_day_in_lb2_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_day_in_lb2_main_main_default, 0);
	lv_style_set_text_color(&style_screen_day_in_lb2_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_screen_day_in_lb2_main_main_default, &lv_font_FjallaOne_Regular_22);
	lv_style_set_text_letter_space(&style_screen_day_in_lb2_main_main_default, 0);
	lv_style_set_pad_left(&style_screen_day_in_lb2_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_day_in_lb2_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_day_in_lb2_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_day_in_lb2_main_main_default, 0);
	lv_obj_add_style(ui->screen_day_in_lb2, &style_screen_day_in_lb2_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_day_in_lb3
	ui->screen_day_in_lb3 = lv_label_create(ui->screen_day_inter_con2);
	lv_obj_set_pos(ui->screen_day_in_lb3, 131, 21);
	lv_obj_set_size(ui->screen_day_in_lb3, 56, 19);
	lv_label_set_text(ui->screen_day_in_lb3, "L/100km");
	lv_label_set_long_mode(ui->screen_day_in_lb3, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->screen_day_in_lb3, LV_TEXT_ALIGN_LEFT, 0);

	//Write style state: LV_STATE_DEFAULT for style_screen_day_in_lb3_main_main_default
	static lv_style_t style_screen_day_in_lb3_main_main_default;
	lv_style_reset(&style_screen_day_in_lb3_main_main_default);
	lv_style_set_radius(&style_screen_day_in_lb3_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_day_in_lb3_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_day_in_lb3_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_day_in_lb3_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_day_in_lb3_main_main_default, 0);
	lv_style_set_text_color(&style_screen_day_in_lb3_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_screen_day_in_lb3_main_main_default, &lv_font_FjallaOne_Regular_17);
	lv_style_set_text_letter_space(&style_screen_day_in_lb3_main_main_default, 0);
	lv_style_set_pad_left(&style_screen_day_in_lb3_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_day_in_lb3_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_day_in_lb3_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_day_in_lb3_main_main_default, 0);
	lv_obj_add_style(ui->screen_day_in_lb3, &style_screen_day_in_lb3_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_day_in_lb4
	ui->screen_day_in_lb4 = lv_label_create(ui->screen_day_inter_con2);
	lv_obj_set_pos(ui->screen_day_in_lb4, 0, 47);
	lv_obj_set_size(ui->screen_day_in_lb4, 79, 17);
	lv_label_set_text(ui->screen_day_in_lb4, "Service Due");
	lv_label_set_long_mode(ui->screen_day_in_lb4, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->screen_day_in_lb4, LV_TEXT_ALIGN_RIGHT, 0);

	//Write style state: LV_STATE_DEFAULT for style_screen_day_in_lb4_main_main_default
	static lv_style_t style_screen_day_in_lb4_main_main_default;
	lv_style_reset(&style_screen_day_in_lb4_main_main_default);
	lv_style_set_radius(&style_screen_day_in_lb4_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_day_in_lb4_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_day_in_lb4_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_day_in_lb4_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_day_in_lb4_main_main_default, 0);
	lv_style_set_text_color(&style_screen_day_in_lb4_main_main_default, lv_color_make(0xff, 0x78, 0x00));
	lv_style_set_text_font(&style_screen_day_in_lb4_main_main_default, &lv_font_FjallaOne_Regular_17);
	lv_style_set_text_letter_space(&style_screen_day_in_lb4_main_main_default, 0);
	lv_style_set_pad_left(&style_screen_day_in_lb4_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_day_in_lb4_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_day_in_lb4_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_day_in_lb4_main_main_default, 0);
	lv_obj_add_style(ui->screen_day_in_lb4, &style_screen_day_in_lb4_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_day_in_lb5
	ui->screen_day_in_lb5 = lv_label_create(ui->screen_day_inter_con2);
	lv_obj_set_pos(ui->screen_day_in_lb5, 81, 45);
	lv_obj_set_size(ui->screen_day_in_lb5, 104, 18);
	lv_label_set_text(ui->screen_day_in_lb5, "00 h 00m");
	lv_label_set_long_mode(ui->screen_day_in_lb5, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->screen_day_in_lb5, LV_TEXT_ALIGN_RIGHT, 0);

	//Write style state: LV_STATE_DEFAULT for style_screen_day_in_lb5_main_main_default
	static lv_style_t style_screen_day_in_lb5_main_main_default;
	lv_style_reset(&style_screen_day_in_lb5_main_main_default);
	lv_style_set_radius(&style_screen_day_in_lb5_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_day_in_lb5_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_day_in_lb5_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_day_in_lb5_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_day_in_lb5_main_main_default, 0);
	lv_style_set_text_color(&style_screen_day_in_lb5_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_screen_day_in_lb5_main_main_default, &lv_font_FjallaOne_Regular_22);
	lv_style_set_text_letter_space(&style_screen_day_in_lb5_main_main_default, 0);
	lv_style_set_pad_left(&style_screen_day_in_lb5_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_day_in_lb5_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_day_in_lb5_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_day_in_lb5_main_main_default, 0);
	lv_obj_add_style(ui->screen_day_in_lb5, &style_screen_day_in_lb5_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_day_in_lb6
	ui->screen_day_in_lb6 = lv_label_create(ui->screen_day_inter_con2);
	lv_obj_set_pos(ui->screen_day_in_lb6, 131, 46);
	lv_obj_set_size(ui->screen_day_in_lb6, 56, 19);
	lv_label_set_text(ui->screen_day_in_lb6, "L/100km");
	lv_label_set_long_mode(ui->screen_day_in_lb6, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->screen_day_in_lb6, LV_TEXT_ALIGN_LEFT, 0);

	//Write style state: LV_STATE_DEFAULT for style_screen_day_in_lb6_main_main_default
	static lv_style_t style_screen_day_in_lb6_main_main_default;
	lv_style_reset(&style_screen_day_in_lb6_main_main_default);
	lv_style_set_radius(&style_screen_day_in_lb6_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_day_in_lb6_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_day_in_lb6_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_day_in_lb6_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_day_in_lb6_main_main_default, 0);
	lv_style_set_text_color(&style_screen_day_in_lb6_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_screen_day_in_lb6_main_main_default, &lv_font_FjallaOne_Regular_17);
	lv_style_set_text_letter_space(&style_screen_day_in_lb6_main_main_default, 0);
	lv_style_set_pad_left(&style_screen_day_in_lb6_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_day_in_lb6_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_day_in_lb6_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_day_in_lb6_main_main_default, 0);
	lv_obj_add_style(ui->screen_day_in_lb6, &style_screen_day_in_lb6_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_day_in_arr1
	ui->screen_day_in_arr1 = lv_img_create(ui->screen_day_inter_con2);
	lv_obj_set_pos(ui->screen_day_in_arr1, 80, 4);
	lv_obj_set_size(ui->screen_day_in_arr1, 14, 9);

	//Write style state: LV_STATE_DEFAULT for style_screen_day_in_arr1_main_main_default
	static lv_style_t style_screen_day_in_arr1_main_main_default;
	lv_style_reset(&style_screen_day_in_arr1_main_main_default);
	lv_style_set_img_recolor(&style_screen_day_in_arr1_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_day_in_arr1_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_day_in_arr1_main_main_default, 255);
	lv_obj_add_style(ui->screen_day_in_arr1, &style_screen_day_in_arr1_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->screen_day_in_arr1, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_day_in_arr1,&new_day_trip_up_arrow_normal);
	lv_img_set_pivot(ui->screen_day_in_arr1, 0,0);
	lv_img_set_angle(ui->screen_day_in_arr1, 0);

		//Write codes screen_day_in_arr2
	ui->screen_day_in_arr2 = lv_img_create(ui->screen_day_inter_con2);
	lv_obj_set_pos(ui->screen_day_in_arr2, 80, 68);
	lv_obj_set_size(ui->screen_day_in_arr2, 14, 9);

	//Write style state: LV_STATE_DEFAULT for style_screen_day_in_arr2_main_main_default
	static lv_style_t style_screen_day_in_arr2_main_main_default;
	lv_style_reset(&style_screen_day_in_arr2_main_main_default);
	lv_style_set_img_recolor(&style_screen_day_in_arr2_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_day_in_arr2_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_day_in_arr2_main_main_default, 255);
	lv_obj_add_style(ui->screen_day_in_arr2, &style_screen_day_in_arr2_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->screen_day_in_arr2, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_day_in_arr2,&new_day_trip_down_arrow_normal);
	lv_img_set_pivot(ui->screen_day_in_arr2, 0,0);
	lv_img_set_angle(ui->screen_day_in_arr2, 0);

	//Write codes screen_day_in_lb8
	ui->screen_day_in_lb8 = lv_img_create(ui->screen_day_inter_con2);
	lv_obj_set_pos(ui->screen_day_in_lb8, 82, 70);
	lv_obj_set_size(ui->screen_day_in_lb8, 12, 7);

	//Write style state: LV_STATE_DEFAULT for style_screen_day_in_lb8_main_main_default
	static lv_style_t style_screen_day_in_lb8_main_main_default;
	lv_style_reset(&style_screen_day_in_lb8_main_main_default);
	lv_style_set_img_recolor(&style_screen_day_in_lb8_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_day_in_lb8_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_day_in_lb8_main_main_default, 0);
	lv_obj_add_style(ui->screen_day_in_lb8, &style_screen_day_in_lb8_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->screen_day_in_lb8, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_day_in_lb8,&new_day_trip_down_arrow_normal);
	lv_img_set_pivot(ui->screen_day_in_lb8, 0,0);
	lv_img_set_angle(ui->screen_day_in_lb8, 0);

	//Write codes screen_Main_day_music_container
	ui->screen_Main_day_music_container = lv_obj_create(ui->screen);
	lv_obj_set_pos(ui->screen_Main_day_music_container, 30, 167);
	lv_obj_set_size(ui->screen_Main_day_music_container, 195, 78);

	//Write style state: LV_STATE_DEFAULT for style_screen_main_day_music_container_main_main_default
	static lv_style_t style_screen_main_day_music_container_main_main_default;
	lv_style_reset(&style_screen_main_day_music_container_main_main_default);
	lv_style_set_radius(&style_screen_main_day_music_container_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_main_day_music_container_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_color(&style_screen_main_day_music_container_main_main_default, lv_color_make(0x08, 0x08, 0x08));
	lv_style_set_bg_grad_dir(&style_screen_main_day_music_container_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_main_day_music_container_main_main_default, 0);
	lv_style_set_border_color(&style_screen_main_day_music_container_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_border_width(&style_screen_main_day_music_container_main_main_default, 0);
	lv_style_set_border_opa(&style_screen_main_day_music_container_main_main_default, 0);
	lv_style_set_pad_left(&style_screen_main_day_music_container_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_main_day_music_container_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_main_day_music_container_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_main_day_music_container_main_main_default, 0);
	lv_obj_add_style(ui->screen_Main_day_music_container, &style_screen_main_day_music_container_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_Day_music_slider_whitebase_img
	ui->screen_Day_music_slider_whitebase_img = lv_img_create(ui->screen_Main_day_music_container);
	lv_obj_set_pos(ui->screen_Day_music_slider_whitebase_img, 25, 62);
	lv_obj_set_size(ui->screen_Day_music_slider_whitebase_img, 130, 2);

	//Write style state: LV_STATE_DEFAULT for style_screen_day_music_slider_whitebase_img_main_main_default
	static lv_style_t style_screen_day_music_slider_whitebase_img_main_main_default;
	lv_style_reset(&style_screen_day_music_slider_whitebase_img_main_main_default);
	lv_style_set_img_recolor(&style_screen_day_music_slider_whitebase_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_day_music_slider_whitebase_img_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_day_music_slider_whitebase_img_main_main_default, 255);
	lv_obj_add_style(ui->screen_Day_music_slider_whitebase_img, &style_screen_day_music_slider_whitebase_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->screen_Day_music_slider_whitebase_img, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_Day_music_slider_whitebase_img,&_night_slider_white_100x2);
	lv_img_set_pivot(ui->screen_Day_music_slider_whitebase_img, 0,0);
	lv_img_set_angle(ui->screen_Day_music_slider_whitebase_img, 0);

	//Write codes screen_Day_music_slider_orange_img
	ui->screen_Day_music_slider_orange_img = lv_img_create(ui->screen_Main_day_music_container);
	lv_obj_set_pos(ui->screen_Day_music_slider_orange_img, 25, 62);
	lv_obj_set_size(ui->screen_Day_music_slider_orange_img, 40, 2);

	//Write style state: LV_STATE_DEFAULT for style_screen_day_music_slider_orange_img_main_main_default
	static lv_style_t style_screen_day_music_slider_orange_img_main_main_default;
	lv_style_reset(&style_screen_day_music_slider_orange_img_main_main_default);
	lv_style_set_img_recolor(&style_screen_day_music_slider_orange_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_day_music_slider_orange_img_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_day_music_slider_orange_img_main_main_default, 255);
	lv_obj_add_style(ui->screen_Day_music_slider_orange_img, &style_screen_day_music_slider_orange_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->screen_Day_music_slider_orange_img, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_Day_music_slider_orange_img,&_night_slider_orange_40x2);
	lv_img_set_pivot(ui->screen_Day_music_slider_orange_img, 0,0);
	lv_img_set_angle(ui->screen_Day_music_slider_orange_img, 0);

	//Write codes screen_Day_music_slide_dot
	ui->screen_Day_music_slide_dot = lv_img_create(ui->screen_Main_day_music_container);
	lv_obj_set_pos(ui->screen_Day_music_slide_dot, 81, 56);
	lv_obj_set_size(ui->screen_Day_music_slide_dot, 14, 14);

	//Write style state: LV_STATE_DEFAULT for style_screen_day_music_slide_dot_main_main_default
	static lv_style_t style_screen_day_music_slide_dot_main_main_default;
	lv_style_reset(&style_screen_day_music_slide_dot_main_main_default);
	lv_style_set_img_recolor(&style_screen_day_music_slide_dot_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_day_music_slide_dot_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_day_music_slide_dot_main_main_default, 255);
	lv_obj_add_style(ui->screen_Day_music_slide_dot, &style_screen_day_music_slide_dot_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->screen_Day_music_slide_dot, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_Day_music_slide_dot,&_night_slider_dot_14x14);
	lv_img_set_pivot(ui->screen_Day_music_slide_dot, 0,0);
	lv_img_set_angle(ui->screen_Day_music_slide_dot, 0);

	//Write codes screen_Day_music_lbl_1
	ui->screen_Day_music_lbl_1 = lv_label_create(ui->screen_Main_day_music_container);
	lv_obj_set_pos(ui->screen_Day_music_lbl_1, 13, 9);
	lv_obj_set_size(ui->screen_Day_music_lbl_1, 153, 20);
	lv_label_set_text(ui->screen_Day_music_lbl_1, "XX XXXXXX");
	lv_label_set_long_mode(ui->screen_Day_music_lbl_1, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->screen_Day_music_lbl_1, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_screen_day_music_lbl_1_main_main_default
	static lv_style_t style_screen_day_music_lbl_1_main_main_default;
	lv_style_reset(&style_screen_day_music_lbl_1_main_main_default);
	lv_style_set_radius(&style_screen_day_music_lbl_1_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_day_music_lbl_1_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_day_music_lbl_1_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_day_music_lbl_1_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_day_music_lbl_1_main_main_default, 0);
	lv_style_set_text_color(&style_screen_day_music_lbl_1_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_screen_day_music_lbl_1_main_main_default, &lv_font_FjallaOne_Regular_22);
	lv_style_set_text_letter_space(&style_screen_day_music_lbl_1_main_main_default, 0);
	lv_style_set_pad_left(&style_screen_day_music_lbl_1_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_day_music_lbl_1_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_day_music_lbl_1_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_day_music_lbl_1_main_main_default, 0);
	lv_obj_add_style(ui->screen_Day_music_lbl_1, &style_screen_day_music_lbl_1_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_Day_music_lbl_2
	ui->screen_Day_music_lbl_2 = lv_label_create(ui->screen_Main_day_music_container);
	lv_obj_set_pos(ui->screen_Day_music_lbl_2, 21, 29);
	lv_obj_set_size(ui->screen_Day_music_lbl_2, 153, 15);
	lv_label_set_text(ui->screen_Day_music_lbl_2, "XX XXXXXX");
	lv_label_set_long_mode(ui->screen_Day_music_lbl_2, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->screen_Day_music_lbl_2, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_screen_day_music_lbl_2_main_main_default
	static lv_style_t style_screen_day_music_lbl_2_main_main_default;
	lv_style_reset(&style_screen_day_music_lbl_2_main_main_default);
	lv_style_set_radius(&style_screen_day_music_lbl_2_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_day_music_lbl_2_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_day_music_lbl_2_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_day_music_lbl_2_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_day_music_lbl_2_main_main_default, 0);
	lv_style_set_text_color(&style_screen_day_music_lbl_2_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_screen_day_music_lbl_2_main_main_default, &lv_font_FjallaOne_Regular_17);
	lv_style_set_text_letter_space(&style_screen_day_music_lbl_2_main_main_default, 0);
	lv_style_set_pad_left(&style_screen_day_music_lbl_2_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_day_music_lbl_2_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_day_music_lbl_2_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_day_music_lbl_2_main_main_default, 0);
	lv_obj_add_style(ui->screen_Day_music_lbl_2, &style_screen_day_music_lbl_2_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_Day_music_lbl_3
	ui->screen_Day_music_lbl_3 = lv_label_create(ui->screen_Main_day_music_container);
	lv_obj_set_pos(ui->screen_Day_music_lbl_3, 15, 34);
	lv_obj_set_size(ui->screen_Day_music_lbl_3, 153, 15);
	lv_label_set_text(ui->screen_Day_music_lbl_3, "XX XXXXXX");
	lv_label_set_long_mode(ui->screen_Day_music_lbl_3, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->screen_Day_music_lbl_3, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_screen_day_music_lbl_3_main_main_default
	static lv_style_t style_screen_day_music_lbl_3_main_main_default;
	lv_style_reset(&style_screen_day_music_lbl_3_main_main_default);
	lv_style_set_radius(&style_screen_day_music_lbl_3_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_day_music_lbl_3_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_day_music_lbl_3_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_day_music_lbl_3_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_day_music_lbl_3_main_main_default, 0);
	lv_style_set_text_color(&style_screen_day_music_lbl_3_main_main_default, lv_color_make(0xB8, 0xB8, 0xB8));
	lv_style_set_text_font(&style_screen_day_music_lbl_3_main_main_default, &lv_font_FjallaOne_Regular_17);
	lv_style_set_text_letter_space(&style_screen_day_music_lbl_3_main_main_default, 0);
	lv_style_set_pad_left(&style_screen_day_music_lbl_3_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_day_music_lbl_3_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_day_music_lbl_3_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_day_music_lbl_3_main_main_default, 0);
	lv_obj_add_style(ui->screen_Day_music_lbl_3, &style_screen_day_music_lbl_3_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_Day_music_up_img
	ui->screen_Day_music_up_img = lv_img_create(ui->screen_Main_day_music_container);
	lv_obj_set_pos(ui->screen_Day_music_up_img, 85, 6);
	lv_obj_set_size(ui->screen_Day_music_up_img, 10, 13);

	//Write style state: LV_STATE_DEFAULT for style_screen_day_music_up_img_main_main_default
	static lv_style_t style_screen_day_music_up_img_main_main_default;
	lv_style_reset(&style_screen_day_music_up_img_main_main_default);
	lv_style_set_img_recolor(&style_screen_day_music_up_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_day_music_up_img_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_day_music_up_img_main_main_default, 255);
	lv_obj_add_style(ui->screen_Day_music_up_img, &style_screen_day_music_up_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_Day_music_down_img
	ui->screen_Day_music_down_img = lv_img_create(ui->screen_Main_day_music_container);
	lv_obj_set_pos(ui->screen_Day_music_down_img, 85, 61);
	lv_obj_set_size(ui->screen_Day_music_down_img, 9, 12);

	//Write style state: LV_STATE_DEFAULT for style_screen_day_music_down_img_main_main_default
	static lv_style_t style_screen_day_music_down_img_main_main_default;
	lv_style_reset(&style_screen_day_music_down_img_main_main_default);
	lv_style_set_img_recolor(&style_screen_day_music_down_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_day_music_down_img_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_day_music_down_img_main_main_default, 255);
	lv_obj_add_style(ui->screen_Day_music_down_img, &style_screen_day_music_down_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_Day_music_sub_button
	ui->screen_Day_music_sub_button = lv_img_create(ui->screen_Main_day_music_container);
	lv_obj_set_pos(ui->screen_Day_music_sub_button, 150, 22);
	lv_obj_set_size(ui->screen_Day_music_sub_button, 30, 30);

	//Write style state: LV_STATE_DEFAULT for style_screen_day_music_sub_button_main_main_default
	static lv_style_t style_screen_day_music_sub_button_main_main_default;
	lv_style_reset(&style_screen_day_music_sub_button_main_main_default);
	lv_style_set_img_recolor(&style_screen_day_music_sub_button_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_day_music_sub_button_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_day_music_sub_button_main_main_default, 255);
	lv_obj_add_style(ui->screen_Day_music_sub_button, &style_screen_day_music_sub_button_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_Main_day_volume_container
	ui->screen_Main_day_volume_container = lv_obj_create(ui->screen);
	lv_obj_set_pos(ui->screen_Main_day_volume_container, 30, 167);
	lv_obj_set_size(ui->screen_Main_day_volume_container, 195, 78);

	//Write style state: LV_STATE_DEFAULT for style_screen_main_day_volume_container_main_main_default
	static lv_style_t style_screen_main_day_volume_container_main_main_default;
	lv_style_reset(&style_screen_main_day_volume_container_main_main_default);
	lv_style_set_radius(&style_screen_main_day_volume_container_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_main_day_volume_container_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_color(&style_screen_main_day_volume_container_main_main_default, lv_color_make(0x08, 0x08, 0x08));
	lv_style_set_bg_grad_dir(&style_screen_main_day_volume_container_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_main_day_volume_container_main_main_default, 0);
	lv_style_set_border_color(&style_screen_main_day_volume_container_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_border_width(&style_screen_main_day_volume_container_main_main_default, 0);
	lv_style_set_border_opa(&style_screen_main_day_volume_container_main_main_default, 0);
	lv_style_set_pad_left(&style_screen_main_day_volume_container_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_main_day_volume_container_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_main_day_volume_container_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_main_day_volume_container_main_main_default, 0);
	lv_obj_add_style(ui->screen_Main_day_volume_container, &style_screen_main_day_volume_container_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_Day_volume_plus
	ui->screen_Day_volume_plus = lv_img_create(ui->screen_Main_day_volume_container);
	lv_obj_set_pos(ui->screen_Day_volume_plus, 85, 5);
	lv_obj_set_size(ui->screen_Day_volume_plus, 11, 11);

	//Write style state: LV_STATE_DEFAULT for style_screen_day_volume_plus_main_main_default
	static lv_style_t style_screen_day_volume_plus_main_main_default;
	lv_style_reset(&style_screen_day_volume_plus_main_main_default);
	lv_style_set_img_recolor(&style_screen_day_volume_plus_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_day_volume_plus_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_day_volume_plus_main_main_default, 255);
	lv_obj_add_style(ui->screen_Day_volume_plus, &style_screen_day_volume_plus_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_Day_volume_minus
	ui->screen_Day_volume_minus = lv_img_create(ui->screen_Main_day_volume_container);
	lv_obj_set_pos(ui->screen_Day_volume_minus, 85, 75);
	lv_obj_set_size(ui->screen_Day_volume_minus, 11, 3);

	//Write style state: LV_STATE_DEFAULT for style_screen_day_volume_minus_main_main_default
	static lv_style_t style_screen_day_volume_minus_main_main_default;
	lv_style_reset(&style_screen_day_volume_minus_main_main_default);
	lv_style_set_img_recolor(&style_screen_day_volume_minus_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_day_volume_minus_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_day_volume_minus_main_main_default, 255);
	lv_obj_add_style(ui->screen_Day_volume_minus, &style_screen_day_volume_minus_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_Day_volume_signbtn
	ui->screen_Day_volume_signbtn = lv_img_create(ui->screen_Main_day_volume_container);
	lv_obj_set_pos(ui->screen_Day_volume_signbtn, 150, 22);
	lv_obj_set_size(ui->screen_Day_volume_signbtn, 30, 30);

	//Write style state: LV_STATE_DEFAULT for style_screen_day_volume_signbtn_main_main_default
	static lv_style_t style_screen_day_volume_signbtn_main_main_default;
	lv_style_reset(&style_screen_day_volume_signbtn_main_main_default);
	lv_style_set_img_recolor(&style_screen_day_volume_signbtn_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_day_volume_signbtn_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_day_volume_signbtn_main_main_default, 255);
	lv_obj_add_style(ui->screen_Day_volume_signbtn, &style_screen_day_volume_signbtn_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_Day_volume_base
	ui->screen_Day_volume_base = lv_img_create(ui->screen_Main_day_volume_container);
	lv_obj_set_pos(ui->screen_Day_volume_base, 40, 40);
	lv_obj_set_size(ui->screen_Day_volume_base, 110, 27);

	//Write style state: LV_STATE_DEFAULT for style_screen_day_volume_base_main_main_default
	static lv_style_t style_screen_day_volume_base_main_main_default;
	lv_style_reset(&style_screen_day_volume_base_main_main_default);
	lv_style_set_img_recolor(&style_screen_day_volume_base_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_day_volume_base_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_day_volume_base_main_main_default, 255);
	lv_obj_add_style(ui->screen_Day_volume_base, &style_screen_day_volume_base_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_img_set_src(ui->screen_Day_volume_base,&img_day_volume_bar_base);

	//Write codes screen_Day_volume_val_img
	ui->screen_Day_volume_val_img = lv_img_create(ui->screen_Main_day_volume_container);
	lv_obj_set_pos(ui->screen_Day_volume_val_img, 40, 40);
	lv_obj_set_size(ui->screen_Day_volume_val_img, 110, 27);

	//Write style state: LV_STATE_DEFAULT for style_screen_day_volume_val_img_main_main_default
	static lv_style_t style_screen_day_volume_val_img_main_main_default;
	lv_style_reset(&style_screen_day_volume_val_img_main_main_default);
	lv_style_set_img_recolor(&style_screen_day_volume_val_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_day_volume_val_img_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_day_volume_val_img_main_main_default, 255);
	lv_obj_add_style(ui->screen_Day_volume_val_img, &style_screen_day_volume_val_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_Day_volume_label
	ui->screen_Day_volume_label = lv_label_create(ui->screen_Main_day_volume_container);
	lv_obj_set_pos(ui->screen_Day_volume_label, 59, 16);
	lv_obj_set_size(ui->screen_Day_volume_label, 70, 20);
	lv_label_set_text(ui->screen_Day_volume_label, "Volume");
	lv_label_set_long_mode(ui->screen_Day_volume_label, LV_LABEL_LONG_WRAP);
	lv_obj_set_style_text_align(ui->screen_Day_volume_label, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_screen_day_volume_label_main_main_default
	static lv_style_t style_screen_day_volume_label_main_main_default;
	lv_style_reset(&style_screen_day_volume_label_main_main_default);
	lv_style_set_radius(&style_screen_day_volume_label_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_day_volume_label_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_day_volume_label_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_day_volume_label_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_day_volume_label_main_main_default, 0);
	lv_style_set_text_color(&style_screen_day_volume_label_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_screen_day_volume_label_main_main_default, &lv_font_FjallaOne_Regular_22);
	lv_style_set_text_letter_space(&style_screen_day_volume_label_main_main_default, 0);
	lv_style_set_pad_left(&style_screen_day_volume_label_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_day_volume_label_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_day_volume_label_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_day_volume_label_main_main_default, 0);
	lv_obj_add_style(ui->screen_Day_volume_label, &style_screen_day_volume_label_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_Main_day_phone_container
	ui->screen_Main_day_phone_container = lv_obj_create(ui->screen);
	lv_obj_set_pos(ui->screen_Main_day_phone_container, 30, 167);
	lv_obj_set_size(ui->screen_Main_day_phone_container, 195, 80);

	//Write style state: LV_STATE_DEFAULT for style_screen_main_day_phone_container_main_main_default
	static lv_style_t style_screen_main_day_phone_container_main_main_default;
	lv_style_reset(&style_screen_main_day_phone_container_main_main_default);
	lv_style_set_radius(&style_screen_main_day_phone_container_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_main_day_phone_container_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_color(&style_screen_main_day_phone_container_main_main_default, lv_color_make(0x08, 0x08, 0x08));
	lv_style_set_bg_grad_dir(&style_screen_main_day_phone_container_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_main_day_phone_container_main_main_default, 0);
	lv_style_set_border_color(&style_screen_main_day_phone_container_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_border_width(&style_screen_main_day_phone_container_main_main_default, 0);
	lv_style_set_border_opa(&style_screen_main_day_phone_container_main_main_default, 0);
	lv_style_set_pad_left(&style_screen_main_day_phone_container_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_main_day_phone_container_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_main_day_phone_container_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_main_day_phone_container_main_main_default, 0);
	lv_obj_add_style(ui->screen_Main_day_phone_container, &style_screen_main_day_phone_container_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_Day_phone_up_arrow
	ui->screen_Day_phone_up_arrow = lv_img_create(ui->screen_Main_day_phone_container);
	lv_obj_set_pos(ui->screen_Day_phone_up_arrow, 84, 4);
	lv_obj_set_size(ui->screen_Day_phone_up_arrow, 12, 7);

	//Write style state: LV_STATE_DEFAULT for style_screen_day_phone_up_arrow_main_main_default
	static lv_style_t style_screen_day_phone_up_arrow_main_main_default;
	lv_style_reset(&style_screen_day_phone_up_arrow_main_main_default);
	lv_style_set_img_recolor(&style_screen_day_phone_up_arrow_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_day_phone_up_arrow_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_day_phone_up_arrow_main_main_default, 255);
	lv_obj_add_style(ui->screen_Day_phone_up_arrow, &style_screen_day_phone_up_arrow_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->screen_Day_phone_up_arrow, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_Day_phone_up_arrow,&new_day_trip_up_arrow_normal);
	lv_img_set_pivot(ui->screen_Day_phone_up_arrow, 0,0);
	lv_img_set_angle(ui->screen_Day_phone_up_arrow, 0);

	//Write codes screen_Day_phone_down_arrow
	ui->screen_Day_phone_down_arrow = lv_img_create(ui->screen_Main_day_phone_container);
	lv_obj_set_pos(ui->screen_Day_phone_down_arrow, 84, 62);
	lv_obj_set_size(ui->screen_Day_phone_down_arrow, 12, 7);

	//Write style state: LV_STATE_DEFAULT for style_screen_day_phone_down_arrow_main_main_default
	static lv_style_t style_screen_day_phone_down_arrow_main_main_default;
	lv_style_reset(&style_screen_day_phone_down_arrow_main_main_default);
	lv_style_set_img_recolor(&style_screen_day_phone_down_arrow_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_day_phone_down_arrow_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_day_phone_down_arrow_main_main_default, 255);
	lv_obj_add_style(ui->screen_Day_phone_down_arrow, &style_screen_day_phone_down_arrow_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->screen_Day_phone_down_arrow, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_Day_phone_down_arrow,&new_day_trip_down_arrow_normal);
	lv_img_set_pivot(ui->screen_Day_phone_down_arrow, 0,0);
	lv_img_set_angle(ui->screen_Day_phone_down_arrow, 0);

	//Write codes screen_Day_phone_lbl_1
	ui->screen_Day_phone_lbl_1 = lv_label_create(ui->screen_Main_day_phone_container);
	lv_obj_set_pos(ui->screen_Day_phone_lbl_1, 8, 7);
	lv_obj_set_size(ui->screen_Day_phone_lbl_1, 183, 20);
	lv_label_set_text(ui->screen_Day_phone_lbl_1, "+91 XXXXXXXXXXX");
	lv_label_set_long_mode(ui->screen_Day_phone_lbl_1, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->screen_Day_phone_lbl_1, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_screen_day_phone_lbl_1_main_main_default
	static lv_style_t style_screen_day_phone_lbl_1_main_main_default;
	lv_style_reset(&style_screen_day_phone_lbl_1_main_main_default);
	lv_style_set_radius(&style_screen_day_phone_lbl_1_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_day_phone_lbl_1_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_day_phone_lbl_1_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_day_phone_lbl_1_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_day_phone_lbl_1_main_main_default, 0);
	lv_style_set_text_color(&style_screen_day_phone_lbl_1_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_screen_day_phone_lbl_1_main_main_default, &lv_font_FjallaOne_Regular_22);
	lv_style_set_text_letter_space(&style_screen_day_phone_lbl_1_main_main_default, 0);
	lv_style_set_pad_left(&style_screen_day_phone_lbl_1_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_day_phone_lbl_1_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_day_phone_lbl_1_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_day_phone_lbl_1_main_main_default, 0);
	lv_obj_add_style(ui->screen_Day_phone_lbl_1, &style_screen_day_phone_lbl_1_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_Day_phone_lbl_2
	ui->screen_Day_phone_lbl_2 = lv_label_create(ui->screen_Main_day_phone_container);
	lv_obj_set_pos(ui->screen_Day_phone_lbl_2, 42, 31);
	lv_obj_set_size(ui->screen_Day_phone_lbl_2, 100, 16);
	lv_label_set_text(ui->screen_Day_phone_lbl_2, "XX XXXXXXXXX");
	lv_label_set_long_mode(ui->screen_Day_phone_lbl_2, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->screen_Day_phone_lbl_2, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_screen_day_phone_lbl_2_main_main_default
	static lv_style_t style_screen_day_phone_lbl_2_main_main_default;
	lv_style_reset(&style_screen_day_phone_lbl_2_main_main_default);
	lv_style_set_radius(&style_screen_day_phone_lbl_2_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_day_phone_lbl_2_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_day_phone_lbl_2_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_day_phone_lbl_2_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_day_phone_lbl_2_main_main_default, 0);
	lv_style_set_text_color(&style_screen_day_phone_lbl_2_main_main_default, lv_color_make(0xB8, 0xB8, 0xB8));
	lv_style_set_text_font(&style_screen_day_phone_lbl_2_main_main_default, &lv_font_FjallaOne_Regular_14);
	lv_style_set_text_letter_space(&style_screen_day_phone_lbl_2_main_main_default, 0);
	lv_style_set_pad_left(&style_screen_day_phone_lbl_2_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_day_phone_lbl_2_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_day_phone_lbl_2_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_day_phone_lbl_2_main_main_default, 0);
	lv_obj_add_style(ui->screen_Day_phone_lbl_2, &style_screen_day_phone_lbl_2_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_Day_phone_btn1
	ui->screen_Day_phone_btn1 = lv_img_create(ui->screen_Main_day_phone_container);
	lv_obj_set_pos(ui->screen_Day_phone_btn1, 28, 49);
	lv_obj_set_size(ui->screen_Day_phone_btn1, 30, 30);

	//Write style state: LV_STATE_DEFAULT for style_screen_day_phone_btn1_main_main_default
	static lv_style_t style_screen_day_phone_btn1_main_main_default;
	lv_style_reset(&style_screen_day_phone_btn1_main_main_default);
	lv_style_set_img_recolor(&style_screen_day_phone_btn1_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_day_phone_btn1_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_day_phone_btn1_main_main_default, 255);
	lv_obj_add_style(ui->screen_Day_phone_btn1, &style_screen_day_phone_btn1_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->screen_Day_phone_btn1, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_Day_phone_btn1,&_img_night_call_declined_decline_30x30);
	lv_img_set_pivot(ui->screen_Day_phone_btn1, 0,0);
	lv_img_set_angle(ui->screen_Day_phone_btn1, 0);

	//Write codes screen_Day_phone_btn2
	ui->screen_Day_phone_btn2 = lv_img_create(ui->screen_Main_day_phone_container);
	lv_obj_set_pos(ui->screen_Day_phone_btn2, 75, 49);
	lv_obj_set_size(ui->screen_Day_phone_btn2, 30, 30);

	//Write style state: LV_STATE_DEFAULT for style_screen_day_phone_btn2_main_main_default
	static lv_style_t style_screen_day_phone_btn2_main_main_default;
	lv_style_reset(&style_screen_day_phone_btn2_main_main_default);
	lv_style_set_img_recolor(&style_screen_day_phone_btn2_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_day_phone_btn2_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_day_phone_btn2_main_main_default, 255);
	lv_obj_add_style(ui->screen_Day_phone_btn2, &style_screen_day_phone_btn2_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->screen_Day_phone_btn2, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_Day_phone_btn2,&_img_night_call_declined_decline_30x30);
	lv_img_set_pivot(ui->screen_Day_phone_btn2, 0,0);
	lv_img_set_angle(ui->screen_Day_phone_btn2, 0);

	//Write codes screen_Day_phone_btn3
	ui->screen_Day_phone_btn3 = lv_img_create(ui->screen_Main_day_phone_container);
	lv_obj_set_pos(ui->screen_Day_phone_btn3, 122, 49);
	lv_obj_set_size(ui->screen_Day_phone_btn3, 30, 30);

	//Write style state: LV_STATE_DEFAULT for style_screen_day_phone_btn3_main_main_default
	static lv_style_t style_screen_day_phone_btn3_main_main_default;
	lv_style_reset(&style_screen_day_phone_btn3_main_main_default);
	lv_style_set_img_recolor(&style_screen_day_phone_btn3_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_day_phone_btn3_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_day_phone_btn3_main_main_default, 255);
	lv_obj_add_style(ui->screen_Day_phone_btn3, &style_screen_day_phone_btn3_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->screen_Day_phone_btn3, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_Day_phone_btn3,&_img_night_incoming_call_accept_30x30);
	lv_img_set_pivot(ui->screen_Day_phone_btn3, 0,0);
	lv_img_set_angle(ui->screen_Day_phone_btn3, 0);

	//Write codes screen_Day_phone_call_btn
	ui->screen_Day_phone_call_btn = lv_img_create(ui->screen_Main_day_phone_container);
	lv_obj_set_pos(ui->screen_Day_phone_call_btn, 146, 19);
	lv_obj_set_size(ui->screen_Day_phone_call_btn, 30, 30);

	//Write style state: LV_STATE_DEFAULT for style_screen_day_phone_call_btn_main_main_default
	static lv_style_t style_screen_day_phone_call_btn_main_main_default;
	lv_style_reset(&style_screen_day_phone_call_btn_main_main_default);
	lv_style_set_img_recolor(&style_screen_day_phone_call_btn_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_day_phone_call_btn_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_day_phone_call_btn_main_main_default, 255);
	lv_obj_add_style(ui->screen_Day_phone_call_btn, &style_screen_day_phone_call_btn_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->screen_Day_phone_call_btn, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_Day_phone_call_btn,&_img_night_contacts_l1_call_icon_30x30);
	lv_img_set_pivot(ui->screen_Day_phone_call_btn, 0,0);
	lv_img_set_angle(ui->screen_Day_phone_call_btn, 0);

	//Write codes screen_Main_day_Navigation
	ui->screen_Main_day_Navigation = lv_obj_create(ui->screen);
	lv_obj_set_pos(ui->screen_Main_day_Navigation, 30, 167);
	lv_obj_set_size(ui->screen_Main_day_Navigation, 195, 95);

	//Write style state: LV_STATE_DEFAULT for style_screen_main_day_navigation_main_main_default
	static lv_style_t style_screen_main_day_navigation_main_main_default;
	lv_style_reset(&style_screen_main_day_navigation_main_main_default);
	lv_style_set_radius(&style_screen_main_day_navigation_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_main_day_navigation_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_color(&style_screen_main_day_navigation_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_dir(&style_screen_main_day_navigation_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_main_day_navigation_main_main_default, 0);
	lv_style_set_border_color(&style_screen_main_day_navigation_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_border_width(&style_screen_main_day_navigation_main_main_default, 0);
	lv_style_set_border_opa(&style_screen_main_day_navigation_main_main_default, 0);
	lv_style_set_pad_left(&style_screen_main_day_navigation_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_main_day_navigation_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_main_day_navigation_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_main_day_navigation_main_main_default, 0);
	lv_obj_add_style(ui->screen_Main_day_Navigation, &style_screen_main_day_navigation_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_No_Sig_Day
	ui->screen_No_Sig_Day = lv_img_create(ui->screen_Main_day_Navigation);
	lv_obj_set_pos(ui->screen_No_Sig_Day, 67, 54);
	lv_obj_set_size(ui->screen_No_Sig_Day, 46, 16);

	//Write style state: LV_STATE_DEFAULT for style_screen_no_sig_day_main_main_default
	static lv_style_t style_screen_no_sig_day_main_main_default;
	lv_style_reset(&style_screen_no_sig_day_main_main_default);
	lv_style_set_img_recolor(&style_screen_no_sig_day_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_no_sig_day_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_no_sig_day_main_main_default, 255);
	lv_obj_add_style(ui->screen_No_Sig_Day, &style_screen_no_sig_day_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_Day_navi_lbl
	ui->screen_Day_navi_lbl = lv_label_create(ui->screen_Main_day_Navigation);
	lv_obj_set_pos(ui->screen_Day_navi_lbl, 5, 6);
	lv_obj_set_size(ui->screen_Day_navi_lbl, 100, 10);
	lv_label_set_text(ui->screen_Day_navi_lbl, "");
	lv_label_set_long_mode(ui->screen_Day_navi_lbl, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->screen_Day_navi_lbl, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_screen_day_navi_lbl_main_main_default
	static lv_style_t style_screen_day_navi_lbl_main_main_default;
	lv_style_reset(&style_screen_day_navi_lbl_main_main_default);
	lv_style_set_radius(&style_screen_day_navi_lbl_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_day_navi_lbl_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_day_navi_lbl_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_day_navi_lbl_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_day_navi_lbl_main_main_default, 0);
	lv_style_set_text_color(&style_screen_day_navi_lbl_main_main_default, lv_color_make(0xff, 0x78, 0x00));
	lv_style_set_text_font(&style_screen_day_navi_lbl_main_main_default, &lv_font_FjallaOne_Regular_10);
	lv_style_set_text_letter_space(&style_screen_day_navi_lbl_main_main_default, 0);
	lv_style_set_pad_left(&style_screen_day_navi_lbl_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_day_navi_lbl_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_day_navi_lbl_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_day_navi_lbl_main_main_default, 0);
	lv_obj_add_style(ui->screen_Day_navi_lbl, &style_screen_day_navi_lbl_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_Day_navi_val
	ui->screen_Day_navi_val = lv_label_create(ui->screen_Main_day_Navigation);
	lv_obj_set_pos(ui->screen_Day_navi_val, 20, 8);
	lv_obj_set_size(ui->screen_Day_navi_val, 30, 17);
	lv_label_set_text(ui->screen_Day_navi_val, "9999");
	lv_label_set_long_mode(ui->screen_Day_navi_val, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->screen_Day_navi_val, LV_TEXT_ALIGN_RIGHT, 0);

	//Write style state: LV_STATE_DEFAULT for style_screen_day_navi_val_main_main_default
	static lv_style_t style_screen_day_navi_val_main_main_default;
	lv_style_reset(&style_screen_day_navi_val_main_main_default);
	lv_style_set_radius(&style_screen_day_navi_val_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_day_navi_val_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_day_navi_val_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_day_navi_val_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_day_navi_val_main_main_default, 0);
	lv_style_set_text_color(&style_screen_day_navi_val_main_main_default, lv_color_make(0xff, 0x78, 0x00));
	lv_style_set_text_font(&style_screen_day_navi_val_main_main_default, &lv_font_FjallaOne_Regular_22);
	lv_style_set_text_letter_space(&style_screen_day_navi_val_main_main_default, 0);
	lv_style_set_pad_left(&style_screen_day_navi_val_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_day_navi_val_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_day_navi_val_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_day_navi_val_main_main_default, 0);
	lv_obj_add_style(ui->screen_Day_navi_val, &style_screen_day_navi_val_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_Day_navi_unit
	ui->screen_Day_navi_unit = lv_label_create(ui->screen_Main_day_Navigation);
	lv_obj_set_pos(ui->screen_Day_navi_unit, 24, 35);
	lv_obj_set_size(ui->screen_Day_navi_unit, 26, 11);
	lv_label_set_text(ui->screen_Day_navi_unit, "km");
	lv_label_set_long_mode(ui->screen_Day_navi_unit, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->screen_Day_navi_unit, LV_TEXT_ALIGN_RIGHT, 0);

	//Write style state: LV_STATE_DEFAULT for style_screen_day_navi_unit_main_main_default
	static lv_style_t style_screen_day_navi_unit_main_main_default;
	lv_style_reset(&style_screen_day_navi_unit_main_main_default);
	lv_style_set_radius(&style_screen_day_navi_unit_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_day_navi_unit_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_day_navi_unit_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_day_navi_unit_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_day_navi_unit_main_main_default, 0);
	lv_style_set_text_color(&style_screen_day_navi_unit_main_main_default, lv_color_make(0xff, 0x78, 0x00));
	lv_style_set_text_font(&style_screen_day_navi_unit_main_main_default, &lv_font_FjallaOne_Regular_14);
	lv_style_set_text_letter_space(&style_screen_day_navi_unit_main_main_default, 0);
	lv_style_set_pad_left(&style_screen_day_navi_unit_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_day_navi_unit_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_day_navi_unit_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_day_navi_unit_main_main_default, 0);
	lv_obj_add_style(ui->screen_Day_navi_unit, &style_screen_day_navi_unit_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_Day_nav_est
	ui->screen_Day_nav_est = lv_label_create(ui->screen_Main_day_Navigation);
	lv_obj_set_pos(ui->screen_Day_nav_est, 143, 35);
	lv_obj_set_size(ui->screen_Day_nav_est, 26, 14);
	lv_label_set_text(ui->screen_Day_nav_est, "ETA");
	lv_label_set_long_mode(ui->screen_Day_nav_est, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->screen_Day_nav_est, LV_TEXT_ALIGN_LEFT, 0);

	//Write style state: LV_STATE_DEFAULT for style_screen_day_nav_est_main_main_default
	static lv_style_t style_screen_day_nav_est_main_main_default;
	lv_style_reset(&style_screen_day_nav_est_main_main_default);
	lv_style_set_radius(&style_screen_day_nav_est_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_day_nav_est_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_day_nav_est_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_day_nav_est_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_day_nav_est_main_main_default, 0);
	lv_style_set_text_color(&style_screen_day_nav_est_main_main_default, lv_color_make(0x98, 0x98, 0x98));
	lv_style_set_text_font(&style_screen_day_nav_est_main_main_default, &lv_font_FjallaOne_Regular_17);
	lv_style_set_text_letter_space(&style_screen_day_nav_est_main_main_default, 0);
	lv_style_set_pad_left(&style_screen_day_nav_est_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_day_nav_est_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_day_nav_est_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_day_nav_est_main_main_default, 0);
	lv_obj_add_style(ui->screen_Day_nav_est, &style_screen_day_nav_est_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_Day_nav_clo_hr
	ui->screen_Day_nav_clo_hr = lv_label_create(ui->screen_Main_day_Navigation);
	lv_obj_set_pos(ui->screen_Day_nav_clo_hr, 130, 8);
	lv_obj_set_size(ui->screen_Day_nav_clo_hr, 18, 15);
	lv_label_set_text(ui->screen_Day_nav_clo_hr, "99");
	lv_label_set_long_mode(ui->screen_Day_nav_clo_hr, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->screen_Day_nav_clo_hr, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_screen_day_nav_clo_hr_main_main_default
	static lv_style_t style_screen_day_nav_clo_hr_main_main_default;
	lv_style_reset(&style_screen_day_nav_clo_hr_main_main_default);
	lv_style_set_radius(&style_screen_day_nav_clo_hr_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_day_nav_clo_hr_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_day_nav_clo_hr_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_day_nav_clo_hr_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_day_nav_clo_hr_main_main_default, 0);
	lv_style_set_text_color(&style_screen_day_nav_clo_hr_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_screen_day_nav_clo_hr_main_main_default, &lv_font_FjallaOne_Regular_17);
	lv_style_set_text_letter_space(&style_screen_day_nav_clo_hr_main_main_default, 0);
	lv_style_set_pad_left(&style_screen_day_nav_clo_hr_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_day_nav_clo_hr_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_day_nav_clo_hr_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_day_nav_clo_hr_main_main_default, 0);
	lv_obj_add_style(ui->screen_Day_nav_clo_hr, &style_screen_day_nav_clo_hr_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_Day_nav_clo_colon
	ui->screen_Day_nav_clo_colon = lv_label_create(ui->screen_Main_day_Navigation);
	lv_obj_set_pos(ui->screen_Day_nav_clo_colon, 148, 8);
	lv_obj_set_size(ui->screen_Day_nav_clo_colon, 4, 13);
	lv_label_set_text(ui->screen_Day_nav_clo_colon, ":");
	lv_label_set_long_mode(ui->screen_Day_nav_clo_colon, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->screen_Day_nav_clo_colon, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_screen_day_nav_clo_colon_main_main_default
	static lv_style_t style_screen_day_nav_clo_colon_main_main_default;
	lv_style_reset(&style_screen_day_nav_clo_colon_main_main_default);
	lv_style_set_radius(&style_screen_day_nav_clo_colon_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_day_nav_clo_colon_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_day_nav_clo_colon_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_day_nav_clo_colon_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_day_nav_clo_colon_main_main_default, 0);
	lv_style_set_text_color(&style_screen_day_nav_clo_colon_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_screen_day_nav_clo_colon_main_main_default, &lv_font_FjallaOne_Regular_17);
	lv_style_set_text_letter_space(&style_screen_day_nav_clo_colon_main_main_default, 0);
	lv_style_set_pad_left(&style_screen_day_nav_clo_colon_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_day_nav_clo_colon_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_day_nav_clo_colon_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_day_nav_clo_colon_main_main_default, 0);
	lv_obj_add_style(ui->screen_Day_nav_clo_colon, &style_screen_day_nav_clo_colon_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_Day_nav_clo_min
	ui->screen_Day_nav_clo_min = lv_label_create(ui->screen_Main_day_Navigation);
	lv_obj_set_pos(ui->screen_Day_nav_clo_min, 153, 8);
	lv_obj_set_size(ui->screen_Day_nav_clo_min, 17, 15);
	lv_label_set_text(ui->screen_Day_nav_clo_min, "99");
	lv_label_set_long_mode(ui->screen_Day_nav_clo_min, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->screen_Day_nav_clo_min, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_screen_day_nav_clo_min_main_main_default
	static lv_style_t style_screen_day_nav_clo_min_main_main_default;
	lv_style_reset(&style_screen_day_nav_clo_min_main_main_default);
	lv_style_set_radius(&style_screen_day_nav_clo_min_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_day_nav_clo_min_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_day_nav_clo_min_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_day_nav_clo_min_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_day_nav_clo_min_main_main_default, 0);
	lv_style_set_text_color(&style_screen_day_nav_clo_min_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_screen_day_nav_clo_min_main_main_default, &lv_font_FjallaOne_Regular_17);
	lv_style_set_text_letter_space(&style_screen_day_nav_clo_min_main_main_default, 0);
	lv_style_set_pad_left(&style_screen_day_nav_clo_min_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_day_nav_clo_min_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_day_nav_clo_min_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_day_nav_clo_min_main_main_default, 0);
	lv_obj_add_style(ui->screen_Day_nav_clo_min, &style_screen_day_nav_clo_min_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_Day_nav_clo_am
	ui->screen_Day_nav_clo_am = lv_label_create(ui->screen_Main_day_Navigation);
	lv_obj_set_pos(ui->screen_Day_nav_clo_am, 174, 8);
	lv_obj_set_size(ui->screen_Day_nav_clo_am, 19, 15);
	lv_label_set_text(ui->screen_Day_nav_clo_am, "AM");
	lv_label_set_long_mode(ui->screen_Day_nav_clo_am, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->screen_Day_nav_clo_am, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_screen_day_nav_clo_am_main_main_default
	static lv_style_t style_screen_day_nav_clo_am_main_main_default;
	lv_style_reset(&style_screen_day_nav_clo_am_main_main_default);
	lv_style_set_radius(&style_screen_day_nav_clo_am_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_day_nav_clo_am_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_day_nav_clo_am_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_day_nav_clo_am_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_day_nav_clo_am_main_main_default, 0);
	lv_style_set_text_color(&style_screen_day_nav_clo_am_main_main_default, lv_color_make(0x98, 0x98, 0x98));
	lv_style_set_text_font(&style_screen_day_nav_clo_am_main_main_default, &lv_font_FjallaOne_Regular_17);
	lv_style_set_text_letter_space(&style_screen_day_nav_clo_am_main_main_default, 0);
	lv_style_set_pad_left(&style_screen_day_nav_clo_am_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_day_nav_clo_am_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_day_nav_clo_am_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_day_nav_clo_am_main_main_default, 0);
	lv_obj_add_style(ui->screen_Day_nav_clo_am, &style_screen_day_nav_clo_am_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_Day_nav_img
	ui->screen_Day_nav_img = lv_img_create(ui->screen_Main_day_Navigation);
	lv_obj_set_pos(ui->screen_Day_nav_img, 55, 5);
	lv_obj_set_size(ui->screen_Day_nav_img, 70, 70);

	//Write style state: LV_STATE_DEFAULT for style_screen_day_nav_img_main_main_default
	static lv_style_t style_screen_day_nav_img_main_main_default;
	lv_style_reset(&style_screen_day_nav_img_main_main_default);
	lv_style_set_img_recolor(&style_screen_day_nav_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_day_nav_img_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_day_nav_img_main_main_default, 255);
	lv_obj_add_style(ui->screen_Day_nav_img, &style_screen_day_nav_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_Passcode_Day_container
	ui->screen_Passcode_Day_container = lv_obj_create(ui->screen);
	lv_obj_set_pos(ui->screen_Passcode_Day_container, 30, 167);
	lv_obj_set_size(ui->screen_Passcode_Day_container, 195, 78);

	//Write style state: LV_STATE_DEFAULT for style_screen_passcode_day_container_main_main_default
	static lv_style_t style_screen_passcode_day_container_main_main_default;
	lv_style_reset(&style_screen_passcode_day_container_main_main_default);
	lv_style_set_radius(&style_screen_passcode_day_container_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_passcode_day_container_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_grad_color(&style_screen_passcode_day_container_main_main_default, lv_color_make(0x08, 0x08, 0x08));
	lv_style_set_bg_grad_dir(&style_screen_passcode_day_container_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_passcode_day_container_main_main_default, 0);
	lv_style_set_border_color(&style_screen_passcode_day_container_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_border_width(&style_screen_passcode_day_container_main_main_default, 0);
	lv_style_set_border_opa(&style_screen_passcode_day_container_main_main_default, 0);
	lv_style_set_pad_left(&style_screen_passcode_day_container_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_passcode_day_container_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_passcode_day_container_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_passcode_day_container_main_main_default, 0);
	lv_obj_add_style(ui->screen_Passcode_Day_container, &style_screen_passcode_day_container_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_passcode_day_lbl1
	ui->screen_passcode_day_lbl1 = lv_label_create(ui->screen_Passcode_Day_container);
	lv_obj_set_pos(ui->screen_passcode_day_lbl1, 46, 9);
	lv_obj_set_size(ui->screen_passcode_day_lbl1, 98, 18);
	lv_label_set_text(ui->screen_passcode_day_lbl1, "Passcode");
	lv_label_set_long_mode(ui->screen_passcode_day_lbl1, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->screen_passcode_day_lbl1, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_screen_passcode_day_lbl1_main_main_default
	static lv_style_t style_screen_passcode_day_lbl1_main_main_default;
	lv_style_reset(&style_screen_passcode_day_lbl1_main_main_default);
	lv_style_set_radius(&style_screen_passcode_day_lbl1_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_passcode_day_lbl1_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_passcode_day_lbl1_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_passcode_day_lbl1_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_passcode_day_lbl1_main_main_default, 0);
	lv_style_set_text_color(&style_screen_passcode_day_lbl1_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_screen_passcode_day_lbl1_main_main_default, &lv_font_FjallaOne_Regular_22);
	lv_style_set_text_letter_space(&style_screen_passcode_day_lbl1_main_main_default, 0);
	lv_style_set_pad_left(&style_screen_passcode_day_lbl1_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_passcode_day_lbl1_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_passcode_day_lbl1_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_passcode_day_lbl1_main_main_default, 0);
	lv_obj_add_style(ui->screen_passcode_day_lbl1, &style_screen_passcode_day_lbl1_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_passcode_day_lbl2
	ui->screen_passcode_day_lbl2 = lv_label_create(ui->screen_Passcode_Day_container);
	lv_obj_set_pos(ui->screen_passcode_day_lbl2, 68, 35);
	lv_obj_set_size(ui->screen_passcode_day_lbl2, 51, 16);
	lv_label_set_text(ui->screen_passcode_day_lbl2, "123456");
	lv_label_set_long_mode(ui->screen_passcode_day_lbl2, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->screen_passcode_day_lbl2, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_screen_passcode_day_lbl2_main_main_default
	static lv_style_t style_screen_passcode_day_lbl2_main_main_default;
	lv_style_reset(&style_screen_passcode_day_lbl2_main_main_default);
	lv_style_set_radius(&style_screen_passcode_day_lbl2_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_passcode_day_lbl2_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_passcode_day_lbl2_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_passcode_day_lbl2_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_passcode_day_lbl2_main_main_default, 0);
	lv_style_set_text_color(&style_screen_passcode_day_lbl2_main_main_default, lv_color_make(0x70, 0x6f, 0x6f));
	lv_style_set_text_font(&style_screen_passcode_day_lbl2_main_main_default, &lv_font_FjallaOne_Regular_16);
	lv_style_set_text_letter_space(&style_screen_passcode_day_lbl2_main_main_default, 0);
	lv_style_set_pad_left(&style_screen_passcode_day_lbl2_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_passcode_day_lbl2_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_passcode_day_lbl2_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_passcode_day_lbl2_main_main_default, 0);
	lv_obj_add_style(ui->screen_passcode_day_lbl2, &style_screen_passcode_day_lbl2_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_passcode_day_lbl3
	ui->screen_passcode_day_lbl3 = lv_label_create(ui->screen_Passcode_Day_container);
	lv_obj_set_pos(ui->screen_passcode_day_lbl3, 60, 38);
	lv_obj_set_size(ui->screen_passcode_day_lbl3, 7, 9);
	lv_label_set_text(ui->screen_passcode_day_lbl3, "<");
	lv_label_set_long_mode(ui->screen_passcode_day_lbl3, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->screen_passcode_day_lbl3, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_screen_passcode_day_lbl3_main_main_default
	static lv_style_t style_screen_passcode_day_lbl3_main_main_default;
	lv_style_reset(&style_screen_passcode_day_lbl3_main_main_default);
	lv_style_set_radius(&style_screen_passcode_day_lbl3_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_passcode_day_lbl3_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_passcode_day_lbl3_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_passcode_day_lbl3_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_passcode_day_lbl3_main_main_default, 0);
	lv_style_set_text_color(&style_screen_passcode_day_lbl3_main_main_default, lv_color_make(0x98, 0x98, 0x98));
	lv_style_set_text_font(&style_screen_passcode_day_lbl3_main_main_default, &lv_font_FjallaOne_Regular_10);
	lv_style_set_text_letter_space(&style_screen_passcode_day_lbl3_main_main_default, 0);
	lv_style_set_pad_left(&style_screen_passcode_day_lbl3_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_passcode_day_lbl3_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_passcode_day_lbl3_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_passcode_day_lbl3_main_main_default, 0);
	lv_obj_add_style(ui->screen_passcode_day_lbl3, &style_screen_passcode_day_lbl3_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_passcode_day_lbl4
	ui->screen_passcode_day_lbl4 = lv_label_create(ui->screen_Passcode_Day_container);
	lv_obj_set_pos(ui->screen_passcode_day_lbl4, 121, 38);
	lv_obj_set_size(ui->screen_passcode_day_lbl4, 7, 9);
	lv_label_set_text(ui->screen_passcode_day_lbl4, ">");
	lv_label_set_long_mode(ui->screen_passcode_day_lbl4, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_align(ui->screen_passcode_day_lbl4, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_screen_passcode_day_lbl4_main_main_default
	static lv_style_t style_screen_passcode_day_lbl4_main_main_default;
	lv_style_reset(&style_screen_passcode_day_lbl4_main_main_default);
	lv_style_set_radius(&style_screen_passcode_day_lbl4_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_passcode_day_lbl4_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_passcode_day_lbl4_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_passcode_day_lbl4_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_passcode_day_lbl4_main_main_default, 0);
	lv_style_set_text_color(&style_screen_passcode_day_lbl4_main_main_default, lv_color_make(0x70, 0x6f, 0x6f));
	lv_style_set_text_font(&style_screen_passcode_day_lbl4_main_main_default, &lv_font_FjallaOne_Regular_10);
	lv_style_set_text_letter_space(&style_screen_passcode_day_lbl4_main_main_default, 0);
	lv_style_set_pad_left(&style_screen_passcode_day_lbl4_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_passcode_day_lbl4_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_passcode_day_lbl4_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_passcode_day_lbl4_main_main_default, 0);
	lv_obj_add_style(ui->screen_passcode_day_lbl4, &style_screen_passcode_day_lbl4_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);


	//Write codes screen_Tacho_Mid_grey
	ui->screen_Tacho_Mid_grey = lv_img_create(ui->screen);
	lv_obj_set_pos(ui->screen_Tacho_Mid_grey, 0, 7);
	lv_obj_set_size(ui->screen_Tacho_Mid_grey, 240, 306);

	//Write style state: LV_STATE_DEFAULT for style_screen_tacho_mid_grey_main_main_default
	static lv_style_t style_screen_tacho_mid_grey_main_main_default;
	lv_style_reset(&style_screen_tacho_mid_grey_main_main_default);
	lv_style_set_img_recolor(&style_screen_tacho_mid_grey_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_tacho_mid_grey_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_tacho_mid_grey_main_main_default, 255);
	lv_obj_add_style(ui->screen_Tacho_Mid_grey, &style_screen_tacho_mid_grey_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_img_set_src(ui->screen_Tacho_Mid_grey,&Red_night_middle_grey_circler);
	
	



	//Write codes screen_ghost_image
	ui->screen_ghost_image = lv_img_create(ui->screen);
	lv_obj_set_pos(ui->screen_ghost_image, 0, 0);
	lv_obj_set_size(ui->screen_ghost_image, 240, 320);

	//Write style state: LV_STATE_DEFAULT for style_screen_ghost_image_main_main_default
	static lv_style_t style_screen_ghost_image_main_main_default;
	lv_style_reset(&style_screen_ghost_image_main_main_default);
	lv_style_set_img_recolor(&style_screen_ghost_image_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_img_recolor_opa(&style_screen_ghost_image_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_ghost_image_main_main_default, 255);
	lv_obj_add_style(ui->screen_ghost_image, &style_screen_ghost_image_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->screen_ghost_image, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_ghost_image,&_1_240x320);
	lv_img_set_pivot(ui->screen_ghost_image, 0,0);
	lv_img_set_angle(ui->screen_ghost_image, 0);
}

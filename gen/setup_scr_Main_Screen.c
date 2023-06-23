/*
 * Copyright 2022 NXP
 * SPDX-License-Identifier: MIT
 */

#include "lvgl/lvgl.h"
#include <stdio.h>
#include "gui_guider.h"
#include "events_init.h"
#include "custom.h"


void setup_scr_Main_Screen(lv_ui *ui){

	//Write codes Main_Screen
	ui->Main_Screen = lv_obj_create(NULL);

	//Write style state: LV_STATE_DEFAULT for style_main_screen_main_main_default
	static lv_style_t style_main_screen_main_main_default;
	lv_style_reset(&style_main_screen_main_main_default);
	lv_style_set_bg_color(&style_main_screen_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_bg_opa(&style_main_screen_main_main_default, 255);
	lv_obj_add_style(ui->Main_Screen, &style_main_screen_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Main_Screen_Welcome_img
	ui->Main_Screen_Welcome_img = lv_img_create(ui->Main_Screen);
	lv_obj_set_pos(ui->Main_Screen_Welcome_img, 0, 0);
	lv_obj_set_size(ui->Main_Screen_Welcome_img, 240, 320);

	//Write style state: LV_STATE_DEFAULT for style_main_screen_welcome_img_main_main_default
	static lv_style_t style_main_screen_welcome_img_main_main_default;
	lv_style_reset(&style_main_screen_welcome_img_main_main_default);
	lv_style_set_img_recolor(&style_main_screen_welcome_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_main_screen_welcome_img_main_main_default, 0);
	lv_style_set_img_opa(&style_main_screen_welcome_img_main_main_default, 255);
	lv_obj_add_style(ui->Main_Screen_Welcome_img, &style_main_screen_welcome_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->Main_Screen_Welcome_img, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->Main_Screen_Welcome_img,&_1_240x320);
	lv_img_set_pivot(ui->Main_Screen_Welcome_img, 0,0);
	lv_img_set_angle(ui->Main_Screen_Welcome_img, 0);
}
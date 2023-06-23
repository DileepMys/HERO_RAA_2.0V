/*
 * Copyright 2022 NXP
 * SPDX-License-Identifier: MIT
 */

#include "lvgl/lvgl.h"

#include "lvgl/lvgl.h"

#include "lvgl/lvgl.h"

#ifndef LV_ATTRIBUTE_MEM_ALIGN
#define LV_ATTRIBUTE_MEM_ALIGN
#endif

#ifndef LV_ATTRIBUTE_IMG_DAY_DOWN_BTN_PRESSED
#define LV_ATTRIBUTE_IMG_DAY_DOWN_BTN_PRESSED
#endif

const LV_ATTRIBUTE_MEM_ALIGN LV_ATTRIBUTE_IMG_DAY_DOWN_BTN_PRESSED uint8_t day_down_btn_pressed_map[] = {
#if LV_COLOR_DEPTH == 16 && LV_COLOR_16_SWAP == 0
  /*Pixel format: Alpha 8 bit, Red: 5 bit, Green: 6 bit, Blue: 5 bit*/
  0xc0, 0xfb, 0xc2, 0xc0, 0xfb, 0xc9, 0x80, 0xfb, 0x12, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfc, 0x0a, 0xc0, 0xfb, 0xa8, 0xc0, 0xfb, 0xa1, 
  0xc0, 0xfb, 0xd3, 0xc0, 0xfb, 0xff, 0xc0, 0xfb, 0xcb, 0xa0, 0xfb, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfc, 0x06, 0xc0, 0xfb, 0xb6, 0xc0, 0xfb, 0xff, 0xc0, 0xfb, 0xe0, 
  0xa0, 0xfb, 0x1c, 0xa0, 0xfb, 0xde, 0xc0, 0xfb, 0xff, 0xc0, 0xfb, 0xc6, 0xa0, 0xfb, 0x0d, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfc, 0x06, 0xa0, 0xfb, 0xaf, 0xc0, 0xfb, 0xff, 0xc0, 0xfb, 0xeb, 0xa0, 0xfb, 0x2d, 
  0x00, 0x00, 0x00, 0xe0, 0xfb, 0x21, 0xc0, 0xfb, 0xe3, 0xc0, 0xfb, 0xff, 0xc0, 0xfb, 0xc0, 0x00, 0xfc, 0x0a, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xa0, 0xfa, 0x03, 0xc0, 0xfb, 0xa9, 0xc0, 0xfb, 0xff, 0xc0, 0xfb, 0xf0, 0xc0, 0xfb, 0x33, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xa0, 0xfb, 0x25, 0xc0, 0xfb, 0xe6, 0xc0, 0xfb, 0xff, 0xc0, 0xfb, 0xba, 0x00, 0xfc, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xa0, 0xfa, 0x03, 0xc0, 0xfb, 0xa1, 0xc0, 0xfb, 0xff, 0xc0, 0xfb, 0xf1, 0xa0, 0xfb, 0x38, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0xfb, 0x2a, 0xc0, 0xfb, 0xea, 0xc0, 0xfb, 0xff, 0xc0, 0xfb, 0xb5, 0x00, 0xfc, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf8, 0x01, 0xc0, 0xfb, 0x9b, 0xc0, 0xfb, 0xff, 0xc0, 0xfb, 0xf5, 0xc0, 0xfb, 0x3d, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xa0, 0xfb, 0x2f, 0xc0, 0xfb, 0xed, 0xc0, 0xfb, 0xff, 0xc0, 0xfb, 0xae, 0x00, 0xfc, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf8, 0x01, 0xc0, 0xfb, 0x92, 0xc0, 0xfb, 0xff, 0xc0, 0xfb, 0xf6, 0xc0, 0xfb, 0x44, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0xfb, 0x35, 0xc0, 0xfb, 0xf0, 0xc0, 0xfb, 0xff, 0xc0, 0xfb, 0xa8, 0xa0, 0xfa, 0x03, 0x00, 0x00, 0x00, 0xc0, 0xfb, 0x8c, 0xc0, 0xfb, 0xff, 0xc0, 0xfb, 0xf9, 0xa0, 0xfb, 0x49, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xa0, 0xfb, 0x3a, 0xc0, 0xfb, 0xf3, 0xc0, 0xfb, 0xff, 0xc0, 0xfb, 0xa4, 0xa0, 0xfb, 0x8d, 0xc0, 0xfb, 0xff, 0xc0, 0xfb, 0xfa, 0xc0, 0xfb, 0x51, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0xfb, 0x40, 0xc0, 0xfb, 0xf5, 0xc0, 0xfb, 0xff, 0xc0, 0xfb, 0xff, 0xc0, 0xfb, 0xfc, 0xa0, 0xfb, 0x56, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0xfb, 0x44, 0xc0, 0xfb, 0xe1, 0xc0, 0xfb, 0xea, 0xa0, 0xfb, 0x58, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
#endif
#if LV_COLOR_DEPTH == 16 && LV_COLOR_16_SWAP != 0
  /*Pixel format: Alpha 8 bit, Red: 5 bit, Green: 6 bit, Blue: 5 bit  BUT the 2  color bytes are swapped*/
  0xfb, 0xc0, 0xc2, 0xfb, 0xc0, 0xc9, 0xfb, 0x80, 0x12, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfc, 0x00, 0x0a, 0xfb, 0xc0, 0xa8, 0xfb, 0xc0, 0xa1, 
  0xfb, 0xc0, 0xd3, 0xfb, 0xc0, 0xff, 0xfb, 0xc0, 0xcb, 0xfb, 0xa0, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfc, 0x00, 0x06, 0xfb, 0xc0, 0xb6, 0xfb, 0xc0, 0xff, 0xfb, 0xc0, 0xe0, 
  0xfb, 0xa0, 0x1c, 0xfb, 0xa0, 0xde, 0xfb, 0xc0, 0xff, 0xfb, 0xc0, 0xc6, 0xfb, 0xa0, 0x0d, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfc, 0x00, 0x06, 0xfb, 0xa0, 0xaf, 0xfb, 0xc0, 0xff, 0xfb, 0xc0, 0xeb, 0xfb, 0xa0, 0x2d, 
  0x00, 0x00, 0x00, 0xfb, 0xe0, 0x21, 0xfb, 0xc0, 0xe3, 0xfb, 0xc0, 0xff, 0xfb, 0xc0, 0xc0, 0xfc, 0x00, 0x0a, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfa, 0xa0, 0x03, 0xfb, 0xc0, 0xa9, 0xfb, 0xc0, 0xff, 0xfb, 0xc0, 0xf0, 0xfb, 0xc0, 0x33, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfb, 0xa0, 0x25, 0xfb, 0xc0, 0xe6, 0xfb, 0xc0, 0xff, 0xfb, 0xc0, 0xba, 0xfc, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfa, 0xa0, 0x03, 0xfb, 0xc0, 0xa1, 0xfb, 0xc0, 0xff, 0xfb, 0xc0, 0xf1, 0xfb, 0xa0, 0x38, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfb, 0xc0, 0x2a, 0xfb, 0xc0, 0xea, 0xfb, 0xc0, 0xff, 0xfb, 0xc0, 0xb5, 0xfc, 0x00, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf8, 0x00, 0x01, 0xfb, 0xc0, 0x9b, 0xfb, 0xc0, 0xff, 0xfb, 0xc0, 0xf5, 0xfb, 0xc0, 0x3d, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfb, 0xa0, 0x2f, 0xfb, 0xc0, 0xed, 0xfb, 0xc0, 0xff, 0xfb, 0xc0, 0xae, 0xfc, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf8, 0x00, 0x01, 0xfb, 0xc0, 0x92, 0xfb, 0xc0, 0xff, 0xfb, 0xc0, 0xf6, 0xfb, 0xc0, 0x44, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfb, 0xc0, 0x35, 0xfb, 0xc0, 0xf0, 0xfb, 0xc0, 0xff, 0xfb, 0xc0, 0xa8, 0xfa, 0xa0, 0x03, 0x00, 0x00, 0x00, 0xfb, 0xc0, 0x8c, 0xfb, 0xc0, 0xff, 0xfb, 0xc0, 0xf9, 0xfb, 0xa0, 0x49, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfb, 0xa0, 0x3a, 0xfb, 0xc0, 0xf3, 0xfb, 0xc0, 0xff, 0xfb, 0xc0, 0xa4, 0xfb, 0xa0, 0x8d, 0xfb, 0xc0, 0xff, 0xfb, 0xc0, 0xfa, 0xfb, 0xc0, 0x51, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfb, 0xc0, 0x40, 0xfb, 0xc0, 0xf5, 0xfb, 0xc0, 0xff, 0xfb, 0xc0, 0xff, 0xfb, 0xc0, 0xfc, 0xfb, 0xa0, 0x56, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfb, 0xc0, 0x44, 0xfb, 0xc0, 0xe1, 0xfb, 0xc0, 0xea, 0xfb, 0xa0, 0x58, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
#endif
};

const lv_img_dsc_t day_down_btn_pressed = {
  .header.always_zero = 0,
  .header.w = 20,
  .header.h = 11,
  .data_size = 220 * LV_COLOR_SIZE / 8,
  .header.cf = LV_IMG_CF_TRUE_COLOR_ALPHA,
  .data = day_down_btn_pressed_map,
};
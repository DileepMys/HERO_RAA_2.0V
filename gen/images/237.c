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

#ifndef LV_ATTRIBUTE_IMG__TRIANGLE_2X4
#define LV_ATTRIBUTE_IMG__TRIANGLE_2X4
#endif

const LV_ATTRIBUTE_MEM_ALIGN LV_ATTRIBUTE_IMG__TRIANGLE_2X4 uint8_t _triangle_2x4_map[] = {
#if LV_COLOR_DEPTH == 16 && LV_COLOR_16_SWAP == 0
  /*Pixel format: Alpha 8 bit, Red: 5 bit, Green: 6 bit, Blue: 5 bit*/
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
#endif
#if LV_COLOR_DEPTH == 16 && LV_COLOR_16_SWAP != 0
  /*Pixel format: Alpha 8 bit, Red: 5 bit, Green: 6 bit, Blue: 5 bit  BUT the 2  color bytes are swapped*/
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
#endif
};

const lv_img_dsc_t _triangle_2x4 = {
  .header.always_zero = 0,
  .header.w = 2,
  .header.h = 4,
  .data_size = 8 * LV_COLOR_SIZE / 8,
  .header.cf = LV_IMG_CF_TRUE_COLOR_ALPHA,
  .data = _triangle_2x4_map,
};

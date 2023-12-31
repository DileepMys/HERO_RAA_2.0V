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

#ifndef LV_ATTRIBUTE_IMG__IMG_TRIP_UP_ARROW_9X9
#define LV_ATTRIBUTE_IMG__IMG_TRIP_UP_ARROW_9X9
#endif

const LV_ATTRIBUTE_MEM_ALIGN LV_ATTRIBUTE_IMG__IMG_TRIP_UP_ARROW_9X9 uint8_t _img_trip_up_arrow_9x9_map[] = {
#if LV_COLOR_DEPTH == 16 && LV_COLOR_16_SWAP == 0
  /*Pixel format: Red: 5 bit, Green: 6 bit, Blue: 5 bit*/
  0x00, 0x00, 0x00, 0x00, 0x08, 0x42, 0xbe, 0xf7, 0xff, 0xff, 0xbe, 0xf7, 0x08, 0x42, 0x00, 0x00, 0x00, 0x00, 
  0x20, 0x00, 0x00, 0x00, 0xf7, 0xbd, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf7, 0xbd, 0x00, 0x00, 0x20, 0x00, 
  0x00, 0x00, 0xcf, 0x7b, 0xbe, 0xf7, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xbe, 0xf7, 0xcf, 0x7b, 0x00, 0x00, 
  0x45, 0x29, 0x79, 0xce, 0xff, 0xff, 0xdf, 0xff, 0x5d, 0xef, 0xdf, 0xff, 0xff, 0xff, 0x79, 0xce, 0xc3, 0x18, 
  0x71, 0x8c, 0xff, 0xff, 0xff, 0xff, 0xfb, 0xde, 0x20, 0x00, 0xfb, 0xde, 0xff, 0xff, 0xff, 0xff, 0x71, 0x8c, 
  0x10, 0x84, 0xff, 0xff, 0xff, 0xff, 0xcf, 0x7b, 0x00, 0x00, 0xcf, 0x7b, 0xff, 0xff, 0xff, 0xff, 0x9e, 0xf7, 
  0xdb, 0xde, 0xff, 0xff, 0x38, 0xc6, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x38, 0xc6, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0x7d, 0xef, 0x2c, 0x63, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x2c, 0x63, 0x7d, 0xef, 0xff, 0xff, 
  0xff, 0xff, 0xd7, 0xbd, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xd7, 0xbd, 0xff, 0xff, 
#endif
#if LV_COLOR_DEPTH == 16 && LV_COLOR_16_SWAP != 0
  /*Pixel format: Red: 5 bit, Green: 6 bit, Blue: 5 bit BUT the 2 bytes are swapped*/
  0x00, 0x00, 0x00, 0x00, 0x42, 0x08, 0xf7, 0xbe, 0xff, 0xff, 0xf7, 0xbe, 0x42, 0x08, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x20, 0x00, 0x00, 0xbd, 0xf7, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xbd, 0xf7, 0x00, 0x00, 0x00, 0x20, 
  0x00, 0x00, 0x7b, 0xcf, 0xf7, 0xbe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf7, 0xbe, 0x7b, 0xcf, 0x00, 0x00, 
  0x29, 0x45, 0xce, 0x79, 0xff, 0xff, 0xff, 0xdf, 0xef, 0x5d, 0xff, 0xdf, 0xff, 0xff, 0xce, 0x79, 0x18, 0xc3, 
  0x8c, 0x71, 0xff, 0xff, 0xff, 0xff, 0xde, 0xfb, 0x00, 0x20, 0xde, 0xfb, 0xff, 0xff, 0xff, 0xff, 0x8c, 0x71, 
  0x84, 0x10, 0xff, 0xff, 0xff, 0xff, 0x7b, 0xcf, 0x00, 0x00, 0x7b, 0xcf, 0xff, 0xff, 0xff, 0xff, 0xf7, 0x9e, 
  0xde, 0xdb, 0xff, 0xff, 0xc6, 0x38, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc6, 0x38, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xef, 0x7d, 0x63, 0x2c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x63, 0x2c, 0xef, 0x7d, 0xff, 0xff, 
  0xff, 0xff, 0xbd, 0xd7, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xbd, 0xd7, 0xff, 0xff, 
#endif
};

const lv_img_dsc_t _img_trip_up_arrow_9x9 = {
  .header.always_zero = 0,
  .header.w = 9,
  .header.h = 9,
  .data_size = 81 * LV_COLOR_SIZE / 8,
  .header.cf = LV_IMG_CF_TRUE_COLOR,
  .data = _img_trip_up_arrow_9x9_map,
};

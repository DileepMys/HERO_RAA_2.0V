/*
 * lvgl_app.h
 *
 *  Created on: 23-Mar-2022
 *      Author: Admin
 */

#ifndef LVGL_APP_H_
#define LVGL_APP_H_

/* Kernel includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
#include "../lvgl/lvgl.h"
#include "Button_Manager_Cfg.h"
#include "lvgl_app.h"

#define lvgl_task_PRIORITY (configMAX_PRIORITIES - 2)


/* MACRO USED FOR BUTTON PRESS DETECTION */

#define BUTTON_RELEASED			0U

#define BUTTON_SHORT_PRESSED	1U

#define BUTTON_LONG_PRESSED		2U

#define BUTTON_LONG_PRESS_AND_HOLD		3U

#define g_RTC_NVM_Block_Id_u32  17

#define RTCNVM_STORAGE_BYTES   6

/* NUMBER OF IMAGES CONFIGURED FOR FULL SCALE OF TACH0 */
#define TOTAL_NUMBER_OF_TACHO_IMG   33

/* TOTAL SWIPE COUNT   task rate - 100ms ,  full swipe time - 700ms ,   700/100 = 7 */
#define TACHO_FULL_SWIPE_COUNT		7

#define MAX_DISPLAYABLE_YEAR   2050

#define MIN_DISPLAYABLE_YEAR    2022

#define HANDLE_BAR_BUTTON_STATUS(x)                      HMI_Get_Handle_Bar_Btn_Status(x)

/**
* @brief This macro is used to define a minimum vehicle speed required to navigate to setting menu screen 
* @Unit:  km
* @Resolution:1 
* @Range: 1 to 10km
* @Applicability: 
* @Note:  
*/
#define HMI_USM_ALLOWED_VEHICLE_SPEED  10

typedef struct
{
    uint32_t g_tacho_img_num;
    uint8_t Feature_text_X;
    uint8_t Feature_text_Y;
    uint8_t Feature_text_W;
    uint8_t Feature_text_H;
    const lv_img_dsc_t *g_tacho_img;
}g_Tacho_image;

typedef struct
{
    uint32_t g_fuel_img_num;
    uint8_t Feature_fuel_text_X;
    uint16_t Feature_fuel_text_Y;
    uint8_t Feature_fuel_text_W;
    uint8_t Feature_fuel_text_H;
    const lv_img_dsc_t *g_fuel_img;
}g_fuel_image;



typedef struct
{
    uint8_t Entry_Img_No;
}HMI_FUEL_IMAGE_TABLE_ST;



typedef struct
{
    uint32_t g_Welcome_img_num;
    const lv_img_dsc_t *g_Welcome_img;
}g_Wel_Ani_image;

typedef enum
{
    MAIN_SCREEN_TO_SETTING_SCREEN = 0,
    MAIN_SCREEN_TO_AUDIO_SCREEEN,
    MAIN_SCREEN_TO_NAVIGATION_SCREEN,
    MAIN_SCREEN_TO_INTERMEDIATE_SCREEN,
    INTERMEDIATE_SCREEN_TO_SETTING_SCREEN,
    MAIN_SCREEN_TO_CALL_SCREEN,
    SETTING_SCREEN_TO_MAIN_SCREEN,
    SETTING_SCREEN_TO_INTERMEDIATE_SCREEN,
    AUDIO_SCREEN_MAIN_SCREEN
}SCREEN_TRANSITON_EN;


typedef struct 
{
   uint8_t day;
   uint8_t month;
   uint16_t year;
   uint8_t minute;
   uint8_t hour;
}g_RTC_DATE_TIME_ST;




/* HMI Presentation Layer States */
typedef enum HMI_PST_State
{
  HMI_PST_IDLE  = 0,                   /* IDLE */
  HMI_PST_WELCOME_SCREEN,
  HMI_PSI_CLEAN_SCREEN,
  HMI_PST_HOME_SCREEN ,  
  HMI_PST_INTERMEDIATE_SCREEN ,  
  HMI_PST_SETTING_SCREEN,           
  HMI_PST_CLOCK_SETTING ,
  HMI_BLOCK_STATE,
  HMI_PST_BLE_NAVIGATION_SCREEN
} hmi_pst_state_EN;

/* HMI WELCOME ANIMATION STATES*/
typedef enum
{
    WELCOME_ANIMATION_NOT_STARTED = 0,
    WELCOME_ANIMATION_STARTED,
    WELCOME_ANIMATION_INPROGRESS,
    WELCOME_ANIMATION_COMPLETED
}HMI_WELCOME_ANIMATION_ST_EN;

#define Welcome_Animation_table     {0,&w7_240x320},\
{1,&w10_240x320},\
{2,&w13_240x320},\
{3,&w19_240x320},\
{4,&w22_240x320},\
{5,&w28_240x320},\
{6,&w31_240x320},\
{7,&w34_240x320},\
{8,&w37_240x320},\
{9,&w40_240x320},\
{10,&w43_240x320},\
{11,&w46_240x320},\
{12,&w52_240x320},\
{13,&w55_240x320},\
{14,&w58_240x320},\
{15,&w61_240x320},\
{16,&w64_240x320},\
{17,&w67_240x320},\
{18,&w73_240x320},\
{19,&w76_240x320}

                                                                       
                                   
                                                    




                               
 #define FUEL_IMAGE_TABLE            {0 ,44, 265 , 85, 40 ,       &img_night_fuel_fill_00},\
                                     {1  ,41, 265, 88, 40 ,       &img_night_fuel_fill_01},\
                                     {2  ,41, 265, 88, 40 ,       &img_night_fuel_fill_02},\
                                     {3  , 41, 265, 88, 40 ,      &img_night_fuel_fill_03},\
                                     {4  , 41, 265, 88, 40 ,      &img_night_fuel_fill_04},\
                                     {5   ,41, 265, 88, 40 ,      &img_night_fuel_fill_05},\
                                     {6   ,41, 265, 88, 40 ,      &img_night_fuel_fill_06},\
                                     {7   ,41, 265, 88, 40 ,      &img_night_fuel_fill_07},\
                                     {8  , 41, 265, 88, 40 ,      &img_night_fuel_fill_08},\
                                     {9  , 41, 265, 88, 40 ,      &img_night_fuel_fill_09},\
                                     {10 ,  41, 265, 88, 40 ,     &img_night_fuel_fill_09_white_icon},\
                                     {11  , 41, 265, 88, 40 ,     &img_night_fuel_fill_11},\
                                     {12  , 41, 265, 88, 40 ,     &img_night_fuel_fill_12},\
                                     {13  , 41, 265, 88, 40 ,     &img_night_fuel_fill_13},\
                                     {14  ,41, 265, 88, 40 ,      &img_night_fuel_fill_14},\
                                     {15   ,41, 265, 88, 40 ,     &img_night_fuel_fill_15},\
                                     {16   ,41, 265, 88, 40 ,     &img_night_fuel_fill_16},\
                                     {17   ,41, 265, 88, 40 ,     &img_night_fuel_fill_17},\
                                     {18   ,41, 265, 88, 40 ,     &img_night_fuel_fill_18},\
                                     {19   ,41, 265, 88, 40 ,     &img_night_fuel_fill_19},\
                                     {20   ,41, 265, 88, 40 ,     &img_night_fuel_fill_20},\
                                     {21   ,41, 265, 88, 40 ,     &img_night_fuel_fill_21},\
                                     {22   ,41, 265,  88, 41 ,    &img_night_fuel_fill_22},\
                                     {23   ,41, 265,  88, 41 ,    &img_night_fuel_fill_23},\
                                     {24   ,41, 265,  88, 42 ,    &img_night_fuel_fill_24},\
                                     {25   ,41, 265,  88, 42 ,    &img_night_fuel_fill_25},\
                                     {26   ,41, 265,  88, 42 ,    &img_night_fuel_fill_26},\
                                     {27   ,41, 265,  88, 43 ,    &img_night_fuel_fill_27},\
                                     {28   ,41, 265, 88, 43 ,     &img_night_fuel_fill_28},\
                                     {29   ,41, 265, 88, 43 ,     &img_night_fuel_fill_29},\
                                     {30   ,41, 265, 88, 43 ,     &img_night_fuel_fill_30},\
                                     {31   ,41, 265, 88, 43 ,     &img_night_fuel_fill_31},\
                                     {32  ,41, 265, 88, 43 ,      &img_night_fuel_fill_32},\
                                     {33   ,41, 265, 88, 43 ,     &img_night_fuel_fill_33},\
                                     {34  ,41, 265, 88, 43 ,      &img_night_fuel_fill_34},\
                                     {35   ,41, 265, 88, 43 ,     &img_night_fuel_fill_35},\
                                     {36   ,41, 265, 88, 43 ,     &img_night_fuel_fill_36},\
                                     {37   ,41, 265, 91, 43 ,     &img_night_fuel_fill_37},\
                                     {38   ,41, 265,  93, 43 ,    &img_night_fuel_fill_38},\
                                     {39   ,41, 265,  96, 43 ,    &img_night_fuel_fill_39},\
                                     {40   ,41, 265,  98, 43 ,    &img_night_fuel_fill_40},\
                                     {41   ,41, 265, 101, 43 ,    &img_night_fuel_fill_41},\
                                     {42   ,41, 265, 103, 43 ,    &img_night_fuel_fill_42},\
                                     {43   ,41, 265, 106, 43 ,    &img_night_fuel_fill_43},\
                                     {44   ,41, 265, 108, 43 ,    &img_night_fuel_fill_44},\
                                     {45   ,41, 265, 111, 43 ,    &img_night_fuel_fill_45},\
                                     {46   ,41, 265, 113, 43 ,    &img_night_fuel_fill_46},\
                                     {47   ,41, 265, 116, 43 ,    &img_night_fuel_fill_47},\
                                     {48   ,41, 265, 118, 43 ,    &img_night_fuel_fill_48},\
                                     {49   ,41, 265, 121, 43 ,    &img_night_fuel_fill_49},\
                                     {50   ,41, 265, 123, 43 ,    &img_night_fuel_fill_50},\
                                     {51   ,41, 265, 126, 43 ,    &img_night_fuel_fill_51},\
                                     {52   ,41, 265, 128, 43 ,    &img_night_fuel_fill_52},\
                                     {53   ,41, 265, 131, 43 ,    &img_night_fuel_fill_53},\
                                     {54   ,41, 265, 133, 43 ,    &img_night_fuel_fill_54},\
                                     {55   ,41, 265, 135, 43 ,    &img_night_fuel_fill_55},\
                                     {56   ,41, 265, 138, 43 ,    &img_night_fuel_fill_56},\
                                     {57   ,41, 265, 140, 43 ,    &img_night_fuel_fill_57},\
                                     {58   ,41, 265, 143, 43 ,    &img_night_fuel_fill_58},\
                                     {59   ,41, 265, 145, 43 ,    &img_night_fuel_fill_59},\
                                     {60   ,41, 265, 147, 43 ,    &img_night_fuel_fill_60},\
                                     {61   ,41, 265, 149, 43 ,    &img_night_fuel_fill_61},\
                                     {62   ,41, 265, 152, 43 ,    &img_night_fuel_fill_62},\
                                     {63   ,41, 265, 154, 43 ,    &img_night_fuel_fill_63},\
                                     {64   ,41, 265, 156, 43 ,    &img_night_fuel_fill_64},\
                                     {65   ,41, 265, 158, 43 ,    &img_night_fuel_fill_65},\
                                     {66   ,41, 265, 158, 43 ,    &img_night_fuel_fill_66}         
                                        

 #define TACHO_IMAGE_TABLE              { 0 ,       7, 6, 227, 75 ,      &img_tacho_chaplets },\
                                        { 4 ,       6, 64, 26, 22 ,      &img_night_tacho_fill_000 },\
                                        { 8 ,      6, 63, 27, 23,   &img_night_tacho_fill_001 },\
                                        { 13 ,      6, 62, 27, 24,   &img_night_tacho_fill_002 },\
                                        { 17 ,     6, 61, 28, 25,  &img_night_tacho_fill_003 },\
                                        { 22 ,     6, 60, 29, 26,   &img_night_tacho_fill_004 },\
                                        { 26 ,     6, 60, 29, 26,  &img_night_tacho_fill_005 },\
                                        { 31 ,     6, 60, 30, 26,  &img_night_tacho_fill_006 },\
                                        { 35 ,     6, 60, 31, 26,   &img_night_tacho_fill_007 },\
                                        { 40 ,     6, 56, 31, 30,  &img_night_tacho_fill_008 },\
                                        { 44 ,     6, 55, 32, 31,  &img_night_tacho_fill_009 },\
                                        { 49 ,     6, 54, 33, 32,  &img_night_tacho_fill_010 },\
                                        { 53 ,     6, 54, 34, 32,   &img_night_tacho_fill_011 },\
                                        { 57 ,     6, 53, 34, 33,  &img_night_tacho_fill_012 },\
                                        { 62 ,     6, 52, 35, 34,  &img_night_tacho_fill_013 },\
                                        { 66 ,     6, 51, 36, 35,  &img_night_tacho_fill_014 },\
                                        { 71 ,     6, 50, 37, 36,   &img_night_tacho_fill_015 },\
                                        { 75 ,     6, 49, 37, 37,  &img_night_tacho_fill_016 },\
                                        { 80 ,     6, 48, 38, 38,  &img_night_tacho_fill_017 },\
                                        { 84 ,     6, 48, 39, 38,   &img_night_tacho_fill_018 },\
                                        { 89 ,     6, 47, 40, 39,   &img_night_tacho_fill_019 },\
                                        { 93 ,     6, 46, 40, 40,   &img_night_tacho_fill_020 },\
                                        { 98 ,     6, 45, 41, 41,   &img_night_tacho_fill_021 },\
                                        { 102 ,     6, 44, 42, 42,   &img_night_tacho_fill_022 },\
                                        { 106 ,     6, 43, 43, 43,   &img_night_tacho_fill_023 },\
                                        { 112 ,    6, 43, 44, 43,  &img_night_tacho_fill_024 },\
                                        { 113 ,    6, 42, 44, 44,  &img_night_tacho_fill_025 },\
                                        { 114 ,    6, 41, 45, 45,  &img_night_tacho_fill_026 },\
                                        { 115 ,    6, 40, 46, 46,   &img_night_tacho_fill_027 },\
                                        { 117 ,    6, 40, 47, 46,  &img_night_tacho_fill_028 },\
                                        { 120 ,    6, 39, 48, 47,  &img_night_tacho_fill_029 },\
                                        { 124 ,    6, 38, 48, 48,  &img_night_tacho_fill_030 },\
                                        { 129 ,    6, 37, 49, 49, &img_night_tacho_fill_031 },\
                                        { 133 ,    6, 37, 50, 49, &img_night_tacho_fill_032 },\
                                        { 138 ,    6, 36, 51, 50, &img_night_tacho_fill_033 },\
                                        { 142 ,    6, 35, 52, 51,  &img_night_tacho_fill_034 },\
                                        { 147 ,    6, 35, 53, 51,  &img_night_tacho_fill_035 },\
                                        { 151 ,    6, 34, 54, 52, &img_night_tacho_fill_036 },\
                                        { 155 ,    6, 33, 54, 53,   &img_night_tacho_fill_037 },\
                                        { 160 ,    6, 32, 55, 54, &img_night_tacho_fill_038 },\
                                        { 164 ,    6, 32, 56, 54,  &img_night_tacho_fill_039 },\
                                        { 169 ,    6, 31, 57, 55, &img_night_tacho_fill_040 },\
                                        { 173 ,    6, 31, 58, 55, &img_night_tacho_fill_041 },\
                                        { 178 ,    6, 30, 59, 56, &img_night_tacho_fill_042 },\
                                        { 182 ,    6, 29, 60, 57,  &img_night_tacho_fill_043 },\
                                        { 187 ,    6, 29, 61, 57,  &img_night_tacho_fill_044 },\
                                        { 191 ,    6, 28, 62, 58, &img_night_tacho_fill_045 },\
                                        { 196 ,    6, 28, 63, 58,  &img_night_tacho_fill_046 },\
                                        { 200 ,    6, 27, 63, 59,  &img_night_tacho_fill_047 },\
                                        { 204 ,    6, 26, 64, 60,   &img_night_tacho_fill_048 },\
                                        { 209 ,    6, 26, 65, 60,  &img_night_tacho_fill_049 },\
                                        { 213 ,    6, 25, 66, 61,  &img_night_tacho_fill_050 },\
                                        { 218 ,    6, 25, 67,61,  &img_night_tacho_fill_051 },\
                                        { 222 ,    6, 25, 68, 61, &img_night_tacho_fill_052 },\
                                        { 225 ,    6,25,69,61, &img_night_tacho_fill_053 },\
                                        { 230 ,    6,23,70,63,  &img_night_tacho_fill_054 },\
                                        { 240 ,    6,23,71,63, &img_night_tacho_fill_055 },\
                                        { 250 ,    6,22,72,64,  &img_night_tacho_fill_056 },\
                                        { 255 ,    6,22,73,64, &img_night_tacho_fill_057 },\
                                        { 260 ,    6,21,74,65,  &img_night_tacho_fill_058 },\
                                        { 267 ,    6, 21, 75, 65,&img_night_tacho_fill_059 },\
                                        { 271 ,    6, 20,76, 66,  &img_night_tacho_fill_060 },\
                                        { 276 ,    6, 20, 77, 66,  &img_night_tacho_fill_061 },\
                                        { 280 ,    6,20,78, 66,  &img_night_tacho_fill_062 },\
                                        { 285 ,    6, 19, 78, 67, &img_night_tacho_fill_063 },\
                                        { 289 ,    6,19,79, 67,  &img_night_tacho_fill_064 },\
                                        { 294 ,    6, 18, 81,68, &img_night_tacho_fill_065 },\
                                        { 298 ,    6, 18, 82, 68,&img_night_tacho_fill_066 },\
                                        { 302 ,    6,18,82,68,  &img_night_tacho_fill_067 },\
                                        { 307 ,     6, 17,83, 69,&img_night_tacho_fill_068 },\
                                        { 311 ,     6,17,84,69,&img_night_tacho_fill_069 },\
                                        { 316 ,     6, 17, 85, 69, &img_night_tacho_fill_070 },\
                                        { 320 ,     6, 16,86, 70,&img_night_tacho_fill_071 },\
                                        { 325 ,   6,16,87,70,  &img_night_tacho_fill_072 },\
                                        { 329 ,     6,16,88,70,&img_night_tacho_fill_073 },\
                                        { 337 ,     6,15,89,71, &img_night_tacho_fill_074 },\
                                        { 340 ,     6,15,90,71, &img_night_tacho_fill_075 },\
                                        { 343 ,    6,15,91,71, &img_night_tacho_fill_076 },\
                                        { 347 ,    6,14,92,72, &img_night_tacho_fill_077 },\
                                        { 350 ,     6,14,93,72,&img_night_tacho_fill_078 },\
                                        { 355 ,    6,14,94,72, &img_night_tacho_fill_079 },\
                                        { 360 ,    6,14,95,72, &img_night_tacho_fill_080 },\
                                        { 365 ,    6,14,96,72, &img_night_tacho_fill_081 },\
                                        { 369 ,     6,13,97,73,&img_night_tacho_fill_082 },\
                                        { 374 ,    6,13,98,73, &img_night_tacho_fill_083 },\
                                        { 378 ,    6,13,99,73, &img_night_tacho_fill_084 },\
                                        { 383 ,    6,13,100,73, &img_night_tacho_fill_085 },\
                                        { 387 ,    6,13,101,73, &img_night_tacho_fill_086 },\
                                        { 392 ,   6,12,102,74,  &img_night_tacho_fill_087 },\
                                        { 396 ,    6,12,103,74, &img_night_tacho_fill_088 },\
                                        { 400 ,    6,12,104,74, &img_night_tacho_fill_089 },\
                                        { 405 ,    6,12,105,74, &img_night_tacho_fill_090 },\
                                        { 409 ,    6,12,106,74, &img_night_tacho_fill_091 },\
                                        { 414 ,   6,12,107,74,  &img_night_tacho_fill_092 },\
                                        { 418 ,     6,12,108,74,&img_night_tacho_fill_093 },\
                                        { 423 ,     6,12,110,74,&img_night_tacho_fill_094 },\
                                        { 427 ,     6,12,111,74,&img_night_tacho_fill_095 },\
                                        { 432 ,     6,12,112,74,&img_night_tacho_fill_096 },\
                                        { 436 ,    6,12,113,74, &img_night_tacho_fill_097 },\
                                        { 440 ,   6,12,114,74,  &img_night_tacho_fill_098 },\
                                        { 445 ,    6,12,115,74, &img_night_tacho_fill_099 },\
                                        { 450 ,    6,12,116,74, &img_night_tacho_fill_100 },\
                                        { 460 ,    6,12,117,74, &img_night_tacho_fill_101 },\
                                        { 470 ,   6,12,118,74,  &img_night_tacho_fill_102 },\
                                        { 475 ,     6,12,119,74, &img_night_tacho_fill_103 },\
                                        { 480 ,    6,12,121,74, &img_night_tacho_fill_104 },\
                                        { 485 ,     6,12,122,74, &img_night_tacho_fill_105 },\
                                        { 490 ,     6,12,123,74, &img_night_tacho_fill_106 },\
                                        { 495 ,     6,12,124,74,&img_night_tacho_fill_107 },\
                                        { 500 ,    6,12,126,74, &img_night_tacho_fill_108 },\
                                        { 505 ,     6,12,127,74,&img_night_tacho_fill_109 },\
                                        { 510 ,    6,12,128,74, &img_night_tacho_fill_110 },\
                                        { 515 ,     6,12,129,74, &img_night_tacho_fill_111 },\
                                        { 520 ,    6,12,131,74, &img_night_tacho_fill_112 },\
                                        { 525 ,    6,12,132,74,  &img_night_tacho_fill_113 },\
                                        { 530 ,    6,12,133,74, &img_night_tacho_fill_114 },\
                                        { 535 ,    6,12,135,74, &img_night_tacho_fill_115 },\
                                        { 540 ,    6,12,136,74, &img_night_tacho_fill_116 },\
                                        { 545 ,     6,12,137,74,&img_night_tacho_fill_117 },\
                                        { 550 ,    6,12,139,74, &img_night_tacho_fill_118 },\
                                        { 554 ,   6,12,140,74,  &img_night_tacho_fill_119 },\
                                        { 556 ,   6,12,141,74,  &img_night_tacho_fill_120 },\
                                        { 557 ,    6,12,142 ,74,&img_night_tacho_fill_121 },\
                                        { 559 ,    6,12,144,74,  &img_night_tacho_fill_122 },\
                                        { 560 ,    6,12,145,74, &img_night_tacho_fill_123 },\
                                        { 562 ,    6,12,146,74, &img_night_tacho_fill_124 },\
                                        { 565 ,    6,12,147,74, &img_night_tacho_fill_125 },\
                                        { 570 ,     6,12,149,74,&img_night_tacho_fill_126 },\
                                        { 574 ,    6,12,150,74, &img_night_tacho_fill_127 },\
                                        { 579 ,   6,12,151,74,  &img_night_tacho_fill_128 },\
                                        { 583 ,    6,12,152,74, &img_night_tacho_fill_129 },\
                                        { 588 ,     6,12,154,74,&img_night_tacho_fill_130 },\
                                        { 592 ,     6,12,155,74,&img_night_tacho_fill_131 },\
                                        { 597 ,     6,12,156,74,&img_night_tacho_fill_132 },\
                                        { 601 ,     6,12,157,74,&img_night_tacho_fill_133 },\
                                        { 610 ,     6,12,158,74,&img_night_tacho_fill_134 },\
                                        { 620 ,    6,12,160,74, &img_night_tacho_fill_135 },\
                                        { 625 ,     6,12,161,74,&img_night_tacho_fill_136 },\
                                        { 630 ,    6,12,162,74,  &img_night_tacho_fill_137 },\
                                        { 635 ,    6,12,163,74, &img_night_tacho_fill_138 },\
                                        { 640 ,    6,12,165,74, &img_night_tacho_fill_139 },\
                                        { 645 ,    6,12,166,74, &img_night_tacho_fill_140 },\
                                        { 650 ,    6,12,167,74, &img_night_tacho_fill_141 },\
                                        { 655 ,    6,12,168,74, &img_night_tacho_fill_142 },\
                                        { 660 ,    6,12,169,74, &img_night_tacho_fill_143 },\
                                        { 665 ,     6,12,171,74,&img_night_tacho_fill_144 },\
                                        { 670 ,   6,12,171,74,  &img_night_tacho_fill_145 },\
                                        { 675 ,    6,12,172,74, &img_night_tacho_fill_146 },\
                                        { 680 ,    6,12,172,74, &img_night_tacho_fill_147 },\
                                        { 684 ,   6,12,175,74,  &img_night_tacho_fill_148 },\
                                        { 688 ,    6,12,176,74, &img_night_tacho_fill_149 },\
                                        { 692 ,     6,12,178,74,&img_night_tacho_fill_150 },\
                                        { 696 ,     6,12,179,74,&img_night_tacho_fill_151 },\
                                        { 700 ,    6,12,180,74, &img_night_tacho_fill_152 },\
                                        { 704 ,     6,12,181,74,&img_night_tacho_fill_153 },\
                                        { 708 ,    6,12,182,74, &img_night_tacho_fill_154 },\
                                        { 712 ,   6,12,184,74,  &img_night_tacho_fill_155 },\
                                        { 717 ,     6,12,184,74,&img_night_tacho_fill_156 },\
                                        { 721 ,     6,12,186,74,&img_night_tacho_fill_157 },\
                                        { 726 ,     6,12,187,74,&img_night_tacho_fill_158 },\
                                        { 730 ,    6,12,188,74, &img_night_tacho_fill_159 },\
                                        { 734 ,    6,12,189,74, &img_night_tacho_fill_160 },\
                                        { 736 ,     6,12,190,74,&img_night_tacho_fill_161 },\
                                        { 740 ,    6,12,191,74, &img_night_tacho_fill_162 },\
                                        { 743 ,    6,12,192,74, &img_night_tacho_fill_163 },\
                                        { 747 ,    6,12,194,74, &img_night_tacho_fill_164 },\
                                        { 749 ,     6,12,194,74,&img_night_tacho_fill_165 },\
                                        { 752 ,     6,12,196,74,&img_night_tacho_fill_166 },\
                                        { 756 ,    6,12,197,74, &img_night_tacho_fill_167 },\
                                        { 760 ,    6,12,198,74, &img_night_tacho_fill_168 },\
                                        { 764 ,    6,12,199,74, &img_night_tacho_fill_169 },\
                                        { 768 ,    6,12,200,74, &img_night_tacho_fill_170 },\
                                        { 770 ,    6,12,201,74, &img_night_tacho_fill_171 },\
                                        { 776 ,    6,12,202,74, &img_night_tacho_fill_172 },\
                                        { 780 ,    6,12,203,74, &img_night_tacho_fill_173 },\
                                        { 787 ,    6,12,204,74, &img_night_tacho_fill_174 },\
                                        { 791 ,    6,12,205,74, &img_night_tacho_fill_175 },\
                                        { 793 ,    6,12,206,74, &img_night_tacho_fill_176 },\
                                        { 796 ,    6,12,207,74, &img_night_tacho_fill_177 },\
                                        { 800 ,    6,12,208,74, &img_night_tacho_fill_178 },\
                                        { 804 ,    6,12,209,74, &img_night_tacho_fill_179 },\
                                        { 808 ,    6,12,210,74, &img_night_tacho_fill_180 },\
                                        { 812 ,    6,12,211,74, &img_night_tacho_fill_181 },\
                                        { 816 ,    6,12,212,74, &img_night_tacho_fill_182 },\
                                        { 820 ,    6,12,213,74, &img_night_tacho_fill_183 },\
                                        { 824 ,    6,12,214,74, &img_night_tacho_fill_184 },\
                                        { 828 ,    6,12,215,74, &img_night_tacho_fill_185 },\
                                        { 833 ,    6,12,216,74, &img_night_tacho_fill_186 },\
                                        { 837 ,    6,12,217,74, &img_night_tacho_fill_187 },\
                                        { 844 ,    6,12,218,74, &img_night_tacho_fill_188 },\
                                        { 850 ,    6,12,219,74, &img_night_tacho_fill_189 },\
                                        { 855 ,    6,12,220,74, &img_night_tacho_fill_190 },\
                                        { 859 ,    6,12,220,74, &img_night_tacho_fill_191 },\
                                        { 864 ,    6,12,221,74, &img_night_tacho_fill_192 },\
                                        { 868 ,    6,12,221,74, &img_night_tacho_fill_193 },\
                                        { 873 ,    6,12,221,74, &img_night_tacho_fill_194 },\
                                        { 877 ,    6,12,221,74, &img_night_tacho_fill_195 },\
                                        { 882 ,    6,12,225,74, &img_night_tacho_fill_196 },\
                                        { 886 ,    6,12,226,74, &img_night_tacho_fill_197 },\
                                        { 891 ,    6,12,226,74, &img_night_tacho_fill_198 },\
                                        { 895 ,    6,12,227,74, &img_night_tacho_fill_199 },\
                                        { 900 ,    6,12,228,74, &img_night_tacho_fill_200 }





                                      
                                       
//uint8_t flag_24hr = 0;         
void lvgl_app_int(void);         
/* The callback function. */
void SwTimerCallback(void);
void my_disp_flush(lv_disp_drv_t * disp, const lv_area_t * area, lv_color_t * color_p);
void lvgl_task(void *pvParameters);
void screen_busy(void);
uint8_t get_NVM_Status(void);
void Set_NVM_Status(void);
void Clear_NVM_Status(void);

void HMI_Welcome_animation(void);

void Handle_Bar_Set_Btn_CBK(uint8_t Button_Status);
void Handle_Bar_Up_Btn_CBK (uint8_t Button_Status);
void Handle_Bar_Down_Btn_CBK (uint8_t Button_Status);
void Handle_Bar_Return_Btn_CBK (uint8_t Button_Status);
static void Clear_Btn_Events(void);

uint8_t HMI_Get_Handle_Bar_Btn_Status(BM_List_Index_Type_En p_Button_ID);

uint8_t HMI_Setting_Screen_Navigation(void);

void Lvgl_Screen_Change_Req_Process(SCREEN_TRANSITON_EN p_screen_en);

void HMI_TRIP_Timer_SW_Reset_Cmd(uint8_t p_Trip_ID);

void RTC_Set_User_Selected_Date(uint8_t p_day_u8,uint8_t p_month_u8,uint16_t p_year_u16);

void Get_Date_Time(g_RTC_DATE_TIME_ST* p_Date_Time_st);

void RTC_Set_User_Selected_Time(uint8_t p_Hour_u8,uint8_t p_Min_u8);

void GUI_Setting_Screen_Telltale_Handler(void);
void HomeScreenExit(void);
void SettingScreenEntry(void);

void GUI_Main_Screen(void);

/* Telltale */
void GUI_Telltale_Handler(void);

void black_Screen(void);

/* Fuel Bar Display  */
void GUI_Fuelmeter_Handler(void);

void set_AVF_Trip_A_Display_Value(uint32_t fl_displayed_AFE_Value);

void memp(char *s);
void hmi_reset(void);
void GUI_RTC_NVM_Write_Am_Pm(void);
void NVM_Write_RTC_Time_Format(void);
uint8_t NVM_Read_RTC_Time_Format(void);

void HMI_CLK_NVM_check(void);

void Lvgl_Display_Init(void);

bool Lvgl_Get_Active_Screen(void);

void Speed_Digit(uint8_t fl_no_Digit_u8,uint8_t Digit_Selection);

void GUI_Service_remainder_Position_Text(void);


void Oil_Tell_Tale_opa(void);
void set_obj_opa(lv_obj_t *text,uint8_t value );
void set_obj_opa_S(lv_obj_t *text_S,uint8_t value_S );
void Avf_Avs_Idle(void);
void set_AFV_Display_Value(uint32_t fl_displayed_AFE_Value);
void Speed_DigitI(uint8_t fl_no_IDigit_u8,uint8_t DigitIn_Selection);
void GUI_Intermediate_Speedometer_Handler(void);
void HMI_Early_Wake_Up_Animation_Control(void);

void HMI_Set_Service_TT_ON(void);

void HMI_Set_Service_TT_OFF(void);

void HMI_Set_FUEL_FLASH_ON(void);

void HMI_Set_FUEL_FLASH_OFF(void);

void ABS_TT_Set_ON(void);

void ABS_TT_Set_OFF(void);

void ABS_TT_Flash_Handling_TT_Mgr(void);

void Telltale_Previous_Entry(void);

void Lvgl_task_Resume(void);

void Lvgl_Task_Suspend(void);

void GUI_Fuel_Gauge_Handler(uint8_t Current_Bar_Level);

/*!
 * @brief Initialization of TFT Buffers
 */
void TFT_Buffers_Init(void);

void LCDIF_ClearAndUpdateLCDBuffer(void);

void HMI_Fuel_Gauge_Initial_Update(void);

void GUI_Intermediate_Speedometer_Handler_Day(void);

void Speed_DigitI_Day(uint8_t fl_no_IDigit_u8,uint8_t DigitIn_Selection);

void GUI_Main_Screen_Entry(void);

void GUI_Main_Screen_Day(void);

void Odo_MainScreen_Entry(void);

void Intermediate_Speedo_Entry(void);

HMI_WELCOME_ANIMATION_ST_EN HMI_Get_Welcome_Animation_Status(void);

void FuelValueEntry(void);

#endif /* LVGL_APP_H_ */

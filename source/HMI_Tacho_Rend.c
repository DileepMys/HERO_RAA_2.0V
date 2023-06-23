/* @file FILE NAME */
#ifndef HMI_TACHO_REND_C
#define HMI_TACHO_REND_C

/***********************************************************************************************************************
 *    DISCLAIMER
 *   Copyright (C) 2011, 2016 Niyata Infotech Pvt. Ltd. All rights reserved.
 ***********************************************************************************************************************/

/************************************************************************************************************************
 * @author              Author : Palani kumar (palanikumar@niyatainfotech.com)
 ***********************************************************************************************************************/

/***********************************************************************************************************************
 *                                                F I L E  D E S C R I P T I O N
 **----------------------------------------------------------------------------------------------------------------------
 *  @brief
 *
 *  File name                       : HMI_Tacho_Rend.c
 *  Version                         : v1.0.2
 *  Micros supported                : 
 *  Compilers supported             : 
 *  Platforms supported             : 
 *  Description                     : This file consists of definitions of Tacho gague rendering process
 *  @bug
--------------------------------------------------------------------------------------------------------------------*/



/***********************************************************************************************************************
 *                                               I N C L U D E   F I L E S
 ***********************************************************************************************************************/
#include "HMI_Tacho_Rend.h"
#include "lvgl_app.h"
#include "Swc_Tachometer.h"
/***********************************************************************************************************************
*                                               I N C L U D E  LIBRARY F I L E S                                     
***********************************************************************************************************************/
#include "hal_stdtypes.h"
#include "math.h"
/***********************************************************************************************************************
 *                                          M A C R O   D E F I N I T I O N S
 ***********************************************************************************************************************/
/*  
 * @brief: This macro is used to config rend filter scale value
 * @Unit:  
 * @Resolution: 
 * @Range: 
 * @Applicability: 
 */
#define GA_REND_FILTER_SCALE_VALUE  (1<<GA_REND_FILTER_SHIFT)
/*  
 * @brief: This macro is used to config rend filter scale value
 * @Unit:  
 * @Resolution: 
 * @Range: 
 * @Applicability: 
 */
#define GA_REND_FILTER_MASK         (~(GA_REND_FILTER_SCALE_VALUE-1))

#define GA_REND_FILTER_SHIFT       4

#define GA_REND_DIR_DECREASING      (UINT8)1

#define GA_REND_DIR_INCREASING      (UINT8)0
/***********************************************************************************************************************
 *                                          L O C A L  V A R I A B L E   D E F I N I T I O N S
 ***********************************************************************************************************************/
typedef struct
{
   UINT16 TargetHystGx;
   UINT16 CurrentGx;
   UINT32 FSGx;
   UINT32 SSGx;
   UINT8  dirregx;
   UINT8  GSRx_step_counter;
} GA_REND_VAR_STRUCT;

GA_REND_VAR_STRUCT tacho_Rend_Buffer;

/* Structure of the configuration for one gauge */
typedef struct
{
   const UINT16 (*get_value_func)(void);        /* Function to get current target counts */
   const GA_REND_CONST_STRUCT * filter_conf;    /* Configuration table of filter characteristics */
   GA_REND_VAR_STRUCT * rend_buffer;            /* Pointer to filter buffer */
} GA_REND_CONFIG_STRUCT;


static const GA_REND_CONST_STRUCT ga_rend_tacho_const =
{
   GA_REND_TACHO_MAXVELG,
   GA_REND_TACHO_HYSTG,
   GA_REND_TACHO_T1,
   GA_REND_TACHO_T2,
   GA_REND_TACHO_GAUGE_COUNT
};

/*
 * @brief: This variable is used to process tacho rendering process
 * @Unit:  
 * @Resolution: 
 * @Range: 0 to 65535
 * @Applicability: 
 */
static const GA_REND_CONFIG_STRUCT g_Tacho_Rend_Cfg =
{
   &HMI_TACHO_GET_ENGINE_RPM,
   &ga_rend_tacho_const,
   &tacho_Rend_Buffer
};

/*
 * @brief: This variable is used to get Tacho Image Index correspoding to Tacho gauge pointer angle
 * @Unit: 
 * @Resolution: 
 * @Range: 0 to 255
 * @Applicability: 
 */
static uint8_t g_Current_Img_Index;

/*
 * @brief: This variable is used to map Tacho RPM VS Image index
 * @Unit:  
 * @Resolution: 
 * @Range:
 * @Applicability: 
 */
const uint16_t HMI_Tacho_Img_Offset_Tbl[9][2] = 
{
   {  0    ,  0},
   {  112  ,  25},
   {  225  ,  54},
   {  337  ,  75},
   {  450  ,  101},
   {  562  ,  125},
   {  675  ,  147},
   {  787  ,  175},
   {  900  ,  196}
};

extern g_Tacho_image g_tacho_img_table[202];
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
/***********************************************************************************************************************
 *                                    P R I V A T E     F U N C T I O N S    D E C L A R A T I O N
 ***********************************************************************************************************************/

/*
 * @brief    This function processes filtering (with hysteresis) for a single gauge
 * @param    GA_REND_CONFIG_STRUCT
 * @return   NONE
 */
static void ga_rend_gauge_command_generation(const GA_REND_CONFIG_STRUCT * gauge_config);

/*
 * @brief    This function processes round off to nearest value
 * @param    value
 * @return   uint16_t
 */
static UINT32 ga_rend_round_to_nearest_N(UINT32 value);
/***********************************************************************************************************************
 *                                          F U N C T I O N     D E F I N I T I O N S
 ***********************************************************************************************************************/
/*
* @brief    This API is used to initialize Tacho gauge rendering process
* @param    NONE
* @return   NONE
* @invocation invoked by Os
*/
void HMI_Tacho_Rend_Init(void)
{
    (void)memset(&tacho_Rend_Buffer, 0, sizeof(tacho_Rend_Buffer));

    g_Current_Img_Index = 0;
}

/*
* @brief    This API is used to de initialize Tacho gauge rendering process
* @param    NONE
* @return   NONE
* @invocation invoked by Os
*/
void HMI_Tacho_Rend_DeInit(void)
{
    (void)memset(&tacho_Rend_Buffer, 0, sizeof(tacho_Rend_Buffer));

}

/*
* @brief    This API is used to do Tacho gauge Rendering process
* @param    NONE
* @return   NONE
* @invocation invoked by Os
*/
void HMI_Tacho_Rend_Mainfunction(void)
{
    /* Tacho gague rendering process*/
    ga_rend_gauge_command_generation(&g_Tacho_Rend_Cfg);

    /* Map Image Index against filtered value*/
    HMI_Tacho_Image_Mapping(((tacho_Rend_Buffer.CurrentGx) / 10));
}

/*
 * @brief    This function processes filtering (with hysteresis) for a single gauge
 * @param    GA_REND_CONFIG_STRUCT
 * @return   NONE
 */
static void ga_rend_gauge_command_generation(const GA_REND_CONFIG_STRUCT * gauge_config)
{
   const GA_REND_CONST_STRUCT * gaugec = gauge_config->filter_conf;
   GA_REND_VAR_STRUCT * gaugev = gauge_config->rend_buffer;
   UINT32 TempGx;
   UINT32 DeltaGx;

   if (gaugev->GSRx_step_counter > 0)
   {
      /* not yet time for update */
      gaugev->GSRx_step_counter--;
   }
   else
   {
      /* reset update counter to configured value */
      gaugev->GSRx_step_counter = gaugec->Gauge_X_Count;

      /* Get new target value from application */
      TempGx = gauge_config->get_value_func();

      /* Add hysteresis with target value*/
      TempGx = TempGx + HMI_TACHO_HYST;

      /*
      ** Perform hysteresis.
      */
      if (TempGx <= gaugec->HystGx)
      {
         /* below deadband - hold at zero */
         gaugev->TargetHystGx = (UINT16)0;
      }
      else if (   ((TempGx - gaugec->HystGx) > gaugev->TargetHystGx)    /* target increased more than deadband */
               || ((gaugev->TargetHystGx - gaugec->HystGx) > gaugev->CurrentGx)  /* current position more than deadband away */
               || ((TempGx + gaugec->HystGx) < gaugev->TargetHystGx)    /* target decreased more than deadband */
               || ((gaugev->TargetHystGx + gaugec->HystGx) < gaugev->CurrentGx)  /* current position more than deadband away */
              )
      {
         /* use new target */
         gaugev->TargetHystGx = TempGx;
      }
      else
      {
         /* no change - keep previous target */
      }

      /*
      ** Perform filtering.
      */
      if ((gaugev->TargetHystGx > gaugev->CurrentGx + HMI_TACHO_HYST) || 
         (gaugev->TargetHystGx < gaugev->CurrentGx - HMI_TACHO_HYST))
      {
         /*
         ** Execute the first stage filter.
         */
         TempGx = (gaugev->TargetHystGx) << GA_REND_FILTER_SHIFT;

         if (TempGx > gaugev->FSGx)
         {
            TempGx = ((UINT32)(TempGx - gaugev->FSGx) >> (gaugec->Tx1)) + gaugev->FSGx + (pow(2 , GA_REND_TACHO_T1) - 1);
         }
         else
         {
            TempGx = gaugev->FSGx - ((UINT32)(gaugev->FSGx - TempGx) >> (gaugec->Tx1));
         }
         gaugev->FSGx = TempGx;

         TempGx = ga_rend_round_to_nearest_N(TempGx);

         /*
         ** Execute the second stage filter.
         */
         if (TempGx > gaugev->SSGx)
         {
            TempGx = ((UINT32)(TempGx - gaugev->SSGx) >> (gaugec->Tx2)) + gaugev->SSGx + ( pow(2 , GA_REND_TACHO_T2) - 1);
         }
         else
         {
            TempGx = gaugev->SSGx - ((UINT32)(gaugev->SSGx - TempGx) >> (gaugec->Tx2));
         }
         gaugev->SSGx = TempGx;

         TempGx = ga_rend_round_to_nearest_N(TempGx);

         TempGx >>= GA_REND_FILTER_SHIFT;

         /*
         ** Calculate the step change and clamp it at the max velocity.
         */
         if (TempGx == gaugev->CurrentGx)
         {
            /* keep current direction */
            DeltaGx = (UINT16)0;
         }
         else if (TempGx > gaugev->CurrentGx)
         {
            /* set current direction */
            gaugev->dirregx = GA_REND_DIR_INCREASING;

            DeltaGx = TempGx - gaugev->CurrentGx;
         }
         else /* (TempGx < gaugev->CurrentGx) */
         {
            /* set current direction */
            gaugev->dirregx = GA_REND_DIR_DECREASING;

            DeltaGx = gaugev->CurrentGx - TempGx;
         }

         if (DeltaGx > gaugec->MaxVelGx)
         {
            DeltaGx = gaugec->MaxVelGx;
         }
         else if ( DeltaGx < HMI_TACHO_HYST)
         {
            /* if Delta is less than hysteresis , slew by hysteresis*/
            DeltaGx = HMI_TACHO_HYST;
         }

         if (TempGx >= gaugev->CurrentGx)
         {
             /* update to new position */
             TempGx = gaugev->CurrentGx + DeltaGx;
         }
         else /* (TempGx < gaugev->CurrentGx) */
         {
             /* update to new position - ensure no underflow */
             if (gaugev->CurrentGx > DeltaGx)
             {
                TempGx = gaugev->CurrentGx - DeltaGx;
             }
             else
             {
                 TempGx = (UINT16)0;
             }
         }

         /* TempGx now contains the updated 'CurrentGx' */
         gaugev->CurrentGx = TempGx;
      }
    }
}

/*
 * @brief    This function processes round off to nearest value
 * @param    value
 * @return   uint16_t
 */
static UINT32 ga_rend_round_to_nearest_N(UINT32 value)
{
   return( (value + (UINT32)(GA_REND_FILTER_SCALE_VALUE/2)) & (UINT32)GA_REND_FILTER_MASK );
}

/*
* @brief    This API is used to map current Gauge Angle to Image Index 
* @param    Tacho Gauge Pointer angle
* @return   NONE
* @invocation Called Tacho rendering mainfunction
*/
void HMI_Tacho_Image_Mapping(UINT16 p_Current_Gx)
{
   uint16_t Offset_Start_index = 0;
   uint16_t Offset_End_index = 0; 
   uint16_t fl_loop_index_u8 = 0;
   bool fl_Img_Index_find_St = FALSE;
   uint16_t fl_Tacho_Angle_First_Row_u32;
   uint16_t fl_Tacho_Angle_Second_Row_u32;
   uint16_t fl_Tacho_Image_Index_First_Row_u32;
   uint16_t fl_Tacho_Image_Index_Second_Row_u32;
   uint16_t fl_Tacho_Angle_Delta_u32;
   uint16_t fl_Tacho_Image_Index_Delta_u32;

   for(fl_loop_index_u8 = 0; fl_loop_index_u8 < 9; fl_loop_index_u8++)
   {
      fl_Tacho_Angle_First_Row_u32 = HMI_Tacho_Img_Offset_Tbl[fl_loop_index_u8][0];
      fl_Tacho_Angle_Second_Row_u32 = HMI_Tacho_Img_Offset_Tbl[fl_loop_index_u8 + 1][0];

      fl_Tacho_Image_Index_First_Row_u32 = HMI_Tacho_Img_Offset_Tbl[fl_loop_index_u8][1];
      fl_Tacho_Image_Index_Second_Row_u32 = HMI_Tacho_Img_Offset_Tbl[fl_loop_index_u8 + 1][1];

      if(p_Current_Gx ==  HMI_Tacho_Img_Offset_Tbl[fl_loop_index_u8][0])
      {
         g_Current_Img_Index =  HMI_Tacho_Img_Offset_Tbl[fl_loop_index_u8][1];
         
         break;
      }				  
      /* Linear Interpolation */
      else if ( (p_Current_Gx > fl_Tacho_Angle_First_Row_u32) &&
               (p_Current_Gx < fl_Tacho_Angle_Second_Row_u32) )
      {
         fl_Tacho_Angle_Delta_u32 = fl_Tacho_Angle_Second_Row_u32 - fl_Tacho_Angle_First_Row_u32;
         fl_Tacho_Image_Index_Delta_u32 = fl_Tacho_Image_Index_Second_Row_u32 - fl_Tacho_Image_Index_First_Row_u32;

         g_Current_Img_Index = fl_Tacho_Image_Index_First_Row_u32 + ((float)(p_Current_Gx - fl_Tacho_Angle_First_Row_u32) / (float)fl_Tacho_Angle_Delta_u32) * fl_Tacho_Image_Index_Delta_u32;

         break;
      }
      else
      {
         
      }

   }

}

uint8_t HMI_Tacho_Rend_Get_Img_Index(void)
{
    return (g_Current_Img_Index);
}
/***********************************************************************************************************************
                                              E N D   O F   S O F T W A R E                                         
 **********************************************************************************************************************/


/***********************************************************************************************************************
 *                                              R E V I S I O N   H I S T O R Y
 ***********************************************************************************************************************
    REVISION NUMBER      : v1.0.2                          
    REVISION DATE        : 01/18/2023        
    CREATED / REVISED BY : Palani kumar (palanikumar@niyatainfotech.com)      
    DESCRIPTION          : Hysteresis added and 1st , 2nd order filter error compensation added
    
    REVISION NUMBER      : v1.0.1                          
    REVISION DATE        : 12/28/2022        
    CREATED / REVISED BY : Palani kumar (palanikumar@niyatainfotech.com)      
    DESCRIPTION          : Tacho gauge processing angle upgrated from 0.1 to 0.01 degree 

    REVISION NUMBER      : v1.0.0                          
    REVISION DATE        : 07/18/2022        
    CREATED / REVISED BY : Palani kumar (palanikumar@niyatainfotech.com)      
    DESCRIPTION          : Initial version            
------------------------------------------------------------------------------------------------------------------------

 ***********************************************************************************************************************/
#endif /* ! FILE NAME */

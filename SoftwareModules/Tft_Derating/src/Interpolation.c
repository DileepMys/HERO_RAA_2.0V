/* @file FILE NAME */
#ifndef INTERPOLATION_C
#define INTERPOLATION_C

/***********************************************************************************************************************
 *    DISCLAIMER
 *   Copyright (C) 2011, 2016 Niyata Infotech Pvt. Ltd. All rights reserved.
 ***********************************************************************************************************************/

/************************************************************************************************************************
 * @author              Author : Rubina Josphine (rubinajosphine@niyatainfotech.com)
 ***********************************************************************************************************************/

/***********************************************************************************************************************
 *                                                F I L E  D E S C R I P T I O N
 **----------------------------------------------------------------------------------------------------------------------
 *  @brief
 *  File name                       : Interpolation.c
 *  Version                         : V1.0.0
 *  Micros supported                : Micro Independent
 *  Compilers supported             : J Link
 *  Platforms supported             : Platform Independent
 *  Description                     : This file consists of definitions of interpolation table
 *  @bug
--------------------------------------------------------------------------------------------------------------------*/



/***********************************************************************************************************************
 *                                               I N C L U D E   F I L E S
 ***********************************************************************************************************************/
#include "Interpolation.h"
#include "stdint.h"
#include "Fuel_Guage.h"


/***********************************************************************************************************************
*                                               I N C L U D E  LIBRARY F I L E S                                     
***********************************************************************************************************************/



/***********************************************************************************************************************
 *                                          M A C R O   D E F I N I T I O N S
 ***********************************************************************************************************************/


/***********************************************************************************************************************
 *                                          L O C A L  V A R I A B L E   D E F I N I T I O N S
 ***********************************************************************************************************************/
/*
 * @brief: This variable is used to give the index for table
 * @Unit:  NA
 * @Resolution: NA
 * @Range: 0 t0 maximum data which is defined
 * @Applicability: TFT Derating
 */
uint16_t g_interpolation_index_u8 = 0;

/*
 * @brief: This variable is used to get the first data from x row
 * @Unit:  NA
 * @Resolution: NA
 * @Range: NA
 * @Applicability: TFT Derating
 */
uint16_t g_first_data_from_x_row_u16;

/*
 * @brief: This variable is used to get the first data from y row
 * @Unit:  NA
 * @Resolution: NA
 * @Range: NA
 * @Applicability: TFT Derating
 */
uint16_t g_first_data_from_y_row_u16;

/*
 * @brief: This variable is used to get the second data from x row
 * @Unit:  NA
 * @Resolution: NA
 * @Range: NA
 * @Applicability: TFT Derating
 */
uint16_t g_second_data_from_x_row_u16;

/*
 * @brief: This variable is used to get the second data from y row
 * @Unit:  NA
 * @Resolution: NA
 * @Range: NA
 * @Applicability: TFT Derating
 */
uint16_t g_second_data_from_y_row_u16;

/*
 * @brief: This variable is used to get the delta value from x row
 * @Unit:  NA
 * @Resolution: NA
 * @Range: NA
 * @Applicability: TFT Derating
 */
uint16_t g_x_row_delta_u16;

/*
 * @brief: This variable is used to get the delta value from y row
 * @Unit:  NA
 * @Resolution: NA
 * @Range: NA
 * @Applicability: TFT Derating
 */
uint16_t g_y_row_delta_u16;

/*
** Define some macros to make the code easier to read.
*/
#define START_VAL       (*(table))
#define END_VAL         (*(table+1))
#define FIRST_IN        (table+2)
#define CURR_VAL_IN     (*(ptr))
#define CURR_VAL_OUT    (*(ptr+1))
#define LAST_VAL_IN     (*(ptr-2))
#define LAST_VAL_OUT    (*(ptr-1))
/***********************************************************************************************************************
 *                                  P R I V A T E   V A R I A B L E   D E F I N I T I O N S
 ***********************************************************************************************************************/

/***********************************************************************************************************************
 *                                    P R I V A T E     F U N C T I O N S    D E C L A R A T I O N
 ***********************************************************************************************************************/

/***********************************************************************************************************************
 *                                          F U N C T I O N     D E F I N I T I O N S
 ***********************************************************************************************************************/
/* API is used to get the interpolated data from table */
uint16_t Interpolation_Handler(uint16_t fl_demanded_data_u16, uint16_t *fl_data_from_table, uint8_t fl_row_size_u8, uint8_t table_config_u8)
{
   
	uint16_t fl_return_data_u16;

    for( g_interpolation_index_u8 = 0; g_interpolation_index_u8 < fl_row_size_u8; g_interpolation_index_u8++ )
    {
        g_first_data_from_x_row_u16 = *fl_data_from_table;
        g_second_data_from_x_row_u16 = *(fl_data_from_table + 2u);
        g_first_data_from_y_row_u16 =*(++fl_data_from_table);
        g_second_data_from_y_row_u16 = *(++fl_data_from_table +1u );
         
    
        /*Check if the demanded data is equal to the value from x row*/          
        if(fl_demanded_data_u16 == *fl_data_from_table)
        {
            fl_return_data_u16 = *(++fl_data_from_table);
            break;
        }
        else if ( (fl_demanded_data_u16 < g_first_data_from_x_row_u16 ) && (fl_demanded_data_u16 > g_second_data_from_x_row_u16 ))
        {            
            g_x_row_delta_u16 = g_second_data_from_x_row_u16 - g_first_data_from_x_row_u16;
            g_y_row_delta_u16 = g_second_data_from_y_row_u16 - g_first_data_from_y_row_u16;

            if(table_config_u8 == 0)
            {
                fl_return_data_u16 =  g_first_data_from_y_row_u16 + ((float)(fl_demanded_data_u16 - g_first_data_from_x_row_u16) / (float)g_x_row_delta_u16) * g_y_row_delta_u16;
            }
            else if (table_config_u8 = 1)
            {
                fl_return_data_u16 =  g_first_data_from_y_row_u16 + (float) (g_y_row_delta_u16) / (float)(g_x_row_delta_u16) * (fl_demanded_data_u16 - g_first_data_from_x_row_u16) ;
            }
            else
            {
                /*Do nothing*/
            }
            break;

        }
        else
        {
            /*Do nothing*/
        }
    }

    return fl_return_data_u16;

}


/*============================================================================
//
//  Function Name:      UINT16 LinearInterpolateWord(UINT16 *table, UINT16 lookupVal)
//
//  Description:        Linear interpolation code.
//
//  Input Arguments:    None
//
//  Output Arguments:   None
//
//                                                   JKANOZA  990713  990713
//==========================================================================*/
UINT16 LinearInterpolateWord(UINT16 *table, UINT16 lookupVal)
{
  UINT16 *ptr;

  /*
  ** If the input value is less or greater than the min/max entry, set it
  ** to the min or max entry value for the lookup function.
  */
  if (lookupVal < START_VAL)
  {
    lookupVal = START_VAL;
  }
  else if (lookupVal > END_VAL)
  {
    lookupVal = END_VAL;
  }

  /*
  ** Search through table until the exact entry is found or bounding entries
  ** are found.  Then interpolate if necessary.
  */
  for (ptr=FIRST_IN; *ptr<=END_VAL; ptr+=2)
  {
    if (CURR_VAL_IN == lookupVal)
    {
      return (CURR_VAL_OUT);
    }
    else
    {
      if (lookupVal < CURR_VAL_IN)
      {
        if (CURR_VAL_OUT >= LAST_VAL_OUT) 
        {
          return (UINT16)((((UINT32)((UINT32)(lookupVal-LAST_VAL_IN) * (UINT32)(CURR_VAL_OUT-LAST_VAL_OUT))/(CURR_VAL_IN-LAST_VAL_IN))+LAST_VAL_OUT));
        }
        else
        {
          return (UINT16)(LAST_VAL_OUT-((UINT32)((UINT32)(lookupVal-LAST_VAL_IN) * (UINT32)(LAST_VAL_OUT-CURR_VAL_OUT))/(CURR_VAL_IN-LAST_VAL_IN)));
        }
      }
    }
  }

  return (0);
}

/***********************************************************************************************************************
                                              E N D   O F   S O F T W A R E                                         
 **********************************************************************************************************************/


/***********************************************************************************************************************
 *                                              R E V I S I O N   H I S T O R Y
 ***********************************************************************************************************************
    REVISION NUMBER      : V1.0.0                          
    REVISION DATE        : May/08/2022        
    CREATED / REVISED BY : Rubina Josphine (rubinajosphine@niyatainfotech.com)      
    DESCRIPTION          : Initial version            
------------------------------------------------------------------------------------------------------------------------

 ***********************************************************************************************************************/
#endif /* ! INTERPOLATION_C */

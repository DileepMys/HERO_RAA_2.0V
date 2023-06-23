/* @file FILE NAME */
#ifndef FUEL_GUAGE_H
#define FUEL_GUAGE_H

/***********************************************************************************************************************
*    DISCLAIMER
*   Copyright (C) 2020 Niyata Infotech Pvt. Ltd. All rights reserved.                                             
***********************************************************************************************************************/

/************************************************************************************************************************
* @author              Author : Palani kumar (palanikumar@niyatainfotech.com)                                                                        
***********************************************************************************************************************/

/***********************************************************************************************************************
*                                                F I L E  D E S C R I P T I O N                                        
**----------------------------------------------------------------------------------------------------------------------
*  @brief
*
*  File name                       : Fuel_Guage.h
*  Version                         : v1.0.0
*  Micros supported                : Micro Independent
*  Compilers supported             : J link
*  Platforms supported             : PLatform Independent                
*  Description                     : This header file contains the declarations of fuel guage
*  @bug                            : N/A
--------------------------------------------------------------------------------------------------------------------*/


/***********************************************************************************************************************
*                                               I N C L U D E   CONFIGURATION F I L E S 
***********************************************************************************************************************/
#include "Fuel_Guage_Cfg.h"
#include "hal_stdtypes.h"
#include "Swc_System_Service.h"
/***********************************************************************************************************************
                                               I N C L U D E  CONDITION BASED F I L E S                             
***********************************************************************************************************************/

/***********************************************************************************************************************
*                                      V E R S I O N   I N T E G R I T Y  C H E C K                                  
***********************************************************************************************************************/

/***********************************************************************************************************************
*                                            M A C R O   D E F I N I T I O N S                                         
***********************************************************************************************************************/
/**
* @brief This macro is used to define 
* @Unit:  
* @Resolution: 
* @Range: 
* @Applicability: 
* @Note:  
*/


/***********************************************************************************************************************
*                                          T Y P E   D E F I N I T I O N S                                           
***********************************************************************************************************************/

/*
 * @brief    This typedef is used to define the variables datatypes
 * @param    NA
 * @return   NA 
 **/

typedef bool BOOLEAN;

typedef uint8_t UINT8;

typedef uint16_t UINT16;

typedef uint32_t UINT32;
/*
 * @brief    This structure is used to define 
 * @param    
 * @param    
 **/

#define TESTBIT( operand, bit_mask )        (((operand) &  (bit_mask)) != ((bit_mask) - (bit_mask)))
#define SETBIT( operand, bit_mask )         ((operand) |= (bit_mask))
#define CLEARBIT( operand, bit_mask )       ((operand) &= ((UINT32)~(bit_mask)))

/*#define ADC_INPUT_VOLTAGE	1800*/	  /* ADC is connected to 1.8v constant power source - 1000 is factored to avoid the float value */
/*#define ADC_MAX_COUNT		4095 */ /* 12BIT ADC IS MAXIMUM COUNT AS 4096 */


typedef enum
{
    FUEL_GUAGE_IDLE = 0,
    FUEL_GAUGE_KEY_ON_SAMPLING,
    FUEL_GUAGE_FUEL_SUPPLY_ON,
    FUEL_GUAGE_ADC_SAMPLING,
    FUEL_GUAGE_FUEL_SUPPLY_OFF,
    FUEL_GUAGE_FUEL_SENSOR_COOL_OFF
}FUEL_GUAGE_ADC_STATE_MACHINE;


typedef enum
{
    LOW_FUEL_TT_OFF = 0,
    LOW_FUEL_TT_ON,
}FUEL_LFW_TT_ST_EN;

/***********************************************************************************************************************
*                                    P U B L I C     F U N C T I O N S    D E C L A R A T I O N                      
***********************************************************************************************************************/

/*
* @brief    This API is used to Initialize the fuel guage 
* @param    NONE
* @return   NONE
* @invocation invoked by trip computer
*/
void Fuel_Guage_Init(void);
/*
* @brief    This API is used to De Initialize the fuel guage 
* @param    NONE
* @return   NONE
* @invocation invoked by trip computer
*/
void Fuel_Guage_DeInit(void);

/*
* @brief    This API is used to initialize the fuel guage peripherals
* @param    NONE
* @return   NONE
* @invocation invoked by trip computer
*/
void Fuel_Guage_Activate(void);

/*
* @brief    This API is used to De activate  the fuel guage  peripherals
* @param    NONE
* @return   NONE
* @invocation invoked by trip computer
*/
void Fuel_Guage_Deactivate(void);

/*
* @brief    This API is used to configure the battery's ADC configuration 
* @param    NONE
* @return   nil
* @invocation invoked by trip computer
*/
void SBATT_ADC_Config_Init(void);

/*
* @brief    This API is used to configure the fuel sensor's  ADC configuration 
* @param    NONE
* @return   nil
* @invocation invoked by trip computer
*/
void Fuel_Sensor_ADC_Config_Init(void);

/*
* @brief    This API is used to get fuel gauge ready status
* @param    NONE
* @return   bool
* @invocation invoked by trip computer
*/
bool Fuel_Gauge_Ready_Status(void);


/*
* @brief    This API is used to ready the battery's ADC value
* @param    NONE
* @return   NONE
* @invocation invoked by trip computer
*/
void Fuel_SBATT_Read_Adc_Value(void);
/*
* @brief    This API is used to process mainfunction of  fuel guage 
* @param    NONE
* @return   NONE
* @invocation invoked by trip computer
*/
void Fuel_Guage_MainFunction(void);
/*
* @brief    This API is used to get current fuel guage bar level 
* @param    NONE
* @return   FUEL_BAR_POS_EN enumeration for different fuel bar level
* @invocation invoked by trip computer
*/
uint8_t Fuel_Guage_Get_Current_Bar_Level(void);
/*
* @brief    This API is used to Get low fuel level indication status 
* @param    NONE
* @return   low fuel status
* @invocation invoked by trip computer
*/
FUEL_LFW_TT_ST_EN Fuel_Guage_Get_Low_Fuel_Status(void);

/*
* @brief    This API is used to Get low fuel level indication status 
* @param    NONE
* @return   average fuel rate
* @invocation invoked by trip computer
*/
uint32_t Get_Average_Fuel(uint8_t fl_Trip_index_u8);

/*
* @brief    This API is used to Get low fuel level indication status 
* @param    NONE
* @return   fuel gauage information 
* @invocation invoked by trip computer
*/
uint16_t Fuel_Guage_Table(uint8_t Fuelbar);

/*
* @brief    This API is used to Get low fuel level indication status 
* @param    NONE
* @return   fuel gauge RAD value
* @invocation invoked by trip computer
*/
uint16_t Swc_Fuel_Gauge_Get_RAD_Value(void);

/*
* @brief    This API is used to Get low fuel level indication status 
* @param    NONE
* @return   fault status
* @invocation invoked by trip computer
*/
uint8_t Swc_Fuel_Gauge_Get_Fault_Status(void);

/*
* @brief    This API is used to Get low fuel level indication status 
* @param    NONE
* @return   pfvalue
* @invocation invoked by trip computer
*/
uint32_t swc_get_pf_value(void);

/*
* @brief    This API is used to Get low fuel level indication status 
* @param    NONE
* @return   bool
* @invocation invoked by trip computer
*/
bool Swc_Fuel_Guage_Fast_Fill_Condition(void);

/*
* @brief    This API is used to Get low fuel level indication status 
* @param    NONE
* @return   void
* @invocation invoked by trip computer
*/
void Fuel_Gauge_NVM_Write (void);

/*
* @brief    This API is used to Get low fuel level indication status 
* @param    NONE
* @return   void
* @invocation invoked by trip computer
*/
void ffuel_calculate_bars(void);

/*
* @brief    This API is used to Get instant debounce flag status 
* @param    NONE
* @return   bool
* @invocation invoked by trip computer
*/
bool Swc_Get_Inst_Debounce_Flag_Status(void);

/*
* @brief    This API is used to clear the instant debounce flag status 
* @param    NONE
* @return   void
* @invocation invoked by trip computer
*/
void Swc_Clear_Inst_Debounce_Flag_Status(void);
/***********************************************************************************************************************
                                              E N D   O F   S O F T W A R E                                         
*********************************************************************************************************************/


/***********************************************************************************************************************
*                                              R E V I S I O N   H I S T O R Y                                       
/***********************************************************************************************************************
    REVISION NUMBER      : v1.0.0                          
    REVISION DATE        : 03/27/2022        
    CREATED / REVISED BY : Palani kumar (palanikumar@niyatainfotech.com)    
    DESCRIPTION          : Initial version                                
------------------------------------------------------------------------------------------------------------------------

***********************************************************************************************************************/
#endif /* ! FUEL_GUAGE_H */

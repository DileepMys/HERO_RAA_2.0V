/* @file FILE NAME */
#ifndef OPT3001_DRIVER_C
#define OPT3001_DRIVER_C

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
 *  File name                       : 
 *  Version                         : 
 *  Micros supported                : 
 *  Compilers supported             : 
 *  Platforms supported             : 
 *  Description                     : This file consists of definitions of 
 *  @bug
--------------------------------------------------------------------------------------------------------------------*/



/***********************************************************************************************************************
 *                                               I N C L U D E   F I L E S
 ***********************************************************************************************************************/
#include "OPT3001_driver.h"
#include "Ambient_light_sensor.h"
/***********************************************************************************************************************
*                                               I N C L U D E  LIBRARY F I L E S                                     
***********************************************************************************************************************/
#include "fsl_lpi2c.h"
#include "I2C_Handler.h"
#include "hal_stdtypes.h"
/***********************************************************************************************************************
 *                                          M A C R O   D E F I N I T I O N S
 ***********************************************************************************************************************/

/*  
 * @brief: This macro is used to 
 * @Unit:  
 * @Resolution: 
 * @Range: 
 * @Applicability: 
 */
#define ALS_LPI2C_DATA_LENGTH 			100u
#define ALS_LPI2C_BAUDRATE               400000U
#define LPI2C_CLOCK_FREQUENCY 		(CLOCK_GetFreq(kCLOCK_OscRc48MDiv2))
#define ALS_LPI2C_MASTER_CLOCK_FREQUENCY    LPI2C_CLOCK_FREQUENCY
#define ALS_LPI2C_MASTER_SLAVE_ADDR_7BIT    0x44u
/***********************************************************************************************************************
 *                                          L O C A L  V A R I A B L E   D E F I N I T I O N S
 ***********************************************************************************************************************/
/*
 * @brief: This variable is used to 
 * @Unit:  
 * @Resolution: 
 * @Range: 
 * @Applicability: 
 */
uint16_t g_Result_Reg_val_u16;
status_t reVal = kStatus_Fail;
/***********************************************************************************************************************
 *                                  P R I V A T E   V A R I A B L E   D E F I N I T I O N S
 ***********************************************************************************************************************/
/*
 * @brief: This variable is used to 
 * @Unit:  
 * @Resolution: 
 * @Range: 
 * @Applicability: 
 *
 */
static lpi2c_master_transfer_t tx_buffer;
uint8_t debug_var = 1 ;
/***********************************************************************************************************************
 *                                    P R I V A T E     F U N C T I O N S    D E C L A R A T I O N
 ***********************************************************************************************************************/


uint8_t g_I2Cmaster_buff[20] = {0};
uint8_t g_Cfg_I2Cmaster_buff[20] = {0};

lpi2c_master_config_t ALS_masterConfig = {0};


/***********************************************************************************************************************
 *                                          F U N C T I O N     D E F I N I T I O N S
 ***********************************************************************************************************************/


/*
 * @brief    This function processes the 
 * @param    
 * @return   
 */
void OPT3001_Init(void)
{
    /* I2c initialization */
     LPI2C_MasterGetDefaultConfig(&ALS_masterConfig);
    ALS_masterConfig.baudRate_Hz = ALS_LPI2C_BAUDRATE;
    ALS_masterConfig.debugEnable = true;
    ALS_masterConfig.ignoreAck = false;
    ALS_masterConfig.pinConfig = kLPI2C_2PinPushPull;
    ALS_masterConfig.baudRate_Hz = 400000U;
    ALS_masterConfig.busIdleTimeout_ns = 0;
    ALS_masterConfig.pinLowTimeout_ns = 0;
    ALS_masterConfig.sdaGlitchFilterWidth_ns = 0;
    ALS_masterConfig.sclGlitchFilterWidth_ns = 0;
    
    LPI2C_MasterInit(ALS_LPI2C_MASTER_BASEADDR, &ALS_masterConfig, ALS_LPI2C_MASTER_CLOCK_FREQUENCY);

    LPI2C_MasterCheckAndClearError(ALS_LPI2C_MASTER_BASEADDR,kLPI2C_MasterBusBusyFlag);
    LPI2C_MasterCheckAndClearError(ALS_LPI2C_MASTER_BASEADDR,kLPI2C_MasterNackDetectFlag);

    /* setup configuration register */
    OPT3001_Get_Lux_Value( REG_CONFIGURATION, Range_field);
}

void OPT3001_DeInit_(void)
{

}

uint16_t OPT3001_Get_Lux_Value(uint8_t Configure_reg,uint16_t Config_data )
{


        /* Master Start and Send to address to slave */
    reVal = LPI2C_MasterStart(ALS_LPI2C_MASTER_BASEADDR, ALS_LPI2C_MASTER_SLAVE_ADDR_7BIT, kLPI2C_Write);
    g_I2Cmaster_buff[0] = Configure_reg;
    g_I2Cmaster_buff[1] = 0XC6;
    g_I2Cmaster_buff[2] = 0X10;

     /* Set up master to receive data from slave. */
    tx_buffer.data = &g_I2Cmaster_buff[0];
    tx_buffer.dataSize = 3;
    tx_buffer.slaveAddress = ALS_LPI2C_MASTER_SLAVE_ADDR_7BIT;
    tx_buffer.direction = kLPI2C_Write;

    /* write to ALS */
    reVal = LPI2C_MasterTransferBlocking(ALS_LPI2C_MASTER_BASEADDR, &tx_buffer);
    if (reVal != kStatus_Success)
    {
        //PRINTF("\r\nError occurred in transmit %d ! \r\n",page);
        return 2;
    }

    LPI2C_MasterStop(ALS_LPI2C_MASTER_BASEADDR);
    //return (g_Result_Reg_val_u16);
} 

uint16_t ALS_read (void)
{

     status_t reVal = kStatus_Fail;
     uint8_t fl_returnval_u8 = 0;
	 bool fl_readcomplete_flag_u8 = FALSE;
     uint16_t g_Cfg_I2Cmaster_buff;
	/* write to ALS */

   
    /* Set up master to receive data from slave. */
        g_I2Cmaster_buff[0]=REG_RESULT;
        tx_buffer.data = g_I2Cmaster_buff;
        tx_buffer.dataSize = 1;
        tx_buffer.slaveAddress = ALS_LPI2C_MASTER_SLAVE_ADDR_7BIT ;
        tx_buffer.direction = kLPI2C_Write;
        tx_buffer.flags = kLPI2C_TransferDefaultFlag;
    reVal = LPI2C_MasterTransferBlocking(ALS_LPI2C_MASTER_BASEADDR, &tx_buffer);
    	if (reVal != kStatus_Success)
	    {
	    	fl_returnval_u8=1;
	    }
        else
        {
            fl_returnval_u8=2;
        }
    

    //reVal = LPI2C_MasterStart(ALS_LPI2C_MASTER_BASEADDR, ALS_LPI2C_MASTER_SLAVE_ADDR_7BIT, kLPI2C_Read);
        tx_buffer.data = g_I2Cmaster_buff;
        tx_buffer.dataSize = 2;  //address
        tx_buffer.slaveAddress = ALS_LPI2C_MASTER_SLAVE_ADDR_7BIT;
        tx_buffer.direction = kLPI2C_Read;
        tx_buffer.flags = kLPI2C_TransferDefaultFlag;
    reVal = LPI2C_MasterTransferBlocking(ALS_LPI2C_MASTER_BASEADDR, &tx_buffer);
    	if (reVal != kStatus_Success)
	    {
	    	fl_returnval_u8=1;
	    }
        else
        {
            fl_returnval_u8=2;
        }
    
      
	     //PRINTF("Master received data :");
	     uint8_t len;
	     for (uint32_t i = 0U; i < len; i++)
	     {
	        
			 /*Set the flag as read complete to update the return value*/
			 fl_readcomplete_flag_u8 = TRUE;
	     }
	     /*Verify whether the read is complete*/
	     if(fl_readcomplete_flag_u8 == TRUE)
	     {
	    	 /*Update the return status*/
	    	 fl_returnval_u8 = E_OK;
	     }
	     //PRINTF("\r\n\r\n");

	    
       g_Result_Reg_val_u16 = g_I2Cmaster_buff[0] << 8 | g_I2Cmaster_buff[1];
       return g_Result_Reg_val_u16;
}

 float I2C_Sensor_value_lux_conversion()
 {
    uint16_t fraction_u16 = 0;
    uint16_t exponent_u16 = 0;
    float I2C_raw_lux_value_f = 0;
    uint16_t I2C_sensor_read_value = 0;

    I2C_sensor_read_value = ALS_read();

    exponent_u16= I2C_sensor_read_value>>12;

    fraction_u16=(I2C_sensor_read_value & 0x0FFF);

    I2C_raw_lux_value_f = 10e-3*(((uint16_t) 1)<<exponent_u16)*fraction_u16;
	return I2C_raw_lux_value_f;

 }



/***********************************************************************************************************************
                                              E N D   O F   S O F T W A R E                                         
 **********************************************************************************************************************/


/***********************************************************************************************************************
 *                                              R E V I S I O N   H I S T O R Y
 ***********************************************************************************************************************
    REVISION NUMBER      : Major.Minor.Patch                          
    REVISION DATE        : MONTH/DATE/YEAR        
    CREATED / REVISED BY : NAME (EMAIL-ID)      
    DESCRIPTION          : Initial version            
------------------------------------------------------------------------------------------------------------------------

 ***********************************************************************************************************************/
#endif /* ! FILE NAME */

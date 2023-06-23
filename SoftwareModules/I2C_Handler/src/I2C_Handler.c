/* @file FILE NAME */
#ifndef I2C_HANDLER_C
#define I2C_HANDLER_C

/***********************************************************************************************************************
 *    DISCLAIMER
 *   Copyright (C) 2011, 2016 Niyata Infotech Pvt. Ltd. All rights reserved.
 ***********************************************************************************************************************/

/************************************************************************************************************************
 * @author              Author : Name (mail-id)
 ***********************************************************************************************************************/

/***********************************************************************************************************************
 *                                                F I L E  D E S C R I P T I O N
 **----------------------------------------------------------------------------------------------------------------------
 *  @brief
 *
 *  File name                       : I2C_Handler.c
 *  Version                         : V1.0.0
 *  Micros supported                : Micro Independent
 *  Compilers supported             : J Link
 *  Platforms supported             : Platform Independent
 *  Description                     : This file consists of definitions of I2C handler
 *  @bug
--------------------------------------------------------------------------------------------------------------------*/



/***********************************************************************************************************************
 *                                               I N C L U D E   F I L E S
 ***********************************************************************************************************************/
#include "I2C_Handler.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "board.h"
#include "fsl_debug_console.h"
#include "fsl_lpi2c.h"
/***********************************************************************************************************************
*                                               I N C L U D E  LIBRARY F I L E S                                     
***********************************************************************************************************************/



/***********************************************************************************************************************
 *                                          M A C R O   D E F I N I T I O N S
 ***********************************************************************************************************************/

/*  
 * @brief: This macro is used to  get clock frequency of the I2C 
 * @Unit:  na
 * @Resolution: na 
 * @Range: nil
 * @Applicability: nil
 */


/* Get frequency of lpi2c clock */
#define LPI2C_CLOCK_FREQUENCY (CLOCK_GetFreq(kCLOCK_OscRc48MDiv2))

/*  
 * @brief: This macro is used to  get master clock frequency of the I2C
 * @Unit:  na
 * @Resolution: na 
 * @Range: nil
 * @Applicability: nil
 */
#define LPI2C_MASTER_CLOCK_FREQUENCY LPI2C_CLOCK_FREQUENCY

/*  
 * @brief: This macro is used to 
 * @Unit:  
 * @Resolution: 
 * @Range: 
 * @Applicability: 
 */
/*#define LPI2C_MASTER_IRQ LPI2C5_IRQn*/

/*  
 * @brief: This macro is used to 
 * @Unit:  
 * @Resolution: 
 * @Range: 
 * @Applicability: 
 */
/*#define LPI2C_MASTER_IRQHandler LPI2C5_IRQHandler*/

/*  
 * @brief: This macro is used to define the master slave address of the I2C
 * @Unit:  na
 * @Resolution: na 
 * @Range: nil
 * @Applicability: nil
 */
#define LPI2C_MASTER_SLAVE_ADDR_7BIT 0x50U

/*  
 * @brief: This macro is used to define the baudrate of the I2C communication protocol
 * @Unit:  na
 * @Resolution: na 
 * @Range: nil
 * @Applicability: nil

 */
#define LPI2C_BAUDRATE               40000U

/*  
 * @brief: This macro is used to  get the maximum data length of the I2C
 * @Unit:  na
 * @Resolution: na 
 * @Range: nil
 * @Applicability: nil
 */
#define LPI2C_DATA_LENGTH            100U

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/
/*
 * @brief: This variable is used to 
 * @Unit:  
 * @Resolution: 
 * @Range: 
 * @Applicability: 
 */
uint8_t g_master_buff[LPI2C_DATA_LENGTH] = {0};

/*
 * @brief: This variable is used to 
 * @Unit:  
 * @Resolution: 
 * @Range: 
 * @Applicability: 
 */
volatile uint8_t g_masterTxIndex         = 0U;

/*
 * @brief: This variable is used to 
 * @Unit:  
 * @Resolution: 
 * @Range: 
 * @Applicability: 
 */
volatile uint8_t g_masterRxIndex         = 0U;

/*
 * @brief: This variable is used to 
 * @Unit:  
 * @Resolution: 
 * @Range: 
 * @Applicability: 
 */
volatile bool g_masterReadBegin          = false;

/*
 * @brief: This variable is used to 
 * @Unit:  
 * @Resolution: 
 * @Range: 
 * @Applicability: 
 */
static lpi2c_master_transfer_t tx_buffer;
lpi2c_master_config_t masterConfig = {0};

/*
 * @brief: This variable is used to 
 * @Unit:  
 * @Resolution: 
 * @Range: 
 * @Applicability: 
 */
uint8_t g_WriteBuffer[16] = {1,3,5,7,9,11,12,13,14,15,16,17,18,19,20,22};

uint8_t g_ReadBuffer[16];
uint8_t g_vari_u8;
uint32_t g_Delay_Tick_Cnt;
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
 * @brief    This function processes the 
 * @param    
 * @return   
 */

/***********************************************************************************************************************
 *                                          F U N C T I O N     D E F I N I T I O N S
 ***********************************************************************************************************************/
/* API is used to initialize the init variables with default values */
void I2C_Handler_Init(void)
{
     LPI2C_MasterGetDefaultConfig(&masterConfig);
    masterConfig.baudRate_Hz = LPI2C_BAUDRATE;

    masterConfig.debugEnable = false;
    masterConfig.ignoreAck = false;
    masterConfig.pinConfig = kLPI2C_2PinPushPull;
    masterConfig.baudRate_Hz = 400000U;
    masterConfig.busIdleTimeout_ns = 0;
    masterConfig.pinLowTimeout_ns = 0;
    masterConfig.sdaGlitchFilterWidth_ns = 0;
    masterConfig.sclGlitchFilterWidth_ns = 0;

    LPI2C_MasterInit(EXAMPLE_LPI2C_MASTER_BASEADDR, &masterConfig, LPI2C_MASTER_CLOCK_FREQUENCY);

    LPI2C_MasterCheckAndClearError(EXAMPLE_LPI2C_MASTER_BASEADDR,kLPI2C_MasterBusBusyFlag);
    LPI2C_MasterCheckAndClearError(EXAMPLE_LPI2C_MASTER_BASEADDR,kLPI2C_MasterNackDetectFlag);

}

/* API is used to reset the initial values of the variables */
void I2C_Handler_De_Init(void)
{

}

/* API is used to activate the peripherals */
void I2C_Handler_Activate(void);

/* API is used to de activate the peripherals */
void I2C_Handler_DeActivate(void);



/* API is used to write data on the I2C */
uint8_t i2c_write_page(uint8_t page, uint8_t * data,uint8_t len) {

	 status_t reVal                     = kStatus_Fail;
	 uint8_t mpage;
	 uint8_t spage;
	 uint32_t delay_cnt = 0;
	 uint32_t xEnd,xStart;

	 if (len > 16)
	 {
		 return -1;
	 }
	 mpage = ((page & 0x10) >> 4);
	 spage = (page & 0x0f);

	 /* Master start and send address to slave. */
	    reVal = LPI2C_MasterStart(EXAMPLE_LPI2C_MASTER_BASEADDR, LPI2C_MASTER_SLAVE_ADDR_7BIT, kLPI2C_Write);
	    if (reVal != kStatus_Success)
	    {
	    	
	    	return -1;
	    }
	    /* Enable module interrupt. */
	    //LPI2C_MasterEnableInterrupts(EXAMPLE_LPI2C_MASTER_BASEADDR, kLPI2C_MasterTxReadyFlag);

	    g_master_buff[0]=spage<<4;
	    /* 5.Set up master to receive data from slave. */
	    for (uint32_t I2C_data = 1U; I2C_data <= len; I2C_data++)
	    {
	        g_master_buff[I2C_data] = *data++;
	    }
	    tx_buffer.data = g_master_buff;
	    tx_buffer.dataSize=len+1;  //address
	    tx_buffer.slaveAddress = LPI2C_MASTER_SLAVE_ADDR_7BIT | (mpage);
	    tx_buffer.direction = kLPI2C_Write;

	    //write to EEPROM
	    reVal = LPI2C_MasterTransferBlocking(EXAMPLE_LPI2C_MASTER_BASEADDR, &tx_buffer);
	    if (reVal != kStatus_Success)
	    {
	    	
	    	return 2;
	    }
	    LPI2C_MasterStop(EXAMPLE_LPI2C_MASTER_BASEADDR);

		/* As per CAV24C02 EEPROM chip datasheet recommendation,  
		 * for page of 16bytes length, I2C write cycle time requires 5ms window to complete write operation */
		for(delay_cnt = 0; delay_cnt < 1000000; delay_cnt++)
		{
			/* do nothing */
		}
	    return 0;
}

uint32_t Get_Delay_Cnt(void)
{
	return (g_Delay_Tick_Cnt);
}

uint8_t i2c_read_page(uint8_t page, uint8_t * data,uint8_t len)
{
	 status_t reVal                     = kStatus_Fail;
	 uint8_t mpage;
	 uint8_t spage;
	 uint8_t fl_returnval_u8 = E_OK;
	 boolean fl_readcomplete_flag_u8 = FALSE;

	 if (len > 16)
	 {
		 return -1;
	 }
	 mpage = ((page & 0x10) >> 4);
	 spage = (page & 0x0f);


	reVal = LPI2C_MasterStart(EXAMPLE_LPI2C_MASTER_BASEADDR, LPI2C_MASTER_SLAVE_ADDR_7BIT, kLPI2C_Write);
		        if (reVal != kStatus_Success)
		        {
		        	
		        	return -1;
		        }

		g_master_buff[0]=spage<<4;
        /* 5.Set up master to receive data from slave. */

        tx_buffer.data = g_master_buff;
        tx_buffer.dataSize = 1;  //address
        tx_buffer.slaveAddress = LPI2C_MASTER_SLAVE_ADDR_7BIT | (mpage);
        tx_buffer.direction = kLPI2C_Write;
        tx_buffer.flags = kLPI2C_TransferNoStopFlag;

        //write to EEPROM
        reVal = LPI2C_MasterTransferBlocking(EXAMPLE_LPI2C_MASTER_BASEADDR, &tx_buffer);
        if (reVal != kStatus_Success)
        {
        	
        	return -1;
        }

	     for (uint32_t I2C_data = 1U; I2C_data < LPI2C_DATA_LENGTH; I2C_data++)
	     {
	         g_master_buff[I2C_data] = 0xAA;
	     }

	             /* 5.Set up master to receive data from slave. */

	             tx_buffer.data = g_master_buff;
	             tx_buffer.dataSize=LPI2C_DATA_LENGTH;  //address
	             tx_buffer.slaveAddress = LPI2C_MASTER_SLAVE_ADDR_7BIT | (mpage);
	             tx_buffer.direction = kLPI2C_Read;
	             tx_buffer.flags = kLPI2C_TransferRepeatedStartFlag;

	             //write to EEPROM
	             reVal = LPI2C_MasterTransferBlocking(EXAMPLE_LPI2C_MASTER_BASEADDR, &tx_buffer);
	             if (reVal != kStatus_Success)
	             {
	             	
	             	return -1;
	             }

	            LPI2C_MasterStop(EXAMPLE_LPI2C_MASTER_BASEADDR);

	     
	     for (uint32_t I2C_data = 0U; I2C_data < len; I2C_data++)
	     {
	         if (I2C_data % 8 == 0)
	         {
	           
	         }
	        

			 *data = g_master_buff[I2C_data];	 
			 data++;

			 /*Set the flag as read complete to update the return value*/
			 fl_readcomplete_flag_u8 = TRUE;
	     }
	     /*Verify whether the read is complete*/
	     if(fl_readcomplete_flag_u8 == TRUE)
	     {
	    	 /*Update the return status*/
	    	 fl_returnval_u8 = E_OK;
	     }
	    
	   
	    return fl_returnval_u8;
}


/***********************************************************************************************************************
                                              E N D   O F   S O F T W A R E                                         
 **********************************************************************************************************************/


/***********************************************************************************************************************
 *                                              R E V I S I O N   H I S T O R Y
 ***********************************************************************************************************************
    REVISION NUMBER      : V1.0.0                          
    REVISION DATE        : MONTH/DATE/YEAR        
    CREATED / REVISED BY : NAME (EMAIL-ID)      
    DESCRIPTION          : Initial version            
------------------------------------------------------------------------------------------------------------------------

 ***********************************************************************************************************************/
#endif /* ! I2C_HANDLER_C */

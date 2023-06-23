/* @file FILE NAME */
#ifndef NVM_HANDLER_C
#define NVM_HANDLER_C

/***********************************************************************************************************************
 *    DISCLAIMER
 *   Copyright (C) 2011, 2016 Niyata Infotech Pvt. Ltd. All rights reserved.
 ***********************************************************************************************************************/

/************************************************************************************************************************
 * @author              Author : Balasubramaniyan (balasubramaniyan.s@niyatainfotech.com)
 ***********************************************************************************************************************/

/***********************************************************************************************************************
 *                                                F I L E  D E S C R I P T I O N
 **----------------------------------------------------------------------------------------------------------------------
 *  @brief
 *
 *  File name                       : NVM Handler.c
 *  Version                         : V1.0.0
 *  Micros supported                : Micro Independent
 *  Compilers supported             : COSMIC
 *  Platforms supported             : Platform Independent
 *  Description                     : This file contains implementations of gear_position

 *  @bug
--------------------------------------------------------------------------------------------------------------------*/

/**********************************************************************************************************************/


/***********************************************************************************************************************
 *                                               I N C L U D E   F I L E S
 ***********************************************************************************************************************/

#include "Swc_NVM_Handler.h"
#include "hal_stdtypes.h"
#include "I2C_Handler.h"
#include "fsl_lpi2c.h"
/***********************************************************************************************************************
 *                                          M A C R O   D E F I N I T I O N S
 ***********************************************************************************************************************/

/*  
 * @brief: This macro is used to set the max speed
 * @Unit:  
 * @Resolution: 
 * @Range: 
 * @Applicability: 
 */

#define LPI2C_MASTER_SLAVE_ADDR_7BIT 0x50U
#define LPI2C_DATA_LENGTH            100U
#define LPI2C_BAUDRATE               40000U
#define LPI2C_MASTER_CLOCK_FREQUENCY LPI2C_CLOCK_FREQUENCY

/* Get frequency of lpi2c clock */
#define LPI2C_CLOCK_FREQUENCY (CLOCK_GetFreq(kCLOCK_OscRc48MDiv2))

/***********************************************************************************************************************
 *                                          L O C A L  V A R I A B L E   D E F I N I T I O N S
 ***********************************************************************************************************************/

/***********************************************************************************************************************
 *                                  P R I V A T E   V A R I A B L E   D E F I N I T I O N S
 ***********************************************************************************************************************/
/*
 * @brief: This array variable  processes the buffer data info
 * @Unit:  N/A
 * @Resolution: N/A
 * @Range: Nil
 * @Applicability: 
 */
uint8_t  g_NVM_Data_Buff_u8[5];
uint32_t g_read_value_32;


/***********************************************************************************************************************
 *                                    P R I V A T E     F U N C T I O N S    D E C L A R A T I O N
 ***********************************************************************************************************************/



/***********************************************************************************************************************
 *                                          F U N C T I O N     D E F I N I T I O N S
 ***********************************************************************************************************************/
/* To initialize the ADC function to be called in the main function*/
void NVM_Handler_Init(void)
{
  
}

/* API is used to reset the NVM init variable with default values */ 
void NVM_Handler_Deint(void)
{

}

/* API is used to activate the NVM init variable with default values */
void NVM_Handler_Activate(void)
{
  /* do nothing */
}

/* API is used to deactivate the NVM init variable with default values */
void NVM_Handler_DeActivate(void)
{
  /* do nothing */
}

/* API is used to get the non volatile memory status whether its ready do its process  */
bool Swc_Get_NVM_Status(void)
{
  bool fl_nvm_status_bl = FALSE;
  fl_nvm_status_bl = LPI2C_MasterGetBusIdleState(LPI2C5);

  return (fl_nvm_status_bl);

}
/* API is used to read the appropriate data in the NVM */
uint8_t NVMData_Readsync(uint32_t id,void *data,uint8_t length)
{
     uint8_t fl_Ret_Val = kStatus_Fail;

    if(data != NULL)
    {           
                    /* API is used to read the data in the I2C */ 
      fl_Ret_Val = i2c_read_page(id,data,length);
    }


    return (fl_Ret_Val);
    
}

/* API is used to write the data into the NVM */
uint8_t NVMData_Writesync(uint32_t id,void *data,uint8_t length)
{
  uint16_t fl_Ret_Val = 0;
   
    if(data != NULL)
    {
                  /* API is used to write data on the I2C */
      fl_Ret_Val = i2c_write_page(id,data,length);

    }

    return (fl_Ret_Val);
}

uint8_t  NVM_Byte_Write_Allocation(uint8_t BlockID,uint8_t *Databuff)
{

	uint8_t write_status =0;
 write_status = NVM_Write_Frame(NVM_Write_Config_St[BlockID].NVM_Write_Start_Address ,Databuff,NVM_Write_Config_St[BlockID].NVM_Write_Size );
 return write_status;
}

uint8_t NVM_Byte_Read_Allocation(uint8_t BlockID,uint8_t *Databuff)
{
	uint8_t read_status =0;
 NVM_Read_Frame(NVM_Write_Config_St[BlockID].NVM_Write_Start_Address ,Databuff,NVM_Write_Config_St[BlockID].NVM_Write_Size );
 return read_status;
}

uint32_t NVM_Write_Frame(uint32_t DstAddress, uint8_t* SrcAddress, uint16_t size)
{
	/* LOCAL VARIABLE */
	uint16_t loop = 0;

	uint8_t NVM_Write_status = 0;

	/* WRITE ALL THE BYTE IN THE FRAME */
	for(loop = 0; loop < size; loop++)
	{
		NVM_Write_status = NVM_Byte_Write((DstAddress+loop), SrcAddress[loop]);
	}
	return NVM_Write_status ;
}


uint32_t NVM_Read_Frame(uint32_t DstAddress, uint8_t* SrcAddress, uint16_t size)
{
	/* LOCAL VARIABLE */
	uint16_t loop = 0;

	uint8_t NVM_Read_status = 0;

	/* WRITE ALL THE BYTE IN THE FRAME */
	for(loop = 0; loop < size; loop++)
	{
	   NVM_Read_status = NVM_Byte_Read((DstAddress+loop), &SrcAddress[loop]);
	}
	return NVM_Read_status;
}

uint8_t NVM_Byte_Write(uint32_t Address, uint8_t Data)
	{
		status_t reVal = kStatus_Fail;
		uint8_t Tx_buffer[20] = {0};
		uint32_t delay_cnt_1 = 0;
		uint8_t Slave_Address = 0;

		/* SLAVE ADDRESS WILL HOLD THE ADDTIONAL BITS IN MEMORY ADDRESS */
		if(Address > 255)
		{
			/* SET THE 8TH BIT OF THE ADDRES TO ENABLE THE EXTENDED ADDRESS */
			Slave_Address |= (LPI2C_MASTER_SLAVE_ADDR_7BIT | (1 << 0));
		}
		else
		{
			/* CLEAR THE 8TH BIT OF THE ADDRESS */
			Slave_Address |= LPI2C_MASTER_SLAVE_ADDR_7BIT;
		}

		reVal = LPI2C_MasterStart(EXAMPLE_LPI2C_MASTER_BASEADDR, Slave_Address, kLPI2C_Write);
		if (reVal != kStatus_Success)
		{
			return kStatus_Fail;
		}

		Tx_buffer[0] = (Address & 0xFF);

		reVal = LPI2C_MasterSend(EXAMPLE_LPI2C_MASTER_BASEADDR, &Tx_buffer[0], 1);

		Tx_buffer[0] = Data;

		reVal = LPI2C_MasterSend(EXAMPLE_LPI2C_MASTER_BASEADDR, &Tx_buffer[0], 1);

		reVal = LPI2C_MasterStop(EXAMPLE_LPI2C_MASTER_BASEADDR);

		for (delay_cnt_1 = 0; delay_cnt_1 < 1000000; delay_cnt_1++)
		{
			/* do nothing */
		}

			if (reVal != kStatus_Success)
		{
			reVal = kStatus_Fail;
		}
		return reVal;
	}

		/*byte Read*/
	uint8_t NVM_Byte_Read(uint32_t Address, uint8_t* Data)
	{
		status_t reVal = kStatus_Fail;
		uint8_t Tx_buffer[20] = {0};
		uint8_t Slave_Address = 0;

		/* SLAVE ADDRESS WILL HOLD THE ADDTIONAL BITS IN MEMORY ADDRESS */
		if(Address > 255)
		{
			/* SET THE 8TH BIT OF THE ADDRES TO ENABLE THE EXTENDED ADDRESS */
			Slave_Address |= (LPI2C_MASTER_SLAVE_ADDR_7BIT | (1 << 0));
		}
		else
		{
			/* CLEAR THE 8TH BIT OF THE ADDRESS */
			Slave_Address |= LPI2C_MASTER_SLAVE_ADDR_7BIT;
		}

		reVal = LPI2C_MasterStart(EXAMPLE_LPI2C_MASTER_BASEADDR, Slave_Address, kLPI2C_Write);
		if (reVal != kStatus_Success)
		{
			return kStatus_Fail;
		}

		 Tx_buffer[0] = Address;
		//Address = Tx_buffer[0];

		reVal = LPI2C_MasterSend(EXAMPLE_LPI2C_MASTER_BASEADDR, &Tx_buffer[0], 1);

		reVal = LPI2C_MasterStart(EXAMPLE_LPI2C_MASTER_BASEADDR, Slave_Address, kLPI2C_Read);
		if (reVal != kStatus_Success)
		{
			return kStatus_Fail;
		}
		// Tx_buffer[0] = Data;

		reVal = LPI2C_MasterReceive(EXAMPLE_LPI2C_MASTER_BASEADDR, &Tx_buffer[0], 1);
		*Data = Tx_buffer[0];

		reVal = LPI2C_MasterStop(EXAMPLE_LPI2C_MASTER_BASEADDR);

			if (reVal != kStatus_Success)
		{
			reVal = kStatus_Fail;
		}
	}




/***********************************************************************************************************************
                                              E N D   O F   S O F T W A R E                                         
 **********************************************************************************************************************/


/***********************************************************************************************************************
 *                                              R E V I S I O N   H I S T O R Y
 ***********************************************************************************************************************
    REVISION NUMBER      : Major.Minor.Patch                          
    REVISION DATE        : MONTH/DATE/YEAR        
    CREATED / REVISED BY : Balsubramaniyan (balasubramaniayan.s@niyatainfoteh.com)       
    DESCRIPTION          : Initial version            
------------------------------------------------------------------------------------------------------------------------

 ***********************************************************************************************************************/
#endif /* ! ADC_C*/

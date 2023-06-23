/* @file UDSAPP_SUPPORT */
#ifndef UDSAPP_SUPPORT_C
#define UDSAPP_SUPPORT_C

/***********************************************************************************************************************
*    DISCLAIMER
*   Copyright (C) 2011, 2016 Niyata Infotech Ptv. Ltd. All rights reserved.                                             
***********************************************************************************************************************/

/************************************************************************************************************************
* @author              Author : Sharmili N (sharmili@niyatainfotech.com)                                                                      
***********************************************************************************************************************/

/***********************************************************************************************************************
*                                                F I L E  D E S C R I P T I O N                                        
**----------------------------------------------------------------------------------------------------------------------
*  @brief
*
*  File name                       : UdsApp_Support.c
*  Version                         : V1.0.1
*  Micros supported                : Micro Agnostic (Independent)
*  Compilers supported             : XXXXX
*  Platforms supported             : XXXXX
*  Description                     : This file consists of definition of Extended support APIs required for UdsApp


*  @bug                          
--------------------------------------------------------------------------------------------------------------------*/

/**********************************************************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif
/**********************************************************************************************************************/

/***********************************************************************************************************************
*                                               I N C L U D E   F I L E S                                            
***********************************************************************************************************************/
#include "UdsApp_Support_Cfg.h"
#include "UdsApp_Support.h"
#include "UdsApp_Cfg.h"
#include "CanIF.h"
#include "hal_stdtypes.h"
#include "TTMgr.h"
#include "UdsApp.h"
#include "Swc_TFT_Illum.h"
#include "Swc_System_Service.h"
//#include "fsl_romapi.h"
//#include "Flash_Handler.h"
#if(UDS_BOOTLOADER_MODE_ENABLED == STD_ON)

#endif
/***********************************************************************************************************************
*                                          L O C A L  V A R I A B L E   D E F I N I T I O N S                                           
***********************************************************************************************************************/

uint8_t UDS_Prog_PreConditionResult = 0;

/***********************************************************************************************************************
*                                    P,BNM ,    R I V A T E     F U N C T I O N S    D E C L A R A T I O N                      
***********************************************************************************************************************/



/*
* @brief    This function is used to handle the Read DID service's reading operation from NVM/RAM/ROM
* @param    Data_Identifier - Identifier to analyze which data to be read from where
* @param    DataBuffer      - Data pointer to store the data read
* @param    DataSize        - Size of the Data to be read
* @return   UDS_UINT8 - E_OK: Read completed successfully
                        E_NOT_OK: Read not eexecuted successfully
*/
UDS_UINT8 UdsApp_Support_Read_Data(UDS_UINT16 Data_Identifier, UDS_UINT8 *DataBuffer, UDS_UINT16 DataSize)
{
    /*Variable to run the search for matching DID to be read fromm NVM*/
    UDS_UINT16 fl_NvM_Read_Index_u16;
    UDS_UINT8 fl_DIDmatched_flag_u8 = (uint8_t)0;
    UDS_UINT16 fl_ROM_Read_Index_u16;
    UDS_UINT8* fl_ReadAddress_u8;
    UDS_UINT8 fl_AdrsIndex_u8;
    UDS_UINT8 fl_readstatus_u8;

    /*Run the search iteration for maximum DIDs configured*/
    for(fl_NvM_Read_Index_u16 = (uint16_t)0; \
       ((fl_NvM_Read_Index_u16 < READ_NVM_MAX_DID) && (fl_DIDmatched_flag_u8 == 0u)); \
       fl_NvM_Read_Index_u16++)
    {
        /*Check for matching DID configured to Read from NVM*/
        if(Data_Identifier == g_Read_NVM_Data_st[fl_NvM_Read_Index_u16].DID)
        {
            fl_DIDmatched_flag_u8 = (uint8_t)1;
           /*Read from NvM*/
			#if(UDS_BOOTLOADER_MODE_ENABLED == STD_ON)
				      fl_readstatus_u8 = TI_Fee_ReadSync(g_Read_NVM_Data_st[fl_NvM_Read_Index_u16].Block_Id, 0, DataBuffer, DataSize);
			#else
				      fl_readstatus_u8 = UDSAPP_READ_NVM(g_Read_NVM_Data_st[fl_NvM_Read_Index_u16].Block_Id, DataBuffer);
			#endif
        }
    }

    /*Read Data from RAM*/
    /*Corresponding implementation to be done - User specific code expected*/


    /*Read Data from ROM
    for(fl_ROM_Read_Index_u16 = (uint16_t)0; \
       ((fl_ROM_Read_Index_u16 < READ_ROM_MAX_DID) && (fl_DIDmatched_flag_u8 == 0u)); \
       fl_ROM_Read_Index_u16++)
    {
        if(Data_Identifier == g_Read_ROM_Data_st[fl_ROM_Read_Index_u16].DID)
        {
            fl_DIDmatched_flag_u8 = (uint8_t)1;
            fl_ReadAddress_u8 = (UDS_UINT8*)g_Read_ROM_Data_st[fl_ROM_Read_Index_u16].StartAddress;
            for(fl_AdrsIndex_u8 = (uint8_t)0; fl_AdrsIndex_u8 < DataSize; fl_AdrsIndex_u8++)
            {
              DataBuffer[fl_AdrsIndex_u8] = fl_ReadAddress_u8[fl_AdrsIndex_u8];
            }
            fl_readstatus_u8 = (uint8_t)0;
        }
    }*/
    return fl_readstatus_u8;
}

/*
* @brief    This function is used to handle the Write DID service's write operation from NVM/RAM/ROM
* @param    Data_Identifier - Identifier to analyze which data to be read from where
* @param    DataBuffer      - Data pointer to store the data read
* @param    DataSize        - Size of the Data to be read
* @return   UDS_UINT8 - E_OK: Write completed successfully
                             E_NOT_OK: Write not eexecuted successfully
*/
UDS_UINT8 UdsApp_Support_Write_Data(UDS_UINT16 Data_Identifier, const UDS_UINT8 *DataBuffer, UDS_UINT16 DataSize)
{
  /*Variable to run the search for matching DID to be read fromm NVM*/
    UDS_UINT16 fl_NvM_Write_Index_u16;
    UDS_UINT8 fl_WriteStatus_u8 = (uint8_t)1;
    UDS_UINT8 fl_DIDmatched_flag_u8 = (uint8_t)0;
    UDS_UINT16 fl_ROM_Write_Index_u16;
    UDS_UINT8* fl_WriteAddress_u8;
    UDS_UINT8 fl_AdrsIndex_u8;
    UDS_UINT8  fl_DatatoWrite_u8[WRITE_ROM_MAX_DID][24];
    UDS_UINT8 fl_write_index;
    UDS_UINT8 fl_Read_Before_Write_Index_u8;

    /*Run the search iteration for maximum DIDs configured*/
            
    for(fl_NvM_Write_Index_u16 = (uint16_t)0; \
       ((fl_NvM_Write_Index_u16 < WRITE_NVM_MAX_DID) && (fl_DIDmatched_flag_u8 == (uint8_t)0)); \
       fl_NvM_Write_Index_u16++)
    {
        /*Check for matching DID configured to Write from NVM*/
        if(Data_Identifier == g_Write_NVM_Data_st[fl_NvM_Write_Index_u16].DID)
        {
            fl_DIDmatched_flag_u8 = (uint8_t)1;
            /*Write to NvM*/
#if(UDS_BOOTLOADER_MODE_ENABLED == STD_ON)
	          fl_WriteStatus_u8 = TI_Fee_WriteSync(g_Write_NVM_Data_st[fl_NvM_Write_Index_u16].Block_Id, &DataBuffer[0],DataSize);
#else
				       fl_WriteStatus_u8 = UDSAPP_WRITE_NVM(g_Write_NVM_Data_st[fl_NvM_Write_Index_u16].Block_Id, (void*)&DataBuffer[0]);

#endif
        }
    }

    /*Write Data to ROM*/
    /*Corresponding implementation to be done - User specific code expected*/
    for(fl_ROM_Write_Index_u16 = (uint16_t)0; \
       ((fl_ROM_Write_Index_u16 < WRITE_ROM_MAX_DID) && (fl_DIDmatched_flag_u8 == (uint8_t)0)); \
       fl_ROM_Write_Index_u16++)
    {
		/*Check for matching DID configured to Write to ROM*/
        if(Data_Identifier == g_Write_ROM_Data_st[fl_ROM_Write_Index_u16].DID)
        {
          fl_DIDmatched_flag_u8 = (uint8_t)1;
          for(fl_Read_Before_Write_Index_u8 = (uint8_t)0; fl_Read_Before_Write_Index_u8 < WRITE_ROM_MAX_DID; fl_Read_Before_Write_Index_u8++)
          {
			      fl_WriteAddress_u8 = (UDS_UINT8*)g_Write_ROM_Data_st[fl_Read_Before_Write_Index_u8].StartAddress;
            for(fl_AdrsIndex_u8 = (uint8_t)0; (fl_AdrsIndex_u8 < DataSize); fl_AdrsIndex_u8++)
            {
              fl_DatatoWrite_u8[fl_Read_Before_Write_Index_u8][fl_AdrsIndex_u8] = fl_WriteAddress_u8[fl_AdrsIndex_u8];
            }
          }
          // SUPPORT_FLASH_HANDLER_ERASEREQ_INIT((uint32_t)g_Write_ROM_Data_st[0].StartAddress, 0x8000);
          // for(fl_write_index = (uint8_t)0;fl_write_index < WRITE_ROM_MAX_DID ; fl_write_index++)
          // {
          //    if(fl_ROM_Write_Index_u16 != fl_write_index)
          //    {
          //      if(FAPI_GET_FSM_STATUS == Fapi_Status_Success)
          //      {
          //         fl_WriteStatus_u8 = SUPPORT_FLASH_HANDLER_ISSUE_PRGRM_CMD((uint32_t)g_Write_ROM_Data_st[fl_write_index].StartAddress,(uint32_t)&fl_DatatoWrite_u8[fl_write_index][0], DataSize);
          //      }
          //      else
          //      {
          //         fl_WriteStatus_u8 = (uint8_t)1;
          //      }
          //    }
          //    else
          //    {
          //     if(FAPI_GET_FSM_STATUS == Fapi_Status_Success)
          //     {
          //        fl_WriteStatus_u8 = SUPPORT_FLASH_HANDLER_ISSUE_PRGRM_CMD((uint32_t)g_Write_ROM_Data_st[fl_ROM_Write_Index_u16].StartAddress,(uint32_t)DataBuffer, DataSize);
          //     }
          //     else
          //     {
          //       fl_WriteStatus_u8 = (uint8_t)1;
          //     }
          //    }
          //  }
        }
    }

    return fl_WriteStatus_u8;
}

/*
* @brief    This API is used to configure the Application check for write memory by address
* @param    pdiagdata - Diagnostic request frame received from the client
* @param    RID - Routine Identifier
* @param    datalength - Data length of the Routine Control record
* @return   EcuReset Condition Status
**/
UDS_UINT8 UDSAPP_WRITE_BY_ADDRESS(UDS_UINT32 Data_Address,const UDS_UINT8 *pdiagdata, UDS_UINT32 DataSize)
{
  UDS_UINT8 fl_WriteStatus_u8 = (uint8_t)1;
  UDS_UINT32*UDS_memory_ADDRESS = ((UDS_UINT32*)Data_Address);
  memcpy(UDS_memory_ADDRESS,pdiagdata,DataSize);
  return fl_WriteStatus_u8; 
}

//uint8_t value = 0;

UDS_UINT8 UDSAPP_FLASH_WRITE_BY_ADDRESS(UDS_UINT32 Data_Address,const UDS_UINT8 *pdiagdata, UDS_UINT32 DataSize)
{
  UDS_UINT32 flash_WriteStatus_u32 = (uint32_t)1;
  UDS_UINT32*UDS_memory_ADDRESS = ((UDS_UINT32*)Data_Address);
  //ROM_FLEXSPI_NorFlash_Erase(FlexSpiInstance, &norConfig,  UDS_memory_ADDRESS,DataSize);
  //ROM_NorFlash_ProgramPage(UDS_memory_ADDRESS,pdiagdata,DataSize);
  return flash_WriteStatus_u32; 
}

/*
* @brief    This API is used to configure the Application check for write memory by address
* @param    pdiagdata - Diagnostic request frame received from the client
* @param    RID - Routine Identifier
* @param    datalength - Data length of the Routine Control record
* @return   EcuReset Condition Status
**/
UDS_UINT8 UDSAPP_READ_BY_ADDRESS( UDS_UINT32 Data_Address,UDS_UINT8 *pdiagdata, UDS_UINT16 DataSize)
{  
  
  UDS_UINT8 fl_WriteStatus_u8 = (uint8_t)1;
  UDS_UINT8 fl_data_index = UDS_ZERO;

  UDS_UINT32*UDS_memory_ADDRESS = ((UDS_UINT32*)Data_Address);

  for(fl_data_index =0 ;fl_data_index<DataSize ; fl_data_index++)
  {
  pdiagdata[fl_data_index] = *UDS_memory_ADDRESS ;
  UDS_memory_ADDRESS++;

  }
 

}

/*
* @brief    This API is used to configure the Application check routine control option  record
* @param    pdiagdata - Diagnostic request frame received from the client
* @param    RID - Routine Identifier
* @param    datalength - Data length of the Routine Control record
* @return   EcuReset Condition Status
**/
UDS_UINT8 Application_Check_Routine_Ctrl_Option_Record_Match(const UDS_UINT8 *pdiagdata, UDS_UINT16 RID, UDS_UINT8 datalength)
{
  UDS_UINT8 fl_RoutineCtrl_Record_Match_Status_u8 = (UDS_UINT8)1;
  /*To be configured by the Integrator with corresponding API to Clear DTC*/
  UDS_UINT32 fl_download_address = (UDS_UINT32)0;
  UDS_UINT32 fl_download_length  = (UDS_UINT32)0;
  if(RID == (UDS_UINT16)0xff00)
  {

      fl_download_address |= (UDS_UINT32)((UDS_UINT32)pdiagdata[0] << 24);
      fl_download_address |= (UDS_UINT32)((UDS_UINT32)pdiagdata[1] << 16);
      fl_download_address |= (UDS_UINT32)((UDS_UINT32)pdiagdata[2] << 8);
      fl_download_address |= (UDS_UINT32)pdiagdata[3];

      fl_download_length |= (UDS_UINT32)((UDS_UINT32)pdiagdata[4] << 24);
      fl_download_length |= (UDS_UINT32)((UDS_UINT32)pdiagdata[5] << 16);
      fl_download_length |= (UDS_UINT32)((UDS_UINT32)pdiagdata[6] << 8);
      fl_download_length |= (UDS_UINT32)pdiagdata[7];

      UDS_APP_OEM_ERASE_REQUEST(fl_download_address, fl_download_length);
  }
  /*The above variable to be set/cleared based on successful/unsuccessful status (UDS_TRUE/ UDS_FALSE) respectively*/
  return fl_RoutineCtrl_Record_Match_Status_u8;
}


/*
 * @brief    This sample function is used to show the implementation skeleton for start routine handler 
 * @param    Routine Identifier RID
 * @return   Routine execution status (UDS_TRUE - successful, UDS_FALSE - unsuccessful)
 **/
UDS_UINT8 Sample_Routine_Start(UDS_UINT16 RID)
{
  /*Implementation to be done - USER-SPECIFIC code expected*/
  
  /*Return value to be UDS_FALSE - UNSUCCESSFUL & UDS_TRUE if SUCCESSFUL*/
  return UDS_TRUE;
}

/*
 * @brief    This sample function is used to show the implementation skeleton for stop routine handler 
 * @param    Routine Identifier RID
 * @return   Routine execution status (UDS_TRUE - successful, UDS_FALSE - unsuccessful)
 **/
UDS_UINT8 Sample_Routine_Stop(UDS_UINT16 RID)
{
  /*Implementation to be done - USER-SPECIFIC code expected*/
  /*Return value to be UDS_FALSE - UNSUCCESSFUL & UDS_TRUE if SUCCESSFUL*/
    return UDS_TRUE;
}

/*
 * @brief    This sample function is used to show the implementation skeleton for get results routine handler
 * @param    RID - Routine Identifier
 * @param    RespDataBuff - Pointer to update the response buffer with routine results
 * @param    DataLen - Pointer to update the length  of the buffer after updating with Routine results
 * @return   Routine execution status (UDS_TRUE - successful, UDS_FALSE - unsuccessful)
 **/
UDS_UINT8 Sample_Routine_Result(uint16_t RoutineControlIndex, UDS_UINT8 *RespDataBuff, UDS_UINT8 *DataLen)
{
  /*Implementation to be done - USER-SPECIFIC code expected*/
  /*To be made sure that @param: RespDataBuff is updated with     Routine Result data to be 
    transmitted to the client*/
  /*To be made sure that @param: DataLen  is updated with the total length of the routine results 
    in bytes for Uds Application's transmission visibility*/
  /*Return value to be UDS_FALSE - UNSUCCESSFUL & UDS_TRUE if SUCCESSFUL*/

	/* GET THE RESULT FROM THE FUNCTION PTR */
	if(g_Routine_List_st[RoutineControlIndex].result_fnptr != NULL)
	{
		RespDataBuff[0] = g_Routine_List_st[RoutineControlIndex].result_fnptr();
		*DataLen = 1;/*  SET THE LENGTH AS 1 */
	}

	return UDS_TRUE;
}

/*
 * @brief    This  function is used to get the pre condition status
 * @param    NIL
 * @return   Returns the pre-condition status as true or false.
 **/
boolean RoutineControl_Pre_Condition_check(void)
      {

          /* check previous condition states such as ign,LVSD/HVSD * from the function if it false it goes off condition */
           bool g_UDS_pre_condition_Status = UDS_FALSE;
           UDS_UINT8 fl_ROUTINECTL_IGN_POSITION_u8;
           UDS_UINT8 fl_ROUTINECTL_LVSD_u8;
           UDS_UINT8 fl_ROUTINECTL_HVSD_u8;


          fl_ROUTINECTL_IGN_POSITION_u8 = UDS_GET_IGN_POSITION();
          fl_ROUTINECTL_LVSD_u8 = UDS_GET_LOW_VOLTAGE_STATE();
          fl_ROUTINECTL_HVSD_u8 = UDS_GET_HIGH_VOLTAGE_STATE();

          /* check condition for ignition position and low/high power state of the ALS system */
          if((fl_ROUTINECTL_IGN_POSITION_u8  != IGN_ON) && \
          (fl_ROUTINECTL_LVSD_u8 != SYSTEM_SERVICE_NORMAL_VOLTAGE) &&\
          (fl_ROUTINECTL_HVSD_u8 != SYSTEM_SERVICE_NORMAL_VOLTAGE))
          {
          /* If the pre condition is true then do the routine control else returned to off state */
       	   g_UDS_pre_condition_Status = UDS_TRUE;
          }
          else
          {
           /* do nothing */
          }

          return g_UDS_pre_condition_Status;
      }


/*
 * @brief    This  function is used to get the status of the voltage range
 * @param    NIL
 * @return   It returns the voltage range.
 **/
       UDS_UINT8 UDS_VOLTAGE_STATUS(void)
       {
        UDS_UINT8 UDS_VOLTAGE_STATUS;
        UDS_UINT8 fl_UDS_TRANSFERDATA_LVSD_u8;
        UDS_UINT8 fl_UDS_TRANSFERDATA_HVSD_u8;

        
        fl_UDS_TRANSFERDATA_LVSD_u8 = UDS_GET_LOW_VOLTAGE_STATE();
        fl_UDS_TRANSFERDATA_HVSD_u8 = UDS_GET_HIGH_VOLTAGE_STATE();

        if ((fl_UDS_TRANSFERDATA_LVSD_u8 == SYSTEM_SERVICE_NORMAL_VOLTAGE) &&\
           (fl_UDS_TRANSFERDATA_HVSD_u8 == SYSTEM_SERVICE_NORMAL_VOLTAGE))
           {
            UDS_VOLTAGE_STATUS = NORMAL_VOLTAGE;
           }
           else if (fl_UDS_TRANSFERDATA_LVSD_u8 != SYSTEM_SERVICE_NORMAL_VOLTAGE) 
           {
            UDS_VOLTAGE_STATUS = LOW_VOLTAGE;
           }
           else
           {
            UDS_VOLTAGE_STATUS = HIGH_VOLTAGE;
           }

        return UDS_VOLTAGE_STATUS;     
       }

/* update the variable with WAKEUP_E_OK VALUE */
UDS_UINT8 network_request_val = (WAKEUP_E_OK);

/*
 * @brief    This  function is used to enable the communication control on CAN
 * @param    NIL
 * @return   It returns the communication control status
 **/
UDS_UINT8 COMMUNICATION_CONTROL_ENABLE(void)
{
  
}  

/*
 * @brief    This  function is used to disable the communication control on CAN
 * @param    NIL
 * @return   It returns the communication control status
 **/
UDS_UINT8 COMMUNICATION_CONTROL_DISABLE(void)
{

} 


uint8_t UDS_EXTERNAL_EEPROM_MEMORY_READ_BLKID(void)
{
  /*Implementation to be done - USER-SPECIFIC code expected*/
  /*Return value to be UDS_FALSE - UNSUCCESSFUL & UDS_TRUE if SUCCESSFUL*/
    return UDS_TRUE;
}

uint8_t UDS_NVM_CHECKSUM(void)
{
  uint8_t fl_checksum_Buff[10] ={0,1,2,3,4,5,6,7,8,9};
  uint8_t fl_checksum_Size = 10;
  uint8_t fl_checksum_result = 0;
  uint8_t fl_checksum_Index = 0;

  for(fl_checksum_Index =0; fl_checksum_Index<=fl_checksum_Size; fl_checksum_Size++ )
  {
    fl_checksum_result = fl_checksum_result ^ fl_checksum_Buff[fl_checksum_Index];
  }

   return fl_checksum_result;
 }

 uint8_t UDS_FLASH_CHECKSUM(void)
 {
    uint8_t *fl_address = (uint8_t *)0x3000;
    uint8_t fl_checksum_Buff = 0;
    uint8_t fl_checksum_Size = 10;
    uint8_t fl_checksum_result = 0;
    uint8_t fl_checksum_Index = 0;

    
    for(fl_checksum_Index =0; fl_checksum_Index <= fl_checksum_Size; fl_checksum_Size++ )
    {
      fl_checksum_Buff = *fl_address;
      fl_address++;
      fl_checksum_result = fl_checksum_result ^ fl_checksum_Buff;
    }

    return fl_checksum_result;
 }

uint8_t UDS_HYPERFLASH_MEMORY_CHECKSUM(void)
{
 /*Implementation to be done - USER-SPECIFIC code expected*/
  /*Return value to be UDS_FALSE - UNSUCCESSFUL & UDS_TRUE if SUCCESSFUL*/
    return UDS_TRUE;
}

uint8_t UDS_ANALOG_INPUT_CHECK(void)
{
   /*Implementation to be done - USER-SPECIFIC code expected*/
  /*Return value to be UDS_FALSE - UNSUCCESSFUL & UDS_TRUE if SUCCESSFUL*/
    return UDS_TRUE;
}

uint8_t UDS_BLE_STATUS_READ(void)
{
   /*Implementation to be done - USER-SPECIFIC code expected*/
  /*Return value to be UDS_FALSE - UNSUCCESSFUL & UDS_TRUE if SUCCESSFUL*/
    return UDS_TRUE;
}

uint8_t UDS_PROGRAM_ALL_NVM(void)
{
 /*Implementation to be done - USER-SPECIFIC code expected*/
  /*Return value to be UDS_FALSE - UNSUCCESSFUL & UDS_TRUE if SUCCESSFUL*/
    return UDS_TRUE;
}


uint8_t UDS_PROGRAM_PRECONDITION_CHECK(void)
{
	/* CHECK FOR THE PRECONDITONS */
	/* CHECK FOR THE NOMINAL BATTERY VOLTAGE */
	if(SysService_Get_BatteryVoltageSts() == SYSTEM_SERVICE_NORMAL_VOLTAGE)
	{
		/* CHECK FOR THE SPEED LESS THAN 10 KMPH */
		if(Get_display_Speed() < 10)
		{
			/* RETURN POSITIVE STATUS */
			UDS_Prog_PreConditionResult = 1;
		}
		else
		{
			/* RETURN FAIL STATUS */
			UDS_Prog_PreConditionResult = 0;
		}
	}
	else
	{
		/* RETURN FAIL STATUS */
		UDS_Prog_PreConditionResult = 0;
	}

	return 1;
}

uint8_t UDS_PROGRAM_PRECONDITION_CHECK_RESULT(void)
{
	return UDS_Prog_PreConditionResult;
}

uint8_t UDS_NVM_CHECKSUM_RESULT (void)
{
  //return checksum_value;
  return 0;
}


/***********************************************************************************************************************
                                              E N D   O F   S O F T W A R E                                         
**********************************************************************************************************************/
#ifdef __cplusplus
}
#endif

/***********************************************************************************************************************
*                                              R E V I S I O N   H I S T O R Y                                       
***********************************************************************************************************************
    REVISION NUMBER      : V1.0.1                                                           
    REVISION DATE        : 31-Jul-2020                                  
    CREATED / REVISED BY : Sharmili N (sharmili@niyatainfotech.com)   
    DESCRIPTION          : Bootloader & Application UDS merged                              
------------------------------------------------------------------------------------------------------------------------
    REVISION NUMBER      : V1.0.0                                                           
    REVISION DATE        : 16-Apr-2020                                  
    CREATED / REVISED BY : Sharmili N (sharmili@niyatainfotech.com)   
    DESCRIPTION          : Initial Version                              
------------------------------------------------------------------------------------------------------------------------

***********************************************************************************************************************/
#endif /* ! UDSAPP_SUPPORT_C */

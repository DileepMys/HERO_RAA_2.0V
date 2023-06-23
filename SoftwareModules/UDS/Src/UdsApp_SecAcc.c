/* @file UDSAPP_SECACC_C */
#ifndef UDSAPP_SECACC_C
#define UDSAPP_SECACC_C

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
*  File name                       : UdsApp_SecAcc.c
*  Version                         : V2.0.1
*  Micros supported                : Micro Agnostic (Independent)
*  Compilers supported             : XXXXX
*  Platforms supported             : XXXXX
*  Description                     : This file consists of definition of Security Access Seed Generation algorithm process


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
#include "UdsApp.h"
#include "UdsApp_SecAcc.h"
#include "stdlib.h"
//#include "rti.h"

/***********************************************************************************************************************
*                                          M A C R O   D E F I N I T I O N S                                         
***********************************************************************************************************************/

/***********************************************************************************************************************
*                                          L O C A L  V A R I A B L E   D E F I N I T I O N S                                           
***********************************************************************************************************************/

/***********************************************************************************************************************
*                                    P R I V A T E     F U N C T I O N S    D E C L A R A T I O N                      
***********************************************************************************************************************/
/*
* @brief    This function is used to generate the Seed's byte 1 using Timer value
* @param    TimerByteVal - Timer byte 1 value
* @return   UINT8 - GeneratedSeed Byte1
*/
static UDS_UINT8 Uds_SecAcc_SeedByte1_Generation(UDS_UINT8 TimerByteVal);

/*
* @brief    This function is used to generate the Seed's byte 2 using Timer value
* @param    TimerByteVal - Timer byte 2 value
* @return   UINT8 - GeneratedSeed Byte2
*/
static UDS_UINT8 Uds_SecAcc_SeedByte2_Generation(UDS_UINT8 TimerByteVal);

/*
* @brief    This function is used to generate the Seed's byte 3 using Timer value
* @param    TimerByteVal - Timer byte 3 value
* @return   UINT8 - GeneratedSeed Byte3
*/
static UDS_UINT8 Uds_SecAcc_SeedByte3_Generation(UDS_UINT8 TimerByteVal);

uint32_t g_ECUGeneratedKey_u8 = 0;

/***********************************************************************************************************************
*                                    P U B  L I C     F U N C T I O N S    D E F I N I T I O N                      
***********************************************************************************************************************/
/*
* @brief    This function is used to generate the Secure Seed with the existing known values of Key, C1 & C2
* @param    NULL
* @return   UINT32 - GeneratedKey
*/


#define UNUM16 short
#define UNUM32 int

enum HeroKeyGenResult
{
  KGRE_Ok = 0,
  KGRE_BufferToSmall = 1,
  KGRE_SecurityLevelInvalid = 2,
  KGRE_VariantInvalid = 3,
  KGRE_UnspecifiedError = 4
};



enum HeroKeyGenResult GenerateKey_IC(
   unsigned int* ipSeedArray, unsigned int iSeedArraySize,
   unsigned int* iopKeyArray, unsigned int iMaxKeyArraySize, 
   unsigned int oActualKeyArraySize)
{
    uint16_t lu16_const1 = 0x4943;// "IC"
	uint16_t lu16_const2 = 0x4142;  // "0x4142 Value given by HMCL-CIT"
	uint32_t  mu32Key=0;
    uint32_t mu32_seed = 0;
    uint16_t  mu32_temp1= 0;
    uint16_t  mu32_temp2 = 0;

	mu32Key = *(iopKeyArray);
	mu32_seed = *(ipSeedArray);
    uint16_t mu32_local_temp1 =  (uint16_t)(mu32_seed >> 16) ;
    uint16_t mu32_local_temp2 = (mu32_local_temp1 * lu16_const2) ;
    uint16_t temp1_value1 =  (uint16_t)(mu32_local_temp2 + lu16_const1);
	mu32_temp1 = (uint16_t)(temp1_value1 * lu16_const2);

     
	uint16_t mu32_local2_temp1 = (uint16_t)(mu32_seed & 0x0000FFFF);
    uint16_t mu32_local2_temp2 = (uint16_t)(mu32_local2_temp1 * lu16_const1);
    uint16_t temp2_value1 =  mu32_local2_temp2 + lu16_const2;
	mu32_temp2 =(uint16_t)(temp2_value1 * lu16_const1);


	mu32Key = (uint32_t)((mu32_temp1 << 16) & 0xFFFFFFFF);
	mu32Key = (uint32_t)(mu32Key|mu32_temp2);  
  

	*(iopKeyArray) = mu32Key;

    return KGRE_Ok;

}



void UdsApp_SecurityAccess_SeedGeneration(uint8_t *buffer)
{
        unsigned int Seed = rand(), Key=0;

        memcpy(&buffer[0], &Seed, 4);

        GenerateKey_IC(&Seed,sizeof(int),&Key,0x4,sizeof(int));
		
        printf("Seed - 0x%x\n", Seed);
        printf("Key - 0x%x\n", Key);

        g_ECUGeneratedKey_u8 = Key;

    return ;
}

uint32 rtiGetCounter(uint32 counter)
{
  //   return rtiREG1->CNT[counter].FRCx;
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
    REVISION NUMBER      : V2.0.1
    REVISION DATE        : 10-Aug-2020
    CREATED / REVISED BY : Sharmili N (sharmili@niyatainfotech.com)
    DESCRIPTION          : Code alignment  done
------------------------------------------------------------------------------------------------------------------------
    REVISION NUMBER      : V2.0.0                                                           
    REVISION DATE        : 11-May-2020                                  
    CREATED / REVISED BY : Sharmili N (sharmili@niyatainfotech.com)   
    DESCRIPTION          : Security Seed Generation algorithm implemented & removed Key generation algorithm                              
------------------------------------------------------------------------------------------------------------------------    
    REVISION NUMBER      : V1.0.0                                                           
    REVISION DATE        : 27-Mar-2020                                  
    CREATED / REVISED BY : Sharmili N (sharmili@niyatainfotech.com)   
    DESCRIPTION          : Initial Version                              
------------------------------------------------------------------------------------------------------------------------

***********************************************************************************************************************/
#endif /* ! UDSAPP_SECACC_C */


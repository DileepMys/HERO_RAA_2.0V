/* @file CRC_C */
#ifndef CRC_C
#define CRC_C

/***********************************************************************************************************************
 *    DISCLAIMER
 *   Copyright (C) 2011, 2016 Niyata Infotech Pvt. Ltd. All rights reserved.
 ***********************************************************************************************************************/

/************************************************************************************************************************
 * @author              Author : Sharmili N (sharmili@niyatainfotech.com)
 ***********************************************************************************************************************/

/***********************************************************************************************************************
 *                                                F I L E  D E S C R I P T I O N
 **----------------------------------------------------------------------------------------------------------------------
 *  @brief
 *
 *  File name                       : Crc.c
 *  Version                         : V1.0.1
 *  Micros supported                : Micro Agnostic (Independent)
 *  Compilers supported             : XXXXX
 *  Platforms supported             : XXXXX
 *  Description                     : This file consists of definitions of CRC
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
#include "Crc.h"
#include "Crc_Cfg.h"

/*Upon SAE J1850 standard selection, the below implementations shall be included*/
#if(CRC_CALCULATION_METHOD == CRC8_SAE_J1850)


/***********************************************************************************************************************
 *                                          L O C A L  V A R I A B L E   D E F I N I T I O N S
 ***********************************************************************************************************************/
#if (CRC8_CALCULATE_MODE == CRC8_HASHTABLE_CALCULATE)
/*
 * @brief: This variable is used as a lookup table for the CRC8 calculation as per SAE J1850 standard
 *         with polynomial 0x1D, initial value 0xFF and final XOR 0xFF
 * @Unit:  N/A
 * @Resolution: N/A
 * @Range: N/A
 * @Applicability: Yes if CRC8_HASHTABLE_CALCULATE mode is chosen
 * @Note: Do not alter the value of this variable
 */
static uint8_t l_CRC8_HashTable_u8[256];

/*
 * @brief    This function is used to fill the hash table with SAE J1850's polynomial based on configuration
 * @param    NULL
 * @return   NULL
 * @applicability     Yes if CRC8_HASHTABLE_CALCULATE mode is chosen.
 */
static void Fill_HashTable_CRC8(void);
#endif


/***********************************************************************************************************************
 *                                    P R I V A T E     F U N C T I O N S    D E C L A R A T I O N
 ***********************************************************************************************************************/
#if (CRC8_CALCULATE_MODE == CRC8_RUNTIME_CALCULATE)
/*
 * @brief    This function processes the calculation CRC8 as per SAE J1850 standard in Runtime without using the Hash table
 * @param    MsgPtr Data pointer to calculate checksum
 * @param    Ptr_Length - length of the pointer
 * @return   Crc remainder
 * @applicability     Yes if CRC8_RUNTIME_CALCULATE mode is chosen.
 */
static uint8_t Runtime_Calculate_CRC8(const uint8_t* MsgPtr, uint32_t Ptr_Length);

#endif
/***********************************************************************************************************************
 *                                          F U N C T I O N     D E F I N I T I O N S
 ***********************************************************************************************************************/
/*
 * @brief    This service initializes CRC layer
 * @param    NULL
 * @return   NULL
 * @note     To be made use if Hash table calculation is used
 */
void Crc_Init(void)
{
#if (CRC8_CALCULATE_MODE == CRC8_HASHTABLE_CALCULATE)
    /*Initialize the hash table with CRC calculation data with the polynomial value provided in configurations*/
    Fill_HashTable_CRC8();
#endif
}

/*
 * @brief    This service makes a CRC8 calculation on Crc_Length data bytes, with SAE J1850 parameters
 * @param    CAN ID - message ID of data to be calculated 
 * @param    Pointer to start address of data block to be calculated.
 * @param    Length of data block to be calculated in bytes.
 * @param    Start value when the algorithm starts.
 * @param    TRUE: First call in a sequence or individual CRC calculation; start from initial value, ignore Crc_StartValue8. 
             FALSE: Subsequent call in a call sequence; Crc_StartValue8 is interpreted to be the return value of previous function call.
 * @return   uint8_t - 8 bit result of CRC calculation.
 */
uint8_t Crc_CalculateCRC8(uint16_t CAN_ID , const uint8_t* Crc_DataPtr, uint32_t Crc_Length)
{
    /*Declaration of function local variables*/
    uint8_t fl_crc_u8 = CRC8_INIT_VALUE;

    /*Verify whether the Data pointer is valid*/
    if (Crc_DataPtr != NULL) 
    {
        /*CRC calculation in Runtime*/
        #if (CRC8_CALCULATE_MODE == CRC8_RUNTIME_CALCULATE)
            fl_crc_u8 = Runtime_Calculate_CRC8(Crc_DataPtr, Crc_Length);
        #endif

        /*CRC calculation with Hash table*/
        #if (CRC8_CALCULATE_MODE == CRC8_HASHTABLE_CALCULATE)

        uint32_t fl_byte_u32;
        uint8_t fl_LowerByte_DATA_ID_U8;
        uint8_t fl_HigherByte_DATA_ID_U8;
        uint16_t fl_DataID_U16;

        /* Calculate DATA ID */
        fl_DataID_U16 = CAN_ID + 0xF008;

        /* Get lower byte of CAN Message ID*/
        fl_LowerByte_DATA_ID_U8 = fl_DataID_U16 & (0x00FF);

        /* Get Higher byte of CAN Message ID*/
        fl_HigherByte_DATA_ID_U8 = (fl_DataID_U16 >> 8);

        fl_crc_u8 = l_CRC8_HashTable_u8[fl_LowerByte_DATA_ID_U8 ^ fl_crc_u8];

        fl_crc_u8 = l_CRC8_HashTable_u8[fl_crc_u8 ^ fl_HigherByte_DATA_ID_U8];

        /*Calculate the CRC value as per the algorithm*/
        for (fl_byte_u32 = (uint8_t)0; fl_byte_u32 < Crc_Length; fl_byte_u32++)
        {
            fl_crc_u8 = l_CRC8_HashTable_u8[fl_crc_u8 ^ *Crc_DataPtr];
            Crc_DataPtr++;
        }
        #endif

        /*Final XOR*/
        fl_crc_u8 = fl_crc_u8 ^ CRC8_XOR_VALUE;
    }

    /*Return the calculated CRC*/
    return fl_crc_u8;
}

#if (CRC8_CALCULATE_MODE == CRC8_HASHTABLE_CALCULATE)
/*
 * @brief    This function is used to fill the hash table with SAE J1850's polynomial based on configuration
 * @param    NULL
 * @return   NULL
 * @note     Yes if CRC8_HASHTABLE_CALCULATE mode is chosen.
 */
static void Fill_HashTable_CRC8(void)
{
    uint16_t fl_hashtable_index_u8;
    uint8_t fl_shiftindex_u8 = (uint8_t)0;
    uint8_t fl_crc_u8 = (uint8_t)0;

    for(fl_hashtable_index_u8 = (uint8_t)0; (fl_hashtable_index_u8 <= (uint8_t)255); fl_hashtable_index_u8++)
    {
        fl_crc_u8 = fl_hashtable_index_u8;
        for(fl_shiftindex_u8 = (uint8_t)0; fl_shiftindex_u8 < (uint8_t)8; ++fl_shiftindex_u8)
        {
            if((fl_crc_u8 & (uint8_t)0x80) != (uint8_t)0)
            {
                fl_crc_u8 = ((fl_crc_u8 << (uint8_t)1) ^ CRC8_POLYNOMIAL_VALUE);
            }
            else
            {
                fl_crc_u8 = (fl_crc_u8 << (uint8_t)1);
            }
            l_CRC8_HashTable_u8[fl_hashtable_index_u8] = fl_crc_u8;
        }
    }
}
#endif

#if (CRC8_CALCULATE_MODE == CRC8_RUNTIME_CALCULATE) 
/*
 * @brief    This function processes the calculation CRC8 as per SAE J1850 standard in Runtime without using the Hash table
 * @param    MsgPtr Data pointer to calculate checksum
 * @param    Ptr_Length - length of the pointer
 * @return   Crc remainder
 * @applicability     Yes if CRC8_RUNTIME_CALCULATE mode is chosen.
 */
static uint8_t Runtime_Calculate_CRC8(const uint8_t* MsgPtr, uint32_t Ptr_Length)
{
    uint8_t fl_crc_u8 = CRC8_INIT_VALUE;
    uint8_t fl_shiftindex_u8;
    uint32_t fl_loopindex_u32;

    for(fl_loopindex_u32 = (uint32_t)0; fl_loopindex_u32 < Ptr_Length; fl_loopindex_u32++)
    {
        fl_crc_u8 = (fl_crc_u8 ^ MsgPtr[fl_loopindex_u32]);

        for(fl_shiftindex_u8 = (uint8_t)0; fl_shiftindex_u8 < (uint8_t)8; ++fl_shiftindex_u8)
        {
            if((fl_crc_u8 & (uint8_t)0x80) != (uint8_t)0)
            {
                fl_crc_u8 = ((fl_crc_u8 << (uint8_t)1) ^ CRC8_POLYNOMIAL_VALUE);
            }
            else
            {
                fl_crc_u8 = (fl_crc_u8 << (uint8_t)1);
            }
        }
    }
    return fl_crc_u8;
}
#endif


/***********************************************************************************************************************
                                              E N D   O F   S O F T W A R E                                         
*********************************************************************************************************************/
#ifdef __cplusplus
}
#endif

/***********************************************************************************************************************
*                                              R E V I S I O N   H I S T O R Y                                       
***********************************************************************************************************************
     REVISION NUMBER      : V1.0.1
     REVISION DATE        : 05/03/2020
     CREATED / REVISED BY : Sharmili N(sharmili@niyatainfotech.com)
     DESCRIPTION          : Run time crc calculation api implemented.
                            Fill_HashTable static function added and implemented.
                            Crc_Init function added to fill in hash table based on polynomial in init.
-------------------------------------------------------------------------------------
    REVISION NUMBER      : V1.0.0                                                
    REVISION DATE        : 24-Feb-2021                              
    CREATED / REVISED BY : Sharmili N (sharmili@niyatainfotech.com)   
    DESCRIPTION          : Initial version                                  
------------------------------------------------------------------------------------------------------------------------

***********************************************************************************************************************/
#endif

#endif /* CRC_C */

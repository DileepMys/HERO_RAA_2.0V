/* @file UDS_TYPES_H */
#ifndef UDS_TYPES_H_
#define UDS_TYPES_H_

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
*  File name                       : Uds_Types.h
*  Version                         : V1.0.0
*  Micros supported                : Micro Agnostic (Independent)
*  Compilers supported             : XXXXX
*  Platforms supported             : XXXXX
*  Description                     : This header file contains the Type defintions of Uds
*  @bug                            : N/A
--------------------------------------------------------------------------------------------------------------------*/

/**********************************************************************************************************************/

/***********************************************************************************************************************
*                                            M A C R O   D E F I N I T I O N S
***********************************************************************************************************************/
/*
* @brief This macro is used to define False status
  @Unit:  N/A
  @Resolution: N/A
  @Range: N/A
  @Applicability: N/A
  @Note:  Do not modify this macro value or name
*/
#define UDS_FALSE                 0x00u

/*
* @brief This macro is used to define True status
  @Unit:  N/A
  @Resolution: N/A
  @Range: N/A
  @Applicability: N/A
  @Note:  Do not modify this macro value or name
*/
#define UDS_TRUE                  1u

/*
* @brief This macro is used to define Enable value
  @Unit:  N/A
  @Resolution: N/A
  @Range: N/A
  @Applicability: N/A
  @Note:  Do not modify this macro value or name
*/
#define DIAG_RESP_REQ                     0x01u

/*
* @brief This macro is used to define Disable value
  @Unit:  N/A
  @Resolution: N/A
  @Range: N/A
  @Applicability: N/A
  @Note:  Do not modify this macro value or name
*/
#define DIAG_RESP_NOT_REQ                    0x00u

/***********************************************************************************************************************
*                                          T Y P E   D E F I N I T I O N S
***********************************************************************************************************************/

typedef unsigned char UDS_UINT8;
typedef unsigned short UDS_UINT16;
typedef unsigned int UDS_UINT32;

/**
 * @brief    This typedef is used as Pointer to execute the corresponding routine when requested
 * @param    Routine Identifier RID
 * @return   Routine execution status
 **/
typedef UDS_UINT8 (*StartStopRoutineHandler_type) (UDS_UINT16 RID);

/**
 * @brief    This typedef is used as Pointer to execute the corresponding routine when requested
 * @param    RID - Routine Identifier
 * @param    RespDataBuff - Pointer to update the response buffer with routine results
 * @param    DataLen - Pointer to update the length  of the buffer after updating with Routine results
 * @return   Routine execution status
 **/
typedef UDS_UINT8 (*GetResultRoutineHandler_type) (UDS_UINT16 RoutineControlIndex, UDS_UINT8 *RespDataBuff, UDS_UINT8 *DataLen);

/***********************************************************************************************************************
                                              E N D   O F   S O F T W A R E
*********************************************************************************************************************/

/***********************************************************************************************************************
*                                              R E V I S I O N   H I S T O R Y
***********************************************************************************************************************
    REVISION NUMBER      : V1.0.0
    REVISION DATE        : 26-June-2020
    CREATED / REVISED BY : Sharmili N (sharmili@niyatainfotech.com)
    DESCRIPTION          : Initial version
------------------------------------------------------------------------------------------------------------------------

***********************************************************************************************************************/
#endif /* ! UDS_TYPES_H_ */

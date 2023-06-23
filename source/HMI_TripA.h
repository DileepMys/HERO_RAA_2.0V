/* @file FILE NAME */
#ifndef HMI_TRIPA_H
#define HMI_TRIPA_H

/***********************************************************************************************************************
*    DISCLAIMER
*   Copyright (C) 2020 Niyata Infotech Pvt. Ltd. All rights reserved.                                             
***********************************************************************************************************************/

/************************************************************************************************************************
* @author              Author : Santhosh Rajavel (santhoshrajavel@niyatainfotech.com)                                                                        
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
*  Description                     : This header file contains the declarations of 
*  @bug                            : N/A
--------------------------------------------------------------------------------------------------------------------*/

/**********************************************************************************************************************/

/**********************************************************************************************************************/
/***********************************************************************************************************************
*                                               I N C L U D E   CONFIGURATION F I L E S 
***********************************************************************************************************************/
#include "hal_stdtypes.h"

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
//signed int Tex_Lb1_val[2]={50,18};

//signed int Avfuel_L2_val[2]={12,38};

/***********************************************************************************************************************
*                                          T Y P E   D E F I N I T I O N S                                           
***********************************************************************************************************************/

/*
 * @brief    This typedef is used to define 
 * @param    
 * @return
 **/


/*
 * @brief    This typedef enum is used to define 
 * @param    
 * @param
 **/


/*
 * @brief    This structure is used to define 
 * @param    
 * @param    
 **/

typedef struct
{
     lv_obj_t *Label_Name;
    signed int *Label_X_Pos;
    signed int *Label_Y_Pos;
}g_Trip_Time_Pos;


typedef struct
{
    const lv_obj_t *Label_Name;
    signed int *Label_X_Pos;
    signed int *Label_Y_Pos;
    signed int *Label_W_Pos;
    signed int *Label_H_Pos;
}g_Trip_Average_Fuel_Pos;


/***********************************************************************************************************************
*                                    P U B L I C     F U N C T I O N S    D E C L A R A T I O N                      
***********************************************************************************************************************/

/*
* @brief    This API is used to 
* @param    
* @return  
* @invocation 
*/

void GUI_TripA_Init(void);

void GUI_TripA_DeInit(void);

void GUI_TripA_Activate(void);

void GUI_TripA_DeActivate(void);

void GUI_TripA_Main_Screen(uint8_t Screen_Main_Int_u8, uint8_t Day_Night_Mode_u8);

void GUI_TripA_Trip_Time_Screen(uint8_t Screen_Main_Int_u8, uint8_t Day_Night_Mode_u8);

void GUI_TripA_AVF_AVS_Screen(uint8_t Screen_Main_Int_u8, uint8_t Day_Night_Mode_u8);

void GUI_TripA_Main_Screen_During(void);
void GUI_TripA_Main_Screen_Entry(void);
void GUI_TripA_Main_Screen_Exit(void);

void GUI_TripA_Trip_Time_Screen_During(void);
void GUI_TripA_Trip_Time_Screen_Entry(void);
void GUI_TripA_Trip_Time_Screen_Exit(void);

void GUI_TripA_AVF_AVS_Screen_During(void);
void GUI_TripA_AVF_AVS_Screen_Entry(void);
void GUI_TripA_AVF_AVS_Screen_Exit(void);

void GUI_TripA_Main_Screen_Night_Entry(void);
void GUI_TripA_Main_Screen_Night_Exit(void);
void GUI_TripA_Main_Screen_Night_During(void);

void TripA_Main_Day_Entry(void);
void TripA_Main_Day_During(void);
void TripA_Main_Day_Exit(void);

void TripA_Time_Day_Entry(void);
void GUI_TripA_Time_Day_During(void);
void TripA_Time_Day_Exit(void);

void TripA_AVF_Day_Entry(void);
void TripA_AVF_Day_During(void);
void TripA_AVF_Day_Exit(void);

uint8_t TripA_Button_UpEvent(void);

uint8_t TripA_Button_DownEvent(void);

/***********************************************************************************************************************
                                              E N D   O F   S O F T W A R E                                         
*********************************************************************************************************************/


/***********************************************************************************************************************
*                                              R E V I S I O N   H I S T O R Y                                       
/***********************************************************************************************************************
    REVISION NUMBER      : Major.Minor.Patch                                                
    REVISION DATE        : MONTH/DATE/YEAR                              
    CREATED / REVISED BY : Santhosh Rajavel (santhoshrajavel@niyatainfotech.com)   
    DESCRIPTION          : Initial version                                  
------------------------------------------------------------------------------------------------------------------------

***********************************************************************************************************************/
#endif /* ! FILE NAME */

/* @file UDS_CFG_C */
#ifndef UDS_CFG_C
#define UDS_CFG_C

/***********************************************************************************************************************
*   DISCLAIMER
*   Copyright © 2011, 2016 Niyata Infotech Pvt. Ltd. All rights reserved.                                             
***********************************************************************************************************************/

/***********************************************************************************************************************
*                                                F I L E  D E S C R I P T I O N                                        
**----------------------------------------------------------------------------------------------------------------------
*  @brief
*
*  File name                       : UDS_Cfg.c
*  Generation Time                 : 18-10-2022 16:41:17
*  Tool Version                    : UDS_Configurator  2.2.1.0
*  Description                     : This file contains the configuration elements of UDS Core Layer
*  @bug                            : N/A
*--------------------------------------------------------------------------------------------------------------------*/

/**********************************************************************************************************************/
#ifdef __cplusplus
extern "C"
{
#endif
/**********************************************************************************************************************/

/***********************************************************************************************************************
*                                               I N C L U D E   F I L E S                                            
***********************************************************************************************************************/
#include "UdsApp.h"
  /***********************************************************************************************************************
*                                          C O N F I G U R A T I O N  V A R I A B L E   D E F I N I T I O N S                                           
***********************************************************************************************************************/
  /*
* @brief This macro is used to configure the service information table
  @Unit:  N/A
  @Resolution: N/A
  @Range: N/A
  @Applicability: YES if DiagSessionControl service enabled
  @Note:  Do not modify this macro value or name
  @param: 1. Service ID - Identifier value of a service
          2. Supported Sessions - UDS_DEFAULT_SESS/ UDS_PROG_SESS/ UDS_EXTND_SESS/ UDS_SAFETY_SYS_DIAG_SESS
          3. Response Support - DIAG_RESP_REQ/ DIAG_RESP_NOT_REQ
          4. Request Type � Supported for Physical or Functional or Both (UDS_PHYSICAL_REQ,UDS_FUNCTIONAL_REQ)
          5. Service Function - a.  Address of the Main Function Service
                                b.  Address of the Post Handling Function
-------------------------------------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------------------------------------
    Example:

   const UDS_ServiceInfo_st  g_UDS_ServiceInfoTable_st[MAX_NO_OF_SRV] ={
    {   UDS_DIAG_SESSION_CONTROL_SID,
        UDS_DEFAULT_SESS | UDS_PROG_SESS | UDS_EXTND_SESS,
        DIAG_RESP_REQ,
        (UDS_PHYSICAL_REQ|UDS_FUNCTIONAL_REQ),
        &UdsApp_Req_DiagSessionControl, 
    },
    {   UDS_ECU_RESET_SID,
        UDS_DEFAULT_SESS | UDS_PROG_SESS | UDS_EXTND_SESS,
        DIAG_RESP_REQ,
        (UDS_PHYSICAL_REQ|UDS_FUNCTIONAL_REQ),
        { &UdsApp_EcuReset,
          &UdsApp_EcuResetHandler                       
        }                             
    }
    };
------------------------------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------------------------------
*************************************************************************************************************************
*/
  const UDS_ServiceInfo_st g_UDS_ServiceInfoTable_st[MAX_NO_OF_SRV] = {
     
	 {	 UDS_DIAG_SESSION_CONTROL_SID,
		 UDS_DEFAULT_SESS | UDS_PROG_SESS | UDS_EXTND_SESS |UDS_VISTEON_SESSION ,
		 DIAG_RESP_REQ ,
		 ( UDS_FUNCTIONAL_REQ | UDS_PHYSICAL_REQ ),
		 {	&UdsApp_DiagnosticSessionControl,
			&AppToBootJmp
		 }
	 },
	 {	 UDS_ECU_RESET_SID,
		 UDS_DEFAULT_SESS | UDS_PROG_SESS | UDS_EXTND_SESS ,
		 DIAG_RESP_REQ ,
		 ( UDS_FUNCTIONAL_REQ | UDS_PHYSICAL_REQ ),
		 {	&UdsApp_EcuReset,
			&UdsApp_EcuResetHandler
		 }
	 },

	 {	 UDS_READ_DATABYID_SID,
		 UDS_DEFAULT_SESS | UDS_PROG_SESS | UDS_EXTND_SESS ,
		 DIAG_RESP_NOT_REQ ,
		 ( UDS_PHYSICAL_REQ ),
		 {	&UdsApp_ReadDataByIdentifier,
			((void *) 0U)
		 }
	 },
	 {	 UDS_READ_MEM_BY_ID_SID,
		 UDS_EXTND_SESS ,
		 DIAG_RESP_NOT_REQ ,
		 ( UDS_PHYSICAL_REQ ),
		 {	&UdsApp_ReadMemoryByAddress,
			((void *) 0U)
		 }
	 },
	 {	 UDS_SECURITY_ACCESS_SID,
		 UDS_PROG_SESS | UDS_EXTND_SESS | UDS_VISTEON_SESSION ,
		 DIAG_RESP_REQ ,
		 ( UDS_PHYSICAL_REQ ),
		 {	&UdsApp_SecurityAccess,
			((void *) 0U)
		 }
	 },
	 {	 UDS_COMMUNICATION_CONTROL_SID  ,
		 UDS_PROG_SESS | UDS_EXTND_SESS ,
		 DIAG_RESP_REQ ,
		 ( UDS_FUNCTIONAL_REQ | UDS_PHYSICAL_REQ ),
		 {	&UdsApp_CommunicationControl,
			((void *) 0U)
		 }
	 },
	 {	 UDS_WRITE_DID_SID,
		 UDS_PROG_SESS | UDS_EXTND_SESS ,
		 DIAG_RESP_NOT_REQ ,
		 ( UDS_PHYSICAL_REQ ),
		 {	&UdsApp_WriteDataByIdentifier,
			((void *) 0U)
		 }
	 },
//	 {	 UDS_IO_CTRL_BYID_SID,
//		 UDS_EXTND_SESS ,
//		 DIAG_RESP_REQ ,
//		 ( UDS_PHYSICAL_REQ ),
//		 {	&UdsApp_InputOutputControlByIdentifier,
//			((void *) 0U)
//		 }
//	 },
	 {	 UDS_ROUTINE_CTRL_SID,
		 UDS_PROG_SESS | UDS_EXTND_SESS ,
		 DIAG_RESP_NOT_REQ ,
		 ( UDS_PHYSICAL_REQ ),
		 {	&UdsApp_RoutineControl,
			((void *) 0U)
		 }
	 },
	 {	 UDS_DWNLD_REQUEST_SID,
		 UDS_PROG_SESS ,
		 DIAG_RESP_NOT_REQ ,
		 ( UDS_PHYSICAL_REQ ),
		 {	&UdsApp_RequestDownload,
			((void *) 0U)
		 }
	 },
	 {	 UDS_TRNSFR_DATA_SID,
		 UDS_PROG_SESS ,
		 DIAG_RESP_NOT_REQ ,
		 ( UDS_PHYSICAL_REQ ),
		 {	&UdsApp_TransferData,
			((void *) 0U)
		 }
	 },
	 {	 UDS_REQ_TRNSFR_EXIT_SID,
		 UDS_PROG_SESS ,
		 DIAG_RESP_NOT_REQ ,
		 ( UDS_PHYSICAL_REQ ),
		 {	&UdsApp_RequestTransferExit,
			((void *) 0U)
		 }
	 },
	 {	 UDS_WRITE_MEM_BY_ID_SID,
		 UDS_EXTND_SESS ,
		 DIAG_RESP_NOT_REQ ,
		 ( UDS_PHYSICAL_REQ ),
		 {	&UdsApp_WriteMemoryByAddress,
			((void *) 0U)
		 }
	 },
	 {	 UDS_TESTER_PRESENT_SID,
		 UDS_DEFAULT_SESS | UDS_PROG_SESS | UDS_EXTND_SESS ,
		 DIAG_RESP_REQ ,
		 ( UDS_FUNCTIONAL_REQ | UDS_PHYSICAL_REQ ),
		 {	&UdsApp_TesterPresent,
			((void *) 0U)
		 }
	 }

  };

/***********************************************************************************************************************
                                              E N D   O F   S O F T W A R E                                         
**********************************************************************************************************************/
#ifdef __cplusplus
}
#endif
#endif /* ! UDS_CFG_C */

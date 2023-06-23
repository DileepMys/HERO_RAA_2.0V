/*============================================================================
**
**                     CONFIDENTIAL VISTEON CORPORATION
**
** This is an unpublished work of authorship, which contains trade secrets,
** created in 2000. Visteon Corporation owns all rights to this work and
** intends to maintain it in confidence to preserve its trade secret status.
** Visteon Corporation reserves the right, under the copyright laws of the
** United States or those of any other country that may have  jurisdiction,
** to protect this work as an unpublished work, in the event of an
** inadvertent or deliberate unauthorized publication. Visteon Corporation
** also reserves its rights under all copyright laws to protect this work as
** a published work, when appropriate. Those having access to this work may
** not copy it, use it, modify it or disclose the information contained in
** it without the written authorization of Visteon Corporation.
**
**============================================================================
**
**  Name:               fuel03_nvm.c
**
**  Description:        NVM file for fuel03.c
**
**  Organization:       Driver Information Software Section,
**                      DI Core Engineering Department
**
**==========================================================================*/
/*#define FUEL03_NVM_C*/


/*============================================================================
**                 I N C L U D E   F I L E S
**==========================================================================*/
#include "fuel03.h"
#include "fuel03_nvm.h"

/*============================================================================
** I N T E R N A L   M A C R O   A N D   T Y P E   D E F I N I T I O N S
**==========================================================================*/

/*============================================================================
**                M E M O R Y   A L L O C A T I O N
**==========================================================================*/

/* --------------------------------------------------------------------------
** NVM allocation.  More details on the meaning of each constant defined
** here can be found in the sample FUEL02.CFG file.
** --------------------------------------------------------------------------
*/
#if ! defined(CC_GENERIC)
#ifdef FUEL03_DEBUG
   #if defined (__arm)
      #pragma arm section rodata="FUEL03_NVM_SEGMENT"
   #elif defined (__COSMIC_SYSTEMS_ICC)
      #pragma section const {FUEL03_NVMSEG}
   #elif defined (__IAR_SYSTEMS_ICC)
      #pragma memory = constseg(FUEL03_NVM_SEGMENT)
   #elif defined (__IAR_SYSTEMS_ICC__)
      #pragma constseg = FUEL03_NVM_SEGMENT
      __root
   #else
	#pragma ghs startdata
    #pragma ghs section data=".FUEL03_NVM_SEGMENT"
   #endif
#else
   #if defined (__arm)
      #pragma arm section rodata="FUEL03_CONST"
   #elif defined (__COSMIC_SYSTEMS_ICC)
      #pragma section const {FUEL03_CONSEG}
   #elif defined (__IAR_SYSTEMS_ICC)
      #pragma memory = constseg(FUEL03_CONST)
   #elif defined (__IAR_SYSTEMS_ICC__)
      #pragma constseg = FUEL03_CONST
      __root
   #else
   #pragma ghs startdata
   #pragma ghs section data=".FUEL03_CONST"

   #endif
#endif

#endif
/* --------------------------------------------------------------------------
** Define times for power stabilization delay, fuel samples to be taken,
** and open/short detect time, number of good samples required and
** Fast Fill debounce counter.
** --------------------------------------------------------------------------
*/
const UINT8  Fuel03KeyOnDelayCounterNVM    = FUEL03_KEY_ON_DELAY_TIME;
const UINT8  Fuel03InitDelayCounterNVM     = FUEL03_INIT_DELAY_COUNT_TIME;
const UINT16 Fuel03FaultCounterNVM         = FUEL03_OPEN_SHORT_FAULT_TIME;
const UINT16 Fuel03FaultRecoveryCounterNVM = FUEL03_OPEN_SHORT_RECOVERY_TIME;
const UINT8  Fuel03InitGoodSamplesReqNVM   = FUEL03_INIT_GOOD_SAMPLES_REQUIRED;
const UINT8  Fuel03FastFillTimeCounterNVM  = FUEL03_MIN_FAST_FILL_TIME;

/* --------------------------------------------------------------------------
** Define the fuel filter base delta and adjustment factor for use when
** in "normal" filter mode.
** --------------------------------------------------------------------------
*/
#if (FUEL03_MULT_FILT_RATES == 1)

 #ifndef FUEL03_SCEM_NUMBER_OF_FUEL_TANKS
 const UINT32 FUEL03_DELTA_NORMAL_BASE_A_NVM[]   = {FUEL03_DELTA_NORMAL_BASE_A1, \
                                                     FUEL03_DELTA_NORMAL_BASE_A2, \
                                                     FUEL03_DELTA_NORMAL_BASE_A3};
 #else
 const UINT32 FUEL03_DELTA_NORMAL_BASE_A_NVM[][FUEL03_SCEM_NUMBER_OF_FUEL_TANKS]   = {FUEL03_DELTA_NORMAL_BASE_A1, \
                                                                                      FUEL03_DELTA_NORMAL_BASE_A2, \
                                                                                      FUEL03_DELTA_NORMAL_BASE_A3};
 #endif

#else
 #ifndef FUEL03_SCEM_NUMBER_OF_FUEL_TANKS
 const UINT32 FUEL03_DELTA_NORMAL_BASE_A_NVM   = FUEL03_DELTA_NORMAL_BASE_A1;
 #else
 const UINT32 FUEL03_DELTA_NORMAL_BASE_A_NVM[FUEL03_SCEM_NUMBER_OF_FUEL_TANKS]   = FUEL03_DELTA_NORMAL_BASE_A1;
 #endif
#endif


#ifndef FUEL03_SCEM_NUMBER_OF_FUEL_TANKS

const UINT16 FUEL03_DELTA_NORMAL_ADJUST_A_NVM = FUEL03_DELTA_NORMAL_ADJUST_A;
const UINT32 FUEL03_DELTA_NORMAL_CLAMP_A_NVM  = FUEL03_DELTA_NORMAL_CLAMP_A;

#else

const UINT16 FUEL03_DELTA_NORMAL_ADJUST_A_NVM[] = FUEL03_DELTA_NORMAL_ADJUST_A;
const UINT32 FUEL03_DELTA_NORMAL_CLAMP_A_NVM[]  = FUEL03_DELTA_NORMAL_CLAMP_A;

#endif
/* --------------------------------------------------------------------------
** Define the fuel filter base delta and ajustment factor for use when
** in "fast fill" filter mode.
** --------------------------------------------------------------------------
*/
#ifndef FUEL03_SCEM_NUMBER_OF_FUEL_TANKS

const UINT16 FUEL03_DELTA_FAST_ADJUST_A_NVM = FUEL03_DELTA_FAST_ADJUST_A;
const UINT32 FUEL03_DELTA_FAST_BASE_A_NVM   = FUEL03_DELTA_FAST_BASE_A;
const UINT32 FUEL03_DELTA_FAST_CLAMP_A_NVM  = FUEL03_DELTA_FAST_CLAMP_A;

#else

const UINT16 FUEL03_DELTA_FAST_ADJUST_A_NVM[] = FUEL03_DELTA_FAST_ADJUST_A;
const UINT32 FUEL03_DELTA_FAST_BASE_A_NVM[]   = FUEL03_DELTA_FAST_BASE_A;
const UINT32 FUEL03_DELTA_FAST_CLAMP_A_NVM[]  = FUEL03_DELTA_FAST_CLAMP_A;

#endif

#ifndef FUEL03_SCEM_NUMBER_OF_FUEL_TANKS

const UINT8 FUEL03_KO_DELTA_A_NVM = FUEL03_KO_DELTA_A;

#else

const UINT8 FUEL03_KO_DELTA_A_NVM[] = FUEL03_KO_DELTA_A;

#endif

/* --------------------------------------------------------------------------
** Define the up and down fill checks used during fuel init.
** --------------------------------------------------------------------------
*/
#ifndef FUEL03_SCEM_NUMBER_OF_FUEL_TANKS

const UINT8 Fuel03PositiveInitFill_A_NVM = FUEL03_POSITIVE_INIT_FILL_DELTA_A;
const UINT8 Fuel03NegativeInitFill_A_NVM = FUEL03_NEGATIVE_INIT_FILL_DELTA_A;

#else

const UINT8 Fuel03PositiveInitFill_A_NVM[] = FUEL03_POSITIVE_INIT_FILL_DELTA_A;
const UINT8 Fuel03NegativeInitFill_A_NVM[] = FUEL03_NEGATIVE_INIT_FILL_DELTA_A;

#endif

/* --------------------------------------------------------------------------
** Define the up and down fill checks used as one of the entrance conditions
** to "fast fill" mode.
** --------------------------------------------------------------------------
*/
#ifndef FUEL03_SCEM_NUMBER_OF_FUEL_TANKS

const UINT8 Fuel03PositiveFastFill_A_NVM = FUEL03_POSITIVE_FAST_FILL_DELTA_A;
const UINT8 Fuel03NegativeFastFill_A_NVM = FUEL03_NEGATIVE_FAST_FILL_DELTA_A;

#else

const UINT8 Fuel03PositiveFastFill_A_NVM[] = FUEL03_POSITIVE_FAST_FILL_DELTA_A;
const UINT8 Fuel03NegativeFastFill_A_NVM[] = FUEL03_NEGATIVE_FAST_FILL_DELTA_A;

#endif

/* --------------------------------------------------------------------------
** Define the 'secondary' up and down fill checks
** --------------------------------------------------------------------------
*/
#ifndef FUEL03_SCEM_NUMBER_OF_FUEL_TANKS

const UINT8 Fuel03SecPosInitFillDeltaNVM_A = FUEL03_SEC_POS_INIT_FILL_DELTA_A;
const UINT8 Fuel03SecNegInitFillDeltaNVM_A = FUEL03_SEC_NEG_INIT_FILL_DELTA_A;

#else

const UINT8 Fuel03SecPosInitFillDeltaNVM_A[] = FUEL03_SEC_POS_INIT_FILL_DELTA_A;
const UINT8 Fuel03SecNegInitFillDeltaNVM_A[] = FUEL03_SEC_NEG_INIT_FILL_DELTA_A;

#endif


/* --------------------------------------------------------------------------
** Define the up and down check limits used for percent full hysteresis.
** --------------------------------------------------------------------------
*/
#ifndef FUEL03_SCEM_NUMBER_OF_FUEL_TANKS

const UINT16 Fuel03PercentFullPosHystNVM = FUEL03_PERCENT_FULL_POSITIVE_HYST;
const UINT16 Fuel03PercentFullNegHystNVM = FUEL03_PERCENT_FULL_NEGATIVE_HYST;

#else

const UINT16 Fuel03PercentFullPosHystNVM[] = FUEL03_PERCENT_FULL_POSITIVE_HYST;
const UINT16 Fuel03PercentFullNegHystNVM[] = FUEL03_PERCENT_FULL_NEGATIVE_HYST;

#endif

/* --------------------------------------------------------------------------
** Define the threshold at which to check for rental car topoff.
** --------------------------------------------------------------------------
*/
#ifndef FUEL03_SCEM_NUMBER_OF_FUEL_TANKS

const UINT8 Fuel03SenderA_RCFillThresholdNVM = FUEL03_SENDERA_RC_FILL_THRESHOLD;

#else

const UINT8 Fuel03SenderA_RCFillThresholdNVM[] = FUEL03_SENDERA_RC_FILL_THRESHOLD;

#endif

/* --------------------------------------------------------------------------
** Define the fill check to use for rental car topoff.
** --------------------------------------------------------------------------
*/
#ifdef FUEL03_RC_FILL_ENABLED
#ifndef FUEL03_SCEM_NUMBER_OF_FUEL_TANKS

const UINT8 Fuel03SenderA_RCFillDeltaNVM = FUEL03_SENDERA_RC_FILL_DELTA;

#else

const UINT8 Fuel03SenderA_RCFillDeltaNVM[] = FUEL03_SENDERA_RC_FILL_DELTA;

#endif
#endif
#ifdef FUEL03_FFRC_ENABLE
 #ifndef FUEL03_SCEM_NUMBER_OF_FUEL_TANKS
const UINT8 Fuel03UpperRateCheckLimit_A_NVM = FUEL03_UPPER_RATE_CHECK_LIMIT_A;
const UINT8 Fuel03LowerRateCheckLimit_A_NVM = FUEL03_LOWER_RATE_CHECK_LIMIT_A;
 #else
const UINT8 Fuel03UpperRateCheckLimit_A_NVM[] = FUEL03_UPPER_RATE_CHECK_LIMIT_A;
const UINT8 Fuel03LowerRateCheckLimit_A_NVM[] = FUEL03_LOWER_RATE_CHECK_LIMIT_A;
 #endif
#endif


#ifndef FUEL03_SCEM_NUMBER_OF_FUEL_TANKS

const UINT8 Fuel03ZssDelta_A_NVM = FUEL03_ZS_DELTA_A;

#else

const UINT8 Fuel03ZssDelta_A_NVM[] = FUEL03_ZS_DELTA_A;

#endif

#ifndef FUEL03_SCEM_NUMBER_OF_FUEL_TANKS

const UINT16 Fuel03A2DShortLimNVM = FUEL03_SHORTED_SENDER_LIMIT;
const UINT16 Fuel03A2DOpenLimNVM = FUEL03_OPEN_SENDER_LIMIT;

#else
const UINT16 Fuel03A2DShortLimNVM[] = FUEL03_SHORTED_SENDER_LIMIT;
const UINT16 Fuel03A2DOpenLimNVM[] = FUEL03_OPEN_SENDER_LIMIT;

#endif

/* --------------------------------------------------------------------------
** Counter value used to determine when to take the zero speed sample
** used for gage init and fast fill.
** --------------------------------------------------------------------------
*/
const UINT16 Fuel03ZeroSpeedCounterNVM = FUEL03_ZERO_SPEED_COUNTER;

/* --------------------------------------------------------------------------
** Flags to enable/disable tank B, dual sender, zss ref only, hill hold,
** and fast fill.
** --------------------------------------------------------------------------
*/
#ifdef FUEL03_ZSS_REF_ONLY
  #define FUEL03_TEMPZ FUEL03_ZSS_REF_ONLY_BIT
#else
  #define FUEL03_TEMPZ 0
#endif

#ifdef FUEL03_HILL_HOLD_ENABLE
  #define FUEL03_TEMP1 FUEL03_HILL_HOLD_ENABLE_BIT
#else
  #define FUEL03_TEMP1 0
#endif

#ifdef FUEL03_FAST_FILL_ENABLE
  #define FUEL03_TEMP2 FUEL03_FAST_FILL_ENABLE_BIT
#else
  #define FUEL03_TEMP2  0
#endif

const UINT8 Fuel03OptionsNVM = (FUEL03_TEMP1 | FUEL03_TEMP2 | FUEL03_TEMPZ );


#pragma ghs section data=default
#pragma ghs enddata

#if !defined(CC_GENERIC)
#ifdef FUEL03_AD_TO_PF_TBL_IN_NVM
/* If AD_TO_PF_TBL is required to be put in NVM, then allocate NVM segment here */

  #if defined (__arm)
    #pragma arm section rodata="FUEL03_NVM_SEGMENT"
  #elif defined (__COSMIC_SYSTEMS_ICC)
    #pragma section const {FUEL03_NVMSEG}
  #elif defined (__IAR_SYSTEMS_ICC)
    #pragma memory = constseg(FUEL03_NVM_SEGMENT)
  #elif defined (__IAR_SYSTEMS_ICC__)
    #pragma constseg = FUEL03_NVM_SEGMENT
    __root
  #else
	#pragma ghs startdata
	#pragma ghs section data=".FUEL03_NVM_SEGMENT"

  #endif

#else
/* If AD_TO_PF_TBL is not required to be put in NVM, then do not anything here
** it means it compiler continue to put AD_TO_PF_TBL in FUEL03_CONST segment */

#endif

#endif

#if !defined(CC_GENERIC)

#ifdef FUEL03_AD_TO_PF_TBL_IN_NVM
#pragma ghs section data=default
#pragma ghs enddata
#endif
  #endif

#if !defined(CC_GENERIC)
#ifdef FUEL03_DEBUG
   #if defined (__arm)
      #pragma arm section rodata="FUEL03_NVM_SEGMENT"
   #elif defined (__COSMIC_SYSTEMS_ICC)
      #pragma section const {FUEL03_NVMSEG}
   #elif defined (__IAR_SYSTEMS_ICC)
      #pragma memory = constseg(FUEL03_NVM_SEGMENT)
   #elif defined (__IAR_SYSTEMS_ICC__)
      #pragma constseg = FUEL03_NVM_SEGMENT
      __root
   #else
   #pragma ghs startdata
   #pragma ghs section data=".FUEL03_NVM_SEGMENT"

   #endif
#else
   #if defined (__arm)
      #pragma arm section rodata="FUEL03_CONST"
   #elif defined (__COSMIC_SYSTEMS_ICC)
      #pragma section const {FUEL03_CONSEG}
   #elif defined (__IAR_SYSTEMS_ICC)
      #pragma memory = constseg(FUEL03_CONST)
   #elif defined (__IAR_SYSTEMS_ICC__)
      #pragma constseg = FUEL03_CONST
      __root
   #else
      #pragma ghs startdata
      #pragma ghs section data=".FUEL03_CONST"

   #endif
#endif


#endif

#ifdef FUEL03_CANFLPS
/* RAD to CANFLPS */
const UINT16 Fuel03_CANFLPS_TableNVM[FUEL03_CANFLPS_SIZE][2] =
    {
      FUEL03_CANFLPS
    };
#endif
/*

** Define the maximum allowed key-off sampling time.
*/
const UINT16 Fuel03KeyOffSampleTimeNVM = FUEL03_KEY_OFF_SAMPLE_TIME;

#ifndef FUEL03_SCEM_NUMBER_OF_FUEL_TANKS
const UINT16 Fuel03Sender_A_TableNVM[FUEL03_SENDER_A_AD_TO_PF_TBL_SIZE][2] =
{
        {  0,     821     },  /* min  max */
        {  0,     0     },  
	      {  256,  14366u      },		/* 	254*256*0%		*/\
	      {  261,  15401u      },		/* 	254*256*0%		*/\
	      {  308, 19193u      },		/* 	254*256*0%		*/\
	      {  320, 19942u      },		/* 	254*256*0%		*/\
	      {  383, 25278u      },		/* 	254*256*0%		*/\
	      {  394, 25934u      },		/* 	254*256*0%		*/\
	      {  458, 31832u      },		/* 	254*256*0%		*/\
	      {  472, 32768u      },	/* 	254*256*31%		*/\
	      {  527, 40539u      }, 	/* 	254*256*42%		*/\
	      {  542, 42037u      }, 	/* 	254*256*53%		*/\
	      {  606, 47794u      }, 	/* 	254*256*64%		*/\
	      {  624, 48918u      },  	/* 	254*256*75%		*/ \
	      {  678, 52429u      }, 	/* 	254*256*86%  	*/ \
        {  700, 53599u      },  	/* 	254*256*100%	*/ \
        {  821, 59872u      }  	/* 	254*256*100%	*/ \
};
#else
const UINT8 fuel03_tank_array[FUEL03_SCEM_NUMBER_OF_FUEL_TANKS][2] = {FUEL03_INDEX_TABLE};
#endif


#pragma ghs section data=default
#pragma ghs enddata

#if FUEL03_LOG_FAULT_RECORD_SIZE > 0
#if !defined(CC_GENERIC)
  #if defined (__arm)
    #pragma arm section rodata="FUEL03_NVM_SEGMENT"
  #elif defined (__COSMIC_SYSTEMS_ICC)
    #pragma section const {FUEL03_NVMSEG}
  #elif defined (__IAR_SYSTEMS_ICC)
    #pragma memory = constseg(FUEL03_NVM_SEGMENT)
  #elif defined (__IAR_SYSTEMS_ICC__)
    #pragma constseg = FUEL03_NVM_SEGMENT
    __root
  #else
 #pragma ghs startdata
 #pragma ghs section data=".FUEL03_NVM_SEGMENT"

  #endif


#endif

/* ----------------------------------------------------------------------------------
** The following configuration items allow the application to decide which fuel
** values to save.
** Set to 1 to enable storage, 0 to disable storage.
** ----------------------------------------------------------------------------------
*/


  /* ------------------------------------------------------------------------
  ** Create a storage location that the fault log will be written to. This is
  ** initialized to an invalid number (0xff).
  ** ------------------------------------------------------------------------
  */
const UINT8 fuel03_next_fault_log_to_write_NVM = 0xff;

const FUEL03_FAULT_SNAPSHOT_STRUCT fuel03_fault_snapshot_A_NVM[FUEL03_LOG_FAULT_RECORD_SIZE];


#if !defined(CC_GENERIC)
#pragma ghs section data=default
#pragma ghs enddata
#endif



#endif

#if !defined(CC_GENERIC)
#if defined (__arm)
  #pragma arm section
#elif defined (__COSMIC_SYSTEMS_ICC)
  #pragma section const {}
#elif defined (__IAR_SYSTEMS_ICC)
  #pragma memory = default
#elif defined (__IAR_SYSTEMS_ICC__)
  #pragma constseg = default
#else


#endif

#endif


/*============================================================================
**
**  $Revision:   1.16  $
**
**============================================================================
**  P V C S    R E V I S I O N    N O T E S
**----------------------------------------------------------------------------
**  For each change to this file, be sure to record:
**  1.  who made the change and when the change was made
**  2.  why the change was made and the intended result
**
**  Date         By      Reason for Change
**  mmm/dd/yy    XXX     -----------------
**
**----------------------------------------------------------------------------
**	03/05/14     RAGARWA1
** Added CC_GENERIC definition to support the VC independent frame work.RTC 126528

** 20/04/12         BVIJAYKU
**  Updated as per CQ BSDI00115615.
**
** 21/10/11         BVIJAYKU
**  Added Pragma for IAR Compiler to support Raman Platform as per CR BSDI00114309.
**
** 05/12/10         JARUN
**  Added support for slosh filter time constants based upon vehicle speed.
**  CQ:BSDI00086712
**
** 08/11/09       KNAGASUB
** As per CQ BSDI00073307-Need memory optimized Fuel package for Newton1.5
**  FUEL03_RC_FILL_ENABLED macro is added to enable/disable the RC_FILL_delta_NVM's

** 09/10/08       KNAGASUB
** changes done in fault record macro's as per review comments.

** 01/10/08       KNAGASUB
** The changes are done as per the CQ BSDI00061422.
** code modified as per review comments
**To deactive the fault record size's set the macro(FUEL03_RAM_LOG_FAULT_RECORD_SIZE,FUEL03_LOG_FAULT_RECORD_SIZE) to zero.

** 25/09/08       KNAGASUB
** The changes are done as per the CQ BSDI00061422.
** The macro is removed FUEL03_LOG_INIT_ERRORS_TO_NVM.
** NVM fault record array is turned  off separately by these macro's
**  FUEL03_RAM_LOG_FAULT_RECORD_SIZE,FUEL03_LOG_FAULT_RECORD_SIZE.

** 24/09/08       KNAGASUB
** The macro FUEL03_NUM_FUEL_TABLES which is used to remove the unused table NVM bytes allocation.

** 09/08/08       KNAGASUB
** Fuel03A2DOpenLimNVM and Fuel03A2DShortLimNVM
** comapatible to more than one tank also.

** 06/08/08      KNAGASUB
** "Const" used directly instead of defining in the FUELO2_CONST macro.

** 6/05/08       CNAGARA1
** Removed a space at the end of the following line. This was giving an error
** while comparing in clearcase.
** '#pragma section const {FUEL03_NVMSEG}'
** This version is equal to FUEL03_V02.03 with above change.
**
** 4/11/08                  CNAGARA1            BSDI00054834
** Moved AD to PF TBL to a separate segment based on the conditinal compilation.
** If FUEL02_AD_TO_PF_TBL_IN_NVM macro is not defined then
** FUEL02_SENDER_A_AD_TO_PF_TBL is put in const segment otherwise this will be
** in NVM segment.
**
**
** 3/30/07       JARUN   BSDI00044140
**
** 02/28/06     JARUN   BSDI00038410
**   Added support for comsic compiler
**   The constant segment name NVM_VARIABLE
**   segment name was changed to FUEL03_CONST.
**   Commented out fuel03_tank_array[].
**
** 5/24/06       RRUSS1  BSDI00031391
**
** Updated to work with auto generated config files.
**
** 6/6/05        RRUSS1  BSDI00020719
**
** Initial creation.
**==========================================================================*/
/*-----------------------------------------------------------------------------
Date               : 24-Sept-2020
By                 : mdevadas
Traceability       : RTC #476591
Change Description : Fuelstep logic update and  "Fuel03Sender_A_TableNVM" moved to NVM for fuel DID write.
------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
Date               : 24-Sept-2020
By                 : mdevadas
Traceability       : RTC #595652
Change Description : Removed the commented code.
------------------------------------------------------------------------------*/
/* end of file ============================================================ */

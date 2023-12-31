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
**  Name:               fuel03_nvm.h
**
**  Description:        Header file for fuel03_nvm.c
**
**  Organization:       Driver Information Software Section,
**                      DI Core Engineering Department
**
**==========================================================================*/
#ifndef FUEL03_NVM_H
#define FUEL03_NVM_H


/*============================================================================
**                 I N C L U D E   F I L E S
**==========================================================================*/
//#include "fuel03.cfg"
#include "Fuel_Guage_Cfg.h"
/*============================================================================
** I N T E R N A L   M A C R O   A N D   T Y P E   D E F I N I T I O N S
**==========================================================================*/
/* --------------------------------------------------------- */
/* BSDI00036642 : Added check for '==1' and undefine if true */
/* This allows the previous functionality to be maintained.  */
/* Note that this is performed before the .h file is         */
/* included so it can take advantage of it also.             */
/* --------------------------------------------------------- */
#ifndef FUEL03_SCEM_NUMBER_OF_FUEL_TANKS
    #error FUEL03_SCEM_NUMBER_OF_FUEL_TANKS must be defined !
#else
    #if (FUEL03_SCEM_NUMBER_OF_FUEL_TANKS == 1)
        #undef FUEL03_SCEM_NUMBER_OF_FUEL_TANKS
    #endif
#endif

/* Backward compatibility - previously, always had 5 fuel tables */
/* independent of FUEL03_SCEM_NUMBER_OF_TANKS                    */
/* Now possible to override to only define the tables required   */
#ifndef FUEL03_NUM_FUEL_TABLES
 #define FUEL03_NUM_FUEL_TABLES     1
#else
 #if FUEL03_NUM_FUEL_TABLES<1
  #error FUEL03_NUM_FUEL_TABLES must be greater than zero !
 #endif
#endif


/*Number of Delta normal base available */
#if (FUEL03_MULT_FILT_RATES == 1)
#define FUEL03_MAX_NUM_DELTA_NORMAL_BASE (3)
#endif


#ifndef FUEL03_LOG_FAULT_RECORD_SIZE
  #define FUEL03_LOG_FAULT_RECORD_SIZE 0
#endif

#ifndef FUEL03_RAM_LOG_FAULT_RECORD_SIZE
   #define FUEL03_RAM_LOG_FAULT_RECORD_SIZE 0
#endif


#if FUEL03_LOG_FAULT_RECORD_SIZE != 0
  #if (FUEL03_RAM_LOG_FAULT_RECORD_SIZE == 0)
    #error FUEL03_RAM_LOG_FAULT_RECORD_SIZE must be defined when FUEL03_LOG_FAULT_RECORD_SIZE macro enabled!
  #elif (FUEL03_RAM_LOG_FAULT_RECORD_SIZE < FUEL03_LOG_FAULT_RECORD_SIZE)
     #error FUEL03_RAM_LOG_FAULT_RECORD_SIZE greater than or equal toFUEL03_LOG_FAULT_RECORD_SIZE!
  #endif
#endif


#ifndef FUEL03_ADD_CONVERGENCE_DATA_TO_FAULT_RECORD
/* ----------------------------------------------------------------------------------
** The following configuration items allow the application to decide which fuel
** values to save.
** Set to 1 to enable storage, 0 to disable storage.
** ----------------------------------------------------------------------------------
*/
#if FUEL03_RAM_LOG_FAULT_RECORD_SIZE > 0
#define FUEL03_LOG_fdelta             (0 )
#define FUEL03_LOG_fdelta_base        (0 )
#define FUEL03_LOG_fdelta_adjust_base (0 )
#define FUEL03_LOG_FilterFlags        (1)
#define FUEL03_LOG_flps               (1)
#define FUEL03_LOG_init_ref           (1)
#define FUEL03_LOG_init_pid           (1)
#define FUEL03_LOG_KeyOffRef          (1)
#define FUEL03_LOG_keyon_radsum       (1 )
#define FUEL03_LOG_keyon_good_samples (1 )
#define FUEL03_LOG_keyon_avgflps      (1 )
#define FUEL03_LOG_MoreFilterFlags    (1 )
#define FUEL03_LOG_FuelFaultCounter   (0 )
#define FUEL03_LOG_FuelFaultRecoveryCounter (0 )
#define FUEL03_LOG_rad                (1)
#define FUEL03_LOG_avg_rad            (0 )
#define FUEL03_LOG_old_rad            (0 )
#define FUEL03_LOG_sample_array       (0)
#define FUEL03_LOG_rc_fill_threshold  (0)
#define FUEL03_LOG_rc_fill_delta      (0)
#define FUEL03_LOG_rflps              (0 )
#define FUEL03_LOG_rfuel              (0 )
#define FUEL03_LOG_slosh_filter       (1 )
#define FUEL03_LOG_slosh_filter_hys   (1 )
#define FUEL03_LOG_zss_ref            (1 )
#define FUEL03_LOG_rate_check_passed  (0 )
#define FUEL03_LOG_rate_check_timer   (0 )
#define FUEL03_LOG_ffrc_delta_ref     (0 )
#define FUEL03_LOG_sample_counter     (0 )
#define FUEL03_LOG_rate_check_sample  (0 )
#define FUEL03_LOG_ConvCycleCounter   (0 )
#define FUEL03_LOG_ConvSample         (0 )
#define FUEL03_LOG_SmplCounter        (0 )
#define FUEL03_LOG_min_vx             (0)
#define FUEL03_LOG_max_vx             (0)
#define FUEL03_LOG_sum_vx             (0)
#define FUEL03_LOG_koc_converged      (1)
#define FUEL03_LOG_koc_fault_flag     (0)
#define FUEL03_LOG_zs_converged       (1 )
#define FUEL03_LOG_moving_sample_counter (0 )
#define FUEL03_LOG_use_avg_flag       (0 )
#define FUEL03_LOG_use_mov_avg        (0 )
#define FUEL03_LOG_err_counter        (0 )
typedef struct {

#if FUEL03_LOG_fdelta==1
 UINT32 fdelta;
#endif
#if FUEL03_LOG_fdelta_base==1
 UINT32 fdelta_base;
#endif
#if FUEL03_LOG_fdelta_adjust_base==1
 UINT16 fdelta_adjust_base;
#endif
#if FUEL03_LOG_FilterFlags==1
 UINT8  FilterFlags;
#endif
#if FUEL03_LOG_flps==1
 UINT8  flps;
#endif
#if FUEL03_LOG_init_ref==1
 UINT8  init_ref;
#endif
#if FUEL03_LOG_init_pid==1
 UINT16 init_pid;
#endif
#if FUEL03_LOG_KeyOffRef==1
 UINT8  KeyOffRef;
#endif
#if FUEL03_LOG_keyon_radsum==1
 UINT32 keyon_radsum;
#endif
#if FUEL03_LOG_keyon_good_samples==1
 UINT8  keyon_good_samples;
#endif
#if FUEL03_LOG_keyon_avgflps==1
 UINT8  keyon_avgflps;
#endif
#if FUEL03_LOG_MoreFilterFlags==1
 UINT8  MoreFilterFlags;
#endif
#if FUEL03_LOG_FuelFaultCounter==1
 UINT16 FuelFaultCounter;
#endif
#if FUEL03_LOG_FuelFaultRecoveryCounter==1
 UINT16 FuelFaultRecoveryCounter;
#endif
#if FUEL03_LOG_rad==1
 UINT16 rad;
#endif
#if FUEL03_LOG_avg_rad==1
 UINT16 avg_rad;
#endif
#if FUEL03_LOG_old_rad==1
 UINT16 old_rad;
#endif
#if FUEL03_LOG_sample_array==1
 UINT16 sample_array[FUEL03_SMPLS_2_AVG];
#endif
#if FUEL03_LOG_rc_fill_threshold==1
 UINT8  rc_fill_threshold;
#endif
#if FUEL03_LOG_rc_fill_delta==1
 UINT8  rc_fill_delta;
#endif
#if FUEL03_LOG_rflps==1
 UINT8  rflps;
#endif
#if FUEL03_LOG_rfuel==1
 UINT8  rfuel;
#endif
#if FUEL03_LOG_slosh_filter==1
 UINT32 slosh_filter;
#endif
#if FUEL03_LOG_slosh_filter_hys==1
 UINT32 slosh_filter_hys;
#endif
#if FUEL03_LOG_zss_ref==1
 UINT8  zss_ref;
#endif
#ifdef FUEL03_FFRC_ENABLE
#if FUEL03_LOG_rate_check_passed==1
 BOOLEAN rate_check_passed;
#endif
#if FUEL03_LOG_rate_check_timer==1
 UINT16  rate_check_timer;
#endif
#if FUEL03_LOG_ffrc_delta_ref==1
 UINT8   ffrc_delta_ref;
#endif
#if FUEL03_LOG_sample_counter==1
 UINT8   sample_counter;
#endif
#if FUEL03_LOG_rate_check_sample==1
 UINT8   rate_check_sample[FUEL03_MAX_RATE_CHECK_SAMPLES+1];
#endif
#endif
#if (FUEL03_REF_AVG_TYPE==4)
#if FUEL03_LOG_ConvCycleCounter==1
 UINT8   ConvCycleCounter;
#endif
#if FUEL03_LOG_ConvSample==1
 UINT8   ConvSample;
#endif
#if FUEL03_LOG_SmplCounter==1
 UINT8   SmplCounter;
#endif
#if FUEL03_LOG_min_vx==1
 UINT8   min_vx;
#endif
#if FUEL03_LOG_max_vx==1
 UINT8   max_vx;
#endif
#if FUEL03_LOG_sum_vx==1
 UINT16  sum_vx;
#endif
#if FUEL03_LOG_koc_converged==1
 BOOLEAN koc_converged;
#endif
#if FUEL03_LOG_koc_fault_flag==1
 BOOLEAN koc_fault_flag;
#endif
#if FUEL03_LOG_zs_converged==1
 BOOLEAN zs_converged;
#endif
#endif
#if FUEL03_LOG_moving_sample_counter==1
 UINT8   moving_sample_counter;
#endif
#if FUEL03_LOG_use_avg_flag==1
 UINT8   use_avg_flag;
#endif
#if FUEL03_LOG_use_mov_avg==1
 UINT8   use_mov_avg;
#endif
#if FUEL03_LOG_err_counter==1
 UINT16  err_counter;
#endif

} FUEL03_FAULT_SNAPSHOT_STRUCT;
#endif
#else
 /* ----------------------------------------------------------------------------------
** The following configuration items allow the application to decide which fuel
** values to save.
** Set to 1 to enable storage, 0 to disable storage.
** ----------------------------------------------------------------------------------
*/
#if FUEL03_RAM_LOG_FAULT_RECORD_SIZE > 0
#define FUEL03_LOG_fdelta             (0 )
#define FUEL03_LOG_fdelta_base        (0 )
#define FUEL03_LOG_keyon_radsum       (1 )
#define FUEL03_LOG_slosh_filter       (1 )
#define FUEL03_LOG_slosh_filter_hys   (1 )
#define FUEL03_LOG_fdelta_adjust_base (0 )
#define FUEL03_LOG_init_pid           (1)
#define FUEL03_LOG_FuelFaultCounter   (0 )
#define FUEL03_LOG_FuelFaultRecoveryCounter (0 )
#define FUEL03_LOG_rad                (1)
#define FUEL03_LOG_avg_rad            (0 )
#define FUEL03_LOG_old_rad            (0 )
#define FUEL03_LOG_sample_array       (0)
#define FUEL03_LOG_err_counter        (0 )
#define FUEL03_LOG_rate_check_timer   (0 )
#define FUEL03_LOG_sum_vx             (1)
#define FUEL03_LOG_ConvCycleCounter   (1 )
#define FUEL03_LOG_ConvSample         (1 )
#define FUEL03_LOG_SmplCounter        (1 )
#define FUEL03_LOG_min_vx             (1)
#define FUEL03_LOG_max_vx             (1)
#define FUEL03_LOG_koc_converged      (1)
#define FUEL03_LOG_koc_fault_flag     (0)
#define FUEL03_LOG_zs_converged       (1 )
#define FUEL03_LOG_rate_check_passed  (0 )
#define FUEL03_LOG_ffrc_delta_ref     (0 )
#define FUEL03_LOG_sample_counter     (0 )
#define FUEL03_LOG_rate_check_sample  (0 )
#define FUEL03_LOG_FilterFlags        (1)
#define FUEL03_LOG_flps               (1)
#define FUEL03_LOG_init_ref           (1)
#define FUEL03_LOG_KeyOffRef          (1)
#define FUEL03_LOG_keyon_good_samples (1 )
#define FUEL03_LOG_keyon_avgflps      (1 )
#define FUEL03_LOG_MoreFilterFlags    (1 )
#define FUEL03_LOG_rc_fill_threshold  (0)
#define FUEL03_LOG_rc_fill_delta      (0)
#define FUEL03_LOG_rflps              (0 )
#define FUEL03_LOG_rfuel              (0 )
#define FUEL03_LOG_zss_ref            (1 )
#define FUEL03_LOG_moving_sample_counter (0 )
#define FUEL03_LOG_use_avg_flag       (0 )
#define FUEL03_LOG_use_mov_avg        (0 )
#define FUEL03_LOG_invalid_condition  (1 )
#define FUEL03_LOG_ignition_cycle_counter  (1 )


typedef struct {

#if FUEL03_LOG_fdelta==1
 UINT32 fdelta;
#endif

#if FUEL03_LOG_fdelta_base==1
 UINT32 fdelta_base;
#endif

#if FUEL03_LOG_keyon_radsum==1
 UINT32 keyon_radsum;
#endif

#if FUEL03_LOG_slosh_filter==1
 UINT32 slosh_filter;
#endif

#if FUEL03_LOG_slosh_filter_hys==1
 UINT32 slosh_filter_hys;
#endif

#if FUEL03_LOG_fdelta_adjust_base==1
 UINT16 fdelta_adjust_base;
#endif

#if FUEL03_LOG_init_pid==1
 UINT16 init_pid;
#endif

#if FUEL03_LOG_FuelFaultCounter==1
 UINT16 FuelFaultCounter;
#endif

#if FUEL03_LOG_FuelFaultRecoveryCounter==1
 UINT16 FuelFaultRecoveryCounter;
#endif

#if FUEL03_LOG_rad==1
 UINT16 rad;
#endif

#if FUEL03_LOG_avg_rad==1
 UINT16 avg_rad;
#endif

#if FUEL03_LOG_old_rad==1
 UINT16 old_rad;
#endif

#if FUEL03_LOG_sample_array==1
 UINT16 sample_array[FUEL03_SMPLS_2_AVG];
#endif

#if FUEL03_LOG_err_counter==1
 UINT16  err_counter;
#endif

#ifdef FUEL03_FFRC_ENABLE
#if FUEL03_LOG_rate_check_timer==1
 UINT16  rate_check_timer;
#endif
#endif

#if (FUEL03_REF_AVG_TYPE==4)
#if FUEL03_LOG_sum_vx==1
 UINT16  sum_vx;
#endif
#if FUEL03_LOG_ConvCycleCounter==1
 UINT8   ConvCycleCounter;
#endif
#if FUEL03_LOG_ConvSample==1
 UINT8   ConvSample;
#endif
#if FUEL03_LOG_SmplCounter==1
 UINT8   SmplCounter;
#endif
#if FUEL03_LOG_min_vx==1
 UINT8   min_vx;
#endif
#if FUEL03_LOG_max_vx==1
 UINT8   max_vx;
#endif
#if FUEL03_LOG_koc_converged==1
 BOOLEAN koc_converged;
#endif
#if FUEL03_LOG_koc_fault_flag==1
 BOOLEAN koc_fault_flag;
#endif
#if FUEL03_LOG_zs_converged==1
 BOOLEAN zs_converged;
#endif
#endif

#ifdef FUEL03_FFRC_ENABLE
#if FUEL03_LOG_rate_check_passed==1
 BOOLEAN rate_check_passed;
#endif
#if FUEL03_LOG_ffrc_delta_ref==1
 UINT8   ffrc_delta_ref;
#endif
#if FUEL03_LOG_sample_counter==1
 UINT8   sample_counter;
#endif
#if FUEL03_LOG_rate_check_sample==1
 UINT8   rate_check_sample[FUEL03_MAX_RATE_CHECK_SAMPLES+1];
#endif
#endif

#if FUEL03_LOG_FilterFlags==1
 UINT8  FilterFlags;
#endif

#if FUEL03_LOG_flps==1
 UINT8  flps;
#endif

#if FUEL03_LOG_init_ref==1
 UINT8  init_ref;
#endif

#if FUEL03_LOG_KeyOffRef==1
 UINT8  KeyOffRef;
#endif

#if FUEL03_LOG_keyon_good_samples==1
 UINT8  keyon_good_samples;
#endif

#if FUEL03_LOG_keyon_avgflps==1
 UINT8  keyon_avgflps;
#endif

#if FUEL03_LOG_MoreFilterFlags==1
 UINT8  MoreFilterFlags;
#endif

#if FUEL03_LOG_rc_fill_threshold==1
 UINT8  rc_fill_threshold;
#endif

#if FUEL03_LOG_rc_fill_delta==1
 UINT8  rc_fill_delta;
#endif

#if FUEL03_LOG_rflps==1
 UINT8  rflps;
#endif

#if FUEL03_LOG_rfuel==1
 UINT8  rfuel;
#endif

#if FUEL03_LOG_zss_ref==1
 UINT8  zss_ref;
#endif

#if FUEL03_LOG_moving_sample_counter==1
 UINT8   moving_sample_counter;
#endif

#if FUEL03_LOG_use_avg_flag==1
 UINT8   use_avg_flag;
#endif

#if FUEL03_LOG_use_mov_avg==1
 UINT8   use_mov_avg;
#endif

#if FUEL03_LOG_invalid_condition==1
 UINT8   fuel03_invalid_condition;
#endif

#if FUEL03_LOG_ignition_cycle_counter==1
 UINT8   fuel03_ignition_cycle_counter;
#endif

/* As of now totally 23 elements have been enabled resulting 35 bytes   */
/* memory occupation. So in order to have multiples of 4 bytes one byte */
/* padding is done here. In future if any bytes are enabled here this   */
/* has to be taken care accordingly                                     */
 UINT8   padded_byte;

} FUEL03_FAULT_SNAPSHOT_STRUCT;
#endif
#endif



/*============================================================================
**                M E M O R Y   A L L O C A T I O N
**==========================================================================*/
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
/* --------------------------------------------------------------------------
** Define times for power stabilization delay, fuel samples to be taken,
** and open/short detect time, number of good samples required and
** FUEL03_MIN_FAST_FILL_TIME counter.
** --------------------------------------------------------------------------
*/
extern const UINT8  Fuel03KeyOnDelayCounterNVM;
extern const UINT8  Fuel03InitDelayCounterNVM;
extern const UINT16 Fuel03FaultCounterNVM;
extern const UINT16 Fuel03FaultRecoveryCounterNVM;
extern const UINT8  Fuel03InitGoodSamplesReqNVM;
extern const UINT8  Fuel03FastFillTimeCounterNVM;

/* --------------------------------------------------------------------------
** Define the fuel filter base delta and adjustment factor for use when
** in "normal" filter mode.
** --------------------------------------------------------------------------
*/
#if (FUEL03_MULT_FILT_RATES == 1)

  #ifndef FUEL03_SCEM_NUMBER_OF_FUEL_TANKS
  extern const UINT32 FUEL03_DELTA_NORMAL_BASE_A_NVM[FUEL03_MAX_NUM_DELTA_NORMAL_BASE];
  #else
  extern const UINT32 FUEL03_DELTA_NORMAL_BASE_A_NVM[FUEL03_MAX_NUM_DELTA_NORMAL_BASE][FUEL03_SCEM_NUMBER_OF_FUEL_TANKS];
  #endif

#else

  #ifndef FUEL03_SCEM_NUMBER_OF_FUEL_TANKS
  extern const UINT32 FUEL03_DELTA_NORMAL_BASE_A_NVM;
  #else
  extern const UINT32 FUEL03_DELTA_NORMAL_BASE_A_NVM[FUEL03_SCEM_NUMBER_OF_FUEL_TANKS];
  #endif

#endif



#ifndef FUEL03_SCEM_NUMBER_OF_FUEL_TANKS

extern const UINT16 FUEL03_DELTA_NORMAL_ADJUST_A_NVM;
extern const UINT32 FUEL03_DELTA_NORMAL_CLAMP_A_NVM;

#else

extern const UINT16 FUEL03_DELTA_NORMAL_ADJUST_A_NVM[FUEL03_SCEM_NUMBER_OF_FUEL_TANKS];
extern const UINT32 FUEL03_DELTA_NORMAL_CLAMP_A_NVM[FUEL03_SCEM_NUMBER_OF_FUEL_TANKS];

#endif
/* --------------------------------------------------------------------------
** Define the fuel filter base delta and ajustment factor for use when
** in "fast fill" filter mode.
** --------------------------------------------------------------------------
*/
#ifndef FUEL03_SCEM_NUMBER_OF_FUEL_TANKS

extern const UINT16 FUEL03_DELTA_FAST_ADJUST_A_NVM;
extern const UINT32 FUEL03_DELTA_FAST_BASE_A_NVM;
extern const UINT32 FUEL03_DELTA_FAST_CLAMP_A_NVM;

#else

extern const UINT16 FUEL03_DELTA_FAST_ADJUST_A_NVM[FUEL03_SCEM_NUMBER_OF_FUEL_TANKS];
extern const UINT32 FUEL03_DELTA_FAST_BASE_A_NVM[FUEL03_SCEM_NUMBER_OF_FUEL_TANKS];
extern const UINT32 FUEL03_DELTA_FAST_CLAMP_A_NVM[FUEL03_SCEM_NUMBER_OF_FUEL_TANKS];

#endif

#ifndef FUEL03_SCEM_NUMBER_OF_FUEL_TANKS

extern const UINT8 FUEL03_KO_DELTA_A_NVM;

#else

extern const UINT8 FUEL03_KO_DELTA_A_NVM[FUEL03_SCEM_NUMBER_OF_FUEL_TANKS];

#endif

#ifdef FUEL03_CANFLPS
extern const UINT16 Fuel03_CANFLPS_TableNVM[FUEL03_CANFLPS_SIZE][2];
#endif

/* --------------------------------------------------------------------------
** Define the up and down fill checks used during fuel init.
** --------------------------------------------------------------------------
*/
#ifndef FUEL03_SCEM_NUMBER_OF_FUEL_TANKS

extern const UINT8 Fuel03PositiveInitFill_A_NVM;
extern const UINT8 Fuel03NegativeInitFill_A_NVM;

#else

extern const UINT8 Fuel03PositiveInitFill_A_NVM[FUEL03_SCEM_NUMBER_OF_FUEL_TANKS];
extern const UINT8 Fuel03NegativeInitFill_A_NVM[FUEL03_SCEM_NUMBER_OF_FUEL_TANKS];

#endif

/* --------------------------------------------------------------------------
** Define the up and down fill checks used as one of the entrance conditions
** to "fast fill" mode.
** --------------------------------------------------------------------------
*/
#ifndef FUEL03_SCEM_NUMBER_OF_FUEL_TANKS

extern const UINT8 Fuel03PositiveFastFill_A_NVM;
extern const UINT8 Fuel03NegativeFastFill_A_NVM;

#else

extern const UINT8 Fuel03PositiveFastFill_A_NVM[FUEL03_SCEM_NUMBER_OF_FUEL_TANKS];
extern const UINT8 Fuel03NegativeFastFill_A_NVM[FUEL03_SCEM_NUMBER_OF_FUEL_TANKS];

#endif

/* --------------------------------------------------------------------------
** Define the 'secondary' up and down fill checks
** --------------------------------------------------------------------------
*/
#ifndef FUEL03_SCEM_NUMBER_OF_FUEL_TANKS

extern const UINT8 Fuel03SecPosInitFillDeltaNVM_A;
extern const UINT8 Fuel03SecNegInitFillDeltaNVM_A;

#else

extern const UINT8 Fuel03SecPosInitFillDeltaNVM_A[FUEL03_SCEM_NUMBER_OF_FUEL_TANKS];
extern const UINT8 Fuel03SecNegInitFillDeltaNVM_A[FUEL03_SCEM_NUMBER_OF_FUEL_TANKS];

#endif


/* --------------------------------------------------------------------------
** Define the up and down check limits used for percent full hysteresis.
** --------------------------------------------------------------------------
*/
#ifndef FUEL03_SCEM_NUMBER_OF_FUEL_TANKS

extern const UINT16 Fuel03PercentFullPosHystNVM;
extern const UINT16 Fuel03PercentFullNegHystNVM;

#else

extern const UINT16 Fuel03PercentFullPosHystNVM[FUEL03_SCEM_NUMBER_OF_FUEL_TANKS];
extern const UINT16 Fuel03PercentFullNegHystNVM[FUEL03_SCEM_NUMBER_OF_FUEL_TANKS];

#endif

/* --------------------------------------------------------------------------
** Define the threshold at which to check for rental car topoff.
** --------------------------------------------------------------------------
*/
#ifndef FUEL03_SCEM_NUMBER_OF_FUEL_TANKS

extern const UINT8 Fuel03SenderA_RCFillThresholdNVM;

#else

extern const UINT8 Fuel03SenderA_RCFillThresholdNVM[FUEL03_SCEM_NUMBER_OF_FUEL_TANKS];

#endif
#ifdef FUEL03_RC_FILL_ENABLED

/* --------------------------------------------------------------------------
** Define the fill check to use for rental car topoff.
** --------------------------------------------------------------------------
*/
#ifndef FUEL03_SCEM_NUMBER_OF_FUEL_TANKS

extern const UINT8 Fuel03SenderA_RCFillDeltaNVM;

#else

extern const UINT8 Fuel03SenderA_RCFillDeltaNVM[FUEL03_SCEM_NUMBER_OF_FUEL_TANKS];

#endif
#endif
#ifdef FUEL03_FFRC_ENABLE
 #ifndef FUEL03_SCEM_NUMBER_OF_FUEL_TANKS
  extern const UINT8 Fuel03UpperRateCheckLimit_A_NVM;
  extern const UINT8 Fuel03LowerRateCheckLimit_A_NVM;
 #else
  extern const UINT8 Fuel03UpperRateCheckLimit_A_NVM[FUEL03_SCEM_NUMBER_OF_FUEL_TANKS];
  extern const UINT8 Fuel03LowerRateCheckLimit_A_NVM[FUEL03_SCEM_NUMBER_OF_FUEL_TANKS];
 #endif
#endif


#ifndef FUEL03_SCEM_NUMBER_OF_FUEL_TANKS

extern const UINT8 Fuel03ZssDelta_A_NVM;

#else

extern const UINT8 Fuel03ZssDelta_A_NVM[FUEL03_SCEM_NUMBER_OF_FUEL_TANKS];

#endif

#ifndef FUEL03_SCEM_NUMBER_OF_FUEL_TANKS
  extern const UINT16 Fuel03A2DShortLimNVM;
  extern const UINT16 Fuel03A2DOpenLimNVM;
 #else
  extern const UINT16 Fuel03A2DShortLimNVM[FUEL03_SCEM_NUMBER_OF_FUEL_TANKS];
  extern const UINT16 Fuel03A2DOpenLimNVM[FUEL03_SCEM_NUMBER_OF_FUEL_TANKS];
 #endif

/* --------------------------------------------------------------------------
** Counter value used to determine when to take the zero speed sample
** used for gage init and fast fill.
** --------------------------------------------------------------------------
*/
extern const UINT16 Fuel03ZeroSpeedCounterNVM;

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

extern const UINT8 Fuel03OptionsNVM;

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


#if (FUEL03_NUM_FUEL_TABLES == 1)

    extern const UINT16 Fuel03Sender_A_TableNVM[FUEL03_SENDER_A_AD_TO_PF_TBL_SIZE][2];
#else
    extern const UINT16 Fuel03Sender_A_TableNVM[FUEL03_NUM_FUEL_TABLES][FUEL03_SENDER_A_AD_TO_PF_TBL_SIZE][2];
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


/*
** Define the maximum allowed key-off sampling time.
*/
extern const UINT16 Fuel03KeyOffSampleTimeNVM;

#ifndef FUEL03_SCEM_NUMBER_OF_FUEL_TANKS
  extern const UINT8 fuel03_tank_array[2];
#else
  extern const UINT8 fuel03_tank_array[FUEL03_SCEM_NUMBER_OF_FUEL_TANKS][2];
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


  /* ------------------------------------------------------------------------
  ** Create a storage location that the fault log will be written to. This is
  ** initialized to an invalid number (0xff).
  ** ------------------------------------------------------------------------
  */
  extern const UINT8 fuel03_next_fault_log_to_write_NVM;

  extern const FUEL03_FAULT_SNAPSHOT_STRUCT fuel03_fault_snapshot_A_NVM[FUEL03_LOG_FAULT_RECORD_SIZE];

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

** 11/04/13         BVIJAYKU
**  Removed compilation error check for FUEL03_INIT_GOOD_SAMPLES_REQUIRED is 0 and QAC warning deviation and 
** added fuel03_KSNvRamCheck() for run time check.

** 05/09/13         BVIJAYKU
**  Added compilation error check for FUEL03_INIT_GOOD_SAMPLES_REQUIRED is 0 and QAC warning deviation.

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
** FUEL03_LOG_avgflps_saddle  macro and related varaibles are  removed.
** Because Fuel03 does not support for saddle tank.
**  FUEL03_RC_FILL_ENABLED macro is added to enable/disable the RC_FILL_delta_NVM's


**
** 09/10/08       KNAGASUB
** changes done in fault record macro's as per review comments.

** 01/10/08       KNAGASUB
** The changes are done as per the CQ BSDI00061422.
** code modified as per review comments
**To deactive the fault record size's set the macro(FUEL03_RAM_LOG_FAULT_RECORD_SIZE,FUEL03_LOG_FAULT_RECORD_SIZE) to zero.

** 25/09/08       KNAGASUB
** The changes are done as per the CQ BSDI00061422.
** The macro is removed FUEL03_LOG_INIT_ERRORS_TO_NVM.
**  NVM fault record array is turned  off separately by these macro's
**  FUEL03_RAM_LOG_FAULT_RECORD_SIZE,FUEL03_LOG_FAULT_RECORD_SIZE.

** 24/09/08       KNAGASUB
** The macro FUEL03_NUM_FUEL_TABLES which is used to remove the unused table NVM bytes allocation.

** 09/08/08       KNAGASUB
** The Fuel03A2DOpenLimNVM and Fuel03A2DShortLimNVM
** comapatible to more than one tank also.

** 04/09/08       KNAGASUB
**  extern const is used instead of FUEL03_CONST_EX.

** 08/31/08       KNAGASUB   BSDI00053792

** THE MACRO FUEL03_ADD_CONVERGENCE_DATA_TO_FAULT_RECORD is added
** to seaparate the NVM and NO NVM changes.

** 05/23/08       CNAGARA1
** Ref: BSDI00053792 (#3, #4,#5)
** 1. Added fuel03_invalid_condition & fuel03_ignition_cycle_counter
**    elements to the FUEL03_FAULT_SNAPSHOT_STRUCT structure.
** 2. Added padded_byte to the same strucute to have the size of strcuture
**    as multiples of 4
**
** 04/18/08       SRATHINA   BSDI00053792
** Modified the structure of FUEL03_FAULT_SNAPSHOT_STRUCT as the structure
** members in the order of UINT32, UIN16, UINT8 as per the ARM_Compiler_Tips.doc
** Point#11 in order to avoid the memory space wastage.
**
** 03/12/08       CNAGARA1   BSDI00053792
** Enabled the following macros for storing the following info into snapshot
** structure
**   FUEL03_LOG_ConvCycleCounter,
**   FUEL03_LOG_ConvSample,
**   FUEL03_LOG_SmplCounter,
**   FUEL03_LOG_min_vx
**   FUEL03_LOG_max_vx
**   FUEL03_LOG_sum_vx
**
** 06/09/08       CNAGARA1
** Ref Peer Review Package ID10444. Defect #5
** a. Removed FUEL03_SCEM_NUMBER_OF_FUEL_TANKS macro check in fuel03.c and
**    fuel03_nvm.c and added here fuel03_nvm.h so that we can have at place
**    instead of being in two files
** b. Removed fuel03.cfg inclusion in fuel03.c and fuel03_nvm.c and added
**    here to avoid having included in two files.
**
** 3/30/07       JARUN   BSDI00044140
**
** 02/28/06     JARUN    BSDI00038410
**   The constant segment name NVM_VARIABLE
**   segment name was changed to FUEL03_CONST.
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
/* end of file ============================================================ */

#endif

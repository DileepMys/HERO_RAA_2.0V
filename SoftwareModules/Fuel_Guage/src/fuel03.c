/*============================================================================

                    CONFIDENTIAL VISTEON CORPORATION

 This is an unpublished work of authorship, which contains trade secrets,
 created in 2000. Visteon Corporation owns all rights to this work and
 intends to maintain it in confidence to preserve its trade secret status.
 Visteon Corporation reserves the right, under the copyright laws of the
 United States or those of any other country that may have  jurisdiction,
 to protect this work as an unpublished work, in the event of an
 inadvertent or deliberate unauthorized publication. Visteon Corporation
 also reserves its rights under all copyright laws to protect this work as
 a published work, when appropriate. Those having access to this work may
 not copy it, use it, modify it or disclose the information contained in
 it without the written authorization of Visteon Corporation.

============================================================================

  Name:               fuel03.c

  Description:        Configurable fuel filter algorithms.

  Organization:       Driver Information Software Section,
                      DI Core Engineering Department

==========================================================================*/
/*#define FUEL03_C */


/*============================================================================
                         O V E R V I E W
=============================================================================*/
/*
** The intent of this code is to provide a configurable fuel filter
** algorithm for use in a variety of instrument cluster applications.
**
** This package is a stripped down single sender version of the Fuel02 package.
** Therefore, the requirements for this code package are detailed in the
** Fuel Algorithm Bookshelf Design Specification (BDS) 4FA1-1A306-CA.
*/


/*============================================================================
                 I N C L U D E   F I L E S
==============================================================================*/
//#include "types.h"
#include "fuel03.h"
#include "fuel03_nvm.h"
#include "Interpolation.h"
//#include "nvmdef.h"
#if FUEL03_LOG_FAULT_RECORD_SIZE > 0
#include "epm_pkg.h"
#endif


/*============================================================================
 I N T E R N A L   M A C R O   A N D   T Y P E   D E F I N I T I O N S
============================================================================*/
/*
   Define a macro to get past the QAC problem with !TESTBIT
*/
#define FUEL03_NOTTESTBIT( operand, bit_mask ) (((operand) &  (bit_mask)) == ((bit_mask) - (bit_mask)))

#define FUEL03_MS_8_BITS( w )                      ((UINT8)((w) >> (8)))
#define FUEL03_MS_16_BITS( l )                     ((UINT16)((l) >> (16)))

/* --------------------------------------------------------------------------
** Define bit flags for the FilterFlags member of the FUEL03_FLT structure.
** --------------------------------------------------------------------------
*/
#define FUEL03_SENDER_OPEN             (0x80u)
#define FUEL03_SENDER_SHORTED          (0x40u)
#define FUEL03_FILL_DETECTED           (0x20u)
#define FUEL03_LOSS_DETECTED           (0x10u)
#define FUEL03_SAMPLE_OPEN_BIT         (0x08u)
#define FUEL03_SAMPLE_SHORT_BIT        (0x04u)
#define FUEL03_SAMPLE_IS_ABOVE_FILTER  (0x02u)
#define FUEL03_SAMPLE_IS_BELOW_FILTER  (0x01u)

/* --------------------------------------------------------------------------
** Define bit flags for the MoreFilterFlags member of the FUEL03_FLT structure.
** --------------------------------------------------------------------------
*/
#define FUEL03_KEY_OFF_SAMPLES_DONE    (0x80u)
#define FUEL03_FAST_FILL_FLAG          (0x40u)
#define FUEL03_FORCE_FUEL_INIT_FLAG    (0x20u)
#define FUEL03_INIT_FLAG               (0x10u)

/* --------------------------------------------------------------------------
** Define general bit flags used in the FuelFlags RAM storage byte.
** --------------------------------------------------------------------------
*/
#define FUEL03_COLD_INIT               (0x80u)
/*#define FUEL03_FORCE_INIT              (0x40u)*/
#define FUEL03_KEY_ON_DELAY_EXPIRED    (0x20u)

/* --------------------------------------------------------------------------
** Values used for PID C90A.
** --------------------------------------------------------------------------
*/
/*#define FUEL03_FILTER_NO_INIT      (0)*/
/*#define FUEL03_FILTER_NO_SAMPLES   (1)*/
/*#define FUEL03_FILTER_JAM_COLD     (2)*/
/*#define FUEL03_FILTER_JAM_FORCED   (3)*/
/*#define FUEL03_ZERO_SPEED_REF_USED (4)*/
/*#define FUEL03_KEY_OFF_REF_USED    (5)*/
/*#define FUEL03_FILTER_MSB_REF_USED (6)*/

/* --------------------------------------------------------------------------
** Values used for fuel03_invalid_condition variable which is used to
** store the FUEL03_VALID_CONDITION() condition status at different locations
** in the code
** --------------------------------------------------------------------------
*/
#define FUEL03_KEYOFF_PROCESSING_DONE   (0x01u)
#define FUEL03_ZSS_KEYOFF_PROCESSING    (0x02u)
#define FUEL03_KEYOFF_PROCESSING_1      (0x04u)
#define FUEL03_KEYOFF_PROCESSING_2      (0x08u)
#define FUEL03_PERIODIC_PROCESSING_1    (0x10u)
#define FUEL03_PERIODIC_PROCESSING_2    (0x20u)

/* --------------------------------------------------------------------------
** Values used for Fuel snapshot nvm queuing.
** --------------------------------------------------------------------------
*/
#define FUEL03_BLK1_QUEUED      (0x80u)
#define FUEL03_BLK2_QUEUED      (0x40u)

/* --------------------------------------------------------------------------
** Values used for FUEL03_MULT_FILT_RATES.
** --------------------------------------------------------------------------
*/
#if (FUEL03_MULT_FILT_RATES == 1)
#define FUEL03_DELTA_NORMAL_BASE_A1_INDX      (0)
#define FUEL03_DELTA_NORMAL_BASE_A2_INDX      (1)
#define FUEL03_DELTA_NORMAL_BASE_A3_INDX      (2)
#endif
/* --------------------------------------------------------------------------
** Typedef the fuel gage filter structure.  For each sender in the product,
** an instance of this structure must be created in RAM.
** --------------------------------------------------------------------------
*/
/* ------------------------------------------------------ */
/* Reordered the following for BSDI00024469 23/02/07 jarun*/
/* ------------------------------------------------------ */
/* ------------------------------------------------------------------------  */
/* KOS_ConvCycleCounter_shadow & KOS_SmplCounter_shadow elements             */
/* are added to just to have the copy of ConvCycleCounter & SmplCounter      */
/* variables. These shadow values are used to store in RAM snapshot in       */
/* fuel03_log_init_errors_to_nvm(). The reason to have the shadow is that    */
/* ConvCycleCounter & SmplCounter are cleared once KEY_OFF processing done   */
/* So the information is lost before storing into RAM snapshot which happens */
/* upon IGN trans into RUN. We used shadow to not disturb the existing proven */
/* code                                                                       */
/* -------------------------------------------------------------------------- */

typedef struct {
   UINT32 fdelta;                  /* [0] Fill Delta (fdelta) value that is added or subtracted
   from slosh filter value depending on the 'direction' of
   the incoming sender value. */
   UINT32 fdelta_base;             /* [0] Fill Delta Base (fdelta_base) value used as the lowest
   value for the fdelta value. */
   UINT32 keyon_radsum;            /* [2] accumulator for the good rad samples at keyon       */
   UINT32 slosh_filter;            /* [1] slosh filter value                       */
#ifdef  FUEL03_SLOSH_HYS
   UINT32 slosh_filter_hys;        /* [0] slosh filter with hysteresis             */
#endif
   UINT16 fdelta_adjust_base;      /* [0] Fill Delta Adjust value used as a small adjustment value
   added to fdelta. */
#ifdef  FUEL03_NEED_PID_C90A
   UINT16 init_pid;                /* [1] Storage location for holding what was used for the
   initialization reference. */
#endif
   UINT16 FuelFaultCounter;        /* [1] Sender open/short fault counter. */
   UINT16 FuelFaultRecoveryCounter;/* [1] Sender open/short recovery fault counter. */
   UINT16 rad;                     /* [1] ratio'd fuel a/d value from application */
   UINT16 avg_rad;                 /* [0] Average 'rad' set by the average rad processing function
   and based on different averaging schemes. */
   UINT16 old_rad;                 /* [0] Used in the average rad processing to hold the
   'old' rad. */
#ifdef  FUEL03_ERR_CNT
   UINT16  err_counter;            /* [0] Error counter for NVM data logging. */
#endif
   UINT8  FilterFlags;             /* [1] FilterFlags is used to store various 'flags' that are
   defined above. */
   UINT8  flps;                    /* [1] Fuel Level Percent full value from 0 to 254,
   255 indicates invalid. */
   UINT8  init_ref;                /* [1] Value used in the fuel filter initialization to hold
   the 'reference' value. */
   UINT8  KeyOffRef;               /* [2] Key off refernce storage location. */

   UINT8  keyon_good_samples;      /* [2] count up counter used during key on sampling period */
   UINT8  keyon_avgflps;           /* [2] Key on average flps storage location. */
   UINT8  MoreFilterFlags;         /* [1] Additional filter flags defined above. */
#ifdef FUEL03_RC_FILL_ENABLED
   UINT8  rc_fill_threshold;       /* [0] rental car fill threshold value from NVM */
   UINT8  rc_fill_delta;           /* [0] rental car fill delta value from NVM     */
#endif
   UINT8  rflps;                   /* [1] reference flps */
   UINT8  rfuel;                   /* [1] reference fuel, refer to the bds for more info */
   UINT8  zss_ref;                 /* [1] zero speed reference value               */
   UINT8   moving_sample_counter;  /* [0] Used in the average rad processing. Know as
   Sample Counter in the BDS. */
   UINT8   use_avg_flag;           /* [0] Flag indicating what to use in the average rad processing. */
   UINT8   use_mov_avg;            /* [0] Flag indicating what to use in the average rad processing. */
#ifdef FUEL03_FFRC_ENABLE
   BOOLEAN rate_check_passed;      /* [2] flag to indicate if the fast fill rate check has passed. */
   UINT8   ffrc_delta_ref;         /* [2] fast fill rate check delta reference */
   UINT8   sample_counter;         /* [0] sample index for rate check sample array */
   UINT8   rate_check_sample[FUEL03_MAX_RATE_CHECK_SAMPLES+1];
   /* [2] array to store values for ffrc */
   UINT16  rate_check_timer;       /* [0] fast fill rate check timer */
#endif
#if (FUEL03_REF_AVG_TYPE==4)     /* The following are used when the convergence algorithm is used. */
   UINT16  sum_vx;                 /* [2] Storage for the sum of the convergence samples. */
   UINT8   ConvCycleCounter;       /* [0] Convergence cycle counter. */
   UINT8   ConvSample;             /* [0] Convergence sample. */
   UINT8   SmplCounter;            /* [0] Convergence sample counter. */
   UINT8   min_vx;                 /* [2] Storage for finding the minimim convergence value. */
   UINT8   max_vx;                 /* [2] Storage for finding the maximum convergence value. */
   BOOLEAN koc_converged;          /* [2] Flag indicating if we have converged. */
   BOOLEAN koc_fault_flag;         /* [2] Convergence fault flag */
   BOOLEAN zs_converged;           /* [2] Fast fill convergence flag */
#if FUEL03_LOG_ConvCycleCounter==1
UINT8  KOS_ConvCycleCounter_shadow;
   UINT8  KOS_SmplCounter_shadow;
#endif
#endif
#if FUEL03_LOG_FAULT_RECORD_SIZE > 0
   BOOLEAN log_nvm_data;           /* [0] Flag indicating if the data should be logged in NVM. */
   UINT8 queue_result;

   /*                            Note: Values in [] indicates if the parameter is logged in NVM in
   an 'error' is detected.
   0 = No logging
   1 = Log it
   2 = Log it if the feature using the item is enabled.
   */

#endif
   UINT16 sample_array[FUEL03_SMPLS_2_AVG];
   /* [0] array used in average rad processing to hold the
   last 'x' samples for averaging. */

} FUEL03_FLT;


/*============================================================================
**      I N T E R N A L   F U N C T I O N   P R O T O T Y P E S
**==========================================================================*/
static void fuel03_cold_init( void );
static void fuel03_start_init( void );
static void fuel03_key_on_samples( void );
static void fuel03_test_sample( void );
static void fuel03_debounce_open_short( void );
static void fuel03_init_avgflps_calc(void);
static void fuel03_ref_fuel_calc( void );
static UINT8 fuel03_rad_to_flps( UINT16 fuel03_rad );
static void fuel03_slosh_filter(BOOLEAN fuel03_live_mode);
static void fuel03_fast_fill_enable_check(void);
static void fuel03_fast_fill_determination(void);
static void fuel03_fdelta_base(void);
static void fuel03_fault_recovery_counter(void);
static void fuel03_fault_counter(void);
static void fuel03_fdelta_base_and_adjust_nvm(void);
static void fuel03_fdelta_fast_base(void);
static void fuel03_fdelta_normal_base(void);
static void fuel03_average_rad_processing( void );
static void fuel03_common_gauge_init( void );
static void fuel03_finit_t3( void );
static void fuel03_finit_F3( void );
static void fuel03_fi_compare( void );
static void fuel03_fi_check( void );
static void fast_fill_determination_f1( void );
#ifdef FUEL03_KEY_OFF_ENABLED
static void fuel03_zss_keyoff_processing( UINT16 fuel03_rada );
#endif
#if (FUEL03_MULT_FILT_RATES == 1)
static UINT8 fuel03_get_fdelta_normal_base_index(void);
#endif
#ifdef FUEL03_RC_FILL_ENABLED
static void fuel03_level_calculation( void );
#endif
#ifdef  FUEL03_SLOSH_HYS
static void fuel03_level_calculation_with_hys( void );
#endif
static void fuel03_filter_initialize( void );

static void fuel03_fast_fill_samples( void );
static UINT8 fuel03_open_short_test(UINT16 fuel03_sample);

#if FUEL03_RAM_LOG_FAULT_RECORD_SIZE > 0
static void fuel03_log_init_errors_to_ram( void );
#endif
#if FUEL03_LOG_FAULT_RECORD_SIZE > 0
static void fuel03_log_init_errors_to_nvm( void );
#endif

#if (FUEL03_REF_AVG_TYPE==4)
static void fuel03_koc_setup( void );
static void fuel03_koc( void );
static void fuel03_ffsc( void );
#endif

#ifdef FUEL03_NEED_DTC_LOGGING
static void fuel03_log_dtcs(void);
#endif

/*============================================================================
**                M E M O R Y   A L L O C A T I O N
**==========================================================================*/


#pragma ghs startdata
#pragma ghs section bss = ".ApplicationBkUp"
/*
** Make sure the number of fuel tanks is between 2 and 10 if defined.
*/
#ifdef FUEL03_SCEM_NUMBER_OF_FUEL_TANKS
#if (FUEL03_SCEM_NUMBER_OF_FUEL_TANKS < 2)
#error FUEL03.CFG: FUEL03_SCEM_NUMBER_OF_FUEL_TANKS must be between 2 and 10.
#endif

#if (FUEL03_SCEM_NUMBER_OF_FUEL_TANKS > 10)
#error FUEL03.CFG: FUEL03_SCEM_NUMBER_OF_FUEL_TANKS must be between 2 and 10.
#endif

static UINT8 Fuel03TankIndex;
#endif

/* --------------------------------------------------------------------------
** Structure RAM allocation for both sender.
** --------------------------------------------------------------------------
*/

static FUEL03_FLT Fuel03SenderA;



/* --------------------------------------------------------------------------
** Combined sender percent full, with and without hysteresis.
** --------------------------------------------------------------------------
*/
#ifdef FUEL03_RC_FILL_ENABLED
static UINT16 fuel03_level;
#endif
#ifdef  FUEL03_SLOSH_HYS
static UINT16 fuel03_level_with_hys;
#endif
/* --------------------------------------------------------------------------
** General flags used by the filter algorithm.
** --------------------------------------------------------------------------
*/
static UINT8 Fuel03Flags;

/* --------------------------------------------------------------------------
** State variable to check the IGN change to do a fuel03_koc_setup()      **
** For fast fill mode.  BSDI00020595,  26/02/07 jarun                     **
** --------------------------------------------------------------------------
*/
#define FUEL03_RESET  0
#define FUEL03_KEYON  1
#define FUEL03_KEYOFF 2
#if (FUEL03_REF_AVG_TYPE==4)
static UINT8 Fuel03State;
/* --------------------------------------------------------------------------
** Timer for enabling Fast Fill if there are not enough good keyon samples.
** --------------------------------------------------------------------------
*/

static UINT16 Fuel03_AVG_Vol_Invalid_Counter;
#endif

/* --------------------------------------------------------------------------
** Timer used during fuel init.  The units of this timer are that of the
** filter iteration rate chosen by the application.
** --------------------------------------------------------------------------
*/
static UINT8 Fuel03KeyOnDelayCounter;
static UINT8 Fuel03InitDelayCounter;

/* --------------------------------------------------------------------------
** Counter for determining when to store the zero speed fuel sample.
** --------------------------------------------------------------------------
*/
static UINT16 Fuel03ZeroSpeedCounter;

#ifdef FUEL03_KEY_OFF_ENABLED
#if (FUEL03_REF_AVG_TYPE!=4)
/* --------------------------------------------------------------------------
** Key-off sampling counter.
** --------------------------------------------------------------------------
*/
static UINT16 Fuel03KeyOffSampleMaxTimer;
#endif
#endif
#if FUEL03_RAM_LOG_FAULT_RECORD_SIZE > 0
static UINT8 fuel03_RAM_fault_record;

#endif

/* --------------------------------------------------------------------------
** Rad to flps 16 bit storage location for fuel03_rad_to_flps.
** BSDI00030114 4/10/06 RRUSS1
** --------------------------------------------------------------------------
*/
static UINT16 Fuel03PercentFull;

/* --------------------------------------------------------------------------
** Timer for entering Fast Fill Mode if FUEL03_MIN_FAST_FILL_TIME elapsed.
** BSDI00044140  03/30/07 JARUN
** --------------------------------------------------------------------------
*/
static UINT8  Fuel03MinFastFillTimeCounter;

/* --------------------------------------------------------------------------
** Previous Fdelta Normal Base A
** --------------------------------------------------------------------------
*/
#if (FUEL03_MULT_FILT_RATES == 1)
static UINT8 Fuel03PrevFdeltaNormalBaseAIndx;
#endif

/* --------------------------------------------------------------------------
** Used to store the FUEL03_VALID_CONDITION() condition check status
** This is used for debug purpose
** --------------------------------------------------------------------------
*/
#if FUEL03_RAM_LOG_FAULT_RECORD_SIZE > 0
#if FUEL03_LOG_invalid_condition==1
static UINT8 fuel03_invalid_condition;
#endif
#endif

#ifdef FUEL03_IGN_STATUS
/* --------------------------------------------------------------------------
** Used to track the number of IGN cycles.It is used to see if there were
** fast key cycles
** --------------------------------------------------------------------------
*/
static UINT8 fuel03_ignition_cycle_counter;
static UINT8 fuel03_ignition_status;
#endif



/*
** Verify that the clamps for the fuel deltas do not exceed 3 bytes.
*/
#ifndef FUEL03_SCEM_NUMBER_OF_FUEL_TANKS
//#if (FUEL03_DELTA_NORMAL_CLAMP_A > 0x00FFFFFFuL)
//#error FUEL03.CFG: FUEL03_DELTA_NORMAL_CLAMP_A must not exceed 0x00FFFFFF.
//#endif
#if (FUEL03_DELTA_FAST_CLAMP_A > 0x00FFFFFFuL)
#error FUEL03.CFG: FUEL03_DELTA_FAST_CLAMP_A must not exceed 0x00FFFFFF.
#endif
#endif

#if (FUEL03_REF_AVG_TYPE > 4)
#error FUEL03.CFG: FUEL03_REF_AVG_TYPE > 4
#endif

#ifndef FUEL03_SCEM_NUMBER_OF_FUEL_TANKS
static const UINT32 fuel03_PRELOAD = FUEL03_SLOSH_FILTER_EMPTY_PRELOAD_A;
#else
static const UINT32 fuel03_PRELOAD[] = FUEL03_SLOSH_FILTER_EMPTY_PRELOAD_A;
#endif


#pragma ghs section bss=default
#pragma ghs enddata
/*============================================================================
**              F U N C T I O N S / S E R V E R S
**==========================================================================*/


/*============================================================================

    Function Name:      void fuel03_average_rad_processing(void)

    Visibility:         Internal

    Description:        This function performs the averaging feature.


    INPUTS/OUTPUTS

    Input Arguments:    None

    Output Arguments:   None

    Critical Section:   None

    Created:            08/06/04 by RRUSS1

    Updated:            08/06/04 by RRUSS1
============================================================================*/
static void fuel03_average_rad_processing( void )
{
    #if( FUEL03_AVG_TYPE != 0 )
    UINT8 fuel03_x;
   UINT32 fuel03_temp32;
    #endif


   /* ----------------------------------------------------------------------
   ** (2) FUEL03_AVG_TYPE = 0 ?
   ** ----------------------------------------------------------------------
   ** Check to see if the avg_type is 0. If it is then just set the
   ** avg_rad to the rad value and return.
   ** --------------------------------------------------------------------*/
    #if( FUEL03_AVG_TYPE == 0 )
   Fuel03SenderA.avg_rad = Fuel03SenderA.rad;  /* (3) AVG RAD x = RAD x */
   return;
    #else

   if( Fuel03SenderA.moving_sample_counter == 0 )
   {
      Fuel03SenderA.moving_sample_counter = FUEL03_SMPLS_2_AVG;
      Fuel03SenderA.use_avg_flag = 1;
   }
   Fuel03SenderA.moving_sample_counter--;

   if( TESTBIT(Fuel03SenderA.FilterFlags, (FUEL03_SAMPLE_OPEN_BIT | FUEL03_SAMPLE_SHORT_BIT)) )
   {
            #if( FUEL03_AVG_TYPE == 3 )
      Fuel03SenderA.use_avg_flag = 0;
            #else
      Fuel03SenderA.rad = Fuel03SenderA.old_rad;
            #endif
   }
   else
   {
      Fuel03SenderA.old_rad = Fuel03SenderA.rad;
   }
   /* ----------------------------------------------------------------------
   ** (13) Sample Sum x = Sample Sum x + RAD x
   ** ----------------------------------------------------------------------
   ** Put the 'rad' value (could be old_rad) into the sample_array[] buffer.
   ** --------------------------------------------------------------------*/
   fuel03_x = Fuel03SenderA.moving_sample_counter;
   Fuel03SenderA.sample_array[fuel03_x] = Fuel03SenderA.rad;

   /* ----------------------------------------------------------------------
   ** (14) Sample Counter x = 0 ?
   ** --------------------------------------------------------------------*/
   if( Fuel03SenderA.moving_sample_counter == 0 )
   {
            #if( FUEL03_AVG_TYPE == 1 )
      Fuel03SenderA.use_mov_avg = 1;
            #else

      if( Fuel03SenderA.use_avg_flag == 0 )
      {
      }
      else
      {
         fuel03_temp32 = 0;
         for( fuel03_x=0; fuel03_x<FUEL03_SMPLS_2_AVG; fuel03_x++ )
         {
            fuel03_temp32 += Fuel03SenderA.sample_array[fuel03_x];
         }
         fuel03_temp32 /= (UINT32)FUEL03_SMPLS_2_AVG;
         Fuel03SenderA.avg_rad = (UINT16)fuel03_temp32;
      }
            #endif
   }

   /* ----------------------------------------------------------------------
   ** (20) Sample Counter x = 0 ?
   ** --------------------------------------------------------------------*/
        #if( FUEL03_AVG_TYPE == 1 )

   if( Fuel03SenderA.use_mov_avg == 1 )
   {
      fuel03_temp32 = 0;
      for( fuel03_x=0; fuel03_x<FUEL03_SMPLS_2_AVG; fuel03_x++ )
      {
         fuel03_temp32 += Fuel03SenderA.sample_array[fuel03_x];
      }
      fuel03_temp32 /= (UINT32)FUEL03_SMPLS_2_AVG;
      Fuel03SenderA.avg_rad = (UINT16)fuel03_temp32;
   }
        #endif


    #endif
}

#ifdef FUEL03_FFRC_ENABLE
/*============================================================================
**
**  Function Name:      void fuel03_fast_fill_rate_check(void)
**
**  Visibility:         Internal
**
**  Description:        This function performs the fast fill rate check if
**                      enabled.
**
**  INPUTS/OUTPUTS
**
**  Input Arguments:    None
**
**  Output Arguments:   None
**
**  Critical Section:   None
**
**  Created:            07/29/04 by RRUSS1
**
**  Updated:            07/29/04 by RRUSS1
**==========================================================================*/
static void fuel03_fast_fill_rate_check( void )
{
   UINT8 fuel03_upper; /* define some locals to make the code easier to look at */
   UINT8 fuel03_lower;
   UINT8 fuel03_loop;
   UINT8 LocalUpper8;
   UINT8 LocalLower8;

   /* rruss1_08_11_04 : added per updated requirements */
   if( TESTBIT(Fuel03SenderA.FilterFlags, (FUEL03_SENDER_OPEN | FUEL03_SENDER_SHORTED)) )
   {
      Fuel03SenderA.rate_check_passed = FALSE;
      return;
   }

   /* ----------------------------------------------------------------------
   ** (2) Rate_Check = 0
   ** --------------------------------------------------------------------*/
   Fuel03SenderA.rate_check_passed = FALSE;

   /* ----------------------------------------------------------------------
   ** (3) zss_ref_x = 0xFF?   Make sure the zero speed sample is valid.
   ** --------------------------------------------------------------------*/
   if( Fuel03SenderA.zss_ref == FUEL03_PERCENT_FULL_INVALID_BYTE )
   {
      /* ----------------------------------------------------------------------
      ** (6) Reset the sample timer.
      ** --------------------------------------------------------------------*/
      Fuel03SenderA.rate_check_timer = FUEL03_RATE_CHECK_TIMER_START_VALUE;
   }
   else
   {
      if( TESTBIT( Fuel03SenderA.MoreFilterFlags, FUEL03_FAST_FILL_FLAG ) )
      {
         Fuel03SenderA.sample_counter = 0;
         Fuel03SenderA.rate_check_timer = FUEL03_RATE_CHECK_TIMER_START_VALUE;
      }
      else
      {
         if( Fuel03SenderA.rate_check_timer != 0 )
         {
            Fuel03SenderA.rate_check_timer--;
         }
         else
         {
            Fuel03SenderA.sample_counter++;
            Fuel03SenderA.rate_check_sample[Fuel03SenderA.sample_counter] = Fuel03SenderA.rflps;


            if( Fuel03SenderA.sample_counter == FUEL03_MAX_RATE_CHECK_SAMPLES )
            {
               fuel03_upper = Fuel03SenderA.rate_check_sample[FUEL03_MAX_RATE_CHECK_SAMPLES];
               fuel03_lower = Fuel03SenderA.rate_check_sample[0];


#ifdef FUEL03_SCEM_NUMBER_OF_FUEL_TANKS
               LocalUpper8 = Fuel03UpperRateCheckLimit_A_NVM[Fuel03TankIndex];
               LocalLower8 = Fuel03LowerRateCheckLimit_A_NVM[Fuel03TankIndex];
#else
               LocalUpper8 = Fuel03UpperRateCheckLimit_A_NVM;
               LocalLower8 = Fuel03LowerRateCheckLimit_A_NVM;
#endif

               if( (fuel03_upper > fuel03_lower) &&
                  ((fuel03_upper - fuel03_lower) > LocalLower8) &&
                  ((fuel03_upper - fuel03_lower) < LocalUpper8)  )
               {
                  Fuel03SenderA.rate_check_passed = TRUE;
               }
               else
               {
                  Fuel03SenderA.ffrc_delta_ref = Fuel03SenderA.rate_check_sample[1];
               }

               for( fuel03_loop = 0; fuel03_loop <= (FUEL03_MAX_RATE_CHECK_SAMPLES-1); fuel03_loop++ )
               {
                  Fuel03SenderA.rate_check_sample[fuel03_loop] = Fuel03SenderA.rate_check_sample[fuel03_loop+1];
               }
               Fuel03SenderA.sample_counter = FUEL03_MAX_RATE_CHECK_SAMPLES-1;
               Fuel03SenderA.rate_check_timer = FUEL03_RATE_CHECK_TIMER_START_VALUE;
            }
            else
            {
               Fuel03SenderA.rate_check_timer = FUEL03_RATE_CHECK_TIMER_START_VALUE;
            }
         }
      }
   }

}
#endif

/*============================================================================
**
**  Function Name:      void fuel03_get_tank_config(void)
**
**  Visibility:         Internal
**
**  Description:        This function configues the tank index value.
**
**  INPUTS/OUTPUTS
**
**  Input Arguments:    None
**
**  Output Arguments:   None
**
**  Critical Section:   None
**
**  Created:            02/20/04 by RRUSS1
**
**  Updated:            05/23/06 by RRUSS1  BSDI00031391
**==========================================================================*/
#ifdef FUEL03_SCEM_NUMBER_OF_FUEL_TANKS
static void fuel03_get_tank_config( void )
{
   UINT8 idx;
   UINT8 idx_val;

   Fuel03TankIndex = 0;

   idx_val = FUEL03_GET_FUEL_SCEM();

   for( idx=0; idx<FUEL03_SCEM_NUMBER_OF_FUEL_TANKS; idx++ )
   {
      if( idx_val == fuel03_tank_array[idx][0] )
      {
         Fuel03TankIndex = fuel03_tank_array[idx][1];
      }
   }
}
#endif

/*============================================================================
**
**  Function Name:      void fuel03_common_gauge_init(void)
**
**  Visibility:         Internal
**
**  Description:        This function initializes the variables to values that
**                      are common to Cold Reset, Warm Reset, and Transition
**                      into run.
**
**  INPUTS/OUTPUTS
**
**  Input Arguments:    Address of FUEL03_FLT structure
**
**  Output Arguments:   None
**
**  Critical Section:   None
**
**  Created:            09/15/03 by RRUSS1
**
**  Updated:            08/13/04 by RRUSS1
**                      03/30/07 by JARUN
**==========================================================================*/
static void fuel03_common_gauge_init( void )
{
   /* ----------------------------------------------------------------------
   ** Set the key on number of good samples collected counter to 0. This
   ** counter counts up and is only used during the inital key on sampling
   ** period.
   ** --------------------------------------------------------------------*/
   Fuel03SenderA.keyon_good_samples = 0;


   /* ----------------------------------------------------------------------
   ** Common FilterFlags Configuration
   **
   ** The following bit flags in FilterFlag are cleared for the 3 common
   ** init events.
   ** --------------------------------------------------------------------*/
   CLEARBIT( Fuel03SenderA.FilterFlags, (FUEL03_SAMPLE_IS_BELOW_FILTER |
      FUEL03_SAMPLE_IS_ABOVE_FILTER |
      FUEL03_FILL_DETECTED          |
      FUEL03_LOSS_DETECTED) );

   /* ----------------------------------------------------------------------
   ** Common MoreFilterFlags Configuration
   **
   ** The following bit flags in MoreFilterFlag are cleared for the 3 common
   ** init events.
   ** 8/13/2004 rruss1 : removed the fast fill init flag
   ** --------------------------------------------------------------------*/
   CLEARBIT( Fuel03SenderA.MoreFilterFlags, ( FUEL03_KEY_OFF_SAMPLES_DONE |
      FUEL03_INIT_FLAG) );

   /* ----------------------------------------------------------------------
   ** Set the average flps to 0.
   ** --------------------------------------------------------------------*/
   Fuel03SenderA.keyon_avgflps = 0;

   /* ----------------------------------------------------------------------
   ** Set the fdelta's.
   ** --------------------------------------------------------------------*/
   Fuel03SenderA.fdelta = 0;

   fuel03_fdelta_base_and_adjust_nvm();

   /* ----------------------------------------------------------------------
   ** Set the flps to invalid.
   ** --------------------------------------------------------------------*/
   Fuel03SenderA.flps = FUEL03_PERCENT_FULL_INVALID_BYTE;

   /* ----------------------------------------------------------------------
   ** Start the init & key on delay counters.
   ** --------------------------------------------------------------------*/
   Fuel03KeyOnDelayCounter = Fuel03KeyOnDelayCounterNVM;
   Fuel03InitDelayCounter = Fuel03InitDelayCounterNVM;

   /* ----------------------------------------------------------------------
   ** Set the Min fast fill time counter to default value.
   ** --------------------------------------------------------------------*/

   Fuel03MinFastFillTimeCounter = Fuel03FastFillTimeCounterNVM;
#ifdef FUEL03_KEY_OFF_ENABLED
#if (FUEL03_REF_AVG_TYPE!=4)
   /* ----------------------------------------------------------------------
   ** Clear the ky off sample timer.
   ** --------------------------------------------------------------------*/
   Fuel03KeyOffSampleMaxTimer = 0;
#endif
#endif
   Fuel03SenderA.rad = FUEL03_PERCENT_FULL_INVALID_BYTE;

   Fuel03SenderA.keyon_radsum = 0;

   /*
   ** Set the fast fill rate check stuff.
   */
#ifdef FUEL03_FFRC_ENABLE
   Fuel03SenderA.rate_check_passed = FALSE;
   Fuel03SenderA.sample_counter = 0;
   Fuel03SenderA.rate_check_timer = FUEL03_RATE_CHECK_TIMER_START_VALUE;
   Fuel03SenderA.ffrc_delta_ref = FUEL03_PERCENT_FULL_INVALID_BYTE;
#endif

   Fuel03SenderA.moving_sample_counter = 0;
#if (FUEL03_REF_AVG_TYPE==4)
   Fuel03_AVG_Vol_Invalid_Counter = 0;
#endif

#if (FUEL03_MULT_FILT_RATES == 1)
   Fuel03PrevFdeltaNormalBaseAIndx = FUEL03_DELTA_NORMAL_BASE_A1_INDX;
#endif

}

/*============================================================================
**
**  Function Name:      void fuel03_cold_init( void )
**
**  Visibility:         Internal
**
**  Description:        Cold init for fuel filter feature server.
**
**  INPUTS/OUTPUTS
**
**  Input Arguments:    *fuel03_flt - fuel filter structure pointer.
**
**  Output Arguments:   None
**
**  Critical Section:   None
**
**  Created:            09/16/03 by RRUSS1
**
**  Updated:            09/16/03 by RRUSS1
**                      05/26/08 by CNAGARA1
**==========================================================================*/
static void fuel03_cold_init( void )
{
   /* ----------------------------------------------------------------------
   ** Cold Reset FilterFlags Configuration
   **
   ** The following bit flags in FilterFlag are cleared during a
   ** cold reset event.
   ** --------------------------------------------------------------------*/
   CLEARBIT( Fuel03SenderA.FilterFlags, (FUEL03_SENDER_OPEN      |
      FUEL03_SENDER_SHORTED   |
      FUEL03_SAMPLE_OPEN_BIT  |
      FUEL03_SAMPLE_SHORT_BIT) );

   /* ----------------------------------------------------------------------
   ** Cold Reset MoreFilterFlags Configuration
   **
   ** The following bit flags in MoreFilterFlag are cleared during a
   ** cold reset event.
   ** 8/13/2004 rruss1 : added fast fill flag
   ** --------------------------------------------------------------------*/
   CLEARBIT( Fuel03SenderA.MoreFilterFlags, (FUEL03_FORCE_FUEL_INIT_FLAG |
      FUEL03_FAST_FILL_FLAG) );

   /* ----------------------------------------------------------------------
   ** Set the open/short sender counter to the default value.
   ** --------------------------------------------------------------------*/
   fuel03_fault_counter();
   fuel03_fault_recovery_counter();

   /* ----------------------------------------------------------------------
   ** Set the slosh filter and slosh filter with hys to the preload value.
   ** --------------------------------------------------------------------*/
#ifndef FUEL03_SCEM_NUMBER_OF_FUEL_TANKS
   Fuel03SenderA.slosh_filter     = fuel03_PRELOAD;
#ifdef  FUEL03_SLOSH_HYS
   Fuel03SenderA.slosh_filter_hys = fuel03_PRELOAD;
#endif
#else
   Fuel03SenderA.slosh_filter     = fuel03_PRELOAD[Fuel03TankIndex];
#ifdef  FUEL03_SLOSH_HYS
   Fuel03SenderA.slosh_filter_hys = fuel03_PRELOAD[Fuel03TankIndex];
#endif
#endif

   Fuel03SenderA.KeyOffRef = FUEL03_PERCENT_FULL_INVALID_BYTE;
#ifdef  FUEL03_NEED_PID_C90A
   Fuel03SenderA.init_pid = 0x00ff;
#endif

   Fuel03SenderA.zss_ref = FUEL03_PERCENT_FULL_INVALID_BYTE;

   Fuel03SenderA.rflps = FUEL03_PERCENT_FULL_INVALID_BYTE;
#if FUEL03_LOG_FAULT_RECORD_SIZE > 0
   Fuel03SenderA.log_nvm_data = 0;
#endif
#if FUEL03_LOG_FAULT_RECORD_SIZE > 0
   Fuel03SenderA.queue_result = 0;
#endif
#ifdef FUEL03_IGN_STATUS
   fuel03_ignition_cycle_counter=0;
   fuel03_ignition_status = FUEL03_RESET;
#endif
}

/*============================================================================
**
**  Function Name:      void fuel03_KSColdInit(void)
**
**  Visibility:         External
**
**  Description:        Cold init for fuel filter feature server.
**
**  INPUTS/OUTPUTS
**
**  Input Arguments:    None
**
**  Output Arguments:   None
**
**  Critical Section:   None
**
**  Created:            05/07/03 by RRUSS1
**
**  Updated:            07/16/03 by RRUSS1
**                      02/27/07 by JARUN for BSDI00038410
**                      03/10/08 by CNAGARA1 - BSDI00055412
**                      01/28/10 by BVIJAYKU- For QAC fix
**==========================================================================*/
void fuel03_KSColdInit(void)
{

#if (FUEL03_REF_AVG_TYPE==4)
   Fuel03State = FUEL03_RESET;
#endif

#ifdef FUEL03_SCEM_NUMBER_OF_FUEL_TANKS
   fuel03_get_tank_config();
#endif
   /*
   ** Set up conditions to start init at the next appropriate time.
   */
   fuel03_setup_for_init();
   fuel03_cold_init();


#ifndef FUEL03_SCEM_NUMBER_OF_FUEL_TANKS
#ifdef FUEL03_RC_FILL_ENABLED
   Fuel03SenderA.rc_fill_threshold = Fuel03SenderA_RCFillThresholdNVM;
   Fuel03SenderA.rc_fill_delta = Fuel03SenderA_RCFillDeltaNVM;
   fuel03_level          = FUEL03_MS_16_BITS( fuel03_PRELOAD );
#endif
#ifdef  FUEL03_SLOSH_HYS
   fuel03_level_with_hys = FUEL03_MS_16_BITS( fuel03_PRELOAD );
#endif
#else
#ifdef FUEL03_RC_FILL_ENABLED
   Fuel03SenderA.rc_fill_threshold = Fuel03SenderA_RCFillThresholdNVM[Fuel03TankIndex];
   Fuel03SenderA.rc_fill_delta = Fuel03SenderA_RCFillDeltaNVM[Fuel03TankIndex];
   fuel03_level          = FUEL03_MS_16_BITS( fuel03_PRELOAD[Fuel03TankIndex] );
#endif
#ifdef  FUEL03_SLOSH_HYS
   fuel03_level_with_hys = FUEL03_MS_16_BITS( fuel03_PRELOAD[Fuel03TankIndex] );
#endif
#endif

   /*
   ** Set the COLD init flag and clear all of the others.
   */
   Fuel03Flags = FUEL03_COLD_INIT;


   /*
   ** If the NVM logging is enabled, set the RAM record pointer to the
   ** max so the first time it is logged to RAM, the pointer will be set to 0.
   */

#if FUEL03_RAM_LOG_FAULT_RECORD_SIZE > 0
   fuel03_RAM_fault_record = FUEL03_RAM_LOG_FAULT_RECORD_SIZE;
#endif

   /* Added the following per BSDI00024437 9/14/05 rruss1 */
#if (FUEL03_REF_AVG_TYPE==4)
   Fuel03SenderA.koc_fault_flag = TRUE;
#endif

#if FUEL03_RAM_LOG_FAULT_RECORD_SIZE > 0
#if FUEL03_LOG_invalid_condition==1
   fuel03_invalid_condition = 0;
#endif
#endif
}
/*============================================================================
**
**  Function Name:      void fuel03_KSWarmInit(void)
**
**  Visibility:         External
**
**  Description:        Warm init for fuel filter feature server.
**
**  INPUTS/OUTPUTS
**
**  Input Arguments:    None
**
**  Output Arguments:   None
**
**  Critical Section:   None
**
**  Created:            05/07/03 by RRUSS1
**
**  Updated:            07/16/03 by RRUSS1
**==========================================================================*/
void fuel03_KSWarmInit(void)
{
   /*
   ** Set up conditions to start init at the next appropriate time.
   */
   fuel03_setup_for_init();
}


/*============================================================================
**
**  Function Name:      void fuel03_KSWakeup(void)
**
**  Visibility:         External
**
**  Description:        Wakeup for fuel filter feature server.
**
**  INPUTS/OUTPUTS
**
**  Input Arguments:    None
**
**  Output Arguments:   None
**
**  Critical Section:   None
**
**  Created:            05/07/03 by RRUSS1
**
**  Updated:            07/16/03 by RRUSS1
**==========================================================================*/
void fuel03_KSWakeup(void)
{
   /*
   ** Set up conditions to start init at the next appropriate time.
   */
   fuel03_setup_for_init();
}
/*============================================================================
**
** Function Name:      BOOLEAN fuel03_KSNvRamCheck(void)
**
** Visibility:         External by way of fuel03.h
**
** Description:        RAM check for the Fuel filter algorithm gage feature server.
**
** Invocation:         Called by SCHED.C via the PROD_SPEC_NVRAM_CHECK_LIST
**                     config item in SCHED.CFG.
**
** Inputs/Outputs:     O - returns FALSE if RAM corruption, TRUE otherwise
**
** Critical Section:   None
**
** Created:            11/04/13 by BVIJAYKU
**
** Updated:            
**
**==========================================================================*/
BOOLEAN fuel03_KSNvRamCheck(void)
{
  BOOLEAN fl_retval_bool;

  /*
  ** Verify that the stepper state is within range.
  */
  if (Fuel03InitGoodSamplesReqNVM == 0)
  {
    fl_retval_bool = FALSE;
  }
  else
  {
    fl_retval_bool = TRUE;
  }
  return(fl_retval_bool);
}
/*============================================================================
**
**  Function Name:      void fuel03_setup_for_init(void)
**
**  Visibility:         External
**
**  Description:        Function to be called whenever the product specific
**                      code wants to start a fuel gage init.
**
**  INPUTS/OUTPUTS
**
**  Input Arguments:    None
**
**  Output Arguments:   None
**
**  Critical Section:   None
**
**  Created:            05/07/03 by RRUSS1
**
**  Updated:            07/16/03 by RRUSS1
**==========================================================================*/
void fuel03_setup_for_init(void)
{
   fuel03_common_gauge_init();

   /*
   ** Set up conditions to start init at the next appropriate time.
   */
   fuel03_start_init();

   /*
   ** Clear all general fuel flags except COLD INIT and FORCE INIT.
   */
   CLEARBIT(Fuel03Flags, FUEL03_KEY_ON_DELAY_EXPIRED) ;

   /*
   ** Start the zero speed counter.
   */
   Fuel03ZeroSpeedCounter = Fuel03ZeroSpeedCounterNVM;

}

/*============================================================================
**
**  Function Name:      void fuel03_start_init( void )
**
**  Visibility:         Internal
**
**  Description:        Setup conditions for fuel gage init.
**
**  INPUTS/OUTPUTS
**
**  Input Arguments:    *fuel03_flt - fuel filter structure pointer.
**
**  Output Arguments:   None
**
**  Critical Section:   None
**
**  Created:            05/07/03 by RRUSS1
**
**  Updated:            10/09/09 by KNAGASUB
**==========================================================================*/
static void fuel03_start_init( void )
{
   /*
   ** Set up RAM to perform a fuel init when the periodic filter routine is
   ** iterated.
   */

   fuel03_fault_counter();
   fuel03_fault_recovery_counter();
   fuel03_fdelta_normal_base();
   fuel03_fdelta_base_and_adjust_nvm();
   /*
   ** Clear all flags except the sender open/short flags.
   */
   CLEARBIT(Fuel03SenderA.FilterFlags, (FUEL03_FILL_DETECTED | FUEL03_LOSS_DETECTED |
      FUEL03_SAMPLE_OPEN_BIT | FUEL03_SAMPLE_SHORT_BIT |
      FUEL03_SAMPLE_IS_ABOVE_FILTER | FUEL03_SAMPLE_IS_BELOW_FILTER));


   /* if the fast fill rate check is enable, don't clear the fast fill flag */
#ifdef FUEL03_FFRC_ENABLE
   CLEARBIT(Fuel03SenderA.MoreFilterFlags, (FUEL03_KEY_OFF_SAMPLES_DONE |
      FUEL03_INIT_FLAG  ));
#else
   Fuel03SenderA.rflps = FUEL03_PERCENT_FULL_INVALID_BYTE;

   CLEARBIT(Fuel03SenderA.MoreFilterFlags, (FUEL03_KEY_OFF_SAMPLES_DONE | FUEL03_INIT_FLAG |FUEL03_FAST_FILL_FLAG ));
#endif
#if FUEL03_LOG_FAULT_RECORD_SIZE > 0
   Fuel03SenderA.queue_result =  (FUEL03_BLK1_QUEUED | FUEL03_BLK2_QUEUED);
#endif
}

#ifdef FUEL03_KEY_OFF_ENABLED
/*============================================================================
**
**  Function Name:      BOOLEAN fuel03_keyoff_processing_done( void )
**
**  Visibility:         External
**
**  Description:        A helper function for key off processing.
**
**  Requirments:        Figure 3.6.4-1 Fuel BDS
**
**  INPUTS/OUTPUTS
**
**  Input Arguments:    None.
**
**  Output Arguments:   None.
**
**  Critical Section:   None
**
**  Created:            08/27/03 by RRUSS1
**
**  Updated:            03/15/06 by RRUSS1
**                      05/26/08 by CNAGARA1
**                      01/28/10 by BVIJAYKU- For QAC fix
**==========================================================================*/
BOOLEAN fuel03_keyoff_processing_done( void )
{
   BOOLEAN fuel03_ret_val = FALSE;

   if( FUEL03_VALID_CONDITION == FALSE )
   {
      fuel03_ret_val = TRUE;
#if FUEL03_RAM_LOG_FAULT_RECORD_SIZE > 0
#if FUEL03_LOG_invalid_condition==1
      fuel03_invalid_condition |= FUEL03_KEYOFF_PROCESSING_DONE;
#endif
#endif

   }
   else
   {
      if( TESTBIT( Fuel03SenderA.MoreFilterFlags, FUEL03_KEY_OFF_SAMPLES_DONE ) )
      {
         fuel03_ret_val = TRUE;
      }
   }
   return( fuel03_ret_val );
}
#endif

#ifdef FUEL03_KEY_OFF_ENABLED
/*============================================================================
**
**  Function Name:      void fuel03_zss_keyoff_processing( UINT16 rada )
**
**  Visibility:         Internal
**
**  Description:        A helper function for key off processing.
**
**  Requirments:        Figure 3.6.4-1 Fuel BDS
**
**  INPUTS/OUTPUTS
**
**  Input Arguments:    rada- latest rationed fuel sample for the A sender
**
**  Output Arguments:   None.
**
**  Critical Section:   None
**
**  Created:            05/07/03 by RRUSS1
**
**  Updated:            02/15/05 by RRUSS1    BSDI00016760
**                      02/27/07 by JARUN    BSDI00038410
**                      01/28/10 by BVIJAYKU
**            07/02/14 by RAGARWA1
**==========================================================================*/
static void fuel03_zss_keyoff_processing( UINT16 fuel03_rada )
{
      if( Fuel03ZeroSpeedCounter == 0 )
      {
         SETBIT( Fuel03SenderA.MoreFilterFlags, FUEL03_KEY_OFF_SAMPLES_DONE );
         return;
      }
      /*Fuel03ZeroSpeedCounter--; removed 3/15/06 rruss1 since it caused the
      counter to decrement at twice the rate */

      fuel03_fast_fill_enable_check();

      /* --------------------------------------*/
      /* VALID CONDITION ? Return if not.      */
      /* --------------------------------------*/
      if( FUEL03_VALID_CONDITION == FALSE )
      {
#if FUEL03_RAM_LOG_FAULT_RECORD_SIZE > 0
#if FUEL03_LOG_invalid_condition==1
         fuel03_invalid_condition |= FUEL03_ZSS_KEYOFF_PROCESSING;
#endif
#endif
      }
      if( FUEL03_VALID_CONDITION != FALSE )
      {
         Fuel03SenderA.rad = fuel03_rada;                 /* Store, */
         fuel03_test_sample();            /* Test,  */
         fuel03_debounce_open_short();    /* and Debounce the sender(s)
         for open/short conditions. */
         fuel03_average_rad_processing();

#if (FUEL03_REF_AVG_TYPE==4)
         fuel03_ffsc();
#else
         #if( FUEL03_REF_AVG_TYPE != 0 )
            /* ----------------------------------------------------------
            ** RFLPS Calc: fig 3.6.4-4
            ** Calculate the Reference FLPS.
            ** --------------------------------------------------------*/
            /* rruss1_08_09_04 : Changed the following from rad to avg_rad per new
            requirments for 'averaging' and put it into both
            flps and rflps. */
            Fuel03SenderA.flps = fuel03_rad_to_flps( Fuel03SenderA.avg_rad );
            Fuel03SenderA.rflps = Fuel03SenderA.flps;

            /* ----------------------------------------------------------
            ** Fast Fill Samples: fig 3.6.4-13
            ** --------------------------------------------------------*/
            fuel03_fast_fill_samples();
         #else
            if( TESTBIT(Fuel03SenderA.FilterFlags, (FUEL03_SAMPLE_OPEN_BIT | FUEL03_SAMPLE_SHORT_BIT)) )
            {
            }
            else
            {
               /* ----------------------------------------------------------
               ** RFLPS Calc: fig 3.6.4-4
               ** Calculate the Reference FLPS.
               ** --------------------------------------------------------*/
               /* rruss1_08_09_04 : Changed the following from rad to avg_rad per new
               requirments for 'averaging' and put it into both
               flps and rflps. */
               Fuel03SenderA.flps = fuel03_rad_to_flps( Fuel03SenderA.avg_rad );
               Fuel03SenderA.rflps = Fuel03SenderA.flps;

               /* ----------------------------------------------------------
               ** Fast Fill Samples: fig 3.6.4-13
               ** --------------------------------------------------------*/
               fuel03_fast_fill_samples();
            }
     #endif
#endif

      }

}
#endif

#ifdef FUEL03_HILL_HOLD_ENABLE

/*============================================================================
**
**  Function Name:      void fuel03_key_off_sample_processing( void )
**
**  Visibility:         External
**
**  Description:        A helper function for periodic keyoff processing of
**                      the fuel sender(s).
**
**  Requirments:        Section of Figure 3.6.4-1 Fuel BDS
**
**  INPUTS/OUTPUTS
**
**  Input Arguments:    Pointer to sender data.
**
**  Output Arguments:   Various. See code.
**
**  Critical Section:   None
**
**  Created:            07/09/03 by RRUSS1
**
**  Updated:            08/18/04 by RRUSS1 -  Added KO Convergence.
**                      08/25/04 by RRUSS1 -  Added check for FUEL03_REF_AVG_TYPE == 0.
**                      02/26/07 by JARUN  - for BSDI00038410
**==========================================================================*/
static void fuel03_key_off_sample_processing( void )
{
   if( FUEL03_NOTTESTBIT(Fuel03SenderA.MoreFilterFlags, FUEL03_KEY_OFF_SAMPLES_DONE) )
   {
      /* ----------------------------------------------------------------------
      ** If the sender is OPEN or SHORT, set the KeyOffRef value to Invalid.
      ** --------------------------------------------------------------------*/
      if( TESTBIT(Fuel03SenderA.FilterFlags, (FUEL03_SENDER_OPEN | FUEL03_SENDER_SHORTED)) )
      {
         /* added the following check 6/27/06 per BSDI00032867 */
#if (FUEL03_REF_AVG_TYPE==4)
#else
         Fuel03SenderA.KeyOffRef = FUEL03_PERCENT_FULL_INVALID_BYTE;
#endif
         SETBIT( Fuel03SenderA.MoreFilterFlags, FUEL03_KEY_OFF_SAMPLES_DONE );
      }
      else
      {
         /* rruss1_08_18_04 : added */
#if (FUEL03_REF_AVG_TYPE==4)
         fuel03_koc();
#else
         /* rruss1_08_25_04 : added */
         if( FUEL03_REF_AVG_TYPE == 0 )
         {
            if( TESTBIT(Fuel03SenderA.FilterFlags, (FUEL03_SAMPLE_OPEN_BIT | FUEL03_SAMPLE_SHORT_BIT)) )
            {
               return;
            }
         }
         /* rruss1_08_09_04 : Changed the following from rad to avg_rad per new
         requirments for 'averaging' */
         Fuel03SenderA.flps = fuel03_rad_to_flps( Fuel03SenderA.avg_rad );
         Fuel03SenderA.rflps = Fuel03SenderA.flps;
         Fuel03SenderA.KeyOffRef = Fuel03SenderA.rflps;
#endif
      }
   }
}
#endif
#ifdef FUEL03_KEY_OFF_ENABLED
/*============================================================================
**
**  Function Name:      void fuel03_keyoff_processing(UINT16 rada)
**
**  Visibility:         External
**
**  Description:        A function to handle periodic keyoff processing of
**                      the fuel sender(s).
**
**  Requirments:        Figure 3.6.4-1 Fuel BDS
**
**  INPUTS/OUTPUTS
**
**  Input Arguments:    rada - latest rationed fuel sample for the A sender
**
**  Output Arguments:   TRUE if keyoff processing finished, else FALSE.
**
**  Critical Section:   None
**
**  Created:            07/09/03 by RRUSS1
**
**  Updated:            08/27/03 by RRUSS1
**                      02/27/07 by JARUN for BSDI00038410
**            07/02/14 by RAGARWA1
**
**==========================================================================*/
void fuel03_keyoff_processing(UINT16 fuel03_rada )
{
#ifdef FUEL03_SCEM_NUMBER_OF_FUEL_TANKS
   fuel03_get_tank_config();
#endif
   /*
   ** Log DTCs for open/shorted sender(s).
   */
#ifdef FUEL03_NEED_DTC_LOGGING
   if( FUEL03_VALID_CONDITION != FALSE )
   {
      fuel03_log_dtcs();
   }
   else
   {

#if FUEL03_RAM_LOG_FAULT_RECORD_SIZE > 0
#if FUEL03_LOG_invalid_condition==1
      fuel03_invalid_condition |= FUEL03_KEYOFF_PROCESSING_1;
#endif
#endif
   }
#endif

#if (FUEL03_REF_AVG_TYPE==4)
   if( Fuel03State != FUEL03_KEYOFF )
   {
      fuel03_koc_setup();
      Fuel03State = FUEL03_KEYOFF;
   }
#endif
#ifdef FUEL03_IGN_STATUS
   fuel03_ignition_status = FUEL03_KEYOFF;
#endif


   /* ----------------------------------------------------------------------
   ** HILL_HOLD_ENABLE = 1 ?
   ** --------------------------------------------------------------------*/
   if( FUEL03_NOTTESTBIT(Fuel03OptionsNVM, FUEL03_HILL_HOLD_ENABLE_BIT) )
   {
     /* ----------------------------------------------------------------------
     ** Set the key off referance values to INVALID.
     ** --------------------------------------------------------------------*/

    Fuel03SenderA.KeyOffRef = FUEL03_PERCENT_FULL_INVALID_BYTE;

     /* ----------------------------------------------------------------------
     ** Check if the ZSS_REF_ONLY option is enabled.
     ** --------------------------------------------------------------------*/

     if( TESTBIT(Fuel03OptionsNVM, FUEL03_ZSS_REF_ONLY_BIT) )
    {
        fuel03_zss_keyoff_processing( fuel03_rada );
    }
    else
    {
      /* -------------------------------------------------- */
       /* Added the following for BSDI00023218               */
       /* -------------------------------------------------- */

      SETBIT( Fuel03SenderA.MoreFilterFlags, FUEL03_KEY_OFF_SAMPLES_DONE );
    }
      return;


   }
#ifdef FUEL03_HILL_HOLD_ENABLE

#if (FUEL03_REF_AVG_TYPE==4)
   if( (Fuel03SenderA.koc_converged != FALSE) ||
      (TESTBIT( Fuel03SenderA.MoreFilterFlags, FUEL03_KEY_OFF_SAMPLES_DONE) ) )
   {
      SETBIT( Fuel03SenderA.MoreFilterFlags, FUEL03_KEY_OFF_SAMPLES_DONE );
      return;
   }
#else

   /* ----------------------------------------------------------------------
   ** A Fuel Init = 1 ?
   ** --------------------------------------------------------------------*/
   if( FUEL03_NOTTESTBIT(Fuel03SenderA.MoreFilterFlags, FUEL03_INIT_FLAG) )
   {
      if(Fuel03SenderA.KeyOffRef != FUEL03_PERCENT_FULL_INVALID_BYTE)
      {

         SETBIT( Fuel03SenderA.MoreFilterFlags, FUEL03_KEY_OFF_SAMPLES_DONE );
         return;

      }
   }


   /* ----------------------------------------------------------------------
   ** Check if the max time to execute after key off has expired.
   ** --------------------------------------------------------------------*/
   if (Fuel03KeyOffSampleMaxTimer >= Fuel03KeyOffSampleTimeNVM)
   {
      SETBIT( Fuel03SenderA.MoreFilterFlags, FUEL03_KEY_OFF_SAMPLES_DONE );

      return;
   }
   Fuel03KeyOffSampleMaxTimer++;
#endif

   /* ----------------------------------------
   ** VALID CONDITION ?
   ** --------------------------------------*/
   if( FUEL03_VALID_CONDITION == FALSE )
   {
#if FUEL03_RAM_LOG_FAULT_RECORD_SIZE > 0
#if FUEL03_LOG_invalid_condition==1
      fuel03_invalid_condition |= FUEL03_KEYOFF_PROCESSING_2;
#endif
#endif
   }
   if( FUEL03_VALID_CONDITION != FALSE )
   {
      Fuel03SenderA.rad = fuel03_rada;                      /* Store, */
      fuel03_test_sample();                 /* Test,  */
      fuel03_debounce_open_short();         /* and Debounce the sender(s)
      for open/short conditions. */
      fuel03_average_rad_processing();     /* pmorris3_08_17_04 was missing */
      fuel03_key_off_sample_processing();

      return;
   }

   return;
#endif

}
#endif
/*============================================================================
**
**  Function Name:      void fuel03_periodic_processing(UINT16 fuel03_rada,
**                                                      BOOLEAN fuel03_jam_filter)
**
**  Visibility:         External
**
**  Description:        This function handles fuel inits and normal/fast mode
**                      filtering of the fuel sender(s).
**
**  Requirments:        Figure 3.6.4-2 Fuel BDS
**
**  INPUTS/OUTPUTS
**
**  Input Arguments:    rada - latest ratioed fuel sample for the SENDER A module.
**                      jam_filter - TRUE if filter(s) should be jammed with
**                                   the latest sample(s)
**
**  Output Arguments:   None
**
**  Critical Section:   None
**
**  Created:            05/07/03 by RRUSS1
**
**  Updated:            08/27/03 by RRUSS1
**                      02/27/07 by JARUN for BSDI00038410
**                      10/09/09 by KNAGASUB for optimization review comments
**                      01/28/10 by BVIJAYKU for QAC fix
**==========================================================================*/
void fuel03_periodic_processing(UINT16 fuel03_rada, BOOLEAN fuel03_jam_filter)
{
#ifdef FUEL03_IGN_STATUS
   if( fuel03_ignition_status != FUEL03_KEYON )
   {
      fuel03_ignition_status = FUEL03_KEYON;
      fuel03_ignition_cycle_counter++;
   }
#endif

   /* ----------------------------------------------------------------------
   ** FUEL KEY ON DELAY COUNTER = 0 ?
   ** ----------------------------------------------------------------------
   ** After the ignition switch transitions, wait a specific amount of
   ** time before taking initialization samples.
   ** --------------------------------------------------------------------*/
   if( Fuel03KeyOnDelayCounter != 0 )
   {
      Fuel03KeyOnDelayCounter--;
      Fuel03InitDelayCounter = Fuel03InitDelayCounterNVM;
      return;
   }

#ifdef FUEL03_SCEM_NUMBER_OF_FUEL_TANKS
   fuel03_get_tank_config();
#endif

   /* ----------------------------------------------------------------------
   ** A Fuel Init = 1 ?
   ** ----------------------------------------------------------------------
   ** Take samples until the fuel init period has expired, and then do
   ** a one-time fuel init.
   ** --------------------------------------------------------------------*/
   if( FUEL03_NOTTESTBIT(Fuel03SenderA.MoreFilterFlags, FUEL03_INIT_FLAG) )
   {
      if( Fuel03InitDelayCounter != 0 )
      {
         /* ----------------------------------------------------------------------
         ** Count down the timer while we are taking samples.
         ** --------------------------------------------------------------------*/
         Fuel03InitDelayCounter--;

         /* ----------------------------------------
         ** VALID CONDITION ?
         ** --------------------------------------*/
         if( FUEL03_VALID_CONDITION() == FALSE )
         {
#if FUEL03_RAM_LOG_FAULT_RECORD_SIZE > 0
#if FUEL03_LOG_invalid_condition==1
            fuel03_invalid_condition |= FUEL03_PERIODIC_PROCESSING_1;
#endif
#endif
         }

         if( FUEL03_VALID_CONDITION() != FALSE )
         {
            Fuel03SenderA.rad = fuel03_rada;                      /* Store, */
            fuel03_test_sample();                 /* Test,  */
            fuel03_debounce_open_short();         /* and Debounce the sender(s) */
#ifdef FUEL03_NEED_DTC_LOGGING
            fuel03_log_dtcs();
#endif
            /* ----------------------------------------------------------------------
            ** Process the rad's into the key on samples.
            ** --------------------------------------------------------------------*/
            fuel03_key_on_samples();

         }
      }
      else
      {
         fuel03_init_avgflps_calc();     /* Fuel Filter Init - AVGFLPS Figure 3.6.4-6   */
         fuel03_ref_fuel_calc();         /* RFUEL Figure 3.6.4-8                        */

         if( FUEL03_NOTTESTBIT(Fuel03SenderA.MoreFilterFlags, FUEL03_INIT_FLAG) )
         {
            fuel03_filter_initialize();  /* Fuel Init Processing Fig 3.6.4-10           */
         }


#if FUEL03_RAM_LOG_FAULT_RECORD_SIZE > 0
         fuel03_log_init_errors_to_ram();
#endif
#ifdef FUEL03_RC_FILL_ENABLED
         fuel03_level_calculation();               /* Fuel Level Calc     Fig 3.6.4-18       */
#endif
#ifdef  FUEL03_SLOSH_HYS
         fuel03_level_calculation_with_hys();      /* Fuel Level Hys Calc Fig 3.6.4-19       */
#endif


      }
      return;
   }
   else   /* fuel init finished */
   {
#if (FUEL03_REF_AVG_TYPE==4)
      if( Fuel03State != FUEL03_KEYON )
      {
         fuel03_koc_setup();
         Fuel03State = FUEL03_KEYON;
      }
#endif

      #ifdef FUEL03_NEED_FILTER_BYPASS_AT_IGN_START
      /* ----------------------------------------------------------------------
      ** Allow an external macro to bypass processing if true.
      ** --------------------------------------------------------------------*/
      if( FUEL03_POWER_MODE_MACRO() != FALSE )
      {
         return;
      }
    #endif
      /* ----------------------------------------
      ** VALID CONDITION ?
      ** --------------------------------------*/
      if( FUEL03_VALID_CONDITION() == FALSE )
      {
#if FUEL03_RAM_LOG_FAULT_RECORD_SIZE > 0
#if FUEL03_LOG_invalid_condition==1
         fuel03_invalid_condition |= FUEL03_PERIODIC_PROCESSING_2;

#endif
#endif
         return;
      }


      Fuel03SenderA.rad = fuel03_rada;                      /* Store, */
      fuel03_test_sample();                 /* Test,  */
      fuel03_debounce_open_short();         /* and Debounce the sender(s) */
      fuel03_average_rad_processing();

      fuel03_fast_fill_enable_check();   /* Fast FIll Enable Check Figure 3.6.4-11     */
#ifdef FUEL03_FFRC_ENABLE
      fuel03_fast_fill_rate_check();
#endif
      fuel03_fast_fill_determination();  /* Fast FIll Figure 3.6.4-12                  */


      /* -----------------
      ** TANK A
      ** ---------------*/
      if( TESTBIT(Fuel03SenderA.FilterFlags, (FUEL03_SENDER_OPEN | FUEL03_SENDER_SHORTED)) )
      {
         Fuel03SenderA.rflps = FUEL03_PERCENT_FULL_INVALID_BYTE;           /* RFLPS = 0xff           */
         Fuel03SenderA.KeyOffRef = FUEL03_PERCENT_FULL_INVALID_BYTE;       /* KEY OFF REF = 0xff     */

#if (FUEL03_REF_AVG_TYPE==4)
         if(TESTBIT(Fuel03SenderA.FilterFlags, (FUEL03_SAMPLE_OPEN_BIT | FUEL03_SAMPLE_SHORT_BIT)))
         {
#if (FUEL03_FILTER_RES==1)
            Fuel03SenderA.flps = 0;
#else
            Fuel03PercentFull = 0;
#endif
            fuel03_slosh_filter( fuel03_jam_filter );

         }
#endif
      }
      else
      {

            #if (FUEL03_AVG_TYPE == 0)
         if((TESTBIT(Fuel03SenderA.FilterFlags, (FUEL03_SAMPLE_OPEN_BIT | FUEL03_SAMPLE_SHORT_BIT))) )
         {
         }
         else
         {
            Fuel03SenderA.flps = fuel03_rad_to_flps( Fuel03SenderA.avg_rad );
            Fuel03SenderA.rflps = Fuel03SenderA.flps;
#if (FUEL03_REF_AVG_TYPE==4)
            Fuel03SenderA.KeyOffRef = FUEL03_PERCENT_FULL_INVALID_BYTE;
#else
            Fuel03SenderA.KeyOffRef = Fuel03SenderA.rflps;
#endif
            fuel03_fast_fill_samples();
            fuel03_slosh_filter( fuel03_jam_filter );
         }
            #else

         Fuel03SenderA.flps = fuel03_rad_to_flps( Fuel03SenderA.avg_rad );
         Fuel03SenderA.rflps = Fuel03SenderA.flps;
#if (FUEL03_REF_AVG_TYPE==4)
         Fuel03SenderA.KeyOffRef = FUEL03_PERCENT_FULL_INVALID_BYTE;
#else
         Fuel03SenderA.KeyOffRef = Fuel03SenderA.rflps;
#endif
         fuel03_fast_fill_samples();
         fuel03_slosh_filter( fuel03_jam_filter );
            #endif
      }
#ifdef FUEL03_HILL_HOLD_ENABLE
      /* ----------------------------------------------------------------------
      ** HILL_HOLD_ENABLE = 1 ?
      ** --------------------------------------------------------------------*/

      if( TESTBIT(Fuel03OptionsNVM, FUEL03_HILL_HOLD_ENABLE_BIT) )
      {
         /* do nothing   */
      }
      else
#endif
         {
         Fuel03SenderA.KeyOffRef = FUEL03_PERCENT_FULL_INVALID_BYTE;
      }

      fuel03_ref_fuel_calc();                   /* RFUEL               Fig 3.6.4-8        */
#ifdef FUEL03_RC_FILL_ENABLED
      fuel03_level_calculation();               /* Fuel Level Calc     Fig 3.6.4-18       */
#endif
#ifdef  FUEL03_SLOSH_HYS
      fuel03_level_calculation_with_hys();      /* Fuel Level Hys Calc Fig 3.6.4-19       */
#endif

#if FUEL03_LOG_FAULT_RECORD_SIZE > 0
      fuel03_log_init_errors_to_nvm();
#endif

      /*
      ** Log DTCs for open/shorted sender(s).
      */
#ifdef FUEL03_NEED_DTC_LOGGING
      fuel03_log_dtcs();
#endif
   }
}

/*============================================================================
**
**  Function Name:      UINT8 fuel03_open_short_test(UINT16 fuel03_sample)
**
**  Visibility:         Internal
**
**  Description:        A function to determine if the latest fuel sample is
**                      open or shorted.
**
**  Requirments:        Figure 3.6.4-3 Fuel BDS
**
**  INPUTS/OUTPUTS
**
**  Input Arguments:    fuel_sample - latest fuel sample RAD
**
**  Output Arguments:   FUEL03_SAMPLE_OPEN - if sample is open
**                      FUEL03_SAMPLE_SHORTED - if sample is short
**                      FUEL03_SAMPLE_OK - if sample is not open or short
**
**  Critical Section:   None
**
**  Created:            07/23/03 by RRUSS1
**
**  Updated:            08/27/03 by RRUSS1
**                      01/28/10 by BVIJAYKU
**==========================================================================*/
static UINT8 fuel03_open_short_test(UINT16 fuel03_sample)
{
   UINT8 fuel03_ret_val = FUEL03_SAMPLE_OK;
   /*
   ** Compare the current with the NVM limits to determine if open or
   ** shorted.  Note that the comparisons are ">" and "<" (not ">=" or
   ** "<=").  This will allow disabling of detection of either or both
   ** short/open by setting the NVM appropriately.
   */
#ifndef FUEL03_SCEM_NUMBER_OF_FUEL_TANKS
   if (fuel03_sample >= Fuel03A2DShortLimNVM)
   {
      fuel03_ret_val = FUEL03_SAMPLE_SHORTED;
   }
   else if (fuel03_sample <= Fuel03A2DOpenLimNVM) /* added 'else' 2/18/2004 rruss1 */
   {
      fuel03_ret_val = FUEL03_SAMPLE_OPEN;
   }
   else /* added 'else {}' 2/18/2004 rruss1 */
   {
   }

#else
   if (fuel03_sample < Fuel03A2DShortLimNVM[Fuel03TankIndex])
   {
      fuel03_ret_val = FUEL03_SAMPLE_SHORTED;
   }
   else if (fuel03_sample > Fuel03A2DOpenLimNVM[Fuel03TankIndex]) /* added 'else' 2/18/2004 rruss1 */
   {
      fuel03_ret_val = FUEL03_SAMPLE_OPEN;
   }
   else /* added 'else {}' 2/18/2004 rruss1 */
   {
   }
#endif

   return( fuel03_ret_val );
}

/*============================================================================
**
**  Function Name:      void fuel03_test_sample( void )
**
**  Visibility:         Internal
**
**  Description:        Routine to test the current fuel sample for open/
**                      short.
**
**  Requirements:       Figure 3.6.4-3 Fuel BDS
**
**  INPUTS/OUTPUTS
**
**  Input Arguments:    fuel03_flt - fuel filter pointer
**
**  Output Arguments:   None
**
**  Critical Section:   None
**
**  Created:            07/23/03 by RRUSS1
**
**  Updated:            08/27/03 by RRUSS1
**                      01/28/10 by BVIJAYKU
**==========================================================================*/
static void fuel03_test_sample( void )
{
   UINT8 fuel03_temp;

   /*
   ** Get status of current sample (OPEN, SHORT, or OK).
   */
   fuel03_temp = fuel03_open_short_test(Fuel03SenderA.rad);

   if (fuel03_temp == FUEL03_SAMPLE_OK)
   {
      /*
      ** Clear the open/short sample flags since the sample is good.
      */
      CLEARBIT(Fuel03SenderA.FilterFlags, (FUEL03_SAMPLE_OPEN_BIT | FUEL03_SAMPLE_SHORT_BIT));
   }
   else if (fuel03_temp == FUEL03_SAMPLE_OPEN)
   {
      /*
      ** Set/clear the appropriate open/short flags.
      */
      SETBIT(Fuel03SenderA.FilterFlags, FUEL03_SAMPLE_OPEN_BIT);
      CLEARBIT(Fuel03SenderA.FilterFlags, FUEL03_SAMPLE_SHORT_BIT);
   }
   else
   {
      /*
      ** Set/clear the appropriate open/short flags.
      */
      SETBIT(Fuel03SenderA.FilterFlags, FUEL03_SAMPLE_SHORT_BIT);
      CLEARBIT(Fuel03SenderA.FilterFlags, FUEL03_SAMPLE_OPEN_BIT);
   }
}


/*============================================================================
**
**  Function Name:      void fuel03_debounce_open_short( void )
**
**  Visibility:         Internal
**
**  Description:        Routine to debounce the sender for open or short
**                      conditions.
**
**  Requirments:        Figure 3.6.4-3 Fuel BDS
**
**  INPUTS/OUTPUTS
**
**  Input Arguments:    fuel03_flt - fuel filter pointer
**
**  Output Arguments:   None
**
**  Critical Section:   None
**
**  Created:            07/23/03 by RRUSS1
**
**  Updated:            08/27/03 by RRUSS1
**                      02/27/07 by JARUN   BSDI00038410
**                      01/28/10 by BVIJAYKU for QAC fix
**==========================================================================*/
static void fuel03_debounce_open_short( void )
{
   bool fl_Inst_Debounce_Flag;
   /*
   ** Check if current sample is open/short.
   */
   if (TESTBIT(Fuel03SenderA.FilterFlags, (FUEL03_SAMPLE_OPEN_BIT | FUEL03_SAMPLE_SHORT_BIT)))
   {
      /*
      ** Check if the sender has already been declared open/short or not.
      */
      fl_Inst_Debounce_Flag = Swc_Get_Inst_Debounce_Flag_Status();

      if(fl_Inst_Debounce_Flag != FALSE)
      {
         Fuel03SenderA.FuelFaultCounter = 0;

         Swc_Clear_Inst_Debounce_Flag_Status();
      }

      if (TESTBIT(Fuel03SenderA.FilterFlags, (FUEL03_SENDER_OPEN | FUEL03_SENDER_SHORTED)))
      {
         /* ** Reset the recovery counter to the max. */
         fuel03_fault_recovery_counter();
      }
      else
      {
         /*
         ** Debounce toward an open/shorted sender.
         */
         if (Fuel03SenderA.FuelFaultCounter != (UINT16)0 )
         {
            (Fuel03SenderA.FuelFaultCounter)--;
         }
         else
         {
            /*
            ** Note that since open/short are not debounced independently,
            ** the sample could oscillate between open/short.  If this happens,
            ** the last sample taken when the debounce counter expires will
            ** determine which DTC is logged.
            */
            if (TESTBIT(Fuel03SenderA.FilterFlags, FUEL03_SAMPLE_OPEN_BIT))
            {
               SETBIT(Fuel03SenderA.FilterFlags, FUEL03_SENDER_OPEN);
               CLEARBIT(Fuel03SenderA.FilterFlags, FUEL03_SENDER_SHORTED);
            }
            else
            {
               CLEARBIT(Fuel03SenderA.FilterFlags, FUEL03_SENDER_OPEN);
               SETBIT(Fuel03SenderA.FilterFlags, FUEL03_SENDER_SHORTED);
            }

            /*
            ** Set the flag to force a fuel init when the sender recovers.
            */
            SETBIT( Fuel03SenderA.MoreFilterFlags, FUEL03_FORCE_FUEL_INIT_FLAG );

            /*
            ** Reset debounce counter to the max debounce time.
            */
            fuel03_fault_counter();
         }
      }

      return;
   }

   /*
   ** If we are here, the current sample is good.  If the sender has been
   ** declared open/short, debounce toward a valid fuel sender.
   */
   if (TESTBIT(Fuel03SenderA.FilterFlags, (FUEL03_SENDER_OPEN | FUEL03_SENDER_SHORTED)))
   {
      if (Fuel03SenderA.FuelFaultRecoveryCounter != (UINT16)0 )
      {
         (Fuel03SenderA.FuelFaultRecoveryCounter)--;
      }
      else
      {
         CLEARBIT(Fuel03SenderA.FilterFlags, (FUEL03_SENDER_OPEN | FUEL03_SENDER_SHORTED));
         fuel03_fault_recovery_counter();


#ifdef FUEL03_FF_RECOV_FLTR_JAM_ENABLE
         Fuel03SenderA.flps = fuel03_rad_to_flps( Fuel03SenderA.avg_rad );
         Fuel03SenderA.slosh_filter = (UINT32)Fuel03SenderA.flps << 24u;
#ifdef  FUEL03_SLOSH_HYS
         Fuel03SenderA.slosh_filter_hys = Fuel03SenderA.slosh_filter;
#endif
#endif
      }

      return;
   }

   /*
   ** Reset debounce counter to the max debounce time.
   */
   fuel03_fault_counter();
   fuel03_fault_recovery_counter();
}

/*============================================================================
**
**  Function Name:      UINT8 fuel03_rad_to_flps(UINT16 fuel03_rad)
**
**  Visibility:         Internal
**
**  Description:        Routine to calculate the fuel percent full.
**
**  Requirments:        Figure 3.6.4-5 Fuel BDS
**
**  INPUTS/OUTPUTS
**
**  Input Arguments:    *fuel03_flt - fuel filter structure pointer,
**                      fuel03_rad - latest RAD
**
**  Output Arguments:   1 byte percent full value.
**
**  Critical Section:   None
**
**  Created:            07/23/03 by RRUSS1
**
**  Updated:            04/10/06 by RRUSS1    BSDI00030114
**
**==========================================================================*/
static UINT8 fuel03_rad_to_flps(UINT16 fuel03_rad)
{
   /* --------------------------------------------------------------------
   ** Use the linear interpolation algorithm to convert from A/D to percent
   ** full.
   ** ------------------------------------------------------------------*/
#ifdef FUEL03_SCEM_NUMBER_OF_FUEL_TANKS
   Fuel03PercentFull = LinearInterpolateWord((UINT16 *)&Fuel03Sender_A_TableNVM[Fuel03TankIndex][0][0], fuel03_rad);
#else
#if FUEL03_NUM_FUEL_TABLES==1
    Fuel03PercentFull = LinearInterpolateWord((UINT16 *)&Fuel03Sender_A_TableNVM[0][0],fuel03_rad);
#else
   Fuel03PercentFull = LinearInterpolateWord((UINT16 *)&Fuel03Sender_A_TableNVM[0][0][0], fuel03_rad);
#endif
#endif
  
   return(FUEL03_MS_8_BITS(Fuel03PercentFull));
}

/*============================================================================
**
**  Function Name:      void fuel03_key_on_samples( void )
**
**  Visibility:         Internal
**
**  Description:        This function provides the fuel key on sample processing.
**
**  Requirments:        Figure 3.6.4-6 Fuel BDS
**
**  INPUTS/OUTPUTS
**
**  Input Arguments:    None
**
**  Output Arguments:   None
**
**  Critical Section:   None
**
**  Created:            05/09/03 by RRUSS1
**
**  Updated:            07/10/03 by RRUSS1
**
**==========================================================================*/
static void fuel03_key_on_samples( void )
{
   /* ----------------------------------------------------------------------
   ** Only add to the sum and increment the good sample counter if the current
   ** sample is not open/short.
   ** --------------------------------------------------------------------*/
   if (FUEL03_NOTTESTBIT(Fuel03SenderA.FilterFlags, (FUEL03_SAMPLE_OPEN_BIT | FUEL03_SAMPLE_SHORT_BIT)))
   {
      Fuel03SenderA.keyon_radsum += Fuel03SenderA.rad;
      Fuel03SenderA.keyon_good_samples++;
   }

}
/*============================================================================
**
**  Function Name:      void fuel03_init_avgflps_calc(void)
**
**  Visibility:         Internal
**
**  Description:        Perform the one time fuel filter initialization after
**                      the appropriate time.
**
**  Requirments:        Figure 3.6.4-7 Fuel BDS
**
**  INPUTS/OUTPUTS
**
**  Input Arguments:    None.
**
**  Output Arguments:   Fuel filter RAM updated if necessary.
**
**  Critical Section:   None
**
**  Created:            07/10/03 by RRUSS1
**
**  Updated:            07/01/14 by RAGARWA1
**
**==========================================================================*/
static void fuel03_init_avgflps_calc(void)
{
  UINT32 fuel03_temp32;

  /****************/
  /* (1) Sender A */
  /****************/

  /* --------------------------------------------------------------------
  ** (2) # GOOD x = 0?
  ** ------------------------------------------------------------------*/
  if( Fuel03SenderA.keyon_good_samples != 0 )
  {
    /* -------------------------------------------------------------
          ** (3) Clear x Fuel Fault detected flag
          ** -----------------------------------------------------------*/
    CLEARBIT(Fuel03SenderA.FilterFlags, (FUEL03_SENDER_OPEN | FUEL03_SENDER_SHORTED ));


    /* --------------------------------------------------------------------
       ** (4) # GOOD X >= FUEL03_INIT_GOOD_SAMPLES_REGUIRED?
       ** --------------------------------------------------------------------
       ** If we didn't get the minimum required good samples for Sender A,
       ** fuel init is finished.
       ** ------------------------------------------------------------------*/
    if( Fuel03SenderA.keyon_good_samples < Fuel03InitGoodSamplesReqNVM )
    {
  #if FUEL03_LOG_FAULT_RECORD_SIZE > 0
      Fuel03SenderA.log_nvm_data = 1; /* rruss1_08_26_04 : added */
  #endif

  #if (FUEL03_REF_AVG_TYPE==4)/* added as per BSDI00058764*/
      Fuel03_AVG_Vol_Invalid_Counter++;
  #endif

      /* -------------------------------------------------------------
            ** (14) Cold Init flag = 1 ?
            ** -------------------------------------------------------------
            ** Note that (8)(9)(10) are not evaluated here because we are
            ** just doing A at this time.
            ** -----------------------------------------------------------*/
      if (TESTBIT(Fuel03Flags, FUEL03_COLD_INIT))
      {
        /* -------------------------------------------------------------
                 ** (15) Set x Force Fuel Init flag = 1
                 ** -----------------------------------------------------------*/
        SETBIT(Fuel03SenderA.MoreFilterFlags, FUEL03_FORCE_FUEL_INIT_FLAG);
      }

      /* -------------------------------------------------------------
            ** (16) x Fuel Init = 1
            ** -----------------------------------------------------------*/
      SETBIT(Fuel03SenderA.MoreFilterFlags, FUEL03_INIT_FLAG);
  #ifdef  FUEL03_NEED_PID_C90A
      /* -------------------------------------------------------------
            ** (17) INIT_PID_x = 0x01, 0xFF
            ** -----------------------------------------------------------*/
      Fuel03SenderA.init_pid = 0x01ff;
  #endif

    }
    else /* Y part of (4), i.e. got the req. good samples */
    {
      /* -------------------------------------------------------------
            ** (5) AVG RAD x = SUM RAD x / * GOOD x
            ** -----------------------------------------------------------*/
      /* QAC warning / error begin*************************************************
            **
            ** The following line of code generates QAC warning / error 2832 (MISRA Rule 21.1).
            ** It has been reviewed by Bhaguluri, Sashidhar on 02/09/13 and deemed acceptable
            ** because it is necessary to perform division. Added fuel03_KSNvRamCheck to check
            ** FUEL03_INIT_GOOD_SAMPLES_REQUIRED is zero or not in fuel03.c.
            ** QAC warning / error end**************************************************/

      fuel03_temp32 = Fuel03SenderA.keyon_radsum / ((UINT16)(Fuel03SenderA.keyon_good_samples));

      Fuel03SenderA.avg_rad = (UINT16)fuel03_temp32; /* added 9/17/2004 rruss1 */

      /* -------------------------------------------------------------
            ** (6) AVG RAD x to AVGFLPS x
            ** -----------------------------------------------------------*/
      Fuel03SenderA.keyon_avgflps = fuel03_rad_to_flps((UINT16)fuel03_temp32);
    }
  }
  else
  {
    #if FUEL03_LOG_FAULT_RECORD_SIZE > 0
    Fuel03SenderA.log_nvm_data = 1; /* rruss1_08_26_04 : added */
    #endif

    #if (FUEL03_REF_AVG_TYPE==4)/* added as per BSDI00058764*/
    Fuel03_AVG_Vol_Invalid_Counter++;
    #endif

    /* -------------------------------------------------------------
          ** (14) Cold Init flag = 1 ?
          ** -------------------------------------------------------------
          ** Note that (8)(9)(10) are not evaluated here because we are
          ** just doing A at this time.
          ** -----------------------------------------------------------*/
    if (TESTBIT(Fuel03Flags, FUEL03_COLD_INIT))
    {
      /* -------------------------------------------------------------
               ** (15) Set x Force Fuel Init flag = 1
               ** -----------------------------------------------------------*/
      SETBIT(Fuel03SenderA.MoreFilterFlags, FUEL03_FORCE_FUEL_INIT_FLAG);
    }

    /* -------------------------------------------------------------
          ** (16) x Fuel Init = 1
          ** -----------------------------------------------------------*/
    SETBIT(Fuel03SenderA.MoreFilterFlags, FUEL03_INIT_FLAG);
    #ifdef  FUEL03_NEED_PID_C90A
    /* -------------------------------------------------------------
          ** (17) INIT_PID_x = 0x01, 0xFF
          ** -----------------------------------------------------------*/
    Fuel03SenderA.init_pid = 0x01ff;
    #endif

  }
}

/*============================================================================
**
**  Function Name:      void fuel03_ref_fuel_calc( void )
**
**  Visibility:         Internal
**
**  Description:        A function to calculate the weighted average
**                      for sender A and B.
**
**  Requirments:        Figure 3.6.4-9 Fuel BDS
**
**  INPUTS/OUTPUTS
**
**  Input Arguments:    None.
**
**  Output Arguments:   None.
**
**  Critical Section:   None
**
**  Created:            07/10/03 by RRUSS1
**
**  Updated:            03/03/05 by RRUSS1
**
**==========================================================================*/
static void fuel03_ref_fuel_calc( void )
{
   Fuel03SenderA.rfuel = (UINT8)(Fuel03SenderA.slosh_filter >> 24u);
}

/*============================================================================
**
**  Function Name:      void fuel03_finit_t3( void )
**
**  Visibility:         Internal
**
**  Description:        Helper function for Fuel Init.
**
**  Requirments:        Figure 3.6.4-11 Fuel BDS
**
**  INPUTS/OUTPUTS
**
**  Input Arguments:    None.
**
**  Output Arguments:   None.
**
**  Critical Section:   None
**
**  Created:            07/23/03 by RRUSS1
**
**  Updated:            11/21/03 by RRUSS1
**
**==========================================================================*/
static void fuel03_finit_t3( void )
{

   /* -------------------------------------------------------------
   ** (17) x Force Fuel Init flag = 0
   ** -----------------------------------------------------------*/
   CLEARBIT( Fuel03SenderA.MoreFilterFlags, FUEL03_FORCE_FUEL_INIT_FLAG );

   /* -------------------------------------------------------------
   ** (18) SLOSH FILT x = AVGFLPS x MSB
   ** -----------------------------------------------------------*/
   Fuel03SenderA.slosh_filter = (UINT32)Fuel03SenderA.keyon_avgflps << 24u;
#ifdef  FUEL03_SLOSH_HYS
   /* -------------------------------------------------------------
   ** (19) FILT HYS x = AVGFLPS x MSB
   ** -----------------------------------------------------------*/
   Fuel03SenderA.slosh_filter_hys = Fuel03SenderA.slosh_filter;
#endif

}

/*============================================================================
**
**  Function Name:      void fuel03_finit_F3( void )
**
**  Visibility:         Internal
**
**  Description:        Helper function for Fuel Init.
**
**  Requirments:        Figure 3.6.4-11 Fuel BDS
**
**  INPUTS/OUTPUTS
**
**  Input Arguments:    None.
**
**  Output Arguments:   None.
**
**  Critical Section:   None
**
**  Created:            08/31/04 by RRUSS1
**
**  Updated:            08/31/04 by RRUSS1
**
**==========================================================================*/
static void fuel03_finit_F3( void )
{

#ifndef FUEL03_SCEM_NUMBER_OF_FUEL_TANKS
   if( (Fuel03SenderA.keyon_avgflps - Fuel03SenderA.rfuel) > Fuel03SecPosInitFillDeltaNVM_A )
   {
#else
      if( (Fuel03SenderA.keyon_avgflps - Fuel03SenderA.rfuel) > Fuel03SecPosInitFillDeltaNVM_A[Fuel03TankIndex] )
      {
#endif
         SETBIT( Fuel03SenderA.FilterFlags, FUEL03_FILL_DETECTED );
#ifdef  FUEL03_NEED_PID_C90A
         Fuel03SenderA.init_pid |= (UINT16)0x8000u;
#endif
#if FUEL03_LOG_FAULT_RECORD_SIZE > 0
         Fuel03SenderA.log_nvm_data = TRUE;
#endif

         fuel03_finit_t3();

         return;
      }
#ifndef FUEL03_SCEM_NUMBER_OF_FUEL_TANKS
      if( (Fuel03SenderA.rfuel - Fuel03SenderA.keyon_avgflps) > Fuel03SecNegInitFillDeltaNVM_A )
      {
#else
         if( (Fuel03SenderA.rfuel - Fuel03SenderA.keyon_avgflps) > Fuel03SecNegInitFillDeltaNVM_A[Fuel03TankIndex] )
         {
#endif
            SETBIT( Fuel03SenderA.FilterFlags, FUEL03_LOSS_DETECTED );
#ifdef  FUEL03_NEED_PID_C90A
            Fuel03SenderA.init_pid |= (UINT16)0x8000u;
#endif
#if FUEL03_LOG_FAULT_RECORD_SIZE > 0
            Fuel03SenderA.log_nvm_data = TRUE;
#endif

            fuel03_finit_t3();

            return;
         }
         else
         {
            CLEARBIT( Fuel03SenderA.FilterFlags, FUEL03_LOSS_DETECTED );
            CLEARBIT( Fuel03SenderA.FilterFlags, FUEL03_FILL_DETECTED );
         }
      }

/*============================================================================
**
**  Function Name:      void fuel03_fi_compare( void )
**
**  Visibility:         Internal
**
**  Description:        Helper function for Fuel Init.
**
**  Requirments:        Figure 3.6.4-11 Fuel BDS
**
**  INPUTS/OUTPUTS
**
**  Input Arguments:    None.
**
**  Output Arguments:   None.
**
**  Critical Section:   None
**
**  Created:            07/23/03 by RRUSS1
**
**  Updated:            11/19/03 by RRUSS1
**
**==========================================================================*/
static void fuel03_fi_compare( void )
{

         /* --------------------------------------------------------------------
         ** (22) (INIT REF x MSB - AVGFLPS x MSB) > NEGATIVE_INIT_FILL_DELTA_x ?
         ** ------------------------------------------------------------------*/
         if( Fuel03SenderA.init_ref > Fuel03SenderA.keyon_avgflps )
         {

#ifndef FUEL03_SCEM_NUMBER_OF_FUEL_TANKS
            if( (Fuel03SenderA.init_ref - Fuel03SenderA.keyon_avgflps) > Fuel03NegativeInitFill_A_NVM )
#else
               if( (Fuel03SenderA.init_ref - Fuel03SenderA.keyon_avgflps) > Fuel03NegativeInitFill_A_NVM[Fuel03TankIndex])
#endif
                  {
                  /* -------------------------------------------------------------
                  ** (23) x Fuel Lose Detected Flag = 1
                  ** -----------------------------------------------------------*/
                  SETBIT( Fuel03SenderA.FilterFlags, FUEL03_LOSS_DETECTED );

                  fuel03_finit_t3();

                  return;
               }
         }
         else /* N part of (22) */
         {
            /* --------------------------------------------------------------------
            ** (24) (AVGFLPS x MSB - INIT REF x MSB) > POSITIVE_INIT_FILL_DELTA_x ?
            **      or
            ** (25) ( RFUEL x > RENTAL_CAR_FILL_THRESHOLD_x
            **      and
            ** (26)   (AVGFLPS x MSB - INIT REF x MSB) > RENTAL_CAR_FILL_DELTA_x ? )
            ** ------------------------------------------------------------------*/
#ifndef FUEL03_SCEM_NUMBER_OF_FUEL_TANKS
            if( ( (Fuel03SenderA.keyon_avgflps - Fuel03SenderA.init_ref) > Fuel03PositiveInitFill_A_NVM)
#else
               if( ( (Fuel03SenderA.keyon_avgflps - Fuel03SenderA.init_ref) > Fuel03PositiveInitFill_A_NVM[Fuel03TankIndex])
#endif
#ifdef FUEL03_RC_FILL_ENABLED
                  ||( (Fuel03SenderA.rfuel > Fuel03SenderA.rc_fill_threshold) &&
                  ((Fuel03SenderA.keyon_avgflps - Fuel03SenderA.init_ref) > Fuel03SenderA.rc_fill_delta))
#endif
                  )
               {
                  /* -------------------------------------------------------------
                  ** (27) x Fuel Fill Detected Flag = 1
                  ** -----------------------------------------------------------*/
                  SETBIT( Fuel03SenderA.FilterFlags, FUEL03_FILL_DETECTED );

                  fuel03_finit_t3();

                  return;
               }
         }

         fuel03_finit_F3();
}

/*============================================================================
**
**  Function Name:      void fuel03_fi_check( void )
**
**  Visibility:         Internal
**
**  Description:        Helper function for Fuel Init.
**
**  Requirments:        Figure 3.6.4-11 Fuel BDS
**
**  INPUTS/OUTPUTS
**
**  Input Arguments:    None.
**
**  Output Arguments:   None.
**
**  Critical Section:   None
**
**  Created:            07/23/03 by RRUSS1
**
**  Updated:            08/30/04 by RRUSS1
**
**==========================================================================*/
static void fuel03_fi_check( void )
{
         /* -------------------------------------------------------------
         ** (3) x Force Fuel Init flag = 1?
         ** -----------------------------------------------------------*/
         if( TESTBIT( Fuel03SenderA.MoreFilterFlags, FUEL03_FORCE_FUEL_INIT_FLAG ) )
         {
#ifdef  FUEL03_NEED_PID_C90A
            /* -------------------------------------------------------------
            ** (4)(28) INIT_PID_x = 03,0xff
            ** -----------------------------------------------------------*/
            Fuel03SenderA.init_pid = 0x03ff;
#endif

            /* -------------------------------------------------------------
            ** (27) x Fuel FIll Detected Flag = 1
            ** -----------------------------------------------------------*/
            SETBIT( Fuel03SenderA.FilterFlags, FUEL03_FILL_DETECTED );

            fuel03_finit_t3();

            return;

         }

         /* -------------------------------------------------------------
         ** (5) ZSS REF x = 0xFF ?
         ** -----------------------------------------------------------*/
         if( Fuel03SenderA.zss_ref != FUEL03_PERCENT_FULL_INVALID_BYTE )
         {
            /* -------------------------------------------------------------
            ** (9) INIT REF x = ZSS REF x
            ** -----------------------------------------------------------*/
            Fuel03SenderA.init_ref = Fuel03SenderA.zss_ref;
#ifdef  FUEL03_NEED_PID_C90A
            /* -------------------------------------------------------------
            ** (10) INIT_PID_x = 04, xx xx = ZSS REF x
            ** -----------------------------------------------------------*/
            Fuel03SenderA.init_pid = 0x0400 + (UINT16)Fuel03SenderA.zss_ref;
#endif
            fuel03_fi_compare();

            return;
         }

         /* -------------------------------------------------------------
         ** (8) KEY OFF REF x = 0xFF ?
         ** -----------------------------------------------------------*/
         if( Fuel03SenderA.KeyOffRef != FUEL03_PERCENT_FULL_INVALID_BYTE )
         {
            /* -------------------------------------------------------------
            ** (9) INIT REF x = KEY OFF REF x
            ** -----------------------------------------------------------*/
            Fuel03SenderA.init_ref = Fuel03SenderA.KeyOffRef;
#ifdef  FUEL03_NEED_PID_C90A
            /* -------------------------------------------------------------
            ** (10) INIT_PID_x = 05, xx xx = ZSS REF x
            ** -----------------------------------------------------------*/
            Fuel03SenderA.init_pid = 0x0500 + (UINT16)Fuel03SenderA.KeyOffRef;
#endif

            fuel03_fi_compare();

            return;
         }
#ifdef FUEL03_HILL_HOLD_ENABLE
         /* -------------------------------------------------------------
         ** (11) HILL_HOLD_ENABLE = 1 ?
         ** -----------------------------------------------------------*/
         if( TESTBIT( Fuel03OptionsNVM, FUEL03_HILL_HOLD_ENABLE_BIT ) )
         {

            #if( FUEL03_FORCE_FILT_JAM == 1 )
            
#if (FUEL03_REF_AVG_TYPE==4)
               if( Fuel03SenderA.koc_fault_flag != FALSE )
#endif
                  {
                  /* -------------------------------------------------------------
                  ** (14) x Fuel FIll Detected Flag = 1
                  ** -----------------------------------------------------------*/
                  SETBIT( Fuel03SenderA.FilterFlags, FUEL03_FILL_DETECTED );
#ifdef  FUEL03_NEED_PID_C90A
                  Fuel03SenderA.init_pid = 0x02ff;
#endif

                  fuel03_finit_t3();

                  return;
               }

#if (FUEL03_REF_AVG_TYPE==4)
               else
               {
#ifdef  FUEL03_NEED_PID_C90A
                  Fuel03SenderA.init_pid  = 0x07ff;
#endif

                  fuel03_finit_F3();
                  return;

               }
#endif
            #else
            
#ifdef  FUEL03_NEED_PID_C90A
               Fuel03SenderA.init_pid  = 0x07ff;
#endif

               fuel03_finit_F3();

               return;
            #endif
         }
         else
         {
#endif
            /* -------------------------------------------------------------
            ** (12) INIT REF x = RFUEL x
            ** -----------------------------------------------------------*/
            Fuel03SenderA.init_ref = Fuel03SenderA.rfuel;
#ifdef  FUEL03_NEED_PID_C90A
            /* -------------------------------------------------------------
            ** (13) INIT_PID_x = 06, RFUEL x
            ** -----------------------------------------------------------*/
            Fuel03SenderA.init_pid = 0x0600 + (UINT16)Fuel03SenderA.rfuel;
#endif

            fuel03_fi_compare();

            return;
#ifdef FUEL03_HILL_HOLD_ENABLE
         }
#endif
}

/*============================================================================
**
**  Function Name:      void fuel03_filter_initialize( void )
**
**  Visibility:         Internal
**
**  Description:        Fuel filter initialization function.
**
**  Requirments:        Figure 3.6.4-11 Fuel BDS
**
**  INPUTS/OUTPUTS
**
**  Input Arguments:    None.
**
**  Output Arguments:   None.
**
**  Critical Section:   None
**
**  Created:            07/23/03 by RRUSS1
**
**  Updated:            07/26/04 by RRUSS1
**
**==========================================================================*/
static void fuel03_filter_initialize( void )
{
         /* -------------------------------------------------------------
         ** (2) Cold init flag = 0
         ** -----------------------------------------------------------*/
         CLEARBIT( Fuel03Flags, FUEL03_COLD_INIT );

         /* -------------------------------------------------------------
         ** (1) Tank Processing = A
         ** -----------------------------------------------------------*/
         if( FUEL03_NOTTESTBIT(Fuel03SenderA.MoreFilterFlags, FUEL03_INIT_FLAG))
         {
            fuel03_fi_check();
            /* -------------------------------------------------------------
            ** x Fuel Init = 1
            ** -----------------------------------------------------------*/
            SETBIT( Fuel03SenderA.MoreFilterFlags, FUEL03_INIT_FLAG );
#if (FUEL03_REF_AVG_TYPE==4)
            Fuel03SenderA.koc_converged = FALSE;
#endif

         }


}

      /*============================================================================
**
**  Function Name:      void fuel03_fast_fill_enable_check_subf1()
**
**  Visibility:         Internal
**
**  Description:        Helper function for Fast fill enable check.
**
**  Requirments:        Figure 3.6.4-12 Fuel BDS
**
**  INPUTS/OUTPUTS
**
**  Input Arguments:    None
**
**  Output Arguments:   None
**
**  Critical Section:   None
**
**  Created:            02/15/05 by RRUSS1
**
**  Updated:            02/15/05 by RRUSS1
**
**==========================================================================*/
#if (FUEL03_REF_AVG_TYPE==4)
      static void fuel03_fast_fill_enable_check_subf1( void  )
      {
         if(FUEL03_NOTTESTBIT(Fuel03SenderA.FilterFlags, (FUEL03_SENDER_OPEN | FUEL03_SENDER_SHORTED)) )
         {

            if( Fuel03SenderA.zs_converged == FALSE )
            {
               fuel03_ffsc();
               if( Fuel03SenderA.zs_converged == FALSE )
               {
                  Fuel03SenderA.zss_ref = FUEL03_PERCENT_FULL_INVALID_BYTE;
                  CLEARBIT( Fuel03SenderA.MoreFilterFlags, FUEL03_FAST_FILL_FLAG );
               }
            }
         }
      }
#endif
/*============================================================================
**
**  Function Name:      void fuel03_fast_fill_enable_check(void)
**
**  Visibility:         Internal
**
**  Description:        Fast fill enable check.
**
**  Requirments:        Figure 3.6.4-12 Fuel BDS
**
**  INPUTS/OUTPUTS
**
**  Input Arguments:    None
**
**  Output Arguments:   None
**
**  Critical Section:   None
**
**  Created:            05/08/03 by RRUSS1
**
**  Updated:            19/11/08 by KNAGASUB
**                      01/28/10 by BVIJAYKU for QAC fix
**==========================================================================*/
static void fuel03_fast_fill_enable_check( void )
{
#if (FUEL03_REF_AVG_TYPE==4)
         if( Fuel03_AVG_Vol_Invalid_Counter != 0 )
         {
            if( Fuel03_AVG_Vol_Invalid_Counter >= FUEL03_AVG_VOL_INVALID_TIME )
            {
               Fuel03_AVG_Vol_Invalid_Counter = 0;
            }
            else
            {
               Fuel03_AVG_Vol_Invalid_Counter++;
               return;
            }
         }
         if( FUEL03_FAST_FILL_MET_MACRO() == FALSE )
         {
            Fuel03SenderA.zss_ref = FUEL03_PERCENT_FULL_INVALID_BYTE;
            CLEARBIT( Fuel03SenderA.MoreFilterFlags, FUEL03_FAST_FILL_FLAG );

            if( Fuel03SenderA.zs_converged != FALSE )
            {
               fuel03_fdelta_normal_base();
            }
            Fuel03SenderA.zs_converged = FALSE;
            Fuel03SenderA.ConvCycleCounter = 0;
            Fuel03SenderA.SmplCounter = 0;
         }
         else
         {
            fuel03_fast_fill_enable_check_subf1();
         }
#else
         if( TESTBIT(Fuel03OptionsNVM, FUEL03_FAST_FILL_ENABLE_BIT))
         {
            /* -------------------------------------------------------------
            ** Check if the fast fill conditions have been met. The
            ** application is responsible for defining what they are and
            ** returns FALSE if not.
            ** -----------------------------------------------------------*/
            if( FUEL03_FAST_FILL_MET_MACRO() != FALSE )
            {
               if( Fuel03ZeroSpeedCounter != (UINT16)0 )
               {
                  Fuel03ZeroSpeedCounter--;
                  return;
               }
               else
               {
                  if( TESTBIT(Fuel03SenderA.FilterFlags, (FUEL03_SENDER_OPEN | FUEL03_SENDER_SHORTED)) )
                  {
                     fuel03_fdelta_normal_base();
                  }
                  else
                  {
                     return;
                  }
               }
            }
            else
            {
               if( Fuel03ZeroSpeedCounter == (UINT16)0 )
               {
                  /* -------------------------------------------------------------
                  ** FDELTA A = FDELTA BASE A
                  ** FDELTA B = FDELTA BASE B
                  ** -----------------------------------------------------------*/
                  fuel03_fdelta_normal_base();
               }
            }
         }

         Fuel03ZeroSpeedCounter = Fuel03ZeroSpeedCounterNVM;

         Fuel03SenderA.zss_ref = FUEL03_PERCENT_FULL_INVALID_BYTE;

         CLEARBIT( Fuel03SenderA.MoreFilterFlags, FUEL03_FAST_FILL_FLAG );
#endif
}

/*============================================================================
**
**  Function Name:      void fast_fill_determination_f1( void )
**
**  Visibility:         Internal
**
**  Description:        Helper function in Fast fill enable check.
**
**  Requirments:        Figure 3.6.4-14 Fuel BDS
**
**  INPUTS/OUTPUTS
**
**  Input Arguments:    None
**
**  Output Arguments:   None
**
**  Critical Section:   None
**
**  Created:            07/11/03 by RRUSS1
**
**  Updated:            07/12/04 by RRUSS1
**                      03/30/07 by JARUN
**                      01/28/10 by BVIJAYKU
**==========================================================================*/
static void fast_fill_determination_f1( void )
{
         if( TESTBIT( Fuel03SenderA.MoreFilterFlags, FUEL03_FAST_FILL_FLAG ) )
         {
         }
         else
         {
            /* Check if FUEL03_MIN_FAST_FILL_TIME elasped */
            if( Fuel03MinFastFillTimeCounter == 0)
            {
               SETBIT( Fuel03SenderA.MoreFilterFlags, FUEL03_FAST_FILL_FLAG );
               fuel03_fdelta_fast_base();
               fuel03_fdelta_base();
            }
            else
            {
               Fuel03MinFastFillTimeCounter--;
            }
         }
}

/*============================================================================
**
**  Function Name:      void fuel03_fast_fill_determination( void )
**
**  Visibility:         Internal
**
**  Description:        Fast fill enable check.
**
**  Requirments:        Figure 3.6.4-14 Fuel BDS
**
**  INPUTS/OUTPUTS
**
**  Input Arguments:    None
**
**  Output Arguments:   None
**
**  Critical Section:   None
**
**  Created:            07/11/03 by RRUSS1
**
**  Updated:            07/12/04 by RRUSS1
**                      03/30/07 by JARUN
**==========================================================================*/
static void fuel03_fast_fill_determination( void )
{
         UINT8 delta_ref;
#if (FUEL03_REF_AVG_TYPE==4)
         if( Fuel03_AVG_Vol_Invalid_Counter != 0 )
         {

            if( TESTBIT( Fuel03SenderA.MoreFilterFlags, FUEL03_FAST_FILL_FLAG ) )
            {

            }
            else
            {
               SETBIT( Fuel03SenderA.MoreFilterFlags, FUEL03_FAST_FILL_FLAG );
               fuel03_fdelta_fast_base();
               fuel03_fdelta_base();
            }
            return;
         }
#endif
         /* -------------------------------------------------------------
         ** Check if the fast fill conditions have been met. The
         ** -----------------------------------------------------------*/
         if( Fuel03SenderA.zss_ref != FUEL03_PERCENT_FULL_INVALID_BYTE )
         {
            if( Fuel03SenderA.rflps == FUEL03_PERCENT_FULL_INVALID_BYTE )
            {
               CLEARBIT( Fuel03SenderA.MoreFilterFlags, FUEL03_FAST_FILL_FLAG );
               Fuel03MinFastFillTimeCounter = Fuel03FastFillTimeCounterNVM;
               return;
            }
            else
            {
#ifdef FUEL03_FFRC_ENABLE
               if( Fuel03SenderA.rate_check_passed == FALSE )
               {
                  Fuel03MinFastFillTimeCounter = Fuel03FastFillTimeCounterNVM;
                  return;
               }
               delta_ref = Fuel03SenderA.ffrc_delta_ref;
#else
               delta_ref = Fuel03SenderA.zss_ref;
#endif
               /* -------------------------------------------------------------
               ** Check for a positive fill delta.
               ** -----------------------------------------------------------*/
               if( Fuel03SenderA.rflps >= delta_ref )
               {
#ifndef FUEL03_SCEM_NUMBER_OF_FUEL_TANKS
                  if ( (Fuel03SenderA.rflps - delta_ref) > Fuel03PositiveFastFill_A_NVM )
                  {
#else
                     if ( (Fuel03SenderA.rflps - delta_ref) > Fuel03PositiveFastFill_A_NVM[Fuel03TankIndex] )
                     {
#endif
                        fast_fill_determination_f1();
                        return;
                     }
                  }

                  /* -------------------------------------------------------------
                  ** Check for a negative fill delta.
                  ** -----------------------------------------------------------*/
                  if( delta_ref >= Fuel03SenderA.rflps )
                  {
#ifndef FUEL03_SCEM_NUMBER_OF_FUEL_TANKS
                     if ( (delta_ref - Fuel03SenderA.rflps) > Fuel03NegativeFastFill_A_NVM )
#else
                        if ( (delta_ref - Fuel03SenderA.rflps) > Fuel03NegativeFastFill_A_NVM[Fuel03TankIndex] )
#endif
                           {

                              fast_fill_determination_f1();
                              return;
                           }
                  }
#ifdef FUEL03_RC_FILL_ENABLED
                  fuel03_level_calculation();

                  /* -------------------------------------------------------------
                  ** Check if the Rental Car Fill Threshold has been exceeded.
                  ** -----------------------------------------------------------*/
                  if(FUEL03_MS_8_BITS(fuel03_level) > Fuel03SenderA.rc_fill_threshold )
                  {
                     if ( (Fuel03SenderA.rflps - Fuel03SenderA.zss_ref) > Fuel03SenderA.rc_fill_delta )
                     {
                        fast_fill_determination_f1();
                        return;
                     }
                  }
#endif
               }
            }
            /* ----------------------------------------------------------------------
            ** Set the Min fast fill time counter to default value.
            ** --------------------------------------------------------------------*/
         Fuel03MinFastFillTimeCounter = Fuel03FastFillTimeCounterNVM;
}

/*============================================================================
**
**  Function Name:      void fuel03_fast_fill_samples( void )
**
**  Visibility:         Internal
**
**  Description:        Fast fill samples.
**
**  Requirments:        Figure 3.6.4-15 Fuel BDS
**
**  INPUTS/OUTPUTS
**
**  Input Arguments:    None
**
**  Output Arguments:   None
**
**  Critical Section:   None
**
**  Created:            05/08/03 by RRUSS1
**
**  Updated:            05/08/03 by RRUSS1
**                      02/27/07 by JARUN for BSDI00038410
**                      01/28/10 by BVIJAYKU for QAC fix
**==========================================================================*/
static void fuel03_fast_fill_samples( void )
{
#if (FUEL03_REF_AVG_TYPE==4)
            {
               return;
            }
#else
            if( Fuel03SenderA.zss_ref == FUEL03_PERCENT_FULL_INVALID_BYTE )
            {
               if( Fuel03ZeroSpeedCounter != (UINT16)0 )
               {
                  return;
               }
               Fuel03SenderA.zss_ref = Fuel03SenderA.rflps;

#ifdef FUEL03_FFRC_ENABLE
               Fuel03SenderA.rate_check_sample[0] = Fuel03SenderA.zss_ref;
#endif

            }
#endif
}

/*============================================================================
**
**  Function Name:      void fuel03_slosh_filter(BOOLEAN fuel03_live_mode )
**
**  Visibility:         Internal
**
**  Description:        Routine to filter slosh from the fuel sender.
**                      error recovery or not.
**
**  Requirments:        Figure 3.6.4-17 Fuel BDS
**
**  INPUTS/OUTPUTS
**
**  Input Arguments:    fuel03_flt - fuel filter pointer
**                      fuel03_live_mode - TRUE: jam filter, FALSE: do not
**
**  Output Arguments:   None
**
**  Critical Section:   None
**
**  Created:            07/17/03 by RRUSS1
**
**  Updated:            04/10/06 by RRUSS1   BSDI00030114
**                      06/02/10 by JARUN
**==========================================================================*/
static void fuel03_slosh_filter(BOOLEAN fuel03_live_mode )
{
            UINT32 fuel03_local_clamp;

#ifdef  FUEL03_SLOSH_HYS
UINT16 LocalFullPos16;
#endif
#ifdef FUEL03_EOL_LIVE
            if( fuel03_live_mode == 1 )
            {
               Fuel03SenderA.slosh_filter = ((UINT32)Fuel03SenderA.flps) << 24u;
#ifdef  FUEL03_SLOSH_HYS
               Fuel03SenderA.slosh_filter_hys = Fuel03SenderA.slosh_filter; /* added 9/22/04 rruss1 */
#endif
            }
            else
#endif
            {
               /* -------------------------------------------------------------
               ** Check the fast fill flag (x Fast Fill flag = 1?)
               ** -----------------------------------------------------------*/
               if( TESTBIT( Fuel03SenderA.MoreFilterFlags, FUEL03_FAST_FILL_FLAG ) )
               {
                  fuel03_fdelta_fast_base();
#ifdef FUEL03_SCEM_NUMBER_OF_FUEL_TANKS
                  Fuel03SenderA.fdelta_adjust_base = FUEL03_DELTA_FAST_ADJUST_A_NVM[Fuel03TankIndex];
                  fuel03_local_clamp = FUEL03_DELTA_FAST_CLAMP_A_NVM[Fuel03TankIndex];
#else
                  Fuel03SenderA.fdelta_adjust_base = FUEL03_DELTA_FAST_ADJUST_A_NVM;
                  fuel03_local_clamp = FUEL03_DELTA_FAST_CLAMP_A_NVM;
#endif
               }
               else
               {
                  fuel03_fdelta_base_and_adjust_nvm();
#ifdef FUEL03_SCEM_NUMBER_OF_FUEL_TANKS
                  fuel03_local_clamp = FUEL03_DELTA_NORMAL_CLAMP_A_NVM[Fuel03TankIndex];
#else
                  fuel03_local_clamp = FUEL03_DELTA_NORMAL_CLAMP_A_NVM;
#endif
               }
               /* -------------------------------------------------------------
               ** FLPS x > SLOSH FILT x MSB ?
               ** -------------------------------------------------------------
               ** If the current sample is above the filter, check if the
               ** previous sample was above as well.  If so, add an adjustment
               ** factor to the delta to be added to the filter.  Similarly,
               ** if the current and previous samples were both below the
               ** filter, add the adjustment factor.  Make sure to clamp the
               ** delta at the limits from the config file.
               ** -----------------------------------------------------------*/
#if (FUEL03_FILTER_RES==1)
               if( Fuel03SenderA.flps > ((UINT8)(Fuel03SenderA.slosh_filter >> 24u)))
#else
               if( Fuel03PercentFull > ((UINT16)(Fuel03SenderA.slosh_filter >> 16u)))
#endif
                  {
                     /* -------------------------------------------------------------
                     ** x < flag = 0     Clear the sample is below filter flag.
                     ** -----------------------------------------------------------*/
                     CLEARBIT(Fuel03SenderA.FilterFlags, FUEL03_SAMPLE_IS_BELOW_FILTER);

                     /* -------------------------------------------------------------
                     ** x > flag = 1 ?
                     ** -----------------------------------------------------------*/
                     if( TESTBIT(Fuel03SenderA.FilterFlags, FUEL03_SAMPLE_IS_ABOVE_FILTER) )
                     {
                        /* -------------------------------------------------------------
                        ** FDELTA x = FDELTA x + FDELTA ADJUST BASE x
                        ** -----------------------------------------------------------*/
                        Fuel03SenderA.fdelta += Fuel03SenderA.fdelta_adjust_base;

                        /* -------------------------------------------------------------
                        ** Clamp FDELTA x to 3 bytes
                        ** -----------------------------------------------------------*/
                        if (Fuel03SenderA.fdelta > fuel03_local_clamp)
                        {
                           Fuel03SenderA.fdelta = fuel03_local_clamp;
                        }
#ifdef  FUEL03_ERR_CNT
                        Fuel03SenderA.err_counter++;
#endif
                     }
                     else
                     {
                        /* -------------------------------------------------------------
                        ** FDELTA x = FDELTA BASE x
                        ** -----------------------------------------------------------*/
                        fuel03_fdelta_base();

                        /* -------------------------------------------------------------
                        ** x > flag = 1     Set the flag indicating that the sample
                        **                  is above the slosh filter value.
                        ** -----------------------------------------------------------*/
                        SETBIT(Fuel03SenderA.FilterFlags, FUEL03_SAMPLE_IS_ABOVE_FILTER);
#ifdef  FUEL03_ERR_CNT
                        Fuel03SenderA.err_counter = 0;
#endif
                     }

                     /* -------------------------------------------------------------
                     ** SLOSH FILT x = SLOSH FILT x + FDELTA x
                     ** -----------------------------------------------------------*/
                     Fuel03SenderA.slosh_filter += Fuel03SenderA.fdelta;
                  }
                  /* -------------------------------------------------------------
                  ** FLPS x < SLOSH FILT x MSB ?
                  ** -----------------------------------------------------------*/
                  /*
                  ** If the current sample is above the filter, check if the
                  ** previous sample was above as well.  If so, add an adjustment
                  ** factor to the delta to be added to the filter.  Similarly,
                  ** if the current and previous samples were both below the
                  ** filter, add the adjustment factor.  Make sure to clamp the
                  ** delta at the limits from the config file.
                  */
#if (FUEL03_FILTER_RES==1)
                  else if( Fuel03SenderA.flps < ((UINT8)(Fuel03SenderA.slosh_filter >> 24u)))
#else
                     else if( Fuel03PercentFull < ((UINT16)(Fuel03SenderA.slosh_filter >> 16u)))
#endif
                        {
                        /* -------------------------------------------------------------
                        ** x > flag = 0     Clear the sample is above filter flag.
                        ** -----------------------------------------------------------*/
                        CLEARBIT(Fuel03SenderA.FilterFlags, FUEL03_SAMPLE_IS_ABOVE_FILTER);

                        /* -------------------------------------------------------------
                        ** x < flag = 1 ?
                        ** -----------------------------------------------------------*/
                        if( TESTBIT(Fuel03SenderA.FilterFlags, FUEL03_SAMPLE_IS_BELOW_FILTER) )
                        {
                           /* -------------------------------------------------------------
                           ** FDELTA x = FDELTA x + FDELTA ADJUST BASE x
                           ** -----------------------------------------------------------*/
                           Fuel03SenderA.fdelta += Fuel03SenderA.fdelta_adjust_base;

                           /* -------------------------------------------------------------
                           ** Clamp FDELTA x to 3 bytes
                           ** -----------------------------------------------------------*/
                           if (Fuel03SenderA.fdelta > fuel03_local_clamp)
                           {
                              Fuel03SenderA.fdelta = fuel03_local_clamp;
                           }
#ifdef  FUEL03_ERR_CNT
                           Fuel03SenderA.err_counter++;
#endif
                        }
                        else
                        {
                           /* -------------------------------------------------------------
                           ** FDELTA x = FDELTA BASE x
                           ** -----------------------------------------------------------*/
                           fuel03_fdelta_base();

                           /* -------------------------------------------------------------
                           ** x < flag = 1     Set the flag indicating that the sample
                           **                  is below the slosh filter value.
                           ** -----------------------------------------------------------*/
                           SETBIT(Fuel03SenderA.FilterFlags, FUEL03_SAMPLE_IS_BELOW_FILTER);
#ifdef  FUEL03_ERR_CNT
                           Fuel03SenderA.err_counter = 0;
#endif
                        }

                        /* -------------------------------------------------------------
                        ** SLOSH FILT x = SLOSH FILT x + FDELTA x
                        ** -----------------------------------------------------------*/
                        if( Fuel03SenderA.slosh_filter > Fuel03SenderA.fdelta )
                        {
                           Fuel03SenderA.slosh_filter -= Fuel03SenderA.fdelta;
                        }
                        else
                        {
                           Fuel03SenderA.slosh_filter = 0;
                        }
                     }
                     else
                     {
                        /* -------------------------------------------------------------
                        ** x > flag = 0     Clear the sample is above filter flag.
                        ** x < flag = 0     Clear the sample is below filter flag.
                        ** -----------------------------------------------------------*/
                        CLEARBIT(Fuel03SenderA.FilterFlags, FUEL03_SAMPLE_IS_ABOVE_FILTER);
                        CLEARBIT(Fuel03SenderA.FilterFlags, FUEL03_SAMPLE_IS_BELOW_FILTER);

                        fuel03_fdelta_base();
                     }


            }
#ifdef  FUEL03_SLOSH_HYS
#ifdef FUEL03_SCEM_NUMBER_OF_FUEL_TANKS
            LocalFullPos16 = Fuel03PercentFullPosHystNVM[Fuel03TankIndex];
#else
            LocalFullPos16 = Fuel03PercentFullPosHystNVM;
#endif

            /* -------------------------------------------------------------
            ** Else perform hysteresis on the percent full data.
            ** -----------------------------------------------------------*/
            if( Fuel03SenderA.slosh_filter > Fuel03SenderA.slosh_filter_hys )
            {
               if( FUEL03_MS_16_BITS(Fuel03SenderA.slosh_filter - Fuel03SenderA.slosh_filter_hys) > LocalFullPos16 )
               {
                  Fuel03SenderA.slosh_filter_hys = Fuel03SenderA.slosh_filter;
               }
            }
            else
            {
#ifdef FUEL03_SCEM_NUMBER_OF_FUEL_TANKS
               LocalFullPos16 = Fuel03PercentFullNegHystNVM[Fuel03TankIndex];
#else
               LocalFullPos16 = Fuel03PercentFullNegHystNVM;
#endif
               if( FUEL03_MS_16_BITS(Fuel03SenderA.slosh_filter_hys - Fuel03SenderA.slosh_filter) > LocalFullPos16 )
               {
                  Fuel03SenderA.slosh_filter_hys = Fuel03SenderA.slosh_filter;
               }
            }
#endif
#ifdef  FUEL03_ERR_CNT
            if( Fuel03SenderA.err_counter > (UINT16)FUEL03_ERR_CNT )
            {
#if FUEL03_LOG_FAULT_RECORD_SIZE > 0
               Fuel03SenderA.log_nvm_data = TRUE;
#endif
               Fuel03SenderA.err_counter = 0;  /* added 9/22/04 rruss1 */
            }
#endif

}
#ifdef FUEL03_RC_FILL_ENABLED

/*============================================================================
**
**  Function Name:      void fuel03_level_calculation( void )
**
**  Visibility:         Internal
**
**  Description:        Routine to calculate the fuel level.
**
**  Requirments:        Figure 3.6.4-20 Fuel BDS
**
**  INPUTS/OUTPUTS
**
**  Input Arguments:    None
**
**  Output Arguments:   None
**
**  Critical Section:   None
**
**  Created:            07/17/03 by RRUSS1
**
**  Updated:            02/23/05 by RRUSS1
**  updated:            08/04/08 by KNAGASUB
**==========================================================================*/
static void fuel03_level_calculation( void )
{
#if (FUEL03_REF_AVG_TYPE!=4)

            if( TESTBIT(Fuel03SenderA.FilterFlags, (FUEL03_SENDER_OPEN | FUEL03_SENDER_SHORTED) ) )
            {
               fuel03_level = (UINT16)0xffffu;
            }
            else
            {
#endif
               fuel03_level = FUEL03_MS_16_BITS(Fuel03SenderA.slosh_filter);

#if (FUEL03_REF_AVG_TYPE!=4)
            }
#endif
}
#endif
#ifdef  FUEL03_SLOSH_HYS
/*============================================================================
**
**  Function Name:      void fuel03_level_calculation_with_hys( void )
**
**  Visibility:         Internal
**
**  Description:        Routine to calculate the fuel level with hysteresis.
**
**  Requirments:        Figure 3.6.4-21 Fuel BDS
**
**  INPUTS/OUTPUTS
**
**  Input Arguments:    None
**
**  Output Arguments:   None
**
**  Critical Section:   None
**
**  Created:            09/12/03 by RRUSS1
**
**  Updated:            09/12/03 by RRUSS1
**                      01/28/10 by BVIJAYKU
**==========================================================================*/
static void fuel03_level_calculation_with_hys( void )
{
      fuel03_level_with_hys = FUEL03_MS_16_BITS(Fuel03SenderA.slosh_filter_hys);
}
#endif
/*============================================================================
**
**  Function Name:      UINT16 fuel03_get_fuel_level( void )
**
**  Visibility:         External
**
**  Description:        Routine to return the single or combined percent full
**                      value of both senders with hysteresis.
**
**  INPUTS/OUTPUTS
**
**  Input Arguments:    None
**
**  Output Arguments:   None
**
**  Critical Section:   None
**
**  Created:            09/12/03 by RRUSS1
**
**  Updated:            09/12/03 by RRUSS1
**                      02/26/07 by JARUN for BSDI00038410
**
**==========================================================================*/
UINT16 fuel03_get_fuel_level(void)
{
     return( FUEL03_MS_16_BITS(Fuel03SenderA.slosh_filter) );
}

#ifdef  FUEL03_SLOSH_HYS
/*============================================================================
**
**  Function Name:      UINT16 fuel03_get_fuel_level_with_hys( void )
**
**  Visibility:         External
**
**  Description:        Routine to return the single or combined percent full
**                      value of both senders with hysteresis.
**
**  INPUTS/OUTPUTS
**
**  Input Arguments:    None
**
**  Output Arguments:   Senders  percent full with hysteresis.
**
**  Critical Section:   None
**
**  Created:            09/12/03 by RRUSS1
**
**  Updated:            09/12/03 by RRUSS1
**
**==========================================================================*/
UINT16 fuel03_get_fuel_level_with_hys(void)
{
     fuel03_level_with_hys =  FUEL03_MS_16_BITS(Fuel03SenderA.slosh_filter_hys);
     return(fuel03_level_with_hys );
}

/*============================================================================
**
**  Function Name:      UINT16 fuel03_get_senderA_PFH(void)
**
**  Visibility:         External
**
**  Description:        Routine to return the percent full value with
**                      hysteresis of sender A.
**
**  INPUTS/OUTPUTS
**
**  Input Arguments:    None.
**
**  Output Arguments:   Sender A percent full with hysteresis.
**
**  Critical Section:   None
**
**  Created:            09/12/03 by RRUSS1
**
**  Updated:            09/12/03 by RRUSS1
**
**==========================================================================*/
UINT16 fuel03_get_senderA_PFH(void)
{
       fuel03_level_with_hys =  FUEL03_MS_16_BITS(Fuel03SenderA.slosh_filter_hys);
       return ( fuel03_level_with_hys );
}
#endif
/*============================================================================
**
**  Function Name:      UINT16 fuel03_get_senderA_PF(void)
**
**  Visibility:         External
**
**  Description:        Routine to return the percent full value without
**                      hysteresis of sender A.
**
**  INPUTS/OUTPUTS
**
**  Input Arguments:    None.
**
**  Output Arguments:   Sender A percent full without hysteresis.
**
**  Critical Section:   None
**
**  Created:            09/12/03 by RRUSS1
**
**  Updated:            09/12/03 by RRUSS1
**
**==========================================================================*/
UINT16 fuel03_get_senderA_PF(void)
{
   return ( FUEL03_MS_16_BITS(Fuel03SenderA.slosh_filter) );
}

/*============================================================================
**
**  Function Name:      BOOLEAN fuel03_init_finished(void)
**
**  Visibility:         External
**
**  Description:        Routine to determine if fuel init is finished.
**
**  INPUTS/OUTPUTS
**
**  Input Arguments:    None
**
**  Output Arguments:   TRUE - fuel init finished
**                      FALSE - fuel init not finished
**
**  Critical Section:   None
**
**  Created:            09/16/03 by RRUSS1
**
**  Updated:            09/16/03 by RRUSS1
**
**==========================================================================*/
BOOLEAN fuel03_init_finished(void)
{
      BOOLEAN fuel03_retval;

      fuel03_retval = FALSE;

      if( TESTBIT(Fuel03SenderA.MoreFilterFlags, FUEL03_INIT_FLAG) )
      {
          fuel03_retval = TRUE;
      }

      return( fuel03_retval );
}
#ifdef FUEL03_AD_NETWORK
/*============================================================================
**
**  Function Name:      void fuel03_network_message_missing(void)
**
**  Visibility:         External
**
**  Description:        Routine to set the key-off reference sample to
**                      invalid when the network message containing
**                      the RAD samples is missing.  Since the function
**                      is so small, it isn't conditionally compiled
**                      out on non-network systems.
**
**  INPUTS/OUTPUTS
**
**  Input Arguments:    None
**
**  Output Arguments:   None
**
**  Critical Section:   None
**
** Created:            09/17/03 by RRUSS1
**
**  Updated:            09/17/03 by RRUSS1
**
**==========================================================================*/
void fuel03_network_message_missing(void)
{
     /*
     ** Set the key off reference to invalid.
     */
     Fuel03SenderA.KeyOffRef = FUEL03_PERCENT_FULL_INVALID_BYTE;
}
#endif

/*============================================================================
**
**  Function Name:      BOOLEAN fuel03_fast_fill_active(void)
**
**  Visibility:         External
**
**  Description:        Routine to determine if any sender has fast fill active.
**
**  INPUTS/OUTPUTS
**
**  Input Arguments:    None
**
**  Output Arguments:   TRUE - fast fill active
**                      FALSE - fast fill not active
**
**  Critical Section:   None
**
**  Created:            09/17/03 by RRUSS1
**
**  Updated:            09/17/03 by RRUSS1
**
**==========================================================================*/
BOOLEAN fuel03_fast_fill_active(void)
{
     BOOLEAN fuel03_retval;

     fuel03_retval = FALSE;

     if( TESTBIT( Fuel03SenderA.MoreFilterFlags, FUEL03_FAST_FILL_FLAG ) )
     {
         fuel03_retval = TRUE;
     }

     return(fuel03_retval);
}


/*============================================================================
**
**  Function Name:      UINT8 fuel03_fill_or_loss_status(void)
**
**  Visibility:         External
**
**  Description:        Routine to determine if a fill or loss has been detected. For
**                      single tank systems only Sender A
**                      fill status,loss detected status and normal is returned. For
**                      2 senders, either A or B fill/loss detected is returned.
**
**  INPUTS/OUTPUTS
**
**  Input Arguments:    None
**
**  Output Arguments:   FUEL03_STATUS_FILL - status fill detected
**                      FUEL03_STATUS_LOSS - status loss detected
**                      FUEL03_STATUS_NORMAL - status fill/loss not detected
**
**  Critical Section:   None
**
**  Created:            10/09/09 by KNAGASUB
**
**  Updated:            01/28/10 by BVIJAYKU
**==========================================================================*/
UINT8 fuel03_fill_or_loss_status(void)
{
    UINT8 fuel03_retval;

    if(TESTBIT(Fuel03SenderA.FilterFlags,FUEL03_FILL_DETECTED))
    {
       fuel03_retval = FUEL03_STATUS_FILL;
    }
    else if(TESTBIT(Fuel03SenderA.FilterFlags,FUEL03_LOSS_DETECTED))
    {
       fuel03_retval = FUEL03_STATUS_LOSS;

    }
    else
    {
       fuel03_retval = FUEL03_STATUS_NORMAL;

    }

    return(fuel03_retval);
}

/*============================================================================
**
**  Function Name:      UINT8 fuel03_open_short_status(void)
**
**  Visibility:         External
**
**  Description:        Routine to determine if an status of open/short sender has been
**                      detected on sender A.
**
**  INPUTS/OUTPUTS
**
**  Input Arguments:    None
**
**  Output Arguments:   FUEL03_STATUS_OPEN -- open detected
**                      FUEL03_STATUS_SHORT -- short detected
**                      FUEL03_STATUS_NO_OPEN_NO_SHORT -- open/short not detected
**
**  Critical Section:   None
**
**  Created:            10/09/09 by KNAGASUB
**
**  Updated:            01/28/10 by BVIJAYKU
**==========================================================================*/
UINT8 fuel03_open_short_status(void)
{
            UINT8 fuel03_retval;
#if (FUEL03_REF_AVG_TYPE==4)
#if (FUEL03_FILTER_RES==1)
            UINT8 fuel03_slosh_filter_temp;
            fuel03_slosh_filter_temp = (UINT8)(Fuel03SenderA.slosh_filter >> 24u);
#else
            UINT16 fuel03_slosh_filter_temp;
            fuel03_slosh_filter_temp = (UINT16)(Fuel03SenderA.slosh_filter >> 16u);
#endif
#endif
#if (FUEL03_REF_AVG_TYPE==4)
            if (TESTBIT(Fuel03SenderA.FilterFlags,FUEL03_SENDER_OPEN))
            {
               if (fuel03_slosh_filter_temp == 0)
               {
                  fuel03_retval = FUEL03_STATUS_OPEN;
               }
            }
            else if(TESTBIT(Fuel03SenderA.FilterFlags,FUEL03_SENDER_SHORTED))
            {
               if (fuel03_slosh_filter_temp == 0)
               {
                  fuel03_retval = FUEL03_STATUS_SHORT;
               }
            }
            else
            {
               fuel03_retval = FUEL03_STATUS_NO_OPEN_SHORT;
            }
#else
            if (TESTBIT(Fuel03SenderA.FilterFlags,FUEL03_SENDER_OPEN))
            {
               fuel03_retval = FUEL03_STATUS_OPEN;
            }
            else if(TESTBIT(Fuel03SenderA.FilterFlags,FUEL03_SENDER_SHORTED))
            {
               fuel03_retval = FUEL03_STATUS_SHORT;

            }
            else
            {
               fuel03_retval = FUEL03_STATUS_NO_OPEN_SHORT;
            }

#endif



            return(fuel03_retval);
 }


#ifdef FUEL03_NEED_PID_C903
/*============================================================================
**
**  Function Name:      UINT8 fuel03_C903_KSGetPID(void *buffer)
**
**  Visibility:         External
**
**  Description:        Routine to return the value for PID $C903 -
**                      "fuel sender 1 -- number of good samples".
**
**  INPUTS/OUTPUTS
**
**  Input Arguments:    buffer - pointer to location to store data
**
**  Output Arguments:   1 - the size of the PID
**
**  Critical Section:   None
**
**  Created:            08/06/03 by RRUSS1
**
**  Updated:            08/06/03 by RRUSS1
**
**==========================================================================*/
UINT8 fuel03_C903_KSGetPID(UINT8 *fuel03_buffer)
{
        /*
        ** Store the data in the buffer.
        */
        *fuel03_buffer = Fuel03SenderA.keyon_good_samples;

        /*
        ** Return 1, the size of the PID.
        */
        return(1);
}
#endif


#ifdef FUEL03_NEED_PID_C904
/*============================================================================
**
**  Function Name:      UINT8 fuel03_C904_KSGetPID(void *buffer)
**
**  Visibility:         External
**
**  Description:        Routine to return the value for PID $C904 -
**                      "fuel sender x -- number of good samples required".
**
**  INPUTS/OUTPUTS
**
**  Input Arguments:    buffer - pointer to location to store data
**
**  Output Arguments:   1 - the size of the PID
**
**  Critical Section:   None
**
**  Created:            08/06/03 by RRUSS1
**
**  Updated:            08/06/03 by RRUSS1
**
**==========================================================================*/
UINT8 fuel03_C904_KSGetPID(UINT8 *fuel03_buffer)
{
        /*
        ** Store the data in the buffer.
        */
        *fuel03_buffer = Fuel03InitGoodSamplesReqNVM;

        /*
        ** Return 1, the size of the PID.
        */
        return(1);
}
#endif


#ifdef FUEL03_NEED_PID_C909
/*============================================================================
**
**  Function Name:      UINT8 fuel03_C909_KSGetPID(void *buffer)
**
**  Visibility:         External
**
**  Description:        Routine to return the value for PID $C909 -
**                      "fuel sender 1 -- average of all samples".
**
**  INPUTS/OUTPUTS
**
**  Input Arguments:    buffer - pointer to location to store data
**
**  Output Arguments:   2 - the size of the PID
**
**  Critical Section:   None
**
**  Created:            08/06/03 by RRUSS1
**
**  Updated:            02/23/06 by JARUN for BSDI00038410
**
**==========================================================================*/
UINT8 fuel03_C909_KSGetPID(UINT16 *fuel03_buffer)
{
        UINT16 fuel03_temp;
        UINT8 *p_temp = (UINT8 *)(void *)fuel03_buffer;

        /*
        ** Calculate the average.
        */
        fuel03_temp = (UINT16)(Fuel03SenderA.keyon_radsum / ((UINT16)(Fuel03SenderA.keyon_good_samples)));

        /*
        ** Store the data in the buffer.
        */
        *p_temp = (UINT8)(fuel03_temp>>8);
        p_temp++;
        *p_temp = (UINT8)(fuel03_temp);

        /*
        ** Return 2, the size of the PID.
        */
        return(2);
}
#endif


#ifdef  FUEL03_NEED_PID_C90A
/*============================================================================
**
**  Function Name:      UINT8 fuel03_C90A_KSGetPID(void *buffer)
**
**  Visibility:         External
**
**  Description:        Routine to return the value for PID $C90A -
**                      "fuel init ref -- reference used at init and value".
**
**  INPUTS/OUTPUTS
**
**  Input Arguments:    buffer - pointer to location to store data
**
**  Output Arguments:   2 - the size of the PID
**
**  Critical Section:   None
**
**  Created:            08/06/03 by RRUSS1
**
**  Updated:            02/26/07 by JARUN for BSDI00038410.
**
**==========================================================================*/
UINT8 fuel03_C90A_KSGetPID(UINT16 *fuel03_buffer)
{
      UINT8 *p_temp = (UINT8 *)(void *)fuel03_buffer;
      /*
      ** Store the data in the buffer.
      */
      *p_temp = (UINT8)(Fuel03SenderA.init_pid>>8);
      p_temp++;
      *p_temp = (UINT8)(Fuel03SenderA.init_pid);

      /*
      ** Return 2, the size of the PID.
      */
      return(2);
}
#endif


#ifdef FUEL03_NEED_PID_C90B
/*============================================================================
**
**  Function Name:      UINT8 fuel03_C90B_KSGetPID(void *buffer)
**
**  Visibility:         External
**
**  Description:        Routine to return the value for PID $C90B -
**                      "fuel sender 2 -- number of good samples".
**
**  INPUTS/OUTPUTS
**
**  Input Arguments:    buffer - pointer to location to store data
**
**  Output Arguments:   1 - the size of the PID
**
**  Critical Section:   None
**
**  Created:            08/06/03 by RRUSS1
**
**  Updated:            08/06/03 by RRUSS1
**
**==========================================================================*/
UINT8 fuel03_C90B_KSGetPID(UINT8 *fuel03_buffer)
{
            /*
        ** Store the data in the buffer.
        */
        *fuel03_buffer = 0;

        /*
        ** Return 1, the size of the PID.
        */
        return(1);
}
#endif


#ifdef FUEL03_NEED_PID_C90C
/*============================================================================
**
**  Function Name:      UINT8 fuel03_C90C_KSGetPID(void *buffer)
**
**  Visibility:         External
**
**  Description:        Routine to return the value for PID $C90C -
**                      "fuel sender 2 -- average of all samples".
**
**  INPUTS/OUTPUTS
**
**  Input Arguments:    buffer - pointer to location to store data
**
**  Output Arguments:   2 - the size of the PID
**
**  Critical Section:   None
**
**  Created:            08/06/03 by RRUSS1
**
**  Updated:            02/26/07 by JARUN for BSDI00038410
**                      05/26/08 by CNAGARA1 to remove QAC warning
**
**==========================================================================*/
UINT8 fuel03_C90C_KSGetPID(UINT16 *fuel03_buffer)
{
        UINT16 fuel03_temp;
        UINT8 *p_temp = (UINT8 *)(void *)fuel03_buffer;

        /*
        ** Calculate the average.
        */
        fuel03_temp = 0;

        /*
        ** Store the data in the buffer.
        */
        *p_temp = (UINT8)(fuel03_temp>>8);
        p_temp++;
        *p_temp = (UINT8)(fuel03_temp);

        /*
        ** Return 2, the size of the PID.
        */
        return(2);
}
#endif

#ifdef  FUEL03_NEED_PID_C90D
/*============================================================================
**
**  Function Name:      UINT8 fuel03_C90D_KSGetPID(void *buffer)
**
**  Visibility:         External
**
**  Description:        Routine to return the value for PID $C90D -
**                      "fuel init ref B -- reference used at init and value".
**
**  INPUTS/OUTPUTS
**
**  Input Arguments:    buffer - pointer to location to store data
**
**  Output Arguments:   2 - the size of the PID
**
**  Critical Section:   None
**
**  Created:            12/03/04 by RRUSS1
**
**  Updated:            12/03/04 by RRUSS1
**                      02/26/07 by JARUN for BSDI00038410
**
**==========================================================================*/
UINT8 fuel03_C90D_KSGetPID(UINT16 *fuel03_buffer)
{
      UINT16 fuel03_temp;
      UINT8 *p_temp = (UINT8 *)fuel03_buffer;

      /*
      ** Calculate the average.
      */
      fuel03_temp = 0;

      /*
      ** Store the data in the buffer.
      */
      *p_temp = (UINT8)(fuel03_temp>>8);
      p_temp++;
      *p_temp = (UINT8)(fuel03_temp);

      /*
      ** Return 2, the size of the PID.
      */
      return(2);
}
#endif


#ifdef FUEL03_NEED_PID_6185
/*============================================================================
**
**  Function Name:      UINT8 fuel03_6185_KSGetPID(void *buffer)
**
**  Visibility:         External
**
**  Description:        Routine to calculate and return the value for
**                      PID $6185 - "Fuel Level Analog Input Status #1".
**
**  INPUTS/OUTPUTS
**
**  Input Arguments:    buffer - pointer to location to store data
**
**  Output Arguments:   1 - the size of the PID
**
**  Critical Section:   None
**
**  Created:            08/06/03 by RRUSS1
**
**  Updated:            09/27/05 by RRUSS1     BSDI00025533
**
**==========================================================================*/
UINT8 fuel03_6185_KSGetPID(void *fuel03_buffer)
{
        UINT16 fuel03_temp;

#ifdef FUEL03_SCEM_NUMBER_OF_FUEL_TANKS
        fuel03_get_tank_config();
#endif


        fuel03_temp = FUEL03_GET_LEVEL_SENDER_A();

        /*
        ** If the sender is open or shorted, return INVALID.  Else convert
        ** the A/D to percent full.
        */
        if (fuel03_open_short_test(fuel03_temp) != FUEL03_SAMPLE_OK)
        {
           *((UINT8 *)fuel03_buffer) = FUEL03_PERCENT_FULL_INVALID_BYTE;
        }
        else
        {
           *((UINT8 *)fuel03_buffer) = fuel03_rad_to_flps( fuel03_temp );
        }

        /*
        ** Return 1, the size of the PID.
        */
        return(1);
}
#endif


#ifdef FUEL03_NEED_PID_6187
/*============================================================================
**
**  Function Name:      UINT8 fuel03_6187_KSGetPID(void *buffer)
**
**  Visibility:         External
**
**  Description:        Routine to calculate and return the value for
**                      PID $6187 - "Fuel Level Analog Input Status #2".
**
**  INPUTS/OUTPUTS
**
**  Input Arguments:    buffer - pointer to location to store data
**
**  Output Arguments:   1 - the size of the PID
**
**  Critical Section:   None
**
**  Created:            08/06/03 by RRUSS1
**
**  Updated:            09/27/05 by RRUSS1     BSDI00025533
**
**==========================================================================*/
UINT8 fuel03_6187_KSGetPID(void *fuel03_buffer)
{
        UINT16 fuel03_temp;

        /*
        ** Get the index of the tank being processed from the product specific
        ** code.  This index determines which set of NVM constants to use
        ** when filtering the fuel input(s).
        */
#ifdef FUEL03_SCEM_NUMBER_OF_FUEL_TANKS
        fuel03_get_tank_config();
#endif

        fuel03_temp = 0;

        /*
        ** If the sender is open or shorted, return INVALID.  Else convert
        ** the A/D to percent full.
        */
        if (fuel03_open_short_test(fuel03_temp) != FUEL03_SAMPLE_OK)
        {
           *((UINT8 *)fuel03_buffer) = FUEL03_PERCENT_FULL_INVALID_BYTE;
        }
        else
        {
           *((UINT8 *)fuel03_buffer) = 0;
        }

        /*
        ** Return 1, the size of the PID.
        */
        return(1);
}
#endif


#ifdef FUEL03_NEED_DIAG_SELF_TEST
/*============================================================================
**
**  Function Name:      void fuel03_KSDiagStartSelfTest(void)
**
**  Visibility:         External
**
**  Description:        Execute once when begin self test to check the two
**                      fuel senders for open/short and log DTCs if
**                      necessary.
**
**  INPUTS/OUTPUTS
**
**  Input Arguments:    none
**
**  Output Arguments:   none
**
**  Critical Section:   None
**
**  Created:            08/06/03 by RRUSS1
**
**  Updated:            09/18/03 by RRUSS1
**                      03/03/08 by CNAGARA1 Updated to fix BSDI00054702
**
**==========================================================================*/
void fuel03_KSDiagStartSelfTest(void)
{
      UINT8 fuel03_temp;

      /*
      ** Get the index of the tank being processed from the product specific
      ** code.  This index determines which set of NVM constants to use
      ** when filtering the fuel input(s).
      */
  #ifdef FUEL03_SCEM_NUMBER_OF_FUEL_TANKS
      fuel03_get_tank_config();
  #endif

      /*
      ** Check Sender A for errors and log DTCs.
      */
      fuel03_temp = fuel03_open_short_test( FUEL03_GET_LEVEL_SENDER_A() );

      if (FUEL03_SAMPLE_OPEN == fuel03_temp)
      {
         FUEL03_LOG_FUEL_SENDER_CKT_OPEN();
         FUEL03_CLR_FUEL_SENDER_CKT_SHORT();
      }
      else if(FUEL03_SAMPLE_SHORTED == fuel03_temp)
      {
         FUEL03_LOG_FUEL_SENDER_CKT_SHORT();
         FUEL03_CLR_FUEL_SENDER_CKT_OPEN();
      }
      else
      {
         FUEL03_CLR_FUEL_SENDER_CKT_OPEN();
         FUEL03_CLR_FUEL_SENDER_CKT_SHORT();
      }
}
#endif


#ifdef FUEL03_NEED_DIAG_EPILOG
/*============================================================================
**
**  Function Name:      void fuel03_KSDiagEpilog(void)
**
**  Visibility:         External
**
**  Description:        Diagnostic epilog routine for the fuel gage.  Start
**                      a re-init.
**
**  INPUTS/OUTPUTS
**
**  Input Arguments:    None
**
**  Output Arguments:   None
**
**  Critical Section:   None
**
**  Created:            08/06/03 by RRUSS1
**
**  Updated:            08/06/03 by RRUSS1
**
**==========================================================================*/
void fuel03_KSDiagEpilog(void)
{
        /*
        ** Start a re-init of the fuel gage via the init function to ensure
        ** that all RAM is reset.
        */
        fuel03_setup_for_init();
}
#endif
#ifdef FUEL03_GET_UNFILTER_FLPS
/*============================================================================
**
**  Function Name:      UINT8 fuel03_get_SenderA_unfiltered_flps(void)
**
**  Visibility:         External
**
**  Description:        Return the unfiltered flps.
**
**  INPUTS/OUTPUTS
**
**  Input Arguments:    none
**
**  Output Arguments:   none
**
**  Critical Section:   None
**
**  Created:            02/26/04 by RRUSS1
**
**  Updated:            02/26/04 by RRUSS1
**
**==========================================================================*/
UINT8 fuel03_get_SenderA_unfiltered_flps( void )
{
        return( Fuel03SenderA.flps );
}
#endif
/*============================================================================
**      K E Y O F F   C O N V E R G E N C E
**==========================================================================*/

/*============================================================================
**
**  Function Name:      static void fuel03_koc_f1_setup( void )
**
**  Visibility:         Internal
**
**  Description:        Helper function in Key off convergence algorithm.
**
**  INPUTS/OUTPUTS
**
**  Input Arguments:    none
**
**  Output Arguments:   none
**
**  Critical Section:   None
**
**  Created:            08/04/04 by RRUSS1
**
**  Updated:            08/04/04 by RRUSS1
**                      03/30/09 by jarun
**                      01/28/10 by BVIJAYKU
**==========================================================================*/
#if (FUEL03_REF_AVG_TYPE==4)
static void fuel03_koc_f1_setup( void )
{
        Fuel03SenderA.koc_converged = FALSE;
        /*   Fuel03SenderA.koc_fault_flag = FALSE; */
        Fuel03SenderA.ConvCycleCounter = 0;
        Fuel03SenderA.ConvSample = 0;

        Fuel03SenderA.SmplCounter = 0;
        Fuel03SenderA.sum_vx = 0;
        Fuel03SenderA.min_vx = 0;
        Fuel03SenderA.max_vx = 0;
}

/*============================================================================
**
**  Function Name:      static void fuel03_koc_setup( void )
**
**  Visibility:         Internal
**
**  Description:        Key off convergence algorithm.
**
**  INPUTS/OUTPUTS
**
**  Input Arguments:    none
**
**  Output Arguments:   none
**
**  Critical Section:   None
**
**  Created:            08/04/04 by RRUSS1
**
**  Updated:            08/04/04 by RRUSS1
**                      03/30/09 by jarun
**
**==========================================================================*/
static void fuel03_koc_setup( void )
{
        fuel03_koc_f1_setup();
}
/*============================================================================
**
**  Function Name:      static void fuel03_fault_flag( FUEL03_FLT *fuel03_flt )
**
**  Visibility:         Internal
**
**  Description:        Key off convergence helper function.
**
**  INPUTS/OUTPUTS
**
**  Input Arguments:    none
**
**  Output Arguments:   none
**
**  Critical Section:   None
**
**  Created:            08/04/04 by RRUSS1
**
**  Updated:            08/04/04 by RRUSS1
**
**==========================================================================*/
static void fuel03_fault_flag( void )
{
        if( TESTBIT(Fuel03SenderA.FilterFlags, (FUEL03_SAMPLE_OPEN_BIT | FUEL03_SAMPLE_SHORT_BIT)) )
        {
           Fuel03SenderA.koc_fault_flag = TRUE;
        }
        else
        {
           Fuel03SenderA.koc_fault_flag = FALSE;
        }
}

/*============================================================================
**
**  Function Name:      static void fuel03_koc_f1( void )
**
**  Visibility:         Internal
**
**  Description:        Key off convergence helper function.
**
**  INPUTS/OUTPUTS
**
**  Input Arguments:    none
**
**  Output Arguments:   none
**
**  Critical Section:   None
**
**  Created:            08/04/04 by RRUSS1
**
**  Updated:            08/04/04 by RRUSS1
**                      05/26/08 by CNAGARA1
**
**==========================================================================*/
static void fuel03_koc_f1( void )
{
        Fuel03SenderA.KeyOffRef = (UINT8)(Fuel03SenderA.sum_vx / (UINT16)Fuel03SenderA.ConvSample);
#if FUEL03_LOG_ConvCycleCounter==1
        Fuel03SenderA.KOS_ConvCycleCounter_shadow = Fuel03SenderA.ConvCycleCounter;
#endif
#if FUEL03_LOG_SmplCounter==1
        Fuel03SenderA.KOS_SmplCounter_shadow = Fuel03SenderA.SmplCounter;
#endif

        Fuel03SenderA.ConvCycleCounter = 0;
        Fuel03SenderA.SmplCounter = 0;
        Fuel03SenderA.koc_converged = TRUE;
        fuel03_fault_flag();
}

/*============================================================================
**
**  Function Name:      static void fuel03_koc( void )
**
**  Visibility:         Internal
**
**  Description:        This is the actual Key off convergence algorithm using
**                      the fuel_flt pointer to execute on the individual sender.
**
**  INPUTS/OUTPUTS
**
**  Input Arguments:    none
**
**  Output Arguments:   none
**
**  Critical Section:   None
**
**  Created:            08/04/04 by RRUSS1
**
**  Updated:            08/04/04 by RRUSS1
**                      03/10/08 by CNAGARA1 - BSDI00055424
**
**==========================================================================*/
static void fuel03_koc( void )
{
        UINT8 fuel03_t_delta;

        if( Fuel03SenderA.ConvCycleCounter >= FUEL03_KOS_CYCLES )
        {
           if( Fuel03SenderA.ConvSample >= FUEL03_KOS_MIN_SMPLS )
           {
              fuel03_koc_f1();
           }
           else
           {
              fuel03_fault_flag();
           }
           SETBIT( Fuel03SenderA.MoreFilterFlags, FUEL03_KEY_OFF_SAMPLES_DONE );

        }
        else
        {
           if( Fuel03SenderA.SmplCounter == 0 )
           {
              if( Fuel03SenderA.koc_converged == FALSE )
              {
                 Fuel03SenderA.SmplCounter++;
                 if( TESTBIT(Fuel03SenderA.FilterFlags, (FUEL03_SAMPLE_OPEN_BIT | FUEL03_SAMPLE_SHORT_BIT)) )
                 {
                    Fuel03SenderA.ConvSample = 0;
                    Fuel03SenderA.sum_vx = 0;
                    Fuel03SenderA.min_vx = 255;
                    Fuel03SenderA.max_vx = 0;
                    return;
                 }
                 else
                 {
                    Fuel03SenderA.flps = fuel03_rad_to_flps( Fuel03SenderA.rad );
                    Fuel03SenderA.ConvSample = 1;
                    Fuel03SenderA.sum_vx = Fuel03SenderA.flps;
                    Fuel03SenderA.min_vx = Fuel03SenderA.flps;
                    Fuel03SenderA.max_vx = Fuel03SenderA.flps;
                    return;
                 }
              }
              else
              {
                 return; /* 'cause kos converged */
              }
           }
           else  /* Smpl Count x != 0 */
           {
              Fuel03SenderA.SmplCounter++;

              if( Fuel03SenderA.SmplCounter >= FUEL03_KOS_COUNTS )
              {
                 if( Fuel03SenderA.ConvSample >= FUEL03_KOS_MIN_SMPLS )
                 {
#ifdef FUEL03_SCEM_NUMBER_OF_FUEL_TANKS
                    fuel03_t_delta = FUEL03_KO_DELTA_A_NVM[Fuel03TankIndex];
#else
                    fuel03_t_delta = FUEL03_KO_DELTA_A_NVM;
#endif
                    if( (Fuel03SenderA.max_vx - Fuel03SenderA.min_vx) <= fuel03_t_delta )
                    {
                       fuel03_koc_f1();
                       return;
                    }
                 }
                 Fuel03SenderA.ConvCycleCounter++;
                 Fuel03SenderA.SmplCounter = 0;
                 Fuel03SenderA.koc_converged = FALSE;
              }
              else
              {
                 if( TESTBIT(Fuel03SenderA.FilterFlags, (FUEL03_SAMPLE_OPEN_BIT | FUEL03_SAMPLE_SHORT_BIT)) )
                 {
                    return;
                 }
                 else
                 {
                    Fuel03SenderA.ConvSample++;
                    Fuel03SenderA.flps = fuel03_rad_to_flps( Fuel03SenderA.rad );
                    Fuel03SenderA.sum_vx += Fuel03SenderA.flps;

                    if( Fuel03SenderA.flps < Fuel03SenderA.min_vx )
                    {
                       Fuel03SenderA.min_vx = Fuel03SenderA.flps;
                    }

                    if( Fuel03SenderA.flps > Fuel03SenderA.max_vx )
                    {
                       Fuel03SenderA.max_vx = Fuel03SenderA.flps;
                    }

                 }
              }
           }
        }
}

/*============================================================================
**      F A S T F I L L    S A M P L E   C O N V E R G E N C E
**==========================================================================*/

/*============================================================================
**
**  Function Name:      static void fuel03_ffsc_f1( void )
**
**  Visibility:         Internal
**
**  Description:        Key off convergence helper function.
**
**  INPUTS/OUTPUTS
**
**  Input Arguments:    none
**
**  Output Arguments:   none
**
**  Critical Section:   None
**
**  Created:            08/04/04 by RRUSS1
**
**  Updated:            08/04/04 by RRUSS1
**
**==========================================================================*/
static void fuel03_ffsc_f1( void )
{
        Fuel03SenderA.zss_ref = (UINT8)(Fuel03SenderA.sum_vx / (UINT16)Fuel03SenderA.ConvSample);
        Fuel03SenderA.ConvCycleCounter = 0;
        Fuel03SenderA.SmplCounter = 0;
        Fuel03SenderA.zs_converged = TRUE;
}

/*============================================================================
**
**  Function Name:      static void fuel03_ffsc( void )
**
**  Visibility:         Internal
**
**  Description:        This is the actual Fastfill Sample convergence algorithm using
**                      the fuel_flt pointer to execute on the individual sender.
**
**  INPUTS/OUTPUTS
**
**  Input Arguments:    none
**
**  Output Arguments:   none
**
**  Critical Section:   None
**
**  Created:            08/25/04 by RRUSS1
**
**  Updated:            08/25/04 by RRUSS1
**
**==========================================================================*/
static void fuel03_ffsc( void )
{
        UINT8 fuel03_t_delta;

        if( Fuel03SenderA.ConvCycleCounter >= FUEL03_ZS_CYCLES )
        {
           if( Fuel03SenderA.ConvSample >= FUEL03_ZS_MIN_SMPLS )
           {
              fuel03_ffsc_f1();
              return;
           }
        }
        else
        {
           if( Fuel03SenderA.SmplCounter == 0 )
           {
              if( Fuel03SenderA.zs_converged == FALSE )
              {
                 Fuel03SenderA.SmplCounter++;
                 if( TESTBIT(Fuel03SenderA.FilterFlags, (FUEL03_SAMPLE_OPEN_BIT | FUEL03_SAMPLE_SHORT_BIT)) )
                 {
                    Fuel03SenderA.ConvSample = 0;
                    Fuel03SenderA.sum_vx = 0;
                    Fuel03SenderA.min_vx = 255;
                    Fuel03SenderA.max_vx = 0;
                    return;
                 }
                 else
                 {
                    Fuel03SenderA.flps = fuel03_rad_to_flps( Fuel03SenderA.rad );
                    Fuel03SenderA.ConvSample = 1;
                    Fuel03SenderA.sum_vx = Fuel03SenderA.flps;
                    Fuel03SenderA.min_vx = Fuel03SenderA.flps;
                    Fuel03SenderA.max_vx = Fuel03SenderA.flps;
                    return;
                 }
              }
              else
              {
                 return; /* 'cause kos converged */
              }
           }
           else  /* Smpl Count x != 0 */
           {
              Fuel03SenderA.SmplCounter++;

              if( Fuel03SenderA.SmplCounter >= FUEL03_ZS_COUNTS )
              {
                 if( Fuel03SenderA.ConvSample >= FUEL03_ZS_MIN_SMPLS )
                 {
#ifdef FUEL03_SCEM_NUMBER_OF_FUEL_TANKS
                    fuel03_t_delta = Fuel03ZssDelta_A_NVM[Fuel03TankIndex];
#else
                    fuel03_t_delta = Fuel03ZssDelta_A_NVM;
#endif
                    if( (Fuel03SenderA.max_vx - Fuel03SenderA.min_vx) <= fuel03_t_delta )
                    {
                       fuel03_ffsc_f1();
                       return;
                    }
                 }
                 Fuel03SenderA.ConvCycleCounter++;
                 Fuel03SenderA.SmplCounter = 0;
                 Fuel03SenderA.zs_converged = FALSE;
              }
              else
              {
                 if( TESTBIT(Fuel03SenderA.FilterFlags, (FUEL03_SAMPLE_OPEN_BIT | FUEL03_SAMPLE_SHORT_BIT)) )
                 {
                    return;
                 }
                 else
                 {
                    Fuel03SenderA.ConvSample++;
                    Fuel03SenderA.flps = fuel03_rad_to_flps( Fuel03SenderA.rad );
                    Fuel03SenderA.sum_vx += Fuel03SenderA.flps;

                    if( Fuel03SenderA.flps < Fuel03SenderA.min_vx )
                    {
                       Fuel03SenderA.min_vx = Fuel03SenderA.flps;
                    }

                    if( Fuel03SenderA.flps > Fuel03SenderA.max_vx )
                    {
                       Fuel03SenderA.max_vx = Fuel03SenderA.flps;
                    }

                 }
              }
           }
        }
}

#endif
#if FUEL03_RAM_LOG_FAULT_RECORD_SIZE > 0

         static FUEL03_FAULT_SNAPSHOT_STRUCT fuel03_snapshot_A_RAM[FUEL03_RAM_LOG_FAULT_RECORD_SIZE];

         /*
         PID C90E -- 4 byte pointer to RAM buffer containing fuel init information (will only need 2 bytes for Mako micros, but will need more for other micros)
         PID C90F -- 2 byte size of RAM buffer in PID C90D
         PID C910 -- 4 byte pointer to NVM buffer containing fuel init information
         PID C911 -- 2 byte size of NVM buffer in PID C90F
         */
#endif
#ifdef  FUEL03_NEED_PID_C90E

/*============================================================================
**
**  Function Name:      UINT8 fuel03_C90e_KSGetPID(UINT32 *fuel03_buffer)
**
**  Visibility:         External
**
**  Description:        Routine to return 4 byte pointer to RAM buffer
**                      containing fuel init information (will only need
**                      2 bytes for Mako micros, but will need more for other micros).
**  INPUTS/OUTPUTS
**
**  Input Arguments:    buffer - pointer to location to store data
**
**  Output Arguments:   4 - the size of the PID
**
**  Critical Section:   None
**
**  Created:            01/13/05 by RRUSS1
**
**  Updated:            01/13/05 by RRUSS1
**                      02/26/07 by JARUN for BSDI00038410
**                      05/08/08 by CNAGARA1 for removal of QAC warning
**==========================================================================*/
UINT8 fuel03_C90e_KSGetPID(UINT32 *fuel03_buffer)
{
        UINT8 *p_temp = (UINT8 *)(void *)fuel03_buffer;

#if FUEL03_RAM_LOG_FAULT_RECORD_SIZE > 0

        /* QAC warning / error begin*************************************************
        **
        ** The following line of code generates QAC warning / error 0306 (MISRA Rule 45).
        ** It has been reviewed by Jeff Kanoza on 5/30/08 and deemed acceptable
        ** because it is necessary to perform this typecast to get the integer value
        ** of the address of the data.
        **
        ** QAC warning / error end**************************************************/
        UINT32 temp32 = (UINT32)&fuel03_snapshot_A_RAM;
#else
        UINT32 temp32 = 0;
#endif
        /*
        ** Store the data in the buffer.
        */
        *p_temp = (UINT8)(temp32>>24);
        p_temp++;
        *p_temp = (UINT8)(temp32>>16);
        p_temp++;
        *p_temp = (UINT8)(temp32>>8);
        p_temp++;
        *p_temp = (UINT8)(temp32);


        /*
        ** Return 4, the size of the PID.
        */
        return(4);
}
#endif
#ifdef  FUEL03_NEED_PID_C90F

/*============================================================================
**
**  Function Name:      UINT8 fuel03_C90f_KSGetPID( void )
**
**  Visibility:         External
**
**  Description:        Routine to return 2 byte size of RAM buffer in PID C90F.
**  INPUTS/OUTPUTS
**
**  Input Arguments:    buffer - pointer to location to store data
**
**  Output Arguments:   2 - the size of the PID
**
**  Critical Section:   None
**
**  Created:            01/13/05 by RRUSS1
**
**  Updated:            01/13/05 by RRUSS1
**                      10/25/06 by RRUSS1
**                      05/08/08 by CNAGARA1 for removal of QAC warning
**==========================================================================*/
UINT8 fuel03_C90f_KSGetPID(UINT16 *fuel03_buffer)
{
        UINT8 *p_temp = (UINT8 *)(void *)fuel03_buffer;

#if FUEL03_RAM_LOG_FAULT_RECORD_SIZE > 0
        UINT16 fuel03_temp = sizeof( fuel03_snapshot_A_RAM );
#else
        UINT16 fuel03_temp = 0;
#endif

        *p_temp = (UINT8)(fuel03_temp>>8);
        p_temp++;
        *p_temp = (UINT8)fuel03_temp;

        return( 2 );
}
#endif
#ifdef  FUEL03_NEED_PID_C912
/*============================================================================
**
**  Function Name:      UINT8 fuel03_C912_KSGetPID(UINT16 *fuel03_buffer )
**
**  Visibility:         External
**
**  Description:        Routine to return PID C912.
**  INPUTS/OUTPUTS
**
**  Input Arguments:    buffer - pointer to location to store data
**
**  Output Arguments:   1 - RAM Fault Record Indicator
**
**  Critical Section:   None
**
**  Created:            04/30/08 by CNAGARA1
**
**  Updated:            05/08/08 by CNAGARA1
**
**==========================================================================*/
UINT8 fuel03_C912_KSGetPID( UINT8 *fuel03_buffer )
{
#if FUEL03_RAM_LOG_FAULT_RECORD_SIZE > 0

            *fuel03_buffer = fuel03_RAM_fault_record;
#else
            *fuel03_buffer = 0;
#endif

            return( 1 );
}
#endif
#ifdef  FUEL03_NEED_PID_C914

/*============================================================================
**
**  Function Name:      UINT8 fuel03_C914_KSGetPID(UINT16 *fuel03_buffer )
**
**  Visibility:         External
**
**  Description:        Routine to return PID C914.
**  INPUTS/OUTPUTS
**
**  Input Arguments:    buffer - pointer to location to store data
**
**  Output Arguments:   1 - the number of fault records that are configured for
**                          storing in RAM
**
**  Critical Section:   None
**
**  Created:            04/30/08 by CNAGARA1
**
**  Updated:            05/08/08 by CNAGARA1
**
**==========================================================================*/
UINT8 fuel03_C914_KSGetPID( UINT8 *fuel03_buffer )
{
        *fuel03_buffer = FUEL03_RAM_LOG_FAULT_RECORD_SIZE;

        return( 1 );
}
#endif
#if FUEL03_RAM_LOG_FAULT_RECORD_SIZE > 0

/*============================================================================
**
**  Function Name:      void fuel03_log_init_errors_to_ram( void )
**
**  Visibility:         External
**
**  Description:        Routine to log the fuel init values to RAM.
**  INPUTS/OUTPUTS
**
**  Input Arguments:
**
**  Output Arguments:
**
**  Critical Section:   None
**
**  Created:            01/13/05 by RRUSS1
**
**  Updated:            01/13/05 by RRUSS1
**                      02/27/07 by JARUN  for BSDI00038410
**==========================================================================*/
static void fuel03_log_init_errors_to_ram( void )
{
        UINT8 x;
#if FUEL03_LOG_sample_array==1
UINT8 tx;
#endif

        /*
        ** Increment the record pointer to the next one and make sure it's
        ** within range. This is so that the pointer always points to the
        ** current incase a write to NVM is required.
        */
        fuel03_RAM_fault_record++;
        if( fuel03_RAM_fault_record >= FUEL03_RAM_LOG_FAULT_RECORD_SIZE )
        {
           fuel03_RAM_fault_record = 0;
        }

        x = fuel03_RAM_fault_record;

#if FUEL03_LOG_fdelta==1
        fuel03_snapshot_A_RAM[x].fdelta = Fuel03SenderA.fdelta;
#endif

#if FUEL03_LOG_fdelta_base==1
        fuel03_snapshot_A_RAM[x].fdelta_base = Fuel03SenderA.fdelta_base;
#endif

#if FUEL03_LOG_fdelta_adjust_base==1
        fuel03_snapshot_A_RAM[x].fdelta_adjust_base = Fuel03SenderA.fdelta_adjust_base;
#endif

#if FUEL03_LOG_FilterFlags==1
        fuel03_snapshot_A_RAM[x].FilterFlags = Fuel03SenderA.FilterFlags;
#endif

#if FUEL03_LOG_flps==1
        fuel03_snapshot_A_RAM[x].flps = Fuel03SenderA.flps;
#endif

#if FUEL03_LOG_init_ref==1
        fuel03_snapshot_A_RAM[x].init_ref = Fuel03SenderA.init_ref;
#endif

#if FUEL03_LOG_init_pid==1
        fuel03_snapshot_A_RAM[x].init_pid = Fuel03SenderA.init_pid;
#endif

#if FUEL03_LOG_KeyOffRef==1
        fuel03_snapshot_A_RAM[x].KeyOffRef = Fuel03SenderA.KeyOffRef;
#endif

#if FUEL03_LOG_keyon_radsum==1
        fuel03_snapshot_A_RAM[x].keyon_radsum = Fuel03SenderA.keyon_radsum;
#endif

#if FUEL03_LOG_keyon_good_samples==1
        fuel03_snapshot_A_RAM[x].keyon_good_samples = Fuel03SenderA.keyon_good_samples;
#endif

#if FUEL03_LOG_keyon_avgflps==1
        fuel03_snapshot_A_RAM[x].keyon_avgflps = Fuel03SenderA.keyon_avgflps;
#endif
#if FUEL03_LOG_MoreFilterFlags==1
        fuel03_snapshot_A_RAM[x].MoreFilterFlags = Fuel03SenderA.MoreFilterFlags;
#endif

#if FUEL03_LOG_FuelFaultCounter==1
        fuel03_snapshot_A_RAM[x].FuelFaultCounter = Fuel03SenderA.FuelFaultCounter;
#endif

#if FUEL03_LOG_FuelFaultRecoveryCounter==1
        fuel03_snapshot_A_RAM[x].FuelFaultRecoveryCounter = Fuel03SenderA.FuelFaultRecoveryCounter;
#endif

#if FUEL03_LOG_rad==1
        fuel03_snapshot_A_RAM[x].rad = Fuel03SenderA.rad;
#endif

#if FUEL03_LOG_avg_rad==1
        fuel03_snapshot_A_RAM[x].avg_rad = Fuel03SenderA.avg_rad;
#endif

#if FUEL03_LOG_old_rad==1
        fuel03_snapshot_A_RAM[x].old_rad = Fuel03SenderA.old_rad;
#endif

#if FUEL03_LOG_sample_array==1
        for( tx=0; tx<FUEL03_SMPLS_2_AVG; tx++ )
        {
           fuel03_snapshot_A_RAM[x].sample_array[tx] = Fuel03SenderA.sample_array[tx];
        }
#endif

#if FUEL03_LOG_rc_fill_threshold==1
        fuel03_snapshot_A_RAM[x].rc_fill_threshold = Fuel03SenderA.rc_fill_threshold;
#endif

#if FUEL03_LOG_rc_fill_delta==1
        fuel03_snapshot_A_RAM[x].rc_fill_delta = Fuel03SenderA.rc_fill_delta;
#endif

#if FUEL03_LOG_rflps==1
        fuel03_snapshot_A_RAM[x].rflps = Fuel03SenderA.rflps;
#endif

#if FUEL03_LOG_rfuel==1
        fuel03_snapshot_A_RAM[x].rfuel = Fuel03SenderA.rfuel;
#endif

#if FUEL03_LOG_slosh_filter==1
        fuel03_snapshot_A_RAM[x].slosh_filter = Fuel03SenderA.slosh_filter;
#endif

#if FUEL03_LOG_slosh_filter_hys==1
        fuel03_snapshot_A_RAM[x].slosh_filter_hys = Fuel03SenderA.slosh_filter_hys;
#endif

#if FUEL03_LOG_zss_ref==1
        fuel03_snapshot_A_RAM[x].zss_ref = Fuel03SenderA.zss_ref;
#endif

#ifdef FUEL03_FFRC_ENABLE
#if FUEL03_LOG_rate_check_passed==1
        fuel03_snapshot_A_RAM[x].rate_check_passed = Fuel03SenderA.rate_check_passed;
#endif

#if FUEL03_LOG_rate_check_timer==1
        fuel03_snapshot_A_RAM[x].rate_check_timer = Fuel03SenderA.rate_check_timer;
#endif

#if FUEL03_LOG_ffrc_delta_ref==1
        fuel03_snapshot_A_RAM[x].ffrc_delta_ref = Fuel03SenderA.ffrc_delta_ref;
#endif

#if FUEL03_LOG_sample_counter==1
        fuel03_snapshot_A_RAM[x].ffrc_delta_ref = Fuel03SenderA.ffrc_delta_ref;
#endif

#if FUEL03_LOG_rate_check_sample==1
        for( x=0; x<FUEL03_MAX_RATE_CHECK_SAMPLES; x++ )
        {
           fuel03_snapshot_A_RAM[x].rate_check_sample[x] = Fuel03SenderA.rate_check_sample[x];
        }
#endif

#endif

#if (FUEL03_REF_AVG_TYPE==4)
#if FUEL03_LOG_ConvCycleCounter==1
        /*
        ** If KOS is converged then store the shadow copy as ConvCycleCounter is
        ** is cleared in that case
        */
        if(FALSE != Fuel03SenderA.koc_converged)
        {
           fuel03_snapshot_A_RAM[x].ConvCycleCounter = Fuel03SenderA.KOS_ConvCycleCounter_shadow;
        }
        else
        {
           fuel03_snapshot_A_RAM[x].ConvCycleCounter = Fuel03SenderA.ConvCycleCounter;
        }
#endif

#if FUEL03_LOG_ConvSample==1
        fuel03_snapshot_A_RAM[x].ConvSample = Fuel03SenderA.ConvSample;
#endif

#if FUEL03_LOG_SmplCounter==1
        /*
        ** If KOS is converged then store the shadow copy as SmplCounter is
        ** is cleared in that case
        */
        if(FALSE != Fuel03SenderA.koc_converged)
        {
           fuel03_snapshot_A_RAM[x].SmplCounter = Fuel03SenderA.KOS_SmplCounter_shadow;
        }
        else
        {
           fuel03_snapshot_A_RAM[x].SmplCounter = Fuel03SenderA.SmplCounter;
        }
#endif

#if FUEL03_LOG_min_vx==1
        fuel03_snapshot_A_RAM[x].min_vx = Fuel03SenderA.min_vx;
#endif

#if FUEL03_LOG_max_vx==1
        fuel03_snapshot_A_RAM[x].max_vx = Fuel03SenderA.max_vx;
#endif

#if FUEL03_LOG_sum_vx==1
        fuel03_snapshot_A_RAM[x].sum_vx = Fuel03SenderA.sum_vx;
#endif

#if FUEL03_LOG_koc_converged==1
        fuel03_snapshot_A_RAM[x].koc_converged = Fuel03SenderA.koc_converged;
#endif

#if FUEL03_LOG_koc_fault_flag==1
        fuel03_snapshot_A_RAM[x].koc_fault_flag = Fuel03SenderA.koc_fault_flag;
#endif

#if FUEL03_LOG_zs_converged==1
        fuel03_snapshot_A_RAM[x].zs_converged = Fuel03SenderA.zs_converged;
#endif
#endif

#if FUEL03_LOG_moving_sample_counter==1
        fuel03_snapshot_A_RAM[x].moving_sample_counter = Fuel03SenderA.moving_sample_counter;
#endif

#if FUEL03_LOG_use_avg_flag==1
        fuel03_snapshot_A_RAM[x].use_avg_flag = Fuel03SenderA.use_avg_flag;
#endif

#if FUEL03_LOG_use_mov_avg==1
        fuel03_snapshot_A_RAM[x].use_mov_avg = Fuel03SenderA.use_mov_avg;
#endif

#if FUEL03_LOG_err_counter==1
        fuel03_snapshot_A_RAM[x].err_counter = Fuel03SenderA.err_counter;
#endif
#ifdef FUEL03_ADD_CONVERGENCE_DATA_TO_FAULT_RECORD
#if FUEL03_LOG_invalid_condition==1
        /*
        ** Clear this byte after saving it so that it is ready for the next key cycle
        */
        fuel03_snapshot_A_RAM[x].fuel03_invalid_condition = fuel03_invalid_condition;
        fuel03_invalid_condition=0;
#endif

#if FUEL03_LOG_ignition_cycle_counter==1
        fuel03_snapshot_A_RAM[x].fuel03_ignition_cycle_counter = fuel03_ignition_cycle_counter;
#endif
#endif

}
#endif
#ifdef  FUEL03_NEED_PID_C910
/*============================================================================
**
**  Function Name:      UINT8 fuel03_C910_KSGetPID(UINT32 *fuel03_buffer)
**
**  Visibility:         External
**
**  Description:        Routine to return 4 byte pointer to NVM buffer
**                      containing fuel init information (will only need
**                      2 bytes for Mako micros, but will need more for other micros).
**
**  INPUTS/OUTPUTS
**
**  Input Arguments:    buffer - pointer to location to store data
**
**  Output Arguments:   4 - the size of the PID
**
**  Critical Section:   None
**
**  Created:            01/13/05 by RRUSS1
**
**  Updated:            01/13/05 by RRUSS1
**                      02/26/07 by JARUN for BSDI00038410
**                      10/23/07 by RRUSS1 BSDI00050096
**                      05/08/08 by CNAGARA1 for removal of QAC warning
**==========================================================================*/
UINT8 fuel03_C910_KSGetPID(UINT32 *fuel03_buffer)
{
    UINT8 *p_temp = (UINT8 *)(void *)fuel03_buffer;

#if FUEL03_LOG_FAULT_RECORD_SIZE > 0

        /* QAC warning / error begin*************************************************
        **
        ** The following line of code generates QAC warning / error 0306 (MISRA Rule 45).
        ** It has been reviewed by Jeff Kanoza on 5/30/08 and deemed acceptable
        ** because it is necessary to perform this typecast to get the integer value
        ** of the address of the data.
        **
        ** QAC warning / error end**************************************************/
        UINT32 temp32 = (UINT32)&fuel03_fault_snapshot_A_NVM;

#else
        UINT32 temp32 = 0;
#endif

        /*
        ** Store the data in the buffer.
        */
        *p_temp = (UINT8)(temp32>>24);
        p_temp++;
        *p_temp = (UINT8)(temp32>>16);
        p_temp++;
        *p_temp = (UINT8)(temp32>>8);
        p_temp++;
        *p_temp = (UINT8)(temp32);

        /*
        ** Return 4, the size of the PID.
        */
        return(4);
}
#endif
#ifdef  FUEL03_NEED_PID_C911

/*============================================================================
**
**  Function Name:      UINT8 fuel03_C911_KSGetPID( void )
**
**  Visibility:         External
**
**  Description:        Routine to return 2 byte size of RAM buffer in PID C911.
**  INPUTS/OUTPUTS
**
**  Input Arguments:    buffer - pointer to location to store data
**
**  Output Arguments:   2 - the size of the PID
**
**  Critical Section:   None
**
**  Created:            01/13/05 by RRUSS1
**
**  Updated:            03/04/05 by RRUSS1
**                      10/23/07 by RRUSS1 BSDI00050096
**                      05/08/08 by CNAGARA1 for removal of QAC warning
**
**==========================================================================*/
UINT8 fuel03_C911_KSGetPID( UINT16 *fuel03_buffer )
{
        UINT8 *p_temp = (UINT8 *)(void *)fuel03_buffer;

#if FUEL03_LOG_FAULT_RECORD_SIZE > 0
        UINT16 fuel03_temp = sizeof( fuel03_fault_snapshot_A_NVM );
#else
        UINT16 fuel03_temp = 0;
#endif

        *p_temp = (UINT8)(fuel03_temp>>8);
        p_temp++;
        *p_temp = (UINT8)fuel03_temp;

        return( 2 );
}

#endif
#ifdef  FUEL03_NEED_PID_C913

/*============================================================================
**
**  Function Name:      UINT8 fuel03_C913_KSGetPID(UINT16 *fuel03_buffer )
**
**  Visibility:         External
**
**  Description:        Routine to return PID C913.
**  INPUTS/OUTPUTS
**
**  Input Arguments:    buffer - pointer to location to store data
**
**  Output Arguments:   1 - Next fault log that is going to be written into
**                      NVM
**
**  Critical Section:   None
**
**  Created:            04/30/08 by CNAGARA1
**
**  Updated:            05/08/08 by CNAGARA1
**
**==========================================================================*/
UINT8 fuel03_C913_KSGetPID( UINT8 *fuel03_buffer )
{
#if FUEL03_LOG_FAULT_RECORD_SIZE > 0
        *fuel03_buffer = fuel03_next_fault_log_to_write_NVM;
#else
        *fuel03_buffer = 0;
#endif

        return( 1 );
}
#endif
#ifdef  FUEL03_NEED_PID_C915

/*============================================================================
**
**  Function Name:      UINT8 fuel03_C915_KSGetPID(UINT16 *fuel03_buffer )
**
**  Visibility:         External
**
**  Description:        Routine to return PID C915.
**  INPUTS/OUTPUTS
**
**  Input Arguments:    buffer - pointer to location to store data
**
**  Output Arguments:   1 - the number of fault records that are configured for
**                          storing in NVM
**
**  Critical Section:   None
**
**  Created:            04/30/08 by CNAGARA1
**
**  Updated:            05/08/08 by CNAGARA1
**
**==========================================================================*/
UINT8 fuel03_C915_KSGetPID( UINT8 *fuel03_buffer )
{
    *fuel03_buffer = FUEL03_LOG_FAULT_RECORD_SIZE;

    return( 1 );
}
#endif
#if FUEL03_LOG_FAULT_RECORD_SIZE > 0

/*============================================================================
**
**  Function Name:      UINT8 fuel03_log_init_errors_to_nvm( void )
**
**  Visibility:         External
**
**  Description:        Routine to log the fuel init values to NVM.
**  INPUTS/OUTPUTS
**
**  Input Arguments:
**
**  Output Arguments:
**
**  Critical Section:   None
**
**  Created:            01/13/05 by RRUSS1
**
**  Updated:            01/13/05 by RRUSS1
**                      03/10/08 by CNAGARA1 - BSDI00055411
**                      05/08/08 by CNAGARA1 - To update for peer review comments
**
**==========================================================================*/
static void fuel03_log_init_errors_to_nvm( void )
{
        BOOLEAN fuel03_epm_result;
        UINT8 fuel03_next_fault_location_RAM = 0;
        UINT8* fuel03_senderA_nvm_addr;
        UINT8 *fuel03_senderA_ram_addr;

        if( Fuel03SenderA.log_nvm_data != FALSE )
        {
           Fuel03SenderA.queue_result = 0;
           /* ------------------------------------------------------------------------
           ** Get the last stored record number from NVM and point it to the next one.
           ** ----------------------------------------------------------------------*/
           fuel03_next_fault_location_RAM = fuel03_next_fault_log_to_write_NVM;
           fuel03_next_fault_location_RAM++;

           if( fuel03_next_fault_location_RAM >= FUEL03_LOG_FAULT_RECORD_SIZE )
           {
              fuel03_next_fault_location_RAM = 0;
           }

           /* ------------------------------------------------------------------------
           ** Write the record number back to NVM.
           ** ----------------------------------------------------------------------*/
           fuel03_epm_result = epm_pkg_q_e2_write( (void *)&fuel03_next_fault_log_to_write_NVM,
              (void *)&fuel03_next_fault_location_RAM,
              NULL, 1);

           if( fuel03_epm_result == FALSE )
           {
              return;
           }
           else
           {
              Fuel03SenderA.log_nvm_data = FALSE;
           }
        }

        if ( Fuel03SenderA.queue_result ==  (FUEL03_BLK1_QUEUED | FUEL03_BLK2_QUEUED) )
        {
           return;
        }

        /*
        ** If all the bytes are not queued at first shot then the following assignment
        ** will get the next fault location from NVM.
        */
        fuel03_next_fault_location_RAM = fuel03_next_fault_log_to_write_NVM;

        fuel03_senderA_nvm_addr = (void *)&fuel03_fault_snapshot_A_NVM[fuel03_next_fault_location_RAM];
        fuel03_senderA_ram_addr = (void *)&fuel03_snapshot_A_RAM[fuel03_RAM_fault_record];

        /* ------------------------------------------------------------------------
        ** Check the results of the last write operation and only update the
        ** fault log record if the record number value was written correctly.
        ** ----------------------------------------------------------------------*/
        if( (sizeof( FUEL03_FAULT_SNAPSHOT_STRUCT)) > EPM_MAX_NUM_MODIFY)
        {
           if ( FUEL03_NOTTESTBIT(Fuel03SenderA.queue_result,FUEL03_BLK1_QUEUED) )
           {
              if ( FALSE != epm_pkg_q_e2_write( (void *)fuel03_senderA_nvm_addr,
                 (void *)fuel03_senderA_ram_addr,
                 NULL,EPM_MAX_NUM_MODIFY ) )
              {
                 SETBIT(Fuel03SenderA.queue_result,FUEL03_BLK1_QUEUED);
              }
           }

           if ( FUEL03_NOTTESTBIT(Fuel03SenderA.queue_result,FUEL03_BLK2_QUEUED) )
           {
              if( FALSE != epm_pkg_q_e2_write( (void *)&fuel03_senderA_nvm_addr[EPM_MAX_NUM_MODIFY],
                 (void *)&fuel03_senderA_ram_addr[EPM_MAX_NUM_MODIFY],
                 NULL,(UINT8)( sizeof( FUEL03_FAULT_SNAPSHOT_STRUCT ) - EPM_MAX_NUM_MODIFY) ) )
              {
                 SETBIT(Fuel03SenderA.queue_result,FUEL03_BLK2_QUEUED);
              }
           }
        }
        else
        {
           if ( FUEL03_NOTTESTBIT(Fuel03SenderA.queue_result,FUEL03_BLK1_QUEUED) )
           {
              if ( FALSE != epm_pkg_q_e2_write( (void *)fuel03_senderA_nvm_addr,
                 (void *)fuel03_senderA_ram_addr,
                 NULL,sizeof( FUEL03_FAULT_SNAPSHOT_STRUCT ) ) )
              {
                 SETBIT(Fuel03SenderA.queue_result,FUEL03_BLK1_QUEUED);
              }
              /*
              ** The BLK2 will be not used if the size of the structure is less than
              ** EPM_MAX_NUM_MODIFY size. So set FUEL03_BLK2_QUEUED always
              */
              SETBIT(Fuel03SenderA.queue_result,FUEL03_BLK2_QUEUED);
           }
        }
}
#endif

#ifdef FUEL03_NEED_DTC_LOGGING
/*============================================================================
**
**  Function Name:      void fuel03_log_dtcs( void )
**
**  Visibility:         Internal
**
**  Description:        Routine to log DTCs for fuel sender faults.
**
**  INPUTS/OUTPUTS
**
**  Input Arguments:
**
**  Output Arguments:
**
**  Critical Section:   None
**
**  Created:            08/15/05 by RRUSS1
**
**  Updated:            08/15/05 by RRUSS1
**
**==========================================================================*/
static void fuel03_log_dtcs(void)
{
        if( FUEL03_DTC_LOGGING_ACTIVE() != FALSE )
        {
           /*
           ** Check sender 1.
           */
           if (TESTBIT(Fuel03SenderA.FilterFlags, FUEL03_SENDER_OPEN))
           {
              FUEL03_LOG_FUEL_SENDER_CKT_OPEN();
           }
           else
           {
              FUEL03_CLR_FUEL_SENDER_CKT_OPEN();
           }

           if (TESTBIT(Fuel03SenderA.FilterFlags, FUEL03_SENDER_SHORTED))
           {
              FUEL03_LOG_FUEL_SENDER_CKT_SHORT();
           }
           else
           {
              FUEL03_CLR_FUEL_SENDER_CKT_SHORT();
           }
        }
}
#endif
#ifdef  FUEL03_GET_KEY_ON_AVGFLPS
         UINT8 Fuel03_SenderA_keyon_avgflps( void )
         {
            return( Fuel03SenderA.keyon_avgflps );
         }
#endif
#ifdef  FUEL03_GET_KEYOFFREF
         UINT8 Fuel03_SenderA_KeyOffRef( void )
         {
            return( Fuel03SenderA.KeyOffRef );
         }
#endif
#ifdef  FUEL03_GET_KEY_ZSSFREF

         UINT8 Fuel03_SenderA_zss_ref( void )
         {
            return( Fuel03SenderA.zss_ref );
         }
#endif
#ifdef  FUEL03_GET_KEY_ON_GOOD_SAMPLE

         UINT8 Fuel03_SenderA_keyon_good_samples( void )
         {
            return( Fuel03SenderA.keyon_good_samples );
         }
#endif
#if (FUEL03_REF_AVG_TYPE==4 )
         UINT8 Fuel03_SenderA_ConvSample( void )
         {
            return( Fuel03SenderA.ConvSample );
         }
#endif
#ifdef FUEL03_CANFLPS
         UINT16 Fuel03_Get_CANFLPS( UINT16 radin )
         {
            UINT16 retval;

            retval = LinearInterpolateWord((UINT16 *)&Fuel03_CANFLPS_TableNVM[0][0], radin);

            return( retval );
         }
#endif
#ifdef FUEL03_CLR_DTC_RESET

/*============================================================================
**
**  Function Name:      void Fuel03_clear_DTC_resets(void)
**
**  Visibility:         External
**
**  Description:        Routine will reset the fault flages and timers
**                      Sender A.
**
**  INPUTS/OUTPUTS
**
**  Input Arguments:    None
**
**  Output Arguments:   None
**
**  Critical Section:   None
**
**  Created:            28/10/08 by KNAGASUB
**
**  updated:            24/11/08 by KNAGASUB
**==========================================================================*/
void fuel03_clear_DTC_resets(void)
{

        CLEARBIT(Fuel03SenderA.FilterFlags, (FUEL03_SAMPLE_OPEN_BIT | FUEL03_SAMPLE_SHORT_BIT));
        CLEARBIT(Fuel03SenderA.FilterFlags, (FUEL03_SENDER_OPEN | FUEL03_SENDER_SHORTED));
        /** Reset debounce counter to the max debounce time.
        */
        fuel03_fault_counter();
        fuel03_fault_recovery_counter();


}
#endif
/*============================================================================
**
**  Function Name:      static void fuel03_fdelta_base(void)
**
**  Visibility:         Intenal
**
**  Description:        Routine will store the fdelta_base value.
**                      It's used for optimiztion purpose
**
**  INPUTS/OUTPUTS
**
**  Input Arguments:    None
**
**  Output Arguments:   None
**
**  Critical Section:   None
**
**  Created:            09/10/09 by KNAGASUB
**
**==========================================================================*/

static void fuel03_fdelta_base(void)
{
        /* -------------------------------------------------------------
        ** FDELTA x = FDELTA BASE x
        ** -----------------------------------------------------------*/
        Fuel03SenderA.fdelta = Fuel03SenderA.fdelta_base;

}
/*============================================================================
**
**  Function Name:      static void fuel03_fault_recovery_counter(void)
**
**  Visibility:         Intenal
**
**  Description:        Routine will store the fdelta_base value.
**                      It's used for optimiztion purpose
**
**  INPUTS/OUTPUTS
**
**  Input Arguments:    None
**
**  Output Arguments:   None
**
**  Critical Section:   None
**
**  Created:            09/10/09 by KNAGASUB
**
**==========================================================================*/

static void fuel03_fault_recovery_counter(void)
{
  Fuel03SenderA.FuelFaultRecoveryCounter = Fuel03FaultRecoveryCounterNVM;
}
/*============================================================================
**
**  Function Name:      static void fuel03_fault_counter(void)
**
**  Visibility:         Intenal
**
**  Description:        Routine will store the fdelta_base value.
**                      It's used for optimiztion purpose
**
**  INPUTS/OUTPUTS
**
**  Input Arguments:    None
**
**  Output Arguments:   None
**
**  Critical Section:   None
**
**  Created:            09/10/09 by KNAGASUB
**
**==========================================================================*/
static void fuel03_fault_counter(void)
{
      Fuel03SenderA.FuelFaultCounter = Fuel03FaultCounterNVM;
}
/*============================================================================
**
**  Function Name:      static void fuel03_fdelta_base_and_adjust_nvm(void)
**
**  Visibility:         Intenal
**
**  Description:        Routine will store the fdelta_base value.
**                      It's used for optimiztion purpose
**
**  INPUTS/OUTPUTS
**
**  Input Arguments:    None
**
**  Output Arguments:   None
**
**  Critical Section:   None
**
**  Created:            09/10/09 by KNAGASUB
**  Updated:            12/05/10 by JARUN
**==========================================================================*/

static void fuel03_fdelta_base_and_adjust_nvm(void)
{
#if (FUEL03_MULT_FILT_RATES == 1)

        UINT8 f1_base_index_U8 = fuel03_get_fdelta_normal_base_index();

#ifdef FUEL03_SCEM_NUMBER_OF_FUEL_TANKS
        Fuel03SenderA.fdelta_base = FUEL03_DELTA_NORMAL_BASE_A_NVM[f1_base_index_U8][Fuel03TankIndex];
        Fuel03SenderA.fdelta_adjust_base = FUEL03_DELTA_NORMAL_ADJUST_A_NVM[Fuel03TankIndex];
#else
        Fuel03SenderA.fdelta_base = FUEL03_DELTA_NORMAL_BASE_A_NVM[f1_base_index_U8];
        Fuel03SenderA.fdelta_adjust_base = FUEL03_DELTA_NORMAL_ADJUST_A_NVM;
#endif

#else

#ifdef FUEL03_SCEM_NUMBER_OF_FUEL_TANKS
        Fuel03SenderA.fdelta_base = FUEL03_DELTA_NORMAL_BASE_A_NVM[Fuel03TankIndex];
        Fuel03SenderA.fdelta_adjust_base = FUEL03_DELTA_NORMAL_ADJUST_A_NVM[Fuel03TankIndex];
#else
        Fuel03SenderA.fdelta_base = FUEL03_DELTA_NORMAL_BASE_A_NVM;
        Fuel03SenderA.fdelta_adjust_base = FUEL03_DELTA_NORMAL_ADJUST_A_NVM;
#endif
#endif
}
/*============================================================================
**
**  Function Name:      static void fuel03_fdelta_fast_base(void)
**
**  Visibility:         Intenal
**
**  Description:        Routine will store the fdelta_base value.
**                      It's used for optimiztion purpose
**
**  INPUTS/OUTPUTS
**
**  Input Arguments:    None
**
**  Output Arguments:   None
**
**  Critical Section:   None
**
**  Created:            09/10/09 by KNAGASUB
**
**==========================================================================*/
static void fuel03_fdelta_fast_base(void)
{
#ifdef FUEL03_SCEM_NUMBER_OF_FUEL_TANKS
            Fuel03SenderA.fdelta_base = FUEL03_DELTA_FAST_BASE_A_NVM[Fuel03TankIndex];
#else
            Fuel03SenderA.fdelta_base = FUEL03_DELTA_FAST_BASE_A_NVM;
#endif
}
/*============================================================================
**
**  Function Name:      static void fuel03_fdelta_normal_base(void)
**
**  Visibility:         Intenal
**
**  Description:        Routine will store the fdelta_base value.
**                      It's used for optimiztion purpose
**
**  INPUTS/OUTPUTS
**
**  Input Arguments:    None
**
**  Output Arguments:   None
**
**  Critical Section:   None
**
**  Created:            09/10/09 by KNAGASUB
**  Updated:            12/05/10 by JARUN
**==========================================================================*/

static void fuel03_fdelta_normal_base(void)
{
#if (FUEL03_MULT_FILT_RATES == 1)

            UINT8 f1_base_index_U8 = fuel03_get_fdelta_normal_base_index();

  #ifdef FUEL03_SCEM_NUMBER_OF_FUEL_TANKS
            Fuel03SenderA.fdelta = FUEL03_DELTA_NORMAL_BASE_A_NVM[f1_base_index_U8][Fuel03TankIndex];
  #else
            Fuel03SenderA.fdelta = FUEL03_DELTA_NORMAL_BASE_A_NVM[f1_base_index_U8];
  #endif

#else
  #ifdef FUEL03_SCEM_NUMBER_OF_FUEL_TANKS
            Fuel03SenderA.fdelta = FUEL03_DELTA_NORMAL_BASE_A_NVM[Fuel03TankIndex];
  #else
            Fuel03SenderA.fdelta = FUEL03_DELTA_NORMAL_BASE_A_NVM;
  #endif

#endif
}
#if (FUEL03_MULT_FILT_RATES == 1)
/*============================================================================
**
**  Function Name:      static UINT8 fuel03_get_fdelta_normal_base_index(void)
**
**  Visibility:         Intenal
**
**  Description:        Routine will provide the Index to fdelta,
**                      according to speed Input.
**
**  INPUTS/OUTPUTS
**
**  Input Arguments:    None
**
**  Output Arguments:   None
**
**  Critical Section:   None
**
**  Created:            12/05/10 by JARUN

**==========================================================================*/

static UINT8 fuel03_get_fdelta_normal_base_index(void)
{

        UINT16 f1_speed_val_U16;

        UINT8 f1_base_index_U8 = FUEL03_DELTA_NORMAL_BASE_A3_INDX;

        if(!FUEL03_SPEED_MSG_MISSING() &&
           !FUEL03_SPEED_MSG_INVALID() &&
           !FUEL03_SPEED_MSG_UNKNOWN())
        {
           f1_speed_val_U16 =  FUEL03_SPEED_MSG_RXD();

           if(f1_speed_val_U16 <= FUEL03_SPD_THRESH_1)
           {
              f1_base_index_U8 = FUEL03_DELTA_NORMAL_BASE_A1_INDX;
           }
           else if(f1_speed_val_U16 <= FUEL03_SPD_THRESH_2)
           {
              f1_base_index_U8 = FUEL03_DELTA_NORMAL_BASE_A2_INDX;
           }
           else
           {
           }
        }
        /* Fdelta Normal Base A != Previous Fdelta Normal Base A */
        if(Fuel03PrevFdeltaNormalBaseAIndx != f1_base_index_U8)
        {
           Fuel03PrevFdeltaNormalBaseAIndx = f1_base_index_U8;
           /* -------------------------------------------------------------
           ** x > flag = 0     Clear the sample is above filter flag.
           ** x < flag = 0     Clear the sample is below filter flag.
           ** -----------------------------------------------------------*/
           CLEARBIT(Fuel03SenderA.FilterFlags, FUEL03_SAMPLE_IS_ABOVE_FILTER);
           CLEARBIT(Fuel03SenderA.FilterFlags, FUEL03_SAMPLE_IS_BELOW_FILTER);
        }

        return(f1_base_index_U8);
}



#endif
         /*
         #ifdef FUEL03_DEBUG
         #include FUEL03_INCLUDE
         #endif

         */
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
         ** 06/26/2014    RAGARWA1
     **  Merge the N2.0 changes. RTC 168572 for reference.
     **  Resolved the defect RTC 171127

         ** 11/04/13         BVIJAYKU
         **  Updated for QAC 8.0R warnings fix.
     ** Changes:
     ** 1. Added FUEL03_NEED_FILTER_BYPASS_AT_IGN_START macro to remove the QAC warning if define
     ** FUEL03_POWER_MODE_MACRO() to FALSE.
     ** 2. Added fuel03_KSNvRamCheck() function to check key on good samples are zero or not.
     ** This function added to get the deviation for the warning generated in line number 2260.
     **

         ** 09/05/13         BVIJAYKU
         **  Updated for QAC 8.0R warnings fix.
         
         ** 08/13/13         BVIJAYKU
         **  Updated for QAC 8.0R warnings fix.

         ** 03/09/12         BVIJAYKU
         **  Updated for QAC 7.1 fix.

         ** 01/12/11         BVIJAYKU
         **  Updated to remove compiler warnings in Raman Platform.
         **
         ** 06/02/10         JARUN
         **  Added previous Fdelta Normal Base A to set < and > flags to 0
         **  on a change to the value of Fdelta Normal Base A
         **
         ** 05/12/10         JARUN
         **  Added support for slosh filter time constants based upon vehicle speed.
         **  CQ:BSDI00086712
         **
         ** 02/03/2010      KNAGASUB
         ** fuel03_KSWarmInit(),fuel03_KSWakeup() added as per review comments.

         ** 01/28/2010       BVIJAYKU
         ** Updated as per review comments.
         **
         ** 01/22/2010       BVIJAYKU
         ** Updated description for the functions and modified fuel03_fill_or_loss_status() and
         ** fuel03_open_short_status().
         **
         ** 01/20/2010       BVIJAYKU
         ** Updated for QAC fix version 4.5.3 with cosmic compiler V4711.
         **
         ** 08/11/09       KNAGASUB
         ** As per CQ BSDI00073307-Need memory optimized Fuel package for Newton1.5
         ** This is levaraged from fuel02_2.08 label
         ** 1) FUEL03_RC_FILL_ENABLED macro is added to enable/disable the RC_FILL_delta functionality
         ** 2) FUEL03_SLOSH_HYS-  macro is added to enable/disable the slosh filter related functionality.
         ** 3) FUEL03_ERR_CNT- macro is added to enable /disable the error counter
         ** 4) KOS_ConvCycleCounter_shadow; and KOS_SmplCounter_shadow varaible are included, when
         **   FUEL03_RAM_LOG_FAULT_RECORD_SIZE > 0 and FUEL03_LOG_ConvCycleCounter==1 satisfied.
         - macro is added to enable /disable the error counter
         ** 5)log_nvm_data and queue_result are included ,when FUEL03_LOG_FAULT_RECORD_SIZE > 0
         ** 6)Following function are added to reduce the memeory size based on list file analysis.
         **    a) static void fuel03_fdelta_base(void);
         **    b)static void fuel03_fault_recovery_counter(void);
         **    c)static void fuel03_fault__counter(void);
         **    d)static void fuel03_fdelta_base_and_adjust_nvm(void);
         **    e)static void fuel03_fdelta_fast_base(void);
         **    f)static void fuel03_fdelta_normal_base(void);
         **    List file analysis:
         **    Fuel03SenderA.fdelta = Fuel03SenderA.fdelta_base;
         **    The above said assignment statement is available 5 times in fuel filter package.
         **    Both the varaibles are UINT32 bit.So MOVW instruction is used for this purpose.
         **    It occupies 6 bytes of ROM size.Two MOVW instruction required for this.
         **    Make this statement as function and replace this function instead of mentioned statement.
         **    8 bytes reduction.Because function call consumes 4 bytes.
         **       i.e,
         **             Previously bytes  (6bytes per MOVW)* 2(per assignment statement) * 5times  =  60 bytes
         **             Now, 6bytes per MOVW)* 2(per assignment statement) + 4* 5                  = 32 bytes
         **             Saving                                                                     = 28 bytes
         ** 7)fuel03_level_calculation() is based on FUEL03_RC_FILL_ENABLED  macro enable/disable.
         ** 8) Fuel03_AVG_Vol_Invalid_Counter is utilized only when ford convergence enabled.
         ** 9)fuel03_invalid_condition enable/disable by FUEL03_ADD_CONVERGENCE_DATA_TO_FAULT_RECORD
         **   and FUEL03_LOG_invalid_condition==1 condition.
         ** 10)FUEL03_IGN_STATUS- macro enable/disable the ign counter varaible's
         ** 11) fuel03_common_gauge_init(), fuel03_KSColdInit(),fuel03_cold_init() modifed
         ** 12) fuel03_KSWarmInit(),fuel03_KSWakeup() are removed.Because fuel03_setup_for_init()
         **     function is used this purpose.
         ** 13) fuel03_setup_for_init(),fuel03_start_init() -modified.
         ** 14) FUEL03_KEY_OFF_ENABLED-macro is added to enable/disable key off processing function()
         ** 15)FUEL03_HILL_HOLD_ENABLE-macro ia added to enable/disable the hill hold functionality.
         ** 16)fuel03_zss_keyoff_processing(),fuel03_periodic_processing(),fuel03_open_short_test()-modified.
         ** 17)fuel03_debounce_open_short() fuel03_init_avgflps_calc() fuel03_finit_t3()fuel03_finit_F3()-modified
         ** 18)fuel03_fi_check(),uel03_fast_fill_enable_check(),fast_fill_determination_f1()-modified
         ** 19) fuel03_slosh_filter()-modified
         ** 20)FUEL03_EOL_LIVE-macro enable/disable the EOL live mode.
         ** 21)FUEL03_AD_NETWORK- macro added to enable/disable the fuel03_network_message_missing()
         ** 22) fuel03_senderA_fast_fill_active()-removed.
         ** 23) FUEL03_GET_UNFILTER_FLPS-enable/disable the fuel03_get_SenderA_unfiltered_flps()
         ** 24)fuel03_koc_f1-modified
         ** 25)FUEL03_NEED_PID_C90E, FUEL03_NEED_PID_C90F , FUEL03_NEED_PID_C912,FUEL03_NEED_PID_C914
         **    FUEL03_NEED_PID_C910,FUEL03_NEED_PID_C911,FUEL03_NEED_PID_C913,FUEL03_NEED_PID_C915
         **     macro's added.
         ** 26)fuel03_log_init_errors_to_ram()-modified
         ** 27)FUEL03_GET_KEY_ON_AVGFLPS,FUEL03_GET_KEY_ON_KEYOFFREF,FUEL03_GET_KEY_ZSSFREF,
         FUEL03_GET_KEY_ON_GOOD_SAMPLE,FUEL03_CANFLPS,FUEL03_CLR_DTC_RESET
         **==========================================================================*/
/*---------------------------------------------------------------------------
Date               : 08/june/2021
By                 : mdevadas
Traceability       : RTC Defect : 595651
Change Description : Removed commented code
-----------------------------------------------------------------------------*/
         /* end of file ============================================================ */

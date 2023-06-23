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

  Name:               fuel03.h

  Description:        Configurable fuel filter algorithms.

  Organization:       Driver Information Software Section,
                      DI Core Engineering Department

==========================================================================*/
#ifndef FUEL03FLT_H
#define FUEL03FLT_H


/*============================================================================
                      O V E R V I E W
=============================================================================*/
/*
** The intent of this code is to provide a configurable fuel filter
** algorithm for use in a variety of instrument cluster applications.
**
** Requirements for this code came from the core fuel gage requirements
** written by Brad Corbin of the SPSS group.
*/

/*============================================================================
                 I N C L U D E   F I L E S
==============================================================================*/
#include "Fuel_Guage.h"
/*============================================================================
    P U B L I C   M A C R O   A N D   T Y P E   D E F I N I T I O N S
=============================================================================*/

/*
** Define some invalid data indicators
*/
#define FUEL03_PERCENT_FULL_INVALID_BYTE  (0xFF)
/*#define FUEL03_PERCENT_FULL_INVALID_WORD  (0xFF00u)*/


/* --------------------------------------------------------------------------
** Values returned by "fuel03_open_short_test()".
** --------------------------------------------------------------------------
*/
#define FUEL03_SAMPLE_OK      (1)
#define FUEL03_SAMPLE_OPEN    (2)
#define FUEL03_SAMPLE_SHORTED (3)

/* --------------------------------------------------------------------------
** Values returned by "fuel03_fill_or_loss_status()".
** --------------------------------------------------------------------------
*/
#define FUEL03_STATUS_FILL    (1)
#define FUEL03_STATUS_LOSS    (2)
#define FUEL03_STATUS_NORMAL  (3)

/* --------------------------------------------------------------------------
** Values returned by "fuel03_open_short_status()".
** --------------------------------------------------------------------------
*/
#define FUEL03_STATUS_OPEN    (1)
#define FUEL03_STATUS_SHORT    (2)
#define FUEL03_STATUS_NO_OPEN_SHORT   (3)

/*============================================================================
   P U B L I C   F U N C T I O N   P R O T O T Y P E S
=============================================================================*/
/*
** Add the following to SCHED.CFG in the appropriate list.
*/
void fuel03_KSColdInit(void);
void fuel03_KSWarmInit(void);
void fuel03_KSWakeup(void);
BOOLEAN fuel03_KSNvRamCheck(void);
/*
** The following should be called by the product specific fuel routines
** in FFUEL.C when it is necessary to start a fuel init, i.e. on
** a transition to RUN or after a high/low battery condition.
**
** If desired, the application can call this function whenever the
** ignition is OFF or ACC, so that when the ignition transitions into
** RUN the filter code is already primed to perform fuel init.
**
** It does not matter how many times this function is called as it
** is just initializing RAM to begin a fuel init.
*/
void fuel03_setup_for_init(void);

/* ---------------------------------------------------------------------------
** The following should be called by the product specific fuel routines
** in FFUEL.C on a periodic basis.  Do not call this function unless
** the filter should be iterated. For example, do not call in ignition
** OFF or in overvoltage conditions.
**
** The period at which this function is called depends on the type of
** fuel sender input -- network or hardwired.  In the network case,
** the function should be iterated whenever a new data message is received.
** In the hardwired case, the function should be iterated at a fixed rate,
** for example 100ms.
**
** The program subsystem engineer should provide requirements for when
** the filter should be iterated and at what rate.  The rate chosen will
** affect the values of many of the constants in the .CFG file.
**
** The first parameter (rada) in the call is for the SENDER A ratio'd A/D value.
**
** The second parameter should be TRUE when the cluster is in manufacturing
** test mode and wants the filter(s) to be jammed with the current A/D
** value.  This value should be set to FALSE otherwise.
** ---------------------------------------------------------------------------
*/
void fuel03_periodic_processing(UINT16 fuel03_rada, BOOLEAN fuel03_jam_filter);

/*
** The following should be called by the product specific fuel routines
** in FFUEL.C on a periodic basis when the ignition switch is off AND
** key-off fuel A/D sampling is required.  Do not call this function unless
** samples should be taken. For example, do not call in overvoltage
** conditions.
**
** The period at which this function is called depends on the type of
** fuel sender input -- network or hardwired.  In the network case,
** the function should be iterated whenever a new data message is received.
** However, it is very likely that the network is not active when the
** ignition switch is off, so this function will not be needed.
** In the hardwired case, the function should be iterated at a fixed rate,
** for example 100ms.
**
** The program subsystem engineer should provide requirements for when
** the filter should be iterated and at what rate.  The rate chosen will
** affect the values of many of the constants in the .CFG file.
**
** The first parameter in the call is for the ratio'd A/D value.
**
** The application must continue to call this function (i.e. not go to
** sleep) in OFF until the keyoff processing is complete.
*/
void fuel03_keyoff_processing(UINT16 fuel03_rada);
BOOLEAN fuel03_keyoff_processing_done( void );

/* ----------------------------------------------------------------------------
** The following should be called to get the percent full value of the
** sender(s) with and without hysteresis.
**
** Typically, the hysteresis value is used to turn on/off the low fuel
** warning light, and the non-hysteresis value is used for fuel gage
** position determination and for data for network transmission of the
** current fuel level.
**
** On single sender systems, the function returns the value for a single
** sender.  On dual sender systems, the function returns the combined value
** for both senders.
**
** These routines do not calculate anything as that is done by the periodic
** processing routines.  They can be called anytime to get the latest value.
**
** The return values are in SCP percent full units, i.e. 0 represents 0%
** full, and 254 represents 99.60% full.  A value of 255 is used to represent
** invalid data.  The MSB of the data represents the whole part of the
** percent full value, and the LSB represents remainder.
**
** ----------------------------------------------------------------------------
*/
UINT16 fuel03_get_fuel_level(void);
UINT16 fuel03_get_fuel_level_with_hys(void);
/*
** ----------------------------------------------------------------------------
 It would be called by application code when a CAN Diagnostics Clear DTCs
 (Service $14) command is received by the cluster regardless of wether Fuel DTCs are logged or not.
 This is executed only when called by application code, so in a sense it is "asynchronous".
*/
void fuel03_clear_DTC_resets(void);

/* ----------------------------------------------------------------------------
** The following should be called to get the individual SenderA and SenderB
** percent full values with or without hysteresis.
**
** The description of the above functions apply to these as well.
** ----------------------------------------------------------------------------
*/
UINT16 fuel03_get_senderA_PFH(void);
UINT16 fuel03_get_senderA_PF(void);

UINT8 fuel03_get_SenderA_unfiltered_flps( void );

/* ----------------------------------------------------------------------------
** The following function returns TRUE when fuel init is finished, FALSE
** otherwise.
**
** Once TRUE, it will remain true until the "fuel03_setup_for_init()"
** function is called.
** ----------------------------------------------------------------------------
*/
BOOLEAN fuel03_init_finished(void);

/*
** The following function returns TRUE if any sender is in fast fill, FALSE
** otherwise.
*/
BOOLEAN fuel03_fast_fill_active(void);
BOOLEAN fuel03_senderA_fast_fill_active(void);

/*
** This function wil return following status
** FUEL03_STATUS_FILL    (1)- if a fill is detected,
** FUEL03_STATUS_LOSS    (2)- if a loss is detected,
** FUEL03_STATUS_NORMAL  (3)- if there is no fill or loss is detected.

*/

UINT8 fuel03_fill_or_loss_status(void);
/*
** This function wil return following status
** FUEL03_STATUS_OPEN            (1)- if an open is detected,
** FUEL03_STATUS_SHORT           (2)- if an short is detected ,
** FUEL03_STATUS_NO_OPEN_SHORT   (3)- if there is no open or short is detected
*/

UINT8 fuel03_open_short_status(void);
/*
** Call the following function if the fuel A/D input comes from a network and
** the message containing the data is missing.  It is only necessary to call
** this once when the message is first declared missing.
**
** It is the applications responsibility to log any DTCs for missing messages
** that may be required.
*/
void fuel03_network_message_missing(void);
/*
** Various PID and diagnostic mode functions.  Some functions are
** not present if the .CFG file configures them out.
*/
UINT8 fuel03_C903_KSGetPID(UINT8 *);
UINT8 fuel03_C904_KSGetPID(UINT8 *);
UINT8 fuel03_C909_KSGetPID(UINT16 *);
UINT8 fuel03_C90A_KSGetPID(UINT16 *);
UINT8 fuel03_C90B_KSGetPID(UINT8 *);
UINT8 fuel03_C90C_KSGetPID(UINT16 *);
UINT8 fuel03_C90D_KSGetPID(UINT16 *);
UINT8 fuel03_6185_KSGetPID(void *);
UINT8 fuel03_6187_KSGetPID(void *);
void fuel03_KSDiagStartSelfTest(void);
void fuel03_KSDiagEpilog(void);
UINT8 fuel03_C90e_KSGetPID(UINT32 *);
UINT8 fuel03_C90f_KSGetPID(UINT16 *);
UINT8 fuel03_C910_KSGetPID(UINT32 *);
UINT8 fuel03_C911_KSGetPID(UINT16 *);
UINT8 fuel03_C912_KSGetPID( UINT8 *);
UINT8 fuel03_C913_KSGetPID( UINT8 *);
UINT8 fuel03_C914_KSGetPID( UINT8 *);
UINT8 fuel03_C915_KSGetPID( UINT8 *);

/*
** Use the following to get the CANFLPS value from the table contained
** in the config file. Note that you must pass the RAD value.
*/
UINT16 Fuel03_Get_CANFLPS( UINT16 radin );

/* --------------------------------------------------------------------------
** Bits used with Fuel03OptionsNVM.
** --------------------------------------------------------------------------
*/
#define FUEL03_HILL_HOLD_ENABLE_BIT   (0x80)
#define FUEL03_FAST_FILL_ENABLE_BIT   (0x40)
#define FUEL03_ZSS_REF_ONLY_BIT       (0x20)

UINT8 Fuel03_SenderA_keyon_avgflps( void );
UINT8 Fuel03_SenderA_KeyOffRef( void );
UINT8 Fuel03_SenderA_zss_ref( void );
UINT8 Fuel03_SenderA_keyon_good_samples( void );
UINT8 Fuel03_SenderA_ConvSample( void );

/*============================================================================
   P U B L I C   D A T A   A N D   A C C E S S   M A C R O S
=============================================================================*/


/*============================================================================
**
**  $Revision:   1.6  $
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
**  06/17/2014		RAGARWA1
**	Merge the N2.0 changes. RTC 168572 for reference.

** 11/04/2013      BVIJAYKU
** Added fuel03_KSNvRamCheck() for QAC warning deviation approval.

** 08/13/2013      BVIJAYKU
** Moved open/short, fill/loss and sample open/short macros from fuel03.c file.

** 02/04/2010      KNAGASUB
** Comments are update in following functions
** 1)fuel03_fill_or_loss_status()
** 2)fuel03_open_short_status()

** 02/03/2010      KNAGASUB
** fuel03_KSWarmInit(),fuel03_KSWakeup() added as per review comments.

** 10/28/10       BVIJAYKU.
** Updated Function description.
**
** 08/11/09       KNAGASUB.
** As per CQ BSDI00073307-Need memory optimized Fuel package for Newton1.5
** Following functions Removed:
** 1)BOOLEAN fuel03_fill_detected(void);
** 2)BOOLEAN fuel03_senderA_fill_detected(void);
** 3)BOOLEAN fuel03_loss_detected(void);
** 4)BOOLEAN fuel03_senderA_loss_detected(void);
** 5)BOOLEAN fuel03_senderA_open_short_detected(void);
** 6)BOOLEAN fuel03_senderA_open_detected(void);
** 7)BOOLEAN fuel03_senderA_short_detected(void);
** 8)Void fuel03_KSWarmInit(void);
** 9)void fuel03_KSWakeup(void);
** Following functions modified to provide the status of the event.
** 1) fuel03_fill_or_loss_status() used instead of fuel03_fill_or_loss_detected()
** 2)fuel03_open_short_status() used instead of fuel03_open_short_detected()
** application function should check the status and do the action accordingly.

** 08/11/09       KNAGASUB.
** The interface function name changed from Fuel03_clear_DTC_resets()  to fuel03_clear_DTC_resets()

** 24/11/08       KNAGASUB.
** The interface function name changed from Fuel03_clear_DTC_resets()  to fuel03_clear_DTC_resets()

** 19/11/08       KNAGASUB.
** The interface function name changed from Fuel03_clear_DTC_flimers()  to Fuel03_clear_DTC_resets()

**  28/10/08      KNAGASUB
**  new interface function Fuel03_clear_DTC_flimers() added as per fuel03_BDD1.4.doc

**  05/08/08      CNAGARA1
**  Added prototypes for C912,C913,C914 & C915 PID interface function per BSDI00055595
**
**  10/25/07      RRUSS1
**
**  Ref BSDI00050096 : Updated C90e - C911 interfaces.
**
**  02/28/07     JARUN   Added interfaces for P356 ETM mode.
**
**  9/21/05      RRUSS1
**
**  Ref BSDI00025533 : Changed the function interfaces for
**                     fuel03_6185_KSGetPID() and fuel03_6187_KSGetPID().
**
** 6/15/05        RRUSS1  BSDI00020719
**
** Moved NVM declarations to a seperate file for the ARM processor support so
** had to add certain bit flags here.
**
**  03/17/05     RRUSS1  Initial creation from fuel02 package.
**
**==========================================================================*/

/* end of file =============================================================*/

#endif


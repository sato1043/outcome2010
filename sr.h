/// sr.h
///   this is a header file for the simple slotmachine.
///

#ifndef __sr_h__
#define __sr_h__

/**
 * ssm_sr_bl_set
 * ssm_sr_bl_reset
 *  - set/reset SR.BL (state register b28: block bit)
 *
 * @param none
 * @return void
 * @see ut_sr.c
 */
void ssm_sr_bl_set();
void ssm_sr_bl_reset();

#endif/*__sr_h__*/

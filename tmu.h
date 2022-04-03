/// tmu.h
///   this is a header file for the simple slotmachine.
///

#ifndef __ssm_tmu_h__
#define __ssm_tmu_h__

#include <stdlib.h> //for size_t
#include <stdint.h> //for uintNN_t

#include "vbr.h"

#define SSM_TMU_QUIANTITY (3)
#define SSM_TMU_ID0 (0)
#define SSM_TMU_ID1 (1)
#define SSM_TMU_ID2 (2)

typedef volatile union ssm_tmu_strt_t_  ssm_tmu_strt_t;
typedef volatile union ssm_tmu_strt_t_* ssm_tmu_strt_tp;

union ssm_tmu_strt_t_
{
  uint8_t pattern;
  struct 
  {
    unsigned int tmu0 : 1 ;
    unsigned int tmu1 : 1 ;
    unsigned int tmu2 : 1 ;
    unsigned int      : 5 ;
  } b;
};

typedef volatile uint32_t   ssm_tmu_cnt_t;
typedef volatile uint32_t*  ssm_tmu_cnt_tp;

typedef ssm_tmu_cnt_t  ssm_tmu_tcor_t;
typedef ssm_tmu_cnt_tp ssm_tmu_tcor_tp;

typedef ssm_tmu_cnt_t  ssm_tmu_tcnt_t;
typedef ssm_tmu_cnt_tp ssm_tmu_tcnt_tp;

typedef ssm_tmu_cnt_t  ssm_tmu_tcpr_t;  //input capture TCLK (external clock???)
typedef ssm_tmu_cnt_tp ssm_tmu_tcpr_tp;

#define SSM_TMU_TCNT_MAX    ((ssm_tmu_cnt_t)0x7FFFFFFFL) /** 2,147,483,647 */

#define SSM_TMU_TCOR_P_FI   (33333400)

#define SSM_TMU_TCNT_P_FI_4     (8333350.       ) /** (P_FI/4)    */
#define SSM_TMU_TCNT_P_FI_16    (2083337.5      ) /** (P_FI/16)   */
#define SSM_TMU_TCNT_P_FI_64    ( 520834.375    ) /** (P_FI/64)   */
#define SSM_TMU_TCNT_P_FI_256   ( 130208.59375  ) /** (P_FI/256)  */
#define SSM_TMU_TCNT_P_FI_1024  (  32552.1484375) /** (P_FI/1024) */

#define SSM_TMU_TCNT_10USEC     (4)
#define SSM_TMU_TCNT_100USEC    (51)
#define SSM_TMU_TCNT_1MSEC      (519)
#define SSM_TMU_TCNT_10MSEC     (5207)
#define SSM_TMU_TCNT_100MSEC    (52072)
#define SSM_TMU_TCNT_1SEC       (520733)

typedef volatile union ssm_tmu_ctrl_t_  ssm_tmu_ctrl_t;
typedef volatile union ssm_tmu_ctrl_t_* ssm_tmu_ctrl_tp;

union ssm_tmu_ctrl_t_
{
  uint16_t pattern;
  struct 
  {
    unsigned int psc  : 3 ; /* p-fai */
    unsigned int cheg : 2 ; /* checking edge */
    unsigned int unie : 1 ; /* permit interruput by underflow  */
    unsigned int      : 2 ;
    unsigned int unf  : 1 ; /* underflow flag 1:occured */
    unsigned int      : 7 ;
  } b;
};

typedef volatile struct ssm_tmu_unit_t_  ssm_tmu_unit_t;
typedef volatile struct ssm_tmu_unit_t_* ssm_tmu_unit_tp;

struct ssm_tmu_unit_t_
{
  ssm_tmu_tcor_t tcor;
  ssm_tmu_tcnt_t tcnt;
  ssm_tmu_ctrl_t ctrl;
  ssm_tmu_tcpr_t tcpr;
};

typedef volatile struct ssm_tmu_unitp_t_  ssm_tmu_unitp_t;
typedef volatile struct ssm_tmu_unitp_t_* ssm_tmu_unitp_tp;

struct ssm_tmu_unitp_t_
{
  ssm_tmu_tcor_tp tcor_p;
  ssm_tmu_tcnt_tp tcnt_p;
  ssm_tmu_ctrl_tp ctrl_p;
  ssm_tmu_tcpr_tp tcpr_p;
};

typedef volatile union ssm_tmu_prio_t_  ssm_tmu_prio_t;
typedef volatile union ssm_tmu_prio_t_* ssm_tmu_prio_tp;

typedef uint8_t  ssm_tmu_prio_mask_t; // <= 15

union ssm_tmu_prio_t_
{
  uint16_t pattern;
  struct
  {
    unsigned int      : 4 ;
    unsigned int tmu2 : 4 ;
    unsigned int tmu1 : 4 ;
    unsigned int tmu0 : 4 ;
  } b;
};

typedef volatile struct ssm_tmu_ios_t_  ssm_tmu_ios_t;
typedef volatile struct ssm_tmu_ios_t_* ssm_tmu_ios_tp;

struct ssm_tmu_ios_t_
{
  ssm_tmu_strt_tp strt_p;
  ssm_tmu_unitp_t unit_p[SSM_TMU_QUIANTITY];
  ssm_tmu_prio_tp prio_p;
};

extern ssm_tmu_ios_t ssm_tmu_ios;

typedef volatile struct ssm_tmu_t_  ssm_tmu_t;
typedef volatile struct ssm_tmu_t_* ssm_tmu_tp;

struct ssm_tmu_t_
{
  ssm_tmu_strt_t strt;
  ssm_tmu_unit_t unit[SSM_TMU_QUIANTITY];
  ssm_tmu_prio_t prio;
};

extern ssm_tmu_t ssm_tmu;


/**
 *  ssm_tmuN_start
 *  ssm_tmuN_stop
 *   - start/stop timer unit. timer must be initialized.
 *
 *  @param n_tmu number of tmu unit N :  0<= n_tmu <= 3
 *  @return none
 */
void ssm_tmuN_start(size_t n_tmu);
void ssm_tmuN_stop(size_t n_tmu);

/**
 *  ssm_tmuN_init
 *   - intialize timer unit
 *
 *  @param n_tmu number of tmu unit N :  0<= n_tmu <= 3
 *  @param prio  interrupt priority mask level
 *  @param interval amount of time form interrupt to interrupt 
 *  @param tuniN interrupt handler function. if is null, no interrupt will occur.
 *  @return 0:succeed <0:failed
 */
int ssm_tmuN_init(
  size_t n_tmu
, ssm_tmu_prio_mask_t prio
, ssm_tmu_tcor_t interval
, ssm_vbr_call_f tuni);

/**
 * ssm_tmuN_wait_til_unf
 *
 *  @param n_tmu number of tmu unit N :  0<= n_tmu <= 3
 *  @return none
 */
void ssm_tmuN_wait_til_unf(size_t n_tmu);

/**
 * ssm_tmuN_tick
 *
 *  @param n_tmu number of tmu unit N :  0<= n_tmu <= 3
 *  @return current TCNTx
 */
ssm_tmu_tcnt_t ssm_tmuN_tick(size_t n_tmu);

/**
 * SSM_TMU_TUNI_NAME
 * SSM_TMU_DECLARE_TUNI
 *  - macro to declare exception handlers / use in headers
 * SSM_TMU_BEGIN_IMPLEMENT_TUNI
 * SSM_TMU_END_IMPLEMENT_TUNI
 *  - macro to implement exception handlers / use in sources
 *
 * @param id_  SSM_TMU_IDx (x=0-2)
 * @param name_ own handler name
 * @return none
 * @see test/ut_tmu.c
 *
 * SSM_TMU_DECLARE_TUNI(SSM_TMU_ID0,000);
 *
 * #ifndef IN_LOCAL
 * #pragma interrupt
 * #endif
 * SSM_TMU_BEGIN_IMPLEMENT_TUNI(SSM_TMU_ID0,000);
 * {
 *   int i =0;
 *   i = i;
 * }
 * SSM_TMU_END_IMPLEMENT_TUNI();
 */
#define SSM_TMU_TUNI_NAME(name_) \
ssm_tmu_tuni_##name_

#define SSM_TMU_DECLARE_TUNI(id_,name_) \
void SSM_TMU_TUNI_NAME(name_)()

#define SSM_TMU_BEGIN_IMPLEMENT_TUNI(id_,name_) \
void SSM_TMU_TUNI_NAME(name_)() \
{                                                \
  /* アンダーフロー(b8)フラグをリセット */       \
  /* これを行わないと再度割り込みが発生する */   \
  ssm_tmu.unit[id_].ctrl.pattern               \
    =ssm_tmu_ios.unit_p[id_].ctrl_p->pattern;  \
  ssm_tmu.unit[id_].ctrl.b.unf =0;             \
  ssm_tmu_ios.unit_p[id_].ctrl_p->pattern      \
    =ssm_tmu.unit[id_].ctrl.pattern;

#define SSM_TMU_END_IMPLEMENT_TUNI(dummy) \
}

///----------------------------------------------------

#define ssm_tmu0_init(prio_,interval_,tuni_) \
              ssm_tmuN_init(SSM_TMU_ID0,prio_,interval_,tuni_)
#define ssm_tmu0_start(a) ssm_tmuN_start(SSM_TMU_ID0)
#define ssm_tmu0_stop(a)  ssm_tmuN_stop(SSM_TMU_ID0)
#define ssm_tmu0_tick(a)  ssm_tmuN_tick(SSM_TMU_ID0)

#define ssm_tmu1_init(prio_,interval_,tuni_) \
              ssm_tmuN_init(SSM_TMU_ID1,prio_,interval_,tuni_)
#define ssm_tmu1_start(a) ssm_tmuN_start(SSM_TMU_ID1)
#define ssm_tmu1_stop(a)  ssm_tmuN_stop(SSM_TMU_ID1)
#define ssm_tmu1_tick(a)  ssm_tmuN_tick(SSM_TMU_ID1)

#define ssm_tmu2_init(prio_,interval_,tuni_) \
              ssm_tmuN_init(SSM_TMU_ID2,prio_,interval_,tuni_)
#define ssm_tmu2_start(a) ssm_tmuN_start(SSM_TMU_ID2)
#define ssm_tmu2_stop(a)  ssm_tmuN_stop(SSM_TMU_ID2)
#define ssm_tmu2_tick(a)  ssm_tmuN_tick(SSM_TMU_ID2)

#endif/*__ssm_tmu_h__*/

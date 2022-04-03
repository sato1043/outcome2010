/// tmu.c
///   this is a implementation for the simple slotmachine.
///

#include "settings.h"

#include "sr.h"
#include "vbr.h"
#include "tmu.h"
#include "util.h"

#include <assert.h> //for assert
#include <string.h> //for memset

#if IN_LOCAL
#include <signal.h> //for create_timer
#include <time.h>

#define CLOCKID CLOCK_REALTIME
#define SIG SIGRTMIN

timer_t timerid =0;
struct itimerspec init_its; //the new initial value and the new interval for the timer
struct itimerspec curr_its[SSM_TMU_QUIANTITY]; // the time until next expiration, and the interval

static void ssm_tmu_debug_handler(int sig, siginfo_t *si, void *uc)
{
  long long curr_tcnt;
  size_t n_tmu;
  for (n_tmu =0; n_tmu <SSM_TMU_QUIANTITY; ++n_tmu)
  {
    if (!(ssm_tmu.strt.pattern & (1<<n_tmu)))
      continue;

    curr_tcnt =
      (curr_its[n_tmu].it_value.tv_sec - init_its.it_interval.tv_sec)
        * 1000000000LL
        + curr_its[n_tmu].it_value.tv_nsec
        - init_its.it_interval.tv_nsec;

    if (curr_tcnt<=0)
    {
      curr_its[n_tmu].it_value.tv_sec  =curr_its[n_tmu].it_interval.tv_sec;
      curr_its[n_tmu].it_value.tv_nsec =curr_its[n_tmu].it_interval.tv_nsec;

      ssm_tmu.unit[n_tmu].tcnt =ssm_tmu.unit[n_tmu].tcor;
      ssm_tmu.unit[n_tmu].ctrl.b.unf =1;
      if (ssm_vbr_get(SSM_VBR_EVT_400+n_tmu))
        (ssm_vbr_get(SSM_VBR_EVT_400+n_tmu))();
    }
    else
    {
      curr_its[n_tmu].it_value.tv_sec  = curr_tcnt / 100000000;
      curr_its[n_tmu].it_value.tv_nsec = curr_tcnt % 100000000;

      ssm_tmu.unit[n_tmu].tcnt = (curr_tcnt/10000)>>2;
    }
  }
}

ssm_tmu_ios_t ssm_tmu_ios = 
{
  (ssm_tmu_strt_tp)&ssm_tmu.strt
, {
    /* tmu0 */ { (ssm_tmu_tcor_tp)&ssm_tmu.unit[0].tcor
                ,(ssm_tmu_tcnt_tp)&ssm_tmu.unit[0].tcnt
                ,(ssm_tmu_ctrl_tp)&ssm_tmu.unit[0].ctrl
                ,(ssm_tmu_tcpr_tp)&ssm_tmu.unit[0].tcpr}
   ,/* tmu1 */ { (ssm_tmu_tcor_tp)&ssm_tmu.unit[1].tcor
                ,(ssm_tmu_tcnt_tp)&ssm_tmu.unit[1].tcnt
                ,(ssm_tmu_ctrl_tp)&ssm_tmu.unit[1].ctrl
                ,(ssm_tmu_tcpr_tp)&ssm_tmu.unit[1].tcpr}
   ,/* tmu2 */ { (ssm_tmu_tcor_tp)&ssm_tmu.unit[2].tcor
                ,(ssm_tmu_tcnt_tp)&ssm_tmu.unit[2].tcnt
                ,(ssm_tmu_ctrl_tp)&ssm_tmu.unit[2].ctrl
                ,(ssm_tmu_tcpr_tp)&ssm_tmu.unit[2].tcpr}
  }
, (ssm_tmu_prio_tp)&ssm_tmu.prio
};

#else
ssm_tmu_ios_t ssm_tmu_ios = 
{
    (ssm_tmu_strt_tp)0xFFD80004
  , {
      /* tmu0 */ { (ssm_tmu_tcor_tp)0xFFD80008 
                  ,(ssm_tmu_tcnt_tp)0xFFD8000C
                  ,(ssm_tmu_ctrl_tp)0xFFD80010
                  ,(ssm_tmu_tcpr_tp)0x00000000 }
    , /* tmu1 */ { (ssm_tmu_tcor_tp)0xFFD80014
                  ,(ssm_tmu_tcnt_tp)0xFFD80018
                  ,(ssm_tmu_ctrl_tp)0xFFD8001C
                  ,(ssm_tmu_tcpr_tp)0x00000000 }
    , /* tmu2 */ { (ssm_tmu_tcor_tp)0xFFD80020
                  ,(ssm_tmu_tcnt_tp)0xFFD80024
                  ,(ssm_tmu_ctrl_tp)0xFFD80028
                  ,(ssm_tmu_tcpr_tp)0xFFD8002C }
    }
  , (ssm_tmu_prio_tp)0xFFD00004
}; 
#endif

ssm_tmu_t ssm_tmu;

inline void ssm_tmuN_start(size_t n_tmu)
{
  ssm_tmu.strt.pattern =ssm_tmu_ios.strt_p->pattern;

  switch(n_tmu)
  {
    case SSM_TMU_ID0: ssm_tmu.strt.b.tmu0 =1; break;
    case SSM_TMU_ID1: ssm_tmu.strt.b.tmu1 =1; break;
    case SSM_TMU_ID2: ssm_tmu.strt.b.tmu2 =1; break;
  }

  ssm_tmu_ios.strt_p->pattern =ssm_tmu.strt.pattern;
}

inline void ssm_tmuN_stop(size_t n_tmu)
{
  ssm_tmu.strt.pattern =ssm_tmu_ios.strt_p->pattern;

  switch(n_tmu)
  {
    case SSM_TMU_ID0: ssm_tmu.strt.b.tmu0 =0; break;
    case SSM_TMU_ID1: ssm_tmu.strt.b.tmu1 =0; break;
    case SSM_TMU_ID2: ssm_tmu.strt.b.tmu2 =0; break;
  }

  ssm_tmu_ios.strt_p->pattern =ssm_tmu.strt.pattern;
}

inline int ssm_tmuN_term()
{
#if IN_LOCAL
  size_t n_tmu;
  for (n_tmu =0; n_tmu<SSM_TMU_QUIANTITY; ++n_tmu)
  {
    if (ssm_tmu.strt.pattern & (1<<n_tmu)) break;
  }
  if (n_tmu == SSM_TMU_QUIANTITY)
  {
    if (timer_delete(timerid) == -1)
      return -1;
    timerid =0;
  }
#endif
  return 0;
}

inline int ssm_tmuN_init(
  size_t n_tmu
, ssm_tmu_prio_mask_t prio
, ssm_tmu_tcor_t interval
, ssm_vbr_call_f tuni
)
{
  assert(prio <= 15);
  if (15 < prio) return -1;

  ssm_tmuN_stop(n_tmu);

  ssm_tmu.unit[n_tmu].ctrl.pattern
    =ssm_tmu_ios.unit_p[n_tmu].ctrl_p->pattern;

  ssm_tmu.unit[n_tmu].ctrl.b.psc  =2; 
  ssm_tmu.unit[n_tmu].ctrl.b.cheg =0; 
  ssm_tmu.unit[n_tmu].ctrl.b.unf  =0; 

  if (tuni)
  {
    ssm_vbr_set(SSM_VBR_EVT_400+n_tmu,tuni);
    ssm_tmu.unit[n_tmu].ctrl.b.unie =1; 
  }
  else
  {
    ssm_vbr_set(SSM_VBR_EVT_400+n_tmu,SSM_VBR_CALL_NONE);
    ssm_tmu.unit[n_tmu].ctrl.b.unie =0; 
  }

#if IN_LOCAL
  if (!timerid)
  {
    struct sigaction sa;
    struct sigevent sev;
    memset(&sa, 0,sizeof(struct sigaction));
    memset(&sev,0,sizeof(struct sigevent));
    memset(&init_its,0,sizeof(struct itimerspec));
    memset(&curr_its,0,sizeof(curr_its));

    sa.sa_flags = SA_SIGINFO;
    sa.sa_sigaction = ssm_tmu_debug_handler;
    sigemptyset(&sa.sa_mask);
    if (sigaction(SIG, &sa, NULL) == -1)
      return -1;

    sev.sigev_notify =SIGEV_SIGNAL;
    sev.sigev_signo  =SIG;
    if (timer_create(CLOCKID, &sev, &timerid) == -1)
      return -1;

    init_its.it_value.tv_sec  =      0;
    init_its.it_value.tv_nsec =1000000;
    init_its.it_interval.tv_sec  =init_its.it_value.tv_sec;
    init_its.it_interval.tv_nsec =init_its.it_value.tv_nsec;
    if (timer_settime(timerid, 0, &init_its, NULL) == -1)
      return -1;
  }

  curr_its[n_tmu].it_value.tv_sec  =(interval >>2) / 100000;
  curr_its[n_tmu].it_value.tv_nsec =(interval >>2) % 100000 * 1000;
  curr_its[n_tmu].it_interval.tv_sec  =curr_its[n_tmu].it_value.tv_sec;
  curr_its[n_tmu].it_interval.tv_nsec =curr_its[n_tmu].it_value.tv_nsec;
#endif

  ssm_tmu_ios.unit_p[n_tmu].ctrl_p->pattern
    =ssm_tmu.unit[n_tmu].ctrl.pattern;

  *(ssm_tmu_ios.unit_p[n_tmu].tcnt_p)     // タイマカウンタ（初期値）
    =*(ssm_tmu_ios.unit_p[n_tmu].tcor_p)  // タイムコンスタントレジスト（オーバーロード時）
      =interval;

  //割り込み優先レベルを変えるときは SR.BL=1にしないといけない。
  //この間に、並列で一般例外を起こさないこと。リセットします。
  //ssm_sr_bl_set();

  ssm_tmu.prio.pattern =ssm_tmu_ios.prio_p->pattern;

  switch(n_tmu)
  {
    case SSM_TMU_ID0: ssm_tmu.prio.b.tmu0 =prio; break;
    case SSM_TMU_ID1: ssm_tmu.prio.b.tmu1 =prio; break;
    case SSM_TMU_ID2: ssm_tmu.prio.b.tmu2 =prio; break;
  }

  ssm_tmu_ios.prio_p->pattern =ssm_tmu.prio.pattern;

  //ssm_sr_bl_reset();

  return 0;
}

inline void ssm_tmuN_wait_til_unf(size_t n_tmu)
{
  ssm_tmuN_start(n_tmu);

  while (
    ssm_tmu.unit[n_tmu].ctrl.pattern
     =ssm_tmu_ios.unit_p[n_tmu].ctrl_p->pattern
      , !ssm_tmu.unit[n_tmu].ctrl.b.unf)
    ;

  ssm_tmu.unit[n_tmu].ctrl.b.unf =0;

  ssm_tmu_ios.unit_p[n_tmu].ctrl_p->pattern
    =ssm_tmu.unit[n_tmu].ctrl.pattern;

  ssm_tmuN_stop(n_tmu);
}

inline ssm_tmu_tcnt_t ssm_tmuN_tick(size_t n_tmu)
{
  return *(ssm_tmu_ios.unit_p[n_tmu].tcnt_p);
}


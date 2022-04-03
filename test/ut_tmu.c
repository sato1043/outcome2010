#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include <limits.h>
#include <unistd.h>

#include "tmu.h"

extern ssm_tmu_ios_t ssm_tmu_ios;

#if 0
int ssm_ut_tmu_XXXXXX()
{
  return 1;
}
#endif

int ssm_ut_tmu_strt()
{
  ssm_tmu_strt_t strt ={0x00};
  assert(strt.pattern == 0x00);
  strt.b.tmu0 =1;
  assert(strt.pattern == 0x01);
  strt.b.tmu1 =1;
  assert(strt.pattern == 0x03);
  strt.b.tmu2 =1;
  assert(strt.pattern == 0x07);
  return 1;
}

int ssm_ut_tmu_cnt()
{
  ssm_tmu_cnt_t n =0;
  assert(n==0);

  n =ULONG_MAX;
  assert(n==ULONG_MAX);

  n =SSM_TMU_TCNT_MAX+ SSM_TMU_TCNT_MAX;
  assert(n<=ULONG_MAX);

  return 1;
}

int ssm_ut_tmu_ctrl()
{
  ssm_tmu_ctrl_t ctrl ={0x0000};
  assert(ctrl.pattern == 0x0000);
  ctrl.b.psc =7;
  assert(ctrl.pattern == 0x0007);
  ctrl.b.cheg =3;
  assert(ctrl.pattern == 0x001f);
  ctrl.b.unie =1;
  assert(ctrl.pattern == 0x003f);
  ctrl.b.unf =1;
  assert(ctrl.pattern == 0x013f);
  return 1;
}

int ssm_ut_tmu_prio()
{
  ssm_tmu_prio_t prio ={0x00};
  assert(prio.pattern == 0x00);
  prio.b.tmu0 =0xf;
  assert(prio.pattern == 0xf000);
  prio.b.tmu1 =0xf;
  assert(prio.pattern == 0xff00);
  prio.b.tmu2 =0xf;
  assert(prio.pattern == 0xfff0);
  return 1;
}

int ssm_ut_tmu_init()
{
  ssm_tmuN_init(SSM_TMU_ID0,10,SSM_TMU_TCNT_1SEC,0);
  return 1;
}

int ssm_ut_tmu_startstop()
{
  ssm_tmuN_init(SSM_TMU_ID0,10,SSM_TMU_TCNT_1SEC,0);
  ssm_tmuN_start(SSM_TMU_ID0);
  ssm_tmuN_stop(SSM_TMU_ID0);
  return 1;
}

int ssm_ut_tmu_wait()
{
  ssm_tmuN_init(SSM_TMU_ID0,10,SSM_TMU_TCNT_1SEC,0);
  ssm_tmuN_wait_til_unf(SSM_TMU_ID0);
  return 1;
}

int ssm_ut_tmu_tick()
{
  ssm_tmu_tcnt_t cnt ,store;

  ssm_tmuN_init(SSM_TMU_ID0,10,SSM_TMU_TCNT_1SEC,0);
  ssm_tmuN_start(SSM_TMU_ID0);
  store =cnt =ssm_tmuN_tick(SSM_TMU_ID0);
  usleep(1000);
  cnt+=ssm_tmuN_tick(SSM_TMU_ID0);
  usleep(1000);
  cnt+=ssm_tmuN_tick(SSM_TMU_ID0);
  usleep(1000);
  cnt+=ssm_tmuN_tick(SSM_TMU_ID0);
  usleep(1000);
  cnt =cnt>>2;
  assert(cnt!=store);
  ssm_tmuN_stop(SSM_TMU_ID0);
  return 1;
}

static int test_is_break =0;

SSM_TMU_DECLARE_TUNI(SSM_TMU_ID0,dummy0);

#ifndef IN_LOCAL
#pragma interrupt
#endif
SSM_TMU_BEGIN_IMPLEMENT_TUNI(SSM_TMU_ID0,dummy0);
{
  ++test_is_break;
}
SSM_TMU_END_IMPLEMENT_TUNI();

int ssm_ut_tmu_tuni()
{
  test_is_break =0;
  ssm_tmuN_init(SSM_TMU_ID0,10,
      SSM_TMU_TCNT_1SEC, SSM_TMU_TUNI_NAME(dummy0));
  ssm_tmuN_start(SSM_TMU_ID0);
  while (test_is_break<3)
    ;
  assert(1<=test_is_break);
  ssm_tmuN_stop(SSM_TMU_ID0);
  return 1;
}

int ssm_ut_tmu_tmu0()
{
  test_is_break =0;
  ssm_tmu0_init(10, SSM_TMU_TCNT_1SEC, SSM_TMU_TUNI_NAME(dummy0));
  ssm_tmu0_start();
  while (!test_is_break)
    ;
  assert(1<=test_is_break);
  ssm_tmu0_stop();
  return 1;
}

static int test_is_break1 =0;

#ifndef IN_LOCAL
#pragma interrupt
#endif
SSM_TMU_BEGIN_IMPLEMENT_TUNI(SSM_TMU_ID1,dummy1);
{
  ++test_is_break1;
}
SSM_TMU_END_IMPLEMENT_TUNI();

int ssm_ut_tmu_tmu1()
{
  test_is_break1 =0;
  ssm_tmu1_init(10, SSM_TMU_TCNT_1SEC, SSM_TMU_TUNI_NAME(dummy1));
  ssm_tmu1_start();
  while (!test_is_break1)
    ;
  assert(1<=test_is_break1);
  ssm_tmu1_stop();
  return 1;
}

static int test_is_break2 =0;

#ifndef IN_LOCAL
#pragma interrupt
#endif
SSM_TMU_BEGIN_IMPLEMENT_TUNI(SSM_TMU_ID2,dummy2);
{
  ++test_is_break2;
}
SSM_TMU_END_IMPLEMENT_TUNI();

int ssm_ut_tmu_tmu2()
{
  test_is_break2 =0;
  ssm_tmu2_init(10, SSM_TMU_TCNT_1SEC, SSM_TMU_TUNI_NAME(dummy2));
  ssm_tmu2_start();
  while (!test_is_break2)
    sleep(1);
  assert(1<=test_is_break2);
  ssm_tmu2_stop();
  return 1;
}

int ssm_ut_tmu_tmu01()
{
  test_is_break =0;
  test_is_break1 =0;

  ssm_tmu0_init(10, SSM_TMU_TCNT_1SEC, SSM_TMU_TUNI_NAME(dummy0));
  ssm_tmu1_init(10, SSM_TMU_TCNT_1SEC, SSM_TMU_TUNI_NAME(dummy1));
  ssm_tmu0_start();
  ssm_tmu1_start();

  while (test_is_break<3)
    ;

  while (!test_is_break1)
    ;

  assert(3<=test_is_break);
  assert(1<=test_is_break1);

  ssm_tmu0_stop();
  ssm_tmu1_stop();

  return 1;
}

int ssm_ut_tmu_tmu02()
{
  test_is_break =0;
  test_is_break2 =0;

  ssm_tmu0_init(10, SSM_TMU_TCNT_1SEC, SSM_TMU_TUNI_NAME(dummy0));
  ssm_tmu2_init(10, SSM_TMU_TCNT_1SEC, SSM_TMU_TUNI_NAME(dummy2));
  ssm_tmu0_start();
  ssm_tmu2_start();

  while (test_is_break<3)
    ;

  while (!test_is_break2)
    ;

  assert(3<=test_is_break);
  assert(1<=test_is_break2);

  ssm_tmu0_stop();
  ssm_tmu2_stop();

  return 1;
}

int ssm_ut_tmu_tmu12()
{
  test_is_break2 =0;
  test_is_break1 =0;

  ssm_tmu2_init(10, SSM_TMU_TCNT_1SEC, SSM_TMU_TUNI_NAME(dummy2));
  ssm_tmu1_init(10, SSM_TMU_TCNT_1SEC, SSM_TMU_TUNI_NAME(dummy1));
  ssm_tmu2_start();
  ssm_tmu1_start();

  while (test_is_break2<3)
    ;

  while (!test_is_break1)
    ;

  assert(3<=test_is_break2);
  assert(1<=test_is_break1);

  ssm_tmu2_stop();
  ssm_tmu1_stop();

  return 1;
}

int ssm_ut_tmu_tmu012()
{
  test_is_break2 =0;
  test_is_break1 =0;
  test_is_break  =0;

  ssm_tmu2_init(10, SSM_TMU_TCNT_1SEC, SSM_TMU_TUNI_NAME(dummy2));
  ssm_tmu1_init(10, SSM_TMU_TCNT_1SEC, SSM_TMU_TUNI_NAME(dummy1));
  ssm_tmu0_init(10, SSM_TMU_TCNT_1SEC, SSM_TMU_TUNI_NAME(dummy0));
  ssm_tmu2_start();
  ssm_tmu1_start();
  ssm_tmu0_start();

  while (test_is_break2< 5)
    ;

  while (test_is_break1< 3)
    ;

  while (test_is_break < 1)
    ;

  assert( 5<=test_is_break2);
  assert( 3<=test_is_break1);
  assert( 1<=test_is_break );

  ssm_tmu2_stop();
  ssm_tmu1_stop();
  ssm_tmu0_stop();

  return 1;
}

int ssm_ut_tmu()
{
  int result =0;

  //result +=ssm_ut_tmu_XXXXXX();
  result +=ssm_ut_tmu_strt();
  result +=ssm_ut_tmu_cnt();
  result +=ssm_ut_tmu_ctrl();
  result +=ssm_ut_tmu_prio();
  result +=ssm_ut_tmu_init();
  result +=ssm_ut_tmu_startstop();
  result +=ssm_ut_tmu_tick();
  result +=ssm_ut_tmu_wait();
  result +=ssm_ut_tmu_tuni();

  result +=ssm_ut_tmu_tmu0();
  result +=ssm_ut_tmu_tmu1();
  result +=ssm_ut_tmu_tmu2();
  result +=ssm_ut_tmu_tmu01();
  result +=ssm_ut_tmu_tmu02();
  result +=ssm_ut_tmu_tmu12();
  result +=ssm_ut_tmu_tmu012();

  printf("ut_tmu ::: total %d test(s) succeeded. :::\n" ,result);

  return result;
}

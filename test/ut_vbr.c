#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "vbr.h"

volatile int trap_result =0;

#if 0
int ssm_ut_vbr_XXXXXX()
{
  return 1;
}
#endif

#ifndef IN_LOCAL
#pragma interrupt
#endif
void ssm_ut_vbr_dummy_call()
{
  trap_result =1;
}

int ssm_ut_vbr_set()
{
  trap_result =0;
  ssm_vbr_set(SSM_VBR_EVT_400,ssm_ut_vbr_dummy_call);
  ssm_vbr_set(SSM_VBR_EVT_400,SSM_VBR_CALL_NONE);
  return 1;
}

int ssm_ut_vbr_trp_set()
{
  trap_result =0;

  ssm_vbr_trp_set(SSM_VBR_EVT_T000,ssm_ut_vbr_dummy_call);
  trapa(0);
  assert(trap_result==1);
  ssm_vbr_trp_set(SSM_VBR_EVT_T000,SSM_VBR_CALL_NONE);

  trap_result =0;

  ssm_vbr_trp_set(SSM_VBR_EVT_T128,ssm_ut_vbr_dummy_call);
  trapa(SSM_VBR_EVT_T128);
  assert(trap_result==1);
  ssm_vbr_trp_set(SSM_VBR_EVT_T128,SSM_VBR_CALL_NONE);

  return 1;
}

int ssm_ut_vbr()
{
  int result =0;

  //result +=ssm_ut_vbr_XXXXXX();
  result +=ssm_ut_vbr_set();
  result +=ssm_ut_vbr_trp_set();

  printf("ut_vbr ::: total %d test(s) succeeded. :::\n" ,result);

  return result;
}


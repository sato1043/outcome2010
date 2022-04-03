#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "settings.h"
#include "util.h"

#include "swth.h"
#include "inpt.h"

#if 0
int ssm_ut_inpt_XXXX()
{
  return 1;
}
#endif

int ssm_ut_inpt_init()
{
  ssm_inpt_init(SSM_FRAME_RATE);
  ssm_inpt_term();
  return 1;
}

int ssm_ut_inpt_add_swth()
{
  ssm_inpt_init(SSM_FRAME_RATE);

  ssm_swth_t swth1;
  ssm_swth_val_t val1={{{0x00},0}};
  ssm_swth_init(&swth1,SSM_SWTH_TYPE_PBTN,&val1);

  ssm_inpt_add_swth(&swth1);
  assert(ssm_inpt.n_quantity == 1);
  assert(ssm_inpt.swth_arr[0] == &swth1);
  assert(ssm_inpt.swth_arr[1] == 0);
  assert(ssm_inpt.swth_arr[2] == 0);
  assert(ssm_inpt.swth_arr[3] == 0);

  ssm_wait_ms(1000);

  ssm_inpt_term();
  return 1;
}

int ssm_ut_inpt_rm_swth()
{
  ssm_inpt_init(SSM_FRAME_RATE);

  ssm_swth_t swth1;
  ssm_swth_val_t val1={{{0x00},0}};
  ssm_swth_init(&swth1,SSM_SWTH_TYPE_PBTN,&val1);

  ssm_swth_t swth2;
  ssm_swth_val_t val2={{{0x00},1}};
  ssm_swth_init(&swth2,SSM_SWTH_TYPE_PBTN,&val2);

  ssm_swth_t swth3;
  ssm_swth_val_t val3={{{0x00},2}};
  ssm_swth_init(&swth3,SSM_SWTH_TYPE_PBTN,&val3);

  ssm_inpt_add_swth(&swth1);
  ssm_inpt_add_swth(&swth2);
  ssm_inpt_add_swth(&swth3);
  assert(ssm_inpt.n_quantity == 3);
  assert(ssm_inpt.swth_arr[0] == &swth1);
  assert(ssm_inpt.swth_arr[1] == &swth2);
  assert(ssm_inpt.swth_arr[2] == &swth3);
  assert(ssm_inpt.swth_arr[3] == 0);

  ssm_wait_ms(1000);

  ssm_inpt_rm_swth(&swth2);
  assert(ssm_inpt.n_quantity == 2);
  assert(ssm_inpt.swth_arr[0] == &swth1);
  assert(ssm_inpt.swth_arr[1] == &swth3);
  assert(ssm_inpt.swth_arr[2] == 0);
  assert(ssm_inpt.swth_arr[3] == 0);

  ssm_inpt_rm_swth(&swth1);
  assert(ssm_inpt.n_quantity == 1);
  assert(ssm_inpt.swth_arr[0] == &swth3);
  assert(ssm_inpt.swth_arr[1] == 0);
  assert(ssm_inpt.swth_arr[2] == 0);
  assert(ssm_inpt.swth_arr[3] == 0);

  ssm_inpt_rm_swth(&swth1);
  assert(ssm_inpt.n_quantity == 1);
  assert(ssm_inpt.swth_arr[0] == &swth3);
  assert(ssm_inpt.swth_arr[1] == 0);
  assert(ssm_inpt.swth_arr[2] == 0);
  assert(ssm_inpt.swth_arr[3] == 0);

  ssm_inpt_rm_swth(&swth3);
  assert(ssm_inpt.n_quantity == 0);
  assert(ssm_inpt.swth_arr[0] == 0);
  assert(ssm_inpt.swth_arr[1] == 0);
  assert(ssm_inpt.swth_arr[2] == 0);
  assert(ssm_inpt.swth_arr[3] == 0);

  ssm_wait_ms(1000);

  ssm_inpt_term();
  return 1;
}

int ssm_ut_inpt()
{
  int result =0;

  result +=ssm_ut_inpt_init();
  result +=ssm_ut_inpt_add_swth();
  result +=ssm_ut_inpt_rm_swth();

  printf("ut_inpt ::: total %d test(s) succeeded. :::\n" ,result);

  return result;
}


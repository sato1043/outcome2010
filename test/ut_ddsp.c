#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "settings.h"
#include "util.h"
#include "led.h"

#include "ddsp.h"

#if 0
int ssm_ut_ddsp_XXXX()
{
  return 1;
}
#endif

int ssm_ut_ddsp_init()
{
  ssm_ddsp_init(SSM_FRAME_RATE);
  ssm_ddsp_term();
  return 1;
}

int ssm_ut_ddsp_add_leds()
{
  ssm_ddsp_init(SSM_FRAME_RATE);

  ssm_leds_t leds1;
  ssm_leds_init(&leds1,SSM_LEDS_TYPE_GNRL,0,0);
  leds1.bits.gnrl.pattern =0xff;

  ssm_ddsp_add_leds(&leds1);
  assert(ssm_ddsp.n_quantity == 1);
  assert(ssm_ddsp.leds_arr[0] == &leds1);
  assert(ssm_ddsp.leds_arr[1] == 0);
  assert(ssm_ddsp.leds_arr[2] == 0);

  ssm_wait_ms(1000);

  ssm_ddsp_term();
  return 1;
}

int ssm_ut_ddsp_rm_leds()
{
  ssm_ddsp_init(SSM_FRAME_RATE);

  ssm_leds_t leds1;
  ssm_leds_init(&leds1,SSM_LEDS_TYPE_GNRL,0,0);
  leds1.bits.gnrl.pattern =0xff;

  ssm_leds_t leds2;
  ssm_leds_init(&leds2,SSM_LEDS_TYPE_SEG7,0,0);
  leds2.bits.seg7.pattern =0xff;

  ssm_leds_t leds3;
  ssm_leds_init(&leds3,SSM_LEDS_TYPE_SEG7,0,0);
  leds3.bits.seg7.pattern =0xff;

  ssm_ddsp_add_leds(&leds1);
  ssm_ddsp_add_leds(&leds2);
  ssm_ddsp_add_leds(&leds3);
  assert(ssm_ddsp.n_quantity == 3);
  assert(ssm_ddsp.leds_arr[0] == &leds1);
  assert(ssm_ddsp.leds_arr[1] == &leds2);
  assert(ssm_ddsp.leds_arr[2] == &leds3);

  ssm_wait_ms(1000);

  ssm_ddsp_rm_leds(&leds2);
  assert(ssm_ddsp.n_quantity == 2);
  assert(ssm_ddsp.leds_arr[0] == &leds1);
  assert(ssm_ddsp.leds_arr[1] == &leds3);
  assert(ssm_ddsp.leds_arr[2] == 0);

  ssm_ddsp_rm_leds(&leds1);
  assert(ssm_ddsp.n_quantity == 1);
  assert(ssm_ddsp.leds_arr[0] == &leds3);
  assert(ssm_ddsp.leds_arr[1] == 0);
  assert(ssm_ddsp.leds_arr[2] == 0);

  ssm_ddsp_rm_leds(&leds1);
  assert(ssm_ddsp.n_quantity == 1);
  assert(ssm_ddsp.leds_arr[0] == &leds3);
  assert(ssm_ddsp.leds_arr[1] == 0);
  assert(ssm_ddsp.leds_arr[2] == 0);

  ssm_ddsp_rm_leds(&leds3);
  assert(ssm_ddsp.n_quantity == 0);
  assert(ssm_ddsp.leds_arr[0] == 0);
  assert(ssm_ddsp.leds_arr[1] == 0);
  assert(ssm_ddsp.leds_arr[2] == 0);

  ssm_wait_ms(1000);

  ssm_ddsp_term();
  return 1;
}

int ssm_ut_ddsp()
{
  int result =0;

  result +=ssm_ut_ddsp_init();
  result +=ssm_ut_ddsp_add_leds();
  result +=ssm_ut_ddsp_rm_leds();

  printf("ut_ddsp ::: total %d test(s) succeeded. :::\n" ,result);

  return result;
}

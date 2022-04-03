#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "settings.h"
#include "util.h"

#include "swth.h"

#include "ctx.h"

#if 0
int ssm_ut_swth_XXXX()
{
  return 1;
}
#endif

int ssm_ut_swth_val_pbth()
{
  ssm_ctx_init();

  leds_arr[0].bits.seg7.pattern =0xff;
  leds_arr[1].bits.seg7.pattern =0xff;
  leds_arr[2].bits.seg7.pattern =0xff;
  leds_arr[3].bits.gnrl.pattern =0xff;

  forever()
  {
    if (ssm_swth_val_pbtn_is_on(&swth_arr[0].val))
      break;
      //leds_arr[0].bits.gnrl.pattern = ~leds_arr[0].bits.seg7.pattern;
    if (ssm_swth_val_pbtn_is_on(&swth_arr[1].val))
      leds_arr[1].bits.seg7.pattern = ~leds_arr[1].bits.seg7.pattern;
    if (ssm_swth_val_pbtn_is_on(&swth_arr[2].val))
      leds_arr[2].bits.seg7.pattern = ~leds_arr[2].bits.seg7.pattern;
    if (ssm_swth_val_pbtn_is_on(&swth_arr[3].val))
      leds_arr[3].bits.seg7.pattern = ~leds_arr[3].bits.gnrl.pattern;
  }

  ssm_ctx_term();

  return 1;
}

int ssm_ut_swth()
{
  int result =0;

  printf("ut_swth ::: please input 1 to end test.\r");
  fflush(stdout);
  result +=ssm_ut_swth_val_pbth();

  printf("ut_swth ::: total %d test(s) succeeded. :::\n" ,result);

  return result;
}

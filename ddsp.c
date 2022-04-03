/// ddsp.c
///   this is a implement file for the simple slotmachine.
///

#include "ddsp.h"
#include "sr.h"

ssm_ddsp_t ssm_ddsp;

int ssm_ddsp_init(size_t fps)
{
  ssm_ddsp.fps =fps;
  ssm_ddsp.n_quantity =0;
  ssm_ddsp.n_current_leds =0;
  size_t n;
  for (n =0; n<SSM_CTX_LEDS_QUANTITY+1; ++n)
    ssm_ddsp.leds_arr[n] =0;

  ssm_tmuN_init(SSM_CTX_DDSP_TMU_ID
      ,SSM_CTX_DDSP_PRIORITY
      ,SSM_TMU_TCNT_1SEC/fps/SSM_CTX_LEDS_QUANTITY
      ,SSM_TMU_TUNI_NAME(ddsp));

  return 0;
}

void ssm_ddsp_start()
{
  ssm_tmuN_start(SSM_CTX_DDSP_TMU_ID);
}

void ssm_ddsp_term()
{
  ssm_tmuN_stop(SSM_CTX_DDSP_TMU_ID);
}

int ssm_ddsp_add_leds(ssm_leds_tp pleds)
{
  if (SSM_CTX_LEDS_QUANTITY < ssm_ddsp.n_quantity+1)
    return -1;

  ssm_sr_bl_set();
  ssm_ddsp.leds_arr[ssm_ddsp.n_quantity] =pleds;
  ++ssm_ddsp.n_quantity;
  ssm_sr_bl_reset();
  return 0;
}

int ssm_ddsp_rm_leds(ssm_leds_tp pleds)
{
  if (ssm_ddsp.n_quantity-1 < 0)
    return -1;

  size_t m,n;
  for (n =0; n < SSM_CTX_LEDS_QUANTITY; ++n)
  {
    if (ssm_ddsp.leds_arr[n] == pleds)
      break;
  }
  if (n == SSM_CTX_LEDS_QUANTITY)
    return 0;

  for (m =n; m < SSM_CTX_LEDS_QUANTITY; ++m)
  {
    ssm_sr_bl_set();
    ssm_ddsp.leds_arr[m] =ssm_ddsp.leds_arr[m+1];
    ssm_sr_bl_reset();
  }

  --ssm_ddsp.n_quantity;
  return 0;
}

#ifndef IN_LOCAL
#pragma interrupt
#endif
SSM_TMU_BEGIN_IMPLEMENT_TUNI(SSM_CTX_DDSP_TMU_ID,ddsp);
{
  ssm_ppi_port_c_p->pattern &= 0x0f;

  if (ssm_ddsp.leds_arr[ssm_ddsp.n_current_leds])
    ssm_leds_output(ssm_ddsp.leds_arr[ssm_ddsp.n_current_leds]);

  ssm_ppi_port_c_p->pattern |= 1 << (ssm_ddsp.n_current_leds+4);

  ssm_ddsp.n_current_leds
    = (ssm_ddsp.n_current_leds+1 < ssm_ddsp.n_quantity)
     ? ssm_ddsp.n_current_leds+1
     : 0 ;
}
SSM_TMU_END_IMPLEMENT_TUNI();


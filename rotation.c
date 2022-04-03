/// rotation.c
///   this is a implement file for the simple slotmachine.
///

#include "rotation.h"
#include "sr.h"

ssm_rotation_t ssm_rotation;

int ssm_rotation_init(size_t fps ,ssm_swth_tp preset)
{
  ssm_rotation.fps         =fps;
  ssm_rotation.n_quantity  =0;
  ssm_rotation.is_rotating =SSM_FALSE;
  ssm_rotation.pswth_reset =preset;
  size_t n;
  for (n =0; n<SSM_CTX_ROTATION_QUANTITY+1; ++n)
  {
    ssm_rotation.drums[n].pdrum =0;
    ssm_rotation.drums[n].pswth =0;
    ssm_rotation.drums[n].pleds =0;
    ssm_rotation.drums[n].was_stopped =SSM_TRUE;
    ssm_rotation.drums[n].fps_res_offs =0;
    ssm_rotation.drums[n].fps_res_curr =0;
  }

  ssm_tmuN_init(
       SSM_CTX_ROTATION_TMU_ID
      ,SSM_CTX_ROTATION_PRIORITY 
      ,SSM_TMU_TCNT_1SEC/fps
      ,SSM_TMU_TUNI_NAME(rotation));

  return 0;
}

void ssm_rotation_start()
{
  ssm_tmuN_start(SSM_CTX_ROTATION_TMU_ID);
}

void ssm_rotation_term()
{
  ssm_tmuN_stop(SSM_CTX_ROTATION_TMU_ID);
}

int ssm_rotation_add_drum(
    ssm_drum_tp pdrum
  , ssm_swth_tp pswth
  , ssm_leds_tp pleds
  , size_t res_offset
)
{
  if (SSM_CTX_ROTATION_QUANTITY < ssm_rotation.n_quantity+1)
    return -1;

  res_offset %= SSM_CTX_ROTATION_RESOLUTION;
  res_offset  =(SSM_CTX_ROTATION_RESOLUTION-1) - res_offset;

  ssm_rotation.drums[ssm_rotation.n_quantity].pdrum =pdrum;
  ssm_rotation.drums[ssm_rotation.n_quantity].pswth =pswth;
  ssm_rotation.drums[ssm_rotation.n_quantity].pleds =pleds;
  ssm_rotation.drums[ssm_rotation.n_quantity].was_stopped =SSM_TRUE;
  ssm_rotation.drums[ssm_rotation.n_quantity].fps_res_offs =res_offset;
  ssm_rotation.drums[ssm_rotation.n_quantity].fps_res_curr =res_offset;

  ssm_rotation.drums[ssm_rotation.n_quantity].pleds->bits.seg7.pattern
    =*(ssm_rotation.drums[ssm_rotation.n_quantity].pdrum->current_pattern);

  ++ssm_rotation.n_quantity;

  return 0;
}

int ssm_rotation_rm_drum(ssm_drum_tp pdrum)
{
  if (ssm_rotation.n_quantity-1 < 0)
    return -1;

  size_t m,n;
  for (n =0; n < SSM_CTX_ROTATION_QUANTITY; ++n)
  {
    if (ssm_rotation.drums[n].pdrum == pdrum)
      break;
  }
  if (n == SSM_CTX_ROTATION_QUANTITY)
    return 0;

  for (m =n; m < SSM_CTX_ROTATION_QUANTITY; ++m)
  {
    ssm_sr_bl_set();
    ssm_rotation.drums[m] =ssm_rotation.drums[m+1];
    ssm_sr_bl_reset();
  }

  --ssm_rotation.n_quantity;
  return 0;
}

int  ssm_rotation_reset()
{
  size_t n;

  if (ssm_rotation.is_rotating)
  {
    ssm_rotation_stop_rotating();
    for (n =0; n<ssm_rotation.n_quantity; ++n)
      ssm_rotation_stop_drum(n);
  }
  else
  {
    for (n =0; n<ssm_rotation.n_quantity; ++n)
    {
      ssm_rotation_reset_resolution(n);
      ssm_rotation_start_drum(n);
    }
    ssm_rotation_start_rotating();
  }
  return 0;
}

#ifndef IN_LOCAL
#pragma interrupt
#endif
SSM_TMU_BEGIN_IMPLEMENT_TUNI(SSM_CTX_ROTATION_TMU_ID,rotation);
{
  if (ssm_swth_val_pbtn_is_on( &(ssm_rotation.pswth_reset->val) ))
  {
    ssm_rotation_reset(); //TODO:
  }

  if (!ssm_rotation.is_rotating)
    return;

  //it comes here, it is rotating.

  ssm_bool_t is_rotating =SSM_FALSE;

  size_t n;
  for (n =0; n<ssm_rotation.n_quantity; ++n)
  {
    if (ssm_rotation.drums[n].was_stopped)
      continue;

    if (ssm_swth_val_pbtn_is_on( &(ssm_rotation.drums[n].pswth->val) ))
    {
      ssm_rotation_stop_drum(n);
      continue;
    }
      
    is_rotating =SSM_TRUE;

    ++(ssm_rotation.drums[n].fps_res_curr);

    if (SSM_CTX_ROTATION_RESOLUTION
          <= ssm_rotation.drums[n].fps_res_curr)
    {
      ssm_rotation.drums[n].fps_res_curr =0;

      ssm_drum_iterate(ssm_rotation.drums[n].pdrum);

      ssm_rotation.drums[n].pleds->bits.seg7.pattern
        =*(ssm_rotation.drums[n].pdrum->current_pattern);
    }

  }//for(n)

  ssm_rotation_set_rotating(is_rotating);

  if (ssm_rotation.is_rotating == SSM_FALSE)
  {
    // >>> it becomes stopping >>>

    if (*(ssm_rotation.drums[0].pdrum->current_pattern)
          ==ssm_drum_digit_patterns[7]
     && *(ssm_rotation.drums[1].pdrum->current_pattern)
          ==ssm_drum_digit_patterns[7]
     && *(ssm_rotation.drums[2].pdrum->current_pattern)
          ==ssm_drum_digit_patterns[7])
    {
      ssm_ppi_port_c_p->pattern &= 0x0f;

      ssm_leds_t leds;
      ssm_leds_init(&leds,SSM_LEDS_TYPE_SEG7,0,0);
      ssm_leds_output(&leds);

      ssm_ppi_port_c_p->pattern |= 0xf0;

      int j;
      for(j =0; j<7; ++j)
      {
        for(leds.bits.seg7.pattern=0x01;;)
        {
          ssm_leds_output(&leds);

          leds.bits.seg7.pattern <<= 1;

          if(leds.bits.seg7.pattern == 0x40) break;

          int i, wait=300*200;
          for(i=0; i<wait; ++i)
            ;
        }
      }
    }
    // <<< it becomes stopping <<<
  }

}
SSM_TMU_END_IMPLEMENT_TUNI();

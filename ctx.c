/// ctx.c
///   this is a implement file for the simple slotmachine.
///

#include <stdlib.h> //for size_t
#include <stdint.h> //for uintXX_t

#include "settings.h"

#include "rnd.h"
#include "ppi.h"
#include "sr.h"

#include "led.h"
#include "ddsp.h"

#include "swth.h"
#include "inpt.h"

#include "drum.h"
#include "rotation.h"

ssm_leds_t leds_arr[SSM_CTX_LEDS_QUANTITY];
ssm_swth_t swth_arr[SSM_CTX_SWTH_QUANTITY];
ssm_drum_t drum_arr[SSM_CTX_SWTH_QUANTITY];

int ssm_ctx_init()
{
  ssm_ppi0_init_a0b0(
      SSM_PPI_O_PORT,SSM_PPI_O_PORT
     ,SSM_PPI_O_PORT,SSM_PPI_I_PORT);

  ssm_leds_init(&leds_arr[0],SSM_LEDS_TYPE_SEG7,0,0);
  ssm_leds_init(&leds_arr[1],SSM_LEDS_TYPE_SEG7,0,0);
  ssm_leds_init(&leds_arr[2],SSM_LEDS_TYPE_SEG7,0,0);
  ssm_leds_init(&leds_arr[3],SSM_LEDS_TYPE_GNRL,0,0);

  ssm_ddsp_init(SSM_FRAME_RATE);
  ssm_ddsp_add_leds(&leds_arr[0]);
  ssm_ddsp_add_leds(&leds_arr[1]);
  ssm_ddsp_add_leds(&leds_arr[2]);
  ssm_ddsp_add_leds(&leds_arr[3]);
  ssm_ddsp_start();

  ssm_swth_val_t v ={{{0x00},0}};
  v.pbtn.bit =1; ssm_swth_init(&swth_arr[0],SSM_SWTH_TYPE_PBTN,&v);
  v.pbtn.bit =0; ssm_swth_init(&swth_arr[1],SSM_SWTH_TYPE_PBTN,&v);
  v.pbtn.bit =2; ssm_swth_init(&swth_arr[2],SSM_SWTH_TYPE_PBTN,&v);
  v.pbtn.bit =3; ssm_swth_init(&swth_arr[3],SSM_SWTH_TYPE_PBTN,&v);

  ssm_inpt_init(SSM_FRAME_RATE);
  ssm_inpt_add_swth(&swth_arr[0]);
  ssm_inpt_add_swth(&swth_arr[1]);
  ssm_inpt_add_swth(&swth_arr[2]);
  ssm_inpt_add_swth(&swth_arr[3]);

  ssm_drum_init(&drum_arr[0]);
  ssm_drum_init(&drum_arr[1]);
  ssm_drum_init(&drum_arr[2]);

  ssm_rotation_init(SSM_CTX_ROTATION_RESOLUTION,&swth_arr[3]);
  ssm_rotation_add_drum(&drum_arr[0] ,&swth_arr[0] ,&leds_arr[0] ,SSM_CTX_ROTATION_RESOLUTION*1/4);
  ssm_rotation_add_drum(&drum_arr[1] ,&swth_arr[1] ,&leds_arr[1] ,SSM_CTX_ROTATION_RESOLUTION*2/4);
  ssm_rotation_add_drum(&drum_arr[2] ,&swth_arr[2] ,&leds_arr[2] ,SSM_CTX_ROTATION_RESOLUTION*3/4);

  ssm_sr_bl_reset();

  ssm_inpt_start();
  ssm_rotation_start();

  return 0;
}

int ssm_ctx_term()
{
  ssm_ddsp_rm_leds(&leds_arr[0]);
  ssm_ddsp_rm_leds(&leds_arr[1]);
  ssm_ddsp_rm_leds(&leds_arr[2]);
  ssm_ddsp_term();

  ssm_inpt_rm_swth(&swth_arr[0]);
  ssm_inpt_rm_swth(&swth_arr[1]);
  ssm_inpt_rm_swth(&swth_arr[2]);
  ssm_inpt_rm_swth(&swth_arr[3]);
  ssm_inpt_term();

  ssm_rotation_rm_drum(&drum_arr[0]);
  ssm_rotation_rm_drum(&drum_arr[1]);
  ssm_rotation_rm_drum(&drum_arr[2]);
  ssm_rotation_rm_drum(&drum_arr[3]);
  ssm_rotation_term();

  return 0;
}

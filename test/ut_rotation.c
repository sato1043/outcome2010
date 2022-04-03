#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "settings.h"
#include "util.h"

#include "led.h"
#include "ddsp.h"

#include "swth.h"
#include "inpt.h"

#include "rotation.h"
#include "sr.h"

static ssm_leds_t leds_arr[SSM_CTX_LEDS_QUANTITY];
static ssm_swth_t swth_arr[SSM_CTX_SWTH_QUANTITY];
static ssm_drum_t drum_arr[SSM_CTX_SWTH_QUANTITY];

#if 0
int ssm_ut_rotation_XXXX()
{
  return 1;
}
#endif

int ssm_ut_rotation_init()
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

  ssm_ddsp_start();
  ssm_inpt_start();
  ssm_rotation_start();

  ssm_rotation_term();
  return 1;
}

int ssm_ut_rotation_add_leds()
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
  ssm_rotation_add_drum(&drum_arr[0] ,&swth_arr[0] ,&leds_arr[0] ,0);
  ssm_rotation_add_drum(&drum_arr[1] ,&swth_arr[1] ,&leds_arr[1] ,1);
  ssm_rotation_add_drum(&drum_arr[2] ,&swth_arr[2] ,&leds_arr[2] ,2);

  ssm_sr_bl_reset();

  assert(ssm_rotation.n_quantity == 3);
  assert(ssm_rotation.drums[0].pdrum == &drum_arr[0]);
  assert(ssm_rotation.drums[1].pdrum == &drum_arr[1]);
  assert(ssm_rotation.drums[2].pdrum == &drum_arr[2]);
  assert(ssm_rotation.drums[0].pswth == &swth_arr[0]);
  assert(ssm_rotation.drums[1].pswth == &swth_arr[1]);
  assert(ssm_rotation.drums[2].pswth == &swth_arr[2]);
  assert(ssm_rotation.drums[0].pleds == &leds_arr[0]);
  assert(ssm_rotation.drums[1].pleds == &leds_arr[1]);
  assert(ssm_rotation.drums[2].pleds == &leds_arr[2]);
  assert(ssm_rotation.drums[0].was_stopped == SSM_FALSE);
  assert(ssm_rotation.drums[1].was_stopped == SSM_FALSE);
  assert(ssm_rotation.drums[2].was_stopped == SSM_FALSE);
  assert(ssm_rotation.drums[0].fps_res_offs == 3);
  assert(ssm_rotation.drums[1].fps_res_offs == 2);
  assert(ssm_rotation.drums[2].fps_res_offs == 1);
  assert(ssm_rotation.drums[0].fps_res_curr == 3);
  assert(ssm_rotation.drums[1].fps_res_curr == 2);
  assert(ssm_rotation.drums[2].fps_res_curr == 1);

  ssm_ddsp_start();
  ssm_inpt_start();
  ssm_rotation_start();

  ssm_wait_ms(1000);

  ssm_rotation_term();
  return 1;
}

int ssm_ut_rotation_rm_leds()
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
  ssm_rotation_add_drum(&drum_arr[0] ,&swth_arr[0] ,&leds_arr[0] ,0);
  ssm_rotation_add_drum(&drum_arr[1] ,&swth_arr[1] ,&leds_arr[1] ,1);
  ssm_rotation_add_drum(&drum_arr[2] ,&swth_arr[2] ,&leds_arr[2] ,2);

  ssm_sr_bl_reset();

  ssm_wait_ms(1000);

  ssm_rotation_rm_drum(&drum_arr[1]);
  assert(ssm_rotation.n_quantity == 2);
  assert(ssm_rotation.drums[0].pdrum == &drum_arr[0]);
  assert(ssm_rotation.drums[1].pdrum == &drum_arr[2]);
  assert(ssm_rotation.drums[2].pdrum == 0);
  assert(ssm_rotation.drums[0].pswth == &swth_arr[0]);
  assert(ssm_rotation.drums[1].pswth == &swth_arr[2]);
  assert(ssm_rotation.drums[2].pswth == 0);
  assert(ssm_rotation.drums[0].pleds == &leds_arr[0]);
  assert(ssm_rotation.drums[1].pleds == &leds_arr[2]);
  assert(ssm_rotation.drums[2].pleds == 0);
  assert(ssm_rotation.drums[0].was_stopped == SSM_FALSE);
  assert(ssm_rotation.drums[1].was_stopped == SSM_FALSE);
  assert(ssm_rotation.drums[2].was_stopped == SSM_FALSE);
  assert(ssm_rotation.drums[0].fps_res_offs == 3);
  assert(ssm_rotation.drums[1].fps_res_offs == 1);
  assert(ssm_rotation.drums[2].fps_res_offs == 0);
  assert(ssm_rotation.drums[0].fps_res_curr == 3);
  assert(ssm_rotation.drums[1].fps_res_curr == 1);
  assert(ssm_rotation.drums[2].fps_res_curr == 0);

  ssm_rotation_rm_drum(&drum_arr[0]);
  assert(ssm_rotation.n_quantity == 1);
  assert(ssm_rotation.drums[0].pdrum == &drum_arr[2]);
  assert(ssm_rotation.drums[1].pdrum == 0);
  assert(ssm_rotation.drums[2].pdrum == 0);
  assert(ssm_rotation.drums[0].pswth == &swth_arr[2]);
  assert(ssm_rotation.drums[1].pswth == 0);
  assert(ssm_rotation.drums[2].pswth == 0);
  assert(ssm_rotation.drums[0].pleds == &leds_arr[2]);
  assert(ssm_rotation.drums[1].pleds == 0);
  assert(ssm_rotation.drums[2].pleds == 0);
  assert(ssm_rotation.drums[0].was_stopped == SSM_FALSE);
  assert(ssm_rotation.drums[1].was_stopped == SSM_FALSE);
  assert(ssm_rotation.drums[2].was_stopped == SSM_FALSE);
  assert(ssm_rotation.drums[0].fps_res_offs == 1);
  assert(ssm_rotation.drums[1].fps_res_offs == 0);
  assert(ssm_rotation.drums[2].fps_res_offs == 0);
  assert(ssm_rotation.drums[0].fps_res_curr == 1);
  assert(ssm_rotation.drums[1].fps_res_curr == 0);
  assert(ssm_rotation.drums[2].fps_res_curr == 0);

  ssm_rotation_rm_drum(&drum_arr[2]);
  assert(ssm_rotation.n_quantity == 0);
  assert(ssm_rotation.drums[0].pdrum == 0);
  assert(ssm_rotation.drums[1].pdrum == 0);
  assert(ssm_rotation.drums[2].pdrum == 0);
  assert(ssm_rotation.drums[0].pswth == 0);
  assert(ssm_rotation.drums[1].pswth == 0);
  assert(ssm_rotation.drums[2].pswth == 0);
  assert(ssm_rotation.drums[0].pleds == 0);
  assert(ssm_rotation.drums[1].pleds == 0);
  assert(ssm_rotation.drums[2].pleds == 0);
  assert(ssm_rotation.drums[0].was_stopped == SSM_FALSE);
  assert(ssm_rotation.drums[1].was_stopped == SSM_FALSE);
  assert(ssm_rotation.drums[2].was_stopped == SSM_FALSE);
  assert(ssm_rotation.drums[0].fps_res_offs == 0);
  assert(ssm_rotation.drums[1].fps_res_offs == 0);
  assert(ssm_rotation.drums[2].fps_res_offs == 0);
  assert(ssm_rotation.drums[0].fps_res_curr == 0);
  assert(ssm_rotation.drums[1].fps_res_curr == 0);
  assert(ssm_rotation.drums[2].fps_res_curr == 0);

  ssm_rotation_term();
  return 1;
}

int ssm_ut_rotation_reset()
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
  ssm_rotation_add_drum(&drum_arr[0] ,&swth_arr[0] ,&leds_arr[0] ,0);
  ssm_rotation_add_drum(&drum_arr[1] ,&swth_arr[1] ,&leds_arr[1] ,1);
  ssm_rotation_add_drum(&drum_arr[2] ,&swth_arr[2] ,&leds_arr[2] ,2);

  ssm_sr_bl_reset();

  ssm_rotation_start_rotating();

  ssm_wait_ms(1000);

  ssm_rotation_reset();

  assert(ssm_rotation.is_rotating == SSM_FALSE);

  return 1;
}

int ssm_ut_rotation()
{
  int result =0;

  result +=ssm_ut_rotation_init();
  result +=ssm_ut_rotation_add_leds();
  result +=ssm_ut_rotation_rm_leds();

  printf("ut_rotation ::: total %d test(s) succeeded. :::\n" ,result);

  return result;
}


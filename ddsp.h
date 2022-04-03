/// ddsp.h
///   this is a header file for the simple slotmachine.
///

#ifndef __ddsp_h__
#define __ddsp_h__

#include <stdlib.h> //for size_t
#include <stdint.h> //for uint8_t

#include "settings.h"

#include "tmu.h"
#include "led.h"

typedef volatile struct ssm_ddsp_t_  ssm_ddsp_t;
typedef volatile struct ssm_ddsp_t_* ssm_ddsp_tp;

struct ssm_ddsp_t_
{
  size_t fps;
  size_t n_quantity;
  size_t n_current_leds;
  ssm_leds_tp leds_arr[SSM_CTX_LEDS_QUANTITY+1];
};

extern ssm_ddsp_t ssm_ddsp;

int  ssm_ddsp_init(size_t fps);
void ssm_ddsp_start();
void ssm_ddsp_term();

int ssm_ddsp_add_leds(ssm_leds_tp pleds);
int ssm_ddsp_rm_leds(ssm_leds_tp pleds);

SSM_TMU_DECLARE_TUNI(SSM_CTX_DDSP_TMU_ID,ddsp);

#endif/*__ddsp_h__*/

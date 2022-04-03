/// ctx.h
///   this is a header file for the simple slotmachine.
///

#ifndef __ctx_h__
#define __ctx_h__

#include <stdint.h> //for uint8_t

#include "settings.h"

#include "led.h"
#include "swth.h"

extern ssm_leds_t leds_arr[SSM_CTX_LEDS_QUANTITY];
extern ssm_swth_t swth_arr[SSM_CTX_SWTH_QUANTITY];

int ssm_ctx_init();
int ssm_ctx_term();

#endif/*__ctx_h__*/

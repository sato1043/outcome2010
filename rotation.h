/// rotation.h
///   this is a header file for the simple slotmachine.
///

#ifndef __rotation_h__
#define __rotation_h__

#include <stdlib.h> //for size_t
#include <stdint.h> //for uint8_t

#include "settings.h"

#include "tmu.h"
#include "swth.h"
#include "drum.h"
#include "led.h"
#include "util.h"

typedef struct ssm_rotation_t_  ssm_rotation_t;
typedef struct ssm_rotation_t_* ssm_rotation_tp;

struct ssm_rotation_t_
{
  size_t fps;
  size_t n_quantity;
  ssm_bool_t is_rotating;
  ssm_swth_tp pswth_reset;
  struct
  {
    ssm_drum_tp pdrum;
    ssm_swth_tp pswth;
    ssm_leds_tp pleds;
    ssm_bool_t was_stopped;
    size_t fps_res_offs;
    size_t fps_res_curr;

  } drums [SSM_CTX_ROTATION_QUANTITY];
};

extern ssm_rotation_t ssm_rotation;

int  ssm_rotation_init();
void ssm_rotation_start();
void ssm_rotation_term();

int ssm_rotation_add_drum(
    ssm_drum_tp pdrum
  , ssm_swth_tp pswth
  , ssm_leds_tp pleds
  , size_t res_offset);

int  ssm_rotation_rm_drum(ssm_drum_tp pdrum);

#define ssm_rotation_start_rotating()   (ssm_rotation.is_rotating = SSM_TRUE)
#define ssm_rotation_stop_rotating()    (ssm_rotation.is_rotating = SSM_FALSE)
#define ssm_rotation_invert_rotating()  \
          (ssm_rotation.is_rotating = !ssm_rotation.is_rotating)
#define ssm_rotation_set_rotating(f)   (ssm_rotation.is_rotating = (f))

#define ssm_rotation_start_drum(n)  (ssm_rotation.drums[(n)].was_stopped = SSM_FALSE)
#define ssm_rotation_stop_drum(n)   (ssm_rotation.drums[(n)].was_stopped = SSM_TRUE)
#define ssm_rotation_invert_drum(n) \
          (ssm_rotation.drums[(n)].was_stopped = !ssm_rotation.drums[(n)].was_stopped)

#define ssm_rotation_reset_resolution(n) \
    ssm_rotation.drums[(n)].fps_res_curr =ssm_rotation.drums[(n)].fps_res_offs;

int  ssm_rotation_reset();

SSM_TMU_DECLARE_TUNI(SSM_CTX_ROTATION_TMU_ID ,rotation);

#endif/*__rotation_h__*/

/// inpt.h
///   this is a header file for the simple slotmachine.
///

#ifndef __inpt_h__
#define __inpt_h__

#include <stdlib.h> //for size_t
#include <stdint.h> //for uint8_t

#include "settings.h"

#include "tmu.h"
#include "swth.h"

typedef volatile struct ssm_inpt_t_  ssm_inpt_t;
typedef volatile struct ssm_inpt_t_* ssm_inpt_tp;

struct ssm_inpt_t_
{
  size_t fps;
  size_t n_quantity;
  ssm_swth_tp swth_arr[SSM_CTX_SWTH_QUANTITY+1];
};

extern ssm_inpt_t ssm_inpt;

int  ssm_inpt_init(size_t fps);
void ssm_inpt_start();
void ssm_inpt_term();

int ssm_inpt_add_swth(ssm_swth_tp pswth);
int ssm_inpt_rm_swth(ssm_swth_tp pswth);

SSM_TMU_DECLARE_TUNI(SSM_CTX_INPT_TMU_ID,inpt);

#endif/*__inpt_h__*/


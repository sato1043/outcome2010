/// led.c
///   this is a implementation for the simple slotmachine.
///

#include "settings.h"

#include "led.h"
#include "util.h"

#include <string.h>

inline int ssm_leds_init(
  ssm_leds_tp pgrp
, ssm_leds_type_t  type
, ssm_leds_bits_tp pbits
, ssm_leds_annx_tp pannx
)
{
  assert(pgrp);
  assert_ssm_leds_type(type);
  memset(pgrp,0,sizeof(ssm_leds_t));

  pgrp->type =type;
  if (pbits) pgrp->bits =*pbits;
  if (pannx) pgrp->annx =*pannx;

  switch(pgrp->type)
  {
    case SSM_LEDS_TYPE_GNRL:
      {
      }
      break;

    case SSM_LEDS_TYPE_SEG7:
      {
      }
      break;
  }
  return 0;
}


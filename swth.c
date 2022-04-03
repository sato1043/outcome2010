/// swth.c
///   this is a implementation for the simple slotmachine.
///

#include "settings.h"

#include "swth.h"
#include "util.h"

#include <string.h>

inline int ssm_swth_init(
  ssm_swth_tp pgrp
, ssm_swth_type_t type
, ssm_swth_val_tp pval
)
{
  assert(pgrp);
  assert_ssm_swth_type(type);
  memset(pgrp,0,sizeof(ssm_swth_t));

  pgrp->type =type;
  if (pval) pgrp->val =*pval;

  switch(pgrp->type)
  {
    case SSM_SWTH_TYPE_PBTN:
      {
      }
      break;
  }
  return 0;
}

void ssm_swth_val_pbtn_input(ssm_swth_val_pbtn_tp p_pbtn)
{
  static size_t cnt =0;
  static uint8_t pattern =0;

  if (!cnt)
    pattern =ssm_ppi_port_c_p->pattern;

  ssm_swth_val_pbtn_input_expr(p_pbtn,pattern);

  cnt = (cnt+1 < SSM_CTX_SWTH_QUANTITY) ? cnt+1 : 0 ;
}

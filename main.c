/// main.c
///   this is a implement file for the simple slotmachine.
///

#include "settings.h"
#include "util.h"
#include "ctx.h"

int main()
{
  ssm_ctx_init();

  forever()
  {
    //if (ssm_swth_val_pbtn_is_on(&swth_arr[3].val))
    //  break;
  }

  ssm_ctx_term();
  return 0;
}

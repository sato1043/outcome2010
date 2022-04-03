#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "settings.h"
#include "util.h"
#include "ctx.h"

#if 0
int ssm_ut_ctx_XXXX()
{
  return 1;
}
#endif

int ssm_ut_ctx_init()
{
  ssm_ctx_init();
  ssm_ctx_term();
  return 1;
}

int ssm_ut_ctx()
{
  int result =0;

  result +=ssm_ut_ctx_init();

  printf("ut_ctx ::: total %d test(s) succeeded. :::\n" ,result);

  return result;
}

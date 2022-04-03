#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "settings.h"
#include "util.h"
#include "drum.h"

#if 0
int ssm_ut_drum_XXXX()
{
    return 1;
}
#endif

int ssm_ut_drum_init()
{
  ssm_drum_t drum;
  ssm_drum_init(&drum);
  int i;
  for (i =0; i<SSM_DRUM_DIGITS_EACH; ++i)
    assert(0<=drum.patterns[i]&& drum.patterns[i]<=9);
  return 1;
}

int ssm_ut_drum_iterate()
{
  ssm_drum_t drum;

  ssm_drum_init(&drum);

  int i;
  for (i =0; i<SSM_DRUM_DIGITS_EACH<<2; ++i)
  {
    ssm_drum_iterate(&drum);
    assert(drum.current_pattern);
  }
  return 1;
}

int ssm_ut_drum()
{
  int result =0;

  result +=ssm_ut_drum_init();
  result +=ssm_ut_drum_iterate();

  printf("ut_drum ::: total %d test(s) succeeded. :::\n" ,result);

  return result;
}

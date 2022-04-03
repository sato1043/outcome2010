#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "settings.h"
#include "util.h"
#include "rnd.h"

#if 0
int ssm_ut_rnd_XXXX()
{
    return 1;
}
#endif

int ssm_ut_rnd_drum()
{
  int drum[10] ={0,0,0,0,0, 0,0,0,0,0};

  ssm_rnd_init(10);

  int j;
  int i;
  for (j =0; j<3; ++j)
    for (i =0; i<10; ++i)
      drum[i] =(int)(9 * ssm_rnd());
  return 1;
}

int ssm_ut_rnd()
{
  int result =0;

  result +=ssm_ut_rnd_drum();

  printf("ut_rnd ::: total %d test(s) succeeded. :::\n" ,result);

  return result;
}


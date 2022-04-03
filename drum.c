/// drum.c
///   this is a implement file for the simple slotmachine.
///

#include "drum.h"
#include "rnd.h"
#include "tmu.h"
#include "settings.h"

#include <limits.h>
#include <string.h>

#if IN_LOCAL
#include <stdio.h>
#endif

ssm_drum_digit_t ssm_drum_digit_patterns[SSM_DRUM_DIGIT_PATTERNS]
  ={ 0x3F ,0x06 ,0x5B ,0x4F ,0x66 ,0x6D ,0x7D ,0x07 ,0x7F ,0x6F };

int  ssm_drum_init(ssm_drum_tp pdrum)
{
#if 0
  int i;
  for (i =0; i<SSM_DRUM_DIGITS_EACH; ++i)
    pdrum->patterns[i] =ssm_drum_digit_patterns[(int)((1000.0 * ssm_rnd()) % 10)]; //TODO:
#else
  pdrum->patterns[0] =ssm_drum_digit_patterns[7];
  pdrum->patterns[1] =ssm_drum_digit_patterns[8];
  pdrum->patterns[2] =ssm_drum_digit_patterns[4];
  pdrum->patterns[3] =ssm_drum_digit_patterns[3];
  pdrum->patterns[4] =ssm_drum_digit_patterns[1];
  pdrum->patterns[5] =ssm_drum_digit_patterns[6];
  pdrum->patterns[6] =ssm_drum_digit_patterns[5];
#endif

  pdrum->current_pattern =&pdrum->patterns[0];
  return 0;
}

ssm_drum_digit_tp ssm_drum_iterate(ssm_drum_tp pdrum)
{
  return pdrum->current_pattern =
    (pdrum->current_pattern+1 < pdrum->patterns+SSM_DRUM_DIGITS_EACH)
      ? pdrum->current_pattern + 1
      : &pdrum->patterns[0];
}

/// drum.h
///   this is a header file for the simple slotmachine.
///

#ifndef __drum_h__
#define __drum_h__

#include <stdint.h> //for uint8_t

typedef uint8_t  ssm_drum_digit_t;
typedef uint8_t* ssm_drum_digit_tp;

#define SSM_DRUM_DIGIT_PATTERNS (10)
extern ssm_drum_digit_t ssm_drum_digit_patterns[SSM_DRUM_DIGIT_PATTERNS];

typedef struct ssm_drum_t_  ssm_drum_t;
typedef struct ssm_drum_t_* ssm_drum_tp;

#define SSM_DRUM_DIGITS_EACH (7)

struct ssm_drum_t_
{
  ssm_drum_digit_t patterns[SSM_DRUM_DIGITS_EACH];
  ssm_drum_digit_tp current_pattern;
};

int  ssm_drum_init(ssm_drum_tp pdrum);

ssm_drum_digit_tp ssm_drum_iterate(ssm_drum_tp pdrum);

#endif/*__drum_h__*/

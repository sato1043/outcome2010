#ifndef __util_h__
#define __util_h__

#if IN_LOCAL
#include <stdio.h>
#include <sys/time.h>
#endif
#include <stdlib.h> //for size_t
#include <stdint.h> //for uintXX_t
#include <limits.h> //for xxx_MAX

#define SSM_OUT     (0)
#define SSM_IN      (1)

#define SSM_OFF     (0)
#define SSM_ON      (1)

typedef int  ssm_bool_t;
typedef int* ssm_bool_tp;
#define SSM_FALSE   (0)
#define SSM_TRUE    (1)

#define bitsof(a) (sizeof(a)<<3)

#define ssm_wait_ms(n) \
  { \
    int ti,tj; \
    for (ti =0; ti<(n); ++ti) \
      for (tj =0; tj<300; ++tj) \
        ; \
  }

#define forever(dummy) for(;;)

#endif/*__util_h__*/

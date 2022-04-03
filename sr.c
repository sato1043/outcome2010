/// sr.c
///   this is a implementation for the simple slotmachine.
///

#include "settings.h"

#include "sr.h"
#include "util.h"

#include <string.h>

void ssm_sr_bl_set()
{
#ifndef IN_LOCAL
  uint32_t set_mask =0x10000000;
  asm volatile
  (
    ";\n"
    "  MOV   %0,R0 ;\n"
    "  STC   SR,R1 ;\n"
    "  OR    R1,R0 ;\n"
    "  LDC   R0,SR ;\n"
    "  ;"
        : /* no output */
        : "r"(set_mask) /* input  */
        : "r0","r1"     /* clobbered register */
  );
#endif
}

void ssm_sr_bl_reset()
{
#ifndef IN_LOCAL
  uint32_t reset_mask =0xefffffff;
  asm volatile
  (
    ";\n"
    "  MOV   %0,R0\n"
    "  STC   SR,R1\n"
    "  AND   R1,R0\n"
    "  LDC   R0,SR\n"
    "  ;"
        : /* no output */
        : "r"(reset_mask) /* input  */
        : "r0","r1"       /* clobbered register */
  );
#endif
}

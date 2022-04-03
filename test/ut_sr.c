#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "sr.h"


int ssm_ut_sr_bl()
{
  int blockbit =1;

  ssm_sr_bl_set();

  blockbit =1;
#ifndef IN_LOCAL
  asm volatile
  (
    ";\n"
    "  STC    SR,R0 ;\n"
    "  SHLR16 R0 ;\n"
    "  SHLR8  R0 ;\n"
    "  SHLR2  R0 ;\n"
    "  SHLR2  R0 ;\n"
    "  AND    #1,R0 ;\n"
    "  MOV    R0,%0 ;\n"
    "  ;"
        : "=r"(blockbit)/* output */
        : /* no input  */
        : "r0" /* clobbered register */
  );
#endif
  assert(blockbit==1);

  ssm_sr_bl_reset();

  blockbit =0;
#ifndef IN_LOCAL
  asm volatile
  (
    ";\n"
    "  STC    SR,R0 ;\n"
    "  SHLR16 R0 ;\n"
    "  SHLR8  R0 ;\n"
    "  SHLR2  R0 ;\n"
    "  SHLR2  R0 ;\n"
    "  AND    #1,R0 ;\n"
    "  MOV    R0,%0 ;\n"
    "  ;"
        : "=r"(blockbit)/* output */
        : /* no input  */
        : "r0" /* clobbered register */
  );
#endif
  assert(blockbit==0);

  return 1;
}

int ssm_ut_sr()
{
  int result =0;

  result +=ssm_ut_sr_bl();

  return result;
}

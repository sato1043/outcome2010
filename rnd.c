/// rnd.c
///   this is a implement file for the simple slotmachine.
///

#include "rnd.h"

#include <limits.h>
#include <stdlib.h> //for size_t

static unsigned long seed = 1;

#define N (1000)
#define M 10

static char s[N];

unsigned long ssm_lrnd(void)
{
  seed = seed * 1566083941UL + 1;
  return seed;
}

double ssm_drnd(void)  /* 0 <= rnd() < 1 */
{
  return (1.0 / (ULONG_MAX + 1.0)) * ssm_lrnd();
}

void ssm_rnd_init(unsigned long x)
{
  seed = x;

  int i, j;

  for (i = N - M; i < N; i++)
  {
    j = (int)((i + 1) * ssm_drnd());  /* 0 <= j <= i */
    if (s[j] == 0) s[j] = 1;
    else           s[i] = 1;
  }

  int d;
  //init_rnd((unsigned long) time(NULL));
  for (i = N - M; i < N; i++) {
      j = (int)((i + 1) * ssm_drnd());  /* 0 <= j <= i */
      if (s[j] == 0) s[j] = 1;
      else           s[i] = 1;
  }
  for (i = 0; i < N; i++)
      if (s[i]) d = (i + 1)%10;


}

int ssm_rnd() /* 0 < ssm_rnd() < M */
{
  static size_t n =0;
  for ( ;; )
  {
    n =(n+1<N)? n+1 : 0 ;
    if (s[n]) return (n + 1) % M;
  }
  return 0;
}

/*
 *   FILE NAME: stdlib_stub.c
 */
#include <stdio.h> //for FILE*
#include <stdlib.h> //for size_t

void *memset(void *dst, int c, size_t len)
{
  size_t n;
  for(n=0; n<len; ++n)
  {
    *(unsigned char*)dst = (unsigned char)c;
    ++dst;
  }
  return dst;
}

void* memcpy(void* dst, const void* src, size_t len)
{
  size_t n;
  for(n=0; n<len; ++n)
  {
    *(unsigned char*)dst = *(unsigned char*)src;
    ++dst;
    ++src;
  }
  return dst;
}

void __assert_fail (
  const char *__assertion
, const char *__file
, unsigned int __line
, const char *__function)
{
  while (1);
}

int printf(const char* fmt, ...)
{
  return 0;
}

size_t strlen(const char* str)
{
  int i=0;
  while(*(str+i) != '\0')
    i++;
  return i;
}

char* strcpy(char* dst, const char* src)
{
  const char *p;
  char *q;
  for(p = src,q=dst; *p; p++, q++)
    *q = *p;
  *q = '\0';
  return dst;
}

char* strncpy(char *dst, const char *src, size_t n)
{
  char* dst_term_p =dst + (n-1);

  const char *p;
  char *q;
  for(p = src,q=dst; *p && q<dst_term_p; p++, q++)
    *q = *p;
  *q = '\0';
  return dst;
}

char* strcat(char* dst, const char* src)
{
  char *q;
  for(q =dst; *q; q++)
    ;

  const char *p;
  for(p = src; *p; p++, q++)
    *q = *p;
  *q = '\0';
  return dst;
}

char* strncat(char* dst, const char* src ,size_t n)
{
  const char* src_term_p =src + (n-1);

  char *q;
  for(q =dst; *q; q++)
    ;

  const char *p;
  for(p = src; *p && p<src_term_p; p++, q++)
    *q = *p;
  *q = '\0';
  return dst;
}

int strcmp(const char *lhs, const char *rhs)
// returns
//   <0 : lhsが辞書順で前　lhs - rhs < 0
//  ==0 : 同じ文字列
//   >0 : lhsが辞書順で後　lhs - rhs > 0
{
  int ret=0;
  int i;

  for(i=0; lhs[i]; i++)
  {
    ret = lhs[i]-rhs[i];
    if(!ret) break;
  }

  if(!lhs[i] && rhs[i]) 
  {
    ret = lhs[i]-rhs[i];
  }
  return ret;
}

unsigned int sleep(unsigned int seconds)
{
  int ti,tj;
  for (ti =0; ti<seconds; ++ti)
  {
    for (tj =0; tj<300; ++tj)
    {
      ;
    }
  }
  return seconds;
}

void usleep(unsigned long usec)
{
  int ti,tj;
  for (ti =0; ti<usec; ++ti)
  {
    ++tj; --tj; ++ti; --ti;
  }
}

FILE *stdout =0;

int fflush(FILE *stream)
{
  return 0;
}

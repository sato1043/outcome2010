#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "led.h"

int ssm_ut_gnrl_bits()
{
  ssm_leds_bits_gnrl_t leds = { 0x00 };
  assert(leds.pattern == 0x00);
  leds.bit.b0 =1;
  assert(leds.pattern == 0x01);
  leds.bit.b1 =1;
  assert(leds.pattern == 0x03);
  leds.bit.b2 =1;
  assert(leds.pattern == 0x07);
  leds.bit.b3 =1;
  assert(leds.pattern == 0x0F);
  leds.bit.b4 =1;
  assert(leds.pattern == 0x1F);
  leds.bit.b5 =1;
  assert(leds.pattern == 0x3F);
  leds.bit.b6 =1;
  assert(leds.pattern == 0x7F);
  leds.bit.b7 =1;
  assert(leds.pattern == 0xFF);
  return 1;
};

int ssm_ut_gnrl_annx()
{
  ssm_leds_annx_gnrl_t annx = {};
  annx =annx;
  return 1;
};

int ssm_ut_seg7_bits()
{
  ssm_leds_bits_seg7_t leds = { 0x00 };
  assert(leds.pattern == 0x00);

  leds.bit.a =1;
  assert(leds.pattern == 0x01);
  leds.bit.b =1;
  assert(leds.pattern == 0x03);
  leds.bit.c =1;
  assert(leds.pattern == 0x07);
  leds.bit.d =1;
  assert(leds.pattern == 0x0F);
  leds.bit.e =1;
  assert(leds.pattern == 0x1F);
  leds.bit.f =1;
  assert(leds.pattern == 0x3F);
  leds.bit.g =1;
  assert(leds.pattern == 0x7F);
  leds.bit.dp =1;
  assert(leds.pattern == 0xFF);
  return 1;
};

int ssm_ut_seg7_annx()
{
  ssm_leds_annx_seg7_t annx = {};
  annx =annx;
  return 1;
};

int ssm_ut_led_grp_type()
{
  ssm_leds_type_t type =SSM_LEDS_TYPE_SEG7;
  assert_ssm_leds_type(type);
  assert(type==SSM_LEDS_TYPE_SEG7);

  type =ssm_leds_type(SSM_LEDS_TYPE_SEG7);
  assert_ssm_leds_type(type);
  assert(type==SSM_LEDS_TYPE_SEG7);

  type =ssm_leds_type(999);
  assert(type==0xe7);

  return 1;
};

int ssm_ut_led_grp_bits()
{
  ssm_leds_bits_t leds = {.gnrl={0x00}};
  assert(leds.gnrl.pattern == 0x00);
  leds.gnrl.bit.b0 =1;
  assert(leds.gnrl.pattern == 0x01);
  leds.gnrl.bit.b1 =1;
  assert(leds.gnrl.pattern == 0x03);
  leds.gnrl.bit.b2 =1;
  assert(leds.gnrl.pattern == 0x07);
  leds.gnrl.bit.b3 =1;
  assert(leds.gnrl.pattern == 0x0F);
  leds.gnrl.bit.b4 =1;
  assert(leds.gnrl.pattern == 0x1F);
  leds.gnrl.bit.b5 =1;
  assert(leds.gnrl.pattern == 0x3F);
  leds.gnrl.bit.b6 =1;
  assert(leds.gnrl.pattern == 0x7F);
  leds.gnrl.bit.b7 =1;
  assert(leds.gnrl.pattern == 0xFF);

  ssm_leds_bits_gnrl_tp pgnrl =&leds.gnrl;
  assert(pgnrl->pattern == 0xFF);
  pgnrl->bit.b7 =0;
  assert(pgnrl->pattern == 0x7F);
  pgnrl->bit.b6 =0;
  assert(pgnrl->pattern == 0x3F);
  pgnrl->bit.b5 =0;
  assert(pgnrl->pattern == 0x1F);
  pgnrl->bit.b4 =0;
  assert(pgnrl->pattern == 0x0F);
  pgnrl->bit.b3 =0;
  assert(pgnrl->pattern == 0x07);
  pgnrl->bit.b2 =0;
  assert(pgnrl->pattern == 0x03);
  pgnrl->bit.b1 =0;
  assert(pgnrl->pattern == 0x01);
  pgnrl->bit.b0 =0;
  assert(pgnrl->pattern == 0x00);

  leds.gnrl.pattern =0xFF;

  ssm_leds_bits_seg7_tp pseg7 =&leds.seg7;
  assert(pseg7->pattern == 0xFF);
  pseg7->bit.dp =0;
  assert(pseg7->pattern == 0x7F);
  pseg7->bit.g =0;
  assert(pseg7->pattern == 0x3F);
  pseg7->bit.f =0;
  assert(pseg7->pattern == 0x1F);
  pseg7->bit.e =0;
  assert(pseg7->pattern == 0x0F);
  pseg7->bit.d =0;
  assert(pseg7->pattern == 0x07);
  pseg7->bit.c =0;
  assert(pseg7->pattern == 0x03);
  pseg7->bit.b =0;
  assert(pseg7->pattern == 0x01);
  pseg7->bit.a =0;
  assert(pseg7->pattern == 0x00);

  ssm_leds_bits_t leds2;
  ssm_leds_bits_gnrl_t gnrl ={0x11};
  ssm_leds_bits_seg7_t seg7 ={0x44};

  leds2.gnrl =gnrl;
  leds2.gnrl.bit.b0 =0;
  assert(leds2.gnrl.pattern == 0x10);

  leds2.seg7 =seg7;
  leds2.seg7.bit.c =0;
  assert(leds2.seg7.pattern == 0x40);

  return 1;
}

int ssm_ut_led_grp_annx()
{
  ssm_leds_annx_t annx ={};
  ssm_leds_annx_gnrl_tp pgnrl =&annx.gnrl;
  ssm_leds_annx_seg7_tp pseg7 =&annx.seg7;

  ssm_leds_annx_t annx2;
  ssm_leds_annx_gnrl_t gnrl={};
  ssm_leds_annx_seg7_t seg7={};

  annx2.gnrl =gnrl =*pgnrl;
  annx2.seg7 =seg7 =*pseg7;

  return 1;
}

int ssm_ut_led_grp()
{
  ssm_leds_t leds;

  ssm_leds_init(&leds,SSM_LEDS_TYPE_GNRL,0,0);
  assert(leds.bits.gnrl.pattern==0x00);

  ssm_leds_init(&leds,SSM_LEDS_TYPE_SEG7,0,0);
  assert(leds.bits.seg7.pattern==0x00);

  ssm_leds_bits_t bits;

  bits.gnrl.pattern =0x11;
  ssm_leds_init(&leds,SSM_LEDS_TYPE_GNRL,&bits,0);
  assert(leds.bits.gnrl.pattern==0x11);

  bits.seg7.pattern =0x44;
  ssm_leds_init(&leds,SSM_LEDS_TYPE_SEG7,&bits,0);
  assert(leds.bits.seg7.pattern==0x44);

  return 1;
}

int ssm_ut_led_grp_output()
{
  ssm_leds_t leds;
  ssm_leds_bits_t bits ={{0x11}};

  ssm_leds_init(&leds,SSM_LEDS_TYPE_GNRL,&bits,0);
  ssm_leds_output(&leds);
  assert(ssm_ppi_port_a_p->pattern==0x11);

  bits.seg7.pattern =0x44;
  ssm_leds_init(&leds,SSM_LEDS_TYPE_SEG7,&bits,0);
  ssm_leds_output(&leds);
  assert(ssm_ppi_port_a_p->pattern==0x44);

  return 1;
}

int ssm_ut_led()
{
  int result =0;

  result +=ssm_ut_gnrl_bits();
  result +=ssm_ut_gnrl_annx();

  result +=ssm_ut_seg7_bits();
  result +=ssm_ut_seg7_annx();

  result +=ssm_ut_led_grp_type();
  result +=ssm_ut_led_grp_bits();
  result +=ssm_ut_led_grp_annx();

  result +=ssm_ut_led_grp();
  result +=ssm_ut_led_grp_output();

  printf("ut_led ::: total %d test(s) succeeded. :::\n" ,result);

  return result;
}

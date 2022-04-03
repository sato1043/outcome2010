#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "ppi.h"

extern ssm_ppi_t ssm_ppi0;

#if 0
int ssm_ut_()
{
  return 1;
}
#endif

int ssm_ut_ppi_port()
{
  ssm_ppi_port_t port = {0x00};
  assert(port.pattern == 0x00);
  port.bit.b0 =1;
  assert(port.pattern == 0x01);
  port.bit.b1 =1;
  assert(port.pattern == 0x03);
  port.bit.b2 =1;
  assert(port.pattern == 0x07);
  port.bit.b3 =1;
  assert(port.pattern == 0x0F);
  port.bit.b4 =1;
  assert(port.pattern == 0x1F);
  port.bit.b5 =1;
  assert(port.pattern == 0x3F);
  port.bit.b6 =1;
  assert(port.pattern == 0x7F);
  port.bit.b7 =1;
  assert(port.pattern == 0xFF);

  port.pattern = 0x00;

  port.bit.b0 =1;
  assert(port.pos.l0 ==1);
  port.bit.b1 =1;
  assert(port.pos.l1 ==1);
  port.bit.b2 =1;
  assert(port.pos.l2 ==1);
  port.bit.b3 =1;
  assert(port.pos.l3 ==1);

  port.bit.b4 =1;
  assert(port.pos.u4 ==1);
  port.bit.b5 =1;
  assert(port.pos.u5 ==1);
  port.bit.b6 =1;
  assert(port.pos.u6 ==1);
  port.bit.b7 =1;
  assert(port.pos.u7 ==1);

  return 1;
}

int ssm_ut_ppi_ctrl()
{
  ssm_ppi_ctrl_t ctrl = {0x00};
  assert(ctrl.pattern == 0x00);
  ctrl.word.ident =1;
  assert(ctrl.pattern == 0x80);
  ctrl.word.grp_a =1;
  assert(ctrl.pattern == 0xa0);
  ctrl.word.grp_a =2;
  assert(ctrl.pattern == 0xc0);
  ctrl.word.grp_a =3;
  assert(ctrl.pattern == 0xe0);
  ctrl.word.a_io =1;
  assert(ctrl.pattern == 0xf0);
  ctrl.word.c_io_u =1;
  assert(ctrl.pattern == 0xf8);
  ctrl.word.grp_b =1;
  assert(ctrl.pattern == 0xfc);
  ctrl.word.b_io =1;
  assert(ctrl.pattern == 0xfe);
  ctrl.word.c_io_l =1;
  assert(ctrl.pattern == 0xff);

  ctrl.pattern = 0x00;

  ctrl.cbit.ident =1;
  assert(ctrl.pattern == 0x80);
  int i;
  for (i=1; i<8; ++i)
  {
    ctrl.cbit.index =i;
    assert(ctrl.pattern == (0x80|i<<1));
  }
  ctrl.cbit.value =1;
  assert(ctrl.pattern == 0x8f);

  return 1;
}

int ssm_ut_ppi_t()
{
  ssm_ppi_t ppi = {{0x00},{0x00}};
  assert(ppi.cbit.pattern == 0x00);
  ppi.cbit.bit.pc0 =1;
  assert(ppi.cbit.pattern == 0x01);
  ppi.cbit.bit.pc1 =1;
  assert(ppi.cbit.pattern == 0x03);
  ppi.cbit.bit.pc2 =1;
  assert(ppi.cbit.pattern == 0x07);
  ppi.cbit.bit.pc3 =1;
  assert(ppi.cbit.pattern == 0x0F);
  ppi.cbit.bit.pc4 =1;
  assert(ppi.cbit.pattern == 0x1F);
  ppi.cbit.bit.pc5 =1;
  assert(ppi.cbit.pattern == 0x3F);
  ppi.cbit.bit.pc6 =1;
  assert(ppi.cbit.pattern == 0x7F);
  ppi.cbit.bit.pc7 =1;
  assert(ppi.cbit.pattern == 0xFF);

  return 1;
}

int ssm_ut_ppi_init()
{
  ssm_ppi0_init_a1b1(
      SSM_PPI_I_PORT,SSM_PPI_I_PORT
     ,SSM_PPI_I_PORT,SSM_PPI_I_PORT);
 
  assert(ssm_ppi0.ctrl.word.ident == 1);
  assert(ssm_ppi0.ctrl.word.grp_a == SSM_PPI_GPA_M1);
  assert(ssm_ppi0.ctrl.word.grp_b == SSM_PPI_GPB_M1);
  assert(ssm_ppi0.ctrl.word.a_io   == SSM_PPI_I_PORT);
  assert(ssm_ppi0.ctrl.word.c_io_u == SSM_PPI_I_PORT);
  assert(ssm_ppi0.ctrl.word.b_io   == SSM_PPI_I_PORT);
  assert(ssm_ppi0.ctrl.word.c_io_l == SSM_PPI_I_PORT);

  ssm_ppi0_init_a0b1(
      SSM_PPI_I_PORT,SSM_PPI_I_PORT
     ,SSM_PPI_I_PORT,SSM_PPI_I_PORT);
 
  assert(ssm_ppi0.ctrl.word.ident == 1);
  assert(ssm_ppi0.ctrl.word.grp_a == SSM_PPI_GPA_M0);
  assert(ssm_ppi0.ctrl.word.grp_b == SSM_PPI_GPB_M1);
  assert(ssm_ppi0.ctrl.word.a_io   == SSM_PPI_I_PORT);
  assert(ssm_ppi0.ctrl.word.c_io_u == SSM_PPI_I_PORT);
  assert(ssm_ppi0.ctrl.word.b_io   == SSM_PPI_I_PORT);
  assert(ssm_ppi0.ctrl.word.c_io_l == SSM_PPI_I_PORT);

  ssm_ppi0_init_a0b0(
      SSM_PPI_O_PORT,SSM_PPI_O_PORT
     ,SSM_PPI_O_PORT,SSM_PPI_I_PORT);
 
  assert(ssm_ppi0.ctrl.word.ident == 1);
  assert(ssm_ppi0.ctrl.word.grp_a == SSM_PPI_GPA_M0);
  assert(ssm_ppi0.ctrl.word.grp_b == SSM_PPI_GPB_M0);
  assert(ssm_ppi0.ctrl.word.a_io   == SSM_PPI_O_PORT);
  assert(ssm_ppi0.ctrl.word.c_io_u == SSM_PPI_O_PORT);
  assert(ssm_ppi0.ctrl.word.b_io   == SSM_PPI_O_PORT);
  assert(ssm_ppi0.ctrl.word.c_io_l == SSM_PPI_I_PORT);

  assert(ssm_ppi0.cbit.bit.pc0 == 0);
  assert(ssm_ppi0.cbit.bit.pc1 == 0);
  assert(ssm_ppi0.cbit.bit.pc2 == 0);
  assert(ssm_ppi0.cbit.bit.pc3 == 0);
  assert(ssm_ppi0.cbit.bit.pc4 == 0);
  assert(ssm_ppi0.cbit.bit.pc5 == 0);
  assert(ssm_ppi0.cbit.bit.pc6 == 0);
  assert(ssm_ppi0.cbit.bit.pc7 == 0);

  return 1;
}

int ssm_ut_ppi_cbit()
{
  ssm_ppi0_init_a0b0(
      SSM_PPI_O_PORT,SSM_PPI_O_PORT
     ,SSM_PPI_O_PORT,SSM_PPI_I_PORT);

  assert(ssm_ppi0.cbit.bit.pc0 == 0);
  assert(ssm_ppi0.cbit.bit.pc1 == 0);
  assert(ssm_ppi0.cbit.bit.pc2 == 0);
  assert(ssm_ppi0.cbit.bit.pc3 == 0);
  assert(ssm_ppi0.cbit.bit.pc4 == 0);
  assert(ssm_ppi0.cbit.bit.pc5 == 0);
  assert(ssm_ppi0.cbit.bit.pc6 == 0);
  assert(ssm_ppi0.cbit.bit.pc7 == 0);

  ssm_ppi0_cbit_set(0);
  assert(ssm_ppi0.cbit.pattern == 0x01);
  ssm_ppi0_cbit_set(1);
  assert(ssm_ppi0.cbit.pattern == 0x03);
  ssm_ppi0_cbit_set(2);
  assert(ssm_ppi0.cbit.pattern == 0x07);
  ssm_ppi0_cbit_set(3);
  assert(ssm_ppi0.cbit.pattern == 0x0f);
  ssm_ppi0_cbit_set(4);
  assert(ssm_ppi0.cbit.pattern == 0x1f);
  ssm_ppi0_cbit_set(5);
  assert(ssm_ppi0.cbit.pattern == 0x3f);
  ssm_ppi0_cbit_set(6);
  assert(ssm_ppi0.cbit.pattern == 0x7f);
  ssm_ppi0_cbit_set(7);
  assert(ssm_ppi0.cbit.pattern == 0xff);

  ssm_ppi0_cbit_rst(0);
  assert(ssm_ppi0.cbit.pattern == 0xfe);
  ssm_ppi0_cbit_rst(1);
  assert(ssm_ppi0.cbit.pattern == 0xfc);
  ssm_ppi0_cbit_rst(2);
  assert(ssm_ppi0.cbit.pattern == 0xf8);
  ssm_ppi0_cbit_rst(3);
  assert(ssm_ppi0.cbit.pattern == 0xf0);
  ssm_ppi0_cbit_rst(4);
  assert(ssm_ppi0.cbit.pattern == 0xe0);
  ssm_ppi0_cbit_rst(5);
  assert(ssm_ppi0.cbit.pattern == 0xc0);
  ssm_ppi0_cbit_rst(6);
  assert(ssm_ppi0.cbit.pattern == 0x80);
  ssm_ppi0_cbit_rst(7);
  assert(ssm_ppi0.cbit.pattern == 0x00);

  return 1;
}

int ssm_ut_ppi()
{
  int result =0;

  result +=ssm_ut_ppi_port();
  result +=ssm_ut_ppi_ctrl();
  result +=ssm_ut_ppi_t();
  result +=ssm_ut_ppi_init();
  result +=ssm_ut_ppi_cbit();

  printf("ut_ppi ::: total %d test(s) succeeded. :::\n" ,result);

  return result;
}

/// ppi.c
///   this is a implementation for the simple slotmachine.
///

#include "settings.h"

#include "ppi.h"
#include "util.h"

#include <string.h>

#if IN_LOCAL
ssm_ppi_port_t ssm_ppi_dummyport_a ={0};
ssm_ppi_port_t ssm_ppi_dummyport_b ={0};
ssm_ppi_port_t ssm_ppi_dummyport_c ={0};
ssm_ppi_ctrl_t ssm_ppi_dummyctrl_r ={0};
#endif

#if IN_LOCAL
ssm_ppi_port_tp  ssm_ppi_port_a_p =&ssm_ppi_dummyport_a;
ssm_ppi_port_tp  ssm_ppi_port_b_p =&ssm_ppi_dummyport_b;
ssm_ppi_port_tp  ssm_ppi_port_c_p =&ssm_ppi_dummyport_c;
ssm_ppi_ctrl_tp  ssm_ppi_ctrl_r_p =&ssm_ppi_dummyctrl_r;
#else
ssm_ppi_port_tp  ssm_ppi_port_a_p =(ssm_ppi_port_tp)0xA4400000;
ssm_ppi_port_tp  ssm_ppi_port_b_p =(ssm_ppi_port_tp)0xA4400001;
ssm_ppi_port_tp  ssm_ppi_port_c_p =(ssm_ppi_port_tp)0xA4400002;
ssm_ppi_ctrl_tp  ssm_ppi_ctrl_r_p =(ssm_ppi_ctrl_tp)0xA4400003;
#endif

ssm_ppi_t ssm_ppi0;

int ssm_ppi0_init(
  ssm_ppi_group_mode_t     grp_a
, ssm_ppi_port_direction_t a_io
, ssm_ppi_port_direction_t c_io_u
, ssm_ppi_group_mode_t     grp_b
, ssm_ppi_port_direction_t b_io
, ssm_ppi_port_direction_t c_io_l
)
{
  ssm_ppi0.ctrl.pattern =0;
  ssm_ppi0.ctrl.word.ident = 1;
  ssm_ppi0.ctrl.word.grp_a  = grp_a ;
  ssm_ppi0.ctrl.word.a_io   = a_io  ;
  ssm_ppi0.ctrl.word.c_io_u = c_io_u;
  ssm_ppi0.ctrl.word.grp_b  = grp_b ;
  ssm_ppi0.ctrl.word.b_io   = b_io  ;
  ssm_ppi0.ctrl.word.c_io_l = c_io_l;

  ssm_ppi_ctrl_r_p->pattern  = ssm_ppi0.ctrl.pattern;

  size_t i;
  for (i=0; i<SSM_PPI_NUM_OF_PORT_BITS; ++i)
    ssm_ppi0_cbit_rst(i);

  return 0;
}

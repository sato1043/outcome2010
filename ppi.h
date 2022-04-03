/// ppi.h
///   this is a header file for the simple slotmachine.
///

#ifndef __ppi_h__
#define __ppi_h__

///TODO buffering ppi port

#include <stdint.h> //for uint8_t

typedef volatile union ssm_ppi_port_t_  ssm_ppi_port_t;
typedef volatile union ssm_ppi_port_t_* ssm_ppi_port_tp;

#define SSM_PPI_NUM_OF_PORT_BITS  (8)

union ssm_ppi_port_t_
{
  uint8_t pattern;
  struct
  {
    unsigned int b0 : 1; /* b0 */
    unsigned int b1 : 1; /* b1 */
    unsigned int b2 : 1; /* b2 */
    unsigned int b3 : 1; /* b3 */
    unsigned int b4 : 1; /* b4 */
    unsigned int b5 : 1; /* b5 */
    unsigned int b6 : 1; /* b6 */
    unsigned int b7 : 1; /* b7 */
  } bit;
  struct
  {
    unsigned int l0 : 1; /* b0 */
    unsigned int l1 : 1; /* b1 */
    unsigned int l2 : 1; /* b2 */
    unsigned int l3 : 1; /* b3 */
    unsigned int u4 : 1; /* b4 */
    unsigned int u5 : 1; /* b5 */
    unsigned int u6 : 1; /* b6 */
    unsigned int u7 : 1; /* b7 */
  } pos;
};

typedef volatile union ssm_ppi_ctrl_t_  ssm_ppi_ctrl_t;
typedef volatile union ssm_ppi_ctrl_t_* ssm_ppi_ctrl_tp;

union ssm_ppi_ctrl_t_
{
  uint8_t pattern;
  struct
  {
    unsigned int c_io_l : 1; /* b0   signal direction (in or out) for PC3-0 */
    unsigned int b_io   : 1; /* b1   signal direction (in or out) for PB */
    unsigned int grp_b  : 1; /* b    mode of port-group A (PB and PC3-0) */
    unsigned int c_io_u : 1; /* b3   signal direction (in or out) for PC4-7 */
    unsigned int a_io   : 1; /* b4   signal direction (in or out) for PA */
    unsigned int grp_a  : 2; /* b6-5 mode of port-group A (PA and PC7-4)*/
    unsigned int ident  : 1; /* b7   always 1 */
  } word;
  struct
  {
    unsigned int value  : 1; /* b0 */
    unsigned int index  : 3; /* b1 */
    unsigned int        : 3; /* b6-4 don't care */
    unsigned int ident  : 1; /* b7   alway 0 */
  } cbit;
};

extern ssm_ppi_port_tp ssm_ppi_port_a_p;
extern ssm_ppi_port_tp ssm_ppi_port_b_p;
extern ssm_ppi_port_tp ssm_ppi_port_c_p;
extern ssm_ppi_ctrl_tp ssm_ppi_ctrl_r_p;
#define ssm_ppi_ctrl_cwr_p  ssm_ppi_ctrl_r_p

typedef uint8_t ssm_ppi_group_mode_t;
#define SSM_PPI_CTRLWORD_MODE0    (0)
#define SSM_PPI_CTRLWORD_MODE1    (1)
#define SSM_PPI_CTRLWOWD_MODE2    (2)

#define SSM_PPI_GPA_M0    SSM_PPI_CTRLWORD_MODE0
#define SSM_PPI_GPA_M1    SSM_PPI_CTRLWORD_MODE1
#define SSM_PPI_GPA_M2    SSM_PPI_CTRLWOWD_MODE2

#define SSM_PPI_GPB_M0    SSM_PPI_CTRLWORD_MODE0
#define SSM_PPI_GPB_M1    SSM_PPI_CTRLWORD_MODE1

typedef uint8_t ssm_ppi_port_direction_t;
#define SSM_PPI_O_PORT  (0)
#define SSM_PPI_I_PORT  (1)

typedef volatile struct ssm_ppi_t_  ssm_ppi_t;
typedef volatile struct ssm_ppi_t_* ssm_ppi_tp;

struct ssm_ppi_t_
{
  ssm_ppi_ctrl_t ctrl;
  ssm_ppi_ctrl_t tmp;
  union
  {
    uint8_t pattern;
    struct
    {
      unsigned int pc0 : 1; /* b0 */
      unsigned int pc1 : 1; /* b1 */
      unsigned int pc2 : 1; /* b2 */
      unsigned int pc3 : 1; /* b3 */
      unsigned int pc4 : 1; /* b4 */
      unsigned int pc5 : 1; /* b5 */
      unsigned int pc6 : 1; /* b6 */
      unsigned int pc7 : 1; /* b7 */
    } bit;
  } cbit;
};

/**
 * ssm_ppi0_init
 *  - setup 8255 ppi controller onto plot board.
 *
 * @param grp_a mode of port-group A (PA and PC7-4)
 * @param a_io signal direction (in or out) for PA
 * @param c_io_u signal direction (in or out) for PC7-4
 * @param grp_b mode of port-group A (PB and PC3-0)
 * @param b_io signal direction (in or out) for PB
 * @param c_io_l signal direction (in or out) for PC3-0
 * @return 0:succedd <0:failed
 * @see ut_ppi.c
 */
int ssm_ppi0_init(
  ssm_ppi_group_mode_t     grp_a
, ssm_ppi_port_direction_t a_io
, ssm_ppi_port_direction_t c_io_u
, ssm_ppi_group_mode_t     grp_b
, ssm_ppi_port_direction_t b_io
, ssm_ppi_port_direction_t c_io_l
);

#define ssm_ppi0_init_a0b0(a_io,c_io_u,b_io,c_io_l) \
        ssm_ppi0_init_a0(a_io,c_io_u,SSM_PPI_GPB_M0,b_io,c_io_l)

#define ssm_ppi0_init_a0b1(a_io,c_io_u,b_io,c_io_l) \
        ssm_ppi0_init_a0(a_io,c_io_u,SSM_PPI_GPB_M1,b_io,c_io_l)

#define ssm_ppi0_init_a0(a_io,c_io_u,grp_b,b_io,c_io_l) \
        ssm_ppi0_init(SSM_PPI_GPA_M0,a_io,c_io_u,grp_b,b_io,c_io_l)

#define ssm_ppi0_init_a1b0(a_io,c_io_u,b_io,c_io_l) \
        ssm_ppi0_init_a1(a_io,c_io_u,SSM_PPI_GPB_M0,b_io,c_io_l)

#define ssm_ppi0_init_a1b1(a_io,c_io_u,b_io,c_io_l) \
        ssm_ppi0_init_a1(a_io,c_io_u,SSM_PPI_GPB_M1,b_io,c_io_l)

#define ssm_ppi0_init_a1(a_io,c_io_u,grp_b,b_io,c_io_l) \
        ssm_ppi0_init(SSM_PPI_GPA_M1,a_io,c_io_u,grp_b,b_io,c_io_l)

#define ssm_ppi0_init_a2b0(a_io,c_io_u,b_io,c_io_l) \
        ssm_ppi0_init_a2(a_io,c_io_u,SSM_PPI_GPB_M0,b_io,c_io_l)

#define ssm_ppi0_init_a2b1(a_io,c_io_u,b_io,c_io_l) \
        ssm_ppi0_init_a2(a_io,c_io_u,SSM_PPI_GPB_M1,b_io,c_io_l)

#define ssm_ppi0_init_a2(a_io,c_io_u,grp_b,b_io,c_io_l) \
        ssm_ppi0_init(SSM_PPI_GPA_M2,a_io,c_io_u,grp_b,b_io,c_io_l)

/**
 * ssm_ppi0_cbit_rst
 * ssm_ppi0_cbit_set
 *  - set/reset each bit of port c
 *
 * @param index_ index of bit number 
 * @return void
 * @see ut_ppi.c
 */
typedef uint8_t ssm_ppi_cbit_index_t;
typedef uint8_t ssm_ppi_cbit_value_t;

#define ssm_ppi0_cbit_rst(index_) \
  { \
    ssm_ppi0.cbit.pattern &= ~(1<<index_); \
    ssm_ppi0.tmp.cbit.ident = 0;           \
    ssm_ppi0.tmp.cbit.index = (index_);    \
    ssm_ppi0.tmp.cbit.value = 0;           \
    ssm_ppi_ctrl_r_p->pattern  = ssm_ppi0.tmp.pattern; \
  }
#define ssm_ppi0_cbit_set(index_) \
  { \
    ssm_ppi0.cbit.pattern |=  (1<<index_); \
    ssm_ppi0.tmp.cbit.ident = 0;           \
    ssm_ppi0.tmp.cbit.index = (index_);    \
    ssm_ppi0.tmp.cbit.value = 1;           \
    ssm_ppi_ctrl_r_p->pattern  = ssm_ppi0.tmp.pattern; \
  }

#endif/*__ppi_h__*/

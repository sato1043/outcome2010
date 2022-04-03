/// swth.h
///   this is a header file for the simple slotmachine.
///

#ifndef __swth_h__
#define __swth_h__

#include <stdint.h>  //for uint8_t
#include <assert.h>  //for assert

#include "ppi.h" //for PPI_A

//class for push button

typedef struct ssm_swth_val_pbtn_t_  ssm_swth_val_pbtn_t;
typedef struct ssm_swth_val_pbtn_t_* ssm_swth_val_pbtn_tp;

struct ssm_swth_val_pbtn_t_
{
  union
  {
    uint8_t  cont;
    struct
    {
      unsigned int lower : 4;
      unsigned int upper : 4;
    };
  };
  uint8_t  bit;
};

void ssm_swth_val_pbtn_input(ssm_swth_val_pbtn_tp p_pbtn);

#define ssm_swth_val_pbtn_input_expr(pbtn_,portdata_) \
  ( ((ssm_swth_val_pbtn_tp)(pbtn_))->cont         \
    = (((ssm_swth_val_pbtn_tp)(pbtn_))->cont <<1) \
       | ((portdata_>> ((ssm_swth_val_pbtn_tp)(pbtn_))->bit) & 1) )

#define ssm_swth_val_pbtn_is_off(p_pbtn_)  (((ssm_swth_val_pbtn_tp)(p_pbtn_))->lower == 0x0)
#define ssm_swth_val_pbtn_is_on(p_pbtn_)   (((ssm_swth_val_pbtn_tp)(p_pbtn_))->lower == 0xf)
#define ssm_swth_val_pbtn_is_cont(p_pbtn_) (((ssm_swth_val_pbtn_tp)(p_pbtn_))->cont  ==0xff)

// class for switch

typedef uint8_t  ssm_swth_type_t;
typedef uint8_t* ssm_swth_type_tp;

#define SSM_SWTH_TYPE_INVALID (0)
#define SSM_SWTH_TYPE_PBTN (1)

#define assert_ssm_swth_type(type) \
  { assert((type)==SSM_SWTH_TYPE_PBTN); }

typedef union ssm_swth_val_t_  ssm_swth_val_t;
typedef union ssm_swth_val_t_* ssm_swth_val_tp;

union ssm_swth_val_t_
{
  ssm_swth_val_pbtn_t pbtn;
};

typedef volatile struct ssm_swth_t_  ssm_swth_t;
typedef volatile struct ssm_swth_t_* ssm_swth_tp;

struct ssm_swth_t_
{
  ssm_swth_type_t type;
  ssm_swth_val_t  val;
};

/**
 * ssm_swth_init 
 *  - initialize ssm_swth_t object.
 * 
 * @param pgrp object to init
 * @param type initialize data for type of switch
 * @param pval initialize data for switch (if is 0, data has zero)
 * @return 0:succeed <0:failed
 * @see test/ut_swth.c
 */
int ssm_swth_init(
  ssm_swth_tp pgrp
, ssm_swth_type_t type
, ssm_swth_val_tp pval
);

/**
 * ssm_swth_input
 *  - input data by the way that come under a ssm_swth_val_XXXX_t 
 * 
 * @param pgrp object to ssm_swth_t
 * @return non-zero:data 0:failed
 * @see test/ut_swth.c
 */
#define ssm_swth_input(pgrp) \
  ( (((ssm_swth_tp)(pgrp))->type==SSM_SWTH_TYPE_PBTN) \
    ? ssm_swth_val_pbtn_input(&((ssm_swth_tp)(pgrp))->val.pbtn) : 0 )

#endif/*__swth_h__*/

/// leds.h
///   this is a header file for the simple slotmachine.
///

#ifndef __led_h__
#define __led_h__

#include <stdint.h>  //for uint8_t
#include <assert.h>  //for assert

#include "ppi.h" //for PPI_A

//class for general LED group information

typedef union  ssm_leds_bits_gnrl_t_  ssm_leds_bits_gnrl_t;
typedef union  ssm_leds_bits_gnrl_t_* ssm_leds_bits_gnrl_tp;

union ssm_leds_bits_gnrl_t_
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
};

typedef struct ssm_leds_annx_gnrl_t_  ssm_leds_annx_gnrl_t;
typedef struct ssm_leds_annx_gnrl_t_* ssm_leds_annx_gnrl_tp;

struct ssm_leds_annx_gnrl_t_
{
};

//class for 7 segment LED

typedef union  ssm_leds_bits_seg7_t_  ssm_leds_bits_seg7_t;
typedef union  ssm_leds_bits_seg7_t_* ssm_leds_bits_seg7_tp;

union ssm_leds_bits_seg7_t_
{
  uint8_t pattern;
  struct 
  {
    unsigned int a : 1; /* b0 */
    unsigned int b : 1; /* b1 */
    unsigned int c : 1; /* b2 */
    unsigned int d : 1; /* b3 */
    unsigned int e : 1; /* b4 */
    unsigned int f : 1; /* b5 */
    unsigned int g : 1; /* b6 */
    unsigned int dp: 1; /* b7 */
  } bit;
};

typedef struct ssm_leds_annx_seg7_t_  ssm_leds_annx_seg7_t;
typedef struct ssm_leds_annx_seg7_t_* ssm_leds_annx_seg7_tp;

struct ssm_leds_annx_seg7_t_
{
};

//class for group of LED

typedef uint8_t  ssm_leds_type_t;
typedef uint8_t* ssm_leds_type_tp;
#define SSM_LEDS_TYPE_INVALID (0)
#define SSM_LEDS_TYPE_GNRL (1)
#define SSM_LEDS_TYPE_SEG7 (2)

#define ssm_leds_type(type) ((ssm_leds_type_t)(type))

#define assert_ssm_leds_type(type) \
  { assert((type)==SSM_LEDS_TYPE_GNRL \
        || (type)==SSM_LEDS_TYPE_SEG7); }

typedef union ssm_leds_bits_t_  ssm_leds_bits_t;
typedef union ssm_leds_bits_t_* ssm_leds_bits_tp;

union ssm_leds_bits_t_
{
  ssm_leds_bits_gnrl_t gnrl;
  ssm_leds_bits_seg7_t seg7;
};

typedef union ssm_leds_annx_t_  ssm_leds_annx_t;
typedef union ssm_leds_annx_t_* ssm_leds_annx_tp;

union ssm_leds_annx_t_
{
  ssm_leds_annx_gnrl_t gnrl;
  ssm_leds_annx_seg7_t seg7;
};

typedef struct ssm_leds_t_  ssm_leds_t;
typedef struct ssm_leds_t_* ssm_leds_tp;

struct ssm_leds_t_
{
  ssm_leds_type_t type;
  ssm_leds_bits_t bits;
  ssm_leds_annx_t annx;
};

/**
 * ssm_leds_init 
 *  - initialize ssm_leds_t object.
 * 
 * @param pgrp object to init
 * @param type initialize data for type of LED group
 * @param bits initialize data for bit pattern data of LED group (if is 0, data has zero)
 * @param annx initialize data for annex information of LED group (if is 0, data has zero)
 * @return 0:succeed <0:failed
 * @see test/ut_led.c
 */
int ssm_leds_init(
  ssm_leds_tp pgrp
, ssm_leds_type_t   type
, ssm_leds_bits_tp pbits
, ssm_leds_annx_tp pannx
);

#if 0
/**
 * ssm_leds_bits(pgrp)
 * ssm_leds_bits_p(pgrp)
 *  - retrieve ssm_led_XXXX_bits_t (or tp) from ssm_leds_t
 * 
 * @param pgrp object to led_grp_t
 * @return non-zero:ssm_led_XXXX_bits_tp 0:failed
 * @see test/ut_led.c
 */
#define ssm_leds_bits(pgrp) \
  ( (((ssm_leds_tp)(pgrp))->type==SSM_LEDS_TYPE_GNRL) \
    ? ((ssm_leds_tp)(pgrp))->bits.gnrl :              \
    (((ssm_leds_tp)(pgrp))->type==SSM_LEDS_TYPE_SEG7) \
    ? ((ssm_leds_tp)(pgrp))->bits.seg7 : 0 )

#define ssm_leds_bits_p(pgrp) \
  ( (((ssm_leds_tp)(pgrp))->type==SSM_LEDS_TYPE_GNRL) \
    ? &(((ssm_leds_tp)(pgrp))->bits.gnrl) :              \
    (((ssm_leds_tp)(pgrp))->type==SSM_LEDS_TYPE_SEG7) \
    ? &(((ssm_leds_tp)(pgrp))->bits.seg7) : 0 )
#endif

/**
 * ssm_leds_output
 *  - output data by the way that come under a ssm_led_XXXX_bits_t 
 * 
 * @param pgrp object to led_grp_t
 * @return non-zero:data 0:failed
 * @see test/ut_led.c
 */
#define ssm_leds_output(pgrp) \
  ( (((ssm_leds_tp)(pgrp))->type==SSM_LEDS_TYPE_GNRL) \
    ? ssm_ppi_port_a_p->pattern =((ssm_leds_tp)(pgrp))->bits.gnrl.pattern : \
    (((ssm_leds_tp)(pgrp))->type==SSM_LEDS_TYPE_SEG7) \
    ? ssm_ppi_port_a_p->pattern =((ssm_leds_tp)(pgrp))->bits.seg7.pattern : 0 )

#endif/*__led_h__*/

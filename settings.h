#ifndef __settings_h__
#define __settings_h__

#define SSM_FRAME_RATE  (50)  /* 50 farames per second */

#define NUMBER_OF_HIT   (77)
#define N_HIT_ROTATE    (3)

#define SSM_CTX_LEDS_QUANTITY (4)
#define SSM_CTX_DDSP_PRIORITY (10)
#define SSM_CTX_DDSP_TMU_ID SSM_TMU_ID0

#define SSM_CTX_SWTH_QUANTITY (4)
#define SSM_CTX_INPT_PRIORITY (13)
#define SSM_CTX_INPT_TMU_ID SSM_TMU_ID1

#define SSM_CTX_ROTATION_RESOLUTION (SSM_FRAME_RATE*5)
#define SSM_CTX_ROTATION_PRIORITY (12)
#define SSM_CTX_ROTATION_QUANTITY (3)
#define SSM_CTX_ROTATION_TMU_ID SSM_TMU_ID2

#endif/*__settings_h__*/

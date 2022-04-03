/// inpt.c
///   this is a implement file for the simple slotmachine.
///

#include "swth.h"
#include "inpt.h"
#include "sr.h"

#if IN_LOCAL
#include <unistd.h>
#include <termios.h>
struct termios ssm_inpt_tios_cookedmode;// cooked モード用
struct termios ssm_inpt_tios_rawmode;   // raw モード用
#endif

ssm_inpt_t ssm_inpt;

int ssm_inpt_init(size_t fps)
{
  ssm_inpt.fps =fps;
  ssm_inpt.n_quantity =0;
  size_t n;
  for (n =0; n<SSM_CTX_SWTH_QUANTITY+1; ++n)
    ssm_inpt.swth_arr[n] =0;

  ssm_tmuN_init(
       SSM_CTX_INPT_TMU_ID
      ,SSM_CTX_INPT_PRIORITY
      ,SSM_TMU_TCNT_1SEC/fps/SSM_CTX_SWTH_QUANTITY
      ,SSM_TMU_TUNI_NAME(inpt));
  return 0;
}

void ssm_inpt_start()
{
  ssm_tmuN_start(SSM_CTX_INPT_TMU_ID);

#if IN_LOCAL
  tcgetattr(STDIN_FILENO, &ssm_inpt_tios_cookedmode);

  ssm_inpt_tios_rawmode = ssm_inpt_tios_cookedmode;
  ssm_inpt_tios_rawmode.c_lflag &= ~(ICANON|ECHO|ISIG);
  ssm_inpt_tios_rawmode.c_cc[VMIN]  =1;
  ssm_inpt_tios_rawmode.c_cc[VTIME] =0;
  tcsetattr(STDIN_FILENO, TCSANOW, &ssm_inpt_tios_rawmode);
#endif
}

void ssm_inpt_term()
{
#if IN_LOCAL
  tcsetattr(STDIN_FILENO, TCSANOW, &ssm_inpt_tios_cookedmode);
#endif
  ssm_tmuN_stop(SSM_CTX_INPT_TMU_ID);
}

int ssm_inpt_add_swth(ssm_swth_tp pswth)
{
  if (SSM_CTX_SWTH_QUANTITY < ssm_inpt.n_quantity+1)
    return -1;

  //ssm_sr_bl_set();
  ssm_inpt.swth_arr[ssm_inpt.n_quantity] =pswth;
  ++ssm_inpt.n_quantity;
  //ssm_sr_bl_reset();
  return 0;
}

int ssm_inpt_rm_swth(ssm_swth_tp pswth)
{
  if (ssm_inpt.n_quantity-1 < 0)
    return -1;

  size_t m,n;
  for (n =0; n < SSM_CTX_SWTH_QUANTITY; ++n)
  {
    if (ssm_inpt.swth_arr[n] == pswth)
      break;
  }
  if (n == SSM_CTX_SWTH_QUANTITY)
    return 0;

  for (m =n; m < SSM_CTX_SWTH_QUANTITY; ++m)
  {
    ssm_sr_bl_set();
    ssm_inpt.swth_arr[m] =ssm_inpt.swth_arr[m+1];
    ssm_sr_bl_reset();
  }

  --ssm_inpt.n_quantity;
  return 0;
}

#ifndef IN_LOCAL
#pragma interrupt
#endif
SSM_TMU_BEGIN_IMPLEMENT_TUNI(SSM_CTX_INPT_TMU_ID,inpt);
{
#if IN_LOCAL
  ssm_inpt_tios_rawmode.c_cc[VMIN] =0;
  tcsetattr(STDIN_FILENO, TCSANOW, &ssm_inpt_tios_rawmode);

  char ch;
  int nread = read(STDIN_FILENO,&ch,1);

  ssm_inpt_tios_rawmode.c_cc[VMIN] =1;
  tcsetattr(STDIN_FILENO, TCSANOW, &ssm_inpt_tios_rawmode);

  if(nread == 1)
  {
    switch(ch)
    {
      case '1': ssm_ppi_port_c_p->pattern |= (1<<ssm_inpt.swth_arr[0]->val.pbtn.bit); break;
      case '2': ssm_ppi_port_c_p->pattern |= (1<<ssm_inpt.swth_arr[1]->val.pbtn.bit); break;
      case '3': ssm_ppi_port_c_p->pattern |= (1<<ssm_inpt.swth_arr[2]->val.pbtn.bit); break;
      case '4': ssm_ppi_port_c_p->pattern |= (1<<ssm_inpt.swth_arr[3]->val.pbtn.bit); break;
    }
  }
#endif

  if (ssm_inpt.swth_arr[0])
    ssm_swth_input(ssm_inpt.swth_arr[0]);
  if (ssm_inpt.swth_arr[1])
    ssm_swth_input(ssm_inpt.swth_arr[1]);
  if (ssm_inpt.swth_arr[2])
    ssm_swth_input(ssm_inpt.swth_arr[2]);
  if (ssm_inpt.swth_arr[3])
    ssm_swth_input(ssm_inpt.swth_arr[3]);
}
SSM_TMU_END_IMPLEMENT_TUNI();

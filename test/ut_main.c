#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

int ssm_ut_ppi(); //ut_ppi.c
int ssm_ut_sr();  //ut_sr.c
int ssm_ut_vbr(); //ut_vbr.c
int ssm_ut_tmu(); //ut_tmu.c

int ssm_ut_led(); //ut_led.c
int ssm_ut_ddsp();//ut_ddsp.c

int ssm_ut_swth(); //ut_ctx.c
int ssm_ut_inpt();//ut_inpt.c

int ssm_ut_ctx(); //ut_ctx.c

int ssm_ut_rnd(); //ut_rnd.c
int ssm_ut_drum(); //ut_drum.c
int ssm_ut_rotation(); //ut_rotation.c

int main()
{
  ssm_ut_ppi(); //PPIを初期化していないとハードウェアが正常に動作しない
  ssm_ut_sr();
  ssm_ut_vbr(); //SR.BL=0をしていないと失敗する
  ssm_ut_tmu();

  ssm_ut_led();
  ssm_ut_ddsp();

  ssm_ut_inpt();

  ssm_ut_rnd();
  ssm_ut_drum();

  ssm_ut_ctx();
  ssm_ut_swth(); //中でctxを使っているので下に持ってきている。

  ssm_ut_rotation();

  return 0;
}

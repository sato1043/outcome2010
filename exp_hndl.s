/*
   一般例外処理ハンドリングプログラム
*/

  .global _exp_hndl100,_exp_hndl400,_exp_hndl600
	.global	_exp_lock
  .text

! 一般例外ハンドラ
!
! (シーケンシャル処理、SR.BL=1のまま）
! (TRAPA命令は#immを使い、個別ベクタ0x160は未使用)
! 処理中に一般例外が発生するとリセット
!
  .org 0x100-0x100 !現在のスクリプトファイル内のロケーションカウンタの値が基準

_exp_hndl100:

    ! ここはJMP命令で飛んでいるのでPRは退避されていない。
    ! PRやR0-R7、R8-R14、SGR->R15の退避・復帰およびRTEは
    ! 呼び出された側の責任で行うことになる。

    MOV     #-1,R0    ! R0 <- 0xFF000020(TRA)
    SHLL16  R0
    SHLL8   R0
    ADD     #0x20,R0
    MOV     R0,R1

    MOV.L   @(4,R1),R0! R0 <- EXPEVT
    SHLR2   R0        ! 直値で0x160とCMP/EQできないので小さくする。      
    SHLR    R0        ! このあたりは外部メモリアクセスがない早い処理を意識している。
    CMP/EQ  #0x2c,R0  ! R0 == 0x160 ?
    BF TP

    MOV.L   @R1,R0    ! R0 <- TRAPA's #imm
    MOV.L   vbr_trp_tbl_A1,R1
    ADD     R1,R0     ! calcurate address of vbr_trp_tbl of TRAPA
    MOV.L   @R0,R0    ! get address of handler routinue

    JMP @R0           ! get exception routine address then jump subroutine
    NOP               ! (and delay slot)

TP:
    MOV.L   vbr_tbl_A1,R1
    ADD     R1,R0     ! calcurate address for indicated index of
                      ! vbr_tbl of TRAPA or a general exception
    MOV.L   @R0,R0

    JMP @R0           ! get exception routine address then jump subroutine
    NOP               ! (and delay slot)
!
  .align 2
vbr_tbl_A1:     .LONG vbr_tbl
vbr_trp_tbl_A1: .LONG vbr_trp_tbl


 
! TLB一般例外ハンドラ
!
  .org 0x400-0x100
_exp_hndl400:
    STS.L   PR,@-R15  ! push PR

    MOV     #-1,R0    ! R0 <- 0xFF000020(TRA)
    SHLL16  R0
    SHLL8   R0
    ADD     #0x20,R0
    MOV     R0,R1

    BRA .
    NOP
!
  .align 2
vbr_tbl_A2:  .LONG vbr_tbl


! 割り込みハンドラ（シーケンシャル処理、SR.BL=1のまま）
! 処理中に一般例外が発生するとリセット
!
  .org 0x600-0x100
_exp_hndl600:

    ! ここはJMP命令で飛んでいるのでPRは退避されていない。
    ! PRやR0-R7、R8-R14、SGR->R15の退避・復帰およびRTEは
    ! 呼び出された側の責任で行うことになる。

    MOV     #-1,R0    ! R0 <- 0xFF000028(INTEVT)
    SHLL16  R0
    SHLL8   R0
    ADD     #0x28,R0
    MOV     R0,R1

    MOV.L   @R1,R0    ! R0 <- INTEVT
    SHLR2   R0
    SHLR    R0

    MOV.L   vbr_tbl_A3,R1
    ADD     R1,R0
    MOV.L   @R0,R0

    JMP @R0           ! jump to next stage of interupt handler
    NOP               ! (and delay slot)
!
  .align 2
vbr_tbl_A3:  .LONG vbr_tbl

! 割り込み処理ルーチン内で利用するレジスタは、
! その処理ルーチンの責任において退避と復帰を行う。

! しかしながら要は、呼出側（ハンドラ）または
! 呼び出された側（処理ルーチン）の責任において、
! 通常ルーチンに戻ったときに元のレジスタ環境（コンテキスト）に
! なっていればよいのである。

!
	.section	.bss
	.align 2
	.type	_exp_lock, @object
	.size	_exp_lock, 4
_exp_lock:
	.zero	4

  .end

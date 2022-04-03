/**********************************************************************
  リセットスタート FILE NAME: startup.s

  C言語で記述できないことはアセンブリ言語で書きます。
   (1) スタックポインタの設定
   (2) VBRの設定
   (3) SRの設定
   (4) スタックセクションの確保
**********************************************************************/

  .equ  SSIZE       ,  0x400        !スタックサイズ
  .equ  _INI_VBR    ,  _exp_hndl100-0x100

  .global __START
  .section  .text

!
!リセットスタートはここから
!
__START:

    !スタックポインタ設定
    MOV.L   _STACK_BOTTOM_A, R15

    ! メモリ設定等、最初に必要な処理がある場合は追加してください。
    BSR INI_BSC_etc
    NOP

     !BSSセクションをクリア
__BSS_CLEAR:
    MOV.L   _bss_start_A, R0
    MOV.L   _bss_end_A,   R1
    CMP/EQ  R0, R1
    BT __CPY_ROM2RAM
    MOV  #0, R2
__BSS_J1:
    MOV.L    R2, @R0
    ADD      #4,  R0
    CMP/HI  R0, R1
    BT __BSS_J1

!
__CPY_ROM2RAM: !_data_startから_data_endまでの領域に、
               !_data_rom_start_A以降のデータをコピーする。
    MOV.L    _data_start_A, R1
    MOV.L    _data_end_A, R2
    CMP/EQ  R1,R2
    BT __INI_VBR
    MOV.L    _data_rom_start_A,R0
_CPY_J1:
    MOV.L    @R0+, R4
    MOV.L    R4,@R1
    ADD      #4,R1
    CMP/HI  R1,R2
    BT _CPY_J1
  
!
__INI_VBR:
    MOV.L   _INI_VBR_A,R0
    LDC     R0,VBR

    MOV.L   _INI_ICR_A,R1 ! IRL0-3を個別IRQに設定
    MOV.L   @R1,R0
    OR      #0x80,R0
    MOV.L   R0,@R1

    MOV.L   _INI_IPRD_A,R0 ! IRL0-3の優先レベルを０に設定
    MOV     #0x00,R1
    SHLL8   R1
    MOV.W   R1,@R0

    MOV.L   _INI_SR_A,R0
    LDC     R0,SR
    !
    MOV.L   _main_A,R3 !main関数へ
    JSR @R3
    NOP
    !
    BRA  .
    NOP

!
  .align 2
_STACK_BOTTOM_A :   .LONG  _STACK_BOTTOM
_INI_VBR_A      :   .LONG  _INI_VBR
_INI_ICR_A      :   .LONG  0xFFD00000
_INI_IPRD_A     :   .LONG  0xFFD00010
_INI_SR_A       :   .LONG  0x50000000 + 0x00 << 4
    ! MD(b30)=1, RB(b29)=0, BL(b28)=0, I3～I0(b7～b4)=0x00:割りこみマスクビット
!
_data_start_A:      .LONG  _data_start
_data_end_A:        .LONG  _data_end
_data_rom_start_A:  .LONG  _data_rom_start
!
_bss_start_A:        .LONG _bss_start
_bss_end_A:          .LONG _bss_end
!
_main_A:            .LONG  main
!


!
  .align 2
INI_BSC_etc:
    ! ここにBSC(Bus State Controller)やSDRAMの初期化などの
    ! 具体的なコードを書きます。

    ! SDRAM等のバスステートコントローラの設定

    MOVA    INI_BSC_etc_DATAS, R0
    MOV      R0,R1
    MOV.L    INI_BSC_etc_DATAS_NUM, R0
    !
INI_BSC_etc_J1:
    MOV.L    @R1+,  R2
    MOV.L    @R1+,  R3
    MOV.L    @R1+,  R4
    !
INI_BSC_etc_1:
    MOV      #1, R5
    CMP/EQ  R2,  R5
    BF       INI_BSC_etc_2
    BRA INI_BSC_etc_J2
    MOV.B    R4,  @R3
    !
INI_BSC_etc_2:
    MOV      #2, R5
    CMP/EQ  R2,R5
    BF       INI_BSC_etc_3
    BRA     INI_BSC_etc_J2
    MOV.W    R4,  @R3
    !
INI_BSC_etc_3:
    MOV      #3, R5
    CMP/EQ  R2,R5
    BF       INI_BSC_etc_J2
    BRA INI_BSC_etc_J2
    MOV.L    R4,  @R3
    !
INI_BSC_etc_J2:
    ADD      #(-1), R0
    CMP/EQ  #0,R0
    BF      INI_BSC_etc_J1
    !
INI_BSC_etc_RTS:
    !レジスタの初期化(ベクタの内容からＰＣとＳＰを設定する)
    !RegisterReset()
    RTS
    NOP
!
  .align 2
INI_BSC_etc_DATAS_NUM:
      .LONG 18
INI_BSC_etc_DATAS:
      .LONG    3, 0xFF800000, 0x00100009  ! BCR1
      .LONG    2, 0xFF800004, 0xAAF4      ! BCR2  エリア１のバス幅を８ビット(01)にする。
      .LONG    2, 0xFF800050, 0x0001      ! BCR3
      .LONG    3, 0xFF800008, 0x11111111  ! WCR1
      .LONG    3, 0xFF80000C, 0xFFF44557  ! WCR2  エリア１のウェイトを９(0b101)にする。
      .LONG    3, 0xFF800010, 0x06666666  ! WCR3
      .LONG    3, 0xFE0A0028, 0x00000002  ! WCR4
      .LONG    3, 0xFE0A00F0, 0x0         ! BCR4
      .LONG    3, 0xFF800014, 0x080925F4  ! MCR (MRSET=0)
      .LONG    1, 0xFF940088, 0x0         ! SDRAM モードセット
      .LONG    2, 0xFF80001C, 0xA508      ! RTCSR
      .LONG    2, 0xFF800024, 0xA508      ! RTCOR (短い)
      .LONG    3, 0xFF800014, 0x480925F4  ! MCR (MRSET=1)
      .LONG    1, 0xFF940088, 0x0         ! SDRAM モードセット
      .LONG    2, 0xFF800024, 0xA582      ! RTCOR
      .LONG    2, 0xFF800018, 0xFFFF      ! PCR (ウェイト最大)

!
  .SECTION .stack
_STACK_TOP:
    .SPACE  SSIZE
_STACK_BOTTOM:

!
  .END


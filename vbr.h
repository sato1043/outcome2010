/// vbr.h
///   this is a header file for the simple slotmachine.
///

#ifndef __vbr_h__
#define __vbr_h__

#include <stdint.h> //for uint8_t

//typedef void (* const ssm_vbr_call_f)(void);
typedef void (*ssm_vbr_call_f)();
#define SSM_VBR_CALL_NONE (0)

// 
// exceptions
//
#define SSM_VBR_CALLS (126)

#define ssm_vbr_get(id_) \
  vbr_tbl[(id_)]

#define ssm_vbr_set(id_,func_) \
  vbr_tbl[(id_)] = (ssm_vbr_call_f)(func_)

extern ssm_vbr_call_f vbr_tbl[SSM_VBR_CALLS];

#define SSM_VBR_EVT_000  (  0) /* PowerOn reset    */
#define SSM_VBR_EVT_020  (  1) /* Manual reset     */
#define SSM_VBR_EVT_040  (  2) /* TLB miss(read)   */
#define SSM_VBR_EVT_060  (  3) /* TLB miss(write)  */
#define SSM_VBR_EVT_080  (  4) /* First Page write */
#define SSM_VBR_EVT_0A0  (  5) /* TLB permition(read) */
#define SSM_VBR_EVT_0C0  (  6) /* TLB permition(write) */
#define SSM_VBR_EVT_0E0  (  7) /* Address error(raed) */
#define SSM_VBR_EVT_100  (  8) /* Address error(write) */
#define SSM_VBR_EVT_120  (  9) /* FPU exception    */
#define SSM_VBR_EVT_140  ( 10) /* TLB double hits  */
#define SSM_VBR_EVT_160  ( 11) /* TRAPA            */
#define SSM_VBR_EVT_180  ( 12) /* Illigal instruction */
#define SSM_VBR_EVT_1A0  ( 13) /* Slot illigal instruction */
#define SSM_VBR_EVT_1C0  ( 14) /* NMI              */
#define SSM_VBR_EVT_1E0  ( 15) /* User braek       */
#define SSM_VBR_EVT_200  ( 16) /* IRL15            */
#define SSM_VBR_EVT_220  ( 17) /* IRL14            */
#define SSM_VBR_EVT_240  ( 18) /* IRL13,IRL0       */
#define SSM_VBR_EVT_260  ( 19) /* IRL12            */
#define SSM_VBR_EVT_280  ( 20) /* IRL11            */
#define SSM_VBR_EVT_2A0  ( 21) /* IRL10,IRL1       */
#define SSM_VBR_EVT_2C0  ( 22) /* IRL9             */
#define SSM_VBR_EVT_2E0  ( 23) /* IRL8             */
#define SSM_VBR_EVT_300  ( 24) /* IRL7,IRL2        */
#define SSM_VBR_EVT_320  ( 25) /* IRL6             */
#define SSM_VBR_EVT_340  ( 26) /* IRL5             */
#define SSM_VBR_EVT_360  ( 27) /* IRL4,IRL3        */
#define SSM_VBR_EVT_380  ( 28) /* IRL3             */
#define SSM_VBR_EVT_3A0  ( 29) /* IRL2             */
#define SSM_VBR_EVT_3C0  ( 30) /* IRL1             */
#define SSM_VBR_EVT_3E0  ( 31) /* Reserved         */
#define SSM_VBR_EVT_400  ( 32) /* TUNI0            */
#define SSM_VBR_EVT_420  ( 33) /* TUNI1            */
#define SSM_VBR_EVT_440  ( 34) /* TUNI2            */
#define SSM_VBR_EVT_460  ( 35) /* TICPI2           */
#define SSM_VBR_EVT_480  ( 36) /* Reserved         */
#define SSM_VBR_EVT_4A0  ( 37) /* Reserved         */
#define SSM_VBR_EVT_4C0  ( 38) /* Reserved         */
#define SSM_VBR_EVT_4E0  ( 39) /* ReservedI        */
#define SSM_VBR_EVT_500  ( 40) /* Reserved         */
#define SSM_VBR_EVT_520  ( 41) /* Reserved         */
#define SSM_VBR_EVT_540  ( 42) /* Reserved         */
#define SSM_VBR_EVT_560  ( 43) /* WDT   ITI        */
#define SSM_VBR_EVT_580  ( 44) /* REF RCMI         */
#define SSM_VBR_EVT_5A0  ( 45) /* REF ROVI         */
#define SSM_VBR_EVT_5C0  ( 46) /* Reserved         */
#define SSM_VBR_EVT_5E0  ( 47) /* Reserved         */
#define SSM_VBR_EVT_600  ( 48) /* H-UDI            */
#define SSM_VBR_EVT_620  ( 49) /* GPIO GPIOI       */
#define SSM_VBR_EVT_640  ( 50) /* DMAC DMTE0       */
#define SSM_VBR_EVT_660  ( 51) /* DMAC DMTE1       */
#define SSM_VBR_EVT_680  ( 52) /* DMAC DMTE2       */
#define SSM_VBR_EVT_6A0  ( 53) /* DMAC DMTE3       */
#define SSM_VBR_EVT_6C0  ( 54) /* DMAC DMAE        */
#define SSM_VBR_EVT_6E0  ( 55) /* Reserved         */
#define SSM_VBR_EVT_700  ( 56) /* Reserved         */
#define SSM_VBR_EVT_720  ( 57) /* Reserved         */
#define SSM_VBR_EVT_740  ( 58) /* Reserved         */
#define SSM_VBR_EVT_760  ( 59) /* Reserved         */
#define SSM_VBR_EVT_780  ( 60) /* DMAC DMTE4       */
#define SSM_VBR_EVT_7A0  ( 61) /* DMAC DMTE5       */
#define SSM_VBR_EVT_7C0  ( 62) /* DMAC DMTE6       */
#define SSM_VBR_EVT_7E0  ( 63) /* DMAC DMTE7       */
#define SSM_VBR_EVT_800  ( 64) /* Illegal FPU      */
#define SSM_VBR_EVT_820  ( 65) /* Illegal slot FPU */
#define SSM_VBR_EVT_840  ( 66) /* IRQ IRQ6         */
#define SSM_VBR_EVT_860  ( 67) /* IRQ IRQ7         */
#define SSM_VBR_EVT_880  ( 68) /* SCIF ERI0        */
#define SSM_VBR_EVT_8A0  ( 69) /* SCIF RXI0        */
#define SSM_VBR_EVT_8C0  ( 70) /* SCIF BRI0        */
#define SSM_VBR_EVT_8E0  ( 71) /* SCIF TXI0        */
#define SSM_VBR_EVT_900  ( 72) /* HCAN2 CANI0      */
#define SSM_VBR_EVT_920  ( 73) /* HCAN2 CANI1      */
#define SSM_VBR_EVT_940  ( 74) /* SSI SSII0        */
#define SSM_VBR_EVT_960  ( 75) /* SSI SSII1        */
#define SSM_VBR_EVT_980  ( 76) /* HAC HACI0        */
#define SSM_VBR_EVT_9A0  ( 77) /* HAC HACI1        */
#define SSM_VBR_EVT_9C0  ( 78) /* IIC IICI0        */
#define SSM_VBR_EVT_9E0  ( 79) /* IIC IICI1        */
#define SSM_VBR_EVT_A00  ( 80) /* USB USBI         */
#define SSM_VBR_EVT_A20  ( 81) /* LCDC VINT        */
#define SSM_VBR_EVT_A40  ( 82) /* Reserved         */
#define SSM_VBR_EVT_A60  ( 83) /* Reserved         */
#define SSM_VBR_EVT_A80  ( 84) /* DMABRG DMABRGI0  */
#define SSM_VBR_EVT_AA0  ( 85) /* DMABRG DMABRGI1  */
#define SSM_VBR_EVT_AC0  ( 86) /* DMABRG DMABRGI2  */
#define SSM_VBR_EVT_AE0  ( 87) /* Reserved         */
#define SSM_VBR_EVT_B00  ( 88) /* SCIF ERI1        */
#define SSM_VBR_EVT_B20  ( 89) /* SCIF RXI1        */
#define SSM_VBR_EVT_B40  ( 90) /* SCIF BRI1        */
#define SSM_VBR_EVT_B60  ( 91) /* SCIF TXI1        */
#define SSM_VBR_EVT_B80  ( 92) /* SCIF ERI2        */
#define SSM_VBR_EVT_BA0  ( 93) /* SCIF RXI2        */
#define SSM_VBR_EVT_BC0  ( 94) /* SCIF BRI2        */
#define SSM_VBR_EVT_BE0  ( 95) /* SCIF TXI2        */
#define SSM_VBR_EVT_C00  ( 96) /* SIM SIMERI       */
#define SSM_VBR_EVT_C20  ( 97) /* SIM SIMRXI       */
#define SSM_VBR_EVT_C40  ( 98) /* SIM SIMTXI       */
#define SSM_VBR_EVT_C60  ( 99) /* SIM SIMTEI       */
#define SSM_VBR_EVT_C80  (100) /* HSPI SPII        */
#define SSM_VBR_EVT_CA0  (101) /* Reserved         */
#define SSM_VBR_EVT_CC0  (102) /* Reserved         */
#define SSM_VBR_EVT_CE0  (103) /* Reserved         */
#define SSM_VBR_EVT_D00  (104) /* MMCIF MMCI0      */
#define SSM_VBR_EVT_D20  (105) /* MMCIF MMCI1      */
#define SSM_VBR_EVT_D40  (106) /* MMCIF MMCI2      */
#define SSM_VBR_EVT_D60  (107) /* MMCIF MMCI3      */
#define SSM_VBR_EVT_D80  (108) /* Reserved         */
#define SSM_VBR_EVT_DA0  (109) /* Reserved         */
#define SSM_VBR_EVT_DC0  (110) /* Reserved         */
#define SSM_VBR_EVT_DE0  (111) /* Reserved         */
#define SSM_VBR_EVT_E00  (112) /* Reserved         */
#define SSM_VBR_EVT_E20  (113) /* Reserved         */
#define SSM_VBR_EVT_E40  (114) /* Reserved         */
#define SSM_VBR_EVT_E60  (115) /* Reserved         */
#define SSM_VBR_EVT_E80  (116) /* MFI MFII         */
#define SSM_VBR_EVT_EA0  (117) /* Reserved         */
#define SSM_VBR_EVT_EC0  (118) /* Reserved         */
#define SSM_VBR_EVT_EE0  (119) /* Reserved         */
#define SSM_VBR_EVT_F00  (120) /* Reserved         */
#define SSM_VBR_EVT_F20  (121) /* Reserved         */
#define SSM_VBR_EVT_F40  (122) /* Reserved         */
#define SSM_VBR_EVT_F60  (123) /* Reserved         */
#define SSM_VBR_EVT_F80  (124) /* ADC ADI          */
#define SSM_VBR_EVT_FA0  (125) /* CMT CMTI         */

#if 0
  #! /usr/bin/perl
  $i =0;
  while(<>)
  {
    chomp;
    split qq|// |;
    printf "#define SSM_VBR_EVT_%s  (%3d) /* %-16s */\n"
      ,uc(substr($_[1],2,3)) ,$i ,substr($_[1],8);
    ++$i;
  }
#endif


// 
// user traps
//
#define SSM_VBR_TRP_CALLS (0x100)

#define ssm_vbr_trp_get(id_) \
  vbr_trp_tbl[(id_)]

#define ssm_vbr_trp_set(id_,func_) \
  vbr_trp_tbl[(id_)] = (ssm_vbr_call_f)(func_)

extern ssm_vbr_call_f vbr_trp_tbl[SSM_VBR_TRP_CALLS];

/**
 * trapa
 *  - call TRAPA #n (trap always)
 *
 * @param n_trap number of #n. n is 8 bit. 0<=n<=255
 * @return none
 * @see ut_vbr.c
 */
#if IN_LOCAL
# define trapa(n_trap_) \
  {                              \
    (vbr_trp_tbl[(n_trap_)])();  \
  }
#else
# define trapa(n_trap_) \
  {                         \
    uint32_t sr;            \
    asm volatile (          \
        "stc sr,%0\n"       \
      "  shlr16 %0\n" /*この瞬間にSR.BL=0->1が起こると防げない;-P*/ \
      "  shlr8  %0"         \
        : "=r"(sr) : : ""); \
    if (!(sr&0x10))         \
      asm volatile ("trapa %0"::"n"(n_trap_)); \
  }

#endif

#define SSM_VBR_EVT_T000  (  0) /* TRAPA #00 */
#define SSM_VBR_EVT_T001  (  1) /* TRAPA #01 */
#define SSM_VBR_EVT_T002  (  2) /* TRAPA #02 */
#define SSM_VBR_EVT_T003  (  3) /* TRAPA #03 */
#define SSM_VBR_EVT_T004  (  4) /* TRAPA #04 */
#define SSM_VBR_EVT_T005  (  5) /* TRAPA #05 */
#define SSM_VBR_EVT_T006  (  6) /* TRAPA #06 */
#define SSM_VBR_EVT_T007  (  7) /* TRAPA #07 */
#define SSM_VBR_EVT_T008  (  8) /* TRAPA #08 */
#define SSM_VBR_EVT_T009  (  9) /* TRAPA #09 */
#define SSM_VBR_EVT_T010  ( 10) /* TRAPA #0A */
#define SSM_VBR_EVT_T011  ( 11) /* TRAPA #0B */
#define SSM_VBR_EVT_T012  ( 12) /* TRAPA #0C */
#define SSM_VBR_EVT_T013  ( 13) /* TRAPA #0D */
#define SSM_VBR_EVT_T014  ( 14) /* TRAPA #0E */
#define SSM_VBR_EVT_T015  ( 15) /* TRAPA #0F */
#define SSM_VBR_EVT_T016  ( 16) /* TRAPA #10 */
#define SSM_VBR_EVT_T017  ( 17) /* TRAPA #11 */
#define SSM_VBR_EVT_T018  ( 18) /* TRAPA #12 */
#define SSM_VBR_EVT_T019  ( 19) /* TRAPA #13 */
#define SSM_VBR_EVT_T020  ( 20) /* TRAPA #14 */
#define SSM_VBR_EVT_T021  ( 21) /* TRAPA #15 */
#define SSM_VBR_EVT_T022  ( 22) /* TRAPA #16 */
#define SSM_VBR_EVT_T023  ( 23) /* TRAPA #17 */
#define SSM_VBR_EVT_T024  ( 24) /* TRAPA #18 */
#define SSM_VBR_EVT_T025  ( 25) /* TRAPA #19 */
#define SSM_VBR_EVT_T026  ( 26) /* TRAPA #1A */
#define SSM_VBR_EVT_T027  ( 27) /* TRAPA #1B */
#define SSM_VBR_EVT_T028  ( 28) /* TRAPA #1C */
#define SSM_VBR_EVT_T029  ( 29) /* TRAPA #1D */
#define SSM_VBR_EVT_T030  ( 30) /* TRAPA #1E */
#define SSM_VBR_EVT_T031  ( 31) /* TRAPA #1F */
#define SSM_VBR_EVT_T032  ( 32) /* TRAPA #20 */
#define SSM_VBR_EVT_T033  ( 33) /* TRAPA #21 */
#define SSM_VBR_EVT_T034  ( 34) /* TRAPA #22 */
#define SSM_VBR_EVT_T035  ( 35) /* TRAPA #23 */
#define SSM_VBR_EVT_T036  ( 36) /* TRAPA #24 */
#define SSM_VBR_EVT_T037  ( 37) /* TRAPA #25 */
#define SSM_VBR_EVT_T038  ( 38) /* TRAPA #26 */
#define SSM_VBR_EVT_T039  ( 39) /* TRAPA #27 */
#define SSM_VBR_EVT_T040  ( 40) /* TRAPA #28 */
#define SSM_VBR_EVT_T041  ( 41) /* TRAPA #29 */
#define SSM_VBR_EVT_T042  ( 42) /* TRAPA #2A */
#define SSM_VBR_EVT_T043  ( 43) /* TRAPA #2B */
#define SSM_VBR_EVT_T044  ( 44) /* TRAPA #2C */
#define SSM_VBR_EVT_T045  ( 45) /* TRAPA #2D */
#define SSM_VBR_EVT_T046  ( 46) /* TRAPA #2E */
#define SSM_VBR_EVT_T047  ( 47) /* TRAPA #2F */
#define SSM_VBR_EVT_T048  ( 48) /* TRAPA #30 */
#define SSM_VBR_EVT_T049  ( 49) /* TRAPA #31 */
#define SSM_VBR_EVT_T050  ( 50) /* TRAPA #32 */
#define SSM_VBR_EVT_T051  ( 51) /* TRAPA #33 */
#define SSM_VBR_EVT_T052  ( 52) /* TRAPA #34 */
#define SSM_VBR_EVT_T053  ( 53) /* TRAPA #35 */
#define SSM_VBR_EVT_T054  ( 54) /* TRAPA #36 */
#define SSM_VBR_EVT_T055  ( 55) /* TRAPA #37 */
#define SSM_VBR_EVT_T056  ( 56) /* TRAPA #38 */
#define SSM_VBR_EVT_T057  ( 57) /* TRAPA #39 */
#define SSM_VBR_EVT_T058  ( 58) /* TRAPA #3A */
#define SSM_VBR_EVT_T059  ( 59) /* TRAPA #3B */
#define SSM_VBR_EVT_T060  ( 60) /* TRAPA #3C */
#define SSM_VBR_EVT_T061  ( 61) /* TRAPA #3D */
#define SSM_VBR_EVT_T062  ( 62) /* TRAPA #3E */
#define SSM_VBR_EVT_T063  ( 63) /* TRAPA #3F */
#define SSM_VBR_EVT_T064  ( 64) /* TRAPA #40 */
#define SSM_VBR_EVT_T065  ( 65) /* TRAPA #41 */
#define SSM_VBR_EVT_T066  ( 66) /* TRAPA #42 */
#define SSM_VBR_EVT_T067  ( 67) /* TRAPA #43 */
#define SSM_VBR_EVT_T068  ( 68) /* TRAPA #44 */
#define SSM_VBR_EVT_T069  ( 69) /* TRAPA #45 */
#define SSM_VBR_EVT_T070  ( 70) /* TRAPA #46 */
#define SSM_VBR_EVT_T071  ( 71) /* TRAPA #47 */
#define SSM_VBR_EVT_T072  ( 72) /* TRAPA #48 */
#define SSM_VBR_EVT_T073  ( 73) /* TRAPA #49 */
#define SSM_VBR_EVT_T074  ( 74) /* TRAPA #4A */
#define SSM_VBR_EVT_T075  ( 75) /* TRAPA #4B */
#define SSM_VBR_EVT_T076  ( 76) /* TRAPA #4C */
#define SSM_VBR_EVT_T077  ( 77) /* TRAPA #4D */
#define SSM_VBR_EVT_T078  ( 78) /* TRAPA #4E */
#define SSM_VBR_EVT_T079  ( 79) /* TRAPA #4F */
#define SSM_VBR_EVT_T080  ( 80) /* TRAPA #50 */
#define SSM_VBR_EVT_T081  ( 81) /* TRAPA #51 */
#define SSM_VBR_EVT_T082  ( 82) /* TRAPA #52 */
#define SSM_VBR_EVT_T083  ( 83) /* TRAPA #53 */
#define SSM_VBR_EVT_T084  ( 84) /* TRAPA #54 */
#define SSM_VBR_EVT_T085  ( 85) /* TRAPA #55 */
#define SSM_VBR_EVT_T086  ( 86) /* TRAPA #56 */
#define SSM_VBR_EVT_T087  ( 87) /* TRAPA #57 */
#define SSM_VBR_EVT_T088  ( 88) /* TRAPA #58 */
#define SSM_VBR_EVT_T089  ( 89) /* TRAPA #59 */
#define SSM_VBR_EVT_T090  ( 90) /* TRAPA #5A */
#define SSM_VBR_EVT_T091  ( 91) /* TRAPA #5B */
#define SSM_VBR_EVT_T092  ( 92) /* TRAPA #5C */
#define SSM_VBR_EVT_T093  ( 93) /* TRAPA #5D */
#define SSM_VBR_EVT_T094  ( 94) /* TRAPA #5E */
#define SSM_VBR_EVT_T095  ( 95) /* TRAPA #5F */
#define SSM_VBR_EVT_T096  ( 96) /* TRAPA #60 */
#define SSM_VBR_EVT_T097  ( 97) /* TRAPA #61 */
#define SSM_VBR_EVT_T098  ( 98) /* TRAPA #62 */
#define SSM_VBR_EVT_T099  ( 99) /* TRAPA #63 */
#define SSM_VBR_EVT_T100  (100) /* TRAPA #64 */
#define SSM_VBR_EVT_T101  (101) /* TRAPA #65 */
#define SSM_VBR_EVT_T102  (102) /* TRAPA #66 */
#define SSM_VBR_EVT_T103  (103) /* TRAPA #67 */
#define SSM_VBR_EVT_T104  (104) /* TRAPA #68 */
#define SSM_VBR_EVT_T105  (105) /* TRAPA #69 */
#define SSM_VBR_EVT_T106  (106) /* TRAPA #6A */
#define SSM_VBR_EVT_T107  (107) /* TRAPA #6B */
#define SSM_VBR_EVT_T108  (108) /* TRAPA #6C */
#define SSM_VBR_EVT_T109  (109) /* TRAPA #6D */
#define SSM_VBR_EVT_T110  (110) /* TRAPA #6E */
#define SSM_VBR_EVT_T111  (111) /* TRAPA #6F */
#define SSM_VBR_EVT_T112  (112) /* TRAPA #70 */
#define SSM_VBR_EVT_T113  (113) /* TRAPA #71 */
#define SSM_VBR_EVT_T114  (114) /* TRAPA #72 */
#define SSM_VBR_EVT_T115  (115) /* TRAPA #73 */
#define SSM_VBR_EVT_T116  (116) /* TRAPA #74 */
#define SSM_VBR_EVT_T117  (117) /* TRAPA #75 */
#define SSM_VBR_EVT_T118  (118) /* TRAPA #76 */
#define SSM_VBR_EVT_T119  (119) /* TRAPA #77 */
#define SSM_VBR_EVT_T120  (120) /* TRAPA #78 */
#define SSM_VBR_EVT_T121  (121) /* TRAPA #79 */
#define SSM_VBR_EVT_T122  (122) /* TRAPA #7A */
#define SSM_VBR_EVT_T123  (123) /* TRAPA #7B */
#define SSM_VBR_EVT_T124  (124) /* TRAPA #7C */
#define SSM_VBR_EVT_T125  (125) /* TRAPA #7D */
#define SSM_VBR_EVT_T126  (126) /* TRAPA #7E */
#define SSM_VBR_EVT_T127  (127) /* TRAPA #7F */
#define SSM_VBR_EVT_T128  (128) /* TRAPA #80 */
#define SSM_VBR_EVT_T129  (129) /* TRAPA #81 */
#define SSM_VBR_EVT_T130  (130) /* TRAPA #82 */
#define SSM_VBR_EVT_T131  (131) /* TRAPA #83 */
#define SSM_VBR_EVT_T132  (132) /* TRAPA #84 */
#define SSM_VBR_EVT_T133  (133) /* TRAPA #85 */
#define SSM_VBR_EVT_T134  (134) /* TRAPA #86 */
#define SSM_VBR_EVT_T135  (135) /* TRAPA #87 */
#define SSM_VBR_EVT_T136  (136) /* TRAPA #88 */
#define SSM_VBR_EVT_T137  (137) /* TRAPA #89 */
#define SSM_VBR_EVT_T138  (138) /* TRAPA #8A */
#define SSM_VBR_EVT_T139  (139) /* TRAPA #8B */
#define SSM_VBR_EVT_T140  (140) /* TRAPA #8C */
#define SSM_VBR_EVT_T141  (141) /* TRAPA #8D */
#define SSM_VBR_EVT_T142  (142) /* TRAPA #8E */
#define SSM_VBR_EVT_T143  (143) /* TRAPA #8F */
#define SSM_VBR_EVT_T144  (144) /* TRAPA #90 */
#define SSM_VBR_EVT_T145  (145) /* TRAPA #91 */
#define SSM_VBR_EVT_T146  (146) /* TRAPA #92 */
#define SSM_VBR_EVT_T147  (147) /* TRAPA #93 */
#define SSM_VBR_EVT_T148  (148) /* TRAPA #94 */
#define SSM_VBR_EVT_T149  (149) /* TRAPA #95 */
#define SSM_VBR_EVT_T150  (150) /* TRAPA #96 */
#define SSM_VBR_EVT_T151  (151) /* TRAPA #97 */
#define SSM_VBR_EVT_T152  (152) /* TRAPA #98 */
#define SSM_VBR_EVT_T153  (153) /* TRAPA #99 */
#define SSM_VBR_EVT_T154  (154) /* TRAPA #9A */
#define SSM_VBR_EVT_T155  (155) /* TRAPA #9B */
#define SSM_VBR_EVT_T156  (156) /* TRAPA #9C */
#define SSM_VBR_EVT_T157  (157) /* TRAPA #9D */
#define SSM_VBR_EVT_T158  (158) /* TRAPA #9E */
#define SSM_VBR_EVT_T159  (159) /* TRAPA #9F */
#define SSM_VBR_EVT_T160  (160) /* TRAPA #A0 */
#define SSM_VBR_EVT_T161  (161) /* TRAPA #A1 */
#define SSM_VBR_EVT_T162  (162) /* TRAPA #A2 */
#define SSM_VBR_EVT_T163  (163) /* TRAPA #A3 */
#define SSM_VBR_EVT_T164  (164) /* TRAPA #A4 */
#define SSM_VBR_EVT_T165  (165) /* TRAPA #A5 */
#define SSM_VBR_EVT_T166  (166) /* TRAPA #A6 */
#define SSM_VBR_EVT_T167  (167) /* TRAPA #A7 */
#define SSM_VBR_EVT_T168  (168) /* TRAPA #A8 */
#define SSM_VBR_EVT_T169  (169) /* TRAPA #A9 */
#define SSM_VBR_EVT_T170  (170) /* TRAPA #AA */
#define SSM_VBR_EVT_T171  (171) /* TRAPA #AB */
#define SSM_VBR_EVT_T172  (172) /* TRAPA #AC */
#define SSM_VBR_EVT_T173  (173) /* TRAPA #AD */
#define SSM_VBR_EVT_T174  (174) /* TRAPA #AE */
#define SSM_VBR_EVT_T175  (175) /* TRAPA #AF */
#define SSM_VBR_EVT_T176  (176) /* TRAPA #B0 */
#define SSM_VBR_EVT_T177  (177) /* TRAPA #B1 */
#define SSM_VBR_EVT_T178  (178) /* TRAPA #B2 */
#define SSM_VBR_EVT_T179  (179) /* TRAPA #B3 */
#define SSM_VBR_EVT_T180  (180) /* TRAPA #B4 */
#define SSM_VBR_EVT_T181  (181) /* TRAPA #B5 */
#define SSM_VBR_EVT_T182  (182) /* TRAPA #B6 */
#define SSM_VBR_EVT_T183  (183) /* TRAPA #B7 */
#define SSM_VBR_EVT_T184  (184) /* TRAPA #B8 */
#define SSM_VBR_EVT_T185  (185) /* TRAPA #B9 */
#define SSM_VBR_EVT_T186  (186) /* TRAPA #BA */
#define SSM_VBR_EVT_T187  (187) /* TRAPA #BB */
#define SSM_VBR_EVT_T188  (188) /* TRAPA #BC */
#define SSM_VBR_EVT_T189  (189) /* TRAPA #BD */
#define SSM_VBR_EVT_T190  (190) /* TRAPA #BE */
#define SSM_VBR_EVT_T191  (191) /* TRAPA #BF */
#define SSM_VBR_EVT_T192  (192) /* TRAPA #C0 */
#define SSM_VBR_EVT_T193  (193) /* TRAPA #C1 */
#define SSM_VBR_EVT_T194  (194) /* TRAPA #C2 */
#define SSM_VBR_EVT_T195  (195) /* TRAPA #C3 */
#define SSM_VBR_EVT_T196  (196) /* TRAPA #C4 */
#define SSM_VBR_EVT_T197  (197) /* TRAPA #C5 */
#define SSM_VBR_EVT_T198  (198) /* TRAPA #C6 */
#define SSM_VBR_EVT_T199  (199) /* TRAPA #C7 */
#define SSM_VBR_EVT_T200  (200) /* TRAPA #C8 */
#define SSM_VBR_EVT_T201  (201) /* TRAPA #C9 */
#define SSM_VBR_EVT_T202  (202) /* TRAPA #CA */
#define SSM_VBR_EVT_T203  (203) /* TRAPA #CB */
#define SSM_VBR_EVT_T204  (204) /* TRAPA #CC */
#define SSM_VBR_EVT_T205  (205) /* TRAPA #CD */
#define SSM_VBR_EVT_T206  (206) /* TRAPA #CE */
#define SSM_VBR_EVT_T207  (207) /* TRAPA #CF */
#define SSM_VBR_EVT_T208  (208) /* TRAPA #D0 */
#define SSM_VBR_EVT_T209  (209) /* TRAPA #D1 */
#define SSM_VBR_EVT_T210  (210) /* TRAPA #D2 */
#define SSM_VBR_EVT_T211  (211) /* TRAPA #D3 */
#define SSM_VBR_EVT_T212  (212) /* TRAPA #D4 */
#define SSM_VBR_EVT_T213  (213) /* TRAPA #D5 */
#define SSM_VBR_EVT_T214  (214) /* TRAPA #D6 */
#define SSM_VBR_EVT_T215  (215) /* TRAPA #D7 */
#define SSM_VBR_EVT_T216  (216) /* TRAPA #D8 */
#define SSM_VBR_EVT_T217  (217) /* TRAPA #D9 */
#define SSM_VBR_EVT_T218  (218) /* TRAPA #DA */
#define SSM_VBR_EVT_T219  (219) /* TRAPA #DB */
#define SSM_VBR_EVT_T220  (220) /* TRAPA #DC */
#define SSM_VBR_EVT_T221  (221) /* TRAPA #DD */
#define SSM_VBR_EVT_T222  (222) /* TRAPA #DE */
#define SSM_VBR_EVT_T223  (223) /* TRAPA #DF */
#define SSM_VBR_EVT_T224  (224) /* TRAPA #E0 */
#define SSM_VBR_EVT_T225  (225) /* TRAPA #E1 */
#define SSM_VBR_EVT_T226  (226) /* TRAPA #E2 */
#define SSM_VBR_EVT_T227  (227) /* TRAPA #E3 */
#define SSM_VBR_EVT_T228  (228) /* TRAPA #E4 */
#define SSM_VBR_EVT_T229  (229) /* TRAPA #E5 */
#define SSM_VBR_EVT_T230  (230) /* TRAPA #E6 */
#define SSM_VBR_EVT_T231  (231) /* TRAPA #E7 */
#define SSM_VBR_EVT_T232  (232) /* TRAPA #E8 */
#define SSM_VBR_EVT_T233  (233) /* TRAPA #E9 */
#define SSM_VBR_EVT_T234  (234) /* TRAPA #EA */
#define SSM_VBR_EVT_T235  (235) /* TRAPA #EB */
#define SSM_VBR_EVT_T236  (236) /* TRAPA #EC */
#define SSM_VBR_EVT_T237  (237) /* TRAPA #ED */
#define SSM_VBR_EVT_T238  (238) /* TRAPA #EE */
#define SSM_VBR_EVT_T239  (239) /* TRAPA #EF */
#define SSM_VBR_EVT_T240  (240) /* TRAPA #F0 */
#define SSM_VBR_EVT_T241  (241) /* TRAPA #F1 */
#define SSM_VBR_EVT_T242  (242) /* TRAPA #F2 */
#define SSM_VBR_EVT_T243  (243) /* TRAPA #F3 */
#define SSM_VBR_EVT_T244  (244) /* TRAPA #F4 */
#define SSM_VBR_EVT_T245  (245) /* TRAPA #F5 */
#define SSM_VBR_EVT_T246  (246) /* TRAPA #F6 */
#define SSM_VBR_EVT_T247  (247) /* TRAPA #F7 */
#define SSM_VBR_EVT_T248  (248) /* TRAPA #F8 */
#define SSM_VBR_EVT_T249  (249) /* TRAPA #F9 */
#define SSM_VBR_EVT_T250  (250) /* TRAPA #FA */
#define SSM_VBR_EVT_T251  (251) /* TRAPA #FB */
#define SSM_VBR_EVT_T252  (252) /* TRAPA #FC */
#define SSM_VBR_EVT_T253  (253) /* TRAPA #FD */
#define SSM_VBR_EVT_T254  (254) /* TRAPA #FE */
#define SSM_VBR_EVT_T255  (255) /* TRAPA #FF */

#if 0

  #! /usr/bin/perl
  $i =0;
  while ($i<0x100)
  {
    #printf "#define SSM_VBR_EVT_T%03d  (%3d) /* TRAPA #%02X */\n" ,$i ,$i ,$i;
    printf "  reserve,      // [%3d] TRAPA #%02X\n" ,$i ,$i;
    ++$i;
  }

#endif

#endif/*__vbr_h__*/

/// vbr.c
///   this is a implementation for the simple slotmachine.
///
//  exception vector table for SH7660
//   

#include "settings.h"

#include "vbr.h"

#define reserve 0

ssm_vbr_call_f vbr_tbl[SSM_VBR_CALLS] =
{
    reserve     // [  0] 0x000 PowerOn reset
,   reserve     // [  1] 0x020 Manual reset
,   reserve     // [  2] 0x040 TLB miss(read)
,   reserve     // [  3] 0x060 TLB miss(write)
,   reserve     // [  4] 0x080 First Page write
,   reserve     // [  5] 0x0a0 TLB permition(read)
,   reserve     // [  6] 0x0c0 TLB permition(write)
,   reserve     // [  7] 0x0e0 Address error(raed)
,   reserve     // [  8] 0x100 Address error(write)
,   reserve     // [  9] 0x120 FPU exception
,   reserve     // [ 10] 0x140 TLB double hits
,   reserve     // [ 11] 0x160 TRAPA
,   reserve     // [ 12] 0x180 Illigal instruction
,   reserve     // [ 13] 0x1a0 Slot illigal instruction
,   reserve     // [ 14] 0x1c0 NMI
,   reserve     // [ 15] 0x1e0 User braek
,   reserve     // [ 16] 0x200 IRL15
,   reserve     // [ 17] 0x220 IRL14
,   reserve     // [ 18] 0x240 IRL13,IRL0
,   reserve     // [ 19] 0x260 IRL12
,   reserve     // [ 20] 0x280 IRL11
,   reserve     // [ 21] 0x2a0 IRL10,IRL1
,   reserve     // [ 22] 0x2c0 IRL9
,   reserve     // [ 23] 0x2e0 IRL8
,   reserve     // [ 24] 0x300 IRL7,IRL2
,   reserve     // [ 25] 0x320 IRL6
,   reserve     // [ 26] 0x340 IRL5
,   reserve     // [ 27] 0x360 IRL4,IRL3
,   reserve     // [ 28] 0x380 IRL3
,   reserve     // [ 29] 0x3a0 IRL2
,   reserve     // [ 30] 0x3c0 IRL1
,   reserve     // [ 31] 0x3e0 Reserved
,   reserve     // [ 32] 0x400 TUNI0
,   reserve     // [ 33] 0x420 TUNI1
,   reserve     // [ 34] 0x440 TUNI2
,   reserve     // [ 35] 0x460 TICPI2
,   reserve     // [ 36] 0x480 Reserved
,   reserve     // [ 37] 0x4a0 Reserved
,   reserve     // [ 38] 0x4c0 Reserved
,   reserve     // [ 39] 0x4e0 ReservedI
,   reserve     // [ 40] 0x500 Reserved
,   reserve     // [ 41] 0x520 Reserved
,   reserve     // [ 42] 0x540 Reserved
,   reserve     // [ 43] 0x560 WDT   ITI
,   reserve     // [ 44] 0x580 REF RCMI
,   reserve     // [ 45] 0x5a0 REF ROVI
,   reserve     // [ 46] 0x5c0 Reserved
,   reserve     // [ 47] 0x5e0 Reserved
,   reserve     // [ 48] 0x600 H-UDI
,   reserve     // [ 49] 0x620 GPIO GPIOI
,   reserve     // [ 50] 0x640 DMAC DMTE0
,   reserve     // [ 51] 0x660 DMAC DMTE1
,   reserve     // [ 52] 0x680 DMAC DMTE2
,   reserve     // [ 53] 0x6a0 DMAC DMTE3
,   reserve     // [ 54] 0x6c0 DMAC DMAE
,   reserve     // [ 55] 0x6e0 Reserved
,   reserve     // [ 56] 0x700 Reserved
,   reserve     // [ 57] 0x720 Reserved
,   reserve     // [ 58] 0x740 Reserved
,   reserve     // [ 59] 0x760 Reserved
,   reserve     // [ 60] 0x780 DMAC DMTE4
,   reserve     // [ 61] 0x7a0 DMAC DMTE5
,   reserve     // [ 62] 0x7c0 DMAC DMTE6
,   reserve     // [ 63] 0x7e0 DMAC DMTE7
,   reserve     // [ 64] 0x800 Illegal FPU
,   reserve     // [ 65] 0x820 Illegal slot FPU
,   reserve     // [ 66] 0x840 IRQ IRQ6
,   reserve     // [ 67] 0x860 IRQ IRQ7
,   reserve     // [ 68] 0x880 SCIF ERI0
,   reserve     // [ 69] 0x8a0 SCIF RXI0
,   reserve     // [ 70] 0x8c0 SCIF BRI0
,   reserve     // [ 71] 0x8e0 SCIF TXI0
,   reserve     // [ 72] 0x900 HCAN2 CANI0
,   reserve     // [ 73] 0x920 HCAN2 CANI1
,   reserve     // [ 74] 0x940 SSI SSII0
,   reserve     // [ 75] 0x960 SSI SSII1
,   reserve     // [ 76] 0x980 HAC HACI0
,   reserve     // [ 77] 0x9a0 HAC HACI1
,   reserve     // [ 78] 0x9c0 IIC IICI0
,   reserve     // [ 79] 0x9e0 IIC IICI1
,   reserve     // [ 80] 0xa00 USB USBI
,   reserve     // [ 81] 0xa20 LCDC VINT
,   reserve     // [ 82] 0xa40 Reserved
,   reserve     // [ 83] 0xa60 Reserved
,   reserve     // [ 84] 0xa80 DMABRG DMABRGI0
,   reserve     // [ 85] 0xaa0 DMABRG DMABRGI1
,   reserve     // [ 86] 0xac0 DMABRG DMABRGI2
,   reserve     // [ 87] 0xae0 Reserved
,   reserve     // [ 88] 0xb00 SCIF ERI1
,   reserve     // [ 89] 0xb20 SCIF RXI1
,   reserve     // [ 90] 0xb40 SCIF BRI1
,   reserve     // [ 91] 0xb60 SCIF TXI1
,   reserve     // [ 92] 0xb80 SCIF ERI2
,   reserve     // [ 93] 0xba0 SCIF RXI2
,   reserve     // [ 94] 0xbc0 SCIF BRI2
,   reserve     // [ 95] 0xbe0 SCIF TXI2
,   reserve     // [ 96] 0xc00 SIM SIMERI
,   reserve     // [ 97] 0xc20 SIM SIMRXI
,   reserve     // [ 98] 0xc40 SIM SIMTXI
,   reserve     // [ 99] 0xc60 SIM SIMTEI
,   reserve     // [100] 0xc80 HSPI SPII
,   reserve     // [101] 0xca0 Reserved
,   reserve     // [102] 0xcc0 Reserved
,   reserve     // [103] 0xce0 Reserved
,   reserve     // [104] 0xd00 MMCIF MMCI0
,   reserve     // [105] 0xd20 MMCIF MMCI1
,   reserve     // [106] 0xd40 MMCIF MMCI2
,   reserve     // [107] 0xd60 MMCIF MMCI3
,   reserve     // [108] 0xd80 Reserved
,   reserve     // [109] 0xda0 Reserved
,   reserve     // [110] 0xdc0 Reserved
,   reserve     // [111] 0xde0 Reserved
,   reserve     // [112] 0xe00 Reserved
,   reserve     // [113] 0xe20 Reserved
,   reserve     // [114] 0xe40 Reserved
,   reserve     // [115] 0xe60 Reserved
,   reserve     // [116] 0xe80 MFI MFII
,   reserve     // [117] 0xea0 Reserved
,   reserve     // [118] 0xec0 Reserved
,   reserve     // [119] 0xee0 Reserved
,   reserve     // [120] 0xf00 Reserved
,   reserve     // [121] 0xf20 Reserved
,   reserve     // [122] 0xf40 Reserved
,   reserve     // [123] 0xf60 Reserved
,   reserve     // [124] 0xf80 ADC ADI
,   reserve     // [125] 0xfa0 CMT CMTI
};

ssm_vbr_call_f vbr_trp_tbl[SSM_VBR_TRP_CALLS] =
{
    reserve     // [  0] TRAPA #00
,   reserve     // [  1] TRAPA #01
,   reserve     // [  2] TRAPA #02
,   reserve     // [  3] TRAPA #03
,   reserve     // [  4] TRAPA #04
,   reserve     // [  5] TRAPA #05
,   reserve     // [  6] TRAPA #06
,   reserve     // [  7] TRAPA #07
,   reserve     // [  8] TRAPA #08
,   reserve     // [  9] TRAPA #09
,   reserve     // [ 10] TRAPA #0A
,   reserve     // [ 11] TRAPA #0B
,   reserve     // [ 12] TRAPA #0C
,   reserve     // [ 13] TRAPA #0D
,   reserve     // [ 14] TRAPA #0E
,   reserve     // [ 15] TRAPA #0F
,   reserve     // [ 16] TRAPA #10
,   reserve     // [ 17] TRAPA #11
,   reserve     // [ 18] TRAPA #12
,   reserve     // [ 19] TRAPA #13
,   reserve     // [ 20] TRAPA #14
,   reserve     // [ 21] TRAPA #15
,   reserve     // [ 22] TRAPA #16
,   reserve     // [ 23] TRAPA #17
,   reserve     // [ 24] TRAPA #18
,   reserve     // [ 25] TRAPA #19
,   reserve     // [ 26] TRAPA #1A
,   reserve     // [ 27] TRAPA #1B
,   reserve     // [ 28] TRAPA #1C
,   reserve     // [ 29] TRAPA #1D
,   reserve     // [ 30] TRAPA #1E
,   reserve     // [ 31] TRAPA #1F
,   reserve     // [ 32] TRAPA #20
,   reserve     // [ 33] TRAPA #21
,   reserve     // [ 34] TRAPA #22
,   reserve     // [ 35] TRAPA #23
,   reserve     // [ 36] TRAPA #24
,   reserve     // [ 37] TRAPA #25
,   reserve     // [ 38] TRAPA #26
,   reserve     // [ 39] TRAPA #27
,   reserve     // [ 40] TRAPA #28
,   reserve     // [ 41] TRAPA #29
,   reserve     // [ 42] TRAPA #2A
,   reserve     // [ 43] TRAPA #2B
,   reserve     // [ 44] TRAPA #2C
,   reserve     // [ 45] TRAPA #2D
,   reserve     // [ 46] TRAPA #2E
,   reserve     // [ 47] TRAPA #2F
,   reserve     // [ 48] TRAPA #30
,   reserve     // [ 49] TRAPA #31
,   reserve     // [ 50] TRAPA #32
,   reserve     // [ 51] TRAPA #33
,   reserve     // [ 52] TRAPA #34
,   reserve     // [ 53] TRAPA #35
,   reserve     // [ 54] TRAPA #36
,   reserve     // [ 55] TRAPA #37
,   reserve     // [ 56] TRAPA #38
,   reserve     // [ 57] TRAPA #39
,   reserve     // [ 58] TRAPA #3A
,   reserve     // [ 59] TRAPA #3B
,   reserve     // [ 60] TRAPA #3C
,   reserve     // [ 61] TRAPA #3D
,   reserve     // [ 62] TRAPA #3E
,   reserve     // [ 63] TRAPA #3F
,   reserve     // [ 64] TRAPA #40
,   reserve     // [ 65] TRAPA #41
,   reserve     // [ 66] TRAPA #42
,   reserve     // [ 67] TRAPA #43
,   reserve     // [ 68] TRAPA #44
,   reserve     // [ 69] TRAPA #45
,   reserve     // [ 70] TRAPA #46
,   reserve     // [ 71] TRAPA #47
,   reserve     // [ 72] TRAPA #48
,   reserve     // [ 73] TRAPA #49
,   reserve     // [ 74] TRAPA #4A
,   reserve     // [ 75] TRAPA #4B
,   reserve     // [ 76] TRAPA #4C
,   reserve     // [ 77] TRAPA #4D
,   reserve     // [ 78] TRAPA #4E
,   reserve     // [ 79] TRAPA #4F
,   reserve     // [ 80] TRAPA #50
,   reserve     // [ 81] TRAPA #51
,   reserve     // [ 82] TRAPA #52
,   reserve     // [ 83] TRAPA #53
,   reserve     // [ 84] TRAPA #54
,   reserve     // [ 85] TRAPA #55
,   reserve     // [ 86] TRAPA #56
,   reserve     // [ 87] TRAPA #57
,   reserve     // [ 88] TRAPA #58
,   reserve     // [ 89] TRAPA #59
,   reserve     // [ 90] TRAPA #5A
,   reserve     // [ 91] TRAPA #5B
,   reserve     // [ 92] TRAPA #5C
,   reserve     // [ 93] TRAPA #5D
,   reserve     // [ 94] TRAPA #5E
,   reserve     // [ 95] TRAPA #5F
,   reserve     // [ 96] TRAPA #60
,   reserve     // [ 97] TRAPA #61
,   reserve     // [ 98] TRAPA #62
,   reserve     // [ 99] TRAPA #63
,   reserve     // [100] TRAPA #64
,   reserve     // [101] TRAPA #65
,   reserve     // [102] TRAPA #66
,   reserve     // [103] TRAPA #67
,   reserve     // [104] TRAPA #68
,   reserve     // [105] TRAPA #69
,   reserve     // [106] TRAPA #6A
,   reserve     // [107] TRAPA #6B
,   reserve     // [108] TRAPA #6C
,   reserve     // [109] TRAPA #6D
,   reserve     // [110] TRAPA #6E
,   reserve     // [111] TRAPA #6F
,   reserve     // [112] TRAPA #70
,   reserve     // [113] TRAPA #71
,   reserve     // [114] TRAPA #72
,   reserve     // [115] TRAPA #73
,   reserve     // [116] TRAPA #74
,   reserve     // [117] TRAPA #75
,   reserve     // [118] TRAPA #76
,   reserve     // [119] TRAPA #77
,   reserve     // [120] TRAPA #78
,   reserve     // [121] TRAPA #79
,   reserve     // [122] TRAPA #7A
,   reserve     // [123] TRAPA #7B
,   reserve     // [124] TRAPA #7C
,   reserve     // [125] TRAPA #7D
,   reserve     // [126] TRAPA #7E
,   reserve     // [127] TRAPA #7F
,   reserve     // [128] TRAPA #80
,   reserve     // [129] TRAPA #81
,   reserve     // [130] TRAPA #82
,   reserve     // [131] TRAPA #83
,   reserve     // [132] TRAPA #84
,   reserve     // [133] TRAPA #85
,   reserve     // [134] TRAPA #86
,   reserve     // [135] TRAPA #87
,   reserve     // [136] TRAPA #88
,   reserve     // [137] TRAPA #89
,   reserve     // [138] TRAPA #8A
,   reserve     // [139] TRAPA #8B
,   reserve     // [140] TRAPA #8C
,   reserve     // [141] TRAPA #8D
,   reserve     // [142] TRAPA #8E
,   reserve     // [143] TRAPA #8F
,   reserve     // [144] TRAPA #90
,   reserve     // [145] TRAPA #91
,   reserve     // [146] TRAPA #92
,   reserve     // [147] TRAPA #93
,   reserve     // [148] TRAPA #94
,   reserve     // [149] TRAPA #95
,   reserve     // [150] TRAPA #96
,   reserve     // [151] TRAPA #97
,   reserve     // [152] TRAPA #98
,   reserve     // [153] TRAPA #99
,   reserve     // [154] TRAPA #9A
,   reserve     // [155] TRAPA #9B
,   reserve     // [156] TRAPA #9C
,   reserve     // [157] TRAPA #9D
,   reserve     // [158] TRAPA #9E
,   reserve     // [159] TRAPA #9F
,   reserve     // [160] TRAPA #A0
,   reserve     // [161] TRAPA #A1
,   reserve     // [162] TRAPA #A2
,   reserve     // [163] TRAPA #A3
,   reserve     // [164] TRAPA #A4
,   reserve     // [165] TRAPA #A5
,   reserve     // [166] TRAPA #A6
,   reserve     // [167] TRAPA #A7
,   reserve     // [168] TRAPA #A8
,   reserve     // [169] TRAPA #A9
,   reserve     // [170] TRAPA #AA
,   reserve     // [171] TRAPA #AB
,   reserve     // [172] TRAPA #AC
,   reserve     // [173] TRAPA #AD
,   reserve     // [174] TRAPA #AE
,   reserve     // [175] TRAPA #AF
,   reserve     // [176] TRAPA #B0
,   reserve     // [177] TRAPA #B1
,   reserve     // [178] TRAPA #B2
,   reserve     // [179] TRAPA #B3
,   reserve     // [180] TRAPA #B4
,   reserve     // [181] TRAPA #B5
,   reserve     // [182] TRAPA #B6
,   reserve     // [183] TRAPA #B7
,   reserve     // [184] TRAPA #B8
,   reserve     // [185] TRAPA #B9
,   reserve     // [186] TRAPA #BA
,   reserve     // [187] TRAPA #BB
,   reserve     // [188] TRAPA #BC
,   reserve     // [189] TRAPA #BD
,   reserve     // [190] TRAPA #BE
,   reserve     // [191] TRAPA #BF
,   reserve     // [192] TRAPA #C0
,   reserve     // [193] TRAPA #C1
,   reserve     // [194] TRAPA #C2
,   reserve     // [195] TRAPA #C3
,   reserve     // [196] TRAPA #C4
,   reserve     // [197] TRAPA #C5
,   reserve     // [198] TRAPA #C6
,   reserve     // [199] TRAPA #C7
,   reserve     // [200] TRAPA #C8
,   reserve     // [201] TRAPA #C9
,   reserve     // [202] TRAPA #CA
,   reserve     // [203] TRAPA #CB
,   reserve     // [204] TRAPA #CC
,   reserve     // [205] TRAPA #CD
,   reserve     // [206] TRAPA #CE
,   reserve     // [207] TRAPA #CF
,   reserve     // [208] TRAPA #D0
,   reserve     // [209] TRAPA #D1
,   reserve     // [210] TRAPA #D2
,   reserve     // [211] TRAPA #D3
,   reserve     // [212] TRAPA #D4
,   reserve     // [213] TRAPA #D5
,   reserve     // [214] TRAPA #D6
,   reserve     // [215] TRAPA #D7
,   reserve     // [216] TRAPA #D8
,   reserve     // [217] TRAPA #D9
,   reserve     // [218] TRAPA #DA
,   reserve     // [219] TRAPA #DB
,   reserve     // [220] TRAPA #DC
,   reserve     // [221] TRAPA #DD
,   reserve     // [222] TRAPA #DE
,   reserve     // [223] TRAPA #DF
,   reserve     // [224] TRAPA #E0
,   reserve     // [225] TRAPA #E1
,   reserve     // [226] TRAPA #E2
,   reserve     // [227] TRAPA #E3
,   reserve     // [228] TRAPA #E4
,   reserve     // [229] TRAPA #E5
,   reserve     // [230] TRAPA #E6
,   reserve     // [231] TRAPA #E7
,   reserve     // [232] TRAPA #E8
,   reserve     // [233] TRAPA #E9
,   reserve     // [234] TRAPA #EA
,   reserve     // [235] TRAPA #EB
,   reserve     // [236] TRAPA #EC
,   reserve     // [237] TRAPA #ED
,   reserve     // [238] TRAPA #EE
,   reserve     // [239] TRAPA #EF
,   reserve     // [240] TRAPA #F0
,   reserve     // [241] TRAPA #F1
,   reserve     // [242] TRAPA #F2
,   reserve     // [243] TRAPA #F3
,   reserve     // [244] TRAPA #F4
,   reserve     // [245] TRAPA #F5
,   reserve     // [246] TRAPA #F6
,   reserve     // [247] TRAPA #F7
,   reserve     // [248] TRAPA #F8
,   reserve     // [249] TRAPA #F9
,   reserve     // [250] TRAPA #FA
,   reserve     // [251] TRAPA #FB
,   reserve     // [252] TRAPA #FC
,   reserve     // [253] TRAPA #FD
,   reserve     // [254] TRAPA #FE
,   reserve     // [255] TRAPA #FF
};

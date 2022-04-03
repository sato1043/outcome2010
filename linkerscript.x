/* ---------------------------------------------------------------------
# 組込みソフトウェア科学習用makefile
# original created 2008.10.24 By HN
# modified by satot43@yahoo.co.jp at Nov.2009
# ---------------------------------------------------------------------*/

OUTPUT_FORMAT("elf32-sh-linux","elf32-sh-linux","elf32-sh-linux")
OUTPUT_ARCH(sh)

ENTRY("__START")

/*
MEMORY
{
	ROM(rx)    : org = 0xA0000000, len = 16*1024*1024
	SDRAM(rxx) : org = 0x8C000000, len = 64*1024*1024
}
*/

SECTIONS
{
	.text 0xA0000000 :
    { startup.o(.text) exp_hndl.o(.text) *(.text) }
	.rodata :
    { *(.rodata) }
	. =ALIGN(4);
	_data_rom_start = .; /* ROM上の.dataの開始アドレス */

	.data 0x8C000000 :
    AT ( ADDR (.rodata) + SIZEOF (.rodata) )
    { _data_start = . ; *(.data*); _data_end   = . ; }
	.bss ALIGN(4) :
    { _bss_start = . ; *(.bss) *(COMMON); _bss_end   = . ; }
	.stack ALIGN(0x1000) :
    { *(.stack) }
}


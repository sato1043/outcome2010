
IN_LOCAL = NO

NDEBUG = YES

ifeq (${IN_LOCAL},NO)
CROSS_COMPILE = sh4-linux-
endif 
CC = ${CROSS_COMPILE}gcc
LD = ${CROSS_COMPILE}gcc
AS = ${CROSS_COMPILE}as
OD = ${CROSS_COMPILE}objdump
OC = ${CROSS_COMPILE}objcopy
ST = ${CROSS_COMPILE}strip

RM=rm -rf
ECHO=echo
CTAGS=ctags

ifeq (${IN_LOCAL},NO)
CFLAGS = -O0 -Wall -gdwarf-2 -m4-nofpu -ml -I.
AFLAGS = 
LDFLAGS = -static -nostdlib -T linkerscript.x
else
CFLAGS = -O0 -Wall -g -DIN_LOCAL -I.
AFLAGS = 
LDFLAGS = -static -DIN_LOCAL -lrt -pthread
endif

ifeq (${NDEBUG},YES)
CFLAGS+= -DNDEBUG
endif

.SUFFIXES:
.SUFFIXES: .o .s .c .out .mot

.s.o:
	${AS}    ${AFLAGS} $< -o $@

.c.o:
	${CC} -c ${CFLAGS} $< -o $@

.out.mot:
	${OC} -R .bss -R .bss0 -R .comment -O srec -S $< $@

# ---------------------------------------------------------------------

PRIMARY = slotmachine

ASRCS = \
	startup.s \
	exp_hndl.s \

SRCS = \
  sr.c \
  vbr.c \
  ppi.c \
  led.c \
  tmu.c \
  ddsp.c \
  swth.c \
  inpt.c \
  ctx.c \
  drum.c \
  rotation.c

ifeq (${NDEBUG},NO)
SRCS+= \
  test/ut_ppi.c \
  test/ut_sr.c \
  test/ut_vbr.c \
  test/ut_tmu.c \
  test/ut_led.c \
  test/ut_ddsp.c \
  test/ut_swth.c \
  test/ut_inpt.c \
  test/ut_ctx.c \
  test/ut_drum.c \
  test/ut_rotation.c \
  test/ut_main.c
else
SRCS+= \
  main.c
endif

ifeq (${IN_LOCAL},NO)
OBJS = ${ASRCS:.s=.o} ${SRCS:.c=.o} stdlib_stub.o
else
OBJS = ${SRCS:.c=.o}
endif

TSTS = ${TSRCS:.c=.o}

SRCDIR = .
OUTDIR = debug

OUTPUT = ${OUTDIR}/${PRIMARY}.out
OUTROM = ${OUTDIR}/${PRIMARY}.mot

# ---------------------------------------------------------------------
.PHONY: all clean strip show-sections tags depend test

all: tags depend ${OUTPUT} ${OUTROM}

${OUTPUT}: ${OUTDIR} ${OBJS}
	${LD} -o $@ ${OBJS} -lgcc ${LDFLAGS}

${OUTDIR}:
	mkdir ${OUTDIR}

test:${OUTPUT}
	./${OUTPUT}


show-sections: ${OUTPUT}
	${OD} -h ${OUTPUT}

strip: ${OUTPUT}
	${ST} ${OUTPUT}

clean:
	-${RM} *.o
	-${RM} test/*.o
	-${RM} ${OUTDIR}
	-${RM} *~ core tags
	-${RM} test/*~ test/core test/tags
	-${ECHO} > Makefile.deps

tags:
	-ctags -R *.c *.h

depend:
	$(CC) $(CFLAGS) -M $(SRCS) $(TSRCS) >> Makefile.deps

Makefile.deps: depend

include Makefile.deps

#  End of Makefile

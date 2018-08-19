include ../../../config.mk

EXTRA_FLAGS=

ludcmp: ludcmp.c ludcmp.h
	${VERBOSE} ${CC} -o ludcmp ludcmp.c ${CFLAGS} -I. -I../../../utilities ../../../utilities/polybench.c 

clean:
	@ rm -f ludcmp


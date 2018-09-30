include ../../../config.mk

EXTRA_FLAGS=

lu: lu.c lu.h
	${VERBOSE} ${CC} -o lu lu.c ${CFLAGS} -I. -I../../../utilities ../../../utilities/polybench.c 

clean:
	@ rm -f lu


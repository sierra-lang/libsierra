include ../../../config.mk

EXTRA_FLAGS=

symm: symm.c symm.h
	${VERBOSE} ${CC} -o symm symm.c ${CFLAGS} -I. -I../../../utilities ../../../utilities/polybench.c 

clean:
	@ rm -f symm


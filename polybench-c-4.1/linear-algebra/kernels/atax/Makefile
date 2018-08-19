include ../../../config.mk

EXTRA_FLAGS=

atax: atax.c atax.h
	${VERBOSE} ${CC} -o atax atax.c ${CFLAGS} -I. -I../../../utilities ../../../utilities/polybench.c 

clean:
	@ rm -f atax


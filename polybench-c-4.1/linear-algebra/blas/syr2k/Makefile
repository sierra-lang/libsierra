include ../../../config.mk

EXTRA_FLAGS=

syr2k: syr2k.c syr2k.h
	${VERBOSE} ${CC} -o syr2k syr2k.c ${CFLAGS} -I. -I../../../utilities ../../../utilities/polybench.c 

clean:
	@ rm -f syr2k


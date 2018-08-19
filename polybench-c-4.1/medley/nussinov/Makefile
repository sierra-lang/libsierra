include ../../config.mk

EXTRA_FLAGS=

nussinov: nussinov.c nussinov.h
	${VERBOSE} ${CC} -o nussinov nussinov.c ${CFLAGS} -I. -I../../utilities ../../utilities/polybench.c 

clean:
	@ rm -f nussinov


include ../../../config.mk

EXTRA_FLAGS=

gemm: gemm.c gemm.h
	${VERBOSE} ${CC} -o gemm gemm.c ${CFLAGS} -I. -I../../../utilities ../../../utilities/polybench.c 

clean:
	@ rm -f gemm


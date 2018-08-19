include ../../config.mk

EXTRA_FLAGS=

seidel-2d: seidel-2d.c seidel-2d.h
	${VERBOSE} ${CC} -o seidel-2d seidel-2d.c ${CFLAGS} -I. -I../../utilities ../../utilities/polybench.c 

clean:
	@ rm -f seidel-2d


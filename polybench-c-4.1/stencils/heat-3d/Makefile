include ../../config.mk

EXTRA_FLAGS=

heat-3d: heat-3d.c heat-3d.h
	${VERBOSE} ${CC} -o heat-3d heat-3d.c ${CFLAGS} -I. -I../../utilities ../../utilities/polybench.c 

clean:
	@ rm -f heat-3d


include ../../config.mk

EXTRA_FLAGS=

floyd-warshall: floyd-warshall.c floyd-warshall.h
	${VERBOSE} ${CC} -o floyd-warshall floyd-warshall.c ${CFLAGS} -I. -I../../utilities ../../utilities/polybench.c 

clean:
	@ rm -f floyd-warshall


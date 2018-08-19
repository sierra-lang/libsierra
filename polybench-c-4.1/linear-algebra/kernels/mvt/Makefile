include ../../../config.mk

EXTRA_FLAGS=-DEXTRALARGE_DATASET -mllvm

mvt: mvt.c mvt.h
	${VERBOSE} ${CC} -o mvt mvt.c ${CFLAGS} ${EXTRA_FLAGS} -I. -I../../../utilities ../../../utilities/polybench.c 

clean:
	@ rm -f mvt *.ll *.tmp


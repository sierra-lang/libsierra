include ../../../config.mk

EXTRA_FLAGS=

gesummv: gesummv.c gesummv.h
	${VERBOSE} ${CC} -o gesummv gesummv.c ${CFLAGS} -I. -I../../../utilities ../../../utilities/polybench.c 

clean:
	@ rm -f gesummv


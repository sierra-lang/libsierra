include ../../config.mk

EXTRA_FLAGS=

adi: adi.c adi.h
	${VERBOSE} ${CC} -o adi adi.c ${CFLAGS} -I. -I../../utilities ../../utilities/polybench.c 

clean:
	@ rm -f adi


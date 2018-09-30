include ../../config.mk

EXTRA_FLAGS=

covariance: covariance.c covariance.h
	${VERBOSE} ${CC} -o covariance covariance.c ${CFLAGS} -I. -I../../utilities ../../utilities/polybench.c 

clean:
	@ rm -f covariance


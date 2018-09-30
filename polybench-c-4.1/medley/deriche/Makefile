include ../../config.mk

EXTRA_FLAGS=

deriche: deriche.c deriche.h
	${VERBOSE} ${CC} -o deriche deriche.c ${CFLAGS} -I. -I../../utilities ../../utilities/polybench.c 

clean:
	@ rm -f deriche *.ll


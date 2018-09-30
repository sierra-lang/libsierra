include ../../../config.mk

EXTRA_FLAGS=-lm

gramschmidt: gramschmidt.c gramschmidt.h
	${VERBOSE} ${CC} -o gramschmidt gramschmidt.c ${CFLAGS} -I. -I../../../utilities ../../../utilities/polybench.c 

clean:
	@ rm -f gramschmidt


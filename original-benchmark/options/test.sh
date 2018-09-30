#!/bin/bash

ERR=0
NUM_TESTS=1

BINARIES=(\
	"options.sse-scalar" \
	"options.sse-4x" \
	"options.sse-8x" \
	"options.avx-scalar" \
	"options.avx-8x" \
	"options.avx-16x" \
	);

if [ $# -eq 1 ];
then
	NUM_TESTS=$1;
fi

for BIN in ${BINARIES[*]};
do
	echo ">> ${BIN} ${NUM_TESTS}";
	./${BIN} ${NUM_TESTS};
	echo
done

exit 0

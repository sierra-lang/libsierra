#!/bin/bash

ERR=0
NUM_TESTS=1

BINARIES=(\
	"mandelbrot.sse-scalar" \
	"mandelbrot.sse-4x" \
	"mandelbrot.sse-8x" \
	"mandelbrot.sse-16x" \
	"mandelbrot.avx-scalar" \
	"mandelbrot.avx-4x" \
	"mandelbrot.avx-8x" \
	"mandelbrot.avx-16x" \
	);

if [ $# -eq 1 ];
then
	NUM_TESTS=$1;
fi

for BIN in ${BINARIES[*]};
do
	rm -f ${BIN}.ppm;
	echo ">> ${BIN} ${NUM_TESTS}";
	./${BIN} ${NUM_TESTS};
	mv -f out.ppm ${BIN}.ppm;
	echo
done

REFSUM=$(md5sum ${BINARIES[0]}.ppm | awk '{print $1}');
echo "md5sum for ${BINARIES[0]}.ppm: ${REFSUM}";

i=1
while [ $i -lt ${#BINARIES[*]} ];
do
	MD5SUM=$(md5sum ${BINARIES[i]}.ppm | awk '{print $1}');

	if [ "${REFSUM}" != "${MD5SUM}" ];
	then
		ERR=1;
		echo "WARNING: md5sum for ${BINARIES[i]}.ppm differs";
	fi

	let "i++"
done

exit ${ERR};

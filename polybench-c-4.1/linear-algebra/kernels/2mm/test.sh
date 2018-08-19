#!/bin/bash

ERR=0
NUM_TESTS=1

BINARIES=(\
	"2mm.sse-scalar" \
	"2mm.sse-4x" \
	"2mm.sse-8x" \
	"2mm.sse-16x" \
	"2mm.avx-scalar" \
	"2mm.avx-4x" \
	"2mm.avx-8x" \
	"2mm.avx-16x" \
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

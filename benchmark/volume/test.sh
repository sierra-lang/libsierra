#!/bin/bash

ERR=0
NUM_TESTS=1

BINARIES=(\
	"volume.sse-scalar" \
	"volume.sse-4x" \
	"volume.sse-8x" \
	"volume.avx-scalar" \
	"volume.avx-8x" \
	"volume.avx-16x" \
	);

if [ $# -eq 1 ];
then
	NUM_TESTS=$1;
fi

# low-res
for BIN in ${BINARIES[*]};
do
	rm -f ${BIN}.ppm;
	echo ">> ${BIN} camera.dat density_lowres.vol ${NUM_TESTS}";
	./${BIN} camera.dat density_lowres.vol ${NUM_TESTS};
	mv -f out.ppm ${BIN}.lowres.ppm;
	echo
done

REFSUM=$(md5sum ${BINARIES[0]}.lowres.ppm | awk '{print $1}');
echo "md5sum for ${BINARIES[0]}.lowres.ppm: ${REFSUM}";

i=1
while [ $i -lt ${#BINARIES[*]} ];
do
	MD5SUM=$(md5sum ${BINARIES[i]}.lowres.ppm | awk '{print $1}');

	if [ "${REFSUM}" != "${MD5SUM}" ];
	then
		ERR=1;
		echo "WARNING: md5sum for ${BINARIES[i]}.lowres.ppm differs";
	fi

	let "i++"
done

if [ ${ERR} -ne 0 ];
then
  exit 1;
fi


# high-res
echo
for BIN in ${BINARIES[*]};
do
	rm -f ${BIN}.ppm;
	echo ">> ${BIN} camera.dat density_highres.vol ${NUM_TESTS}";
	./${BIN} camera.dat density_highres.vol ${NUM_TESTS};
	mv -f out.ppm ${BIN}.highres.ppm;
	echo
done

REFSUM=$(md5sum ${BINARIES[0]}.highres.ppm | awk '{print $1}');
echo "md5sum for ${BINARIES[0]}.highres.ppm: ${REFSUM}";

i=1
while [ $i -lt ${#BINARIES[*]} ];
do
	MD5SUM=$(md5sum ${BINARIES[i]}.highres.ppm | awk '{print $1}');

	if [ "${REFSUM}" != "${MD5SUM}" ];
	then
		ERR=1;
		echo "WARNING: md5sum for ${BINARIES[i]}.highres.ppm differs";
	fi

	let "i++"
done

exit ${ERR};

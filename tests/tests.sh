#!/bin/bash

ALL=0
FAILURE=0

for FILE in $@;
do
	sh -c "./test.sh ${FILE}"
	if [ $? -ne 0 ];
	then
		FAILURE=$(expr ${FAILURE} + 1)
	fi
	ALL=$(expr ${ALL} + 1)
done

echo "${ALL} tests run"
echo "${FAILURE} tests failed, $(expr ${ALL} - ${FAILURE}) tests passed"

if [ ${FAILURE} -ne 0 ];
then
	exit 1
fi

exit 0

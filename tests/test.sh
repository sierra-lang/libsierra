#!/bin/bash

if [ $# -ne 1 ];
then
  echo "ERROR:   Illegal number of arguments: $#"
  exit 1
fi

if [ ! -f $1 ];
then
  echo "ERROR:   File '$1' does not exist"
  exit 1
fi

SRC="$1.cpp"

if [ ! -f ${SRC} ];
then
  echo "ERROR:   Source file '${SRC}' not found"
  exit 1
fi

RESULT=$(grep --color=never -e '$RESULT:' "${SRC}" | sed -e 's/^.*$RESULT: *//' - | awk '{print $1}')

sh -c "$1"
ACTUAL=$?

if [ ${ACTUAL} -ne ${RESULT} ];
then
  echo "WARNING: $1: expected ${RESULT} but was ${ACTUAL}"
	exit 1
fi

echo "PASS:    $1"
exit 0

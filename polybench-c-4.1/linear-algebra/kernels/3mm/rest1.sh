#!/bin/sh -x

DATASETSIZE='-DEXTRALARGE_DATASET'
#DATASETSIZE='-DLARGE_DATASET'
#DATASETSIZE='-DSTANDARD_DATASET'
#DATASETSIZE='-DSMALL_DATASET'
#DATASETSIZE='-DMINI_DATASET'

#DUMP=''
DUMP='-DPOLYBENCH_DUMP_ARRAYS'

FILE='3mm'

#DEBUG=''
#DEBUG='-debug'
DEBUG='-debug-only=polly-ast'


UTILITY='../../../utilities'
POLY="$UTILITY/polybench.c"
FLAGS="-pthread -fopenmp -lm $POLY"
INCLUDES="-I. -I$UTILITY"






# optimize ll files by applying o3 with opt
opt -S -O3 $FILE-tileparallel.ll > $FILE-tileparallelend.ll
opt -S -O3 $FILE-tileboth.ll > $FILE-tilebothend.ll

# build executables of the new optimized files without o3
clang -O3 $FILE-tileparallelend.ll -o $FILE-tileparallel.exe $FLAGS -DPOLYBENCH_TIME $DATASETSIZE $DUMP
clang -O3 $FILE-tilebothend.ll -o $FILE-tileboth.exe $FLAGS -DPOLYBENCH_TIME $DATASETSIZE $DUMP





MINPARALLEL=`./$FILE-tileparallel.exe 2> dump-$FILE-tileparallel.txt`
MINBOTH=`./$FILE-tileboth.exe 2> dump-$FILE-tileboth.txt`


# run everything
for i in `seq 1 10`; do
    TMP=`./$FILE-tileparallel.exe 2> dump-$FILE-tileparallel.txt`
    if (( $(echo "$MINPARALLEL > $TMP" | bc -l) )); then
        MINPARALLEL=$TMP
    fi
    TMP=`./$FILE-tileboth.exe 2> dump-$FILE-tileboth.txt`
    if (( $(echo "$MINBOTH > $TMP" | bc -l) )); then
        MINBOTH=$TMP
    fi
done


echo "=========== 11 runs and picked out the minimum respectively ============="
echo ""
echo "tileparallel"
echo "$MINPARALLEL"
echo ""
echo "tileboth"
echo "$MINBOTH"
echo ""


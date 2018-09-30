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



clang $INCLUDES -pthread -fopenmp -DPOLYBENCH_TIME -DPOLYBENCH_USE_C99_PROTO $DATASETSIZE $DUMP -S -emit-llvm $FILE.c
opt -S -polly-canonicalize $FILE.ll > $FILE.tmp


# apply optimizations with tiling
opt -S -polly-opt-isl -polly-codegen -polly-parallel $FILE.tmp $DEBUG -pass-remarks-analysis=polly-scops -polly-scops > $FILE-tileparallel.ll 2> c.debug
opt -S -polly-opt-isl -polly-codegen -polly-task -polly-parallel $FILE.tmp $DEBUG -pass-remarks-analysis=polly-scops -polly-scops > $FILE-tileboth.ll 2> d.debug

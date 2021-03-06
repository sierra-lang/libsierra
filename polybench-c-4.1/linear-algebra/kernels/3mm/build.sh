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




# prepare for the optimizations
clang $INCLUDES -pthread -fopenmp -DPOLYBENCH_TIME -DPOLYBENCH_USE_C99_PROTO $DATASETSIZE $DUMP -S -emit-llvm $FILE.c
opt -S -polly-canonicalize $FILE.ll > $FILE.tmp

# apply optimizations with tiling
opt -S -polly-opt-isl -polly-codegen $FILE.tmp $DEBUG -pass-remarks-analysis=polly-scops -polly-scops > $FILE-onlytile.ll 2> a.debug
opt -S -polly-opt-isl -polly-codegen -polly-task $FILE.tmp $DEBUG -pass-remarks-analysis=polly-scops -polly-scops > $FILE-tiletask.ll 2> b.debug
# apply optimizations without tiling
opt -S -polly-codegen -polly-parallel $FILE.tmp $DEBUG -pass-remarks-analysis=polly-scops -polly-scops > $FILE-parallel.ll 2> c.debug
opt -S -polly-codegen -polly-task $FILE.tmp $DEBUG -pass-remarks-analysis=polly-scops -polly-scops > $FILE-task.ll 2> b.debug
opt -S -polly-codegen -polly-task -polly-parallel $FILE.tmp $DEBUG -pass-remarks-analysis=polly-scops -polly-scops > $FILE-both.ll 2> d.debug

# optimize ll files by applying o3 with opt
opt -S -O3 $FILE-onlytile.ll > $FILE-onlytileend.ll
opt -S -O3 $FILE-tiletask.ll > $FILE-tiletaskend.ll
opt -S -O3 $FILE-parallel.ll > $FILE-parallelend.ll
opt -S -O3 $FILE-task.ll > $FILE-taskend.ll
opt -S -O3 $FILE-both.ll > $FILE-bothend.ll

# build executables of the new optimized files without o3
clang -O3 $FILE-onlytileend.ll -o $FILE-onlytile.exe $FLAGS -DPOLYBENCH_TIME $DATASETSIZE $DUMP
clang -O3 $FILE-tiletaskend.ll -o $FILE-tiletask.exe $FLAGS -DPOLYBENCH_TIME $DATASETSIZE $DUMP

clang -O3 $FILE-taskend.ll -o $FILE-task.exe $FLAGS -DPOLYBENCH_TIME $DATASETSIZE $DUMP
clang -O3 $FILE-parallelend.ll -o $FILE-parallel.exe $FLAGS -DPOLYBENCH_TIME $DATASETSIZE $DUMP
clang -O3 $FILE-bothend.ll -o $FILE-both.exe $FLAGS -DPOLYBENCH_TIME $DATASETSIZE $DUMP

# create normal executable which is the baseline
clang -O3 -pthread -fopenmp -lm -o $FILE.exe $FILE.c -DPOLYBENCH_TIME -DPOLYBENCH_USE_C99_PROTO $DATASETSIZE $DUMP $INCLUDES $POLY


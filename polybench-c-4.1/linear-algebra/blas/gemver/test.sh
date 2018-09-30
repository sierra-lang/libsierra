#!/bin/sh -x

DATASETSIZE='-DEXTRALARGE_DATASET'
#DATASETSIZE='-DLARGE_DATASET'
#DATASETSIZE='-DSTANDARD_DATASET'
#DATASETSIZE='-DSMALL_DATASET'
#DATASETSIZE='-DMINI_DATASET'

DUMP=''
#DUMP='-DPOLYBENCH_DUMP_ARRAYS'

FILE='gemver'

#DEBUG=''
#DEBUG='-debug'
DEBUG='-debug-only=polly-ast'




# create executable with polly task parallel
clang -I. -I../../../utilities -pthread -fopenmp -DPOLYBENCH_TIME -DPOLYBENCH_USE_C99_PROTO $DATASETSIZE $DUMP -S -emit-llvm $FILE.c

opt -S -polly-canonicalize $FILE.ll > $FILE.tmp

opt -S -polly-codegen -polly-task $FILE.tmp $DEBUG -pass-remarks-analysis=polly-scops -polly-scops > $FILE-end.ll 2> b.out

clang $FILE-end.ll -o $FILE-tasks -pthread -fopenmp -lm ../../../utilities/polybench.c -DPOLYBENCH_TIME $DATASETSIZE $DUMP
clang -O3 $FILE-end.ll -o $FILE-tasks-o3 -pthread -fopenmp -lm ../../../utilities/polybench.c -DPOLYBENCH_TIME $DATASETSIZE $DUMP


opt -O3 $FILE-end.ll > $FILE-endend.ll

clang $FILE-endend.ll -o $FILE-opt-tasks -pthread -fopenmp -lm ../../../utilities/polybench.c -DPOLYBENCH_TIME $DATASETSIZE $DUMP
clang -O3 $FILE-endend.ll -o $FILE-opt-tasks-o3 -pthread -fopenmp -lm ../../../utilities/polybench.c -DPOLYBENCH_TIME $DATASETSIZE $DUMP



# create normal executable
clang -O3 -pthread -fopenmp -lm -o $FILE $FILE.c -DPOLYBENCH_TIME -DPOLYBENCH_USE_C99_PROTO $DATASETSIZE $DUMP -I. -I../../../utilities ../../../utilities/polybench.c



# run everything
echo ""
echo "$FILE"
./$FILE 2> dump-$FILE.txt

echo ""
echo "tasks"
./$FILE-tasks 2> dump-$FILE-task.txt

echo ""
echo "tasks o3"
./$FILE-tasks-o3 2> dump-$FILE-tasko3.txt

echo ""
echo "opt tasks"
./$FILE-opt-tasks 2> dump-$FILE-taskopt.txt

echo ""
echo "opt tasks o3"
./$FILE-opt-tasks-o3 2> dump-$FILE-taskopto3.txt


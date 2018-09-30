#!/bin/sh -x

DATASETSIZE='-DEXTRALARGE_DATASET'
#DATASETSIZE='-DLARGE_DATASET'
#DATASETSIZE='-DSTANDARD_DATASET'
#DATASETSIZE='-DSMALL_DATASET'
#DATASETSIZE='-DMINI_DATASET'

#DUMP=''
DUMP='-DPOLYBENCH_DUMP_ARRAYS'

FILE='correlation'

#DEBUG=''
#DEBUG='-debug'
DEBUG='-debug-only=polly-ast'

UTILITY='../../utilities'
POLY="$UTILITY/polybench.c"
FLAGS="-pthread -fopenmp -lm $POLY"
INCLUDES="-I. -I$UTILITY"




# prepare for the optimizations
clang $INCLUDES -pthread -fopenmp -DPOLYBENCH_TIME -DPOLYBENCH_USE_C99_PROTO $DATASETSIZE $DUMP -S -emit-llvm $FILE.c
opt -S -polly-canonicalize $FILE.ll > $FILE.tmp

# apply optimizations
opt -S -polly-codegen $FILE.tmp $DEBUG -pass-remarks-analysis=polly-scops -polly-scops > $FILE-nothing.ll 2> a.debug
opt -S -polly-codegen -polly-task $FILE.tmp $DEBUG -pass-remarks-analysis=polly-scops -polly-scops > $FILE-task.ll 2> b.debug
opt -S -polly-codegen -polly-parallel $FILE.tmp $DEBUG -pass-remarks-analysis=polly-scops -polly-scops > $FILE-parallel.ll 2> c.debug
opt -S -polly-codegen -polly-task -polly-parallel $FILE.tmp $DEBUG -pass-remarks-analysis=polly-scops -polly-scops > $FILE-both.ll 2> d.debug

# create the executables without o3
clang $FILE-nothing.ll -o $FILE-nothing $FLAGS -DPOLYBENCH_TIME $DATASETSIZE $DUMP
clang $FILE-task.ll -o $FILE-task $FLAGS -DPOLYBENCH_TIME $DATASETSIZE $DUMP
clang $FILE-parallel.ll -o $FILE-parallel $FLAGS -DPOLYBENCH_TIME $DATASETSIZE $DUMP
clang $FILE-both.ll -o $FILE-both $FLAGS -DPOLYBENCH_TIME $DATASETSIZE $DUMP

# create the executables with o3
clang -O3 $FILE-nothing.ll -o $FILE-nothing-o3 $FLAGS -DPOLYBENCH_TIME $DATASETSIZE $DUMP
clang -O3 $FILE-task.ll -o $FILE-task-o3 $FLAGS -DPOLYBENCH_TIME $DATASETSIZE $DUMP
clang -O3 $FILE-parallel.ll -o $FILE-parallel-o3 $FLAGS -DPOLYBENCH_TIME $DATASETSIZE $DUMP
clang -O3 $FILE-both.ll -o $FILE-both-o3 $FLAGS -DPOLYBENCH_TIME $DATASETSIZE $DUMP

# optimize ll files by applying o3 with opt
opt -O3 $FILE-nothing.ll > $FILE-nothingend.ll
opt -O3 $FILE-task.ll > $FILE-taskend.ll
opt -O3 $FILE-parallel.ll > $FILE-parallelend.ll
opt -O3 $FILE-both.ll > $FILE-bothend.ll

# build executables of the new optimized files without o3
clang $FILE-nothingend.ll -o $FILE-opt-nothing $FLAGS -DPOLYBENCH_TIME $DATASETSIZE $DUMP
clang $FILE-taskend.ll -o $FILE-opt-task $FLAGS -DPOLYBENCH_TIME $DATASETSIZE $DUMP
clang $FILE-parallelend.ll -o $FILE-opt-parallel $FLAGS -DPOLYBENCH_TIME $DATASETSIZE $DUMP
clang $FILE-bothend.ll -o $FILE-opt-both $FLAGS -DPOLYBENCH_TIME $DATASETSIZE $DUMP

# build executables of the new optimized files without o3
clang -O3 $FILE-nothingend.ll -o $FILE-opt-nothing-o3 $FLAGS -DPOLYBENCH_TIME $DATASETSIZE $DUMP
clang -O3 $FILE-taskend.ll -o $FILE-opt-task-o3 $FLAGS -DPOLYBENCH_TIME $DATASETSIZE $DUMP
clang -O3 $FILE-parallelend.ll -o $FILE-opt-parallel-o3 $FLAGS -DPOLYBENCH_TIME $DATASETSIZE $DUMP
clang -O3 $FILE-bothend.ll -o $FILE-opt-both-o3 $FLAGS -DPOLYBENCH_TIME $DATASETSIZE $DUMP



# create normal executable
clang -O3 -pthread -fopenmp -lm -o $FILE $FILE.c -DPOLYBENCH_TIME -DPOLYBENCH_USE_C99_PROTO $DATASETSIZE $DUMP $INCLUDES $POLY



# run everything
echo ""
echo "$FILE"
./$FILE 2> dump-$FILE.txt


echo ""
echo ""
echo "polly nothing unoptimized"
./$FILE-nothing 2> dump-$FILE-nothing.txt

echo ""
echo "polly nothing exe with o3"
./$FILE-nothing-o3 2> dump-$FILE-nothingo3.txt

echo ""
echo "polly opt nothing"
./$FILE-opt-nothing 2> dump-$FILE-nothingopt.txt

echo ""
echo "polly opt nothing exe with o3"
./$FILE-opt-nothing-o3 2> dump-$FILE-nothingopto3.txt


echo ""
echo ""
echo "polly task unoptimized"
./$FILE-task 2> dump-$FILE-task.txt

echo ""
echo "polly task exe with o3"
./$FILE-task-o3 2> dump-$FILE-tasko3.txt

echo ""
echo "polly opt task"
./$FILE-opt-task 2> dump-$FILE-taskopt.txt

echo ""
echo "polly opt task exe with o3"
./$FILE-opt-task-o3 2> dump-$FILE-taskopto3.txt


echo ""
echo ""
echo "polly parallel unoptimized"
./$FILE-parallel 2> dump-$FILE-parallel.txt

echo ""
echo "polly parallel exe with o3"
./$FILE-parallel-o3 2> dump-$FILE-parallelo3.txt

echo ""
echo "polly opt parallel"
./$FILE-opt-parallel 2> dump-$FILE-parallelopt.txt

echo ""
echo "polly opt parallel exe with o3"
./$FILE-opt-parallel-o3 2> dump-$FILE-parallelopto3.txt


echo ""
echo ""
echo "polly both unoptimized"
./$FILE-both 2> dump-$FILE-both.txt

echo ""
echo "polly both exe with o3"
./$FILE-both-o3 2> dump-$FILE-botho3.txt

echo ""
echo "polly opt both"
./$FILE-opt-both 2> dump-$FILE-bothopt.txt

echo ""
echo "polly opt both exe with o3"
./$FILE-opt-both-o3 2> dump-$FILE-bothopto3.txt


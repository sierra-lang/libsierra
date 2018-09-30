#!/bin/sh -x

FILE='deriche'

MIN=`./$FILE.exe 2> dump-$FILE.txt`
MINNOTHING=`./$FILE-nothing.exe 2> dump-$FILE-nothing.txt`
MINTASK=`./$FILE-task.exe 2> dump-$FILE-task.txt`
MINPARALLEL=`./$FILE-parallel.exe 2> dump-$FILE-parallel.txt`
MINBOTH=`./$FILE-both.exe 2> dump-$FILE-both.txt`


# run everything
for i in `seq 1 10`; do
    #run o3
    TMP=`./$FILE.exe 2> dump-$FILE.txt`
    if (( $(echo "$MIN > $TMP" | bc -l) )); then
        MIN=$TMP
    fi
    #run seq polly
    TMP=`./$FILE-nothing.exe 2> dump-$FILE-nothing.txt`
    if (( $(echo "$MINNOTHING > $TMP" | bc -l) )); then
        MINNOTHING=$TMP
    fi
    TMP=`./$FILE-task.exe 2> dump-$FILE-task.txt`
    if (( $(echo "$MINTASK > $TMP" | bc -l) )); then
        MINTASK=$TMP
    fi
    TMP=`./$FILE-parallel.exe 2> dump-$FILE-parallel.txt`
    if (( $(echo "$MINPARALLEL > $TMP" | bc -l) )); then
        MINPARALLEL=$TMP
    fi
    TMP=`./$FILE-both.exe 2> dump-$FILE-both.txt`
    if (( $(echo "$MINBOTH > $TMP" | bc -l) )); then
        MINBOTH=$TMP
    fi
done


echo "=========== 11 runs and picked out the minimum respectively ============="
echo ""
echo "o3"
echo "$MIN"
echo ""
echo "seq polly"
echo "$MINNOTHING"
echo ""
echo "task"
echo "$MINTASK"
echo ""
echo "parallel"
echo "$MINPARALLEL"
echo ""
echo "both"
echo "$MINBOTH"

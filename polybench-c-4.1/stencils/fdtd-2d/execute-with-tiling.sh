#!/bin/sh -x

FILE='fdtd-2d'

MIN=`./$FILE.exe 2> dump-$FILE.txt`
MINTILE=`./$FILE-onlytile.exe 2> dump-$FILE-onlytile.txt`
MINTILETASK=`./$FILE-tiletask.exe 2> dump-$FILE-tiletask.txt`


# run everything
for i in `seq 1 10`; do
    #run o3
    TMP=`./$FILE.exe 2> dump-$FILE.txt`
    if (( $(echo "$MIN > $TMP" | bc -l) )); then
        MIN=$TMP
    fi
    #run seq polly
    TMP=`./$FILE-onlytile.exe 2> dump-$FILE-onlytile.txt`
    if (( $(echo "$MINTILE > $TMP" | bc -l) )); then
        MINTILE=$TMP
    fi
    TMP=`./$FILE-tiletask.exe 2> dump-$FILE-tiletask.txt`
    if (( $(echo "$MINTILETASK > $TMP" | bc -l) )); then
        MINTILETASK=$TMP
    fi
done


echo "=========== 11 runs and picked out the minimum respectively ============="
echo ""
echo "o3"
echo "$MIN"
echo ""
echo "seq polly"
echo "$MINTILE"
echo ""
echo "task"
echo "$MINTILETASK"
echo ""

CC=clang
POLLY_FLAGS=-mllvm -polly -mllvm -polly-process-unprofitable -mllvm -polly-parallel-force
CFLAGS=-DPOLYBENCH_TIME -DPOLYBENCH_USE_C99_PROTO -Xclang -load -Xclang /home/wiam/Documents/bachelor/bachelor-git/build/lib/LLVMPolly.so ${POLLY_FLAGS}

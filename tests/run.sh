#!/bin/zsh


FILENAME="${1%.*}"
#LIBCLANG="-Xclang -load -Xclang $INSTALL_DIR/lib/libclang.so"
CLANG_LIBRVCODEGEN="-Xclang -load -Xclang $INSTALL_DIR/lib/LLVMRVCodeGen.so"
OPT_LIBRVCODEGEN="-load=LLVMRVCodeGen.so -rvcodegen"


echo "------> emit ll file for $FILENAME"
#$CXX -S -emit-llvm $LIBCLANG -fsierra -I.. $1 -o $FILENAME.ll
$CXX -S -emit-llvm -std=c++11 -fsierra -I.. $1 -o $FILENAME.ll


echo "------> opt ll file for $FILENAME with mem2reg"
$OPT -S $LIBRVCODEGEN ${FILENAME}.ll &> ${FILENAME}.opt.ll

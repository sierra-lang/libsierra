#!/usr/bin/zsh


FILENAME="${1%.*}"
OPT_LIBRVCODEGEN="-load=LLVMRVCodeGen.so" #" -rvcodegen"



echo "------> emit ll file for ${FILENAME}"
#$CXX -S -emit-llvm $LIBCLANG -fsierra -I.. $1 -o $FILENAME.ll
$CXX -S -emit-llvm -std=c++11 -fsierra -I.. $1 -o ${FILENAME}.ll

echo "------> opt ll file with mem2reg for ${FILENAME}"
$OPT -S -mem2reg ${FILENAME}.ll &> ${FILENAME}.opt.ll

echo "------> opt ll file with rv fo ${FILENAME}"
$OPT -O1 -S -load=${INSTALL_DIR}/lib/libRVCodeGen.so -rvcodegen ${FILENAME}.ll -o ${FILENAME}.rv.ll -debug-only=rvcodegen


echo "------> run everythin with clang directly"
$CXX -O1 -S -emit-llvm -std=c++11 -fsierra -Xclang -load -Xclang ${INSTALL_DIR}/lib/libRVCodeGen.so -mllvm -debug-only=rvcodegen -I.. $1 -o ${FILENAME}.rv.ll

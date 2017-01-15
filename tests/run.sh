#!/usr/bin/zsh


FILENAME="${1%.*}"
LIBCLANG="-Xclang -load -Xclang $INSTALL_DIR/lib/libclang.so"


echo "------> emit ll file for $FILENAME"
$CC -S -emit-llvm $LIBCLANG -fsierra -I.. $1 -o $FILENAME.ll

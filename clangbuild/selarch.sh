#!/usr/bin/env sh
chmod +x clangbuild/tools/clang-emit.sh
CLANG=clangbuild/tools/clang-emit.sh
export CLANG
bash clangbuild/$1/clang-wrap.sh
make CC=$CC

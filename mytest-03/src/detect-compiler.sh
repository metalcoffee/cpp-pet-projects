#!/bin/bash
set -euo pipefail

GCC_FLAGS="-std=c++17 -Wall -Wextra -Werror -o compiled-test -I../../"
for cmd in clang++-12 g++-10 clang++ g++; do
    if command -v "$cmd" >/dev/null 2>&1 && "$cmd" --version | grep "clang version 12" >/dev/null; then
        echo "$cmd $GCC_FLAGS"
        exit 0
    fi
done
for cmd in g++-10 g++; do
    if command -v "$cmd" >/dev/null 2>&1 && "$cmd" --version | grep "g++.* 10\." >/dev/null; then
        echo "$cmd $GCC_FLAGS"
        exit 0
    fi
done

CL_FLAGS="/std:c++17 /W4 /WX /EHsc /Fe:compiled-test /I../../ /nologo"
for cmd in cl; do
    if command -v "$cmd" >/dev/null 2>&1 && "$cmd" 2>&1 | grep "Microsoft (R) C/C++ Optimizing Compiler Version" >/dev/null; then
        echo "$cmd $CL_FLAGS"
        exit 0
    fi
done

echo "Unable to find suitable compiler" >&2
exit 1

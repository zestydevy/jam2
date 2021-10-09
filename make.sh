#!/bin/bash

export ROOT=/etc/n64
export PATH="/opt/crashsdk/bin:$PATH"
export N64_LIBGCCDIR="/opt/crashsdk/lib/gcc/mips64-elf/11.2.0"
export N64_NEWLIBDIR="/opt/crashsdk/mips64-elf/lib"
export N64_NEWLIBINCDIR="/opt/crashsdk/mips64-elf/include"
export ROOT=/etc/n64

rm -rf ./build
mkdir -p ./build/obj
make
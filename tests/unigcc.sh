#! /bin/sh
fullname=$(basename $1)
filename="${fullname%.*}"
../../bin/unicore32-linux-gcc-4.4.2 -static -nostdlib -O2 -o $filename $fullname
gcc -o "${filename}-X86" -DX86 $fullname
../../unicore32-linux/bin/objdump -d $filename > "${filename}.S"


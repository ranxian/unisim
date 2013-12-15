#! /bin/sh
fullname=$(basename $1)
filename=${fullname%.*}
make
./unigcc.sh $fullname 
./unisim $filename

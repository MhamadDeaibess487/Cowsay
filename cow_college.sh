#!/bin/bash

if [ $# -eq 0 ]; then
    echo "Usage: $0 <n>"
    exit 1
fi

n=$1

a=1
b=1

while [ $a -le $n ]; do
    cowsay "La vache dit : $a"
    sleep 1
    c=$((a + b))
    a=$b
    b=$c
done
cowsay -T "U" " La vache tire la langue"

#!/bin/bash

if [ $# != 1 ]; then
    echo "Usage: $0 <nombre>"
    exit 1
fi

for ((i = 1; i <= $1; i++)); do
    square=$((i * i))
    cowsay "La vache dit: Le carré de $i est $square"
    sleep 1
done

cowsay -T "U" " La vache tire la langue"

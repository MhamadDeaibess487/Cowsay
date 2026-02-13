#!/bin/bash

if [ $# -eq 0 ]; then
    echo "Usage: $0 <n>"
    exit 1
fi

n=$1

primes=( )
for ((num=2; num<=$n; num++)); do
    prime=1
    for ((i=2; i<$num; i++)); do
        if [ $((num % i)) -eq 0 ]; then
            prime=0
            break
        fi
    done
    if [ $prime -eq 1 ]; then
        primes+=( $num )
    fi
done

for prime in "${primes[@]}"; do
    cowsay la vach dit : $prime 
    sleep 1
done
cowsay -T "U" " La vache tire la langue"

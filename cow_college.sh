#!/bin/bash
set -e

if [[ $# == 1 && $1 == --help ]]; then
    printf 'Usage: %s <nombre>\nAffiche Fibonacci jusqu’à nombre.\nExemple: bash %s "%s"\n' "$0" "$0" "5"
    exit 0
fi
if [[ $# != 1 ]]; then
    echo "Usage: $0 <nombre> (voir --help)" >&2
    exit 1
fi
if [[ ! $1 =~ ^[0-9]{1,7}$ ]] || (( 10#$1 > 1000000 )); then
    echo "Erreur: nombre doit être un entier entre 0 et 1000000." >&2
    exit 1
fi
# Interpret leading zeroes in decimal, never as shell arithmetic or octal.
set -- "$((10#$1))"
command -v cowsay >/dev/null 2>&1 || { echo "Dépendance manquante: cowsay" >&2; exit 1; }


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

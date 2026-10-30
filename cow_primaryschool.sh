#!/bin/bash
set -e

if [[ $# == 1 && $1 == --help ]]; then
    printf 'Usage: %s <nombre>\nCompte de 1 à nombre.\nExemple: bash %s "%s"\n' "$0" "$0" "5"
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


for ((i = 1; i <= $1; i++)); do
    cowsay "La vache dit: $i"
    sleep 1
done

cowsay -T "U" " La vache tire la langue"

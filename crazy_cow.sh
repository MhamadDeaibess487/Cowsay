#!/bin/bash
set -e

if [[ $# == 1 && $1 == --help ]]; then
    printf 'Usage: %s <nombre>\nVache du côté obscur et conversion en binaire.\nExemple: bash %s "%s"\n' "$0" "$0" "5"
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
command -v bc >/dev/null 2>&1 || { echo "Dépendance manquante: bc" >&2; exit 1; }


number=$1

# Vache avec des chaussures
cowsay -f vader-koala "I'm now a dark side cow!"

# Conversion du nombre en binaire
binary=$(echo "obase=2; $number" | bc)

cowsay "Le Nombre binaire de $number est $binary"

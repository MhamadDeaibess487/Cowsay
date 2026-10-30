#!/bin/bash
set -e

if [[ $# == 1 && $1 == --help ]]; then
    printf 'Usage: %s <expression>\nCalcule une expression avec bc (scale=2).\nExemple: bash %s "%s"\n' "$0" "$0" "2+3"
    exit 0
fi
if [[ $# != 1 ]]; then
    echo "Usage: $0 <expression> (voir --help)" >&2
    exit 1
fi
if [[ -z $1 ]]; then
    echo "Erreur: expression vide." >&2
    exit 1
fi
command -v cowsay >/dev/null 2>&1 || { echo "Dépendance manquante: cowsay" >&2; exit 1; }
command -v bc >/dev/null 2>&1 || { echo "Dépendance manquante: bc" >&2; exit 1; }


if ! result=$(printf 'scale=2; %s\n' "$1" | bc 2>&1) ||
   [[ -z $result || $result == *[!0-9.$'\n'\\\ -]* ]]; then
    printf 'Expression invalide: %s\n' "$result" >&2
    exit 1
fi
cowsay "$1 = $result"

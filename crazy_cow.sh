#!/bin/bash

if [ $# -eq 0 ]; then
    echo "Usage: $0 <number>"
    exit 1
fi

number=$1

# Vache avec des chaussures
cowsay -f vader-koala "I'm now a dark side cow!"

# Conversion du nombre en binaire
binary=$(echo "obase=2; $number" | bc)

cowsay "Le Nombre binaire de $number est $binary"

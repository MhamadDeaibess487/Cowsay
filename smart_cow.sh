#!/bin/bash

if [ $# -eq 0 ]; then
    echo "Usage: $0 <expression>"
    exit 1
fi

result=$(echo "scale=2; $1" | bc)
cowsay "$1 = $result"

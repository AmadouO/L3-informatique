#!/bin/bash

if [ ! -d "notes" ]; then
    echo " Dossiers notes introuvable "
    exit 1
fi 

if [ ! -d "out" ]; then
    mkdir out
fi

num_etudiants=$(awk -F ',' '{print $1}' notes/* | sort -u)

for num_e in $num_etudiants; do
    ./page_etu.sh "$num_e"
done


echo " Toutes les pages on ete generer "
    
#!/bin/bash

if [ $# -ne 1 ]; then
    echo " Usage : $0 num_etu "
    exit 1
fi

num_etu=$1

if [ ! -d "notes" ]; then
    echo " Dossiers notes intourvable "
    exit 1
fi 

somme=0
nbre_notes=0

for fichier in notes/*; do
   for  note in $(awk -F ',' -v num_e="$num_etu" '$1 == num_e {print $4}' "$fichier"); do
        somme=$((somme + note))
        ((nbre_notes++))
    done
done

if [ $nbre_notes -eq 0 ]; then
    echo " aucune notes trouver pour l'etudiant num : $num_etu"
    exit 1
fi 

moyenne=$(awk -v som="$somme" -v nbr_n="$nbre_notes" 'BEGIN { print som / nbr_n }')

echo "la moyenne de numero etudiant $num_etu est : $moyenne "
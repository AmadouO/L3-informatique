#!/bin/bash

# Vérifier le nombre d'arguments
if [ $# -ne 2 ]; then
    echo "Usage: $0 <UE> <Groupe>"
    exit 1
fi

UE="$1"
GROUPE="$2"
FICHIER_CSV="notes/$UE"

# Vérifier si le fichier CSV existe
if [ ! -f "$FICHIER_CSV" ]; then
    echo "Erreur : fichier des notes introuvable pour l'UE $UE."
    exit 1
fi

# Extraire les notes des étudiants du groupe donné et calculer la moyenne
moyenne=$(awk -F',' -v grp="$GROUPE" '$3 == grp {sum += $4; count++} END {if (count > 0) print sum / count; else print "Groupe introuvable"}' "$FICHIER_CSV")

echo "$moyenne"

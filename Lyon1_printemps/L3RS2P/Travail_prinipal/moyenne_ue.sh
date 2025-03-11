#!/bin/bash

# Vérifier le nombre d'arguments
if [ $# -ne 1 ]; then
    echo "Usage: $0 <UE>"
    exit 1
fi

UE="$1"
FICHIER_CSV="notes/$UE"

# Vérifier si le fichier CSV existe
if [ ! -f "$FICHIER_CSV" ]; then
    echo "Erreur : fichier des notes introuvable pour l'UE $UE."
    exit 1
fi

# Calculer la moyenne des notes de tous les étudiants de l'UE
moyenne=$(awk -F',' '{sum += $4; count++} END {if (count > 0) print sum / count; else print "Aucune note disponible"}' "$FICHIER_CSV")

echo "$moyenne"

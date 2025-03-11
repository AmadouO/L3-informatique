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

# Lister tous les groupes uniques et générer une page HTML pour chacun
GROUPES=$(awk -F',' '{print $3}' "$FICHIER_CSV" | sort -u)

for GROUPE in $GROUPES; do
    ./page_groupe.sh "$UE" "$GROUPE"
done

echo "Pages de groupes générées pour l'UE $UE."

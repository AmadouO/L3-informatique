#!/bin/bash

# Vérifier si le dossier "out" existe, sinon le créer
mkdir -p out

# Lister toutes les UE (c'est-à-dire tous les fichiers CSV dans "out/")
for FICHIER in notes/*; do
    if [[ -f "$FICHIER" ]]; then
        UE=$(basename "$FICHIER")
        ./page_ue.sh "$UE"
    fi
done

echo "Toutes les pages UE ont été générées."

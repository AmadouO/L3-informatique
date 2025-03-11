#!/bin/bash

# Vérifier si un argument est fourni
if [ $# -ne 1 ]; then
    echo "Usage: $0 <archive_notes.tar.gz>"
    exit 1
fi

ARCHIVE="$1"

# Création des dossiers
mkdir -p notes out

# Extraction de l'archive dans le dossier "notes"
tar -xzf "$ARCHIVE" -C notes

# Vérifier si l'extraction a réussi
if [ $? -ne 0 ]; then
    echo "Erreur lors de l'extraction de l'archive."
    exit 1
fi

echo "Archive extraite dans le dossier notes."

# Génération des fichiers CSV pour toutes les UEs
./generer_toutes_ues.sh

# Génération des pages HTML pour toutes les UEs et leurs groupes
./page_toutes_ues.sh

# Génération de l'index
./generer_index.sh

echo "Génération du site terminée."

#!/bin/bash

# Vérifier si un argument est fourni
if [ $# -ne 1 ]; then
    echo "Usage: $0 code_UE"
    exit 1
fi

code_UE="$1"
dossier_site="site"
dossier_out="out"
fichier_csv="$dossier_out/$code_UE"

# Créer le dossier out s'il n'existe pas
mkdir -p "$dossier_out"

# Vider le fichier CSV s'il existe déjà
> "$fichier_csv"

# Parcourir les fichiers des étudiants
for fichier in "$dossier_site"/etu_p*.html; do
    # Vérifier si des fichiers existent (évite une erreur si aucun fichier ne correspond)
    [ -e "$fichier" ] || continue

    # Récupérer les infos de l'étudiant et les ajouter au CSV
    ./get_etu.sh "$code_UE" "$fichier" >> "$fichier_csv"
done

echo "Fichier généré : $fichier_csv"

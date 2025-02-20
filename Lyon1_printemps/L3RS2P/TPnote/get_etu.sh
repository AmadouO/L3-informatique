#!/bin/bash

# Vérifier si le bon nombre d'arguments est fourni
if [ $# -ne 2 ]; then
    echo "Usage: $0 code_UE fichier_html"
    exit 1
fi

code_UE="$1"
fichier_html="$2"

# Vérifier si le fichier existe
if [ ! -f "$fichier_html" ]; then
    echo "Fichier introuvable: $fichier_html"
    exit 1
fi

# Vérifier si le fichier correspond bien à un étudiant
if [[ ! "$fichier_html" =~ site/etu_p[0-9]+\.html$ ]]; then
    echo "Format de nom de fichier incorrect"
    exit 1
fi

# Récupérer les informations de l'étudiant
num_etu=$(./get_num_etu.sh "$fichier_html")
nom_etu=$(./get_nom.sh "$fichier_html")
groupe_etu=$(./get_groupe.sh "$code_UE" "$num_etu")
note_etu=$(./get_notes.sh "$fichier_html" | grep "^$code_UE " | cut -d ' ' -f2)

# Vérifier si toutes les informations ont été récupérées
if [ -z "$num_etu" ] || [ -z "$nom_etu" ] || [ -z "$groupe_etu" ] || [ -z "$note_etu" ]; then
    echo "Erreur: impossible de récupérer toutes les informations"
    exit 1
fi

# Affichage au format CSV
echo "$num_etu,$nom_etu,$groupe_etu,$note_etu"

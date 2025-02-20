#!/bin/bash

# Vérifier si un argument est fourni
if [ $# -ne 1 ]; then
    echo "Usage: $0 fichier_html"
    exit 1
fi

# Vérifier si le fichier existe
if [ ! -f "$1" ]; then
    echo "Fichier introuvable: $1"
    exit 1
fi

# Extraire et afficher les notes (Format: "nom_UE note")
sed -n 's|<tr><td>\([^<]*\)</td><td>\([^<]*\)</td></tr>|\1 \2|p' "$1"
#grep '<tr><td>' "$1" | cut -d '>' -f3 | cut -d '<' -f1 | paste - -  

# \([])
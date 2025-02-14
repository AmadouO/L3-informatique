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

# Extraire le nom de l'étudiant avec une expression régulière 
# -oP pour activer les options -o (afficher uniquement les correspondances) et -P (utiliser les expressions régulières PCRE)
nom=$(grep -oP '(?<=<h1>)[^<]+' "$1")
# (?<=<h1>) pour indiquer que le nom doit être précédé de <h1> et [^<]+ pour capturer tous les caractères jusqu'à la balise de fermeture <
# ?<= est un lookbehind positif qui permet de vérifier si le nom est précédé de <h1> sans inclure <h1> dans la correspondance 

# Vérifier si un nom a été trouvé
if [ -z "$nom" ]; then
    echo "Nom introuvable dans le fichier."
    exit 1
fi

echo "$nom"

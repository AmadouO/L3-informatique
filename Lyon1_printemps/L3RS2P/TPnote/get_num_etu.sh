#!/bin/bash

if [ $# -ne 1 ]; then
    echo " Usage : $0 nom fichier html "
    exit 1
fi 

filename=$(basename -- "$1") # basename pour extraire le nom du fichier sans le chemin
# -- pour éviter les problèmes avec les noms de fichiers commençant par un tiret
echo "$filename"

# vérifier si le nom de fichier est de la forme etu_p[0-9]{7}.html 
if [[ "$filename" =~ ^etu_p[0-9]{7}\.html$ ]]; then # =~ permet d'utiliser les expressions régulières
# ^ pour indiquer le début de la chaine, $ pour la fin de la chaine et \ pour échapper le point et [0-9]{7} pour 7 chiffres de 0 à 9

    num_etu="${filename:4:8}" # extraire les 8 chiffres après le 4ème caractère

    echo "$num_etu"
else
    echo " format de nom de fichier incorrect"
    exit 1
fi 
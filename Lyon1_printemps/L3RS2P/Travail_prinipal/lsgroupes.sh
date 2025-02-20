#!/bin/bash

####################################################################################################################################
# Question 2-) Écrire un script qui, pour une UE dont le code est donné en paramètre, affiche tous les groupes de cette UE 
####################################################################################################################################

# Vérifier si un argument est passé au script 
if [ $# -ne 1 ]; then
    echo "Usage : $0 code_UE"
    exit 1
fi

# Stocker le code de l'UE dans une variable
code_UE=$1

# Vérifier si le dossier notes existe 
if [ ! -d "notes" ]; then 
    echo "Erreur : le dossier 'notes' est introuvable."
    exit 1
fi

# Vérifier si le fichier correspondant à l'UE existe
if [ ! -f "notes/$code_UE" ]; then
    echo "Erreur : le fichier 'notes/$code_UE' est introuvable."
    exit 1
fi

# Extraire et afficher les groupes de l'UE
awk -F ',' '{print $3}' "notes/$code_UE" | sort | uniq 
#awk -F ',' '{print $3}' "notes/$code_UE" | sort | uniq 

# -F ',' : délimiteur de champ est la virgule et print $3 : afficher la 3ème colonne et sort : trier les groupes par ordre alphabétique et uniq : supprimer les doublons 

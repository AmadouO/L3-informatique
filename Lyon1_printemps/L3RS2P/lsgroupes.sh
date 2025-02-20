#!/bin/bash


####################################################################################################################################
# Question 2-) Ecrire un script qui, pour une UE dont le code est donné en paramètre, affiche tous les groupes de cette UE 
####################################################################################################################################

# on verifie si au moins un argument est passé au script 
if [ $# -ne 1 ]; then
    echo " Usage : $0 code_UE " 
    exit 1
fi

# on stocke le code de l'UE dans une variable
code_UE=$1

# on verifie si le dossier notes existe 
if [ ! -d "notes" ]; then 
    echo "erreur : le dossier notes est introuvable. "
    exit 1
fi

awk -F ',' 'BEGIN{ print $3}' "notes/$code_UE.csv" | sort | uniq # on affiche les groupes de l'UE
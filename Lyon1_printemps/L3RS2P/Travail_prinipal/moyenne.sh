#!/bin/bash

################################################################
# $# : indique le nombre d'arguments passés au script
# $0 : indique le nom du script
# $1 : indique le premier argument passé au script
# $2 : indique le deuxième argument passé au script
# $@ : indique tous les arguments passés au script
# $* : indique tous les arguments passés au script
# $? : indique le code de retour de la dernière commande
# -eq : indique l'égalité (équivalent à ==) 
# -ne : indique la différence (équivalent à !=)
# -lt : indique inférieur (équivalent à <)
# -le : indique inférieur ou égal (équivalent à <=)
# -gt : indique supérieur (équivalent à >)
# -ge : indique supérieur ou égal (équivalent à >=)
# -z : indique la chaine vide
# -n : indique la chaine non vide
# -d : indique si le dossier existe
# -f : indique si le fichier existe
# -r : indique si le fichier est lisible
# -w : indique si le fichier est modifiabl
# -x : indique si le fichier est exécutable
# -s : indique si le fichier est non vide
# grep -q : indique si la chaine est trouvée
# -a : indique le ET logique (équivalent à &&)
# -o : indique le OU logique (équivalent à ||)

# then : indique le début du bloc d'instructions d'une condition 
################################################################

####################################################################################################################################
###################### Exercice 1 ##################################################################################################
# Question 1-) Ecrire un script qui calcule la moyenne des nombres passés en argument
####################################################################################################################################

# on verifie si au moins un argument est passé au script 
if [ $# -eq 0 ]; then
    echo " Usage : $0 nombre1 nombre2 ... nombreN" # $0 : nom du script suivit des arguments passés au script 
    exit 1 # on quitte le script avec un code d'erreur 1 
fi

# on initialise la variable somme à 0 
somme=0
for nombre in $@; do
    somme=$((somme + nombre )) # on additionne les nombres passés en argument 
done 

# on calcule la moyenne 
moyenne=$(awk -v somme="$somme" -v nbr_arg="$#" 'BEGIN{ print somme / nbr_arg }') # on calcule la moyenne avec awk
# -v : permet de passer des variables à awk

# on affiche la moyenne 
echo "La moyenne est : $moyenne"

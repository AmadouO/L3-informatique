#!/bin/bash

###################################################################
#   for fichier in notes/*; do
#    while IFS=',' read -r num nom ue note; do
#       if [ "$num" == "$num_etu" ]; then
#             somme=$((somme + note))
#             ((nbre_notes++))
#             table_rows+="<tr><td>$(basenam "$fichier")</td><td>$note</td></tr>"
#         fi
#     done < "$fichier"
# done
#       
###################################################################

# on verifie si un seul argument est passé au script
if [ $# -ne 1 ]; then 
    echo " Usage : $0 num_etu "
    exit 1
fi 

num_etu=$1 # on stocke le numero etudiant dans la variable num_etu

# on verifie si le dossier notes existe
if [ ! -d "notes" ]; then
    echo " Dossier notes intourvable "
    exit 1
fi 

# on verifie si le dossier out existe 
if [ ! -d "out" ]; then
    mkdir out
fi 

# on recupere le nom de l'etudiant correspondant au numero etudiant
nom_etu=$(awk -F ',' -v num_e="$num_etu" '$1 == num_e {print $2; exit}' notes/*)

# on verifie si l'etudiant existe
if [ -z "$nom_etu" ]; then
    echo " l'etudiant introuvable avec le numero etudiant : $num_etu "
    exit 1
fi

# on initialise les variables somme et nbre_notes à 0 et table_rows à une chaine vide
somme=0
nbre_notes=0
table_rows=""


# on parcourt les fichiers du dossier notes 
for fichier in notes/*; do #pour chaque fichier dans le dossier notes 
   for  note in $(awk -F ',' -v num_e="$num_etu" '$1 == num_e {print $4}' "$fichier"); do #pour chaque note de l'etudiant 
        somme=$((somme + note)) # on ajoute la note à la somme
        ((nbre_notes++)) #on compte le nombre de notes
        table_rows+="<tr><td>$(basename "$fichier")</td><td>$note</td></tr>" # on ajoute une ligne dans le tableau

    done
done

# on verifie si l'etudiant a des notes
if [ "$nbre_notes" -eq 0 ]; then
    echo " aucune note trouver pour l'etudiant : $num_etu" 
    exit 1
fi 

# on calcule la moyenne avec awk
moyenne=$(awk -v som="$somme" -v nbr_n="$nbre_notes" 'BEGIN{print som / nbr_n}')

# on genere la page html
html_file="out/etu_$num_etu.html"

# on cree le fichier html 
cat <<EOF > "$html_file"
<html>
<head><title>$nom_etu ($num_etu)</title></head>
<body>
<h1>$nom_etu ($num_etu)</h1>
<p>Moyenne: $moyenne</p>
<table>
$table_rows
</table>
</body>
</html>
EOF

echo "Page générée : $html_file"
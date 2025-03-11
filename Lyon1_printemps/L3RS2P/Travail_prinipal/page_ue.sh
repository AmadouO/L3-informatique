#!/bin/bash

# Vérifier le nombre d'arguments
if [ $# -ne 1 ]; then
    echo "Usage: $0 <UE>"
    exit 1
fi

UE="$1"
FICHIER_CSV="notes/$UE"
FICHIER_HTML="out/ue_${UE}.html"

# Vérifier si le fichier CSV existe
if [ ! -f "$FICHIER_CSV" ]; then
    echo "Erreur : fichier des notes introuvable pour l'UE $UE."
    exit 1
fi

# Calculer la moyenne de l'UE
MOYENNE=$(./moyenne_ue.sh "$UE")

# Générer les pages des groupes
./groupes_ue.sh "$UE"

# Lister tous les groupes de l'UE
GROUPES=$(awk -F',' '{print $3}' "$FICHIER_CSV" | sort -u)

# Générer le fichier HTML de l'UE
{
    echo "<html><head><title>UE $UE</title></head><body>"
    echo "<h1>UE: $UE</h1>"
    echo "<p>Moyenne des étudiants : $MOYENNE</p>"
    echo "<h2>Groupes :</h2><ul>"

    for GROUPE in $GROUPES; do
        echo "<li><a href=\"ue_${UE}_${GROUPE}.html\">Groupe $GROUPE</a></li>"
    done

    echo "</ul></body></html>"
} > "$FICHIER_HTML"

echo "Fichier HTML généré : $FICHIER_HTML"

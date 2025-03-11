#!/bin/bash

# Vérifier le nombre d'arguments
if [ $# -ne 2 ]; then
    echo "Usage: $0 <UE> <Groupe>"
    exit 1
fi

UE="$1"
GROUPE="$2"
FICHIER_CSV="notes/$UE"
FICHIER_HTML="out/ue_${UE}_${GROUPE}.html"

# Vérifier si le fichier CSV existe
if [ ! -f "$FICHIER_CSV" ]; then
    echo "Erreur : fichier des notes introuvable pour l'UE $UE."
    exit 1
fi

# Calculer la moyenne du groupe
MOYENNE=$(./moyenne_groupe.sh "$UE" "$GROUPE")

# Générer le fichier HTML
{
    echo "<html><head><title>Groupe $GROUPE - $UE</title></head><body>"
    echo "<h1>UE: $UE - Groupe: $GROUPE</h1>"
    echo "<p>Moyenne du groupe: $MOYENNE</p>"
    echo "<table border='1'><tr><th>Numéro Étudiant</th><th>Nom</th><th>Note</th></tr>"

    awk -F',' -v grp="$GROUPE" '{if ($3 == grp) print "<tr><td><a href=\"etu_" $1 ".html\">" $1 "</a></td><td>" $2 "</td><td>" $4 "</td></tr>"}' "$FICHIER_CSV"

    echo "</table></body></html>"
} > "$FICHIER_HTML"

echo "Fichier HTML généré : $FICHIER_HTML"

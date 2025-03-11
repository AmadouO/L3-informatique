#!/bin/bash

# Vérifier si le dossier "out" existe
if [ ! -d "out" ]; then
    echo "Erreur : Le dossier 'out' n'existe pas."
    exit 1
fi

FICHIER_INDEX="out/index.html"

# Générer la page index.html
{
    echo "<html><head><title>Index du site</title></head><body>"
    echo "<h1>Index des UEs</h1>"
    echo "<ul>"

    # Lister toutes les pages d'UE générées
    for FICHIER in out/ue_*.html; do
        if [[ -f "$FICHIER" && ! "$FICHIER" =~ _[A-Z]\.html$ ]]; then
            UE=$(basename "$FICHIER" .html)
            echo "<li><a href=\"$UE.html\">$UE</a></li>"
        fi
    done

    echo "</ul></body></html>"
} > "$FICHIER_INDEX"

echo "Fichier index généré : $FICHIER_INDEX"

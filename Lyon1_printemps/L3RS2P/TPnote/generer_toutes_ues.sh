#!/bin/bash

# Vérifier que le dossier site existe
dossier_site="site"
if [ ! -d "$dossier_site" ]; then
    echo "Erreur : le dossier '$dossier_site' est introuvable."
    exit 1
fi

# Trouver tous les fichiers HTML des UE et en extraire les codes d’UE
ues=$(ls "$dossier_site"/ue_*.html 2>/dev/null | sed -E 's|.*/ue_([^_]+).*|\1|' | sort -u)

# Vérifier si des UE ont été trouvées
if [ -z "$ues" ]; then
    echo "Aucune UE trouvée dans '$dossier_site'."
    exit 1
fi

# Générer les fichiers CSV pour toutes les UE
for ue in $ues; do
    ./generer_ue.sh "$ue"
done

echo "Génération terminée. Fichiers disponibles dans 'out/'."

#!/bin/bash

# Vérifier si le bon nombre d'arguments est fourni
if [ $# -ne 2 ]; then
    echo "Usage: $0 code_UE num_etu"
    exit 1
fi

code_UE="$1"
num_etu="$2"

# Parcourir les fichiers de groupe correspondants à l'UE
for fichier in site/ue_"$code_UE"_*.html; do
    # Vérifier si le fichier existe (évite les erreurs si aucun fichier ne correspond)
    [ -f "$fichier" ] || continue

    # Vérifier si le numéro d'étudiant est dans le fichier
    if grep -q "$num_etu" "$fichier"; then
        # Extraire le groupe depuis le nom du fichier
        groupe=$(echo "$fichier" | sed -E "s|site/ue_${code_UE}_([A-Z]).html|\1|")
        echo "$groupe"
        exit 0
    fi
done

# Si aucun fichier ne contient l'étudiant, afficher une erreur
echo "Étudiant non trouvé dans l'UE $code_UE"
exit 1

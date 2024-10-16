#include "skip_liste.h"
#include <cstdlib>  // pour std::rand() et std::srand()
#include <ctime>    // pour std::time()

// Constructeur pour initialiser la Skip-List
Skip_List::Skip_List() {
    taille = 0;
    niveau_etabli = false;

    // Initialiser la cellule sentinelle (Cellule bidon) avec HMAX niveaux
    ad = new Cellule;
    ad->niveau = HMAX;

    for (int i = 0; i < HMAX; i++) {
        ad->psuivant[i] = nullptr;
    }

    // Initialiser la graine pour la génération aléatoire
    std::srand(std::time(0));
}

// Fonction d'affichage de la liste à tous les niveaux
void Skip_List::affichage() const {
    for (int i = 0; i < HMAX; i++) {
        std::cout << "Niveau " << i << " : ";
        Cellule *courant = ad->psuivant[i];
        while (courant != nullptr) {
            std::cout << courant->info << " -> ";
            courant = courant->psuivant[i];
        }
        std::cout << "nullptr" << std::endl;
    }
}

// Fonction pour établir les niveaux de chaînage
void Skip_List::etablissement_des_niveau() {
    if (taille < 2) {
        return;  // Si la liste a moins de deux éléments, on ne fait rien
    }

    Cellule *p_courant = ad->psuivant[0];  // On commence après la cellule bidon
    int compteur = 0;

    while (p_courant != nullptr) {
        int niveau_random = std::rand() % HMAX;  // On choisit aléatoirement le nombre de niveaux
        p_courant->niveau = niveau_random;

        for (int i = 1; i < niveau_random; i++) {
            if (p_courant->psuivant[i] != nullptr) {
                p_courant->psuivant[i] = p_courant->psuivant[0];  // Ajuster les niveaux
            }
        }
        p_courant = p_courant->psuivant[0];
        compteur++;
    }
    niveau_etabli = true;
}

// Fonction pour insérer un élément
void Skip_List::insere(const Elem &e) {
    Cellule *precedents[HMAX];  // Tableau pour enregistrer les précédents à chaque niveau
    Cellule *courant = ad;

    // Parcourir chaque niveau pour trouver l'endroit où insérer l'élément
    for (int i = HMAX - 1; i >= 0; i--) {
        while (courant->psuivant[i] != nullptr && courant->psuivant[i]->info < e) {
            courant = courant->psuivant[i];
        }
        precedents[i] = courant;
    }

    // Insérer au niveau de base (niveau 0)
    int niveau_insertion = std::rand() % HMAX;  // Niveau aléatoire pour l'insertion
    Cellule *nouvelle_cellule = new Cellule;
    nouvelle_cellule->info = e;
    nouvelle_cellule->niveau = niveau_insertion;

    for (int i = 0; i <= niveau_insertion; i++) {
        nouvelle_cellule->psuivant[i] = precedents[i]->psuivant[i];
        precedents[i]->psuivant[i] = nouvelle_cellule;
    }

    taille++;
}

// Fonction de recherche d'un élément
Cellule* Skip_List::rechercherElem(const Elem &e) {
    Cellule *courant = ad;

    // On parcourt les niveaux à partir du plus haut
    for (int i = HMAX - 1; i >= 0; i--) {
        while (courant->psuivant[i] != nullptr && courant->psuivant[i]->info < e) {
            courant = courant->psuivant[i];
        }
    }
    courant = courant->psuivant[0];  // Aller au niveau 0

    if (courant != nullptr && courant->info == e) {
        return courant;
    }
    return nullptr;
}

// Fonction pour supprimer un élément
void Skip_List::suppressionElem(const Elem &e) {
    Cellule *precedents[HMAX];
    Cellule *courant = ad;

    // Parcourir les niveaux pour trouver les précédents de l'élément à supprimer
    for (int i = HMAX - 1; i >= 0; i--) {
        while (courant->psuivant[i] != nullptr && courant->psuivant[i]->info < e) {
            courant = courant->psuivant[i];
        }
        precedents[i] = courant;
    }

    courant = courant->psuivant[0];  // Passer au niveau 0

    // Si l'élément est trouvé, on le supprime à chaque niveau où il apparaît
    if (courant != nullptr && courant->info == e) {
        for (int i = 0; i < HMAX; i++) {
            if (precedents[i]->psuivant[i] == courant) {
                precedents[i]->psuivant[i] = courant->psuivant[i];
            }
        }
        delete courant;
        taille--;
    }
}

// Fonction pour afficher uniquement le second niveau
void Skip_List::affichageNiveau() {
    if (!niveau_etabli) {
        std::cout << "Le second niveau de chaînage n'est pas établi." << std::endl;
        return;
    }

    std::cout << "Niveau 2 : ";
    Cellule *courant = ad->psuivant[1];  // On commence au niveau 1 (le second niveau)

    while (courant != nullptr) {
        std::cout << courant->info << " -> ";
        courant = courant->psuivant[1];
    }
    std::cout << "nullptr" << std::endl;
}

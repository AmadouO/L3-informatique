#include <iostream>
#include "arbre.h"

int main() {
    arbre monArbre;

    // Insertion d'éléments dans l'arbre
    monArbre.insereApartirDunNoeud(10, monArbre.racine);
    monArbre.insereApartirDunNoeud(5, monArbre.racine);
    monArbre.insereApartirDunNoeud(15, monArbre.racine);
    monArbre.insereApartirDunNoeud(3, monArbre.racine);
    monArbre.insereApartirDunNoeud(7, monArbre.racine);
    monArbre.insereApartirDunNoeud(13, monArbre.racine);
    monArbre.insereApartirDunNoeud(18, monArbre.racine);

    // Création des coutures
    monArbre.creat_couture(*monArbre.racine, nullptr);

    // Affichage infixé avec coutures
    std::cout << "Affichage infixé avec coutures :\n";
    monArbre.aff();

    // Affichage de l'arbre avec niveaux d'indentation
    std::cout << "\nAffichage détaillé de l'arbre :\n";
    monArbre.affichageApartitirDunNoeud(monArbre.racine, 0);

    return 0;
}

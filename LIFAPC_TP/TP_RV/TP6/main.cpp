#include <iostream>
#include "arbre.h"

int main() {
    // Création d'un arbre binaire de recherche
    arbre abr;

    // Insertion d'éléments dans l'arbre
    abr.insereElement(10);
    abr.insereElement(5);
    abr.insereElement(15);
    abr.insereElement(2);
    abr.insereElement(7);
    abr.insereElement(12);
    abr.insereElement(20);

    int rech = 7;
    if (abr.rechercheElement(rech)) {
        std::cout << "L'element " << rech << " a ete trouve dans l'arbre.\n";
    } else {
        std::cout << "L'element " << rech << " n'est pas dans l'arbre.\n";
    }

    std::cout << "Affichage infixe : ";
    abr.affichageInfixer();

    std::cout<< std::endl;


    std::cout << "\nAffichage préfixe : ";
    abr.affichagePrefixer();

    std::cout << "\nAffichage postfixe : ";
    abr.affichagePostfixer();
    std::cout<< std::endl;

    return 0;
}

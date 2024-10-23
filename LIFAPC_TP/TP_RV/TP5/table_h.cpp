#include <iostream>
#include "table_h.h"

table_h::table_h(int taille, int (*ptr_ph) (int cle, int capacite)){
    this->taille_table = taille;
    this->tab_etat = new Etat[taille];
    this->tab_cle = new int[taille];
    this->tab_info =  new int[taille];
    this->nbr_elment = 0;
    this->ph= ptr_ph;
    for (int i = 0; i < this->taille_table; i++){
        this->tab_etat[i] = libre;
    }
}

/*int table_h::hacher(int a){
    return a % this->taille_table;
}*/


void table_h::insere(int elem){
    if (nbr_elment >= taille_table){
        std::cout<<" table plein impossible d'inserer ";
        return;
    }
    int res = ph(elem, taille_table); //hacher(elem);

    while (tab_etat[res] == occupe && tab_cle[res] != elem) {
        res = (res + 1) % taille_table;  
        
    }

    // Si la cle existe deja, mise à jour de l'info associee
    if (tab_etat[res] == occupe && tab_cle[res] == elem) {
        tab_info[res] = elem;  // Mise à jour de l'information (ici, elle est identique à l'élément)
        return;
    }
    
    // Insertion de l'element dans la table
    tab_cle[res] = elem;
    tab_info[res] = elem; 
    tab_etat[res] = occupe;  // Marquer la case comme occupee
    nbr_elment++;

    std::cout << "elment " << elem << " insere avec succes à l'indice " << res << "." << std::endl;

}
void table_h::rechercher(int elem) {
    //int res = hacher(elem);  // Calculer l'indice avec la fonction de hachage
    int res = ph(elem, taille_table); //hacher(elem);
   
    int essais = 0;          // Pour compter les essais de rehachage

    // Rehachage pour rechercher l'élément
    while (tab_etat[res] != libre && essais < taille_table) {
        // Si l'élément est trouvé
        if (tab_etat[res] == occupe && tab_cle[res] == elem) {
            std::cout << "Élément " << elem << " trouvé à l'indice " << res << "." << std::endl;
            return;
        }
        essais++;
        res = (res + 1) % taille_table;  // Rehachage
    }

    // Si l'élément n'est pas trouvé après avoir parcouru la table
    std::cout << "Élément " << elem << " non trouvé dans la table." << std::endl;
}

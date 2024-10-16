#include <iostream>
#include "skip_liste.h"

Skip_List::Skip_List(){
    Cellule *bidon = new Cellule;
    for(int i = 0; i < HMAX; i++){
        bidon->psuivant[i] = nullptr;//initialiser les pointeur de la cellule bidon a nulptr pour chaque niveau
    }
    this->ad = bidon;//l'adresse de la tete liste pointe vers la cellule bidon
    bidon->niveau = HMAX; // la cellule bidon est de niveau maximal 
    taille = 0;
    niveau_etabli = false;

}

void Skip_List::affichage()const{
    for(int i = 0; i < HMAX; i++){
        std::cout<< "Niveau : " <<  i << std::endl;
        Cellule *p_courant = this->ad->psuivant[i];
        while(p_courant != nullptr){
            std::cout<< p_courant->info << " ==> " ;
            p_courant = p_courant->psuivant[i];
        }
        std::cout<< "nulptr" <<std::endl;
    }
}

void Skip_List::etablissement_des_niveau(){
    if(taille < 2 ){ //si la liste a moins de deux element on sors de la fonction
        return; 
    }

    Cellule *p_courant = this->ad->psuivant[0];// on commence apres la cellule bidon
    Cellule *p_niveau_suivant[HMAX];//pointeur pour chaque niveau 


    for(int i = 0; i < HMAX; i++){
        p_niveau_suivant[i] = nullptr; //initialiser les pointeur des niveau suivant a nulptr pour chaque niveau 
    }
    //int compteur = 0;
    //parcourir la liste de bas en haut 
    while (p_courant != nullptr)
    {
        int nbre_alea = std::rand() % HMAX; // on choisi aleatoirement le nombre de niveau de la cellule 
        p_courant->niveau = nbre_alea; //assigner ce niveau a la cellule 

        //pour chaque niveau etable on fait pointer vers la cellule suivant 
        for(int i = 0; i < nbre_alea; i++){
            if( p_niveau_suivant[i] != nullptr){
                p_niveau_suivant[i]->psuivant[i] = p_courant; //le precedent cellule niveau i pointe sur p_courant
            }
            p_niveau_suivant[i] = p_courant; //puis on met a jour le tableau de niveau suivant pour le prochain tour
        }
        p_courant = p_courant->psuivant[0];// passer a la cellule suivant au niveau de base 
    }
    for(int i = 0; i < HMAX;)
    niveau_etabli = true;
    
}
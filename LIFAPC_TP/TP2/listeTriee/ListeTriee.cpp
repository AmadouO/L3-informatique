#include <iostream>
#include "ListeTriee.h"

Liste::Liste(){
    Cellule *bidon = new Cellule;
        taille = 0;
        this->ad = bidon;
    }

void Liste::affichage() const{
    if (ad == nullptr || ad->psuivant == nullptr){
        std::cout<<"votre liste est vide "<< std::endl;
        }else{
            Cellule *pc = ad->psuivant;
            while (pc != nullptr){
                std::cout<< pc->info<< std::endl;
                pc = pc->psuivant; 
            }
        }
} 


void Liste::insere(const Elem & e){
    Cellule *nouvel_c  = new Cellule;
    nouvel_c->info = e;
    nouvel_c->psuivant = nullptr;


    if (ad == nullptr || ad->psuivant == nullptr || ad->psuivant->info >= e) {
        nouvel_c->psuivant = ad->psuivant;  // Insertion en tête (ou après la sentinelle)
        ad->psuivant = nouvel_c;
    } else {
        Cellule *p_tmp = this->ad ;
        while (p_tmp->psuivant != nullptr && p_tmp->psuivant->info < e){
            p_tmp = p_tmp->psuivant;
        }
            nouvel_c->psuivant = p_tmp->psuivant;
            p_tmp->psuivant = nouvel_c;
    }
}


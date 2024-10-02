#include <iostream>
#include "liste.h"


class Liste; // declaration



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

/*
void Liste::affichage() const{
        if (ad == nullptr){
            std::cout<<"votre liste est vide "<< std::endl;
        }else{
            Cellule *pc = ad;
            while (pc != nullptr){
                std::cout<< pc->info<< std::endl;
                pc = pc->psuivant; 
            }
        }
    } 

void Liste::ajoutEnTete(const Elem & e){
        Cellule *pc = new Cellule();
        pc->info = e;
        pc->psuivant = this->ad;
        this->ad = pc;
        taille++;
    }   
*/
 void Liste::ajoutEnTete(const Elem & e){
        Cellule *tmp = new Cellule;
        Cellule *pc = new Cellule;
        pc->info = e;
       // pc->psuivant = this->ad;
        tmp = this->ad->psuivant;
        this->ad->psuivant = pc;
        pc = tmp;
        taille++;
 }
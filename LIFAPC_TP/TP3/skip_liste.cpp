#include <iostream>
#include "skip_liste.h"

skip_liste::skip_liste()
{
    Cellule *bidon = new Cellule;
    taille = 0; 
    b = false;
    this->ad = bidon;

}
void skip_liste::affichage() const{
    if (ad == nullptr || ad->psuivant[0] == nullptr){
        std::cout<<"votre liste est vide "<< std::endl;
        }else{
            Cellule *pc = ad->psuivant[0];
            while (pc != nullptr){
                std::cout<< pc->info<< std::endl;
                pc = pc->psuivant[0]; 
            }
        }
} 

void skip_liste::insere(const Elem & e){    
    Cellule *p_travail = this->ad;

        while ((p_travail->psuivant[0] != nullptr) && p_travail->psuivant[0]->info < e)
        {
            p_travail = p_travail->psuivant[0];
        } 
    

    Cellule *nouveau_c = new Cellule;
    nouveau_c->info = e;

    Cellule *tmp ;
    tmp = p_travail->psuivant[0];
    p_travail->psuivant[0] = nouveau_c;
    nouveau_c->psuivant[0] = tmp;

}

void skip_liste::etablissement_des_niveau(){
    Cellule *p_travail;
    p_travail = this->ad;

    for (int i = 0; i < HMAX; i++)
    {
        Cellule *p_balad;
        p_balad = this->ad->psuivant[i];
        while (p_balad != nullptr)
        {
            int n = rand()%2;
            if( n == 0 ){
                p_travail->psuivant[1 + i] = p_balad;
                p_balad = p_balad->psuivant[i];
                p_travail = p_balad;
            }else{
                p_balad = p_balad->psuivant[i];
            }
        }
        
    }
    

    
}






































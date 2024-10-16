#include <iostream>

 #include "liste.h"

 Liste::Liste(){
    Cellule *cel_bidon = new Cellule;
    cel_bidon->psuivant = nullptr;
    this->ad = cel_bidon;
    taille = 0;
 }

 bool Liste::testVide() const{
   return taille == 0;
 }

 Elem Liste::premierElement() const{
    return this->ad->info;
 }

Cellule * Liste::premiereCellule() const{
    return this->ad;
}
Cellule * Liste::celluleSuivante(const Cellule *pc) const{
    return pc->psuivant;
}

Elem Liste::elementCellule(const Cellule * pc) const{
    return pc->info;
}

void Liste::vide(){
    if(testVide()){
        suppressionEnTete();
    }
}


 void Liste::affichage() const{
    //pour commence apres la cellule bidon (sentinelle)
    Cellule *p_courant = this->ad->psuivant;

    //verifier que la liste n'est pas vide (c a d aucune cellule apres la cellule bidon)
    if (p_courant == nullptr)
    {
        std::cout<<"votre liste est vide "<< std::endl;
    }else{
        //parcourir la liste
        while ( p_courant != nullptr)
        {
            std::cout<< p_courant->info << " ==> " ;
            p_courant = p_courant->psuivant;
        }
        std::cout<< std::endl;
        
    }
 }

void Liste::ajoutEnTete(const Elem & e){
    Cellule *p_courant = new Cellule;
    p_courant->info = e;
    p_courant->psuivant = this->ad->psuivant; // inserer apres la cellule bidon 
    this->ad->psuivant = p_courant;                 // p_courant devient la premiere cellule 
    taille++;

}

void Liste::suppressionEnTete(){
    Cellule *p_courant = this->ad; //on memorise la premiere cellule 
    ad = ad->psuivant;               //la deuxieme cellule devient la premiere
    delete p_courant;
    taille--;
}

void Liste::ajoutEnQueue(const Elem & e){
    Cellule *new_cellule = new Cellule; //nouvelle cellule
    new_cellule->info = e;               //nouevelle cellule prend l'element a ajouter 
    new_cellule->psuivant = nullptr;        //la nouvelle cellule sera en queu , donc sont suivant sera nullptr


        //on parcoure la liste jusqu'a la fin
        Cellule *p_courant = this->ad;
        while (p_courant->psuivant != nullptr){
            p_courant = p_courant->psuivant; //on conitnue a avancer 
        }
        p_courant->psuivant = new_cellule; // on ajoute la nouvelle cellule a la fin
        taille++;
}

void Liste::insereElementApresCellule(const Elem & e,Cellule *pc){

    if(pc == nullptr){
        return; // si la cellule est vide on peut pas l'inserer
    }

    Cellule *new_cellule = new Cellule;
    new_cellule->info = e;

    //insertion de la nouvelle cellule apres une cellule pc
    new_cellule->psuivant = pc->psuivant;
    pc->psuivant = new_cellule;

    taille++;
     
}

Cellule * Liste::rechercheElement(const Elem & e) const{
    
        Cellule *p_courant = this->ad->psuivant; // on ignore la cellule bidon

          //on parcoure la liste 
        while ( p_courant != nullptr )
        {
            if(p_courant->info == e ){ //si l'element courant est egale a l'element rechercher 
                return p_courant;      // on retourne l'element en question
            }
            p_courant = p_courant->psuivant; //on conitnue a avancer 

        }
        return nullptr;
    }




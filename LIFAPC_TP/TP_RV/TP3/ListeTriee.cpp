#include <iostream>

#include "ListeTriee.h"

ListeTriee::ListeTriee(){
    Cellule *cel_bidon = new Cellule;
    this->ad = cel_bidon;
    cel_bidon->psuivant = nullptr;
    taille = 0;
    niveau2_etabli = false;
}

 void ListeTriee::affichage() const{
    //pour commence apres la cellule bidon (sentinelle)
    Cellule *p_courant = this->ad->psuivant;

    //verifier que la liste n'est pas vide (c a d aucune cellule apres la cellule bidon)
    if (p_courant == nullptr){
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


void ListeTriee::insere(const Elem & e){
    Cellule *cell_a_inserer = new Cellule;
    cell_a_inserer->info = e;

    Cellule *p_courant = this->ad; //on commence le parcour depuis la cellule bidon
    //on parcour pour trouver l'emplacement ou inserer ( tout en respectant l'ordre croissant )
    while (p_courant->psuivant != nullptr  && p_courant->psuivant->info < e )
    {
        p_courant = p_courant->psuivant;
    }
    //on insere la nouvelle cellule 
    cell_a_inserer->psuivant = p_courant->psuivant;
    p_courant->psuivant = cell_a_inserer;

    
}
Cellule * ListeTriee::rechercherElem(const Elem & e){
    Cellule *p_courant = this->ad->psuivant; // on commence le parcour apres la cellule bidon
    // on verifie que la cellule courante existe et que l'element courant est inférieur a l'element a rechercher
    while (p_courant != nullptr && p_courant->info < e )
    {
        
        p_courant = p_courant->psuivant; //on continue a avancer 
    }
    // on verifie que la cellule courante existe et que l'element courant est identique a l'element rechercher
    if(p_courant != nullptr && p_courant->info == e){
            return p_courant; // on returne la cellule courant 
        }
    return nullptr;// sinon on retrune nullptr
}

void ListeTriee::suppressionElem(const Elem & e){
    Cellule *p_courant = this->ad->psuivant;//on stock l'element suivant dans la cellule courant 
    Cellule *p_precedent = this->ad;//on stocke l'element precedent 
    // on verifie que la cellule courante existe et que l'element courant est inférieur a l'elem a supprimer
    while (p_courant != nullptr && p_courant->info < e )
    {
        p_precedent = p_courant; // On affecte la cellule precedente pour qu'elle pointe sur la cellule courante
        p_courant = p_courant->psuivant; //on continue a avancer 
    }
    // on verifie que la cellule courante existe et que l'element courant est identique a l'element a supprimer
    if(p_courant != nullptr && p_courant->info == e){
            //on saute l'element a supprimer (l'element courant ) pour pointe sur la cellule qui est apres l'elment courant 
            p_precedent->psuivant = p_courant->psuivant;
            delete p_courant; // on supprime la cellule courant 
            taille--;
        }

}


void ListeTriee::etablissementSecondNiveau(){
    //on verifie si la liste a moins de deux element donc pas de second niveau 
    if(taille < 2){
        return; //on sort de la fonction
    }

    Cellule *p_courant = this->ad->psuivant;// on commence apres la cellule bidon
    Cellule *p_second_N_chainage ;//pointeur pour le second niveau de chainage 

    if(p_courant != nullptr){ //on verifie si la liste n'est pas vide
        p_second_N_chainage = p_courant->psuivant; //on initialise le pointeur de second niveau de chainage en pointant sur la cellule suivant
    }else{ //si la liste est vide 
        p_second_N_chainage = nullptr; // on initialise le pointeur de second niveau de chainage a nullptr
    }

    int compteur = 0; //initialisation d'un compteur pour gerer l'activation du second niveau de chainage une cellule sur deux

    while (p_courant != nullptr) // on parcour la liste jusqu'a la fin
    {
        if(compteur % 2 == 0){//si le compteur est paire on etablie le second niveau de chainage 
            p_courant->psuivant2 = p_second_N_chainage;
        }else{//si le compteur est impaire on ne lie pas au second niveau
            p_courant->psuivant2 = nullptr;
        }

        p_courant = p_courant->psuivant;// on avance a la cellule suivant dans le premier niveau de chainage 

        //on verifie si le pointeur de la cellule du second niveau de chainage et la cellule d'apres ne son pas null (!= nulptr)
        if(p_second_N_chainage != nullptr && p_second_N_chainage->psuivant != nullptr){
            p_second_N_chainage = p_second_N_chainage->psuivant->psuivant; // on avance de deux cellule
        }else{//s'il sont null ( == nulptr)
            p_second_N_chainage = nullptr;//on pointe sur nulptr
        }
        compteur++;//incrementation du compteur a chaque iteration pour alterner entre cellule paire et impaire
    }
    niveau2_etabli = true;//true pour dire que le second niveau de chainage est bien etabli
    
}

void ListeTriee::affichageNiveau2() {
    if (!niveau2_etabli) {
        std::cout << "Le second niveau de chaînage n'est pas établi." << std::endl;
        return;
    }

    Cellule *p_courant = ad->psuivant2;  // on Commence au second niveau
    while (p_courant != nullptr) {
        std::cout << p_courant->info << " ==> ";
        p_courant = p_courant->psuivant2;  // On avance dans le second niveau
    }
    std::cout << std::endl;
}


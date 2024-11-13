#include <iostream>
#include "AVL.h"

node::node(const Elem& e){
    element = e;
    f_gauche = nullptr;
    f_droit = nullptr;


}



AVL::AVL(){
    this->racine = nullptr;
}
    


void AVL::affichageApartitirDunNoeud( node *n, int prof){
    if(n != nullptr){
        affichageApartitirDunNoeud(n->f_droit,prof+1);
        for(int i = 0; i < prof ; i++){
            std::cout<<" ";
        }
        std::cout << n->element << "\n";

         affichageApartitirDunNoeud(n->f_gauche, prof + 1);

    }
 }




node* AVL::insereApartirDunNoeud(const Elem &e, node *&n){
    if(n == nullptr){
        n = new node(e);
        n->element = e;
        n->f_gauche = nullptr;
        n->f_droit = nullptr;
        n->hauteur = 1;
        n->desequilibre = 0;
        return n; 
    }else{
        if(e > n->element){
            insereApartirDunNoeud(e, n->f_droit);
            //mise a jour des hauteur du noeud 
            // le cas ou n->gauche est null
            if(n->f_gauche == nullptr){
                n->hauteur = std::max(0, n->f_droit->hauteur) + 1;
                n->desequilibre =  0 - n->f_droit->hauteur;
    
            }else{
                n->hauteur = std::max(n->f_gauche->hauteur, n->f_droit->hauteur) + 1;
                n->desequilibre =  n->f_gauche->hauteur - n->f_droit->hauteur;

            }
        }else{
            insereApartirDunNoeud(e, n->f_gauche);
            if(n->f_droit == nullptr){
                n->hauteur = std::max(n->f_gauche->hauteur, 0) + 1;
                n->desequilibre =  n->f_gauche->hauteur - 0;
            }else{
                n->hauteur = std::max(n->f_gauche->hauteur, n->f_droit->hauteur) + 1;
                n->desequilibre =  n->f_gauche->hauteur - n->f_droit->hauteur;

            }
        }
    }
}
void AVL::rotation_droite( node *&ptr_n){
    node *ptr_g = ptr_n->f_gauche;
    ptr_n->f_gauche = ptr_g->f_droit;
    ptr_g->f_droit = ptr_n;
    ptr_n = ptr_g;
    
}







































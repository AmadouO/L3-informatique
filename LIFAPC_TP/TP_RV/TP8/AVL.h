#ifndef _AVL__
#define _AVL__
#include "element.h"


class node{
    friend class AVL;
    private:
    Elem element;
    node * f_gauche;
    node * f_droit;
       int hauteur;
    int desequilibre;


   //bool cousu;//indicateur de fil droit

    node(const Elem& e);
};

class AVL
{

private:
    node *racine;
    


public:
    AVL();
    node* insereApartirDunNoeud(const Elem &e, node *&n);
    void affichageApartitirDunNoeud( node *n, int prof);
    void rotation_droite( node *&ptr_n);
   

};
#endif
















































































































































































































































































































































































































































































































































/*

 ~arbre();
    bool rechercheElement(const Elem &elment) const;
    void insereElement( const Elem &element);
    void affichage() const;

bool rechercher(node* n, const Elem& element) const ;
    void inserer(node*& n, const Elem& element); 
    void afficher(node* n) const ;


void arbre::afficher(node* n) const {

    if (n == nullptr){
        return;
    }

    if (n->f_gauche) {
        afficher(n->f_gauche);
    }
        std::cout << n->element << " ";
    
    if(n->cousu){
        afficher(n->f_droit);
    }else if(n->f_droit){
        afficher(n->f_droit);
    }
}



bool arbre::rechercheElement(const Elem& element) const {
    return rechercher(racine, element);
}

void arbre::insereElement(const Elem& element) {
    inserer(racine, element);
}
void arbre::affichage() const {
    afficher(racine);
}


// Fonction recursive pour rechercher un element
bool arbre::rechercher(node* n, const Elem& element) const {
    if (n == nullptr) {
        return false; // element non trouver
    }
    if (element == n->element) {
        return true; // element trouver
    }
    if (element < n->element){
        return rechercher(n->f_gauche, element); //on recherche dans le sous arbre de gauche
    }else{
        return rechercher(n->f_droit, element);  // Recherche dans le sous-arbre droit

    }
}

    // Fonction recursive pour inserer un element
void arbre::inserer(node*& n, const Elem& element) 
{
    if (n == nullptr) {
        n = new node(element); // on cree un nouveau nœud si on atteint une feuille
    } else if (element < n->element) {
        inserer(n->f_gauche, element); // on insert dans le sous-arbre gauche
    } else if (element > n->element) {
        inserer(n->f_droit, element);  // on insert dans le sous-arbre droit
    }
}
*/
#include <iostream>
#include "arbre.h"

node::node(const Elem& e){
    element = e;
    f_gauche = nullptr;
    f_droit = nullptr;
    cousu = false;

}

arbre::arbre(){
    this->racine = nullptr;
}

arbre::~arbre(){
    detruire(this->racine);
}

bool arbre::rechercheElement(const Elem& element) const {
    return rechercher(racine, element);
}

void arbre::insereElement(const Elem& element) {
    inserer(racine, element);
}
void arbre::affichageInfixer() const {
    afficherInfixe(racine);
}

void arbre::affichagePrefixer() const {
    afficherPrefixe(racine);
}

void arbre::affichagePostfixer() const {
    afficherPostfixe(racine);
}


// --------------------------------------------------------------------
// Implementations des fonctions privees
// --------------------------------------------------------------------

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

// Fonction recursive d'affichage infixe
// affichage ordre croissant 
void arbre::afficherInfixe(node* n) const {
    if (n != nullptr) {
        afficherInfixe(n->f_gauche);
        std::cout << n->element << " ";
        afficherInfixe(n->f_droit);
    }
}

// Fonction recursive d'affichage préfixe
void arbre::afficherPrefixe(node* n) const {
    if (n != nullptr) {
        std::cout << n->element << " ";
        afficherPrefixe(n->f_gauche);
        afficherPrefixe(n->f_droit);
    }
}

// Fonction recursive d'affichage postfixe
void arbre::afficherPostfixe(node* n) const {
    if (n != nullptr) {
        afficherPostfixe(n->f_gauche);
        afficherPostfixe(n->f_droit);
        std::cout << n->element << " ";
    }
}
//fonction recursive de destruiction des noeuds
void arbre::detruire(node *n){
    if(n != nullptr){
        detruire( n->f_gauche);
        detruire( n->f_droit);
        delete n;
    }
}

































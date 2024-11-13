#ifndef _ARBRE__
#define _ARBRE__
#include "element.h"


class node{
    friend class arbre;
    private:
    Elem element;
    node * f_gauche;
    node * f_droit;

    bool cousu;//indicateur de fil droit

    node(const Elem& e);
};

class arbre
{

private:
    node *racine;
    bool rechercher(node* n, const Elem& element) const ;
    void inserer(node*& n, const Elem& element); 
    void afficherInfixe(node* n) const ;
    void afficherPrefixe(node* n) const;
    void afficherPostfixe(node* n) const;

    void detruire(node *n); //Destruiction recursive de noeuds
public:
    arbre();
    ~arbre();
    bool rechercheElement(const Elem &elment) const;
    void insereElement( const Elem &element);
    void affichageInfixer() const;
    void affichagePrefixer() const;
    void affichagePostfixer()const ;

};
#endif

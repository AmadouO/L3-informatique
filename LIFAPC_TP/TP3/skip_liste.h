#ifndef _SKIP_LISTE

#include "element.h"
#include <iostream>

#define HMAX 10



class Cellule{
    friend class skip_liste;

    public :
        Elem info;
        Cellule *psuivant[HMAX];
        int niveau;

};

class skip_liste
{
private:
    
    int taille;
    Cellule *ad;
    bool b;

public:
    skip_liste();

    void affichage() const;

    void insere(const Elem & e);
    void insere_autre_niveau(const Elem & e);
    Cellule* recherche(const Elem & e);
    void etablissement_des_niveau();
};






#endif
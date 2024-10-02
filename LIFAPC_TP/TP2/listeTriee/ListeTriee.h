#ifndef _LISTE
#define _LISTE

#include "element.h" //offrant le type Elem
#include <iostream>


class Liste; // declaration

class Cellule
{
    friend class Liste;

    public :
        Elem info;
        Cellule *psuivant;
};
class Liste
{
    //Donnees membres-----------------------------------------------------------
        Cellule *ad;
        int taille;
        
    public :
        //Constructeurs-------------------------------------------------------------
    Liste();

    void affichage() const;

    void insere(const Elem & e);

};
#endif

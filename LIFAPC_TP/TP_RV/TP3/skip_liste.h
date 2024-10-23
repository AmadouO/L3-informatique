// LIFAP6 - Automne 2017 - R. Chaine

#ifndef _LISTE
#define _LISTE

#include "element.h" //offrant le type Elem
#include <iostream>

#define HMAX 10

class Skip_List; // declaration

class Cellule
{
    friend class Skip_List;

    //private :
    public :
        Elem info;
        Cellule *psuivant[HMAX];
        int niveau;
};

class Skip_List
{
    public :
    Skip_List();

    void affichage() const;
    void etablissement_des_niveau();
    void insere(const Elem & e);
    Cellule * rechercherElem(const Elem & e);
    void suppressionElem(const Elem & e);
    void affichageNiveau();

    
 
    private :
    //Donnees membres-----------------------------------------------------------
        Cellule *ad;
        int taille;
        bool niveau_etabli;
};


#endif  



// LIFAP6 - Automne 2017 - R. Chaine

#ifndef _LISTE
#define _LISTE

#include "element.h" //offrant le type Elem

class ListeTriee; // declaration

class Cellule
{
    friend class ListeTriee;

    //private :
    public :
        Elem info;
        Cellule *psuivant;
        Cellule *psuivant2; // Deuxième niveau de chaînage (vers la cellule deux positions plus loin)
};

class ListeTriee
{
    public :
    ListeTriee();

    void affichage() const;

    Cellule * rechercherElem(const Elem & e);
    void suppressionElem(const Elem & e);

    void insere(const Elem & e);
    void etablissementSecondNiveau();
    void affichageNiveau2();

    
 
    private :
    //Donnees membres-----------------------------------------------------------
        Cellule *ad;
        int taille;
        bool niveau2_etabli;
};


#endif

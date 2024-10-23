//_Pragma once
#ifndef _TABLE_H_
#define _TABLE_H_

#include <iostream>

enum Etat { occupe, libere, libre};

class table_h
{
    public:
     Etat *tab_etat;
     int *tab_cle;
     int *tab_info;
     int taille_table;
     int nbr_elment;
    int (*ph) (int cle, int capacite);
    int (*ppas)(int cle, int i);


    public:
        table_h( int taille, int (*ptr_ph) (int cle, int capacite));
       // ~table_h();
        int hacher(int a,int n);
        void insere(int elem);
        void rechercher(int elem);

};


#endif

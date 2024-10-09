#include <iostream>
#include"skip_liste.h"

int main(){
    skip_liste s_list;
    s_list.insere(1);
    s_list.insere(2);
    s_list.insere(3);

    s_list.affichage();
    
    Cellule *mac = s_list.recherche(1);
    std::cout<<mac->info<<std::endl;
       Cellule *macs = s_list.recherche(2);
    std::cout<<macs->info<<std::endl;
    Cellule *mace = s_list.recherche(3);
    std::cout<<mace->info<<std::endl;
    //s_list.etablissement_des_niveau();

    return 0;
}
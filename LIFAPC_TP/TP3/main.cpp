#include <iostream>
#include"skip_liste.h"

int main(){
    skip_liste s_list;
    s_list.insere(1);
    s_list.insere(2);
    s_list.insere(3);
    s_list.etablissement_des_niveau();

    s_list.affichage();
    return 0;
}
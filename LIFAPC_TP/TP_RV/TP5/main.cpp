
#include <cstdio>
#include <iostream>
#include "table_h.h"

int hacher(int a,int n){
    return a % n;
}

int main()
{
  std::cout<< "bonjour" << std::endl;
  table_h table_hachage(10, hacher);

  table_hachage.insere(2);
  table_hachage.insere(3);
  table_hachage.insere(5);
  table_hachage.insere(6);
  table_hachage.insere(12);


  table_hachage.rechercher(6);
  table_hachage.rechercher(12);
  table_hachage.rechercher(13);




  


  return 0;
}

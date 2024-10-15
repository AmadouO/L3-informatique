// LIFAP6 - Automne 2017 - R. Chaine

#include "element.h"
#include "ListeTriee.h"
#include <cstdio>
#include <iostream>

int main()
{
  std::cout<< "bonjour" << std::endl;

  ListeTriee lili;
  lili.insere(0);
  lili.insere(1);
  lili.insere(20);
  lili.insere(10);
  lili.insere(2);
  lili.insere(30);
  lili.insere(35);
  lili.insere(33);
  Cellule *rech = lili.rechercherElem(30);
  std::cout<< rech->psuivant->psuivant->info << std::endl;
 // lili.suppressionElem(30);

for(int i = 0; i < 5; i++){
  lili.insere(std::rand()%100);// #include <cstdlib>


}
lili.etablissementSecondNiveau();

lili.affichage();
lili.affichageNiveau2();





  



  /*
  std::printf("Lili\n");
  for(int i=1;i<5;i++)
    lili.ajoutEnTete(i);
  std::printf("Lili\n");
  lili.affichage();
  for(int i=10;i<15;i++)
    lili.ajoutEnQueue(i);
  std::printf("Lili\n");
  lili.affichage();
  Liste lolo(lili);
  std::printf("Lolo\n");
  lolo.affichage();
  lili.vide();
  std::printf("Lolo\n");
  lolo.affichage();
  lolo=lili;
  printf("Lolo\n");
  lolo.affichage(); */
  return 0;
}

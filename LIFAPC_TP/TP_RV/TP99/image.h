#include <iostream>
#include <string>

using namespace std;

typedef int Elem ;
enum Etat { decouvert ,visite };



class Image {

  public :
      int Ligne ;
      int Colonne ;
      int *IntenPix;
      Etat * tabEtat;
      int * Distance;
      int * Predecess;
  public :
  Image(string nomFichier) ;
  int indice (int LargLigne ,int i ,int j) ;




     
};

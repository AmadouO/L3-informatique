#include <iostream>
#include <string>

using namespace std;

typedef int Elem ;
enum Etat { decouvert ,visite };


struct Pixel {
    int index;
    int distance;
    Pixel(int i, int j){
       this->index =i ;
       this->distance =j ;
    }

    bool operator<(const Pixel& other) const {
        return distance > other.distance; // Priorité minimale pour Dijkstra
    }
};

class Image {

  public :
      bool djiskstra ;
      int Ligne ;
      int Colonne ;
      int *IntenPix;
      int * tabEtat;
      int * Distance;
      int * Predecess;
  public :

  Image(string nomFichier) ;
  ~Image();
  int indice (int LargLigne ,int i ,int j) ;
  void InitialiseEtat();
  void InitialiseDistance();
  void InitialisePredec();
  int* voisins(int i, int j ,int & taille);
  void calculerDistances() ;
  void sauvegarderDistanceDansPGM(string fichierSortie);
  void retroprojection(string fichierSortie);
  int  projeterPixelSurForme(int x, int y);
  int projeterPixelSurUnion(Image * autre, int x, int y);
  int* distanceUnion(Image& autre);
  static bool validerPGM(string& cheminFichier);




     
};

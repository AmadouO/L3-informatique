#include <iostream>
#include <algorithm>
#include <cstdio> //fopen, fclose, fprintf, fscanf
#include <fstream> //ifstream, ofstream
#include <cstdlib> //exit


#include "image.h"
using namespace std;

Image::Image(string nomFichier){
     ifstream ifs;
  ifs.open(nomFichier);
  if(ifs.bad())
    {std::cout<<"Impossible d'ouvrir le fichier "<<nomFichier<<" en lecture \n"; exit(1);}
  int temp;
  int compt = 0;
  char c ;
  ifs >> c ;
  ifs >> c ;
  ifs >>  this -> Ligne ;
  ifs >>  this -> Colonne ;
  ifs >> temp ; // je jette la valeur de l'intensite des couleurs 
  this -> IntenPix = new int [this -> Ligne * this -> Ligne] ;
  while(ifs >> temp ){
     IntenPix[compt] =temp ;
     compt ++ ;
  }
   
  ifs.close();

}

int Image::indice (int LargLigne ,int i ,int j) {
    return i * (LargLigne + 1) + j ;
}






int main() {
     
     string nom = "image.pgm";
     Image c(nom) ;

     cout << c.IntenPix[0] << endl;
     int val = c.indice(c.Colonne ,0 ,1);
     cout << val << endl ;


    return 0;
}

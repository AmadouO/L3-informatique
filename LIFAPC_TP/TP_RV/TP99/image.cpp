#include <iostream>
#include <algorithm>
#include <cstdio> //fopen, fclose, fprintf, fscanf
#include <fstream> //ifstream, ofstream
#include <cstdlib> //exit
#include <queue>    // Pour la file de priorité


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
  this -> IntenPix = new int [this -> Ligne * this -> Colonne] ;
  this -> Distance = new int [this -> Ligne * this -> Colonne] ;
  this -> tabEtat = new int [this -> Ligne * this -> Colonne] ;
  this -> Predecess = new int [this -> Ligne * this -> Colonne] ;
  while(ifs >> temp ){
     IntenPix[compt] =temp ;
     compt ++ ;
  }
  ifs.close();

}

Image::~Image() {
    delete[] IntenPix;
    delete[] Distance;
    delete[] tabEtat;
    delete[] Predecess;
}

// On calcule l'indice correspondant à une position (i, j) dans un tableau 1D
int Image::indice (int LargLigne ,int i ,int j) {
    return i * LargLigne  + j ; // Calcule l'indice à partir de la ligne et de la colonne
}

// on Initialise le tableau des états en fonction des intensités des pixels
void Image::InitialiseEtat(){
  for (int i=0 ; i<this->Ligne * this->Colonne ;i++){
    if(this->IntenPix[i] == 0){
      this->tabEtat[i] = visite;// Définit l'état comme 0 (visité)
    }
    
  }
}

// on Initialise le tableau des distances avec des valeurs par défaut
void Image::InitialiseDistance(){
  const int INFINI = 1000000;  // Représente une distance infinie
  for (int i=0 ; i<this->Ligne * this->Colonne ;i++){
    if((this->IntenPix[i]) == 0){
      this->Distance[i] = 0;// Distance initiale à 0
    }
    else{
      this->Distance[i] = INFINI; // Distance initiale infinie
    }
    
  }
}

// on Initialise le tableau des prédécesseurs avec une valeur par défaut (-1)
void Image::InitialisePredec(){
  for (int i=0 ; i<this->Ligne * this->Colonne ;i++){
      this->Predecess[i] = -1; // Indique qu'aucun prédécesseur n'est défini
  }
}
// Retourne les indices des voisins d'un pixel donné (i, j)
int* Image::voisins(int i, int j, int & taille) {
    int* result = new int[8]; // Tableau dynamique pour stocker les indices des voisins
     taille = 0; // Compteur pour le nombre de voisins

    if (i > 0) {
        result[taille] = indice(Colonne, i - 1, j); // Voisin du haut
        taille++;
    }
    if (i > 0 && j < Colonne - 1) {
        result[taille] = indice(Colonne, i - 1, j + 1);// Voisin en haut à droite 
        taille++;
    }
    if (j < Colonne - 1) {
        result[taille] = indice(Colonne, i, j + 1); // Voisin à droite
        taille++;
    }
    if (i < Ligne - 1 && j < Colonne - 1) {
        result[taille] = indice(Colonne, i + 1, j + 1); // Voisin en bas à droite
        taille++;
    }
    if (i < Ligne - 1) {
        result[taille] = indice(Colonne, i + 1, j); // Voisin du bas
        taille++;
    }
    if (i < Ligne - 1 && j > 0) {
        result[taille] = indice(Colonne, i + 1, j - 1); // Voisin en bas à gauche
        taille++;
    }
    if (j > 0) {
        result[taille] = indice(Colonne, i, j - 1); // Voisin à gauche
        taille++;
    }
    if (i > 0 && j > 0) {
        result[taille] = indice(Colonne, i - 1, j - 1); // Voisin en haut à gauche
        taille++;
    }
    return result; // On Retourne le tableau des indices des voisins
}

// On sauvegarde les distances calculées dans un fichier au format PGM
void Image::sauvegarderDistanceDansPGM(string fichierSortie) {
    std::ofstream ofs(fichierSortie);
    if (!ofs.is_open()) {
        std::cerr << "Impossible d'ouvrir le fichier " << fichierSortie << " en écriture.\n";
        return;
    }
    
    ofs << "P2\n";  
    ofs << this->Colonne << " " << this->Ligne << "\n";
    ofs << "255\n";  

    for (int i = 0; i < this->Ligne * this->Colonne; i++) {
        int intensity = this->Distance[i];
        ofs << intensity << " ";  
    }
    ofs << "\n";

    ofs.close();
    std::cout << "Image de distance sauvegardée dans " << fichierSortie << "\n";
}


void Image::calculerDistances() {
    std::priority_queue<Pixel> file; 

    for (int i = 0; i < Ligne * Colonne; i++) {
        if (IntenPix[i] == 0) {
            file.push(Pixel(i, 0));  // On les ajoute dans la file
        }
    }

    // Algorithme de Dijkstra
    while (!file.empty()) {
        Pixel courant = file.top();  
        file.pop();  
        // Si le pixel a déjà été visité, on l'ignore
        

        // Convertir l'indice en coordonnées (i, j)
        int i = courant.index / Colonne;
        int j = courant.index % Colonne;

        tabEtat[courant.index] = visite;  

        int taille;
        int* voisinsTableau = voisins(i, j, taille);

        for (int k = 0; k < taille; k++) {
            int voisinIndex = voisinsTableau[k];
        
            int voisinI = voisinIndex / Colonne;
            int voisinJ = voisinIndex % Colonne;

            int cout = (i == voisinI || j == voisinJ) ? 2 : 3;  // 2 si horizontal/vertical, 3 si diagonal

            int nouveauCout = Distance[courant.index] + cout;  // Mise à jour de la distance

            if (nouveauCout < Distance[voisinIndex]) {
                Distance[voisinIndex] = nouveauCout;
                Predecess[voisinIndex] = courant.index;

                file.push(Pixel(voisinIndex, nouveauCout));
            }
        }

        delete[] voisinsTableau;  
    }
    this->djiskstra =true ;
}

void Image::retroprojection(string fichierSortie) {
    std::ofstream ofs(fichierSortie);
    if (!ofs.is_open()) {
        std::cerr << "Impossible d'ouvrir le fichier " << fichierSortie << " en écriture.\n";
        return;
    }
 
    ofs << "P2\n";
    ofs << Colonne << " " << Ligne << "\n";
    ofs << "255\n"; 

    for (int i = 0; i < Ligne * Colonne; i++) {
        if (Distance[i] == 0) {
            ofs << "0 "; 
        } else {
            ofs << "255 ";  
        }
    }
    ofs << "\n";
    ofs.close();
    std::cout << "Image de rétroprojection sauvegardée dans " << fichierSortie << "\n";
}


 int  Image::projeterPixelSurForme(int x, int y) {
    int Index = indice(Colonne, x, y);
    int pred ;

    if (Distance[Index] == 0) {
        return Index;
    }
    while ( Distance[Index] != 0) {
        pred =Index ;
        Index = Predecess[Index];
    }
       return pred;
}

int* Image::distanceUnion(Image& autre ) {
    if (this->Ligne != autre.Ligne || this->Colonne != autre.Colonne) {
        cout << "Erreur : Les dimensions des deux images ne sont pas les memes"<<endl;
        exit(1);
    }
    autre.InitialiseDistance();
    autre.calculerDistances();
    int* distanceUnion = new int[this->Ligne * this->Colonne];

    for (int i = 0; i < this->Ligne * this->Colonne; i++) {
        distanceUnion[i] = std::min(this->Distance[i], autre.Distance[i]);
    }

    return distanceUnion;
}


int Image::projeterPixelSurUnion(Image * autre, int x, int y) {
    if (this->Ligne != autre->Ligne || this->Colonne != autre->Colonne) {
        cout << "Erreur : Les dimensions des deux images ne sont pas les mêmes." << endl;
        exit(1);
    }

    // Vérifier si Dijkstra a été exécuté
    if (!this->djiskstra || !autre->djiskstra) {
        cout << "Erreur : Les images doivent avoir leurs distances calculées avec Dijkstra avant d'appeler cette fonction." << endl;
        exit(1);
    }

    int indexPixel = indice(Colonne, x, y);

    int distance1 = this->Distance[indexPixel];
    int distance2 = autre->Distance[indexPixel];

    if (distance1 <= distance2) {
        return this->projeterPixelSurForme(x, y);
    } else {
        return autre->projeterPixelSurForme(x, y);
    }
} 

bool Image::validerPGM(string& cheminFichier) {
    ifstream fichier(cheminFichier, ios::in);
    if (!fichier) {
        cout << "Erreur : Impossible d'ouvrir le fichier " << cheminFichier << endl;
        return false;
    }

    string magicNumber;
    fichier >> magicNumber;
    int largeur, hauteur, maxVal;
    fichier >> largeur >> hauteur >> maxVal;

    if (magicNumber != "P2" || (largeur <= 0 || hauteur <= 0 || maxVal <= 0)) {
        return false;
    }
    int nombreDePixels = largeur * hauteur;
    int pixelCount = 0;
    int pixel;
    while (fichier >> pixel) {
        if (pixel < 0 || pixel > maxVal) {
            return false;
        }
        pixelCount++;
    }

    if (pixelCount != nombreDePixels) {
       
        return false;
    }

    cout << "Le fichier " << cheminFichier << " est valide." << endl;
    return true;
}






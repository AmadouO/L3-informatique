#include "image.h"


void afficherMenu() {
    cout << "\nMenu - Bibliothèque d'Images" << endl;
    cout << "1. Charger une image PGM et initialiser les distances et les états" << endl;
    cout << "2. Calculer les distances (Algorithme de Dijkstra)" << endl;
    cout << "3. Sauvegarder l'image des distances dans un fichier PGM" << endl;
    cout << "4. Sauvegarder la rétroprojection dans un fichier PGM" << endl;
    cout << "5. Projeter un pixel sur une forme" << endl;
    cout << "6. Projeter un pixel sur l'union de deux images" << endl;
    cout << "7. Quitter" << endl;
    cout << "Votre choix : ";
}

int main() {
    Image *img1; // Image principale
    Image *img2; // Image pour l'union
    string fichier, fichierSortie;
    int choix;
    bool imageChargee = false; // Indique si une image a été chargée
    bool continuer = true;

    while (continuer) {
        afficherMenu();
        cin >> choix;

        switch (choix) {
            case 1:
                cout << "Entrez le nom du fichier PGM à charger : ";
                cin >> fichier;

                if (Image::validerPGM(fichier)) {
                    img1 = new Image(fichier); // Charger l'image principale
                    img1->InitialiseDistance();
                    img1->InitialiseEtat();
                    img1->InitialisePredec();
                    imageChargee = true;
                    cout << "Image chargée et initialisée avec succès." << endl;
                } else {
                    cout << "Le fichier PGM est invalide ou introuvable." << endl;
                }
                break;

            case 2:
                if (imageChargee) {
                    img1->calculerDistances();
                    cout << "Distances calculées avec l'algorithme de Dijkstra." << endl;
                } else {
                    cout << "Aucune image n'a été chargée. Veuillez charger une image d'abord." << endl;
                }
                break;

            case 3:
                if (imageChargee) {
                    cout << "Entrez le nom du fichier PGM pour sauvegarder l'image des distances : ";
                    cin >> fichierSortie;
                    img1->sauvegarderDistanceDansPGM(fichierSortie);
                    cout << "Image des distances sauvegardée avec succès." << endl;
                } else {
                    cout << "Aucune image n'a été chargée ou distances non calculées." << endl;
                }
                break;

            case 4:
                if (imageChargee) {
                    cout << "Entrez le nom du fichier PGM pour sauvegarder la rétroprojection : ";
                    cin >> fichierSortie;
                    img1->retroprojection(fichierSortie);
                    cout << "Rétroprojection sauvegardée avec succès." << endl;
                } else {
                    cout << "Aucune image n'a été chargée ou distances non calculées." << endl;
                }
                break;

            case 5:
                if (imageChargee) {
                    int x, y;
                    cout << "Entrez les coordonnées du pixel (x, y) : ";
                    cin >> x >> y;
                    int index = img1->projeterPixelSurForme(x, y);
                    cout << "Le pixel projeté sur la forme a l'indice : " << index << endl;
                } else {
                    cout << "Aucune image n'a été chargée ou distances non calculées." << endl;
                }
                break;

            case 6:
                if (imageChargee) {
                    cout << "Entrez le nom du fichier PGM pour charger la deuxième image : ";
                    cin >> fichier;

                    if (Image::validerPGM(fichier)) {
                        img2 =new Image(fichier); // Charger la deuxième image
                        img2->InitialiseDistance();
                        img2->InitialiseEtat();
                        img2->InitialisePredec();
                        img2->calculerDistances();

                        int x, y;
                        cout << "Entrez les coordonnées du pixel (x, y) : ";
                        cin >> x >> y;

                        int index = img1->projeterPixelSurUnion(img2, x, y);
                        cout << "Le pixel projeté sur l'union a l'indice : " << index << endl;
                    } else {
                        cout << "Le fichier PGM est invalide ou introuvable." << endl;
                    }
                } else {
                    cout << "Veuillez charger et initialiser une image avant d'utiliser cette fonction." << endl;
                }
                break;

            case 7:
                cout << "Merci d'avoir utilisé le programme. À bientôt !" << endl;
                continuer = false;
                break;

            default:
                cout << "Choix invalide. Veuillez réessayer." << endl;
                break;
        }
    }

    return 0;
}

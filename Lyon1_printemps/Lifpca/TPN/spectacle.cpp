// À COMPLETER : écrire ici votre nom et numéro de machine :
// Nom : ...
// Prénom : ...
// Numéro étudiant : ...
// Numéro de machine : ...
/********************************************************************
 * Copyright (C) 2022 by UCBL                                       *
 * Initial author: Gregoire Pichon                                  *
 ********************************************************************/

//LIGNE DE COMPILATION
//g++ spectacle.cpp  -g -O0 -Wall -Wextra  -std=c++11  -pthread -o spectacle

#include <thread>
#include <mutex>
#include <iostream>
#include <vector>
#include <condition_variable>
#include <unistd.h>
using namespace std;

mutex cout_mutex;

/**
 * Fonction appelée là où vous devez écrire du code. Ne modifiez pas la
 * fonction, mais vous ne devriez plus l'appeler si vous terminez le TP.
 */
#define A_FAIRE() do {							\
    cout << __FILE__ << ":" << __LINE__ << ": Cette partie n'est pas encore faite, à vous !" << endl; \
    abort();								\
  } while (0)
bool debug = false;
bool check = true;


/**
 * Classe de base commune aux moniteurs.
 * Ne pas modifier.
 */
class Spectacle
{
public:
  virtual bool achatSpectacle(int) = 0;
  virtual void ajoutPlace() = 0;
  virtual void plusDePlace() = 0;
  virtual void nouvellesPlaces() = 0;

protected:
  /**
   * Achete une place. Précondition : une place doit être disponible !
   */
  void achatEffectif()
  {
    unique_lock<mutex> l(m);
    places_dispo--;
    verification();
  }
  /**
   * Ajoute une place (qui pourra être achetée via achatEffectif()).
   */
  void ajoutEffectif()
  {
    unique_lock<mutex> l(m);
    places_dispo++;
    verification();
  }

private:
  void verification()
  {
    if (places_dispo < 0 && check)
      {
	cout << "On achète une place alors que c'est déjà complet ! " << endl;
	abort();
      }
  }
  mutex m;
  int places_dispo = 0;
};

Spectacle *gestion_spectacle = nullptr;
int nb_spectateurs = 4;
int nb_rounds = 2;

/**
 * Version qui ne fait rien.
 * Ne pas modifier, sauf le commentaire À FAIRE.
 */
class Spectacle_Sans_Protection : public Spectacle
{
  bool achatSpectacle(int id) {
    if (debug) {
      cout << "Achat Spectacle par " << id << endl;
    }
    achatEffectif();
    return 1;
  };
  void ajoutPlace() {
    if (debug) {
      cout << "Ajout Place." << endl;
    }
    ajoutEffectif();
  };
  void plusDePlace() {
  };
  void nouvellesPlaces() {
  };
  /* À FAIRE
     Expliquez le problème avec cette classe : Quel message d'erreur obtenez-vous ? Pourquoi ?
     Répondez ici:
    // À FAIRE : 
// Cette classe ne protège pas l'accès concurrent à ses données partagées.
// Plusieurs threads peuvent modifier le nombre de places en même temps, entraînant des conditions de course.
// Exemple : Deux spectateurs lisent le nombre de places disponibles simultanément, et chacun pense pouvoir acheter la dernière place.
// Cela peut conduire à des réservations en double, un nombre de places négatif, ou des plantages du programme.
// Une solution est d'utiliser des mécanismes de synchronisation (mutex, sémaphores, etc.).



  */
};

class Spectacle_Sur : public Spectacle
{
  bool achatSpectacle(int id) {
    bool got_place = false;
    // À FAIRE : gérer correctement l'accès concurrent aux places
    // (Il est interdit de supprimer les appels aux fonctions ...Effectif(),
    // mais vous ne devez appeler achatEffectif que quand l'achat est
    // effectivement réalisé, c'est à dire quand la fonction renvoie 'true')
    //A_FAIRE(); // À SUPPRIMER
    unique_lock<mutex> loc(mtx);
    while (nb_place_dispo == 0){
      cv.wait(loc);
    }
      nb_place_dispo--;
      achatEffectif();
      got_place = true;
    return got_place;
  };
  void ajoutPlace() {
    // À FAIRE : gérer correctement l'accès concurrent aux places
    // (Il est interdit de supprimer les appels aux fonctions ...Effectif())
   // A_FAIRE(); // À SUPPRIMER
   unique_lock<mutex> loc(mtx);
   nb_place_dispo++;
    ajoutEffectif();
    cv.notify_all();
  };
  void plusDePlace() {
    // RIEN A FAIRE ICI
  };
  void nouvellesPlaces() {
    // RIEN A FAIRE ICI
  };
private:
  // À FAIRE : ajouter le nécessaire pour que la classe se comporte comme un moniteur de Hoare.
  mutex mtx;
  condition_variable cv;
  int nb_place_dispo = 0;
};

class Spectacle_Avec_Attente : public Spectacle
{
  bool achatSpectacle(int id) {
    bool got_place = false;
    // À FAIRE : gérer correctement l'accès concurrent aux places avec attente
    // (Il est interdit de supprimer les appels aux fonctions ...Effectif(),
    // mais vous ne devez appeler achatEffectif que quand l'achat est
    // effectivement réalisé, c'est à dire quand la fonction renvoie 'true')
    //A_FAIRE(); // À SUPPRIMER
    unique_lock<mutex> loc(mtx);
    while(nb_place_dispo == 0 && fini == false){
      cv.wait(loc);
    }
    if(nb_place_dispo > 0){
      nb_place_dispo--;
      achatEffectif();
      got_place = true;
    }
    return got_place;
  };
  void ajoutPlace() {
    // À FAIRE : gérer correctement l'accès concurrent aux places avec attente
    // (Il est interdit de supprimer les appels aux fonctions ...Effectif())
    //A_FAIRE(); // À SUPPRIMER
    unique_lock<mutex> loc(mtx);
    nb_place_dispo++;
    ajoutEffectif();
    cv.notify_all();
  };
  void plusDePlace() {
    // À FAIRE : gérer correctement l'accès concurrent aux places avec attente
    // (Il est interdit de supprimer les appels aux fonctions ...Effectif())
    //A_FAIRE(); // À SUPPRIMER
    unique_lock<mutex> loc(mtx);
    fini  = true;
    cv.notify_all();
  };
  void nouvellesPlaces() {
    // À FAIRE : gérer correctement l'accès concurrent aux places avec attente
    // (Il est interdit de supprimer les appels aux fonctions ...Effectif())
    //A_FAIRE(); // À SUPPRIMER
    unique_lock<mutex> loc(mtx);
    fini = false;
  };
private:
  // À FAIRE : ajouter le nécessaire pour que la classe se comporte comme un moniteur de Hoare.
  mutex mtx;
  condition_variable cv;
  int nb_place_dispo = 0;
  bool fini = false;
};


class Spectacle_Sans_Famine : public Spectacle
{
  bool achatSpectacle(int id) {
    bool got_place = false;
    // À FAIRE : gérer correctement l'accès concurrent aux places sans famine
    // (Il est interdit de supprimer les appels aux fonctions ...Effectif(),
    // mais vous ne devez appeler achatEffectif que quand l'achat est
    // effectivement réalisé, c'est à dire quand la fonction renvoie 'true')
    A_FAIRE(); // À SUPPRIMER
    achatEffectif();
    return got_place;
  };
  void ajoutPlace() {
    // À FAIRE : gérer correctement l'accès concurrent aux places sans famine
    // (Il est interdit de supprimer les appels aux fonctions ...Effectif())
    A_FAIRE(); // À SUPPRIMER
    ajoutEffectif();
  };
  void plusDePlace() {
    // À FAIRE : gérer correctement l'accès concurrent aux places sans famine
    // (Il est interdit de supprimer les appels aux fonctions ...Effectif())
    A_FAIRE(); // À SUPPRIMER
  };
  void nouvellesPlaces() {
    // À FAIRE : gérer correctement l'accès concurrent aux places sans famine
    // (Il est interdit de supprimer les appels aux fonctions ...Effectif())
    A_FAIRE(); // À SUPPRIMER
  };
private:
  // À FAIRE : ajouter le nécessaire pour que la classe se comporte comme un moniteur de Hoare.
  /* À FAIRE
     Justifiez ici l'absence de famine





  */
};

/**************** Lancement des threads utilisant les moniteurs ******************/

/**
 * Latence de chaque spectateur pour accèder au site de réservation
 * Ne pas modifier.
 */
int rand_latence()
{
  return 10*(rand()%50);
}


/**
 * Comportement d'un thread "spectateur"
 */
void spectateur(int id, int latence, int round)
{
  usleep(latence); // Toujours la meme latence d'un round à un autre
  bool got_place = gestion_spectacle->achatSpectacle(id);

  lock_guard<mutex> l(cout_mutex);
  if (got_place){
    cout << "Le spectateur " << id << " a obtenu une place au tour " << round << endl;
  }
    else {
    cout << "Le spectateur " << id << " n'a pas obtenu de place au tour " << round << endl;
  }
}

/**
 * Comportement d'un thread "vendeur"
 */
void vendeur(int round)
{
  sleep(1); // On attend avant de vendre les places
  int nb_places_dispo =  nb_spectateurs / 4 + rand()%(nb_spectateurs / 2);
  lock_guard<mutex> l(cout_mutex);
  cout << nb_places_dispo << " places sont disponibles au tour " << round << endl;
  for (int j = 0; j < nb_places_dispo; j++)
    {
      gestion_spectacle->ajoutPlace();	    
    }
  // On indique qu'il ne sera plus possible d'acheter des places (aucune place ne sera ajoutée)
  gestion_spectacle->plusDePlace();	    
}


void lancement_multithread()
{
  // Creation de la latence de chaque potentiel spectateur
  int delais[nb_spectateurs];
  for (int i = 0; i < nb_spectateurs; i++)
    {
      delais[i] = rand_latence();
    }

  for (int round = 0; round < nb_rounds; round++){
    // On remet en place la possibilité d'acheter des places
    gestion_spectacle->nouvellesPlaces();	    

    cout << "On lance les threads du tour " << round << endl;

    //spectateur(0, delais[0], round); // À SUPPRIMER
    //vendeur(round); // À SUPPRIMER

    // À FAIRE : lancer nb_spectateurs threads "spectateur" et un
    // thread "vendeur", puis attendre que les threads aient terminé.
   // A_FAIRE(); // À SUPPRIMER

   vector<thread> thrd_spec;

   for( int i = 0; i < nb_spectateurs; i++){
      thrd_spec.push_back(thread(spectateur, i, delais[i], round));

   }

    thread thrd_vend(vendeur, round);


    for( int i = 0; i < nb_spectateurs; i++){
      thrd_spec[i].join(); // permet d'attendre la fin du thread
    }

    thrd_vend.join(); // permet d'attendre la fin du thread


    cout << "Tous les threads ont terminé, round suivant." << endl;
  }
}

/**
 * Fonction principale qui analyse la ligne de commande.
 * Ne pas modifier.
 */
int main(int argc, char **argv)
{
  for (int i = 1; i < argc; i++)
    {
      if (string(argv[i]) == "--nb-spectateurs")
	{
	  i++;
	  nb_spectateurs = stoi(argv[i]);
	}
      else if (string(argv[i]) == "--nb-rounds")
	{
	  i++;
	  nb_rounds = stoi(argv[i]);
	}
      else if (string(argv[i]) == "--debug")
	{
	  debug = true;
	}
      else if (string(argv[i]) == "--no-check")
	{
	  check = false;
	}
      else if (string(argv[i]) == "--sur")
	{
	  gestion_spectacle = new Spectacle_Sur();
	}
      else if (string(argv[i]) == "--attente")
	{
	  gestion_spectacle = new Spectacle_Avec_Attente();
	}
      else if (string(argv[i]) == "--sans-famine")
	{
	  gestion_spectacle = new Spectacle_Sans_Famine();
	}
      else
	{
	  cout << "ERROR: Unknown option: " << argv[i] << endl;
	  exit(1);
	}
    }
  if (gestion_spectacle == nullptr)
    {
      gestion_spectacle = new Spectacle_Sans_Protection();
    }
  
  lancement_multithread();
}

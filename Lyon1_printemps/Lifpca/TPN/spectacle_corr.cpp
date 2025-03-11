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

#define MAX_SPECTATEURS 1000
int was_waiting[MAX_SPECTATEURS];

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
    m.lock();
    if (nb_places > 0){
      if (debug) {
	cout << "Achat Spectacle par " << id << endl;
      }
      got_place = true;
      nb_places--;
      achatEffectif();
    }
    m.unlock();
    return got_place;
  };
  void ajoutPlace() {
    // À FAIRE : gérer correctement l'accès concurrent aux places
    // (Il est interdit de supprimer les appels aux fonctions ...Effectif())
    if (debug) {
      cout << "Ajout Place." << endl;
    }
    m.lock();
    nb_places++;    
    ajoutEffectif();
    m.unlock();
  };
  void plusDePlace() {
  };
  void nouvellesPlaces() {
  };
private:
  // À FAIRE : ajouter le nécessaire pour que la classe se comporte comme un moniteur de Hoare.
  mutex m;
  int nb_places=0;
};

class Spectacle_Avec_Attente : public Spectacle
{
  bool achatSpectacle(int id) {
    bool got_place = false;
    // À FAIRE : gérer correctement l'accès concurrent aux places avec attente
    // (Il est interdit de supprimer les appels aux fonctions ...Effectif(),
    // mais vous ne devez appeler achatEffectif que quand l'achat est
    // effectivement réalisé, c'est à dire quand la fonction renvoie 'true')
    m.lock();
    while (nb_places == 0 && fini == false){
      c.wait(m);
    }
    if (nb_places > 0){
      if (debug) {
	cout << "Achat Spectacle par " << id << endl;
      }
      got_place = true;
      nb_places--;
      achatEffectif();
    }
    m.unlock();
    return got_place;
  };
  void ajoutPlace() {
    // À FAIRE : gérer correctement l'accès concurrent aux places avec attente
    // (Il est interdit de supprimer les appels aux fonctions ...Effectif())
    if (debug) {
      cout << "Ajout Place." << endl;
    }
    m.lock();
    nb_places++;    
    ajoutEffectif();
    c.notify_all();
    m.unlock();
  };
  void plusDePlace() {
    // À FAIRE : gérer correctement l'accès concurrent aux places avec attente
    // (Il est interdit de supprimer les appels aux fonctions ...Effectif())
    m.lock();
    fini = true;
    c.notify_all();
    m.unlock();
  };
  void nouvellesPlaces() {
    // À FAIRE : gérer correctement l'accès concurrent aux places avec attente
    // (Il est interdit de supprimer les appels aux fonctions ...Effectif())
    m.lock();
    fini = false;
    m.unlock();
  };
private:
  // À FAIRE : ajouter le nécessaire pour que la classe se comporte comme un moniteur de Hoare.
  mutex m;
  condition_variable_any c;
  int nb_places=0;
  bool fini = false;
};


int some_waiting(){
  int max = 0;
  for (int i = 0; i<nb_spectateurs; i++){
    if (was_waiting[i] > max){
      max = was_waiting[i];
    }
  }
  return max;
}

class Spectacle_Sans_Famine : public Spectacle
{
  bool achatSpectacle(int id) {
    bool got_place = false;
    // À FAIRE : gérer correctement l'accès concurrent aux places sans famine
    // (Il est interdit de supprimer les appels aux fonctions ...Effectif(),
    // mais vous ne devez appeler achatEffectif que quand l'achat est
    // effectivement réalisé, c'est à dire quand la fonction renvoie 'true')
    m.lock();
    // Soit il n'y a plus de place ou le tour est fini.
    // S'il reste des places, on verifie qu'il ne reste pas quelqu'un
    // de plus prioritaire en comparant le nombre de tours depuis
    // lesquels on attend et le nombre maximum parmi les autres
    // threads.
    while ((nb_places == 0 && fini == false) || ((nb_places > 0) && (was_waiting[id]!=some_waiting()))){
      c.wait(m);
    }
    if (nb_places > 0){
      if (debug) {
	cout << "Achat Spectacle par " << id << endl;
      }
      got_place = true;
      nb_places--;
      achatEffectif();
      was_waiting[id] = 0;
      c.notify_all();
    }
    else{
      was_waiting[id]++;
    }
    m.unlock();
    return got_place;
  };
  void ajoutPlace() {
    // À FAIRE : gérer correctement l'accès concurrent aux places sans famine
    // (Il est interdit de supprimer les appels aux fonctions ...Effectif())
    if (debug) {
      cout << "Ajout Place." << endl;
    }
    m.lock();
    nb_places++;    
    ajoutEffectif();
    c.notify_all();
    m.unlock();
  };
  void plusDePlace() {
    // À FAIRE : gérer correctement l'accès concurrent aux places sans famine
    // (Il est interdit de supprimer les appels aux fonctions ...Effectif())
    m.lock();
    fini = true;
    c.notify_all();
    m.unlock();
  };
  void nouvellesPlaces() {
    // À FAIRE : gérer correctement l'accès concurrent aux places sans famine
    // (Il est interdit de supprimer les appels aux fonctions ...Effectif())
    m.lock();
    fini = false;
    m.unlock();
  };
private:
  // À FAIRE : ajouter le nécessaire pour que la classe se comporte comme un moniteur de Hoare.
  mutex m;
  condition_variable_any c;
  int nb_places=0;
  bool fini = false;
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

mutex affichage;

/**
 * Comportement d'un thread "spectateur"
 */
void spectateur(int id, int latence, int round)
{
  usleep(latence); // Toujours la meme latence d'un round à un autre
  bool got_place = gestion_spectacle->achatSpectacle(id);

  affichage.lock();
  if (got_place){
    cout << "Le spectateur " << id << " a obtenu une place au tour " << round << endl;
  }
    else {
    cout << "Le spectateur " << id << " n'a pas obtenu de place au tour " << round << endl;
  }
  affichage.unlock();
}

/**
 * Comportement d'un thread "vendeur"
 */
void vendeur(int round)
{
  sleep(1); // On attend avant de vendre les places
  int nb_places_dispo =  nb_spectateurs / 4 + rand()%(nb_spectateurs / 2);
  affichage.lock();
  cout << nb_places_dispo << " places sont disponibles au tour " << round << endl;
  affichage.unlock();
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
      was_waiting[i] = 0;
    }

  for (int round = 0; round < nb_rounds; round++){
    // On remet en place la possibilité d'acheter des places
    gestion_spectacle->nouvellesPlaces();	    

    cout << "On lance les threads du tour " << round << endl;


    // À FAIRE : lancer nb_spectateurs threads "spectateur" et un
    // thread "vendeur", puis attendre que les threads aient terminé.

    vector<thread> v;
    v.push_back(thread(vendeur, round));
    for (int i = 0; i < nb_spectateurs; i++)
      {
	v.push_back(thread(spectateur, i, delais[i], round));
      }
    for (thread &t : v)
      {
	t.join();
      }

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

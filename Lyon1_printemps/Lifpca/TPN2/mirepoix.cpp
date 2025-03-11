// À COMPLETER : écrire ici votre nom et numéro de machine :
// Nom : ...
// Prénom : ...
// Numéro de machine : ...
#include <sys/time.h>
#include <condition_variable>
#include <iostream>
#include <mutex>
#include <sstream>
#include <string>
#include <thread>
#include <vector>
#include <math.h>
#include <unistd.h>
#include <queue>

using namespace std;

//LIGNE DE COMPILATION
//g++ mirepoix.cpp  -g -O0 -Wall -Wextra  -std=c++11  -pthread -o mirepoix

////////////////////////////////////////////
////////////////////////////////////////////
/* FONCTIONS AUXILIAIRES, NE PAS MODIFIER */
#define MASSE_MAX 19

int debug   = 0;
int nb_cars = 5;

class Verification {
public:
  void verification_tonnage() {
    if (_masse_courante > MASSE_MAX) {
      printf("TONNAGE TROP IMPORTANT !!!!\n");
      exit(1);
    }
  }

  void entree_effective(int masse, int i) {
    unique_lock<mutex> l(m);
    _masse_courante += masse;
    if (debug){
      printf("Voiture %3d: Entrée effective (masse %d)\n", i, masse);
    }
    verification_tonnage();
  }

  void sortie_effective(int masse, int i) {
    unique_lock<mutex> l(m);
    verification_tonnage();
    _masse_courante -= masse;
    if (debug){
      printf("Voiture %3d: Sortie effective (masse %d)\n", i, masse);
    }
  }
private:
  int _masse_courante = 0;
  mutex m;
};
Verification verif;
  

double timevalsub(struct timeval *tv1, const struct timeval *tv2) {
  double res = 0;
  res = tv2->tv_sec - tv1->tv_sec;
  res += (tv2->tv_usec - tv1->tv_usec)*1.0/1000000;
  return res;
}

class GestionPont {
public:
  virtual void entree(int masse, int i) = 0;
  virtual void sortie(int masse, int i) = 0;
};

class GestionPont_Seq : public GestionPont {
  void entree(int masse, int i) {
    if (debug){
      printf("Voiture %3d: Tentative d'entrée sans contrôle (masse %d)\n", i, masse);
    }
    verif.entree_effective(masse, i);
  }

  void sortie(int masse, int i) {
    if (debug){
      printf("Voiture %3d: Sortie sans contrôle\n", i);
    }
    verif.sortie_effective(masse, i);
  }
};

bool sequential;
GestionPont *gestionPont = NULL;

double loop_seq(int *attentes, int *passages, int *masses){
  double temps_total = 0;
  int i;
  for (i=0; i<nb_cars; i++){
    struct timeval tv1, tv2;
    gettimeofday(&tv1, NULL);
    usleep(attentes[i]);
    gestionPont->entree(masses[i], i);
    usleep(passages[i]);
    gestionPont->sortie(masses[i], i);
    gettimeofday(&tv2, NULL);
    double duree = timevalsub(&tv1, &tv2);
    temps_total += duree;
  }
  return temps_total;
}

/* FIN DES FONCTIONS AUXILIAIRES          */
////////////////////////////////////////////
////////////////////////////////////////////

/* À COMPLETER :
   Réponse à la question posée partie I V0 : Création des threads.
   Qu'observez-vous par rapport au programme séquentiel? Quel est le
   problème de l'approche?

   ...
*/

class GestionPont_V0 : public GestionPont {
  void entree(int masse, int i) {
    if (debug){
      printf("Voiture %3d: Tentative d'entrée parallèle V0 (masse %d)\n", i, masse);
    }
    /* À COMPLETER */
    verif.entree_effective(masse, i);
  }
  
  void sortie(int masse, int i) {
    verif.sortie_effective(masse, i);

    /* À COMPLETER */
  }
private:
  /* À COMPLETER */
};


class GestionPont_V1 : public GestionPont {
  void entree(int masse, int i) {
    if (debug){
      printf("Tentative d'entrée parallèle V1 (masse %d)\n", masse);
    }
    /* À COMPLETER */
    verif.entree_effective(masse, i);
  }
  
  void sortie(int masse, int i) {
    verif.sortie_effective(masse, i);

    /* À COMPLETER */
  }
private:
  /* À COMPLETER */
};

/* À COMPLETER
   Répondez ici à la question posée en IV Problème de famine:
   Indiquez un exemple de famine :

   ...
 */

class GestionPont_Famine : public GestionPont {
  void entree(int masse, int i) {
    if (debug){
      printf("Voiture %3d: Tentative d'entrée parallèle famine (masse %d)\n", i, masse);
    }
    /* À COMPLETER */
    verif.entree_effective(masse, i);
  }
  
  void sortie(int masse, int i) {
    verif.sortie_effective(masse, i);

    /* À COMPLETER */
  }
private:
  /* À COMPLETER */
};

void car_thread(int i, int attente, int passage, int masse, double &temps){
  struct timeval tv1, tv2;
  gettimeofday(&tv1, NULL);

  if (masse > MASSE_MAX){
    printf("Voiture %3d: Masse trop importante: %d", i, masse);
    return;
  }
  usleep(attente);
  gestionPont->entree(masse, i);
  usleep(passage);
  gestionPont->sortie(masse, i);
  gettimeofday(&tv2, NULL);
  double duree = timevalsub(&tv1, &tv2);
  temps = duree;
}

double loop_parallel(int *attentes, int *passages, int *masses){
  double temps_total = 0;

  /* À COMPLÉTER */
  return temps_total;
}

/////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////
/* Initialize command line arguments with default values */
void parse_command_line(int argc, char** argv) {
  sequential = true;
  for (int i = 1; i < argc; i++) {
    if (string(argv[i]) ==  "--nb-cars") {
      i++;
      nb_cars = stoi(argv[i]);
    } else if (string(argv[i]) ==  "--debug") {
      debug = 1;
    } else if (string(argv[i]) ==  "--para_bug") {
      gestionPont = new GestionPont_Seq();
      sequential = false;
    } else if (string(argv[i]) ==  "--para_V0") {
      gestionPont = new GestionPont_V0();
      sequential = false;
    } else if (string(argv[i]) ==  "--para_V1") {
      gestionPont = new GestionPont_V1();
      sequential = false;
    } else if (string(argv[i]) ==  "--famine") {
      gestionPont = new GestionPont_Famine();
      sequential = false;
    } else {
      cout << "ERROR: Unknown option: " << argv[i] << endl;
      exit (1);
    }
  }
  if (gestionPont == NULL) {
    gestionPont = new GestionPont_Seq();
  }
}

/* MAIN() : NE PAS MODIFIER ! */
int main(int argc, char ** argv) {
  /* lecture des arguments en ligne de commande */
  parse_command_line(argc, argv);

  int attentes[nb_cars];
  int passages[nb_cars];
  int masses[nb_cars];
  
  if (nb_cars == 5){
    attentes[0]=0;
    attentes[1]=1000;
    attentes[2]=2000;
    attentes[3]=3000;
    attentes[4]=4000;
    passages[0]=10000;
    passages[1]=10000;
    passages[2]=10000;
    passages[3]=10000;
    passages[4]=10000;
    masses[0]=10;
    masses[1]=15;
    masses[2]=5;
    masses[3]=5;
    masses[4]=MASSE_MAX;
  } else {
    int i;
    printf("Masses \n");
    for (i=0; i<nb_cars; i++){
      attentes[i] = 1+rand() % 299;
      passages[i] = 1+rand() % 299;
      masses[i]   = rand() % MASSE_MAX;
      printf("%2d ", masses[i]);
    }
    printf("\n");
  }
  double temps;
  if (sequential) {
    temps = loop_seq(attentes, passages, masses);
  } else {
    temps = loop_parallel(attentes, passages, masses);
  }
  cout << "Th principal : Le temps total de calcul est " << temps << endl;
  
  return 0;
}
/////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////

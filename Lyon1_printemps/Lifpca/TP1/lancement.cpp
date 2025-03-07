#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <sys/time.h>
#include <math.h>
#include <thread>
#include <vector> 

/**g++ thread.cpp -std=c++11 -pthread -o thread */

using namespace std;


double timevalsub(struct timeval *tv1, const struct timeval *tv2) {
  double res = 0;
  res = tv2->tv_sec - tv1->tv_sec;
  res += (tv2->tv_usec - tv1->tv_usec)*1.0/1000000;
  return res;
}

// Returns the duration of call
void fct(int num, int nbtours, double &res) {
  struct timeval tv1, tv2;
  int err;

  cout << num << " lancement de la fonction pour " << nbtours << " itérations"
  << endl;
  // #####################################
  // Partie calcul
  double temps_total = 0;
  for (int i=0; i<nbtours; i++) {
    int j;
    
    err = gettimeofday(&tv1, NULL);
    if (err != 0) {
      perror("gettimeofday");
      exit(EXIT_FAILURE);
    }

    double sum = 0;
    for(j=0; j<5000000; j++) {
      sum += log(j+1);
    }
    
    err = gettimeofday(&tv2, NULL);
    if (err != 0) {
      perror("gettimeofday");
      exit(EXIT_FAILURE);
    }
    double duree = timevalsub(&tv1, &tv2);
    temps_total += duree;

    // Version avec "cerr" si on veut voir les problèmes
    // d'entrelacement des sorties :
    // cerr << num << " : je viens de faire un calcul dont le résultat est "
    //     << sum << ", il a fallu " << duree << " secondes" << endl ;
    // fprintf ne pose pas ce problème :
    fprintf(stdout, "%d : je viens de faire un calcul dont le résultat est %g,"
	            "il a fallu %g secondes\n", num, sum, duree);
  }
  // fin de la partie calcul
  // ###########################

  res = temps_total;
}


int main(int argc, char **argv) {
  int i;
  
  // Paramètres
  int nbthreads = 10;
  int nbtours = 5;
  
  // lecture des arguments
  if ((argc==2)&&(atoi(argv[1]))) {
    // s'il y a un argument numérique on l'utilise pour
    // connaître le nombre de threads/lancements de la fonction
    nbthreads = atoi(argv[1]);
  } else if (argc != 1) {
    // il y a au moins un argument mais qui n'est pas le bon
    cerr << "usage " << argv[0] << " [<nb de lancements et de threads>]"
	 << endl;
    exit (1);
  }
  cout << "Th principal : lancement de " << nbthreads << " fois la fonction"
       << endl;
  
  vector<thread> vec_thread;
  
  vector<double> result(nbthreads);
  double temps_total = 0;

  for(int i=0; i < nbthreads; i++){
    vec_thread.push_back(thread(fct,i,nbtours, ref(result[i])));
  }
  for(int i = 0; i < nbthreads; i++){
    vec_thread[i].join();
    temps_total += result[i];

  }
  


  /*
  double temps_total = 0, temps_fonction;
  for (i=0; i<nbthreads; i++) {
    fct(i, nbtours,temps_fonction);
    temps_total += temps_fonction;
  }
  */
  

  cout << "Th principal : Le temps total de calcul est " << temps_total << endl;

  return 0;
}

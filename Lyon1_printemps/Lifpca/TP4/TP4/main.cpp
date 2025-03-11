#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <sys/time.h>
#include <math.h>
#include <mutex> 
#include <condition_variable>
#include <vector>
#include <thread>


using namespace std;

class Barriere
{
private:
    mutex m;
    condition_variable cv;
    int nombre_thread;
    int conteur;
public:
    Barriere(int n){
        conteur = 0;
        nombre_thread = n;
    }

    void wait(){
        unique_lock<mutex> lock(m);
        conteur++;
        if(conteur == nombre_thread){
            conteur = 0;
            cv.notify_all();
        }else{
            cv.wait(lock);
        }
    }
};

// Fonction pour calculer Fibonacci de manière récursive
int fibonacci(int n) {
    if (n <= 1) {
        return n;
    }else{
        return fibonacci(n - 1) + fibonacci(n - 2);
    }
}
mutex cout_mutex;
void fnct_exec_thrds(int id, int nombre_tours, Barriere &barriere){
    for(int i = 0; i < nombre_tours; i++){
        {
            //afficher l'heure actuelle
            lock_guard<mutex> lock(cout_mutex);
            time_t now = time(0);
            cout << "thread " << id << " tour " << i << " time " << ctime(&now) << endl;

        }

        //tirer un nombre aléatoire entre 10 et 20
        int x = rand() % 10 + 10; 
        {
            lock_guard<mutex> lock(cout_mutex);
            cout << "thread " << id << " tour " << i << " nombre tirer alea x est : " << x << endl;

        }

        //calculer le fibonacci de x 
        int fib = fibonacci(x);

        {
            lock_guard<mutex> lock(cout_mutex);
            cout << "thread " << id << " tour " << i << " fibonacci de x est : " << fib << endl;

        }
        
        //attendre que tous les threads finissent
        barriere.wait();
    }
}



int main(int argv, char *arvg[]) {
    int nbre_threads, nbre_tours;

    cout << "Donner le nombre de threads" << endl ;
    cin >> nbre_threads;
    cout << "Donner le nombre de tours" << endl ;
    cin >> nbre_tours;

    Barriere barrier(nbre_threads);
    vector<thread> thds;

    for (int i = 0; i < nbre_threads; i++){
        thds.push_back(thread(fnct_exec_thrds, i ,nbre_tours, std::ref(barrier)));
    }

    for(int i = 0 ; i < nbre_tours; i++){
        thds[i].join();
    }

}
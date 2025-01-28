/**g++ thread.cpp -std=c++11 -pthread -o thread */


#include <thread>
#include <iostream>
#include <mutex>
using namespace std;
#define N 100

int v = 0;
mutex m1, m2;

void incr(int &v) {
	for (int i = 0; i < N; ++i) {
		m1.lock();
		m2.lock();
		++v;
		m2.unlock();
		m1.unlock();
	}
}

void decr(int &v) {
	for (int i = 0; i < N; ++i) {
		m2.lock();
		m1.lock();
		--v;
		m1.unlock();
		m2.unlock();
	}
}


// ce programme Utilise deux mutex de manière incorrecte et peut produire un interblocage (deadlock) à l'exécution car le thread incr verrouille m1 puis m2 tandis que le thread decr verrouille m2 puis m1.
int main() {
	thread t1(incr, ref(v));
	thread t2(decr, ref(v));
	t1.join();
	t2.join();
	cout << v << endl;
}

/****************************************************************************************************************************************************************************************
 ** **************************************************************************Debut******************************************************************************************************

#include <thread>
#include <iostream>
#include <mutex>
using namespace std;
#define N 100

int v = 0;
mutex m1, m2;

void incr(int &v) {
	for (int i = 0; i < N; ++i) {
		m1.lock();
		m2.lock();
		++v;
		m2.unlock();
		m1.unlock();
	}
}

void decr(int &v) {
	for (int i = 0; i < N; ++i) {
		m1.lock();
		m2.lock();
		--v;
		m2.unlock();
		m1.unlock();
	}
}

// ce programme Utilise deux mutex, mais m2 ne sert à rien et ne change pas le comportement du programme 
int main() {
	thread t1(incr, ref(v));
	thread t2(decr, ref(v));
	t1.join();
	t2.join();
	cout << v << endl;
}

**********************************************************************Fin***********************************************************************************************************/
/********************************************************************************************************************************************************************************* */

/****************************************************************************************************************************************************************************************
 ** **************************************************************************Debut******************************************************************************************************

#include <thread>
#include <iostream>
#include <mutex>
#include <condition_variable>
#include <unistd.h>
using namespace std;

int go = false;
mutex m;
condition_variable cond_var;

void attendre() {
	cout << "Je vais attendre" << endl;
	unique_lock<mutex> l(m);
	while (go == false) {
		; // Attente active : ne rien faire tant que le flag go est faux
	}
	cout << "Je suis réveillé" << endl;
}

void reveiller() {
	sleep(1); // Attendre 1 seconde
	cout << "Je vais réveiller" << endl;
	unique_lock<mutex> l(m); // il essaie de verrouiller le mutex m et attend que le mutex soit disponible pour le verrouiller mais il est déjà verrouillé par le thread attendre 
	go = true;
}
// ce programme fait une boucle infinie car le thread attendre est en attente active et ne libère pas le verrou du mutex m pour permettre au thread reveiller de le verrouiller et de changer la valeur du flag go.
int main() {
	thread t1(attendre);
	thread t2(reveiller);
	t1.join();
	t2.join();
}

**********************************************************************Fin***********************************************************************************************************/
/********************************************************************************************************************************************************************************* */


/****************************************************************************************************************************************************************************************
 ** **************************************************************************Debut******************************************************************************************************
#include <thread>
#include <iostream>
#include <mutex>
#include <condition_variable>
#include <unistd.h>
using namespace std;

int go = false;
mutex m;
condition_variable cond_var;

void attendre() {
	cout << "Je vais attendre" << endl;
	while (go == false) {
		; // Attente active : ne rien faire tant que le flag go est faux 
	}
	cout << "Je suis réveillé" << endl;
}

void reveiller() {
	sleep(1); // Attendre 1 seconde
	cout << "Je vais réveiller" << endl;
	go = true;
}

// ce programme fait un attente active d'un tread jusqu'à ce qu'un autre thread le réveille en changeant la valeur du flag go. 
int main() {
	thread t1(attendre);
	thread t2(reveiller);
	t1.join();
	t2.join();
}

**********************************************************************Fin***********************************************************************************************************/
/********************************************************************************************************************************************************************************* */


/****************************************************************************************************************************************************************************************
 ** **************************************************************************Debut******************************************************************************************************

#include <thread>
#include <iostream>
#include <mutex>
#include <condition_variable>
#include <unistd.h>
using namespace std;

int go = false; // flag pour indiquer si le thread peut continuer ou non
mutex m;
condition_variable cond_var;// variable de condition qui permet de synchroniser les threads en attendant qu'une condition soit remplie

void attendre() {
	cout << "Je vais attendre" << endl;
	unique_lock<mutex> l(m); //unique_lock est un verrou qui peut être verrouillé et déverrouillé plusieurs fois verrouiller jusqu'à ce que le thread soit réveillé par un autre thread avec la méthode notify_one
	while (go == false) { // tant que le flag go est faux, on attend
		cond_var.wait(l); // la méthode wait permet de libérer le verrou et de mettre le thread en attente jusqu'à ce qu'il soit réveillé par un autre thread
	}
	cout << "Je suis réveillé" << endl;
}

void reveiller() {
	sleep(1); // Attendre 1 seconde
	cout << "Je vais réveiller" << endl;
	unique_lock<mutex> l(m);
	go = true;
	cond_var.notify_one();
}

// ce programme fait un attente passive d'un thread jusqu'à ce qu'un autre thread le réveille en changeant la valeur du flag go et en appelant la méthode notify_one pour réveiller le thread en attente.
int main() {
	thread t1(attendre);
	thread t2(reveiller);
	t1.join();
	t2.join();
}

**********************************************************************Fin***********************************************************************************************************/
/********************************************************************************************************************************************************************************* */


/****************************************************************************************************************************************************************************************
 ** **************************************************************************Debut******************************************************************************************************
#include <vector>
#include <thread>
#include <unistd.h>
#include <iostream>
using namespace std;

void f() {
	sleep(1); // Attendre 1 seconde pour faire dormir le thread pendant 1 seconde avant d'afficher le message suivant 
}
// ce programme se termine en 1 seconde car les threads s'exécutent en parallèle.
int main() {
	vector<thread> v;
	for (int i = 0; i < 10; i++) {
		v.push_back(thread(f)); // push_back permet d'ajouter un élément à la fin du vecteur 
        cout << "Thread " << i << " lancé" << endl;
	}
	for (int i = 0; i < 10; i++) {
		v[i].join();
	}
}
/**********************************************************************Fin***********************************************************************************************************/
/********************************************************************************************************************************************************************************* */

/***************************************************************************************************************************************************************************************
 * **************************************************************************Debut******************************************************************************************************

#include <vector>
#include <thread>
#include <unistd.h>
#include <iostream>
using namespace std;

void f() {
	sleep(1); // Attendre 1 seconde
}

int main() {
	for (int i = 0; i < 10; i++) {
		thread t(f);
        cout << "Thread " << i << " lancé" << endl;
		t.join();
	}
}

**********************************************************************Fin***********************************************************************************************************/
/********************************************************************************************************************************************************************************* */


/***************************************************************************************************************************************************************************************
 * **************************************************************************Debut******************************************************************************************************

#include <thread>
#include <iostream>
#include <mutex>
using namespace std;

int v = 0;

void incr(int &v) {
	++v;
}

void decr(int &v) {
	--v;
}
// ce programme peut afficher autre chose que 0 si les deux threads s'exécutent en parallèle car ils accèdent à la même variable v et le mutex n'est pas utilisé pour protéger la variable v des accès concurrents des deux threads.
int main() {
	mutex m;
	m.lock();
	thread t1(incr, ref(v));
	thread t2(decr, ref(v));
	t1.join();
	t2.join();
	m.unlock();
	cout << v << endl;
}

**********************************************************************Fin***********************************************************************************************************/
/********************************************************************************************************************************************************************************* */


/***************************************************************************************************************************************************************************************
 * **************************************************************************Debut******************************************************************************************************
#include <thread>
#include <iostream>
#include <mutex>
using namespace std;

int v = 0;

void incr(int &v) {
	mutex m;
	m.lock();
	++v;
	m.unlock();
}

void decr(int &v) {
	mutex m;
	m.lock();
	--v;
	m.unlock();
}
// ce programme peut afficher autre chose que 0 car la synchronisation des thraeds sont mal faite chaque thread a son propre mutex (verrou) et ne protège pas la variable v des accès concurrents des deux threads 
int main() {
	thread t1(incr, ref(v));
	thread t2(decr, ref(v));
	t1.join();
	t2.join();
	cout << v << endl;
}

**********************************************************************Fin***********************************************************************************************************/
/********************************************************************************************************************************************************************************* */


/********************************************************************************************************************************************************************************** */
/***************************************************************************Debut****************************************************************************************************** */
// Les threads sont des processus légers qui partagent la même mémoire.
/*#include <thread>
#include <iostream>
#include <mutex>
using namespace std;

int v = 0;
mutex m;

void incr(int &v) {
	m.lock();
	++v;
	m.unlock();
}

void decr(int &v) {
	m.lock();
	--v;
	m.unlock();
}
// ce programme affiche 0 car les deux threads s'exécutent en séquence et non en parallèle car ils accèdent à la même variable v et sont protégés par un mutex.
// le mutex permet de protéger la variable v des accès concurrents des deux threads et de garantir que les deux threads ne modifient pas la variable v en même temps.
int main() {
	thread t1(incr, ref(v));
	thread t2(decr, ref(v));
	t1.join();
	t2.join();
	cout << v << endl;
}

****************************************************************************Fin***************************************************************************************************** */
/********************************************************************************************************************************************************************************* */

/***************************************************************************************************************************************************************************************
 * **************************************************************************Debut******************************************************************************************************
#include <thread>
#include <iostream>
using namespace std;

int v = 0;

void incr(int &v) {
	++v;
}

void decr(int &v) {
	--v;
}

// ce programme peut afficher autre chose que 0 si les deux threads s'exécutent en parallèle car ils accèdent à la même variable v.

int main() {
	thread t1(incr, ref(v));
	thread t2(decr, ref(v));
	t1.join();
	t2.join();
	cout << v << endl;
}
**********************************************************************Fin***********************************************************************************************************/
/********************************************************************************************************************************************************************************* */
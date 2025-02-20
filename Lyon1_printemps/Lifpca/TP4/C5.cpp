#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <sys/time.h>
#include <math.h>
#include <thread>
#include <mutex> 
#include <condition_variable>

using namespace std;

mutex m;
condition_variable c;
bool verif1 = false;
bool verif2 = false;

void func_A1(){
    m.lock();
    cout << "I am A1 I should finish before B starts" << endl;
    verif1 = true;
    c.notify_all();
    m.unlock();
}

void func_A2(){
  m.lock();
  cout << "I am A2 I should finish before B starts" << endl;
  verif2= true;
  c.notify_all();
  m.unlock();
}

void func_B(){

  unique_lock l(m);
  while(!verif1 || !verif2 )
 {
    c.wait(l);
   }
  cout << "I am B I should start after A1 and A2 finish" << endl;
  
  cout << "ok";
}


int main(int argv, char *arvg[]) {
  std::thread A1 = thread(func_A1);
  std::thread A2 = thread(func_A2);
  std::thread B  = thread(func_B);

  A1.join();
  A2.join();
  B.join();
  return 0;
}

// La solution est-elle facilement généralisable au cas n threads ?
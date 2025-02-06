#ifndef PROD_CONS_H
#define PROD_CONS_H

#include <queue>
#include <mutex>
#include <condition_variable>


using namespace std;


template <class T>

class prod_conso{
    private: 
        std::queue<T> buf;
        std::mutex mtx; 
        std::condition_variable cv_prod, cv_cons; 
        int max_size;

    public:
    prod_conso(int taille_max){
        max_size = taille_max;
    };

    void put(T elm){
        std::unique_lock<mutex> l(mtx);
        while( buf.size() == max_size ){
            cv_prod.wait(l);
        }
        
        buf.push(elm);
        cv_cons.notify_one();
    }
    T get(){
        std::unique_lock<mutex> l(mtx);
        while(buf.empty()){
        cv_cons.wait(l);
        }
        T res = buf.front();
        buf.pop();
        cv_prod.notify_one();
        return res;

    }
};

#endif 
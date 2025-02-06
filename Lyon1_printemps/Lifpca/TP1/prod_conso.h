#ifndef PROD_CONS_H
#define PROD_CONS_H

#include <queue>
#include <mutex>
#include <condition_variable>

// Structure représentant un rectangle à afficher
struct rect {
    int slice_number; // Numéro de la tranche
    int y_start;      // Position en y du début du rectangle
    rect(int sn, int y) : slice_number(sn), y_start(y) {}
};

// Classe ProdCons implémentant un buffer de type producteur-consommateur
class ProdCons {
private:
    std::queue<rect> buffer; // File d'attente FIFO des rectangles
    std::mutex mtx; // Mutex pour protéger l'accès à la file
    std::condition_variable cv_producer, cv_consumer; // Variables de condition pour la synchronisation
    size_t max_size; // Taille maximale du buffer

public:
    // Constructeur avec taille maximale du buffer
    ProdCons(size_t size) : max_size(size) {}

    // Méthode pour insérer un élément dans la file (bloquante si la file est pleine)
    void put(const rect& r) {
        std::unique_lock<std::mutex> lock(mtx);
        cv_producer.wait(lock, [this] { return buffer.size() < max_size; }); // Attendre s'il n'y a plus de place
        buffer.push(r); // Ajouter l'élément
        cv_consumer.notify_one(); // Réveiller un consommateur
    }

    // Méthode pour récupérer un élément de la file (bloquante si la file est vide)
    rect get() {
        std::unique_lock<std::mutex> lock(mtx);
        cv_consumer.wait(lock, [this] { return !buffer.empty(); }); // Attendre si la file est vide
        rect r = buffer.front(); // Récupérer l'élément en tête
        buffer.pop(); // Supprimer l'élément de la file
        cv_producer.notify_one(); // Réveiller un producteur
        return r;
    }
};

#endif // PROD_CONS_H
/*
Pour intégrer la classe ProdCons dans ton code principal, voici les étapes :

Inclure ProdCons dans le fichier principal
→ Ajoute #include "prodcons.h" en haut du fichier contenant main().

Créer une instance de ProdCons
→ Dans main(), crée un objet ProdCons avec une taille maximale du buffer (ex. number_of_slices).

Modifier les threads de calcul (draw_screen_worker)
→ Remplacer draw_rect_thread_safe(slice_number, y); par prod_cons.put(rect(slice_number, y));.

Créer un thread d’affichage
→ Ajouter un thread consommateur qui récupère les rectangles de ProdCons et appelle draw_rect().

*/
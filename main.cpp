#include "mbed.h"

// LED pour la boucle principale
DigitalOut led(LED1);

// Mutex pour synchroniser les threads
Mutex mutex_ping_pong;

// Fonction pour afficher "Ping"
void ping() {
    /*for (int i = 0; i < 100; i++) {
        mutex_ping_pong.lock(); // Verrouiller avant l'accès partagé
        printf("Ping\n");
        mutex_ping_pong.unlock(); // Déverrouiller pour permettre à "Pong" de s'exécuter
        ThisThread::sleep_for(10ms); // Petite pause pour simuler un délai
    }*/
    while (true) {
        mutex_ping_pong.lock(); // Verrouiller avant l'accès partagé
        printf("Ping\n");
        mutex_ping_pong.unlock(); // Déverrouiller pour permettre à "Pong" de s'exécuter
        ThisThread::sleep_for(250ms); // Petite pause pour simuler un délai
    }
}

// Fonction pour afficher "Pong"
void pong() {
    /*for (int i = 0; i < 100; i++) {
        mutex_ping_pong.lock(); // Verrouiller avant l'accès partagé
        printf("Pong\n");
        mutex_ping_pong.unlock(); // Déverrouiller pour permettre à "Ping" de s'exécuter
        ThisThread::sleep_for(10ms); // Petite pause pour simuler un délai
    }*/
    while (true) {
        mutex_ping_pong.lock(); // Verrouiller avant l'accès partagé
        printf("Pong\n");
        mutex_ping_pong.unlock(); // Déverrouiller pour permettre à "Ping" de s'exécuter
        ThisThread::sleep_for(250ms); // Petite pause pour simuler un délai
    }
}

int main() {
    // Création des threads
    Thread thread_ping;
    Thread thread_pong;

    // Démarrage des threads
    thread_ping.start(ping);
    thread_pong.start(pong);

    // Boucle principale
    while (true) {
        led = !led; // Inverser l'état de la LED
        mutex_ping_pong.lock(); // Verrouiller avant l'accès partagé
        printf("Alive!\n");
        mutex_ping_pong.unlock(); // Déverrouiller pour permettre à "Ping" de s'exécuter
        ThisThread::sleep_for(500ms); // Attendre 500 ms avant le prochain clignotement
    }
}

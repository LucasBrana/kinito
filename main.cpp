#include "mbed.h"

// LED pour la boucle principale
DigitalOut led(LED1);

// Mutex pour synchroniser les threads
Mutex mutex_ping_pong;

// Fonction pour afficher "Ping"
void ping() {
    while (true) {
        mutex_ping_pong.lock(); // Verrouiller avant l'accès partagé
        printf("Ping\n");
        mutex_ping_pong.unlock(); // Déverrouiller pour permettre à "Pong" de s'exécuter
        ThisThread::sleep_for(250ms); // Petite pause pour simuler un délai
    }
}

// Fonction pour afficher "Pong"
void pong() {
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

    // Définir les priorités des threads
    thread_ping.set_priority(osPriorityAboveNormal); // Ping : Priorité au-dessus de la normale
    thread_pong.set_priority(osPriorityNormal);      // Pong : Priorité normale
    // La boucle principale conserve sa priorité par défaut (osPriorityNormal)

    // Boucle principale
    while (true) {
        led = !led; // Inverser l'état de la LED
        mutex_ping_pong.lock(); // Verrouiller avant l'accès partagé
        printf("Alive!\n");
        mutex_ping_pong.unlock(); // Déverrouiller pour permettre à "Ping" ou "Pong" de s'exécuter
        ThisThread::sleep_for(500ms); // Attendre 500 ms avant le prochain clignotement
    }
}

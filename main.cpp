#include "mbed.h"

// LED pour la boucle principale
DigitalOut led(LED1);

// Fonction pour afficher "Ping" 100 fois
void ping() {
    for (int i = 0; i < 100; i++) {
        printf("Ping\n");
        ThisThread::sleep_for(10ms);
    }
}

// Fonction pour afficher "Pong" 100 fois
void pong() {
    for (int i = 0; i < 100; i++) {
        printf("Pong\n");
        ThisThread::sleep_for(10ms);
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
        printf("Alive!\n");
        ThisThread::sleep_for(500ms); // Attendre 500 ms avant le prochain clignotement
    }
}

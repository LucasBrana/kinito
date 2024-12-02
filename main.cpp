/*
 * Copyright (c) 2022, CATIE
 * SPDX-License-Identifier: Apache-2.0
 */
#include "mbed.h"

// Déclaration d'une LED connectée à une broche spécifique
DigitalOut led(LED1);

// Déclaration d'un bouton avec interruption
InterruptIn button(BUTTON1); // Remplacez BUTTON1 par la broche correspondante si nécessaire

// Déclaration du Timer
Timer button_timer;

// Déclaration d'une queue d'événements
EventQueue queue;

// Variable pour stocker la durée de l'appui
chrono::milliseconds duration;

// Fonction déclenchée lors de l'appui sur le bouton
void on_button_released() {
    led = 0; // Éteindre la LED
    button_timer.stop(); // Arrêter le Timer
    duration = chrono::duration_cast<chrono::milliseconds>(button_timer.elapsed_time());
    button_timer.reset(); // Réinitialiser le Timer

    // Planifier l'affichage de la durée via la queue
    queue.call([]() {
        printf("Button pressed duration: %lld ms\n", duration.count());
    });
}

// Fonction déclenchée lors du relâchement du bouton
void on_button_pressed() {
    button_timer.start(); // Démarrer le Timer

    led = 1; // Allumer la LED
}

int main()
{
    // Associer les interruptions à leurs fonctions respectives
    button.fall(&on_button_released);
    button.rise(&on_button_pressed); 

    // Démarrer la queue d'événements
    Thread event_thread;
    event_thread.start(callback(&queue, &EventQueue::dispatch_forever));

    // Boucle principale
    while (true) {
        ThisThread::sleep_for(1s); // Simulation d'une tâche de fond
    }
}

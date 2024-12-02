/*
 * Copyright (c) 2022, CATIE
 * SPDX-License-Identifier: Apache-2.0
 */
#include "mbed.h"

// Déclaration d'une LED connectée à une broche spécifique
DigitalOut led(LED1);

// Déclaration d'un bouton avec interruption
InterruptIn button(BUTTON1);

// Déclaration d'un Ticker
Ticker led_ticker;

// Déclaration d'une queue d'événements
EventQueue queue;

// Tableau des fréquences (en millisecondes)
chrono::milliseconds frequencies[] = {100ms, 200ms, 500ms, 1000ms};
int frequency_index = 0;

// Fonction pour alterner l'état de la LED
void toggle_led() {
    led = !led;
}

// Fonction appelée dans l'ISR pour changer la fréquence
void schedule_change_frequency() {
    queue.call([]() {
        // Passer à la fréquence suivante dans le tableau
        frequency_index = (frequency_index + 1) % (sizeof(frequencies) / sizeof(frequencies[0]));

        // Reconfigurer le Ticker avec la nouvelle fréquence
        led_ticker.detach();
        led_ticker.attach(&toggle_led, frequencies[frequency_index]);

        // Afficher la nouvelle fréquence sur la sortie standard
        printf("New frequency: %lld ms\n", frequencies[frequency_index].count());
    });
}

int main()
{
    // Configurer le Ticker avec la première fréquence
    led_ticker.attach(&toggle_led, frequencies[frequency_index]);

    // Configurer l'interruption pour le bouton
    button.fall(&schedule_change_frequency);

    // Démarrer la queue d'événements dans un thread séparé
    Thread event_thread;
    event_thread.start(callback(&queue, &EventQueue::dispatch_forever));

    // Boucle principale vide
    while (true) {
        ThisThread::sleep_for(1s);
    }
}

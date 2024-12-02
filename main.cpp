/*
 * Copyright (c) 2022, CATIE
 * SPDX-License-Identifier: Apache-2.0
 */
#include "mbed.h"

// Déclaration d'une LED connectée à une broche spécifique
DigitalOut led(LED1);

// Déclaration d'un bouton avec interruption
InterruptIn button(BUTTON1); 

void on_button_pressed() {
    led = !led;
}

int main()
{
    // Attacher une interruption pour détecter un appui sur le bouton
    button.fall(&on_button_pressed); // Déclenche sur un front descendant (bouton pressé)

    // Boucle principale (vide, car tout est géré par interruption)
    while (true) {
        // L'application principale peut effectuer d'autres tâches
        ThisThread::sleep_for(1s); // Simulation d'une tâche de fond
    }
}

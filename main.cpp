/*
 * Copyright (c) 2022, CATIE
 * SPDX-License-Identifier: Apache-2.0
 */
#include "mbed.h"

namespace {
#define PERIOD_MS 1000ms
}

int main()
{
    // Déclaration d'une LED connectée à une broche spécifique
    DigitalOut led(LED1); // LED1 est généralement une LED intégrée à la carte

    // Déclaration d'un bouton connecté à une broche spécifique
    DigitalIn button(BUTTON1); // USER_BUTTON est une macro standard pour le bouton utilisateur intégré (remplacez par la broche si nécessaire)

    while (true) {
        // Lire l'état du bouton
        int button_state = button.read(); // 0 = bouton non appuyé, 1 = bouton appuyé

        // Afficher l'état du bouton sur la sortie standard
        printf("Button state: %d\n", button_state);

        // Allumer la LED si le bouton est appuyé, sinon l'éteindre
        if (button_state == 1) {
            led = 1; // Allumer la LED
        } else {
            led = 0; // Éteindre la LED
        }

        // Petit délai pour limiter la fréquence du polling
        ThisThread::sleep_for(100ms);
    }
}

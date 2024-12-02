/*
 * Copyright (c) 2022, CATIE
 * SPDX-License-Identifier: Apache-2.0
 */
#include "mbed.h"

namespace {
#define PERIOD_MS 2000ms
}

int main()
{
    // Déclaration d'une LED connectée à une broche spécifique
    DigitalOut led(LED1); // LED1 est généralement une LED intégrée à la carte

    while (true) {
        led = 1; // Allumer la LED
        ThisThread::sleep_for(PERIOD_MS / 2); // Attendre la moitié de la période
        led = 0; // Éteindre la LED
        ThisThread::sleep_for(PERIOD_MS / 2); // Attendre l'autre moitié de la période
    }
}

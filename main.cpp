/*
 * Copyright (c) 2022, CATIE
 * SPDX-License-Identifier: Apache-2.0
 */
#include "mbed.h"

// Déclaration d'une LED connectée à une broche spécifique
DigitalOut led(LED1);

// Déclaration d'un Ticker
Ticker led_ticker;

// Fonction pour alterner l'état de la LED
void toggle_led() {
    led = !led; // Inverser l'état de la LED
}

int main()
{
    led_ticker.attach(&toggle_led, 500ms);
}

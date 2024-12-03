/*
 * Copyright (c) 2022, CATIE
 * SPDX-License-Identifier: Apache-2.0
 */
#include "mbed.h"
#include "bme280.h"

using namespace sixtron;

// Initialisation de l'I2C et du capteur BME280
I2C i2c(I2C1_SDA, I2C1_SCL);
BME280 bme280(&i2c, BME280::I2CAddress::Address1);

DigitalOut led(LED1);

int main() {
    printf("Initializing BME280...\n");

    // Initialisation du capteur
    if (!bme280.initialize()) {
        printf("Error: Failed to initialize BME280\n");
        return 1;
    }
    printf("BME280 initialized successfully\n");

    // Configuration des paramètres de mesure
    bme280.set_sampling(
        BME280::SensorMode::NORMAL,
        BME280::SensorSampling::OVERSAMPLING_X1,   // Température
        BME280::SensorSampling::OVERSAMPLING_X1,   // Pression
        BME280::SensorSampling::OVERSAMPLING_X1,   // Humidité
        BME280::SensorFilter::OFF, 
        BME280::StandbyDuration::MS_0_5
    );

    while (true) {
        led = 1;

        // Lire les données environnementales
        float temperature = bme280.temperature();
        float humidity = bme280.humidity();
        float pressure = bme280.pressure();

        // Afficher les données sur le terminal
        printf("Temperature: %.2f °C\n", temperature);
        printf("Humidity: %.2f %%\n", humidity);
        printf("Pressure: %.2f hPa\n", pressure);

        led = 0;
        ThisThread::sleep_for(1s);
    }
}
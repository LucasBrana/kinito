#include "mbed.h"
#include "bme280.h"

using namespace sixtron;

// Initialisation de l'I2C et du capteur BME280
I2C i2c(I2C1_SDA, I2C1_SCL);
BME280 bme280(&i2c, BME280::I2CAddress::Address1);

// LED et bouton
DigitalOut led(LED1);
InterruptIn button(BUTTON1);

// Ticker pour les tâches périodiques
Ticker ticker_led;
Ticker ticker_temperature_humidity;

// Queue pour gérer les événements
EventQueue queue;

// Fonction pour clignoter la LED toutes les 5s
void toggle_led() {
    led = !led;
    printf("LED toggled\n");
}

// Fonction pour afficher température et humidité toutes les 2s
void display_temperature_humidity() {
    float temperature = bme280.temperature();
    float humidity = bme280.humidity();
    printf("Temperature: %.2f °C\n", temperature);
    printf("Humidity: %.2f %%\n", humidity);
}

// Fonction pour afficher la pression en appuyant sur le bouton
void display_pressure() {
    queue.call([]() {
        float pressure = bme280.pressure();
        printf("Pressure: %.2f hPa\n", pressure);
    });
}

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

    // Configurer les tickers
    ticker_led.attach(queue.event(toggle_led), 5s);                      
    ticker_temperature_humidity.attach(queue.event(display_temperature_humidity), 2s); 

    // Configurer l'interruption du bouton
    button.rise(queue.event(display_pressure)); 

    // Démarrer la queue
    queue.dispatch_forever();
}

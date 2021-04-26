/*
Sensor module
*/

#include "configuration.h"

#if not SENSOR_USE_DUMMY
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
Adafruit_BME280 _sensor;
#endif

// Returns the temperature in C
float getTemperature() {
    #if SENSOR_USE_DUMMY
        return (float) random(100, 300) / 10.0;
    #else
        return (float) _sensor.readTemperature();
    #endif
}

// Returns the himidity in %
float getHumidity() {
    #if SENSOR_USE_DUMMY
        return (float) random(30, 90);
    #else
        return (float) _sensor.readHumidity();
    #endif
}

// Returns the pressure in hPa
float getPressure() {
    #if SENSOR_USE_DUMMY
        return (float) random(9800, 10300) / 10.0;
    #else
        return (float) _sensor.readPressure() / 100.0F;
    #endif
}

void sensorSetup() {
    #if SENSOR_USE_DUMMY
        randomSeed(analogRead(A0));
    #else
        if (!_sensor.begin(SENSOR_BME280_ADDRESS)) {
            DEBUG_MSG("[SENSOR] Could not find a valid BME280 sensor, check wiring!\n");
            while (1) delay(10);
        }
        DEBUG_MSG("[SENSOR] Sensor ready!\n");
    #endif
}

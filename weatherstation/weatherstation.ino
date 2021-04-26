/*

SIMPLE EXAMPLE FOR TTGO/HELTEC-LORA32

Copyright (C) 2018-2021 by Xose Pérez <xose dot perez at gmail dot com>

This sketch requires LMIC library by Matthijs Kooijman
https://github.com/matthijskooijman/arduino-lmic

Tested on TTGO-LORA32-V10 & HELTEC-LORA32-V1

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/

#include "configuration.h"
#include <rom/rtc.h>
#include "CayenneLPP.h"
#include <Wire.h>

// -----------------------------------------------------------------------------
// Configuration
// -----------------------------------------------------------------------------

// Message counter, stored in RTC memory, survives deep sleep
RTC_DATA_ATTR uint32_t count = 0;
CayenneLPP lpp(16);

// -----------------------------------------------------------------------------
// Application
// -----------------------------------------------------------------------------

unsigned char msb(float value) {
    return (int(value) >> 8) & 0xFF;
}

unsigned char lsb(float value) {
    return int(value) & 0xFF;
}

void send() {

    // Payload
    lpp.reset();
    lpp.addTemperature(1, getTemperature());
    lpp.addRelativeHumidity(2, getHumidity());
    lpp.addBarometricPressure(3, getPressure());
   
    #if LORAWAN_CONFIRMED_EVERY
        bool confirmed = (count % LORAWAN_CONFIRMED_EVERY == 0);
    #else
        bool confirmed = false;
    #endif
    ttn_send(lpp.getBuffer(), lpp.getSize(), LORAWAN_PORT, confirmed);

    count++;

}

void callback(uint8_t message) {

    if (EV_JOINING == message) screenPrint("[TTN] Joining...\n");
    if (EV_JOINED == message) screenPrint("[TTN] Joined!\n");
    if (EV_JOIN_FAILED == message) screenPrint("[TTN] Join failed\n");
    if (EV_REJOIN_FAILED == message) screenPrint("[TTN] Rejoin failed\n");
    if (EV_RESET == message) screenPrint("[TTN] Reset\n");
    if (EV_LINK_DEAD == message) screenPrint("[TTN] Link dead\n");
    if (EV_ACK == message) screenPrint("[TTN] ACK received\n");
    if (EV_PENDING == message) screenPrint("[TTN] Message discarded\n");
    if (EV_ERROR == message) screenPrint("[TTN] Error sending\n");
    //if (EV_QUEUED == message) screenPrint("[TTN] Message queued\n");

    if (EV_TXCOMPLETE == message) {
        screenPrint("[TTN] Message sent\n");
    }

    if (EV_RESPONSE == message) {

        screenPrint("[TTN] Response: ");

        size_t len = ttn_response_len();
        uint8_t data[len];
        ttn_response(data, len);

        char buffer[6];
        for (uint8_t i=0; i<len; i++) {
            snprintf(buffer, sizeof(buffer), "0x%02X ", data[i]);
            screenPrint(buffer);
        }

        screenPrint("\n");

    }

}

// -----------------------------------------------------------------------------
// Main methods
// -----------------------------------------------------------------------------

void setup() {

    // Init serial port for debugging
    #ifdef DEBUG_PORT
        DEBUG_PORT.begin(SERIAL_BAUD);
    #endif

    // I2C
    i2cSetup();
    i2cScan();

    // Screen
    screenSetup();
    screenPrint("WEATHER STATION\n");

    // Sensor
    sensorSetup();

    // TTN setup
    if (!ttn_setup()) {
        screenPrint("[MAIN] Could not find the radio module!\n");
        while (true);
    }
    ttn_register(callback);
    ttn_join();
    ttn_sf(LORAWAN_SF);
    ttn_adr(LORAWAN_ADR);

}

void loop() {

    // Send every TX_INTERVAL millis
    static uint32_t last = 0;
    if (0 == last || millis() - last > TX_INTERVAL) {
        last = millis();
        send();
    }

    ttn_loop();

}

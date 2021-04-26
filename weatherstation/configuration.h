/*

TTGO-LORA32 based TTN Node

Copyright (C) 2018-2021 by Xose Pérez <xose dot perez at gmail dot com>

This code requires LMIC library by Matthijs Kooijman
https://github.com/matthijskooijman/arduino-lmic

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

#pragma once

#include <Arduino.h>
#include <lmic.h>

// Copy and rename credentials.sample.h to credentials.h
// and configure it with your node settings
#include "credentials.h"

void ttn_register(void (*callback)(uint8_t message));

// -----------------------------------------------------------------------------
// Configuration
// -----------------------------------------------------------------------------

#define DEBUG_PORT              Serial      // Serial debug port
#define SERIAL_BAUD             115200      // Serial debug baud rate
#define TX_INTERVAL             20000       // Send message every these many millis
#define LORAWAN_PORT            1           // Port the messages will be sent to
#define LORAWAN_CONFIRMED_EVERY 0           // Send confirmed message every these many messages (0 means never)
#define LORAWAN_SF              DR_SF7      // Spreading factor
#define LORAWAN_ADR             0           // Enable ADR

// -----------------------------------------------------------------------------
// DEBUG
// -----------------------------------------------------------------------------

#ifdef DEBUG_PORT
#define DEBUG_MSG(...) DEBUG_PORT.printf( __VA_ARGS__ )
#else
#define DEBUG_MSG(...)
#endif

// -----------------------------------------------------------------------------
// Custom messages
// -----------------------------------------------------------------------------

#define EV_QUEUED               100
#define EV_PENDING              101
#define EV_ACK                  102
#define EV_RESPONSE             103
#define EV_ERROR                104

// -----------------------------------------------------------------------------
// Hardware
// -----------------------------------------------------------------------------

//#define TTGO_LORA32 // https://www.thethingsnetwork.org/forum/t/big-esp32-sx127x-topic-part-2/11973
#define HELTEC_LORA32_V1
//#define HELTEC_LORA32_V2

// -----------------------------------------------------------------------------
// LoRa (SPI)
// -----------------------------------------------------------------------------

#ifdef TTGO_LORA32
    #define SCK_GPIO            5
    #define MISO_GPIO           19
    #define MOSI_GPIO           27
    #define NSS_GPIO            18
    #define RESET_GPIO          14
    #define DIO0_GPIO           26
    #define DIO1_GPIO           33
    #define DIO2_GPIO           32
#endif

#ifdef HELTEC_LORA32_V1
    #define SCK_GPIO            5
    #define MISO_GPIO           19
    #define MOSI_GPIO           27
    #define NSS_GPIO            18
    #define RESET_GPIO          14
    #define DIO0_GPIO           26
    #define DIO1_GPIO           33
    #define DIO2_GPIO           32
#endif

#ifdef HELTEC_LORA32_V2
    #define SCK_GPIO            5
    #define MISO_GPIO           19
    #define MOSI_GPIO           27
    #define NSS_GPIO            18
    #define RESET_GPIO          14
    #define DIO0_GPIO           26
    #define DIO1_GPIO           35
    #define DIO2_GPIO           34
#endif

#define SDA_GPIO                4
#define SCL_GPIO                15

// -----------------------------------------------------------------------------
// Display (I2C)
// -----------------------------------------------------------------------------

#define DISPLAY_RESET           16

// -----------------------------------------------------------------------------
// LEDs
// -----------------------------------------------------------------------------
#define LED_GPIO                2

// -----------------------------------------------------------------------------
// Sensor
// -----------------------------------------------------------------------------

#define SENSOR_USE_DUMMY        0
#define SENSOR_BME280_ADDRESS   0x76


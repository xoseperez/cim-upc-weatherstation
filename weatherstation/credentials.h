/*

Credentials file

*/

#pragma once

// Only one of these settings must be defined at the same time
//#define USE_ABP
#define USE_OTAA // OTAA not working ATM

#ifdef USE_ABP

    // LoRaWAN NwkSKey, network session key (LSB)
    static const u1_t PROGMEM NWKSKEY[16] = { 0x90, 0xAA, 0x0B, 0xCD, 0x8D, 0xB1, 0x46, 0x8D, 0x94, 0xC1, 0x9B, 0x01, 0x73, 0x9D, 0xBB, 0x67 };

    // LoRaWAN AppSKey, application session key (LSB)
    static const u1_t PROGMEM APPSKEY[16] = { 0xB1, 0x11, 0x4A, 0xAF, 0x0D, 0x2F, 0x88, 0x4D, 0xB0, 0x8F, 0x1D, 0x5C, 0xBF, 0x5A, 0xF6, 0xE4 };

    // LoRaWAN end-device address (DevAddr)
    // This has to be unique for every node
    static const u4_t DEVADDR             = 0x260B3589;

#endif

#ifdef USE_OTAA

    // This EUI must be in little-endian format, so least-significant-byte
    // first (LSB). When copying an EUI from ttnctl output, this means to reverse
    // the bytes. For TTN issued EUIs the last bytes should be 0xD5, 0xB3,
    // 0x70.
    static const u1_t PROGMEM APPEUI[8]  = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };

    // This should also be in little endian format (LSB), see above.
    static const u1_t PROGMEM DEVEUI[8]  = { 0x00, 0x05, 0xF4, 0xBE, 0xE1, 0x36, 0x06, 0x22 };

    // This key should be in big endian format (or, since it is not really a
    // number but a block of memory, endianness does not really apply). In
    // practice, a key taken from ttnctl can be copied as-is.
    // The key shown here is the semtech default key.
    static const u1_t PROGMEM APPKEY[16] = { 0x63, 0xDE, 0xA1, 0xD7, 0x18, 0x81, 0x6A, 0x99, 0x48, 0x6D, 0x14, 0x95, 0x3F, 0x47, 0x94, 0xD2 };

#endif

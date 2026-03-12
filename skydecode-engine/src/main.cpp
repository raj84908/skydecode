#include <cstdint>
#include <iomanip>
#include <iostream>
#include <string>

#include "decoder/adsb_decoder.h"

int main() {
    const std::string raw = "8D4840D6202CC371C32CE0576098";

    std::cout << "ADS-B message: " << raw << "\n\n";

    const auto bytes = skydecode::hexToBytes(raw);
    const uint8_t* data = bytes.data();

    // ADS-B field layout (bits are 1-indexed, MSB-first):
    //   Bits  1-5  : Downlink Format (DF)
    //   Bits  6-8  : Capability (CA)
    //   Bits  9-32 : ICAO 24-bit address
    //   Bits 33-37 : Type Code (TC)  — first field of the ME payload

    const uint32_t df   = skydecode::extractBits(data,  1, 5);
    const uint32_t icao = skydecode::extractBits(data,  9, 24);
    const uint32_t tc   = skydecode::extractBits(data, 33, 5);

    std::cout << std::dec;
    std::cout << "Downlink Format (DF): " << df << "\n";
    std::cout << "ICAO Address       : "
              << std::uppercase << std::hex << std::setw(6) << std::setfill('0') << icao
              << " (" << std::dec << icao << ")\n";
    std::cout << "Type Code (TC)     : " << tc << "\n";

    // Expected: DF=17 (ADS-B), ICAO=0x4840D6 (4735190), TC=4 (airborne position, barometric alt)
    return 0;
}

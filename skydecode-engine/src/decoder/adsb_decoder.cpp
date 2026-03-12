#include "decoder/adsb_decoder.h"

#include <stdexcept>

namespace skydecode {

std::vector<uint8_t> hexToBytes(const std::string& hex) {
    if (hex.size() % 2 != 0) {
        throw std::invalid_argument("Hex string must have an even number of characters");
    }

    std::vector<uint8_t> bytes;
    bytes.reserve(hex.size() / 2);

    for (size_t i = 0; i < hex.size(); i += 2) {
        auto nibble = [](char c) -> uint8_t {
            if (c >= '0' && c <= '9') return static_cast<uint8_t>(c - '0');
            if (c >= 'A' && c <= 'F') return static_cast<uint8_t>(c - 'A' + 10);
            if (c >= 'a' && c <= 'f') return static_cast<uint8_t>(c - 'a' + 10);
            throw std::invalid_argument(std::string("Invalid hex character: ") + c);
        };
        bytes.push_back(static_cast<uint8_t>((nibble(hex[i]) << 4) | nibble(hex[i + 1])));
    }

    return bytes;
}

uint32_t extractBits(const uint8_t* data, int startBit, int numBits) {
    // startBit is 1-indexed; bits are ordered MSB-first within each byte.
    uint32_t result = 0;
    for (int i = 0; i < numBits; ++i) {
        int bitIndex  = startBit - 1 + i;        // 0-indexed absolute bit position
        int byteIndex = bitIndex / 8;
        int bitShift  = 7 - (bitIndex % 8);      // shift within byte (MSB = shift 7)
        result = (result << 1) | ((data[byteIndex] >> bitShift) & 1u);
    }
    return result;
}

} // namespace skydecode

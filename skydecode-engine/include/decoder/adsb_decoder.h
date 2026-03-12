#pragma once

#include <cstdint>
#include <string>
#include <vector>

namespace skydecode {

// Converts a hex string (e.g. "8D4840D6202CC371C32CE0576098") to raw bytes.
std::vector<uint8_t> hexToBytes(const std::string& hex);

// Extracts numBits bits starting at startBit (1-indexed, MSB-first) from data.
// Returns the extracted value as a uint32_t.
uint32_t extractBits(const uint8_t* data, int startBit, int numBits);

} // namespace skydecode

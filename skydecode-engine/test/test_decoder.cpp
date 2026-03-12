#include <catch2/catch_test_macros.hpp>

#include "decoder/adsb_decoder.h"

// ── hexToBytes ────────────────────────────────────────────────────────────────

TEST_CASE("hexToBytes converts known ADS-B message", "[hexToBytes]") {
    const auto bytes = skydecode::hexToBytes("8D4840D6202CC371C32CE0576098");
    REQUIRE(bytes.size() == 14);
    CHECK(bytes[0]  == 0x8D);
    CHECK(bytes[1]  == 0x48);
    CHECK(bytes[2]  == 0x40);
    CHECK(bytes[3]  == 0xD6);
    CHECK(bytes[13] == 0x98);
}

TEST_CASE("hexToBytes handles lowercase hex", "[hexToBytes]") {
    const auto bytes = skydecode::hexToBytes("8d4840d6");
    REQUIRE(bytes.size() == 4);
    CHECK(bytes[0] == 0x8D);
    CHECK(bytes[3] == 0xD6);
}

TEST_CASE("hexToBytes throws on odd-length input", "[hexToBytes]") {
    CHECK_THROWS_AS(skydecode::hexToBytes("ABC"), std::invalid_argument);
}

TEST_CASE("hexToBytes throws on invalid character", "[hexToBytes]") {
    CHECK_THROWS_AS(skydecode::hexToBytes("ZZ"), std::invalid_argument);
}

// ── extractBits ───────────────────────────────────────────────────────────────

TEST_CASE("extractBits extracts Downlink Format (bits 1-5) == 17", "[extractBits]") {
    const auto bytes = skydecode::hexToBytes("8D4840D6202CC371C32CE0576098");
    const uint32_t df = skydecode::extractBits(bytes.data(), 1, 5);
    CHECK(df == 17);
}

TEST_CASE("extractBits extracts ICAO address (bits 9-32) == 0x4840D6", "[extractBits]") {
    const auto bytes = skydecode::hexToBytes("8D4840D6202CC371C32CE0576098");
    const uint32_t icao = skydecode::extractBits(bytes.data(), 9, 24);
    CHECK(icao == 0x4840D6u);
}

TEST_CASE("extractBits extracts Type Code (bits 33-37) == 4", "[extractBits]") {
    const auto bytes = skydecode::hexToBytes("8D4840D6202CC371C32CE0576098");
    const uint32_t tc = skydecode::extractBits(bytes.data(), 33, 5);
    CHECK(tc == 4);
}

TEST_CASE("extractBits single-byte boundary: first byte 0x8D", "[extractBits]") {
    const uint8_t data[] = {0x8D};
    // Full byte should equal 0x8D
    CHECK(skydecode::extractBits(data, 1, 8) == 0x8Du);
    // Top nibble: 1000 = 8
    CHECK(skydecode::extractBits(data, 1, 4) == 8u);
    // Bottom nibble: 1101 = 13
    CHECK(skydecode::extractBits(data, 5, 4) == 13u);
}

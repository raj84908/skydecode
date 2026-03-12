cmake_minimum_required(VERSION 3.21)
project(skydecode-engine VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(MSVC)
    add_compile_options(/W4 /utf-8)
endif()

# ── Dependencies ──────────────────────────────────────────────────────────────

include(FetchContent)

FetchContent_Declare(
    nlohmann_json
    GIT_REPOSITORY https://github.com/nlohmann/json.git
    GIT_TAG        v3.11.3
    GIT_SHALLOW    TRUE
)
FetchContent_MakeAvailable(nlohmann_json)

FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG        v3.5.4
    GIT_SHALLOW    TRUE
)
FetchContent_MakeAvailable(Catch2)

# ── Library: decoder ──────────────────────────────────────────────────────────

add_library(decoder
    src/decoder/adsb_decoder.cpp
)

target_include_directories(decoder PUBLIC include)

# ── Executable: skydecode-engine ──────────────────────────────────────────────

add_executable(skydecode-engine
    src/main.cpp
)

target_link_libraries(skydecode-engine PRIVATE
    decoder
    nlohmann_json::nlohmann_json
)

# ── Tests ─────────────────────────────────────────────────────────────────────

enable_testing()

add_executable(test_decoder
    test/test_decoder.cpp
)

target_link_libraries(test_decoder PRIVATE
    decoder
    Catch2::Catch2WithMain
)

include(CTest)
include(Catch)
catch_discover_tests(test_decoder)

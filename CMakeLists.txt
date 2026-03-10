cmake_minimum_required(VERSION 3.21)
project(skydecode VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# MSVC-specific settings
if(MSVC)
    add_compile_options(/W4 /utf-8)
endif()

# Fetch nlohmann/json (header-only)
include(FetchContent)
FetchContent_Declare(
    nlohmann_json
    GIT_REPOSITORY https://github.com/nlohmann/json.git
    GIT_TAG        v3.11.3
    GIT_SHALLOW    TRUE
)
FetchContent_MakeAvailable(nlohmann_json)

# Main executable
add_executable(skydecode
    src/main.cpp
)

target_include_directories(skydecode PRIVATE include)

target_link_libraries(skydecode PRIVATE nlohmann_json::nlohmann_json)

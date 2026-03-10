#include <iostream>
#include <nlohmann/json.hpp>

int main() {
    std::cout << "SkyDecode Engine v0.1" << std::endl;

    // Quick sanity check that nlohmann/json is available
    nlohmann::json info = {
        {"engine", "SkyDecode"},
        {"version", "0.1"}
    };
    std::cout << info.dump(2) << std::endl;

    return 0;
}

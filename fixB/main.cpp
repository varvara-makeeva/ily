#include "config.hpp"
#include <iostream>

int main() {
    std::cout << Config::kMax << "\n";

    const int* p = &Config::kMax;
    std::cout << *p << "\n";
}
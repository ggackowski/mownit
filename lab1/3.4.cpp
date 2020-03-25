#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>

float sum(unsigned n) {
    auto sum = .0f;
    auto err = .0f;
    for (auto i = 1; i <= n; ++i) {
        auto y = 1.0 / std::pow(2, i + 1); - err;
        auto temp = sum + y;
        err = (temp - sum) - y;
        sum = temp;
    }
    return sum;
}

int main() {
    std::cout << "n = 50 " << sum(50) << std::endl;
    std::cout << "n = 100 " << sum(100) << std::endl;
    std::cout << "n = 200 " << sum(200) << std::endl;
    std::cout << "n = 500 " << sum(500) << std::endl;
    std::cout << "n = 800 " << sum(800) << std::endl;
}
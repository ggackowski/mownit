#include <iostream>
#include <vector>
#include <cmath>

template <typename T>
T sumForward(unsigned n) {
    T sum = .0;
    for (unsigned i = 1; i <= n; ++i) {
        sum += 1.0 / std::pow(2, i + 1);
    }
    return sum;
}

template <typename T>
T sumBackward(unsigned n) {
    T sum = .0;
    for (unsigned i = n; i >= 1; --i) {
        sum += 1.0 / std::pow(2, i + 1);
    }
    return sum;
}

int main() {
    std::cout << "Pojedyncza precyzja\nW przod" << std::endl;
    std::cout << "n = 50 " << sumForward<double>(50) << std::endl;
    std::cout << "n = 100 " << sumForward<double>(100) << std::endl;
    std::cout << "n = 200 " << sumForward<double>(200) << std::endl;
    std::cout << "n = 500 " << sumForward<double>(500) << std::endl;
    std::cout << "n = 800 " << sumForward<double>(800) << std::endl;

    std::cout << "Wstecz" << std::endl;
    std::cout << "n = 50 " << sumBackward<float>(50) << std::endl;
    std::cout << "n = 100 " << sumBackward<float>(100) << std::endl;
    std::cout << "n = 200 " << sumBackward<float>(200) << std::endl;
    std::cout << "n = 500 " << sumBackward<float>(500) << std::endl;
    std::cout << "n = 800 " << sumBackward<float>(800) << std::endl;
}
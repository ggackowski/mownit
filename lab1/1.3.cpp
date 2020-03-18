#include <cmath>
#include <iostream> 
#include <vector> 

int main() {
    const auto N = 1e7;
    const auto value = 0.82345f;
    std::vector<float> vctr(N);

    for (auto i = vctr.begin(); i != vctr.end(); ++i) 
        *i = value;

    auto sum = 0.0f;

    for (auto i = vctr.begin(); i != vctr.end(); ++i) {
        sum += *i;
        auto index = i - vctr.begin();
        if (index % 25000 == 0) {
            const auto absError = std::abs(sum - (index + 1) * value);
            const auto error = absError / ((index + 1) * value);
            std::cout << error << std::endl;
        }
    }

    const auto absError = std::abs(sum - N * value);
    const auto error = absError / (N * value);

    std::cout << "Blad bezwzgledny: " << absError << std::endl;
    std::cout << "Blad wzgledny: " << error << std::endl;

}
#include <iostream>
#include <vector>


float KahanSum(std::vector<float> & v) {
    auto sum = .0f;
    auto err = .0f;
    for (auto i = v.begin(); i != v.end(); ++i) {
        auto y = *i - err;
        auto temp = sum + y;
        err = (temp - sum) - y;
        sum = temp;
    }
    return sum;
}

int main() {
    const auto N = 1e7;
    const auto value = 0.82345f;
    std::vector<float> vctr(N);

    for (auto i = vctr.begin(); i != vctr.end(); ++i) 
        *i = value;
    
    
    const auto absError = std::abs(KahanSum(vctr) - N * value);
    const auto error = absError / (N * value);

    std::cout << "Blad bezwzgledny: " << absError << std::endl;
    std::cout << "Blad wzgledny: " << error << std::endl;


}
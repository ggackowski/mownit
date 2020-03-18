#include <iostream> 
#include <vector> 

int main() {
    const auto N = 10000000;
    const auto value = 0.82345f;
    std::vector<float> vctr(N);

    for (auto i = vctr.begin(); i != vctr.end(); ++i) 
        *i = value;

    auto sum = 0.0f;

    for (auto i = vctr.begin(); i != vctr.end(); ++i) 
        sum += *i;

    std::cout << sum << std::endl;
}
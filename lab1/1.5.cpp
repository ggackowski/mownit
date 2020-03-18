#include <cmath>
#include <iostream> 
#include <vector> 

float rec_sum(std::vector<float> & v, unsigned begin, unsigned end) {
    if (end - begin == 0) return v[begin];
    if (end - begin == 1) return v[end] + v[begin];
    unsigned div = (end + begin) / 2;
    return rec_sum(v, begin, div) + rec_sum(v, div + 1, end);
}

int main() {
    const auto N = 1e7;
    const auto value = 0.82345f;
    std::vector<float> vctr(N);

    for (auto i = vctr.begin(); i != vctr.end(); ++i) 
        *i = value;

    auto sum = 0.0f;

    sum = rec_sum(vctr, 0, vctr.size() - 1);


    const auto absError = std::abs(sum - N * value);
    const auto error = absError / (N * value);

    std::cout << "Blad bezwzgledny: " << absError << std::endl;
    std::cout << "Blad wzgledny: " << error << std::endl;

}
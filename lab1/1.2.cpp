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

    for (auto i = vctr.begin(); i != vctr.end(); ++i) 
        sum += *i;

    const auto absError = std::abs(sum - N * value);
    const auto error = absError / (N * value);

    std::cout << "Blad bezwzgledny: " << absError << std::endl;
    std::cout << "Blad wzgledny: " << error << std::endl;

}

/*
    float result = sum1;
    float abs_err = std::abs(value * N - result);
    float err = abs_err / (value * N);
    
    /*std::cout << result << std::endl;
    std::cout << abs_err << std::endl;
    std::cout << err << std::endl;

    for (int i = 0; i < N; ++i) {
        sum2 += vctr[i];
        if (i % 25000 == 0) {
            float tmp_err = std::abs(sum2 - value * i);
            std::cout << tmp_err / (value * i) << std::endl;

        }
    }
    */
#include "rectangleIntegration.cpp"
#include "trapezoidalIntegration.cpp"
#include "simpsonsIntegration.cpp"
#include "piCalculator.cpp"
#include "monteCarloIntegration.cpp"
#include <iostream>
#include <cmath>

int main() {

    auto f = [](double x) { return x*x + 3*x; };
    auto g = [](double x) { return 12 + std::sin(x); };
    auto h = [](double x) {return std::exp(x); };

    double low = 2;
    double high = 12;
    int precision = 5;
    int monteCarloPrecision = 100000;

    Integral ** integrals = new Integral * [4];
    integrals[0] = new RectangleIntegration(precision);
    integrals[1] = new TrapezoidalIntegration(precision);
    integrals[2] = new SimpsonsIntegration(precision);
    integrals[3] = new MonteCarloIntegration(monteCarloPrecision);
    
    for (int i = 0; i < 4; ++i) {
        std::cout << integrals[i]->integrate(low, high, f) << std::endl;
    }

    PiCalculator * piCalculator = new PiCalculator(monteCarloPrecision);
    std::cout << piCalculator->getPi() << std::endl;



}
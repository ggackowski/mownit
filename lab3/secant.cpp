
#include <iostream>
#include <limits.h>
#include <cmath>

double f1(double x) {
    return std::cos(x) * std::cosh(x) - 1;
}

double f2(double x) {
    return 1 / x - std::tan(x);
}

double f3(double x) {
    return std::pow(2, -x) + std::exp(x) + 2 * std::cos(x) - 6;
}

double dist(double a, double b) {
    return std::abs(a - b);
}

double (*f) (double);

std::pair<int, double> secant(int it, double epsilon) {
    double x0 = 0.3;
    double x1 = 1;
    int i = 0;
    do {
        double x = (f(x1) * x0 - f(x0) * x1) / (f(x1) - f(x0));
        x0 = x1;
        x1 = x;
    } while (i < it && dist(x1, x0) >= epsilon);

    return std::make_pair(i, x1);
}
/*
        xn = x;
        b1 = b;
        x = (f(a) * b - f(b) * a) / (f(a) - f(b1));
        std::cout << "b tutaj ejst: " << b << std::endl;
        std::cout << x << " | " << xn << std::endl;
        i++;
        std::cout << "a: " << a << " b: " << b << std::endl;
        std::cout << "f(x) " << f(x) << std::endl; 
        if (f(x) * f(a) > 0) {
            a = x;
        }
        if (f(x) * f(b) > 0) {
            b = x;
        }
        std::cout << "at: " << a << " bt: " << b << std::endl;
       */

int main() {
    f = f2;
    auto res = secant(100, 0.1);
    std::cout << res.first << " " << res.second << "\n";

}
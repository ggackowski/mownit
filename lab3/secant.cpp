
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
double a;
double b;

std::pair<int, double> secant(int it, double epsilon) {
    double x0 = a;
    double x1 = b;
    int i = 0;
    do {
        double x = x1;
        x1 = (f(x1) * x0 - f(x0) * x1) / (f(x1) - f(x0));
        x0 = x;
        ++i;
    } while (i < it && dist(x1, x0) >= epsilon);

    return std::make_pair(i, x1);
}

std::pair<double, unsigned> secantMethod(double (*f)(double), double a, double b, double eps, int maxIter){
    double xn0 = a;
    double xn1 = b;

    unsigned i = 0;

    while(abs(f(xn1)) > eps && i < maxIter){
        // std::cout << "f(x) = " << f(x) << " f'(x) = " << derivative(f,x,1e-10) << std::endl;
        double temp = xn1;
        xn1 = (f(xn1) * xn0 - f(xn0) * xn1) / (f(xn1) - f(xn0));
        xn0 = temp;

        if(xn0 == xn1){
            throw("Zbyt maly epsilon!\n");
        }
        i++;
    }
    return std::make_pair(xn1, i);
}

int main() {
    f = f2;
    a = 0;
    b = M_PI / 2;
    auto res = secantMethod(f, a, b, 0.1, 100);
   // auto res = secant(100, 0.1);
    std::cout << res.first << " " << res.second << "\n";

}
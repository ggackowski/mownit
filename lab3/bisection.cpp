#include <iostream>
#include <cmath>

template <typename T> 
int sgn(T val) {
    return (T(0) < val) - (val < T(0));
}

double f1(double x) {
    return std::cos(x) * std::cosh(x) - 1;
}

double f2(double x) {
    return 1 / x - std::tan(x);
}

double f3(double x) {
    return std::pow(2, -x) + std::exp(x) + 2 * std::cos(x) - 6;
}

double (*f)(double);

double dist(double a, double b) {
    return std::abs(a - b);
}

std::pair<double, int> bisection(double begin, double end, double epsilon) {
    static int iteration = 0;
    double root = (begin + end) / 2;
    if (dist(f(root), 0) < epsilon) {
        int it = iteration;
        iteration = 0;
        return std::make_pair(root, it + 1);
    }
    if (dist(begin, end) < 1e-33) {
        int it = iteration;
        iteration = 0;
        return std::make_pair(-1, -1);
    }
    else {
        iteration++;
        if (sgn(f(root)) == sgn(f(begin))) 
            return bisection(root, end, epsilon);
        else 
            return bisection(begin, root, epsilon);
    }
}


int main() {
    
    f = f1;
    auto r = bisection((3 / 2) * M_PI, 2 * M_PI, 1e-13); //brak m zerowego
    std::cout << r.first << " " << r.second << std::endl;

    f = f2;
    r = bisection(0, M_PI / 2, 1e-33); //-7: 25   -15: 52   -33: 53
    std::cout << r.first << " " << r.second << std::endl;

    f = f3;
    r = bisection(1, 3, 1e-33); //-7: 23  -15: 48  -33: 53
    std::cout << r.first << " " << r.second << std::endl;




}
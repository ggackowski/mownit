#include "aghMatrix.h"
#include <unistd.h>
#include <iostream>


const double k = 1;
const double m = 2;

double f1(double x) {
    return std::sin(k * x / M_PI) * exp(-m * x / M_PI);
}

double f2(double x) {
    return std::exp(k * cos(m * x));
}

double f3(double x) {
    return std::sin(m * x) * std::exp(-m * x / M_PI);
}

double f4(double x) {
    return x * x - m * cos(M_PI * x / k);
}

double random_n() {
    return rand() / double(RAND_MAX);
}

std::vector<std::pair<double, double>>
    getRandomPoints(double begin, double end, double (*f) (double), int n) {
        std::vector<std::pair<double, double>> points;
        for (int i = 0; i < n; ++i) {
            double val = random_n() * (end - begin) + begin;
            points.push_back(std::make_pair(val, f(val)));
        }
        return points;
    }

std::vector<std::vector<double>> 
    generateMatrix(std::vector<std::pair<double, double>> points, int m) {
        int n = points.size();
        std::vector<std::vector<double>> matrix(m + 1);
        for (int i = 0; i <= m; ++i) {

            for (int k = 0; k <= m; ++k) {
                double s = 0;
                for (int j = 0; j < n; ++j) 
                    s += std::pow(points[j].first, k + i);

                matrix[i].push_back(s);
            }

            double s = 0;
            for (int j = 0; j < n; ++j) 
                s += points[j].second * std::pow(points[j].first, i);

            matrix[i].push_back(s);
        }      
        return matrix;
    
}

int main() 
{

    int begin = 1;
    int end = 6;
    int pts_size = 10;
    double (*f) (double) = f4;
    auto pts = getRandomPoints(begin, end, f, pts_size);
    
    for (int i = 0; i < pts.size(); ++i) {
        std::cout << pts[i].first << " " << pts[i].second << std::endl;
    }

    auto matrix = generateMatrix(pts, 6);

    AGHMatrix<double> mat8(matrix);

    std::cout << mat8.gauss();
    auto res = mat8.Jacobi(300);
    for (int i = 0; i < res.size(); ++i)
      std::cout << "x[" << i << "] = " << res[i] << std::endl; 
    return 0;
}
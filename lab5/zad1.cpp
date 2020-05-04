#define _GLIBCXX_USE_CXX11_ABI 0
#define _USE_MATH_DEFINES 
#include <iostream>
#include <cmath>
#include <ctime>
#include <vector>

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


int begin = -3;
int end = 3;
int pts_size = 40;
int level = 6;
double (*f) (double) = f4;



std::vector<std::pair<double, double>>
    getRandomPoints() {
        std::vector<std::pair<double, double>> points;
        for (int i = 0; i < pts_size; ++i) {
            double val = random_n() * (end - begin) + begin;
            points.push_back(std::make_pair(val, f(val)));
        }
        return points;
}

std::vector<std::vector<double>> 
    generateMatrix(std::vector<std::pair<double, double>> points) {
        int n = points.size();
        std::vector<std::vector<double>> matrix(level + 1);
        for (int i = 0; i <= level; ++i) {

            for (int k = 0; k <= level; ++k) {
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

std::vector<double> getCoefficiens(std::vector<std::vector<double>> matrix) {
    int n = matrix.size();
    std::vector<double> coefficients(n, 0);
    for (int i = 0; i < n - 1; i++)
        for (int k = i + 1; k < n; k++){
            double tmp = matrix[k][i] / matrix[i][i];
            for (int j = 0; j <= n; j++)
                matrix[k][j] -= tmp * matrix[i][j];
        }

    for (int i = n - 1; i >= 0; i--){
        coefficients.at(i) = matrix[i][n];
        for (int j = 0; j < n; j++)
            if (j != i)
                coefficients.at(i) -= matrix[i][j] * coefficients.at(j);
        coefficients.at(i) /= matrix[i][i];
    }

    return coefficients;
}

double value(double x, std::vector<double> coeff) {
    double sum = 0;
    for (int i = 0; i < coeff.size(); ++i) 
        sum += coeff[i] * std::pow(x, i);
    return sum;
}

double error(std::vector<double> coeff, std::vector<std::pair<double, double>> pts)  {
    double err = 0;
    for (int i = 0; i < pts.size(); ++i) {
        err += std::pow(value(pts[i].first, coeff) - pts[i].second, 2);
    }
    return err;
    
}

double error2(std::vector<double> coeff, std::vector<std::pair<double, double>> pts)  {
    double err = 0;
    for (double i = begin ; i <= end; i += 2e-4) {
        double p = std::pow(value(i, coeff) - f(i), 2);
        err += p;
    }
    return err;

}

void show(std::vector<std::pair<double, double>> pts) {
    auto matrix = generateMatrix(pts);
    auto c = getCoefficiens(matrix);
    std::string s = "";
    for (int i = 0; i < c.size(); ++i) {
        s += std::to_string(c[i]);
        s += " ";
    }
    s = "python plot.py " + s;
    system(s.c_str());
}

void show2(std::vector<double> coeff) {
    for (int i = 0; i < coeff.size(); ++i) {
        if (i == 0) std::cout << coeff[i] << " ";
        else if (coeff[i] > 0) std::cout << "+" << coeff[i] << " * x^" << i << " ";
        else std::cout << coeff[i] << " * x^" << i << " "; 
    }
    std::cout << std::endl;
}

int main() {
    srand(time(NULL));

    
    auto pts = getRandomPoints();
   
    for (int i = 0; i < pts.size(); ++i) {
        std::cout << pts[i].first << " " << pts[i].second << std::endl;
    }
    
    int min_err = 100000;
    int min_st = 1;

    for (int i = 1; i < pts.size(); ++i) {
        level = i;
        auto m = generateMatrix(pts);
        auto c = getCoefficiens(m);
        auto err = error2(c, pts);
        if (min_err > err) {
            min_err = err;
            min_st = i;
        }
    }

    level = min_st;
    std::cout << "\nMIN ERR: " << min_err << "\nMIN ST: " << min_st << std::endl;
    //show(pts);
    auto m = generateMatrix(pts);
    auto c = getCoefficiens(m);
    
    show2(c);

    std::cout << std::endl << value(-3, c) << " " << value(3, c) << std::endl;

}
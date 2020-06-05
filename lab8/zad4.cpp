#include <iostream>
#include <complex>
#include <vector>
#include <sys/times.h>
#include <unistd.h>
#include <fstream>

class DFT {
    public:
        DFT(std::vector<std::complex<double>> inpt) {
            input = inpt;
        }

        std::vector<std::complex<double>> get() {
            std::vector<std::complex<double>> result(input.size());
            for (int i = 0; i < input.size(); ++i) {
                result[i] = 0;
                for (int j = 0; j < input.size(); ++j) {
                    result[i] += input[j] * std::complex<double>((cos((-2.0 * M_PI)/input.size() * i * j)), (sin((-2. * M_PI) / input.size() * i * j)));
                }

            }
            return result;
        }

    private:
        std::vector<std::complex<double>> input;
};

class FFT {
    public:
        FFT(std::vector<std::complex<double>> inpt) {
            input = inpt;
        }

        void _get(std::vector<std::complex<double>> & x) {
            if (x.size() <= 4) {
                DFT * dft = new DFT(x);
                x = dft->get();
            }
            else {
                std::vector<std::complex<double>> odd;
                std::vector<std::complex<double>> even;
                for (int i = 0; i < x.size(); ++i) {
                    if (!(i % 2))
                        even.push_back(x[i]);
                    else
                        odd.push_back(x[i]);
                }
                _get(even);
                _get(odd);
                for (int i = 0; i < x.size() / 2; ++i) {
                   std::complex<double> factor = 
                                std::complex<double>(cos((-2.0 * M_PI * i) / x.size()), 
                                sin((-2.0 * M_PI * i) / x.size())) * odd[i];
                   x[i] = even[i] + factor;
                   x[i + (x.size() / 2)] = even[i] - factor;
                }

            }
        }

        std::vector<std::complex<double>> get() {
            _get(input);
            return input;
        }

    private:
        std::vector<std::complex<double>> input;
};

double tm(int begin, int end) {
    return double(end - begin) / sysconf(_SC_CLK_TCK);
}


int main() {


   std::fstream stream("data", std::ios_base::in);
   std::vector<std::complex<double>> input;
   double in = 0;
   while (stream >> in) 
       input.push_back(std::complex<double>(in, 0));
    
    for (auto i : input) 
        std::cout << i << " ";

    FFT * fft = new FFT(input);

    auto result = fft->get();

    std::cout << std::endl;
    for (auto i : result)
        std::cout << sqrt(i.imag() * i.imag() + i.real() * i.real()) << std::endl;

}


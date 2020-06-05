#include <iostream>
#include <complex>
#include <vector>



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
                    result[i] += input[j] * 
                                std::complex<double>((cos((-2. * M_PI)/input.size() * i * j)),
                                (sin((-2. * M_PI) / input.size() * i * j)));
                }

            }
            return result;
            
        }
    
    private:
        std::vector<std::complex<double>> input;
};

int main() {

    const int N = 8;

    std::vector<std::complex<double>> input(N);
    input[0] = std::complex<double>(1, 0);
    input[1] = std::complex<double>(2, -1);
    input[2] = std::complex<double>(0, -1);
    input[3] = std::complex<double>(-1, 2);
    input[4] = std::complex<double>(1, 0);
    input[5] = std::complex<double>(2, -1);
    input[6] = std::complex<double>(0, -1);
    input[7] = std::complex<double>(-1, 2);

    DFT * dft = new DFT(input);
    auto output = dft->get();
    for (int i = 0; i < output.size(); ++i)
        std::cout << output[i] << " ";
    std::cout << std::endl;

    return 0;
}
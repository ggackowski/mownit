#include <iostream>
#include <iomanip>
#include <limits>

int main() {
  float epsilon = 1.0f;
  while (1.0f + (0.5 * epsilon) != 1.0f) {
    epsilon *= 0.5f;
  }

  std::cout << epsilon << std::endl;
  std::cout << ((1.0f + epsilon) == 1) << std::endl;
  std::cout << ((1.0f + epsilon * 0.5f) == 1) << std::endl;
  
}
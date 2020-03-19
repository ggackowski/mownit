#include <iostream>
#include <iomanip>

int main() {
  float epsilon = 1.0f;
  while (1.0f + (0.5 * epsilon) != 1.0f) {
    epsilon *= 0.5f;
  }

  std::cout << epsilon << std::endl;
}
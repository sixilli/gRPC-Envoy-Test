#include "matrix.h"
#include <string>
#include <iostream>

int main() {
  Matrix<int> m1, m2;
  auto m3 = m1 + m2;
  m3.print_matrix();
  return 0;
}
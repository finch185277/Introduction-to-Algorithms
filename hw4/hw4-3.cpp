#include "lp_solver.h"
#include <iostream>
#include <vector>

int main() {
  int n, w, v;
  std::cin >> n >> w >> v;

  std::vector<std::vector<double>> A(2 + n * 4, std::vector<double>(n * 2));
  for (int i = 0; i < n; i++) { // input Wi
    std::cin >> A.at(0).at(i * 2);
    A.at(0).at(i * 2 + 1) = A.at(0).at(i * 2);
  }
  for (int i = 0; i < n; i++) { // input Vi
    std::cin >> A.at(1).at(i * 2);
    A.at(1).at(i * 2 + 1) = A.at(1).at(i * 2);
  }

  for (int i = 0; i < n * 2; i++)
    A.at(2 + i).at(i) = 1;

  for (int i = 0; i < n * 2; i++)
    A.at(2 + n * 2 + i).at(i) = -1;

  std::vector<double> y(n * 2);

  std::vector<double> c(2 + n * 4);
  c.at(0) = w;
  c.at(1) = v;
  for (int i = 0; i < n * 2; i++)
    c.at(2 + i) = 1;

  std::vector<double> b(n * 2);
  for (int i = 0; i < n; i++) { // input Pi
    std::cin >> b.at(i * 2);
    b.at(i * 2 + 1) = b.at(i * 2) * 0.8;
  }

  double z = lp_solver(GLP_MAX, b, A, y, c);

  std::cout << z << std::endl;
  for (int i = 0; i < n; i++)
    std::cout << y.at(i * 2) + y.at(i * 2 + 1) << " ";
  std::cout << std::endl;
  return 0;
}

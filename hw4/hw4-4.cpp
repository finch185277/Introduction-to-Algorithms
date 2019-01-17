#include "lp_solver.h"
#include <iostream>
#include <vector>

int main() { // by @shihyw
  int n, k;
  std::cin >> n >> k;

  std::vector<std::vector<double>> A(k + n, std::vector<double>(n));
  std::vector<double> b(k + n);

  for (int i = 0; i < k; i++) {
    char x, y;
    int cc;
    std::cin >> x >> cc >> y;
    A.at(i).at(x - 97) = 1, A.at(i).at(y - 97) = -1;
    b.at(i) = -cc;
  }
  for (int i = k; i < k + n; i++) {
    A.at(i).at(i - k) = 1;
    b.at(i) = 26;
  }

  std::vector<double> y(n);

  std::vector<double> c(n, 1);

  double z = lp_solver(GLP_MAX, c, A, y, b);

  for (int i = 0; i < n; i++)
    std::cout << y[i] << " ";
  return 0;
}

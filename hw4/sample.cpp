#include "lp_solver.h"
#include <iostream>
#include <vector>
using namespace std;

/*
** optimize z = c^T y  (optimize: GLP_MIN or GLP_MAX)
** subject to Ay <= b
**
** return z
*/

// double lp_solver(int optimize, const vector<double>& c, const
// vector<vector<double> >& A, vector<double> &y, const vector<double> &b);

int main() {

  /*
   * The following code solves the linear program
   *
   * minimize    7 y1 + 11 y2 + 13 y3
   * subject to  y1 - y3 <= 1
   *             2 y1 + y2 + 3 y3 <= 2
   *
   *
   * i.e. return min{c^T y : Ay <= b}
   */

  vector<vector<double>> A;
  A.resize(2);
  for (int i = 0; i < 2; ++i) {
    A[i].resize(3);
  }
  A[0][0] = 1, A[0][1] = 0, A[0][2] = -1;
  A[1][0] = 2, A[1][1] = 1, A[1][2] = 3;

  vector<double> y;
  y.resize(3);

  vector<double> b;
  b.resize(2);
  b[0] = 1, b[1] = 2;

  vector<double> c;
  c.resize(3);
  c[0] = 7, c[1] = 11, c[2] = 13;

  double z = lp_solver(GLP_MAX, c, A, y, b);

  cout << "the optimal objective value is " << z << endl;
  cout << "the optimal solution is (";
  for (int i = 0; i < 3; ++i) {
    cout << y[i] << ((i == 2) ? "" : ",");
  }
  cout << ")" << endl;
  return 0;
}

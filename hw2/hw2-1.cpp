#include <cstring>
#include <iostream>
#define MAXN 1005

int main() {
  int n;
  int origin[MAXN][MAXN];
  int cost[MAXN][MAXN];
  std::cin >> n;
  std::memset(origin, 0, sizeof origin);
  std::memset(cost, 0, sizeof cost);
  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++)
      std::cin >> origin[i][j];

  for (int i = 1; i < n; i++) { // init bound max cost
    cost[i][0] = std::max(abs(origin[i][0] - origin[i - 1][0]), cost[i - 1][0]);
  }
  for (int j = 1; j < n; j++) {
    cost[0][j] = std::max(abs(origin[0][j] - origin[0][j - 1]), cost[0][j - 1]);
  }
  for (int i = 1; i < n; i++) {
    for (int j = 1; j < n; j++) {
      int cost_from_top, cost_from_left;
      cost_from_top = // count the max cost
          std::max(abs(origin[i][j] - origin[i - 1][j]), cost[i - 1][j]);
      cost_from_left =
          std::max(abs(origin[i][j] - origin[i][j - 1]), cost[i][j - 1]);
      cost[i][j] = std::min(cost_from_top, cost_from_left); // choose path
    }
  }
  std::cout << cost[n - 1][n - 1] << '\n';
}

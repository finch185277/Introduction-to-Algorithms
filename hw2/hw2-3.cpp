#include <cstring>
#include <iostream>

#define MOD 1000000007
#define MAX 5005
long long int dp[MAX][MAX][2];
long long int ans[MAX];

long long int sol_dp(int _h, int _i, int state) {
  if (_h < 0 || _i < 0)
    return 0;
  if (dp[_h][_i][state] != -1) {
    return dp[_h][_i][state];
  }
  if (_h < _i)
    return dp[_h][_i][state] = 0;
  if (_i == 1 && _h >= 2)
    return dp[_h][_i][state] = 1;
  if (state == 0 && _i == _h)
    return dp[_h][_i][state] = 1;
  if (state == 1 && _i == _h - 1)
    return dp[_h][_i][state] = 1;

  if (state == 0) { // black
    dp[_h][_i][state] =
        (sol_dp(_h - 1, _i - 1, 0) + sol_dp(_h - 1, _i - 1, 1)) % MOD *
        (sol_dp(_h - 1, _i - 1, 0) + sol_dp(_h - 1, _i - 1, 1) % MOD) % MOD;
  } else {
    dp[_h][_i][state] = sol_dp(_h - 1, _i, 0) * sol_dp(_h - 1, _i, 0) % MOD;
  }
  return dp[_h][_i][state];
}

long long int find_ans(int _h) {
  if (ans[_h] != -1)
    return ans[_h];
  ans[_h] = 0;
  for (int _i = 1; _i <= _h; _i++)
    ans[_h] = ((sol_dp(_h, _i, 0) + sol_dp(_h, _i, 1)) % MOD + ans[_h]) % MOD;
  return ans[_h];
}

int main() {
  std::memset(dp, -1, sizeof dp);
  std::memset(ans, -1, sizeof ans);
  int case_count;
  std::cin >> case_count;
  while (case_count--) {
    int tree_hight;
    std::cin >> tree_hight;
    std::cout << (MOD + find_ans(tree_hight) - find_ans(tree_hight - 1)) % MOD
              << '\n';
  }
  return 0;
}

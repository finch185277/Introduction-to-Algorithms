#include <cstring>
#include <iostream>

#define MOD 1000000007
#define MAX 5005
long long int dp[MAX][MAX][2];
long long int ans[MAX];

// _h = tree height
// _n = how many black from top traverse to buttom
// state = root color
// btw ... Thanks to Tracy XD
long long int sol_dp(int _h, int _n, int state) {
  if (_h <= 0 || _n <= 0)
    return 0;
  if (dp[_h][_n][state] != -1)
    return dp[_h][_n][state];
  if (_h < _n)
    return dp[_h][_n][state] = 0;

  if (_n == 1 && _h >= 2) // for recursive
    return dp[_h][_n][state] = 1;
  if (state == 0 && _n == _h) // all black
    return dp[_h][_n][state] = 1;
  if (state == 1 && _n == _h - 1) // all black exclude root is red
    return dp[_h][_n][state] = 1;

  if (state == 0) { // root is black
    dp[_h][_n][state] =
        (sol_dp(_h - 1, _n - 1, 0) + sol_dp(_h - 1, _n - 1, 1)) % MOD *
        (sol_dp(_h - 1, _n - 1, 0) + sol_dp(_h - 1, _n - 1, 1) % MOD) % MOD;
  } else { // root is red
    dp[_h][_n][state] = sol_dp(_h - 1, _n, 0) * sol_dp(_h - 1, _n, 0) % MOD;
  }
  return dp[_h][_n][state];
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
    int th;
    std::cin >> th;
    std::cout << (MOD + find_ans(th) - find_ans(th - 1)) % MOD << '\n';
  }
  return 0;
}

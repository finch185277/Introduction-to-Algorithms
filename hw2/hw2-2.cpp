#include <algorithm>
#include <cstring>
#include <iostream>

#define MAX 10005
int dp[2][MAX];
int ans[MAX];

void lcs(std::string &_s1, std::string &_s2, int _m, int _n) {
  for (int i = 1; i <= _m; i++) {
    std::memset(dp[i % 2], 0, sizeof dp[i % 2]);
    for (int j = 1; j <= _n; j++) {
      dp[i % 2][j] = std::max(dp[!(i % 2)][j], dp[i % 2][j - 1]);
      if (_s1[i - 1] == _s2[j - 1])
        dp[i % 2][j] = std::max(dp[i % 2][j], dp[!(i % 2)][j - 1] + 1);
    }
    ans[i] = dp[i % 2][_m + 1 - i] * 2 - 1;
  }
}

int main() { // by @tracyliu (for fast solution)
  std::memset(dp, 0, sizeof dp);
  std::memset(ans, 0, sizeof ans);
  std::string str1;
  std::cin >> str1;
  std::string str2(str1);
  std::reverse(str2.begin(), str2.end());
  int len_s = str1.size();
  lcs(str1, str2, str1.size(), str2.size());
  for (int i = 1; i <= len_s; i++)
    std::cout << ans[i] << ' ';
  std::cout << '\n';
}

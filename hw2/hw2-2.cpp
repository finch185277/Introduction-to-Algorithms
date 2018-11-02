#include <algorithm>
#include <cstring>
#include <iostream>

#define MAX 10005

int lcs(std::string &_s1, std::string &_s2, int _m, int _n) {
  int dp[_m + 1][_n + 1];
  for (int i = 0; i <= _m; i++) {
    for (int j = 0; j <= _n; j++) {
      if (i == 0 || j == 0)
        dp[i][j] = 0;
      else if (_s1[i - 1] == _s2[j - 1])
        dp[i][j] = dp[i - 1][j - 1] + 1;
      else
        dp[i][j] = std::max(dp[i - 1][j], dp[i][j - 1]);
    }
  }
  return dp[_m][_n];
}

int main() {
  int ans[MAX];
  std::string str1;
  std::cin >> str1;
  std::string str2(str1);
  std::reverse(str2.begin(), str2.end());
  int len_s = str1.size();
  for (int i = 0; i < len_s; i++) {
    std::string tmp1(str1.substr(0, i));
    std::string tmp2(str2.substr(0, len_s - i - 1));
    ans[i] = 1 + 2 * lcs(tmp1, tmp2, tmp1.size(), tmp2.size());
  }
  for (int i = 0; i < len_s; i++)
    std::cout << ans[i] << ' ';
  std::cout << '\n';
}

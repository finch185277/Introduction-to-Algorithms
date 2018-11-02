#include <algorithm>
#include <cstring>
#include <iostream>

#define MAX 10005

int lcs(std::string &s1, std::string &s2, int m, int n) {
  if (m == 0 || n == 0)
    return 0;
  if (s1[m - 1] == s2[n - 1])
    return lcs(s1, s2, m - 1, n - 1) + 1;
  else
    return std::max(lcs(s1, s2, m, n - 1), lcs(s1, s2, m - 1, n));
}

int main() {
  int ans[MAX];
  std::string str1;
  std::cin >> str1;
  std::string str2(str1);
  std::reverse(str2.begin(), str2.end());
  std::memset(ans, 1, sizeof ans);
  int len_s = str1.size();
  for (int i = 0; i <= len_s / 2; i++) {
    std::string tmp1(str1.substr(0, i));
    std::string tmp2(str2.substr(0, len_s - i - 1));
    ans[i] = 1 + 2 * lcs(tmp1, tmp2, tmp1.size(), tmp2.size());
  }
  for (int i = len_s / 2 + 1; i < len_s; i++) {
    std::string tmp1(str1.substr(0, i));
    std::string tmp2(str2.substr(0, len_s - i - 1));
    ans[i] = 1 + 2 * lcs(tmp1, tmp2, tmp1.size(), tmp2.size());
  }
  for (int i = 0; i < len_s; i++)
    std::cout << ans[i] << ' ';
  std::cout << '\n';
}

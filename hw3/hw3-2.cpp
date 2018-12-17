#include <algorithm>
#include <array>
#include <cstring>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <utility>
#include <vector>

struct dra {
  int x, y;
  int blood;
};

std::vector<dra> get_dra(int _cnt) {
  std::vector<dra> _rt;
  while (_cnt--) {
    dra _d;
    std::cin >> _d.x >> _d.y >> _d.blood;
    _rt.push_back(_d);
  }
  return _rt;
}

std::vector<int> get_tur(int _len) {
  std::vector<int> _rt;
  while (_len--) {
    int _c;
    std::cin >> _c;
    _rt.push_back(_c);
  }
  return _rt;
}

int main() {
  int area_len, dra_cnt;
  std::cin >> area_len >> dra_cnt;
  std::vector<int> raw_tur(get_tur(area_len)), col_tur(get_tur(area_len));
  std::vector<dra> dra_info(get_dra(dra_cnt));
  int all_blood = 0, all_bul = 0;
  for (dra _d : dra_info) {
    all_blood += _d.blood;
  }
  for (int _rb : raw_tur) {
    all_bul += _rb;
  }
  for (int _cb : col_tur) {
    all_bul += _cb;
  }
  // std::cout << all_blood << ' ' << all_bul << std::endl;
  if (all_blood > all_bul)
    std::cout << "No" << std::endl;
  else {
    bool check_single_dra_flag = true;
    for (dra _d : dra_info) {
      if (raw_tur.at(_d.x - 1) + col_tur.at(_d.y - 1) < _d.blood) {
        check_single_dra_flag = false;
        break;
      }
    }
    if (!check_single_dra_flag)
      std::cout << "No" << std::endl;
    else
      std::cout << "Yes" << std::endl;
  }
  return 0;
}

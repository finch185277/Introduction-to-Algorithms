#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

struct node {
  long long int x, y;
};
bool sort_x(node &_lhs, node &_rhs) { return _lhs.x < _rhs.x; }
bool sort_y(node &_lhs, node &_rhs) { return _lhs.y < _rhs.y; }

int main() {
  std::cin.sync_with_stdio(false);
  std::cin.tie(NULL);
  long long int red_count, blue_count;
  long long int max_size = -1, base = 0;
  std::cin >> red_count >> blue_count;
  std::vector<node> red_points, blue_points;
  std::vector<node>::iterator red_index, blue_index;
  while (red_count--) {
    node _tmp;
    std::cin >> _tmp.x >> _tmp.y;
    red_points.push_back(_tmp);
  }
  while (blue_count--) {
    node _tmp;
    std::cin >> _tmp.x >> _tmp.y;
    blue_points.push_back(_tmp);
  }
  std::sort(red_points.begin(), red_points.end(), sort_y);
  std::sort(blue_points.begin(), blue_points.end(), sort_y);
  for (red_index = red_points.begin(); red_index != red_points.end();
       red_index++) {
    if ((*red_index).y <= (blue_points.front()).y)
      red_points.erase(red_points.begin());
  }
  std::sort(red_points.begin(), red_points.end(), sort_x);
  std::sort(blue_points.begin(), blue_points.end(), sort_x);
  for (blue_index = blue_points.begin(); blue_index != blue_points.end();
       blue_index++) {
    if ((*blue_index).x <= (red_points.front()).x)
      blue_points.erase(blue_points.begin());
  }
  for (auto i = red_points.begin(); i != red_points.end(); i++) {
    auto _l = blue_points.begin(), _h = blue_points.end() - 1;
    while (_l != _h - 1) {
      // std::cout << ' ' << (*i).x << ' ' << (*i).y << ' ';
      auto _m = _l + std::distance(_l, _h) / 2;
      long long int L_area = std::max(((*_l).x - (*i).x), base) *
                             std::max(((*i).y - (*_l).y), base),
                    H_area = std::max(((*_h).x - (*i).x), base) *
                             std::max(((*i).y - (*_h).y), base);
      if (L_area > H_area) {
        _h = _m;
        // std::cout << (*_l).x << ' ' << (*_l).y << '\n';
        max_size = std::max(max_size, L_area);
      } else {
        _l = _m;
        // std::cout << (*_h).x << ' ' << (*_h).y << '\n';
        max_size = std::max(max_size, H_area);
      }
    }
    _l = blue_points.begin();
    _h = blue_points.end() - 1;
    auto _m = _l + std::distance(_l, _h) / 2;
    for (auto j = _m - log2(std::distance(_l, _h));
         j <= _m + log2(std::distance(_l, _h)) - 1; j++) {
      long long int tmp_area =
          std::max(((*j).x - (*i).x), base) * std::max(((*i).y - (*j).y), base);
      max_size = std::max(max_size, tmp_area);
    }
    for (auto j = _l; j <= _l + log2(std::distance(_l, _h)); j++) {
      long long int tmp_area =
          std::max(((*j).x - (*i).x), base) * std::max(((*i).y - (*j).y), base);
      max_size = std::max(max_size, tmp_area);
    }
    for (auto j = _h - log2(std::distance(_l, _h)); j <= _h; j++) {
      long long int tmp_area =
          std::max(((*j).x - (*i).x), base) * std::max(((*i).y - (*j).y), base);
      max_size = std::max(max_size, tmp_area);
    }
  }
  std::cout << max_size << '\n';
}

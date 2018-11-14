#include <algorithm>
#include <iostream>
#include <vector>

struct node {
  long long int x, y;
};

bool cmp_red(node &_lhs, node &_rhs) {
  if (_lhs.x < _rhs.x)
    return true;
  else if (_lhs.x == _rhs.x && _lhs.y > _rhs.y)
    return true;
  else
    return false;
}

bool cmp_blue(node &_lhs, node &_rhs) {
  if (_lhs.x > _rhs.x)
    return true;
  else if (_lhs.x == _rhs.x && _lhs.y < _rhs.y)
    return true;
  else
    return false;
}

auto exact_points(std::vector<node> _points, bool flag) {
  std::vector<node> ret;
  ret.push_back(_points.front());
  for (auto i = _points.begin() + 1; i != _points.end(); i++) {
    if (flag) {
      if ((*i).y > ret.back().y) // ascending
        ret.push_back(*i);
    } else {
      if ((*i).y < ret.back().y) // descending
        ret.push_back(*i);
    }
  }
  return ret;
}

long long int det_area(auto i, auto j) {
  return std::max((*j).x - (*i).x, 0LL) * std::max((*i).y - (*j).y, 0LL);
}

int main() {
  std::cin.sync_with_stdio(false);
  std::cin.tie(NULL);
  long long int red_count, blue_count;
  long long int max_size = -1;
  std::cin >> red_count >> blue_count;
  std::vector<node> red_points, blue_points;
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
  std::sort(red_points.begin(), red_points.end(), cmp_red);
  std::sort(blue_points.begin(), blue_points.end(), cmp_blue);
  // for (auto i = red_points.begin(); i != red_points.end(); i++) {
  // for (auto j = blue_points.begin(); j != blue_points.end(); j++) {
  // std::cout << (*i).x << ' ' << (*i).y << ' ' << (*j).x << ' ' << (*j).y
  // << '\n';
  //   }
  // }
  auto red_p = exact_points(red_points, true);
  auto blue_p = exact_points(blue_points, false);
  for (auto i = red_p.begin(); i != red_p.end(); i++) {
    for (auto j = blue_p.begin(); j != blue_p.end(); j++) {
      max_size = std::max(max_size, det_area(i, j));
    }
  }
  std::cout << max_size << '\n';
}

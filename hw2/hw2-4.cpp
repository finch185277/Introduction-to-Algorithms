#include <algorithm>
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
    if ((*red_index).y <= (*blue_points.begin()).y)
      red_points.erase(red_points.begin());
  }
  std::sort(red_points.begin(), red_points.end(), sort_x);
  std::sort(blue_points.begin(), blue_points.end(), sort_x);
  for (blue_index = blue_points.begin(); blue_index != blue_points.end();
       blue_index++) {
    if ((*blue_index).x <= (*red_points.begin()).x)
      blue_points.erase(blue_points.begin());
  }
  for (auto i = red_points.begin(); i != red_points.end(); i++) {
    for (auto j = blue_points.begin(); j != blue_points.end(); j++) {
      max_size = std::max(max_size, (std::max(((*j).x - (*i).x), base) *
                                     std::max(((*i).y - (*j).y), base)));
    }
  }
  std::cout << max_size << '\n';
}

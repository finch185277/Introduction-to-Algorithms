#include <algorithm>
#include <array>
#include <cstring>
#include <iostream>
#include <stack>
#include <utility>
#include <vector>
#define MAX 100005

struct edge {
  int u, v;
};

struct connected_component {
  int boss;
  std::vector<int> member;
};

edge get_edge() {
  edge _edge;
  std::cin >> _edge.u >> _edge.v;
  return _edge;
}

std::vector<int> init(const int _node_num) {
  std::vector<int> _par;
  _par.push_back(0); // 1-base
  for (int i = 1; i <= _node_num; i++)
    _par.push_back(i);
  return _par;
}

int find_boss(const int _t, std::vector<int> &_par) {
  if (_par.at(_t) == _t)
    return _t;
  return _par.at(_t) = find_boss(_par.at(_t), _par);
}

void union_node(const int _s, const int _t, std::vector<int> &_par) {
  _par.at(find_boss(_s, _par)) = find_boss(_t, _par);
}

bool is_exist_node(const int _n, const std::vector<int> &_v) {
  if (std::find(_v.begin(), _v.end(), _n) != _v.end())
    return true;
  else
    return false;
}

// useing DFS to find connected component
void depth_first_search(const std::vector<edge> &_edge_list,
                        std::vector<int> &_par) {
  std::vector<int> _visited_node;
  for (edge _e : _edge_list) {
    if (!is_exist_node(_e.u, _visited_node)) {
      union_node(_e.u, _e.v, _par);
      _visited_node.push_back(_e.u);
    }
    if (!is_exist_node(_e.v, _visited_node)) {
      union_node(_e.v, _e.u, _par);
      _visited_node.push_back(_e.v);
    }
  }
}

std::vector<connected_component>
make_connected_component_group(const int _node_num, std::vector<int> &_par) {
  std::vector<connected_component> _connected_component_group;
  for (int i = 1; i <= _node_num; i++) {
    bool _exist_c = false;
    for (auto _c = _connected_component_group.begin();
         _c != _connected_component_group.end(); _c++) {
      if (_c->boss == find_boss(i, _par)) {
        _c->member.push_back(i);
        _exist_c = true;
        break;
      }
    }
    if (!_exist_c) {
      connected_component _tmp;
      _tmp.boss = find_boss(i, _par);
      _tmp.member.push_back(i);
      _connected_component_group.push_back(_tmp);
    }
  }
  return _connected_component_group;
}

bool is_exist_char(const char &_t, const std::string &_node_str,
                   const connected_component &_c) {
  for (int _n : _c.member) {
    if (_t == _node_str[_n - 1]) // 1-base
      return true;
  }
  return false;
}

void print_vector(const std::vector<char> &_v) {
  std::cout << "_target_vec: ";
  for (char _t : _v)
    std::cout << _t << ' ';
  std::cout << std::endl;
}

bool check_exist_path(
    const std::string &_node_str, const std::string &_target_str,
    const std::vector<connected_component> &_connected_component_group) {
  std::vector<char> _target_vec;
  std::copy(_target_str.begin(), _target_str.end(),
            std::back_inserter(_target_vec));
  std::sort(_target_vec.begin(), _target_vec.end());
  _target_vec.erase(std::unique(_target_vec.begin(), _target_vec.end()),
                    _target_vec.end());
  // print_vector(_target_vec);
  for (connected_component _c : _connected_component_group) {
    int _success_count(0);
    for (char _t : _target_vec) {
      if (is_exist_char(_t, _node_str, _c))
        _success_count++;
      else
        break;
    }
    if (_success_count == _target_vec.size())
      return true;
  }
  return false;
}

void print_connected_component(const std::string _s,
                               const std::vector<connected_component> &_cg) {
  std::cout << "print_connected_component: " << std::endl;
  int index = 1;
  for (connected_component _c : _cg) {
    std::cout << index++ << ": ";
    for (int i : _c.member) {
      std::cout << i << '-' << _s[i - 1] << ' '; // 1-base
    }
    std::cout << std::endl;
  }
}

void print_par(const int _node_num, std::vector<int> &_par) {
  std::cout << "print_par:" << std::endl;
  for (int i = 1; i <= _node_num; i++)
    std::cout << _par.at(i) << ' ';
  std::cout << std::endl;
}

void print_edge(const std::vector<edge> &_edge_list) {
  std::cout << "print_edge:" << std::endl;
  for (edge _e : _edge_list) {
    std::cout << _e.u << ' ' << _e.v << std::endl;
  }
}

int main() {
  // initial
  int node_num, edge_num;
  std::string node_str, target_str;
  std::vector<edge> edge_list;
  std::cin >> node_num >> edge_num >> node_str;
  int _edge_num(edge_num);
  while (_edge_num--) {
    edge e1 = get_edge();
    edge e2(e1);
    std::swap(e2.u, e2.v);
    edge_list.push_back(e1);
    edge_list.push_back(e2);
  }
  std::cin >> target_str;
  std::vector<int> par(init(node_num));
  // print_par(node_num, par);

  // solve
  depth_first_search(edge_list, par);
  std::vector<connected_component> connected_component_group(
      make_connected_component_group(node_num, par));
  bool exist_flag(
      check_exist_path(node_str, target_str, connected_component_group));

  // output
  // print_edge(edge_list);
  // print_par(node_num, par);
  // print_connected_component(node_str, connected_component_group);

  if (exist_flag)
    std::cout << "Yes" << std::endl;
  else
    std::cout << "No" << std::endl;
  return 0;
}

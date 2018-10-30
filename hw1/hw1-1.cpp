#include "OJ.h"

#include <bits/stdc++.h>
using namespace std;

void naive(vector<Point> &points) {
  int n = (int)points.size() / 2;
  do {
    oj.set_match(points);
    display();
  } while (update(n, points));
}

void DC(vector<Point> &points) {
  if (points.size() <= 4) { // boundary case (naive)...
    naive(points);
    return;
  } else { // D&C ...
    vector<Point> sub1, sub2;
    partition(points, sub1, sub2);
    oj.set_match(sub1);
    oj.set_match(sub2);
    display();
    DC(points);
    DC(sub1);
    DC(sub2);
  }
}

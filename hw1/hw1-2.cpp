#include "OJ.h"
#include "Point.h"

#include <bits/stdc++.h>
using namespace std;

bool update(int n, vector<Point> &points) {
  bool result = false;
  for (int i = 0; i < n; i++) {
    for (int j = i + 1; j < n; j++) {
      Line L1 = {points[i], points[i + n] - points[i]};
      Line L2 = {points[j], points[j + n] - points[j]};
      if (intersection(L1, L2)) {
        result = true;
        swap(points[i], points[j]);
      }
    }
  }
  return result;
}

void naive(vector<Point> &points) {
  int n = (int)points.size() / 2;
  do {
    oj.set_match(points);
    display();
  } while (update(n, points));
}

void DC(vector<Point> &points) {
  if (points.size() <= 2048) { // boundary case (naive)...
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

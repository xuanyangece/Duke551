#include "point.h"

#include <math.h>

#include <iostream>

using namespace std;

Point::Point() : x(0), y(0) {}

void Point::move(double dx, double dy) {
  x += dx;
  y += dy;
}

double Point::distanceFrom(const Point & p) {
  double dx = (this->x - p.x) * (this->x - p.x);
  double dy = (this->y - p.y) * (this->y - p.y);
  return sqrt(dx + dy);
}

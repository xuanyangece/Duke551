#include "circle.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "point.h"

double getAngle(double r1, double r2, double dis) {
  return acos((r1 * r1 + dis * dis - r2 * r2) / (2.0 * r1 * dis));
}

void Circle::move(double dx, double dy) {
  this->center.move(dx, dy);
}

double Circle::intersectionArea(const Circle & otherCircle) {
  double dis = center.distanceFrom(otherCircle.center);
  double r1 = this->radius;
  double r2 = otherCircle.radius;

  // no intersection
  if (r1 + r2 <= dis) {
    return 0.0;
  }

  // swap to get the smaller one to r1
  if (r2 < r1) {
    double temp = r2;
    r2 = r1;
    r1 = temp;
  }

  // include
  if (r2 - r1 >= dis) {
    return M_PI * r1 * r1;
  }

  // intersect
  double ang1(0.0), ang2(0.0);
  ang1 = getAngle(r1, r2, dis) * 2.0;
  ang2 = getAngle(r2, r1, dis) * 2.0;
  double res = 0;
  res = 0.5 * r1 * r1 * (ang1 - sin(ang1)) + 0.5 * r2 * r2 * (ang2 - sin(ang2));
  return res;
}

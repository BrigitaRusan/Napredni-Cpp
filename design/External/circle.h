#pragma once
#include "point.h"

class Circle {
    public:
        Circle(float radius, Point center) : radius_{radius}, center_{center} {}

        float radius() const { return radius_; }
        Point center() const { return center_; }
    private:
        float radius_;
        Point center_;
};

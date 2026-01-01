#ifndef MATH_UTILS_HPP
#define MATH_UTILS_HPP

#include <cmath>

namespace math_utils {

float point_to_segment_distance(float px, float py, float x1, float y1,
                                float x2, float y2) {
    float ab_x = x2 - x1;
    float ab_y = y2 - y1;

    float ap_x = px - x1;
    float ap_y = py - y1;

    float bp_x = px - x2;
    float bp_y = py - y2;

    float ab_ap = ab_x * ap_x + ab_y * ap_y;
    float ab_ab = ab_x * ab_x + ab_y * ab_y;
    float t = ab_ap / ab_ab;

    // Project point P onto the line segment AB
    if (t < 0.0f) {
        // P is closer to A
        return std::sqrt(ap_x * ap_x + ap_y * ap_y);
    }
    else if (t > 1.0f) {
        // P is closer to B
        return std::sqrt(bp_x * bp_x + bp_y * bp_y);
    }
    else {
        // The projection is on the segment
        float proj_x = x1 + t * ab_x;
        float proj_y = y1 + t * ab_y;
        return std::sqrt((px - proj_x) * (px - proj_x) +
                         (py - proj_y) * (py - proj_y));
    }
}

}  // namespace math_utils

#endif  // MATH_UTILS_HPP

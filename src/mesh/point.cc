#include "point.h"

namespace xpt {

namespace mesh {

Point::Point(const float x, const float y) {
  position = {x, y};
}

std::string Point::to_str(int precision) const {
  // Print position with given precision
  std::ostringstream output;
  output << std::fixed << std::setprecision(precision)
         << "(" << position.first << ", " << position.second << ")";
  return output.str();
}

bool Point::operator<(const Point &rhs) const noexcept {
  if (position.first > rhs.position.first) {
    return false;
  } else if (position.second > rhs.position.second) {
    return false;
  } else if (*this == rhs) {
    return false;
  }
  return true;
}

bool Point::operator>(const Point &rhs) const noexcept {
  if (position.first < rhs.position.first) {
    return false;
  } else if (position.second < rhs.position.second) {
    return false;
  } else if (*this == rhs) {
    return false;
  }
  return true;
}

} // namespace mesh

} // namespace xpt

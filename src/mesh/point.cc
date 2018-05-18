#include "point.h"

namespace xpt {

namespace mesh {

Point::Point(const float x, const float y) {
  position_ = {x, y};
}

std::string Point::to_str(int precision) const {
  // Print position with given precision
  std::ostringstream output;
  output << std::fixed << std::setprecision(precision)
         << "(" << position_.first << ", " << position_.second << ")";
  return output.str();
}

// Arithmetic Operators

Point Point::operator-() const {
  Point temp{-(*this).x_, -(*this).y_};
  return temp;
}

Point& Point::operator+=(const Coordinate &rhs) {
  (*this).position_.first += rhs.first;
  (*this).position_.second += rhs.second;
  return *this;
}

Point& Point::operator+=(const Point &rhs) {
  (*this).position_.first += rhs.position_.first;
  (*this).position_.second += rhs.position_.second;
  return *this;
}

Point& Point::operator-=(const Coordinate &rhs) {
  (*this).position_.first -= rhs.first;
  (*this).position_.second -= rhs.second;
  return *this;
}

Point& Point::operator-=(const Point &rhs) {
  *this += -rhs;
  return *this;
}

Point Point::operator+(const Coordinate &rhs) const {
  Point temp(*this);
  return temp += rhs;
}

Point Point::operator+(const Point &rhs) const {
  Point temp(*this);
  return temp += rhs;
}

// Comparison Operators

bool Point::operator<(const Point &rhs) const noexcept {
  if (position_.first > rhs.position_.first) {
    return false;
  } else if (position_.second > rhs.position_.second) {
    return false;
  } else if (*this == rhs) {
    return false;
  }
  return true;
}

bool Point::operator>(const Point &rhs) const noexcept {
  if (position_.first < rhs.position_.first) {
    return false;
  } else if (position_.second < rhs.position_.second) {
    return false;
  } else if (*this == rhs) {
    return false;
  }
  return true;
}

} // namespace mesh

} // namespace xpt

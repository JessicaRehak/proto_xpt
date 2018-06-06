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

// Arithmetic Operators

Point Point::operator-() const {
  Point temp{-(*this).x, -(*this).y};
  return temp;
}

Point& Point::operator+=(const Coordinate &rhs) {
  (*this).position.first += rhs.first;
  (*this).position.second += rhs.second;
  return *this;
}

Point& Point::operator+=(const Point &rhs) {
  (*this).position.first += rhs.position.first;
  (*this).position.second += rhs.position.second;
  return *this;
}

Point& Point::operator-=(const Coordinate &rhs) {
  (*this).position.first -= rhs.first;
  (*this).position.second -= rhs.second;
  return *this;
}

Point& Point::operator-=(const Point &rhs) {
  *this += -rhs;
  return *this;
}

Point& Point::operator*=(const float rhs) {
  (*this).x *= rhs;
  (*this).y *= rhs;
  return *this;
}

Point& Point::operator/=(const float rhs) {
  (*this).x /= rhs;
  (*this).y /= rhs;
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

Point Point::operator-(const Coordinate &rhs) const {
  Point temp(*this);
  return temp -= rhs;
}

Point Point::operator-(const Point &rhs) const {
  Point temp(*this);
  return temp -= rhs;
}

Point Point::operator*(const float rhs) const {
  Point temp{rhs*(*this).x, rhs*(*this).y};
  return temp;
};

Point Point::operator/(const float rhs) const {
  Point temp{(*this).x/rhs, (*this).y/rhs};
  return temp;
};

// Comparison Operators

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

#ifndef PROTO_XPT_MESH_POINT_H_
#define PROTO_XPT_MESH_POINT_H_

#include <cmath>

#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <utility>

namespace xpt {

namespace mesh {

struct Point {
  // 2D Point struct
  using Coordinate = std::pair<float, float>;
  
  explicit Point(const Coordinate coordinates) : position_(coordinates) {};
  Point(const float, const float);
  ~Point() = default;
  
  Coordinate position_;
  float& x_{position_.first};
  float& y_{position_.second};

  float Length() const { return std::sqrt(std::pow(x_, 2) + std::pow(y_, 2)); };

  std::string to_str(int precision = 2) const;
  
  // Arithmetic Operators
  Point& operator+=(const Coordinate &rhs);
  Point& operator+=(const Point &rhs);

  Point operator+(const Coordinate &rhs) const;
  Point operator+(const Point &rhs) const;
  
  // Equivalence operators
  inline bool operator==(const Point &rhs) const noexcept {
    return position_ == rhs.position_; }

  inline bool operator!=(const Point &rhs) const noexcept {
    return position_ != rhs.position_; }

  // Checks x^2 + y^2 == r^2
  bool operator==(float r) const { return (*this).Length() == r; };
  bool operator!=(float r) const { return !(*this == r); };

  // Comparison operators
  bool operator<(const Point &rhs) const noexcept;
  bool operator>(const Point &rhs) const noexcept;
  inline bool operator<=(const Point &rhs) const noexcept {
    return *this < rhs || *this == rhs;};
  inline bool operator>=(const Point &rhs) const noexcept {
    return *this > rhs || *this == rhs;};
  
  // // Move constructor and move assign
  Point(Point&&) = default;
  Point& operator=(Point&&) = default;
  
  // // Copy constructor and copy assign
  Point(const Point&) = default;
  Point& operator=(const Point&) = default;
};

} // namespace mesh

} // namespace xpt

#endif //PROTO_XPT_MESH_POINT_H_

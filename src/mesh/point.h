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

using Coordinate = std::pair<float, float>;

struct Point {
  // 2D Point struct
  //using Coordinate = std::pair<float, float>;
  
  explicit Point(const Coordinate coordinates) : position(coordinates) {};
  Point(const float, const float);
  ~Point() = default;
  
  Coordinate position;
  float& x{position.first};
  float& y{position.second};

  float Length() const { return std::sqrt(std::pow(x, 2) + std::pow(y, 2)); };

  std::string to_str(int precision = 2) const;
  
  // Arithmetic Operators

  Point operator-() const;
  
  Point& operator+=(const Coordinate &rhs);
  Point& operator+=(const Point &rhs);

  Point operator+(const Coordinate &rhs) const;
  Point operator+(const Point &rhs) const;

  Point& operator-=(const Coordinate &rhs);
  Point& operator-=(const Point &rhs);
  
  // Equivalence operators
  inline bool operator==(const Point &rhs) const noexcept {
    return position == rhs.position; }

  inline bool operator!=(const Point &rhs) const noexcept {
    return position != rhs.position; }

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

#ifndef PROTO_XPT_MESH_POINT_H_
#define PROTO_XPT_MESH_POINT_H_

#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <utility>

namespace xpt {

namespace mesh {

struct Point {
  // 2D Point struct
  using Coordinates = std::pair<float, float>;
  
  explicit Point(const Coordinates coordinates) : position(coordinates) {};
  explicit Point(const float, const float);
  //~Point() = default;
  
  Coordinates position;

  std::string to_str(int precision = 2) const;
  
  // // Arithmetic Operators
  // Point& operator+=(const Coordinates &rhs);
  
  // // Comparison operators
  // inline bool operator==(const Point &rhs) const {
  //   return this.position == rhs.position; }

  // inline bool operator!=(const Point &rhs) const {
  //   return this.position != rhs.position; }
  
  // // Move constructor and move assign
  // Point(Point&&) = default;
  // Point& operator=(Point&&) = default;
  
  // // Copy constructor and copy assign
  // Point(const Point&) = default;
  // Point& operator=(const Point&) = default;
  
};

} // namespace mesh

} // namespace xpt

#endif //PROTO_XPT_MESH_POINT_H_

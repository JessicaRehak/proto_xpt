#ifndef PROTO_XPT_MESH_NODE_H_
#define PROTO_XPT_MESH_NODE_H_

#include <cmath>

#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <utility>

namespace xpt {

namespace mesh {

using Coordinate = std::pair<float, float>;

struct Node {
  // 2D Node struct to hold position and solution data
  
  Node(const Coordinate coordinates, const float value = 0, bool is_edge = false)
      : position(coordinates), value(value), is_edge(is_edge) {};
  Node(const float x, const float y, const float value = 0, bool is_edge = false)
      : value(value), is_edge(is_edge) { position = {x,y}; };
  ~Node() = default;
  
  Coordinate position;
  float& x{position.first};
  float& y{position.second};
  float value;
  bool is_edge;

  float Length() const { return std::sqrt(std::pow(x, 2) + std::pow(y, 2)); };
  
  // Arithmetic Operators

  Node operator-() const;
  
  Node& operator+=(const Coordinate &rhs);
  Node& operator+=(const Node &rhs);

  Node& operator-=(const Coordinate &rhs);
  Node& operator-=(const Node &rhs);

  Node& operator*=(const float rhs);
  Node& operator/=(const float rhs);
  
  Node operator+(const Coordinate &rhs) const;
  Node operator+(const Node &rhs) const;

  Node operator-(const Coordinate &rhs) const;
  Node operator-(const Node &rhs) const;

  Node operator*(const float rhs) const;
  Node operator/(const float rhs) const;
  
  // Equivalence operators
  inline bool operator==(const Node &rhs) const noexcept {
    return position == rhs.position; }

  inline bool operator!=(const Node &rhs) const noexcept {
    return position != rhs.position; }

  // Checks x^2 + y^2 == r^2
  bool operator==(float r) const { return (*this).Length() == r; };
  bool operator!=(float r) const { return !(*this == r); };

  // Comparison operators
  bool operator<(const Node &rhs) const noexcept;
  bool operator>(const Node &rhs) const noexcept;
  
  inline bool operator<=(const Node &rhs) const noexcept {
    return *this < rhs || *this == rhs;};
  inline bool operator>=(const Node &rhs) const noexcept {
    return *this > rhs || *this == rhs;};
  
  // // Move constructor and move assign
  Node(Node&&) = default;
  Node& operator=(Node&&) = default;
  
  // // Copy constructor and copy assign
  Node(const Node&) = default;
  Node& operator=(const Node&) = default;
};

std::string to_string(const Node node, const int precision = 2);


} // namespace mesh

} // namespace xpt

#endif //PROTO_XPT_MESH_NODE_H_

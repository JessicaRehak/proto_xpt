#ifndef PROTO_XPT_MESH_NODE_H_
#define PROTO_XPT_MESH_NODE_H_

#include "nodeI.h"

#include <cmath>

#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

namespace xpt {

namespace mesh {

class Node : public NodeI{
 private:
  Coordinate position_;
  float &x_ { position_.first };
  float &y_ { position_.second };
  float value_;
  bool is_edge_;
 public:
  // 2D Node struct to hold position and solution data
  
  explicit Node(const Coordinate coordinates, const float value = 0,
                bool is_edge = false)
      : position_(coordinates), value_(value), is_edge_(is_edge) {};
  Node(const float x, const float y, const float value = 0, bool is_edge = false)
      : value_(value), is_edge_(is_edge) { position_ = {x,y}; };
  ~Node() = default;

  // Setters and gutters
  float x() const override { return position_.first; };
  float y() const override { return position_.second; };
  float value() const override {return value_; };
  bool is_edge() const override {return is_edge_; };
  Coordinate position() const override { return position_; };

  Node& set_x(float x);
  Node& set_y(float y);
  Node& set_value(float value);
  Node& set_is_edge(bool is_edge);
  Node& set_position(Coordinate position);
  
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
    return position_ == rhs.position_; }

  inline bool operator!=(const Node &rhs) const noexcept {
    return position_ != rhs.position_; }

  // Checks x^2 + y^2 == r^2
  bool operator==(float r) const;
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
float Length(const Node node);

} // namespace mesh

} // namespace xpt

#endif //PROTO_XPT_MESH_NODE_H_

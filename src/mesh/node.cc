#include "node.h"

namespace xpt {

namespace mesh {

// Settters and getters

Node& Node::set_x(float x) {
  position_.first = x;
  return *this;
}
Node& Node::set_y(float y) {
  position_.second = y;
  return *this;
}

Node& Node::set_value(float value) {
  value_ = value;
  return *this;
}

Node& Node::set_is_edge(bool is_edge) {
  is_edge_ = is_edge;
  return *this;
}

Node& Node::set_position(Coordinate position) {
  position_ = position;
  return *this;
}

bool Node::operator==(float r) const {
  return Length(*this) == r;
}

// Arithmetic Operators

Node Node::operator-() const {
  Node temp{-(*this).x(), -(*this).y()};
  return temp;
}

Node& Node::operator+=(const Coordinate &rhs) {
  (*this).position_.first += rhs.first;
  (*this).position_.second += rhs.second;
  return *this;
}

Node& Node::operator+=(const Node &rhs) {
  (*this).position_.first += rhs.position_.first;
  (*this).position_.second += rhs.position_.second;
  return *this;
}

Node& Node::operator-=(const Coordinate &rhs) {
  (*this).position_.first -= rhs.first;
  (*this).position_.second -= rhs.second;
  return *this;
}

Node& Node::operator-=(const Node &rhs) {
  *this += -rhs;
  return *this;
}

Node& Node::operator*=(const float rhs) {
  (*this).x_ *= rhs;
  (*this).y_ *= rhs;
  return *this;
}

Node& Node::operator/=(const float rhs) {
  (*this).x_ /= rhs;
  (*this).y_ /= rhs;
  return *this;
}

Node Node::operator+(const Coordinate &rhs) const {
  Node temp(*this);
  return temp += rhs;
}

Node Node::operator+(const Node &rhs) const {
  Node temp(*this);
  return temp += rhs;
}

Node Node::operator-(const Coordinate &rhs) const {
  Node temp(*this);
  return temp -= rhs;
}

Node Node::operator-(const Node &rhs) const {
  Node temp(*this);
  return temp -= rhs;
}

Node Node::operator*(const float rhs) const {
  Node temp{rhs*(*this).x_, rhs*(*this).y_};
  return temp;
};

Node Node::operator/(const float rhs) const {
  Node temp{(*this).x_/rhs, (*this).y_/rhs};
  return temp;
};

// Comparison Operators

bool Node::operator<(const Node &rhs) const noexcept {
  if (position_.first > rhs.position_.first) {
    return false;
  } else if (position_.second > rhs.position_.second) {
    return false;
  } else if (*this == rhs) {
    return false;
  }
  return true;
}

bool Node::operator>(const Node &rhs) const noexcept {
  if (position_.first < rhs.position_.first) {
    return false;
  } else if (position_.second < rhs.position_.second) {
    return false;
  } else if (*this == rhs) {
    return false;
  }
  return true;
}

// Non-member functions

std::string to_string(const Node node, int precision) {
  // Print position with given precision
  std::ostringstream output;
  output << std::fixed << std::setprecision(precision)
         << "(" << node.x() << ", " << node.y() << ")";
  return output.str();
}

float Length(const Node node) {
  return std::sqrt(std::pow(node.x(), 2) + std::pow(node.y(), 2));
}


} // namespace mesh

} // namespace xpt

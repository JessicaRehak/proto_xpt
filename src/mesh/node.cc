#include "node.h"

namespace xpt {

namespace mesh {

std::string to_string(const Node node, int precision) {
  // Print position with given precision
  std::ostringstream output;
  output << std::fixed << std::setprecision(precision)
         << "(" << node.position.first << ", " << node.position.second << ")";
  return output.str();
}

// Arithmetic Operators

Node Node::operator-() const {
  Node temp{-(*this).x, -(*this).y};
  return temp;
}

Node& Node::operator+=(const Coordinate &rhs) {
  (*this).position.first += rhs.first;
  (*this).position.second += rhs.second;
  return *this;
}

Node& Node::operator+=(const Node &rhs) {
  (*this).position.first += rhs.position.first;
  (*this).position.second += rhs.position.second;
  return *this;
}

Node& Node::operator-=(const Coordinate &rhs) {
  (*this).position.first -= rhs.first;
  (*this).position.second -= rhs.second;
  return *this;
}

Node& Node::operator-=(const Node &rhs) {
  *this += -rhs;
  return *this;
}

Node& Node::operator*=(const float rhs) {
  (*this).x *= rhs;
  (*this).y *= rhs;
  return *this;
}

Node& Node::operator/=(const float rhs) {
  (*this).x /= rhs;
  (*this).y /= rhs;
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
  Node temp{rhs*(*this).x, rhs*(*this).y};
  return temp;
};

Node Node::operator/(const float rhs) const {
  Node temp{(*this).x/rhs, (*this).y/rhs};
  return temp;
};

// Comparison Operators

bool Node::operator<(const Node &rhs) const noexcept {
  if (position.first > rhs.position.first) {
    return false;
  } else if (position.second > rhs.position.second) {
    return false;
  } else if (*this == rhs) {
    return false;
  }
  return true;
}

bool Node::operator>(const Node &rhs) const noexcept {
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

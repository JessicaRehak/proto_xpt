#ifndef PROTO_XPT_MESH_NODE_H_
#define PROTO_XPT_MESH_NODE_H_

#include "point.h"

namespace xpt {

namespace mesh {

class Node : public Point {
  // Node class for storing solution data and "edge" status
 public:
  explicit Node(const Coordinate coordinates, const float value = 0,
                bool is_edge = false) :
      Point(coordinates), value_(value), is_edge_(is_edge) {};

  float get_value() const { return value_; };
  bool get_is_edge() const { return is_edge_; };
  
  Node &set_value(float new_value) { value_ = new_value; return *this; };
  Node &set_is_edge(bool new_is_edge) { is_edge_ = new_is_edge; return *this; };
  
 private:
  bool is_edge_ = false;
  float value_;
};

} // namespace mesh

} // namespace xpt

#endif //PROTO_XPT_MESH_NODE_H_

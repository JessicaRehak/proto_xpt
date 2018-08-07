#ifndef PROTO_XPT_MESH_NODEI_H_
#define PROTO_XPT_MESH_NODEI_H_

#include <utility>

namespace xpt {

namespace mesh {

using Coordinate = std::pair<float, float>;

class NodeI { 
  virtual float x() const = 0;
  virtual float y() const = 0;
  virtual float value() const = 0;
  virtual bool is_edge() const = 0;
  virtual Coordinate position() const = 0;
};

} // namespace mesh

} // namespace xpt

#endif // PROTO_XPT_MESH_NODEI_H_

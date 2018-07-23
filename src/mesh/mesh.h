#ifndef PROTO_XPT_MESH_MESH_H_
#define PROTO_XPT_MESH_MESH_H_

#include <iostream>
#include <memory>
#include <vector>

#include "point.h"

namespace xpt {

namespace mesh {

class Mesh {
 public:
  //Cartesian Mesh

  explicit Mesh() {};
  ~Mesh() = default;

  std::vector<Point> points_;
};

std::unique_ptr<Mesh> ImportMeshFromStream(std::istream &input_stream);
  
} //namespace mesh

} //namespace xpt

#endif

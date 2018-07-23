#include "mesh.h"

namespace xpt {

namespace mesh {

std::unique_ptr<Mesh> ImportMeshFromStream(std::istream &input_stream) {
  return std::make_unique<Mesh>();
}

} //namespace mesh

} //namespace xpt

#include "mesh.h"
#include "mesh2dcartesian.pb.h"

namespace xpt {

namespace mesh {

std::unique_ptr<Mesh> ImportMeshFromStream(std::istream &input_stream) {

  proto_xpt_protobuf::Mesh2DCartesian import_mesh;
  if (!import_mesh.ParseFromIstream(&input_stream)) {
    throw std::runtime_error("Failed to parse serialized string");
  }

  std::unique_ptr<Mesh> new_mesh = std::make_unique<Mesh>();
  new_mesh->set_x_max(import_mesh.x_max());
  new_mesh->set_x_min(import_mesh.x_min());
  new_mesh->set_y_max(import_mesh.y_max());
  new_mesh->set_y_min(import_mesh.y_min());
  
  return new_mesh;
}

} //namespace mesh

} //namespace xpt

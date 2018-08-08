#include "mesh.h"
#include "mesh2dcartesian.pb.h"

namespace xpt {

namespace mesh {

void Mesh::AddNode(int index, std::unique_ptr<Node> node) {
  nodes_.insert({index, std::move(node)});
}

const Node &Mesh::GetNode(int index) const {
  return *(nodes_.find(index)->second);
}

// Non-member functions

// std::unique_ptr<Mesh> ImportMeshFromStream(std::istream &input_stream) {

//   proto_xpt_protobuf::Mesh2DCartesian import_mesh;
//   if (!import_mesh.ParseFromIstream(&input_stream)) {
//     throw std::runtime_error("Failed to parse serialized string");
//   }

//   std::unique_ptr<Mesh> new_mesh =
//       std::make_unique<Mesh>(import_mesh.x_min(), import_mesh.x_max(),
//                              import_mesh.y_min(), import_mesh.y_max());

//   for (size_t i = 0; i < import_mesh.nodes_size(); ++i) {
//     Coordinate position{import_mesh.nodes(i).x(), import_mesh.nodes(i).y()};
//     std::unique_ptr<Node> new_node = std::make_unique<Node>(position);
//     new_mesh->AdoptNode(i, std::move(new_node));
//   }
//   return new_mesh;
// }



// std::string to_string(const Mesh &mesh) {
//   // Prints information about the mesh
//   std::stringstream return_string;
//   return_string << "Mesh parameters\n"
//                 << "x_min: " << mesh.get_x_min() << "\tx_max: "<< mesh.get_x_max()
//                 << "\ny_min: " << mesh.get_y_min() << "\ty_max: " << mesh.get_y_max()
//                 << std::endl;
//   return_string << "Nodes\n";
//   for (auto node : mesh.get_nodes()) {
//     return_string << node.first << ": " << xpt::mesh::to_string(node.second) << "\n";
//   }   
//   return return_string.str();
// }

} //namespace mesh

} //namespace xpt

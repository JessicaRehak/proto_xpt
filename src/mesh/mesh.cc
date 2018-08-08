#include "mesh.h"
#include "mesh2dcartesian.pb.h"

namespace xpt {

namespace mesh {

void Mesh::AddNode(int index, std::unique_ptr<Node> node) {
  nodes_.insert({index, std::move(node)});
}

const Node &Mesh::GetNode(int index) const {
  auto node_ptr = nodes_.find(index);
  if (node_ptr == nodes_.end())
    throw std::runtime_error("Bad node index: " + std::to_string(index));
  return *(node_ptr->second);
}

// Non-member functions

std::unique_ptr<Mesh> ImportMeshFromStream(std::istream &input_stream) {

  proto_xpt_protobuf::Mesh2DCartesian import_mesh;
  if (!import_mesh.ParseFromIstream(&input_stream)) {
    throw std::runtime_error("Failed to parse serialized string");
  }

  std::unique_ptr<Mesh> new_mesh =
      std::make_unique<Mesh>(import_mesh.x_min(), import_mesh.x_max(),
                             import_mesh.y_min(), import_mesh.y_max());

  for (size_t i = 0; i < import_mesh.nodes_size(); ++i) {
    Coordinate position{import_mesh.nodes(i).x(), import_mesh.nodes(i).y()};
    std::unique_ptr<Node> new_node = std::make_unique<Node>(position);
    new_mesh->AddNode(i, std::move(new_node));
  }

  
  for (size_t i = 0; i < import_mesh.triangles_size(); ++i) {
    Triangle new_triangle;
    for (auto cit = import_mesh.triangles(i).nodes().cbegin();
         cit < import_mesh.triangles(i).nodes().cend();
         ++cit) {
      new_triangle.push_back(*cit);
    }
    new_mesh->AddTriangle(new_triangle);
  }  
  
  return new_mesh;
}

std::string to_string(const Mesh &mesh) {
  // Prints information about the mesh
  std::stringstream return_string;
  return_string << "Mesh parameters\n"
                << "x_min: " << mesh.x_min() << "\tx_max: "<< mesh.x_max()
                << "\ny_min: " << mesh.y_min() << "\ty_max: " << mesh.y_max()
                << std::endl;
  return_string << "Nodes\n";
  for (const auto &node : mesh.nodes()) {
    return_string << node.first << ": " << xpt::mesh::to_string(*node.second) << "\n";
  }
  return_string << "Elements\n";
  for (auto triangle : mesh.triangles()) {
    for (int val : triangle) {
      return_string << val << " ";
    }
    return_string << "\n";
  }
      
  
  return return_string.str();
}

} //namespace mesh

} //namespace xpt

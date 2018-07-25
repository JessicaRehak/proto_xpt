#include "../mesh.h"
#include "../point.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <array>
#include <iostream>
#include <memory>
#include <utility>

#include "../mesh2dcartesian.pb.h"

using Node = proto_xpt_protobuf::Mesh2DCartesian_Node;
using Triangle = proto_xpt_protobuf::Mesh2DCartesian_Triangle;

class MeshTest : public ::testing::Test {
 protected:
  void SetUp() override;
  std::istringstream input_string_stream_;
  proto_xpt_protobuf::Mesh2DCartesian test_proto_mesh_{};
};

void MeshTest::SetUp() {
  // Create a serialized Mesh file for construction
  test_proto_mesh_.set_x_max(5.0);
  test_proto_mesh_.set_x_min(-1.0);
  test_proto_mesh_.set_y_max(5.0);
  test_proto_mesh_.set_y_min(-1.0);

  input_string_stream_.str(test_proto_mesh_.SerializeAsString());
  
  // std::array<std::pair<float, float>, 5>
  //     nodes{std::make_pair(0.0, 0.0), std::make_pair(0.0, 5.0),
  //       std::make_pair(5.0, 0.0), std::make_pair(5.0, 5.0), std::make_pair(2.5, 2.5)};

  // for (auto pair : nodes) {
  //   Node *new_node = test_proto_mesh_.add_nodes();
  //   new_node->set_x(pair.first);
  //   new_node->set_y(pair.second);
  // }

  // std::array<std::tuple<int, int, int>, 4>
  //     triangles{std::make_tuple(0, 1, 5), std::make_tuple(0, 2, 5),
  //       std::make_tuple(4, 1, 5), std::make_tuple(4,2,5)};

  // for (auto triangle : triangles) {
  //   Triangle *new_triangle = test_proto_mesh_.add_triangles();
  //   new_triangle->set_nodes(0, std::get<0>(triangle));
  //   new_triangle->set_nodes(1, std::get<1>(triangle));
  //   new_triangle->set_nodes(2, std::get<2>(triangle)); 
  // }
}

TEST_F(MeshTest, Initial) {
  std::unique_ptr<xpt::mesh::Mesh> test_mesh =
      xpt::mesh::ImportMeshFromStream(input_string_stream_);
  ASSERT_EQ(test_mesh->get_x_min(), -1.0);
  ASSERT_EQ(test_mesh->get_x_max(), 5.0);
  ASSERT_EQ(test_mesh->get_y_min(), -1.0);
  ASSERT_EQ(test_mesh->get_y_max(), 5.0);
}

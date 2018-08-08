#include "../mesh.h"
#include "../node.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <google/protobuf/text_format.h>

#include <array>
#include <iostream>
#include <memory>
#include <utility>

#include "../mesh2dcartesian.pb.h"

using ProtoNode = proto_xpt_protobuf::Mesh2DCartesian_Node;
using ProtoTriangle = proto_xpt_protobuf::Mesh2DCartesian_Triangle;

class MeshIntTest : public ::testing::Test {
 protected:
  void SetUp() override {};
  std::unique_ptr<xpt::mesh::Mesh> test_mesh =
      std::make_unique<xpt::mesh::Mesh>();
};

class MeshProtoTest : public MeshIntTest {
 protected:
  std::istringstream input_string_stream_;
  proto_xpt_protobuf::Mesh2DCartesian test_proto_mesh_{};
  void SetUp() override;
};

void MeshProtoTest::SetUp() {
  // Create a serialized Mesh file for construction
  test_proto_mesh_.set_x_max(5.0);
  test_proto_mesh_.set_x_min(-1.0);
  test_proto_mesh_.set_y_max(5.0);
  test_proto_mesh_.set_y_min(-1.0);
  
  std::array<std::pair<float, float>, 5>
       nodes{std::make_pair(0.0, 0.0), std::make_pair(0.0, 5.0),
         std::make_pair(5.0, 0.0), std::make_pair(5.0, 5.0), std::make_pair(2.5, 2.5)};

  for (auto pair : nodes) {
    ProtoNode *new_node = test_proto_mesh_.add_nodes();
    new_node->set_x(pair.first);
    new_node->set_y(pair.second);
  }

  std::array<std::tuple<int, int, int>, 4>
      triangles{std::make_tuple(0, 1, 5), std::make_tuple(0, 2, 5),
        std::make_tuple(4, 1, 5), std::make_tuple(4,2,5)};
  
  for (auto triangle : triangles) {
    ProtoTriangle *new_triangle = test_proto_mesh_.add_triangles();
    new_triangle->add_nodes(std::get<0>(triangle));
    new_triangle->add_nodes(std::get<1>(triangle));
    new_triangle->add_nodes(std::get<2>(triangle)); 
  }
  
  input_string_stream_.str(test_proto_mesh_.SerializeAsString());
  
  test_mesh = xpt::mesh::ImportMeshFromStream(input_string_stream_);

}

TEST_F(MeshIntTest, AddNode) {
  auto new_node = std::make_unique<xpt::mesh::Node>(0.0, 0.0);
  test_mesh->AddNode(0, std::move(new_node));
  ASSERT_EQ(test_mesh->nodes().find(0)->second->x(), 0.0);
  ASSERT_EQ(test_mesh->nodes().find(0)->second->y(), 0.0);
}

TEST_F(MeshIntTest, GetNode) {
  auto new_node = std::make_unique<xpt::mesh::Node>(-2.3, 100.3);
  test_mesh->AddNode(0, std::move(new_node));
  EXPECT_FLOAT_EQ(test_mesh->GetNode(0).x(), -2.3);
  EXPECT_FLOAT_EQ(test_mesh->GetNode(0).y(), 100.3);
}

TEST_F(MeshIntTest, BadNode) {
  EXPECT_THROW(test_mesh->GetNode(0).x(), std::runtime_error);
  auto new_node = std::make_unique<xpt::mesh::Node>(-2.3, 100.3);
  test_mesh->AddNode(0, std::move(new_node));
  EXPECT_THROW(test_mesh->GetNode(1).x(), std::runtime_error);
}

TEST_F(MeshProtoTest, MeshProperties) {
  ASSERT_EQ(test_mesh->x_min(), -1.0);
  ASSERT_EQ(test_mesh->x_max(), 5.0);
  ASSERT_EQ(test_mesh->y_min(), -1.0);
  ASSERT_EQ(test_mesh->y_max(), 5.0);
}

TEST_F(MeshProtoTest, MeshNodes) {
  xpt::mesh::Coordinate origin{0.0, 0.0};
  ASSERT_EQ(test_mesh->nodes().size(), 5);
}

TEST_F(MeshProtoTest, MeshPrint) {

  std::string mesh_string = xpt::mesh::to_string(*test_mesh);
  std::cout << mesh_string << std::endl;
  for (const auto &node : test_mesh->nodes()) {
    std::string node_string = xpt::mesh::to_string(*node.second);
    EXPECT_THAT(mesh_string, ::testing::HasSubstr(node_string));
  }
}

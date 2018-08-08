#include "../mesh.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <array>
#include <iostream>
#include <memory>
#include <utility>

#include "../mesh2dcartesian.pb.h"

using ProtoNode = proto_xpt_protobuf::Mesh2DCartesian_Node;
using ProtoTriangle = proto_xpt_protobuf::Mesh2DCartesian_Triangle;

class MeshTest : public ::testing::Test {
 protected:
  void SetUp() override;
  xpt::mesh::Mesh test_mesh;
  
};

void MeshTest::SetUp() {

}

TEST_F(MeshTest, AddTriangle) {
  xpt::mesh::Triangle new_triangle{0, 3, 2};
  test_mesh.AddTriangle(new_triangle);
  EXPECT_EQ(test_mesh.triangles()[0], new_triangle);
}

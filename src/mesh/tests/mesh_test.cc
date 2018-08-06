#include "../mesh.h"
#include "../node.h"

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
};

void MeshTest::SetUp() {

}

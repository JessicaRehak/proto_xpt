#include "../node.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

class NodeTest : public ::testing::Test {
 protected:
  void SetUp() override {};
};

TEST_F(NodeTest, DefaultInit) {
  xpt::mesh::Coordinate position{1.0, -2.0};
  xpt::mesh::Node test_node(position);

  ASSERT_EQ(test_node.get_value(), 0.0);
  ASSERT_FALSE(test_node.get_is_edge());
}

TEST_F(NodeTest, ValueInit) {
  xpt::mesh::Coordinate position{1.0, -2.0};
  xpt::mesh::Node test_node(position, 10.0, true);

  ASSERT_EQ(test_node.get_value(), 10.0);
  ASSERT_TRUE(test_node.get_is_edge());
}

TEST_F(NodeTest, SetValues) {
  xpt::mesh::Coordinate position{1.0, -2.0};
  xpt::mesh::Node test_node(position, 10.0);
  test_node.set_value(20.0);
  test_node.set_is_edge(true);
  ASSERT_EQ(test_node.get_value(), 20.0);
  ASSERT_TRUE(test_node.get_is_edge());
}


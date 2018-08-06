#include "../node.h"

#include <cmath>

#include <array>
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <utility>

class NodeTest : public ::testing::Test {
 protected:
  void SetUp() override {};
  float x = 1.0, y = -10.0;
  xpt::mesh::Node testNode{x, y};
};

class NodeCompareTest : public NodeTest {
  // Fixture for testing comparison operators
 protected:
  float gt_x = 2.23*x, lt_x = 0.534*x;
  float gt_y = -2.394*y, lt_y = 10.56*y;
  xpt::mesh::Node testNode_gt{gt_x, gt_y};
  xpt::mesh::Node testNode_lt{lt_x, lt_y};
  xpt::mesh::Node testNode_nt{gt_x, lt_y}; //not gt or lt
  xpt::mesh::Node testNode_nt_2{lt_x, gt_y}; //not gt or lt
  xpt::mesh::Node testNode_eq{x, y};
  xpt::mesh::Node testNode_ne{3.4, 0.0};
};

class NodeShiftTest : public NodeTest {
  // Fixture for comparing shift operators (arithmetic)
 protected:
  xpt::mesh::Coordinate origin{0.0, 0.0};
  xpt::mesh::Coordinate p2{10.0, 20.0}; // Shift node
  xpt::mesh::Node shift_node{p2};
  xpt::mesh::Node refl_node{-x, -y};
  // all in format testCoord_xs where x is the number of shifts by p2
  xpt::mesh::Coordinate testCoord_1s{x + p2.first, y + p2.second};
  xpt::mesh::Coordinate testCoord_2s{x + 2*p2.first, y + 2*p2.second};
  xpt::mesh::Coordinate testCoord_3s{x + 3*p2.first, y + 3*p2.second};
  xpt::mesh::Coordinate testCoord_4s{x + 4*p2.first, y + 4*p2.second};

  xpt::mesh::Coordinate testCoord_2m{2*x, 2*y};
  xpt::mesh::Coordinate testCoord_3m{3*x, 3*y};
  xpt::mesh::Coordinate testCoord_4m{4*x, 4*y};

  // For ease of writing tests these are stored in an array
  std::array<xpt::mesh::Coordinate, 5>
  testCoord_s = {{testNode.position, testCoord_1s, testCoord_2s,
                  testCoord_3s, testCoord_4s}};

  std::array<xpt::mesh::Coordinate, 5>
  testCoord_m = {{origin, testNode.position, testCoord_2m,
                  testCoord_3m, testCoord_4m}};
};

TEST_F(NodeTest, PairConstructor) {
  xpt::mesh::Coordinate position{1.0, -4.0};
  xpt::mesh::Node testNode_c{position};
  ASSERT_EQ(testNode_c.position, position);
  ASSERT_FALSE(testNode_c.is_edge);
  ASSERT_EQ(testNode_c.value, 0);
 }

TEST_F(NodeTest, FloatConstructor) {
  xpt::mesh::Coordinate position{1.0, -4.0};
  xpt::mesh::Node testNode_c{1.0, -4.0};
  ASSERT_EQ(testNode_c.position, position);
  ASSERT_FALSE(testNode_c.is_edge);
  ASSERT_EQ(testNode_c.value, 0);
}

TEST_F(NodeTest, Length) {
  float ans = std::sqrt(101);
  ASSERT_EQ(testNode.Length(), ans);
}

TEST_F(NodeTest, Accessors) {
  xpt::mesh::Coordinate ans{3.0, -10.0};
  xpt::mesh::Coordinate ans2{3.0, 12.7};
  
  testNode.x = 3.0;
  ASSERT_EQ(testNode.position, ans);
  testNode.y = 12.7;
  ASSERT_EQ(testNode.position, ans2);
}

TEST_F(NodeTest, toStr_default) {
  ASSERT_EQ(xpt::mesh::to_string(testNode), "(1.00, -10.00)");
}

TEST_F(NodeTest, toStr_specific) {
  std::string output = xpt::mesh::to_string(testNode, 4);
  ASSERT_EQ(output, "(1.0000, -10.0000)");
}

TEST_F(NodeCompareTest, EquivOps) {
  ASSERT_TRUE(testNode == testNode_eq);
  ASSERT_FALSE(testNode == testNode_ne);
  ASSERT_TRUE(testNode != testNode_ne);
  ASSERT_FALSE(testNode != testNode_eq);
}

TEST_F(NodeCompareTest, EquivFloat) {
  float ans = std::sqrt(101);
  ASSERT_TRUE(testNode == ans);
  ASSERT_FALSE(testNode != ans);
  ASSERT_FALSE(testNode == 34.2);
  ASSERT_TRUE(testNode != 34.2);
}

TEST_F(NodeCompareTest, ComparisonOps) {
  ASSERT_TRUE(testNode_gt > testNode);
  ASSERT_TRUE(testNode_lt < testNode);
  ASSERT_FALSE(testNode_gt < testNode);
  ASSERT_FALSE(testNode_lt > testNode);
  ASSERT_FALSE(testNode_eq > testNode);
  ASSERT_FALSE(testNode_eq < testNode);
  ASSERT_FALSE(testNode_nt > testNode);
  ASSERT_FALSE(testNode_nt < testNode);
  ASSERT_FALSE(testNode_nt_2 > testNode);
  ASSERT_FALSE(testNode_nt_2 < testNode);
}

TEST_F(NodeCompareTest, ComparisonEqOps) {
  ASSERT_TRUE(testNode_gt >= testNode);
  ASSERT_TRUE(testNode_lt <= testNode);
  ASSERT_FALSE(testNode_gt <= testNode);
  ASSERT_FALSE(testNode_lt >= testNode);
  ASSERT_TRUE(testNode_eq >= testNode);
  ASSERT_TRUE(testNode_eq <= testNode);
  ASSERT_FALSE(testNode_nt >= testNode);
  ASSERT_FALSE(testNode_nt <= testNode);
  ASSERT_FALSE(testNode_nt_2 >= testNode);
  ASSERT_FALSE(testNode_nt_2 <= testNode);
}

TEST_F(NodeShiftTest, UnaryMinusOp) {
  ASSERT_EQ(-testNode, refl_node);
}

TEST_F(NodeShiftTest, PlusMinusBinOpsPair) {
  testNode += p2;
  ASSERT_EQ(testNode.position, testCoord_s[1]);
  (testNode += p2) += p2;
  ASSERT_EQ(testNode.position, testCoord_s[3]);
  (testNode -= p2) -= p2;
  ASSERT_EQ(testNode.position, testCoord_s[1]);
  testNode -= p2;
  ASSERT_EQ(testNode.position, testCoord_s[0]);
}

TEST_F(NodeShiftTest, PlusMinusBinOpsNode) {

  testNode += shift_node;
  ASSERT_EQ(testNode.position, testCoord_s[1]);
  // Check chaining
  (testNode += shift_node) += shift_node;
  ASSERT_EQ(testNode.position, testCoord_s[3]);
  (testNode -= shift_node) -= shift_node;
  ASSERT_EQ(testNode.position, testCoord_s[1]);
  testNode -= shift_node;
  ASSERT_EQ(testNode.position, testCoord_s[0]);
}

TEST_F(NodeShiftTest, PlusMinusOpsPair) {
  xpt::mesh::Node new_node = testNode + p2;
  xpt::mesh::Node chain_node = (testNode + p2) + p2;
  xpt::mesh::Node zero_node = new_node - p2;
  xpt::mesh::Node zero_chain_node = (chain_node - p2) - p2;
  
  ASSERT_EQ(new_node.position, testCoord_s[1]);
  ASSERT_EQ(chain_node.position, testCoord_s[2]);
  ASSERT_EQ(zero_node.position, testCoord_s[0]);
  ASSERT_EQ(zero_chain_node.position, testCoord_s[0]);
}

TEST_F(NodeShiftTest, PlusMinusOpsNode) {
  xpt::mesh::Node new_node = testNode + shift_node;
  xpt::mesh::Node chain_node = (testNode + shift_node) + shift_node;
  xpt::mesh::Node zero_node = new_node - shift_node;
  xpt::mesh::Node zero_chain_node = (chain_node - shift_node) - shift_node;
  
  ASSERT_EQ(new_node.position, testCoord_s[1]);
  ASSERT_EQ(chain_node.position, testCoord_s[2]);
  ASSERT_EQ(zero_node.position, testCoord_s[0]);
  ASSERT_EQ(zero_chain_node.position, testCoord_s[0]);
}

TEST_F(NodeShiftTest, MultiplyOps) {
  xpt::mesh::Node new_node = testNode * 2;
  xpt::mesh::Node origin = testNode * 0.0;
  xpt::mesh::Node chain_node = (testNode * 2) * 2;

  ASSERT_EQ(new_node.position, testCoord_m[2]);
  ASSERT_EQ(origin.position, testCoord_m[0]);
  ASSERT_EQ(chain_node.position, testCoord_m[4]);
}

TEST_F(NodeShiftTest, MultiplyEqOps) {
  testNode *= 2;
  ASSERT_EQ(testNode.position, testCoord_m[2]);
  (testNode *= 0.5) *= 2;
  ASSERT_EQ(testNode.position, testCoord_m[2]);
}

TEST_F(NodeShiftTest, DivideOps) {
  xpt::mesh::Node new_node = testNode / 0.5;
  xpt::mesh::Node chain_node = (testNode / 0.5) / 0.5;

  ASSERT_EQ(new_node.position, testCoord_m[2]);
  ASSERT_EQ(chain_node.position, testCoord_m[4]);
}


TEST_F(NodeShiftTest, DivideEqOps) {
  testNode /= 0.5;
  ASSERT_EQ(testNode.position, testCoord_m[2]);
  (testNode /= 0.5) /= 2;
  ASSERT_EQ(testNode.position, testCoord_m[2]);
}


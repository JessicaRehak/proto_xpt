#include "../point.h"

#include <cmath>

#include <array>
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <utility>

class PointTest : public ::testing::Test {
 protected:
  void SetUp() override {};
  float x = 1.0, y = -10.0;
  xpt::mesh::Point testPoint{x, y};
};

class PointCompareTest : public PointTest {
  // Fixture for testing comparison operators
 protected:
  float gt_x = 2.23*x, lt_x = 0.534*x;
  float gt_y = -2.394*y, lt_y = 10.56*y;
  xpt::mesh::Point testPoint_gt{gt_x, gt_y};
  xpt::mesh::Point testPoint_lt{lt_x, lt_y};
  xpt::mesh::Point testPoint_nt{gt_x, lt_y}; //not gt or lt
  xpt::mesh::Point testPoint_nt_2{lt_x, gt_y}; //not gt or lt
  xpt::mesh::Point testPoint_eq{x, y};
  xpt::mesh::Point testPoint_ne{3.4, 0.0};
};

class PointShiftTest : public PointTest {
  // Fixture for comparing shift operators (arithmetic)
 protected:
  xpt::mesh::Coordinate p2{10.0, 20.0}; // Shift point
  xpt::mesh::Point shift_point{p2};
  xpt::mesh::Point refl_point{-x, -y};
  // all in format testCoord_xs where x is the number of shifts by p2
  xpt::mesh::Coordinate testCoord_1s{x + p2.first, y + p2.second};
  xpt::mesh::Coordinate testCoord_2s{x + 2*p2.first, y + 2*p2.second};
  xpt::mesh::Coordinate testCoord_3s{x + 3*p2.first, y + 3*p2.second};
  xpt::mesh::Coordinate testCoord_4s{x + 4*p2.first, y + 4*p2.second};

  // For ease of writing tests these are stored in an array
  std::array<xpt::mesh::Coordinate, 5>
  testCoord_s = {{testPoint.position, testCoord_1s, testCoord_2s,
                  testCoord_3s, testCoord_4s}};
};

TEST_F(PointTest, PairConstructor) {
  xpt::mesh::Coordinate position{1.0, -4.0};
  xpt::mesh::Point testPoint_c{position};
  ASSERT_EQ(testPoint_c.position, position);
 }

TEST_F(PointTest, FloatConstructor) {
  xpt::mesh::Coordinate position{1.0, -4.0};
  xpt::mesh::Point testPoint_c{1.0, -4.0};
  ASSERT_EQ(testPoint_c.position, position);
}

TEST_F(PointTest, Length) {
  float ans = std::sqrt(101);
  ASSERT_EQ(testPoint.Length(), ans);
}

TEST_F(PointTest, Accessors) {
  xpt::mesh::Coordinate ans{3.0, -10.0};
  xpt::mesh::Coordinate ans2{3.0, 12.7};
  
  testPoint.x = 3.0;
  ASSERT_EQ(testPoint.position, ans);
  testPoint.y = 12.7;
  ASSERT_EQ(testPoint.position, ans2);
}

TEST_F(PointTest, toStr_default) {
  ASSERT_EQ(testPoint.to_str(), "(1.00, -10.00)");
}

TEST_F(PointTest, toStr_specific) {
  ASSERT_EQ(testPoint.to_str(4), "(1.0000, -10.0000)");
}

TEST_F(PointCompareTest, EquivOps) {
  ASSERT_TRUE(testPoint == testPoint_eq);
  ASSERT_FALSE(testPoint == testPoint_ne);
  ASSERT_TRUE(testPoint != testPoint_ne);
  ASSERT_FALSE(testPoint != testPoint_eq);
}

TEST_F(PointCompareTest, EquivFloat) {
  float ans = std::sqrt(101);
  ASSERT_TRUE(testPoint == ans);
  ASSERT_FALSE(testPoint != ans);
  ASSERT_FALSE(testPoint == 34.2);
  ASSERT_TRUE(testPoint != 34.2);
}

TEST_F(PointCompareTest, ComparisonOps) {
  ASSERT_TRUE(testPoint_gt > testPoint);
  ASSERT_TRUE(testPoint_lt < testPoint);
  ASSERT_FALSE(testPoint_gt < testPoint);
  ASSERT_FALSE(testPoint_lt > testPoint);
  ASSERT_FALSE(testPoint_eq > testPoint);
  ASSERT_FALSE(testPoint_eq < testPoint);
  ASSERT_FALSE(testPoint_nt > testPoint);
  ASSERT_FALSE(testPoint_nt < testPoint);
  ASSERT_FALSE(testPoint_nt_2 > testPoint);
  ASSERT_FALSE(testPoint_nt_2 < testPoint);
}

TEST_F(PointCompareTest, ComparisonEqOps) {
  ASSERT_TRUE(testPoint_gt >= testPoint);
  ASSERT_TRUE(testPoint_lt <= testPoint);
  ASSERT_FALSE(testPoint_gt <= testPoint);
  ASSERT_FALSE(testPoint_lt >= testPoint);
  ASSERT_TRUE(testPoint_eq >= testPoint);
  ASSERT_TRUE(testPoint_eq <= testPoint);
  ASSERT_FALSE(testPoint_nt >= testPoint);
  ASSERT_FALSE(testPoint_nt <= testPoint);
  ASSERT_FALSE(testPoint_nt_2 >= testPoint);
  ASSERT_FALSE(testPoint_nt_2 <= testPoint);
}

TEST_F(PointShiftTest, UnaryMinusOp) {
  ASSERT_EQ(-testPoint, refl_point);
}

TEST_F(PointShiftTest, PlusMinusBinOpsPair) {
  testPoint += p2;
  ASSERT_EQ(testPoint.position, testCoord_s[1]);
  (testPoint += p2) += p2;
  ASSERT_EQ(testPoint.position, testCoord_s[3]);
  (testPoint -= p2) -= p2;
  ASSERT_EQ(testPoint.position, testCoord_s[1]);
  testPoint -= p2;
  ASSERT_EQ(testPoint.position, testCoord_s[0]);
}

TEST_F(PointShiftTest, PlusMinusBinOpsPoint) {

  testPoint += shift_point;
  ASSERT_EQ(testPoint.position, testCoord_s[1]);
  // Check chaining
  (testPoint += shift_point) += shift_point;
  ASSERT_EQ(testPoint.position, testCoord_s[3]);
}

TEST_F(PointShiftTest, PlusMinusOpsPair) {
  xpt::mesh::Point new_point = testPoint + p2;
  xpt::mesh::Point chain_point = (testPoint + p2) + p2;
  
  ASSERT_EQ(new_point.position, testCoord_s[1]);
  ASSERT_EQ(chain_point.position, testCoord_s[2]);
}

TEST_F(PointShiftTest, PlusMinusOpsPoint) {
  xpt::mesh::Point new_point = testPoint + shift_point;
  xpt::mesh::Point chain_point = (testPoint + shift_point) + shift_point;
  
  ASSERT_EQ(new_point.position, testCoord_s[1]);
  ASSERT_EQ(chain_point.position, testCoord_s[2]);
}



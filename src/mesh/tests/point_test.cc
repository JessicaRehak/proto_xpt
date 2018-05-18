#include "../point.h"

#include <cmath>

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

TEST_F(PointTest, PairConstructor) {
  xpt::mesh::Coordinate position{1.0, -4.0};
  xpt::mesh::Point testPoint_c{position};
  ASSERT_EQ(testPoint_c.position_, position);
 }

TEST_F(PointTest, FloatConstructor) {
  xpt::mesh::Coordinate position{1.0, -4.0};
  xpt::mesh::Point testPoint_c{1.0, -4.0};
  ASSERT_EQ(testPoint_c.position_, position);
}

TEST_F(PointTest, Length) {
  float ans = std::sqrt(101);
  ASSERT_EQ(testPoint.Length(), ans);
}

TEST_F(PointTest, Accessors) {
  xpt::mesh::Coordinate ans{3.0, -10.0};
  xpt::mesh::Coordinate ans2{3.0, 12.7};
  
  testPoint.x_ = 3.0;
  ASSERT_EQ(testPoint.position_, ans);
  testPoint.y_ = 12.7;
  ASSERT_EQ(testPoint.position_, ans2);
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

TEST_F(PointTest, PlusEqOpPair) {
  xpt::mesh::Coordinate p2{10.0, 20.0};
  xpt::mesh::Coordinate ans{x + p2.first, y + p2.second};
  xpt::mesh::Coordinate ans_2{x + 3*p2.first, y + 3*p2.second};
  
  testPoint += p2;
  ASSERT_EQ(testPoint.position_, ans);
  (testPoint += p2) += p2;
  ASSERT_EQ(testPoint.position_, ans_2);
}

TEST_F(PointTest, PlusEqOpPoint) {
  xpt::mesh::Coordinate p2{10.0, 20.0};
  xpt::mesh::Point point2{p2};
  xpt::mesh::Coordinate ans{x + p2.first, y + p2.second};
  xpt::mesh::Coordinate ans_2{x + 3*p2.first, y + 3*p2.second};
  testPoint += point2;
  ASSERT_EQ(testPoint.position_, ans);
  // Check chaining
  (testPoint += point2) += point2;
  ASSERT_EQ(testPoint.position_, ans_2);
}

TEST_F(PointTest, PlusOpPair) {
  xpt::mesh::Coordinate p2{10.0, 20.0};
  xpt::mesh::Coordinate ans{x + p2.first, y + p2.second};
  xpt::mesh::Coordinate ans_2{x + 2*p2.first, y + 2*p2.second};

  xpt::mesh::Point new_point = testPoint + p2;
  xpt::mesh::Point chain_point = (testPoint + p2) + p2;
  
  ASSERT_EQ(new_point.position_, ans);
  ASSERT_EQ(chain_point.position_, ans_2);
}

TEST_F(PointTest, PlusOpPoint) {
  xpt::mesh::Coordinate p2{10.0, 20.0};
  xpt::mesh::Point point2{p2};
  xpt::mesh::Coordinate ans{x +  p2.first, y + p2.second};
  xpt::mesh::Coordinate ans_2{x + 2*p2.first, y + 2*p2.second};

  xpt::mesh::Point new_point = testPoint + point2;
  xpt::mesh::Point chain_point = (testPoint + point2) + point2;
  
  ASSERT_EQ(new_point.position_, ans);
  ASSERT_EQ(chain_point.position_, ans_2);
}

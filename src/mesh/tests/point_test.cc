#include "../point.h"

#include <cmath>

#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <utility>

class PointTest : public ::testing::Test {
 protected:
  void SetUp() override {};
  xpt::mesh::Point testPoint{1.0, -10.0};
  xpt::mesh::Point testPoint_gt{3.4, 0.0};
  xpt::mesh::Point testPoint_lt{0.3, -20.0};
  xpt::mesh::Point testPoint_nt{3.0, -40.5}; //not gt or lt
  xpt::mesh::Point testPoint_nt_2{-45.0, 3.5}; //not gt or lt
  xpt::mesh::Point testPoint_eq{1.0, -10.0};
  xpt::mesh::Point testPoint_ne{3.4, 0.0};
};

TEST_F(PointTest, PairConstructor) {
  std::pair<float, float> position{1.0, -4.0};
  xpt::mesh::Point testPoint_c{position};
  ASSERT_EQ(testPoint_c.position, position);
 }

TEST_F(PointTest, FloatConstructor) {
  std::pair<float, float> position{1.0, -4.0};
  xpt::mesh::Point testPoint_c{1.0, -4.0};
  ASSERT_EQ(testPoint_c.position, position);
}

TEST_F(PointTest, Length) {
  float ans = std::sqrt(101);
  ASSERT_EQ(testPoint.Length(), ans);
}

TEST_F(PointTest, toStr_default) {
  ASSERT_EQ(testPoint.to_str(), "(1.00, -10.00)");
}

TEST_F(PointTest, toStr_specific) {
  ASSERT_EQ(testPoint.to_str(4), "(1.0000, -10.0000)");
}

TEST_F(PointTest, EquivOps) {
  ASSERT_TRUE(testPoint == testPoint_eq);
  ASSERT_FALSE(testPoint == testPoint_ne);
  ASSERT_TRUE(testPoint != testPoint_ne);
  ASSERT_FALSE(testPoint != testPoint_eq);
}

TEST_F(PointTest, ComparisonOps) {
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

TEST_F(PointTest, ComparisonEqOps) {
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
  std::pair<float, float> p2{10.0, 20.0};
  std::pair<float, float> ans{testPoint.position.first + p2.first,
        testPoint.position.second + p2.second};
  std::pair<float, float> ans_2{testPoint.position.first + 3*p2.first,
        testPoint.position.second + 3*p2.second};
  testPoint += p2;
  ASSERT_EQ(testPoint.position, ans);
  // Check chaining
  (testPoint += p2) += p2;
  ASSERT_EQ(testPoint.position, ans_2);
}

TEST_F(PointTest, PlusEqOpPoint) {
  std::pair<float, float> p2{10.0, 20.0};
  xpt::mesh::Point point2{p2};
  std::pair<float, float> ans{testPoint.position.first + p2.first,
        testPoint.position.second + p2.second};
  std::pair<float, float> ans_2{testPoint.position.first + 3*p2.first,
        testPoint.position.second + 3*p2.second};
  testPoint += point2;
  ASSERT_EQ(testPoint.position, ans);
  // Check chaining
  (testPoint += point2) += point2;
  ASSERT_EQ(testPoint.position, ans_2);
}

TEST_F(PointTest, PlusOpPair) {
  std::pair<float, float> p2{10.0, 20.0};
  std::pair<float, float> ans{testPoint.position.first + p2.first,
        testPoint.position.second + p2.second};
  std::pair<float, float> ans_2{testPoint.position.first + 2*p2.first,
        testPoint.position.second + 2*p2.second};

  xpt::mesh::Point new_point = testPoint + p2;
  xpt::mesh::Point chain_point = (testPoint + p2) + p2;
  
  ASSERT_EQ(new_point.position, ans);
  ASSERT_EQ(chain_point.position, ans_2);
}

TEST_F(PointTest, PlusOpPoint) {
  std::pair<float, float> p2{10.0, 20.0};
  xpt::mesh::Point point2{p2};
  std::pair<float, float> ans{testPoint.position.first + p2.first,
        testPoint.position.second + p2.second};
  std::pair<float, float> ans_2{testPoint.position.first + 2*p2.first,
        testPoint.position.second + 2*p2.second};

  xpt::mesh::Point new_point = testPoint + point2;
  xpt::mesh::Point chain_point = (testPoint + point2) + point2;
  
  ASSERT_EQ(new_point.position, ans);
  ASSERT_EQ(chain_point.position, ans_2);
}

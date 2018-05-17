#include "../point.h"

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
}

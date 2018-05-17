#include "../point.h"

#include <gtest/gtest.h>
#include <utility>

class PointTest : public ::testing::Test {
 protected:
  void SetUp() override {};
  xpt::mesh::Point testPoint{1.0, -10.0};
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

TEST_F(PointTest, toStr) {
  ASSERT_EQ(testPoint.to_str(), "(1.0, -10.0)");
}

#include <iostream>

#ifdef TEST
#include <gtest/gtest.h>
#endif

int main(int argc, char* argv[]) {
#ifdef TEST
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
#else
  std::cout << "XPT with Protocol Buffers!" <<std::endl;
  return 0;
#endif
}

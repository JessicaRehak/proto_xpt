#include <iostream>

#include <array>
#include <iostream>

#ifdef TEST
#include <gtest/gtest.h>
#endif

int main(int argc, char* argv[]) {
#ifdef TEST
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
#else
  if (argc != 2) {
    std::cerr << "Usage: " << argv[0] << " PROTO_FILE.mesh2dcartesian"
              << std::endl;
  } else {
    std::cout << "Processing: " << argv[1] << std::endl;
    return 0;
  }
#endif
}

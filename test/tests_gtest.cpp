#include "gtest/gtest.h"

extern "C" {
#include "compilation.h"
#include "composition.h"
#include "dataloader.h"
#include "playlist.h"
}

int main(int argc, char** argv) {
  // The following line must be executed to initialize Google Mock
  // (and Google Test) before running the tests.
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

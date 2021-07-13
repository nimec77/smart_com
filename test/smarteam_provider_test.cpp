//
// Created by nim on 05.07.2021.
//

#include <gtest/gtest.h>
#include <iostream>
#include <smarteam/data/providers/smarteam_provider.h>

using namespace smarteam;

class SmarteamProviderTest : public ::testing::Test {
 protected:
  static void SetUpTestSuite() {
    //    std::cout << "SetUpTestSuite" << std::endl;
    CoInitialize(nullptr);
  }

  static void TearDownTestSuite() {
    //    std::cout << "TearDownTestSuite" << std::endl;
    CoUninitialize();
  }

  void SetUp() override {
    //    std::cout << "SetUp" << std::endl;
  }

  void TearDown() override {
    //    std::cout << "TearDown" << std::endl;
  }
};

TEST_F(SmarteamProviderTest, SmarteamGetInstanceTest) {
  auto smarteam_either = SmarteamProvider::GetInstance();

  ASSERT_TRUE(smarteam_either);

  ASSERT_EQ(typeid(smarteam_either), typeid(SmarteamProvider::SmarteamEither));

  smarteam_either.WhenRight([](auto r) {
    ASSERT_EQ(typeid(r), typeid(SmarteamProvider *));
  });
}


TEST_F(SmarteamProviderTest, SmarteamProvderGetEngineTest) {
  auto smarteam_either = SmarteamProvider::GetInstance();

  ASSERT_TRUE(smarteam_either);

  ASSERT_EQ(typeid(smarteam_either), typeid(SmarteamProvider::SmarteamEither));

  auto engine_either = smarteam_either.RightFlatMap([](const auto smarteam_provider_ptr) {
    EXPECT_EQ(typeid(smarteam_provider_ptr), typeid(SmarteamProvider *));
    return smarteam_provider_ptr->GetEngine();
  });

  ASSERT_TRUE(engine_either);

  ASSERT_EQ(typeid(engine_either), typeid(SmarteamProvider::EngineEither));

  engine_either.WhenRight([](const auto engine_ptr) {
    ASSERT_EQ(typeid(engine_ptr), typeid(IDispatch *));
  });
}

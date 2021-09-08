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
  }

  void SetUp() override {
    //    std::cout << "SetUp" << std::endl;
  }

  void TearDown() override {
    //    std::cout << "TearDown" << std::endl;
  }
};

TEST_F(SmarteamProviderTest, SmarteamGetInstanceTest) {
  const auto smarteam_either_ = SmarteamProvider::GetInstance();

  ASSERT_TRUE(smarteam_either_);

  ASSERT_EQ(typeid(smarteam_either_), typeid(SmarteamProvider::SmarteamEither));

  smarteam_either_.WhenRight([](auto smarteam_provider_ptr) {
    ASSERT_EQ(typeid(smarteam_provider_ptr), typeid(std::shared_ptr<SmarteamProvider>));

    ASSERT_TRUE(smarteam_provider_ptr);
  });
}

TEST_F(SmarteamProviderTest, SmarteamProvderGetEngineTest) {
  const auto smarteam_either_ = SmarteamProvider::GetInstance();

  ASSERT_TRUE(smarteam_either_);

  ASSERT_EQ(typeid(smarteam_either_), typeid(SmarteamProvider::SmarteamEither));

  const auto engine_either_ = smarteam_either_.RightFlatMap([](const auto smarteam_provider_ptr) {
    EXPECT_EQ(typeid(smarteam_provider_ptr), typeid(std::shared_ptr<SmarteamProvider>));
    EXPECT_TRUE(smarteam_provider_ptr);
    return smarteam_provider_ptr->GetEngine();
  });

  ASSERT_TRUE(engine_either_);

  ASSERT_EQ(typeid(engine_either_), typeid(SmarteamProvider::IDispatchEither));

  engine_either_.WhenRight([](const auto engine_ptr) {
    ASSERT_EQ(typeid(engine_ptr), typeid(IDispatch *));
    ASSERT_NE(engine_ptr, nullptr);
  });
}

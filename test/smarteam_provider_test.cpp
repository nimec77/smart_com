//
// Created by nim on 05.07.2021.
//

#include "test_config.h"
#include <gtest/gtest.h>
#include <iostream>
#include <smarteam/constatns.h>
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
    SmarteamProvider::GetInstance().WhenRight([](const auto smarteam_provider_ptr) {
      smarteam_provider_ptr->~SmarteamProvider();
    });
  }
};

TEST_F(SmarteamProviderTest, SmarteamCreateTest) {
  auto smarteam_either = SmarteamProvider::SmarteamCreate(kSmarTeamProdId);

  ASSERT_TRUE(smarteam_either);

  ASSERT_EQ(typeid(smarteam_either), typeid(SmarteamProvider::SmarteamEither));

  smarteam_either.WhenRight([](auto r) {
    ASSERT_EQ(typeid(r), typeid(SmarteamProvider *));
  });
}

TEST_F(SmarteamProviderTest, SmarteamCreateFakeTest) {
  auto smarteam_either = SmarteamProvider::SmarteamCreate(test_config::kFakeProdId);

  ASSERT_FALSE(smarteam_either);

  ASSERT_EQ(typeid(smarteam_either), typeid(SmarteamProvider::SmarteamEither));

  smarteam_either.WhenLeft([](const auto l) {
    EXPECT_EQ(typeid(l), typeid(std::exception));
    const auto message = l.what();
    EXPECT_STREQ(message, "data_helper::GetClassId CLSIDFromProgID error: 800401f3");
  });
}

TEST_F(SmarteamProviderTest, SmarteamFromActiveObjectFakeTest) {
  auto smarteam_either = SmarteamProvider::SmarteamFromActiveObject(test_config::kFakeProdId);

  ASSERT_FALSE(smarteam_either);

  ASSERT_EQ(typeid(smarteam_either), typeid(SmarteamProvider::SmarteamEither));

  smarteam_either.WhenLeft([](const auto l) {
    EXPECT_EQ(typeid(l), typeid(std::exception));
    const auto message = l.what();
    EXPECT_STREQ(message, "data_helper::GetClassId CLSIDFromProgID error: 800401f3");
  });
}

TEST_F(SmarteamProviderTest, DISABLED_SmartemFromActiveObjectTest) {
  auto smarteam_either = SmarteamProvider::SmarteamFromActiveObject(kSmarTeamProdId);

  ASSERT_TRUE(smarteam_either);

  ASSERT_EQ(typeid(smarteam_either), typeid(SmarteamProvider::SmarteamEither));

  smarteam_either.WhenRight([](auto r) {
    ASSERT_EQ(typeid(r), typeid(SmarteamProvider));
  });
}
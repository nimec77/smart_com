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
  void SetUp() override {
    CoInitialize(nullptr);
  }
  void TearDown() override {
    CoUninitialize();
  }
};

TEST_F(SmarteamProviderTest, SmarteamCreateTest) {
  auto smarteam_either = SmarteamProvider::SmarteamCreate(kSmarTeamProdId);

  ASSERT_EQ(typeid(smarteam_either), typeid(SmarteamProvider::SmarteamEither));

  smarteam_either.When(
      [](const auto l) {
        FAIL() << "Error create SmarTeam object";
      },
      [](auto r) {
        ASSERT_EQ(typeid(r), typeid(SmarteamProvider));
      });
}

TEST_F(SmarteamProviderTest, SmarteamCreateFakeTest) {
  auto smarteam_either = SmarteamProvider::SmarteamCreate(test_config::kFakeProdId);

  ASSERT_EQ(typeid(smarteam_either), typeid(SmarteamProvider::SmarteamEither));

  smarteam_either.When(
      [](const auto l) {
        EXPECT_EQ(typeid(l), typeid(std::exception));
        const auto message = l.what();
        EXPECT_STREQ(message, "::GetClassId CLSIDFromProgID error: 800401f3");
      },
      [](auto r) {
        FAIL() << "Error: A fake object can't be created!";
      });
}

TEST_F(SmarteamProviderTest, SmarteamFromActiveObjectFakeTest) {
  auto smarteam_either = SmarteamProvider::SmarteamFromActiveObject(test_config::kFakeProdId);

  ASSERT_EQ(typeid(smarteam_either), typeid(SmarteamProvider::SmarteamEither));

  smarteam_either.When(
      [](const auto l) {
        EXPECT_EQ(typeid(l), typeid(std::exception));
        const auto message = l.what();
        EXPECT_STREQ(message, "::GetClassId CLSIDFromProgID error: 800401f3");
      },
      [](auto r) {
        FAIL() << "Error: A fake object can't be created!";
      });
}

TEST_F(SmarteamProviderTest, DISABLED_SmartemFromActiveObjectTest) {
  auto smarteam_either = SmarteamProvider::SmarteamFromActiveObject(kSmarTeamProdId);

  ASSERT_EQ(typeid(smarteam_either), typeid(SmarteamProvider::SmarteamEither));

  smarteam_either.When(
      [](const auto l) {
        const auto message = l.what();
        FAIL() << "Error get SmarTeam object (Maybe SmarTeam not running): " << message;
      },
      [](auto r) {
        ASSERT_EQ(typeid(r), typeid(SmarteamProvider));
      });
}
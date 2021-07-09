//
// Created by nim on 07.07.2021.
//

#include <gtest/gtest.h>
#include <smarteam/data/data_helper.h>
#include <smarteam/constatns.h>

TEST(DataHelperTest, MakeErrorMessageTest) {
  const auto message = data_helper::MakeErrorMessage("Error message", -2147221021);

  ASSERT_STREQ(message.c_str(), "Error message 800401e3");
}

TEST(DataHelperTest, GetClassIdFailTest) {
  auto result = data_helper::GetClassId(L"EmptyClassId");

  ASSERT_EQ(typeid(result), typeid(data_helper::GetClassIdEither));

  ASSERT_FALSE(result);

  result.WhenLeft([](auto l) {
    EXPECT_EQ(typeid(l), typeid(std::exception));
    const auto message = l.what();
    EXPECT_STREQ(message, "data_helper::GetClassId CLSIDFromProgID error: 800401f3");
  });
}

TEST(DataHelperTest, GetClassIdSuccessTest) {
  auto result = data_helper::GetClassId(smarteam::kSmarTeamProdId);

  ASSERT_EQ(typeid(result), typeid(data_helper::GetClassIdEither));

  ASSERT_TRUE(result);

  const CLSID clsid = {};
  auto smart_app = result | clsid;

  ASSERT_EQ(typeid(smart_app), typeid(CLSID));

  ASSERT_NE(smart_app, clsid);
}
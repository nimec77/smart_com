//
// Created by nim on 09.07.2021.
//

#include "../test_config.h"
#include <gtest/gtest.h>
#include <smarteam/helper.h>

TEST(HelperTest, Utf16ToUtf8Test) {
  auto result_en = helper::Utf16ToUtf8(L"Test string");

  ASSERT_TRUE(result_en);

  ASSERT_STREQ(result_en | "", "Test string");

  auto result_ru = helper::Utf16ToUtf8(test_config::kTestUtf16RuStr);

  ASSERT_TRUE(result_ru);

  ASSERT_STREQ(result_ru | "", "Тестовая строка");

  auto result = helper::Utf16ToUtf8(test_config::kTestUtf16Str);

  ASSERT_TRUE(result);

  ASSERT_STREQ(result | "", "Test string, Тестовая строка");
}

TEST(HelperTest, Utf16ToUtf8FailTest) {
  auto result = helper::Utf16ToUtf8(nullptr);

  ASSERT_FALSE(result);

  result.WhenLeft([](auto l) {
    EXPECT_EQ(typeid(l), typeid(std::exception));
    const auto message = l.what();
    EXPECT_STREQ(message, "helper::Utf16ToUtf8 WideCharToMultiByte error get string length");
  });
}
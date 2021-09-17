//
// Created by nim on 16.09.2021.
//

#include "../../../test_config.h"
#include <common/helpers/string_helper.h>
#include <gtest/gtest.h>
#include <gmock/gmock.h>

TEST(StringHelperTest, WStringToBytesTest) {
  const auto result_ = string_helper::WStringToBytes(test_config::kEncodedTestWStr);

  ASSERT_TRUE(result_);
  ASSERT_EQ(typeid(result_), typeid(BytesEither));

  result_.WhenRight([](const auto data) {
    ASSERT_EQ(typeid(data), typeid(Bytes));
    const auto value_ = std::string{data.begin(), data.end()};
    const auto encoded_ = helper::Utf16ToUtf8(test_config::kEncodedTestWStr) | "";
    ASSERT_STREQ(value_.c_str(), encoded_.c_str());
  });
}

TEST(StringHelperTest, BytesToHexString) {
  const auto key_data_ = Bytes{test_config::kKey, test_config::kKey + sizeof(test_config::kKey)};
  const auto result_ = string_helper::BytesToHexString(key_data_);

  ASSERT_EQ(typeid(result_), typeid(StringEither));
  ASSERT_TRUE(result_);

  result_.WhenRight([key_data_](const auto hex_string) {
    ASSERT_EQ(typeid(hex_string), typeid(std::string));
    ASSERT_STREQ(hex_string.c_str(), test_config::kHexKey);
  });
}

TEST(StringHelperTest, HexStringToBytes) {
  const auto result_ = string_helper::HexStringToBytes(test_config::kHexKey);

  ASSERT_EQ(typeid(result_), typeid(BytesEither));
  ASSERT_TRUE(result_);

  result_.WhenRight([](const auto key_data) {
    ASSERT_EQ(typeid(key_data), typeid(Bytes));
    const auto key_ = string_helper::BytesToHexString(key_data) | "";
    ASSERT_STREQ(key_.c_str(), test_config::kHexKey);
  });
}
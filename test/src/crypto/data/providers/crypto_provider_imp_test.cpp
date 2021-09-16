//
// Created by nim on 14.09.2021.
//

#include "../../../test_config.h"
#include <codecvt>
#include <crypto/data/providers/crypto_provider_imp.h>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

CryptoProvider *crypto_provider{nullptr};

class CryptoProviderImpTest : public ::testing::Test {
 protected:
  static void SetUpTestSuite() {
    crypto_provider = new CryptoProviderImp();
  }
  static void TearDownTestSuite() {
    delete crypto_provider;
  }
};

TEST_F(CryptoProviderImpTest, Md5HashSuccessTest) {
  auto const value_ = std::string{"123456"};

  auto const data_ = std::vector<BYTE>{value_.begin(), value_.end()};

  auto result_ = crypto_provider->Md5Hash(data_);

  ASSERT_TRUE(result_);

  ASSERT_EQ(typeid(result_), typeid(BytesEither));

  result_.WhenRight([](const auto hash_data) {
    ASSERT_EQ(typeid(hash_data), typeid(Bytes));
    ASSERT_THAT(hash_data, testing::ElementsAreArray(test_config::kKey));
  });
}

TEST_F(CryptoProviderImpTest, EncodeAesSuccessTest) {

  const auto key_data_ = Bytes{test_config::kKey, test_config::kKey + sizeof(test_config::kKey)};

  auto value_ = helper::Utf16ToUtf8(test_config::kEncodedTestWStr) | std::string{};

  auto data_ = Bytes{value_.begin(), value_.end()};
  auto result_ = crypto_provider->EncodeAes(key_data_, data_);
  result_.WhenRight([](const auto encoded) {
    ASSERT_EQ(typeid(encoded), typeid(Bytes));
            ASSERT_THAT(encoded,
                        testing::ElementsAreArray(test_config::kEncodedData));
//    for (int item : encoded) {
//      std::cout << "0x" << std::hex << std::setfill('0') << std::setw(2) << item << ", ";
//    }
    std::cout << std::endl;
  });

  ASSERT_TRUE(result_);

  ASSERT_EQ(typeid(result_), typeid(BytesEither));
}

TEST_F(CryptoProviderImpTest, DecodeAesSuccessTest) {
  const auto key_data_ = Bytes{test_config::kKey, test_config::kKey + sizeof(test_config::kKey)};

  const auto data_ = Bytes{test_config::kEncodedData, test_config::kEncodedData + sizeof(test_config::kEncodedData)};

  auto result_ = crypto_provider->DecodeAes(key_data_, data_);

  ASSERT_TRUE(result_);

  ASSERT_EQ(typeid(result_), typeid(BytesEither));

  result_.WhenRight([](const auto decoded) {
    ASSERT_EQ(typeid(decoded), typeid(Bytes));

    std::string value_{decoded.begin(), decoded.end()};
    std::cout << value_ << std::endl;

    const auto encoded_value_ = helper::Utf16ToUtf8(test_config::kEncodedTestWStr) | "";
    ASSERT_STREQ(value_.c_str(), encoded_value_.c_str());
  });
}
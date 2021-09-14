//
// Created by nim on 14.09.2021.
//

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
    ASSERT_THAT(hash_data,
                testing::ElementsAre(0xe1, 0x0a, 0xdc, 0x39, 0x49, 0xba, 0x59, 0xab, 0xbe, 0x56, 0xe0, 0x57, 0xf2,
                                     0x0f, 0x88, 0x3e));
  });
}
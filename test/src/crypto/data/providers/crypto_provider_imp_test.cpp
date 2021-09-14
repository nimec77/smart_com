//
// Created by nim on 14.09.2021.
//

#include <crypto/data/providers/crypto_provider_imp.h>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

CryptoProvider *crypto_provider{nullptr};

const BYTE key[] = {
    0xe1, 0x0a, 0xdc, 0x39, 0x49, 0xba, 0x59, 0xab,
    0xbe, 0x56, 0xe0, 0x57, 0xf2, 0x0f, 0x88, 0x3e};

const BYTE encoded_data[] = {
    0xb5, 0x81, 0xce, 0x78, 0x29, 0x97, 0xa9, 0x43,
    0x60, 0x6b, 0x46, 0x29, 0x47, 0x41, 0x49, 0x89};

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
    ASSERT_THAT(hash_data, testing::ElementsAreArray(key));
  });
}

TEST_F(CryptoProviderImpTest, EncodeAesSuccessTest) {

  const auto key_data_ = Bytes{key, key + sizeof(key)};

  auto const value_ = std::string{"Test data!"};

  auto const data_ = std::vector<BYTE>{value_.begin(), value_.end()};

  auto result_ = crypto_provider->EncodeAes(key_data_, data_);

  ASSERT_TRUE(result_);

  ASSERT_EQ(typeid(result_), typeid(BytesEither));

  result_.WhenRight([](const auto encoded) {
    ASSERT_EQ(typeid(encoded), typeid(Bytes));
    ASSERT_THAT(encoded,
                testing::ElementsAreArray(encoded_data));
    //    for (int item : encoded) {
    //      std::cout << "0x" << std::hex << std::setfill('0') << std::setw(2) << item << ", ";
    //    }
    //    std::cout << std::endl;
  });
}
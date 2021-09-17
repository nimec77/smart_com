//
// Created by nim on 08.09.2021.
//

#include "../../../../test_config.h"
#include <common/base_types.h>
#include <common/helpers/helper.h>
#include <crypto/data/ports/providers/crypto_provider.h>
#include <crypto/data/ports/providers/sid_provider.h>
#include <crypto/data/repositories/crypto_repository_imp.h>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

using ::testing::AtLeast;
using ::testing::Return;

class MockSidProvider : public SidProvider {
 public:
  MOCK_METHOD(WStringEither, GetName, (), (noexcept));
  MOCK_METHOD(WStringEither, GetAccountSidFromName, (std::wstring), (noexcept));
};

class MockCryptoProvider : public CryptoProvider {
 public:
  //  virtual BytesEither Md5Hash(const Bytes &data) noexcept = 0;
  MOCK_METHOD(BytesEither, Md5Hash, (const Bytes &data), (noexcept));
  //  virtual BytesEither EncodeAes(const Bytes &key_data, const Bytes &data) noexcept = 0;
  MOCK_METHOD(BytesEither, EncodeAes, (const Bytes &key_data, const Bytes &data), (noexcept));
  //  virtual BytesEither DecodeAes(const Bytes &key_data, const Bytes &data) noexcept = 0;
  MOCK_METHOD(BytesEither, DecodeAes, (const Bytes &key_data, const Bytes &data), (noexcept));
};

std::shared_ptr<MockSidProvider> mock_sid_provider;
std::shared_ptr<MockCryptoProvider> mock_crypto_provider;
CryptoRepository *crypto_repository_ptr{nullptr};

class CryptoRepositoryImpTest : public ::testing::Test {
 protected:
  static void SetUpTestSuite() {
    mock_sid_provider = std::make_shared<MockSidProvider>();
    mock_crypto_provider = std::make_shared<MockCryptoProvider>();
    crypto_repository_ptr = new CryptoRepositoryImp(SidProvider::SidProviderPtr{mock_sid_provider},
                                                    CryptoProvider::CryptoProviderPtr{mock_crypto_provider});
  }

  static void TearDownTestSuite() {
    delete crypto_repository_ptr;
    mock_sid_provider.reset();
    mock_crypto_provider.reset();
  }
};

TEST_F(CryptoRepositoryImpTest, GetSidTestSuccess) {
  const auto username_ = std::wstring{L"Username"};
  const auto w_user_sid_ = std::wstring{L"User Sid"};
  const auto user_sid_ = helper::Utf16ToUtf8(w_user_sid_.c_str()) | "";

  EXPECT_CALL(*mock_sid_provider, GetName())
      .Times(1)
      .WillOnce(Return(WStringEither::RightOf(username_)));

  EXPECT_CALL(*mock_sid_provider, GetAccountSidFromName(::testing::_))
      .Times(1)
      .WillOnce(Return(WStringEither::RightOf(w_user_sid_)));

  auto result_ = crypto_repository_ptr->GetSid();

  ASSERT_EQ(typeid(result_), typeid(WStringEither));

  ASSERT_TRUE(result_);

  result_.WhenRight([user_sid_](const auto w_sid) {
    ASSERT_EQ(typeid(w_sid), typeid(std::wstring));
    const auto sid_ = helper::Utf16ToUtf8(w_sid.c_str()) | "";
    ASSERT_STREQ(sid_.c_str(), user_sid_.c_str());
  });
}

TEST_F(CryptoRepositoryImpTest, GetSidTestFailedGetName) {
  const auto error_ = std::runtime_error("GetName Error");
  const auto w_user_sid_ = std::wstring{L"User Sid"};

  EXPECT_CALL(*mock_sid_provider, GetName())
      .Times(1)
      .WillOnce(Return(WStringEither::LeftOf(error_)));

  EXPECT_CALL(*mock_sid_provider, GetAccountSidFromName(::testing::_))
      .Times(AtLeast(0))
      .WillOnce(Return(WStringEither::RightOf(w_user_sid_)));

  auto result_ = crypto_repository_ptr->GetSid();

  ASSERT_EQ(typeid(result_), typeid(WStringEither));

  ASSERT_FALSE(result_);

  result_.WhenLeft([error_](const auto left) {
    ASSERT_EQ(typeid(left), typeid(std::exception));
    ASSERT_STREQ(left.what(), error_.what());
  });
}

TEST_F(CryptoRepositoryImpTest, GetSidTestFailedGetAccountSidFromName) {
  const auto username_ = std::wstring{L"Username"};
  const auto error_ = std::runtime_error("GetAccountSidFromName Error");

  EXPECT_CALL(*mock_sid_provider, GetName())
      .Times(1)
      .WillOnce(Return(WStringEither::RightOf(username_)));

  EXPECT_CALL(*mock_sid_provider, GetAccountSidFromName(::testing::_))
      .Times(1)
      .WillOnce(Return(WStringEither::LeftOf(error_)));

  auto result_ = crypto_repository_ptr->GetSid();

  ASSERT_EQ(typeid(result_), typeid(WStringEither));

  ASSERT_FALSE(result_);

  result_.WhenLeft([error_](const auto left) {
    ASSERT_EQ(typeid(left), typeid(std::exception));
    ASSERT_STREQ(left.what(), error_.what());
  });
}

TEST_F(CryptoRepositoryImpTest, EncodeSuccess) {

  const auto key_hash_ = Bytes{test_config::kKey, test_config::kKey + sizeof(test_config::kKey)};
  const auto encoded_ = Bytes{test_config::kEncodedData, test_config::kEncodedData + sizeof(test_config::kEncodedData)};

  EXPECT_CALL(*mock_crypto_provider, Md5Hash(::testing::_))
      .Times(1)
      .WillOnce(Return(BytesEither::RightOf(key_hash_)));

  EXPECT_CALL(*mock_crypto_provider, EncodeAes(::testing::_, ::testing::_))
      .Times(1)
      .WillOnce(Return(BytesEither::RightOf(encoded_)));

  const auto result_ = crypto_repository_ptr->Encode(test_config::kSecretKey, test_config::kEncodedTestWStr);

  ASSERT_EQ(typeid(result_), typeid(StringEither));

  ASSERT_TRUE(result_);

  result_.WhenRight([encoded_](const auto value) {
    ASSERT_EQ(typeid(value), typeid(std::string));
    const auto text_ = string_helper::BytesToHexString(encoded_) | "";
    ASSERT_STREQ(value.c_str(), text_.c_str());
  });
}

TEST_F(CryptoRepositoryImpTest, EncodeFailureMd5HashError) {
  const auto error_ = std::runtime_error("Md5Hash error");
  const auto encoded_ = Bytes{test_config::kEncodedData, test_config::kEncodedData + sizeof(test_config::kEncodedData)};

  EXPECT_CALL(*mock_crypto_provider, Md5Hash(::testing::_))
  .Times(1)
  .WillOnce(Return(BytesEither::LeftOf(error_)));

  EXPECT_CALL(*mock_crypto_provider, EncodeAes(::testing::_, ::testing::_))
  .Times(AtLeast(0))
  .WillOnce(Return(BytesEither::RightOf(encoded_)));

  const auto result_ = crypto_repository_ptr->Encode(test_config::kSecretKey, test_config::kEncodedTestWStr);

  ASSERT_EQ(typeid(result_), typeid(StringEither));

  ASSERT_FALSE(result_);

  result_.WhenLeft([error_](const auto left) {
    ASSERT_EQ(typeid(left), typeid(std::exception));
    ASSERT_STREQ(left.what(), error_.what());
  });
}

TEST_F(CryptoRepositoryImpTest, EncodeFailureEncodeAesError) {
  const auto key_hash_ = Bytes{test_config::kKey, test_config::kKey + sizeof(test_config::kKey)};
  const auto error_ = std::runtime_error("EncodeAes error");

  EXPECT_CALL(*mock_crypto_provider, Md5Hash(::testing::_))
  .Times(1)
  .WillOnce(Return(BytesEither::RightOf(key_hash_)));

  EXPECT_CALL(*mock_crypto_provider, EncodeAes(::testing::_, ::testing::_))
  .Times(1)
  .WillOnce(Return(BytesEither::LeftOf(error_)));

  const auto result_ = crypto_repository_ptr->Encode(test_config::kSecretKey, test_config::kEncodedTestWStr);

  ASSERT_EQ(typeid(result_), typeid(StringEither));

  ASSERT_FALSE(result_);

  result_.WhenLeft([error_](const auto left) {
    ASSERT_EQ(typeid(left), typeid(std::exception));
    ASSERT_STREQ(left.what(), error_.what());
  });
}
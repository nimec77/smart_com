//
// Created by nim on 08.09.2021.
//

#include "../../../../test_config.h"
#include <common/base_types.h>
#include <common/helpers/helper.h>
#include <crypto/domain/use_cases/crypto_use_cases.h>
#include <crypto/domain/use_cases/ports/repositories/crypto_repository.h>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

using ::testing::AtLeast;
using ::testing::Return;

class MockCryptoRepository : public CryptoRepository {
 public:
  MOCK_METHOD(WStringEither, GetSid, (), (noexcept));
  MOCK_METHOD(StringEither, Encode, (const wchar_t *), (noexcept));
  MOCK_METHOD(StringEither, Decode, (const wchar_t *), (noexcept));
};

TEST(CryptoUseCasesTest, EncodeSuccess) {
  const auto encoded_ = helper::Utf16ToUtf8(test_config::kEncodedTestWStr) | "";
  const auto mock_crypto_repository_ = std::make_shared<MockCryptoRepository>();
  auto crypto_use_cases_ = CryptoUseCases(CryptoRepository::CryptoRepositoryPtr(mock_crypto_repository_));

  EXPECT_CALL(*mock_crypto_repository_, Encode(::testing::_))
      .Times(1)
      .WillOnce(Return(StringEither::RightOf(encoded_)));

  const auto result_ = crypto_use_cases_.Encode(test_config::kEncodedTestWStr);

  ASSERT_EQ(typeid(result_), typeid(StringEither));
  ASSERT_TRUE(result_);

  result_.WhenRight([encoded_](const auto value) {
    ASSERT_EQ(typeid(value), typeid(std::string));
    ASSERT_STREQ(value.c_str(), encoded_.c_str());
  });
}

TEST(CryptoUseCasesTest, EncodeTestFailure) {
  const auto error = std::runtime_error("Encode Error");

  const auto mock_crypto_repository_ = std::make_shared<MockCryptoRepository>();
  auto crypto_use_cases_ = CryptoUseCases(CryptoRepository::CryptoRepositoryPtr(mock_crypto_repository_));

  EXPECT_CALL(*mock_crypto_repository_, Encode(::testing::_))
      .Times(1)
      .WillOnce(Return(StringEither::LeftOf(error)));

  const auto result_ = crypto_use_cases_.Encode(test_config::kDecodedTestWStr);

  ASSERT_EQ(typeid(result_), typeid(StringEither));
  ASSERT_TRUE(!result_);

  result_.WhenLeft([error](const auto left) {
    const auto message = left.what();
    ASSERT_STREQ(error.what(), message);
  });
}

TEST(CryptoUseCasesTest, DecodeTestSuccess) {
  const auto encoded_ = helper::Utf16ToUtf8(test_config::kEncodedTestWStr) | "";
  const auto mock_crypto_repository_ = std::make_shared<MockCryptoRepository>();
  auto crypto_use_cases_ = CryptoUseCases(CryptoRepository::CryptoRepositoryPtr(mock_crypto_repository_));

  EXPECT_CALL(*mock_crypto_repository_, Decode(::testing::_))
      .Times(1)
      .WillOnce(Return(StringEither::RightOf(encoded_)));

  const auto result_ = crypto_use_cases_.Decode(test_config::kEncodedTestWStr);

  ASSERT_EQ(typeid(result_), typeid(StringEither));
  ASSERT_TRUE(result_);

  result_.WhenRight([encoded_](const auto value) {
    ASSERT_EQ(typeid(value), typeid(std::string));
    ASSERT_STREQ(value.c_str(), encoded_.c_str());
  });
}

TEST(CryptoUseCasesTest, DecodeTestFailure) {
  const auto error = std::runtime_error("Decode Error");

  const auto mock_crypto_repository_ = std::make_shared<MockCryptoRepository>();
  auto crypto_use_cases_ = CryptoUseCases(CryptoRepository::CryptoRepositoryPtr(mock_crypto_repository_));

  EXPECT_CALL(*mock_crypto_repository_, Decode(::testing::_))
      .Times(1)
      .WillOnce(Return(StringEither::LeftOf(error)));

  const auto result_ = crypto_use_cases_.Decode(test_config::kEncodedTestWStr);

  ASSERT_EQ(typeid(result_), typeid(StringEither));
  ASSERT_TRUE(!result_);

  result_.WhenLeft([error](const auto left) {
    const auto message = left.what();
    ASSERT_STREQ(error.what(), message);
  });
}

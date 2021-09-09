//
// Created by nim on 08.09.2021.
//

#include "../../../../test_config.h"
#include <common/base_types.h>
#include <crypto/domain/use_cases/crypto_use_cases.h>
#include <crypto/domain/use_cases/ports/repositories/crypto_repository.h>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

using ::testing::AtLeast;
using ::testing::Return;

class MockCryptoRepository : public CryptoRepository {
 public:
  MOCK_METHOD(StringEither, GetSid, (), (noexcept));
  MOCK_METHOD(WStringEither, Encode, (const wchar_t *), (noexcept));
  MOCK_METHOD(WStringEither, Decode, (const wchar_t *), (noexcept));
};

TEST(CryptoUseCasesTest, EncodeTestSuccess) {
  const auto mock_crypto_repository_ = std::make_shared<MockCryptoRepository>();
  auto crypto_use_cases_ = CryptoUseCases(CryptoRepository::CryptoRepositoryPtr(mock_crypto_repository_));

  EXPECT_CALL(*mock_crypto_repository_, Encode(::testing::_))
      .Times(1)
      .WillOnce(Return(WStringEither::RightOf(test_config::kEncodedTestStr)));

  const auto result_ = crypto_use_cases_.Encode(test_config::kDecodedTestStr);

  ASSERT_EQ(typeid(result_), typeid(WStringEither));
  ASSERT_TRUE(result_);

  result_.WhenRight([](const auto value) {
    ASSERT_EQ(typeid(value), typeid(std::wstring));
    ASSERT_STREQ(value.c_str(), test_config::kEncodedTestStr);
  });
}

TEST(CryptoUseCasesTest, EncodeTestFailure) {
  const auto error = std::runtime_error("Encode Error");

  const auto mock_crypto_repository_ = std::make_shared<MockCryptoRepository>();
  auto crypto_use_cases_ = CryptoUseCases(CryptoRepository::CryptoRepositoryPtr(mock_crypto_repository_));

  EXPECT_CALL(*mock_crypto_repository_, Encode(::testing::_))
      .Times(1)
      .WillOnce(Return(WStringEither::LeftOf(error)));

  const auto result_ = crypto_use_cases_.Encode(test_config::kDecodedTestStr);

  ASSERT_EQ(typeid(result_), typeid(WStringEither));
  ASSERT_TRUE(!result_);

  result_.WhenLeft([error](const auto left) {
    const auto message = left.what();
    ASSERT_STREQ(error.what(), message);
  });
}

TEST(CryptoUseCasesTest, DecodeTestSuccess) {
  const auto mock_crypto_repository_ = std::make_shared<MockCryptoRepository>();
  auto crypto_use_cases_ = CryptoUseCases(CryptoRepository::CryptoRepositoryPtr(mock_crypto_repository_));

  EXPECT_CALL(*mock_crypto_repository_, Decode(::testing::_))
      .Times(1)
      .WillOnce(Return(WStringEither::RightOf(test_config::kDecodedTestStr)));

  const auto result_ = crypto_use_cases_.Decode(test_config::kEncodedTestStr);

  ASSERT_EQ(typeid(result_), typeid(WStringEither));
  ASSERT_TRUE(result_);

  result_.WhenRight([](const auto value) {
    ASSERT_EQ(typeid(value), typeid(std::wstring));
    ASSERT_STREQ(value.c_str(), test_config::kDecodedTestStr);
  });
}

TEST(CryptoUseCasesTest, DecodeTestFailure) {
  const auto error = std::runtime_error("Decode Error");

  const auto mock_crypto_repository_ = std::make_shared<MockCryptoRepository>();
  auto crypto_use_cases_ = CryptoUseCases(CryptoRepository::CryptoRepositoryPtr(mock_crypto_repository_));

  EXPECT_CALL(*mock_crypto_repository_, Decode(::testing::_))
      .Times(1)
      .WillOnce(Return(WStringEither::LeftOf(error)));

  const auto result_ = crypto_use_cases_.Decode(test_config::kEncodedTestStr);

  ASSERT_EQ(typeid(result_), typeid(WStringEither));
  ASSERT_TRUE(!result_);

  result_.WhenLeft([error](const auto left) {
    const auto message = left.what();
    ASSERT_STREQ(error.what(), message);
  });
}

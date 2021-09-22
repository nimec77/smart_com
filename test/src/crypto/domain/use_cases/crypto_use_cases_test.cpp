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
  MOCK_METHOD(StringEither, Encode, (std::wstring secret_key, std::wstring text), (noexcept));
  MOCK_METHOD(StringEither, Decode, (std::wstring secret_key, std::wstring hex_value), (noexcept));
};

std::shared_ptr<MockCryptoRepository> mock_crypto_repository;
CryptoUseCases *crypto_use_cases_ptr{nullptr};

class CryptoUseCasesTest : public ::testing::Test {
 protected:
  static void SetUpTestSuite() {
    mock_crypto_repository = std::make_shared<MockCryptoRepository>();
    crypto_use_cases_ptr = new CryptoUseCases(mock_crypto_repository);
  }

  static void TearDownTestSuite() {
    delete crypto_use_cases_ptr;
    mock_crypto_repository.reset();
  }
};

TEST_F(CryptoUseCasesTest, GetSidSuccess) {
  EXPECT_CALL(*mock_crypto_repository, GetSid())
  .Times(1)
  .WillOnce(Return(WStringEither::RightOf(test_config::kSid)));

  const auto result_ = crypto_use_cases_ptr->GetSid();

  ASSERT_EQ(typeid(result_), typeid(StringEither));
  ASSERT_TRUE(result_);

  result_.WhenRight([](const auto value) {
    ASSERT_EQ(typeid(value), typeid(std::string));
    const auto sid_ = helper::Utf16ToUtf8(test_config::kSid) | "";
    ASSERT_STREQ(value.c_str(), sid_.c_str());
  });
}

TEST_F(CryptoUseCasesTest, GetSidFailure) {
  const auto error_ = std::runtime_error("GetSid Error");

  EXPECT_CALL(*mock_crypto_repository, GetSid())
  .Times(1)
  .WillOnce(Return(WStringEither::LeftOf(error_)));

  const auto result_ = crypto_use_cases_ptr->GetSid();

  ASSERT_EQ(typeid(result_), typeid(StringEither));
  ASSERT_FALSE(result_);

  result_.WhenLeft([error_](const auto left) {
    ASSERT_EQ(typeid(left), typeid(std::exception));
    ASSERT_STREQ(error_.what(), left.what());
  });
}

TEST_F(CryptoUseCasesTest, EncodeSuccess) {
  const auto encoded_ = helper::Utf16ToUtf8(test_config::kEncodedTestWStr) | "";

  EXPECT_CALL(*mock_crypto_repository, GetSid())
      .Times(1)
      .WillOnce(Return(WStringEither::RightOf(test_config::kSid)));

  EXPECT_CALL(*mock_crypto_repository, Encode(::testing::_, ::testing::_))
      .Times(1)
      .WillOnce(Return(StringEither::RightOf(encoded_)));

  const auto result_ = crypto_use_cases_ptr->Encode(test_config::kEncodedTestWStr);

  ASSERT_EQ(typeid(result_), typeid(StringEither));
  ASSERT_TRUE(result_);

  result_.WhenRight([encoded_](const auto value) {
    ASSERT_EQ(typeid(value), typeid(std::string));
    ASSERT_STREQ(value.c_str(), encoded_.c_str());
  });
}

TEST_F(CryptoUseCasesTest, EncodeFailureGetSidError) {
  const auto error_ = std::runtime_error("GetSid Error");
  const auto encoded_ = helper::Utf16ToUtf8(test_config::kEncodedTestWStr) | "";

  EXPECT_CALL(*mock_crypto_repository, GetSid())
      .Times(1)
      .WillOnce(Return(WStringEither::LeftOf(error_)));

  EXPECT_CALL(*mock_crypto_repository, Encode(::testing::_, ::testing::_))
      .Times(AtLeast(0))
      .WillOnce(Return(StringEither::RightOf(encoded_)));

  const auto result_ = crypto_use_cases_ptr->Encode(test_config::kEncodedTestWStr);

  ASSERT_EQ(typeid(result_), typeid(StringEither));
  ASSERT_FALSE(result_);

  result_.WhenLeft([error_](const auto left) {
    ASSERT_EQ(typeid(left), typeid(std::exception));
    ASSERT_STREQ(error_.what(), left.what());
  });
}

TEST_F(CryptoUseCasesTest, EncodeFailureEncodeError) {
  const auto error_ = std::runtime_error("Encode Error");
  const auto encoded_ = helper::Utf16ToUtf8(test_config::kEncodedTestWStr) | "";

  EXPECT_CALL(*mock_crypto_repository, GetSid())
      .Times(1)
      .WillOnce(Return(WStringEither::RightOf(test_config::kSid)));

  EXPECT_CALL(*mock_crypto_repository, Encode(::testing::_, ::testing::_))
      .Times(1)
      .WillOnce(Return(StringEither::LeftOf(error_)));

  const auto result_ = crypto_use_cases_ptr->Encode(test_config::kEncodedTestWStr);

  ASSERT_EQ(typeid(result_), typeid(StringEither));
  ASSERT_FALSE(result_);

  result_.WhenLeft([error_](const auto left) {
    ASSERT_EQ(typeid(left), typeid(std::exception));
    ASSERT_STREQ(error_.what(), left.what());
  });
}

TEST_F(CryptoUseCasesTest, DecodeSuccess) {
    const auto encoded_ = helper::Utf16ToUtf8(test_config::kEncodedTestWStr) | "";

    EXPECT_CALL(*mock_crypto_repository, GetSid())
    .Times(1)
    .WillOnce(Return(WStringEither::RightOf(test_config::kSid)));

    EXPECT_CALL(*mock_crypto_repository, Decode(::testing::_, ::testing::_))
        .Times(1)
        .WillOnce(Return(StringEither::RightOf(encoded_)));

    const auto result_ = crypto_use_cases_ptr->Decode(test_config::kEncodedTestWStr);

    ASSERT_EQ(typeid(result_), typeid(StringEither));
    ASSERT_TRUE(result_);

    result_.WhenRight([encoded_](const auto value) {
      ASSERT_EQ(typeid(value), typeid(std::string));
      ASSERT_STREQ(value.c_str(), encoded_.c_str());
    });
}

TEST_F(CryptoUseCasesTest, DecodeFailureGetSidError) {
  const auto error_ = std::runtime_error("GetSid Error");
  const auto encoded_ = helper::Utf16ToUtf8(test_config::kEncodedTestWStr) | "";

  EXPECT_CALL(*mock_crypto_repository, GetSid())
  .Times(1)
  .WillOnce(Return(WStringEither::LeftOf(error_)));

  EXPECT_CALL(*mock_crypto_repository, Decode(::testing::_, ::testing::_))
  .Times(AtLeast(0))
  .WillOnce(Return(StringEither::RightOf(encoded_)));

  const auto result_ = crypto_use_cases_ptr->Decode(test_config::kEncodedTestWStr);

  ASSERT_EQ(typeid(result_), typeid(StringEither));
  ASSERT_FALSE(result_);

  result_.WhenLeft([error_](const auto left) {
    ASSERT_EQ(typeid(left), typeid(std::exception));
    ASSERT_STREQ(error_.what(), left.what());
  });
}

TEST_F(CryptoUseCasesTest, DecodeFailureDecodeError) {
  const auto error_ = std::runtime_error("Decode Error");

  EXPECT_CALL(*mock_crypto_repository, GetSid())
  .Times(1)
  .WillOnce(Return(WStringEither::RightOf(test_config::kSid)));

  EXPECT_CALL(*mock_crypto_repository, Decode(::testing::_, ::testing::_))
  .Times(1)
  .WillOnce(Return(StringEither::LeftOf(error_)));

  const auto result_ = crypto_use_cases_ptr->Decode(test_config::kEncodedTestWStr);

  ASSERT_EQ(typeid(result_), typeid(StringEither));
  ASSERT_FALSE(result_);

  result_.WhenLeft([error_](const auto left) {
    ASSERT_EQ(typeid(left), typeid(std::exception));
    ASSERT_STREQ(error_.what(), left.what());
  });
}

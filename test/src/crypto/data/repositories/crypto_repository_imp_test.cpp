//
// Created by nim on 08.09.2021.
//

#include "../../../../test_config.h"
#include <common/base_types.h>
#include <common/helpers/data_helper.h>
#include <crypto/data/ports/providers/token_provider.h>
#include <crypto/data/repositories/crypto_repository_imp.h>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

using ::testing::AtLeast;
using ::testing::Return;
using TokenInformationEither = TokenProvider::TokenInformationEither;
using TokenProviderPtr = TokenProvider::TokenProviderPtr;

class MockTokenProvider : public TokenProvider {
 public:
  MOCK_METHOD(HandleEither, GetToken, (), (noexcept));
  MOCK_METHOD(TokenInformationEither, GetTokenInformation, (HandlePtr), (noexcept));
  MOCK_METHOD(BoolEither, IsValidSidInToken, (TokenInformationPtr), (noexcept));
  MOCK_METHOD(StringEither, SidToString, (TokenInformationPtr), (noexcept));
};

std::shared_ptr<MockTokenProvider> mock_token_provider;
CryptoRepositoryImp crypto_repository_imp {nullptr};

class CryptoRepositoryImpTest : public ::testing::Test {
 protected:
  static void SetUpTestSuite() {
    mock_token_provider = std::make_shared<MockTokenProvider>();
    crypto_repository_imp = CryptoRepositoryImp(TokenProviderPtr(mock_token_provider));
  }

  static void TearDownTestSuite() {
    crypto_repository_imp.~CryptoRepositoryImp();
    mock_token_provider.reset();
  }
};


TEST_F(CryptoRepositoryImpTest, GetSidTestSuccess) {
  const auto sid_string_ = std::string("User SID");
  auto handle_ = INVALID_HANDLE_VALUE;
  auto handle_ptr_ = data_helper::MakeHandleSharedPtr(handle_);
  const auto token_info_ = std::make_shared<TOKEN_INFORMATION_CLASS>();

  EXPECT_CALL(*mock_token_provider, GetToken())
      .Times(1)
      .WillOnce(Return(HandleEither::RightOf(handle_ptr_)));

  EXPECT_CALL(*mock_token_provider, GetTokenInformation(::testing::_))
      .Times(1)
      .WillOnce(Return(TokenInformationEither::RightOf(token_info_)));

  EXPECT_CALL(*mock_token_provider, IsValidSidInToken(::testing::_))
      .Times(1)
      .WillOnce(Return(BoolEither::RightOf(true)));

  EXPECT_CALL(*mock_token_provider, SidToString(::testing::_))
      .Times(1)
      .WillOnce(Return(StringEither::RightOf(sid_string_)));

  const auto result_ = crypto_repository_imp.GetSid();

  ASSERT_EQ(typeid(result_), typeid(StringEither));
  ASSERT_TRUE(result_);

  result_.WhenRight([sid_string_](const auto value) {
    ASSERT_EQ(typeid(value), typeid(std::string));
    ASSERT_STREQ(value.c_str() , sid_string_.c_str());
  });
}

TEST_F(CryptoRepositoryImpTest, GetSidGetTokenError) {
  const auto error = std::runtime_error("GetToken Error");

  EXPECT_CALL(*mock_token_provider, GetToken())
  .Times(1)
  .WillOnce(Return(HandleEither::LeftOf(error)));

  const auto result_ = crypto_repository_imp.GetSid();

  ASSERT_EQ(typeid(result_), typeid(StringEither));
  ASSERT_TRUE(!result_);

  result_.WhenLeft([error](const auto left) {
    const auto message = left.what();
    ASSERT_STREQ(error.what(), message);
  });
}

TEST_F(CryptoRepositoryImpTest, GetSidGetTokenInformationError) {
  const auto error = std::runtime_error("GetTokenInformation Error");
  auto handle_ = INVALID_HANDLE_VALUE;
  auto handle_ptr_ = data_helper::MakeHandleSharedPtr(handle_);

  EXPECT_CALL(*mock_token_provider, GetToken())
  .Times(1)
  .WillOnce(Return(HandleEither::RightOf(handle_ptr_)));

  EXPECT_CALL(*mock_token_provider, GetTokenInformation(::testing::_))
  .Times(1)
  .WillOnce(Return(TokenInformationEither::LeftOf(error)));

  const auto result_ = crypto_repository_imp.GetSid();

  ASSERT_EQ(typeid(result_), typeid(StringEither));
  ASSERT_TRUE(!result_);

  result_.WhenLeft([error](const auto left) {
    const auto message = left.what();
    ASSERT_STREQ(error.what(), message);
  });
}

TEST_F(CryptoRepositoryImpTest, GetSidIsValidSidInTokenError) {
  const auto error = std::runtime_error("IsValidSidInToken Error");
  auto handle_ = INVALID_HANDLE_VALUE;
  auto handle_ptr_ = data_helper::MakeHandleSharedPtr(handle_);
  const auto token_info_ = std::make_shared<TOKEN_INFORMATION_CLASS>();

  EXPECT_CALL(*mock_token_provider, GetToken())
  .Times(1)
  .WillOnce(Return(HandleEither::RightOf(handle_ptr_)));

  EXPECT_CALL(*mock_token_provider, GetTokenInformation(::testing::_))
  .Times(1)
  .WillOnce(Return(TokenInformationEither::RightOf(token_info_)));

  EXPECT_CALL(*mock_token_provider, IsValidSidInToken(::testing::_))
  .Times(1)
  .WillOnce(Return(BoolEither::LeftOf(error)));

  const auto result_ = crypto_repository_imp.GetSid();

  ASSERT_EQ(typeid(result_), typeid(StringEither));
  ASSERT_TRUE(!result_);

  result_.WhenLeft([error](const auto left) {
    const auto message = left.what();
    ASSERT_STREQ(error.what(), message);
  });
}

TEST_F(CryptoRepositoryImpTest, GetSidSidToStringError) {
  const auto error = std::runtime_error("SidToString Error");
  auto handle_ = INVALID_HANDLE_VALUE;
  auto handle_ptr_ = data_helper::MakeHandleSharedPtr(handle_);
  const auto token_info_ = std::make_shared<TOKEN_INFORMATION_CLASS>();

  EXPECT_CALL(*mock_token_provider, GetToken())
  .Times(1)
  .WillOnce(Return(HandleEither::RightOf(handle_ptr_)));

  EXPECT_CALL(*mock_token_provider, GetTokenInformation(::testing::_))
  .Times(1)
  .WillOnce(Return(TokenInformationEither::RightOf(token_info_)));

  EXPECT_CALL(*mock_token_provider, IsValidSidInToken(::testing::_))
  .Times(1)
  .WillOnce(Return(BoolEither::RightOf(true)));

  EXPECT_CALL(*mock_token_provider, SidToString(::testing::_))
  .Times(1)
  .WillOnce(Return(StringEither::LeftOf(error)));

  const auto result_ = crypto_repository_imp.GetSid();

  ASSERT_EQ(typeid(result_), typeid(StringEither));
  ASSERT_TRUE(!result_);

  result_.WhenLeft([error](const auto left) {
    const auto message = left.what();
    ASSERT_STREQ(error.what(), message);
  });
}


TEST_F(CryptoRepositoryImpTest, EncodeTestFailure) {
  const auto error = std::runtime_error("Not Implemented");

  const auto result_ = crypto_repository_imp.Encode(test_config::kEncodedTestStr);

  ASSERT_EQ(typeid(result_), typeid(WStringEither));
  ASSERT_TRUE(!result_);

  result_.WhenLeft([error](const auto left) {
    const auto message = left.what();
    ASSERT_STREQ(error.what(), message);
  });
}

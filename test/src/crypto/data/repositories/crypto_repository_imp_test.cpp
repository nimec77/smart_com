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

TEST(CryptoRepositoryImpTest, GetSidTestSuccess) {
  const auto sid_string_ = std::string("User SID");
  auto handle_ = INVALID_HANDLE_VALUE;
  auto handle_ptr_ = data_helper::MakeHandleSharedPtr(handle_);
  const auto token_info_ = std::make_shared<TOKEN_INFORMATION_CLASS>();

  const auto mock_token_provider_ = std::make_shared<MockTokenProvider>();
  auto crypto_repository_imp_ = CryptoRepositoryImp(TokenProviderPtr(mock_token_provider_));

  EXPECT_CALL(*mock_token_provider_, GetToken())
      .Times(1)
      .WillOnce(Return(HandleEither::RightOf(handle_ptr_)));

  EXPECT_CALL(*mock_token_provider_, GetTokenInformation(::testing::_))
      .Times(1)
      .WillOnce(Return(TokenInformationEither::RightOf(token_info_)));

  EXPECT_CALL(*mock_token_provider_, IsValidSidInToken(::testing::_))
      .Times(1)
      .WillOnce(Return(BoolEither::RightOf(true)));

  EXPECT_CALL(*mock_token_provider_, SidToString(::testing::_))
      .Times(1)
      .WillOnce(Return(StringEither::RightOf(sid_string_)));

  const auto result_ = crypto_repository_imp_.GetSid();

  ASSERT_EQ(typeid(result_), typeid(StringEither));
  ASSERT_TRUE(result_);

  result_.WhenRight([sid_string_](const auto value) {
    ASSERT_EQ(typeid(value), typeid(std::string));
    ASSERT_STREQ(value.c_str() , sid_string_.c_str());
  });
}

TEST(CryptoRepositoryImpTest, EncodeTestFailure) {
  const auto error = std::runtime_error("Not Implemented");

  const auto mock_token_provider_ = std::make_shared<MockTokenProvider>();
  auto crypto_repository_imp_ = CryptoRepositoryImp(TokenProviderPtr(mock_token_provider_));

  const auto result_ = crypto_repository_imp_.Encode(test_config::kEncodedTestStr);

  ASSERT_EQ(typeid(result_), typeid(WStringEither));
  ASSERT_TRUE(!result_);

  result_.WhenLeft([error](const auto left) {
    const auto message = left.what();
    ASSERT_STREQ(error.what(), message);
  });
}

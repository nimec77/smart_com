//
// Created by nim on 08.09.2021.
//

#include "../../../../test_config.h"
#include <crypto/data/ports/providers/token_provider.h>
#include <crypto/data/repositories/crypto_repository_imp.h>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

using ::testing::AtLeast;
using ::testing::Return;
using WStringEither = CryptoRepository::WStringEither;
using HandleEither = TokenProvider::HandleEither;

class MockTokenProvider : public TokenProvider {
 public:
  MOCK_METHOD(HandleEither, GetToken, (), (noexcept));
};

TEST(CryptoRepositoryImpTest, GetTokenTestSuccess) {
  const auto handle_ = reinterpret_cast<HANDLE>(1);
  const auto mock_token_provider_ = std::make_shared<MockTokenProvider>();
  auto crypto_repository_imp_ = CryptoRepositoryImp(TokenProvider::TokenProviderPtr(mock_token_provider_));

  EXPECT_CALL(*mock_token_provider_, GetToken())
      .Times(1)
      .WillOnce(Return(HandleEither ::RightOf(std::make_shared<HANDLE>(handle_))));

  const auto result_ = crypto_repository_imp_.Encode(test_config::kEncodedTestStr);

  ASSERT_EQ(typeid(result_), typeid(WStringEither));
  ASSERT_TRUE(result_);

  result_.WhenRight([](const auto value) {
    ASSERT_EQ(typeid(value), typeid(const wchar_t *));
    ASSERT_STREQ(value, L"Token");
  });
}

TEST(CryptoRepositoryImpTest, GetTokenTestFailure) {
  const auto error = std::runtime_error("GetToken Error");

  const auto mock_token_provider_ = std::make_shared<MockTokenProvider>();
  auto crypto_repository_imp_ = CryptoRepositoryImp(TokenProvider::TokenProviderPtr(mock_token_provider_));

  EXPECT_CALL(*mock_token_provider_, GetToken())
      .Times(1)
      .WillOnce(Return(HandleEither ::LeftOf(error)));

  const auto result_ = crypto_repository_imp_.Encode(test_config::kEncodedTestStr);

  ASSERT_EQ(typeid(result_), typeid(WStringEither));
  ASSERT_TRUE(!result_);

  result_.WhenLeft([error](const auto left) {
    const auto message = left.what();
    ASSERT_STREQ(error.what(), message);
  });
}
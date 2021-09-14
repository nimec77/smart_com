//
// Created by nim on 08.09.2021.
//

#include "../../../../test_config.h"
#include <common/base_types.h>
#include <common/helpers/helper.h>
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

std::shared_ptr<MockSidProvider> mock_sid_provider;
CryptoRepositoryImp crypto_repository_imp{nullptr};

class CryptoRepositoryImpTest : public ::testing::Test {
 protected:
  static void SetUpTestSuite() {
    mock_sid_provider = std::make_shared<MockSidProvider>();
    crypto_repository_imp = CryptoRepositoryImp(SidProvider::SidProviderPtr{mock_sid_provider});
  }

  static void TearDownTestSuite() {
    crypto_repository_imp.~CryptoRepositoryImp();
    mock_sid_provider.reset();
  }
};

TEST_F(CryptoRepositoryImpTest, GetNameTestSuccess) {
  const auto username_ = std::wstring{L"Username"};

  EXPECT_CALL(*mock_sid_provider, GetName())
  .Times(1)
  .WillOnce(Return(WStringEither::RightOf(username_)));
}

/*
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

  EXPECT_CALL(*mock_token_provider, GetTokenInfo(::testing::_))
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

  EXPECT_CALL(*mock_token_provider, GetTokenInfo(::testing::_))
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

  EXPECT_CALL(*mock_token_provider, GetTokenInfo(::testing::_))
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
*/
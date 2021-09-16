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
  const auto w_user_sid_ = std::wstring{L"User Sid"};
  const auto user_sid_ = helper::Utf16ToUtf8(w_user_sid_.c_str()) | "";

  EXPECT_CALL(*mock_sid_provider, GetName())
      .Times(1)
      .WillOnce(Return(WStringEither::RightOf(username_)));

  EXPECT_CALL(*mock_sid_provider, GetAccountSidFromName(::testing::_))
      .Times(1)
      .WillOnce(Return(WStringEither::RightOf(w_user_sid_)));

  auto result_ = crypto_repository_imp.GetSid();

  ASSERT_EQ(typeid(result_), typeid(StringEither));

  ASSERT_TRUE(result_);

  result_.WhenRight([user_sid_](const auto sid) {
    ASSERT_EQ(typeid(sid), typeid(std::string));
    ASSERT_STREQ(sid.c_str(), user_sid_.c_str());
  });
}

TEST_F(CryptoRepositoryImpTest, GetNameTestFailedGetName) {
  const auto error_ = std::runtime_error("GetName Error");
  const auto w_user_sid_ = std::wstring{L"User Sid"};

  EXPECT_CALL(*mock_sid_provider, GetName())
      .Times(1)
      .WillOnce(Return(WStringEither::LeftOf(error_)));

  EXPECT_CALL(*mock_sid_provider, GetAccountSidFromName(::testing::_))
      .Times(testing::AtLeast(0))
      .WillOnce(Return(WStringEither::RightOf(w_user_sid_)));

  auto result_ = crypto_repository_imp.GetSid();

  ASSERT_EQ(typeid(result_), typeid(StringEither));

  ASSERT_FALSE(result_);

  result_.WhenLeft([error_](const auto left) {
    ASSERT_EQ(typeid(left), typeid(std::exception));
    ASSERT_STREQ(left.what(), error_.what());
  });
}

TEST_F(CryptoRepositoryImpTest, GetNameTestFailedGetAccountSidFromName) {
  const auto username_ = std::wstring{L"Username"};
  const auto error_ = std::runtime_error("GetAccountSidFromName Error");

  EXPECT_CALL(*mock_sid_provider, GetName())
      .Times(1)
      .WillOnce(Return(WStringEither::RightOf(username_)));

  EXPECT_CALL(*mock_sid_provider, GetAccountSidFromName(::testing::_))
      .Times(1)
      .WillOnce(Return(WStringEither::LeftOf(error_)));

  auto result_ = crypto_repository_imp.GetSid();

  ASSERT_EQ(typeid(result_), typeid(StringEither));

  ASSERT_FALSE(result_);

  result_.WhenLeft([error_](const auto left) {
    ASSERT_EQ(typeid(left), typeid(std::exception));
    ASSERT_STREQ(left.what(), error_.what());
  });
}

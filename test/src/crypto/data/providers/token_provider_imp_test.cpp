//
// Created by nim on 09.09.2021.
//

#include <crypto/data/providers/token_provider_imp.h>
#include <gtest/gtest.h>

TokenProvider *token_provider{nullptr};

class TokenProviderImpTest : public ::testing::Test {
 protected:
  static void SetUpTestSuite() {
    token_provider = new TokenProviderImp();
  }

  static void TearDownTestSuite() {
    delete token_provider;
  }
};

TEST_F(TokenProviderImpTest, GetNameTestSuccess) {

  const auto result_ = token_provider->GetName();

  ASSERT_EQ(typeid(result_), typeid(WStringEither));

  ASSERT_TRUE(result_);

  result_.WhenRight([](const auto username) {
    ASSERT_EQ(typeid(username), typeid(std::wstring));
  });
}

TEST_F(TokenProviderImpTest, GetAccountSidFromNameTestSuccess) {
  auto username_ = token_provider->GetName();


  const auto result_ = token_provider->GetAccountSidFromName(username_ | L"");

  ASSERT_EQ(typeid(result_), typeid(WStringEither));

  ASSERT_TRUE(result_);

  result_.WhenRight([](const auto sid) {
    std::wcout << sid << std::endl;
    ASSERT_EQ(typeid(sid), typeid(std::wstring));
  });
}

TEST_F(TokenProviderImpTest, GetAccountSidFromNameTestFailed) {

  const auto result_ = token_provider->GetAccountSidFromName(L"empty_name");

  ASSERT_EQ(typeid(result_), typeid(WStringEither));

  ASSERT_TRUE(!result_);

  result_.WhenLeft([](const auto left) {
    const auto message = left.what();
    std::cout << message << std::endl;
    ASSERT_STREQ(message, "TokenProvider::GetAccountSidFromName LookupAccountNameLocalW error: 534");
  });
}
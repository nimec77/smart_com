//
// Created by nim on 20.09.2021.
//

#include "../../../test_config.h"
#include <crypto/data/providers/crypto_provider_imp.h>
#include <crypto/data/providers/sid_provider_imp.h>
#include <crypto/data/repositories/crypto_repository_imp.h>
#include <crypto/gateways/crypto_gateway_imp.h>
#include <gtest/gtest.h>
#include <common/pods/enums/exception_type.h>

SidProvider::SidProviderPtr sid_provider_ptr;
CryptoProvider::CryptoProviderPtr crypto_provider_ptr;
CryptoRepository::CryptoRepositoryPtr crypto_repository_ptr;
CryptoUseCases crypto_use_cases;
CryptoGateway *crypto_gateway_ptr;

class CryptoGatewayTest : public ::testing::Test {
 protected:
  static void SetUpTestSuite() {
    sid_provider_ptr = std::shared_ptr<SidProvider>(new SidProviderImp());
    crypto_provider_ptr = std::shared_ptr<CryptoProvider>(new CryptoProviderImp());
    crypto_repository_ptr = std::shared_ptr<CryptoRepository>(
        new CryptoRepositoryImp(sid_provider_ptr, crypto_provider_ptr));
    crypto_use_cases = CryptoUseCases(crypto_repository_ptr);
    crypto_gateway_ptr = new CryptoGatewayImp(crypto_use_cases);
  }

  static void TearDownTestSuite() {
    delete crypto_gateway_ptr;
    crypto_use_cases.~CryptoUseCases();
    crypto_repository_ptr.reset();
    crypto_provider_ptr.reset();
    sid_provider_ptr.reset();
  }
};

TEST_F(CryptoGatewayTest, EncodeSuccessTest) {
  const auto result_ = crypto_gateway_ptr->Encode(test_config::kEncodedTestWStr);

  ASSERT_EQ(typeid(result_), typeid(EitherPod<const char *> *));


  ASSERT_FALSE(result_->is_left);

  ASSERT_EQ(typeid(result_->right), typeid(const char *));

  delete result_;
}

TEST_F(CryptoGatewayTest, DecodeSuccessTest) {

  const auto encoded_ = crypto_gateway_ptr->Encode(test_config::kEncodedTestWStr);

  const auto str_ = std::string{encoded_->right};
  const auto w_str_ = std::wstring{str_.begin(), str_.end()};
  const auto result_ = crypto_gateway_ptr->Decode(w_str_.c_str());

  ASSERT_FALSE(result_->is_left);

  ASSERT_EQ(typeid(result_->right), typeid(const char *));

  const auto decoded_ = helper::Utf16ToUtf8(test_config::kEncodedTestWStr) | "";

  ASSERT_STREQ(result_->right, decoded_.c_str());
}

TEST_F(CryptoGatewayTest, DecodeFailureTest) {
  const auto result_ = crypto_gateway_ptr->Decode(test_config::kEncodedTestWStr);

  ASSERT_TRUE(result_->is_left);

  ASSERT_EQ(typeid(result_->left), typeid(ExceptionPod));

  const auto exception_pod_ = result_->left;

  ASSERT_EQ(exception_pod_.exception_type, ExceptionType::kException);
  ASSERT_STREQ(exception_pod_.message, "invalid stoul argument");
}
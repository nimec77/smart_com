//
// Created by nim on 19.07.2021.
//

#include "../../../test_config.h"
#include <gtest/gtest.h>
#include <smarteam/data/repositories/smarteam_repository_imp.h>
#include <smarteam/domain/use_cases/ports/gateways/user_gateway.h>
#include <smarteam/gateways/user_gateway_imp.h>
#include <common/pods/either_pod.h>

SmarteamRepository::SmarteamRepositoryPtr smarteam_repo_ptr;

class UserGatewayTest : public ::testing::Test {
 protected:
  static void SetUpTestSuite() {
    //    std::cout << "SetUpTestSuite" << std::endl;
    CoInitialize(nullptr);
    smarteam_repo_ptr = SmarteamRepositoryImp::GetInstance() | nullptr;
    ASSERT_NE(smarteam_repo_ptr, nullptr);
  }

  static void TearDownTestSuite() {
    //    std::cout << "TearDownTestSuite" << std::endl;
  }
};

TEST_F(UserGatewayTest, UserGatewayCreateTest) {
  const auto user_use_cases_ = UserUseCases(smarteam_repo_ptr);
  const auto user_gateway_ = UserGatewayImp(user_use_cases_);
  ASSERT_EQ(typeid(user_gateway_), typeid(UserGatewayImp));
}

TEST_F(UserGatewayTest, UserGatewayLoginTestSuccess) {
  const auto user_use_cases_ = UserUseCases(smarteam_repo_ptr);
  auto user_gateway_ = UserGatewayImp(user_use_cases_);

  user_gateway_.UserLogoff();

  const auto result_ = user_gateway_.UserLogin(test_config::kUserName, test_config::kUserPassword);

  ASSERT_EQ(typeid(result_), typeid(new EitherPod<bool>{false, {}, true}));

  ASSERT_EQ(result_->is_left, false);

  ASSERT_EQ(result_->right, true);
}

TEST_F(UserGatewayTest, UserGatewayLoginTestFailure) {
  const auto user_use_cases_ = UserUseCases(smarteam_repo_ptr);
  auto user_gateway_ = UserGatewayImp(user_use_cases_);

  user_gateway_.UserLogoff();

  const auto result_ = user_gateway_.UserLogin(test_config::kUserName, test_config::kUserFakePassword);

  ASSERT_EQ(typeid(result_), typeid(new EitherPod<bool>{false, {}, false}));

  ASSERT_EQ(result_->is_left, false);

  ASSERT_EQ(result_->right, false);
}

TEST_F(UserGatewayTest, UserGatewayLogoffTest) {
  const auto user_use_cases_ = UserUseCases(smarteam_repo_ptr);
  auto user_gateway_ = UserGatewayImp(user_use_cases_);

  user_gateway_.UserLogin(test_config::kUserName, test_config::kUserPassword);

  const auto result_ = user_gateway_.UserLogoff();

  ASSERT_EQ(typeid(result_), typeid(new EitherPod<bool>{false, {}, true}));

  ASSERT_EQ(result_->is_left, false);

  ASSERT_EQ(result_->right, true);
}
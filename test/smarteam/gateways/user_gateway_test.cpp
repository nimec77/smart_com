//
// Created by nim on 19.07.2021.
//

#include "../../test_config.h"
#include <gtest/gtest.h>
#include <smarteam/data/repositories/smarteam_repository_imp.h>
#include <smarteam/gateways/user_gateway_imp.h>

SmarteamRepositoryImp *smarteam_repo_ptr;

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
  const auto user_gateway_ = UserGatewayImp(*smarteam_repo_ptr);
  ASSERT_EQ(typeid(user_gateway_), typeid(UserGatewayImp));
}

TEST_F(UserGatewayTest, UserGatewayLoginTest) {
  auto user_gateway_ = UserGatewayImp(*smarteam_repo_ptr);

  const auto result_ = user_gateway_.UserLogin(test_config::kUserName, test_config::kUserPassword);

  ASSERT_TRUE(result_);

  ASSERT_EQ(typeid(result_), typeid(UserGateway::BoolEither));

  result_.WhenRight([](const auto is_user_login) {
    ASSERT_EQ(typeid(is_user_login), typeid(bool));
    ASSERT_TRUE(is_user_login);
  });
}
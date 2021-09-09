//
// Created by nim on 16.07.2021.
//

#include "../../../../test_config.h"
#include <gtest/gtest.h>
#include <common/base_types.h>
#include <smarteam/data/repositories/smarteam_repository_imp.h>

class SmarteamRepositoryTest : public ::testing::Test {
 protected:
  static void SetUpTestSuite() {
    //    std::cout << "SetUpTestSuite" << std::endl;
    CoInitialize(nullptr);
  }

  static void TearDownTestSuite() {
    //    std::cout << "TearDownTestSuite" << std::endl;
  }
};

TEST_F(SmarteamRepositoryTest, SmarteamRepositoryGetInstanceTest) {
  const auto smarteam_repo_either_ = SmarteamRepositoryImp::GetInstance();

  ASSERT_EQ(typeid(smarteam_repo_either_), typeid(SmarteamRepositoryImp::SmarteamRepoEither));

  ASSERT_TRUE(smarteam_repo_either_);

  smarteam_repo_either_.WhenRight([](const auto smarteam_rep_ptr) {
    ASSERT_EQ(typeid(smarteam_rep_ptr), typeid(SmarteamRepository::SmarteamRepositoryPtr));

    ASSERT_NE(smarteam_rep_ptr, nullptr);
  });
}

TEST_F(SmarteamRepositoryTest, SmarteamRepositoryUserLogoffTest) {
  const auto smarteam_repo_either_ = SmarteamRepositoryImp::GetInstance();

  ASSERT_TRUE(smarteam_repo_either_);

  const auto smarteam_repo_ptr_ = smarteam_repo_either_ | nullptr;

  ASSERT_NE(smarteam_repo_ptr_, nullptr);

  const auto logged_either_ = smarteam_repo_ptr_->UserLogoff();

  ASSERT_EQ(typeid(logged_either_), typeid(BoolEither));

  ASSERT_TRUE(logged_either_);

  logged_either_.WhenRight([](const auto is_log_off) {
    ASSERT_EQ(typeid(is_log_off), typeid(bool));

    ASSERT_TRUE(is_log_off);
  });
}

TEST_F(SmarteamRepositoryTest, SmarteamRepositoryUserLoginTest) {
  const auto smarteam_repo_either_ = SmarteamRepositoryImp::GetInstance();

  ASSERT_TRUE(smarteam_repo_either_);

  const auto smarteam_repo_ptr_ = smarteam_repo_either_ | nullptr;

  ASSERT_NE(smarteam_repo_ptr_, nullptr);

  const auto login_either_ = smarteam_repo_ptr_->UserLogin(_bstr_t{test_config::kUserName}, _bstr_t{test_config::kUserPassword});

  ASSERT_EQ(typeid(login_either_), typeid(BoolEither));

  ASSERT_TRUE(login_either_);

  login_either_.WhenRight([](const auto is_login) {
    ASSERT_EQ(typeid(is_login), typeid(bool));
    ASSERT_TRUE(is_login);
  });
}

TEST_F(SmarteamRepositoryTest, SmarteamRepositoryUserLoginFailTest) {
  const auto smarteam_repo_either_ = SmarteamRepositoryImp::GetInstance();

  ASSERT_TRUE(smarteam_repo_either_);

  const auto smarteam_repo_ptr_ = smarteam_repo_either_ | nullptr;

  ASSERT_NE(smarteam_repo_ptr_, nullptr);

  const auto is_logo_off_ = smarteam_repo_ptr_->UserLogoff();

  ASSERT_TRUE(is_logo_off_);

  const auto password_ = _bstr_t{test_config::kUserPassword} + _bstr_t{"1"};
  const auto login_either_ = smarteam_repo_ptr_->UserLogin(_bstr_t{test_config::kUserName}, password_);

  ASSERT_EQ(typeid(login_either_), typeid(BoolEither));

  ASSERT_TRUE(login_either_);

  login_either_.WhenRight([](const auto is_login) {
    ASSERT_EQ(typeid(is_login), typeid(bool));
    ASSERT_FALSE(is_login);
  });
}

TEST_F(SmarteamRepositoryTest, SmarteamRepositoryUserLoggedOnTest) {
  const auto smarteam_repo_either_ = SmarteamRepositoryImp::GetInstance();

  ASSERT_TRUE(smarteam_repo_either_);

  const auto smarteam_repo_ptr_ = smarteam_repo_either_ | nullptr;

  ASSERT_NE(smarteam_repo_ptr_, nullptr);

  const auto login_either_ = smarteam_repo_ptr_->UserLogin(_bstr_t{test_config::kUserName}, _bstr_t{test_config::kUserPassword});

  ASSERT_TRUE(login_either_);

  const auto logged_on_either_ = smarteam_repo_ptr_->UserLoggedOn();

  ASSERT_EQ(typeid(logged_on_either_), typeid(BoolEither));

  ASSERT_TRUE(logged_on_either_);

  logged_on_either_.WhenRight([](const auto is_logged_in) {
    ASSERT_EQ(typeid(is_logged_in), typeid(bool));
    ASSERT_TRUE(is_logged_in);
  });
}
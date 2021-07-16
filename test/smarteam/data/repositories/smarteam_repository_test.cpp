//
// Created by nim on 16.07.2021.
//

#include <gtest/gtest.h>
#include <smarteam/data/repositories/smarteam_repository.h>

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
  const auto smarteam_repo_either = SmarteamRepository::GetInstance();

  ASSERT_EQ(typeid(smarteam_repo_either), typeid(SmarteamRepository::SmarteamRepoEither));

  ASSERT_TRUE(smarteam_repo_either);

  smarteam_repo_either.WhenRight([](const auto smarteam_rep_ptr) {
    ASSERT_EQ(typeid(smarteam_rep_ptr), typeid(SmarteamRepository *));

    ASSERT_NE(smarteam_rep_ptr, nullptr);
  });
}

TEST_F(SmarteamRepositoryTest, SmarteamRepositoryUserLogoffTest) {
  const auto smarteam_repo_either = SmarteamRepository::GetInstance();

  ASSERT_TRUE(smarteam_repo_either);

  const auto smarteam_repo_ptr = smarteam_repo_either | nullptr;

  ASSERT_NE(smarteam_repo_ptr, nullptr);

  const auto logged_either = smarteam_repo_ptr->UserLogoff();

  ASSERT_EQ(typeid(logged_either), typeid(SmarteamRepository::BoolEither));

  ASSERT_TRUE(logged_either);

  logged_either.WhenRight([](const auto is_log_off) {
    ASSERT_EQ(typeid(is_log_off), typeid(bool));

    ASSERT_TRUE(is_log_off);
  });
}
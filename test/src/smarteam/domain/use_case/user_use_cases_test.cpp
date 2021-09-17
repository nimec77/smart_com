//
// Created by nim on 07.09.2021.
//

#include "../../../../test_config.h"
#include <common/base_types.h>
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <smarteam/domain/use_cases/ports/repositories/smarteam_repository.h>
#include <smarteam/domain/use_cases/user_use_cases.h>

using ::testing::AtLeast;
using ::testing::Return;

class MockSmarteamRepository : public SmarteamRepository {
 public:
  MOCK_METHOD(BoolEither, UserLoggedOn, (), (noexcept));
  MOCK_METHOD(BoolEither, UserLogoff, (), (noexcept));
  MOCK_METHOD(BoolEither, UserLogin, (const _bstr_t &user_name, const _bstr_t &password), (noexcept));
};

std::shared_ptr<MockSmarteamRepository> mock_smarteam_repository;
UserUseCases *user_use_cases_ptr{nullptr};

class UserUseCasesTest : public ::testing::Test {
 protected:
  static void SetUpTestSuite() {
    mock_smarteam_repository = std::make_shared<MockSmarteamRepository>();
    user_use_cases_ptr = new UserUseCases(mock_smarteam_repository);
  }

  static void TearDownTestSuite() {
    delete user_use_cases_ptr;
    mock_smarteam_repository.reset();
  }
};

TEST_F(UserUseCasesTest, UserLogoffTestNoLoggined) {

  EXPECT_CALL(*mock_smarteam_repository, UserLoggedOn())
      .Times(1)
      .WillOnce(Return(BoolEither::RightOf(false)));

  const auto result_ = user_use_cases_ptr->UserLogoff();

  ASSERT_EQ(typeid(result_), typeid(BoolEither));

  ASSERT_TRUE(result_);

  result_.WhenRight([](const auto is_logoff) {
    ASSERT_EQ(typeid(is_logoff), typeid(bool));
    ASSERT_TRUE(is_logoff);
  });
}

TEST_F(UserUseCasesTest, UserLogoffTestLoggined) {

  EXPECT_CALL(*mock_smarteam_repository, UserLoggedOn())
      .Times(1)
      .WillOnce(Return(BoolEither::RightOf(true)));

  EXPECT_CALL(*mock_smarteam_repository, UserLogoff)
      .Times(1)
      .WillOnce(Return(BoolEither::RightOf(true)));

  const auto result_ = user_use_cases_ptr->UserLogoff();

  ASSERT_EQ(typeid(result_), typeid(BoolEither));

  ASSERT_TRUE(result_);

  result_.WhenRight([](const auto is_logoff) {
    ASSERT_EQ(typeid(is_logoff), typeid(bool));
    ASSERT_TRUE(is_logoff);
  });
}

TEST_F(UserUseCasesTest, UserLogoffLoggedOnError) {
  const auto error = std::runtime_error("LoggedOn Error");

  EXPECT_CALL(*mock_smarteam_repository, UserLoggedOn())
      .Times(1)
      .WillOnce(Return(BoolEither::LeftOf(error)));

  EXPECT_CALL(*mock_smarteam_repository, UserLogoff)
      .Times(AtLeast(0))
      .WillOnce(Return(BoolEither::RightOf(true)));

  const auto result_ = user_use_cases_ptr->UserLogoff();

  ASSERT_EQ(typeid(result_), typeid(BoolEither));

  ASSERT_TRUE(!result_);

  result_.WhenLeft([error](const auto left) {
    ASSERT_EQ(typeid(left), typeid(std::exception));
    ASSERT_STREQ(left.what(), error.what());
  });
}

TEST_F(UserUseCasesTest, UserLogoffError) {
  const auto error = std::runtime_error("Logoff Error");

  EXPECT_CALL(*mock_smarteam_repository, UserLoggedOn())
      .Times(1)
      .WillOnce(Return(BoolEither::RightOf(true)));

  EXPECT_CALL(*mock_smarteam_repository, UserLogoff)
      .Times(1)
      .WillOnce(Return(BoolEither::LeftOf(error)));

  const auto result_ = user_use_cases_ptr->UserLogoff();

  ASSERT_EQ(typeid(result_), typeid(BoolEither));

  ASSERT_TRUE(!result_);

  result_.WhenLeft([error](const auto left) {
    ASSERT_EQ(typeid(left), typeid(std::exception));
    ASSERT_STREQ(left.what(), error.what());
  });
}

TEST_F(UserUseCasesTest, UserLogoffFirstError) {
  const auto first_error = std::runtime_error("LoggedOn Error");
  const auto second_error = std::runtime_error("Logoff Error");

  EXPECT_CALL(*mock_smarteam_repository, UserLoggedOn())
      .Times(1)
      .WillOnce(Return(BoolEither::LeftOf(first_error)));

  EXPECT_CALL(*mock_smarteam_repository, UserLogoff)
      .Times(AtLeast(0))
      .WillOnce(Return(BoolEither::LeftOf(second_error)));

  const auto result_ = user_use_cases_ptr->UserLogoff();

  ASSERT_EQ(typeid(result_), typeid(BoolEither));

  ASSERT_TRUE(!result_);

  result_.WhenLeft([first_error](const auto left) {
    ASSERT_EQ(typeid(left), typeid(std::exception));
    ASSERT_STREQ(left.what(), first_error.what());
  });
}

TEST_F(UserUseCasesTest, UserLoginTestSuccess) {

  EXPECT_CALL(*mock_smarteam_repository, UserLogin(::testing::_, ::testing::_))
      .Times(1)
      .WillOnce(Return(BoolEither::RightOf(true)));

  const auto result_ = user_use_cases_ptr->UserLogin(test_config::kUserName, test_config::kUserPassword);
  ASSERT_EQ(typeid(result_), typeid(BoolEither));

  ASSERT_TRUE(result_);

  result_.WhenRight([](const auto is_logoff) {
    ASSERT_EQ(typeid(is_logoff), typeid(bool));
    ASSERT_TRUE(is_logoff);
  });
}

TEST_F(UserUseCasesTest, UserLoginTestFailure) {

  EXPECT_CALL(*mock_smarteam_repository, UserLogin(::testing::_, ::testing::_))
      .Times(1)
      .WillOnce(Return(BoolEither::RightOf(false)));

  const auto result_ = user_use_cases_ptr->UserLogin(test_config::kUserName, test_config::kUserPassword);
  ASSERT_EQ(typeid(result_), typeid(BoolEither));

  ASSERT_TRUE(result_);

  result_.WhenRight([](const auto is_logoff) {
    ASSERT_EQ(typeid(is_logoff), typeid(bool));
    ASSERT_FALSE(is_logoff);
  });
}

TEST_F(UserUseCasesTest, UserLoginTestException) {
  auto error = std::runtime_error("Login Error");

  EXPECT_CALL(*mock_smarteam_repository, UserLogin(::testing::_, ::testing::_))
      .Times(1)
      .WillOnce(Return(BoolEither::LeftOf(error)));

  const auto result_ = user_use_cases_ptr->UserLogin(test_config::kUserName, test_config::kUserPassword);
  ASSERT_EQ(typeid(result_), typeid(BoolEither));

  ASSERT_FALSE(result_);

  result_.WhenLeft([error](const auto left) {
    ASSERT_EQ(typeid(left), typeid(std::exception));
    ASSERT_STREQ(left.what(), error.what());
  });
}
//
// Created by nim on 07.09.2021.
//

#include "../../../../test_config.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <smarteam/domain/use_cases/ports/repositories/smarteam_repository.h>
#include <smarteam/domain/use_cases/user_use_cases.h>

using ::testing::AtLeast;
using ::testing::Return;
using BoolEither = UserUseCases::BoolEither;

class MockSmarteamRepository : public SmarteamRepository {
 public:
  MOCK_METHOD(BoolEither, UserLoggedOn, (), (noexcept));
  MOCK_METHOD(BoolEither, UserLogoff, (), (noexcept));
  MOCK_METHOD(BoolEither, UserLogin, (const _bstr_t &user_name, const _bstr_t &password), (noexcept));
};

TEST(UserUseCasesTest, UserLogoffTestNoLoggined) {
  MockSmarteamRepository mock_smarteam_repository_;
  auto user_use_cases_ = UserUseCases(mock_smarteam_repository_);

  EXPECT_CALL(mock_smarteam_repository_, UserLoggedOn())
      .Times(1)
      .WillOnce(Return(BoolEither::RightOf(false)));

  const auto result_ = user_use_cases_.UserLogoff();

  ASSERT_EQ(typeid(result_), typeid(UserUseCases::BoolEither));

  ASSERT_TRUE(result_);

  result_.WhenRight([](const auto is_logoff) {
    ASSERT_EQ(typeid(is_logoff), typeid(bool));
    ASSERT_TRUE(is_logoff);
  });
}

TEST(UserUseCasesTest, UserLogoffTestLoggined) {
  MockSmarteamRepository mock_smarteam_repository_;
  auto user_use_cases_ = UserUseCases(mock_smarteam_repository_);

  EXPECT_CALL(mock_smarteam_repository_, UserLoggedOn())
  .Times(1)
  .WillOnce(Return(BoolEither::RightOf(true)));

  EXPECT_CALL(mock_smarteam_repository_, UserLogoff)
  .Times(1)
  .WillOnce(Return(BoolEither::RightOf(true)));

  const auto result_ = user_use_cases_.UserLogoff();

  ASSERT_EQ(typeid(result_), typeid(UserUseCases::BoolEither));

  ASSERT_TRUE(result_);

  result_.WhenRight([](const auto is_logoff) {
    ASSERT_EQ(typeid(is_logoff), typeid(bool));
    ASSERT_TRUE(is_logoff);
  });
}

TEST(UserUseCasesTest, UserLogoffLoggedOnError) {
  const auto error = std::runtime_error("LoggedOn Error");
  MockSmarteamRepository mock_smarteam_repository_;
  auto user_use_cases_ = UserUseCases(mock_smarteam_repository_);

  EXPECT_CALL(mock_smarteam_repository_, UserLoggedOn())
  .Times(1)
  .WillOnce(Return(BoolEither::LeftOf(error)));

  const auto result_ = user_use_cases_.UserLogoff();

  ASSERT_EQ(typeid(result_), typeid(UserUseCases::BoolEither));

  ASSERT_TRUE(!result_);

  result_.WhenLeft([error](const auto left) {
    const auto message = left.what();
    std::cout << message << std::endl;
    ASSERT_STREQ(error.what(), message);
  });

}

TEST(UserUseCasesTest, UserLogoffError) {
  const auto error = std::runtime_error("Logoff Error");
  MockSmarteamRepository mock_smarteam_repository_;
  auto user_use_cases_ = UserUseCases(mock_smarteam_repository_);

  EXPECT_CALL(mock_smarteam_repository_, UserLoggedOn())
  .Times(1)
  .WillOnce(Return(BoolEither::RightOf(true)));

  EXPECT_CALL(mock_smarteam_repository_, UserLogoff)
  .Times(1)
  .WillOnce(Return(BoolEither::LeftOf(error)));

  const auto result_ = user_use_cases_.UserLogoff();

  ASSERT_EQ(typeid(result_), typeid(UserUseCases::BoolEither));

  ASSERT_TRUE(!result_);

  result_.WhenLeft([error](const auto left) {
    const auto message = left.what();
    std::cout << message << std::endl;
    ASSERT_STREQ(error.what(), message);
  });
}

TEST(UserUseCasesTest, UserLogoffFirstError) {
  const auto first_error = std::runtime_error("LoggedOn Error");
  const auto second_error = std::runtime_error("Logoff Error");
  MockSmarteamRepository mock_smarteam_repository_;
  auto user_use_cases_ = UserUseCases(mock_smarteam_repository_);

  EXPECT_CALL(mock_smarteam_repository_, UserLoggedOn())
  .Times(1)
  .WillOnce(Return(BoolEither::LeftOf(first_error)));

  EXPECT_CALL(mock_smarteam_repository_, UserLogoff)
  .Times(AtLeast(0))
  .WillOnce(Return(BoolEither::LeftOf(second_error)));

  const auto result_ = user_use_cases_.UserLogoff();

  ASSERT_EQ(typeid(result_), typeid(UserUseCases::BoolEither));

  ASSERT_TRUE(!result_);

  result_.WhenLeft([first_error](const auto left) {
    const auto message = left.what();
    std::cout << message << std::endl;
    ASSERT_STREQ(first_error.what(), message);
  });
}

TEST(UserUseCasesTest, UserLoginTestSuccess) {
  MockSmarteamRepository mock_smarteam_repository_;
  auto user_use_cases_ = UserUseCases(mock_smarteam_repository_);

  EXPECT_CALL(mock_smarteam_repository_, UserLogin(::testing::_,::testing::_))
  .Times(1)
  .WillOnce(Return(BoolEither::RightOf(true)));

  const auto result_ = user_use_cases_.UserLogin(test_config::kUserName, test_config::kUserPassword);
  ASSERT_EQ(typeid(result_), typeid(UserUseCases::BoolEither));

  ASSERT_TRUE(result_);

  result_.WhenRight([](const auto is_logoff) {
    ASSERT_EQ(typeid(is_logoff), typeid(bool));
    ASSERT_TRUE(is_logoff);
  });
}

TEST(UserUseCasesTest, UserLoginTestFailure) {
  MockSmarteamRepository mock_smarteam_repository_;
  auto user_use_cases_ = UserUseCases(mock_smarteam_repository_);

  EXPECT_CALL(mock_smarteam_repository_, UserLogin(::testing::_,::testing::_))
  .Times(1)
  .WillOnce(Return(BoolEither::RightOf(false)));

  const auto result_ = user_use_cases_.UserLogin(test_config::kUserName, test_config::kUserPassword);
  ASSERT_EQ(typeid(result_), typeid(UserUseCases::BoolEither));

  ASSERT_TRUE(result_);

  result_.WhenRight([](const auto is_logoff) {
    ASSERT_EQ(typeid(is_logoff), typeid(bool));
    ASSERT_TRUE(!is_logoff);
  });
}

TEST(UserUseCasesTest, UserLoginTestException) {
  auto error = std::runtime_error("Login Error");
  MockSmarteamRepository mock_smarteam_repository_;
  auto user_use_cases_ = UserUseCases(mock_smarteam_repository_);

  EXPECT_CALL(mock_smarteam_repository_, UserLogin(::testing::_,::testing::_))
  .Times(1)
  .WillOnce(Return(BoolEither::LeftOf(error)));

  const auto result_ = user_use_cases_.UserLogin(test_config::kUserName, test_config::kUserPassword);
  ASSERT_EQ(typeid(result_), typeid(UserUseCases::BoolEither));

  ASSERT_TRUE(!result_);

  result_.WhenLeft([error](const auto left) {
    const auto message = left.what();
    std::cout << message << std::endl;
    ASSERT_STREQ(error.what(), message);
  });
}
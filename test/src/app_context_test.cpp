//
// Created by nim on 06.09.2021.
//
#include <app_context.h>
#include <gtest/gtest.h>

TEST(AppContextTest, AppContextCreateTest) {
  const auto result = AppContext();

  ASSERT_EQ(typeid(result), typeid(AppContext));
}

TEST(AppContextTest, InitTest) {
  auto app_context = AppContext();

  const auto result_ = app_context.Init();

  ASSERT_EQ(typeid(result_), typeid(new EitherPod<bool>{false, {}, true}));

  ASSERT_EQ(result_->is_left, false);

  ASSERT_EQ(result_->right, true);
}

TEST(AppContextTest, ReleaseTest) {
  auto app_context = AppContext();

  app_context.Init();

  const auto result_ = app_context.Release();

  ASSERT_EQ(typeid(result_), typeid(new EitherPod<bool>{false, {}, true}));

  ASSERT_EQ(result_->is_left, false);

  ASSERT_EQ(result_->right, true);
}

TEST(AppContextTest, GetUserGatewayTest) {
  auto app_context = AppContext();

  const auto result = app_context.GetUserGateway();

  ASSERT_NE(result, nullptr);
}
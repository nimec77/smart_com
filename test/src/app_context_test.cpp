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
  auto app_context_ = AppContext();

  app_context_.Init();

  const auto result_ = app_context_.Release();

  ASSERT_EQ(typeid(result_), typeid(new EitherPod<bool>{false, {}, true}));

  ASSERT_EQ(result_->is_left, false);

  ASSERT_EQ(result_->right, true);
}

TEST(AppContextTest, GetUserGatewayTest) {
  auto app_context_ = AppContext();

  auto result_ = app_context_.GetUserGateway();

  ASSERT_EQ(result_, nullptr);

  app_context_.Init();

  result_ = app_context_.GetUserGateway();

  ASSERT_NE(result_, nullptr);
}

TEST(AppContextTest, GetCryptoGatewayTest) {
  auto app_context_ = AppContext();

  auto result_ = app_context_.GetCryptoGateway();

  ASSERT_EQ(result_, nullptr);

  app_context_.Init();

  result_ = app_context_.GetCryptoGateway();

  ASSERT_NE(result_, nullptr);

}
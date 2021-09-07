//
// Created by nim on 06.09.2021.
//
#include <app_context.h>
#include <gtest/gtest.h>

TEST(AppContextTest, AppContextInitTest) {
  auto app_context = AppContext();

  const auto result = app_context.Init();

  ASSERT_EQ(typeid(result), typeid(new EitherPod<bool>{false, {}, true}));

  ASSERT_EQ(result->is_left, false);

  ASSERT_EQ(result->right, true);
}

TEST(AppContextTest, AppContextReleaseTest) {
  auto app_context = AppContext();

  app_context.Init();

  const auto result = app_context.Release();

  ASSERT_EQ(typeid(result), typeid(new EitherPod<bool>{false, {}, true}));

  ASSERT_EQ(result->is_left, false);

  ASSERT_EQ(result->right, true);
}

//
// Created by nim on 06.09.2021.
//
#include <app_context.h>
#include <gtest/gtest.h>
#include <smarteam/gateways/smarteam_gateway.h>

TEST(AppContextTest, AppContextSetTest) {
  auto context = AppContext();

  ASSERT_EQ(context.Size(), 0);

  const auto smarteam_gateway_ = SmarteamGateway();

  context.Set(typeid(SmarteamGateway).name(), std::any(smarteam_gateway_));

  ASSERT_EQ(context.Size(), 1);
}

TEST(AppContextTest, AppContextGetTest) {
  auto context = AppContext();

  const auto smarteam_gateway_ = SmarteamGateway();

  context.Set(typeid(SmarteamGateway).name(), std::any(smarteam_gateway_));

  const auto result_ = std::any_cast<SmarteamGateway>(context.Get(typeid(SmarteamGateway).name()));

  ASSERT_EQ(typeid(result_), typeid(SmarteamGateway));
}

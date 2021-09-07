//
// Created by nim on 19.07.2021.
//

#include "user_gateway_imp.h"

using BoolEither = UserGatewayImp::BoolEither;

UserGatewayImp::UserGatewayImp(const UserUseCases &user_use_case) noexcept : user_use_case{user_use_case} {}

EitherPod<bool> *UserGatewayImp::UserLogoff() noexcept {
  return user_use_case.UserLogoff()
      .Fold(
          [](const auto left) noexcept {
            return new EitherPod<bool>{true, gateway_helper::PodFromException(left)};
          },
          [](const auto right) noexcept {
            return new EitherPod<bool>{false, {}, true};
          });
}

EitherPod<bool> *UserGatewayImp::UserLogin(const wchar_t *username, const wchar_t *password) noexcept {

  return user_use_case.UserLogin(username, password)
      .Fold(
          [](const auto left) noexcept { return new EitherPod<bool>{true, gateway_helper::PodFromException(left)}; },
          [](const auto right) noexcept {
            return new EitherPod<bool>{false, {}, true};
          });
}

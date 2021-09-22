//
// Created by nim on 17.09.2021.
//

#include "crypto_gateway_imp.h"

CryptoGatewayImp::CryptoGatewayImp(const CryptoUseCases &crypto_use_cases) noexcept : crypto_use_cases{crypto_use_cases} {}

EitherPod<const char *> *CryptoGatewayImp::GetSid() noexcept {
  return crypto_use_cases.GetSid().Fold(
      [](const auto left) noexcept {
        return new EitherPod<const char *>{true, gateway_helper::PodFromException(left)};
      },
      [](const auto right) noexcept {
        return new EitherPod<const char *>{false, {}, gateway_helper::StringToCharPtr(right)};
      });
}

EitherPod<const char *> *CryptoGatewayImp::Encode(const wchar_t *text) noexcept {
  return crypto_use_cases.Encode(text).Fold(
      [](const auto left) noexcept {
        return new EitherPod<const char *>{true, gateway_helper::PodFromException(left)};
      },
      [](const auto right) noexcept {
        return new EitherPod<const char *>{false, {}, gateway_helper::StringToCharPtr(right)};
      });
}

EitherPod<const char *> *CryptoGatewayImp::Decode(const wchar_t *hex_text) noexcept {
  return crypto_use_cases.Decode(hex_text).Fold(
      [](const auto left) noexcept {
        std::cout << left.what() << std::endl;
        return new EitherPod<const char *>{true, gateway_helper::PodFromException(left)};
      },
      [](const auto right) noexcept {
        return new EitherPod<const char *>{false, {}, gateway_helper::StringToCharPtr(right)};
      });
}

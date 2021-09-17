//
// Created by nim on 17.09.2021.
//

#include "crypto_gateway_imp.h"

CryptoGatewayImp::CryptoGatewayImp(const CryptoUseCases &crypto_use_cases) noexcept : crypto_use_cases{crypto_use_cases} {}

EitherPod<const char *> *CryptoGatewayImp::Encode(const wchar_t *key, const wchar_t *text) noexcept {
  return new EitherPod<const char*>{};
}

EitherPod<const char *> *CryptoGatewayImp::Decode(const wchar_t *key, const wchar_t *hex_text) noexcept {
  return new EitherPod<const char*>{};
}

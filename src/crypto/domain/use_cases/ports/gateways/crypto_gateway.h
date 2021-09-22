//
// Created by nim on 17.09.2021.
//

#ifndef SMART_COM_SRC_CRYPTO_DOMAIN_USE_CASES_PORTS_GATEWAYS_CRYPTO_GATEWAY_H_
#define SMART_COM_SRC_CRYPTO_DOMAIN_USE_CASES_PORTS_GATEWAYS_CRYPTO_GATEWAY_H_

#include <monad/either.h>
#include <common/pods/either_pod.h>

class CryptoGateway {
 public:
  using CryptoGatewayPtr = std::shared_ptr<CryptoGateway>;

  virtual ~CryptoGateway() noexcept = default;

  virtual EitherPod<const char *> *GetSid() noexcept = 0;

  virtual EitherPod<const char *> *Encode(const wchar_t *text) noexcept = 0;

  virtual EitherPod<const char *> *Decode(const wchar_t *hex_text) noexcept = 0;
};

#endif//SMART_COM_SRC_CRYPTO_DOMAIN_USE_CASES_PORTS_GATEWAYS_CRYPTO_GATEWAY_H_

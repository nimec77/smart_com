//
// Created by nim on 17.09.2021.
//

#ifndef SMART_COM_SRC_CRYPTO_GATEWAYS_CRYPTO_GATEWAY_IMP_H_
#define SMART_COM_SRC_CRYPTO_GATEWAYS_CRYPTO_GATEWAY_IMP_H_

#include <common/helpers/geteway_helper.h>
#include <crypto/domain/use_cases/ports/gateways/crypto_gateway.h>
#include <crypto/domain/use_cases/crypto_use_cases.h>

class CryptoGatewayImp : public CryptoGateway {
 public:
  explicit CryptoGatewayImp(const CryptoUseCases &crypto_use_cases) noexcept;

  ~CryptoGatewayImp() noexcept override = default;

  EitherPod<const char *> *GetSid() noexcept override;

  EitherPod<const char *> *Encode(const wchar_t *text) noexcept override;

  EitherPod<const char *> *Decode(const wchar_t *hex_text) noexcept override;

 private:
  CryptoUseCases crypto_use_cases;
};

#endif//SMART_COM_SRC_CRYPTO_GATEWAYS_CRYPTO_GATEWAY_IMP_H_

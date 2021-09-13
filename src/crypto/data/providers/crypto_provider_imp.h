//
// Created by nim on 13.09.2021.
//

#ifndef SMART_COM_SRC_CRYPTO_DATA_PROVIDERS_CRYPTO_PROVIDER_IMP_H_
#define SMART_COM_SRC_CRYPTO_DATA_PROVIDERS_CRYPTO_PROVIDER_IMP_H_

#include <stdexcept>
#include <common/helpers/data_helper.h>
#include <crypto/data/ports/providers/crypto_provider.h>

#define NT_SUCCESS(status)  (((NTSTATUS)(status)) >= 0)

class CryptoProviderImp : public CryptoProvider {

 public:
  CryptoProviderImp() noexcept = default;

  virtual ~CryptoProviderImp() = default;

  BytesEither Md5Hash(const Bytes &data) noexcept override;
  BoolEither InitAes() noexcept override;
  BytesEither EncodeAes(const Bytes &key_data, const Bytes &data) noexcept override;
  BytesEither DecodeAes(const Bytes &data) noexcept override;
};

#endif//SMART_COM_SRC_CRYPTO_DATA_PROVIDERS_CRYPTO_PROVIDER_IMP_H_

//
// Created by nim on 13.09.2021.
//

#ifndef SMART_COM_SRC_CRYPTO_DATA_PORTS_PROVIDERS_CRYPTO_PROVIDER_H_
#define SMART_COM_SRC_CRYPTO_DATA_PORTS_PROVIDERS_CRYPTO_PROVIDER_H_

#include <common/base_types.h>
#include <memory>

class CryptoProvider {
 public:
  using CryptoProviderPtr = std::shared_ptr<CryptoProvider>;

  virtual ~CryptoProvider() noexcept = default;

  virtual BytesEither Md5Hash(const Bytes &data) noexcept = 0;

  virtual BytesEither EncodeAes(const Bytes &key_data, const Bytes &data) noexcept = 0;

  virtual BytesEither DecodeAes(const Bytes &key_data, const Bytes &data) noexcept = 0;
};

#endif//SMART_COM_SRC_CRYPTO_DATA_PORTS_PROVIDERS_CRYPTO_PROVIDER_H_

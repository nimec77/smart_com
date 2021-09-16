//
// Created by nim on 08.09.2021.
//

#ifndef SMART_COM_SRC_CRYPTO_DOMAIN_USE_CASES_PORTS_REPOSITORIES_CRYPTO_REPOSITORY_H_
#define SMART_COM_SRC_CRYPTO_DOMAIN_USE_CASES_PORTS_REPOSITORIES_CRYPTO_REPOSITORY_H_

#include <common/base_types.h>
#include <memory>

class CryptoRepository {
 public:
  using CryptoRepositoryPtr = std::shared_ptr<CryptoRepository>;

  virtual ~CryptoRepository() noexcept = default;

  virtual WStringEither GetSid() noexcept = 0;

  virtual StringEither Encode(std::wstring secret_key, std::wstring text) noexcept = 0;

  virtual StringEither Decode(std::wstring secret_key, std::wstring hex_value) noexcept = 0;

};

#endif//SMART_COM_SRC_CRYPTO_DOMAIN_USE_CASES_PORTS_REPOSITORIES_CRYPTO_REPOSITORY_H_

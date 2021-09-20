//
// Created by nim on 08.09.2021.
//

#ifndef SMART_COM_SRC_CRYPTO_DOMAIN_USE_CASES_CRYPTO_USE_CASES_H_
#define SMART_COM_SRC_CRYPTO_DOMAIN_USE_CASES_CRYPTO_USE_CASES_H_

#include <common/base_types.h>
#include <crypto/domain/use_cases/ports/repositories/crypto_repository.h>
#include <stdexcept>

class CryptoUseCases  {
 public:
  using CryptoUseCasesPtr = std::shared_ptr<CryptoUseCases>;

  explicit CryptoUseCases() noexcept = default;

  explicit CryptoUseCases(CryptoRepository::CryptoRepositoryPtr crypto_repository_ptr) noexcept;

  virtual ~CryptoUseCases() noexcept;

  StringEither Encode(const std::wstring& value) noexcept;

  StringEither Decode(const std::wstring& hex_value) noexcept;

 private:
  CryptoRepository::CryptoRepositoryPtr  crypto_repository_ptr{nullptr};
};

#endif//SMART_COM_SRC_CRYPTO_DOMAIN_USE_CASES_CRYPTO_USE_CASES_H_

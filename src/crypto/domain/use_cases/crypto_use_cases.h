//
// Created by nim on 08.09.2021.
//

#ifndef SMART_COM_SRC_CRYPTO_DOMAIN_USE_CASES_CRYPTO_USE_CASES_H_
#define SMART_COM_SRC_CRYPTO_DOMAIN_USE_CASES_CRYPTO_USE_CASES_H_

#include <crypto/domain/use_cases/ports/repositories/crypto_repository.h>
#include <stdexcept>

class CryptoUseCases  {
 public:
  using WStringEither = CryptoRepository::WStringEither;

  explicit CryptoUseCases(CryptoRepository::CryptoRepositoryPtr crypto_repository_ptr) noexcept;

  virtual ~CryptoUseCases() noexcept;

  WStringEither Encode(const wchar_t *value) noexcept;

  WStringEither Decode(const wchar_t *value) noexcept;

 private:
  CryptoRepository::CryptoRepositoryPtr  crypto_repository_ptr;
};

#endif//SMART_COM_SRC_CRYPTO_DOMAIN_USE_CASES_CRYPTO_USE_CASES_H_

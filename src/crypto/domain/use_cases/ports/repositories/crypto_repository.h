//
// Created by nim on 08.09.2021.
//

#ifndef SMART_COM_SRC_CRYPTO_DOMAIN_USE_CASES_PORTS_REPOSITORIES_CRYPTO_REPOSITORY_H_
#define SMART_COM_SRC_CRYPTO_DOMAIN_USE_CASES_PORTS_REPOSITORIES_CRYPTO_REPOSITORY_H_

#include <monad/either.h>
#include <memory>

class CryptoRepository {
 public:
  using CryptoRepositoryPtr = std::shared_ptr<CryptoRepository>;
  using WStringEither = monad::Either<std::exception, const wchar_t *>;

  virtual ~CryptoRepository() noexcept = default;

  virtual WStringEither Encode(const wchar_t *value) noexcept = 0;

  virtual WStringEither Decode(const wchar_t *value) noexcept = 0;
};

#endif//SMART_COM_SRC_CRYPTO_DOMAIN_USE_CASES_PORTS_REPOSITORIES_CRYPTO_REPOSITORY_H_

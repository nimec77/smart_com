//
// Created by nim on 08.09.2021.
//

#ifndef SMART_COM_SRC_CRYPTO_DATA_REPOSITORIES_CRYPTO_REPOSITORY_IMP_H_
#define SMART_COM_SRC_CRYPTO_DATA_REPOSITORIES_CRYPTO_REPOSITORY_IMP_H_

#include <crypto/data/ports/providers/token_provider.h>
#include <crypto/domain/use_cases/ports/repositories/crypto_repository.h>
#include <stdexcept>

class CryptoRepositoryImp : public CryptoRepository {
 public:
  explicit CryptoRepositoryImp(TokenProvider::TokenProviderPtr token_provider_ptr) noexcept;

  ~CryptoRepositoryImp() noexcept override;

  WStringEither Encode(const wchar_t *value) noexcept override;

  WStringEither Decode(const wchar_t *value) noexcept override;

 private:
  TokenProvider::TokenProviderPtr token_provider_ptr;
};

#endif//SMART_COM_SRC_CRYPTO_DATA_REPOSITORIES_CRYPTO_REPOSITORY_IMP_H_

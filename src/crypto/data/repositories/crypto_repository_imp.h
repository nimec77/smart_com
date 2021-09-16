//
// Created by nim on 08.09.2021.
//

#ifndef SMART_COM_SRC_CRYPTO_DATA_REPOSITORIES_CRYPTO_REPOSITORY_IMP_H_
#define SMART_COM_SRC_CRYPTO_DATA_REPOSITORIES_CRYPTO_REPOSITORY_IMP_H_

#include <common/base_types.h>
#include <common/helpers/helper.h>
#include <crypto/data/ports/providers/sid_provider.h>
#include <crypto/data/ports/providers/crypto_provider.h>
#include <crypto/domain/use_cases/ports/repositories/crypto_repository.h>
#include <stdexcept>

class CryptoRepositoryImp : public CryptoRepository {
 public:
  CryptoRepositoryImp(SidProvider::SidProviderPtr sid_provider_ptr,
                               CryptoProvider::CryptoProviderPtr crypto_provider_ptr) noexcept;

  ~CryptoRepositoryImp() noexcept override;

  WStringEither GetSid() noexcept override;

  StringEither Encode(const wchar_t *value) noexcept override;

  StringEither Decode(const wchar_t *value) noexcept override;

 private:
  SidProvider::SidProviderPtr sid_provider_ptr;
  CryptoProvider::CryptoProviderPtr crypto_provider_ptr;
};

#endif//SMART_COM_SRC_CRYPTO_DATA_REPOSITORIES_CRYPTO_REPOSITORY_IMP_H_

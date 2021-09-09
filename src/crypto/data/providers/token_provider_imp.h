//
// Created by nim on 09.09.2021.
//

#ifndef SMART_COM_SRC_CRYPTO_DATA_PROVIDERS_TOKEN_PROVIDER_IMP_H_
#define SMART_COM_SRC_CRYPTO_DATA_PROVIDERS_TOKEN_PROVIDER_IMP_H_

#include <crypto/data/ports/providers/token_provider.h>
#include <stdexcept>
#include <common/helpers/data_helper.h>
#include <Lmcons.h>
#include <sddl.h>

class TokenProviderImp : public TokenProvider {
 public:
  TokenProviderImp() noexcept = default;

  ~TokenProviderImp() noexcept override = default;

  WStringEither GetName() noexcept override;

  WStringEither GetAccountSidFromName(std::wstring username) noexcept override;
};

#endif//SMART_COM_SRC_CRYPTO_DATA_PROVIDERS_TOKEN_PROVIDER_IMP_H_

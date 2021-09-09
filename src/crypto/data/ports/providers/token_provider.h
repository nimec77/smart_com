//
// Created by nim on 08.09.2021.
//

#ifndef SMART_COM_SRC_CRYPTO_DATA_PORTS_PROVIDERS_TOKEN_PROVIDER_H_
#define SMART_COM_SRC_CRYPTO_DATA_PORTS_PROVIDERS_TOKEN_PROVIDER_H_

#include <common/base_types.h>
#include <memory>
#include <windows.h>

class TokenProvider {
 public:
  using TokenProviderPtr = std::shared_ptr<TokenProvider>;
  using TokenInformationPtr = std::shared_ptr<TOKEN_INFORMATION_CLASS>;
  using TokenInformationEither = monad::Either<std::exception, TokenInformationPtr>;

  virtual ~TokenProvider() noexcept = default;

  virtual WStringEither GetName() noexcept = 0;

  virtual WStringEither GetAccountSidFromName(std::wstring username) noexcept = 0;
};

#endif//SMART_COM_SRC_CRYPTO_DATA_PORTS_PROVIDERS_TOKEN_PROVIDER_H_

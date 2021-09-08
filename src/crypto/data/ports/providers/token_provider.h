//
// Created by nim on 08.09.2021.
//

#ifndef SMART_COM_SRC_CRYPTO_DATA_PORTS_PROVIDERS_TOKEN_PROVIDER_H_
#define SMART_COM_SRC_CRYPTO_DATA_PORTS_PROVIDERS_TOKEN_PROVIDER_H_

#include <monad/either.h>
#include <memory>
#include <windows.h>

class TokenProvider {
 public:
  using TokenProviderPtr = std::shared_ptr<TokenProvider>;
  using HandleEither = monad::Either<std::exception, std::shared_ptr<HANDLE>>;

  virtual HandleEither GetToken() noexcept = 0;
};

#endif//SMART_COM_SRC_CRYPTO_DATA_PORTS_PROVIDERS_TOKEN_PROVIDER_H_

//
// Created by nim on 08.09.2021.
//

#ifndef SMART_COM_SRC_CRYPTO_DATA_PORTS_PROVIDERS_SID_PROVIDER_H_
#define SMART_COM_SRC_CRYPTO_DATA_PORTS_PROVIDERS_SID_PROVIDER_H_

#include <common/base_types.h>
#include <memory>
#include <windows.h>

class SidProvider {
 public:
  using SidProviderPtr = std::shared_ptr<SidProvider>;

  virtual ~SidProvider() noexcept = default;

  virtual WStringEither GetName() noexcept = 0;

  virtual WStringEither GetAccountSidFromName(std::wstring username) noexcept = 0;
};

#endif//SMART_COM_SRC_CRYPTO_DATA_PORTS_PROVIDERS_SID_PROVIDER_H_

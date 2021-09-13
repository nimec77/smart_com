//
// Created by nim on 09.09.2021.
//

#ifndef SMART_COM_SRC_CRYPTO_DATA_PROVIDERS_SID_PROVIDER_IMP_H_
#define SMART_COM_SRC_CRYPTO_DATA_PROVIDERS_SID_PROVIDER_IMP_H_

#include <common/helpers/data_helper.h>
#include <crypto/data/ports/providers/sid_provider.h>
#include <sddl.h>
#include <stdexcept>

class SidProviderImp : public SidProvider {
 public:
  SidProviderImp() noexcept = default;

  ~SidProviderImp() noexcept override = default;

  WStringEither GetName() noexcept override;

  WStringEither GetAccountSidFromName(std::wstring username) noexcept override;
};

#endif//SMART_COM_SRC_CRYPTO_DATA_PROVIDERS_SID_PROVIDER_IMP_H_

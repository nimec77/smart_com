//
// Created by nim on 05.07.2021.
//

#ifndef SMART_COM_SMARTEAM_DATA_PROVIDERS_SMARTEAM_PROVIDER_H_
#define SMART_COM_SMARTEAM_DATA_PROVIDERS_SMARTEAM_PROVIDER_H_

#include <common/helpers/data_helper.h>
#include <iostream>
#include <monad/either.h>
#include <smarteam/constatns.h>
#include <sstream>
#include <windows.h>
#include <memory>

namespace smarteam {
class SmarteamProvider {
 public:
  using SmarteamProviderPtr = std::shared_ptr<SmarteamProvider>;
  using IDispatchEither = monad::Either<std::exception, IDispatch *>;
  using SmarteamEither = monad::Either<std::exception, SmarteamProviderPtr>;

  static SmarteamEither GetInstance() noexcept;

  virtual ~SmarteamProvider() noexcept;

  virtual IDispatchEither GetEngine() noexcept;

  SmarteamProvider(const SmarteamProvider &) = delete;

  void operator=(const SmarteamProvider &) = delete;

 private:
  IDispatch &engine;
  explicit SmarteamProvider(IDispatch &engine) noexcept;
};
}// namespace smarteam

#endif//SMART_COM_SMARTEAM_DATA_PROVIDERS_SMARTEAM_PROVIDER_H_

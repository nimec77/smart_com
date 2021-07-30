//
// Created by nim on 05.07.2021.
//

#ifndef SMART_COM_SMARTEAM_DATA_PROVIDERS_SMARTEAM_PROVIDER_H_
#define SMART_COM_SMARTEAM_DATA_PROVIDERS_SMARTEAM_PROVIDER_H_

#include <iostream>
#include <monad/either.h>
#include <smarteam/constatns.h>
#include <smarteam/data/data_helper.h>
#include <sstream>
#include <windows.h>

namespace smarteam {
class SmarteamProvider {
 public:
  using SmarteamEither = monad::Either<std::exception, SmarteamProvider *>;
  using IDispatchEither = monad::Either<std::exception, IDispatch *>;

  static SmarteamEither GetInstance() noexcept;

  virtual ~SmarteamProvider() noexcept;

  virtual IDispatchEither GetEngine() noexcept;

  SmarteamProvider(const SmarteamProvider &) = delete;

  void operator=(const SmarteamProvider &) = delete;

 private:
  IDispatch &smarteam_app;
  explicit SmarteamProvider(IDispatch &app);
};
}// namespace smarteam

#endif//SMART_COM_SMARTEAM_DATA_PROVIDERS_SMARTEAM_PROVIDER_H_

//
// Created by nim on 05.07.2021.
//

#ifndef SMART_COM_SMARTEAM_DATA_PROVIDERS_SMARTEAM_PROVIDER_H_
#define SMART_COM_SMARTEAM_DATA_PROVIDERS_SMARTEAM_PROVIDER_H_

#include <iostream>
#include <smarteam/constatns.h>
#include <smarteam/data/data_helper.h>
#include <sstream>
#include <windows.h>
#include <monad/either.h>

namespace smarteam {
class SmarteamProvider {
 public:
  using SmarteamEither = monad::Either<std::exception, SmarteamProvider>;
  static SmarteamEither SmarteamCreate(const wchar_t *prog_id);

  static SmarteamEither SmarteamFromActiveObject(const wchar_t *prog_id);

  virtual ~SmarteamProvider();

 private:
  IDispatchPtr smarteam_app{};
  explicit SmarteamProvider(IDispatch *smarteam_app);
};
}// namespace smarteam

#endif//SMART_COM_SMARTEAM_DATA_PROVIDERS_SMARTEAM_PROVIDER_H_

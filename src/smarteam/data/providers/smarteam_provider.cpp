//
// Created by nim on 05.07.2021.
//

#include "smarteam_provider.h"

namespace smarteam {
using SmarteamEither = SmarteamProvider::SmarteamEither;

SmarteamProvider::SmarteamProvider(IDispatch *smarteam_app) : smarteam_app(smarteam_app) {
  std::cout << "SmarteamProvider start" << std::endl;
}

SmarteamProvider::~SmarteamProvider() {
  std::cout << "~SmarteamProvider start" << std::endl;
  data_helper::SafeRelease(smarteam_app);
}

SmarteamEither SmarteamProvider::SmarteamCreate(const wchar_t *prog_id) {
  std::cout << "SmartreamProvider::SmarteamCreate start" << std::endl;

  return data_helper::GetClassId(prog_id).RightFlatMap([](auto clsid) {
    IDispatch* app{};
    auto hr = CoCreateInstance(clsid, nullptr, CLSCTX_LOCAL_SERVER, IID_IDispatch, (void **) &app);
    if (FAILED(hr)) {
      auto exception = std::runtime_error(data_helper::MakeErrorMessage("SmarteamProvider::SmarteamCreate CoCreateInstance error:", hr));
      return SmarteamEither::LeftOf(exception);
    }
    auto smarteam_provider = SmarteamProvider(app);
    return SmarteamEither::RightOf(smarteam_provider);
  });
}
SmarteamEither SmarteamProvider::SmarteamFromActiveObject(const wchar_t *prog_id) {
  std::cout << "SmartreamProvider::SmarteamFromActiveObject start" << std::endl;

  return data_helper::GetClassId(prog_id).RightFlatMap([](auto clsid) {
    IUnknown* i_unknown;
    auto hr = GetActiveObject(clsid, nullptr, &i_unknown);
    if (FAILED(hr)) {
      auto exception = std::runtime_error(data_helper::MakeErrorMessage("SmarteamProvider::SmarteamFromActiveObject GetActiveObject error:", hr));
      return SmarteamEither::LeftOf(exception);
    }
    IDispatch* app{};
    hr = i_unknown->QueryInterface(IID_IDispatch, (void **)&app);
    i_unknown->Release();
    if (FAILED(hr)) {
      auto exception = std::runtime_error(data_helper::MakeErrorMessage("SmarteamProvider::SmarteamFromActiveObject QueryInterface error:", hr));
      return SmarteamEither::LeftOf(exception);
    }
    auto smarteam_provider = SmarteamProvider(app);
    return SmarteamEither::RightOf(smarteam_provider);
  });
}

}// namespace smarteam

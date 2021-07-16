//
// Created by nim on 05.07.2021.
//

#include "smarteam_provider.h"

#include <utility>

namespace smarteam {
using SmarteamEither = SmarteamProvider::SmarteamEither;
using EngineEither = SmarteamProvider::IDispatchEither;

SmarteamProvider *smarteam_provider_ptr{};

SmarteamProvider::SmarteamProvider(IDispatch &app) : smarteam_app{app} {
  std::cout << "SmarteamProvider start" << std::endl;
}

SmarteamProvider::~SmarteamProvider() {
  std::cout << "~SmarteamProvider start" << std::endl;
  data_helper::SafeRelease((IDispatch *) &smarteam_app);
  smarteam_provider_ptr = nullptr;
}

SmarteamEither SmarteamProvider::GetInstance() {
  std::cout << "SmartreamProvider::GetInstance start" << std::endl;

  if (smarteam_provider_ptr != nullptr) {
    return SmarteamEither::RightOf(smarteam_provider_ptr);
  }
  return data_helper::GetClassId(kSmarTeamProdId).RightFlatMap([](const auto clsid) {
    IDispatch *app{};
    const auto hr = CoCreateInstance(clsid, nullptr, CLSCTX_LOCAL_SERVER, IID_IDispatch, (void **) &app);
    if (FAILED(hr)) {
      return SmarteamEither::LeftOf(
          std::runtime_error(data_helper::MakeErrorMessage("SmarteamProvider::SmarteamCreate CoCreateInstance error:", hr)));
    }
    smarteam_provider_ptr = new SmarteamProvider(*app);
    return SmarteamEither::RightOf(smarteam_provider_ptr);
  });
}

EngineEither SmarteamProvider::GetEngine() {
  return data_helper::GetNames(smarteam_app, kSmarTeamEngine).RightFlatMap([=, this](const auto dispid) {
    DISPPARAMS dp = {nullptr, nullptr, 0, 0};
    VARIANT result;
    VariantInit(&result);
    const auto hr = smarteam_app.Invoke(dispid, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_PROPERTYGET, &dp, &result,
                                  nullptr, nullptr);

    if (FAILED(hr)) {
      return IDispatchEither::LeftOf(
          std::runtime_error(
              data_helper::MakeErrorMessage("SmarteamProvider::GetEngine Invoke error:", hr)));
    }
    return IDispatchEither::RightOf(result.pdispVal);
  });
}

}// namespace smarteam

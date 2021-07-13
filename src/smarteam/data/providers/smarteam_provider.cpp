//
// Created by nim on 05.07.2021.
//

#include "smarteam_provider.h"

#include <utility>

namespace smarteam {
using SmarteamEither = SmarteamProvider::SmarteamEither;
using EngineEither = SmarteamProvider::EngineEither;

SmarteamProvider *smarteam_provider = nullptr;

SmarteamProvider::SmarteamProvider(IDispatch &app) : smarteam_app{app} {
  std::cout << "SmarteamProvider start" << std::endl;
}

SmarteamProvider::~SmarteamProvider() {
  std::cout << "~SmarteamProvider start" << std::endl;
  data_helper::SafeRelease(smarteam_app);
  smarteam_provider = nullptr;
}

SmarteamEither SmarteamProvider::GetInstance(const wchar_t *prog_id) {
  std::cout << "SmartreamProvider::GetInstance start" << std::endl;

  if (smarteam_provider != nullptr) {
    return SmarteamEither::RightOf(smarteam_provider);
  }
  return data_helper::GetClassId(prog_id).RightFlatMap([](const auto clsid) {
    IDispatch *app{};
    auto hr = CoCreateInstance(clsid, nullptr, CLSCTX_LOCAL_SERVER, IID_IDispatch, (void **) &app);
    if (FAILED(hr)) {
      auto exception = std::runtime_error(data_helper::MakeErrorMessage("SmarteamProvider::SmarteamCreate CoCreateInstance error:", hr));
      return SmarteamEither::LeftOf(exception);
    }
    smarteam_provider = new SmarteamProvider(*app);
    return SmarteamEither::RightOf(smarteam_provider);
  });
}

SmarteamEither SmarteamProvider::GetInstance() {
  if (smarteam_provider == nullptr) {
    auto exception = std::runtime_error("SmarteamProvider::GetInstance error: First you need to create an object of the class");
    return SmarteamEither::LeftOf(exception);
  }
  return SmarteamEither::RightOf(smarteam_provider);
}

EngineEither SmarteamProvider::GetEngine() {
  return data_helper::GetNames(smarteam_app, kSmarTeamEngine).RightFlatMap([=, this](const auto dispid) {
    DISPPARAMS dp = {nullptr, nullptr, 0, 0};
    VARIANT result;
    VariantInit(&result);
    auto hr = this->smarteam_app.Invoke(dispid, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_PROPERTYGET, &dp, &result,
                                        nullptr, nullptr);

    if (FAILED(hr)) {
      auto exception = std::runtime_error(
          data_helper::MakeErrorMessage("SmarteamProvider::GetEngine Invoke error:", hr));
      return EngineEither::LeftOf(exception);
    }
    return EngineEither::RightOf(result.pdispVal);
  });
}

}// namespace smarteam

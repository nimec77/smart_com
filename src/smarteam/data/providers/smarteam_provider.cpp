//
// Created by nim on 05.07.2021.
//

#include "smarteam_provider.h"

#include <utility>

namespace smarteam {
using SmarteamEither = SmarteamProvider::SmarteamEither;

SmarteamProvider *smarteam_provider = nullptr;

SmarteamProvider::SmarteamProvider(IDispatch &app) : smarteam_app(app) {
  std::cout << "SmarteamProvider start" << std::endl;
}

SmarteamProvider::~SmarteamProvider() {
  std::cout << "~SmarteamProvider start" << std::endl;
  data_helper::SafeRelease(smarteam_app);
  smarteam_provider = nullptr;
}

SmarteamEither SmarteamProvider::SmarteamCreate(const wchar_t *prog_id) {
  std::cout << "SmartreamProvider::SmarteamCreate start" << std::endl;

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
SmarteamEither SmarteamProvider::SmarteamFromActiveObject(const wchar_t *prog_id) {
  std::cout << "SmartreamProvider::SmarteamFromActiveObject start" << std::endl;

  if (smarteam_provider != nullptr) {
    return SmarteamEither::RightOf(smarteam_provider);
  }
  return data_helper::GetClassId(prog_id).RightFlatMap([](auto clsid) {
    IUnknown *i_unknown;
    auto hr = GetActiveObject(clsid, nullptr, &i_unknown);
    if (FAILED(hr)) {
      auto exception = std::runtime_error(data_helper::MakeErrorMessage("SmarteamProvider::SmarteamFromActiveObject GetActiveObject error:", hr));
      return SmarteamEither::LeftOf(exception);
    }
    IDispatch *app{};
    hr = i_unknown->QueryInterface(IID_IDispatch, (void **) &app);
    i_unknown->Release();
    if (FAILED(hr)) {
      auto exception = std::runtime_error(data_helper::MakeErrorMessage("SmarteamProvider::SmarteamFromActiveObject QueryInterface error:", hr));
      return SmarteamEither::LeftOf(exception);
    }
    smarteam_provider = new SmarteamProvider(*app);
    return SmarteamEither::RightOf(smarteam_provider);
  });
}
SmarteamEither SmarteamProvider::GetInstance() {
  if (smarteam_provider == nullptr) {
    auto exception = std::runtime_error("First you need to create an object of the class");
    return SmarteamEither::LeftOf(exception);
  }
  return SmarteamEither::RightOf(smarteam_provider);
}

using EngineEither = SmarteamProvider::EngineEither;

//EngineEither SmarteamProvider::GetEngine() {
//  auto dispatch_id = data_helper::get_names(reinterpret_cast<IDispatch &>(*smarteam_app), L"Engine");
//  DISPPARAMS dp = {nullptr, nullptr, 0, 0 };
//  VARIANT result;
//  VariantInit(&result);
//  auto hr = smarteam_app->Invoke(0, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_PROPERTYGET, &dp, &result,
//                                 nullptr, nullptr);
//  if (FAILED(hr)) {
//    std::string error = "SmarteamProvider::get_engine error:" + std::to_string(hr);
//    std::cerr << error << std::endl;
//    throw std::exception(error.c_str());
//  }
//
//  return EngineEither::RightOf(result.pdispVal);
//}
}// namespace smarteam

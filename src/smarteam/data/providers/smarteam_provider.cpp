//
// Created by nim on 05.07.2021.
//

#include "smarteam_provider.h"

#include <utility>

namespace smarteam {
using IDispatchEither = SmarteamProvider::IDispatchEither;
using SmarteamEither = SmarteamProvider::SmarteamEither;

SmarteamProvider *smarteam_provider_ptr{};

SmarteamProvider::SmarteamProvider(IDispatch &engine) noexcept : engine{engine} {
}

SmarteamProvider::~SmarteamProvider() noexcept {
  std::cout << "~SmarteamProvider" << std::endl;
  data_helper::SafeRelease(&engine);
  smarteam_provider_ptr = nullptr;
}

SmarteamEither SmarteamProvider::GetInstance() noexcept {
  if (smarteam_provider_ptr != nullptr) {
    return SmarteamEither::RightOf(smarteam_provider_ptr);
  }
  return data_helper::GetClassId(kSmarTeamProdId)
      .RightFlatMap([](const auto clsid) noexcept {
        IDispatch *app_{};

        IUnknown *i_unknown_;
        auto hr_ = GetActiveObject(clsid, nullptr, &i_unknown_);
        if (SUCCEEDED(hr_)) {
          hr_ = i_unknown_->QueryInterface(IID_IDispatch, (void **) &app_);
          if (SUCCEEDED(hr_)) {
            smarteam_provider_ptr = new SmarteamProvider(*app_);
            return SmarteamEither::RightOf(smarteam_provider_ptr);
          }
        }
        hr_ = CoCreateInstance(clsid, nullptr, CLSCTX_LOCAL_SERVER, IID_IDispatch, (void **) &app_);
        if (FAILED(hr_)) {
          return SmarteamEither::LeftOf(
              std::runtime_error(data_helper::MakeErrorMessage("SmarteamProvider::GetInstance CoCreateInstance error:", hr_)));
        }
        smarteam_provider_ptr = new SmarteamProvider(*app_);
        return SmarteamEither::RightOf(smarteam_provider_ptr);
      });
}

IDispatchEither SmarteamProvider::GetEngine() noexcept {
  return data_helper::GetNames(engine, kSmarTeamEngine)
      .RightFlatMap([=, this](const auto dispid) noexcept {
        DISPPARAMS dp_ = {nullptr, nullptr, 0, 0};
        VARIANT result_;
        VariantInit(&result_);
        const auto hr_ = engine.Invoke(dispid, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_PROPERTYGET, &dp_, &result_,
                                             nullptr, nullptr);

        if (FAILED(hr_)) {
          return IDispatchEither::LeftOf(
              std::runtime_error(
                  data_helper::MakeErrorMessage("SmarteamProvider::GetEngine Invoke error:", hr_)));
        }
        return IDispatchEither::RightOf(result_.pdispVal);
      });
}

}// namespace smarteam

//
// Created by nim on 13.07.2021.
//

#include "engine_provider.h"

namespace smarteam {
using IDispatchEither = EngineProvider::IDispatchEither;
using EngineProviderEither = EngineProvider::EngineProviderEither;

EngineProvider *engine_provider_ptr{};

EngineProvider::EngineProvider(IDispatch &app) noexcept : engine_app{app} {}

EngineProvider::~EngineProvider() noexcept {
  std::cout << "~EngineProvider" << std::endl;
  data_helper::SafeRelease((IDispatch *) &engine_app);
  engine_provider_ptr = nullptr;
}

EngineProvider *EngineProvider::GetInstance(IDispatch *app) noexcept {
  if (engine_provider_ptr == nullptr) {
    engine_provider_ptr = new EngineProvider(*app);
  }

  return engine_provider_ptr;
}

EngineProviderEither EngineProvider::GetInstance() noexcept {
  if (engine_provider_ptr != nullptr) {
    return EngineProviderEither::RightOf(engine_provider_ptr);
  }

  return EngineProviderEither::LeftOf(std::runtime_error("Null pointer exception"));
}

IDispatchEither EngineProvider::CreateSession(const _bstr_t &application_name, const _bstr_t &configuration_name) noexcept {
  return data_helper::GetNames(engine_app, kCreateSession)
      .RightFlatMap([this, application_name, configuration_name](const auto dispid) noexcept {
        DISPPARAMS dp_ = {nullptr, nullptr, 0, 0};

        VARIANT args_[2];
        args_[0].vt = VT_BSTR;
        args_[0].bstrVal = configuration_name;
        args_[1].vt = VT_BSTR;
        args_[1].bstrVal = application_name;
        dp_.rgvarg = args_;
        dp_.cArgs = 2;
        dp_.cNamedArgs = 0;

        VARIANT result_;
        VariantInit(&result_);
        const auto hr_ = engine_app.Invoke(dispid, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &dp_, &result_,
                                           nullptr, nullptr);
        for (auto &arg_ : args_) {
          VariantClear(&arg_);
        }
        if (FAILED(hr_)) {
          IDispatchEither::LeftOf(
              std::runtime_error(data_helper::MakeErrorMessage("EngineProvider::CreateSession Invoke error:", hr_)));
        }

        return IDispatchEither::RightOf(result_.pdispVal);
      });
}
IDispatchEither EngineProvider::GetDatabase(long index) noexcept {
  return data_helper::GetNames(engine_app, kDatabases).RightFlatMap([this, index](const auto dispid) noexcept {
    DISPPARAMS dp_ = {nullptr, nullptr, 0, 0};

    VARIANT base_index_;
    base_index_.vt = VT_INT;
    base_index_.intVal = index;
    dp_.rgvarg = &base_index_;
    dp_.cArgs = 1;
    dp_.cNamedArgs = 0;

    VARIANT result_;
    VariantInit(&result_);
    const auto hr_ = engine_app.Invoke(dispid, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_PROPERTYGET, &dp_, &result_,
                                       nullptr, nullptr);
    VariantClear(&base_index_);

    if (FAILED(hr_)) {
      IDispatchEither::LeftOf(
          std::runtime_error(data_helper::MakeErrorMessage("EngineProvider::GetDatabase Invoke error:", hr_)));
    }

    return IDispatchEither::RightOf(result_.pdispVal);
  });
}

}// namespace smarteam
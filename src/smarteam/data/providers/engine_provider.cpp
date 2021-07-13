//
// Created by nim on 13.07.2021.
//

#include "engine_provider.h"

namespace smarteam {
using EngineEither = EngineProvider::EngineEither;
using IDispatchEither = EngineProvider::IDispatchEither;

EngineProvider *engine_provider_ptr = nullptr;

EngineProvider::EngineProvider(IDispatch &app) : engine_app{app} {
  std::cout << "EngineProvider start" << std::endl;
}

EngineProvider::~EngineProvider() {
  std::cout << "~EngineProvider start" << std::endl;
  data_helper::SafeRelease((IDispatch *) &engine_app);
  engine_provider_ptr = nullptr;
}

EngineEither EngineProvider::GetInstance(IDispatch *app) {
  std::cout << "EngineProvider::GetInstance start" << std::endl;
  if (engine_provider_ptr == nullptr) {
    engine_provider_ptr = new EngineProvider(*app);
  }

  return EngineEither::RightOf(engine_provider_ptr);
}
IDispatchEither EngineProvider::CreateSession(const _bstr_t &application_name, const _bstr_t &configuration_name) {
  return data_helper::GetNames(engine_app, kCreateSession)
      .RightFlatMap([this, application_name, configuration_name](const auto dispid) {
        DISPPARAMS dp = {nullptr, nullptr, 0, 0};

        VARIANT args[2];
        args[0].vt = VT_BSTR;
        args[0].bstrVal = configuration_name;
        args[1].vt = VT_BSTR;
        args[1].bstrVal = application_name;
        dp.rgvarg = args;
        dp.cArgs = 2;
        dp.cNamedArgs = 0;

        VARIANT result;
        VariantInit(&result);
        auto hr = engine_app.Invoke(dispid, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &dp, &result,
                                    nullptr, nullptr);
        for (auto &arg : args) {
          VariantClear(&arg);
        }
        if (FAILED(hr)) {
          auto exception = std::runtime_error(data_helper::MakeErrorMessage("EngineProvider::CreateSession Invoke error:", hr));
          IDispatchEither::LeftOf(exception);
        }

        return IDispatchEither::RightOf(result.pdispVal);
      });
}

}// namespace smarteam
//
// Created by nim on 13.07.2021.
//

#ifndef SMART_COM_SRC_SMARTEAM_DATA_PROVIDERS_ENGINE_PROVIDER_H_
#define SMART_COM_SRC_SMARTEAM_DATA_PROVIDERS_ENGINE_PROVIDER_H_

#include <common/base_types.h>
#include <common/helpers/data_helper.h>
#include <iostream>
#include <smarteam/constatns.h>
#include <windows.h>
#include <memory>

namespace smarteam {
class EngineProvider {
 public:
  using EngineProviderPtr = std::shared_ptr<EngineProvider>;
  using EngineProviderEither = monad::Either<std::exception, EngineProviderPtr>;

  static EngineProviderPtr GetInstance(IDispatch *app) noexcept;

  static EngineProviderEither GetInstance() noexcept;

  virtual ~EngineProvider() noexcept;

  virtual IDispatchEither CreateSession(const _bstr_t& application_name, const _bstr_t& configuration_name) noexcept;

  virtual IDispatchEither GetDatabase(long index) noexcept;

  EngineProvider(const EngineProvider &) = delete;

  void operator=(const EngineProvider &) = delete;

 private:
  IDispatch &engine_app;
  explicit EngineProvider(IDispatch &app) noexcept;
};

}// namespace smarteam

#endif//SMART_COM_SRC_SMARTEAM_DATA_PROVIDERS_ENGINE_PROVIDER_H_

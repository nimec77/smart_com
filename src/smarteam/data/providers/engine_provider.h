//
// Created by nim on 13.07.2021.
//

#ifndef SMART_COM_SRC_SMARTEAM_DATA_PROVIDERS_ENGINE_PROVIDER_H_
#define SMART_COM_SRC_SMARTEAM_DATA_PROVIDERS_ENGINE_PROVIDER_H_

#include <iostream>
#include <monad/either.h>
#include <smarteam/constatns.h>
#include <smarteam/data/data_helper.h>
#include <windows.h>

namespace smarteam {
class EngineProvider {
 public:
  using EngineEither = monad::Either<std::exception, EngineProvider *>;
  using IDispatchEither = monad::Either<std::exception, IDispatch *>;

  static EngineEither GetInstance(IDispatch *app);

  virtual ~EngineProvider();

  virtual IDispatchEither CreateSession(const _bstr_t& application_name, const _bstr_t& configuration_name);

  virtual IDispatchEither GetDatabase(long index);

  EngineProvider(const EngineProvider &) = delete;

  void operator=(const EngineProvider &) = delete;

 private:
  IDispatch &engine_app;
  explicit EngineProvider(IDispatch &app);
};

}// namespace smarteam

#endif//SMART_COM_SRC_SMARTEAM_DATA_PROVIDERS_ENGINE_PROVIDER_H_

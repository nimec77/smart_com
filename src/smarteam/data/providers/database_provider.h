//
// Created by nim on 13.07.2021.
//

#ifndef SMART_COM_SRC_SMARTEAM_DATA_PROVIDERS_DATABASE_PROVIDER_H_
#define SMART_COM_SRC_SMARTEAM_DATA_PROVIDERS_DATABASE_PROVIDER_H_

#include <common/helpers/data_helper.h>
#include <iostream>
#include <monad/either.h>
#include <smarteam/constatns.h>
#include <windows.h>
#include <memory>

namespace smarteam {
class DatabaseProvider {
 public:
  using DatabaseProviderPtr = std::shared_ptr<DatabaseProvider>;
  using BstrEither = monad::Either<std::exception, _bstr_t>;
  using DatabaseProviderEither = monad::Either<std::exception, DatabaseProviderPtr>;

  static DatabaseProviderPtr GetInstance(IDispatch *app) noexcept;

  static DatabaseProviderEither GetInstance() noexcept;

  virtual ~DatabaseProvider() noexcept;

  virtual BstrEither GetAlias() noexcept;

  virtual BstrEither GetPassword() noexcept;

  DatabaseProvider(const DatabaseProvider &) = delete;

  void operator=(const DatabaseProvider &) = delete;

 private:
  IDispatch &database_app;
  explicit DatabaseProvider(IDispatch &app) noexcept;
};
}// namespace smarteam

#endif//SMART_COM_SRC_SMARTEAM_DATA_PROVIDERS_DATABASE_PROVIDER_H_

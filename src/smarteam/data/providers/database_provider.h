//
// Created by nim on 13.07.2021.
//

#ifndef SMART_COM_SRC_SMARTEAM_DATA_PROVIDERS_DATABASE_PROVIDER_H_
#define SMART_COM_SRC_SMARTEAM_DATA_PROVIDERS_DATABASE_PROVIDER_H_

#include <iostream>
#include <monad/either.h>
#include <smarteam/constatns.h>
#include <smarteam/data/data_helper.h>
#include <windows.h>

namespace smarteam {
class DatabaseProvider {
 public:
  using DatabaseEither = monad::Either<std::exception, DatabaseProvider *>;
  using BstrEither = monad::Either<std::exception, _bstr_t>;

  static DatabaseEither GetInstance(IDispatch *app);

  virtual ~DatabaseProvider();

  virtual BstrEither GetAlias();

  virtual BstrEither GetPassword();

  DatabaseProvider(const DatabaseProvider &) = delete;

  void operator=(const DatabaseProvider &) = delete;

 private:
  IDispatch &database_app;
  explicit DatabaseProvider(IDispatch &app);
};
}// namespace smarteam

#endif//SMART_COM_SRC_SMARTEAM_DATA_PROVIDERS_DATABASE_PROVIDER_H_

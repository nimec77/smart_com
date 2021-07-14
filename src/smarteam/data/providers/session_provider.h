//
// Created by nim on 13.07.2021.
//

#ifndef SMART_COM_SRC_SMARTEAM_DATA_PROVIDERS_SESSION_PROVIDER_H_
#define SMART_COM_SRC_SMARTEAM_DATA_PROVIDERS_SESSION_PROVIDER_H_

#include <iostream>
#include <monad/either.h>
#include <smarteam/constatns.h>
#include <smarteam/data/data_helper.h>
#include <windows.h>

namespace smarteam {
class SessionProvider {
 public:
  using IDispatchEither = monad::Either<std::exception, IDispatch *>;
  using BoolEither = monad::Either<std::exception, bool>;

  static SessionProvider* GetInstance(IDispatch *app) noexcept;

  virtual ~SessionProvider();

  virtual IDispatchEither OpenDatabaseConnection(_bstr_t& connection_string,
                                                 _bstr_t& database_password,
                                                 bool password_is_encoded);

  virtual BoolEither UserLogin(_bstr_t& user_name, _bstr_t& password);

  virtual BoolEither UserLoggedOn();

  SessionProvider(const SessionProvider &) = delete;

  void operator=(const SessionProvider &) = delete;

 private:
  IDispatch &session_app;
  explicit SessionProvider(IDispatch &app) noexcept;
};
}// namespace smarteam

#endif//SMART_COM_SRC_SMARTEAM_DATA_PROVIDERS_SESSION_PROVIDER_H_

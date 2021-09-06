//
// Created by nim on 13.07.2021.
//

#ifndef SMART_COM_SRC_SMARTEAM_DATA_PROVIDERS_SESSION_PROVIDER_H_
#define SMART_COM_SRC_SMARTEAM_DATA_PROVIDERS_SESSION_PROVIDER_H_

#include <common/helpers/data_helper.h>
#include <iostream>
#include <monad/either.h>
#include <smarteam/constatns.h>
#include <smarteam/domain/enums/password_type.h>
#include <windows.h>

namespace smarteam {
class SessionProvider {
 public:
  using IDispatchEither = monad::Either<std::exception, IDispatch *>;
  using BoolEither = monad::Either<std::exception, bool>;
  using SessionProviderEither = monad::Either<std::exception, SessionProvider*>;

  static SessionProvider* GetInstance(IDispatch *app) noexcept;

  static SessionProviderEither GetInstance() noexcept;

  virtual ~SessionProvider() noexcept;

  virtual IDispatchEither OpenDatabaseConnection(const _bstr_t& connection_string,
                                                 const _bstr_t& database_password,
                                                 PasswordType password_type) noexcept;

  virtual BoolEither UserLogin(const _bstr_t& user_name, const _bstr_t& password) noexcept;

  virtual BoolEither UserLoggedOn() noexcept;

  virtual BoolEither UserLogoff() noexcept;

  SessionProvider(const SessionProvider &) = delete;

  void operator=(const SessionProvider &) = delete;

 private:
  IDispatch &session_app;
  explicit SessionProvider(IDispatch &app) noexcept;
};
}// namespace smarteam

#endif//SMART_COM_SRC_SMARTEAM_DATA_PROVIDERS_SESSION_PROVIDER_H_

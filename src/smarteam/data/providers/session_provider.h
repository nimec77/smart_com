//
// Created by nim on 13.07.2021.
//

#ifndef SMART_COM_SRC_SMARTEAM_DATA_PROVIDERS_SESSION_PROVIDER_H_
#define SMART_COM_SRC_SMARTEAM_DATA_PROVIDERS_SESSION_PROVIDER_H_

#include <common/base_types.h>
#include <common/helpers/data_helper.h>
#include <iostream>
#include <monad/either.h>
#include <smarteam/constatns.h>
#include <smarteam/domain/enums/password_type.h>
#include <windows.h>
#include <memory>

namespace smarteam {
class SessionProvider {
 public:
  using SessionProviderPtr = std::shared_ptr<SessionProvider>;
  using SessionProviderEither = monad::Either<std::exception, SessionProviderPtr>;

  static SessionProviderPtr GetInstance(IDispatch *app) noexcept;

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

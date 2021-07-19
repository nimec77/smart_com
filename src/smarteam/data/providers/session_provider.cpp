//
// Created by nim on 13.07.2021.
//

#include "session_provider.h"

namespace smarteam {
using IDispatchEither = SessionProvider::IDispatchEither;
using BoolEither = SessionProvider::BoolEither;

SessionProvider *session_provider_ptr{};

SessionProvider::SessionProvider(IDispatch &app) noexcept : session_app{app} {
  std::cout << "SessionProvider start" << std::endl;
}

SessionProvider::~SessionProvider() {
  std::cout << "~SessionProvider start" << std::endl;
  data_helper::SafeRelease((IDispatch *) &session_app);
  session_provider_ptr = nullptr;
}

SessionProvider *SessionProvider::GetInstance(IDispatch *app) noexcept {
  std::cout << "SessionProvider::GetInstance start" << std::endl;
  if (session_provider_ptr == nullptr) {
    session_provider_ptr = new SessionProvider(*app);
  }

  return session_provider_ptr;
}

IDispatchEither SessionProvider::OpenDatabaseConnection(const _bstr_t &connection_string, const _bstr_t &database_password, PasswordType password_type) {
  return data_helper::GetNames(session_app, kOpenDatabaseConnection)
      .RightFlatMap([this, connection_string, database_password, password_type](const auto dispid) {
        DISPPARAMS dp_ = {nullptr, nullptr, 0, 0};

        VARIANT args_[3];
        args_[0].vt = VT_BOOL;
        args_[0].boolVal = password_type == Encoded ? VARIANT_TRUE : VARIANT_FALSE;
        args_[1].vt = VT_BSTR;
        args_[1].bstrVal = database_password;
        args_[2].vt = VT_BSTR;
        args_[2].bstrVal = connection_string;
        dp_.rgvarg = args_;
        dp_.cArgs = 3;
        dp_.cNamedArgs = 0;

        VARIANT result_;
        VariantInit(&result_);
        const auto hr_ = session_app.Invoke(dispid, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &dp_, &result_,
                                     nullptr, nullptr);
        for (auto &arg_ : args_) {
          VariantClear(&arg_);
        }
        if (FAILED(hr_)) {
          IDispatchEither::LeftOf(
              std::runtime_error(
                  data_helper::MakeErrorMessage("SessionProvider::OpenDatabaseConnection Invoke error:", hr_)));
        }

        return IDispatchEither::RightOf(result_.pdispVal);
      });
}

BoolEither SessionProvider::UserLogin(const _bstr_t &user_name, const _bstr_t &password) {
  return data_helper::GetNames(session_app, kUserLogin).RightFlatMap([this, user_name, password](const auto dispid) {
    DISPPARAMS dp_ = {nullptr, nullptr, 0, 0};

    VARIANT args_[2];
    args_[0].vt = VT_BSTR;
    args_[0].bstrVal = password;
    args_[1].vt = VT_BSTR;
    args_[1].bstrVal = user_name;
    dp_.rgvarg = args_;
    dp_.cArgs = 2;
    dp_.cNamedArgs = 0;

    VARIANT result_;
    VariantInit(&result_);
    const auto hr_ = session_app.Invoke(dispid, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &dp_, &result_,
                                 nullptr, nullptr);
    if (FAILED(hr_)) {
      return BoolEither::LeftOf(
          std::runtime_error(
              data_helper::MakeErrorMessage("SessionProvider::UserLogin Invoke error:", hr_)));
    }

    return BoolEither::RightOf(result_.boolVal == VARIANT_TRUE);
  });
}
BoolEither SessionProvider::UserLoggedOn() {
  return data_helper::GetNames(session_app, kUserLoggedOn).RightFlatMap([this](const auto dispid) {
    DISPPARAMS dp_ = {nullptr, nullptr, 0, 0};
    VARIANT result_;
    VariantInit(&result_);
    const auto hr_ = session_app.Invoke(dispid, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_PROPERTYGET, &dp_, &result_,
                                 nullptr, nullptr);
    if (FAILED(hr_)) {
      return BoolEither::LeftOf(
          std::runtime_error(
              data_helper::MakeErrorMessage("SessionProvider::UserLoggedOn Invoke error:", hr_)));
    }

    return BoolEither::RightOf(result_.boolVal == VARIANT_TRUE);
  });
}
BoolEither SessionProvider::UserLogoff() {
  return data_helper::GetNames(session_app, kUserLogoff).RightFlatMap([this](const auto dispid) {
    DISPPARAMS dp_ = {nullptr, nullptr, 0, 0};

    const auto hr_ = session_app.Invoke(dispid, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &dp_, nullptr,
                                 nullptr, nullptr);

    if (FAILED(hr_)) {
      return BoolEither::LeftOf(
          std::runtime_error(
              data_helper::MakeErrorMessage("SessionProvider::UserLogoff Invoke error:", hr_)));
    }

    return BoolEither::RightOf(true);
  });
}

}// namespace smarteam
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

IDispatchEither SessionProvider::OpenDatabaseConnection(const _bstr_t &connection_string, const _bstr_t &database_password, bool password_is_encoded) {
  return data_helper::GetNames(session_app, kOpenDatabaseConnection)
      .RightFlatMap([this, connection_string, database_password, password_is_encoded](const auto dispid) {
        DISPPARAMS dp = {nullptr, nullptr, 0, 0};

        VARIANT args[3];
        args[0].vt = VT_BOOL;
        args[0].boolVal = password_is_encoded ? VARIANT_TRUE : VARIANT_FALSE;
        args[1].vt = VT_BSTR;
        args[1].bstrVal = database_password;
        args[2].vt = VT_BSTR;
        args[2].bstrVal = connection_string;
        dp.rgvarg = args;
        dp.cArgs = 3;
        dp.cNamedArgs = 0;

        VARIANT result;
        VariantInit(&result);
        const auto hr = session_app.Invoke(dispid, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &dp, &result,
                                     nullptr, nullptr);
        for (auto &arg : args) {
          VariantClear(&arg);
        }
        if (FAILED(hr)) {
          IDispatchEither::LeftOf(
              std::runtime_error(
                  data_helper::MakeErrorMessage("SessionProvider::OpenDatabaseConnection Invoke error:", hr)));
        }

        return IDispatchEither::RightOf(result.pdispVal);
      });
}

BoolEither SessionProvider::UserLogin(const _bstr_t &user_name, const _bstr_t &password) {
  return data_helper::GetNames(session_app, kUserLogin).RightFlatMap([this, user_name, password](const auto dispid) {
    DISPPARAMS dp = {nullptr, nullptr, 0, 0};

    VARIANT args[2];
    args[0].vt = VT_BSTR;
    args[0].bstrVal = password;
    args[1].vt = VT_BSTR;
    args[1].bstrVal = user_name;
    dp.rgvarg = args;
    dp.cArgs = 2;
    dp.cNamedArgs = 0;

    VARIANT result;
    VariantInit(&result);
    const auto hr = session_app.Invoke(dispid, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &dp, &result,
                                 nullptr, nullptr);
    if (FAILED(hr)) {
      return BoolEither::LeftOf(
          std::runtime_error(
              data_helper::MakeErrorMessage("SessionProvider::UserLogin Invoke error:", hr)));
    }

    return BoolEither::RightOf(result.boolVal == VARIANT_TRUE);
  });
}
BoolEither SessionProvider::UserLoggedOn() {
  return data_helper::GetNames(session_app, kUserLoggedOn).RightFlatMap([this](const auto dispid) {
    DISPPARAMS dp = {nullptr, nullptr, 0, 0};
    VARIANT result;
    VariantInit(&result);
    const auto hr = session_app.Invoke(dispid, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_PROPERTYGET, &dp, &result,
                                 nullptr, nullptr);
    if (FAILED(hr)) {
      return BoolEither::LeftOf(
          std::runtime_error(
              data_helper::MakeErrorMessage("SessionProvider::UserLoggedOn Invoke error:", hr)));
    }

    return BoolEither::RightOf(result.boolVal == VARIANT_TRUE);
  });
}
BoolEither SessionProvider::UserLogoff() {
  return data_helper::GetNames(session_app, kUserLogoff).RightFlatMap([this](const auto dispid) {
    DISPPARAMS dp = {nullptr, nullptr, 0, 0};

    const auto hr = session_app.Invoke(dispid, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &dp, nullptr,
                                 nullptr, nullptr);

    if (FAILED(hr)) {
      return BoolEither::LeftOf(
          std::runtime_error(
              data_helper::MakeErrorMessage("SessionProvider::UserLogoff Invoke error:", hr)));
    }

    return BoolEither::RightOf(true);
  });
}

}// namespace smarteam
//
// Created by nim on 13.07.2021.
//

#include "database_provider.h"

namespace smarteam {
using DatabaseEither = DatabaseProvider::DatabaseEither;
using BstrEither = DatabaseProvider::BstrEither;

DatabaseProvider *database_provider_ptr;

DatabaseProvider::DatabaseProvider(IDispatch &app) : database_app{app} {
  std::cout << "DatabaseProvider start" << std::endl;
}

DatabaseProvider::~DatabaseProvider() {
  std::cout << "~DatabaseProvider start" << std::endl;
  data_helper::SafeRelease((IDispatch *) &database_app);
  database_provider_ptr = nullptr;
}

DatabaseEither DatabaseProvider::GetInstance(IDispatch *app) {
  std::cout << "DatabaseProvider::GetInstance start" << std::endl;
  if (database_provider_ptr == nullptr) {
    database_provider_ptr = new DatabaseProvider(*app);
  }
  return DatabaseEither::RightOf(database_provider_ptr);
}
BstrEither DatabaseProvider::GetAlias() {
  return data_helper::GetNames(database_app, kAlias)
      .RightFlatMap([this](const auto dispid) {
        DISPPARAMS dp = {nullptr, nullptr, 0, 0};

        VARIANT result;
        VariantInit(&result);
        auto hr = database_app.Invoke(dispid, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_PROPERTYGET, &dp, &result,
                                      nullptr, nullptr);
        VariantClear(&result);

        if (FAILED(hr)) {
          const auto exception = std::runtime_error(data_helper::MakeErrorMessage("DatabaseProvider::GetAlias Invoke error:", hr));
          BstrEither ::LeftOf(exception);
        }

        auto alias = _bstr_t(result.bstrVal);
        return BstrEither::RightOf(alias);
      });
}
BstrEither DatabaseProvider::GetPassword() {
  return data_helper::GetNames(database_app, kPassword)
      .RightFlatMap([this](const auto dispid) {
        DISPPARAMS dp = {nullptr, nullptr, 0, 0};

        VARIANT result;
        VariantInit(&result);
        auto hr = database_app.Invoke(dispid, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_PROPERTYGET, &dp, &result,
                                      nullptr, nullptr);
        VariantClear(&result);

        if (FAILED(hr)) {
          const auto exception = std::runtime_error(data_helper::MakeErrorMessage("DatabaseProvider::GetPassword Invoke error:", hr));
          BstrEither ::LeftOf(exception);
        }

        auto password = _bstr_t(result.bstrVal);
        return BstrEither::RightOf(password);
      });
}

}// namespace smarteam
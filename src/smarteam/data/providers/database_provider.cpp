//
// Created by nim on 13.07.2021.
//

#include "database_provider.h"

namespace smarteam {
using DatabaseProviderPtr = DatabaseProvider::DatabaseProviderPtr;
using DatabaseProviderEither = DatabaseProvider::DatabaseProviderEither;

DatabaseProviderPtr database_provider_ptr;

DatabaseProvider::DatabaseProvider(IDispatch &app) noexcept : database_app{app} {}

DatabaseProvider::~DatabaseProvider() noexcept {
  std::cout << "~DatabaseProvider" << std::endl;
  helper::SafeRelease(&database_app);
  database_provider_ptr.reset();
}

DatabaseProviderPtr DatabaseProvider::GetInstance(IDispatch *app) noexcept {
  if (!database_provider_ptr) {
    database_provider_ptr = DatabaseProviderPtr(new DatabaseProvider(*app));
  }
  return database_provider_ptr;
}

DatabaseProviderEither DatabaseProvider::GetInstance() noexcept {
  if (database_provider_ptr != nullptr) {
    return DatabaseProviderEither::RightOf(database_provider_ptr);
  }

  return DatabaseProviderEither::LeftOf(std::runtime_error("Null pointer exception"));
}


BstrEither DatabaseProvider::GetAlias() noexcept {
  return helper::GetNames(database_app, kAlias)
      .RightFlatMap([this](const auto dispid) noexcept {
        DISPPARAMS dp_ = {nullptr, nullptr, 0, 0};

        VARIANT result_;
        VariantInit(&result_);
        const auto hr_ = database_app.Invoke(dispid, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_PROPERTYGET, &dp_, &result_,
                                      nullptr, nullptr);
        VariantClear(&result_);

        if (FAILED(hr_)) {
          BstrEither ::LeftOf(std::runtime_error(helper::MakeErrorMessage("DatabaseProvider::GetAlias Invoke error:", hr_)));
        }

        return BstrEither::RightOf(_bstr_t(result_.bstrVal));
      });
}
BstrEither DatabaseProvider::GetPassword() noexcept {
  return helper::GetNames(database_app, kPassword)
      .RightFlatMap([this](const auto dispid) noexcept {
        DISPPARAMS dp_ = {nullptr, nullptr, 0, 0};

        VARIANT result_;
        VariantInit(&result_);
        const auto hr_ = database_app.Invoke(dispid, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_PROPERTYGET, &dp_, &result_,
                                      nullptr, nullptr);
        VariantClear(&result_);

        if (FAILED(hr_)) {
          BstrEither::LeftOf(
              std::runtime_error(helper::MakeErrorMessage("DatabaseProvider::GetPassword Invoke error:", hr_)));
        }

        return BstrEither::RightOf(_bstr_t(result_.bstrVal));
      });
}

}// namespace smarteam
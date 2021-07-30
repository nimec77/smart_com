//
// Created by nim on 13.07.2021.
//

#include "database_provider.h"

namespace smarteam {
using BstrEither = DatabaseProvider::BstrEither;
using DatabaseProviderEither = DatabaseProvider::DatabaseProviderEither;

DatabaseProvider *database_provider_ptr{};

DatabaseProvider::DatabaseProvider(IDispatch &app) noexcept : database_app{app} {}

DatabaseProvider::~DatabaseProvider() noexcept {
  std::cout << "~DatabaseProvider" << std::endl;
  data_helper::SafeRelease((IDispatch *) &database_app);
  database_provider_ptr = nullptr;
}

DatabaseProvider *DatabaseProvider::GetInstance(IDispatch *app) noexcept {
  if (database_provider_ptr == nullptr) {
    database_provider_ptr = new DatabaseProvider(*app);
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
  return data_helper::GetNames(database_app, kAlias)
      .RightFlatMap([this](const auto dispid) noexcept {
        DISPPARAMS dp_ = {nullptr, nullptr, 0, 0};

        VARIANT result_;
        VariantInit(&result_);
        const auto hr_ = database_app.Invoke(dispid, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_PROPERTYGET, &dp_, &result_,
                                      nullptr, nullptr);
        VariantClear(&result_);

        if (FAILED(hr_)) {
          BstrEither ::LeftOf(std::runtime_error(data_helper::MakeErrorMessage("DatabaseProvider::GetAlias Invoke error:", hr_)));
        }

        return BstrEither::RightOf(_bstr_t(result_.bstrVal));
      });
}
BstrEither DatabaseProvider::GetPassword() noexcept {
  return data_helper::GetNames(database_app, kPassword)
      .RightFlatMap([this](const auto dispid) noexcept {
        DISPPARAMS dp_ = {nullptr, nullptr, 0, 0};

        VARIANT result_;
        VariantInit(&result_);
        const auto hr_ = database_app.Invoke(dispid, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_PROPERTYGET, &dp_, &result_,
                                      nullptr, nullptr);
        VariantClear(&result_);

        if (FAILED(hr_)) {
          BstrEither::LeftOf(
              std::runtime_error(data_helper::MakeErrorMessage("DatabaseProvider::GetPassword Invoke error:", hr_)));
        }

        return BstrEither::RightOf(_bstr_t(result_.bstrVal));
      });
}

}// namespace smarteam
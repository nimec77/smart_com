//
// Created by nim on 13.07.2021.
//

#include "database_provider.h"

namespace smarteam {
using BstrEither = DatabaseProvider::BstrEither;

DatabaseProvider *database_provider_ptr{};

DatabaseProvider::DatabaseProvider(IDispatch &app) noexcept : database_app{app} {
  std::cout << "DatabaseProvider start" << std::endl;
}

DatabaseProvider::~DatabaseProvider() {
  std::cout << "~DatabaseProvider start" << std::endl;
  data_helper::SafeRelease((IDispatch *) &database_app);
  database_provider_ptr = nullptr;
}

DatabaseProvider *DatabaseProvider::GetInstance(IDispatch *app) noexcept {
  std::cout << "DatabaseProvider::GetInstance start" << std::endl;
  if (database_provider_ptr == nullptr) {
    database_provider_ptr = new DatabaseProvider(*app);
  }
  return database_provider_ptr;
}

BstrEither DatabaseProvider::GetAlias() {
  return data_helper::GetNames(database_app, kAlias)
      .RightFlatMap([this](const auto dispid) {
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
BstrEither DatabaseProvider::GetPassword() {
  return data_helper::GetNames(database_app, kPassword)
      .RightFlatMap([this](const auto dispid) {
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
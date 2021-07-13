//
// Created by nim on 13.07.2021.
//

#include "database_provider.h"

namespace smarteam {
using DatabaseEither = DatabaseProvider::DatabaseEither;

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

}// namespace smarteam
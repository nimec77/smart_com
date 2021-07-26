//
// Created by nim on 19.07.2021.
//

#include "user_gateway_imp.h"

using BoolEither = UserGateway::BoolEither;

UserGatewayImp::UserGatewayImp(SmarteamRepository& smarteam_repository) : smarteam_repository(smarteam_repository) {
}

UserGateway::BoolEither UserGatewayImp::UserLogoff() {
  return smarteam_repository.UserLoggedOn()
      .RightFlatMap([this](const auto is_user_logged_on) {
        return is_user_logged_on ? smarteam_repository.UserLogoff() : BooEither::RightOf(true);
      });
}

BoolEither UserGatewayImp::UserLogin(const wchar_t* user_name, const wchar_t* password) {

  std::wcout << user_name << std::endl;
  return smarteam_repository.UserLogin( _bstr_t{user_name},  _bstr_t{password});
}
